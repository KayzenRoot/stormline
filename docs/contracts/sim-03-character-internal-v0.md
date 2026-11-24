# SIM-03 internal contract v0 — logical character motor metadata

**Status:** `FROZEN INTERNAL API / LOGICAL METADATA ONLY / NO CHARACTER RUNTIME`. **ADR:** [ADR-0134](../adr/0134-sim-03-internal-character-motor-metadata.md). **Architecture:** [sim-03-internal-character-motor-metadata](../architecture/sim-03-internal-character-motor-metadata.md). **Governance:** [sim-03-governance-v0](sim-03-governance-v0.md). **Planning-only policy:** [ADR-0033](../adr/0033-sim-03-authoritative-character-motor-policy.md) remains `PROPOSED`.

This contract freezes the exact C++20 header-only logical API for the SIM-03 internal sequence. It creates no motor, sweeper, contact execution, input layer, camera update, ECS mutation, GPU or runtime behavior. Every slice below is separately gated; this document alone authorizes no code.

## Common types

Namespace `stormline::character`, headers under `src/stormline/character/`.

```cpp
using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using i32 = std::int32_t;
using f32 = float;

inline constexpr u32 kMaxControllers = 32;
inline constexpr u32 kMaxLocomotion = 32;
inline constexpr u32 kMaxInputActions = 64;
inline constexpr u32 kMaxCameras = 16;
inline constexpr u32 kMaxTickWindow = 240;

enum class CharacterError : std::uint8_t {
    None, InvalidArgument, DuplicateId, NotFound, CapacityFull,
    NonFiniteValue, OutOfRange, ControllerInvalid, LocomotionInvalid,
    InputInvalid, CameraInvalid, Incomplete, Unsupported
};

struct CharacterDiagnostic {
    CharacterError code{CharacterError::None};
    u32 owner_id{0};
    u32 index{0};
};
```

Shared detail helpers: `set_character_error`, `finite(f32)`, kind allowlist checks and `unit_axis(x, y, z)` (`|x²+y²+z² − 1| <= 1e-3`).

## `SIM-03-03` (controllers)

```cpp
enum class ControllerDimension : std::uint8_t { TwoD, ThreeD };
enum class ControllerMode : std::uint8_t { Kinematic, Dynamic };

struct ControllerDesc {
    u32 controller_id{0};
    u32 revision{0};
    u32 entity_id{0};
    ControllerDimension dimension{ControllerDimension::TwoD};
    ControllerMode mode{ControllerMode::Kinematic};
    f32 half_x{0.0f};
    f32 half_y{0.0f};
    f32 half_z{0.0f};
    f32 up_x{0.0f};
    f32 up_y{1.0f};
    f32 up_z{0.0f};
    f32 max_slope_degrees{45.0f};
    f32 step_height{0.0f};
    bool snap_to_ground{true};
    bool slide_on_slope{true};
    bool enabled{false};
};

struct ControllerSetDesc {
    u32 owner_id{0};
    u32 revision{0};
    u32 controller_count{0};
    std::array<ControllerDesc, kMaxControllers> controllers{};
};

struct ControllerPlan {
    u32 controller_count{0};
    u32 two_d_count{0};
    u32 three_d_count{0};
    u32 kinematic_count{0};
    u32 dynamic_count{0};
    u32 enabled_count{0};
};

[[nodiscard]] CharacterError plan_controllers(
    const ControllerSetDesc& controllers, ControllerPlan& plan,
    CharacterDiagnostic& diagnostic) noexcept;
```

Semantics: owner ID/revision nonzero; count `0..32`; controller IDs nonzero and unique; revisions nonzero; dimension/mode allowlists; half extents finite: 2D requires half_x and half_y `> 0` and half_z `== 0`; 3D requires half_x/half_y/half_z `> 0`; up axis unit and, for 2D, `up_z == 0`; max slope `0..90`; step height finite and `>= 0`. Plan counts dimensions, modes and enabled controllers. No movement or sweeps.

## `SIM-03-04` (locomotion)

```cpp
struct LocomotionDesc {
    u32 locomotion_id{0};
    u32 revision{0};
    u32 controller_id{0};
    f32 walk_speed{0.0f};
    f32 run_speed{0.0f};
    f32 air_speed{0.0f};
    f32 acceleration{0.0f};
    f32 deceleration{0.0f};
    f32 jump_height{0.0f};
    u32 jump_buffer_ticks{0};
    u32 coyote_ticks{0};
    f32 dash_speed{0.0f};
    u32 dash_ticks{0};
    bool enabled{false};
};

struct LocomotionSetDesc {
    u32 owner_id{0};
    u32 revision{0};
    u32 locomotion_count{0};
    std::array<LocomotionDesc, kMaxLocomotion> locomotion{};
};

struct LocomotionPlan {
    u32 locomotion_count{0};
    u32 ground_count{0};
    u32 air_count{0};
    u32 jump_count{0};
    u32 dash_count{0};
    u32 enabled_count{0};
};

[[nodiscard]] CharacterError plan_locomotion(
    const LocomotionSetDesc& locomotion, LocomotionPlan& plan,
    CharacterDiagnostic& diagnostic) noexcept;
```

Semantics: owner ID/revision nonzero; count `0..32`; IDs nonzero and unique; revisions nonzero; controller_id nonzero; all speeds/acceleration/deceleration/jump/dash finite; walk/run/air/jump/dash `>= 0`; run_speed `>= walk_speed`; acceleration and deceleration `> 0`; buffer/coyote/dash ticks `0..240`. Plan counts nonzero ground/air/jump/dash policies and enabled entries. No simulation.

