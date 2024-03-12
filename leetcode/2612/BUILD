# 2612: https://leetcode.com/problems/minimum-reverse-operations/description/
cc_library(
  name = "reverse",
  hdrs = ["reverse.h"],
  srcs = ["reverse.cc"],
  deps = [
    "@com_google_absl//absl/log",
    "@com_google_absl//absl/strings",
  ],
)

cc_test(
  name = "reverse_test",
  srcs = ["reverse_test.cc"],
  deps = [
    ":reverse",
    "@com_google_googletest//:gtest",
    "@com_google_googletest//:gtest_main"
  ],
)