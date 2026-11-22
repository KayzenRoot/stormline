#ifndef STORMLINE_DATA_VFS_VFS_CACHE_HPP
#define STORMLINE_DATA_VFS_VFS_CACHE_HPP

#include "stormline/data/vfs/vfs_path.hpp"

#include <array>
#include <span>

namespace stormline::data::vfs {

struct CacheKey {
    MountId mount{};
    u64 generation{0};
    VfsPath path{};
};

class PathCache final {
public:
    PathCache() noexcept = default;

    [[nodiscard]] VfsError put(
        MountId mount, u64 generation, const VfsPath& path,
        std::span<const std::uint8_t> bytes) noexcept {
        if (!valid(mount) || generation == 0 || bytes.size() > kMaxStorageBytes) {
            return VfsError::InvalidArgument;
        }
        for (u32 index = 0; index < size_; ++index) {
            if (same_key(entries_[index].key, mount, generation, path)) {
                copy_bytes(entries_[index], bytes);
                return VfsError::None;
            }
        }
        if (size_ >= kMaxCacheEntries) {
            ++dropped_;
            return VfsError::BufferFull;
        }
        Entry& entry = entries_[size_];
        entry.key = CacheKey{mount, generation, path};
        copy_bytes(entry, bytes);
        ++size_;
        return VfsError::None;
    }

    [[nodiscard]] VfsError get(
        MountId mount, u64 generation, const VfsPath& path,
        std::span<std::uint8_t> output, u32& out_size) noexcept {
        out_size = 0;
        if (!valid(mount) || generation == 0) {
            return VfsError::InvalidArgument;
        }
        u32 stale_index = kMaxCacheEntries;
        for (u32 index = 0; index < size_; ++index) {
            const Entry& entry = entries_[index];
            if (entry.key.mount.value == mount.value
                && view(entry.key.path) == view(path)) {
                if (entry.key.generation != generation) {
                    stale_index = index;
                    continue;
                }
                out_size = entry.size;
                if (output.size() < entry.size) {
                    return VfsError::BufferFull;
                }
                for (u32 offset = 0; offset < entry.size; ++offset) {
                    output[offset] = entry.bytes[offset];
                }
                return VfsError::None;
            }
        }
        return stale_index == kMaxCacheEntries ? VfsError::NotFound : VfsError::StaleMount;
    }

    [[nodiscard]] u32 invalidate_mount(MountId mount) noexcept {
        u32 removed = 0;
        u32 index = 0;
        while (index < size_) {
            if (entries_[index].key.mount.value == mount.value) {
                for (u32 next = index + 1; next < size_; ++next) {
                    entries_[next - 1] = entries_[next];
                }
                --size_;
                ++removed;
            } else {
                ++index;
            }
        }
        return removed;
    }

    void clear() noexcept {
        size_ = 0;
        dropped_ = 0;
    }

    [[nodiscard]] u32 size() const noexcept { return size_; }
    [[nodiscard]] u64 dropped() const noexcept { return dropped_; }

private:
    struct Entry {
        CacheKey key{};
        std::array<std::uint8_t, kMaxStorageBytes> bytes{};
        u32 size{0};
    };

    static bool same_key(
        const CacheKey& key, MountId mount, u64 generation,
        const VfsPath& path) noexcept {
        return key.mount.value == mount.value && key.generation == generation
            && view(key.path) == view(path);
    }

    static void copy_bytes(Entry& entry, std::span<const std::uint8_t> bytes) noexcept {
        entry.size = static_cast<u32>(bytes.size());
        for (u32 index = 0; index < entry.size; ++index) {
            entry.bytes[index] = bytes[index];
        }
    }

    std::array<Entry, kMaxCacheEntries> entries_{};
    u32 size_{0};
    u64 dropped_{0};
};

}  // namespace stormline::data::vfs

#endif  // STORMLINE_DATA_VFS_VFS_CACHE_HPP
