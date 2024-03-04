# 149: https://leetcode.com/problems/max-buysell-on-a-line/
cc_library(
  name = "buysell",
  hdrs = ["buysell.h"],
  srcs = ["buysell.cc"],
  deps = [
    "@com_google_absl//absl/log",
  ],
)

cc_test(
  name = "buysell_test",
  srcs = ["buysell_test.cc"],
  deps = [
    ":buysell",
    "@com_google_googletest//:gtest",
    "@com_google_googletest//:gtest_main"
  ],
)