#include <string>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/strings/string_view.h"
#include "puzzlesolvers/common/dictionary.h"
#include "puzzlesolvers/spellingbee/spellingbee.h"
#include "spellingbee.h"

ABSL_FLAG(std::string, dictionary, "/tmp/words.txt", "Dictionary location");
ABSL_FLAG(std::string, characters, "", "Set of characters to use to find words");
ABSL_FLAG(std::string, required_character, " ", "Required character");

int main(int argc, char** argv) {
  absl::ParseCommandLine(argc, argv);

  char required_char = absl::GetFlag(FLAGS_required_character)[0];
  std::string character_str = absl::GetFlag(FLAGS_characters);
  std::string dictionary_path = absl::GetFlag(FLAGS_dictionary);
  LOG(INFO) << "Finding words with character set " << character_str;
  LOG(INFO) << "Requiring character " << required_char;

  std::set<char> characters;
  
  for (char c : character_str) {
    characters.insert(c);
  }
  if (characters.count(required_char) == 0) {
    LOG(FATAL) << "required char " << required_char << " should be part of the character set";
  }

  LOG(INFO) << "Loading dictionary from " << dictionary_path;
  auto status_or_dictionary =
      puzzlesolvers::Dictionary::MakeDictionaryFromPath(
        dictionary_path);
  if (!status_or_dictionary.ok() || *status_or_dictionary == nullptr) {
    LOG(FATAL) << "Couldn't load dictionary from "
               << absl::GetFlag(FLAGS_dictionary);
  }

  puzzlesolvers::SpellingBee spelling_bee(*status_or_dictionary.value());
  std::set<absl::string_view> words = spelling_bee.FindWords(characters, required_char);
  for (absl::string_view word : words) {
    LOG(INFO) << "matching word: " << word;
  }
}