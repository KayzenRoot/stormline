# CORE-05 INTERNAL_ONLY Math / Coordinates / Units / Precision / IDs Contract v0 (NLE-PRPLAN-CORE-05-02)

**Status:** `CONTRACT PROPOSAL / NOT IMPLEMENTED / NO CODE AUTHORIZED`. **Base:** `d08150a11b9688482ae2aa4d84b3a5756830fa75`. **ADR:** [ADR-0108](../adr/0108-core-05-governance-slice.md), [ADR-0007](../adr/0007-core-05-coordinate-policy.md) planning-only. **WO:** [NLE-PRPLAN-CORE-05-02](../work-orders/NLE-PRPLAN-CORE-05-02.md).

## Objective

Freeze the first bounded CORE-05 logical API for original scalar/vector/matrix/quaternion math, explicit coordinate spaces, unit-bearing quantities, world precision/origin epoch and stable identifiers. Define typed errors, golden-test oracles and exact implementation allowlists. No implementation, dependency, public ABI, serialization, release or engine integration is authorized by this contract.

## Admission and boundaries

- Formal `CORE-01` dependency remains; admission is limited to completed `CORE-01-03/-06/-07/-08/-12/-13` capabilities under ADR-0108/ADR-0086. CORE-01 module completion is **not** claimed.
- CORE-05 owns owned math value types, coordinate/unit tags, world precision/origin epoch and stable identifier contracts.
- CORE-01 owns platform/CPU detection; CORE-02 memory/alignment; CORE-03 scheduling; CORE-04 `TickId`; GFX-01 backend clip/projection and winding; SIM physics solver precision; DATA serialization format; WORLD origin-shift orchestration; NET replication. Those owners are unchanged.
- No third-party math type, GLM/Eigen/DirectXMath/MathFu include, SIMD intrinsic, platform API or public ABI appears in this contract.
- All production headers are internal, header-only and exception-free. C++20 only.

## Conventions

- Right-handed 3D world: `+X` right, `+Y` up, `-Z` forward. `cross(+X,+Y) = +Z`.
- World distance in meters; time in seconds (CORE-04 owns the tick clock); angles in radians at math boundaries. Degrees are an explicit unit conversion.
- Column-vector algebra: `world = parent * local`; points use `w = 1`; directions use `w = 0`.
- Matrix algebraic composition order is separate from storage. `Mat3`/`Mat4` store **column-major** values at `elements[column * dimension + row]`; no code may infer algebraic order from memory byte order.
- 2D/UI pixel coordinate systems, clip-space Y/depth and graphics winding are named adapters owned by later modules, never implicit. No conversion is provided by this contract.
- `f32` is the local/render candidate; `f64` is the first global persistent-origin candidate. Signed-cell positions are not selected in v0.
- No bit-exact numerical, cross-compiler, cross-CPU, SIMD or physics/netcode determinism claim is made.

## Internal API (logical, exact names)

