# GFX-02 INTERNAL_ONLY Logical Shader Pipeline Contract v0 (NLE-PRPLAN-GFX-02-02)

**Status:** `CONTRACT PROPOSAL / NOT IMPLEMENTED / NO CODE AUTHORIZED`. **Base:** `c1f0b89`. **ADR:** [ADR-0116](../adr/0116-gfx-02-internal-shader-pipeline.md). **WO:** [NLE-PRPLAN-GFX-02-02](../work-orders/NLE-PRPLAN-GFX-02-02.md).

## Objective

Freeze the first bounded GFX-02 logical API: SSCL-0 source parsing, typed diagnostics, validated shader IR, reflection metadata, deterministic variant planning, in-memory cache identity and dependency-revision invalidation. No native compiler, external frontend, GPU artifact, driver, renderer, dependency, ABI or release.

## Admission and boundaries

- Formal dependencies are `GFX-01` and `DATA-03`; neither is module-qualified.
- GFX-02 owns logical shader source/IR/reflection/variant/cache/incremental metadata.
- DATA-02 identity; DATA-03 import provenance/receipts; GFX-01 device capabilities; CORE-01 OS; CORE-02 memory; CORE-06 diagnostics; GFX-05 material semantics; DATA-05 cook.
- No GLSL/HLSL/Slang/WGSL/SPIR-V/DXIL/MSL/Tint/Naga/DXC/glslang, compiler executable or SDK is selected.

## Policy invariants

- **No native compiler or GPU.** SSCL-0 only; no compiled GPU artifact, driver, pipeline, render or hot reload.
- **Declarative subset.** No expressions, control flow, macros, includes, host paths or executable content.
- **Bounded.** Source, lines, names, declarations, diagnostics, variants, cache entries and dependencies are fixed.
- **Deterministic.** Source order, reflection slots, variant order and fingerprints are canonical.
- **Typed fail-closed errors.** All invalid input returns a stable `ShaderError` and bounded diagnostic span.
- **No artifact claim.** IR/reflection/cache metadata is not a native shader binary or pipeline.
- **Identity is not authentication.** FNV-1a 64 detects accidental mismatch only.
- **No host I/O.** All APIs operate on caller-provided in-memory spans.

## Internal API (logical, exact names)

