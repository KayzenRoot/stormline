#ifndef STORMLINE_PROCEDURAL_GRAPH_PLAN_HPP
#define STORMLINE_PROCEDURAL_GRAPH_PLAN_HPP

#include <array>

#include "stormline/procedural/procedural_types.hpp"

namespace stormline::procedural {

struct GraphNodeDesc {
    u32 node_id{0};
    u32 algorithm_id{0};
    u32 algorithm_version{0};
    u32 input_type{0};
    u32 output_type{0};
    u32 fan_out{0};
};

struct GraphEdgeDesc {
    u32 edge_id{0};
    u32 from_node{0};
    u32 to_node{0};
};

struct GraphSetDesc {
    u32 graph_id{0};
    u32 revision{0};
    u32 node_count{0};
    u32 edge_count{0};
    std::array<GraphNodeDesc, kMaxGraphNodes> nodes{};
    std::array<GraphEdgeDesc, kMaxGraphEdges> edges{};
};

struct GraphPlan {
    u32 node_count{0};
    u32 edge_count{0};
    u32 root_count{0};
    u32 leaf_count{0};
    u32 max_depth{0};
};

[[nodiscard]] inline ProcError plan_graph(
    const GraphSetDesc& graph, GraphPlan& plan,
    ProcDiagnostic& diagnostic) noexcept {
    plan = GraphPlan{};
    diagnostic = ProcDiagnostic{};
    if (graph.graph_id == 0 || graph.revision == 0) {
        return detail::set_proc_error(
            diagnostic, ProcError::InvalidArgument, graph.graph_id, 0);
    }
    if (graph.node_count == 0) {
        return detail::set_proc_error(
            diagnostic, ProcError::GraphInvalid, graph.graph_id, 0);
    }
    if (graph.node_count > kMaxGraphNodes
        || graph.edge_count > kMaxGraphEdges) {
        return detail::set_proc_error(
            diagnostic, ProcError::CapacityFull, graph.graph_id, 0);
    }
    for (u32 index = 0; index < graph.node_count; ++index) {
        const GraphNodeDesc& node = graph.nodes[index];
        if (node.node_id == 0 || node.algorithm_id == 0
            || node.algorithm_version == 0 || node.input_type == 0
            || node.output_type == 0 || node.fan_out > kMaxNodeFanOut) {
            return detail::set_proc_error(
                diagnostic, ProcError::GraphInvalid, graph.graph_id, index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (graph.nodes[previous].node_id == node.node_id) {
                return detail::set_proc_error(
                    diagnostic, ProcError::DuplicateId, graph.graph_id,
                    index);
            }
        }
    }
    for (u32 index = 0; index < graph.edge_count; ++index) {
        const GraphEdgeDesc& edge = graph.edges[index];
        if (edge.edge_id == 0 || edge.from_node == 0 || edge.to_node == 0
            || edge.from_node == edge.to_node) {
            return detail::set_proc_error(
                diagnostic, ProcError::GraphInvalid, graph.graph_id, index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (graph.edges[previous].edge_id == edge.edge_id
                || (graph.edges[previous].from_node == edge.from_node
                    && graph.edges[previous].to_node == edge.to_node)) {
                return detail::set_proc_error(
                    diagnostic, ProcError::DuplicateId, graph.graph_id,
                    index);
            }
        }
        bool from_found = false;
        bool to_found = false;
        for (u32 candidate = 0; candidate < graph.node_count; ++candidate) {
            if (graph.nodes[candidate].node_id == edge.from_node) {
                from_found = true;
            }
            if (graph.nodes[candidate].node_id == edge.to_node) {
                to_found = true;
            }
        }
        if (!from_found || !to_found) {
            return detail::set_proc_error(
                diagnostic, ProcError::NotFound, graph.graph_id, index);
        }
    }
    std::array<u32, kMaxGraphNodes> indegree{};
    std::array<u32, kMaxGraphNodes> outdegree{};
    for (u32 index = 0; index < graph.edge_count; ++index) {
        u32 from_index = 0;
        u32 to_index = 0;
        for (u32 candidate = 0; candidate < graph.node_count; ++candidate) {
            if (graph.nodes[candidate].node_id
                == graph.edges[index].from_node) {
                from_index = candidate;
            }
            if (graph.nodes[candidate].node_id
                == graph.edges[index].to_node) {
                to_index = candidate;
            }
        }
        if (outdegree[from_index] >= kMaxNodeFanOut) {
            return detail::set_proc_error(
                diagnostic, ProcError::OutOfRange, graph.graph_id, index);
        }
        ++outdegree[from_index];
        ++indegree[to_index];
    }
    const std::array<u32, kMaxGraphNodes> initial_indegree = indegree;
    std::array<u32, kMaxGraphNodes> depth{};
    std::array<u32, kMaxGraphNodes> queue{};
    u32 head = 0;
    u32 tail = 0;
    for (u32 index = 0; index < graph.node_count; ++index) {
        if (indegree[index] == 0) {
            depth[index] = 1;
            queue[tail++] = index;
        }
    }
    u32 processed = 0;
    while (head < tail) {
        const u32 node_index = queue[head++];
        ++processed;
        for (u32 edge_index = 0; edge_index < graph.edge_count;
             ++edge_index) {
            if (graph.edges[edge_index].from_node
                != graph.nodes[node_index].node_id) {
                continue;
            }
            u32 target = 0;
            for (u32 candidate = 0; candidate < graph.node_count;
                 ++candidate) {
                if (graph.nodes[candidate].node_id
                    == graph.edges[edge_index].to_node) {
                    target = candidate;
                }
            }
            if (depth[node_index] + 1 > depth[target]) {
                depth[target] = depth[node_index] + 1;
            }
            if (--indegree[target] == 0) {
                queue[tail++] = target;
            }
        }
    }
    if (processed != graph.node_count) {
        return detail::set_proc_error(
            diagnostic, ProcError::CycleDetected, graph.graph_id, 0);
    }
    plan.node_count = graph.node_count;
    plan.edge_count = graph.edge_count;
    for (u32 index = 0; index < graph.node_count; ++index) {
        if (initial_indegree[index] == 0) {
            ++plan.root_count;
        }
        if (outdegree[index] == 0) {
            ++plan.leaf_count;
        }
        if (depth[index] > plan.max_depth) {
            plan.max_depth = depth[index];
        }
    }
    if (plan.max_depth > kMaxGraphDepth) {
        plan = GraphPlan{};
        return detail::set_proc_error(
            diagnostic, ProcError::OutOfRange, graph.graph_id, 0);
    }
    return ProcError::None;
}

}  // namespace stormline::procedural

#endif  // STORMLINE_PROCEDURAL_GRAPH_PLAN_HPP
