# NLE-PRPLAN-SIM-01-06 — Joint metadata (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-SIM-01-06`. **Predecessor:** `SIM-01-05` queries. **Issue:** #46. **Base:** `e7c602e`. **ADR:** [ADR-0132](../adr/0132-sim-01-internal-physics-2d-metadata.md). **Contract:** [sim-01-physics2d-internal-v0](../contracts/sim-01-physics2d-internal-v0.md).

## OBJECTIVE

Implement bounded logical joint metadata with unique IDs, distinct body references, allowlisted joint kinds, finite anchors and ordered limits.

## CONTEXT

SIM-01-01..-05 are approved or completed. No constraint solver, joint runtime or backend exists.

## SCOPE

- `joint_plan.hpp` and JNT-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Prior slice changes, triggers, masks, qualification, closeout; constraint solving, simulation, solver/backend, ECS mutation, GPU, physics runtime.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0132, internal contract, governance contract, prior physics headers.

## REQUIREMENTS

GOV-001..007; ADR-0132; JNT-01.

## ARCHITECTURE RULES

SIM-01 owns logical joint descriptors only; no constraint is solved and no runtime joint exists.

## CONSTRAINTS

Risk `LOW`; `INTERNAL_ONLY`; no solver/backend/constraint runtime/GPU/physics runtime/editor; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; JNT-01 valid/invalid fixtures.
- No constraint solver, simulation or backend.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

JNT-01 world/revision/count validation, unique joint IDs, distinct body refs, kind allowlist, finite anchors/limits, ordered limits, kind/collide counts, capacity, reset and determinism.

## DELIVERABLES

Header, JNT-01 tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, JNT-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, solver/backend selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `e7c602e`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-SIM-01-06-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-SIM-01-06.md`.
