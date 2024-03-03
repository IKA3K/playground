#include "checker.h"

#include "gtest/gtest.h"

TEST(CheckerTest, ProvidedTestCases) {
  EXPECT_EQ(pwdchecker("a"), 5);
  EXPECT_EQ(pwdchecker("aA1"), 3);
  EXPECT_EQ(pwdchecker("1337C0d3"), 0);
}

TEST(CheckerTest, MadeUpTestCases) {
  EXPECT_EQ(pwdchecker("AAAAAA"), 2);
  // Change 2 characters for to get all types of chars.
  EXPECT_EQ(pwdchecker("AAAAAA"), 2);
  // Same as above except length not enough.
  EXPECT_EQ(pwdchecker("11111"), 2);
  EXPECT_EQ(pwdchecker("aaaa"), 3);
  EXPECT_EQ(pwdchecker("aaa"), 4);
  EXPECT_EQ(pwdchecker("aa"), 4);
  EXPECT_EQ(pwdchecker("a"), 5);
  EXPECT_EQ(pwdchecker(""), 6);
}

TEST(CheckerTest, SymbolCases) {
  // For some reason symbols don't count towards the
  // limit, so will need change 3 characters here.
  EXPECT_EQ(pwdchecker(".!.!.!"), 3);
  EXPECT_EQ(pwdchecker("...!!!"), 3);
  EXPECT_EQ(pwdchecker("!!!!!!!!"), 3);
}