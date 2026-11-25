# NLE-PRPLAN-SIM-03-05 — Input response metadata (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-SIM-03-05`. **Predecessor:** `SIM-03-04` locomotion. **Issue:** #48. **Base:** `ac9bb206`. **ADR:** [ADR-0134](../adr/0134-sim-03-internal-character-motor-metadata.md). **Contract:** [sim-03-character-internal-v0](../contracts/sim-03-character-internal-v0.md).

## OBJECTIVE

Implement bounded logical input-response metadata with unique actions, axis indexes, dead zones, scales and integer buffer windows.

## CONTEXT

SIM-03-01..-04 are approved or completed. No device polling, event dispatch or movement runtime exists.

## SCOPE

- `input_plan.hpp` and INPUT-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Earlier slice changes, later slices, qualification, closeout; device polling, event dispatch, motor/sweeper, contacts, solver/backend, camera update, ECS mutation, GPU, character runtime.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0134, internal contract, governance contract, `character_types.hpp`.

## REQUIREMENTS

GOV-001..007; ADR-0134; INPUT-01.

## ARCHITECTURE RULES

SIM-03 owns logical input descriptors only; no device polling, event queue, backend type or runtime behavior is exposed.

## CONSTRAINTS

Risk `LOW`; `INTERNAL_ONLY`; no input device/event/motor/camera/ECS/GPU/runtime; CORE-01/02/03 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; INPUT-01 valid/invalid fixtures.
- Axis/dead-zone/scale validity, buffer windows, capacity, reset and determinism.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

INPUT-01 owner/revision/count validation, unique actions, axis 0..7, dead zone 0..1, nonzero finite scale, buffer ticks 0..240, capacity, reset and determinism.

## DELIVERABLES

Header, INPUT-01 tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, INPUT-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, device polling/event/backend selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `ac9bb206`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-SIM-03-05-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-SIM-03-05.md`.
