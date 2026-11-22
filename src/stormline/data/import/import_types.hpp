#ifndef STORMLINE_DATA_IMPORT_IMPORT_TYPES_HPP
#define STORMLINE_DATA_IMPORT_IMPORT_TYPES_HPP

#include <array>
#include <cstdint>

namespace stormline::data::imports {

using u32 = std::uint32_t;
using u64 = std::uint64_t;
using u8 = std::uint8_t;

inline constexpr u32 kMaxImporters = 16;
inline constexpr u32 kMaxSignatureBytes = 16;
inline constexpr u32 kMaxReceipts = 64;
inline constexpr u32 kMaxReceiptWarnings = 8;
inline constexpr u32 kMaxTextureDimension = 16384;
inline constexpr u32 kMaxMipLevels = 15;
inline constexpr u32 kMaxAnimationJoints = 256;
inline constexpr u32 kMaxAnimationTracks = 256;
inline constexpr u32 kMaxAnimationKeyframes = 4096;
inline constexpr u32 kMaxAnimationDurationMs = 3600000;
inline constexpr u32 kMaxAudioFrames = 10000000;

enum class ImportError : std::uint8_t {
    None,
    InvalidArgument,
    InvalidPath,
    UnknownFormat,
    UnsupportedFormat,
    SignatureTruncated,
    DuplicateImporter,
    DuplicateReceipt,
    InvalidTexture,
    InvalidAnimation,
    InvalidAudio,
    CapacityFull,
    NotFound,
    AssetMismatch,
    BufferFull
};

enum class FormatId : std::uint8_t {
    Unknown,
    Png,
    Jpeg,
    Glb,
    Wav
};

enum class ArtifactType : std::uint8_t {
    Unknown,
    Texture2D,
    Mesh,
    Animation,
    Audio,
    Metadata
};

enum class ValidationStatus : std::uint8_t {
    Valid,
    Invalid
};

struct ImporterDescriptor {
    u32 importer_id{0};
    u32 version{0};
    FormatId format{FormatId::Unknown};
    ArtifactType artifact{ArtifactType::Unknown};
    std::array<char, 8> extension{};
    u32 extension_length{0};
};

}  // namespace stormline::data::imports

#endif  // STORMLINE_DATA_IMPORT_IMPORT_TYPES_HPP
