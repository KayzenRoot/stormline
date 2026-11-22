# NLE-PRPLAN-DATA-03-09 — G6 qualification activation

**Status:** `G6 QUALIFICATION ACTIVATION / CODE AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `ae1bab2`. **Formal packet:** `NLE-PRPLAN-DATA-03-09`. **ADR:** [ADR-0112](../adr/0112-data-03-governance-slice.md). **Contract:** [data-03-import-v0](../contracts/data-03-import-v0.md). **WO:** [NLE-PRPLAN-DATA-03-09](../work-orders/NLE-PRPLAN-DATA-03-09.md).

## Authorization

The owner authorized completion of DATA-01..04 on 2026-11-22. DATA-03-01..08 are approved/completed. This gate activates only QLF-I qualification after Docs Validation and pt-BR audit.

## DATA-02 capability admission

- Formal dependency is `DATA-02`, `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`.
- Admission uses completed DATA-02 capabilities.
- `module_completion_claimed=false`.
- No decoder, archive, native filesystem, persistence, network, MCP or release capability is used.

## Activated scope

- `tests/core/data03_import_qualification_tests.cpp`
- Additive CMake/workflow entries
- `docs/evidence/NLE-PRPLAN-DATA-03-09.md`

No production file is authorized. QLF-I01..04 are required.

## Gate state after merge

- Manifest root `DATA03_09_READY_L1_CAPABILITY_OVERLAY`: **653 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 76 `COMPLETED`, 18 approved gates**.
- `DATA-03-09` becomes `EXECUTOR_READY`; `DATA-03-10` remains `PLANNED_BLOCKED`.
