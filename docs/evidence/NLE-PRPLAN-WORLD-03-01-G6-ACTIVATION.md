# NLE-PRPLAN-WORLD-03-01 — G6 governance activation

**Status:** `G6 GOVERNANCE ACTIVATION / DOCUMENTATION ONLY / NO CODE AUTHORIZED BY THIS RECORD`. **Base main:** `720f21b`. **Formal packet:** `NLE-PRPLAN-WORLD-03-01`. **ADR:** [ADR-0129](../adr/0129-world-03-internal-spatial-streaming-metadata.md). **Contract:** [world-03-governance-v0](../contracts/world-03-governance-v0.md). **WO:** [NLE-PRPLAN-WORLD-03-01](../work-orders/NLE-PRPLAN-WORLD-03-01.md).

## Authorization

The owner authorized continuation on 2026-11-24. WORLD-02 and DATA-05 internal sequences are complete but not qualified. This gate approves only the internal logical governance of WORLD-03; it does not approve ADR-0028 for runtime code.

## Capability admission

- Formal dependencies are `WORLD-02` and `DATA-05`; neither is module-qualified.
- Admission uses completed WORLD-02 and DATA-05 internal capabilities.
- `module_completion_claimed=false`.

## Activated scope

- `docs/adr/0129-world-03-internal-spatial-streaming-metadata.md`
- `docs/architecture/world-03-internal-spatial-streaming-metadata.md`
- `docs/contracts/world-03-governance-v0.md`
- `docs/work-orders/NLE-PRPLAN-WORLD-03-01.md`
- activation evidence/JSON, manifest/validator/tests and checkpoint entry

No source header, executable test, CMake target, workflow target, async streaming or I/O is authorized. `WORLD-03-02` must freeze the exact API before `-03`.

## Gate state after merge

- Manifest root `WORLD03_01_APPROVED_GOVERNANCE_ONLY`: **502 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 195 `COMPLETED`, 51 approved gates**.
- `WORLD-03-01` becomes `APPROVED_GOVERNANCE`; `WORLD-03-02`..`-08` remain `PLANNED_BLOCKED`.
