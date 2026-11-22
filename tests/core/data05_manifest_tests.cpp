#include "stormline/data/bundle/bundle_manifest.hpp"

#include <array>
#include <cstdio>
#include <string_view>

namespace {
using namespace stormline::data::bundle;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

bool run_man01() {
    begin();
    const std::array<std::uint8_t, 1> a{static_cast<std::uint8_t>('a')};
    expect(fnv1a64(std::span<const std::uint8_t>()) == 0xcbf29ce484222325ULL, "empty fnv");
    expect(fnv1a64(a) == 0xaf63dc4c8601ec8cULL, "a fnv");

    const std::array<std::uint8_t, 4> bytes{1, 2, 3, 4};
    BundleManifest manifest;
    expect(manifest.init(1) == BundleError::None, "init");
    expect(manifest.add(ManifestEntry{1, 0, 4, fnv1a64(bytes)}) == BundleError::None,
           "entry");
    expect(verify_chunk(manifest, 1, bytes) == BundleError::None, "verify");
    std::array<std::uint8_t, 4> changed = bytes;
    changed[0] = 9;
    expect(verify_chunk(manifest, 1, changed) == BundleError::FingerprintMismatch,
           "mismatch");
    expect(verify_chunk(manifest, 1, a) == BundleError::InvalidArgument, "length");
    expect(verify_chunk(manifest, 2, bytes) == BundleError::NotFound, "missing");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_data05_manifest_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "man01") { success = run_man01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
