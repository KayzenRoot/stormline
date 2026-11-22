# DATA-02 INTERNAL_ONLY Asset Registry Contract v0 (NLE-PRPLAN-DATA-02-02)

**Status:** `CONTRACT PROPOSAL / NOT IMPLEMENTED / NO CODE AUTHORIZED`. **Base:** `5443021`. **ADR:** [ADR-0111](../adr/0111-data-02-governance-slice.md), [ADR-0010](../adr/0010-data-02-asset-identity.md) planning-only. **WO:** [NLE-PRPLAN-DATA-02-02](../work-orders/NLE-PRPLAN-DATA-02-02.md).

## Objective

Freeze the first bounded DATA-02 logical API: opaque 128-bit asset identity, project-scoped path mapping, tombstones, typed dependency edges with cycles/unresolved reporting, bounded tags, deterministic queries, typed metadata schema and ID-based references. State is fixed-capacity and in memory. No SQLite, serialization, persistence, native filesystem, MCP, network, public ABI or release is authorized.

## Admission and boundaries

- Formal `CORE-01` dependency remains; admission is limited to completed `CORE-01-03/-06/-07/-08/-12/-13` capabilities under ADR-0111/ADR-0086. CORE-01 module completion is **not** claimed.
- DATA-01 is `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`; DATA-02 consumes only its logical `VfsPath`.
- DATA-02 owns identity, path mapping, tombstones, dependency edges, tags, queries, metadata schema and reference resolution.
- DATA-01 owns logical VFS; CORE-01 native OS; CORE-02 memory; CORE-03 jobs; CORE-04 ticks; CORE-06 diagnostics; DATA-03 import/decode; DATA-04 serialization/transactions; DATA-05 bundles/streaming.
- No SQLite, BLAKE3, UUID library, JSON/CBOR, archive, network, editor UI or MCP raw access is selected.

## Policy invariants

- **Identity is not location.** `AssetId` is an opaque 128-bit value, never a path, digest or pointer.
- **Project scoping.** The same `VfsPath` may exist in different projects; path collision is checked within one `ProjectId`.
- **Tombstone, not erase.** Deleting marks `Tombstoned`; the ID remains visible and references resolve to a typed tombstone.
- **Bounded.** 64 assets, 128 dependency edges, 8 tags per asset, 8 metadata entries per asset and 64 query results.
- **Deterministic.** Query, tag and dependency outputs are sorted by `AssetId` ascending (`high`, then `low`).
- **Explicit graph truth.** Missing dependency targets are retained as unresolved; cycles are rejected on insertion.
- **No persistence.** No operation survives process exit; no serialization format exists.
- **No host leakage.** Errors contain codes, not host paths or secrets.

## Internal API (logical, exact names)

