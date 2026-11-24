# WORLD-05 internal procedural generation metadata contract v0

**Status:** `APPROVED CONTRACT / INTERNAL_ONLY / NO GENERATION RUNTIME`. **ADR:** [ADR-0131](../adr/0131-world-05-internal-procedural-generation-metadata.md). **Architecture:** [world-05-internal-procedural-generation-metadata](../architecture/world-05-internal-procedural-generation-metadata.md). **Governance:** [world-05-governance-v0](world-05-governance-v0.md).

Freeze the bounded logical API for seed/domain metadata, generator graph topology, rules, biome classification, geometry recipes and content generator metadata. No graph evaluation, RNG/noise, WFC solver, asset I/O, cook/cache, source writes, mesh generation, GPU preview, renderer, editor, performance, ABI or release.

## Namespace and common types

Header-only under `src/stormline/procedural/`, namespace `stormline::procedural`.

```cpp
using u8 = std::uint8_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using i64 = std::int64_t;
using f32 = float;

inline constexpr u32 kMaxSeedDomains = 16;
inline constexpr u32 kMaxGraphNodes = 64;
inline constexpr u32 kMaxGraphEdges = 128;
inline constexpr u32 kMaxGraphDepth = 16;
inline constexpr u32 kMaxNodeFanOut = 8;
inline constexpr u32 kMaxRules = 32;
inline constexpr u32 kMaxBiomeZones = 16;
inline constexpr u32 kMaxGeometryRecipes = 32;
inline constexpr u32 kMaxContentGenerators = 32;
inline constexpr u32 kMaxGeneratorOutputCap = 4096;
inline constexpr u32 kMaxTotalOutputCap = 65536;

enum class ProcError : std::uint8_t {
    None,
    InvalidArgument,
    DuplicateId,
    NotFound,
    CapacityFull,
    NonFiniteValue,
    OutOfRange,
    SeedInvalid,
    GraphInvalid,
    RuleInvalid,
    BiomeInvalid,
    GeometryInvalid,
    GeneratorInvalid,
    CycleDetected,
    Incomplete,
    Unsupported
};

enum class PrimitiveKind : std::uint8_t { Box, Plane, Sphere, Heightfield };
enum class GeneratorCategory : std::uint8_t { Biome, Geometry, Placement, Rule };

struct ProcDiagnostic {
    ProcError code{ProcError::None};
    u32 source_id{0};
    u32 index{0};
};
```

## Seed/domain metadata

```cpp
struct SeedDomainDesc {
    u32 domain_id{0};
    u32 derivation_version{0};
    u32 channel_count{0};
};

struct SeedSetDesc {
    u32 project_id{0};
    u32 graph_id{0};
    u64 seed_high{0};
    u64 seed_low{0};
    u32 domain_count{0};
    std::array<SeedDomainDesc, kMaxSeedDomains> domains{};
};

struct SeedPlan {
    u32 domain_count{0};
    u32 total_channels{0};
    u64 seed_high{0};
    u64 seed_low{0};
};

[[nodiscard]] ProcError plan_seed_domains(
    const SeedSetDesc& seed, SeedPlan& plan,
    ProcDiagnostic& diagnostic) noexcept;
```

Semantics: project/graph IDs nonzero; seed halves not both zero; domain count `1..16`; domain IDs and derivation versions nonzero and unique; channel count `1..8`; checked total channels `<= 128`. Plan echoes seed halves and domain/channel counts; no random stream is produced.

## Generator graph topology metadata

```cpp
struct GraphNodeDesc {
    u32 node_id{0};
    u32 algorithm_id{0};
    u32 algorithm_version{0};
    u32 input_type{0};
    u32 output_type{0};
    u32 fan_out{0};
};

struct GraphEdgeDesc {
    u32 edge_id{0};
    u32 from_node{0};
    u32 to_node{0};
};

struct GraphSetDesc {
    u32 graph_id{0};
    u32 revision{0};
    u32 node_count{0};
    u32 edge_count{0};
    std::array<GraphNodeDesc, kMaxGraphNodes> nodes{};
    std::array<GraphEdgeDesc, kMaxGraphEdges> edges{};
};

struct GraphPlan {
    u32 node_count{0};
    u32 edge_count{0};
    u32 root_count{0};
    u32 leaf_count{0};
    u32 max_depth{0};
};

[[nodiscard]] ProcError plan_graph(
    const GraphSetDesc& graph, GraphPlan& plan,
    ProcDiagnostic& diagnostic) noexcept;
```

