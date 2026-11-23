#ifndef STORMLINE_GRAPHICS_RENDER_GRAPH_GRAPH_TRANSIENT_HPP
#define STORMLINE_GRAPHICS_RENDER_GRAPH_GRAPH_TRANSIENT_HPP

#include "stormline/graphics/render_graph/graph_dependency.hpp"

#include <algorithm>

namespace stormline::graphics::render_graph {

namespace detail {

[[nodiscard]] inline GraphError validate_order(
    const GraphDefinition& graph, const DependencyPlan& dependencies,
    GraphDiagnostic& diagnostic) noexcept {
    if (dependencies.order_count != graph.pass_count) {
        return set_error(diagnostic, GraphError::InvalidArgument, 0, 0, 0);
    }
    for (u32 index = 0; index < dependencies.order_count; ++index) {
        if (find_pass(graph, dependencies.order[index]) == kMaxPasses) {
            return set_error(diagnostic, GraphError::InvalidArgument,
                             dependencies.order[index], 0, index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (dependencies.order[previous] == dependencies.order[index]) {
                return set_error(diagnostic, GraphError::InvalidArgument,
                                 dependencies.order[index], 0, index);
            }
        }
    }
    return GraphError::None;
}

[[nodiscard]] inline bool alias_compatible(
    const ResourceDesc& resource, const AliasGroup& group) noexcept {
    return resource.bytes == group.bytes
        && resource.alignment == group.alignment;
}

}  // namespace detail

[[nodiscard]] inline GraphError plan_transients(
    const GraphDefinition& graph, const DependencyPlan& dependencies,
    AliasPlan& plan, GraphDiagnostic& diagnostic) noexcept {
    plan = AliasPlan{};
    const GraphError validation = validate_graph(graph, diagnostic);
    if (validation != GraphError::None) {
        return validation;
    }
    const GraphError order_status =
        detail::validate_order(graph, dependencies, diagnostic);
    if (order_status != GraphError::None) {
        return order_status;
    }

    std::array<u32, kMaxPasses> positions{};
    positions.fill(kMaxPasses);
    for (u32 index = 0; index < dependencies.order_count; ++index) {
        positions[detail::find_pass(graph, dependencies.order[index])] = index;
    }

    std::array<Lifetime, kMaxResources> lifetimes{};
    u32 lifetime_count = 0;
    for (u32 resource_index = 0; resource_index < graph.resource_count;
         ++resource_index) {
        const ResourceDesc& resource = graph.resources[resource_index];
        if (resource.kind != ResourceKind::Transient) {
            continue;
        }
        u32 first = kMaxPasses;
        u32 last = 0;
        bool used = false;
        for (u32 use_index = 0; use_index < graph.use_count; ++use_index) {
            const UseDesc& use = graph.uses[use_index];
            if (use.resource_id != resource.id) {
                continue;
            }
            const u32 pass_index = detail::find_pass(graph, use.pass_id);
            const u32 position = positions[pass_index];
            if (!used || position < first) {
                first = position;
            }
            if (!used || position > last) {
                last = position;
            }
            used = true;
        }
        if (used) {
            lifetimes[lifetime_count] = Lifetime{resource.id, first, last};
            ++lifetime_count;
        }
    }
    std::sort(lifetimes.begin(), lifetimes.begin() + lifetime_count,
              [](const Lifetime& left, const Lifetime& right) {
                  if (left.first_pass != right.first_pass) {
                      return left.first_pass < right.first_pass;
                  }
                  return left.resource_id < right.resource_id;
              });
    for (u32 index = 0; index < lifetime_count; ++index) {
        plan.lifetimes[index] = lifetimes[index];
    }
    plan.lifetime_count = lifetime_count;

    for (u32 index = 0; index < lifetime_count; ++index) {
        const Lifetime& lifetime = lifetimes[index];
        const u32 resource_index = detail::find_resource(graph, lifetime.resource_id);
        const ResourceDesc& resource = graph.resources[resource_index];
        u32 group_index = kMaxAliasGroups;
        for (u32 candidate = 0; candidate < plan.group_count; ++candidate) {
            const AliasGroup& group = plan.groups[candidate];
            if (!detail::alias_compatible(resource, group)) {
                continue;
            }
            u32 group_last = 0;
            bool has_member = false;
            for (u32 member = 0; member < group.resource_count; ++member) {
                for (u32 entry = 0; entry < plan.lifetime_count; ++entry) {
                    if (plan.lifetimes[entry].resource_id
                        == group.resource_ids[member]) {
                        if (!has_member || plan.lifetimes[entry].last_pass > group_last) {
                            group_last = plan.lifetimes[entry].last_pass;
                        }
                        has_member = true;
                        break;
                    }
                }
            }
            if (has_member && group_last < lifetime.first_pass) {
                group_index = candidate;
                break;
            }
        }
        if (group_index == kMaxAliasGroups) {
            if (plan.group_count >= kMaxAliasGroups) {
                return detail::set_error(
                    diagnostic, GraphError::CapacityFull, 0,
                    lifetime.resource_id, index);
            }
            AliasGroup& group = plan.groups[plan.group_count];
            group = AliasGroup{};
            group.bytes = resource.bytes;
            group.alignment = resource.alignment;
            group.resource_ids[0] = resource.id;
            group.resource_count = 1;
            ++plan.group_count;
        } else {
            AliasGroup& group = plan.groups[group_index];
            if (group.resource_count >= kMaxResources) {
                return detail::set_error(
                    diagnostic, GraphError::CapacityFull, 0,
                    lifetime.resource_id, index);
            }
            if (resource.bytes > 0xFFFFFFFFFFFFFFFFULL - plan.alias_saved_bytes) {
                return detail::set_error(
                    diagnostic, GraphError::CapacityFull, 0,
                    lifetime.resource_id, index);
            }
            group.resource_ids[group.resource_count] = resource.id;
            ++group.resource_count;
            plan.alias_saved_bytes += resource.bytes;
        }
    }
    return GraphError::None;
}

}  // namespace stormline::graphics::render_graph

#endif  // STORMLINE_GRAPHICS_RENDER_GRAPH_GRAPH_TRANSIENT_HPP
