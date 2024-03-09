#include "max.h"

#include "gtest/gtest.h"

TEST(MaxTest, ProvidedTestCases) {
  EXPECT_EQ(max_spending({{8,5,2}, {6,4,1}, {9,7,3}}), 285);
  EXPECT_EQ(max_spending({{10,8,6,4,2}, {9,7,5,3,2}}), 386);
}
