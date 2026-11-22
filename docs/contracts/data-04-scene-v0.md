# DATA-04 INTERNAL_ONLY Scene Document Contract v0 (NLE-PRPLAN-DATA-04-02)

**Status:** `CONTRACT PROPOSAL / NOT IMPLEMENTED / NO CODE AUTHORIZED`. **Base:** `50836b4`. **ADR:** [ADR-0113](../adr/0113-data-04-governance-slice.md), [ADR-0012](../adr/0012-data-04-scene-schema-policy.md) planning-only. **WO:** [NLE-PRPLAN-DATA-04-02](../work-orders/NLE-PRPLAN-DATA-04-02.md).

## Objective

Freeze the first bounded DATA-04 logical API: versioned schema descriptors, declarative in-memory scene documents with entities/components/asset references, atomic patches and semantic entity diffs. No JSON/CBOR, schema validator, canonicalization, persistence, migration journal, native I/O, network, public ABI or release is authorized.

## Admission and boundaries

- Formal dependencies are `CORE-05` and `DATA-02`; neither is module-qualified.
- DATA-04 owns scene schema descriptors, declarative documents, bounded patches and semantic diffs.
- DATA-01 VFS; DATA-02 identity; DATA-03 import metadata; CORE-05 typed math/IDs; CORE-01 native OS; CORE-02 memory; CORE-03 jobs; CORE-04 ticks; CORE-06 diagnostics; DATA-05 bundles.
- No JSON/CBOR codec, schema validator, database, serialization, canonicalization library or network is selected.

## Policy invariants

- **No byte format.** Values are in memory; no parse/serialize/roundtrip claim.
- **Stable opaque IDs.** Scene/entity/component IDs are 64-bit values, never array indices or pointers.
- **Versioned schema.** Schema ID 1, version 1..3, capabilities subset `0x3`, canonicalization version 1.
- **Bounded.** 64 entities, 128 components, 64 asset references, 64 patch operations, 128 diff entries.
- **Atomic patches.** Failed patches leave the document unchanged; stale base revision is rejected.
- **Explicit graph.** Duplicate IDs, missing parents and parent cycles fail closed.
- **Identity via DATA-02.** Asset references carry `AssetId`.
- **No persistence or format claim.**

## Internal API (logical, exact names)

```cpp
namespace stormline::data::scene {

using u32 = std::uint32_t;
using u64 = std::uint64_t;

inline constexpr u32 kMaxEntities = 64;
inline constexpr u32 kMaxComponents = 128;
inline constexpr u32 kMaxAssetRefs = 64;
inline constexpr u32 kMaxPatchOps = 64;
inline constexpr u32 kMaxDiffs = 128;
inline constexpr u32 kMaxNameBytes = 32;

enum class SceneError : std::uint8_t {
    None,
    InvalidArgument,
    InvalidSchema,
    UnsupportedSchema,
    DuplicateId,
    NotFound,
    ParentCycle,
    StaleRevision,
    CapacityFull,
    InvalidPatch,
    BufferFull
};

struct SceneId { u64 value{0}; };
struct EntityId { u64 value{0}; };
struct ComponentId { u64 value{0}; };
[[nodiscard]] constexpr bool valid(SceneId id) noexcept { return id.value != 0; }
[[nodiscard]] constexpr bool valid(EntityId id) noexcept { return id.value != 0; }
[[nodiscard]] constexpr bool valid(ComponentId id) noexcept { return id.value != 0; }

struct SchemaDescriptor {
    u32 schema_id{0};
    u32 version{0};
    u32 capabilities{0};
    u32 canonicalization_version{0};
};
[[nodiscard]] SceneError validate_schema(const SchemaDescriptor& schema) noexcept;

struct EntityRecord {
    EntityId id{};
    EntityId parent{};
    u32 child_order{0};
    bool enabled{true};
    std::array<char, kMaxNameBytes> name{};
    u32 name_length{0};
};
struct ComponentRecord {
    ComponentId id{};
    EntityId entity{};
    u32 type_id{0};
    u32 type_version{0};
};
struct AssetRef {
    registry::AssetId asset{};
    EntityId entity{};
    u32 role{0};
};

class SceneDocument final {
public:
    SceneDocument() noexcept = default;
    [[nodiscard]] SceneError init(
        SceneId scene, registry::ProjectId project,
        const SchemaDescriptor& schema) noexcept;
    [[nodiscard]] SceneError add_entity(const EntityRecord& entity) noexcept;
    [[nodiscard]] SceneError add_component(const ComponentRecord& component) noexcept;
    [[nodiscard]] SceneError add_asset_ref(const AssetRef& ref) noexcept;
    [[nodiscard]] SceneError find_entity(EntityId id, EntityRecord& out) const noexcept;
    [[nodiscard]] SceneError find_component(
        ComponentId id, ComponentRecord& out) const noexcept;
    [[nodiscard]] bool entity_at(u32 index, EntityRecord& out) const noexcept;
    [[nodiscard]] SceneId scene() const noexcept;
    [[nodiscard]] registry::ProjectId project() const noexcept;
    [[nodiscard]] SchemaDescriptor schema() const noexcept;
    [[nodiscard]] u64 revision() const noexcept;
    [[nodiscard]] u32 entity_count() const noexcept;
    [[nodiscard]] u32 component_count() const noexcept;
    [[nodiscard]] u32 asset_ref_count() const noexcept;
};

enum class PatchOp : std::uint8_t { AddEntity, RemoveEntity, SetEnabled };
struct PatchOperation {
    PatchOp kind{PatchOp::AddEntity};
    EntityRecord entity{};
    EntityId target{};
    bool enabled{true};
};
struct ScenePatch {
    u64 operation_id{0};
    u64 base_revision{0};
    SceneId scene{};
};
[[nodiscard]] SceneError apply_patch(
    SceneDocument& document, const ScenePatch& patch,
    std::span<const PatchOperation> operations) noexcept;

enum class DiffKind : std::uint8_t { Added, Removed, EnabledChanged, NameChanged };
struct DiffEntry {
    EntityId entity{};
    DiffKind kind{DiffKind::Added};
};
[[nodiscard]] SceneError diff(
    const SceneDocument& base, const SceneDocument& next,
    std::span<DiffEntry> output, u32& out_count) noexcept;

}  // namespace stormline::data::scene
```

