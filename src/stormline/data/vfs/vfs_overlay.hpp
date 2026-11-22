#ifndef STORMLINE_DATA_VFS_VFS_OVERLAY_HPP
#define STORMLINE_DATA_VFS_VFS_OVERLAY_HPP

#include "stormline/data/vfs/vfs_mount.hpp"

namespace stormline::data::vfs {

struct LookupResult {
    VfsError status{VfsError::NotFound};
    MountId mount{};
    VfsPath relative{};
    u64 generation{0};
    u32 shadowed_count{0};
};

[[nodiscard]] inline VfsError resolve(
    const MountTable& mounts, const VfsPath& path, LookupResult& out) noexcept {
    MountInfo selected{};
    bool found = false;
    u32 matches = 0;
    for (u32 index = 0; index < mounts.size(); ++index) {
        MountInfo candidate{};
        if (!mounts.at(index, candidate) || !is_prefix(candidate.root, path)) {
            continue;
        }
        ++matches;
        if (!found || candidate.priority > selected.priority
            || (candidate.priority == selected.priority
                && candidate.id.value < selected.id.value)) {
            selected = candidate;
            found = true;
        }
    }
    if (!found) {
        out = LookupResult{};
        return VfsError::NotFound;
    }

    LookupResult result{};
    result.status = VfsError::None;
    result.mount = selected.id;
    result.generation = selected.generation;
    result.shadowed_count = matches - 1;
    if (selected.root.length == 0) {
        result.relative = path;
    } else {
        const u32 offset = selected.root.length + 1;
        result.relative.length = path.length - offset;
        for (u32 index = 0; index < result.relative.length; ++index) {
            result.relative.bytes[index] = path.bytes[offset + index];
        }
    }
    out = result;
    return VfsError::None;
}

}  // namespace stormline::data::vfs

#endif  // STORMLINE_DATA_VFS_VFS_OVERLAY_HPP
