#include "stormline/data/bundle/cook_plan.hpp"

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

[[nodiscard]] CookAsset asset(u64 id, u32 revision) {
    CookAsset value{};
    value.asset = registry::AssetId{0, id};
    value.source_revision = revision;
    return value;
}

bool run_tgt01() {
    begin();
    TargetProfile target{1, TargetOs::Linux, TargetArch::X64, 0x3, 2};
    expect(validate_target(target) == BundleError::None, "target");
    target.profile_id = 0;
    expect(validate_target(target) == BundleError::InvalidTarget, "target id");
    target.profile_id = 1;
    target.feature_flags = 0x80;
    expect(validate_target(target) == BundleError::UnsupportedFeature, "feature");
    target.feature_flags = 0;
    target.quality_tier = 0;
    expect(validate_target(target) == BundleError::InvalidTarget, "quality 0");
    target.quality_tier = 4;
    expect(validate_target(target) == BundleError::InvalidTarget, "quality 4");
    target.quality_tier = 1;

    std::array<CookAsset, 3> assets{asset(1, 1), asset(2, 2), asset(3, 3)};
    CookPlan plan{};
    expect(make_cook_plan(target, assets, plan) == BundleError::None, "plan");
    expect(plan.profile_id == 1 && plan.asset_count == 3
           && plan.estimated_bytes == 3 * kMaxChunkBytes, "plan values");
    expect(make_cook_plan(target, std::span<const CookAsset>(), plan)
           == BundleError::InvalidArgument, "empty");
    std::array<CookAsset, 2> duplicate{asset(1, 1), asset(1, 2)};
    expect(make_cook_plan(target, duplicate, plan) == BundleError::DuplicateId, "duplicate");
    std::array<CookAsset, 1> invalid{asset(0, 1)};
    expect(make_cook_plan(target, invalid, plan) == BundleError::InvalidArgument, "asset");
    invalid[0] = asset(4, 0);
    expect(make_cook_plan(target, invalid, plan) == BundleError::InvalidArgument, "revision");
    std::array<CookAsset, kMaxCookAssets + 1> too_many{};
    expect(make_cook_plan(target, too_many, plan) == BundleError::InvalidArgument, "too many");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_data05_target_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "tgt01") { success = run_tgt01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
