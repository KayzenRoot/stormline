#ifndef STORMLINE_TILEMAP_COLLISION_PLAN_HPP
#define STORMLINE_TILEMAP_COLLISION_PLAN_HPP

#include "stormline/tilemap/tilemap_types.hpp"

namespace stormline::tilemap {

struct CollisionShapeDesc {
    u32 shape_id{0};
    u32 revision{0};
    CollisionShapeKind kind{CollisionShapeKind::Rect};
    f32 x{0.0f};
    f32 y{0.0f};
    f32 width{0.0f};
    f32 height{0.0f};
    bool solid{true};
    bool one_way{false};
};

struct TileCollisionDesc {
    u32 tile_id{0};
    u32 revision{0};
    u32 shape_count{0};
    std::array<CollisionShapeDesc, kMaxCollisionShapes> shapes{};
};

struct TileCollisionPlan {
    u32 shape_count{0};
    u32 solid_count{0};
};

[[nodiscard]] inline TilemapError plan_tile_collision(
    const TileCollisionDesc& collision, TileCollisionPlan& plan,
    TilemapDiagnostic& diagnostic) noexcept {
    plan = TileCollisionPlan{};
    diagnostic = TilemapDiagnostic{};
    if (collision.tile_id == 0 || collision.revision == 0) {
        return detail::set_tilemap_error(
            diagnostic, TilemapError::InvalidArgument, collision.tile_id, 0);
    }
    if (collision.shape_count > kMaxCollisionShapes) {
        return detail::set_tilemap_error(
            diagnostic, TilemapError::CapacityFull, collision.tile_id, 0);
    }
    for (u32 index = 0; index < collision.shape_count; ++index) {
        const CollisionShapeDesc& shape = collision.shapes[index];
        if (shape.shape_id == 0 || shape.revision == 0) {
            return detail::set_tilemap_error(
                diagnostic, TilemapError::InvalidArgument, collision.tile_id,
                index);
        }
        if (!detail::valid_shape_kind(shape.kind)) {
            return detail::set_tilemap_error(
                diagnostic, TilemapError::InvalidArgument, collision.tile_id,
                index);
        }
        if (!detail::finite(shape.x) || !detail::finite(shape.y)
            || !detail::finite(shape.width) || !detail::finite(shape.height)) {
            return detail::set_tilemap_error(
                diagnostic, TilemapError::NonFiniteValue, collision.tile_id,
                index);
        }
        if (shape.one_way && !shape.solid) {
            return detail::set_tilemap_error(
                diagnostic, TilemapError::CollisionInvalid, collision.tile_id,
                index);
        }
        if (shape.kind == CollisionShapeKind::Rect) {
            if (!(shape.width > 0.0f) || !(shape.height > 0.0f)) {
                return detail::set_tilemap_error(
                    diagnostic, TilemapError::CollisionInvalid,
                    collision.tile_id, index);
            }
        } else if (shape.width == 0.0f && shape.height == 0.0f) {
            return detail::set_tilemap_error(
                diagnostic, TilemapError::CollisionInvalid, collision.tile_id,
                index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (collision.shapes[previous].shape_id == shape.shape_id) {
                return detail::set_tilemap_error(
                    diagnostic, TilemapError::DuplicateId, collision.tile_id,
                    index);
            }
        }
        if (shape.solid) {
            ++plan.solid_count;
        }
    }
    plan.shape_count = collision.shape_count;
    return TilemapError::None;
}

}  // namespace stormline::tilemap

#endif  // STORMLINE_TILEMAP_COLLISION_PLAN_HPP
