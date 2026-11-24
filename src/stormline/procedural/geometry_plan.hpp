#ifndef STORMLINE_PROCEDURAL_GEOMETRY_PLAN_HPP
#define STORMLINE_PROCEDURAL_GEOMETRY_PLAN_HPP

#include <array>

#include "stormline/procedural/procedural_types.hpp"

namespace stormline::procedural {

struct GeometryRecipeDesc {
    u32 recipe_id{0};
    u32 revision{0};
    PrimitiveKind primitive{PrimitiveKind::Box};
    u32 source_asset_id{0};
    f32 unit_scale{1.0f};
    u32 lod_count{1};
};

struct GeometrySetDesc {
    u32 graph_id{0};
    u32 revision{0};
    u32 recipe_count{0};
    std::array<GeometryRecipeDesc, kMaxGeometryRecipes> recipes{};
};

struct GeometryPlan {
    u32 recipe_count{0};
    u32 box_count{0};
    u32 plane_count{0};
    u32 sphere_count{0};
    u32 heightfield_count{0};
    f32 max_unit_scale{0.0f};
};

[[nodiscard]] inline ProcError plan_geometry(
    const GeometrySetDesc& geometry, GeometryPlan& plan,
    ProcDiagnostic& diagnostic) noexcept {
    plan = GeometryPlan{};
    diagnostic = ProcDiagnostic{};
    if (geometry.graph_id == 0 || geometry.revision == 0) {
        return detail::set_proc_error(
            diagnostic, ProcError::InvalidArgument, geometry.graph_id, 0);
    }
    if (geometry.recipe_count > kMaxGeometryRecipes) {
        return detail::set_proc_error(
            diagnostic, ProcError::CapacityFull, geometry.graph_id, 0);
    }
    for (u32 index = 0; index < geometry.recipe_count; ++index) {
        const GeometryRecipeDesc& recipe = geometry.recipes[index];
        if (recipe.recipe_id == 0 || recipe.revision == 0
            || recipe.source_asset_id == 0
            || !detail::valid_primitive(recipe.primitive)) {
            return detail::set_proc_error(
                diagnostic, ProcError::GeometryInvalid, geometry.graph_id,
                index);
        }
        if (!detail::finite(recipe.unit_scale)
            || !(recipe.unit_scale > 0.0f) || recipe.lod_count == 0
            || recipe.lod_count > 8) {
            return detail::set_proc_error(
                diagnostic, ProcError::OutOfRange, geometry.graph_id, index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (geometry.recipes[previous].recipe_id == recipe.recipe_id) {
                return detail::set_proc_error(
                    diagnostic, ProcError::DuplicateId, geometry.graph_id,
                    index);
            }
        }
    }
    plan.recipe_count = geometry.recipe_count;
    for (u32 index = 0; index < geometry.recipe_count; ++index) {
        const GeometryRecipeDesc& recipe = geometry.recipes[index];
        switch (recipe.primitive) {
            case PrimitiveKind::Box:
                ++plan.box_count;
                break;
            case PrimitiveKind::Plane:
                ++plan.plane_count;
                break;
            case PrimitiveKind::Sphere:
                ++plan.sphere_count;
                break;
            case PrimitiveKind::Heightfield:
                ++plan.heightfield_count;
                break;
        }
        if (recipe.unit_scale > plan.max_unit_scale) {
            plan.max_unit_scale = recipe.unit_scale;
        }
    }
    return ProcError::None;
}

}  // namespace stormline::procedural

#endif  // STORMLINE_PROCEDURAL_GEOMETRY_PLAN_HPP
