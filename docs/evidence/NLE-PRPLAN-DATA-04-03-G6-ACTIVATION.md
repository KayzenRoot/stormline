# NLE-PRPLAN-DATA-04-03 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / CODE AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `d2b5dc3`. **Formal packet:** `NLE-PRPLAN-DATA-04-03`. **ADR:** [ADR-0113](../adr/0113-data-04-governance-slice.md). **Contract:** [data-04-scene-v0](../contracts/data-04-scene-v0.md). **WO:** [NLE-PRPLAN-DATA-04-03](../work-orders/NLE-PRPLAN-DATA-04-03.md).

## Authorization

The owner authorized completion of DATA-01..04 on 2026-11-22. DATA-04-01..02 are approved. This gate activates only schema validation after Docs Validation and pt-BR audit.

## Capability admission

- Formal dependencies are `CORE-05` and `DATA-02`; neither is module-qualified.
- Admission uses completed CORE-05 typed math/IDs and DATA-02 capabilities.
- `module_completion_claimed=false`.

## Activated scope

- `src/stormline/data/scene/scene_types.hpp`
- `src/stormline/data/scene/scene_schema.hpp`
- `tests/core/data04_schema_tests.cpp`
- Additive CMake/workflow entries
- `docs/evidence/NLE-PRPLAN-DATA-04-03.md`

SCH-01 is required. No codec, persistence or native I/O is permitted.

## Gate state after merge

- Manifest root `DATA04_03_READY_L1_CAPABILITY_OVERLAY`: **649 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 78 `COMPLETED`, 20 approved gates**.
- `DATA-04-03` becomes `EXECUTOR_READY`; `DATA-04-04`..`-08` remain `PLANNED_BLOCKED`.
