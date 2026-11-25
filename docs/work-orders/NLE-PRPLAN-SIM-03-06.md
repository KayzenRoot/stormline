# NLE-PRPLAN-SIM-03-06 — Decoupled camera metadata (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-SIM-03-06`. **Predecessor:** `SIM-03-05` input. **Issue:** #48. **Base:** `9a1bf649`. **ADR:** [ADR-0134](../adr/0134-sim-03-internal-character-motor-metadata.md). **Contract:** [sim-03-character-internal-v0](../contracts/sim-03-character-internal-v0.md).

## OBJECTIVE

Implement bounded logical decoupled-camera metadata with finite offsets/damping, pitch range and enforced independence from animation.

## CONTEXT

SIM-03-01..-05 are approved or completed. No camera transform, device polling or movement runtime exists.

## SCOPE

- `camera_plan.hpp` and CAM-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Earlier slice changes, later slices, qualification, closeout; camera update/transform, device polling, motor/sweeper, contacts, solver/backend, ECS mutation, GPU, character runtime.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0134, internal contract, governance contract, `character_types.hpp`.

## REQUIREMENTS

GOV-001..007; ADR-0134; CAM-01.

## ARCHITECTURE RULES

SIM-03 owns logical camera intent only; no transform, matrix, camera update or backend type is exposed.

## CONSTRAINTS

Risk `LOW`; `INTERNAL_ONLY`; no camera/input/motor/ECS/GPU/runtime; CORE-01/02/03 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; CAM-01 valid/invalid fixtures.
- Finite offsets/damping, pitch range, animation independence, capacity, reset and determinism.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

CAM-01 owner/revision/count validation, unique IDs, controller refs, finite distances/angles/damping, pitch -89..89, damping 0..1, enforced independence, capacity, reset and determinism.

## DELIVERABLES

Header, CAM-01 tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, CAM-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, camera update/animation coupling/backend selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `9a1bf649`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-SIM-03-06-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-SIM-03-06.md`.
