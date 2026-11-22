#ifndef STORMLINE_DATA_VFS_VFS_PATH_HPP
#define STORMLINE_DATA_VFS_VFS_PATH_HPP

#include "stormline/data/vfs/vfs_types.hpp"

#include <cstddef>

namespace stormline::data::vfs {

namespace detail {

[[nodiscard]] constexpr char lower_ascii(char value) noexcept {
    return (value >= 'A' && value <= 'Z') ? static_cast<char>(value - 'A' + 'a') : value;
}

[[nodiscard]] inline bool equals_ignore_case(std::string_view lhs, std::string_view rhs) noexcept {
    if (lhs.size() != rhs.size()) {
        return false;
    }
    for (std::size_t index = 0; index < lhs.size(); ++index) {
        if (lower_ascii(lhs[index]) != lower_ascii(rhs[index])) {
            return false;
        }
    }
    return true;
}

[[nodiscard]] inline bool reserved_component(std::string_view component) noexcept {
    const std::size_t dot = component.find('.');
    const std::string_view base = dot == std::string_view::npos
        ? component
        : component.substr(0, dot);
    if (equals_ignore_case(base, "con") || equals_ignore_case(base, "prn")
        || equals_ignore_case(base, "aux") || equals_ignore_case(base, "nul")) {
        return true;
    }
    if (base.size() == 4 && (equals_ignore_case(base.substr(0, 3), "com")
                             || equals_ignore_case(base.substr(0, 3), "lpt"))) {
        const char digit = base[3];
        return digit >= '1' && digit <= '9';
    }
    return false;
}

}  // namespace detail

[[nodiscard]] inline std::string_view view(const VfsPath& path) noexcept {
    return std::string_view(path.bytes.data(), path.length);
}

[[nodiscard]] constexpr bool empty(const VfsPath& path) noexcept {
    return path.length == 0;
}

[[nodiscard]] inline VfsError make_path(std::string_view text, VfsPath& out) noexcept {
    if (text.empty()) {
        out = VfsPath{};
        return VfsError::None;
    }
    if (text.size() > kMaxPathBytes) {
        return VfsError::InvalidPath;
    }
    if (text.front() == '/' || text.back() == '/') {
        return VfsError::PathEscape;
    }
    if (text.find('\\') != std::string_view::npos
        || text.find(':') != std::string_view::npos) {
        return VfsError::PathEscape;
    }
    for (const char byte : text) {
        if (byte == '\0' || static_cast<unsigned char>(byte) < 0x20
            || static_cast<unsigned char>(byte) > 0x7E) {
            return VfsError::InvalidPath;
        }
    }

    VfsPath path{};
    u32 length = 0;
    u32 component_start = 0;
    const u32 text_size = static_cast<u32>(text.size());
    for (u32 index = 0; index <= text_size; ++index) {
        if (index == text_size || text[index] == '/') {
            const u32 component_length = index - component_start;
            if (component_length == 0 || component_length > kMaxComponentBytes) {
                return VfsError::InvalidPath;
            }
            const std::string_view component =
                text.substr(component_start, component_length);
            if (component == "." || component == "..") {
                return VfsError::PathEscape;
            }
            if (component.back() == '.' || component.back() == ' ') {
                return VfsError::InvalidPath;
            }
            if (detail::reserved_component(component)) {
                return VfsError::InvalidPath;
            }
            for (u32 offset = 0; offset < component_length; ++offset) {
                path.bytes[length++] = component[offset];
            }
            if (index != text_size) {
                path.bytes[length++] = '/';
            }
            component_start = index + 1;
        }
    }
    path.length = length;
    out = path;
    return VfsError::None;
}

[[nodiscard]] inline bool is_prefix(const VfsPath& prefix, const VfsPath& path) noexcept {
    if (prefix.length == 0) {
        return true;
    }
    if (prefix.length > path.length) {
        return false;
    }
    for (u32 index = 0; index < prefix.length; ++index) {
        if (prefix.bytes[index] != path.bytes[index]) {
            return false;
        }
    }
    return prefix.length == path.length || path.bytes[prefix.length] == '/';
}

}  // namespace stormline::data::vfs

#endif  // STORMLINE_DATA_VFS_VFS_PATH_HPP
