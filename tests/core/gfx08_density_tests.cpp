#include "stormline/graphics/vfx/density_plan.hpp"

#include <cstdio>
#include <limits>
#include <string_view>

namespace {
using namespace stormline::graphics::vfx;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

bool run_den01() {
    begin();
    VfxDensityStampDesc stamp{};
    stamp.stamp_id = 8;
    stamp.revision = 2;
    stamp.density = 0.5f;
    stamp.extinction = 0.25f;
    stamp.extent_x = 1.0f;
    stamp.extent_y = 1.0f;
    stamp.extent_z = 1.0f;
    stamp.lifetime_seconds = 2.0f;
    stamp.max_density = 1.0f;
    VfxDensityPlan plan{};
    VfxDiagnostic diagnostic{};

    expect(plan_density_stamp(stamp, plan, diagnostic) == VfxError::None,
           "valid stamp");
    expect(plan.density == 0.5f && plan.extinction == 0.25f
               && !plan.clamped,
           "valid plan");

    stamp.density = 1.5f;
    expect(plan_density_stamp(stamp, plan, diagnostic) == VfxError::None,
           "clamped stamp");
    expect(plan.density == 1.0f && plan.clamped, "clamp receipt");

    stamp.stamp_id = 0;
    expect(plan_density_stamp(stamp, plan, diagnostic)
               == VfxError::InvalidArgument,
           "zero stamp");
    expect(plan.density == 0.0f && !plan.clamped, "reset");

    stamp.stamp_id = 8;
    stamp.density = -0.1f;
    expect(plan_density_stamp(stamp, plan, diagnostic)
               == VfxError::DensityInvalid,
           "negative density");
    stamp.density = 0.5f;
    stamp.extinction = -0.1f;
    expect(plan_density_stamp(stamp, plan, diagnostic)
               == VfxError::DensityInvalid,
           "negative extinction");
    stamp.extinction = 0.25f;
    stamp.extent_y = 0.0f;
    expect(plan_density_stamp(stamp, plan, diagnostic)
               == VfxError::DensityInvalid,
           "zero extent");
    stamp.extent_y = 1.0f;
    stamp.lifetime_seconds = 0.0f;
    expect(plan_density_stamp(stamp, plan, diagnostic)
               == VfxError::DensityInvalid,
           "zero lifetime");
    stamp.lifetime_seconds = 2.0f;
    stamp.max_density = 0.0f;
    expect(plan_density_stamp(stamp, plan, diagnostic)
               == VfxError::DensityInvalid,
           "zero max density");
    stamp.max_density = 1.0f;
    stamp.extent_z = std::numeric_limits<f32>::quiet_NaN();
    expect(plan_density_stamp(stamp, plan, diagnostic)
               == VfxError::NonFiniteValue,
           "nonfinite extent");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_gfx08_density_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "den01") { success = run_den01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
