# NLE-PRPLAN-WORLD-01-08 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / TEST AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `d124444`. **Formal packet:** `NLE-PRPLAN-WORLD-01-08`. **ADR:** [ADR-0127](../adr/0127-world-01-internal-entity-metadata.md). **Contract:** [world-01-entity-internal-v0](../contracts/world-01-entity-internal-v0.md). **WO:** [NLE-PRPLAN-WORLD-01-08](../work-orders/NLE-PRPLAN-WORLD-01-08.md).

## Authorization

The owner authorized continuation on 2026-11-24. WORLD-01-01..-07 are approved. This gate activates only integrated internal qualification fixtures.

## Capability admission

- Formal dependencies are `CORE-05` and `DATA-04`; neither is module-qualified.
- `module_completion_claimed=false`.

## Activated scope

- `tests/core/world01_qualification_tests.cpp`
- additive CMake/workflow and `docs/evidence/NLE-PRPLAN-WORLD-01-08.md`

QLF-W101..W104 are required. Qualification is internal CI only; no runtime ECS, storage, threading, serialization, hardware or performance qualification is claimed.

## Gate state after merge

- Manifest root `WORLD01_08_READY_L1_CAPABILITY_OVERLAY`: **513 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 186 `COMPLETED`, 48 approved gates**.
- `WORLD-01-08` becomes `EXECUTOR_READY`; `WORLD-01-09` remains `PLANNED_BLOCKED`.
