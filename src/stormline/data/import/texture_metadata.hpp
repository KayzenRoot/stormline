#ifndef STORMLINE_DATA_IMPORT_TEXTURE_METADATA_HPP
#define STORMLINE_DATA_IMPORT_TEXTURE_METADATA_HPP

#include "stormline/data/import/import_types.hpp"

namespace stormline::data::imports {

struct TextureMetadata {
    u32 width{0};
    u32 height{0};
    u32 mip_levels{0};
    u8 channels{0};
    bool srgb{false};
};

[[nodiscard]] inline ImportError validate_texture(
    const TextureMetadata& metadata, u32& warning_count) noexcept {
    warning_count = 0;
    if (metadata.width == 0 || metadata.width > kMaxTextureDimension
        || metadata.height == 0 || metadata.height > kMaxTextureDimension
        || metadata.channels == 0 || metadata.channels > 4
        || metadata.mip_levels > kMaxMipLevels) {
        return ImportError::InvalidTexture;
    }
    const u32 max_dimension =
        metadata.width > metadata.height ? metadata.width : metadata.height;
    u32 floor_log2 = 0;
    u32 value = max_dimension;
    while (value > 1) {
        value >>= 1;
        ++floor_log2;
    }
    const u32 max_mips = floor_log2 + 1;
    if (metadata.mip_levels > max_mips) {
        return ImportError::InvalidTexture;
    }
    const bool width_pot = (metadata.width & (metadata.width - 1)) == 0;
    const bool height_pot = (metadata.height & (metadata.height - 1)) == 0;
    if (!width_pot || !height_pot) {
        warning_count = 1;
    }
    return ImportError::None;
}

}  // namespace stormline::data::imports

#endif  // STORMLINE_DATA_IMPORT_TEXTURE_METADATA_HPP
