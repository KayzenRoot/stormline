#include "stormline/data/bundle/stream_window.hpp"

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

bool run_str01() {
    begin();
    BundleManifest manifest;
    expect(manifest.init(1) == BundleError::None, "manifest init");
    expect(manifest.add(ManifestEntry{1, 0, 4, 0}) == BundleError::None, "entry 1");
    expect(manifest.add(ManifestEntry{2, 4, 4, 0}) == BundleError::None, "entry 2");
    expect(manifest.add(ManifestEntry{3, 8, 4, 0}) == BundleError::None, "entry 3");
    expect(manifest.add(ManifestEntry{1, 12, 4, 0}) == BundleError::DuplicateId,
           "duplicate entry");
    expect(manifest.add(ManifestEntry{4, 2, 4, 0}) == BundleError::ChunkOverlap, "overlap");
    expect(manifest.add(ManifestEntry{5, 4095, 4, 0}) == BundleError::InvalidArgument,
           "range");
    expect(manifest.total_bytes() == 12, "total");

    ChunkStore store;
    const std::array<std::uint8_t, 4> bytes{1, 2, 3, 4};
    expect(store.put(1, bytes) == BundleError::None, "chunk 1");
    expect(store.put(2, bytes) == BundleError::None, "chunk 2");
    expect(store.put(3, bytes) == BundleError::None, "chunk 3");
    expect(store.put(1, bytes) == BundleError::DuplicateId, "duplicate chunk");
    expect(store.put(0, bytes) == BundleError::InvalidArgument, "invalid chunk");

    StreamWindow window;
    expect(window.init(manifest, store, 1, 8) == BundleError::None, "window init");
    expect(window.request(1) == BundleError::None, "request 1");
    expect(window.request(1) == BundleError::None, "idempotent");
    expect(window.chunk_count() == 1 && window.loaded_bytes() == 4, "window counts");
    expect(window.request(2) == BundleError::None, "request 2");
    expect(window.request(3) == BundleError::CapacityFull, "budget");
    expect(window.request(99) == BundleError::NotFound, "missing");

    expect(window.init(manifest, store, 2, 8) == BundleError::InvalidArgument,
           "generation mismatch");
    expect(window.init(manifest, store, 1, 0) == BundleError::InvalidArgument, "budget zero");
    expect(manifest.init(2) == BundleError::None, "reinit manifest");
    expect(window.request(1) == BundleError::StaleGeneration, "stale");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_data05_stream_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "str01") { success = run_str01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
