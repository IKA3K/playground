#include "puzzlesolvers/common/set_intersection.h"

#include <string>

#include <gtest/gtest.h>

namespace {

using puzzlesolvers::Intersection;

typedef std::vector<const std::set<std::string>*> PointerVec;

TEST(SetIntersectionTest, TestSingleSet) {
  std::set<std::string> s = {"abalone", "bear", "cow"};

  // Single pointer.
  PointerVec v = {&s};
  EXPECT_TRUE(s == Intersection<std::string>(v));
  // Multiple pointers.
  PointerVec v2 = {&s, &s, &s};
  EXPECT_TRUE(s == Intersection<std::string>(v2));
}

std::set<std::string> a = {"aardvark", "bear", "cow"};
std::set<std::string> b = {"aardvark", "bearish", "cowpie"};
std::set<std::string> c = {"abalone", "bear", "cow"};
std::set<std::string> d = {"abalone", "bear", "cowpie"};

TEST(SetIntersectionTest, TestMultipleSets1) {
  std::set<std::string> expected1 = {"aardvark"};
  PointerVec v1 = {&a, &b};
  EXPECT_TRUE(expected1 == Intersection<std::string>(v1));
}

TEST(SetIntersectionTest, TestMultipleSets2) {
  std::set<std::string> expected2 = {};
  PointerVec v2 = {&a, &b, &c};
  PointerVec v2a = {&a, &b, &c, &d};
  EXPECT_TRUE(expected2 == Intersection<std::string>(v2));
  EXPECT_TRUE(expected2 == Intersection<std::string>(v2a));
}

TEST(SetIntersectionTest, TestMultipleSets3) {
  std::set<std::string> expected3 = {"bear", "cow"};
  PointerVec v3 = {&a, &c};
  EXPECT_TRUE(expected3 == Intersection<std::string>(v3));
}

TEST(SetIntersectionTest, TestMultipleSets4) {
  std::set<std::string> expected4 = {"bear"};
  PointerVec v4 = {&a, &c, &d};
  EXPECT_TRUE(expected4 == Intersection<std::string>(v4));
}

}  // namespace