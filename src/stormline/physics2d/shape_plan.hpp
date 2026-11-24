#ifndef STORMLINE_PHYSICS2D_SHAPE_PLAN_HPP
#define STORMLINE_PHYSICS2D_SHAPE_PLAN_HPP

#include <array>

#include "stormline/physics2d/physics2d_types.hpp"

namespace stormline::physics2d {

struct ShapeDesc {
    u32 shape_id{0};
    u32 body_id{0};
    u32 revision{0};
    ShapeKind kind{ShapeKind::Circle};
    f32 half_x{0.0f};
    f32 half_y{0.0f};
    f32 radius{0.0f};
    f32 density{0.0f};
    bool sensor{false};
};

struct ShapeSetDesc {
    u32 world_id{0};
    u32 revision{0};
    u32 shape_count{0};
    std::array<ShapeDesc, kMaxShapes> shapes{};
};

struct ShapePlan {
    u32 shape_count{0};
    u32 circle_count{0};
    u32 box_count{0};
    u32 capsule_count{0};
    u32 polygon_count{0};
    u32 sensor_count{0};
};

[[nodiscard]] inline Physics2DError plan_shapes(
    const ShapeSetDesc& shapes, ShapePlan& plan,
    Physics2DDiagnostic& diagnostic) noexcept {
    plan = ShapePlan{};
    diagnostic = Physics2DDiagnostic{};
    if (shapes.world_id == 0 || shapes.revision == 0) {
        return detail::set_physics2d_error(
            diagnostic, Physics2DError::InvalidArgument, shapes.world_id, 0);
    }
    if (shapes.shape_count > kMaxShapes) {
        return detail::set_physics2d_error(
            diagnostic, Physics2DError::CapacityFull, shapes.world_id, 0);
    }
    for (u32 index = 0; index < shapes.shape_count; ++index) {
        const ShapeDesc& shape = shapes.shapes[index];
        if (shape.shape_id == 0 || shape.body_id == 0
            || shape.revision == 0
            || !detail::valid_shape_kind(shape.kind)) {
            return detail::set_physics2d_error(
                diagnostic, Physics2DError::ShapeInvalid, shapes.world_id,
                index);
        }
        if (!detail::finite(shape.half_x) || !detail::finite(shape.half_y)
            || !detail::finite(shape.radius)
            || !detail::finite(shape.density)) {
            return detail::set_physics2d_error(
                diagnostic, Physics2DError::NonFiniteValue, shapes.world_id,
                index);
        }
        if (shape.kind == ShapeKind::Circle
            || shape.kind == ShapeKind::Capsule) {
            if (!(shape.radius > 0.0f)) {
                return detail::set_physics2d_error(
                    diagnostic, Physics2DError::ShapeInvalid, shapes.world_id,
                    index);
            }
        } else {
            if (!(shape.half_x > 0.0f) || !(shape.half_y > 0.0f)) {
                return detail::set_physics2d_error(
                    diagnostic, Physics2DError::ShapeInvalid, shapes.world_id,
                    index);
            }
        }
        if (!(shape.density >= 0.0f)) {
            return detail::set_physics2d_error(
                diagnostic, Physics2DError::OutOfRange, shapes.world_id,
                index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (shapes.shapes[previous].shape_id == shape.shape_id) {
                return detail::set_physics2d_error(
                    diagnostic, Physics2DError::DuplicateId, shapes.world_id,
                    index);
            }
        }
    }
    plan.shape_count = shapes.shape_count;
    for (u32 index = 0; index < shapes.shape_count; ++index) {
        const ShapeDesc& shape = shapes.shapes[index];
        switch (shape.kind) {
            case ShapeKind::Circle:
                ++plan.circle_count;
                break;
            case ShapeKind::Box:
                ++plan.box_count;
                break;
            case ShapeKind::Capsule:
                ++plan.capsule_count;
                break;
            case ShapeKind::Polygon:
                ++plan.polygon_count;
                break;
        }
        if (shape.sensor) {
            ++plan.sensor_count;
        }
    }
    return Physics2DError::None;
}

}  // namespace stormline::physics2d

#endif  // STORMLINE_PHYSICS2D_SHAPE_PLAN_HPP
