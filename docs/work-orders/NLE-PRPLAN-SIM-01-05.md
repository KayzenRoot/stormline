# NLE-PRPLAN-SIM-01-05 — Query intent metadata (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-SIM-01-05`. **Predecessor:** `SIM-01-04` collision shapes. **Issue:** #46. **Base:** `f03edb0`. **ADR:** [ADR-0132](../adr/0132-sim-01-internal-physics-2d-metadata.md). **Contract:** [sim-01-physics2d-internal-v0](../contracts/sim-01-physics2d-internal-v0.md).

## OBJECTIVE

Implement bounded logical query-intent metadata with stable IDs, allowlisted query kinds, finite regions, masks and result limits.

## CONTEXT

SIM-01-01..-04 are approved or completed. No broadphase, raycast, overlap query, shape cast or result set exists.

## SCOPE

- `query_plan.hpp` and QRY-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Bodies/shapes changes, joints, triggers, masks, qualification, closeout; query execution, broadphase, contacts, simulation, ECS mutation, GPU, physics runtime.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0132, internal contract, governance contract, prior physics headers.

## REQUIREMENTS

GOV-001..007; ADR-0132; QRY-01.

## ARCHITECTURE RULES

SIM-01 owns logical query descriptors only; no query is executed and no result set is produced.

## CONSTRAINTS

Risk `LOW`; `INTERNAL_ONLY`; no solver/backend/query execution/broadphase/GPU/physics runtime/editor; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; QRY-01 valid/invalid fixtures.
- No query execution, result set, broadphase or simulation.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

QRY-01 world/revision/count validation, unique query IDs, nonzero revisions, kind allowlist, finite origins/directions, mask nonzero, max-results bounds, distance rules, checked total limit, capacity, reset and determinism.

## DELIVERABLES

Header, QRY-01 tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, QRY-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, query execution/backend selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `f03edb0`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-SIM-01-05-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-SIM-01-05.md`.
