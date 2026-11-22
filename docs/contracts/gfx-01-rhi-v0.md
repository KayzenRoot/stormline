# GFX-01 INTERNAL_ONLY Backend-Neutral RHI Contract v0 (NLE-PRPLAN-GFX-01-02)

**Status:** `CONTRACT PROPOSAL / NOT IMPLEMENTED / NO CODE AUTHORIZED`. **Base:** `0282408`. **ADR:** [ADR-0115](../adr/0115-gfx-01-governance-slice.md), [ADR-0014](../adr/0014-gfx-01-rhi-backends.md) planning-only. **WO:** [NLE-PRPLAN-GFX-01-02](../work-orders/NLE-PRPLAN-GFX-01-02.md).

## Objective

Freeze a backend-neutral logical RHI contract: adapters, device generations/lifecycle, queue roles, buffer/texture descriptors and handles, barriers and feature tiers, exercised by a Null/reference backend. No native GPU, shader, swapchain, rendering, dependency, ABI or release.

## Admission and boundaries

- Formal dependencies are `CORE-01` and `CORE-02`; neither is module-qualified.
- GFX-01 owns logical adapters/devices/queues/resources/barriers/features.
- CORE-01 native OS; CORE-02 memory; CORE-03 jobs; CORE-04 ticks; CORE-05 math/IDs; CORE-06 diagnostics; DATA-05 bundles; GFX-02 shaders; GFX-03 render graph.
- No Vulkan/D3D12/Metal/SDL GPU/Dawn/wgpu/bgfx dependency or SDK is selected or implemented.

## Policy invariants

- **No native GPU.** Null/reference backend only; no driver, device, swapchain, rendering or presentation.
- **Opaque handles.** Handles carry device generation, slot and slot generation; no raw GPU pointer.
- **Generation fencing.** Device recovery increments generation; old handles are stale.
- **Explicit features.** Required feature bits and tier are validated; unsupported fails closed.
- **Bounded.** 4 adapters, 4 queues, 64 resources, 32 barriers, 64-byte labels.
- **Checked descriptors.** Buffer size/usage/alignment and texture dimensions/levels/format/usage are validated.
- **Logical sync.** Barriers validate handle generation and access/stage transitions; no real hazards.
- **No rendering claim.** No shader, pipeline, draw, present, timing or performance.

## Internal API (logical, exact names)

```cpp
namespace stormline::graphics::rhi {

using u32 = std::uint32_t;
using u64 = std::uint64_t;

inline constexpr u32 kMaxAdapters = 4;
inline constexpr u32 kMaxQueues = 4;
inline constexpr u32 kMaxResources = 64;
inline constexpr u32 kMaxBarriers = 32;
inline constexpr u32 kMaxLabelBytes = 64;
inline constexpr u32 kMaxBufferBytes = 4096;
inline constexpr u32 kMaxTextureDimension = 4096;
inline constexpr u32 kMaxTextureLevels = 8;

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

inline constexpr u32 kFeatureCompute = 1u << 0;
inline constexpr u32 kFeatureIndirectDraw = 1u << 1;
inline constexpr u32 kFeatureDescriptorIndexing = 1u << 2;
inline constexpr u32 kFeatureTimestampQuery = 1u << 3;
inline constexpr u32 kAllFeatures = kFeatureCompute | kFeatureIndirectDraw
    | kFeatureDescriptorIndexing | kFeatureTimestampQuery;

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

[[nodiscard]] u32 adapter_count() noexcept;
[[nodiscard]] RhiError adapter_at(u32 index, AdapterInfo& out) noexcept;

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

class RhiDevice final {
public:
    RhiDevice() noexcept = default;
    [[nodiscard]] RhiError init(const DeviceDescriptor& descriptor, Capabilities& out) noexcept;
    [[nodiscard]] RhiError close() noexcept;
    [[nodiscard]] RhiError lose() noexcept;
    [[nodiscard]] RhiError recover(Capabilities& out) noexcept;
    [[nodiscard]] DeviceState state() const noexcept;
    [[nodiscard]] u64 generation() const noexcept;
    [[nodiscard]] Capabilities capabilities() const noexcept;

    [[nodiscard]] RhiError create_buffer(
        const BufferDesc& descriptor, ResourceHandle& out) noexcept;
    [[nodiscard]] RhiError create_texture(
        const TextureDesc& descriptor, ResourceHandle& out) noexcept;
    [[nodiscard]] RhiError release(const ResourceHandle& handle) noexcept;
    [[nodiscard]] RhiError resource_info(
        const ResourceHandle& handle, ResourceClass& out_class,
        u32& out_size) const noexcept;

    [[nodiscard]] bool queue_supported(QueueRole role) const noexcept;
    [[nodiscard]] RhiError submit(QueueRole role, u32 command_count) noexcept;
    [[nodiscard]] u32 submit_count() const noexcept;

    [[nodiscard]] RhiError validate_barrier(const Barrier& barrier) const noexcept;
};

}  // namespace stormline::graphics::rhi
```

