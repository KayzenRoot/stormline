#ifndef STORMLINE_HYBRID_LAYER_PLAN_HPP
#define STORMLINE_HYBRID_LAYER_PLAN_HPP

#include <array>

#include "stormline/hybrid/hybrid_types.hpp"

namespace stormline::hybrid {

struct HybridObjectRef {
    u32 object_id{0};
    u32 revision{0};
    ObjectKind kind{ObjectKind::Sprite};
    f32 depth_key{0.0f};
};

struct HybridLayerDesc {
    u32 layer_id{0};
    u32 revision{0};
    CompositionMode mode{CompositionMode::OrderedCanvasOverlay};
    u32 author_order{0};
    bool depth_test{false};
    bool depth_write{false};
    AlphaPolicy alpha{AlphaPolicy::Opaque};
    u32 object_count{0};
    std::array<HybridObjectRef, kMaxHybridObjects> objects{};
};

struct HybridLayerSetDesc {
    u32 scene_id{0};
    u32 revision{0};
    u32 layer_count{0};
    std::array<HybridLayerDesc, kMaxHybridLayers> layers{};
};

struct HybridLayerPlan {
    u32 layer_count{0};
    u32 object_count{0};
    u32 depth_write_count{0};
    u32 canvas_count{0};
};

[[nodiscard]] inline HybridError plan_layers(
    const HybridLayerSetDesc& layers, HybridLayerPlan& plan,
    HybridDiagnostic& diagnostic) noexcept {
    plan = HybridLayerPlan{};
    diagnostic = HybridDiagnostic{};
    if (layers.scene_id == 0 || layers.revision == 0) {
        return detail::set_hybrid_error(
            diagnostic, HybridError::InvalidArgument, layers.scene_id, 0);
    }
    if (layers.layer_count == 0 || layers.layer_count > kMaxHybridLayers) {
        return detail::set_hybrid_error(
            diagnostic, HybridError::LayerInvalid, layers.scene_id, 0);
    }
    HybridLayerPlan computed{};
    computed.layer_count = layers.layer_count;
    for (u32 layer_index = 0; layer_index < layers.layer_count; ++layer_index) {
        const HybridLayerDesc& layer = layers.layers[layer_index];
        if (layer.layer_id == 0 || layer.revision == 0
            || !detail::valid_mode(layer.mode)
            || !detail::valid_alpha(layer.alpha)) {
            return detail::set_hybrid_error(
                diagnostic, HybridError::LayerInvalid, layers.scene_id,
                layer_index);
        }
        for (u32 previous = 0; previous < layer_index; ++previous) {
            if (layers.layers[previous].author_order == layer.author_order) {
                return detail::set_hybrid_error(
                    diagnostic, HybridError::DuplicateId, layers.scene_id,
                    layer_index);
            }
        }
        if (layer.object_count > kMaxHybridObjects) {
            return detail::set_hybrid_error(
                diagnostic, HybridError::LayerInvalid, layers.scene_id,
                layer_index);
        }
        if (layer.mode != CompositionMode::SharedDepthWorld
            && (layer.depth_test || layer.depth_write)) {
            return detail::set_hybrid_error(
                diagnostic, HybridError::LayerInvalid, layers.scene_id,
                layer_index);
        }
        if (layer.depth_write && !layer.depth_test) {
            return detail::set_hybrid_error(
                diagnostic, HybridError::LayerInvalid, layers.scene_id,
                layer_index);
        }
        if (layer.mode == CompositionMode::SharedDepthWorld
            && layer.alpha == AlphaPolicy::Blended && layer.depth_write) {
            return detail::set_hybrid_error(
                diagnostic, HybridError::LayerInvalid, layers.scene_id,
                layer_index);
        }
        if (layer.depth_write) {
            ++computed.depth_write_count;
        }
        if (layer.mode == CompositionMode::OrderedCanvasOverlay) {
            ++computed.canvas_count;
        }
        for (u32 object_index = 0; object_index < layer.object_count;
             ++object_index) {
            const HybridObjectRef& object = layer.objects[object_index];
            if (object.object_id == 0 || object.revision == 0
                || !detail::valid_object_kind(object.kind)) {
                return detail::set_hybrid_error(
                    diagnostic, HybridError::LayerInvalid, layers.scene_id,
                    object_index);
            }
            if (!detail::finite(object.depth_key)) {
                return detail::set_hybrid_error(
                    diagnostic, HybridError::NonFiniteValue, layers.scene_id,
                    object_index);
            }
            for (u32 prior_layer = 0; prior_layer <= layer_index; ++prior_layer) {
                const u32 limit = prior_layer == layer_index
                    ? object_index
                    : layers.layers[prior_layer].object_count;
                for (u32 prior_object = 0; prior_object < limit;
                     ++prior_object) {
                    if (layers.layers[prior_layer].objects[prior_object].object_id
                        == object.object_id) {
                        return detail::set_hybrid_error(
                            diagnostic, HybridError::DuplicateId,
                            layers.scene_id, object_index);
                    }
                }
            }
            ++computed.object_count;
        }
    }
    plan = computed;
    return HybridError::None;
}

}  // namespace stormline::hybrid

#endif  // STORMLINE_HYBRID_LAYER_PLAN_HPP
