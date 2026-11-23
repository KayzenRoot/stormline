#ifndef STORMLINE_GRAPHICS_CANVAS2D_SPRITE_PLAN_HPP
#define STORMLINE_GRAPHICS_CANVAS2D_SPRITE_PLAN_HPP

#include "stormline/graphics/canvas2d/canvas_types.hpp"

namespace stormline::graphics::canvas2d {

struct SpriteDrawDesc {
    u32 sprite_id{0};
    u32 revision{0};
    u32 asset_id{0};
    u32 asset_revision{0};
    u32 atlas_id{0};
    u32 layer_id{0};
    u32 region_x{0};
    u32 region_y{0};
    u32 region_width{0};
    u32 region_height{0};
    f32 pivot_x{0.0f};
    f32 pivot_y{0.0f};
    bool flip_x{false};
    bool flip_y{false};
    f32 tint_r{1.0f};
    f32 tint_g{1.0f};
    f32 tint_b{1.0f};
    f32 tint_a{1.0f};
};

struct SpritePlan {
    u32 sprite_id{0};
    u32 asset_id{0};
    u32 atlas_id{0};
    u32 layer_id{0};
    bool visible{false};
};

[[nodiscard]] inline CanvasError plan_sprite(
    const SpriteDrawDesc& sprite, SpritePlan& plan,
    CanvasDiagnostic& diagnostic) noexcept {
    plan = SpritePlan{};
    diagnostic = CanvasDiagnostic{};
    if (sprite.sprite_id == 0 || sprite.revision == 0
        || sprite.asset_id == 0 || sprite.asset_revision == 0
        || sprite.atlas_id == 0 || sprite.layer_id == 0) {
        return detail::set_canvas_error(
            diagnostic, CanvasError::InvalidArgument, sprite.sprite_id, 0);
    }
    if (sprite.region_width == 0 || sprite.region_height == 0) {
        return detail::set_canvas_error(
            diagnostic, CanvasError::SpriteInvalid, sprite.sprite_id, 0);
    }
    if (!detail::finite(sprite.pivot_x) || !detail::finite(sprite.pivot_y)
        || !detail::finite(sprite.tint_r) || !detail::finite(sprite.tint_g)
        || !detail::finite(sprite.tint_b) || !detail::finite(sprite.tint_a)) {
        return detail::set_canvas_error(
            diagnostic, CanvasError::NonFiniteValue, sprite.sprite_id, 0);
    }
    if (sprite.tint_r < 0.0f || sprite.tint_r > 1.0f
        || sprite.tint_g < 0.0f || sprite.tint_g > 1.0f
        || sprite.tint_b < 0.0f || sprite.tint_b > 1.0f
        || sprite.tint_a < 0.0f || sprite.tint_a > 1.0f) {
        return detail::set_canvas_error(
            diagnostic, CanvasError::OutOfRange, sprite.sprite_id, 0);
    }
    plan.sprite_id = sprite.sprite_id;
    plan.asset_id = sprite.asset_id;
    plan.atlas_id = sprite.atlas_id;
    plan.layer_id = sprite.layer_id;
    plan.visible = true;
    return CanvasError::None;
}

}  // namespace stormline::graphics::canvas2d

#endif  // STORMLINE_GRAPHICS_CANVAS2D_SPRITE_PLAN_HPP
