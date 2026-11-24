#ifndef STORMLINE_WORLD_QUERY_PLAN_HPP
#define STORMLINE_WORLD_QUERY_PLAN_HPP

#include <array>

#include "stormline/world/world_types.hpp"

namespace stormline::world {

struct EntityQueryDesc {
    u32 query_id{0};
    u32 revision{0};
    u32 world_epoch{0};
    u32 required_count{0};
    u32 excluded_count{0};
    std::array<u32, kMaxQueryTypes> required_types{};
    std::array<u32, kMaxQueryTypes> excluded_types{};
};

struct EntityQueryPlan {
    u32 required_count{0};
    u32 excluded_count{0};
};

[[nodiscard]] inline WorldError plan_entity_query(
    const EntityQueryDesc& query, EntityQueryPlan& plan,
    WorldDiagnostic& diagnostic) noexcept {
    plan = EntityQueryPlan{};
    diagnostic = WorldDiagnostic{};
    if (query.query_id == 0 || query.revision == 0
        || query.world_epoch == 0) {
        return detail::set_world_error(
            diagnostic, WorldError::InvalidArgument, query.query_id, 0);
    }
    if (query.required_count == 0
        || query.required_count > kMaxQueryTypes) {
        return detail::set_world_error(
            diagnostic, WorldError::QueryInvalid, query.query_id, 0);
    }
    if (query.excluded_count > kMaxQueryTypes) {
        return detail::set_world_error(
            diagnostic, WorldError::QueryInvalid, query.query_id, 0);
    }
    for (u32 index = 0; index < query.required_count; ++index) {
        const u32 type_id = query.required_types[index];
        if (type_id == 0) {
            return detail::set_world_error(
                diagnostic, WorldError::QueryInvalid, query.query_id, index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (query.required_types[previous] == type_id) {
                return detail::set_world_error(
                    diagnostic, WorldError::DuplicateId, query.query_id,
                    index);
            }
        }
        for (u32 excluded = 0; excluded < query.excluded_count; ++excluded) {
            if (query.excluded_types[excluded] == type_id) {
                return detail::set_world_error(
                    diagnostic, WorldError::DuplicateId, query.query_id,
                    index);
            }
        }
    }
    for (u32 index = 0; index < query.excluded_count; ++index) {
        const u32 type_id = query.excluded_types[index];
        if (type_id == 0) {
            return detail::set_world_error(
                diagnostic, WorldError::QueryInvalid, query.query_id, index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (query.excluded_types[previous] == type_id) {
                return detail::set_world_error(
                    diagnostic, WorldError::DuplicateId, query.query_id,
                    index);
            }
        }
    }
    plan.required_count = query.required_count;
    plan.excluded_count = query.excluded_count;
    return WorldError::None;
}

}  // namespace stormline::world

#endif  // STORMLINE_WORLD_QUERY_PLAN_HPP
