#include "puzzlesolvers/spellingbee/spellingbee.h"

#include "absl/memory/memory.h"

#include <gtest/gmock.h>
#include <gtest/gtest.h>

using puzzlesolvers::Dictionary;
using puzzlesolvers::SpellingBee;
using puzzlesolvers::WordsByCharMap;

std::unique_ptr<Dictionary> MakeTestDictionary() {
  std::set<std::string> words = {
    "adverse", "bread", "carbs", "destruct", "everyone", "funk", "garbage",
    "horse", "iota", "junky", "kiosk", "laminate", "micron", "naval", "orange",
    "pumpkin", "quarrel", "raven", "savings", "tester", "universe", "valor",
    "yeast", "zoning"
  };
  return absl::make_unique<Dictionary>(words);
}

TEST(SpellingBeeTest, TestFindingWords) {
  Dictionary test_dictionary = MakeTestDictionary();
  
}