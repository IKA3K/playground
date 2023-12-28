#include "puzzlesolvers/common/dictionary.h"

#include <gtest/gtest.h>

#include "absl/flags/flag.h"
#include "absl/log/log.h"
#include "absl/status/status.h"

ABSL_FLAG(std::string, test_file_path, "/tmp/words.txt", "File that must exist for unit test to succeed.");

TEST(DictionaryTest, TestManualLoad) {
  // Chars: abcdegiklmnoruy
  auto dict = puzzlesolvers::Dictionary(
      {"armadillo", "book", "curmudgeon", "donkey"});
  std::string expected_chars = "abcdegiklmnoruy";
  for (char c : expected_chars) {
    EXPECT_NE(dict.words_by_char().find(c), dict.words_by_char().end());
  }
  std::string unexpected_chars = "hjqstvwxz";
  for (char c : unexpected_chars) {
    EXPECT_EQ(dict.words_by_char().find(c), dict.words_by_char().end());
  }
}

TEST(DictionaryTest, TestCantFindFile) {
  auto status_or_dict = puzzlesolvers::Dictionary::MakeDictionaryFromPath("/tmp/this_file_doesnt_exist");
  EXPECT_TRUE(absl::IsNotFound(status_or_dict.status()));
}

TEST(DictionaryTest, TestFindsFakeFile) {
  auto status_or_dict = puzzlesolvers::Dictionary::MakeDictionaryFromPath(
      absl::GetFlag(FLAGS_test_file_path));
  EXPECT_TRUE(status_or_dict.ok());
  // Test that a few words exist/don't exist.
  const auto& words_by_char= (*status_or_dict)->words_by_char();
  const auto& word_map = words_by_char.at('a');
  EXPECT_GT(word_map.size(), 0);
  EXPECT_EQ(word_map.count("aaaaa"), 0);
  EXPECT_EQ(word_map.count("anchovy"), 1);
  EXPECT_EQ(word_map.count("armadillo"), 1);
  EXPECT_EQ(word_map.count("armor"), 1);
}