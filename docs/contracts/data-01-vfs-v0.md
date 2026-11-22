# DATA-01 INTERNAL_ONLY Virtual File System Contract v0 (NLE-PRPLAN-DATA-01-02)

**Status:** `CONTRACT PROPOSAL / NOT IMPLEMENTED / NO CODE AUTHORIZED`. **Base:** `626a11c`. **ADR:** [ADR-0110](../adr/0110-data-01-governance-slice.md), [ADR-0009](../adr/0009-data-01-vfs-policy.md) planning-only. **WO:** [NLE-PRPLAN-DATA-01-02](../work-orders/NLE-PRPLAN-DATA-01-02.md).

## Objective

Freeze the first bounded DATA-01 logical API: ASCII-only normalized virtual paths, read-only in-memory mount table, deterministic overlay resolution, capabilities, bounded path cache and a memory-only storage abstraction. No native filesystem, archive codec, write path, network, dependency, public ABI or release is authorized.

## Admission and boundaries

- Formal `CORE-01` dependency remains; admission is limited to completed `CORE-01-03/-06/-07/-08/-12/-13` capabilities under ADR-0110/ADR-0086. CORE-01 module completion is **not** claimed.
- DATA-01 owns logical path validation, mount table, overlay resolution, capabilities, cache keys and storage-interface values.
- CORE-01 owns native OS bridge; CORE-02 memory; CORE-03 jobs/cancellation; CORE-04 ticks; CORE-06 diagnostics; DATA-02 identity; DATA-03 import/decode; DATA-04 serialization; DATA-05 bundles/streaming.
- No OS path is opened, resolved, stat'ed or canonicalized by this contract. No PhysicsFS/libzip/archive/native backend/network is selected.

## Policy invariants

- **ASCII-only first slice.** Valid path bytes are printable ASCII `0x21..0x7E` plus interior spaces; no Unicode/casefold normalization yet.
- **Relative only.** No leading `/`, drive/UNC, backslash, colon, NUL, control byte, empty component, `.`/`..`, trailing dot/space or Windows reserved name.
- **Read-only.** Mounts are read-only; no write/delete/rename/archive operation exists.
- **No sandbox claim.** Lexical validation is not OS confinement; native backends require separate G6 evidence.
- **Deterministic overlay.** Highest priority wins; equal priority uses lower `MountId`; shadowed matches are counted.
- **Generation fencing.** Mount add/remove increments a table generation; cache entries keyed by mount generation.
- **Bounded.** Fixed path capacity, mount count, capability count, cache entries and storage files; drops are typed and counted.
- **No host leakage.** Errors and values do not include host paths, descriptors or secrets.

## Internal API (logical, exact names)

