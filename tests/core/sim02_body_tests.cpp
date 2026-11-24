#include "stormline/physics3d/body_plan.hpp"

#include <cstdio>
#include <limits>
#include <string_view>

namespace {
using namespace stormline::physics3d;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

BodyDesc body(u32 id, BodyKind kind, bool enabled) {
    BodyDesc desc{};
    desc.body_id = id;
    desc.revision = 1;
    desc.kind = kind;
    desc.x = 1.0f;
    desc.y = 2.0f;
    desc.z = 3.0f;
    desc.qx = 0.0f;
    desc.qy = 0.0f;
    desc.qz = 0.0f;
    desc.qw = 1.0f;
    desc.density = 1.0f;
    desc.damping = 0.5f;
    desc.enabled = enabled;
    return desc;
}

BodySetDesc body_set() {
    BodySetDesc desc{};
    desc.world_id = 10;
    desc.revision = 2;
    desc.body_count = 3;
    desc.bodies[0] = body(1, BodyKind::Static, true);
    desc.bodies[1] = body(2, BodyKind::Kinematic, false);
    desc.bodies[2] = body(3, BodyKind::Dynamic, true);
    desc.bodies[2].bullet = true;
    return desc;
}

bool run_body301() {
    begin();
    BodySetDesc bodies = body_set();
    BodyPlan plan{};
    Physics3DDiagnostic diagnostic{};
    expect(plan_bodies(bodies, plan, diagnostic) == Physics3DError::None,
           "valid bodies");
    expect(plan.body_count == 3 && plan.static_count == 1
               && plan.kinematic_count == 1 && plan.dynamic_count == 1
               && plan.enabled_count == 2,
           "valid plan");
    expect(diagnostic.code == Physics3DError::None, "success diagnostic");

    BodyPlan repeat{};
    expect(plan_bodies(bodies, repeat, diagnostic) == Physics3DError::None,
           "repeat bodies");
    expect(repeat.enabled_count == plan.enabled_count, "deterministic plan");

    bodies.world_id = 0;
    expect(plan_bodies(bodies, plan, diagnostic)
               == Physics3DError::InvalidArgument,
           "zero world");
    expect(plan.body_count == 0 && plan.enabled_count == 0,
           "reset on zero world");
    bodies = body_set();
    bodies.revision = 0;
    expect(plan_bodies(bodies, plan, diagnostic)
               == Physics3DError::InvalidArgument,
           "zero revision");
    bodies = body_set();
    bodies.body_count = kMaxBodies + 1;
    expect(plan_bodies(bodies, plan, diagnostic)
               == Physics3DError::CapacityFull,
           "body overflow");

    bodies = body_set();
    bodies.bodies[1].body_id = 0;
    expect(plan_bodies(bodies, plan, diagnostic)
               == Physics3DError::BodyInvalid,
           "zero body id");
    expect(diagnostic.index == 1, "zero body diagnostic");
    bodies = body_set();
    bodies.bodies[1].revision = 0;
    expect(plan_bodies(bodies, plan, diagnostic)
               == Physics3DError::BodyInvalid,
           "zero body revision");
    bodies = body_set();
    bodies.bodies[1].kind = static_cast<BodyKind>(9);
    expect(plan_bodies(bodies, plan, diagnostic)
               == Physics3DError::BodyInvalid,
           "invalid kind");

    bodies = body_set();
    bodies.bodies[1].x = std::numeric_limits<f32>::quiet_NaN();
    expect(plan_bodies(bodies, plan, diagnostic)
               == Physics3DError::NonFiniteValue,
           "non-finite pose");
    bodies = body_set();
    bodies.bodies[1].qz = 2.0f;
    expect(plan_bodies(bodies, plan, diagnostic)
               == Physics3DError::OutOfRange,
           "non-unit quaternion");
    bodies = body_set();
    bodies.bodies[1].density = -1.0f;
    expect(plan_bodies(bodies, plan, diagnostic)
               == Physics3DError::OutOfRange,
           "negative density");
    bodies = body_set();
    bodies.bodies[1].damping = 1.5f;
    expect(plan_bodies(bodies, plan, diagnostic)
               == Physics3DError::OutOfRange,
           "damping above one");
    bodies = body_set();
    bodies.bodies[2].body_id = 1;
    expect(plan_bodies(bodies, plan, diagnostic)
               == Physics3DError::DuplicateId,
           "duplicate body");
    expect(diagnostic.index == 2, "duplicate body diagnostic");

    bodies = body_set();
    bodies.body_count = kMaxBodies;
    for (u32 index = 0; index < kMaxBodies; ++index) {
        bodies.bodies[index] =
            body(index + 1, static_cast<BodyKind>(index % 3), index % 2 == 0);
    }
    expect(plan_bodies(bodies, plan, diagnostic) == Physics3DError::None,
           "capacity bodies");
    expect(plan.body_count == kMaxBodies && plan.enabled_count == kMaxBodies / 2,
           "capacity plan");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_sim02_body_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "body301") { success = run_body301(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
