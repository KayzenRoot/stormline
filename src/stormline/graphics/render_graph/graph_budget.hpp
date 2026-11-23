#ifndef STORMLINE_GRAPHICS_RENDER_GRAPH_GRAPH_BUDGET_HPP
#define STORMLINE_GRAPHICS_RENDER_GRAPH_GRAPH_BUDGET_HPP

#include "stormline/graphics/render_graph/graph_transient.hpp"

namespace stormline::graphics::render_graph {

namespace detail {

[[nodiscard]] inline bool checked_add(u64 left, u64 right, u64& out) noexcept {
    if (right > 0xFFFFFFFFFFFFFFFFULL - left) {
        return false;
    }
    out = left + right;
    return true;
}

}  // namespace detail

[[nodiscard]] inline GraphError plan_budget(
    const GraphDefinition& graph, const AliasPlan& aliases,
    const GpuBudgetSnapshot& budget, BudgetPlan& plan,
    GraphDiagnostic& diagnostic) noexcept {
    plan = BudgetPlan{};
    const GraphError validation = validate_graph(graph, diagnostic);
    if (validation != GraphError::None) {
        return validation;
    }
    if (!budget.known || budget.total_bytes == 0 || budget.headroom_bytes == 0) {
        return detail::set_error(
            diagnostic, GraphError::BudgetUnknown, 0, 0, 0);
    }
    if (budget.headroom_bytes > budget.total_bytes) {
        return detail::set_error(
            diagnostic, GraphError::InvalidArgument, 0, 0, 0);
    }
    if (aliases.group_count > kMaxAliasGroups) {
        return detail::set_error(
            diagnostic, GraphError::InvalidArgument, 0, 0, 0);
    }

    u64 persistent = 0;
    for (u32 index = 0; index < graph.resource_count; ++index) {
        const ResourceDesc& resource = graph.resources[index];
        if (resource.kind == ResourceKind::Persistent
            || resource.kind == ResourceKind::History) {
            if (!detail::checked_add(persistent, resource.bytes, persistent)) {
                return detail::set_error(
                    diagnostic, GraphError::InvalidArgument, 0, resource.id, index);
            }
        }
    }
    u64 transient_peak = 0;
    for (u32 index = 0; index < aliases.group_count; ++index) {
        const AliasGroup& group = aliases.groups[index];
        if (group.bytes == 0 || group.resource_count == 0) {
            return detail::set_error(
                diagnostic, GraphError::InvalidArgument, 0, 0, index);
        }
        if (!detail::checked_add(transient_peak, group.bytes, transient_peak)) {
            return detail::set_error(
                diagnostic, GraphError::InvalidArgument, 0, 0, index);
        }
    }
    u64 required = 0;
    if (!detail::checked_add(persistent, transient_peak, required)) {
        return detail::set_error(
            diagnostic, GraphError::InvalidArgument, 0, 0, 0);
    }

    plan.persistent_bytes = persistent;
    plan.transient_peak_bytes = transient_peak;
    plan.alias_saved_bytes = aliases.alias_saved_bytes;
    plan.required_bytes = required;
    plan.within_budget = required <= budget.headroom_bytes;
    if (!plan.within_budget) {
        return detail::set_error(
            diagnostic, GraphError::BudgetExceeded, 0, 0, 0);
    }
    return GraphError::None;
}

}  // namespace stormline::graphics::render_graph

#endif  // STORMLINE_GRAPHICS_RENDER_GRAPH_GRAPH_BUDGET_HPP
