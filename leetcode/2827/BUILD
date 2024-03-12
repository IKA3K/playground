# 2827: https://leetcode.com/problems/number-of-beautiful-integers-in-the-range/description/
cc_library(
  name = "find",
  hdrs = ["find.h"],
  srcs = ["find.cc"],
  deps = [
    "@com_google_absl//absl/log:check",
    "@com_google_absl//absl/log",
    "@com_google_absl//absl/strings",
  ],
)

cc_test(
  name = "find_test",
  srcs = ["find_test.cc"],
  deps = [
    ":find",
    "@com_google_googletest//:gtest",
    "@com_google_googletest//:gtest_main"
  ],
)