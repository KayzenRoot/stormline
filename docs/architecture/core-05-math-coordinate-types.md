# CORE-05 — Mathematical Foundation, Coordinate Spaces & Stable Types v0.1

**WO:** NLE-P00-WO-002-CORE-05 | **Research issue:** #102 | **State:** PROPOSED / DOCUMENTATION ONLY | **Risk:** LOW (docs); ELEVATED in world/physics serialization integration.

## Objective and cross-system ownership
Establish a precise, versionable mathematical vocabulary shared across Stormline 2D/2.5D/3D, Windows/Linux/macOS, headless and future web. Avoid representation errors becoming silent gameplay/physics/netcode divergence.

- CORE-05 owns math scalar/vector/matrix/quaternion and explicit coordinate/unit/identifier *contracts*.
- CORE-01 owns platform and CPU capabilities; CORE-02 memory and alignment policy; CORE-03 task scheduling; CORE-04 tick time.
- SIM, WORLD, GFX, DATA, NET, editor and MCP consume typed math APIs but must not silently change conventions or write internal state. GFX-01 handles backend projection/clip-space conversions, physics chooses solver precision in its own ADR.
- Public SDK should not depend on third-party library types. Interop adapters are opt-in, versioned and testable.

## Proposed spatial conventions (not a released API)
| Topic | Proposed invariant | Verification |
|---|---|---|
| World axes | 3D right-handed, +Y up, +X right, camera forward -Z; 2D uses explicit XY plane and view-space conversion | basis handedness and orientation golden tests |
| Units | meters for world distance, seconds for time from CORE-04, radians for angles; physical units strong typed at boundaries | dimension mismatch rejection, degrees/radians explicit conversion |
| Transform | column-vector matrix convention, world = parent * local; vector points w=1, directions w=0 | composed translation/rotation/scale and inverse |
| Memory representation | column-major matrix storage candidate, separately declared from algebraic multiplication order | matrix layout and interop test with GPU backends |
| Clip | clip depth/projection specified per GFX backend; NO assumption all Vulkan, D3D, Metal and Web backends share Y/depth conventions | round-trip clip conversion and near/far golden tests |
| Quaternion | normalized quaternion invariant at public boundaries, explicit sign-canonicalization for serialized equality, defined multiplication order | rotation/inverse and boundary tests; q and -q represent same rotation |
| Scalars | f32 for local/render payloads; f64 candidate for global persistent world origins; checked i64 cell indices | finite checks, precision budgets, overflow and same-point-after-rebase |
| IDs | persistent project/scene/asset references are stable opaque identifiers, in-memory entity handles are distinct generational identities | asset renaming and entity recycling cannot alias old references |

Choice of +Y and camera forward -Z is **PROPOSED**, not claimed to be the only valid choice. 2D y-down pixel canvas, UI and Web coordinate conventions are explicit adapters; direct conversion is forbidden without a named source/target space.

## Typed interface candidates (conceptual schemas)
- `Vec2<T,Space,Unit>`, `Vec3<T,Space,Unit>`, `Vec4<T,Space,Unit>` and `UnitQuaternion<T,From,To>`: tags prevent accidental world/local, pixels/meters and angle unit mixing. C++ template specialization is only one implementation candidate; avoid unbounded codegen.
- `Mat4<T,From,To>`, `Transform<From,To>`: explicit composition order, supported affine/invertible modes, singular matrix typed failure.
- `WorldPosition`: candidate `cell_i64[3] + local_f64[3]` or bounded global f64; compare memory/serialization cost. `LocalPositionF32` is a camera/physics-zone relative projection, never persisted as absolute world truth.
- `OriginEpoch` and `RebaseTransform`: stable origin version and signed delta, atomically applied at a simulation barrier. Origin shifts are coordinate changes, not movement/teleporting an entity.
- `PersistentId` vs `RuntimeHandle{index,generation}`: UUID128 or equivalent stable opaque project identifiers remain under selection; never serialize a volatile memory address or generational slot as a lasting reference.
- `Expected<T, MathError>` or equivalent: ZERO_LENGTH, NON_FINITE, SINGULAR_MATRIX, PRECISION_LOSS, OUT_OF_RANGE, OVERFLOW, SPACE_MISMATCH, INVALID_UNIT, INVALID_ORIGIN_EPOCH, INVALID_ID.
- `CoordinateConversion`: explicitly named from/to spaces, local-to-world, world-to-view, view-to-clip and inverse; typed errors on loss/unsupported backend.
- `MathSchemaVersion`: explicit serialization version, units, axes, matrix order, projection metadata; never reinterpret old coordinate data silently.

