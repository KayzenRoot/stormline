#ifndef STORMLINE_GRAPHICS_RENDER_GRAPH_GRAPH_DEPENDENCY_HPP
#define STORMLINE_GRAPHICS_RENDER_GRAPH_GRAPH_DEPENDENCY_HPP

#include "stormline/graphics/render_graph/graph_definition.hpp"

#include <algorithm>

namespace stormline::graphics::render_graph {

namespace detail {

[[nodiscard]] inline bool is_writer(Access access) noexcept {
    return access == Access::Write || access == Access::ReadWrite;
}

[[nodiscard]] inline bool is_reader(Access access) noexcept {
    return access == Access::Read || access == Access::ReadWrite;
}

[[nodiscard]] inline bool edge_exists(
    const DependencyPlan& plan, u32 producer, u32 consumer,
    u32 resource) noexcept {
    for (u32 index = 0; index < plan.edge_count; ++index) {
        const DependencyEdge& edge = plan.edges[index];
        if (edge.producer_pass == producer && edge.consumer_pass == consumer
            && edge.resource_id == resource) {
            return true;
        }
    }
    return false;
}

}  // namespace detail

[[nodiscard]] inline GraphError build_dependency_plan(
    const GraphDefinition& graph, DependencyPlan& plan,
    GraphDiagnostic& diagnostic) noexcept {
    plan = DependencyPlan{};
    const GraphError validation = validate_graph(graph, diagnostic);
    if (validation != GraphError::None) {
        return validation;
    }

    std::array<u32, kMaxResources> writers{};
    writers.fill(kMaxResources);
    for (u32 use_index = 0; use_index < graph.use_count; ++use_index) {
        const UseDesc& use = graph.uses[use_index];
        if (!detail::is_writer(use.access)) {
            continue;
        }
        const u32 resource_index = detail::find_resource(graph, use.resource_id);
        const u32 pass_index = detail::find_pass(graph, use.pass_id);
        if (writers[resource_index] != kMaxResources
            && writers[resource_index] != pass_index) {
            return detail::set_error(
                diagnostic, GraphError::AmbiguousWriter, use.pass_id,
                use.resource_id, use_index);
        }
        writers[resource_index] = pass_index;
    }

    for (u32 use_index = 0; use_index < graph.use_count; ++use_index) {
        const UseDesc& use = graph.uses[use_index];
        const u32 resource_index = detail::find_resource(graph, use.resource_id);
        const ResourceDesc& resource = graph.resources[resource_index];
        if (detail::is_reader(use.access) && !detail::is_writer(use.access)
            && resource.kind == ResourceKind::Transient
            && writers[resource_index] == kMaxResources) {
            return detail::set_error(
                diagnostic, GraphError::UninitializedRead, use.pass_id,
                use.resource_id, use_index);
        }
    }

    for (u32 use_index = 0; use_index < graph.use_count; ++use_index) {
        const UseDesc& use = graph.uses[use_index];
        if (!detail::is_reader(use.access)) {
            continue;
        }
        const u32 resource_index = detail::find_resource(graph, use.resource_id);
        const u32 writer = writers[resource_index];
        if (writer == kMaxResources) {
            continue;
        }
        const u32 consumer = detail::find_pass(graph, use.pass_id);
        if (writer == consumer || detail::edge_exists(
                plan, graph.passes[writer].id, use.pass_id, use.resource_id)) {
            continue;
        }
        if (plan.edge_count >= kMaxEdges) {
            return detail::set_error(
                diagnostic, GraphError::CapacityFull, use.pass_id,
                use.resource_id, use_index);
        }
        plan.edges[plan.edge_count] = DependencyEdge{
            graph.passes[writer].id, use.pass_id, use.resource_id,
            Hazard::RAW};
        ++plan.edge_count;
    }
    std::sort(plan.edges.begin(), plan.edges.begin() + plan.edge_count,
              [](const DependencyEdge& left, const DependencyEdge& right) {
                  if (left.consumer_pass != right.consumer_pass) {
                      return left.consumer_pass < right.consumer_pass;
                  }
                  if (left.producer_pass != right.producer_pass) {
                      return left.producer_pass < right.producer_pass;
                  }
                  return left.resource_id < right.resource_id;
              });

    std::array<std::array<bool, kMaxPasses>, kMaxPasses> adjacency{};
    std::array<u32, kMaxPasses> indegree{};
    for (u32 edge_index = 0; edge_index < plan.edge_count; ++edge_index) {
        const DependencyEdge& edge = plan.edges[edge_index];
        const u32 producer = detail::find_pass(graph, edge.producer_pass);
        const u32 consumer = detail::find_pass(graph, edge.consumer_pass);
        if (!adjacency[producer][consumer]) {
            adjacency[producer][consumer] = true;
            ++indegree[consumer];
        }
    }

    std::array<bool, kMaxPasses> placed{};
    for (u32 step = 0; step < graph.pass_count; ++step) {
        u32 selected = kMaxPasses;
        for (u32 index = 0; index < graph.pass_count; ++index) {
            if (!placed[index] && indegree[index] == 0) {
                selected = index;
                break;
            }
        }
        if (selected == kMaxPasses) {
            u32 blocked = 0;
            while (blocked < graph.pass_count && placed[blocked]) {
                ++blocked;
            }
            return detail::set_error(
                diagnostic, GraphError::Cycle,
                graph.passes[blocked].id, 0, blocked);
        }
        placed[selected] = true;
        plan.order[plan.order_count] = graph.passes[selected].id;
        ++plan.order_count;
        for (u32 consumer = 0; consumer < graph.pass_count; ++consumer) {
            if (adjacency[selected][consumer]) {
                --indegree[consumer];
            }
        }
    }
    return GraphError::None;
}

}  // namespace stormline::graphics::render_graph

#endif  // STORMLINE_GRAPHICS_RENDER_GRAPH_GRAPH_DEPENDENCY_HPP
