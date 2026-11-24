#ifndef STORMLINE_WORLD_COMPONENT_SCHEMA_PLAN_HPP
#define STORMLINE_WORLD_COMPONENT_SCHEMA_PLAN_HPP

#include <array>

#include "stormline/world/world_types.hpp"

namespace stormline::world {

struct ComponentFieldDesc {
    u32 field_id{0};
    FieldKind kind{FieldKind::U32};
    f32 range_min{0.0f};
    f32 range_max{0.0f};
};

struct ComponentSchemaDesc {
    u32 type_id{0};
    u32 version{0};
    u32 field_count{0};
    std::array<ComponentFieldDesc, kMaxComponentFields> fields{};
};

struct ComponentRegistryDesc {
    u32 world_epoch{0};
    u32 type_count{0};
    std::array<ComponentSchemaDesc, kMaxComponentTypes> types{};
};

struct ComponentRegistryPlan {
    u32 type_count{0};
    u32 field_count{0};
};

[[nodiscard]] inline WorldError plan_component_registry(
    const ComponentRegistryDesc& registry, ComponentRegistryPlan& plan,
    WorldDiagnostic& diagnostic) noexcept {
    plan = ComponentRegistryPlan{};
    diagnostic = WorldDiagnostic{};
    if (registry.world_epoch == 0) {
        return detail::set_world_error(
            diagnostic, WorldError::InvalidArgument, registry.world_epoch, 0);
    }
    if (registry.type_count == 0
        || registry.type_count > kMaxComponentTypes) {
        return detail::set_world_error(
            diagnostic, WorldError::ComponentInvalid, registry.world_epoch, 0);
    }
    ComponentRegistryPlan computed{};
    computed.type_count = registry.type_count;
    for (u32 type_index = 0; type_index < registry.type_count; ++type_index) {
        const ComponentSchemaDesc& schema = registry.types[type_index];
        if (schema.type_id == 0 || schema.version == 0) {
            return detail::set_world_error(
                diagnostic, WorldError::ComponentInvalid, registry.world_epoch,
                type_index);
        }
        for (u32 previous = 0; previous < type_index; ++previous) {
            if (registry.types[previous].type_id == schema.type_id) {
                return detail::set_world_error(
                    diagnostic, WorldError::DuplicateId, registry.world_epoch,
                    type_index);
            }
        }
        if (schema.field_count == 0
            || schema.field_count > kMaxComponentFields) {
            return detail::set_world_error(
                diagnostic, WorldError::ComponentInvalid, registry.world_epoch,
                type_index);
        }
        for (u32 field_index = 0; field_index < schema.field_count;
             ++field_index) {
            const ComponentFieldDesc& field = schema.fields[field_index];
            if (field.field_id == 0
                || !detail::valid_field_kind(field.kind)) {
                return detail::set_world_error(
                    diagnostic, WorldError::ComponentInvalid,
                    registry.world_epoch, field_index);
            }
            for (u32 previous = 0; previous < field_index; ++previous) {
                if (schema.fields[previous].field_id == field.field_id) {
                    return detail::set_world_error(
                        diagnostic, WorldError::DuplicateId,
                        registry.world_epoch, field_index);
                }
            }
            if (!detail::finite(field.range_min)
                || !detail::finite(field.range_max)) {
                return detail::set_world_error(
                    diagnostic, WorldError::NonFiniteValue,
                    registry.world_epoch, field_index);
            }
            if (field.range_min > field.range_max) {
                return detail::set_world_error(
                    diagnostic, WorldError::OutOfRange, registry.world_epoch,
                    field_index);
            }
            ++computed.field_count;
        }
    }
    plan = computed;
    return WorldError::None;
}

}  // namespace stormline::world

#endif  // STORMLINE_WORLD_COMPONENT_SCHEMA_PLAN_HPP
