#include <string>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/strings/string_view.h"
#include "dictionary.h"
#include "puzzlesolvers/spellingbee/dictionary.h"
#include "puzzlesolvers/spellingbee/spellingbee.h"
#include "spellingbee.h"

ABSL_FLAG(std::string, dictionary, "/tmp/words.txt", "Dictionary location");
ABSL_FLAG(std::string, characters, "", "Set of characters to use to find words");

int main(int argc, char** argv) {
  absl::ParseCommandLine(argc, argv);

  std::string character_str = absl::GetFlag(FLAGS_characters);
  std::string dictionary_path = absl::GetFlag(FLAGS_dictionary);
  LOG(INFO) << "Finding words with character set " << character_str;
  LOG(INFO) << "Loading dictionary from " << dictionary_path;
  auto status_or_dictionary =
      puzzlesolvers::Dictionary::MakeDictionaryFromPath(
        dictionary_path);
  if (!status_or_dictionary.ok() || *status_or_dictionary == nullptr) {
    LOG(FATAL) << "Couldn't load dictionary from "
               << absl::GetFlag(FLAGS_dictionary);
  }

  puzzlesolvers::SpellingBee spelling_bee(*status_or_dictionary.value());
  std::set<char> characters;
  
  for (char c : character_str) {
    characters.insert(c);
  }
  std::set<absl::string_view> words = spelling_bee.FindWords(characters);
  for (absl::string_view word : words) {
    LOG(INFO) << "matching word: " << word;
  }
}