#ifndef STORMLINE_DATA_VFS_VFS_TYPES_HPP
#define STORMLINE_DATA_VFS_VFS_TYPES_HPP

#include <array>
#include <cstdint>
#include <string_view>

namespace stormline::data::vfs {

using u32 = std::uint32_t;
using u64 = std::uint64_t;
using i64 = std::int64_t;

inline constexpr u32 kMaxPathBytes = 512;
inline constexpr u32 kMaxComponentBytes = 64;
inline constexpr u32 kMaxMounts = 32;
inline constexpr u32 kMaxCapabilities = 16;
inline constexpr u32 kMaxCacheEntries = 64;
inline constexpr u32 kMaxStorageFiles = 64;
inline constexpr u32 kMaxStorageBytes = 256;

enum class VfsError : std::uint8_t {
    None,
    InvalidPath,
    PathEscape,
    InvalidMount,
    MountCollision,
    NotFound,
    Shadowed,
    Ambiguous,
    CapabilityDenied,
    ReadOnly,
    StaleMount,
    BufferFull,
    InvalidArgument,
    InternalFailure
};

struct VfsPath {
    std::array<char, kMaxPathBytes> bytes{};
    u32 length{0};
};

struct MountId {
    u64 value{0};
};

[[nodiscard]] constexpr bool valid(MountId id) noexcept {
    return id.value != 0;
}

struct WorkspaceId {
    u64 value{0};
};

[[nodiscard]] constexpr bool valid(WorkspaceId id) noexcept {
    return id.value != 0;
}

}  // namespace stormline::data::vfs

#endif  // STORMLINE_DATA_VFS_VFS_TYPES_HPP