## Precision and large worlds
- A single global f32 absolute position does not scale safely across large worlds: represent world coordinates in double or indexed cells, then compute relative local f32 rendering/physics payload after subtracting origin **in high precision**.
- Proposed floating-origin protocol: WORLD layer chooses a new origin at a CORE-04 safe tick boundary; CORE-03 commits state/barrier before dependent SIM/GFX/NET snapshots; CORE-05 supplies pure checked transform conversion. Remote entities and physics velocities **do not change** as a result of coordinate rebase.
- Rebase is idempotent per origin epoch and must not be applied twice; shifts invalidate cached relative transforms intentionally and preserve stable global IDs. Serialization records global positions and origin metadata, never ephemeral camera-local coords.
- For deterministic replay, origin changes are tick-tagged ordered events. Numeric reproducibility across compilers/CPU SIMD/FTZ/FMA or physics solvers is a separate integration proof. Never promise bit identity by choosing double.
- Compare global f64 vs cell+i64/f64 after large map requirements. No fixed max world size, VRAM usage or centimeter precision guarantee without agreed bounds and benchmarks.

## Math safety and high performance
- Scalar reference path must be test oracle; SIMD SSE2/AVX2/NEON only behind verified CPU dispatch and bench on 2-core and Apple Silicon devices. Alignment, padding, ABI and endian must be documented before interop/serialization. Numeric stable scalar tests take priority over premature SIMD specialization.
- Safe normalization detects zero vectors, NaN and infinity. Matrix inversion returns typed singular/near-singular failure; tolerance must be scale-aware and specified by operation, not a universal epsilon. Invalid quaternion cannot silently propagate.
- No unsafe mixed f32/f64 implicit narrowing; serialized numeric fields use explicit precision, endianness and schema.
- No generational runtime handle in persisted assets or externally accessible MCP resources. MCP/CLI receives validated commands with stable reference IDs and scope authorization, no raw address or arbitrary object mutation.

## Future golden tests and proof obligations (NOT RUN)
1. Coordinate basis/handedness: cross(+X,+Y)=+Z for right-handed world; +Y up, -Z forward; explicit 2D/UI conversion. Verify transform matrices Mparent * Mchild and round-trip parent/local/world.
2. Quaternion inverse/normalization, q/-q equivalent rotation and explicit serialized canonicalization; sign of transformed basis vectors and negative/nonuniform scale handling.
3. Degenerate, near-singular, nonfinite, zero-length and invalid unit/space input rejected with typed outcomes; tolerance parameter fixtures and overflow checks.
4. Meter/pixel/angle conversions, vertical camera mirroring, handedness and clip depth for each actual graphics backend **after GFX-01 picks APIs**; do not present speculative graphics tests as run.
5. Translation beyond 10^6 and 10^9 meters with camera-relative f32 vs unshifted f32; record relative positional error in meters and define a numeric budget before PASS. Multi-cell 64-bit overflow and negative-index tests.
6. Origin shift before/after a network snapshot preserves global position and stable persistent IDs; multiple shifts and rollback/replay event order respect TickId.
7. PersistentId survives rename/save-reopen; stale RuntimeHandle rejected after generation change; collisions simulated and validated.
8. SIMD scalar-reference differential and cross-compiler tests: MSVC/clang-cl x64 Windows, GCC/Clang Linux, Apple Clang arm64 macOS, Intel feasibility; web wasm opt-in. Record CPU/GPU, toolchain, flags, seed, tolerance, sample count, p95 cost in future executable WO.
9. Performance/precision only measured with hardware and workload evidence. No native code, benchmarks, renderer or editor built in this planning phase.

## Alternatives and limitations
- C++20 custom small strongly typed wrappers + scalar baseline recommended for API boundaries, optionally GLM as implementation aid. Do not reinvent a general linear algebra library prematurely.
- GLM modern releases support C++17+ and permissive license; GPU storage layout and numerical behavior are **not** fixed implicitly by GLM type names.
- Eigen robust for broader linear algebra but MPL-2.0 obligations and heavier generic features must be evaluated; do not introduce weak-copyleft dependency without owner-approved distribution analysis.
- DirectXMath is MIT and SIMD-aware but Windows-oriented; use only behind an optional Windows backend, never required cross-platform public types.
- Original Stormline precision innovations must be measurable against simple camera-relative f64+f32 and cell approaches.

## Approved-vs-proposed gate
This document is research candidate only. CORE-05 implementation issue #22 remains BLOCKED with executor_ready=false. Implementation requires exact ABI/types/file paths, schema and backend conversions, approved ADR, dependency proofs, actual tests and resource budgets.

## Sources
- GLM official source/compiler/licensing: https://github.com/g-truc/glm
- GLM official documentation: https://glm.g-truc.net/
- Eigen headers/MPL2: https://libeigen.gitlab.io/index.html
- DirectXMath platform and license: https://learn.microsoft.com/en-us/windows/win32/dxmath/directxmath-portal and https://github.com/microsoft/DirectXMath
- MathFu optional game SIMD comparator: https://google.github.io/mathfu/
- JoltPhysics world precision behavior for future SIM integration: https://jrouwe.github.io/JoltPhysicsDocs/
