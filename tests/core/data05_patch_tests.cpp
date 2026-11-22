#include "stormline/data/bundle/patch_plan.hpp"

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

bool run_pat01() {
    begin();
    BundleManifest base;
    BundleManifest target;
    expect(base.init(1) == BundleError::None, "base init");
    expect(target.init(2) == BundleError::None, "target init");
    expect(base.add(ManifestEntry{1, 0, 4, 100}) == BundleError::None, "base a");
    expect(base.add(ManifestEntry{2, 4, 4, 200}) == BundleError::None, "base b");
    expect(target.add(ManifestEntry{1, 0, 4, 100}) == BundleError::None, "target a");
    expect(target.add(ManifestEntry{2, 4, 4, 300}) == BundleError::None, "target b");
    expect(target.add(ManifestEntry{3, 8, 4, 400}) == BundleError::None, "target c");

    PatchPlan plan{};
    expect(make_patch_plan(base, target, plan) == BundleError::None, "plan");
    expect(plan.base_generation == 1 && plan.target_generation == 2, "generations");
    expect(plan.reuse_count == 1 && plan.fetch_count == 2, "counts");
    expect(make_patch_plan(base, base, plan) == BundleError::PatchConflict, "same gen");
    BundleManifest zero;
    expect(make_patch_plan(zero, target, plan) == BundleError::PatchConflict, "zero base");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_data05_patch_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "pat01") { success = run_pat01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
