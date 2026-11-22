#ifndef STORMLINE_DATA_VFS_VFS_STORAGE_HPP
#define STORMLINE_DATA_VFS_VFS_STORAGE_HPP

#include "stormline/data/vfs/vfs_path.hpp"

#include <array>
#include <span>

namespace stormline::data::vfs {

struct StorageDescriptor {
    MountId mount{};
    u64 generation{0};
    u32 flags{0};
};

class StorageBackend {
public:
    virtual ~StorageBackend() = default;

    [[nodiscard]] virtual VfsError read(
        const VfsPath& path, std::span<std::uint8_t> output,
        u32& out_size) noexcept = 0;
};

class MemoryStorage final : public StorageBackend {
public:
    MemoryStorage() noexcept = default;

    [[nodiscard]] VfsError put(
        const VfsPath& path, std::span<const std::uint8_t> bytes) noexcept {
        VfsPath normalized{};
        const VfsError path_error = normalize(path, normalized);
        if (path_error != VfsError::None) {
            return path_error;
        }
        if (bytes.size() > kMaxStorageBytes) {
            return VfsError::InvalidArgument;
        }
        for (u32 index = 0; index < size_; ++index) {
            if (view(files_[index].path) == view(normalized)) {
                copy_bytes(files_[index], bytes);
                return VfsError::None;
            }
        }
        if (size_ >= kMaxStorageFiles) {
            return VfsError::BufferFull;
        }
        File& file = files_[size_];
        file.path = normalized;
        copy_bytes(file, bytes);
        ++size_;
        return VfsError::None;
    }

    [[nodiscard]] VfsError read(
        const VfsPath& path, std::span<std::uint8_t> output,
        u32& out_size) noexcept override {
        out_size = 0;
        VfsPath normalized{};
        const VfsError path_error = normalize(path, normalized);
        if (path_error != VfsError::None) {
            return path_error;
        }
        for (u32 index = 0; index < size_; ++index) {
            const File& file = files_[index];
            if (view(file.path) != view(normalized)) {
                continue;
            }
            out_size = file.size;
            if (output.size() < file.size) {
                return VfsError::BufferFull;
            }
            for (u32 offset = 0; offset < file.size; ++offset) {
                output[offset] = file.bytes[offset];
            }
            return VfsError::None;
        }
        return VfsError::NotFound;
    }

    [[nodiscard]] VfsError erase(const VfsPath& path) noexcept {
        VfsPath normalized{};
        const VfsError path_error = normalize(path, normalized);
        if (path_error != VfsError::None) {
            return path_error;
        }
        for (u32 index = 0; index < size_; ++index) {
            if (view(files_[index].path) != view(normalized)) {
                continue;
            }
            for (u32 next = index + 1; next < size_; ++next) {
                files_[next - 1] = files_[next];
            }
            --size_;
            return VfsError::None;
        }
        return VfsError::NotFound;
    }

    [[nodiscard]] u32 size() const noexcept { return size_; }

private:
    struct File {
        VfsPath path{};
        std::array<std::uint8_t, kMaxStorageBytes> bytes{};
        u32 size{0};
    };

    static VfsError normalize(const VfsPath& input, VfsPath& out) noexcept {
        if (input.length > kMaxPathBytes) {
            return VfsError::InvalidPath;
        }
        return make_path(view(input), out);
    }

    static void copy_bytes(File& file, std::span<const std::uint8_t> bytes) noexcept {
        file.size = static_cast<u32>(bytes.size());
        for (u32 index = 0; index < file.size; ++index) {
            file.bytes[index] = bytes[index];
        }
    }

    std::array<File, kMaxStorageFiles> files_{};
    u32 size_{0};
};

}  // namespace stormline::data::vfs

#endif  // STORMLINE_DATA_VFS_VFS_STORAGE_HPP
