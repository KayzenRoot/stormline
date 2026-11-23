#include "stormline/graphics/vfx/trail_plan.hpp"

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

VfxTrailDesc valid_trail() {
    VfxTrailDesc trail{};
    trail.source_id = 6;
    trail.revision = 2;
    trail.sample_count = 4;
    trail.samples[0] = VfxTrailSample{0.0f, 0.3f};
    trail.samples[1] = VfxTrailSample{0.1f, 0.25f};
    trail.samples[2] = VfxTrailSample{0.2f, 0.2f};
    trail.samples[3] = VfxTrailSample{0.3f, 0.15f};
    trail.max_segments = 4;
    trail.max_vertices = 8;
    trail.max_age_seconds = 1.0f;
    return trail;
}

bool run_trl01() {
    begin();
    VfxTrailDesc trail = valid_trail();
    VfxTrailPlan plan{};
    VfxDiagnostic diagnostic{};

    expect(plan_trail(trail, plan, diagnostic) == VfxError::None,
           "valid trail");
    expect(plan.segments == 3 && plan.vertices == 8,
           "valid geometry");
    expect(plan.lifetime_seconds == 0.3f, "lifetime");

    trail.source_id = 0;
    expect(plan_trail(trail, plan, diagnostic) == VfxError::InvalidArgument,
           "zero source");
    expect(plan.segments == 0 && plan.lifetime_seconds == 0.0f, "reset");

    trail = valid_trail();
    trail.sample_count = 1;
    expect(plan_trail(trail, plan, diagnostic) == VfxError::GeometryInvalid,
           "too few samples");
    trail.sample_count = kMaxTrailSamples + 1;
    expect(plan_trail(trail, plan, diagnostic) == VfxError::GeometryInvalid,
           "too many samples");
    trail = valid_trail();
    trail.samples[2].age_seconds = 0.05f;
    expect(plan_trail(trail, plan, diagnostic) == VfxError::GeometryInvalid,
           "unordered ages");
    trail = valid_trail();
    trail.samples[1].age_seconds = 0.2f;
    trail.samples[2].age_seconds = 0.2f;
    expect(plan_trail(trail, plan, diagnostic) == VfxError::GeometryInvalid,
           "duplicate ages");
    trail = valid_trail();
    trail.samples[1].width = 0.0f;
    expect(plan_trail(trail, plan, diagnostic) == VfxError::GeometryInvalid,
           "zero width");
    trail = valid_trail();
    trail.samples[1].age_seconds = std::numeric_limits<f32>::quiet_NaN();
    expect(plan_trail(trail, plan, diagnostic) == VfxError::NonFiniteValue,
           "nonfinite age");
    trail = valid_trail();
    trail.max_age_seconds = 0.2f;
    expect(plan_trail(trail, plan, diagnostic) == VfxError::OutOfRange,
           "max age");
    trail = valid_trail();
    trail.max_age_seconds = 0.0f;
    expect(plan_trail(trail, plan, diagnostic) == VfxError::OutOfRange,
           "zero max age");
    trail = valid_trail();
    trail.max_segments = 0;
    expect(plan_trail(trail, plan, diagnostic) == VfxError::InvalidArgument,
           "zero segment cap");
    trail = valid_trail();
    trail.max_vertices = 7;
    expect(plan_trail(trail, plan, diagnostic) == VfxError::BudgetExceeded,
           "vertex cap");
    trail = valid_trail();
    trail.max_segments = 2;
    expect(plan_trail(trail, plan, diagnostic) == VfxError::BudgetExceeded,
           "segment cap");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_gfx08_trail_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "trl01") { success = run_trl01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
