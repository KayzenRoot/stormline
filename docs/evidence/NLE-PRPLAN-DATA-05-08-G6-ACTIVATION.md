# NLE-PRPLAN-DATA-05-08 — G6 qualification activation

**Status:** `G6 QUALIFICATION ACTIVATION / CODE AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `eee95bc`. **Formal packet:** `NLE-PRPLAN-DATA-05-08`. **ADR:** [ADR-0114](../adr/0114-data-05-governance-slice.md). **Contract:** [data-05-bundle-v0](../contracts/data-05-bundle-v0.md). **WO:** [NLE-PRPLAN-DATA-05-08](../work-orders/NLE-PRPLAN-DATA-05-08.md).

## Authorization

The owner authorized continuation on 2026-11-22. DATA-05-01..07 are approved/completed. This gate activates only QLF-B qualification after Docs Validation and pt-BR audit.

## Capability admission

- Formal dependencies are `DATA-03` and `DATA-04`; neither is module-qualified.
- Admission uses completed DATA-03 and DATA-04 capabilities.
- `module_completion_claimed=false`.

## Activated scope

- `tests/core/data05_bundle_qualification_tests.cpp`
- Additive CMake/workflow entries
- `docs/evidence/NLE-PRPLAN-DATA-05-08.md`

QLF-B01..04 are required. No production file is authorized.

## Gate state after merge

- Manifest root `DATA05_08_READY_L1_CAPABILITY_OVERLAY`: **636 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 89 `COMPLETED`, 22 approved gates**.
- `DATA-05-08` becomes `EXECUTOR_READY`; `DATA-05-09` remains `PLANNED_BLOCKED`.
