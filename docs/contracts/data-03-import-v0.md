# DATA-03 INTERNAL_ONLY Import Planning Contract v0 (NLE-PRPLAN-DATA-03-02)

**Status:** `CONTRACT PROPOSAL / NOT IMPLEMENTED / NO CODE AUTHORIZED`. **Base:** `ba715a2`. **ADR:** [ADR-0112](../adr/0112-data-03-governance-slice.md), [ADR-0011](../adr/0011-data-03-import-policy.md) planning-only. **WO:** [NLE-PRPLAN-DATA-03-02](../work-orders/NLE-PRPLAN-DATA-03-02.md).

## Objective

Freeze the first bounded DATA-03 logical API: importer descriptors, signature sniffing, import plans, caller-supplied texture/animation/audio metadata validation and bounded provenance receipts. No image/mesh/audio decoder, conversion, archive, native file access, serialization, persistence, MCP, network, public ABI or release is authorized.

## Admission and boundaries

- Formal `DATA-02` dependency; DATA-02 is `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`.
- DATA-01 owns `VfsPath`; DATA-02 owns `AssetId`; DATA-03 owns importer descriptions, sniffing, metadata validation and receipts.
- CORE-01 native OS; CORE-02 memory; CORE-03 jobs; CORE-04 ticks; CORE-06 diagnostics; DATA-04 serialization; DATA-05 bundles.
- No decoder, archive codec, compression library, asset SDK, parser execution or network is selected.

## Policy invariants

- **No real decoding.** The module validates caller-supplied metadata; it does not parse image/mesh/audio bytes.
- **Bounded.** 16 importers, 16 signature bytes, 64 receipts, 8 warnings and explicit metadata quotas.
- **Fail closed.** Truncated/unknown signatures, unknown formats and malformed metadata return typed errors.
- **Deterministic.** Descriptor lookup is by format; receipt scans are insertion-ordered.
- **Identity is DATA-02.** Receipts carry `AssetId` but mint nothing and persist nothing.
- **No host leakage.** Errors carry codes, not buffers, paths or secrets.
- **No conversion claim.** Artifact types are logical descriptors only.

## Internal API (logical, exact names)