```cpp
namespace stormline::core::math {

using f32 = float;
using f64 = double;

inline constexpr f64 kPi = 3.14159265358979323846;
inline constexpr f64 kDegreesToRadians = kPi / 180.0;
inline constexpr f64 kRadiansToDegrees = 180.0 / kPi;
inline constexpr std::uint32_t kMathSchemaVersion = 1;

enum class MathError : std::uint8_t {
    None,
    NonFinite,
    ZeroLength,
    SingularMatrix,
    Overflow,
    OutOfRange,
    InvalidQuaternion,
    SpaceMismatch,
    UnitMismatch,
    PrecisionLoss,
    InvalidOriginEpoch,
    StaleHandle,
    InvalidId,
    InternalFailure
};

template <typename T>
struct MathResult {
    T value{};
    MathError error{MathError::None};
    [[nodiscard]] constexpr bool ok() const noexcept {
        return error == MathError::None;
    }
};

template <typename T> struct Vec2 { T x{}, y{}; };
template <typename T> struct Vec3 { T x{}, y{}, z{}; };
template <typename T> struct Vec4 { T x{}, y{}, z{}, w{}; };
template <typename T> struct Mat3 { std::array<T, 9> elements{}; };
template <typename T> struct Mat4 { std::array<T, 16> elements{}; };
template <typename T> struct Quat { T x{}, y{}, z{}, w{}; };

using Vec2f = Vec2<f32>;  using Vec2d = Vec2<f64>;
using Vec3f = Vec3<f32>;  using Vec3d = Vec3<f64>;
using Vec4f = Vec4<f32>;  using Vec4d = Vec4<f64>;
using Mat3f = Mat3<f32>;  using Mat3d = Mat3<f64>;
using Mat4f = Mat4<f32>;  using Mat4d = Mat4<f64>;
using Quatf = Quat<f32>;  using Quatd = Quat<f64>;

// math_types.hpp / vec.hpp -- CORE-05-03
template <typename T> [[nodiscard]] constexpr Vec2<T> add(const Vec2<T>&, const Vec2<T>&) noexcept;
template <typename T> [[nodiscard]] constexpr Vec3<T> add(const Vec3<T>&, const Vec3<T>&) noexcept;
template <typename T> [[nodiscard]] constexpr Vec4<T> add(const Vec4<T>&, const Vec4<T>&) noexcept;
template <typename T> [[nodiscard]] constexpr Vec2<T> subtract(const Vec2<T>&, const Vec2<T>&) noexcept;
template <typename T> [[nodiscard]] constexpr Vec3<T> subtract(const Vec3<T>&, const Vec3<T>&) noexcept;
template <typename T> [[nodiscard]] constexpr Vec4<T> subtract(const Vec4<T>&, const Vec4<T>&) noexcept;
template <typename T> [[nodiscard]] constexpr Vec2<T> scale(const Vec2<T>&, T) noexcept;
template <typename T> [[nodiscard]] constexpr Vec3<T> scale(const Vec3<T>&, T) noexcept;
template <typename T> [[nodiscard]] constexpr Vec4<T> scale(const Vec4<T>&, T) noexcept;
template <typename T> [[nodiscard]] constexpr T dot(const Vec2<T>&, const Vec2<T>&) noexcept;
template <typename T> [[nodiscard]] constexpr T dot(const Vec3<T>&, const Vec3<T>&) noexcept;
template <typename T> [[nodiscard]] constexpr T dot(const Vec4<T>&, const Vec4<T>&) noexcept;
template <typename T> [[nodiscard]] constexpr Vec3<T> cross(const Vec3<T>&, const Vec3<T>&) noexcept;
template <typename T> [[nodiscard]] constexpr T length_squared(const Vec2<T>&) noexcept;
template <typename T> [[nodiscard]] constexpr T length_squared(const Vec3<T>&) noexcept;
template <typename T> [[nodiscard]] constexpr T length_squared(const Vec4<T>&) noexcept;
template <typename T> [[nodiscard]] MathResult<T> length(const Vec2<T>&) noexcept;
template <typename T> [[nodiscard]] MathResult<T> length(const Vec3<T>&) noexcept;
template <typename T> [[nodiscard]] MathResult<T> length(const Vec4<T>&) noexcept;
template <typename T> [[nodiscard]] MathResult<Vec2<T>> normalized(const Vec2<T>&) noexcept;
template <typename T> [[nodiscard]] MathResult<Vec3<T>> normalized(const Vec3<T>&) noexcept;
template <typename T> [[nodiscard]] MathResult<Vec4<T>> normalized(const Vec4<T>&) noexcept;
template <typename T> [[nodiscard]] constexpr bool finite(const Vec2<T>&) noexcept;
template <typename T> [[nodiscard]] constexpr bool finite(const Vec3<T>&) noexcept;
template <typename T> [[nodiscard]] constexpr bool finite(const Vec4<T>&) noexcept;
template <typename T> [[nodiscard]] bool approx_equal(T, T, T abs_tolerance, T rel_tolerance) noexcept;
template <typename T> [[nodiscard]] bool approx_equal(const Vec2<T>&, const Vec2<T>&, T, T) noexcept;
template <typename T> [[nodiscard]] bool approx_equal(const Vec3<T>&, const Vec3<T>&, T, T) noexcept;
template <typename T> [[nodiscard]] bool approx_equal(const Vec4<T>&, const Vec4<T>&, T, T) noexcept;

// mat.hpp -- CORE-05-04
template <typename T> [[nodiscard]] constexpr Mat3<T> identity3() noexcept;
template <typename T> [[nodiscard]] constexpr Mat4<T> identity4() noexcept;
template <typename T> [[nodiscard]] Mat3<T> multiply(const Mat3<T>&, const Mat3<T>&) noexcept;
template <typename T> [[nodiscard]] Mat4<T> multiply(const Mat4<T>&, const Mat4<T>&) noexcept;
template <typename T> [[nodiscard]] constexpr Mat3<T> transpose(const Mat3<T>&) noexcept;
template <typename T> [[nodiscard]] constexpr Mat4<T> transpose(const Mat4<T>&) noexcept;
template <typename T> [[nodiscard]] constexpr Mat4<T> translation(const Vec3<T>&) noexcept;
template <typename T> [[nodiscard]] constexpr Mat4<T> scaling(const Vec3<T>&) noexcept;
template <typename T> [[nodiscard]] Mat4<T> rotation_x(T radians) noexcept;
template <typename T> [[nodiscard]] Mat4<T> rotation_y(T radians) noexcept;
template <typename T> [[nodiscard]] Mat4<T> rotation_z(T radians) noexcept;
template <typename T> [[nodiscard]] MathResult<Vec3<T>> transform_point(const Mat4<T>&, const Vec3<T>&) noexcept;
template <typename T> [[nodiscard]] Vec3<T> transform_direction(const Mat4<T>&, const Vec3<T>&) noexcept;
template <typename T> [[nodiscard]] MathResult<T> determinant(const Mat3<T>&) noexcept;
template <typename T> [[nodiscard]] MathResult<T> determinant(const Mat4<T>&) noexcept;
template <typename T> [[nodiscard]] MathResult<Mat3<T>> inverse(const Mat3<T>&) noexcept;
template <typename T> [[nodiscard]] MathResult<Mat4<T>> inverse(const Mat4<T>&) noexcept;

// quat.hpp -- CORE-05-04
template <typename T> [[nodiscard]] constexpr Quat<T> identity_quat() noexcept;
template <typename T> [[nodiscard]] MathResult<Quat<T>> from_axis_angle(const Vec3<T>& axis, T radians) noexcept;
template <typename T> [[nodiscard]] MathResult<Quat<T>> normalized(const Quat<T>&) noexcept;
template <typename T> [[nodiscard]] constexpr Quat<T> multiply(const Quat<T>&, const Quat<T>&) noexcept;
template <typename T> [[nodiscard]] constexpr Quat<T> conjugate(const Quat<T>&) noexcept;
template <typename T> [[nodiscard]] constexpr T dot(const Quat<T>&, const Quat<T>&) noexcept;
template <typename T> [[nodiscard]] constexpr Quat<T> canonicalized(const Quat<T>&) noexcept;
template <typename T> [[nodiscard]] MathResult<Vec3<T>> rotate(const Quat<T>&, const Vec3<T>&) noexcept;

// coords.hpp -- CORE-05-05
struct WorldSpace final {};
struct LocalSpace final {};
struct ViewSpace final {};
struct ClipSpace final {};
struct PixelSpace final {};

template <typename T, typename Space> struct Position3 { Vec3<T> value{}; };
template <typename T, typename Space> struct Direction3 { Vec3<T> value{}; };
template <typename T, typename From, typename To> struct Transform3 { Mat4<T> matrix{}; };

template <typename T, typename Space>
[[nodiscard]] constexpr Transform3<T, Space, Space> identity_transform() noexcept;
template <typename T, typename A, typename B, typename C>
[[nodiscard]] Transform3<T, A, C> compose(
    const Transform3<T, B, C>& parent,
    const Transform3<T, A, B>& child) noexcept;
template <typename T, typename From, typename To>
[[nodiscard]] MathResult<Position3<T, To>> transform_position(
    const Transform3<T, From, To>&, const Position3<T, From>&) noexcept;
template <typename T, typename From, typename To>
[[nodiscard]] Direction3<T, To> transform_direction(
    const Transform3<T, From, To>&, const Direction3<T, From>&) noexcept;
template <typename T, typename From, typename To>
[[nodiscard]] MathResult<Transform3<T, To, From>> inverse(
    const Transform3<T, From, To>&) noexcept;

// units.hpp -- CORE-05-06
struct Meters final {};
struct Centimeters final {};
struct Millimeters final {};
struct Seconds final {};
struct Milliseconds final {};
struct Radians final {};
struct Degrees final {};

template <typename T, typename Unit> struct Quantity { T value{}; };

template <typename T, typename Unit>
[[nodiscard]] constexpr Quantity<T, Unit> add(const Quantity<T, Unit>&, const Quantity<T, Unit>&) noexcept;
template <typename T, typename Unit>
[[nodiscard]] constexpr Quantity<T, Unit> subtract(const Quantity<T, Unit>&, const Quantity<T, Unit>&) noexcept;
template <typename T, typename Unit>
[[nodiscard]] constexpr Quantity<T, Unit> scale(const Quantity<T, Unit>&, T) noexcept;
template <typename T>
[[nodiscard]] MathResult<Quantity<T, Radians>> to_radians(Quantity<T, Degrees>) noexcept;
template <typename T>
[[nodiscard]] MathResult<Quantity<T, Degrees>> to_degrees(Quantity<T, Radians>) noexcept;
template <typename T>
[[nodiscard]] MathResult<Quantity<T, Meters>> to_meters(Quantity<T, Centimeters>) noexcept;
template <typename T>
[[nodiscard]] MathResult<Quantity<T, Centimeters>> to_centimeters(Quantity<T, Meters>) noexcept;
template <typename T>
[[nodiscard]] MathResult<Quantity<T, Meters>> to_meters(Quantity<T, Millimeters>) noexcept;
template <typename T>
[[nodiscard]] MathResult<Quantity<T, Seconds>> to_seconds(Quantity<T, Milliseconds>) noexcept;
template <typename T>
[[nodiscard]] MathResult<Quantity<T, Milliseconds>> to_milliseconds(Quantity<T, Seconds>) noexcept;

// precision.hpp -- CORE-05-07
struct OriginEpoch { std::uint64_t value{0}; };
struct WorldPosition { Vec3<f64> global_meters{}; OriginEpoch epoch{}; };
struct LocalPosition { Vec3<f32> meters{}; OriginEpoch epoch{}; };
struct Origin { Vec3<f64> meters{}; OriginEpoch epoch{}; };

[[nodiscard]] MathResult<LocalPosition> to_local(
    const WorldPosition&, const Origin&) noexcept;
[[nodiscard]] MathResult<WorldPosition> to_world(
    const LocalPosition&, const Origin&) noexcept;
[[nodiscard]] MathResult<WorldPosition> rebase(
    const WorldPosition&, OriginEpoch expected, OriginEpoch next) noexcept;
[[nodiscard]] f64 local_error_bound(f64 global_delta_meters) noexcept;

// ids.hpp -- CORE-05-08
struct PersistentId {
    std::uint64_t high{0};
    std::uint64_t low{0};
    friend constexpr bool operator==(PersistentId, PersistentId) noexcept = default;
};
struct RuntimeHandle {
    std::uint32_t index{0};
    std::uint32_t generation{0};
    friend constexpr bool operator==(RuntimeHandle, RuntimeHandle) noexcept = default;
};
struct IdBytes { std::array<std::uint8_t, 16> bytes{}; };

[[nodiscard]] constexpr bool valid(PersistentId) noexcept;
[[nodiscard]] constexpr bool valid(RuntimeHandle) noexcept;
[[nodiscard]] constexpr bool handle_is_current(RuntimeHandle, std::uint32_t current_generation) noexcept;
[[nodiscard]] IdBytes encode_persistent_id(PersistentId) noexcept;
[[nodiscard]] MathResult<PersistentId> decode_persistent_id(const IdBytes&) noexcept;

}  // namespace stormline::core::math
```

