#include "buysell.h"

#include "gtest/gtest.h"

TEST(BuySellTest, ProvidedTestCases) {
  /**
  Example 1:

  Input: prices = [7,1,5,3,6,4]
  Output: 5
  Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
  Note that buying on day 2 and selling on day 1 is not allowed because you must buy before you sell.
  */
  // The actual max profit is 7, which is 5-1 + 6-3 = 4 + 3 = 7.
  EXPECT_EQ(max_profit({7,1,5,3,6,4}, 3), 7);
  /**
  Example 2:

  Input: prices = [7,6,4,3,1]
  Output: 0
  Explanation: In this case, no transactions are done and the max profit = 0.
   */
  EXPECT_EQ(max_profit({7,6,4,3,1}, 1), 0);
}