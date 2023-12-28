#ifndef PUZZLESOLVERS_SPELLINGBEE_SPELLINGBEE_H
#define PUZZLESOLVERS_SPELLINGBEE_SPELLINGBEE_H

#include "puzzlesolvers/common/dictionary.h"

#include <set>
#include <string>

#include "absl/strings/string_view.h"

namespace puzzlesolvers {

// Solver for the NYT Spelling Bee puzzle game.
// https://www.nytimes.com/puzzles/spelling-bee
class SpellingBee {
 public:
  explicit SpellingBee(const Dictionary& dictionary) : dictionary_(dictionary) {}
  ~SpellingBee() = default;
  SpellingBee(const SpellingBee&) = delete;

  // Returns words that match the characters provided.
  std::set<absl::string_view> FindWords(std::set<char> characters, char required_char);

 private:
  const Dictionary& dictionary_;  // Not owned.
};

}  // namespace puzzlesolvers

#endif  // PUZZLESOLVERS_SPELLINGBEE_SPELLINGBEE_H