#include "puzzlesolvers/letterboxed/letterboxed.h"

#include "absl/flags/flag.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/str_cat.h"

ABSL_FLAG(int, min_word_length, 3, "Minimum valid word length.");

namespace puzzlesolvers {

// Returns the set of next usable words, sorted by longest length first.
std::vector<absl::string_view> Box::NextWords(char current_char) {
  
}

// Returns true if the word provided by `s` can be produced by this graph.
bool Box::IsValidWord(absl::string_view s) {
  if (s.length() < absl::GetFlag(FLAGS_min_word_length)) {
    return false;
  }
  std::set<char> all_chars = merged_sets({top, bottom, left, right});
  if (!all_chars.contains(s[0])) {
    return false;
  }
  std::set<char> next = Next(s[0]);
  for (size_t i = 1; i < s.size(); ++i) {
    if (!all_chars.contains(s[i]) ||
        !next.contains(s[i])) {
      return false;
    }
    next = Next(s[i]);
  }
  return true;
}

// Returns the next set of characters that can be selected.
absl::StatusOr<std::set<char>> Box::Next(char c) {
  if (top.contains(c)) {
    return merged({left, right, bottom});
  }
  if (right.contains(c)) {
    return merged({top, left, bottom});
  }
  if (bottom.contains(c)) {
    return merged({top, left, right});
  }
  if (left.contains(c)) {
    return merged({top, right, bottom});
  }
  return absl::NotFoundError(absl::StrCat("Invalid char ", c));
}
  
}  // namespace puzzlesolvers