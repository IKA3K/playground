#include "reverse.h"

#include "gtest/gtest.h"

TEST(ReverseTest, ProvidedTestCases) {
  EXPECT_EQ(min_reverse_operations(4, 0, {1,2}, 4),
            {0, -1, -1, 1});
  EXPECT_EQ(min_reverse_operations(5, 0, {2,4}, 3),
            {0, -1, -1, -1, -1});
}