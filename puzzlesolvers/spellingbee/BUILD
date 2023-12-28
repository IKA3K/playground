package(
  default_visibility = ["//visibility:public"]
)

cc_library(
  name = "spellingbee",
  hdrs = ["spellingbee.h"],
  srcs = ["spellingbee.cc"],
  deps = [
    "//puzzlesolvers/common:dictionary",
    "//puzzlesolvers/common:set_intersection",
    "@com_google_absl//absl/flags:flag",
    "@com_google_absl//absl/status",
    "@com_google_absl//absl/strings",
  ],
)

cc_test(
  name = "spellingbee_test",
  srcs = ["spellingbee_test.cc"],
  deps = [
    ":spellingbee",
    "@com_google_absl//absl/flags:flag",
    "@com_google_absl//absl/status",
    "@com_google_absl//absl/strings",
    "@com_google_googletest//:gtest_main",
  ],
)

cc_binary(
  name = "spellingbee_main",
  srcs = ["spellingbee_main.cc"],
  deps = [
    ":spellingbee",
    "//puzzlesolvers/common:dictionary",
    "@com_google_absl//absl/flags:flag",
    "@com_google_absl//absl/flags:parse",
    "@com_google_absl//absl/strings",
  ],
)