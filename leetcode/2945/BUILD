# 2945: https://leetcode.com/problems/find-maximum-non-decreasing-array-length/description/
cc_library(
  name = "max_non_decreasing_length",
  hdrs = ["max_non_decreasing_length.h"],
  srcs = ["max_non_decreasing_length.cc"],
  deps = [
    "@com_google_absl//absl/log",
    "@com_google_absl//absl/strings",
  ],
)

cc_test(
  name = "max_non_decreasing_length_test",
  srcs = ["max_non_decreasing_length_test.cc"],
  deps = [
    ":max_non_decreasing_length",
    "@com_google_googletest//:gtest",
    "@com_google_googletest//:gtest_main"
  ],
)