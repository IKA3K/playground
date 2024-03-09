# 2931: https://leetcode.com/problems/maximum-spending-after-buying-items/description/
cc_library(
  name = "max",
  hdrs = ["max.h"],
  srcs = ["max.cc"],
  deps = [
    "@com_google_absl//absl/log",
    "@com_google_absl//absl/strings",
  ],
)

cc_test(
  name = "max_test",
  srcs = ["max_test.cc"],
  deps = [
    ":max",
    "@com_google_googletest//:gtest",
    "@com_google_googletest//:gtest_main"
  ],
)