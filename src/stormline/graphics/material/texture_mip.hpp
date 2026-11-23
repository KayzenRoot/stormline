#ifndef STORMLINE_GRAPHICS_MATERIAL_TEXTURE_MIP_HPP
#define STORMLINE_GRAPHICS_MATERIAL_TEXTURE_MIP_HPP

#include "stormline/graphics/material/virtual_texture.hpp"

#include <algorithm>
#include <cstdint>
#include <limits>

namespace stormline::graphics::material {

struct MipLevel {
    u32 width{0};
    u32 height{0};
    u32 bytes{0};
};

struct MipChain {
    u32 texture_id{0};
    u32 count{0};
    std::array<MipLevel, kMaxMips> levels{};
};

namespace detail {

inline u32 mip_bytes_per_pixel(TextureFormat format) noexcept {
    switch (format) {
        case TextureFormat::Rgba8Unorm:
        case TextureFormat::Rgba8Srgb:
        case TextureFormat::Depth32Float:
            return 4;
        case TextureFormat::Rgba16Float:
            return 8;
    }
    return 0;
}

}  // namespace detail

[[nodiscard]] inline MaterialError build_mip_chain(
    const TextureDesc& texture, MipChain& chain,
    MaterialDiagnostic& diagnostic) noexcept {
    chain = MipChain{};
    diagnostic = MaterialDiagnostic{};
    if (texture.levels == 0 || texture.levels > kMaxMips
        || texture.levels != detail::expected_levels(texture.width,
                                                      texture.height)) {
        return detail::set_texture_error(
            diagnostic, MaterialError::InvalidMipChain, texture.id, 0);
    }
    const MaterialError validation = detail::validate_texture_desc(texture);
    if (validation != MaterialError::None) {
        return detail::set_texture_error(
            diagnostic, MaterialError::InvalidArgument, texture.id, 0);
    }
    const u32 bytes_per_pixel = detail::mip_bytes_per_pixel(texture.format);
    if (bytes_per_pixel == 0) {
        return detail::set_texture_error(
            diagnostic, MaterialError::InvalidMipChain, texture.id, 0);
    }
    MipChain result{};
    result.texture_id = texture.id;
    result.count = texture.levels;
    for (u32 level = 0; level < texture.levels; ++level) {
        const u32 width = std::max<u32>(1, texture.width >> level);
        const u32 height = std::max<u32>(1, texture.height >> level);
        const std::uint64_t bytes =
            static_cast<std::uint64_t>(width) * height * bytes_per_pixel;
        if (bytes > std::numeric_limits<u32>::max()) {
            return detail::set_texture_error(
                diagnostic, MaterialError::InvalidMipChain, texture.id, level);
        }
        result.levels[level] = MipLevel{
            width, height, static_cast<u32>(bytes)};
    }
    chain = result;
    return MaterialError::None;
}

}  // namespace stormline::graphics::material

#endif  // STORMLINE_GRAPHICS_MATERIAL_TEXTURE_MIP_HPP
