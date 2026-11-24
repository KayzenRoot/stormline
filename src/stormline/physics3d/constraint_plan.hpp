#ifndef STORMLINE_PHYSICS3D_CONSTRAINT_PLAN_HPP
#define STORMLINE_PHYSICS3D_CONSTRAINT_PLAN_HPP

#include <array>

#include "stormline/physics3d/physics3d_types.hpp"

namespace stormline::physics3d {

struct ConstraintDesc {
    u32 constraint_id{0};
    u32 revision{0};
    ConstraintKind kind{ConstraintKind::Fixed};
    u32 body_a{0};
    u32 body_b{0};
    f32 anchor_a_x{0.0f};
    f32 anchor_a_y{0.0f};
    f32 anchor_a_z{0.0f};
    f32 anchor_b_x{0.0f};
    f32 anchor_b_y{0.0f};
    f32 anchor_b_z{0.0f};
    f32 axis_x{0.0f};
    f32 axis_y{0.0f};
    f32 axis_z{1.0f};
    f32 min_limit{0.0f};
    f32 max_limit{0.0f};
    f32 break_impulse{0.0f};
    bool motor_enabled{false};
    bool collide_connected{false};
};

struct ConstraintSetDesc {
    u32 world_id{0};
    u32 revision{0};
    u32 constraint_count{0};
    std::array<ConstraintDesc, kMaxConstraints> constraints{};
};

struct ConstraintPlan {
    u32 constraint_count{0};
    u32 fixed_count{0};
    u32 distance_count{0};
    u32 hinge_count{0};
    u32 slider_count{0};
    u32 cone_twist_count{0};
    u32 six_dof_count{0};
    u32 motor_count{0};
    u32 collide_count{0};
};

[[nodiscard]] inline bool axis_required(ConstraintKind kind) noexcept {
    return kind == ConstraintKind::Hinge || kind == ConstraintKind::Slider
        || kind == ConstraintKind::ConeTwist;
}

[[nodiscard]] inline Physics3DError plan_constraints(
    const ConstraintSetDesc& constraints, ConstraintPlan& plan,
    Physics3DDiagnostic& diagnostic) noexcept {
    plan = ConstraintPlan{};
    diagnostic = Physics3DDiagnostic{};
    if (constraints.world_id == 0 || constraints.revision == 0) {
        return detail::set_physics3d_error(
            diagnostic, Physics3DError::InvalidArgument, constraints.world_id,
            0);
    }
    if (constraints.constraint_count > kMaxConstraints) {
        return detail::set_physics3d_error(
            diagnostic, Physics3DError::CapacityFull, constraints.world_id, 0);
    }
    for (u32 index = 0; index < constraints.constraint_count; ++index) {
        const ConstraintDesc& joint = constraints.constraints[index];
        if (joint.constraint_id == 0 || joint.revision == 0
            || joint.body_a == 0 || joint.body_b == 0
            || joint.body_a == joint.body_b
            || !detail::valid_constraint_kind(joint.kind)) {
            return detail::set_physics3d_error(
                diagnostic, Physics3DError::ConstraintInvalid,
                constraints.world_id, index);
        }
        if (!detail::finite(joint.anchor_a_x)
            || !detail::finite(joint.anchor_a_y)
            || !detail::finite(joint.anchor_a_z)
            || !detail::finite(joint.anchor_b_x)
            || !detail::finite(joint.anchor_b_y)
            || !detail::finite(joint.anchor_b_z)
            || !detail::finite(joint.min_limit)
            || !detail::finite(joint.max_limit)
            || !detail::finite(joint.break_impulse)) {
            return detail::set_physics3d_error(
                diagnostic, Physics3DError::NonFiniteValue,
                constraints.world_id, index);
        }
        if (!(joint.min_limit <= joint.max_limit)
            || !(joint.break_impulse >= 0.0f)) {
            return detail::set_physics3d_error(
                diagnostic, Physics3DError::OutOfRange, constraints.world_id,
                index);
        }
        if (axis_required(joint.kind)
            && !detail::unit_axis(joint.axis_x, joint.axis_y,
                                  joint.axis_z)) {
            return detail::set_physics3d_error(
                diagnostic, Physics3DError::ConstraintInvalid,
                constraints.world_id, index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (constraints.constraints[previous].constraint_id
                == joint.constraint_id) {
                return detail::set_physics3d_error(
                    diagnostic, Physics3DError::DuplicateId,
                    constraints.world_id, index);
            }
        }
    }
    plan.constraint_count = constraints.constraint_count;
    for (u32 index = 0; index < constraints.constraint_count; ++index) {
        const ConstraintDesc& joint = constraints.constraints[index];
        switch (joint.kind) {
            case ConstraintKind::Fixed:
                ++plan.fixed_count;
                break;
            case ConstraintKind::Distance:
                ++plan.distance_count;
                break;
            case ConstraintKind::Hinge:
                ++plan.hinge_count;
                break;
            case ConstraintKind::Slider:
                ++plan.slider_count;
                break;
            case ConstraintKind::ConeTwist:
                ++plan.cone_twist_count;
                break;
            case ConstraintKind::SixDof:
                ++plan.six_dof_count;
                break;
        }
        if (joint.motor_enabled) {
            ++plan.motor_count;
        }
        if (joint.collide_connected) {
            ++plan.collide_count;
        }
    }
    return Physics3DError::None;
}

}  // namespace stormline::physics3d

#endif  // STORMLINE_PHYSICS3D_CONSTRAINT_PLAN_HPP
