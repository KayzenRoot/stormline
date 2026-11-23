#ifndef STORMLINE_GRAPHICS_RHI_RHI_FEATURE_HPP
#define STORMLINE_GRAPHICS_RHI_RHI_FEATURE_HPP

#include "stormline/graphics/rhi/rhi_device.hpp"

namespace stormline::graphics::rhi {

inline constexpr u32 kSupportedTier = 1;

[[nodiscard]] inline bool features_supported(
    u32 available, u32 required) noexcept {
    return required != 0 && (required & ~kAllFeatures) == 0
        && (required & ~available) == 0;
}

[[nodiscard]] inline bool tier_supported(u32 tier) noexcept {
    return tier == kSupportedTier;
}

}  // namespace stormline::graphics::rhi

#endif  // STORMLINE_GRAPHICS_RHI_RHI_FEATURE_HPP