Semantics: graph ID/revision nonzero; node count `1..64`; node IDs, algorithm IDs and versions nonzero and unique; input/output types nonzero; fan-out `<= 8`; edge count `<= 128`; edge IDs unique; endpoints exist; no self-edge, duplicate edge or cycle. Plan returns node/edge counts, roots, leaves and DAG depth `<= 16`. No node is evaluated.

## Rule metadata

```cpp
struct RuleDesc {
    u32 rule_id{0};
    u32 revision{0};
    u32 condition_code{0};
    f32 weight{0.0f};
    u32 priority{0};
    bool enabled{false};
};

struct RuleSetDesc {
    u32 graph_id{0};
    u32 revision{0};
    u32 rule_count{0};
    std::array<RuleDesc, kMaxRules> rules{};
};

struct RulePlan {
    u32 rule_count{0};
    u32 enabled_count{0};
    f32 total_weight{0.0f};
    u32 max_priority{0};
};

[[nodiscard]] ProcError plan_rules(
    const RuleSetDesc& rules, RulePlan& plan,
    ProcDiagnostic& diagnostic) noexcept;
```

Semantics: graph ID/revision nonzero; rule count `0..32`; rule IDs, revisions and condition codes nonzero and unique; weight finite in `[0, 1]`; priority metadata; plan returns enabled count, total weight and maximum priority. No rule is evaluated.

## Biome classification metadata

```cpp
struct BiomeZoneDesc {
    u32 zone_id{0};
    u32 revision{0};
    u32 palette_asset_id{0};
    f32 weight{0.0f};
    u32 priority{0};
    bool enabled{false};
};

struct BiomeSetDesc {
    u32 graph_id{0};
    u32 revision{0};
    u32 zone_count{0};
    std::array<BiomeZoneDesc, kMaxBiomeZones> zones{};
};

struct BiomePlan {
    u32 zone_count{0};
    u32 enabled_count{0};
    f32 total_weight{0.0f};
    u32 max_priority{0};
};

[[nodiscard]] ProcError plan_biomes(
    const BiomeSetDesc& biomes, BiomePlan& plan,
    ProcDiagnostic& diagnostic) noexcept;
```

Semantics: graph ID/revision nonzero; zone count `1..16`; zone IDs and revisions nonzero and unique; palette asset IDs nonzero; weight finite in `[0, 1]`; plan returns enabled count, total weight and maximum priority. No classification is computed.

## Geometry recipe metadata

```cpp
struct GeometryRecipeDesc {
    u32 recipe_id{0};
    u32 revision{0};
    PrimitiveKind primitive{PrimitiveKind::Box};
    u32 source_asset_id{0};
    f32 unit_scale{1.0f};
    u32 lod_count{1};
};

struct GeometrySetDesc {
    u32 graph_id{0};
    u32 revision{0};
    u32 recipe_count{0};
    std::array<GeometryRecipeDesc, kMaxGeometryRecipes> recipes{};
};

struct GeometryPlan {
    u32 recipe_count{0};
    u32 box_count{0};
    u32 plane_count{0};
    u32 sphere_count{0};
    u32 heightfield_count{0};
    f32 max_unit_scale{0.0f};
};

[[nodiscard]] ProcError plan_geometry(
    const GeometrySetDesc& geometry, GeometryPlan& plan,
    ProcDiagnostic& diagnostic) noexcept;
```

Semantics: graph ID/revision nonzero; recipe count `0..32`; recipe IDs and revisions nonzero and unique; primitive allowlisted; source asset ID nonzero; unit scale finite `> 0`; LOD count `1..8`; plan returns primitive counts and maximum unit scale. No mesh or geometry buffer is produced.

