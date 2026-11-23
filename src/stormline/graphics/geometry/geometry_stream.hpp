#ifndef STORMLINE_GRAPHICS_GEOMETRY_GEOMETRY_STREAM_HPP
#define STORMLINE_GRAPHICS_GEOMETRY_GEOMETRY_STREAM_HPP

#include "stormline/graphics/geometry/geometry_instance.hpp"

#include <algorithm>

namespace stormline::graphics::geometry {

namespace detail {

inline u32 find_chunk(const ChunkSet& set, u32 chunk_id) noexcept {
    for (u32 index = 0; index < set.count; ++index) {
        if (set.chunks[index].chunk_id == chunk_id) {
            return index;
        }
    }
    return kMaxChunks;
}

inline bool is_resident(const ResidentChunks& resident, u32 chunk_id) noexcept {
    for (u32 index = 0; index < resident.count; ++index) {
        if (resident.chunk_ids[index] == chunk_id) {
            return true;
        }
    }
    return false;
}

}  // namespace detail

[[nodiscard]] inline GeometryError plan_stream(
    const ChunkSet& chunks, const ResidentChunks& resident,
    u32 byte_budget, StreamPlan& plan,
    GeometryDiagnostic& diagnostic) noexcept {
    plan = StreamPlan{};
    if (chunks.scene_generation == 0 || chunks.count > kMaxChunks
        || resident.count > kMaxChunks || byte_budget == 0) {
        return detail::set_error(
            diagnostic, GeometryError::InvalidArgument, 0, 0, 0);
    }
    for (u32 index = 0; index < chunks.count; ++index) {
        const GeometryChunk& chunk = chunks.chunks[index];
        if (chunk.chunk_id == 0 || chunk.mesh_id == 0
            || chunk.lod_level >= kMaxLodLevels || chunk.bytes == 0) {
            return detail::set_error(
                diagnostic, GeometryError::InvalidArgument, 0, chunk.mesh_id, index);
        }
        if (!chunk.verified) {
            return detail::set_error(
                diagnostic, GeometryError::UnverifiedChunk, 0, chunk.mesh_id, index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (chunks.chunks[previous].chunk_id == chunk.chunk_id) {
                return detail::set_error(
                    diagnostic, GeometryError::DuplicateId, 0, chunk.mesh_id, index);
            }
        }
    }
    for (u32 index = 0; index < resident.count; ++index) {
        const u32 chunk_id = resident.chunk_ids[index];
        if (detail::find_chunk(chunks, chunk_id) == kMaxChunks) {
            return detail::set_error(
                diagnostic, GeometryError::NotFound, 0, 0, index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (resident.chunk_ids[previous] == chunk_id) {
                return detail::set_error(
                    diagnostic, GeometryError::InvalidArgument, 0, 0, index);
            }
        }
    }

    std::array<u32, kMaxChunks> candidates{};
    u32 candidate_count = 0;
    for (u32 index = 0; index < chunks.count; ++index) {
        if (!detail::is_resident(resident, chunks.chunks[index].chunk_id)) {
            candidates[candidate_count] = index;
            ++candidate_count;
        }
    }
    std::sort(candidates.begin(), candidates.begin() + candidate_count,
              [&chunks](u32 left, u32 right) {
                  const GeometryChunk& a = chunks.chunks[left];
                  const GeometryChunk& b = chunks.chunks[right];
                  if (a.mesh_id != b.mesh_id) {
                      return a.mesh_id < b.mesh_id;
                  }
                  if (a.lod_level != b.lod_level) {
                      return a.lod_level < b.lod_level;
                  }
                  return a.chunk_id < b.chunk_id;
              });

    u64 total = 0;
    for (u32 index = 0; index < candidate_count; ++index) {
        const GeometryChunk& chunk = chunks.chunks[candidates[index]];
        if (total + chunk.bytes > byte_budget) {
            plan.truncated = true;
            break;
        }
        total += chunk.bytes;
        plan.chunk_ids[plan.count] = chunk.chunk_id;
        ++plan.count;
    }
    plan.total_bytes = static_cast<u32>(total);
    return GeometryError::None;
}

}  // namespace stormline::graphics::geometry

#endif  // STORMLINE_GRAPHICS_GEOMETRY_GEOMETRY_STREAM_HPP
