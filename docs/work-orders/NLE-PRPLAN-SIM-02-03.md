# NLE-PRPLAN-SIM-02-03 — Rigid body metadata 3D (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-SIM-02-03`. **Predecessor:** `SIM-02-02` contract. **Issue:** #47. **Base:** `9968eb68`. **ADR:** [ADR-0133](../adr/0133-sim-02-internal-physics-3d-metadata.md). **Contract:** [sim-02-physics3d-internal-v0](../contracts/sim-02-physics3d-internal-v0.md).

## OBJECTIVE

Implement bounded logical 3D rigid-body metadata with unique IDs, kind allowlist, finite pose/quaternion, density/damping bounds and enabled counts.

## CONTEXT

SIM-02-01 and -02 are approved. No solver, broadphase or simulation exists.

## SCOPE

- `physics3d_types.hpp`, `body_plan.hpp` and BODY3-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Prior slice changes, later slices, qualification, closeout; solver/backend, broadphase, queries, contacts, simulation, ECS mutation, GPU, physics runtime.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0133, internal contract, governance contract.

## REQUIREMENTS

GOV-001..007; ADR-0133; BODY3-01.

## ARCHITECTURE RULES

SIM-02 owns logical body metadata only; no integration, solver handle or backend type is exposed.

## CONSTRAINTS

Risk `LOW`; `INTERNAL_ONLY`; no solver/broadphase/query/contact/simulation/ECS/GPU/runtime; CORE-01/02/03 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; BODY3-01 valid/invalid fixtures.
- Unit-quaternion rule, density/damping bounds and reset behavior.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

BODY3-01 world/revision/count validation, unique IDs, kind allowlist, finite pose/quaternion, density/damping bounds, capacity, reset and determinism.

## DELIVERABLES

Headers, BODY3-01 tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, BODY3-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, solver/broadphase/backend selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `9968eb68`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-SIM-02-03-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-SIM-02-03.md`.
