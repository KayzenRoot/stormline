#ifndef STORMLINE_GRAPHICS_MATERIAL_DECAL_HPP
#define STORMLINE_GRAPHICS_MATERIAL_DECAL_HPP

#include "stormline/graphics/material/material_types.hpp"

#include <algorithm>
#include <cmath>

namespace stormline::graphics::material {

struct DecalDesc {
    u32 id{0};
    u32 layer{0};
    f32 x{0.0f};
    f32 y{0.0f};
    f32 z{0.0f};
    f32 radius{0.0f};
    f32 opacity{1.0f};
    bool normal_blend{false};
};

struct DecalSet {
    u32 count{0};
    std::array<DecalDesc, kMaxDecals> decals{};
};

struct DecalPlan {
    u32 count{0};
    std::array<u32, kMaxDecals> decal_ids{};
};

namespace detail {

inline MaterialError set_decal_error(
    MaterialDiagnostic& diagnostic, MaterialError code, u32 decal_id,
    u32 index) noexcept {
    diagnostic = MaterialDiagnostic{code, decal_id, 0, index};
    return code;
}

inline bool valid_decal(const DecalDesc& decal) noexcept {
    return decal.id != 0 && decal.layer < 32
        && std::isfinite(decal.x) && std::isfinite(decal.y)
        && std::isfinite(decal.z) && std::isfinite(decal.radius)
        && decal.radius > 0.0f && std::isfinite(decal.opacity)
        && decal.opacity >= 0.0f && decal.opacity <= 1.0f;
}

struct DecalOrderKey {
    u32 layer{0};
    u32 id{0};
};

}  // namespace detail

[[nodiscard]] inline MaterialError plan_decals(
    const DecalSet& set, DecalPlan& plan,
    MaterialDiagnostic& diagnostic) noexcept {
    plan = DecalPlan{};
    diagnostic = MaterialDiagnostic{};
    if (set.count > kMaxDecals) {
        return detail::set_decal_error(
            diagnostic, MaterialError::CapacityFull, 0, 0);
    }
    std::array<detail::DecalOrderKey, kMaxDecals> keys{};
    for (u32 index = 0; index < set.count; ++index) {
        const DecalDesc& decal = set.decals[index];
        if (!detail::valid_decal(decal)) {
            return detail::set_decal_error(
                diagnostic, MaterialError::InvalidArgument, decal.id, index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (set.decals[previous].id == decal.id) {
                return detail::set_decal_error(
                    diagnostic, MaterialError::DecalConflict, decal.id, index);
            }
        }
        keys[index] = detail::DecalOrderKey{decal.layer, decal.id};
    }
    std::sort(keys.begin(), keys.begin() + set.count,
              [](const detail::DecalOrderKey& left,
                 const detail::DecalOrderKey& right) {
                  if (left.layer != right.layer) {
                      return left.layer < right.layer;
                  }
                  return left.id < right.id;
              });
    plan.count = set.count;
    for (u32 index = 0; index < set.count; ++index) {
        plan.decal_ids[index] = keys[index].id;
    }
    return MaterialError::None;
}

}  // namespace stormline::graphics::material

#endif  // STORMLINE_GRAPHICS_MATERIAL_DECAL_HPP
