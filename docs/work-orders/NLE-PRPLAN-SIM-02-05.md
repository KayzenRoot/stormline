# NLE-PRPLAN-SIM-02-05 — Broadphase layer metadata 3D (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-SIM-02-05`. **Predecessor:** `SIM-02-04` shapes. **Issue:** #47. **Base:** `98d8a727`. **ADR:** [ADR-0133](../adr/0133-sim-02-internal-physics-3d-metadata.md). **Contract:** [sim-02-physics3d-internal-v0](../contracts/sim-02-physics3d-internal-v0.md).

## OBJECTIVE

Implement bounded logical broadphase-layer metadata with unique layer IDs, bit ranges, group rules and symmetric compatibility checks.

## CONTEXT

SIM-02-01..-04 are approved or completed. No AABB tree, sweep or candidate generation exists.

## SCOPE

- `layer_plan.hpp` and BROAD3-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Earlier slice changes, later slices, qualification, closeout; AABB tree, sweep, narrowphase, contacts, solver/backend, simulation, ECS mutation, GPU, physics runtime.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0133, internal contract, governance contract, `physics3d_types.hpp`.

## REQUIREMENTS

GOV-001..007; ADR-0133; BROAD3-01.

## ARCHITECTURE RULES

SIM-02 owns logical layer descriptors only; no broadphase execution, candidate list or backend type is exposed.

## CONSTRAINTS

Risk `LOW`; `INTERNAL_ONLY`; no broadphase execution/narrowphase/contact/solver/GPU/runtime; CORE-01/02/03 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; BROAD3-01 valid/invalid fixtures.
- Group override and symmetric compatibility checks, capacity, reset and determinism.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

BROAD3-01 world/revision/count validation, unique layer IDs, bit validity, group counting, symmetric compatibility including group override, capacity, reset and determinism.

## DELIVERABLES

Header, BROAD3-01 tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, BROAD3-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, broadphase execution/backend selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `98d8a727`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-SIM-02-05-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-SIM-02-05.md`.
