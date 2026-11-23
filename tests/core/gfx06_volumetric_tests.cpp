#include "stormline/graphics/lighting/volumetric_plan.hpp"

#include <cstdio>
#include <limits>
#include <string_view>

namespace {
using namespace stormline::graphics::lighting;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

[[nodiscard]] VolumetricDesc volume(u32 id, u32 steps = 8) {
    VolumetricDesc value{};
    value.id = id;
    value.revision = 1;
    value.density = 0.1f;
    value.extinction = 0.2f;
    value.scattering = 0.3f;
    value.anisotropy = 0.0f;
    value.tier = VolumetricTier::Analytic;
    value.step_count = steps;
    return value;
}

bool run_vol01() {
    begin();
    VolumetricPlan plan{};
    LightingDiagnostic diagnostic{};

    expect(plan_volumetrics(VolumetricSet{}, 16, plan, diagnostic)
               == LightingError::None,
           "empty");
    expect(plan.count == 0 && plan.total_steps == 0, "empty counts");

    VolumetricSet set{};
    set.count = 2;
    set.volumes[0] = volume(20, 4);
    set.volumes[1] = volume(10, 6);
    expect(plan_volumetrics(set, 10, plan, diagnostic) == LightingError::None,
           "plan");
    expect(plan.count == 2 && plan.volume_ids[0] == 10
               && plan.volume_ids[1] == 20 && plan.total_steps == 10,
           "plan order");

    expect(plan_volumetrics(set, 9, plan, diagnostic)
               == LightingError::VolumetricBudgetExceeded,
           "budget");
    expect(plan.count == 0 && plan.total_steps == 0, "budget reset");
    expect(plan_volumetrics(set, 0, plan, diagnostic)
               == LightingError::InvalidArgument,
           "zero budget");

    set.volumes[1] = volume(20, 2);
    expect(plan_volumetrics(set, 10, plan, diagnostic)
               == LightingError::DuplicateId,
           "duplicate");
    set.volumes[1] = volume(10, 2);
    set.volumes[1].id = 0;
    expect(plan_volumetrics(set, 10, plan, diagnostic)
               == LightingError::InvalidArgument,
           "zero id");
    set.volumes[1] = volume(10, 2);
    set.volumes[1].revision = 0;
    expect(plan_volumetrics(set, 10, plan, diagnostic)
               == LightingError::InvalidArgument,
           "zero revision");
    set.volumes[1] = volume(10, 2);
    set.volumes[1].density = std::numeric_limits<f32>::quiet_NaN();
    expect(plan_volumetrics(set, 10, plan, diagnostic)
               == LightingError::NonFiniteValue,
           "density nan");
    set.volumes[1] = volume(10, 2);
    set.volumes[1].extinction = std::numeric_limits<f32>::infinity();
    expect(plan_volumetrics(set, 10, plan, diagnostic)
               == LightingError::NonFiniteValue,
           "extinction inf");
    set.volumes[1] = volume(10, 2);
    set.volumes[1].scattering = -0.1f;
    expect(plan_volumetrics(set, 10, plan, diagnostic)
               == LightingError::OutOfRange,
           "scattering negative");
    set.volumes[1] = volume(10, 2);
    set.volumes[1].anisotropy = 1.1f;
    expect(plan_volumetrics(set, 10, plan, diagnostic)
               == LightingError::OutOfRange,
           "anisotropy high");
    set.volumes[1].anisotropy = -1.1f;
    expect(plan_volumetrics(set, 10, plan, diagnostic)
               == LightingError::OutOfRange,
           "anisotropy low");
    set.volumes[1] = volume(10, 2);
    set.volumes[1].tier = static_cast<VolumetricTier>(200);
    expect(plan_volumetrics(set, 10, plan, diagnostic)
               == LightingError::InvalidArgument,
           "tier enum");
    set.volumes[1] = volume(10, 0);
    expect(plan_volumetrics(set, 10, plan, diagnostic)
               == LightingError::InvalidArgument,
           "steps zero");

    set.count = kMaxVolumetrics + 1;
    expect(plan_volumetrics(set, 10, plan, diagnostic)
               == LightingError::InvalidArgument,
           "capacity");
    expect(diagnostic.code == LightingError::InvalidArgument, "diagnostic");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_gfx06_volumetric_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "vol01") { success = run_vol01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
