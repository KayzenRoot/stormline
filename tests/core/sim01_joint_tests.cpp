#include "stormline/physics2d/joint_plan.hpp"

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

JointDesc joint(u32 id, JointKind kind, u32 a, u32 b, bool collide) {
    JointDesc desc{};
    desc.joint_id = id;
    desc.revision = 1;
    desc.kind = kind;
    desc.body_a = a;
    desc.body_b = b;
    desc.anchor_a_x = 0.5f;
    desc.anchor_a_y = -0.5f;
    desc.anchor_b_x = 1.5f;
    desc.anchor_b_y = -1.5f;
    desc.min_limit = -1.0f;
    desc.max_limit = 1.0f;
    desc.collide_connected = collide;
    return desc;
}

JointSetDesc joint_set() {
    JointSetDesc desc{};
    desc.world_id = 10;
    desc.revision = 2;
    desc.joint_count = 4;
    desc.joints[0] = joint(1, JointKind::Distance, 1, 2, false);
    desc.joints[1] = joint(2, JointKind::Revolute, 2, 3, true);
    desc.joints[2] = joint(3, JointKind::Prismatic, 3, 4, false);
    desc.joints[3] = joint(4, JointKind::Weld, 4, 5, true);
    return desc;
}

bool run_jnt01() {
    begin();
    JointSetDesc joints = joint_set();
    JointPlan plan{};
    Physics2DDiagnostic diagnostic{};
    expect(plan_joints(joints, plan, diagnostic) == Physics2DError::None,
           "valid joints");
    expect(plan.joint_count == 4 && plan.distance_count == 1
               && plan.revolute_count == 1 && plan.prismatic_count == 1
               && plan.weld_count == 1 && plan.collide_count == 2,
           "valid plan");
    expect(diagnostic.code == Physics2DError::None, "success diagnostic");
    JointPlan repeat{};
    expect(plan_joints(joints, repeat, diagnostic) == Physics2DError::None,
           "repeat joints");
    expect(repeat.collide_count == plan.collide_count
               && repeat.weld_count == plan.weld_count,
           "deterministic plan");

    joints.world_id = 0;
    expect(plan_joints(joints, plan, diagnostic)
               == Physics2DError::InvalidArgument,
           "zero world");
    expect(plan.joint_count == 0 && plan.collide_count == 0,
           "reset on zero world");
    joints = joint_set();
    joints.revision = 0;
    expect(plan_joints(joints, plan, diagnostic)
               == Physics2DError::InvalidArgument,
           "zero revision");
    joints = joint_set();
    joints.joint_count = kMaxJoints + 1;
    expect(plan_joints(joints, plan, diagnostic)
               == Physics2DError::CapacityFull,
           "joint overflow");

    joints = joint_set();
    joints.joints[1].joint_id = 0;
    expect(plan_joints(joints, plan, diagnostic)
               == Physics2DError::JointInvalid,
           "zero joint id");
    expect(diagnostic.index == 1, "zero joint diagnostic");
    joints = joint_set();
    joints.joints[1].revision = 0;
    expect(plan_joints(joints, plan, diagnostic)
               == Physics2DError::JointInvalid,
           "zero joint revision");
    joints = joint_set();
    joints.joints[1].body_a = 0;
    expect(plan_joints(joints, plan, diagnostic)
               == Physics2DError::JointInvalid,
           "zero body a");
    joints = joint_set();
    joints.joints[1].body_b = joints.joints[1].body_a;
    expect(plan_joints(joints, plan, diagnostic)
               == Physics2DError::JointInvalid,
           "same body");
    joints = joint_set();
    joints.joints[1].kind =
        static_cast<JointKind>(static_cast<u8>(99));
    expect(plan_joints(joints, plan, diagnostic)
               == Physics2DError::JointInvalid,
           "unknown kind");
    joints = joint_set();
    joints.joints[3].joint_id = 1;
    expect(plan_joints(joints, plan, diagnostic)
               == Physics2DError::DuplicateId,
           "duplicate joint");
    expect(diagnostic.index == 3, "duplicate joint diagnostic");

    joints = joint_set();
    joints.joints[0].anchor_a_x =
        std::numeric_limits<f32>::quiet_NaN();
    expect(plan_joints(joints, plan, diagnostic)
               == Physics2DError::NonFiniteValue,
           "nan anchor");
    joints = joint_set();
    joints.joints[0].min_limit = 2.0f;
    joints.joints[0].max_limit = 1.0f;
    expect(plan_joints(joints, plan, diagnostic)
               == Physics2DError::OutOfRange,
           "reversed limits");

    joints = joint_set();
    joints.joint_count = kMaxJoints;
    for (u32 index = 0; index < kMaxJoints; ++index) {
        joints.joints[index] =
            joint(index + 1, static_cast<JointKind>(index % 4),
                  index + 1, index + 2, index % 2 == 0);
    }
    expect(plan_joints(joints, plan, diagnostic) == Physics2DError::None,
           "capacity joints");
    expect(plan.joint_count == kMaxJoints && plan.distance_count == 16
               && plan.revolute_count == 16 && plan.prismatic_count == 16
               && plan.weld_count == 16 && plan.collide_count == 32,
           "capacity plan");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_sim01_joint_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "jnt01") { success = run_jnt01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
