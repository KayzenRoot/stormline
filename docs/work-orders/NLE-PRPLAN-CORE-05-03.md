# NLE-PRPLAN-CORE-05-03 — Scalar/error/vector slice (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Gate:** G6 implementation + CORE-01 capability admission. **Formal packet:** `NLE-PRPLAN-CORE-05-03`. **Predecessor:** `CORE-05-02` contract. **Issue:** #22. **Base:** `de206bfc17f2f43011ca06effe9993baee85cab3`. **ADR:** [ADR-0108](../adr/0108-core-05-governance-slice.md). **Contract:** [core-05-math-v0](../contracts/core-05-math-v0.md).

## OBJECTIVE

Implement exactly the first CORE-05 slice: owned scalar aliases, `MathError`, `MathResult<T>`, `Vec2/3/4` and the frozen vector operations with typed failures. No matrices, quaternions, coordinate transforms, units, precision/origin or IDs are authorized.

## CONTEXT

CORE-05-01 governance and CORE-05-02 contract are approved. ADR-0108 admits only completed CORE-01 capabilities; CORE-01 is not module-qualified. The owner instructed continuation on 2026-11-22. This packet activates only `CORE-05-03`.

## SCOPE

- `math_types.hpp`: `f32`, `f64`, constants, `MathError`, `MathResult<T>`, `Vec2/3/4` and scalar aliases.
- `vec.hpp`: component-wise add/subtract/scale, dot, 3D cross, length squared/length, normalize, finite and approximate equality exactly as contracted.
- `tests/core/core05_vector_tests.cpp`: MATH-01, MATH-02 and typed scalar/error fixtures.
- Additive CMake `INTERFACE` target/tests and workflow path filters.
- Evidence file.

## OUT OF SCOPE

`Mat3/4`, `Quat`, coordinate-space wrappers/transforms, units, `WorldPosition`/`OriginEpoch`, `PersistentId`/`RuntimeHandle`, SIMD, third-party math, serialization, physics/GFX/netcode/WORLD integration, public ABI/release, CORE-01 completion, CORE-05-04 or later.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0007/0086/0108, `core-05-math-v0`/governance contracts, CORE-05 architecture, CORE-01 capability evidence, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0108; ADR-0086; contract semantics for `MathError`/`MathResult`/vectors; no implicit narrowing or non-finite propagation.

## ARCHITECTURE RULES

CORE-05 owns math value types. CORE-01 platform/CPU, CORE-02 memory, CORE-03 scheduling, CORE-04 `TickId`, GFX/ SIM/ DATA/ WORLD/ NET boundaries unchanged. Header-only internal C++20; no exception crosses the API; no third-party include or intrinsic.

## CONSTRAINTS

Risk `ELEVATED`; release `INTERNAL_ONLY`; no dependency/package/secret/paid service; CORE-01 not module-qualified; CORE-02 NOT_QUALIFIED; CORE-03/04 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## ACCEPTANCE CRITERIA

- Exact allowlist; all declared vector operations compile and match the contract.
- MATH-01: add/subtract/scale/dot exact fixtures for `Vec2/3/4`; zero-length normalize → `ZeroLength`; non-finite normalize → `NonFinite`; no NaN propagation.
- MATH-02: right-handed basis, `cross(+X,+Y) == +Z`; `+Y` up, `-Z` forward; no 2D/UI conversion invented.
- `length`/`normalized` overflow and finite checks are typed; `approx_equal` rejects invalid tolerances.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; no dependency/ABI/release change.
- pt-BR audit `APPROVED`; manifest effect after merge documented.

## TESTS

MATH-01 and MATH-02 from the contract, plus scalar `MathResult` success/failure, component finite checks, tolerance validation and overflow/non-finite fixtures. Existing full CTest suite remains required.

## DELIVERABLES

`math_types.hpp`, `vec.hpp`, vector tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, MATH-01/02, sanitizers/CI, errors/corrections, security/rollback, no overclaim. APPROVED/CORRECTION REQUIRED/BLOCKED.

## STOP CONDITION

Stale base, gate not merged, API drift, third-party/intrinsic, matrix/quat/coords/units/precision/ID code, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim. Stop and report.

## CONTEXT LOCK

Base `de206bfc17f2f43011ca06effe9993baee85cab3`; contract blob `e6fb5f8a4f9934848d71be9d535018b0b99531e2`; CORE-05-02 gate PR #537.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-CORE-05-03-G6-ACTIVATION.md` for the gate; `docs/evidence/NLE-PRPLAN-CORE-05-03.md` for implementation.
