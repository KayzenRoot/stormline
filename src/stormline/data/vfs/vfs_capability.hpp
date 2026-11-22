#ifndef STORMLINE_DATA_VFS_VFS_CAPABILITY_HPP
#define STORMLINE_DATA_VFS_VFS_CAPABILITY_HPP

#include "stormline/data/vfs/vfs_types.hpp"

#include <array>

namespace stormline::data::vfs {

struct AccessCapability {
    WorkspaceId workspace{};
    MountId mount{};
    bool read{false};
};

class CapabilitySet final {
public:
    CapabilitySet() noexcept = default;

    [[nodiscard]] VfsError grant(const AccessCapability& capability) noexcept {
        if (!valid(capability.workspace) || !valid(capability.mount)
            || !capability.read) {
            return VfsError::InvalidArgument;
        }
        for (u32 index = 0; index < size_; ++index) {
            if (capabilities_[index].workspace.value == capability.workspace.value
                && capabilities_[index].mount.value == capability.mount.value) {
                capabilities_[index] = capability;
                return VfsError::None;
            }
        }
        if (size_ >= kMaxCapabilities) {
            return VfsError::BufferFull;
        }
        capabilities_[size_] = capability;
        ++size_;
        return VfsError::None;
    }

    [[nodiscard]] VfsError revoke(WorkspaceId workspace, MountId mount) noexcept {
        for (u32 index = 0; index < size_; ++index) {
            if (capabilities_[index].workspace.value == workspace.value
                && capabilities_[index].mount.value == mount.value) {
                for (u32 next = index + 1; next < size_; ++next) {
                    capabilities_[next - 1] = capabilities_[next];
                }
                --size_;
                return VfsError::None;
            }
        }
        return VfsError::NotFound;
    }

    [[nodiscard]] bool allows(WorkspaceId workspace, MountId mount) const noexcept {
        if (!valid(workspace) || !valid(mount)) {
            return false;
        }
        for (u32 index = 0; index < size_; ++index) {
            if (capabilities_[index].workspace.value == workspace.value
                && capabilities_[index].mount.value == mount.value
                && capabilities_[index].read) {
                return true;
            }
        }
        return false;
    }

    [[nodiscard]] u32 size() const noexcept {
        return size_;
    }

private:
    std::array<AccessCapability, kMaxCapabilities> capabilities_{};
    u32 size_{0};
};

}  // namespace stormline::data::vfs

#endif  // STORMLINE_DATA_VFS_VFS_CAPABILITY_HPP
