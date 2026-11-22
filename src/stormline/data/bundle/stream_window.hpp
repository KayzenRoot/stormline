#ifndef STORMLINE_DATA_BUNDLE_STREAM_WINDOW_HPP
#define STORMLINE_DATA_BUNDLE_STREAM_WINDOW_HPP

#include "stormline/data/bundle/bundle_types.hpp"

#include <array>
#include <span>

namespace stormline::data::bundle {

struct ManifestEntry {
    u64 chunk_id{0};
    u32 offset{0};
    u32 length{0};
    u64 fingerprint{0};
};

class BundleManifest final {
public:
    BundleManifest() noexcept = default;

    [[nodiscard]] BundleError init(u64 generation) noexcept {
        if (generation == 0) {
            return BundleError::InvalidArgument;
        }
        size_ = 0;
        total_bytes_ = 0;
        generation_ = generation;
        return BundleError::None;
    }

    [[nodiscard]] BundleError add(const ManifestEntry& entry) noexcept {
        if (generation_ == 0 || entry.chunk_id == 0 || entry.length == 0
            || entry.length > kMaxChunkBytes || entry.offset > 4096
            || entry.length > 4096 - entry.offset) {
            return BundleError::InvalidArgument;
        }
        for (u32 index = 0; index < size_; ++index) {
            if (entries_[index].chunk_id == entry.chunk_id) {
                return BundleError::DuplicateId;
            }
            const u32 begin = entry.offset;
            const u32 end = entry.offset + entry.length;
            const u32 other_begin = entries_[index].offset;
            const u32 other_end = entries_[index].offset + entries_[index].length;
            if (begin < other_end && other_begin < end) {
                return BundleError::ChunkOverlap;
            }
        }
        if (size_ >= kMaxManifestEntries) {
            return BundleError::CapacityFull;
        }
        if (total_bytes_ > 4096 - entry.length) {
            return BundleError::RangeOverflow;
        }
        entries_[size_++] = entry;
        total_bytes_ += entry.length;
        return BundleError::None;
    }

    [[nodiscard]] BundleError find(u64 chunk_id, ManifestEntry& out) const noexcept {
        for (u32 index = 0; index < size_; ++index) {
            if (entries_[index].chunk_id == chunk_id) {
                out = entries_[index];
                return BundleError::None;
            }
        }
        return BundleError::NotFound;
    }

    [[nodiscard]] bool at(u32 index, ManifestEntry& out) const noexcept {
        if (index >= size_) {
            return false;
        }
        out = entries_[index];
        return true;
    }

    [[nodiscard]] u32 size() const noexcept { return size_; }
    [[nodiscard]] u64 generation() const noexcept { return generation_; }
    [[nodiscard]] u32 total_bytes() const noexcept { return total_bytes_; }

private:
    std::array<ManifestEntry, kMaxManifestEntries> entries_{};
    u32 size_{0};
    u64 generation_{0};
    u32 total_bytes_{0};
};

class ChunkStore final {
public:
    ChunkStore() noexcept = default;

    [[nodiscard]] BundleError put(u64 chunk_id, std::span<const u8> bytes) noexcept {
        if (chunk_id == 0 || bytes.empty() || bytes.size() > kMaxChunkBytes) {
            return BundleError::InvalidArgument;
        }
        for (u32 index = 0; index < size_; ++index) {
            if (chunks_[index].id == chunk_id) {
                return BundleError::DuplicateId;
            }
        }
        if (size_ >= kMaxChunks) {
            return BundleError::CapacityFull;
        }
        Chunk& chunk = chunks_[size_];
        chunk.id = chunk_id;
        chunk.size = static_cast<u32>(bytes.size());
        for (u32 index = 0; index < chunk.size; ++index) {
            chunk.bytes[index] = bytes[index];
        }
        ++size_;
        return BundleError::None;
    }

    [[nodiscard]] BundleError get(
        u64 chunk_id, std::span<u8> output, u32& out_size) const noexcept {
        out_size = 0;
        for (u32 index = 0; index < size_; ++index) {
            if (chunks_[index].id != chunk_id) {
                continue;
            }
            out_size = chunks_[index].size;
            if (output.size() < chunks_[index].size) {
                return BundleError::BufferFull;
            }
            for (u32 offset = 0; offset < chunks_[index].size; ++offset) {
                output[offset] = chunks_[index].bytes[offset];
            }
            return BundleError::None;
        }
        return BundleError::NotFound;
    }

    [[nodiscard]] u32 size() const noexcept { return size_; }

private:
    struct Chunk {
        u64 id{0};
        std::array<u8, kMaxChunkBytes> bytes{};
        u32 size{0};
    };
    std::array<Chunk, kMaxChunks> chunks_{};
    u32 size_{0};
};

class StreamWindow final {
public:
    StreamWindow() noexcept = default;

    [[nodiscard]] BundleError init(
        const BundleManifest& manifest, const ChunkStore& store,
        u64 generation, u32 byte_budget) noexcept {
        if (generation == 0 || generation != manifest.generation()
            || byte_budget == 0 || byte_budget > kMaxStreamBytes) {
            return BundleError::InvalidArgument;
        }
        manifest_ = &manifest;
        store_ = &store;
        generation_ = generation;
        budget_ = byte_budget;
        loaded_bytes_ = 0;
        chunk_count_ = 0;
        return BundleError::None;
    }

    [[nodiscard]] BundleError request(u64 chunk_id) noexcept {
        if (manifest_ == nullptr || store_ == nullptr) {
            return BundleError::InvalidArgument;
        }
        if (generation_ != manifest_->generation()) {
            return BundleError::StaleGeneration;
        }
        ManifestEntry entry{};
        const BundleError manifest_status = manifest_->find(chunk_id, entry);
        if (manifest_status != BundleError::None) {
            return manifest_status;
        }
        for (u32 index = 0; index < chunk_count_; ++index) {
            if (loaded_[index] == chunk_id) {
                return BundleError::None;
            }
        }
        std::array<u8, kMaxChunkBytes> bytes{};
        u32 stored_size = 0;
        const BundleError store_status = store_->get(chunk_id, bytes, stored_size);
        if (store_status != BundleError::None) {
            return store_status;
        }
        if (stored_size != entry.length) {
            return BundleError::FingerprintMismatch;
        }
        if (entry.length > budget_ - loaded_bytes_) {
            return BundleError::CapacityFull;
        }
        if (chunk_count_ >= kMaxChunks) {
            return BundleError::CapacityFull;
        }
        loaded_[chunk_count_++] = chunk_id;
        loaded_bytes_ += entry.length;
        return BundleError::None;
    }

    [[nodiscard]] u32 chunk_count() const noexcept { return chunk_count_; }
    [[nodiscard]] u32 loaded_bytes() const noexcept { return loaded_bytes_; }
    [[nodiscard]] u32 budget() const noexcept { return budget_; }

private:
    const BundleManifest* manifest_{nullptr};
    const ChunkStore* store_{nullptr};
    u64 generation_{0};
    u32 budget_{0};
    u32 loaded_bytes_{0};
    u32 chunk_count_{0};
    std::array<u64, kMaxChunks> loaded_{};
};

}  // namespace stormline::data::bundle

#endif  // STORMLINE_DATA_BUNDLE_STREAM_WINDOW_HPP
