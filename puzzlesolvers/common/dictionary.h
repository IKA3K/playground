#ifndef PUZZLESOLVERS_COMMON_DICTIONARY_H
#define PUZZLESOLVERS_COMMON_DICTIONARY_H

#include <set>
#include <string>

#include "absl/container/flat_hash_map.h"
#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"

namespace puzzlesolvers {

// Intentionally references locations in memory; requires that a stable word pool is referenced.
typedef absl::flat_hash_map<char, std::set<absl::string_view>> WordsByCharMap;

// Dictionary of words addressable by character to solve char-by-char puzzle
// games.
// Designed to be used in combination with Intersection (set_intersection.h).
class Dictionary {
 public:
  // Exposed for allowing 
  explicit Dictionary(std::set<std::string> words); 
  virtual ~Dictionary() = default;
  Dictionary(const Dictionary&) = delete;

  static absl::StatusOr<std::unique_ptr<Dictionary>> MakeDictionaryFromPath(absl::string_view path);

  virtual const WordsByCharMap& words_by_char() const {
    return words_by_char_;
  }

 private:
  std::set<std::string> words_;
  WordsByCharMap words_by_char_;
};

}  // namespace puzzlesolvers

#endif  // PUZZLESOLVERS_COMMON_DICTIONARY_H