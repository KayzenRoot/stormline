# NLE-PRPLAN-SIM-02-06 — Query intent metadata 3D (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-SIM-02-06`. **Predecessor:** `SIM-02-05` layers. **Issue:** #47. **Base:** `cbe9f7b7`. **ADR:** [ADR-0133](../adr/0133-sim-02-internal-physics-3d-metadata.md). **Contract:** [sim-02-physics3d-internal-v0](../contracts/sim-02-physics3d-internal-v0.md).

## OBJECTIVE

Implement bounded logical 3D query-intent metadata with ray/overlap/sweep/shape-cast descriptors, finite regions and bounded result limits.

## CONTEXT

SIM-02-01..-05 are approved or completed. No query execution, broadphase or result generation exists.

## SCOPE

- `query_plan.hpp` and QUERY3-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Earlier slice changes, later slices, qualification, closeout; query execution, result sets, broadphase, contacts, solver/backend, simulation, ECS mutation, GPU, physics runtime.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0133, internal contract, governance contract, `physics3d_types.hpp`.

## REQUIREMENTS

GOV-001..007; ADR-0133; QUERY3-01.

## ARCHITECTURE RULES

SIM-02 owns logical query descriptors only; no execution, hit result, candidate list or backend type is exposed.

## CONSTRAINTS

Risk `LOW`; `INTERNAL_ONLY`; no query execution/broadphase/contact/solver/GPU/runtime; CORE-01/02/03 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; QUERY3-01 valid/invalid fixtures.
- Direction/max-distance per-kind rules, result caps, capacity, reset and determinism.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

QUERY3-01 world/revision/count validation, unique query IDs, kind allowlist, finite regions, direction/nonzero rules, per-query and total result caps, capacity, reset and determinism.

## DELIVERABLES

Header, QUERY3-01 tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, QUERY3-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, query execution/backend selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `cbe9f7b7`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-SIM-02-06-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-SIM-02-06.md`.
