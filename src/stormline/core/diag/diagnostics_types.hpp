#ifndef STORMLINE_CORE_DIAG_DIAGNOSTICS_TYPES_HPP
#define STORMLINE_CORE_DIAG_DIAGNOSTICS_TYPES_HPP

#include <array>
#include <cstddef>
#include <cstdint>
#include <string_view>

namespace stormline::core::diag {

using u8 = std::uint8_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using i64 = std::int64_t;
using f64 = double;

inline constexpr u32 kDiagnosticsSchemaVersion = 1;
inline constexpr u32 kMaxAttributes = 8;
inline constexpr u32 kLogBufferCapacity = 128;
inline constexpr u32 kTraceBufferCapacity = 128;
inline constexpr u32 kCounterCapacity = 64;
inline constexpr u32 kCrashPrecedingRecords = 16;
inline constexpr u32 kProfileCapacity = 64;
inline constexpr u32 kTelemetryCapacity = 64;
inline constexpr u32 kMaxMessageBytes = 192;
inline constexpr u32 kMaxNameBytes = 96;
inline constexpr u32 kMaxAttributeKeyBytes = 32;
inline constexpr u32 kMaxAttributeValueBytes = 96;

enum class DiagnosticSeverity : u8 {
    Trace,
    Debug,
    Info,
    Warn,
    Error,
    Fatal
};

enum class DiagnosticReason : u8 {
    None,
    InvalidInput,
    ProjectAssetError,
    AllocationPressure,
    FrameBudgetOverrun,
    JobDeadlineMiss,
    DeviceLost,
    AudioUnderrun,
    NetworkPeerError,
    CrashUnhandled,
    BufferFull,
    Unsupported,
    NotEnabled,
    InternalFailure
};

enum class DiagnosticError : u8 {
    None,
    InvalidArgument,
    OutOfRange,
    BufferFull,
    NotEnabled,
    Shutdown,
    Overflow,
    NonFinite,
    Unsupported,
    InternalFailure
};

struct BuildId {
    u64 high{0};
    u64 low{0};
};

struct TraceId {
    u64 high{0};
    u64 low{0};
};

struct SpanId {
    u64 value{0};
};

struct SessionId {
    u64 value{0};
};

struct DiagnosticTime {
    i64 monotonic_ns{0};
};

template <typename T>
struct DiagResult {
    T value{};
    DiagnosticError error{DiagnosticError::None};

    [[nodiscard]] constexpr bool ok() const noexcept {
        return error == DiagnosticError::None;
    }
};

[[nodiscard]] constexpr bool valid(BuildId id) noexcept {
    return id.high != 0 || id.low != 0;
}

[[nodiscard]] constexpr bool valid(TraceId id) noexcept {
    return id.high != 0 || id.low != 0;
}

[[nodiscard]] constexpr bool valid(SpanId id) noexcept {
    return id.value != 0;
}

[[nodiscard]] constexpr bool valid(SessionId id) noexcept {
    return id.value != 0;
}

template <u32 N>
struct BoundedText {
    std::array<char, N> bytes{};
    u32 length{0};
};

template <u32 N>
[[nodiscard]] inline std::string_view view(const BoundedText<N>& text) noexcept {
    return std::string_view(text.bytes.data(), text.length);
}

template <u32 N>
[[nodiscard]] inline DiagnosticError assign_text(
    BoundedText<N>& out, std::string_view text) noexcept {
    if (text.size() > static_cast<std::size_t>(N)
        || text.find('\0') != std::string_view::npos) {
        return DiagnosticError::InvalidArgument;
    }
    out.bytes.fill('\0');
    for (std::size_t index = 0; index < text.size(); ++index) {
        out.bytes[index] = text[index];
    }
    out.length = static_cast<u32>(text.size());
    return DiagnosticError::None;
}

}  // namespace stormline::core::diag

#endif  // STORMLINE_CORE_DIAG_DIAGNOSTICS_TYPES_HPP
