#include "max_non_decreasing_length.h"

#include "absl/log/log.h"
#include "absl/strings/str_join.h"

int find_max_length(const std::vector<int>& nums) {
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
    There are corner cases where rolling backwards is preferable, e.g.:
    [1,3,3,2,5,6] becomes [1,3,5,5,6] in the best case, and [1,3,3,7,6]
    in the walk-ahead only case.

    Meanwhile [1,3,3,2,3,6] is clearly better as [1,3,3,5,6] and not
    [1,3,5,9].

    If we combine both situations using offsets, like:
    [1,3,3,2,5,6,7,6,15], then we could probably try both metholodiges
    at the same time. So for this case, once we notice the drop at 2,
    we save iter pointing at 3, then find the next value 5. Then do
    either 3+2, and 2+5, and see which results in more elements.
  */
  if (nums.empty()) {
    return 0;
  }
  std::vector<int> new_nums = {nums.front()};
  new_nums.reserve(nums.size());
  for (int i = 1; i < nums.size(); ++i) {
    // Special case for adding backwards.
    if (new_nums.back() > nums[i]) {
      if (i+1 < nums.size() && (new_nums.back() + nums[i]) <= nums[i+1]) {
        // Collapse existing value to make new value.
        new_nums.back() += nums[i];
      } else {
        int rolling_sum = nums[i];
        while (rolling_sum < new_nums.back() && (++i) < nums.size()) {
          rolling_sum += nums[i];
        }
        if (rolling_sum >= new_nums.back()) {
          new_nums.push_back(rolling_sum);
        }
      }
      continue;
    }
    new_nums.push_back(nums[i]);
  }

  LOG(ERROR) << "New array: [" << absl::StrJoin(new_nums, ", ") << "]";
  return new_nums.size();
}