```cpp
namespace stormline::data::registry {

using u32 = std::uint32_t;
using u64 = std::uint64_t;

inline constexpr u32 kMaxAssets = 64;
inline constexpr u32 kMaxDependencies = 128;
inline constexpr u32 kMaxTagsPerAsset = 8;
inline constexpr u32 kMaxTagBytes = 32;
inline constexpr u32 kMaxMetadataEntriesPerAsset = 8;
inline constexpr u32 kMaxMetadataKeyBytes = 32;
inline constexpr u32 kMaxMetadataValueBytes = 64;
inline constexpr u32 kMaxQueryResults = 64;
inline constexpr u32 kSupportedSchemaVersion = 1;

enum class RegistryError : std::uint8_t {
    None,
    InvalidArgument,
    InvalidId,
    InvalidPath,
    DuplicateId,
    DuplicatePath,
    NotFound,
    Tombstoned,
    CapacityFull,
    DependencyCycle,
    UnresolvedReference,
    InvalidTag,
    InvalidSchema,
    RevisionConflict,
    BufferFull,
    InternalFailure
};

struct ProjectId { u64 value{0}; };
[[nodiscard]] constexpr bool valid(ProjectId id) noexcept { return id.value != 0; }

struct AssetId { u64 high{0}; u64 low{0}; };
[[nodiscard]] constexpr bool valid(AssetId id) noexcept {
    return id.high != 0 || id.low != 0;
}
[[nodiscard]] constexpr bool less(AssetId lhs, AssetId rhs) noexcept {
    return lhs.high != rhs.high ? lhs.high < rhs.high : lhs.low < rhs.low;
}

enum class AssetKind : std::uint8_t {
    Unknown, Texture, Mesh, Material, Audio, Scene, Script
};

enum class AssetStatus : std::uint8_t { Active, Tombstoned };

struct AssetRecord {
    AssetId id{};
    ProjectId project{};
    VfsPath path{};
    AssetKind kind{AssetKind::Unknown};
    AssetStatus status{AssetStatus::Active};
    u64 revision{1};
    u32 schema_version{0};
};

class AssetRegistry final {
public:
    AssetRegistry() noexcept = default;

    [[nodiscard]] RegistryError add(const AssetRecord& record) noexcept;
    [[nodiscard]] RegistryError find(AssetId id, AssetRecord& out) const noexcept;
    [[nodiscard]] RegistryError find_by_path(
        ProjectId project, const VfsPath& path, AssetId& out) const noexcept;
    [[nodiscard]] bool at(u32 index, AssetRecord& out) const noexcept;
    [[nodiscard]] RegistryError tombstone(AssetId id) noexcept;
    [[nodiscard]] u32 size() const noexcept;

    // DATA-02-04
    enum class DependencyKind : std::uint8_t { Runtime, Build, Editor };
    struct DependencyEdge {
        AssetId from{};
        AssetId to{};
        DependencyKind kind{DependencyKind::Runtime};
    };
    [[nodiscard]] RegistryError add_dependency(const DependencyEdge& edge) noexcept;
    [[nodiscard]] RegistryError remove_dependency(
        AssetId from, AssetId to, DependencyKind kind) noexcept;
    [[nodiscard]] bool has_dependency(
        AssetId from, AssetId to, DependencyKind kind) const noexcept;
    [[nodiscard]] RegistryError dependencies_of(
        AssetId from, std::span<AssetId> output, u32& out_count) const noexcept;
    [[nodiscard]] RegistryError dependents_of(
        AssetId to, std::span<AssetId> output, u32& out_count) const noexcept;
    [[nodiscard]] u32 dependency_count() const noexcept;
    [[nodiscard]] u32 unresolved_dependencies() const noexcept;

    // DATA-02-05
    struct Tag {
        std::array<char, kMaxTagBytes> bytes{};
        u32 length{0};
    };
    [[nodiscard]] static RegistryError make_tag(
        std::string_view text, Tag& out) noexcept;
    [[nodiscard]] RegistryError add_tag(AssetId id, const Tag& tag) noexcept;
    [[nodiscard]] RegistryError remove_tag(AssetId id, const Tag& tag) noexcept;
    [[nodiscard]] bool has_tag(AssetId id, const Tag& tag) const noexcept;
    [[nodiscard]] RegistryError tags_of(
        AssetId id, std::span<Tag> output, u32& out_count) const noexcept;

    // DATA-02-06
    struct AssetQuery {
        ProjectId project{};
        bool has_kind{false};
        AssetKind kind{AssetKind::Unknown};
        bool has_tag{false};
        Tag tag{};
        bool has_prefix{false};
        VfsPath prefix{};
        u32 offset{0};
    };
    [[nodiscard]] RegistryError query(
        const AssetQuery& filter, std::span<AssetId> output,
        u32& out_count, u32& next_offset) const noexcept;

    // DATA-02-07
    struct MetadataEntry {
        std::array<char, kMaxMetadataKeyBytes> key{};
        u32 key_length{0};
        std::array<char, kMaxMetadataValueBytes> value{};
        u32 value_length{0};
    };
    [[nodiscard]] static RegistryError make_metadata_entry(
        std::string_view key, std::string_view value, MetadataEntry& out) noexcept;
    [[nodiscard]] RegistryError set_metadata(
        AssetId id, u32 schema_version,
        std::span<const MetadataEntry> entries) noexcept;
    [[nodiscard]] RegistryError metadata(
        AssetId id, std::span<MetadataEntry> output, u32& out_count) const noexcept;

    // DATA-02-08
    struct AssetReference {
        AssetId asset{};
        AssetKind expected_kind{AssetKind::Unknown};
        u32 subasset{0};
    };
    [[nodiscard]] static RegistryError make_reference(
        AssetId id, AssetKind expected_kind, u32 subasset,
        AssetReference& out) noexcept;
    [[nodiscard]] RegistryError resolve_reference(
        const AssetReference& reference, AssetRecord& out) const noexcept;
    [[nodiscard]] RegistryError rename(
        AssetId id, const VfsPath& destination) noexcept;
    [[nodiscard]] RegistryError impact(
        AssetId id, std::span<AssetId> output, u32& out_count) const noexcept;
};

}  // namespace stormline::data::registry
```