No implementation is provided. Names or semantics may be refined only by an audited contract correction before `GFX-01-03`.

## Semantics

- **Adapters:** exactly one Null adapter with features `kFeatureCompute | kFeatureIndirectDraw`, max buffer 4096, texture 4096×4096, levels 8.
- **Init:** adapter ID must match, required features subset of adapter features, required tier 1 only; otherwise typed failure. Generation starts at 1.
- **Loss/recover:** `lose` from Ready → Lost; `recover` from Lost → Ready and increments generation, invalidating all prior handles. Call on wrong state returns `InvalidArgument`.
- **Buffers:** size 1..4096, usage nonzero subset `0x3F`, alignment power-of-two 1..256; capacity 64. Release invalidates slot generation.
- **Textures:** width/height 1..4096, levels 1..8, known format, usage nonzero subset `0x3F`; capacity 64. Release invalidates slot generation.
- **Handles:** device generation/slot/slot generation must match current state; stale/wrong class returns `StaleHandle`; released slot returns `StaleHandle`.
- **Queues:** Null supports Graphics and Transfer; Compute requires `kFeatureCompute` and is supported because the adapter advertises it. `submit` requires Ready, supported role and command count 1..64; increments a counter.
- **Barriers:** resource handle current, old/new access/stage nonzero and not equal? Old/new stage must be known bits; invalid returns `SyncInvalid`. No real GPU synchronization is performed.
- **Threading:** single-owner; no allocation, driver, file, network or global mutable state.

## Test oracles (future GFX-01-03..-09)

| ID | Scenario | Oracle |
|---|---|---|
| DEV-01 | adapters/device lifecycle | adapter list, init validation, loss/recover generation, close |
| QUE-01 | queue roles/submit | support, invalid role, count bounds, state checks |
| BUF-01 | buffers/handles | descriptor bounds, create/release, stale handle, capacity |
| TEX-01 | textures | dimensions/levels/format/usage, capacity, release |
| SYN-01 | barriers | valid transition, stale handle, invalid bits |
| TIER-01 | feature tiers | required features/tier, unsupported failure, capabilities |
| QLF-G01 | integrated | adapter→device→queue→buffer→texture→barrier→loss/recover |
| QLF-G02 | deterministic repeat | repeated sequence identical generations/caps/counts |
| QLF-G03 | failure recovery | each typed error followed by valid operation |
| QLF-G04 | bounded overload | 10,000 create/submit/barrier attempts keep capacities |

## Implementation allowlists

Headers are internal and header-only under `src/stormline/graphics/rhi/`. CMake adds one `INTERFACE` target and one test executable per packet; no production `.cpp`.

### `GFX-01-03` (devices)

1. `src/stormline/graphics/rhi/rhi_types.hpp`
2. `src/stormline/graphics/rhi/rhi_device.hpp`
3. `tests/core/gfx01_device_tests.cpp`
4. `CMakeLists.txt`
5. `.github/workflows/core01-internal-headless.yml`
6. `docs/evidence/NLE-PRPLAN-GFX-01-03.md`

### `GFX-01-04` (queues)

1. `src/stormline/graphics/rhi/rhi_queue.hpp`
2. `tests/core/gfx01_queue_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-GFX-01-04.md`

### `GFX-01-05` (buffers)

1. `src/stormline/graphics/rhi/rhi_buffer.hpp`
2. `tests/core/gfx01_buffer_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-GFX-01-05.md`

### `GFX-01-06` (textures)

1. `src/stormline/graphics/rhi/rhi_texture.hpp`
2. `tests/core/gfx01_texture_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-GFX-01-06.md`

### `GFX-01-07` (synchronization)

1. `src/stormline/graphics/rhi/rhi_sync.hpp`
2. `tests/core/gfx01_sync_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-GFX-01-07.md`

### `GFX-01-08` (feature tiers)

1. `src/stormline/graphics/rhi/rhi_feature.hpp`
2. `tests/core/gfx01_feature_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-GFX-01-08.md`

### `GFX-01-09` (qualification)

1. `tests/core/gfx01_rhi_qualification_tests.cpp`
2. `CMakeLists.txt`
3. `.github/workflows/core01-internal-headless.yml`
4. `docs/evidence/NLE-PRPLAN-GFX-01-09.md`

`GFX-01-10` is documentary closeout only. Qualification is internal/CI-only; no native GPU, rendering, hardware, ABI or release claim.

## Stop / rollback / security

Stop on stale source, missing admission, native GPU/API/driver selection, shader/render/swapchain code, raw GPU pointer, public ABI/release claim or HIGH/CRITICAL. Revert normally; never force push.
