#include "stormline/physics2d/body_plan.hpp"

#include <cstdio>
#include <limits>
#include <string_view>

namespace {
using namespace stormline::physics2d;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

BodyDesc body(u32 id, BodyKind kind, f32 density, f32 damping, bool enabled) {
    BodyDesc desc{};
    desc.body_id = id;
    desc.revision = 1;
    desc.kind = kind;
    desc.x = static_cast<f32>(id);
    desc.y = -static_cast<f32>(id);
    desc.angle = 0.5f;
    desc.density = density;
    desc.damping = damping;
    desc.enabled = enabled;
    desc.bullet = false;
    return desc;
}

BodySetDesc body_set() {
    BodySetDesc desc{};
    desc.world_id = 10;
    desc.revision = 2;
    desc.body_count = 4;
    desc.bodies[0] = body(1, BodyKind::Static, 1.0f, 0.0f, true);
    desc.bodies[1] = body(2, BodyKind::Dynamic, 2.0f, 0.25f, true);
    desc.bodies[2] = body(3, BodyKind::Kinematic, 0.0f, 0.5f, false);
    desc.bodies[3] = body(4, BodyKind::Dynamic, 1.5f, 1.0f, true);
    return desc;
}

bool run_body01() {
    begin();
    BodySetDesc bodies = body_set();
    BodyPlan plan{};
    Physics2DDiagnostic diagnostic{};
    expect(plan_bodies(bodies, plan, diagnostic) == Physics2DError::None,
           "valid bodies");
    expect(plan.body_count == 4 && plan.static_count == 1
               && plan.kinematic_count == 1 && plan.dynamic_count == 2
               && plan.enabled_count == 3,
           "valid plan");
    expect(diagnostic.code == Physics2DError::None, "success diagnostic");
    BodyPlan repeat{};
    expect(plan_bodies(bodies, repeat, diagnostic) == Physics2DError::None,
           "repeat bodies");
    expect(repeat.dynamic_count == plan.dynamic_count
               && repeat.enabled_count == plan.enabled_count,
           "deterministic plan");

    bodies.world_id = 0;
    expect(plan_bodies(bodies, plan, diagnostic)
               == Physics2DError::InvalidArgument,
           "zero world");
    expect(plan.body_count == 0 && plan.dynamic_count == 0,
           "reset on zero world");
    bodies = body_set();
    bodies.revision = 0;
    expect(plan_bodies(bodies, plan, diagnostic)
               == Physics2DError::InvalidArgument,
           "zero revision");
    bodies = body_set();
    bodies.body_count = kMaxBodies + 1;
    expect(plan_bodies(bodies, plan, diagnostic)
               == Physics2DError::CapacityFull,
           "body overflow");

    bodies = body_set();
    bodies.bodies[1].body_id = 0;
    expect(plan_bodies(bodies, plan, diagnostic)
               == Physics2DError::BodyInvalid,
           "zero body id");
    expect(diagnostic.index == 1, "zero body diagnostic");
    bodies = body_set();
    bodies.bodies[1].revision = 0;
    expect(plan_bodies(bodies, plan, diagnostic)
               == Physics2DError::BodyInvalid,
           "zero body revision");
    bodies = body_set();
    bodies.bodies[1].kind =
        static_cast<BodyKind>(static_cast<u8>(99));
    expect(plan_bodies(bodies, plan, diagnostic)
               == Physics2DError::BodyInvalid,
           "unknown kind");
    bodies = body_set();
    bodies.bodies[3].body_id = 1;
    expect(plan_bodies(bodies, plan, diagnostic)
               == Physics2DError::DuplicateId,
           "duplicate body");
    expect(diagnostic.index == 3, "duplicate body diagnostic");

    bodies = body_set();
    bodies.bodies[0].x = std::numeric_limits<f32>::quiet_NaN();
    expect(plan_bodies(bodies, plan, diagnostic)
               == Physics2DError::NonFiniteValue,
           "nan pose");
    bodies = body_set();
    bodies.bodies[0].density = -1.0f;
    expect(plan_bodies(bodies, plan, diagnostic)
               == Physics2DError::OutOfRange,
           "negative density");
    bodies = body_set();
    bodies.bodies[0].damping = -0.1f;
    expect(plan_bodies(bodies, plan, diagnostic)
               == Physics2DError::OutOfRange,
           "negative damping");
    bodies = body_set();
    bodies.bodies[0].damping = 1.5f;
    expect(plan_bodies(bodies, plan, diagnostic)
               == Physics2DError::OutOfRange,
           "damping overflow");

    bodies = body_set();
    bodies.body_count = kMaxBodies;
    for (u32 index = 0; index < kMaxBodies; ++index) {
        bodies.bodies[index] =
            body(index + 1, static_cast<BodyKind>(index % 3), 1.0f, 0.5f,
                 index % 2 == 0);
    }
    expect(plan_bodies(bodies, plan, diagnostic) == Physics2DError::None,
           "capacity bodies");
    expect(plan.body_count == kMaxBodies && plan.static_count == 22
               && plan.kinematic_count == 21 && plan.dynamic_count == 21
               && plan.enabled_count == 32,
           "capacity plan");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_sim01_body_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "body01") { success = run_body01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
