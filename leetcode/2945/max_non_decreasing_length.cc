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

    What's the worst possible scenario? That would have to be values in forever
    decreasing order, since it's possible to make a longer array than if iterating
    forwards. e.g.

    [6,5,5,4,3,2,1], if going forward only, would yield [26]
    but the optimized solution is [6,10,10].

    I think the solution should revolve around the largest existing number and largest
    sums in the array, since that influences how we construct any other value.

    e.g. [1,2,8,6,10,5,2,3] would result in [1,2,14,20]
  */
}