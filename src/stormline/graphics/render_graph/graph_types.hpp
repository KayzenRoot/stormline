#ifndef STORMLINE_GRAPHICS_RENDER_GRAPH_GRAPH_TYPES_HPP
#define STORMLINE_GRAPHICS_RENDER_GRAPH_GRAPH_TYPES_HPP

#include "stormline/graphics/rhi/rhi_types.hpp"

#include <array>
#include <cstdint>

namespace stormline::graphics::render_graph {

namespace rhi = stormline::graphics::rhi;

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

inline constexpr u32 kMaxPasses = 64;
inline constexpr u32 kMaxResources = 128;
inline constexpr u32 kMaxUses = 256;
inline constexpr u32 kMaxEdges = 512;
inline constexpr u32 kMaxTransitions = 256;
inline constexpr u32 kMaxAliasGroups = 64;
inline constexpr u32 kMaxDiagnostics = 16;
inline constexpr u32 kMaxNameBytes = 32;
inline constexpr u32 kMaxAlignment = 4096;

enum class GraphError : std::uint8_t {
    None,
    InvalidArgument,
    DuplicatePass,
    DuplicateResource,
    NotFound,
    CapacityFull,
    Cycle,
    AmbiguousWriter,
    UninitializedRead,
    InvalidUse,
    QueueUnsupported,
    AliasConflict,
    BudgetUnknown,
    BudgetExceeded,
    StaleGeneration
};

enum class ResourceKind : std::uint8_t { External, Persistent, Transient, History };
enum class Access : std::uint8_t { Read, Write, ReadWrite };
enum class PassKind : std::uint8_t { Graphics, Compute, Copy, Present };
enum class Hazard : std::uint8_t { RAW, WAR, WAW };
enum class GraphAccess : std::uint8_t { None, Read, Write };

struct GraphDiagnostic {
    GraphError code{GraphError::None};
    u32 pass_id{0};
    u32 resource_id{0};
    u32 index{0};
};

struct ResourceDesc {
    u32 id{0};
    ResourceKind kind{ResourceKind::Transient};
    u64 bytes{0};
    u32 alignment{1};
};

struct PassDesc {
    u32 id{0};
    rhi::QueueRole queue{rhi::QueueRole::Graphics};
    PassKind kind{PassKind::Graphics};
    bool side_effect{false};
};

struct UseDesc {
    u32 pass_id{0};
    u32 resource_id{0};
    Access access{Access::Read};
};

struct GraphDefinition {
    u64 device_generation{0};
    u32 resource_count{0};
    std::array<ResourceDesc, kMaxResources> resources{};
    u32 pass_count{0};
    std::array<PassDesc, kMaxPasses> passes{};
    u32 use_count{0};
    std::array<UseDesc, kMaxUses> uses{};
};

struct DependencyEdge {
    u32 producer_pass{0};
    u32 consumer_pass{0};
    u32 resource_id{0};
    Hazard hazard{Hazard::RAW};
};

struct DependencyPlan {
    u32 order_count{0};
    std::array<u32, kMaxPasses> order{};
    u32 edge_count{0};
    std::array<DependencyEdge, kMaxEdges> edges{};
};

struct SyncTransition {
    u32 resource_id{0};
    GraphAccess old_access{GraphAccess::None};
    GraphAccess new_access{GraphAccess::None};
    rhi::QueueRole old_queue{rhi::QueueRole::Graphics};
    rhi::QueueRole new_queue{rhi::QueueRole::Graphics};
    u32 before_pass{0};
};

struct SyncPlan {
    u32 transition_count{0};
    std::array<SyncTransition, kMaxTransitions> transitions{};
};

struct Lifetime {
    u32 resource_id{0};
    u32 first_pass{0};
    u32 last_pass{0};
};

struct AliasGroup {
    u32 resource_count{0};
    std::array<u32, kMaxResources> resource_ids{};
    u64 bytes{0};
    u32 alignment{1};
};

struct AliasPlan {
    u32 lifetime_count{0};
    std::array<Lifetime, kMaxResources> lifetimes{};
    u32 group_count{0};
    std::array<AliasGroup, kMaxAliasGroups> groups{};
    u64 alias_saved_bytes{0};
};

struct GpuBudgetSnapshot {
    bool known{false};
    u64 total_bytes{0};
    u64 headroom_bytes{0};
};

struct BudgetPlan {
    u64 persistent_bytes{0};
    u64 transient_peak_bytes{0};
    u64 alias_saved_bytes{0};
    u64 required_bytes{0};
    bool within_budget{false};
};

}  // namespace stormline::graphics::render_graph

#endif  // STORMLINE_GRAPHICS_RENDER_GRAPH_GRAPH_TYPES_HPP
