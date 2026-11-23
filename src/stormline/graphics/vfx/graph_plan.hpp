#ifndef STORMLINE_GRAPHICS_VFX_GRAPH_PLAN_HPP
#define STORMLINE_GRAPHICS_VFX_GRAPH_PLAN_HPP

#include "stormline/graphics/vfx/vfx_types.hpp"

namespace stormline::graphics::vfx {

struct VfxGraphNode {
    u32 node_id{0};
    u32 revision{0};
    VfxNodeKind kind{VfxNodeKind::Emitter};
    VfxPortType input_type{VfxPortType::Flow};
    VfxPortType output_type{VfxPortType::Flow};
};

struct VfxGraphEdge {
    u32 source_node{0};
    u32 target_node{0};
    VfxPortType port_type{VfxPortType::Flow};
};

struct VfxGraphDesc {
    u32 graph_id{0};
    u32 revision{0};
    u32 node_count{0};
    std::array<VfxGraphNode, kMaxGraphNodes> nodes{};
    u32 edge_count{0};
    std::array<VfxGraphEdge, kMaxGraphEdges> edges{};
};

struct VfxGraphPlan {
    u32 node_count{0};
    u32 edge_count{0};
    std::array<u32, kMaxGraphNodes> order{};
    bool acyclic{false};
};

namespace detail {

inline VfxError set_vfx_error(
    VfxDiagnostic& diagnostic, VfxError code, u32 source_id, u32 node_id,
    u32 index) noexcept {
    diagnostic = VfxDiagnostic{code, source_id, node_id, index};
    return code;
}

inline bool valid_node_kind(VfxNodeKind kind) noexcept {
    switch (kind) {
        case VfxNodeKind::Emitter:
        case VfxNodeKind::Init:
        case VfxNodeKind::Force:
        case VfxNodeKind::Update:
        case VfxNodeKind::Event:
        case VfxNodeKind::Render:
        case VfxNodeKind::Output:
            return true;
    }
    return false;
}

inline bool valid_port_type(VfxPortType type) noexcept {
    switch (type) {
        case VfxPortType::Flow:
        case VfxPortType::Scalar:
        case VfxPortType::Vector:
        case VfxPortType::Color:
        case VfxPortType::Material:
        case VfxPortType::Geometry:
            return true;
    }
    return false;
}

inline bool valid_simulation_policy(SimulationPolicy policy) noexcept {
    switch (policy) {
        case SimulationPolicy::CpuReference:
        case SimulationPolicy::CpuRender:
        case SimulationPolicy::GpuCompute:
            return true;
    }
    return false;
}

inline u32 find_node(const VfxGraphDesc& graph, u32 node_id) noexcept {
    for (u32 index = 0; index < graph.node_count; ++index) {
        if (graph.nodes[index].node_id == node_id) {
            return index;
        }
    }
    return kMaxGraphNodes;
}

}  // namespace detail

[[nodiscard]] inline VfxError validate_graph(
    const VfxGraphDesc& graph, VfxGraphPlan& plan,
    VfxDiagnostic& diagnostic) noexcept {
    plan = VfxGraphPlan{};
    diagnostic = VfxDiagnostic{};
    if (graph.graph_id == 0 || graph.revision == 0) {
        return detail::set_vfx_error(
            diagnostic, VfxError::InvalidArgument, graph.graph_id, 0, 0);
    }
    if (graph.node_count > kMaxGraphNodes
        || graph.edge_count > kMaxGraphEdges) {
        return detail::set_vfx_error(
            diagnostic, VfxError::GraphTooComplex, graph.graph_id, 0, 0);
    }
    for (u32 index = 0; index < graph.node_count; ++index) {
        const VfxGraphNode& node = graph.nodes[index];
        if (node.node_id == 0 || node.revision == 0) {
            return detail::set_vfx_error(
                diagnostic, VfxError::InvalidArgument, graph.graph_id,
                node.node_id, index);
        }
        if (!detail::valid_node_kind(node.kind)
            || !detail::valid_port_type(node.input_type)
            || !detail::valid_port_type(node.output_type)) {
            return detail::set_vfx_error(
                diagnostic, VfxError::InvalidArgument, graph.graph_id,
                node.node_id, index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (graph.nodes[previous].node_id == node.node_id) {
                return detail::set_vfx_error(
                    diagnostic, VfxError::DuplicateId, graph.graph_id,
                    node.node_id, index);
            }
        }
    }
    std::array<u32, kMaxGraphNodes> indegree{};
    for (u32 index = 0; index < graph.edge_count; ++index) {
        const VfxGraphEdge& edge = graph.edges[index];
        const u32 source = detail::find_node(graph, edge.source_node);
        const u32 target = detail::find_node(graph, edge.target_node);
        if (!detail::valid_port_type(edge.port_type)) {
            return detail::set_vfx_error(
                diagnostic, VfxError::InvalidArgument, graph.graph_id,
                edge.source_node, index);
        }
        if (source == kMaxGraphNodes || target == kMaxGraphNodes) {
            return detail::set_vfx_error(
                diagnostic, VfxError::NotFound, graph.graph_id,
                source == kMaxGraphNodes ? edge.source_node : edge.target_node,
                index);
        }
        if (edge.source_node == edge.target_node) {
            return detail::set_vfx_error(
                diagnostic, VfxError::InvalidArgument, graph.graph_id,
                edge.source_node, index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (graph.edges[previous].source_node == edge.source_node
                && graph.edges[previous].target_node == edge.target_node) {
                return detail::set_vfx_error(
                    diagnostic, VfxError::DuplicateId, graph.graph_id,
                    edge.source_node, index);
            }
        }
        if (graph.nodes[source].output_type != edge.port_type
            || graph.nodes[target].input_type != edge.port_type) {
            return detail::set_vfx_error(
                diagnostic, VfxError::PortTypeMismatch, graph.graph_id,
                edge.source_node, index);
        }
        ++indegree[target];
    }
    std::array<u32, kMaxGraphNodes> queue{};
    u32 head = 0;
    u32 tail = 0;
    for (u32 index = 0; index < graph.node_count; ++index) {
        if (indegree[index] == 0) {
            queue[tail] = index;
            ++tail;
        }
    }
    u32 ordered = 0;
    while (head < tail) {
        const u32 current = queue[head];
        ++head;
        plan.order[ordered] = graph.nodes[current].node_id;
        ++ordered;
        for (u32 index = 0; index < graph.edge_count; ++index) {
            if (detail::find_node(graph, graph.edges[index].source_node)
                != current) {
                continue;
            }
            const u32 target =
                detail::find_node(graph, graph.edges[index].target_node);
            if (indegree[target] == 0) {
                continue;
            }
            --indegree[target];
            if (indegree[target] == 0) {
                queue[tail] = target;
                ++tail;
            }
        }
    }
    if (ordered != graph.node_count) {
        return detail::set_vfx_error(
            diagnostic, VfxError::GraphCycle, graph.graph_id, 0, 0);
    }
    plan.node_count = graph.node_count;
    plan.edge_count = graph.edge_count;
    plan.acyclic = true;
    return VfxError::None;
}

}  // namespace stormline::graphics::vfx

#endif  // STORMLINE_GRAPHICS_VFX_GRAPH_PLAN_HPP
