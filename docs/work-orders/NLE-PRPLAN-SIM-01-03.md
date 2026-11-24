# NLE-PRPLAN-SIM-01-03 — Rigid body metadata (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-SIM-01-03`. **Predecessor:** `SIM-01-02` contract. **Issue:** #46. **Base:** `180a52c`. **ADR:** [ADR-0132](../adr/0132-sim-01-internal-physics-2d-metadata.md). **Contract:** [sim-01-physics2d-internal-v0](../contracts/sim-01-physics2d-internal-v0.md).

## OBJECTIVE

Implement bounded logical rigid-body metadata with stable IDs, allowlisted body kinds, finite pose/density/damping and deterministic body plans.

## CONTEXT

SIM-01-01/-02 are approved. No solver, backend, simulation or runtime physics exists.

## SCOPE

- `physics2d_types.hpp`, `body_plan.hpp` and BODY-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Shapes, queries, joints, triggers, masks, qualification, closeout; solver/backend, simulation, broadphase/narrowphase, ECS mutation, GPU, physics runtime.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0132, internal contract, governance contract, SIM-01 architecture.

## REQUIREMENTS

GOV-001..007; ADR-0132; BODY-01.

## ARCHITECTURE RULES

SIM-01 owns logical body descriptors only; WORLD-01 owns entities and no body is simulated.

## CONSTRAINTS

Risk `LOW`; `INTERNAL_ONLY`; no solver/backend/simulation/GPU/assets/physics runtime/editor; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; BODY-01 valid/invalid fixtures.
- No solver, simulation, ECS mutation or backend.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

BODY-01 world/revision/count validation, unique body IDs, nonzero revisions, kind allowlist, finite pose/angle, density/damping ranges, kind counts, enabled count, capacity, reset and determinism.

## DELIVERABLES

Headers, BODY-01 tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, BODY-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, solver/backend selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `180a52c`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-SIM-01-03-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-SIM-01-03.md`.
