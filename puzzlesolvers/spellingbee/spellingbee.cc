#include "puzzlesolvers/spellingbee/spellingbee.h"

#include "absl/flags/flag.h"
#include "puzzlesolvers/spellingbee/set_intersection.h"

ABSL_FLAG(int, min_span, 4, "Require at least N characters per span");

namespace puzzlesolvers {
  
std::set<absl::string_view> SpellingBee::FindWords(std::set<char> characters) {
  // Sanity check that characters only contains lowercase alpha.
  for (char c : characters) {
    if (!isalpha(c) || !islower(c)) {
      LOG(FATAL) << "only supports lowercase, passed " << c;
    }
  }

  std::set<absl::string_view> output;
  // Create every permutation of intersection.
  auto iter = characters.begin();
  for (; iter != characters.end(); ++iter) {
    auto next = iter;
    ++next;
    for (; next != characters.end(); ++next) { 
      std::vector<const std::set<absl::string_view>*> v;
      v.reserve(characters.size());
      const auto& words_by_char = dictionary_.words_by_char();
      auto span_start = iter;
      auto span_end = next;
      bool span_too_short = false;
      for (int min_span = absl::GetFlag(FLAGS_min_span);
           min_span > 0;
           --min_span) {
        if (span_end == characters.end()) {
          span_too_short = true;
          break;
        }
        ++span_end;
      }
      if (span_too_short) {
        break;
      }
      std::string s;
      while (span_start != span_end) {
        s += *span_start;
        v.push_back(&words_by_char.at(*span_start));
        ++span_start;
      }
      LOG(INFO) << "Looking for words w/combination " << s;
      std::set<absl::string_view> intersection = Intersection<absl::string_view>(v);
      LOG(INFO) << "Found " << intersection.size() << " words containing characters";
      // Insert into word set.
      output.insert(intersection.begin(), intersection.end());
    }
  }

  // Trim words that contain characters outside of the character set.
  std::set<absl::string_view> trimmed_output;
  int skipped_words;
  std::for_each(output.begin(), output.end(),
                [&trimmed_output, &skipped_words, characters](
                    absl::string_view word) {
    for (char c : word) {
      if (characters.count(c) == 0) {
        ++skipped_words;
        return;
      }
    }
    trimmed_output.insert(word);
  });
  LOG(INFO) << "Found " << output.size() << " words, "
            << trimmed_output.size() << " words after trimming "
            << skipped_words << " words";
  return trimmed_output;
}

}  // namespace puzzlesolvers