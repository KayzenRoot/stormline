# WORLD-04 internal terrain/environment metadata contract v0

**Status:** `APPROVED CONTRACT / INTERNAL_ONLY / NO TERRAIN OR ENVIRONMENT RUNTIME`. **ADR:** [ADR-0130](../adr/0130-world-04-internal-terrain-environment-metadata.md). **Architecture:** [world-04-internal-terrain-environment-metadata](../architecture/world-04-internal-terrain-environment-metadata.md). **Governance:** [world-04-governance-v0](world-04-governance-v0.md).

Freeze the bounded logical API for terrain patches, splat/material layers, vegetation placement, water bodies, sky profiles and weather intents. No heightfield/mesh storage, mesh generation, terrain/water rendering, GPU LOD, texture residency, vegetation instancing, atmosphere/weather simulation, physics/network coordination, renderer, editor, GPU, performance, ABI or release.

## Namespace and common types

Header-only under `src/stormline/terrain/`, namespace `stormline::terrain`.

```cpp
using u8 = std::uint8_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using i64 = std::int64_t;
using f32 = float;

inline constexpr u32 kMaxTerrainPatches = 64;
inline constexpr u32 kMaxPatchNeighbors = 8;
inline constexpr u32 kMaxTerrainLod = 8;
inline constexpr u32 kMaxSplatLayers = 16;
inline constexpr u32 kMaxVegetationGroups = 32;
inline constexpr u32 kMaxVegetationInstances = 4096;
inline constexpr u32 kMaxWaterBodies = 32;
inline constexpr u32 kMaxSkyProfiles = 16;
inline constexpr u32 kMaxWeatherZones = 32;

enum class TerrainError : std::uint8_t {
    None,
    InvalidArgument,
    DuplicateId,
    NotFound,
    CapacityFull,
    NonFiniteValue,
    OutOfRange,
    PatchInvalid,
    SplatInvalid,
    VegetationInvalid,
    WaterInvalid,
    SkyInvalid,
    WeatherInvalid,
    Incomplete,
    Unsupported
};

enum class PatchTopology : std::uint8_t { Heightfield, MeshSurface };
enum class WaterClass : std::uint8_t { Ocean, Lake, River, Local };
enum class QualityTier : std::uint8_t { Low, Medium, High, Ultra };

struct TerrainDiagnostic {
    TerrainError code{TerrainError::None};
    u32 asset_id{0};
    u32 index{0};
};
```

## Terrain patch metadata

```cpp
struct TerrainPatchDesc {
    u64 patch_key{0};
    u32 revision{0};
    i64 tile_x{0};
    i64 tile_z{0};
    u32 lod{0};
    PatchTopology topology{PatchTopology::Heightfield};
    u32 neighbor_count{0};
    std::array<u64, kMaxPatchNeighbors> neighbors{};
};

struct TerrainPatchSetDesc {
    u32 asset_id{0};
    u32 revision{0};
    u32 patch_count{0};
    std::array<TerrainPatchDesc, kMaxTerrainPatches> patches{};
};

struct TerrainPatchPlan {
    u32 patch_count{0};
    u32 max_lod{0};
    u32 mesh_surface_count{0};
    i64 min_tile_x{0};
    i64 max_tile_x{0};
    i64 min_tile_z{0};
    i64 max_tile_z{0};
};

[[nodiscard]] TerrainError plan_terrain_patches(
    const TerrainPatchSetDesc& patches, TerrainPatchPlan& plan,
    TerrainDiagnostic& diagnostic) noexcept;
```

Semantics: asset ID/revision nonzero; patch count `1..64`; patch keys nonzero and unique; `(tile_x, tile_z)` pairs unique; patch revisions nonzero; LOD `<= 8`; topology allowlisted; neighbors are nonzero existing patch keys, unique per patch, not self, and count `<= 8`. Plan returns count, maximum LOD, mesh-surface count and signed tile bounds. Negative tile coordinates are valid.

## Splat/material layer metadata

```cpp
struct SplatLayerDesc {
    u32 layer_id{0};
    u32 material_asset_id{0};
    u32 revision{0};
    f32 weight{0.0f};
    u8 channel{0};
    u32 precedence{0};
};

struct SplatSetDesc {
    u32 asset_id{0};
    u32 revision{0};
    u32 layer_count{0};
    std::array<SplatLayerDesc, kMaxSplatLayers> layers{};
};

struct SplatPlan {
    u32 layer_count{0};
    u32 material_count{0};
    f32 total_weight{0.0f};
};

[[nodiscard]] TerrainError plan_splat_layers(
    const SplatSetDesc& splat, SplatPlan& plan,
    TerrainDiagnostic& diagnostic) noexcept;
```

