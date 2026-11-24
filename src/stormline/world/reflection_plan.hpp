#ifndef STORMLINE_WORLD_REFLECTION_PLAN_HPP
#define STORMLINE_WORLD_REFLECTION_PLAN_HPP

#include <array>

#include "stormline/world/world_types.hpp"

namespace stormline::world {

struct ReflectionFieldDesc {
    u32 field_id{0};
    u32 name_id{0};
    FieldKind kind{FieldKind::U32};
    f32 range_min{0.0f};
    f32 range_max{0.0f};
    bool editable{false};
    bool serialized{false};
};

struct ReflectionTypeDesc {
    u32 type_id{0};
    u32 version{0};
    u32 field_count{0};
    std::array<ReflectionFieldDesc, kMaxComponentFields> fields{};
};

struct ReflectionSetDesc {
    u32 world_epoch{0};
    u32 type_count{0};
    std::array<ReflectionTypeDesc, kMaxComponentTypes> types{};
};

struct ReflectionPlan {
    u32 type_count{0};
    u32 field_count{0};
    u32 editable_count{0};
    u32 serialized_count{0};
};

[[nodiscard]] inline WorldError plan_reflection(
    const ReflectionSetDesc& reflection, ReflectionPlan& plan,
    WorldDiagnostic& diagnostic) noexcept {
    plan = ReflectionPlan{};
    diagnostic = WorldDiagnostic{};
    if (reflection.world_epoch == 0) {
        return detail::set_world_error(
            diagnostic, WorldError::InvalidArgument, reflection.world_epoch,
            0);
    }
    if (reflection.type_count == 0
        || reflection.type_count > kMaxComponentTypes) {
        return detail::set_world_error(
            diagnostic, WorldError::ReflectionInvalid, reflection.world_epoch,
            0);
    }
    ReflectionPlan computed{};
    computed.type_count = reflection.type_count;
    for (u32 type_index = 0; type_index < reflection.type_count; ++type_index) {
        const ReflectionTypeDesc& type = reflection.types[type_index];
        if (type.type_id == 0 || type.version == 0) {
            return detail::set_world_error(
                diagnostic, WorldError::ReflectionInvalid,
                reflection.world_epoch, type_index);
        }
        for (u32 previous = 0; previous < type_index; ++previous) {
            if (reflection.types[previous].type_id == type.type_id) {
                return detail::set_world_error(
                    diagnostic, WorldError::DuplicateId,
                    reflection.world_epoch, type_index);
            }
        }
        if (type.field_count == 0
            || type.field_count > kMaxComponentFields) {
            return detail::set_world_error(
                diagnostic, WorldError::ReflectionInvalid,
                reflection.world_epoch, type_index);
        }
        for (u32 field_index = 0; field_index < type.field_count;
             ++field_index) {
            const ReflectionFieldDesc& field = type.fields[field_index];
            if (field.field_id == 0 || field.name_id == 0
                || !detail::valid_field_kind(field.kind)) {
                return detail::set_world_error(
                    diagnostic, WorldError::ReflectionInvalid,
                    reflection.world_epoch, field_index);
            }
            for (u32 previous = 0; previous < field_index; ++previous) {
                if (type.fields[previous].field_id == field.field_id
                    || type.fields[previous].name_id == field.name_id) {
                    return detail::set_world_error(
                        diagnostic, WorldError::DuplicateId,
                        reflection.world_epoch, field_index);
                }
            }
            if (!detail::finite(field.range_min)
                || !detail::finite(field.range_max)) {
                return detail::set_world_error(
                    diagnostic, WorldError::NonFiniteValue,
                    reflection.world_epoch, field_index);
            }
            if (field.range_min > field.range_max) {
                return detail::set_world_error(
                    diagnostic, WorldError::OutOfRange,
                    reflection.world_epoch, field_index);
            }
            ++computed.field_count;
            if (field.editable) {
                ++computed.editable_count;
            }
            if (field.serialized) {
                ++computed.serialized_count;
            }
        }
    }
    plan = computed;
    return WorldError::None;
}

}  // namespace stormline::world

#endif  // STORMLINE_WORLD_REFLECTION_PLAN_HPP
