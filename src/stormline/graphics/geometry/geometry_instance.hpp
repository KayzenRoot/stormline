#ifndef STORMLINE_GRAPHICS_GEOMETRY_GEOMETRY_INSTANCE_HPP
#define STORMLINE_GRAPHICS_GEOMETRY_GEOMETRY_INSTANCE_HPP

#include "stormline/graphics/geometry/geometry_types.hpp"

#include <algorithm>
#include <cmath>

namespace stormline::graphics::geometry {

namespace detail {

inline GeometryError set_error(
    GeometryDiagnostic& diagnostic, GeometryError code, u32 instance_id,
    u32 mesh_id, u32 index) noexcept {
    diagnostic = GeometryDiagnostic{code, instance_id, mesh_id, index};
    return code;
}

inline bool valid_bounds(const SphereBounds& bounds) noexcept {
    if (!std::isfinite(bounds.radius) || bounds.radius < 0.0f) {
        return false;
    }
    if (!bounds.known) {
        return true;
    }
    return std::isfinite(bounds.center.x) && std::isfinite(bounds.center.y)
        && std::isfinite(bounds.center.z);
}

inline bool valid_instance(const InstanceDesc& instance) noexcept {
    return instance.id != 0 && instance.mesh_id != 0
        && instance.material_id != 0 && valid_bounds(instance.bounds);
}

inline u32 find_instance(const InstanceSet& set, u32 id) noexcept {
    for (u32 index = 0; index < set.count; ++index) {
        if (set.instances[index].id == id) {
            return index;
        }
    }
    return kMaxInstances;
}

}  // namespace detail

[[nodiscard]] inline const char* geometry_error_name(
    GeometryError error) noexcept {
    switch (error) {
        case GeometryError::None: return "None";
        case GeometryError::InvalidArgument: return "InvalidArgument";
        case GeometryError::DuplicateId: return "DuplicateId";
        case GeometryError::NotFound: return "NotFound";
        case GeometryError::CapacityFull: return "CapacityFull";
        case GeometryError::InvalidBounds: return "InvalidBounds";
        case GeometryError::UnknownBounds: return "UnknownBounds";
        case GeometryError::InvalidCamera: return "InvalidCamera";
        case GeometryError::GenerationMismatch: return "GenerationMismatch";
        case GeometryError::HierarchyCycle: return "HierarchyCycle";
        case GeometryError::InvalidLodChain: return "InvalidLodChain";
        case GeometryError::UnverifiedChunk: return "UnverifiedChunk";
        case GeometryError::StreamBudgetExceeded: return "StreamBudgetExceeded";
        case GeometryError::GeometryBudgetExceeded: return "GeometryBudgetExceeded";
    }
    return "Unknown";
}

[[nodiscard]] inline GeometryError add_instance(
    InstanceSet& set, const InstanceDesc& instance) noexcept {
    if (set.count >= kMaxInstances) {
        return GeometryError::CapacityFull;
    }
    if (instance.id == 0 || instance.mesh_id == 0 || instance.material_id == 0) {
        return GeometryError::InvalidArgument;
    }
    if (!detail::valid_bounds(instance.bounds)) {
        return GeometryError::InvalidBounds;
    }
    if (detail::find_instance(set, instance.id) != kMaxInstances) {
        return GeometryError::DuplicateId;
    }
    set.instances[set.count] = instance;
    ++set.count;
    return GeometryError::None;
}

[[nodiscard]] inline GeometryError validate_instances(
    const InstanceSet& set, GeometryDiagnostic& diagnostic) noexcept {
    diagnostic = GeometryDiagnostic{};
    if (set.scene_generation == 0 || set.count > kMaxInstances) {
        return detail::set_error(
            diagnostic, GeometryError::InvalidArgument, 0, 0, 0);
    }
    for (u32 index = 0; index < set.count; ++index) {
        const InstanceDesc& instance = set.instances[index];
        if (instance.id == 0 || instance.mesh_id == 0 || instance.material_id == 0) {
            return detail::set_error(
                diagnostic, GeometryError::InvalidArgument, instance.id,
                instance.mesh_id, index);
        }
        if (!detail::valid_bounds(instance.bounds)) {
            return detail::set_error(
                diagnostic, GeometryError::InvalidBounds, instance.id,
                instance.mesh_id, index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (set.instances[previous].id == instance.id) {
                return detail::set_error(
                    diagnostic, GeometryError::DuplicateId, instance.id,
                    instance.mesh_id, index);
            }
        }
    }
    return GeometryError::None;
}

[[nodiscard]] inline GeometryError plan_batches(
    const InstanceSet& set, BatchPlan& plan,
    GeometryDiagnostic& diagnostic) noexcept {
    plan = BatchPlan{};
    const GeometryError validation = validate_instances(set, diagnostic);
    if (validation != GeometryError::None) {
        return validation;
    }
    for (u32 index = 0; index < set.count; ++index) {
        const InstanceDesc& instance = set.instances[index];
        u32 batch_index = kMaxBatches;
        for (u32 candidate = 0; candidate < plan.count; ++candidate) {
            if (plan.batches[candidate].mesh_id == instance.mesh_id
                && plan.batches[candidate].material_id == instance.material_id) {
                batch_index = candidate;
                break;
            }
        }
        if (batch_index == kMaxBatches) {
            if (plan.count >= kMaxBatches) {
                return detail::set_error(
                    diagnostic, GeometryError::CapacityFull, instance.id,
                    instance.mesh_id, index);
            }
            batch_index = plan.count;
            plan.batches[batch_index] = InstanceBatch{};
            plan.batches[batch_index].mesh_id = instance.mesh_id;
            plan.batches[batch_index].material_id = instance.material_id;
            ++plan.count;
        }
        InstanceBatch& batch = plan.batches[batch_index];
        if (batch.count >= kMaxInstances) {
            return detail::set_error(
                diagnostic, GeometryError::CapacityFull, instance.id,
                instance.mesh_id, index);
        }
        batch.instance_indices[batch.count] = index;
        ++batch.count;
    }
    std::sort(plan.batches.begin(), plan.batches.begin() + plan.count,
              [](const InstanceBatch& left, const InstanceBatch& right) {
                  if (left.mesh_id != right.mesh_id) {
                      return left.mesh_id < right.mesh_id;
                  }
                  return left.material_id < right.material_id;
              });
    return GeometryError::None;
}

}  // namespace stormline::graphics::geometry

#endif  // STORMLINE_GRAPHICS_GEOMETRY_GEOMETRY_INSTANCE_HPP
