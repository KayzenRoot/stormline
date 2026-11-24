# TWO-03 INTERNAL_ONLY Animation Contract v0 (NLE-PRPLAN-TWO-03-02)

**Status:** `CONTRACT PROPOSAL / NOT IMPLEMENTED / NO CODE AUTHORIZED`. **Base:** `c534bbc`. **ADR:** [ADR-0125](../adr/0125-two-03-internal-animation-pipeline.md). **WO:** [NLE-PRPLAN-TWO-03-02](../work-orders/NLE-PRPLAN-TWO-03-02.md).

## Objective

Freeze the first bounded TWO-03 logical API: flipbook frame, 2D bone hierarchy, clip blend, cutscene track/cue and rational timeline planning. No animation runtime, pose evaluation, skinning, audio, export, dependency, ABI or release.

## Admission and boundaries

- Formal dependency is `TWO-01`; it is not module-qualified.
- TWO-03 owns logical animation/sequencing plans.
- TWO-01 Canvas; DATA assets/authoring; AUDIO sound; GFX rendering; WORLD/GAME/PHYS authority.
- No runtime, audio device, codec, importer, renderer or hardware driver is selected.

## Policy invariants

- **No runtime or export.** Metadata/planning only; no frame sample, pose, skin, audio, encoder or media file.
- **Rational/checked time.** Frame holds and cue ticks are integer/checked; overflow and invalid durations fail closed.
- **Bounded and finite.** Fixed capacities; NaN/Inf, cycles, unbounded nesting and zero weights are rejected.
- **No identity interpolation.** Sprite/event IDs are discrete; weights apply only to numeric channels.
- **Deterministic.** Stable IDs, declared order and integer time determine output.

## Internal API (logical, exact names)

```cpp
namespace stormline::animation {

using u8 = std::uint8_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using i64 = std::int64_t;
using f32 = float;

inline constexpr u32 kMaxFlipbookFrames = 64;
inline constexpr u32 kMaxBones = 32;
inline constexpr u32 kMaxBlendClips = 4;
inline constexpr u32 kMaxSequenceTracks = 16;
inline constexpr u32 kMaxSequenceCues = 16;
inline constexpr u32 kMaxSequenceDepth = 4;

enum class AnimationError : std::uint8_t {
    None,
    InvalidArgument,
    DuplicateId,
    NotFound,
    CapacityFull,
    NonFiniteValue,
    OutOfRange,
    TimeInvalid,
    FlipbookInvalid,
    SkeletonInvalid,
    BlendInvalid,
    SequenceInvalid,
    DepthExceeded,
    EventInvalid,
    Unsupported
};

enum class TrackKind : std::uint8_t {
    Sprite, Bone, Camera, Audio, Vfx, GameplayEvent
};

struct AnimationDiagnostic {
    AnimationError code{AnimationError::None};
    u32 source_id{0};
    u32 index{0};
};

struct FlipbookFrame {
    u32 frame_id{0};
    u32 sprite_id{0};
    u32 atlas_region_id{0};
    u32 hold_frames{0};
};

struct FlipbookDesc {
    u32 clip_id{0};
    u32 revision{0};
    u32 timebase_denominator{0};
    u32 frame_count{0};
    std::array<FlipbookFrame, kMaxFlipbookFrames> frames{};
};

struct FlipbookPlan {
    u32 frame_count{0};
    u64 total_frames{0};
};

[[nodiscard]] AnimationError plan_flipbook(
    const FlipbookDesc& flipbook, FlipbookPlan& plan,
    AnimationDiagnostic& diagnostic) noexcept;

struct BoneDesc {
    u32 bone_id{0};
    u32 revision{0};
    u32 parent_id{0};
    f32 local_x{0.0f};
    f32 local_y{0.0f};
    f32 local_rotation{0.0f};
};

struct SkeletonDesc {
    u32 skeleton_id{0};
    u32 revision{0};
    u32 bone_count{0};
    std::array<BoneDesc, kMaxBones> bones{};
};

struct SkeletonPlan {
    u32 bone_count{0};
    u32 max_depth{0};
    u32 root_count{0};
};

[[nodiscard]] AnimationError plan_skeleton(
    const SkeletonDesc& skeleton, SkeletonPlan& plan,
    AnimationDiagnostic& diagnostic) noexcept;

struct BlendClipDesc {
    u32 clip_id{0};
    u32 revision{0};
    f32 weight{0.0f};
};

struct BlendDesc {
    u32 blend_id{0};
    u32 revision{0};
    bool additive{false};
    bool discrete_targets{false};
    u32 clip_count{0};
    std::array<BlendClipDesc, kMaxBlendClips> clips{};
};

struct BlendPlan {
    u32 clip_count{0};
    std::array<f32, kMaxBlendClips> normalized_weights{};
};

[[nodiscard]] AnimationError plan_blend(
    const BlendDesc& blend, BlendPlan& plan,
    AnimationDiagnostic& diagnostic) noexcept;

struct SequenceCue {
    u32 cue_id{0};
    u32 revision{0};
    TrackKind kind{TrackKind::Sprite};
    u64 tick{0};
    u64 duration_ticks{0};
};

struct SequenceTrack {
    u32 track_id{0};
    u32 revision{0};
    TrackKind kind{TrackKind::Sprite};
    u32 cue_count{0};
    std::array<SequenceCue, kMaxSequenceCues> cues{};
};

struct SequenceDesc {
    u32 sequence_id{0};
    u32 revision{0};
    u32 timebase_denominator{0};
    u64 duration_ticks{0};
    u32 track_count{0};
    std::array<SequenceTrack, kMaxSequenceTracks> tracks{};
    u32 nesting_depth{0};
};

struct SequencePlan {
    u32 track_count{0};
    u32 cue_count{0};
    u32 max_depth{0};
};

[[nodiscard]] AnimationError plan_sequence(
    const SequenceDesc& sequence, SequencePlan& plan,
    AnimationDiagnostic& diagnostic) noexcept;

struct TimelineDesc {
    u32 timeline_id{0};
    u32 revision{0};
    u32 fps_numerator{0};
    u32 fps_denominator{0};
    u64 duration_frames{0};
    u32 sample_rate{0};
    u64 loop_start_frame{0};
    u64 loop_end_frame{0};
};

struct TimelinePlan {
    u64 frame_count{0};
    u64 sample_count{0};
    u64 loop_length_frames{0};
};

[[nodiscard]] AnimationError plan_timeline(
    const TimelineDesc& timeline, TimelinePlan& plan,
    AnimationDiagnostic& diagnostic) noexcept;

}  // namespace stormline::animation
```

