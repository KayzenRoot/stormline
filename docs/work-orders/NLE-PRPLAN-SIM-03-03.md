# NLE-PRPLAN-SIM-03-03 — Controller profile metadata 2D/3D (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-SIM-03-03`. **Predecessor:** `SIM-03-02` contract. **Issue:** #48. **Base:** `21846d2c`. **ADR:** [ADR-0134](../adr/0134-sim-03-internal-character-motor-metadata.md). **Contract:** [sim-03-character-internal-v0](../contracts/sim-03-character-internal-v0.md).

## OBJECTIVE

Implement bounded logical controller profile metadata with dimension/mode allowlists, finite extents, unit up axis, slope/step bounds and enabled counts.

## CONTEXT

SIM-03-01 and -02 are approved. No motor, sweeper or character runtime exists.

## SCOPE

- `character_types.hpp`, `controller_plan.hpp` and CTRL-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Prior slice changes, later slices, qualification, closeout; motor/sweeper, contact execution, solver/backend, input devices, camera update, ECS mutation, GPU, character runtime.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0134, internal contract, governance contract, ADR-0033 research architecture.

## REQUIREMENTS

GOV-001..007; ADR-0134; CTRL-01.

## ARCHITECTURE RULES

SIM-03 owns logical controller metadata only; no motor handle, backend type or runtime behavior is exposed.

## CONSTRAINTS

Risk `LOW`; `INTERNAL_ONLY`; no motor/sweeper/contact/input/camera/ECS/GPU/runtime; CORE-01/02/03 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; CTRL-01 valid/invalid fixtures.
- 2D/3D extent rules, unit up axis, slope/step bounds, capacity, reset and determinism.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

CTRL-01 owner/revision/count validation, unique IDs, dimension/mode allowlists, 2D/3D extents, unit up axis, slope/step bounds, capacity, reset and determinism.

## DELIVERABLES

Headers, CTRL-01 tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, CTRL-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, motor/sweeper/backend selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `21846d2c`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-SIM-03-03-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-SIM-03-03.md`.
