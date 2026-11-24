#ifndef STORMLINE_PHYSICS3D_SHAPE_PLAN_HPP
#define STORMLINE_PHYSICS3D_SHAPE_PLAN_HPP

#include <array>

#include "stormline/physics3d/physics3d_types.hpp"

namespace stormline::physics3d {

struct ShapeDesc {
    u32 shape_id{0};
    u32 body_id{0};
    u32 revision{0};
    ShapeKind kind{ShapeKind::Sphere};
    f32 half_x{0.0f};
    f32 half_y{0.0f};
    f32 half_z{0.0f};
    f32 radius{0.0f};
    f32 half_height{0.0f};
    f32 density{0.0f};
    u32 material_id{0};
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
    u32 sphere_count{0};
    u32 box_count{0};
    u32 capsule_count{0};
    u32 convex_count{0};
    u32 compound_count{0};
    u32 mesh_count{0};
    u32 heightfield_count{0};
    u32 sensor_count{0};
};

[[nodiscard]] inline Physics3DError plan_shapes(
    const ShapeSetDesc& shapes, ShapePlan& plan,
    Physics3DDiagnostic& diagnostic) noexcept {
    plan = ShapePlan{};
    diagnostic = Physics3DDiagnostic{};
    if (shapes.world_id == 0 || shapes.revision == 0) {
        return detail::set_physics3d_error(
            diagnostic, Physics3DError::InvalidArgument, shapes.world_id, 0);
    }
    if (shapes.shape_count > kMaxShapes) {
        return detail::set_physics3d_error(
            diagnostic, Physics3DError::CapacityFull, shapes.world_id, 0);
    }
    for (u32 index = 0; index < shapes.shape_count; ++index) {
        const ShapeDesc& shape = shapes.shapes[index];
        if (shape.shape_id == 0 || shape.body_id == 0
            || shape.revision == 0
            || !detail::valid_shape_kind(shape.kind)
            || shape.material_id == 0) {
            return detail::set_physics3d_error(
                diagnostic, Physics3DError::ShapeInvalid, shapes.world_id,
                index);
        }
        if (!detail::finite(shape.half_x) || !detail::finite(shape.half_y)
            || !detail::finite(shape.half_z)
            || !detail::finite(shape.radius)
            || !detail::finite(shape.half_height)
            || !detail::finite(shape.density)) {
            return detail::set_physics3d_error(
                diagnostic, Physics3DError::NonFiniteValue, shapes.world_id,
                index);
        }
        switch (shape.kind) {
            case ShapeKind::Sphere:
                if (!(shape.radius > 0.0f)) {
                    return detail::set_physics3d_error(
                        diagnostic, Physics3DError::ShapeInvalid,
                        shapes.world_id, index);
                }
                break;
            case ShapeKind::Capsule:
                if (!(shape.radius > 0.0f) || !(shape.half_height >= 0.0f)) {
                    return detail::set_physics3d_error(
                        diagnostic, Physics3DError::ShapeInvalid,
                        shapes.world_id, index);
                }
                break;
            case ShapeKind::Box:
            case ShapeKind::Convex:
            case ShapeKind::Compound:
            case ShapeKind::Mesh:
            case ShapeKind::Heightfield:
                if (!(shape.half_x > 0.0f) || !(shape.half_y > 0.0f)
                    || !(shape.half_z > 0.0f)) {
                    return detail::set_physics3d_error(
                        diagnostic, Physics3DError::ShapeInvalid,
                        shapes.world_id, index);
                }
                break;
        }
        if (!(shape.density >= 0.0f)) {
            return detail::set_physics3d_error(
                diagnostic, Physics3DError::OutOfRange, shapes.world_id,
                index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (shapes.shapes[previous].shape_id == shape.shape_id) {
                return detail::set_physics3d_error(
                    diagnostic, Physics3DError::DuplicateId, shapes.world_id,
                    index);
            }
        }
    }
    plan.shape_count = shapes.shape_count;
    for (u32 index = 0; index < shapes.shape_count; ++index) {
        const ShapeDesc& shape = shapes.shapes[index];
        switch (shape.kind) {
            case ShapeKind::Sphere:
                ++plan.sphere_count;
                break;
            case ShapeKind::Box:
                ++plan.box_count;
                break;
            case ShapeKind::Capsule:
                ++plan.capsule_count;
                break;
            case ShapeKind::Convex:
                ++plan.convex_count;
                break;
            case ShapeKind::Compound:
                ++plan.compound_count;
                break;
            case ShapeKind::Mesh:
                ++plan.mesh_count;
                break;
            case ShapeKind::Heightfield:
                ++plan.heightfield_count;
                break;
        }
        if (shape.sensor) {
            ++plan.sensor_count;
        }
    }
    return Physics3DError::None;
}

}  // namespace stormline::physics3d

#endif  // STORMLINE_PHYSICS3D_SHAPE_PLAN_HPP