```cpp
namespace stormline::graphics::shader {

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

inline constexpr u32 kMaxSourceBytes = 4096;
inline constexpr u32 kMaxSourceLines = 256;
inline constexpr u32 kMaxNameBytes = 32;
inline constexpr u32 kMaxPathBytes = 64;
inline constexpr u32 kMaxBindings = 64;
inline constexpr u32 kMaxInputs = 32;
inline constexpr u32 kMaxOutputs = 32;
inline constexpr u32 kMaxUniforms = 32;
inline constexpr u32 kMaxStaticSwitches = 16;
inline constexpr u32 kMaxVariants = 64;
inline constexpr u32 kMaxCacheEntries = 64;
inline constexpr u32 kMaxDependencies = 32;
inline constexpr u32 kMaxDiagnostics = 16;

enum class ShaderError : std::uint8_t {
    None,
    InvalidArgument,
    EmptySource,
    SourceTooLarge,
    TooManyLines,
    PathTooLong,
    InvalidToken,
    UnexpectedToken,
    InvalidName,
    InvalidModule,
    MissingStage,
    DuplicateStage,
    UnknownType,
    DuplicateBinding,
    StageRestriction,
    CapacityFull,
    VariantLimit,
    CacheFull,
    CacheMiss,
    CacheMismatch,
    StaleRevision
};

enum class ShaderStage : std::uint8_t { Vertex, Fragment, Compute };
enum class BindingKind : std::uint8_t { Input, Output, Uniform };
enum class ShaderType : std::uint8_t {
    Float, Vec2, Vec3, Vec4, Mat3, Mat4, Int, Uint, Bool
};

struct Name {
    std::array<char, kMaxNameBytes> text{};
    u8 length{0};
};
struct SourcePath {
    std::array<char, kMaxPathBytes> text{};
    u8 length{0};
};

[[nodiscard]] ShaderError make_name(std::string_view text, Name& out) noexcept;
[[nodiscard]] std::string_view name_view(const Name& name) noexcept;
[[nodiscard]] ShaderError make_source_path(std::string_view text, SourcePath& out) noexcept;
[[nodiscard]] std::string_view path_view(const SourcePath& path) noexcept;
[[nodiscard]] const char* shader_error_name(ShaderError error) noexcept;

struct SourceSpan {
    u32 line{0};
    u32 column{0};
    u32 length{0};
};
struct Diagnostic {
    ShaderError code{ShaderError::None};
    SourceSpan span{};
    SourcePath path{};
};

struct Binding {
    Name name{};
    ShaderType type{ShaderType::Float};
    BindingKind kind{BindingKind::Uniform};
};

struct ShaderIr {
    SourcePath path{};
    Name module_name{};
    ShaderStage stage{ShaderStage::Vertex};
    u32 binding_count{0};
    std::array<Binding, kMaxBindings> bindings{};
    u64 source_fingerprint{0};
    u32 source_lines{0};
};

[[nodiscard]] ShaderError compile_shader(
    const SourcePath& path, std::string_view source,
    ShaderIr& out, Diagnostic& diagnostic) noexcept;

[[nodiscard]] u32 shader_type_size(ShaderType type) noexcept;
[[nodiscard]] u32 shader_type_alignment(ShaderType type) noexcept;

struct ReflectedBinding {
    Name name{};
    ShaderType type{ShaderType::Float};
    BindingKind kind{BindingKind::Uniform};
    u32 slot{0};
    u32 byte_size{0};
    u32 alignment{0};
};
struct ShaderReflection {
    Name module_name{};
    ShaderStage stage{ShaderStage::Vertex};
    u32 binding_count{0};
    std::array<ReflectedBinding, kMaxBindings> bindings{};
    u64 source_fingerprint{0};
};

[[nodiscard]] ShaderError reflect_shader(
    const ShaderIr& ir, ShaderReflection& out) noexcept;

struct VariantRequest {
    u32 recipe_version{0};
    u32 switch_count{0};
    u32 max_variants{0};
};
struct VariantKey {
    u64 source_fingerprint{0};
    u32 recipe_version{0};
    u16 switch_bits{0};
    ShaderStage stage{ShaderStage::Vertex};
};
struct VariantPlan {
    u32 count{0};
    std::array<VariantKey, kMaxVariants> keys{};
};

[[nodiscard]] ShaderError plan_variants(
    const ShaderIr& ir, const VariantRequest& request,
    VariantPlan& out) noexcept;

struct CacheKey {
    u64 value{0};
};
struct CacheEntry {
    CacheKey key{};
    u64 payload_fingerprint{0};
};

[[nodiscard]] ShaderError make_cache_key(
    const VariantKey& variant, u64 dependency_fingerprint,
    CacheKey& out) noexcept;

class ShaderCache final {
public:
    ShaderCache() noexcept = default;
    [[nodiscard]] ShaderError put(
        const CacheKey& key, u64 payload_fingerprint) noexcept;
    [[nodiscard]] ShaderError get(
        const CacheKey& key, u64& out_payload) const noexcept;
    [[nodiscard]] u32 size() const noexcept;
    void clear() noexcept;
private:
    std::array<CacheEntry, kMaxCacheEntries> entries_{};
    u32 size_{0};
};

struct DependencyRef {
    u64 id{0};
    u64 revision{0};
};
struct DependencySet {
    u32 count{0};
    std::array<DependencyRef, kMaxDependencies> dependencies{};
};
struct IncrementalState {
    u64 dependency_fingerprint{0};
    u64 cache_key{0};
};

[[nodiscard]] ShaderError dependency_fingerprint(
    const DependencySet& dependencies, u64& out) noexcept;
[[nodiscard]] ShaderError plan_incremental(
    const DependencySet& dependencies, const IncrementalState& previous,
    bool& out_rebuild, u64& out_fingerprint) noexcept;

}  // namespace stormline::graphics::shader
```

No implementation is provided. Names or semantics may be refined only by an audited contract correction before `GFX-02-03`.

## Semantics