## `SIM-03-05` (input response)

```cpp
struct InputActionDesc {
    u32 action_id{0};
    u32 revision{0};
    u32 axis_index{0};
    f32 dead_zone{0.0f};
    f32 scale{1.0f};
    u32 buffer_ticks{0};
    bool consume_on_use{false};
    bool enabled{false};
};

struct InputSetDesc {
    u32 owner_id{0};
    u32 revision{0};
    u32 action_count{0};
    std::array<InputActionDesc, kMaxInputActions> actions{};
};

struct InputPlan {
    u32 action_count{0};
    u32 axis_count{0};
    u32 buffered_count{0};
    u32 enabled_count{0};
};

[[nodiscard]] CharacterError plan_input(
    const InputSetDesc& input, InputPlan& plan,
    CharacterDiagnostic& diagnostic) noexcept;
```

Semantics: owner ID/revision nonzero; count `0..64`; action IDs nonzero and unique; revisions nonzero; axis_index `0..7` (0 means digital action); dead_zone `0..1`; scale finite and nonzero; buffer_ticks `0..240`; plan counts axis actions (`axis_index != 0`), buffered actions and enabled actions. No device polling or event dispatch.

## `SIM-03-06` (decoupled camera)

```cpp
struct CameraDesc {
    u32 camera_id{0};
    u32 revision{0};
    u32 target_controller_id{0};
    f32 distance{0.0f};
    f32 height{0.0f};
    f32 yaw_offset_degrees{0.0f};
    f32 pitch_degrees{0.0f};
    f32 position_damping{0.0f};
    f32 rotation_damping{0.0f};
    bool follow_enabled{false};
    bool independent_from_animation{true};
};

struct CameraSetDesc {
    u32 owner_id{0};
    u32 revision{0};
    u32 camera_count{0};
    std::array<CameraDesc, kMaxCameras> cameras{};
};

struct CameraPlan {
    u32 camera_count{0};
    u32 follow_count{0};
    u32 independent_count{0};
};

[[nodiscard]] CharacterError plan_cameras(
    const CameraSetDesc& cameras, CameraPlan& plan,
    CharacterDiagnostic& diagnostic) noexcept;
```

Semantics: owner ID/revision nonzero; count `0..16`; camera IDs nonzero and unique; revisions nonzero; target_controller_id nonzero; finite distance/height/yaw/pitch/damping; distance `>= 0`; pitch `-89..89`; position/rotation damping `0..1`; `independent_from_animation` must be true (fail closed on animation-coupled cameras). Plan counts follow-enabled and independent cameras. No camera transform is produced.

## Common rules

All functions are `noexcept`, allocation-free, exception-free and use no file, network, audio, GPU, clock, thread, random source or global state. Invalid input resets the plan to default and sets a typed diagnostic with the owner ID and index. All capacities are fixed at compile time. Tick windows are integer ticks, never wall-clock seconds.

## Test oracles

| ID | Scenario | Oracle |
|---|---|---|
| CTRL-01 | controllers | dimension/mode allowlists, finite extents, unit up axis, slope/step bounds |
| LOCO-01 | locomotion | finite speeds, run >= walk, positive accel/decel, tick windows |
| INPUT-01 | input response | unique actions, axis/dead-zone/scale validity, buffer windows |
| CAM-01 | decoupled camera | finite offsets/damping, pitch range, animation independence |
| QLF-S301 | integrated | controller -> locomotion -> input -> camera |
| QLF-S302 | deterministic repeat | identical plans/counts |
| QLF-S303 | failure recovery | typed error followed by valid operation |
| QLF-S304 | bounded overload | 10,000 attempts keep caps |

## Implementation allowlists

No production `.cpp`. One `INTERFACE` target and one test executable per implementation packet. `character_types.hpp` may be introduced only by `-03`; later packets must not modify earlier production headers.

### `SIM-03-03` (controllers)

1. `src/stormline/character/character_types.hpp`
2. `src/stormline/character/controller_plan.hpp`
3. `tests/core/sim03_controller_tests.cpp`
4. `CMakeLists.txt`
5. `.github/workflows/core01-internal-headless.yml`

### `SIM-03-04` (locomotion)

1. `src/stormline/character/locomotion_plan.hpp`
2. `tests/core/sim03_locomotion_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`

### `SIM-03-05` (input response)

1. `src/stormline/character/input_plan.hpp`
2. `tests/core/sim03_input_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`

### `SIM-03-06` (decoupled camera)

1. `src/stormline/character/camera_plan.hpp`
2. `tests/core/sim03_camera_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`

### `SIM-03-07` (qualification)

1. `tests/core/sim03_qualification_tests.cpp`
2. `CMakeLists.txt`
3. `.github/workflows/core01-internal-headless.yml`
4. `docs/evidence/NLE-PRPLAN-SIM-03-07.md`

### `SIM-03-08` (closeout)

Evidence only; no production, test, CMake or workflow file.

## Out of scope

Motor/sweeper execution, contact queries, solver/backend (Jolt/Box2D/Rapier), input devices, camera transform, animation root motion, ECS mutation, replay, GPU, editor, audio, export, performance, ABI, release and production readiness. ADR-0033 remains `PROPOSED`.
