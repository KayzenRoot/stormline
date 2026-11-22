#ifndef STORMLINE_GRAPHICS_RHI_RHI_TYPES_HPP
#define STORMLINE_GRAPHICS_RHI_RHI_TYPES_HPP

#include <cstdint>

namespace stormline::graphics::rhi {

using u32 = std::uint32_t;
using u64 = std::uint64_t;
using u8 = std::uint8_t;

inline constexpr u32 kMaxAdapters = 4;
inline constexpr u32 kMaxQueues = 4;
inline constexpr u32 kMaxResources = 64;
inline constexpr u32 kMaxBarriers = 32;
inline constexpr u32 kMaxLabelBytes = 64;
inline constexpr u32 kMaxBufferBytes = 4096;
inline constexpr u32 kMaxTextureDimension = 4096;
inline constexpr u32 kMaxTextureLevels = 8;

inline constexpr u32 kFeatureCompute = 1u << 0;
inline constexpr u32 kFeatureIndirectDraw = 1u << 1;
inline constexpr u32 kFeatureDescriptorIndexing = 1u << 2;
inline constexpr u32 kFeatureTimestampQuery = 1u << 3;
inline constexpr u32 kAllFeatures = kFeatureCompute | kFeatureIndirectDraw
    | kFeatureDescriptorIndexing | kFeatureTimestampQuery;

enum class RhiError : std::uint8_t {
    None,
    InvalidArgument,
    InvalidAdapter,
    UnsupportedFeature,
    InvalidDescriptor,
    DuplicateId,
    NotFound,
    CapacityFull,
    StaleHandle,
    StaleGeneration,
    DeviceLost,
    QueueUnsupported,
    SyncInvalid,
    BufferFull
};

enum class Backend : std::uint8_t { Null };
enum class DeviceState : std::uint8_t { Uninitialized, Ready, Lost, Disposed };
enum class QueueRole : std::uint8_t { Graphics, Compute, Transfer };
enum class ResourceClass : std::uint8_t { Buffer, Texture };
enum class Format : std::uint8_t { Rgba8Unorm, Rgba8Srgb, R32Float, Depth32Float };

struct AdapterInfo {
    u32 adapter_id{0};
    Backend backend{Backend::Null};
    u32 vendor_id{0};
    u32 device_id{0};
    u32 feature_flags{0};
    u32 max_buffer_bytes{0};
    u32 max_texture_dimension{0};
    u32 max_texture_levels{0};
};

struct DeviceDescriptor {
    u32 adapter_id{0};
    u32 required_features{0};
    u32 required_tier{0};
};

struct Capabilities {
    u32 device_generation{0};
    u32 feature_flags{0};
    u32 max_buffer_bytes{0};
    u32 max_texture_dimension{0};
    u32 max_texture_levels{0};
    u32 queue_roles{0};
};

struct ResourceHandle {
    u64 device_generation{0};
    u32 slot{0};
    u32 slot_generation{0};
    ResourceClass resource_class{ResourceClass::Buffer};
};

struct BufferDesc {
    u32 size{0};
    u32 usage{0};
    u32 alignment{0};
};

struct TextureDesc {
    u32 width{0};
    u32 height{0};
    u32 levels{0};
    Format format{Format::Rgba8Unorm};
    u32 usage{0};
};

struct Barrier {
    ResourceHandle resource{};
    u32 old_access{0};
    u32 new_access{0};
    u32 old_stage{0};
    u32 new_stage{0};
};

}  // namespace stormline::graphics::rhi

#endif  // STORMLINE_GRAPHICS_RHI_RHI_TYPES_HPP