No implementation is provided. Names or semantics may be refined only by an audited contract correction before `CORE-05-03`.

## Semantics

- **Errors:** no exception crosses the API. Inputs that are non-finite, zero-length where a direction is required, singular/near-singular for inversion, outside `f32` range, stale epoch/handle or invalid identifier return the listed `MathError`; no `NaN`/`Inf` is silently propagated. `MathResult<T>` uses `None` on success and a non-`None` error with a default-initialized `value` on failure.
- **Vector:** component-wise `add`/`subtract`/`scale`; `dot`; 3D `cross`. `length_squared` may overflow to infinity for extreme inputs; callers requiring validation use `length`. `length` rejects non-finite components with `NonFinite` and non-finite/overflowed magnitude with `Overflow`. `normalized` rejects a zero vector with `ZeroLength`, non-finite input with `NonFinite` and non-finite magnitude with `Overflow`; it returns a finite unit vector within tolerance.
- **Approximation:** `approx_equal` compares component-wise using `|a-b| <= max(abs_tolerance, rel_tolerance * max(|a|,|b|))`. Negative or non-finite tolerances return `false`; the function is never a correctness substitute for exact integer/fixture oracles.
- **Matrices:** `elements` is column-major storage: `elements[column * N + row]`. `multiply(A, B)` computes algebraic `A * B`; `translation(t)` maps `p` to `p + t`; `scaling(s)` maps component-wise; `rotation_x/y/z` are right-handed positive rotations in radians. `transform_point` computes homogeneous `w`, divides when `w != 1`, and returns `SingularMatrix` when `w` is zero or non-finite; `transform_direction` ignores translation. `determinant` rejects non-finite inputs/result with `NonFinite`/`Overflow`. `inverse` rejects non-finite input with `NonFinite`, and `|det| <= epsilon * scale^N` with `SingularMatrix`, where `scale` is the maximum absolute input element and `N` is 3 or 4. It computes in the input scalar type; it makes no cross-compiler bit-identity claim.
- **Quaternions:** storage `{x,y,z,w}`. `from_axis_angle` normalizes the axis and rejects zero/non-finite axes. `normalized` rejects zero/non-finite/overflowed norm. `multiply` uses Hamilton product; `conjugate` negates `x,y,z`; `rotate` requires a normalized quaternion within `8 * epsilon` of unit norm and returns `InvalidQuaternion` otherwise. `canonicalized` returns the same rotation with `w > 0`, or when `w == 0` the first nonzero of `x,y,z` positive; `q` and `-q` therefore canonicalize identically. Sign canonicalization is for serialized equality, not a claim that raw quaternions are unique.
- **Spaces:** `Position3<T, Space>`, `Direction3<T, Space>` and `Transform3<T, From, To>` use distinct C++ types. Cross-space assignment, addition or transformation without a matching `Transform3` is a compile-time error. `compose(parent, child)` requires `parent: B->C` and `child: A->B` and returns `A->C` with matrix `parent.matrix * child.matrix`. `transform_position` returns `SingularMatrix` when homogeneous `w` is zero/non-finite. `inverse` returns `SingularMatrix`/`NonFinite` consistently with matrix inversion. No world/view/clip/pixel conversion is implemented in v0; later owners add named transforms.
- **Units:** distinct `Quantity<T, Unit>` types prevent implicit mixing. `add`/`subtract` require the same unit and scalar type; `scale` preserves unit. Conversion functions are explicit and reject non-finite input/result with `NonFinite`/`Overflow`. Degrees/radians use `kDegreesToRadians`/`kRadiansToDegrees`; meters/centimeters/millimeters use exact decimal scale; seconds/milliseconds use 1000. No implicit narrowing between `f32` and `f64`.
- **Precision:** `WorldPosition.global_meters` is global truth in `f64`; `LocalPosition.meters` is a relative `f32` payload tied to an `OriginEpoch`. `to_local` requires equal epochs, subtracts origin in `f64`, rejects a delta outside `f32` finite range with `Overflow`, and returns the rounded local value. `to_world` requires equal epochs and rejects non-finite result with `Overflow`. `rebase` requires `expected == position.epoch` and `next.value > expected.value`; it preserves `global_meters` exactly and only advances the epoch, proving that an origin shift is not gameplay movement. Double application with the same stale expected epoch returns `InvalidOriginEpoch`. `local_error_bound(delta)` returns `2^-24 * max(1.0, |delta|)` as the documented `f32` rounding budget; it is not a guarantee for accumulated operations.
- **IDs:** `PersistentId{0,0}` is invalid; a valid persistent ID is stable across rename/save/reopen and is not a pointer, address or runtime index. `RuntimeHandle.index == 0` or `generation == 0` is invalid; `handle_is_current` is false for invalid handles and for any generation mismatch. Recycling a slot with a new generation must not validate an old handle. `encode_persistent_id` writes `high` then `low` as 16 big-endian bytes; `decode_persistent_id` rejects an all-zero result with `InvalidId`.
- **Schema:** `kMathSchemaVersion` is 1. Persistence must record it together with axes, units and matrix storage; no old coordinate data may be reinterpreted silently. DATA owns the actual serialization format.
- **Determinism envelope:** the scalar reference path is the test oracle. No SIMD, FMA contraction, fast-math, FTZ or third-party backend is selected. Same inputs and same IEEE-754 scalar operations are expected to produce the same results on a conforming target, but no cross-compiler/CPU bit-identity or physics/netcode determinism is claimed.

