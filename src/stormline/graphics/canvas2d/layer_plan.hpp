#ifndef STORMLINE_GRAPHICS_CANVAS2D_LAYER_PLAN_HPP
#define STORMLINE_GRAPHICS_CANVAS2D_LAYER_PLAN_HPP

#include "stormline/graphics/canvas2d/canvas_types.hpp"

namespace stormline::graphics::canvas2d {

struct CanvasLayerDesc {
    u32 layer_id{0};
    u32 revision{0};
    u32 order{0};
    f32 opacity{1.0f};
    BlendMode blend{BlendMode::Blend};
    bool visible{true};
    u32 clip_depth{0};
};

struct CanvasLayerSet {
    u32 count{0};
    std::array<CanvasLayerDesc, kMaxLayers> layers{};
};

struct LayerPlan {
    u32 count{0};
    std::array<u32, kMaxLayers> order{};
};

[[nodiscard]] inline CanvasError plan_layers(
    const CanvasLayerSet& layers, LayerPlan& plan,
    CanvasDiagnostic& diagnostic) noexcept {
    plan = LayerPlan{};
    diagnostic = CanvasDiagnostic{};
    if (layers.count > kMaxLayers) {
        return detail::set_canvas_error(
            diagnostic, CanvasError::CapacityFull, 0, 0);
    }
    for (u32 index = 0; index < layers.count; ++index) {
        const CanvasLayerDesc& layer = layers.layers[index];
        if (layer.layer_id == 0 || layer.revision == 0) {
            return detail::set_canvas_error(
                diagnostic, CanvasError::InvalidArgument, layer.layer_id,
                index);
        }
        if (!detail::valid_blend(layer.blend)) {
            return detail::set_canvas_error(
                diagnostic, CanvasError::InvalidArgument, layer.layer_id,
                index);
        }
        if (!detail::finite(layer.opacity)) {
            return detail::set_canvas_error(
                diagnostic, CanvasError::NonFiniteValue, layer.layer_id,
                index);
        }
        if (layer.opacity < 0.0f || layer.opacity > 1.0f
            || layer.clip_depth > 8) {
            return detail::set_canvas_error(
                diagnostic, CanvasError::OutOfRange, layer.layer_id, index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (layers.layers[previous].layer_id == layer.layer_id) {
                return detail::set_canvas_error(
                    diagnostic, CanvasError::DuplicateId, layer.layer_id,
                    index);
            }
            if (layers.layers[previous].order == layer.order) {
                return detail::set_canvas_error(
                    diagnostic, CanvasError::LayerOrderInvalid, layer.layer_id,
                    index);
            }
        }
    }
    std::array<u32, kMaxLayers> ids{};
    std::array<u32, kMaxLayers> orders{};
    for (u32 index = 0; index < layers.count; ++index) {
        ids[index] = layers.layers[index].layer_id;
        orders[index] = layers.layers[index].order;
    }
    for (u32 index = 0; index < layers.count; ++index) {
        u32 smallest = index;
        for (u32 candidate = index + 1; candidate < layers.count; ++candidate) {
            if (orders[candidate] < orders[smallest]) {
                smallest = candidate;
            }
        }
        if (smallest != index) {
            const u32 id = ids[index];
            ids[index] = ids[smallest];
            ids[smallest] = id;
            const u32 order = orders[index];
            orders[index] = orders[smallest];
            orders[smallest] = order;
        }
    }
    for (u32 index = 0; index < layers.count; ++index) {
        plan.order[index] = ids[index];
    }
    plan.count = layers.count;
    return CanvasError::None;
}

}  // namespace stormline::graphics::canvas2d

#endif  // STORMLINE_GRAPHICS_CANVAS2D_LAYER_PLAN_HPP
