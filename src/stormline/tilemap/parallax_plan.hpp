#ifndef STORMLINE_TILEMAP_PARALLAX_PLAN_HPP
#define STORMLINE_TILEMAP_PARALLAX_PLAN_HPP

#include "stormline/tilemap/tilemap_types.hpp"

namespace stormline::tilemap {

struct ParallaxLayerDesc {
    u32 layer_id{0};
    u32 revision{0};
    f32 factor_x{1.0f};
    f32 factor_y{1.0f};
    bool repeat_x{false};
    bool repeat_y{false};
};

struct ParallaxPlan {
    f32 factor_x{1.0f};
    f32 factor_y{1.0f};
    bool repeat_x{false};
    bool repeat_y{false};
};

[[nodiscard]] inline TilemapError plan_parallax(
    const ParallaxLayerDesc& parallax, ParallaxPlan& plan,
    TilemapDiagnostic& diagnostic) noexcept {
    plan = ParallaxPlan{};
    diagnostic = TilemapDiagnostic{};
    if (parallax.layer_id == 0 || parallax.revision == 0) {
        return detail::set_tilemap_error(
            diagnostic, TilemapError::InvalidArgument, parallax.layer_id, 0);
    }
    if (!detail::finite(parallax.factor_x)
        || !detail::finite(parallax.factor_y)) {
        return detail::set_tilemap_error(
            diagnostic, TilemapError::NonFiniteValue, parallax.layer_id, 0);
    }
    if (parallax.factor_x < 0.0f || parallax.factor_x > 4.0f
        || parallax.factor_y < 0.0f || parallax.factor_y > 4.0f) {
        return detail::set_tilemap_error(
            diagnostic, TilemapError::ParallaxInvalid, parallax.layer_id, 0);
    }
    plan.factor_x = parallax.factor_x;
    plan.factor_y = parallax.factor_y;
    plan.repeat_x = parallax.repeat_x;
    plan.repeat_y = parallax.repeat_y;
    return TilemapError::None;
}

}  // namespace stormline::tilemap

#endif  // STORMLINE_TILEMAP_PARALLAX_PLAN_HPP
