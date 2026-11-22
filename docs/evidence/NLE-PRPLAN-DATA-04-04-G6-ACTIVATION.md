# NLE-PRPLAN-DATA-04-04 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / CODE AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `a10b825`. **Formal packet:** `NLE-PRPLAN-DATA-04-04`. **ADR:** [ADR-0113](../adr/0113-data-04-governance-slice.md). **Contract:** [data-04-scene-v0](../contracts/data-04-scene-v0.md). **WO:** [NLE-PRPLAN-DATA-04-04](../work-orders/NLE-PRPLAN-DATA-04-04.md).

## Authorization

The owner authorized completion of DATA-01..04 on 2026-11-22. DATA-04-01..03 are approved/completed. This gate activates only the declarative document after Docs Validation and pt-BR audit.

## Capability admission

- Formal dependencies are `CORE-05` and `DATA-02`; neither is module-qualified.
- Admission uses completed CORE-05 and DATA-02 capabilities.
- `module_completion_claimed=false`.

## Activated scope

- `src/stormline/data/scene/scene_document.hpp`
- `tests/core/data04_document_tests.cpp`
- Additive CMake/workflow entries
- `docs/evidence/NLE-PRPLAN-DATA-04-04.md`

DOC-01 is required. No codec, persistence or native I/O is permitted.

## Gate state after merge

- Manifest root `DATA04_04_READY_L1_CAPABILITY_OVERLAY`: **648 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 79 `COMPLETED`, 20 approved gates**.
- `DATA-04-04` becomes `EXECUTOR_READY`; `DATA-04-05`..`-08` remain `PLANNED_BLOCKED`.
