#include "lru_cache.h"

#include <cstdlib>
#include <ctime>
#include <thread>

#include "absl/log/log.h"
#include "absl/synchronization/barrier.h"
#include "absl/time/time.h"
#include "gtest/gtest.h"

namespace {

TEST(LRUCacheTest, TestBasicCacheBehavior) {
  // Max 4 values.
  memory::cache::LRUCache<int, int> cache(4);

  LOG(INFO) << "Testing initialization";
  EXPECT_EQ(cache.current_size(), 0) << "Current size is not zero";
  EXPECT_EQ(cache.Get(0), nullptr) << "Found an object that shouldn't have been there";

  LOG(INFO) << "Testing adding new KVs";
  EXPECT_EQ(cache.Cache(0, 0), std::nullopt);
  EXPECT_EQ(*cache.Get(0), 0);
  EXPECT_EQ(cache.current_size(), 1);

  EXPECT_EQ(cache.Cache(1, 1), std::nullopt);
  EXPECT_EQ(cache.current_size(), 2);
  EXPECT_EQ(*cache.Get(1), 1);

  EXPECT_EQ(cache.Cache(2, 2), std::nullopt);
  EXPECT_EQ(cache.current_size(), 3);
  EXPECT_EQ(*cache.Get(2), 2);

  EXPECT_EQ(cache.Cache(3, 3), std::nullopt);
  EXPECT_EQ(cache.current_size(), 4);
  EXPECT_EQ(*cache.Get(3), 3);

  LOG(INFO) << "Testing adding new KV beyond size";
  EXPECT_EQ(cache.Cache(4, 4), 0);  // Evicts 0.
  EXPECT_EQ(cache.current_size(), 4);
  EXPECT_EQ(*cache.Get(4), 4);
  EXPECT_TRUE(cache.Get(0) == nullptr);

  // Normally adding 5 should evict 1 next, but let's Get(1), which should force 2 to the front.
  EXPECT_EQ(*cache.Get(1), 1);
  EXPECT_EQ(cache.Cache(5, 5), 2);  // Evicted 2 instead of 1.
  EXPECT_EQ(cache.current_size(), 4);

  // Next evictions should then be 3, 4, and finally 1.
  EXPECT_EQ(cache.Cache(6, 6), 3);
  EXPECT_EQ(cache.Cache(7, 7), 4);
  EXPECT_EQ(cache.Cache(8, 8), 1);

  // Also test updates to the cache by replacing values with negative versions.
  EXPECT_EQ(*cache.Get(5), 5);
  EXPECT_EQ(cache.Cache(5, -5), std::nullopt);
  EXPECT_EQ(*cache.Get(5), -5);

  EXPECT_EQ(*cache.Get(6), 6);
  EXPECT_EQ(cache.Cache(6, -6), std::nullopt);
  EXPECT_EQ(*cache.Get(6), -6);

  EXPECT_EQ(*cache.Get(7), 7);
  EXPECT_EQ(cache.Cache(7, -7), std::nullopt);
  EXPECT_EQ(*cache.Get(7), -7);

  EXPECT_EQ(*cache.Get(8), 8);
  EXPECT_EQ(cache.Cache(8, -8), std::nullopt);
  EXPECT_EQ(*cache.Get(8), -8);
}

TEST(LRUCacheTest, TestMultiThreading) {
  // Tests that the cache doesn't fall over when doing random things across random threads.
  // Allow only up to 4 values for maximum insanity.
  memory::cache::LRUCache<int, int> threadsafe_cache(4);

  {
    LOG(INFO) << "Creating threads";
    // Create a whole bunch of threads in a vector and have them spam the heck out of the cache.
    int num_threads = 10;
    absl::Barrier barrier(num_threads);
    absl::Duration wasted_duration = absl::Seconds(0.100);  // Run for 100ms

    std::srand(std::time(nullptr));
    auto cache_populator = [&threadsafe_cache, &barrier, wasted_duration] (int thread_num) {
      LOG(INFO) << "Waiting in thread " << thread_num;
      barrier.Block();
      LOG(INFO) << "Populating in thread " << thread_num;
      absl::Time start = absl::Now();
      while (absl::Now() - start < wasted_duration) {        
        threadsafe_cache.Cache(std::rand() * 10000, std::rand() * 10000);
      }
      LOG(INFO) << "Exiting thread " << thread_num;
    };
    std::vector<std::thread> threads;
    threads.reserve(num_threads);
    for (int i = 0; i < num_threads; ++i) {
      threads.emplace_back(std::thread(cache_populator, i));
    }
    for (int i = 0; i < num_threads; ++i) {
      threads[i].join();
    }
  }

  // Expect that we don't have anything weird happen.
  EXPECT_EQ(threadsafe_cache.current_size(), 4);
}

}  // namespace
