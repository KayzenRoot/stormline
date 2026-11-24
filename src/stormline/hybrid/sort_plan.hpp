#ifndef STORMLINE_HYBRID_SORT_PLAN_HPP
#define STORMLINE_HYBRID_SORT_PLAN_HPP

#include <array>

#include "stormline/hybrid/hybrid_types.hpp"

namespace stormline::hybrid {

struct HybridSortObject {
    u32 object_id{0};
    u32 revision{0};
    u32 layer_order{0};
    f32 depth_key{0.0f};
    u32 tie_breaker{0};
};

struct HybridSortDesc {
    u32 scene_id{0};
    u32 revision{0};
    u32 object_count{0};
    std::array<HybridSortObject, kMaxHybridObjects> objects{};
};

struct HybridSortPlan {
    u32 object_count{0};
    std::array<u32, kMaxHybridObjects> order{};
};

namespace detail {

inline bool sort_before(
    const HybridSortObject& left, const HybridSortObject& right) noexcept {
    if (left.layer_order != right.layer_order) {
        return left.layer_order < right.layer_order;
    }
    if (left.depth_key != right.depth_key) {
        return left.depth_key < right.depth_key;
    }
    return left.tie_breaker < right.tie_breaker;
}

}  // namespace detail

[[nodiscard]] inline HybridError plan_sort(
    const HybridSortDesc& sort, HybridSortPlan& plan,
    HybridDiagnostic& diagnostic) noexcept {
    plan = HybridSortPlan{};
    diagnostic = HybridDiagnostic{};
    if (sort.scene_id == 0 || sort.revision == 0) {
        return detail::set_hybrid_error(
            diagnostic, HybridError::InvalidArgument, sort.scene_id, 0);
    }
    if (sort.object_count == 0 || sort.object_count > kMaxHybridObjects) {
        return detail::set_hybrid_error(
            diagnostic, HybridError::SortInvalid, sort.scene_id, 0);
    }
    for (u32 index = 0; index < sort.object_count; ++index) {
        const HybridSortObject& object = sort.objects[index];
        if (object.object_id == 0 || object.revision == 0) {
            return detail::set_hybrid_error(
                diagnostic, HybridError::SortInvalid, sort.scene_id, index);
        }
        if (!detail::finite(object.depth_key)) {
            return detail::set_hybrid_error(
                diagnostic, HybridError::NonFiniteValue, sort.scene_id, index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (sort.objects[previous].object_id == object.object_id) {
                return detail::set_hybrid_error(
                    diagnostic, HybridError::DuplicateId, sort.scene_id, index);
            }
        }
    }
    std::array<HybridSortObject, kMaxHybridObjects> sorted = sort.objects;
    for (u32 index = 1; index < sort.object_count; ++index) {
        const HybridSortObject current = sorted[index];
        u32 position = index;
        while (position > 0
               && detail::sort_before(current, sorted[position - 1])) {
            sorted[position] = sorted[position - 1];
            --position;
        }
        sorted[position] = current;
    }
    plan.object_count = sort.object_count;
    for (u32 index = 0; index < sort.object_count; ++index) {
        plan.order[index] = sorted[index].object_id;
    }
    return HybridError::None;
}

}  // namespace stormline::hybrid

#endif  // STORMLINE_HYBRID_SORT_PLAN_HPP
