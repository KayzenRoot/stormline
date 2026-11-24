#ifndef STORMLINE_PHYSICS2D_JOINT_PLAN_HPP
#define STORMLINE_PHYSICS2D_JOINT_PLAN_HPP

#include <array>

#include "stormline/physics2d/physics2d_types.hpp"

namespace stormline::physics2d {

struct JointDesc {
    u32 joint_id{0};
    u32 revision{0};
    JointKind kind{JointKind::Distance};
    u32 body_a{0};
    u32 body_b{0};
    f32 anchor_a_x{0.0f};
    f32 anchor_a_y{0.0f};
    f32 anchor_b_x{0.0f};
    f32 anchor_b_y{0.0f};
    f32 min_limit{0.0f};
    f32 max_limit{0.0f};
    bool collide_connected{false};
};

struct JointSetDesc {
    u32 world_id{0};
    u32 revision{0};
    u32 joint_count{0};
    std::array<JointDesc, kMaxJoints> joints{};
};

struct JointPlan {
    u32 joint_count{0};
    u32 distance_count{0};
    u32 revolute_count{0};
    u32 prismatic_count{0};
    u32 weld_count{0};
    u32 collide_count{0};
};

[[nodiscard]] inline Physics2DError plan_joints(
    const JointSetDesc& joints, JointPlan& plan,
    Physics2DDiagnostic& diagnostic) noexcept {
    plan = JointPlan{};
    diagnostic = Physics2DDiagnostic{};
    if (joints.world_id == 0 || joints.revision == 0) {
        return detail::set_physics2d_error(
            diagnostic, Physics2DError::InvalidArgument, joints.world_id, 0);
    }
    if (joints.joint_count > kMaxJoints) {
        return detail::set_physics2d_error(
            diagnostic, Physics2DError::CapacityFull, joints.world_id, 0);
    }
    for (u32 index = 0; index < joints.joint_count; ++index) {
        const JointDesc& joint = joints.joints[index];
        if (joint.joint_id == 0 || joint.revision == 0
            || joint.body_a == 0 || joint.body_b == 0
            || joint.body_a == joint.body_b
            || !detail::valid_joint_kind(joint.kind)) {
            return detail::set_physics2d_error(
                diagnostic, Physics2DError::JointInvalid, joints.world_id,
                index);
        }
        if (!detail::finite(joint.anchor_a_x)
            || !detail::finite(joint.anchor_a_y)
            || !detail::finite(joint.anchor_b_x)
            || !detail::finite(joint.anchor_b_y)
            || !detail::finite(joint.min_limit)
            || !detail::finite(joint.max_limit)) {
            return detail::set_physics2d_error(
                diagnostic, Physics2DError::NonFiniteValue, joints.world_id,
                index);
        }
        if (!(joint.min_limit <= joint.max_limit)) {
            return detail::set_physics2d_error(
                diagnostic, Physics2DError::OutOfRange, joints.world_id,
                index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (joints.joints[previous].joint_id == joint.joint_id) {
                return detail::set_physics2d_error(
                    diagnostic, Physics2DError::DuplicateId, joints.world_id,
                    index);
            }
        }
    }
    plan.joint_count = joints.joint_count;
    for (u32 index = 0; index < joints.joint_count; ++index) {
        const JointDesc& joint = joints.joints[index];
        switch (joint.kind) {
            case JointKind::Distance:
                ++plan.distance_count;
                break;
            case JointKind::Revolute:
                ++plan.revolute_count;
                break;
            case JointKind::Prismatic:
                ++plan.prismatic_count;
                break;
            case JointKind::Weld:
                ++plan.weld_count;
                break;
        }
        if (joint.collide_connected) {
            ++plan.collide_count;
        }
    }
    return Physics2DError::None;
}

}  // namespace stormline::physics2d

#endif  // STORMLINE_PHYSICS2D_JOINT_PLAN_HPP
