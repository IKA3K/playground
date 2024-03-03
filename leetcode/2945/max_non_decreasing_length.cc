#include "max_non_decreasing_length.h"

int find_max_length(std::vector<int>& nums) {
  /**
    Problem statement:

    You are given a 0-indexed integer array `nums`.

    You can perform any number of operations, where each operation involves
    selecting a subarray of the array and replacing it with the sum of its
    elements. For example, if the given array is [1,3,5,6] and you select
    subarray [3,5] the array will convert to [1,8,6].

    Return the maximum length of a non-decreasing array that can be made after
    applying operations.

    A subarray is a contiguous non-empty sequence of elements within an array.
    */

  /**
    Thinking out aloud:

    The easiest way to do this it seems is to have just a single iterator and a
    few bookkeeping vars:

    1. Iter pointing at the last value that ended a non-decreasing range.
    2. Lookahead iter used for checking next values for a large enough value
    3. Running summation of values used by iter #2.
    4. Running count of how many values are removed in the process.

    If iter #2 finds a value larger than the summation #3, then go back to using iter
    #1.
   */
  return 0;
}