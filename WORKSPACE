load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# ----------------------------------------------------------------------------
# Abseil (C++)
http_archive(
  name = "com_google_absl",
  urls = ["https://github.com/abseil/abseil-cpp/archive/refs/tags/20230802.1.zip"],
  strip_prefix = "abseil-cpp-20230802.1",
)

http_archive(
  name = "com_github_google_benchmark",
  urls = ["https://github.com/google/benchmark/archive/refs/tags/v1.5.2.zip"],
  strip_prefix = "benchmark-1.5.2",
)

# End (Abseil C++)
# ----------------------------------------------------------------------------

# ----------------------------------------------------------------------------
# Bazel Rules/Protocol Buffers

# rules_cc defines rules for generating C++ code from Protocol Buffers.
http_archive(
    name = "rules_cc",
    urls = ["https://github.com/bazelbuild/rules_cc/releases/download/0.0.9/rules_cc-0.0.9.tar.gz"],
    sha256 = "2037875b9a4456dce4a79d112a8ae885bbc4aad968e6587dca6e64f3a0900cdf",
    strip_prefix = "rules_cc-0.0.9",
)

# rules_proto defines abstract rules for building Protocol Buffers.
http_archive(
    name = "rules_proto",
    sha256 = "903af49528dc37ad2adbb744b317da520f133bc1cbbecbdd2a6c546c9ead080b",
    strip_prefix = "rules_proto-6.0.0-rc0",
    url = "https://github.com/bazelbuild/rules_proto/releases/download/6.0.0-rc0/rules_proto-6.0.0-rc0.tar.gz",
)

load("@rules_cc//cc:repositories.bzl", "rules_cc_dependencies")
rules_cc_dependencies()

git_repository(
    name = "com_google_protobuf",
    remote = "https://github.com/protocolbuffers/protobuf",
    tag = "v25.1",
)
load("@com_google_protobuf//:protobuf_deps.bzl", "protobuf_deps")

protobuf_deps()

# End (Protocol Buffers)
# ----------------------------------------------------------------------------

# googletest
http_archive(
    name = "com_google_googletest",
    strip_prefix = "googletest-1.14.0",
    urls = ["https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip"],
)