- **Source path:** 1..64 nonzero bytes; identifiers/module names 1..32 bytes matching `[A-Za-z_][A-Za-z0-9_]*`.
- **Source:** 1..4096 bytes and at most 256 lines; ASCII whitespace and `//` comments only; a final newline is optional.
- **Module:** exactly `shader <name> { ... }`; exactly one `stage` declaration; duplicate or missing stage fails.
- **Declarations:** `input|output|uniform <type> <name>;`; known types only; names unique across all declarations.
- **Stage restriction:** `compute` rejects input/output declarations; vertex/fragment permit all kinds.
- **Capacities:** 64 total bindings; 32 inputs, 32 outputs and 32 uniforms independently.
- **Diagnostics:** first error returns its code with 1-based line/column and token length; path copied to the diagnostic; no allocation or host path.
- **IR:** preserves declaration order and source fingerprint (FNV-1a 64 over exact source bytes); `source_lines` is the number of lines.
- **Reflection:** valid IR only; slots assigned from 0 by declaration order within each kind; sizes/alignments are logical metadata: float/int/uint/bool 4/4, vec2 8/8, vec3 12/16, vec4 16/16, mat3 48/16, mat4 64/16.
- **Variants:** recipe version nonzero; 0..16 static switches; `2^switch_count` must fit `max_variants` (1..64) or `VariantLimit`; keys sorted by ascending `switch_bits`; identical source/recipe/switch/stage yields identical key.
- **Cache:** key value and payload fingerprint nonzero; capacity 64; duplicate equal key+payload is idempotent; same key with different payload returns `CacheMismatch`; absent key returns `CacheMiss`; `clear` resets size.
- **Dependencies:** 1..32 entries; IDs and revisions nonzero and unique; fingerprint canonicalizes by ascending ID so input order does not change the result.
- **Incremental:** rebuild when previous fingerprint differs, previous fingerprint is zero or previous cache key is zero; outputs the current fingerprint; no file, process or network access.
- **Threading:** single-owner unless synchronized; no allocation, exception, compiler, driver, file or global mutable state.
- **FNV-1a 64** is non-cryptographic and is not a signature, trust anchor or security boundary.

## Test oracles (future GFX-02-03..-08)

| ID | Scenario | Oracle |
|---|---|---|
| PAR-01 | parser/IR | valid vertex/fragment/compute; comments; all types; diagnostics for every typed failure; capacity and line limits |
| REF-01 | reflection | slot order by kind; size/alignment table; fingerprint and module metadata; invalid IR |
| VAR-01 | variants | 0/1/8/16 switches; limit; stable ascending keys; invalid recipe/count |
| CAC-01 | cache | put/get; idempotent duplicate; mismatch; capacity; miss; clear |
| INC-01 | incremental | same/changed dependency; order-insensitive fingerprint; duplicates/limits |
| QLF-S01 | integrated | source -> IR -> reflection -> variants -> cache -> incremental |
| QLF-S02 | deterministic repeat | repeated pipeline produces identical IR/reflection/keys/cache results |
| QLF-S03 | failure recovery | each typed error followed by a valid operation |
| QLF-S04 | bounded overload | 10,000 parse/reflect/variant/cache/incremental attempts keep capacities |

## Implementation allowlists

Headers are internal and header-only under `src/stormline/graphics/shader/`. CMake adds one `INTERFACE` target and one test executable per packet; no production `.cpp`.

### `GFX-02-03` (SSCL-0 parser/IR)

1. `src/stormline/graphics/shader/shader_types.hpp`
2. `src/stormline/graphics/shader/shader_parser.hpp`
3. `tests/core/gfx02_shader_tests.cpp`
4. `CMakeLists.txt`
5. `.github/workflows/core01-internal-headless.yml`
6. `docs/evidence/NLE-PRPLAN-GFX-02-03.md`

### `GFX-02-04` (reflection)

1. `src/stormline/graphics/shader/shader_reflection.hpp`
2. `tests/core/gfx02_reflection_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-GFX-02-04.md`

### `GFX-02-05` (variants)

1. `src/stormline/graphics/shader/shader_variant.hpp`
2. `tests/core/gfx02_variant_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-GFX-02-05.md`

### `GFX-02-06` (cache)

1. `src/stormline/graphics/shader/shader_cache.hpp`
2. `tests/core/gfx02_cache_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-GFX-02-06.md`

### `GFX-02-07` (incremental)

1. `src/stormline/graphics/shader/shader_incremental.hpp`
2. `tests/core/gfx02_incremental_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-GFX-02-07.md`

### `GFX-02-08` (qualification)

1. `tests/core/gfx02_shader_qualification_tests.cpp`
2. `CMakeLists.txt`
3. `.github/workflows/core01-internal-headless.yml`
4. `docs/evidence/NLE-PRPLAN-GFX-02-08.md`

`GFX-02-09` is documentary closeout only. Qualification is internal/CI-only; no native compiler, GPU artifact, rendering, hardware, ABI or release claim.

## Stop / rollback / security

Stop on stale source, missing admission, native compiler/API/driver selection, executable shader content, host I/O, network, public ABI/release claim or HIGH/CRITICAL. Revert normally; never force push.
