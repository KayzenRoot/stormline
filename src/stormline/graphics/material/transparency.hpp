#ifndef STORMLINE_GRAPHICS_MATERIAL_TRANSPARENCY_HPP
#define STORMLINE_GRAPHICS_MATERIAL_TRANSPARENCY_HPP

#include "stormline/graphics/material/material_types.hpp"

#include <algorithm>
#include <cmath>

namespace stormline::graphics::material {

struct TransparentItem {
    u32 id{0};
    f32 depth{0.0f};
    AlphaMode alpha{AlphaMode::Blend};
    BlendMode blend{BlendMode::AlphaBlend};
    bool depth_write{false};
};

struct TransparentSet {
    u32 count{0};
    std::array<TransparentItem, kMaxTransparentItems> items{};
};

struct TransparencyPlan {
    u32 count{0};
    std::array<u32, kMaxTransparentItems> item_ids{};
    u32 overdraw_count{0};
};

namespace detail {

inline MaterialError set_transparency_error(
    MaterialDiagnostic& diagnostic, MaterialError code, u32 item_id,
    u32 index) noexcept {
    diagnostic = MaterialDiagnostic{code, item_id, 0, index};
    return code;
}

inline bool valid_transparent_alpha(AlphaMode alpha) noexcept {
    return alpha == AlphaMode::Blend || alpha == AlphaMode::Transmission;
}

inline bool valid_blend(BlendMode blend) noexcept {
    switch (blend) {
        case BlendMode::Opaque:
        case BlendMode::AlphaBlend:
        case BlendMode::Premultiplied:
            return true;
    }
    return false;
}

inline bool valid_transparent_blend(
    AlphaMode alpha, BlendMode blend) noexcept {
    if (!valid_blend(blend)) {
        return false;
    }
    if (alpha == AlphaMode::Blend) {
        return blend == BlendMode::AlphaBlend
            || blend == BlendMode::Premultiplied;
    }
    if (alpha == AlphaMode::Transmission) {
        return blend == BlendMode::AlphaBlend;
    }
    return false;
}

struct TransparencyOrderKey {
    f32 depth{0.0f};
    u32 id{0};
};

}  // namespace detail

[[nodiscard]] inline MaterialError plan_transparency(
    const TransparentSet& set, u32 max_items,
    TransparencyPlan& plan, MaterialDiagnostic& diagnostic) noexcept {
    plan = TransparencyPlan{};
    diagnostic = MaterialDiagnostic{};
    if (set.count > kMaxTransparentItems || max_items == 0
        || max_items > kMaxTransparentItems) {
        return detail::set_transparency_error(
            diagnostic, MaterialError::InvalidArgument, 0, 0);
    }
    if (set.count > max_items) {
        return detail::set_transparency_error(
            diagnostic, MaterialError::TransparencyBudgetExceeded, 0, 0);
    }
    std::array<detail::TransparencyOrderKey, kMaxTransparentItems> keys{};
    for (u32 index = 0; index < set.count; ++index) {
        const TransparentItem& item = set.items[index];
        if (item.id == 0 || !std::isfinite(item.depth)) {
            return detail::set_transparency_error(
                diagnostic, MaterialError::InvalidArgument, item.id, index);
        }
        if (!detail::valid_transparent_alpha(item.alpha)) {
            return detail::set_transparency_error(
                diagnostic, MaterialError::InvalidAlphaMode, item.id, index);
        }
        if (item.depth_write || !detail::valid_transparent_blend(
                                    item.alpha, item.blend)) {
            return detail::set_transparency_error(
                diagnostic, MaterialError::InvalidArgument, item.id, index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (set.items[previous].id == item.id) {
                return detail::set_transparency_error(
                    diagnostic, MaterialError::InvalidArgument, item.id, index);
            }
        }
        keys[index] = detail::TransparencyOrderKey{item.depth, item.id};
    }
    std::sort(keys.begin(), keys.begin() + set.count,
              [](const detail::TransparencyOrderKey& left,
                 const detail::TransparencyOrderKey& right) {
                  if (left.depth != right.depth) {
                      return left.depth > right.depth;
                  }
                  return left.id < right.id;
              });
    plan.count = set.count;
    for (u32 index = 0; index < set.count; ++index) {
        plan.item_ids[index] = keys[index].id;
    }
    if (plan.count > 0) {
        plan.overdraw_count = plan.count - 1;
    }
    return MaterialError::None;
}

}  // namespace stormline::graphics::material

#endif  // STORMLINE_GRAPHICS_MATERIAL_TRANSPARENCY_HPP
