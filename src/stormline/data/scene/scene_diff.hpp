#ifndef STORMLINE_DATA_SCENE_SCENE_DIFF_HPP
#define STORMLINE_DATA_SCENE_SCENE_DIFF_HPP

#include "stormline/data/scene/scene_document.hpp"

#include <span>

namespace stormline::data::scene {

enum class DiffKind : std::uint8_t {
    Added,
    Removed,
    EnabledChanged,
    NameChanged
};

struct DiffEntry {
    EntityId entity{};
    DiffKind kind{DiffKind::Added};
};

[[nodiscard]] inline SceneError diff(
    const SceneDocument& base, const SceneDocument& next,
    std::span<DiffEntry> output, u32& out_count) noexcept {
    out_count = 0;
    if (base.scene().value != next.scene().value) {
        return SceneError::InvalidArgument;
    }
    DiffEntry entries[kMaxDiffs]{};
    u32 count = 0;
    for (u32 index = 0; index < base.entity_count(); ++index) {
        EntityRecord base_entity{};
        if (!base.entity_at(index, base_entity)) {
            continue;
        }
        EntityRecord next_entity{};
        if (next.find_entity(base_entity.id, next_entity) == SceneError::NotFound) {
            entries[count++] = DiffEntry{base_entity.id, DiffKind::Removed};
            continue;
        }
        if (base_entity.enabled != next_entity.enabled) {
            entries[count++] = DiffEntry{base_entity.id, DiffKind::EnabledChanged};
        }
        bool same_name = base_entity.name_length == next_entity.name_length;
        if (same_name) {
            for (u32 position = 0; position < base_entity.name_length; ++position) {
                if (base_entity.name[position] != next_entity.name[position]) {
                    same_name = false;
                    break;
                }
            }
        }
        if (!same_name) {
            entries[count++] = DiffEntry{base_entity.id, DiffKind::NameChanged};
        }
    }
    for (u32 index = 0; index < next.entity_count(); ++index) {
        EntityRecord next_entity{};
        if (!next.entity_at(index, next_entity)) {
            continue;
        }
        EntityRecord base_entity{};
        if (base.find_entity(next_entity.id, base_entity) == SceneError::NotFound) {
            entries[count++] = DiffEntry{next_entity.id, DiffKind::Added};
        }
    }
    for (u32 index = 1; index < count; ++index) {
        const DiffEntry key = entries[index];
        u32 position = index;
        while (position > 0
               && (entries[position - 1].entity.value > key.entity.value
                   || (entries[position - 1].entity.value == key.entity.value
                       && static_cast<std::uint8_t>(entries[position - 1].kind)
                           > static_cast<std::uint8_t>(key.kind)))) {
            entries[position] = entries[position - 1];
            --position;
        }
        entries[position] = key;
    }
    out_count = count;
    if (count > output.size()) {
        return SceneError::BufferFull;
    }
    for (u32 index = 0; index < count; ++index) {
        output[index] = entries[index];
    }
    return SceneError::None;
}

}  // namespace stormline::data::scene

#endif  // STORMLINE_DATA_SCENE_SCENE_DIFF_HPP
