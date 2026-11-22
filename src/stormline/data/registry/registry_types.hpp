#ifndef STORMLINE_DATA_REGISTRY_REGISTRY_TYPES_HPP
#define STORMLINE_DATA_REGISTRY_REGISTRY_TYPES_HPP

#include "stormline/data/vfs/vfs_path.hpp"

#include <cstdint>

namespace stormline::data::registry {

namespace vfs = stormline::data::vfs;

using u32 = std::uint32_t;
using u64 = std::uint64_t;

inline constexpr u32 kMaxAssets = 64;
inline constexpr u32 kMaxDependencies = 128;
inline constexpr u32 kMaxTagsPerAsset = 8;
inline constexpr u32 kMaxTagBytes = 32;
inline constexpr u32 kMaxMetadataEntriesPerAsset = 8;
inline constexpr u32 kMaxMetadataKeyBytes = 32;
inline constexpr u32 kMaxMetadataValueBytes = 64;
inline constexpr u32 kMaxQueryResults = 64;
inline constexpr u32 kSupportedSchemaVersion = 1;

enum class RegistryError : std::uint8_t {
    None,
    InvalidArgument,
    InvalidId,
    InvalidPath,
    DuplicateId,
    DuplicatePath,
    NotFound,
    Tombstoned,
    CapacityFull,
    DependencyCycle,
    UnresolvedReference,
    InvalidTag,
    InvalidSchema,
    RevisionConflict,
    BufferFull,
    InternalFailure
};

struct ProjectId {
    u64 value{0};
};

[[nodiscard]] constexpr bool valid(ProjectId id) noexcept {
    return id.value != 0;
}

struct AssetId {
    u64 high{0};
    u64 low{0};
};

[[nodiscard]] constexpr bool valid(AssetId id) noexcept {
    return id.high != 0 || id.low != 0;
}

[[nodiscard]] constexpr bool less(AssetId lhs, AssetId rhs) noexcept {
    return lhs.high != rhs.high ? lhs.high < rhs.high : lhs.low < rhs.low;
}

enum class AssetKind : std::uint8_t {
    Unknown,
    Texture,
    Mesh,
    Material,
    Audio,
    Scene,
    Script
};

enum class AssetStatus : std::uint8_t {
    Active,
    Tombstoned
};

struct AssetRecord {
    AssetId id{};
    ProjectId project{};
    vfs::VfsPath path{};
    AssetKind kind{AssetKind::Unknown};
    AssetStatus status{AssetStatus::Active};
    u64 revision{1};
    u32 schema_version{0};
};

}  // namespace stormline::data::registry

#endif  // STORMLINE_DATA_REGISTRY_REGISTRY_TYPES_HPP
