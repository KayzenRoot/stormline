#ifndef STORMLINE_GRAPHICS_CANVAS2D_ATLAS_PLAN_HPP
#define STORMLINE_GRAPHICS_CANVAS2D_ATLAS_PLAN_HPP

#include "stormline/graphics/canvas2d/canvas_types.hpp"

namespace stormline::graphics::canvas2d {

struct AtlasRegion {
    u32 region_id{0};
    u32 revision{0};
    u32 x{0};
    u32 y{0};
    u32 width{0};
    u32 height{0};
};

struct AtlasDesc {
    u32 atlas_id{0};
    u32 revision{0};
    u32 width{0};
    u32 height{0};
    u32 gutter{0};
    u32 mip_count{0};
    u32 region_count{0};
    std::array<AtlasRegion, kMaxAtlasRegions> regions{};
};

struct AtlasPlan {
    u32 atlas_id{0};
    u32 region_count{0};
    u32 mip_count{0};
};

[[nodiscard]] inline CanvasError plan_atlas(
    const AtlasDesc& atlas, AtlasPlan& plan,
    CanvasDiagnostic& diagnostic) noexcept {
    plan = AtlasPlan{};
    diagnostic = CanvasDiagnostic{};
    if (atlas.atlas_id == 0 || atlas.revision == 0) {
        return detail::set_canvas_error(
            diagnostic, CanvasError::InvalidArgument, atlas.atlas_id, 0);
    }
    if (atlas.width == 0 || atlas.height == 0) {
        return detail::set_canvas_error(
            diagnostic, CanvasError::AtlasInvalid, atlas.atlas_id, 0);
    }
    if (atlas.mip_count == 0 || atlas.mip_count > 16) {
        return detail::set_canvas_error(
            diagnostic, CanvasError::AtlasInvalid, atlas.atlas_id, 0);
    }
    if (atlas.region_count > kMaxAtlasRegions) {
        return detail::set_canvas_error(
            diagnostic, CanvasError::CapacityFull, atlas.atlas_id, 0);
    }
    for (u32 index = 0; index < atlas.region_count; ++index) {
        const AtlasRegion& region = atlas.regions[index];
        if (region.region_id == 0 || region.revision == 0) {
            return detail::set_canvas_error(
                diagnostic, CanvasError::InvalidArgument, atlas.atlas_id,
                index);
        }
        if (region.width == 0 || region.height == 0
            || static_cast<u64>(region.x) + region.width > atlas.width
            || static_cast<u64>(region.y) + region.height > atlas.height) {
            return detail::set_canvas_error(
                diagnostic, CanvasError::AtlasInvalid, atlas.atlas_id, index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (atlas.regions[previous].region_id == region.region_id) {
                return detail::set_canvas_error(
                    diagnostic, CanvasError::DuplicateId, atlas.atlas_id,
                    index);
            }
        }
    }
    plan.atlas_id = atlas.atlas_id;
    plan.region_count = atlas.region_count;
    plan.mip_count = atlas.mip_count;
    return CanvasError::None;
}

}  // namespace stormline::graphics::canvas2d

#endif  // STORMLINE_GRAPHICS_CANVAS2D_ATLAS_PLAN_HPP