No implementation is provided. Names or semantics may be refined only by an audited contract correction before `DATA-02-03`.

## Semantics

- **Add:** requires valid project/ID, nonempty active record, valid path, unique ID, unique `(project, path)`, capacity. Duplicate ID returns `DuplicateId`; duplicate path returns `DuplicatePath`; full returns `CapacityFull`. `revision` must be 1 and `schema_version` 0 for a new record.
- **Find:** missing returns `NotFound`; tombstoned record is returned with `Tombstoned` and copied to `out`.
- **Find by path:** exact project+path match; missing `NotFound`; tombstoned `Tombstoned`.
- **Tombstone:** missing `NotFound`; active becomes tombstoned and revision increments; already tombstoned returns `Tombstoned`. ID and path remain reserved.
- **Dependencies:** `from` must exist and be active; `to` may be missing (retained as unresolved) but must be valid and different from `from`. Duplicate same kind returns `None`; full returns `CapacityFull`; adding an edge that closes a cycle returns `DependencyCycle` and changes nothing. `dependencies_of`/`dependents_of` return unique IDs sorted ascending; insufficient output returns `BufferFull` with required `out_count`; missing source `NotFound`.
- **Tags:** tag text is 1..32 printable ASCII bytes `0x21..0x7E`, excluding `/`, `:`, backslash, whitespace and control; case-sensitive. Add requires active asset; duplicate tag returns `None`; per-asset capacity 8 returns `CapacityFull`; remove missing `NotFound`. `tags_of` preserves insertion order.
- **Query:** filters active assets of the exact project, optionally kind, tag and DATA-01 component-boundary path prefix. Results are `AssetId` ascending. `offset` skips matches; output capacity is caller-owned; `next_offset` is 0 when exhausted, otherwise the next offset. Empty output returns `InvalidArgument`. Unknown kind/tag/prefix simply match none.
- **Schema:** schema version must equal 1; entries 0..8; keys unique, 1..32 printable ASCII `[A-Za-z0-9_.-]`; values 0..64 printable ASCII `0x20..0x7E`; invalid returns `InvalidSchema`/`InvalidArgument`. `set_metadata` replaces the full entry set atomically and sets `schema_version`. Inactive asset returns `Tombstoned`/`NotFound`. `metadata` insufficient output returns `BufferFull` with required count.
- **References:** `make_reference` requires a valid ID; expected kind may be `Unknown` (any); subasset is opaque. `resolve_reference` returns `NotFound`, `Tombstoned` or `InvalidArgument` (kind mismatch) without returning a record on failure. Rename requires active asset, valid path, unique `(project, path)`, and preserves ID; it increments revision and returns `DuplicatePath` on collision. Existing references resolve unchanged because they hold the ID. `impact` returns unique transitive dependents, excluding the asset itself, sorted ascending, bounded by `kMaxAssets`; missing source `NotFound`; insufficient output `BufferFull` with required count.
- **Threading:** values are single-owner unless the caller synchronizes. No global mutable state, allocation, exception, blocking call, file or network access.

