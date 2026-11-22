#ifndef STORMLINE_DATA_VFS_VFS_MOUNT_HPP
#define STORMLINE_DATA_VFS_VFS_MOUNT_HPP

#include "stormline/data/vfs/vfs_path.hpp"

#include <array>

namespace stormline::data::vfs {

enum class MountMode : std::uint8_t {
    ReadOnly
};

struct MountInfo {
    MountId id{};
    VfsPath root{};
    u32 priority{0};
    MountMode mode{MountMode::ReadOnly};
    u64 generation{0};
};

class MountTable final {
public:
    MountTable() noexcept = default;

    [[nodiscard]] VfsError add(const MountInfo& mount) noexcept {
        if (!valid(mount.id) || mount.mode != MountMode::ReadOnly) {
            return VfsError::InvalidMount;
        }
        for (u32 index = 0; index < size_; ++index) {
            if (mounts_[index].id.value == mount.id.value
                || view(mounts_[index].root) == view(mount.root)) {
                return VfsError::MountCollision;
            }
        }
        if (size_ >= kMaxMounts) {
            return VfsError::BufferFull;
        }
        MountInfo stored = mount;
        stored.generation = ++generation_;
        mounts_[size_] = stored;
        ++size_;
        return VfsError::None;
    }

    [[nodiscard]] VfsError remove(MountId id) noexcept {
        for (u32 index = 0; index < size_; ++index) {
            if (mounts_[index].id.value == id.value) {
                for (u32 next = index + 1; next < size_; ++next) {
                    mounts_[next - 1] = mounts_[next];
                }
                --size_;
                ++generation_;
                return VfsError::None;
            }
        }
        return VfsError::NotFound;
    }

    [[nodiscard]] bool find(MountId id, MountInfo& out) const noexcept {
        for (u32 index = 0; index < size_; ++index) {
            if (mounts_[index].id.value == id.value) {
                out = mounts_[index];
                return true;
            }
        }
        return false;
    }

    [[nodiscard]] bool at(u32 index, MountInfo& out) const noexcept {
        if (index >= size_) {
            return false;
        }
        out = mounts_[index];
        return true;
    }

    [[nodiscard]] u32 size() const noexcept {
        return size_;
    }

    [[nodiscard]] u64 generation() const noexcept {
        return generation_;
    }

    void clear() noexcept {
        size_ = 0;
        ++generation_;
    }

private:
    std::array<MountInfo, kMaxMounts> mounts_{};
    u32 size_{0};
    u64 generation_{0};
};

}  // namespace stormline::data::vfs

#endif  // STORMLINE_DATA_VFS_VFS_MOUNT_HPP
