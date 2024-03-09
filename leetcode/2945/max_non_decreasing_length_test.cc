#include "max_non_decreasing_length.h"

#include <vector>

#include "gtest/gtest.h"

TEST(MaxNonDecreasingLengthTest, ProvidedTestCases) {
  /**
    Example 1:

    Input: nums = [5,2,2]
    Output: 1
    Explanation: This array with length 3 is not non-decreasing.
    We have two ways to make the array length two.
    First, choosing subarray [2,2] converts the array to [5,4].
    Second, choosing subarray [5,2] converts the array to [7,2].
    In these two ways the array is not non-decreasing.
    And if we choose subarray [5,2,2] and replace it with [9] it becomes non-decreasing. 
    So the answer is 1.
    */
  EXPECT_EQ(find_max_length({5,2,2}), 1);
  /**
    Example 2:

    Input: nums = [1,2,3,4]
    Output: 4
    Explanation: The array is non-decreasing. So the answer is 4.
   */
  EXPECT_EQ(find_max_length({1,2,3,4}), 4);
  /**
    Example 3:

    Input: nums = [4,3,2,6]
    Output: 3
    Explanation: Replacing [3,2] with [5] converts the given array to [4,5,6] that is non-decreasing.
    Because the given array is not non-decreasing, the maximum possible answer is 3.
   */
  EXPECT_EQ(find_max_length({4,3,2,6}), 3);
}

TEST(MaxNonDecreasingLengthTest, MyTestCases) {
  /**
    [1,3,3,2,3,6] is clearly better as [1,3,3,5,6] (5) and not
    [1,3,5,9].
    */
  EXPECT_EQ(find_max_length({1,3,3,2,3,6}), 5);

  /**
    [1,3,3,2,5,6] is clearly better as [1,3,5,5,6] (5) and not
    [1,3,3,7,6].
    */
  EXPECT_EQ(find_max_length({1,3,3,2,5,6}), 5);

  /**
    If we combine both situations using offsets, like:
    [1,3,3,2,5,6,7,6,15], then this should be [1,3,5,5,6,13,15] (7)
      */
  EXPECT_EQ(find_max_length({1,3,3,2,5,6,7,6,15}), 7);
}

TEST(MaxNonDecreasingLengthTest, TrapTestCases) {
  EXPECT_EQ(find_max_length({5,2,2,8}), 2);
}