## Test oracles (future DATA-02-03..-09)

| ID | Scenario | Oracle |
|---|---|---|
| ID-01 | stable identity | add/find/path lookup; duplicate ID/path; tombstone preserves ID/path; capacity; revision increment |
| DEP-01 | dependency graph | add/remove/duplicate; missing target unresolved; cycle rejected; sorted forward/reverse edges; capacity |
| TAG-01 | tags | valid/invalid ASCII; duplicate; per-asset quota; add/remove/has/list order |
| QUERY-01 | deterministic queries | project/kind/tag/prefix filters; ascending IDs; offset/cursor; empty output; bounded results |
| SCHEMA-01 | metadata schema | version 1 only; entry/key/value limits; duplicate keys; atomic replace; capacity; tombstone |
| REF-01 | references | resolve active/tombstoned/kind mismatch; rename preserves ID and references; path collision; impact transitive |
| QLF-R01 | integrated registry | add assets→tags→metadata→dependencies→query→reference→rename→impact |
| QLF-R02 | deterministic repeat | repeated sequence yields identical IDs/order/status/edges/tags/metadata |
| QLF-R03 | failure recovery | each typed error followed by a successful valid operation |
| QLF-R04 | bounded overload | 10,000 add/edge/tag/query attempts keep fixed capacities and count unresolved/overflow |

## Implementation allowlists

Headers are internal and header-only under `src/stormline/data/registry/`. CMake adds one `INTERFACE` target and one test executable per packet; no production `.cpp` is required. Any new file requires an audited contract correction.

### `DATA-02-03` (identity and path mapping)

1. `src/stormline/data/registry/registry_types.hpp`
2. `src/stormline/data/registry/asset_registry.hpp`
3. `tests/core/data02_id_tests.cpp`
4. `CMakeLists.txt` (additive DATA-02 target/tests)
5. `.github/workflows/core01-internal-headless.yml` (additive DATA-02 filters)
6. `docs/evidence/NLE-PRPLAN-DATA-02-03.md`

### `DATA-02-04` (dependencies)

1. `src/stormline/data/registry/asset_registry.hpp` (additive dependency methods)
2. `tests/core/data02_dependency_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-DATA-02-04.md`

### `DATA-02-05` (tags)

1. `src/stormline/data/registry/asset_registry.hpp` (additive tag methods)
2. `tests/core/data02_tag_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-DATA-02-05.md`

### `DATA-02-06` (queries)

1. `src/stormline/data/registry/asset_registry.hpp` (additive query method)
2. `tests/core/data02_query_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-DATA-02-06.md`

### `DATA-02-07` (schema)

1. `src/stormline/data/registry/asset_registry.hpp` (additive metadata methods)
2. `tests/core/data02_schema_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-DATA-02-07.md`

### `DATA-02-08` (references)

1. `src/stormline/data/registry/asset_registry.hpp` (additive reference/rename/impact methods)
2. `tests/core/data02_reference_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-DATA-02-08.md`

### `DATA-02-09` (qualification)

1. `tests/core/data02_registry_qualification_tests.cpp`
2. `CMakeLists.txt`
3. `.github/workflows/core01-internal-headless.yml`
4. `docs/evidence/NLE-PRPLAN-DATA-02-09.md`

`DATA-02-10` is documentary closeout only. Qualification is internal/CI-only; no persistence, database, native filesystem, hardware, ABI or release claim.

## Stop / rollback / security

Stop on stale source, missing admission, SQLite/serialization/persistence/native I/O, ID reuse, path or tombstone ambiguity, unbounded traversal, host path leakage, secret exposure, public ABI/release claim or HIGH/CRITICAL. Unmerged: close the branch. After merge: normal revert PR; never force push.

No implementation is authorized by this contract. `DATA-02-03` requires its own G6 activation and explicit owner authorization.