## Test oracles (future CORE-05-03..-09)

| ID | Scenario | Oracle |
|---|---|---|
| MATH-01 | vector algebra | add/subtract/scale/dot exact fixtures for `Vec2/3/4`; zero-length and non-finite normalize return `ZeroLength`/`NonFinite`; no NaN propagation |
| MATH-02 | basis/handedness | `cross(+X,+Y) == +Z`, `+Y` up, `-Z` forward; 2D/UI conversion is absent and compile-time explicit |
| MATH-03 | matrix composition | identity, `multiply(A,B)`, translation/scale/rotation fixtures; `transform_point` uses `w=1`; `transform_direction` ignores translation; column-major indices verified |
| MATH-04 | matrix degeneracy | exact singular, near-singular (at/below `epsilon * scale^N`), non-finite and zero matrices → `SingularMatrix`/`NonFinite`; valid inverse round-trips within tolerance |
| MATH-05 | quaternions | axis/angle fixtures; `q` and `-q` give the same rotated vector and canonicalize identically; inverse rotation; zero/non-finite/unnormalized inputs → typed errors |
| MATH-06 | transform spaces | parent `B->C` times child `A->B`; point/direction composition; round-trip `inverse`; cross-space mismatch fails to compile (static_assert fixture) |
| MATH-07 | units | 180° = π rad, 100 cm = 1 m, 1 s = 1000 ms; non-finite conversion → `NonFinite`; unit/space mixing fails to compile |
| MATH-08 | large coordinates | `f64` global at 10^6 and 10^9 m with camera-relative `f32`; error ≤ `local_error_bound(delta)`; no unshifted `f32` absolute claim |
| MATH-09 | origin rebase | `to_local`/`to_world` preserve global point within budget; rebase preserves `global_meters` exactly, advances epoch once, rejects stale/backward/duplicate epoch with `InvalidOriginEpoch` |
| MATH-10 | stable IDs | persistent ID equality and big-endian encode/decode round-trip; all-zero invalid; rename/reopen does not change bytes |
| MATH-11 | runtime handles | generation mismatch and invalid index/generation rejected; slot recycling cannot validate an old handle; no address-derived identity |
| MATH-12 | determinism/quality | scalar path only; no third-party include, SIMD intrinsic, RTTI/exception dependency or public ABI; repeated runs and Linux/Windows/macOS builds agree on fixtures |

