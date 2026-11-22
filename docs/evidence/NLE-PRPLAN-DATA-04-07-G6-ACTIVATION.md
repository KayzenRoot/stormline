# NLE-PRPLAN-DATA-04-07 — G6 qualification activation

**Status:** `G6 QUALIFICATION ACTIVATION / CODE AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `5163c81`. **Formal packet:** `NLE-PRPLAN-DATA-04-07`. **ADR:** [ADR-0113](../adr/0113-data-04-governance-slice.md). **Contract:** [data-04-scene-v0](../contracts/data-04-scene-v0.md). **WO:** [NLE-PRPLAN-DATA-04-07](../work-orders/NLE-PRPLAN-DATA-04-07.md).

## Authorization

The owner authorized completion of DATA-01..04 on 2026-11-22. DATA-04-01..06 are approved/completed. This gate activates only QLF-S qualification after Docs Validation and pt-BR audit.

## Capability admission

- Formal dependencies are `CORE-05` and `DATA-02`; neither is module-qualified.
- Admission uses completed CORE-05 and DATA-02 capabilities.
- `module_completion_claimed=false`.

## Activated scope

- `tests/core/data04_scene_qualification_tests.cpp`
- Additive CMake/workflow entries
- `docs/evidence/NLE-PRPLAN-DATA-04-07.md`

QLF-S01..04 are required. No production file is authorized.

## Gate state after merge

- Manifest root `DATA04_07_READY_L1_CAPABILITY_OVERLAY`: **645 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 82 `COMPLETED`, 20 approved gates**.
- `DATA-04-07` becomes `EXECUTOR_READY`; `DATA-04-08` remains `PLANNED_BLOCKED`.
