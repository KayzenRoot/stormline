#ifndef STORMLINE_GRAPHICS_GEOMETRY_GEOMETRY_TYPES_HPP
#define STORMLINE_GRAPHICS_GEOMETRY_GEOMETRY_TYPES_HPP

#include <array>
#include <cstdint>

namespace stormline::graphics::geometry {

using u8 = std::uint8_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using f32 = float;

inline constexpr u32 kMaxInstances = 128;
inline constexpr u32 kMaxMeshes = 64;
inline constexpr u32 kMaxLodLevels = 8;
inline constexpr u32 kMaxChunks = 64;
inline constexpr u32 kMaxBatches = 32;
inline constexpr u32 kMaxPlanes = 6;
inline constexpr u32 kMaxStreamRequests = 64;
inline constexpr u32 kMaxNameBytes = 32;

enum class GeometryError : std::uint8_t {
    None,
    InvalidArgument,
    DuplicateId,
    NotFound,
    CapacityFull,
    InvalidBounds,
    UnknownBounds,
    InvalidCamera,
    GenerationMismatch,
    HierarchyCycle,
    InvalidLodChain,
    UnverifiedChunk,
    StreamBudgetExceeded,
    GeometryBudgetExceeded
};

enum class VegetationKind : std::uint8_t { None, Grass, Bush, Tree };
enum class VegetationRenderClass : std::uint8_t { Mesh, Billboard, Skip };

struct Vec3 {
    f32 x{0.0f};
    f32 y{0.0f};
    f32 z{0.0f};
};

struct Plane {
    Vec3 normal{};
    f32 distance{0.0f};
};

struct SphereBounds {
    Vec3 center{};
    f32 radius{0.0f};
    bool known{false};
};

struct GeometryDiagnostic {
    GeometryError code{GeometryError::None};
    u32 instance_id{0};
    u32 mesh_id{0};
    u32 index{0};
};

struct InstanceDesc {
    u32 id{0};
    u32 mesh_id{0};
    u32 material_id{0};
    SphereBounds bounds{};
    VegetationKind vegetation{VegetationKind::None};
    bool double_sided{false};
    bool alpha_cutout{false};
    bool billboard_allowed{false};
};

struct InstanceSet {
    u64 scene_generation{0};
    u32 count{0};
    std::array<InstanceDesc, kMaxInstances> instances{};
};

struct InstanceBatch {
    u32 mesh_id{0};
    u32 material_id{0};
    u32 count{0};
    std::array<u32, kMaxInstances> instance_indices{};
};

struct BatchPlan {
    u32 count{0};
    std::array<InstanceBatch, kMaxBatches> batches{};
};

struct ViewFrustum {
    u64 scene_generation{0};
    u32 plane_count{0};
    std::array<Plane, kMaxPlanes> planes{};
    Vec3 camera{};
    f32 max_distance{0.0f};
};

struct CullResult {
    u32 visible_count{0};
    std::array<u32, kMaxInstances> visible_ids{};
    u32 culled_count{0};
};

struct LodLevel {
    f32 geometric_error{0.0f};
    u32 triangle_count{0};
};

struct LodChain {
    u64 scene_generation{0};
    u32 mesh_id{0};
    u32 level_count{0};
    std::array<LodLevel, kMaxLodLevels> levels{};
};

struct LodRequest {
    Vec3 camera{};
    f32 screen_scale{1.0f};
    f32 max_screen_error{0.0f};
    u32 previous_level{0};
};

struct LodSelection {
    u32 mesh_id{0};
    u32 level{0};
    u32 triangle_count{0};
    f32 projected_error{0.0f};
};

struct HlodNode {
    u32 mesh_id{0};
    u32 parent_mesh_id{0};
    f32 geometric_error{0.0f};
    u32 triangle_count{0};
    bool proxy{false};
};

struct HlodSet {
    u64 scene_generation{0};
    u32 count{0};
    std::array<HlodNode, kMaxMeshes> nodes{};
};

struct HlodSelection {
    u32 mesh_id{0};
    f32 geometric_error{0.0f};
    bool proxy{false};
};

struct GeometryChunk {
    u32 chunk_id{0};
    u32 mesh_id{0};
    u32 lod_level{0};
    u32 bytes{0};
    bool verified{false};
};

struct ChunkSet {
    u64 scene_generation{0};
    u32 count{0};
    std::array<GeometryChunk, kMaxChunks> chunks{};
};

struct ResidentChunks {
    u32 count{0};
    std::array<u32, kMaxChunks> chunk_ids{};
};

struct StreamPlan {
    u32 count{0};
    std::array<u32, kMaxStreamRequests> chunk_ids{};
    u32 total_bytes{0};
    bool truncated{false};
};

struct VegetationRequest {
    Vec3 camera{};
    f32 billboard_distance{0.0f};
};

struct VegetationDecision {
    u32 instance_id{0};
    VegetationRenderClass render_class{VegetationRenderClass::Mesh};
    bool double_sided{false};
    bool alpha_cutout{false};
};

struct GeometryMetrics {
    u32 mesh_id{0};
    u32 vertex_count{0};
    u32 triangle_count{0};
    u32 byte_count{0};
};

struct GeometryMetricSet {
    u32 count{0};
    std::array<GeometryMetrics, kMaxMeshes> meshes{};
};

struct GeometryBudget {
    u64 max_vertices{0};
    u64 max_triangles{0};
    u64 max_bytes{0};
};

struct GeometryBudgetPlan {
    u64 total_vertices{0};
    u64 total_triangles{0};
    u64 total_bytes{0};
    bool within_budget{false};
};

}  // namespace stormline::graphics::geometry

#endif  // STORMLINE_GRAPHICS_GEOMETRY_GEOMETRY_TYPES_HPP
