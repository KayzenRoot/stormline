#ifndef STORMLINE_PHYSICS2D_BODY_PLAN_HPP
#define STORMLINE_PHYSICS2D_BODY_PLAN_HPP

#include <array>

#include "stormline/physics2d/physics2d_types.hpp"

namespace stormline::physics2d {

struct BodyDesc {
    u32 body_id{0};
    u32 revision{0};
    BodyKind kind{BodyKind::Static};
    f32 x{0.0f};
    f32 y{0.0f};
    f32 angle{0.0f};
    f32 density{0.0f};
    f32 damping{0.0f};
    bool enabled{false};
    bool bullet{false};
};

struct BodySetDesc {
    u32 world_id{0};
    u32 revision{0};
    u32 body_count{0};
    std::array<BodyDesc, kMaxBodies> bodies{};
};

struct BodyPlan {
    u32 body_count{0};
    u32 static_count{0};
    u32 kinematic_count{0};
    u32 dynamic_count{0};
    u32 enabled_count{0};
};

[[nodiscard]] inline Physics2DError plan_bodies(
    const BodySetDesc& bodies, BodyPlan& plan,
    Physics2DDiagnostic& diagnostic) noexcept {
    plan = BodyPlan{};
    diagnostic = Physics2DDiagnostic{};
    if (bodies.world_id == 0 || bodies.revision == 0) {
        return detail::set_physics2d_error(
            diagnostic, Physics2DError::InvalidArgument, bodies.world_id, 0);
    }
    if (bodies.body_count > kMaxBodies) {
        return detail::set_physics2d_error(
            diagnostic, Physics2DError::CapacityFull, bodies.world_id, 0);
    }
    for (u32 index = 0; index < bodies.body_count; ++index) {
        const BodyDesc& body = bodies.bodies[index];
        if (body.body_id == 0 || body.revision == 0
            || !detail::valid_body_kind(body.kind)) {
            return detail::set_physics2d_error(
                diagnostic, Physics2DError::BodyInvalid, bodies.world_id,
                index);
        }
        if (!detail::finite(body.x) || !detail::finite(body.y)
            || !detail::finite(body.angle) || !detail::finite(body.density)
            || !detail::finite(body.damping)) {
            return detail::set_physics2d_error(
                diagnostic, Physics2DError::NonFiniteValue, bodies.world_id,
                index);
        }
        if (!(body.density >= 0.0f) || !(body.damping >= 0.0f)
            || !(body.damping <= 1.0f)) {
            return detail::set_physics2d_error(
                diagnostic, Physics2DError::OutOfRange, bodies.world_id,
                index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (bodies.bodies[previous].body_id == body.body_id) {
                return detail::set_physics2d_error(
                    diagnostic, Physics2DError::DuplicateId, bodies.world_id,
                    index);
            }
        }
    }
    plan.body_count = bodies.body_count;
    for (u32 index = 0; index < bodies.body_count; ++index) {
        const BodyDesc& body = bodies.bodies[index];
        switch (body.kind) {
            case BodyKind::Static:
                ++plan.static_count;
                break;
            case BodyKind::Kinematic:
                ++plan.kinematic_count;
                break;
            case BodyKind::Dynamic:
                ++plan.dynamic_count;
                break;
        }
        if (body.enabled) {
            ++plan.enabled_count;
        }
    }
    return Physics2DError::None;
}

}  // namespace stormline::physics2d

#endif  // STORMLINE_PHYSICS2D_BODY_PLAN_HPP