## Content generator metadata

```cpp
struct ContentGeneratorDesc {
    u32 generator_id{0};
    u32 revision{0};
    GeneratorCategory category{GeneratorCategory::Biome};
    u32 seed_domain_id{0};
    u32 output_cap{0};
};

struct GeneratorSetDesc {
    u32 graph_id{0};
    u32 revision{0};
    u32 generator_count{0};
    std::array<ContentGeneratorDesc, kMaxContentGenerators> generators{};
};

struct GeneratorPlan {
    u32 generator_count{0};
    u32 biome_count{0};
    u32 geometry_count{0};
    u32 placement_count{0};
    u32 rule_count{0};
    u32 total_output_cap{0};
};

[[nodiscard]] ProcError plan_generators(
    const GeneratorSetDesc& generators, GeneratorPlan& plan,
    ProcDiagnostic& diagnostic) noexcept;
```

Semantics: graph ID/revision nonzero; generator count `0..32`; generator IDs and revisions nonzero and unique; category allowlisted; seed domain ID nonzero; per-generator output cap `1..4096`; checked total `<= 65536`; plan returns category counts and total cap. No artifact is produced.

## Common rules

All functions are `noexcept`, allocation-free, exception-free and use no file, network, audio, GPU, clock, thread, random source or global state. Invalid input resets the plan to default and sets a typed diagnostic with the graph/project ID and index. All capacities are fixed at compile time.

## Test oracles

| ID | Scenario | Oracle |
|---|---|---|
| SEED-01 | seeds/domains | nonzero identity, unique domains, channel bounds |
| GRAPH-01 | graph topology | unique nodes/edges, endpoints, DAG, depth/fan-out |
| RULE-01 | rules | condition/weight ranges, uniqueness, precedence |
| BIOME-01 | biomes | unique zones, palette refs, weight ranges |
| GEO-01 | geometry recipes | primitive/source/unit/LOD bounds |
| GEN-01 | content generators | unique IDs, categories, per-total caps |
| QLF-W501 | integrated | seed -> graph -> rule -> biome -> geometry -> generator |
| QLF-W502 | deterministic repeat | identical plans/counts |
| QLF-W503 | failure recovery | typed error followed by valid operation |
| QLF-W504 | bounded overload | 10,000 attempts keep caps |

## Implementation allowlists

No production `.cpp`. One `INTERFACE` target and one test executable per implementation packet.

### `WORLD-05-03` (seeds)

1. `src/stormline/procedural/procedural_types.hpp`
2. `src/stormline/procedural/seed_plan.hpp`
3. `tests/core/world05_seed_tests.cpp`
4. `CMakeLists.txt`
5. `.github/workflows/core01-internal-headless.yml`
6. `docs/evidence/NLE-PRPLAN-WORLD-05-03.md`

### `WORLD-05-04` (graphs)

1. `src/stormline/procedural/graph_plan.hpp`
2. `tests/core/world05_graph_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-WORLD-05-04.md`

### `WORLD-05-05` (rules)

1. `src/stormline/procedural/rule_plan.hpp`
2. `tests/core/world05_rule_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-WORLD-05-05.md`

### `WORLD-05-06` (biomes)

1. `src/stormline/procedural/biome_plan.hpp`
2. `tests/core/world05_biome_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-WORLD-05-06.md`

### `WORLD-05-07` (geometry)

1. `src/stormline/procedural/geometry_plan.hpp`
2. `tests/core/world05_geometry_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-WORLD-05-07.md`

### `WORLD-05-08` (content generators)

1. `src/stormline/procedural/generator_plan.hpp`
2. `tests/core/world05_generator_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-WORLD-05-08.md`

### `WORLD-05-09` (qualification)

1. `tests/core/world05_qualification_tests.cpp`
2. `CMakeLists.txt`
3. `.github/workflows/core01-internal-headless.yml`
4. `docs/evidence/NLE-PRPLAN-WORLD-05-09.md`
