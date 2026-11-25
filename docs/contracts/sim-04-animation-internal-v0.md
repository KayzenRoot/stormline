# SIM-04 internal contract v0 — logical skeletal animation metadata

**Status:** `FROZEN INTERNAL API / LOGICAL METADATA ONLY / NO ANIMATION RUNTIME`. **ADR:** [ADR-0135](../adr/0135-sim-04-internal-skeletal-animation-metadata.md). **Architecture:** [sim-04-internal-skeletal-animation-metadata](../architecture/sim-04-internal-skeletal-animation-metadata.md). **Governance:** [sim-04-governance-v0](sim-04-governance-v0.md). **Planning-only policy:** [ADR-0034](../adr/0034-sim-04-animation-authority-retarget-ik-and-ragdoll.md) remains `PROPOSED`.

This contract freezes the exact C++20 header-only logical API for the SIM-04 internal sequence. It creates no pose evaluator, graph runtime, IK solver, ragdoll activation, codec, sync runtime, root-motion application, ECS mutation, GPU or runtime behavior. Every slice below is separately gated; this document alone authorizes no code.

## Common types

Namespace `stormline::animation`, headers under `src/stormline/animation/`.

```cpp
using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using i32 = std::int32_t;
using f32 = float;

inline constexpr u32 kMaxRetargetProfiles = 16;
inline constexpr u32 kMaxRetargetPairs = 64;
inline constexpr u32 kMaxBlendNodes = 64;
inline constexpr u32 kMaxIkChains = 32;
inline constexpr u32 kMaxIkIterations = 64;
inline constexpr u32 kMaxRagdollProfiles = 16;
inline constexpr u32 kMaxCompressionProfiles = 16;
inline constexpr u32 kMaxSyncGroups = 32;
inline constexpr u32 kMaxTickWindow = 240;

enum class AnimationError : std::uint8_t {
    None, InvalidArgument, DuplicateId, NotFound, CapacityFull,
    NonFiniteValue, OutOfRange, RetargetInvalid, BlendInvalid, IkInvalid,
    RagdollInvalid, CompressionInvalid, SyncInvalid, Incomplete, Unsupported
};

struct AnimationDiagnostic {
    AnimationError code{AnimationError::None};
    u32 owner_id{0};
    u32 index{0};
};
```

Shared detail helpers: `set_animation_error`, `finite(f32)` and `unit_scalar_in(f32, f32, f32)` for `[0,1]` checks.

## `SIM-04-03` (retargeting)

```cpp
struct RetargetJointPair {
    u32 source_joint{0};
    u32 target_joint{0};
};

struct RetargetProfileDesc {
    u32 retarget_id{0};
    u32 revision{0};
    f32 bind_scale{1.0f};
    u32 pair_count{0};
    std::array<RetargetJointPair, kMaxRetargetPairs> pairs{};
    bool enabled{false};
};

struct RetargetSetDesc {
    u32 owner_id{0};
    u32 revision{0};
    u32 profile_count{0};
    std::array<RetargetProfileDesc, kMaxRetargetProfiles> profiles{};
};

struct RetargetPlan {
    u32 profile_count{0};
    u32 total_pair_count{0};
    u32 enabled_count{0};
};

[[nodiscard]] AnimationError plan_retargets(
    const RetargetSetDesc& retargets, RetargetPlan& plan,
    AnimationDiagnostic& diagnostic) noexcept;
```

Semantics: owner ID/revision nonzero; profile count `0..16`; profile IDs nonzero and unique; revisions nonzero; bind_scale finite and `> 0`; pair count `0..64`; source/target joints nonzero; source joints unique and target joints unique within a profile. Plan counts profiles, total pairs and enabled profiles. No pose conversion.

## `SIM-04-04` (blend trees)

