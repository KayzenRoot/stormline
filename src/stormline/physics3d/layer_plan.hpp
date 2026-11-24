#ifndef STORMLINE_PHYSICS3D_LAYER_PLAN_HPP
#define STORMLINE_PHYSICS3D_LAYER_PLAN_HPP

#include <array>

#include "stormline/physics3d/physics3d_types.hpp"

namespace stormline::physics3d {

struct LayerDesc {
    u32 layer_id{0};
    u32 revision{0};
    u32 layer_bits{0};
    u32 mask_bits{0};
    u32 group_index{0};
};

struct LayerSetDesc {
    u32 world_id{0};
    u32 revision{0};
    u32 layer_count{0};
    std::array<LayerDesc, kMaxLayers> layers{};
};

struct LayerPlan {
    u32 layer_count{0};
    u32 group_count{0};
    u32 compatible_pair_count{0};
};

[[nodiscard]] inline bool layers_compatible(
    const LayerDesc& a, const LayerDesc& b) noexcept {
    if (a.group_index != 0 || b.group_index != 0) {
        return a.group_index != 0 && a.group_index == b.group_index;
    }
    return (a.layer_bits & b.mask_bits) != 0
        && (b.layer_bits & a.mask_bits) != 0;
}

[[nodiscard]] inline Physics3DError plan_layers(
    const LayerSetDesc& layers, LayerPlan& plan,
    Physics3DDiagnostic& diagnostic) noexcept {
    plan = LayerPlan{};
    diagnostic = Physics3DDiagnostic{};
    if (layers.world_id == 0 || layers.revision == 0) {
        return detail::set_physics3d_error(
            diagnostic, Physics3DError::InvalidArgument, layers.world_id, 0);
    }
    if (layers.layer_count > kMaxLayers) {
        return detail::set_physics3d_error(
            diagnostic, Physics3DError::CapacityFull, layers.world_id, 0);
    }
    for (u32 index = 0; index < layers.layer_count; ++index) {
        const LayerDesc& layer = layers.layers[index];
        if (layer.layer_id == 0 || layer.revision == 0
            || layer.layer_bits == 0 || layer.mask_bits == 0) {
            return detail::set_physics3d_error(
                diagnostic, Physics3DError::LayerInvalid, layers.world_id,
                index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (layers.layers[previous].layer_id == layer.layer_id) {
                return detail::set_physics3d_error(
                    diagnostic, Physics3DError::DuplicateId, layers.world_id,
                    index);
            }
        }
    }
    plan.layer_count = layers.layer_count;
    for (u32 index = 0; index < layers.layer_count; ++index) {
        const LayerDesc& layer = layers.layers[index];
        if (layer.group_index == 0) {
            continue;
        }
        bool seen = false;
        for (u32 previous = 0; previous < index; ++previous) {
            if (layers.layers[previous].group_index == layer.group_index) {
                seen = true;
                break;
            }
        }
        if (!seen) {
            ++plan.group_count;
        }
    }
    for (u32 first = 0; first < layers.layer_count; ++first) {
        for (u32 second = first + 1; second < layers.layer_count; ++second) {
            if (layers_compatible(layers.layers[first],
                                  layers.layers[second])) {
                ++plan.compatible_pair_count;
            }
        }
    }
    return Physics3DError::None;
}

}  // namespace stormline::physics3d

#endif  // STORMLINE_PHYSICS3D_LAYER_PLAN_HPP