## Implementation allowlists

Headers are internal and header-only. CMake adds one `INTERFACE` target and one test executable per packet; no production `.cpp` is required. Any new file requires an audited contract correction.

### `CORE-05-03` (scalar, errors, result, vectors)

1. `src/stormline/core/math/math_types.hpp`
2. `src/stormline/core/math/vec.hpp`
3. `tests/core/core05_vector_tests.cpp`
4. `CMakeLists.txt` (additive CORE-05 target/tests)
5. `.github/workflows/core01-internal-headless.yml` (additive CORE-05 filters)
6. `docs/evidence/NLE-PRPLAN-CORE-05-03.md`

### `CORE-05-04` (matrices and quaternions)

1. `src/stormline/core/math/mat.hpp`
2. `src/stormline/core/math/quat.hpp`
3. `tests/core/core05_matrix_quat_tests.cpp`
4. `CMakeLists.txt` (additive CORE-05 target/tests)
5. `.github/workflows/core01-internal-headless.yml` (additive CORE-05 filters)
6. `docs/evidence/NLE-PRPLAN-CORE-05-04.md`

### `CORE-05-05` (coordinate spaces and transforms)

1. `src/stormline/core/math/coords.hpp`
2. `tests/core/core05_coord_tests.cpp`
3. `CMakeLists.txt` (additive CORE-05 target/tests)
4. `.github/workflows/core01-internal-headless.yml` (additive CORE-05 filters)
5. `docs/evidence/NLE-PRPLAN-CORE-05-05.md`

