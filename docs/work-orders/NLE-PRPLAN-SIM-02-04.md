# NLE-PRPLAN-SIM-02-04 — Collision shape metadata 3D (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-SIM-02-04`. **Predecessor:** `SIM-02-03` bodies. **Issue:** #47. **Base:** `144b5a18`. **ADR:** [ADR-0133](../adr/0133-sim-02-internal-physics-3d-metadata.md). **Contract:** [sim-02-physics3d-internal-v0](../contracts/sim-02-physics3d-internal-v0.md).

## OBJECTIVE

Implement bounded logical 3D collision-shape metadata with kind allowlist, dimension rules, density/material validation and sensor counts.

## CONTEXT

SIM-02-01..-03 are approved or completed. No narrowphase, mesh import or collision pipeline exists.

## SCOPE

- `shape_plan.hpp` and SHAPE3-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Earlier slice changes, later slices, qualification, closeout; narrowphase, mesh/heightfield import, contacts, solver/backend, simulation, ECS mutation, GPU, physics runtime.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0133, internal contract, governance contract, `physics3d_types.hpp`.

## REQUIREMENTS

GOV-001..007; ADR-0133; SHAPE3-01.

## ARCHITECTURE RULES

SIM-02 owns logical shape descriptors only; no narrowphase, mesh cooking or backend type is exposed.

## CONSTRAINTS

Risk `LOW`; `INTERNAL_ONLY`; no narrowphase/import/contact/solver/broadphase/GPU/runtime; CORE-01/02/03 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; SHAPE3-01 valid/invalid fixtures.
- Dimension rules per kind, density/material checks, reset behavior.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

SHAPE3-01 world/revision/count validation, unique IDs, kind allowlist, per-kind dimension rules, density/material checks, capacity, reset and determinism.

## DELIVERABLES

Header, SHAPE3-01 tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, SHAPE3-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, importer/narrowphase/backend selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `144b5a18`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-SIM-02-04-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-SIM-02-04.md`.
