# CORE-05 — Math & Coordinate Stack Research Matrix

**WO:** NLE-P00-WO-002-CORE-05 | **Issue:** #102 | **State:** PROPOSED / DOCS ONLY

| Candidate | How it works | License | Portability & advantage | Risk/gate |
|---|---|---|---|---|
| C++20 scalar reference + strong wrappers | owned public types, explicit units/spaces, simple constexpr vector/matrix functions | original owned code; language/runtime dependent | portable, easiest to golden test and stabilize ABI | don't reinvent general numerical algebra; SIMD performance to be measured |
| GLM (g-truc/glm) | header-only GLSL-like vectors, matrices, quaternions and transforms | permissive MIT or Happy Bunny modified MIT terms; verify chosen tag | Windows/Linux/macOS and C++17+ supported by current project; light adoption candidate | implicit conventions/precision/layout and compiler flags; wrapping necessary |
| Eigen 3.4/5.x | expression template dense/sparse matrix and geometry | MPL-2.0 weak copyleft | portable, strong scientific/numerical operations; header-only | notice/file-level licensing, template complexity, SIMD/ABI, compile times; use where warranted |
| DirectXMath | MS SIMD-friendly all-inline vectors/matrices | MIT | well-suited Windows Direct3D/Xbox code paths | Windows design target: cannot mandate as portable engine core |
| MathFu | game-centric matrix/quaternion library with SSE/NEON | see official repository LICENSE; verify exact terms | portable comparator for SIMD math | maintenance, transitive submodule footprint and test status require review |
| Ad hoc f32 everywhere | in-place homogeneous float positions | original | minimal transient memory | REJECT global large-world coordinate and source of precision/camera jitter |
| Global f64 + relative f32 | double absolute world and camera-relative float data | original | simple first candidate for large worlds | costly f64 serialization on memory-critical targets; GPU conversion tested |
| Signed cell index + local offset | i64 cells with bounded f32/f64 offsets | original | predictable large coordinates, streaming-friendly | complicated world rebasing, overflow and replication; don't mandate without scale evidence |

## Proposed selection order
1. Author a small, stable **type and coordinate contract**, independent of GLM/Eigen/DirectXMath types. Begin with scalar/oracle semantics and golden tests.
2. Evaluate GLM as primary mathematical implementation comparator for vector/matrix/quaternion work. Only pin exact release after license/CVE/toolchain review; no dependency is installed by this WO.
3. Use Eigen for heavy linear algebra only if a later subsystem needs it and MPL-2.0 obligations are consciously accepted.
4. DirectXMath optional on Windows and MathFu optional as performance comparators. Do not introduce code duplication by running 3 different maths kernels in one release.
5. Treat f64 global + relative f32 and optional cell+local schemes as **alternative architectures**, not an unverified claim of infinite precision.
6. No backend-specific clip-space, handedness or column-major assumption is silently imported: conversions must be explicit.

## Weighted evaluation; no manufactured scores
Correctness/typed boundaries 30%; large-world precision and rebase 20%; cross-platform and stable serialization 20%; CPU/ABI/SIMD measurable cost 15%; license/supply chain and maintainability 10%; developer ergonomics 5%. Benchmarks must report representative workloads and target hardware, with scalar baseline.

## Official references and verification
- GLM: https://github.com/g-truc/glm ; https://glm.g-truc.net/
- Eigen: https://libeigen.gitlab.io/index.html
- DirectXMath: https://learn.microsoft.com/en-us/windows/win32/dxmath/directxmath-portal ; https://github.com/microsoft/DirectXMath
- MathFu: https://google.github.io/mathfu/

**Status:** No production dependency selected, binary compiled, library vendored, hardware benchmark performed or final coordinate-space contract approved for engine code.
