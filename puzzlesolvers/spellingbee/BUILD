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
  name = "spellingbee",
  hdrs = ["spellingbee.h"],
  srcs = ["spellingbee.cc"],
  deps = [
    "@com_google_absl//absl/flag",
    "@com_google_absl//absl/status",
    "@com_google_absl//absl/strings",
  ],
)

cc_test(
  name = "spellingbee_test",
  srcs = ["spellingbee_test.cc"],
  deps = [
    ":spellingbee",
    "@com_google_absl//absl/flag",
    "@com_google_absl//absl/status",
    "@com_google_absl//absl/strings",
  ],
)

cc_binary(
  name = "spellingbee_main",
  srcs = ["spellingbee_main.cc"],
  deps = [":spellingbee"]
)