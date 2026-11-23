#ifndef STORMLINE_GRAPHICS_RENDER_GRAPH_GRAPH_DEFINITION_HPP
#define STORMLINE_GRAPHICS_RENDER_GRAPH_GRAPH_DEFINITION_HPP

#include "stormline/graphics/render_graph/graph_types.hpp"

namespace stormline::graphics::render_graph {

namespace detail {

inline GraphError set_error(
    GraphDiagnostic& diagnostic, GraphError code, u32 pass_id,
    u32 resource_id, u32 index) noexcept {
    diagnostic = GraphDiagnostic{code, pass_id, resource_id, index};
    return code;
}

[[nodiscard]] inline bool valid_resource(const ResourceDesc& resource) noexcept {
    return resource.id != 0
        && static_cast<u8>(resource.kind) <= static_cast<u8>(ResourceKind::History)
        && resource.bytes != 0
        && resource.bytes <= 0x7FFFFFFFFFFFFFFFULL
        && resource.alignment != 0
        && resource.alignment <= kMaxAlignment
        && (resource.alignment & (resource.alignment - 1)) == 0;
}

[[nodiscard]] inline bool valid_pass(const PassDesc& pass) noexcept {
    return pass.id != 0
        && static_cast<u8>(pass.queue) <= static_cast<u8>(rhi::QueueRole::Transfer)
        && static_cast<u8>(pass.kind) <= static_cast<u8>(PassKind::Present);
}

[[nodiscard]] inline bool valid_access(Access access) noexcept {
    return static_cast<u8>(access) <= static_cast<u8>(Access::ReadWrite);
}

[[nodiscard]] inline u32 find_resource(
    const GraphDefinition& graph, u32 id) noexcept {
    for (u32 index = 0; index < graph.resource_count; ++index) {
        if (graph.resources[index].id == id) {
            return index;
        }
    }
    return kMaxResources;
}

[[nodiscard]] inline u32 find_pass(
    const GraphDefinition& graph, u32 id) noexcept {
    for (u32 index = 0; index < graph.pass_count; ++index) {
        if (graph.passes[index].id == id) {
            return index;
        }
    }
    return kMaxPasses;
}

}  // namespace detail

[[nodiscard]] inline const char* graph_error_name(GraphError error) noexcept {
    switch (error) {
        case GraphError::None: return "None";
        case GraphError::InvalidArgument: return "InvalidArgument";
        case GraphError::DuplicatePass: return "DuplicatePass";
        case GraphError::DuplicateResource: return "DuplicateResource";
        case GraphError::NotFound: return "NotFound";
        case GraphError::CapacityFull: return "CapacityFull";
        case GraphError::Cycle: return "Cycle";
        case GraphError::AmbiguousWriter: return "AmbiguousWriter";
        case GraphError::UninitializedRead: return "UninitializedRead";
        case GraphError::InvalidUse: return "InvalidUse";
        case GraphError::QueueUnsupported: return "QueueUnsupported";
        case GraphError::AliasConflict: return "AliasConflict";
        case GraphError::BudgetUnknown: return "BudgetUnknown";
        case GraphError::BudgetExceeded: return "BudgetExceeded";
        case GraphError::StaleGeneration: return "StaleGeneration";
    }
    return "Unknown";
}

[[nodiscard]] inline GraphError add_resource(
    GraphDefinition& graph, const ResourceDesc& resource) noexcept {
    if (graph.resource_count >= kMaxResources) {
        return GraphError::CapacityFull;
    }
    if (!detail::valid_resource(resource)) {
        return GraphError::InvalidArgument;
    }
    if (detail::find_resource(graph, resource.id) != kMaxResources) {
        return GraphError::DuplicateResource;
    }
    graph.resources[graph.resource_count] = resource;
    ++graph.resource_count;
    return GraphError::None;
}

[[nodiscard]] inline GraphError add_pass(
    GraphDefinition& graph, const PassDesc& pass) noexcept {
    if (graph.pass_count >= kMaxPasses) {
        return GraphError::CapacityFull;
    }
    if (!detail::valid_pass(pass)) {
        return GraphError::InvalidArgument;
    }
    if (detail::find_pass(graph, pass.id) != kMaxPasses) {
        return GraphError::DuplicatePass;
    }
    graph.passes[graph.pass_count] = pass;
    ++graph.pass_count;
    return GraphError::None;
}

[[nodiscard]] inline GraphError add_use(
    GraphDefinition& graph, const UseDesc& use) noexcept {
    if (graph.use_count >= kMaxUses) {
        return GraphError::CapacityFull;
    }
    if (!detail::valid_access(use.access)) {
        return GraphError::InvalidUse;
    }
    if (detail::find_pass(graph, use.pass_id) == kMaxPasses
        || detail::find_resource(graph, use.resource_id) == kMaxResources) {
        return GraphError::NotFound;
    }
    graph.uses[graph.use_count] = use;
    ++graph.use_count;
    return GraphError::None;
}

[[nodiscard]] inline GraphError validate_graph(
    const GraphDefinition& graph, GraphDiagnostic& diagnostic) noexcept {
    diagnostic = GraphDiagnostic{};
    if (graph.device_generation == 0) {
        return detail::set_error(
            diagnostic, GraphError::InvalidArgument, 0, 0, 0);
    }
    if (graph.pass_count == 0 || graph.resource_count == 0
        || graph.use_count > kMaxUses) {
        return detail::set_error(
            diagnostic, GraphError::InvalidArgument, 0, 0, 0);
    }
    if (graph.pass_count > kMaxPasses || graph.resource_count > kMaxResources) {
        return detail::set_error(
            diagnostic, GraphError::CapacityFull, 0, 0, 0);
    }
    for (u32 index = 0; index < graph.resource_count; ++index) {
        const ResourceDesc& resource = graph.resources[index];
        if (!detail::valid_resource(resource)) {
            return detail::set_error(
                diagnostic, GraphError::InvalidArgument, 0, resource.id, index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (graph.resources[previous].id == resource.id) {
                return detail::set_error(
                    diagnostic, GraphError::DuplicateResource, 0, resource.id,
                    index);
            }
        }
    }
    for (u32 index = 0; index < graph.pass_count; ++index) {
        const PassDesc& pass = graph.passes[index];
        if (!detail::valid_pass(pass)) {
            return detail::set_error(
                diagnostic, GraphError::InvalidArgument, pass.id, 0, index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (graph.passes[previous].id == pass.id) {
                return detail::set_error(
                    diagnostic, GraphError::DuplicatePass, pass.id, 0, index);
            }
        }
    }
    for (u32 index = 0; index < graph.use_count; ++index) {
        const UseDesc& use = graph.uses[index];
        if (!detail::valid_access(use.access)) {
            return detail::set_error(
                diagnostic, GraphError::InvalidUse, use.pass_id,
                use.resource_id, index);
        }
        if (detail::find_pass(graph, use.pass_id) == kMaxPasses
            || detail::find_resource(graph, use.resource_id) == kMaxResources) {
            return detail::set_error(
                diagnostic, GraphError::NotFound, use.pass_id,
                use.resource_id, index);
        }
    }
    return GraphError::None;
}

}  // namespace stormline::graphics::render_graph

#endif  // STORMLINE_GRAPHICS_RENDER_GRAPH_GRAPH_DEFINITION_HPP