```cpp
namespace stormline::data::imports {

using u32 = std::uint32_t;
using u64 = std::uint64_t;
using u8 = std::uint8_t;

inline constexpr u32 kMaxImporters = 16;
inline constexpr u32 kMaxSignatureBytes = 16;
inline constexpr u32 kMaxReceipts = 64;
inline constexpr u32 kMaxReceiptWarnings = 8;
inline constexpr u32 kMaxTextureDimension = 16384;
inline constexpr u32 kMaxMipLevels = 15;
inline constexpr u32 kMaxAnimationJoints = 256;
inline constexpr u32 kMaxAnimationTracks = 256;
inline constexpr u32 kMaxAnimationKeyframes = 4096;
inline constexpr u32 kMaxAnimationDurationMs = 3600000;
inline constexpr u32 kMaxAudioFrames = 10000000;

enum class ImportError : std::uint8_t {
    None,
    InvalidArgument,
    InvalidPath,
    UnknownFormat,
    UnsupportedFormat,
    SignatureTruncated,
    DuplicateImporter,
    DuplicateReceipt,
    InvalidTexture,
    InvalidAnimation,
    InvalidAudio,
    CapacityFull,
    NotFound,
    AssetMismatch,
    BufferFull
};

enum class FormatId : std::uint8_t { Unknown, Png, Jpeg, Glb, Wav };
enum class ArtifactType : std::uint8_t { Unknown, Texture2D, Mesh, Animation, Audio, Metadata };
enum class ValidationStatus : std::uint8_t { Valid, Invalid };

struct ImporterDescriptor {
    u32 importer_id{0};
    u32 version{0};
    FormatId format{FormatId::Unknown};
    ArtifactType artifact{ArtifactType::Unknown};
    std::array<char, 8> extension{};
    u32 extension_length{0};
};

class ImporterRegistry final {
public:
    ImporterRegistry() noexcept = default;
    [[nodiscard]] ImportError add(const ImporterDescriptor& descriptor) noexcept;
    [[nodiscard]] ImportError find(FormatId format, ImporterDescriptor& out) const noexcept;
    [[nodiscard]] ImportError sniff(
        std::span<const u8> signature, FormatId& out) const noexcept;
    struct ImportRequest {
        vfs::VfsPath source{};
        FormatId declared_format{FormatId::Unknown};
        std::span<const u8> signature{};
    };
    struct ImportPlan {
        FormatId detected{FormatId::Unknown};
        u32 importer_id{0};
        u32 importer_version{0};
        ArtifactType artifact{ArtifactType::Unknown};
    };
    [[nodiscard]] ImportError plan(
        const ImportRequest& request, ImportPlan& out) const noexcept;
    [[nodiscard]] u32 size() const noexcept;
};

struct TextureMetadata {
    u32 width{0};
    u32 height{0};
    u32 mip_levels{0};
    u8 channels{0};
    bool srgb{false};
};
[[nodiscard]] ImportError validate_texture(
    const TextureMetadata& metadata, u32& warning_count) noexcept;

struct AnimationMetadata {
    u32 joint_count{0};
    u32 track_count{0};
    u32 keyframe_count{0};
    u32 duration_ms{0};
};
[[nodiscard]] ImportError validate_animation(
    const AnimationMetadata& metadata, u32& warning_count) noexcept;

struct AudioMetadata {
    u32 sample_rate{0};
    u8 channels{0};
    u8 bits_per_sample{0};
    u32 frame_count{0};
};
[[nodiscard]] ImportError validate_audio(
    const AudioMetadata& metadata, u32& warning_count) noexcept;

struct ArtifactMetadata {
    ArtifactType type{ArtifactType::Unknown};
    TextureMetadata texture{};
    AnimationMetadata animation{};
    AudioMetadata audio{};
};
struct ValidationResult {
    ValidationStatus status{ValidationStatus::Invalid};
    ImportError error{ImportError::None};
    u32 warning_count{0};
};
[[nodiscard]] ImportError validate_artifact(
    const ArtifactMetadata& metadata, ValidationResult& out) noexcept;

struct ImportReceipt {
    u64 operation_id{0};
    registry::AssetId asset{};
    u32 importer_id{0};
    u32 importer_version{0};
    FormatId format{FormatId::Unknown};
    u64 source_fingerprint{0};
    u32 artifact_count{0};
    u32 warning_count{0};
    ValidationStatus validation{ValidationStatus::Invalid};
};

class ReceiptLog final {
public:
    ReceiptLog() noexcept = default;
    [[nodiscard]] ImportError add(const ImportReceipt& receipt) noexcept;
    [[nodiscard]] ImportError find(u64 operation_id, ImportReceipt& out) const noexcept;
    [[nodiscard]] u32 size() const noexcept;
    [[nodiscard]] u32 warning_total() const noexcept;
};

}  // namespace stormline::data::imports
```

No implementation is provided. Names or semantics may be refined only by an audited contract correction before `DATA-03-03`.

## Semantics

- **Descriptor:** requires nonzero importer ID/version, known format/artifact, extension 1..8 ASCII alphanumeric or `.`/`-`/`_`; duplicate ID or format returns `DuplicateImporter`; full returns `CapacityFull`.
- **Sniff:** Png `89 50 4E 47 0D 0A 1A 0A`; Jpeg `FF D8 FF`; Glb `67 6C 54 46`; Wav `52 49 46 46` with bytes 8..11 `57 41 56 45`. Empty/truncated input returns `SignatureTruncated`; valid prefix but insufficient Wav returns `SignatureTruncated`; unknown returns `UnknownFormat`.
- **Plan:** source path must be a valid nonempty `VfsPath`; sniffed format must have an importer; declared known format must equal sniffed format or return `UnsupportedFormat`; output carries detected format, importer ID/version and artifact type.
- **Texture:** width/height 1..16384, channels 1..4, mip levels 0..15 and at most `floor(log2(max(width,height))) + 1`; non-power-of-two dimensions add one warning; invalid returns `InvalidTexture`.
- **Animation:** joints 1..256, tracks 1..256, keyframes 1..4096, duration 1..3,600,000 ms; invalid returns `InvalidAnimation`; zero warnings on valid.
- **Audio:** sample rate 8000..192000, channels 1..8, bits 8/16/24/32, frames 1..10,000,000; invalid returns `InvalidAudio`; zero warnings.
- **Validation:** selects texture/animation/audio validator by artifact type; unknown type returns `InvalidArgument`; output status is `Valid` only when the validator returns `None`.
- **Receipt:** requires nonzero operation ID, valid `AssetId`, known format, nonzero importer/version and artifact count 1..8; duplicate operation ID returns `DuplicateReceipt`; full returns `CapacityFull`; `find` missing returns `NotFound`; `warning_total` is bounded and cannot overflow (saturating).
- **Threading:** single-owner unless synchronized. No allocation, exception, blocking call, file, archive, decoder, network or global mutable state.

