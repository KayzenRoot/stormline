#include "stormline/core/internal/process_paths.hpp"

#include <new>
#include <string_view>
#include <utility>

namespace stormline::core::internal {
namespace {

thread_local int forced_error_value = 0;

std::error_code forced_error() noexcept {
    if (forced_error_value == 0) {
        return {};
    }
    return {forced_error_value, std::generic_category()};
}

bool contains_nul(const std::filesystem::path& path) noexcept {
    const auto& native = path.native();
    return native.find(static_cast<std::filesystem::path::value_type>(0)) != native.npos;
}

bool is_valid_utf8(std::string_view text) noexcept {
    const auto* bytes = reinterpret_cast<const unsigned char*>(text.data());
    std::size_t index = 0;
    while (index < text.size()) {
        const unsigned char lead = bytes[index];
        if (lead <= 0x7FU) {
            ++index;
            continue;
        }

        std::size_t extra = 0;
        if (lead >= 0xC2U && lead <= 0xDFU) {
            extra = 1;
        } else if (lead >= 0xE0U && lead <= 0xEFU) {
            extra = 2;
        } else if (lead >= 0xF0U && lead <= 0xF4U) {
            extra = 3;
        } else {
            return false;
        }

        if (index + extra >= text.size()) {
            return false;
        }
        for (std::size_t offset = 1; offset <= extra; ++offset) {
            if ((bytes[index + offset] & 0xC0U) != 0x80U) {
                return false;
            }
        }
        if (lead == 0xE0U && bytes[index + 1] < 0xA0U) {
            return false;
        }
        if (lead == 0xEDU && bytes[index + 1] > 0x9FU) {
            return false;
        }
        if (lead == 0xF0U && bytes[index + 1] < 0x90U) {
            return false;
        }
        if (lead == 0xF4U && bytes[index + 1] > 0x8FU) {
            return false;
        }
        index += extra + 1;
    }
    return true;
}

PathError path_encoding_error(const std::filesystem::path& path) noexcept {
    if (path.empty() || contains_nul(path)) {
        return PathError::InvalidPath;
    }
    try {
        const std::u8string encoded = path.u8string();
        const std::string_view bytes(reinterpret_cast<const char*>(encoded.data()), encoded.size());
        return is_valid_utf8(bytes) ? PathError::None : PathError::InvalidPath;
    } catch (const std::bad_alloc&) {
        return PathError::AllocationFailed;
    } catch (const std::system_error&) {
        return PathError::InvalidPath;
    } catch (...) {
        return PathError::InternalFailure;
    }
}

PathError map_error(const std::error_code& error, PathError fallback) noexcept {
    if (error == std::errc::permission_denied || error == std::errc::operation_not_permitted) {
        return PathError::AccessDenied;
    }
    if (error == std::errc::invalid_argument || error == std::errc::filename_too_long) {
        return PathError::InvalidPath;
    }
    if (error == std::errc::no_such_file_or_directory || error == std::errc::not_a_directory) {
        if (fallback == PathError::CurrentDirectoryUnavailable
            || fallback == PathError::TemporaryDirectoryUnavailable) {
            return fallback;
        }
        return PathError::NotFound;
    }
    return fallback;
}

bool is_within(const std::filesystem::path& root, const std::filesystem::path& candidate) noexcept {
    auto root_part = root.begin();
    auto candidate_part = candidate.begin();
    for (; root_part != root.end(); ++root_part, ++candidate_part) {
        if (candidate_part == candidate.end() || *root_part != *candidate_part) {
            return false;
        }
    }
    return true;
}

} // namespace

PathResult current_directory() noexcept {
    try {
        if (const auto forced = forced_error(); forced) {
            return {map_error(forced, PathError::CurrentDirectoryUnavailable), {}};
        }
        std::error_code error;
        const auto path = std::filesystem::current_path(error);
        if (error) {
            return {map_error(error, PathError::CurrentDirectoryUnavailable), {}};
        }
        return {PathError::None, path};
    } catch (const std::bad_alloc&) {
        return {PathError::AllocationFailed, {}};
    } catch (...) {
        return {PathError::InternalFailure, {}};
    }
}

PathResult temporary_directory() noexcept {
    try {
        if (const auto forced = forced_error(); forced) {
            return {map_error(forced, PathError::TemporaryDirectoryUnavailable), {}};
        }
        std::error_code error;
        const auto path = std::filesystem::temp_directory_path(error);
        if (error) {
            return {map_error(error, PathError::TemporaryDirectoryUnavailable), {}};
        }
        return {PathError::None, path};
    } catch (const std::bad_alloc&) {
        return {PathError::AllocationFailed, {}};
    } catch (...) {
        return {PathError::InternalFailure, {}};
    }
}

PathResult normalize_absolute(const std::filesystem::path& input) noexcept {
    try {
        if (const auto encoding = path_encoding_error(input); encoding != PathError::None) {
            return {encoding, {}};
        }
        if (const auto forced = forced_error(); forced) {
            return {map_error(forced, PathError::InternalFailure), {}};
        }
        std::error_code error;
        const auto absolute = std::filesystem::absolute(input, error);
        if (error) {
            return {map_error(error, PathError::InternalFailure), {}};
        }
        auto canonical = std::filesystem::weakly_canonical(absolute, error);
        if (error) {
            return {map_error(error, PathError::InternalFailure), {}};
        }
        return {PathError::None, std::move(canonical)};
    } catch (const std::bad_alloc&) {
        return {PathError::AllocationFailed, {}};
    } catch (...) {
        return {PathError::InternalFailure, {}};
    }
}

PathResult normalize_within_root(
    const std::filesystem::path& root,
    const std::filesystem::path& candidate) noexcept {
    try {
        if (const auto encoding = path_encoding_error(root); encoding != PathError::None) {
            return {encoding, {}};
        }
        if (const auto encoding = path_encoding_error(candidate); encoding != PathError::None) {
            return {encoding, {}};
        }
        if (const auto forced = forced_error(); forced) {
            return {map_error(forced, PathError::NotFound), {}};
        }

        std::error_code error;
        const auto root_status = std::filesystem::status(root, error);
        if (root_status.type() == std::filesystem::file_type::not_found) {
            return {PathError::NotFound, {}};
        }
        if (error) {
            return {map_error(error, PathError::NotFound), {}};
        }
        if (!std::filesystem::is_directory(root_status)) {
            return {PathError::InvalidPath, {}};
        }

        const auto root_absolute = std::filesystem::absolute(root, error);
        if (error) {
            return {map_error(error, PathError::InternalFailure), {}};
        }
        auto root_canonical = std::filesystem::weakly_canonical(root_absolute, error);
        if (error) {
            return {map_error(error, PathError::InternalFailure), {}};
        }

        const auto resolved = candidate.is_absolute() ? candidate : (root_canonical / candidate);
        std::error_code probe_error;
        (void)std::filesystem::status(resolved, probe_error);
        if (probe_error == std::errc::permission_denied) {
            return {PathError::AccessDenied, {}};
        }
        auto candidate_canonical = std::filesystem::weakly_canonical(resolved, error);
        if (error) {
            return {map_error(error, PathError::NotFound), {}};
        }
        if (!is_within(root_canonical, candidate_canonical)) {
            return {PathError::PathTraversalRejected, {}};
        }
        return {PathError::None, std::move(candidate_canonical)};
    } catch (const std::bad_alloc&) {
        return {PathError::AllocationFailed, {}};
    } catch (...) {
        return {PathError::InternalFailure, {}};
    }
}

PathTextResult to_utf8(const std::filesystem::path& input) noexcept {
    try {
        if (input.empty() || contains_nul(input)) {
            return {PathError::InvalidPath, {}};
        }
        const std::u8string encoded = input.u8string();
        std::string bytes(reinterpret_cast<const char*>(encoded.data()), encoded.size());
        if (!is_valid_utf8(bytes)) {
            return {PathError::InvalidPath, {}};
        }
        return {PathError::None, std::move(bytes)};
    } catch (const std::bad_alloc&) {
        return {PathError::AllocationFailed, {}};
    } catch (const std::system_error&) {
        return {PathError::InvalidPath, {}};
    } catch (...) {
        return {PathError::InternalFailure, {}};
    }
}

void ProcessPathsTestAccess::force_error(std::errc error) noexcept {
    forced_error_value = static_cast<int>(error);
}

void ProcessPathsTestAccess::clear_forced_error() noexcept {
    forced_error_value = 0;
}

} // namespace stormline::core::internal
