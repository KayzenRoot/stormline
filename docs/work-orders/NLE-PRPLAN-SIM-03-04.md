# NLE-PRPLAN-SIM-03-04 — Locomotion metadata (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-SIM-03-04`. **Predecessor:** `SIM-03-03` controllers. **Issue:** #48. **Base:** `0ee9e188`. **ADR:** [ADR-0134](../adr/0134-sim-03-internal-character-motor-metadata.md). **Contract:** [sim-03-character-internal-v0](../contracts/sim-03-character-internal-v0.md).

## OBJECTIVE

Implement bounded logical locomotion metadata with finite speeds, run/walk ordering, positive acceleration/deceleration, jump/dash descriptors and integer tick windows.

## CONTEXT

SIM-03-01..-03 are approved or completed. No movement simulation, motor or contact execution exists.

## SCOPE

- `locomotion_plan.hpp` and LOCO-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Earlier slice changes, later slices, qualification, closeout; movement simulation, motor/sweeper, contacts, solver/backend, input devices, camera update, ECS mutation, GPU, character runtime.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0134, internal contract, governance contract, `character_types.hpp`.

## REQUIREMENTS

GOV-001..007; ADR-0134; LOCO-01.

## ARCHITECTURE RULES

SIM-03 owns logical locomotion descriptors only; no movement, contact gating, backend type or runtime behavior is exposed.

## CONSTRAINTS

Risk `LOW`; `INTERNAL_ONLY`; no simulation/motor/sweeper/input/camera/ECS/GPU/runtime; CORE-01/02/03 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; LOCO-01 valid/invalid fixtures.
- Speed ordering, positive acceleration/deceleration, tick windows, capacity, reset and determinism.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

LOCO-01 owner/revision/count validation, unique IDs, controller refs, finite speeds, run >= walk, accel/decel > 0, buffer/coyote/dash ticks 0..240, capacity, reset and determinism.

## DELIVERABLES

Header, LOCO-01 tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, LOCO-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, simulation/motor/backend selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `0ee9e188`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-SIM-03-04-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-SIM-03-04.md`.
