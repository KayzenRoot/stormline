#include "stormline/spatial/origin_plan.hpp"

#include <cstdio>
#include <limits>
#include <string_view>

namespace {
using namespace stormline::spatial;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

OriginEpochDesc origin_epoch() {
    OriginEpochDesc desc{};
    desc.world_id = 10;
    desc.revision = 2;
    desc.old_epoch = 4;
    desc.new_epoch = 5;
    desc.old_x = 1.0f;
    desc.old_y = -2.0f;
    desc.old_z = 3.0f;
    desc.new_x = -4.0f;
    desc.new_y = 5.0f;
    desc.new_z = -6.0f;
    desc.physics_ack = true;
    desc.render_ack = true;
    desc.network_ack = true;
    return desc;
}

bool run_org01() {
    begin();
    OriginEpochDesc origin = origin_epoch();
    OriginPlan plan{};
    SpatialDiagnostic diagnostic{};
    expect(plan_origin_change(origin, plan, diagnostic) == SpatialError::None,
           "valid origin");
    expect(plan.old_epoch == 4 && plan.new_epoch == 5 && plan.accepted,
           "accepted origin");
    expect(diagnostic.code == SpatialError::None,
           "success diagnostic");
    OriginPlan repeat{};
    expect(plan_origin_change(origin, repeat, diagnostic) == SpatialError::None,
           "repeat origin");
    expect(repeat.old_epoch == plan.old_epoch
               && repeat.new_epoch == plan.new_epoch
               && repeat.accepted == plan.accepted,
           "deterministic origin");

    for (u32 mask = 0; mask < 8; ++mask) {
        origin = origin_epoch();
        origin.physics_ack = (mask & 1u) != 0;
        origin.render_ack = (mask & 2u) != 0;
        origin.network_ack = (mask & 4u) != 0;
        expect(plan_origin_change(origin, plan, diagnostic)
                   == SpatialError::None,
               "ack matrix success");
        expect(plan.accepted == (mask == 7u), "ack matrix acceptance");
    }

    origin = origin_epoch();
    origin.world_id = 0;
    expect(plan_origin_change(origin, plan, diagnostic)
               == SpatialError::InvalidArgument,
           "zero world");
    expect(plan.old_epoch == 0 && plan.new_epoch == 0 && !plan.accepted,
           "reset on zero world");
    origin = origin_epoch();
    origin.revision = 0;
    expect(plan_origin_change(origin, plan, diagnostic)
               == SpatialError::InvalidArgument,
           "zero revision");
    origin = origin_epoch();
    origin.old_epoch = 0;
    expect(plan_origin_change(origin, plan, diagnostic)
               == SpatialError::OriginInvalid,
           "zero old epoch");
    origin = origin_epoch();
    origin.new_epoch = 0;
    expect(plan_origin_change(origin, plan, diagnostic)
               == SpatialError::OriginInvalid,
           "zero new epoch");
    origin = origin_epoch();
    origin.new_epoch = origin.old_epoch;
    expect(plan_origin_change(origin, plan, diagnostic)
               == SpatialError::OriginInvalid,
           "same epoch");

    origin = origin_epoch();
    origin.old_x = std::numeric_limits<f32>::quiet_NaN();
    expect(plan_origin_change(origin, plan, diagnostic)
               == SpatialError::NonFiniteValue,
           "nan old x");
    origin = origin_epoch();
    origin.old_y = std::numeric_limits<f32>::infinity();
    expect(plan_origin_change(origin, plan, diagnostic)
               == SpatialError::NonFiniteValue,
           "infinite old y");
    origin = origin_epoch();
    origin.old_z = -std::numeric_limits<f32>::infinity();
    expect(plan_origin_change(origin, plan, diagnostic)
               == SpatialError::NonFiniteValue,
           "infinite old z");
    origin = origin_epoch();
    origin.new_x = std::numeric_limits<f32>::quiet_NaN();
    expect(plan_origin_change(origin, plan, diagnostic)
               == SpatialError::NonFiniteValue,
           "nan new x");
    origin = origin_epoch();
    origin.new_y = std::numeric_limits<f32>::infinity();
    expect(plan_origin_change(origin, plan, diagnostic)
               == SpatialError::NonFiniteValue,
           "infinite new y");
    origin = origin_epoch();
    origin.new_z = std::numeric_limits<f32>::quiet_NaN();
    expect(plan_origin_change(origin, plan, diagnostic)
               == SpatialError::NonFiniteValue,
           "nan new z");
    expect(plan.accepted == false, "reset on nonfinite");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_world03_origin_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "org01") { success = run_org01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
