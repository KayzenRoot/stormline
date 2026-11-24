# NLE-PRPLAN-WORLD-02-01 — G6 governance activation

**Status:** `G6 GOVERNANCE ACTIVATION / DOCUMENTATION ONLY / NO CODE AUTHORIZED BY THIS RECORD`. **Base main:** `711cb9e`. **Formal packet:** `NLE-PRPLAN-WORLD-02-01`. **ADR:** [ADR-0128](../adr/0128-world-02-internal-scene-prefab-metadata.md). **Contract:** [world-02-governance-v0](../contracts/world-02-governance-v0.md). **WO:** [NLE-PRPLAN-WORLD-02-01](../work-orders/NLE-PRPLAN-WORLD-02-01.md).

## Authorization

The owner authorized continuation on 2026-11-24. WORLD-01 and DATA-02 internal sequences are complete but not qualified. This gate approves only the internal logical governance of WORLD-02; it does not approve ADR-0027 for runtime code.

## Capability admission

- Formal dependencies are `WORLD-01` and `DATA-02`; neither is module-qualified.
- Admission uses completed WORLD-01 and DATA-02 internal capabilities.
- `module_completion_claimed=false`.

## Activated scope

- `docs/adr/0128-world-02-internal-scene-prefab-metadata.md`
- `docs/architecture/world-02-internal-scene-prefab-metadata.md`
- `docs/contracts/world-02-governance-v0.md`
- `docs/work-orders/NLE-PRPLAN-WORLD-02-01.md`
- activation evidence/JSON, manifest/validator/tests and checkpoint entry

No source header, executable test, CMake target, workflow target, scene graph runtime or prefab expansion is authorized. `WORLD-02-02` must freeze the exact API before `-03`.

## Gate state after merge

- Manifest root `WORLD02_01_APPROVED_GOVERNANCE_ONLY`: **511 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 188 `COMPLETED`, 49 approved gates**.
- `WORLD-02-01` becomes `APPROVED_GOVERNANCE`; `WORLD-02-02`..`-09` remain `PLANNED_BLOCKED`.