## Test oracles (future DATA-03-03..-09)

| ID | Scenario | Oracle |
|---|---|---|
| IMP-01 | importer registry and planning | descriptor add/find/duplicates/capacity; signature sniff; declared mismatch; valid plan |
| TEX-01 | texture metadata | dimension/channel/mip boundaries; non-POT warning; invalid |
| ANIM-01 | animation metadata | joints/tracks/keyframes/duration boundaries; invalid |
| AUDIO-01 | audio metadata | rate/channels/bits/frames boundaries; invalid |
| VAL-01 | integrated validation | type dispatch, valid/invalid status, warning propagation, unknown type |
| REC-01 | provenance receipts | add/find/duplicate/capacity; warning total; asset/format fields |
| QLF-I01 | integrated pipeline | sniff→plan→validate→receipt |
| QLF-I02 | deterministic repeat | repeated sequence yields identical plan/validation/receipt |
| QLF-I03 | failure recovery | each typed error followed by a successful valid operation |
| QLF-I04 | bounded overload | 10,000 descriptor/plan/receipt attempts keep fixed capacities |

## Implementation allowlists

Headers are internal and header-only under `src/stormline/data/import/`. CMake adds one `INTERFACE` target and one test executable per packet; no production `.cpp` is required. Any new file requires an audited contract correction.

### `DATA-03-03` (importers and planning)

1. `src/stormline/data/import/import_types.hpp`
2. `src/stormline/data/import/importer_registry.hpp`
3. `tests/core/data03_importer_tests.cpp`
4. `CMakeLists.txt` (additive DATA-03 target/tests)
5. `.github/workflows/core01-internal-headless.yml` (additive DATA-03 filters)
6. `docs/evidence/NLE-PRPLAN-DATA-03-03.md`

### `DATA-03-04` (textures)

1. `src/stormline/data/import/texture_metadata.hpp`
2. `tests/core/data03_texture_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-DATA-03-04.md`

### `DATA-03-05` (animations)

1. `src/stormline/data/import/animation_metadata.hpp`
2. `tests/core/data03_animation_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-DATA-03-05.md`

### `DATA-03-06` (audio)

1. `src/stormline/data/import/audio_metadata.hpp`
2. `tests/core/data03_audio_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-DATA-03-06.md`

### `DATA-03-07` (validation pipeline)

1. `src/stormline/data/import/import_validation.hpp`
2. `tests/core/data03_validation_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-DATA-03-07.md`

### `DATA-03-08` (provenance receipts)

1. `src/stormline/data/import/import_receipt.hpp`
2. `tests/core/data03_receipt_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-DATA-03-08.md`

### `DATA-03-09` (qualification)

1. `tests/core/data03_import_qualification_tests.cpp`
2. `CMakeLists.txt`
3. `.github/workflows/core01-internal-headless.yml`
4. `docs/evidence/NLE-PRPLAN-DATA-03-09.md`

`DATA-03-10` is documentary closeout only. Qualification is internal/CI-only; no decoder, archive, native filesystem, hardware, ABI or release claim.

## Stop / rollback / security

Stop on stale source, missing admission, real decoder/archive/conversion/native I/O, dependency selection, unbounded input, host path leakage, public ABI/release claim or HIGH/CRITICAL. Unmerged: close the branch. After merge: normal revert PR; never force push.

No implementation is authorized by this contract. `DATA-03-03` requires its own G6 activation and explicit owner authorization.
