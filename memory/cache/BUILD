cc_library(
  name = "lru_cache",
  hdrs = ["lru_cache.h"],
  deps = [
    "@com_google_absl//absl/base",
    "@com_google_absl//absl/synchronization",
  ],
)

cc_test(
  name = "lru_cache_test",
  srcs = ["lru_cache_test.cc"],
  deps = [
    ":lru_cache",
    "@com_google_absl//absl/log",
    "@com_google_googletest//:gtest",
    "@com_google_googletest//:gtest_main",
  ]
)