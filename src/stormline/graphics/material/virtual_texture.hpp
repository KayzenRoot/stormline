#ifndef STORMLINE_GRAPHICS_MATERIAL_VIRTUAL_TEXTURE_HPP
#define STORMLINE_GRAPHICS_MATERIAL_VIRTUAL_TEXTURE_HPP

#include "stormline/graphics/material/material_types.hpp"

#include <algorithm>
#include <cstdint>
#include <limits>

namespace stormline::graphics::material {

struct TextureDesc {
    u32 id{0};
    u32 width{0};
    u32 height{0};
    u16 levels{0};
    TextureFormat format{TextureFormat::Rgba8Unorm};
    ColorSpace color_space{ColorSpace::Linear};
    TextureUsage usage{TextureUsage::BaseColor};
};

struct TextureSet {
    u32 count{0};
    std::array<TextureDesc, kMaxTextures> textures{};
};

struct VirtualTexture {
    u32 texture_id{0};
    u32 page_size{0};
    u32 page_count{0};
};

struct ResidentPages {
    u32 count{0};
    std::array<u32, kMaxPages> page_ids{};
};

struct RequestedPages {
    u32 count{0};
    std::array<u32, kMaxPages> page_ids{};
};

struct PagePlan {
    u32 count{0};
    std::array<u32, kMaxPages> page_ids{};
    u32 pages_bytes{0};
    bool truncated{false};
};

namespace detail {

inline MaterialError set_texture_error(
    MaterialDiagnostic& diagnostic, MaterialError code, u32 texture_id,
    u32 index) noexcept {
    diagnostic = MaterialDiagnostic{code, 0, texture_id, index};
    return code;
}

inline bool valid_texture_format(TextureFormat format) noexcept {
    switch (format) {
        case TextureFormat::Rgba8Unorm:
        case TextureFormat::Rgba8Srgb:
        case TextureFormat::Rgba16Float:
        case TextureFormat::Depth32Float:
            return true;
    }
    return false;
}

inline bool valid_texture_usage(TextureUsage usage) noexcept {
    switch (usage) {
        case TextureUsage::BaseColor:
        case TextureUsage::Normal:
        case TextureUsage::Orm:
        case TextureUsage::Emissive:
        case TextureUsage::Occlusion:
        case TextureUsage::Height:
            return true;
    }
    return false;
}

inline bool valid_color_space(ColorSpace color_space) noexcept {
    switch (color_space) {
        case ColorSpace::Srgb:
        case ColorSpace::Linear:
            return true;
    }
    return false;
}

inline u16 expected_levels(u32 width, u32 height) noexcept {
    u32 dimension = std::max(width, height);
    u16 levels = 1;
    while (dimension > 1 && levels < kMaxMips) {
        dimension >>= 1;
        ++levels;
    }
    return levels;
}

inline MaterialError validate_texture_desc(
    const TextureDesc& texture) noexcept {
    if (texture.id == 0 || texture.width == 0 || texture.height == 0
        || texture.width > 16384 || texture.height > 16384) {
        return MaterialError::InvalidArgument;
    }
    if (texture.levels == 0 || texture.levels > kMaxMips
        || texture.levels != expected_levels(texture.width, texture.height)) {
        return MaterialError::InvalidArgument;
    }
    if (!valid_texture_format(texture.format)
        || !valid_texture_usage(texture.usage)
        || !valid_color_space(texture.color_space)) {
        return MaterialError::InvalidArgument;
    }
    if (texture.usage == TextureUsage::BaseColor
        && texture.color_space != ColorSpace::Srgb) {
        return MaterialError::InvalidArgument;
    }
    if ((texture.usage == TextureUsage::Normal
         || texture.usage == TextureUsage::Orm
         || texture.usage == TextureUsage::Height
         || texture.usage == TextureUsage::Occlusion)
        && texture.color_space != ColorSpace::Linear) {
        return MaterialError::InvalidArgument;
    }
    if (texture.format == TextureFormat::Depth32Float) {
        if (texture.color_space != ColorSpace::Linear
            || texture.usage == TextureUsage::BaseColor
            || texture.usage == TextureUsage::Emissive) {
            return MaterialError::InvalidArgument;
        }
    }
    return MaterialError::None;
}

inline u32 find_texture(const TextureSet& set, u32 id) noexcept {
    for (u32 index = 0; index < set.count; ++index) {
        if (set.textures[index].id == id) {
            return index;
        }
    }
    return kMaxTextures;
}

inline bool valid_page_ids(
    const std::array<u32, kMaxPages>& ids, u32 count,
    u32 page_count) noexcept {
    for (u32 index = 0; index < count; ++index) {
        if (ids[index] == 0 || ids[index] > page_count) {
            return false;
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (ids[previous] == ids[index]) {
                return false;
            }
        }
    }
    return true;
}

inline bool resident_contains(
    const ResidentPages& resident, u32 page_id) noexcept {
    for (u32 index = 0; index < resident.count; ++index) {
        if (resident.page_ids[index] == page_id) {
            return true;
        }
    }
    return false;
}

}  // namespace detail

[[nodiscard]] inline MaterialError add_texture(
    TextureSet& set, const TextureDesc& texture) noexcept {
    if (set.count >= kMaxTextures) {
        return MaterialError::CapacityFull;
    }
    const MaterialError validation = detail::validate_texture_desc(texture);
    if (validation != MaterialError::None) {
        return validation;
    }
    if (detail::find_texture(set, texture.id) != kMaxTextures) {
        return MaterialError::DuplicateId;
    }
    set.textures[set.count] = texture;
    ++set.count;
    return MaterialError::None;
}

[[nodiscard]] inline MaterialError validate_textures(
    const TextureSet& set, MaterialDiagnostic& diagnostic) noexcept {
    diagnostic = MaterialDiagnostic{};
    if (set.count > kMaxTextures) {
        return detail::set_texture_error(
            diagnostic, MaterialError::InvalidArgument, 0, 0);
    }
    for (u32 index = 0; index < set.count; ++index) {
        const TextureDesc& texture = set.textures[index];
        const MaterialError validation = detail::validate_texture_desc(texture);
        if (validation != MaterialError::None) {
            return detail::set_texture_error(
                diagnostic, validation, texture.id, index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (set.textures[previous].id == texture.id) {
                return detail::set_texture_error(
                    diagnostic, MaterialError::DuplicateId, texture.id, index);
            }
        }
    }
    return MaterialError::None;
}

[[nodiscard]] inline MaterialError plan_pages(
    const VirtualTexture& texture, const RequestedPages& requested,
    const ResidentPages& resident, u32 budget_pages, PagePlan& plan,
    MaterialDiagnostic& diagnostic) noexcept {
    plan = PagePlan{};
    diagnostic = MaterialDiagnostic{};
    if (texture.texture_id == 0 || texture.page_size == 0
        || texture.page_count == 0) {
        return detail::set_texture_error(
            diagnostic, MaterialError::InvalidArgument, texture.texture_id, 0);
    }
    const std::uint64_t total_bytes =
        static_cast<std::uint64_t>(texture.page_size) * texture.page_count;
    if (total_bytes > std::numeric_limits<u32>::max()) {
        return detail::set_texture_error(
            diagnostic, MaterialError::InvalidArgument, texture.texture_id, 0);
    }
    if (requested.count > kMaxPages || resident.count > kMaxPages) {
        return detail::set_texture_error(
            diagnostic, MaterialError::InvalidArgument, texture.texture_id, 0);
    }
    if (!detail::valid_page_ids(
            requested.page_ids, requested.count, texture.page_count)) {
        return detail::set_texture_error(
            diagnostic, MaterialError::InvalidArgument, texture.texture_id, 0);
    }
    if (!detail::valid_page_ids(
            resident.page_ids, resident.count, texture.page_count)) {
        return detail::set_texture_error(
            diagnostic, MaterialError::InvalidArgument, texture.texture_id, 0);
    }
    const u32 capacity = std::min(budget_pages, kMaxPages);
    for (u32 index = 0; index < requested.count; ++index) {
        const u32 page_id = requested.page_ids[index];
        if (detail::resident_contains(resident, page_id)) {
            continue;
        }
        if (plan.count >= capacity) {
            plan.truncated = true;
            continue;
        }
        plan.page_ids[plan.count] = page_id;
        ++plan.count;
    }
    const std::uint64_t admitted_bytes =
        static_cast<std::uint64_t>(plan.count) * texture.page_size;
    plan.pages_bytes = static_cast<u32>(admitted_bytes);
    return MaterialError::None;
}

}  // namespace stormline::graphics::material

#endif  // STORMLINE_GRAPHICS_MATERIAL_VIRTUAL_TEXTURE_HPP
