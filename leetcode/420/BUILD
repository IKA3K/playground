# 420
cc_library(
  name = "checker",
  hdrs = ["checker.h"],
  srcs = ["checker.cc"],
  deps = [
    "@com_google_absl//absl/log",
    "@com_google_absl//absl/strings",
  ],
)

cc_test(
  name = "checker_test",
  srcs = ["checker_test.cc"],
  deps = [
    ":checker",
    "@com_google_googletest//:gtest",
    "@com_google_googletest//:gtest_main"
  ],
)