No implementation is provided. Names or semantics may be refined only by an audited contract correction before `DATA-04-03`.

## Semantics

- **Schema:** `schema_id == 1`, `version` 1..3, `capabilities` subset `0x3`, `canonicalization_version == 1`; otherwise `InvalidSchema`/`UnsupportedSchema`.
- **Init:** requires valid scene/project and valid schema; initial revision is 1. Re-init replaces the empty document.
- **Entity:** requires valid ID, nonzero name 1..32 printable ASCII excluding `/`, `:`, backslash and control; parent zero or an existing entity; duplicate ID `DuplicateId`; parent cycle `ParentCycle`; capacity 64. Parent is checked and cycle-detected on insert.
- **Component:** valid component ID, existing entity, nonzero type/version, duplicate ID `DuplicateId`, capacity 128.
- **AssetRef:** valid DATA-02 `AssetId`, existing entity, capacity 64; duplicates allowed only with a different role.
- **Patch:** operation ID nonzero, scene matches, base revision equals current; each operation is applied to a copy; any failure leaves the original unchanged; success increments revision. `AddEntity` uses entity insertion rules; `RemoveEntity` removes the entity and its components/asset refs; `SetEnabled` requires an existing entity.
- **Diff:** compares entities by stable ID; emits `Added`, `Removed`, `EnabledChanged`, `NameChanged`, sorted by entity ID then kind; duplicate kinds are not emitted; output insufficient returns `BufferFull` with required count.
- **Threading:** single-owner unless synchronized. No allocation, exception, file, JSON/CBOR, database or network.

## Test oracles (future DATA-04-03..-07)

| ID | Scenario | Oracle |
|---|---|---|
| SCH-01 | schema versions | valid 1/2/3, invalid id/version/capability/canonicalization |
| DOC-01 | declarative document | entity/component/asset-ref add/find/at/count; duplicate IDs; name/parent/capacity |
| PATCH-01 | atomic patches | add/remove/set-enabled; stale revision; failed patch unchanged; revision bump |
| DIFF-01 | semantic diff | added/removed/enabled/name, sorted stable IDs, buffer full |
| QLF-S01 | integrated | init→entities→components→refs→patch→diff |
| QLF-S02 | deterministic repeat | repeated sequence yields identical IDs/revisions/diff |
| QLF-S03 | failure recovery | each typed error followed by a valid operation |
| QLF-S04 | bounded overload | 10,000 entity/component/ref/patch attempts keep fixed capacities |

## Implementation allowlists

Headers are internal and header-only under `src/stormline/data/scene/`. CMake adds one `INTERFACE` target and one test executable per packet; no production `.cpp`. Any new file requires an audited contract correction.

### `DATA-04-03` (schemas)

1. `src/stormline/data/scene/scene_types.hpp`
2. `src/stormline/data/scene/scene_schema.hpp`
3. `tests/core/data04_schema_tests.cpp`
4. `CMakeLists.txt`
5. `.github/workflows/core01-internal-headless.yml`
6. `docs/evidence/NLE-PRPLAN-DATA-04-03.md`

### `DATA-04-04` (declarative document)

1. `src/stormline/data/scene/scene_document.hpp`
2. `tests/core/data04_document_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-DATA-04-04.md`

### `DATA-04-05` (compatible changes)

1. `src/stormline/data/scene/scene_patch.hpp`
2. `tests/core/data04_patch_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-DATA-04-05.md`

### `DATA-04-06` (semantic diffs)

1. `src/stormline/data/scene/scene_diff.hpp`
2. `tests/core/data04_diff_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-DATA-04-06.md`

### `DATA-04-07` (qualification)

1. `tests/core/data04_scene_qualification_tests.cpp`
2. `CMakeLists.txt`
3. `.github/workflows/core01-internal-headless.yml`
4. `docs/evidence/NLE-PRPLAN-DATA-04-07.md`

`DATA-04-08` is documentary closeout only. Qualification is internal/CI-only; no JSON/CBOR, persistence, native filesystem, hardware, ABI or release claim.

## Stop / rollback / security

Stop on stale source, missing admission, codec/format/persistence/native I/O, dependency selection, unbounded input, host path leakage, public ABI/release claim or HIGH/CRITICAL. Revert normally; never force push.

No implementation is authorized by this contract. `DATA-04-03` requires its own G6 activation.
