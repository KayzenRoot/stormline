# NLE-PRPLAN-SIM-02-08 — Integration metadata 3D (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-SIM-02-08`. **Predecessor:** `SIM-02-07` constraints. **Issue:** #47. **Base:** `821e3d9c`. **ADR:** [ADR-0133](../adr/0133-sim-02-internal-physics-3d-metadata.md). **Contract:** [sim-02-physics3d-internal-v0](../contracts/sim-02-physics3d-internal-v0.md).

## OBJECTIVE

Implement bounded logical 3D integration metadata with scene/streaming/authority/tick references, per-kind requirements and tick bounds.

## CONTEXT

SIM-02-01..-07 are approved or completed. No ECS mutation, scene bridge, streaming execution or fixed-tick runtime exists.

## SCOPE

- `integration_plan.hpp` and INTEGRATION3-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Earlier slice changes, later slices, qualification, closeout; ECS mutation, scene/physics bridge, streaming execution, tick runtime, solver/backend, GPU, physics runtime.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0133, internal contract, governance contract, `physics3d_types.hpp`.

## REQUIREMENTS

GOV-001..007; ADR-0133; INTEGRATION3-01.

## ARCHITECTURE RULES

SIM-02 owns logical integration descriptors only; no bridge execution, ECS write, tick loop or backend type is exposed.

## CONSTRAINTS

Risk `LOW`; `INTERNAL_ONLY`; no ECS/bridge/streaming/runtime/solver/GPU; CORE-01/02/03 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; INTEGRATION3-01 valid/invalid fixtures.
- Per-kind reference rules, tick bounds 1..240, capacity, reset and determinism.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

INTEGRATION3-01 world/revision/count validation, unique IDs, kind allowlist, world equality, scene/cell/authority/tick requirements, tick min/max, capacity, reset and determinism.

## DELIVERABLES

Header, INTEGRATION3-01 tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, INTEGRATION3-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, ECS/bridge/runtime/backend selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `821e3d9c`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-SIM-02-08-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-SIM-02-08.md`.