No implementation is provided. Names or semantics may be refined only by an audited contract correction before `TWO-03-03`.

## Semantics

- **Flipbook:** clip/revision/timebase nonzero; frame count bounded; frame IDs nonzero/unique; sprite/atlas IDs nonzero; hold frames positive; checked total `u64`.
- **Skeleton:** IDs/revisions nonzero and unique; parent is `0` (root) or an existing bone; self-parent/cycle/depth >16 fail; transforms finite.
- **Blend:** IDs/revisions nonzero and unique; count bounded; weights finite nonnegative; positive sum; normalized weights deterministic; additive requires discrete targets.
- **Sequence:** IDs/revisions/timebase/duration nonzero; track/cue counts bounded; kinds allowlisted; cue tick+duration within duration; IDs unique; nesting depth `<=4`.
- **Timeline:** IDs nonzero; fps/sample rate/duration positive; loop end `>start` and `<=duration`; checked sample-count multiplication; loop length returned.
- **Common:** all functions `noexcept`; no allocation, exception, file, network, audio, GPU, thread or global state. Invalid input zeroes/defaults outputs and sets the diagnostic.

## Test oracles (future TWO-03-03..-08)

| ID | Scenario | Oracle |
|---|---|---|
| FLB-01 | flipbooks | IDs, holds, timebase, total |
| BON-01 | skeleton | unique IDs, parent DAG, cycle/depth, finite transforms |
| BLD-01 | blend | weights, normalization, additive/discrete policy |
| SEQ-01 | cutscenes | tracks/cues, kinds, timing, nesting depth |
| TML-01 | timelines | fps/sample mapping, loops, overflow |
| QLF-T301 | integrated | flipbook->skeleton->blend->sequence->timeline |
| QLF-T302 | deterministic repeat | identical plans/weights/counts |
| QLF-T303 | failure recovery | typed error followed by valid operation |
| QLF-T304 | bounded overload | 10,000 attempts keep caps |

## Implementation allowlists

Headers are internal and header-only under `src/stormline/animation/`. CMake adds one `INTERFACE` target and one test executable per packet; no production `.cpp`.

### `TWO-03-03` (flipbooks)

1. `src/stormline/animation/animation_types.hpp`
2. `src/stormline/animation/flipbook_plan.hpp`
3. `tests/core/two03_flipbook_tests.cpp`
4. `CMakeLists.txt`
5. `.github/workflows/core01-internal-headless.yml`
6. `docs/evidence/NLE-PRPLAN-TWO-03-03.md`

### `TWO-03-04` (bones)

1. `src/stormline/animation/skeleton_plan.hpp`
2. `tests/core/two03_skeleton_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-TWO-03-04.md`

### `TWO-03-05` (blend)

1. `src/stormline/animation/blend_plan.hpp`
2. `tests/core/two03_blend_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-TWO-03-05.md`

### `TWO-03-06` (cutscenes)

1. `src/stormline/animation/sequence_plan.hpp`
2. `tests/core/two03_sequence_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-TWO-03-06.md`

### `TWO-03-07` (timelines)

1. `src/stormline/animation/timeline_plan.hpp`
2. `tests/core/two03_timeline_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-TWO-03-07.md`

### `TWO-03-08` (qualification)

1. `tests/core/two03_animation_qualification_tests.cpp`
2. `CMakeLists.txt`
3. `.github/workflows/core01-internal-headless.yml`
4. `docs/evidence/NLE-PRPLAN-TWO-03-08.md`
