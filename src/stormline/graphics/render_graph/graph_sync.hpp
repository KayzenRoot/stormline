#ifndef STORMLINE_GRAPHICS_RENDER_GRAPH_GRAPH_SYNC_HPP
#define STORMLINE_GRAPHICS_RENDER_GRAPH_GRAPH_SYNC_HPP

#include "stormline/graphics/render_graph/graph_dependency.hpp"

namespace stormline::graphics::render_graph {

namespace detail {

[[nodiscard]] inline GraphAccess mapped_access(Access access) noexcept {
    return access == Access::Read ? GraphAccess::Read : GraphAccess::Write;
}

[[nodiscard]] inline bool ordered_pass_present(
    const DependencyPlan& dependencies, u32 pass_id) noexcept {
    for (u32 index = 0; index < dependencies.order_count; ++index) {
        if (dependencies.order[index] == pass_id) {
            return true;
        }
    }
    return false;
}

}  // namespace detail

[[nodiscard]] inline GraphError plan_sync(
    const GraphDefinition& graph, const DependencyPlan& dependencies,
    SyncPlan& plan, GraphDiagnostic& diagnostic) noexcept {
    plan = SyncPlan{};
    const GraphError validation = validate_graph(graph, diagnostic);
    if (validation != GraphError::None) {
        return validation;
    }
    if (dependencies.order_count != graph.pass_count) {
        return detail::set_error(
            diagnostic, GraphError::InvalidArgument, 0, 0, 0);
    }
    for (u32 index = 0; index < dependencies.order_count; ++index) {
        if (detail::find_pass(graph, dependencies.order[index]) == kMaxPasses) {
            return detail::set_error(
                diagnostic, GraphError::InvalidArgument,
                dependencies.order[index], 0, index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (dependencies.order[previous] == dependencies.order[index]) {
                return detail::set_error(
                    diagnostic, GraphError::InvalidArgument,
                    dependencies.order[index], 0, index);
            }
        }
    }

    std::array<GraphAccess, kMaxResources> access{};
    std::array<rhi::QueueRole, kMaxResources> queue{};
    std::array<bool, kMaxResources> initialized{};
    for (u32 order_index = 0; order_index < dependencies.order_count;
         ++order_index) {
        const u32 pass_id = dependencies.order[order_index];
        const u32 pass_index = detail::find_pass(graph, pass_id);
        const PassDesc& pass = graph.passes[pass_index];
        for (u32 use_index = 0; use_index < graph.use_count; ++use_index) {
            const UseDesc& use = graph.uses[use_index];
            if (use.pass_id != pass_id) {
                continue;
            }
            const u32 resource_index = detail::find_resource(graph, use.resource_id);
            if (resource_index == kMaxResources) {
                return detail::set_error(
                    diagnostic, GraphError::InvalidArgument, pass_id,
                    use.resource_id, use_index);
            }
            const GraphAccess next = detail::mapped_access(use.access);
            const GraphAccess previous = access[resource_index];
            const rhi::QueueRole previous_queue = initialized[resource_index]
                ? queue[resource_index] : pass.queue;
            const bool transition = !initialized[resource_index]
                || previous != next || previous_queue != pass.queue;
            if (transition) {
                if (plan.transition_count >= kMaxTransitions) {
                    return detail::set_error(
                        diagnostic, GraphError::CapacityFull, pass_id,
                        use.resource_id, use_index);
                }
                plan.transitions[plan.transition_count] = SyncTransition{
                    use.resource_id, previous, next, previous_queue,
                    pass.queue, pass_id};
                ++plan.transition_count;
            }
            access[resource_index] = next;
            queue[resource_index] = pass.queue;
            initialized[resource_index] = true;
        }
    }
    return GraphError::None;
}

}  // namespace stormline::graphics::render_graph

#endif  // STORMLINE_GRAPHICS_RENDER_GRAPH_GRAPH_SYNC_HPP