Semantics: asset ID/revision nonzero; layer count `1..16`; layer IDs and material asset IDs nonzero; layer IDs unique; revisions nonzero; channel `0..3`; weight finite in `[0, 1]`; total weight finite and `<= 1.0` within `1e-6`. `material_count` is the number of distinct material asset IDs. No texture resource is created.

## Vegetation placement metadata

```cpp
struct VegetationGroupDesc {
    u64 group_key{0};
    u32 prototype_asset_id{0};
    u32 revision{0};
    u32 instance_count{0};
    u32 density_limit{0};
    bool collider_required{false};
    f32 min_x{0.0f};
    f32 min_z{0.0f};
    f32 max_x{0.0f};
    f32 max_z{0.0f};
};

struct VegetationSetDesc {
    u32 asset_id{0};
    u32 revision{0};
    u32 group_count{0};
    std::array<VegetationGroupDesc, kMaxVegetationGroups> groups{};
};

struct VegetationPlan {
    u32 group_count{0};
    u32 total_instances{0};
    u32 collider_group_count{0};
};

[[nodiscard]] TerrainError plan_vegetation(
    const VegetationSetDesc& vegetation, VegetationPlan& plan,
    TerrainDiagnostic& diagnostic) noexcept;
```

Semantics: asset ID/revision nonzero; group count `0..32`; group keys and prototype asset IDs nonzero; group keys unique; revisions nonzero; `1 <= instance_count <= density_limit <= 4096`; finite ordered bounds (`min < max`); checked total instances `<= 4096`. `collider_group_count` counts groups with `collider_required`. No instance buffer, transform or collider is created.

## Water body metadata

```cpp
struct WaterBodyDesc {
    u64 body_key{0};
    u32 revision{0};
    WaterClass water_class{WaterClass::Local};
    f32 min_x{0.0f};
    f32 min_z{0.0f};
    f32 max_x{0.0f};
    f32 max_z{0.0f};
    f32 surface_height{0.0f};
    f32 wave_amplitude{0.0f};
    f32 wave_frequency{0.0f};
    bool shore_complete{false};
};

struct WaterSetDesc {
    u32 asset_id{0};
    u32 revision{0};
    u32 body_count{0};
    std::array<WaterBodyDesc, kMaxWaterBodies> bodies{};
};

struct WaterPlan {
    u32 body_count{0};
    u32 ocean_count{0};
    u32 lake_count{0};
    u32 river_count{0};
    u32 local_count{0};
    u32 incomplete_shore_count{0};
    f32 min_surface{0.0f};
    f32 max_surface{0.0f};
};

[[nodiscard]] TerrainError plan_water(
    const WaterSetDesc& water, WaterPlan& plan,
    TerrainDiagnostic& diagnostic) noexcept;
```

Semantics: asset ID/revision nonzero; body count `0..32`; body keys nonzero and unique; revisions nonzero; class allowlisted; finite ordered bounds; surface height finite; wave amplitude finite `>= 0`; wave frequency finite `> 0`; shore completeness is reported but does not reject the plan. Plan returns class counts and surface-height bounds. No simulation, buoyancy or rendering is performed.

## Sky/environment profile metadata

```cpp
struct SkyProfileDesc {
    u32 profile_id{0};
    u32 revision{0};
    f32 time_of_day{0.0f};
    f32 sun_dir_x{0.0f};
    f32 sun_dir_y{0.0f};
    f32 sun_dir_z{0.0f};
    f32 moon_dir_x{0.0f};
    f32 moon_dir_y{0.0f};
    f32 moon_dir_z{0.0f};
    f32 cloud_coverage{0.0f};
    f32 fog_density{0.0f};
    QualityTier tier{QualityTier::Low};
};

struct SkySetDesc {
    u32 asset_id{0};
    u32 revision{0};
    u32 profile_count{0};
    std::array<SkyProfileDesc, kMaxSkyProfiles> profiles{};
};

struct SkyPlan {
    u32 profile_count{0};
    u32 low_count{0};
    u32 medium_count{0};
    u32 high_count{0};
    u32 ultra_count{0};
    f32 max_cloud_coverage{0.0f};
};

[[nodiscard]] TerrainError plan_sky(
    const SkySetDesc& sky, SkyPlan& plan,
    TerrainDiagnostic& diagnostic) noexcept;
```

