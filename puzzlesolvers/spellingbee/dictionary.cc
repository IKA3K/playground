#include "puzzlesolvers/spellingbee/dictionary.h"

#include <fstream>
#include <string>

#include "absl/flags/flag.h"
#include "absl/log/log.h"
#include "absl/memory/memory.h"
#include "absl/status/status.h"

ABSL_FLAG(std::string, dictionary_path, "/tmp/words.txt", "Path to words file, 1 per line.");
ABSL_FLAG(int, min_word_length, 4, "Minimum word length to accept in dictionary.");

namespace puzzlesolvers {

Dictionary::Dictionary(std::set<std::string> words) {
  words_ = std::move(words);

  int min_length = absl::GetFlag(FLAGS_min_word_length);
  int words_skipped = 0;
  for (const auto& word : words_) {
    if (word.size() < min_length) {
      ++words_skipped;
      continue;
    }

    bool is_ok = true;
    for (const char c : word) {
      if (!isalpha(c) || !islower(c)) {
        ++words_skipped;
        is_ok = false;
        break;
      }
    }
    if (is_ok) {
      for (const char c : word) {
        // Intentionally reference location in memory.
        auto [iter, inserted] = words_by_char_[c].insert(absl::string_view(word.c_str()));
        if (inserted) {
          LOG_EVERY_N(INFO, 1000) << "Inserted word: " << *iter;
        }
      }
    }
  }
  LOG(INFO) << "Created dictionary with " << words_.size() << " (" << words_skipped << " skipped).";
}

absl::StatusOr<std::unique_ptr<Dictionary>> Dictionary::MakeDictionaryFromPath(absl::string_view path) {
  std::ifstream ifs(path.data());
  if (!ifs) {
    return absl::NotFoundError("Can't find file");
  }
  std::string line;
  std::set<std::string> words;
  while (std::getline(ifs, line)) {
    words.insert(line);
  }

  LOG(INFO) << "Loaded " << words.size() << " words from disk.";
  return absl::make_unique<Dictionary>(words);
}

}  // namespace puzzlesolvers