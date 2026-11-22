# DATA-05 INTERNAL_ONLY Bundle Contract v0 (NLE-PRPLAN-DATA-05-02)

**Status:** `CONTRACT PROPOSAL / NOT IMPLEMENTED / NO CODE AUTHORIZED`. **Base:** `23544da`. **ADR:** [ADR-0114](../adr/0114-data-05-governance-slice.md), [ADR-0013](../adr/0013-data-05-cooking-policy.md) planning-only. **WO:** [NLE-PRPLAN-DATA-05-02](../work-orders/NLE-PRPLAN-DATA-05-02.md).

## Objective

Freeze the first bounded DATA-05 logical API: target/cook plans, a Stormline-owned RLE codec, chunk store and streaming window, FNV-1a 64 manifest verification and incremental chunk reuse. No external codec, archive, signing, network, persistence, native I/O, public ABI or release.

## Admission and boundaries

- Formal dependencies are `DATA-03` and `DATA-04`; neither is qualified.
- DATA-05 owns target/cook plans, bounded RLE, chunk store/window, manifest fingerprints and reuse plans.
- DATA-01 VFS; DATA-02 identity; DATA-03 import metadata; DATA-04 scene documents; CORE-01 native OS; CORE-02 memory; CORE-03 jobs; CORE-04 ticks; CORE-06 diagnostics.
- No zstd/LZ4/Brotli/meshoptimizer/KTX2, archive library, signing key, HTTP stack or dependency is selected.

## Policy invariants

- **In-memory only.** No host file, archive, network or persistence.
- **Owned RLE only.** Compression is a bounded internal RLE codec; no external codec or wire-format claim.
- **Fingerprint is not authentication.** FNV-1a 64 is non-cryptographic and detects accidental mismatch only.
- **Stable identity.** Assets use DATA-02 `AssetId`; chunk IDs are opaque 64-bit values.
- **Bounded.** 64 assets/chunks/manifest entries/patch entries; 256-byte chunks; 1024-byte stream budget.
- **Range safe.** Offset/length arithmetic is checked; overlap/overflow fail closed.
- **Generation fenced.** Streaming binds a manifest generation; stale generation fails closed.
- **No persistence/recovery claim.**

## Internal API (logical, exact names)

```cpp
namespace stormline::data::bundle {

using u32 = std::uint32_t;
using u64 = std::uint64_t;
using u8 = std::uint8_t;

inline constexpr u32 kMaxCookAssets = 64;
inline constexpr u32 kMaxChunks = 64;
inline constexpr u32 kMaxChunkBytes = 256;
inline constexpr u32 kMaxManifestEntries = 64;
inline constexpr u32 kMaxStreamBytes = 1024;
inline constexpr u32 kMaxWarnings = 8;

enum class BundleError : std::uint8_t {
    None,
    InvalidArgument,
    InvalidTarget,
    UnsupportedFeature,
    DuplicateId,
    NotFound,
    CapacityFull,
    RangeOverflow,
    ChunkOverlap,
    StaleGeneration,
    FingerprintMismatch,
    CompressionLimit,
    PatchConflict,
    BufferFull
};

enum class TargetOs : std::uint8_t { Windows, Linux, Macos, Web };
enum class TargetArch : std::uint8_t { X64, Arm64, Wasm };

struct TargetProfile {
    u32 profile_id{0};
    TargetOs os{TargetOs::Windows};
    TargetArch arch{TargetArch::X64};
    u32 feature_flags{0};
    u32 quality_tier{0};
};
[[nodiscard]] BundleError validate_target(const TargetProfile& target) noexcept;

struct CookAsset {
    registry::AssetId asset{};
    u32 source_revision{0};
    u32 flags{0};
};
struct CookPlan {
    u32 profile_id{0};
    u32 asset_count{0};
    u32 estimated_bytes{0};
    u32 warning_count{0};
};
[[nodiscard]] BundleError make_cook_plan(
    const TargetProfile& target, std::span<const CookAsset> assets,
    CookPlan& out) noexcept;

[[nodiscard]] BundleError rle_encode(
    std::span<const u8> input, std::span<u8> output,
    u32& out_size) noexcept;
[[nodiscard]] BundleError rle_decode(
    std::span<const u8> encoded, std::span<u8> output,
    u32& out_size) noexcept;

[[nodiscard]] u64 fnv1a64(std::span<const u8> bytes) noexcept;

struct ManifestEntry {
    u64 chunk_id{0};
    u32 offset{0};
    u32 length{0};
    u64 fingerprint{0};
};
class BundleManifest final {
public:
    BundleManifest() noexcept = default;
    [[nodiscard]] BundleError init(u64 generation) noexcept;
    [[nodiscard]] BundleError add(const ManifestEntry& entry) noexcept;
    [[nodiscard]] BundleError find(u64 chunk_id, ManifestEntry& out) const noexcept;
    [[nodiscard]] u32 size() const noexcept;
    [[nodiscard]] u64 generation() const noexcept;
    [[nodiscard]] u32 total_bytes() const noexcept;
private:
    std::array<ManifestEntry, kMaxManifestEntries> entries_{};
    u32 size_{0};
    u64 generation_{0};
    u32 total_bytes_{0};
};

class ChunkStore final {
public:
    ChunkStore() noexcept = default;
    [[nodiscard]] BundleError put(u64 chunk_id, std::span<const u8> bytes) noexcept;
    [[nodiscard]] BundleError get(u64 chunk_id, std::span<u8> output, u32& out_size) const noexcept;
    [[nodiscard]] u32 size() const noexcept;
};

class StreamWindow final {
public:
    StreamWindow() noexcept = default;
    [[nodiscard]] BundleError init(
        const BundleManifest& manifest, const ChunkStore& store,
        u64 generation, u32 byte_budget) noexcept;
    [[nodiscard]] BundleError request(u64 chunk_id) noexcept;
    [[nodiscard]] u32 chunk_count() const noexcept;
    [[nodiscard]] u32 loaded_bytes() const noexcept;
    [[nodiscard]] u32 budget() const noexcept;
};

struct PatchPlan {
    u64 base_generation{0};
    u64 target_generation{0};
    u32 reuse_count{0};
    u32 fetch_count{0};
};
[[nodiscard]] BundleError make_patch_plan(
    const BundleManifest& base, const BundleManifest& target,
    PatchPlan& out) noexcept;

}  // namespace stormline::data::bundle
```

