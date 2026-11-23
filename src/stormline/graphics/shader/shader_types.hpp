#ifndef STORMLINE_GRAPHICS_SHADER_SHADER_TYPES_HPP
#define STORMLINE_GRAPHICS_SHADER_SHADER_TYPES_HPP

#include <array>
#include <cstdint>
#include <string_view>

namespace stormline::graphics::shader {

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

inline constexpr u32 kMaxSourceBytes = 4096;
inline constexpr u32 kMaxSourceLines = 256;
inline constexpr u32 kMaxNameBytes = 32;
inline constexpr u32 kMaxPathBytes = 64;
inline constexpr u32 kMaxBindings = 64;
inline constexpr u32 kMaxInputs = 32;
inline constexpr u32 kMaxOutputs = 32;
inline constexpr u32 kMaxUniforms = 32;
inline constexpr u32 kMaxStaticSwitches = 16;
inline constexpr u32 kMaxVariants = 64;
inline constexpr u32 kMaxCacheEntries = 64;
inline constexpr u32 kMaxDependencies = 32;
inline constexpr u32 kMaxDiagnostics = 16;

enum class ShaderError : std::uint8_t {
    None,
    InvalidArgument,
    EmptySource,
    SourceTooLarge,
    TooManyLines,
    PathTooLong,
    InvalidToken,
    UnexpectedToken,
    InvalidName,
    InvalidModule,
    MissingStage,
    DuplicateStage,
    UnknownType,
    DuplicateBinding,
    StageRestriction,
    CapacityFull,
    VariantLimit,
    CacheFull,
    CacheMiss,
    CacheMismatch,
    StaleRevision
};

enum class ShaderStage : std::uint8_t { Vertex, Fragment, Compute };
enum class BindingKind : std::uint8_t { Input, Output, Uniform };
enum class ShaderType : std::uint8_t {
    Float, Vec2, Vec3, Vec4, Mat3, Mat4, Int, Uint, Bool
};

struct Name {
    std::array<char, kMaxNameBytes> text{};
    u8 length{0};
};

struct SourcePath {
    std::array<char, kMaxPathBytes> text{};
    u8 length{0};
};

[[nodiscard]] inline bool is_identifier_start(char value) noexcept {
    return (value >= 'A' && value <= 'Z') || (value >= 'a' && value <= 'z')
        || value == '_';
}

[[nodiscard]] inline bool is_identifier_body(char value) noexcept {
    return is_identifier_start(value) || (value >= '0' && value <= '9');
}

[[nodiscard]] inline ShaderError make_name(
    std::string_view text, Name& out) noexcept {
    out = Name{};
    if (text.empty() || text.size() > kMaxNameBytes
        || !is_identifier_start(text[0])) {
        return ShaderError::InvalidName;
    }
    for (const char value : text) {
        if (!is_identifier_body(value)) {
            return ShaderError::InvalidName;
        }
    }
    out.length = static_cast<u8>(text.size());
    for (u32 index = 0; index < text.size(); ++index) {
        out.text[index] = text[index];
    }
    return ShaderError::None;
}

[[nodiscard]] inline std::string_view name_view(const Name& name) noexcept {
    return std::string_view(name.text.data(), name.length);
}

[[nodiscard]] inline ShaderError make_source_path(
    std::string_view text, SourcePath& out) noexcept {
    out = SourcePath{};
    if (text.empty()) {
        return ShaderError::InvalidArgument;
    }
    if (text.size() > kMaxPathBytes) {
        return ShaderError::PathTooLong;
    }
    for (const char value : text) {
        const u8 byte = static_cast<u8>(value);
        if (byte < 0x20 || byte == 0x7F) {
            return ShaderError::InvalidArgument;
        }
    }
    out.length = static_cast<u8>(text.size());
    for (u32 index = 0; index < text.size(); ++index) {
        out.text[index] = text[index];
    }
    return ShaderError::None;
}

[[nodiscard]] inline std::string_view path_view(const SourcePath& path) noexcept {
    return std::string_view(path.text.data(), path.length);
}

[[nodiscard]] inline const char* shader_error_name(ShaderError error) noexcept {
    switch (error) {
        case ShaderError::None: return "None";
        case ShaderError::InvalidArgument: return "InvalidArgument";
        case ShaderError::EmptySource: return "EmptySource";
        case ShaderError::SourceTooLarge: return "SourceTooLarge";
        case ShaderError::TooManyLines: return "TooManyLines";
        case ShaderError::PathTooLong: return "PathTooLong";
        case ShaderError::InvalidToken: return "InvalidToken";
        case ShaderError::UnexpectedToken: return "UnexpectedToken";
        case ShaderError::InvalidName: return "InvalidName";
        case ShaderError::InvalidModule: return "InvalidModule";
        case ShaderError::MissingStage: return "MissingStage";
        case ShaderError::DuplicateStage: return "DuplicateStage";
        case ShaderError::UnknownType: return "UnknownType";
        case ShaderError::DuplicateBinding: return "DuplicateBinding";
        case ShaderError::StageRestriction: return "StageRestriction";
        case ShaderError::CapacityFull: return "CapacityFull";
        case ShaderError::VariantLimit: return "VariantLimit";
        case ShaderError::CacheFull: return "CacheFull";
        case ShaderError::CacheMiss: return "CacheMiss";
        case ShaderError::CacheMismatch: return "CacheMismatch";
        case ShaderError::StaleRevision: return "StaleRevision";
    }
    return "Unknown";
}

[[nodiscard]] inline u32 shader_type_size(ShaderType type) noexcept {
    switch (type) {
        case ShaderType::Float:
        case ShaderType::Int:
        case ShaderType::Uint:
        case ShaderType::Bool: return 4;
        case ShaderType::Vec2: return 8;
        case ShaderType::Vec3: return 12;
        case ShaderType::Vec4: return 16;
        case ShaderType::Mat3: return 48;
        case ShaderType::Mat4: return 64;
    }
    return 0;
}

[[nodiscard]] inline u32 shader_type_alignment(ShaderType type) noexcept {
    switch (type) {
        case ShaderType::Float:
        case ShaderType::Int:
        case ShaderType::Uint:
        case ShaderType::Bool: return 4;
        case ShaderType::Vec2: return 8;
        case ShaderType::Vec3:
        case ShaderType::Vec4:
        case ShaderType::Mat3:
        case ShaderType::Mat4: return 16;
    }
    return 0;
}

}  // namespace stormline::graphics::shader

#endif  // STORMLINE_GRAPHICS_SHADER_SHADER_TYPES_HPP
