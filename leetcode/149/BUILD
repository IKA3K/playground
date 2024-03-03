# 149: https://leetcode.com/problems/max-points-on-a-line/
cc_library(
  name = "points",
  hdrs = ["points.h"],
  srcs = ["points.cc"],
  deps = [
    "@com_google_absl//absl/log",
  ],
)

cc_test(
  name = "points_test",
  srcs = ["points_test.cc"],
  deps = [
    ":points",
    "@com_google_googletest//:gtest",
    "@com_google_googletest//:gtest_main"
  ],
)