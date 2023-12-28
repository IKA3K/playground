cc_library(
  name = "dictionary",
  hdrs = ["dictionary.h"],
  srcs = ["dictionary.cc"],
  deps = [
    "@com_google_absl//absl/flags:flag",
    "@com_google_absl//absl/log",
    "@com_google_absl//absl/memory",
    "@com_google_absl//absl/status",
    "@com_google_absl//absl/status:statusor",
    "@com_google_absl//absl/strings",
  ],
)

cc_test(
  name = "dictionary_test",
  srcs = ["dictionary_test.cc"],
  deps = [
    ":dictionary",
    "@com_google_absl//absl/flags:flag",
    "@com_google_absl//absl/log",
    "@com_google_googletest//:gtest_main",
  ],
)
cc_library(
  name = "set_intersection",
  hdrs = ["set_intersection.h"],
  deps = [
    "@com_google_absl//absl/log",
  ],
)

cc_test(
  name = "set_intersection_test",
  srcs = ["set_intersection_test.cc"],
  deps = [
    ":set_intersection",
    "@com_google_googletest//:gtest_main",
  ],
)