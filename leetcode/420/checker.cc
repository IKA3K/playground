#include "checker.h"

#include <cstring>
#include <utility>
#include <vector>

#include "absl/log/log.h"

int pwdchecker(absl::string_view s) {
  LOG(INFO) << "checking string " << s;
  // Problem statement:
  // A password is considered strong if the below conditions are all met:
  // * It has at least 6 characters and at most 20 characters.
  // * It contains at least one lowercase letter, at least one uppercase letter, and at least one digit.
  // * It does not contain three repeating characters in a row (i.e., "Baaabb0" is weak, but "Baaba0" is strong).
  //
  // Given a string password, return the minimum number of steps required
  // to make password strong. if password is already strong, return 0.
  //
  // In one step, you can:
  // * Insert one character to password,
  // * Delete one character from password, or
  // * Replace one character of password with another character.

  int min_length = 6;
  int max_length = 20;
  // Thinking out aloud:
  //
  // Step 0:
  // There's one case where the answer is already clear, and that's when the password
  // is 1 or 2 characters; it doesn't matter what the characters are because there's
  // no 3-in-a-row-repeating. Return 6-length immediately.
  if (s.length() < 3) {
    LOG(INFO) << "short circuit";
    return min_length - s.length();
  }
  // Step 1:
  // The 3-in-a-row is hardest to meet, and should be checked first, looking
  // for the ability to change the character to something else (but don't
  // add it to the count yet, since it could be usable for another section).
  //
  // Step 2:
  // Once the locations are found, move onto checking what characters are remaining
  // and seeing what characters are needed to make the password strong, first
  // making sure length is up to 6. After that, start going through ranges.
  //
  // Step 3:
  //
  // If there is any instance of a string 3 characters in a row, use
  // one immediately to switch the other two types, making sure to check the 4th
  // character to ensure it doesn't cause another repeating pattern.
  //
  // If there are no missing char types, just change the 3rd character so
  // that it no longer matches the next character, e.g.:
  // 'aaaaaaa' -> 'aaAaaaa' -> 'aaAaaAa'
  //
  // Step 4:
  // Lastly, if the password > 20 chars, add the delta to the
  // count.

  // Keep track of the number of repeating ranges.
  std::vector<std::pair<int, int> > repeating_ranges;
  bool has_lower_case = false;
  bool has_upper_case = false;
  bool has_digit = false;

  int num_repeats = 0;
  for (int i = 0; i < s.size(); ++i) {
    // Check for character types if any of the bools are still false.
    if (!has_lower_case && std::islower(s[i])) {
      has_lower_case = true;
    }
    if (!has_upper_case && std::isupper(s[i])) {
      has_upper_case = true;
    }
    if (!has_digit && std::isdigit(s[i])) {
      has_digit = true;
    }

    if (i == 0) {
      continue;  // Special case for first char.
    }

    if (s[i-1] == s[i]) {
      ++num_repeats;
    } else {
      num_repeats = 0;
    }

    if (num_repeats == 2) {
      // Add range.
      repeating_ranges.push_back(std::pair<int, int>(i-2, i));
    } else if (num_repeats > 2) {
      // Update previous range.
      repeating_ranges.back().second = i;
    }
  }

  int applied_changes = 0;

  // Before checking the ranges, check if the length is still < 6.
  std::vector<bool*> fix_up = {&has_digit, &has_lower_case, &has_upper_case};
  int needed_extra_chars = (min_length - s.length());
  for (bool* has_type : fix_up) {
    if (needed_extra_chars <= 0) {
      break;
    }
    // Add 1 for every bool that is not yet flipped to true .
    if (!*has_type) {
      *has_type = true;
      ++applied_changes;
      --needed_extra_chars;
    }
  }
  // If there are still any remaining extra chars, add them all to applied changes.
  // (e.g. if we have all the types of chars already).
  if (needed_extra_chars > 0) {
    applied_changes += needed_extra_chars;
  }

  LOG(INFO) << "Applied changes before checking repeating ranges: " << applied_changes;
  for (auto [front_index, back_index] : repeating_ranges) {
    LOG(INFO) << "Inspecting range [" << front_index << "," << back_index << "]";
    int length = back_index - front_index + 1;
    // Min num changes is length / 3.
    int min_changes = length / 3;
    // See if we can reuse any changes.
    int reused_changes = 0;
    for (bool* has_char : fix_up) {
      if (reused_changes <= min_changes) {
        ++reused_changes;
        *has_char = true;
      }
    }
    applied_changes += min_changes;
  }
  LOG(INFO) << "Applied changes after checking repeating ranges: " << applied_changes;
  // Add 1 for every bool that is not yet flipped to true.
  for (bool* has_type : fix_up) {
    applied_changes += *has_type ? 0 : 1;
  }
  // Lastly, add changes for length if it's still too long
  if (s.length() > max_length) {
    applied_changes += (max_length - s.length());
  }
  LOG(INFO) << "Final changes: " << applied_changes;
  return applied_changes;
}