# NLE-PRPLAN-SIM-02-07 — Constraint metadata 3D (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-SIM-02-07`. **Predecessor:** `SIM-02-06` queries. **Issue:** #47. **Base:** `a81e446e`. **ADR:** [ADR-0133](../adr/0133-sim-02-internal-physics-3d-metadata.md). **Contract:** [sim-02-physics3d-internal-v0](../contracts/sim-02-physics3d-internal-v0.md).

## OBJECTIVE

Implement bounded logical 3D constraint metadata with distinct body references, finite anchors/limits, unit axes and kind/motor/collide counts.

## CONTEXT

SIM-02-01..-06 are approved or completed. No constraint solver, joint runtime or simulation exists.

## SCOPE

- `constraint_plan.hpp` and CONSTRAINT3-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Earlier slice changes, later slices, qualification, closeout; constraint solver, joint runtime, contacts, simulation, ECS mutation, GPU, physics runtime.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0133, internal contract, governance contract, `physics3d_types.hpp`.

## REQUIREMENTS

GOV-001..007; ADR-0133; CONSTRAINT3-01.

## ARCHITECTURE RULES

SIM-02 owns logical constraint descriptors only; no solver handle, impulse, runtime joint or backend type is exposed.

## CONSTRAINTS

Risk `LOW`; `INTERNAL_ONLY`; no solver/runtime/contact/simulation/ECS/GPU; CORE-01/02/03 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; CONSTRAINT3-01 valid/invalid fixtures.
- Distinct body refs, finite anchors/limits, unit axes per kind, capacity, reset and determinism.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

CONSTRAINT3-01 world/revision/count validation, unique IDs, kind allowlist, distinct bodies, finite anchors/limits, min<=max, unit axes for Hinge/Slider/ConeTwist, capacity, reset and determinism.

## DELIVERABLES

Header, CONSTRAINT3-01 tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, CONSTRAINT3-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, solver/runtime/backend selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `a81e446e`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-SIM-02-07-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-SIM-02-07.md`.
