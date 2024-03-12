#ifndef MEMORY_CACHE_LRU_CACHE_H
#define MEMORY_CACHE_LRU_CACHE_H

#include <cstddef>
#include <cstdint>
#include <list>
#include <map>
#include <memory>
#include <optional>
#include <utility>

#include "absl/base/thread_annotations.h"
#include "absl/synchronization/mutex.h"

namespace memory {
namespace cache {

// LRUCache provides caching for 
template<typename Key, typename Value>
class LRUCache {
 public:
  // Creats an LRUCache that can hold up to `size` elements.
  explicit LRUCache(size_t size);

  // Caches the value `v` at location `k`.
  // 
  // Caching an item automatically promotes the key `k` to be the newest
  // element, even if it wasn't used before.
  //
  // If an object was evicted to make room, the key of the value thrown out is returned.
  std::optional<Key> Cache(const Key& k, const Value& v) ABSL_LOCKS_EXCLUDED(m_);

  // Attempts to get the value at value `k`.
  // Returns nullptr if not found in cache.
  std::shared_ptr<Value> Get(const Key& k) ABSL_LOCKS_EXCLUDED(m_);

  size_t current_size() ABSL_LOCKS_EXCLUDED(m_) {
    absl::ReaderMutexLock lock(&m_);
    return cache_.size();
  }

 private:
  // Updates cache location
  void UpdateQueueLocation(const Key& k) ABSL_EXCLUSIVE_LOCKS_REQUIRED(m_);

  // Max number of elements to hold.
  size_t size_;
  // Cache of value + location of the key inside the queue (if it updates, we )
  std::map<Key, std::pair<std::shared_ptr<Value> , typename std::list<Key>::iterator> > cache_ ABSL_GUARDED_BY(m_);
  // Keeps track of which items have been used and in which order.
  std::list<Key> usage_queue_ ABSL_GUARDED_BY(m_);
  // Lock to allow multi-threaded access to both the cache.
  absl::Mutex m_;
};

// Implementation
template<typename Key, typename Value>
LRUCache<Key, Value>::LRUCache(size_t size) : size_(size) {}

template<typename Key, typename Value>
std::optional<Key> LRUCache<Key, Value>::Cache(const Key& k, const Value& v) {
  absl::WriterMutexLock lock(&m_);

  // Existing item. Update the value, and remove the item from the queue
  // and push it back.
  if (cache_.count(k)) {
    cache_[k].first = std::make_shared<Value>(v);  // Override value.
    // Update the location of the iter to the end.
    UpdateQueueLocation(k);

    // Return nothing, as no key was added.
    return std::nullopt;
  }

  // New item.
  std::optional<Key> discarded_key;
  if (usage_queue_.size() == size_) {
    // Pop the first item, and drop it from the cache.
    discarded_key = usage_queue_.front();
    usage_queue_.pop_front();
    cache_.erase(*discarded_key);
  }

  // Add k to the end of the queue first (since we want cache_.count(k) to return 0)
  // in the call.
  UpdateQueueLocation(k);
  // Add the new item.
  cache_[k].first = std::make_shared<Value>(v);
  return discarded_key;
}

template<typename Key, typename Value>
std::shared_ptr<Value> LRUCache<Key, Value>::Get(const Key& k) {
  absl::WriterMutexLock lock(&m_);
  if (!cache_.count(k)) {
    return nullptr;
  }
  // Update location in queue.
  UpdateQueueLocation(k);
  return cache_[k].first;
}

template<typename Key, typename Value>
void LRUCache<Key, Value>::UpdateQueueLocation(const Key& k) {
  if (cache_.count(k)) {
    typename std::list<Key>::iterator iter = cache_.at(k).second;
    usage_queue_.erase(iter);
  }
  usage_queue_.push_back(k);
  // Promote k to newest element.
  typename std::list<Key>::iterator new_iter = usage_queue_.end();
  --new_iter;
  cache_[k].second = new_iter;
} 

}  // namespace cache
}  // namespace memory

#endif  // MEMORY_CACHE_LRU_CACHE_H