Semantics: asset ID/revision nonzero; profile count `1..16`; profile IDs nonzero and unique; revisions nonzero; `time_of_day` finite in `[0, 24)`; sun and moon direction components finite with at least one nonzero component each; cloud coverage finite in `[0, 1]`; fog density finite `>= 0`; quality tier allowlisted. Plan returns tier counts and maximum cloud coverage. No light, atmosphere or renderer is created.

## Weather visual intent metadata

```cpp
struct WeatherZoneDesc {
    u32 zone_id{0};
    u32 revision{0};
    u32 source_tick{0};
    u32 source_revision{0};
    f32 rain_intensity{0.0f};
    f32 snow_intensity{0.0f};
    f32 wind_speed{0.0f};
    f32 fog_density{0.0f};
    bool authoritative_ack{false};
};

struct WeatherSetDesc {
    u32 asset_id{0};
    u32 revision{0};
    u32 zone_count{0};
    std::array<WeatherZoneDesc, kMaxWeatherZones> zones{};
};

struct WeatherPlan {
    u32 zone_count{0};
    u32 acknowledged_count{0};
    u32 pending_count{0};
    f32 max_rain{0.0f};
    f32 max_snow{0.0f};
    f32 max_wind{0.0f};
};

[[nodiscard]] TerrainError plan_weather(
    const WeatherSetDesc& weather, WeatherPlan& plan,
    TerrainDiagnostic& diagnostic) noexcept;
```

Semantics: asset ID/revision nonzero; zone count `0..32`; zone IDs nonzero and unique; revisions nonzero; source tick and source revision nonzero; rain/snow intensities finite in `[0, 1]`; wind speed and fog density finite `>= 0`; acknowledgement is reported but never fabricated. Plan returns acknowledged/pending counts and maxima. No climate simulation or gameplay authority is created.

## Common rules

All functions are `noexcept`, allocation-free, exception-free and use no file, network, audio, GPU, clock, thread or global state. Invalid input resets the plan to default and sets a typed diagnostic with the asset ID and index. All capacities are fixed at compile time.

## Test oracles

| ID | Scenario | Oracle |
|---|---|---|
| TER-01 | terrain patches | unique keys/tiles, LOD, neighbors, signed bounds |
| SPL-01 | splat layers | normalized weights, channels, precedence, material count |
| VEG-01 | vegetation | unique groups, density bounds, checked totals, collider count |
| WAT-01 | water | classes, finite bounds/waves, shore completeness, surface bounds |
| SKY-01 | sky profiles | time/direction/range limits, tier counts |
| CLI-01 | weather | tick/revision, finite intensities, ack counts |
| QLF-W401 | integrated | terrain -> splat -> vegetation -> water -> sky -> weather |
| QLF-W402 | deterministic repeat | identical plans/counts |
| QLF-W403 | failure recovery | typed error followed by valid operation |
| QLF-W404 | bounded overload | 10,000 attempts keep caps |

## Implementation allowlists

No production `.cpp`. One `INTERFACE` target and one test executable per implementation packet.

### `WORLD-04-03` (terrain patches)

1. `src/stormline/terrain/terrain_types.hpp`
2. `src/stormline/terrain/terrain_patch_plan.hpp`
3. `tests/core/world04_terrain_tests.cpp`
4. `CMakeLists.txt`
5. `.github/workflows/core01-internal-headless.yml`
6. `docs/evidence/NLE-PRPLAN-WORLD-04-03.md`

### `WORLD-04-04` (splat layers)

1. `src/stormline/terrain/splat_plan.hpp`
2. `tests/core/world04_splat_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-WORLD-04-04.md`

### `WORLD-04-05` (vegetation)

1. `src/stormline/terrain/vegetation_plan.hpp`
2. `tests/core/world04_vegetation_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-WORLD-04-05.md`

### `WORLD-04-06` (water)

1. `src/stormline/terrain/water_plan.hpp`
2. `tests/core/world04_water_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-WORLD-04-06.md`

### `WORLD-04-07` (sky)

1. `src/stormline/terrain/sky_plan.hpp`
2. `tests/core/world04_sky_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-WORLD-04-07.md`

### `WORLD-04-08` (weather)

1. `src/stormline/terrain/weather_plan.hpp`
2. `tests/core/world04_weather_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-WORLD-04-08.md`

### `WORLD-04-09` (qualification)

1. `tests/core/world04_qualification_tests.cpp`
2. `CMakeLists.txt`
3. `.github/workflows/core01-internal-headless.yml`
4. `docs/evidence/NLE-PRPLAN-WORLD-04-09.md`
