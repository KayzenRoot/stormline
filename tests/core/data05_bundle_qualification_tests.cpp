#include "stormline/data/bundle/bundle_manifest.hpp"
#include "stormline/data/bundle/cook_plan.hpp"
#include "stormline/data/bundle/patch_plan.hpp"
#include "stormline/data/bundle/rle.hpp"
#include "stormline/data/bundle/stream_window.hpp"

#include <array>
#include <cstdio>
#include <string_view>

namespace {
using namespace stormline::data::bundle;
namespace registry = stormline::data::registry;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

[[nodiscard]] CookAsset cook_asset(u64 id) {
    CookAsset value{};
    value.asset = registry::AssetId{0, id};
    value.source_revision = 1;
    return value;
}

bool run_qlf_b01() {
    begin();
    TargetProfile target{1, TargetOs::Linux, TargetArch::X64, 3, 2};
    std::array<CookAsset, 2> assets{cook_asset(1), cook_asset(2)};
    CookPlan plan{};
    expect(make_cook_plan(target, assets, plan) == BundleError::None, "cook");
    expect(plan.asset_count == 2, "cook count");

    const std::array<std::uint8_t, 4> source{1, 1, 2, 2};
    std::array<std::uint8_t, 8> encoded{};
    u32 encoded_size = 0;
    expect(rle_encode(source, encoded, encoded_size) == BundleError::None, "encode");
    std::array<std::uint8_t, 4> decoded{};
    u32 decoded_size = 0;
    expect(rle_decode(std::span<const std::uint8_t>(encoded.data(), encoded_size),
                      decoded, decoded_size) == BundleError::None, "decode");
    expect(decoded == source, "roundtrip");

    BundleManifest manifest;
    expect(manifest.init(1) == BundleError::None, "manifest");
    expect(manifest.add(ManifestEntry{1, 0, 4, fnv1a64(decoded)}) == BundleError::None,
           "entry");
    ChunkStore store;
    expect(store.put(1, decoded) == BundleError::None, "store");
    StreamWindow window;
    expect(window.init(manifest, store, 1, 8) == BundleError::None, "window");
    expect(window.request(1) == BundleError::None, "request");
    expect(window.loaded_bytes() == 4, "loaded");

    BundleManifest next;
    expect(next.init(2) == BundleError::None, "next");
    expect(next.add(ManifestEntry{1, 0, 4, fnv1a64(decoded)}) == BundleError::None,
           "next entry");
    PatchPlan patch{};
    expect(make_patch_plan(manifest, next, patch) == BundleError::None, "patch");
    expect(patch.reuse_count == 1 && patch.fetch_count == 0, "reuse");
    return finish();
}

struct Snapshot {
    u32 cook_assets{0};
    u32 encoded_size{0};
    u64 fingerprint{0};
    u32 stream_bytes{0};
    u32 reuse{0};
};

[[nodiscard]] bool snapshot(Snapshot& out) {
    TargetProfile target{1, TargetOs::Linux, TargetArch::X64, 3, 2};
    std::array<CookAsset, 2> assets{cook_asset(1), cook_asset(2)};
    CookPlan plan{};
    if (make_cook_plan(target, assets, plan) != BundleError::None) {
        return false;
    }
    const std::array<std::uint8_t, 4> source{1, 1, 2, 2};
    std::array<std::uint8_t, 8> encoded{};
    u32 encoded_size = 0;
    if (rle_encode(source, encoded, encoded_size) != BundleError::None) {
        return false;
    }
    BundleManifest manifest;
    if (manifest.init(1) != BundleError::None
        || manifest.add(ManifestEntry{1, 0, 4, fnv1a64(source)}) != BundleError::None) {
        return false;
    }
    ChunkStore store;
    if (store.put(1, source) != BundleError::None) {
        return false;
    }
    StreamWindow window;
    if (window.init(manifest, store, 1, 8) != BundleError::None
        || window.request(1) != BundleError::None) {
        return false;
    }
    BundleManifest next;
    if (next.init(2) != BundleError::None
        || next.add(ManifestEntry{1, 0, 4, fnv1a64(source)}) != BundleError::None) {
        return false;
    }
    PatchPlan patch{};
    if (make_patch_plan(manifest, next, patch) != BundleError::None) {
        return false;
    }
    out.cook_assets = plan.asset_count;
    out.encoded_size = encoded_size;
    out.fingerprint = fnv1a64(source);
    out.stream_bytes = window.loaded_bytes();
    out.reuse = patch.reuse_count;
    return true;
}

bool run_qlf_b02() {
    begin();
    Snapshot first{};
    Snapshot second{};
    expect(snapshot(first), "first");
    expect(snapshot(second), "second");
    expect(first.cook_assets == second.cook_assets, "cook repeat");
    expect(first.encoded_size == second.encoded_size, "encoded repeat");
    expect(first.fingerprint == second.fingerprint, "fingerprint repeat");
    expect(first.stream_bytes == second.stream_bytes, "stream repeat");
    expect(first.reuse == second.reuse, "reuse repeat");
    return finish();
}

bool run_qlf_b03() {
    begin();
    TargetProfile target{0, TargetOs::Linux, TargetArch::X64, 0, 1};
    std::array<CookAsset, 1> assets{cook_asset(1)};
    CookPlan plan{};
    expect(make_cook_plan(target, assets, plan) == BundleError::InvalidTarget, "bad target");
    target.profile_id = 1;
    expect(make_cook_plan(target, assets, plan) == BundleError::None, "after target");

    const std::array<std::uint8_t, 1> byte{1};
    std::array<std::uint8_t, 1> scratch{};
    u32 dummy_size = 0;
    expect(rle_encode(std::span<const std::uint8_t>(), scratch, dummy_size)
           == BundleError::InvalidArgument, "empty rle");
    std::array<std::uint8_t, 2> encoded{};
    u32 encoded_size = 0;
    expect(rle_encode(byte, encoded, encoded_size) == BundleError::None, "after empty");

    BundleManifest manifest;
    expect(manifest.add(ManifestEntry{1, 0, 1, 0}) == BundleError::InvalidArgument,
           "uninitialized");
    expect(manifest.init(1) == BundleError::None, "after manifest");
    expect(manifest.add(ManifestEntry{1, 0, 1, fnv1a64(byte)}) == BundleError::None,
           "after init");
    expect(verify_chunk(manifest, 1, byte) == BundleError::None, "verify");
    return finish();
}

bool run_qlf_b04() {
    begin();
    TargetProfile target{1, TargetOs::Linux, TargetArch::X64, 0, 1};
    std::array<CookAsset, 1> assets{cook_asset(1)};
    CookPlan plan{};
    for (u32 index = 0; index < 10000; ++index) {
        expect(make_cook_plan(target, assets, plan) == BundleError::None, "cook overload");
    }
    const std::array<std::uint8_t, 4> source{1, 1, 2, 2};
    std::array<std::uint8_t, 8> encoded{};
    u32 encoded_size = 0;
    for (u32 index = 0; index < 10000; ++index) {
        expect(rle_encode(source, encoded, encoded_size) == BundleError::None, "rle overload");
    }
    BundleManifest manifest;
    expect(manifest.init(1) == BundleError::None, "manifest");
    u32 manifest_entries = 0;
    for (u32 index = 0; index < 10000; ++index) {
        const BundleError status =
            manifest.add(ManifestEntry{index + 1,
                index < kMaxManifestEntries ? index : kMaxManifestEntries, 1, 0});
        if (status == BundleError::None) {
            ++manifest_entries;
        } else {
            expect(status == BundleError::CapacityFull || status == BundleError::InvalidArgument,
                   "manifest overload");
        }
    }
    expect(manifest_entries == kMaxManifestEntries, "manifest capacity");
    expect(manifest.size() == kMaxManifestEntries, "manifest size");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_data05_bundle_qualification_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "qlf01") { success = run_qlf_b01(); }
    else if (mode == "qlf02") { success = run_qlf_b02(); }
    else if (mode == "qlf03") { success = run_qlf_b03(); }
    else if (mode == "qlf04") { success = run_qlf_b04(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