No implementation is provided. Names or semantics may be refined only by an audited contract correction before `DATA-05-03`.

## Semantics

- **Target:** profile ID nonzero; OS/arch known; feature flags subset `0x7F`; quality tier 1..3; otherwise `InvalidTarget`/`UnsupportedFeature`.
- **Cook plan:** 1..64 assets; valid `AssetId`; source revision nonzero; duplicate asset rejected; estimated bytes = `asset_count * 256` with checked cap; warning zero in this sequence.
- **RLE:** input 1..256 bytes; output pairs `(count 1..255, byte)`; runs split at 255; output too small returns `BufferFull` with required size; decode rejects empty/truncated pairs and output >256 with `CompressionLimit`.
- **Manifest:** generation nonzero; 1..64 entries; chunk ID nonzero and unique; offset+length ≤ 4096 checked; overlapping ranges rejected; total bytes bounded; fingerprint computed by caller.
- **Chunk store:** 1..64 chunks; ID nonzero and unique; bytes 1..256; `put` duplicate returns `DuplicateId`; `get` insufficient output `BufferFull` with required size; missing `NotFound`.
- **Stream:** generation must equal manifest generation; budget 1..1024; each requested chunk must exist in manifest and store, length must match, range already loaded is idempotent; budget overflow `CapacityFull`; missing `NotFound`; stale/wrong generation `StaleGeneration`.
- **Patch plan:** generations must differ; compare entries by chunk ID and fingerprint; equal fingerprint counts reuse, otherwise fetch; missing target/base generation mismatch `PatchConflict`; counts are bounded by manifest size.
- **Threading:** single-owner unless synchronized. No allocation, exception, compression library, file, network or global mutable state.

## Test oracles (future DATA-05-03..-08)

| ID | Scenario | Oracle |
|---|---|---|
| TGT-01 | target/cook plan | target validation; asset count/duplicates; estimated bytes; capacity |
| RLE-01 | owned RLE | roundtrip; run split; buffer full; truncated/invalid decode; limit |
| MAN-01 | manifest/fingerprint | generation/entry validation; overlap/overflow; FNV stability; verify |
| STR-01 | streaming window | generation fence; budget; idempotent request; missing; capacity |
| PAT-01 | incremental reuse | same/different fingerprint reuse/fetch; generation mismatch |
| QLF-B01 | integrated | target→cook→RLE→manifest→store→stream→patch |
| QLF-B02 | deterministic repeat | repeated sequence identical fingerprints/plans/counts |
| QLF-B03 | failure recovery | each typed error followed by valid operation |
| QLF-B04 | bounded overload | 10,000 target/RLE/manifest/stream/patch attempts keep capacities |

## Implementation allowlists

Headers are internal and header-only under `src/stormline/data/bundle/`. CMake adds one `INTERFACE` target and one test executable per packet; no production `.cpp`.

### `DATA-05-03` (target/cook plan)

1. `src/stormline/data/bundle/bundle_types.hpp`
2. `src/stormline/data/bundle/cook_plan.hpp`
3. `tests/core/data05_target_tests.cpp`
4. `CMakeLists.txt`
5. `.github/workflows/core01-internal-headless.yml`
6. `docs/evidence/NLE-PRPLAN-DATA-05-03.md`

### `DATA-05-04` (RLE)

1. `src/stormline/data/bundle/rle.hpp`
2. `tests/core/data05_rle_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-DATA-05-04.md`

### `DATA-05-05` (streaming)

1. `src/stormline/data/bundle/stream_window.hpp`
2. `tests/core/data05_stream_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-DATA-05-05.md`

### `DATA-05-06` (manifests)

1. `src/stormline/data/bundle/bundle_manifest.hpp`
2. `tests/core/data05_manifest_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-DATA-05-06.md`

### `DATA-05-07` (incremental update)

1. `src/stormline/data/bundle/patch_plan.hpp`
2. `tests/core/data05_patch_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-DATA-05-07.md`

### `DATA-05-08` (qualification)

1. `tests/core/data05_bundle_qualification_tests.cpp`
2. `CMakeLists.txt`
3. `.github/workflows/core01-internal-headless.yml`
4. `docs/evidence/NLE-PRPLAN-DATA-05-08.md`

`DATA-05-09` is documentary closeout only. Qualification is internal/CI-only; no external codec, signing, network, persistence, native filesystem, hardware, ABI or release claim.

## Stop / rollback / security

Stop on stale source, missing admission, external codec/signing/archive/network/persistence, host I/O, unbounded input, public ABI/release claim or HIGH/CRITICAL. Revert normally; never force push.