```cpp
namespace stormline::data::vfs {

using u32 = std::uint32_t;
using u64 = std::uint64_t;
using i64 = std::int64_t;

inline constexpr u32 kMaxPathBytes = 512;
inline constexpr u32 kMaxComponentBytes = 64;
inline constexpr u32 kMaxMounts = 32;
inline constexpr u32 kMaxCapabilities = 16;
inline constexpr u32 kMaxCacheEntries = 64;
inline constexpr u32 kMaxStorageFiles = 64;
inline constexpr u32 kMaxStorageBytes = 256;

enum class VfsError : std::uint8_t {
    None,
    InvalidPath,
    PathEscape,
    InvalidMount,
    MountCollision,
    NotFound,
    Shadowed,
    Ambiguous,
    CapabilityDenied,
    ReadOnly,
    StaleMount,
    BufferFull,
    InvalidArgument,
    InternalFailure
};

struct VfsPath {
    std::array<char, kMaxPathBytes> bytes{};
    u32 length{0};
};

[[nodiscard]] VfsError make_path(std::string_view text, VfsPath& out) noexcept;
[[nodiscard]] std::string_view view(const VfsPath& path) noexcept;
[[nodiscard]] bool empty(const VfsPath& path) noexcept;
[[nodiscard]] bool is_prefix(const VfsPath& prefix, const VfsPath& path) noexcept;

struct MountId { u64 value{0}; };
[[nodiscard]] constexpr bool valid(MountId id) noexcept { return id.value != 0; }

enum class MountMode : std::uint8_t { ReadOnly };

struct MountInfo {
    MountId id{};
    VfsPath root{};
    u32 priority{0};
    MountMode mode{MountMode::ReadOnly};
    u64 generation{0};
};

class MountTable final {
public:
    MountTable() noexcept = default;
    [[nodiscard]] VfsError add(const MountInfo& mount) noexcept;
    [[nodiscard]] VfsError remove(MountId id) noexcept;
    [[nodiscard]] bool find(MountId id, MountInfo& out) const noexcept;
    [[nodiscard]] bool at(u32 index, MountInfo& out) const noexcept;
    [[nodiscard]] u32 size() const noexcept;
    [[nodiscard]] u64 generation() const noexcept;
    void clear() noexcept;
private:
    std::array<MountInfo, kMaxMounts> mounts_{};
    u32 size_{0};
    u64 generation_{0};
};

struct LookupResult {
    VfsError status{VfsError::NotFound};
    MountId mount{};
    VfsPath relative{};
    u64 generation{0};
    u32 shadowed_count{0};
};

[[nodiscard]] VfsError resolve(
    const MountTable& mounts, const VfsPath& path, LookupResult& out) noexcept;

struct WorkspaceId { u64 value{0}; };
[[nodiscard]] constexpr bool valid(WorkspaceId id) noexcept { return id.value != 0; }

struct AccessCapability {
    WorkspaceId workspace{};
    MountId mount{};
    bool read{false};
};

class CapabilitySet final {
public:
    CapabilitySet() noexcept = default;
    [[nodiscard]] VfsError grant(const AccessCapability& capability) noexcept;
    [[nodiscard]] VfsError revoke(WorkspaceId workspace, MountId mount) noexcept;
    [[nodiscard]] bool allows(WorkspaceId workspace, MountId mount) const noexcept;
    [[nodiscard]] u32 size() const noexcept;
private:
    std::array<AccessCapability, kMaxCapabilities> capabilities_{};
    u32 size_{0};
};

struct CacheKey {
    MountId mount{};
    u64 generation{0};
    VfsPath path{};
};

class PathCache final {
public:
    PathCache() noexcept = default;
    [[nodiscard]] VfsError put(
        MountId mount, u64 generation, const VfsPath& path,
        std::span<const std::uint8_t> bytes) noexcept;
    [[nodiscard]] VfsError get(
        MountId mount, u64 generation, const VfsPath& path,
        std::span<std::uint8_t> output, u32& out_size) noexcept;
    [[nodiscard]] u32 invalidate_mount(MountId mount) noexcept;
    void clear() noexcept;
    [[nodiscard]] u32 size() const noexcept;
    [[nodiscard]] u64 dropped() const noexcept;
private:
    struct Entry {
        CacheKey key{};
        std::array<std::uint8_t, kMaxStorageBytes> bytes{};
        u32 size{0};
    };
    std::array<Entry, kMaxCacheEntries> entries_{};
    u32 size_{0};
    u64 dropped_{0};
};

struct StorageDescriptor {
    MountId mount{};
    u64 generation{0};
    u32 flags{0};
};

class StorageBackend {
public:
    virtual ~StorageBackend() = default;
    [[nodiscard]] virtual VfsError read(
        const VfsPath& path, std::span<std::uint8_t> output,
        u32& out_size) noexcept = 0;
};

class MemoryStorage final : public StorageBackend {
public:
    MemoryStorage() noexcept = default;
    [[nodiscard]] VfsError put(
        const VfsPath& path, std::span<const std::uint8_t> bytes) noexcept;
    [[nodiscard]] VfsError read(
        const VfsPath& path, std::span<std::uint8_t> output,
        u32& out_size) noexcept override;
    [[nodiscard]] VfsError erase(const VfsPath& path) noexcept;
    [[nodiscard]] u32 size() const noexcept;
private:
    struct File {
        VfsPath path{};
        std::array<std::uint8_t, kMaxStorageBytes> bytes{};
        u32 size{0};
    };
    std::array<File, kMaxStorageFiles> files_{};
    u32 size_{0};
};

}  // namespace stormline::data::vfs
```

No implementation is provided. Names or semantics may be refined only by an audited contract correction before `DATA-01-03`.

## Semantics

- **Path validation:** `make_path` accepts empty as the root. For nonempty text: length ≤ 512; no leading/trailing `/`, no `//`, no backslash, `:`, NUL, control `0x00..0x1F` or byte `>0x7E`; components 1..64 bytes; no `.`/`..`; no component ending in `.` or space; no Windows reserved device name case-insensitively. It copies the original ASCII bytes without casefold.
- **Prefix:** `is_prefix("", path)` is true; `is_prefix("a", "a")` true; `is_prefix("a", "a/b")` true; `is_prefix("a", "ab")` false.
- **Mount table:** `add` requires valid ID, read-only mode, unique ID and unique normalized root, capacity; it stores table generation+1. `remove` requires an existing ID and shifts remaining entries; generation increments. `find`/`at` copy values; missing/out-of-range returns false. `clear` resets mounts and increments generation.
- **Overlay:** `resolve` selects the matching mount with highest priority; equal priority chooses lower `MountId`. It returns `None` with mount/relative path/generation and counts lower-priority matches; no match returns `NotFound`. A relative path is the suffix after `root/`; root mount returns the original path.
- **Capabilities:** `grant` requires valid workspace/mount, `read=true`, unique key; duplicate updates; full returns `BufferFull`. `revoke` missing returns `NotFound`. `allows` is true only for an exact read capability.
- **Cache:** key is `(mount, generation, path)`. `put` requires valid mount/generation, path, size ≤256; duplicate key updates; full returns `BufferFull` and increments `dropped`. `get` requires matching key/generation and enough output space; insufficient output returns `BufferFull` with required `out_size`; missing/stale returns `NotFound`/`StaleMount`.
- **Storage:** `MemoryStorage` is a fixed in-memory file table, no OS calls. `put` requires a valid path, size ≤256, unique path (update existing), capacity 64. `read` copies bytes; insufficient output returns `BufferFull` with required size; missing `NotFound`. `erase` missing `NotFound`.
- **Threading:** values are single-owner unless the caller synchronizes. No global mutable state, allocation, exception or blocking call.
- **Schema:** no serialization is implemented. Persistent paths/IDs require a later DATA schema and must not rely on host path strings.

