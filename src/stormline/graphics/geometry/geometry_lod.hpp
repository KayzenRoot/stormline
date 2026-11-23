#ifndef STORMLINE_GRAPHICS_GEOMETRY_GEOMETRY_LOD_HPP
#define STORMLINE_GRAPHICS_GEOMETRY_GEOMETRY_LOD_HPP

#include "stormline/graphics/geometry/geometry_instance.hpp"

#include <cmath>

namespace stormline::graphics::geometry {

namespace detail {

inline bool valid_lod_chain(const LodChain& chain) noexcept {
    if (chain.scene_generation == 0 || chain.mesh_id == 0
        || chain.level_count == 0 || chain.level_count > kMaxLodLevels) {
        return false;
    }
    if (chain.levels[0].geometric_error != 0.0f) {
        return false;
    }
    for (u32 index = 0; index < chain.level_count; ++index) {
        const LodLevel& level = chain.levels[index];
        if (!std::isfinite(level.geometric_error) || level.geometric_error < 0.0f
            || level.triangle_count == 0) {
            return false;
        }
        if (index > 0) {
            if (level.geometric_error < chain.levels[index - 1].geometric_error
                || level.triangle_count > chain.levels[index - 1].triangle_count) {
                return false;
            }
        }
    }
    return true;
}

inline u32 find_hlod_node(const HlodSet& set, u32 mesh_id) noexcept {
    for (u32 index = 0; index < set.count; ++index) {
        if (set.nodes[index].mesh_id == mesh_id) {
            return index;
        }
    }
    return kMaxMeshes;
}

inline bool hlod_ancestor(
    const HlodSet& set, u32 mesh_id, u32 root_mesh_id) noexcept {
    u32 current = mesh_id;
    for (u32 step = 0; step <= set.count; ++step) {
        if (current == root_mesh_id) {
            return true;
        }
        if (current == 0) {
            return false;
        }
        const u32 index = find_hlod_node(set, current);
        if (index == kMaxMeshes) {
            return false;
        }
        current = set.nodes[index].parent_mesh_id;
    }
    return false;
}

}  // namespace detail

[[nodiscard]] inline GeometryError validate_lod_chain(
    const LodChain& chain, GeometryDiagnostic& diagnostic) noexcept {
    diagnostic = GeometryDiagnostic{};
    if (!detail::valid_lod_chain(chain)) {
        return detail::set_error(
            diagnostic, GeometryError::InvalidLodChain, 0, chain.mesh_id, 0);
    }
    return GeometryError::None;
}

[[nodiscard]] inline GeometryError select_lod(
    const LodChain& chain, const SphereBounds& bounds,
    const LodRequest& request, LodSelection& selection,
    GeometryDiagnostic& diagnostic) noexcept {
    selection = LodSelection{};
    const GeometryError validation = validate_lod_chain(chain, diagnostic);
    if (validation != GeometryError::None) {
        return validation;
    }
    if (!std::isfinite(request.screen_scale) || request.screen_scale <= 0.0f
        || !std::isfinite(request.max_screen_error)
        || request.max_screen_error < 0.0f
        || request.previous_level >= chain.level_count
        || !detail::valid_bounds(bounds)) {
        return detail::set_error(
            diagnostic, GeometryError::InvalidArgument, 0, chain.mesh_id, 0);
    }

    selection.mesh_id = chain.mesh_id;
    if (!bounds.known) {
        selection.level = 0;
        selection.triangle_count = chain.levels[0].triangle_count;
        selection.projected_error = 0.0f;
        return GeometryError::None;
    }

    const f32 dx = bounds.center.x - request.camera.x;
    const f32 dy = bounds.center.y - request.camera.y;
    const f32 dz = bounds.center.z - request.camera.z;
    f32 distance = std::sqrt(dx * dx + dy * dy + dz * dz);
    if (distance < 1.0f) {
        distance = 1.0f;
    }
    u32 chosen = 0;
    for (u32 index = 1; index < chain.level_count; ++index) {
        const f32 projected =
            chain.levels[index].geometric_error / distance * request.screen_scale;
        if (projected <= request.max_screen_error) {
            chosen = index;
        }
    }
    if (request.previous_level > 0 && request.previous_level < chosen) {
        const f32 previous_projected = chain.levels[request.previous_level]
            .geometric_error / distance * request.screen_scale;
        if (previous_projected <= request.max_screen_error * 1.25f) {
            chosen = request.previous_level;
        }
    }
    selection.level = chosen;
    selection.triangle_count = chain.levels[chosen].triangle_count;
    selection.projected_error =
        chain.levels[chosen].geometric_error / distance * request.screen_scale;
    return GeometryError::None;
}

[[nodiscard]] inline GeometryError validate_hlod(
    const HlodSet& set, GeometryDiagnostic& diagnostic) noexcept {
    diagnostic = GeometryDiagnostic{};
    if (set.scene_generation == 0 || set.count == 0 || set.count > kMaxMeshes) {
        return detail::set_error(
            diagnostic, GeometryError::InvalidArgument, 0, 0, 0);
    }
    for (u32 index = 0; index < set.count; ++index) {
        const HlodNode& node = set.nodes[index];
        if (node.mesh_id == 0 || node.parent_mesh_id == node.mesh_id
            || !std::isfinite(node.geometric_error) || node.geometric_error < 0.0f
            || node.triangle_count == 0) {
            return detail::set_error(
                diagnostic, GeometryError::InvalidArgument, 0, node.mesh_id, index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (set.nodes[previous].mesh_id == node.mesh_id) {
                return detail::set_error(
                    diagnostic, GeometryError::DuplicateId, 0, node.mesh_id, index);
            }
        }
        if (node.parent_mesh_id != 0
            && detail::find_hlod_node(set, node.parent_mesh_id) == kMaxMeshes) {
            return detail::set_error(
                diagnostic, GeometryError::NotFound, 0, node.parent_mesh_id, index);
        }
        u32 current = node.mesh_id;
        for (u32 step = 0; step <= set.count; ++step) {
            if (current == 0) {
                break;
            }
            const u32 current_index = detail::find_hlod_node(set, current);
            if (current_index == kMaxMeshes) {
                return detail::set_error(
                    diagnostic, GeometryError::NotFound, 0, current, index);
            }
            current = set.nodes[current_index].parent_mesh_id;
            if (step == set.count) {
                return detail::set_error(
                    diagnostic, GeometryError::HierarchyCycle, 0, node.mesh_id,
                    index);
            }
        }
    }
    return GeometryError::None;
}

[[nodiscard]] inline GeometryError select_hlod(
    const HlodSet& set, u32 root_mesh_id, f32 max_error,
    HlodSelection& selection, GeometryDiagnostic& diagnostic) noexcept {
    selection = HlodSelection{};
    const GeometryError validation = validate_hlod(set, diagnostic);
    if (validation != GeometryError::None) {
        return validation;
    }
    if (detail::find_hlod_node(set, root_mesh_id) == kMaxMeshes
        || !std::isfinite(max_error) || max_error < 0.0f) {
        return detail::set_error(
            diagnostic, GeometryError::InvalidArgument, 0, root_mesh_id, 0);
    }
    bool found = false;
    for (u32 index = 0; index < set.count; ++index) {
        const HlodNode& node = set.nodes[index];
        if (!detail::hlod_ancestor(set, node.mesh_id, root_mesh_id)) {
            continue;
        }
        if (node.geometric_error > max_error) {
            continue;
        }
        if (!found || node.geometric_error > selection.geometric_error
            || (node.geometric_error == selection.geometric_error
                && node.mesh_id < selection.mesh_id)) {
            selection.mesh_id = node.mesh_id;
            selection.geometric_error = node.geometric_error;
            selection.proxy = node.proxy;
            found = true;
        }
    }
    return GeometryError::None;
}


}  // namespace stormline::graphics::geometry

#endif  // STORMLINE_GRAPHICS_GEOMETRY_GEOMETRY_LOD_HPP
