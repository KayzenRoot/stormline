# NLE-PRPLAN-CORE-05-05 — Typed coordinate spaces (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Gate:** G6 implementation + CORE-01 capability admission. **Formal packet:** `NLE-PRPLAN-CORE-05-05`. **Predecessor:** `CORE-05-04` completed. **Issue:** #22. **Base:** `a9e1fce752e8190d875caa5d7fea7415d0a6c8ab`. **ADR:** [ADR-0108](../adr/0108-core-05-governance-slice.md). **Contract:** [core-05-math-v0](../contracts/core-05-math-v0.md).

## OBJECTIVE

Implement typed `WorldSpace`/`LocalSpace`/`ViewSpace`/`ClipSpace`/`PixelSpace` tags, `Position3`, `Direction3`, `Transform3`, identity/compose/transform/inverse with compile-time space separation. No units, precision/origin, IDs, backend projection, SIMD, third-party math, serialization, ABI or release is authorized.

## CONTEXT

CORE-05-01/02/03/04 are approved/completed. ADR-0108 admits only completed CORE-01 capabilities; CORE-01 is not module-qualified. The owner instructed continuation on 2026-11-22. This packet activates only `CORE-05-05`.

## SCOPE

- `coords.hpp`: space tags, `Position3<T,Space>`, `Direction3<T,Space>`, `Transform3<T,From,To>`, `identity_transform`, `compose`, `transform_position`, `transform_direction`, `inverse`.
- `tests/core/core05_coord_tests.cpp`: MATH-06 and compile-time mismatch fixtures.
- Additive CMake target/tests and TSan target list.
- Evidence file.

## OUT OF SCOPE

`units.hpp`, `precision.hpp`, `ids.hpp`, unit/persistent-ID types, world origin, backend clip/projection/winding, SIMD, third-party math, serialization, public ABI/release, CORE-01 completion, CORE-05-06 or later.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0007/0086/0108, `core-05-math-v0`, CORE-05 architecture, CORE-05-04 evidence, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0108; ADR-0086; MATH-06; column-vector composition `parent * child`; no implicit space conversion.

## ARCHITECTURE RULES

CORE-05 owns coordinate-space wrappers; GFX owns backend clip/projection and winding; SIM/PHYS/WORLD/NET/DATA boundaries unchanged. Header-only internal C++20; scalar reference path only; no third-party include or intrinsic.

## CONSTRAINTS

Risk `ELEVATED`; release `INTERNAL_ONLY`; no dependency/package/secret/paid service; CORE-01 not module-qualified; CORE-02 NOT_QUALIFIED; CORE-03/04 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## ACCEPTANCE CRITERIA

- Exact allowlist; space tags make cross-space assignment/operations compile-time errors.
- MATH-06: identity, parent `B->C` times child `A->B`, point/direction composition, inverse round-trip, `transform_position`/`transform_direction`.
- No implicit world/view/clip/pixel conversion; no backend projection.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; no dependency/ABI/release change; pt-BR audit `APPROVED`.

## TESTS

MATH-06 plus `static_assert` fixtures for incompatible `Position3`/`Direction3`/`Transform3` types; point `w=1` and direction translation ignore. Existing full CTest suite remains required.

## DELIVERABLES

`coords.hpp`, coordinate tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, MATH-06, sanitizers/CI, errors/corrections, security/rollback, no overclaim. APPROVED/CORRECTION REQUIRED/BLOCKED.

## STOP CONDITION

Stale base, gate not merged, API drift, third-party/intrinsic, units/precision/ID code, backend conversion, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim. Stop and report.

## CONTEXT LOCK

Base `a9e1fce752e8190d875caa5d7fea7415d0a6c8ab`; contract blob `e6fb5f8a4f9934848d71be9d535018b0b99531e2`; CORE-05-04 code PR #542 and closeout #543 merged.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-CORE-05-05-G6-ACTIVATION.md` for the gate; `docs/evidence/NLE-PRPLAN-CORE-05-05.md` for implementation.
