# NLE-PRPLAN-CORE-05-07 — World precision and origin epoch (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Gate:** G6 implementation + CORE-01 capability admission. **Formal packet:** `NLE-PRPLAN-CORE-05-07`. **Predecessor:** `CORE-05-06` completed. **Issue:** #22. **Base:** `cdda5ab9c4082e3ead5c42317c8b1277416dc0be`. **ADR:** [ADR-0108](../adr/0108-core-05-governance-slice.md). **Contract:** [core-05-math-v0](../contracts/core-05-math-v0.md).

## OBJECTIVE

Implement `f64` global `WorldPosition`, `f32` relative `LocalPosition`, `OriginEpoch`, `Origin`, `to_local`, `to_world`, `rebase` and `local_error_bound` with typed epoch/overflow failures. No stable IDs, backend conversion, SIMD, third-party math, serialization, ABI or release is authorized.

## CONTEXT

CORE-05-01..06 are approved/completed. ADR-0108 admits only completed CORE-01 capabilities; CORE-01 is not module-qualified. The owner instructed continuation on 2026-11-22. This packet activates only `CORE-05-07`.

## SCOPE

- `precision.hpp`: `OriginEpoch`, `WorldPosition`, `LocalPosition`, `Origin`, conversions, rebase and error bound.
- `tests/core/core05_precision_tests.cpp`: MATH-08/MATH-09, epoch/overflow/non-finite fixtures.
- Additive CMake target/tests and TSan target list.
- Evidence file.

## OUT OF SCOPE

`ids.hpp`, stable IDs, world streaming, backend clip/projection, SIMD, third-party math, serialization, public ABI/release, CORE-01 completion, CORE-05-08 or later.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0007/0086/0108, `core-05-math-v0`, CORE-05 architecture, CORE-05-06 evidence, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0108; ADR-0086; MATH-08/MATH-09; no gameplay teleport or bit-exact claim.

## ARCHITECTURE RULES

CORE-05 supplies pure checked precision/origin conversion; WORLD owns origin-shift orchestration at a CORE-04/CORE-03 barrier; SIM/GFX/NET/DATA boundaries unchanged. Header-only internal C++20; scalar reference path only.

## CONSTRAINTS

Risk `ELEVATED`; release `INTERNAL_ONLY`; no dependency/package/secret/paid service; CORE-01 not module-qualified; CORE-02 NOT_QUALIFIED; CORE-03/04 not qualified; G3 NOT_CLEARED; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; global `f64` truth, local `f32` relative payload and epoch checks.
- MATH-08: 10^6/10^9 m fixtures within `local_error_bound`; overflow/non-finite typed.
- MATH-09: rebase preserves global exactly, advances epoch once, rejects stale/backward/duplicate epochs with `InvalidOriginEpoch`.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; no dependency/ABI/release change; pt-BR audit `APPROVED`.

## TESTS

MATH-08/09 plus epoch mismatch, `f32` overflow, f64 overflow, non-finite and exact global preservation. Existing full CTest suite remains required.

## DELIVERABLES

`precision.hpp`, precision tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, MATH-08/09, sanitizers/CI, errors/corrections, security/rollback, no overclaim. APPROVED/CORRECTION REQUIRED/BLOCKED.

## STOP CONDITION

Stale base, gate not merged, API drift, third-party/intrinsic, ID/serialization code, hidden movement, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim. Stop and report.

## CONTEXT LOCK

Base `cdda5ab9c4082e3ead5c42317c8b1277416dc0be`; contract blob `e6fb5f8a4f9934848d71be9d535018b0b99531e2`; CORE-05-06 code PR #548 and closeout #549 merged.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-CORE-05-07-G6-ACTIVATION.md` for the gate; `docs/evidence/NLE-PRPLAN-CORE-05-07.md` for implementation.