### `CORE-05-06` (units)

1. `src/stormline/core/math/units.hpp`
2. `tests/core/core05_unit_tests.cpp`
3. `CMakeLists.txt` (additive CORE-05 target/tests)
4. `.github/workflows/core01-internal-headless.yml` (additive CORE-05 filters)
5. `docs/evidence/NLE-PRPLAN-CORE-05-06.md`

### `CORE-05-07` (precision / origin epoch)

1. `src/stormline/core/math/precision.hpp`
2. `tests/core/core05_precision_tests.cpp`
3. `CMakeLists.txt` (additive CORE-05 target/tests)
4. `.github/workflows/core01-internal-headless.yml` (additive CORE-05 filters)
5. `docs/evidence/NLE-PRPLAN-CORE-05-07.md`

### `CORE-05-08` (stable IDs / runtime handles)

1. `src/stormline/core/math/ids.hpp`
2. `tests/core/core05_id_tests.cpp`
3. `CMakeLists.txt` (additive CORE-05 target/tests)
4. `.github/workflows/core01-internal-headless.yml` (additive CORE-05 filters)
5. `docs/evidence/NLE-PRPLAN-CORE-05-08.md`

### `CORE-05-09` (qualification)

1. `tests/core/core05_qualification_tests.cpp`
2. `CMakeLists.txt` (additive CORE-05 qualification target)
3. `.github/workflows/core01-internal-headless.yml` (additive CORE-05 qualification filters)
4. `docs/evidence/NLE-PRPLAN-CORE-05-09.md`

`CORE-05-10` is documentary closeout only. Qualification requires separate G6 and real cross-target CI; no hardware, SIMD or performance PASS is implied.

## Stop / rollback / security

Stop on stale source, missing admission, third-party math type, SIMD/platform intrinsic, implicit narrowing, non-finite propagation, unbounded template space/type, public ABI/release claim, `CORE-01` completion claim or HIGH/CRITICAL. Unmerged: close the branch. After merge: normal revert PR; never force push.

No implementation is authorized by this contract. `CORE-05-03` requires its own G6 activation and explicit owner authorization.
