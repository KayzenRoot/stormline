# NLE-PRPLAN-SIM-01-08 — Collision mask metadata (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-SIM-01-08`. **Predecessor:** `SIM-01-07` triggers. **Issue:** #46. **Base:** `6b9c892`. **ADR:** [ADR-0132](../adr/0132-sim-01-internal-physics-2d-metadata.md). **Contract:** [sim-01-physics2d-internal-v0](../contracts/sim-01-physics2d-internal-v0.md).

## OBJECTIVE

Implement bounded logical collision-mask metadata with unique IDs, category/collision bits, group rules and symmetric compatibility checks.

## CONTEXT

SIM-01-01..-07 are approved or completed. No broadphase filter, contact generation or collision pipeline exists.

## SCOPE

- `mask_plan.hpp` and MSK-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Prior slice changes, qualification, closeout; contact generation, broadphase, solver/backend, simulation, ECS mutation, GPU, physics runtime.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0132, internal contract, governance contract, prior physics headers.

## REQUIREMENTS

GOV-001..007; ADR-0132; MSK-01.

## ARCHITECTURE RULES

SIM-01 owns logical mask descriptors only; no collision pair is generated and rendering layers are not coupled.

## CONSTRAINTS

Risk `LOW`; `INTERNAL_ONLY`; no broadphase/contact/solver/backend/GPU/physics runtime/editor; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; MSK-01 valid/invalid fixtures.
- No contact generation, broadphase or simulation.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

MSK-01 world/revision/count validation, unique mask IDs, nonzero revisions/bits, group counting, symmetric compatibility including group override, capacity, reset and determinism.

## DELIVERABLES

Header, MSK-01 tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, MSK-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, contact/broadphase/backend selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `6b9c892`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-SIM-01-08-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-SIM-01-08.md`.
