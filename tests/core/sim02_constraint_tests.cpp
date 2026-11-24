#include "stormline/physics3d/constraint_plan.hpp"

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

ConstraintDesc joint(u32 id, ConstraintKind kind, bool motor, bool collide) {
    ConstraintDesc desc{};
    desc.constraint_id = id;
    desc.revision = 1;
    desc.kind = kind;
    desc.body_a = 1;
    desc.body_b = 2;
    desc.anchor_a_x = 0.0f;
    desc.anchor_a_y = 0.0f;
    desc.anchor_a_z = 0.0f;
    desc.anchor_b_x = 0.0f;
    desc.anchor_b_y = 0.0f;
    desc.anchor_b_z = 0.0f;
    desc.axis_x = 0.0f;
    desc.axis_y = 0.0f;
    desc.axis_z = 1.0f;
    desc.min_limit = 0.0f;
    desc.max_limit = 1.0f;
    desc.break_impulse = 10.0f;
    desc.motor_enabled = motor;
    desc.collide_connected = collide;
    return desc;
}

ConstraintSetDesc joint_set() {
    ConstraintSetDesc desc{};
    desc.world_id = 10;
    desc.revision = 2;
    desc.constraint_count = 4;
    desc.constraints[0] = joint(1, ConstraintKind::Fixed, false, false);
    desc.constraints[1] = joint(2, ConstraintKind::Hinge, true, false);
    desc.constraints[2] = joint(3, ConstraintKind::Slider, false, true);
    desc.constraints[3] = joint(4, ConstraintKind::ConeTwist, false, false);
    return desc;
}

bool run_constraint301() {
    begin();
    ConstraintSetDesc constraints = joint_set();
    ConstraintPlan plan{};
    Physics3DDiagnostic diagnostic{};
    expect(plan_constraints(constraints, plan, diagnostic)
               == Physics3DError::None,
           "valid constraints");
    expect(plan.constraint_count == 4 && plan.fixed_count == 1
               && plan.hinge_count == 1 && plan.slider_count == 1
               && plan.cone_twist_count == 1 && plan.motor_count == 1
               && plan.collide_count == 1,
           "valid plan");
    expect(diagnostic.code == Physics3DError::None, "success diagnostic");

    ConstraintPlan repeat{};
    expect(plan_constraints(constraints, repeat, diagnostic)
               == Physics3DError::None,
           "repeat constraints");
    expect(repeat.motor_count == plan.motor_count, "deterministic plan");

    constraints.world_id = 0;
    expect(plan_constraints(constraints, plan, diagnostic)
               == Physics3DError::InvalidArgument,
           "zero world");
    expect(plan.constraint_count == 0, "reset on zero world");
    constraints = joint_set();
    constraints.revision = 0;
    expect(plan_constraints(constraints, plan, diagnostic)
               == Physics3DError::InvalidArgument,
           "zero revision");
    constraints = joint_set();
    constraints.constraint_count = kMaxConstraints + 1;
    expect(plan_constraints(constraints, plan, diagnostic)
               == Physics3DError::CapacityFull,
           "constraint overflow");

    constraints = joint_set();
    constraints.constraints[1].constraint_id = 0;
    expect(plan_constraints(constraints, plan, diagnostic)
               == Physics3DError::ConstraintInvalid,
           "zero constraint id");
    expect(diagnostic.index == 1, "zero constraint diagnostic");
    constraints = joint_set();
    constraints.constraints[1].revision = 0;
    expect(plan_constraints(constraints, plan, diagnostic)
               == Physics3DError::ConstraintInvalid,
           "zero revision");
    constraints = joint_set();
    constraints.constraints[1].body_a = 0;
    expect(plan_constraints(constraints, plan, diagnostic)
               == Physics3DError::ConstraintInvalid,
           "zero body a");
    constraints = joint_set();
    constraints.constraints[1].body_b = constraints.constraints[1].body_a;
    expect(plan_constraints(constraints, plan, diagnostic)
               == Physics3DError::ConstraintInvalid,
           "same bodies");
    constraints = joint_set();
    constraints.constraints[1].kind = static_cast<ConstraintKind>(9);
    expect(plan_constraints(constraints, plan, diagnostic)
               == Physics3DError::ConstraintInvalid,
           "invalid kind");
    constraints = joint_set();
    constraints.constraints[1].axis_z = 0.0f;
    expect(plan_constraints(constraints, plan, diagnostic)
               == Physics3DError::ConstraintInvalid,
           "non-unit hinge axis");

    constraints = joint_set();
    constraints.constraints[1].anchor_b_y =
        std::numeric_limits<f32>::quiet_NaN();
    expect(plan_constraints(constraints, plan, diagnostic)
               == Physics3DError::NonFiniteValue,
           "non-finite anchor");
    constraints = joint_set();
    constraints.constraints[1].min_limit = 2.0f;
    constraints.constraints[1].max_limit = 1.0f;
    expect(plan_constraints(constraints, plan, diagnostic)
               == Physics3DError::OutOfRange,
           "min above max");
    constraints = joint_set();
    constraints.constraints[1].break_impulse = -1.0f;
    expect(plan_constraints(constraints, plan, diagnostic)
               == Physics3DError::OutOfRange,
           "negative break impulse");
    constraints = joint_set();
    constraints.constraints[2].constraint_id = 1;
    expect(plan_constraints(constraints, plan, diagnostic)
               == Physics3DError::DuplicateId,
           "duplicate constraint");
    expect(diagnostic.index == 2, "duplicate constraint diagnostic");

    constraints = joint_set();
    constraints.constraint_count = kMaxConstraints;
    for (u32 index = 0; index < kMaxConstraints; ++index) {
        constraints.constraints[index] =
            joint(index + 1, static_cast<ConstraintKind>(index % 6),
                  index % 2 == 0, index % 3 == 0);
    }
    expect(plan_constraints(constraints, plan, diagnostic)
               == Physics3DError::None,
           "capacity constraints");
    expect(plan.constraint_count == kMaxConstraints
               && plan.motor_count == kMaxConstraints / 2,
           "capacity plan");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_sim02_constraint_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "constraint301") { success = run_constraint301(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
