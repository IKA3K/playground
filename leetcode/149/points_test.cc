#include "points.h"

#include "gtest/gtest.h"

TEST(PointsTest, ProvidedTestCases) {
  // Provided test cases from leetcode.com
  Points p = {{1,1}, {2,2}, {3,3}};
  EXPECT_EQ(max_points(p), 3);

  p = {{1,1},{3,2},{5,3},{4,1},{2,3},{1,4}};
  EXPECT_EQ(max_points(p), 4);
}

TEST(PointsTest, Limits) {
  // Passing empty to max_points should return 0.
  Points p;
  EXPECT_EQ(max_points(p), 0);
  // Passing a single point to max_points should return 1.
  p = {{1,1}};
  EXPECT_EQ(max_points(p), 1);
  // Passing completely arbitrary points should return 2.
  p = {
    {1,1}, {2,0}, {3,2}, {4,-1}, {5, 9}
  };
  EXPECT_EQ(max_points(p), 2);
  // Passing points with rate of inf should return that.
  p = {{1,1},{1,2},{1,3},{1,4},{1,5},{2,2},{3,3}};
  EXPECT_EQ(max_points(p), 5);
}

TEST(PointsTest, CreatedTestCases) {
  Points a = {
    {1,1}, {2,2}, {3,3},
    {1,1},{3,2},{5,3},{4,1},{2,3},{1,4}
  };
  // Combination of test cases above, should still yield 4.
  EXPECT_EQ(max_points(a), 4);
  // Invert x and y in p, and the result should still be 4.
  for (Point& p : a) {
    std::swap(p[0], p[1]);
  }
  EXPECT_EQ(max_points(a), 4);

  // Add {4,4} and {5,5} to the list, which should make max_points return 5.
  a.push_back({4,4});
  a.push_back({5,5});
  EXPECT_EQ(max_points(a), 5);
}