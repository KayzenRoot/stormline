#ifndef STORMLINE_GRAPHICS_MATERIAL_TEXTURE_SAMPLER_HPP
#define STORMLINE_GRAPHICS_MATERIAL_TEXTURE_SAMPLER_HPP

#include "stormline/graphics/material/material_types.hpp"

#include <cmath>

namespace stormline::graphics::material {

struct SamplerProfile {
    TextureFormat format{TextureFormat::Rgba8Unorm};
    FilterMode min_filter{FilterMode::Linear};
    FilterMode mag_filter{FilterMode::Linear};
    FilterMode mip_filter{FilterMode::Linear};
    WrapMode wrap_u{WrapMode::Repeat};
    WrapMode wrap_v{WrapMode::Repeat};
    f32 lod_bias{0.0f};
    f32 lod_min{0.0f};
    f32 lod_max{12.0f};
    u32 max_anisotropy{1};
    bool compare{false};
};

namespace detail {

inline MaterialError set_sampler_error(
    MaterialDiagnostic& diagnostic, u32 index = 0) noexcept {
    diagnostic = MaterialDiagnostic{
        MaterialError::InvalidSampler, 0, 0, index};
    return MaterialError::InvalidSampler;
}

inline bool valid_sampler_format(TextureFormat format) noexcept {
    switch (format) {
        case TextureFormat::Rgba8Unorm:
        case TextureFormat::Rgba8Srgb:
        case TextureFormat::Rgba16Float:
        case TextureFormat::Depth32Float:
            return true;
    }
    return false;
}

inline bool valid_filter(FilterMode filter) noexcept {
    switch (filter) {
        case FilterMode::Nearest:
        case FilterMode::Linear:
            return true;
    }
    return false;
}

inline bool valid_wrap(WrapMode wrap) noexcept {
    switch (wrap) {
        case WrapMode::Clamp:
        case WrapMode::Repeat:
        case WrapMode::Mirror:
            return true;
    }
    return false;
}

inline bool power_of_two(u32 value) noexcept {
    return value != 0 && (value & (value - 1)) == 0;
}

}  // namespace detail

[[nodiscard]] inline MaterialError validate_sampler(
    const SamplerProfile& sampler,
    MaterialDiagnostic& diagnostic) noexcept {
    diagnostic = MaterialDiagnostic{};
    if (!detail::valid_sampler_format(sampler.format)
        || !detail::valid_filter(sampler.min_filter)
        || !detail::valid_filter(sampler.mag_filter)
        || !detail::valid_filter(sampler.mip_filter)
        || !detail::valid_wrap(sampler.wrap_u)
        || !detail::valid_wrap(sampler.wrap_v)) {
        return detail::set_sampler_error(diagnostic);
    }
    if (!std::isfinite(sampler.lod_bias) || !std::isfinite(sampler.lod_min)
        || !std::isfinite(sampler.lod_max)) {
        return detail::set_sampler_error(diagnostic);
    }
    if (sampler.lod_bias < -16.0f || sampler.lod_bias > 16.0f
        || sampler.lod_min < -16.0f || sampler.lod_min > 16.0f
        || sampler.lod_max < -16.0f || sampler.lod_max > 16.0f
        || sampler.lod_min > sampler.lod_max) {
        return detail::set_sampler_error(diagnostic);
    }
    if (sampler.max_anisotropy < 1 || sampler.max_anisotropy > 16
        || !detail::power_of_two(sampler.max_anisotropy)) {
        return detail::set_sampler_error(diagnostic);
    }
    if (sampler.compare
        && sampler.format != TextureFormat::Depth32Float) {
        return detail::set_sampler_error(diagnostic);
    }
    return MaterialError::None;
}

}  // namespace stormline::graphics::material

#endif  // STORMLINE_GRAPHICS_MATERIAL_TEXTURE_SAMPLER_HPP
