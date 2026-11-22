# NLE-PRPLAN-CORE-05-04 — Matrices and quaternions slice (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Gate:** G6 implementation + CORE-01 capability admission. **Formal packet:** `NLE-PRPLAN-CORE-05-04`. **Predecessor:** `CORE-05-03` completed. **Issue:** #22. **Base:** `c81778bc22a6df36553b249e9311772dbf87a19e`. **ADR:** [ADR-0108](../adr/0108-core-05-governance-slice.md). **Contract:** [core-05-math-v0](../contracts/core-05-math-v0.md).

## OBJECTIVE

Implement the second CORE-05 slice: column-major `Mat3`/`Mat4`, affine/projection point transformation, determinant/inverse with scale-aware singular rejection, `Quat`, axis-angle construction, normalization, multiplication, conjugation, canonicalization and rotation. No coordinate-space wrappers, units, precision/origin, IDs, SIMD, third-party math, serialization, ABI or release is authorized.

## CONTEXT

CORE-05-01 governance, CORE-05-02 contract and CORE-05-03 vectors are approved/completed. ADR-0108 admits only completed CORE-01 capabilities; CORE-01 is not module-qualified. The owner instructed continuation on 2026-11-22. This packet activates only `CORE-05-04`.

## SCOPE

- `mat.hpp`: `Mat3<T>`, `Mat4<T>`, aliases, identity, multiply, transpose, translation, scaling, right-handed X/Y/Z rotations, `transform_point` with homogeneous divide, `transform_direction`, determinant and inverse.
- `quat.hpp`: `Quat<T>`, aliases, identity, axis-angle, normalize, Hamilton product, conjugate, dot, canonicalization and rotate.
- `tests/core/core05_matrix_quat_tests.cpp`: MATH-03, MATH-04 and MATH-05.
- Additive CMake target/tests and TSan target list.
- Evidence file.

## OUT OF SCOPE

`coords.hpp`, `units.hpp`, `precision.hpp`, `ids.hpp`, space/unit tags, `WorldPosition`/`OriginEpoch`, stable IDs, SIMD, third-party math, serialization, backend clip/projection, physics/GFX/WORLD/NET integration, public ABI/release, CORE-01 completion, CORE-05-05 or later.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0007/0086/0108, `core-05-math-v0`, CORE-05 architecture, CORE-05-03 evidence, CORE-01 capability evidence, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0108; ADR-0086; MATH-03/04/05; column-major `elements[column * N + row]`; no implicit narrow/non-finite propagation.

## ARCHITECTURE RULES

CORE-05 owns the math values; CORE-01/02/03/04, GFX clip/projection, SIM solver precision, DATA serialization, WORLD origin and NET replication remain their owners. Header-only internal C++20; scalar reference path only; no third-party include or intrinsic.

## CONSTRAINTS

Risk `ELEVATED`; release `INTERNAL_ONLY`; no dependency/package/secret/paid service; CORE-01 not module-qualified; CORE-02 NOT_QUALIFIED; CORE-03/04 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## ACCEPTANCE CRITERIA

- Exact allowlist; `Mat3/4` column-major storage and contract operations compile.
- MATH-03: identity/multiply/translation/scaling/rotation fixtures; point `w=1`, direction ignores translation; column-major indices checked.
- MATH-04: singular, near-singular, zero and non-finite matrices return `SingularMatrix`/`NonFinite`; valid inverse round-trips within tolerance.
- MATH-05: axis-angle fixtures; `q` and `-q` rotate identically and canonicalize identically; zero/non-finite/unnormalized quaternion inputs typed; conjugate/inverse rotation.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; no dependency/ABI/release change; pt-BR audit `APPROVED`.

## TESTS

MATH-03/04/05 from the contract, plus determinant/inverse, homogeneous divide, quaternion normalization/canonicalization and typed error fixtures. Existing full CTest suite remains required.

## DELIVERABLES

`mat.hpp`, `quat.hpp`, matrix/quaternion tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, MATH-03/04/05, sanitizers/CI, errors/corrections, security/rollback, no overclaim. APPROVED/CORRECTION REQUIRED/BLOCKED.

## STOP CONDITION

Stale base, gate not merged, API drift, third-party/intrinsic, coords/units/precision/ID code, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim. Stop and report.

## CONTEXT LOCK

Base `c81778bc22a6df36553b249e9311772dbf87a19e`; contract blob `e6fb5f8a4f9934848d71be9d535018b0b99531e2`; CORE-05-03 code PR #539 and closeout #540 merged.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-CORE-05-04-G6-ACTIVATION.md` for the gate; `docs/evidence/NLE-PRPLAN-CORE-05-04.md` for implementation.
