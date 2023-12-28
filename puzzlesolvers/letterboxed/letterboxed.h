#ifndef PUZZLESOLVERS_LETTERBOXED_LETTERBOXED_H
#define PUZZLESOLVERS_LETTERBOXED_LETTERBOXED_H

#include <set>
#include <string>

#include "absl/strings/string_view.h"
#include "puzzlesolvers/common/dictionary.h"

namespace puzzlesolvers {

struct Box {
  std::set<char> top;
  std::set<char> right;
  std::set<char> bottom;
  std::set<char> left;

  // Returns the set of next usable words, sorted by longest length first.
  std::vector<absl::string_view> NextWords(char current_char);
  // Returns true if the word provided by `s` can be produced by this graph.
  bool IsValidWord(absl::string_view s);
  // Returns the next set of characters that can be selected from
  std::set<char> Next(char c);
};

// Convenience wrapper for a string of words.
typedef std::vector<absl::string_view> Path;

// Solver for the NY Times puzzle game Letter Boxed.
// https://www.nytimes.com/puzzles/letter-boxed
class LetterBoxed {
 public:
  explicit LetterBoxed(const Dictionary& dictionary);

  // Given a 4-sided box, return valid paths, with the shortest path
  // returned first.
  std::vector<Path> FindPaths(Box box);

 private:
  const Dictionary& dictionary_;  // Not owned.
};

}  // namespace puzzlesolvers