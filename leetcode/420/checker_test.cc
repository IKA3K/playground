#include "checker.h"

#include "gtest/gtest.h"

TEST(CheckerTest, ProvidedTestCases) {
  EXPECT_EQ(pwdchecker("a"), 5);
  EXPECT_EQ(pwdchecker("aA1"), 3);
  EXPECT_EQ(pwdchecker("1337C0d3"), 0);
}

TEST(CheckerTest, MadeUpTestCases) {
  // Change 2 characters for to get all types of chars.
  EXPECT_EQ(pwdchecker("aaaaaa"), 2);
  // Same as above except length not enough.
  EXPECT_EQ(pwdchecker("aaaaa"), 3);
  EXPECT_EQ(pwdchecker("aaaa"), 3);
  EXPECT_EQ(pwdchecker("aaa"), 4);
}