```cpp
enum class BlendKind : std::uint8_t { Lerp, Additive, Mask, Blend1D, Blend2D };

struct BlendNodeDesc {
    u32 node_id{0};
    u32 revision{0};
    BlendKind kind{BlendKind::Lerp};
    f32 weight{1.0f};
    f32 threshold{0.0f};
    bool enabled{false};
};

struct BlendSetDesc {
    u32 owner_id{0};
    u32 revision{0};
    u32 node_count{0};
    std::array<BlendNodeDesc, kMaxBlendNodes> nodes{};
};

struct BlendPlan {
    u32 node_count{0};
    u32 lerp_count{0};
    u32 additive_count{0};
    u32 mask_count{0};
    u32 blend_1d_count{0};
    u32 blend_2d_count{0};
    u32 enabled_count{0};
};

[[nodiscard]] AnimationError plan_blends(
    const BlendSetDesc& blends, BlendPlan& plan,
    AnimationDiagnostic& diagnostic) noexcept;
```

Semantics: owner ID/revision nonzero; count `0..64`; node IDs nonzero and unique; revisions nonzero; kind allowlist; weight and threshold finite and in `[0,1]`. Plan counts kinds and enabled nodes. No graph evaluation.

## `SIM-04-05` (IK)

```cpp
struct IkChainDesc {
    u32 chain_id{0};
    u32 revision{0};
    u32 bone_count{0};
    u32 iterations{0};
    f32 tolerance{0.0f};
    f32 target_weight{1.0f};
    bool enabled{false};
};

struct IkSetDesc {
    u32 owner_id{0};
    u32 revision{0};
    u32 chain_count{0};
    std::array<IkChainDesc, kMaxIkChains> chains{};
};

struct IkPlan {
    u32 chain_count{0};
    u32 total_bone_count{0};
    u32 max_iterations{0};
    u32 enabled_count{0};
};

[[nodiscard]] AnimationError plan_ik(
    const IkSetDesc& ik, IkPlan& plan,
    AnimationDiagnostic& diagnostic) noexcept;
```

Semantics: owner ID/revision nonzero; count `0..32`; chain IDs nonzero and unique; revisions nonzero; bone_count `1..16`; iterations `0..64`; tolerance finite and `>= 0`; target_weight finite and in `[0,1]`. Plan counts chains, total bones, max iterations and enabled chains. No solver.

## `SIM-04-06` (ragdoll)

```cpp
struct RagdollProfileDesc {
    u32 ragdoll_id{0};
    u32 revision{0};
    u32 body_mapping_id{0};
    u32 constraint_mapping_id{0};
    f32 activation_weight{1.0f};
    bool auto_activate{false};
    bool enabled{false};
};

struct RagdollSetDesc {
    u32 owner_id{0};
    u32 revision{0};
    u32 profile_count{0};
    std::array<RagdollProfileDesc, kMaxRagdollProfiles> profiles{};
};

struct RagdollPlan {
    u32 profile_count{0};
    u32 auto_count{0};
    u32 enabled_count{0};
};

[[nodiscard]] AnimationError plan_ragdolls(
    const RagdollSetDesc& ragdolls, RagdollPlan& plan,
    AnimationDiagnostic& diagnostic) noexcept;
```

Semantics: owner ID/revision nonzero; count `0..16`; profile IDs nonzero and unique; revisions nonzero; body/constraint mapping IDs nonzero; activation_weight finite and in `[0,1]`. Plan counts auto-enabled and enabled profiles. No physics lifetime ownership.

## `SIM-04-07` (compression)

```cpp
struct CompressionProfileDesc {
    u32 profile_id{0};
    u32 revision{0};
    u32 translation_bits{0};
    u32 rotation_bits{0};
    u32 scale_bits{0};
    u32 keyframe_interval{0};
    bool lossless{false};
    bool enabled{false};
};

struct CompressionSetDesc {
    u32 owner_id{0};
    u32 revision{0};
    u32 profile_count{0};
    std::array<CompressionProfileDesc, kMaxCompressionProfiles> profiles{};
};

struct CompressionPlan {
    u32 profile_count{0};
    u32 lossless_count{0};
    u32 enabled_count{0};
};

[[nodiscard]] AnimationError plan_compression(
    const CompressionSetDesc& compression, CompressionPlan& plan,
    AnimationDiagnostic& diagnostic) noexcept;
```

