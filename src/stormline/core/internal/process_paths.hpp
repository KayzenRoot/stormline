#pragma once

#include <cstdint>
#include <filesystem>
#include <string>
#include <system_error>

namespace stormline::core::internal {

// Internal-only typed result for the read-only process-path queries. This is
// not a public API, ABI or plugin boundary.
enum class PathError : std::uint8_t {
    None,
    CurrentDirectoryUnavailable,
    TemporaryDirectoryUnavailable,
    NotFound,
    AccessDenied,
    InvalidPath,
    PathTraversalRejected,
    AllocationFailed,
    InternalFailure
};

struct PathResult final {
    PathError error{PathError::None};
    std::filesystem::path path{};

    [[nodiscard]] bool ok() const noexcept { return error == PathError::None; }
};

struct PathTextResult final {
    PathError error{PathError::None};
    std::string utf8{};

    [[nodiscard]] bool ok() const noexcept { return error == PathError::None; }
};

[[nodiscard]] PathResult current_directory() noexcept;
[[nodiscard]] PathResult temporary_directory() noexcept;
[[nodiscard]] PathResult normalize_absolute(const std::filesystem::path& input) noexcept;
[[nodiscard]] PathResult normalize_within_root(
    const std::filesystem::path& root,
    const std::filesystem::path& candidate) noexcept;
[[nodiscard]] PathTextResult to_utf8(const std::filesystem::path& input) noexcept;

// Internal-only deterministic error-injection seam for tests. It is
// thread-local, defaults to no injection and is not part of any ABI.
struct ProcessPathsTestAccess final {
    static void force_error(std::errc error) noexcept;
    static void clear_forced_error() noexcept;
};

} // namespace stormline::core::internal
