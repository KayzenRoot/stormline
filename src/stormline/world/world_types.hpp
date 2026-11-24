#ifndef STORMLINE_WORLD_WORLD_TYPES_HPP
#define STORMLINE_WORLD_WORLD_TYPES_HPP

#include <cstdint>

namespace stormline::world {

using u8 = std::uint8_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using f32 = float;

inline constexpr u32 kMaxWorldEntities = 64;
inline constexpr u32 kMaxComponentTypes = 32;
inline constexpr u32 kMaxComponentFields = 16;
inline constexpr u32 kMaxQueryTypes = 8;
inline constexpr u32 kMaxQueryResults = 64;

enum class WorldError : std::uint8_t {
    None,
    InvalidArgument,
    DuplicateId,
    NotFound,
    CapacityFull,
    NonFiniteValue,
    OutOfRange,
    EntityInvalid,
    ComponentInvalid,
    LifecycleInvalid,
    QueryInvalid,
    ReflectionInvalid,
    Unsupported
};

enum class EntityState : std::uint8_t {
    Alive,
    DestroyRequested,
    Tombstoned,
    Retired
};

enum class FieldKind : std::uint8_t {
    Bool,
    U32,
    I32,
    F32,
    StringId,
    EntityRef
};

struct WorldDiagnostic {
    WorldError code{WorldError::None};
    u32 source_id{0};
    u32 index{0};
};

namespace detail {

inline WorldError set_world_error(
    WorldDiagnostic& diagnostic, WorldError code, u32 source_id,
    u32 index) noexcept {
    diagnostic = WorldDiagnostic{code, source_id, index};
    return code;
}

inline bool finite(f32 value) noexcept {
    return value == value && value - value == 0.0f;
}

inline bool valid_state(EntityState state) noexcept {
    switch (state) {
        case EntityState::Alive:
        case EntityState::DestroyRequested:
        case EntityState::Tombstoned:
        case EntityState::Retired:
            return true;
    }
    return false;
}

inline bool valid_field_kind(FieldKind kind) noexcept {
    switch (kind) {
        case FieldKind::Bool:
        case FieldKind::U32:
        case FieldKind::I32:
        case FieldKind::F32:
        case FieldKind::StringId:
        case FieldKind::EntityRef:
            return true;
    }
    return false;
}

}  // namespace detail

}  // namespace stormline::world

#endif  // STORMLINE_WORLD_WORLD_TYPES_HPP
