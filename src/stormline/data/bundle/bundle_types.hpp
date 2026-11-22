#ifndef STORMLINE_DATA_BUNDLE_BUNDLE_TYPES_HPP
#define STORMLINE_DATA_BUNDLE_BUNDLE_TYPES_HPP

#include "stormline/data/registry/registry_types.hpp"

#include <cstdint>

namespace stormline::data::bundle {

using u32 = std::uint32_t;
using u64 = std::uint64_t;
using u8 = std::uint8_t;

inline constexpr u32 kMaxCookAssets = 64;
inline constexpr u32 kMaxChunks = 64;
inline constexpr u32 kMaxChunkBytes = 256;
inline constexpr u32 kMaxManifestEntries = 64;
inline constexpr u32 kMaxStreamBytes = 1024;
inline constexpr u32 kMaxWarnings = 8;

enum class BundleError : std::uint8_t {
    None,
    InvalidArgument,
    InvalidTarget,
    UnsupportedFeature,
    DuplicateId,
    NotFound,
    CapacityFull,
    RangeOverflow,
    ChunkOverlap,
    StaleGeneration,
    FingerprintMismatch,
    CompressionLimit,
    PatchConflict,
    BufferFull
};

enum class TargetOs : std::uint8_t {
    Windows,
    Linux,
    Macos,
    Web
};

enum class TargetArch : std::uint8_t {
    X64,
    Arm64,
    Wasm
};

struct TargetProfile {
    u32 profile_id{0};
    TargetOs os{TargetOs::Windows};
    TargetArch arch{TargetArch::X64};
    u32 feature_flags{0};
    u32 quality_tier{0};
};

struct CookAsset {
    registry::AssetId asset{};
    u32 source_revision{0};
    u32 flags{0};
};

struct CookPlan {
    u32 profile_id{0};
    u32 asset_count{0};
    u32 estimated_bytes{0};
    u32 warning_count{0};
};

}  // namespace stormline::data::bundle

#endif  // STORMLINE_DATA_BUNDLE_BUNDLE_TYPES_HPP