## Test oracles (future DATA-01-03..-09)

| ID | Scenario | Oracle |
|---|---|---|
| PATH-01 | valid/invalid paths | empty root; max 512; component 64; reject leading/trailing `/`, `//`, backslash, `:`, NUL, control, non-ASCII, `.`/`..`, trailing dot/space, reserved device, overlong |
| MOUNT-01 | mount lifecycle | add/find/remove/clear; duplicate ID/root; read-only; capacity; generation increments |
| OVERLAY-01 | deterministic overlays | priority wins; equal priority lower ID; root/component boundaries; `shadowed_count`; no match |
| CAP-01 | capabilities | grant/revoke/allows; duplicate update; invalid workspace/mount/read=false; capacity |
| CACHE-01 | bounded cache | put/get; duplicate update; generation mismatch; insufficient output; invalidate mount; full/drop |
| STORAGE-01 | memory storage | put/read/erase; duplicate update; missing; too large; capacity; no OS calls |
| QLF-01 | integrated VFS | path→mount→overlay→capability→cache→memory storage |
| QLF-02 | deterministic repeat | repeated sequence yields identical path/mount/overlay/cache values |
| QLF-03 | failure recovery | each typed error followed by successful valid operation |
| QLF-04 | bounded overload | 10,000 mount/cache/storage attempts keep fixed capacities and count drops |

## Implementation allowlists

Headers are internal and header-only. CMake adds one `INTERFACE` target and one test executable per packet; no production `.cpp` is required. Any new file requires an audited contract correction.

### `DATA-01-03` (types + paths)

1. `src/stormline/data/vfs/vfs_types.hpp`
2. `src/stormline/data/vfs/vfs_path.hpp`
3. `tests/core/data01_path_tests.cpp`
4. `CMakeLists.txt` (additive DATA-01 target/tests)
5. `.github/workflows/core01-internal-headless.yml` (additive DATA-01 filters)
6. `docs/evidence/NLE-PRPLAN-DATA-01-03.md`

### `DATA-01-04` (mounts)

1. `src/stormline/data/vfs/vfs_mount.hpp`
2. `tests/core/data01_mount_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-DATA-01-04.md`

### `DATA-01-05` (overlays)

1. `src/stormline/data/vfs/vfs_overlay.hpp`
2. `tests/core/data01_overlay_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-DATA-01-05.md`

### `DATA-01-06` (capabilities)

1. `src/stormline/data/vfs/vfs_capability.hpp`
2. `tests/core/data01_capability_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-DATA-01-06.md`

### `DATA-01-07` (cache)

1. `src/stormline/data/vfs/vfs_cache.hpp`
2. `tests/core/data01_cache_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-DATA-01-07.md`

### `DATA-01-08` (memory storage abstraction)

1. `src/stormline/data/vfs/vfs_storage.hpp`
2. `tests/core/data01_storage_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-DATA-01-08.md`

### `DATA-01-09` (qualification)

1. `tests/core/data01_vfs_qualification_tests.cpp`
2. `CMakeLists.txt`
3. `.github/workflows/core01-internal-headless.yml`
4. `docs/evidence/NLE-PRPLAN-DATA-01-09.md`

`DATA-01-10` is documentary closeout only. Qualification is internal/CI-only; no native filesystem confinement, archive, write, hardware, ABI or release claim.

## Stop / rollback / security

Stop on stale source, missing admission, OS path/I/O, archive/native backend, write/delete/extract, host path leakage, traversal acceptance, secret exposure, unbounded capacity, public ABI/release claim or HIGH/CRITICAL. Unmerged: close the branch. After merge: normal revert PR; never force push.

No implementation is authorized by this contract. `DATA-01-03` requires its own G6 activation and explicit owner authorization.
