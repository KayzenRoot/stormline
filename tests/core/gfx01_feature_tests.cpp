#include "stormline/graphics/rhi/rhi_feature.hpp"

#include <cstdio>
#include <string_view>

namespace {
using namespace stormline::graphics::rhi;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

[[nodiscard]] u32 null_features() {
    AdapterInfo adapter{};
    if (adapter_at(0, adapter) != RhiError::None) {
        return 0;
    }
    return adapter.feature_flags;
}

[[nodiscard]] bool init_with(u32 features, u32 tier) {
    RhiDevice device;
    Capabilities caps{};
    return device.init(DeviceDescriptor{1, features, tier}, caps) == RhiError::None;
}

bool run_tier01() {
    begin();
    const u32 available = null_features();
    expect(available == (kFeatureCompute | kFeatureIndirectDraw), "null features");

    expect(features_supported(available, kFeatureCompute), "compute supported");
    expect(features_supported(available, kFeatureIndirectDraw), "indirect supported");
    expect(features_supported(available, kFeatureCompute | kFeatureIndirectDraw),
           "combined supported");
    expect(!features_supported(available, kFeatureDescriptorIndexing),
           "descriptor indexing unsupported");
    expect(!features_supported(available, kFeatureTimestampQuery),
           "timestamp unsupported");
    expect(!features_supported(available, 0), "zero required");
    expect(!features_supported(available, kAllFeatures | (1u << 4)), "unknown bit");
    expect(!features_supported(0, kFeatureCompute), "empty available");

    expect(tier_supported(1), "tier one");
    expect(!tier_supported(0), "tier zero");
    expect(!tier_supported(2), "tier two");
    expect(!tier_supported(0xFFFFFFFFu), "tier max");

    expect(init_with(kFeatureCompute, 1), "init compute");
    expect(init_with(kFeatureIndirectDraw, 1), "init indirect");
    expect(init_with(kFeatureCompute | kFeatureIndirectDraw, 1), "init combined");
    expect(!init_with(kFeatureDescriptorIndexing, 1), "init unsupported feature");
    expect(!init_with(kFeatureTimestampQuery, 1), "init unsupported timestamp");
    expect(!init_with(kAllFeatures | (1u << 4), 1), "init unknown feature");
    expect(!init_with(0, 1), "init zero feature");
    expect(!init_with(kFeatureCompute, 0), "init tier zero");
    expect(!init_with(kFeatureCompute, 2), "init tier two");

    RhiDevice device;
    Capabilities caps{};
    expect(device.init(DeviceDescriptor{1, kFeatureCompute, 1}, caps) == RhiError::None,
           "init capabilities");
    expect(caps.feature_flags == available, "capability feature snapshot");
    expect(caps.max_buffer_bytes == kMaxBufferBytes, "capability buffer");
    expect(caps.max_texture_dimension == kMaxTextureDimension, "capability dimension");
    expect(caps.max_texture_levels == kMaxTextureLevels, "capability levels");
    expect(device.lose() == RhiError::None, "lose");
    Capabilities recovered{};
    expect(device.recover(recovered) == RhiError::None, "recover");
    expect(recovered.device_generation == 2, "recovered generation");
    expect(recovered.feature_flags == available, "recovered features");
    expect(recovered.max_buffer_bytes == caps.max_buffer_bytes, "recovered buffer");
    expect(recovered.max_texture_dimension == caps.max_texture_dimension,
           "recovered dimension");
    expect(recovered.max_texture_levels == caps.max_texture_levels, "recovered levels");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_gfx01_feature_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "tier01") { success = run_tier01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