Semantics: owner ID/revision nonzero; count `0..16`; profile IDs nonzero and unique; revisions nonzero; bit widths `1..32`; keyframe_interval `1..240`. Plan counts lossless and enabled profiles. No codec.

## `SIM-04-08` (sync groups)

```cpp
struct SyncGroupDesc {
    u32 group_id{0};
    u32 revision{0};
    u32 leader_id{0};
    u32 member_count{0};
    f32 phase{0.0f};
    bool enabled{false};
};

struct SyncSetDesc {
    u32 owner_id{0};
    u32 revision{0};
    u32 group_count{0};
    std::array<SyncGroupDesc, kMaxSyncGroups> groups{};
};

struct SyncPlan {
    u32 group_count{0};
    u32 phased_count{0};
    u32 enabled_count{0};
};

[[nodiscard]] AnimationError plan_sync(
    const SyncSetDesc& sync, SyncPlan& plan,
    AnimationDiagnostic& diagnostic) noexcept;
```

Semantics: owner ID/revision nonzero; count `0..32`; group IDs nonzero and unique; revisions nonzero; leader ID nonzero; member_count `1..32`; phase finite and in `[0,1]`. Plan counts phased (`phase != 0`) and enabled groups. No runtime synchronization.

## Common rules

All functions are `noexcept`, allocation-free, exception-free and use no file, network, audio, GPU, clock, thread, random source or global state. Invalid input resets the plan to default and sets a typed diagnostic with the owner ID and index. All capacities are fixed at compile time.

## Test oracles

| ID | Scenario | Oracle |
|---|---|---|
| RET-01 | retarget | unique profile/joint pairs, positive bind scale |
| BLEND-01 | blend trees | kind allowlist, weights/thresholds in `[0,1]` |
| IK-01 | IK chains | bone/iteration bounds, finite tolerance/target weight |
| RAG-01 | ragdoll | mapping refs, activation weight |
| CMP-01 | compression | bit widths, keyframe interval |
| SYNC-01 | sync groups | leader/member refs, phase bounds |
| QLF-S401 | integrated | retarget -> blend -> IK -> ragdoll -> compression -> sync |
| QLF-S402 | deterministic repeat | identical plans/counts |
| QLF-S403 | failure recovery | typed error followed by valid operation |
| QLF-S404 | bounded overload | 10,000 attempts keep caps |

## Implementation allowlists

No production `.cpp`. One `INTERFACE` target and one test executable per implementation packet. `animation_types.hpp` may be introduced only by `-03`; later packets must not modify earlier production headers.

### `SIM-04-03` (retargeting)

1. `src/stormline/animation/animation_types.hpp`
2. `src/stormline/animation/retarget_plan.hpp`
3. `tests/core/sim04_retarget_tests.cpp`
4. `CMakeLists.txt`
5. `.github/workflows/core01-internal-headless.yml`

### `SIM-04-04` (blend trees)

1. `src/stormline/animation/blend_plan.hpp`
2. `tests/core/sim04_blend_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`

### `SIM-04-05` (IK)

1. `src/stormline/animation/ik_plan.hpp`
2. `tests/core/sim04_ik_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`

### `SIM-04-06` (ragdoll)

1. `src/stormline/animation/ragdoll_plan.hpp`
2. `tests/core/sim04_ragdoll_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`

### `SIM-04-07` (compression)

1. `src/stormline/animation/compression_plan.hpp`
2. `tests/core/sim04_compression_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`

### `SIM-04-08` (sync)

1. `src/stormline/animation/sync_plan.hpp`
2. `tests/core/sim04_sync_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`

### `SIM-04-09` (qualification)

1. `tests/core/sim04_qualification_tests.cpp`
2. `CMakeLists.txt`
3. `.github/workflows/core01-internal-headless.yml`
4. `docs/evidence/NLE-PRPLAN-SIM-04-09.md`

### `SIM-04-10` (closeout)

Evidence only; no production, test, CMake or workflow file.

## Out of scope

Pose evaluation, blend/IK execution, ragdoll runtime, codecs, root-motion application, replay, ECS mutation, GPU, editor, audio, export, performance, ABI, release and production readiness. ADR-0034 remains `PROPOSED`.
