# NLE-PRPLAN-DATA-05-06 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / CODE AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `95466bf`. **Formal packet:** `NLE-PRPLAN-DATA-05-06`. **ADR:** [ADR-0114](../adr/0114-data-05-governance-slice.md). **Contract:** [data-05-bundle-v0](../contracts/data-05-bundle-v0.md). **WO:** [NLE-PRPLAN-DATA-05-06](../work-orders/NLE-PRPLAN-DATA-05-06.md).

## Authorization

The owner authorized continuation on 2026-11-22. DATA-05-01..05 are approved/completed. This gate activates only manifest fingerprint verification after Docs Validation and pt-BR audit.

## Capability admission

- Formal dependencies are `DATA-03` and `DATA-04`; neither is module-qualified.
- Admission uses completed DATA-03 and DATA-04 capabilities.
- `module_completion_claimed=false`.

## Activated scope

- `src/stormline/data/bundle/bundle_manifest.hpp`
- `tests/core/data05_manifest_tests.cpp`
- Additive CMake/workflow entries
- `docs/evidence/NLE-PRPLAN-DATA-05-06.md`

MAN-01 is required. FNV-1a 64 is non-cryptographic; no signing claim.

## Gate state after merge

- Manifest root `DATA05_06_READY_L1_CAPABILITY_OVERLAY`: **638 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 87 `COMPLETED`, 22 approved gates**.
- `DATA-05-06` becomes `EXECUTOR_READY`; `DATA-05-07`..`-09` remain `PLANNED_BLOCKED`.
