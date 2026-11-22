#ifndef STORMLINE_DATA_SCENE_SCENE_TYPES_HPP
#define STORMLINE_DATA_SCENE_SCENE_TYPES_HPP

#include <array>
#include <cstdint>

namespace stormline::data::scene {

using u32 = std::uint32_t;
using u64 = std::uint64_t;

inline constexpr u32 kMaxEntities = 64;
inline constexpr u32 kMaxComponents = 128;
inline constexpr u32 kMaxAssetRefs = 64;
inline constexpr u32 kMaxPatchOps = 64;
inline constexpr u32 kMaxDiffs = 128;
inline constexpr u32 kMaxNameBytes = 32;

enum class SceneError : std::uint8_t {
    None,
    InvalidArgument,
    InvalidSchema,
    UnsupportedSchema,
    DuplicateId,
    NotFound,
    ParentCycle,
    StaleRevision,
    CapacityFull,
    InvalidPatch,
    BufferFull
};

struct SceneId {
    u64 value{0};
};
struct EntityId {
    u64 value{0};
};
struct ComponentId {
    u64 value{0};
};

[[nodiscard]] constexpr bool valid(SceneId id) noexcept { return id.value != 0; }
[[nodiscard]] constexpr bool valid(EntityId id) noexcept { return id.value != 0; }
[[nodiscard]] constexpr bool valid(ComponentId id) noexcept { return id.value != 0; }

struct SchemaDescriptor {
    u32 schema_id{0};
    u32 version{0};
    u32 capabilities{0};
    u32 canonicalization_version{0};
};

struct EntityRecord {
    EntityId id{};
    EntityId parent{};
    u32 child_order{0};
    bool enabled{true};
    std::array<char, kMaxNameBytes> name{};
    u32 name_length{0};
};

struct ComponentRecord {
    ComponentId id{};
    EntityId entity{};
    u32 type_id{0};
    u32 type_version{0};
};

}  // namespace stormline::data::scene

#endif  // STORMLINE_DATA_SCENE_SCENE_TYPES_HPP
