# NLE-PRPLAN-TWO-04-01 — G6 governance activation

**Status:** `G6 GOVERNANCE ACTIVATION / DOCUMENTATION ONLY / NO CODE AUTHORIZED BY THIS RECORD`. **Base main:** `60187a1`. **Formal packet:** `NLE-PRPLAN-TWO-04-01`. **ADR:** [ADR-0126](../adr/0126-two-04-internal-hybrid-composition.md). **Contract:** [two-04-governance-v0](../contracts/two-04-governance-v0.md). **WO:** [NLE-PRPLAN-TWO-04-01](../work-orders/NLE-PRPLAN-TWO-04-01.md).

## Authorization

The owner authorized continuation on 2026-11-24. TWO-01 and GFX-04 internal sequences are complete but not qualified. This gate approves only the internal logical governance of TWO-04; it does not approve ADR-0025 for runtime code.

## Capability admission

- Formal dependencies are `TWO-01` and `GFX-04`; neither is module-qualified.
- Admission uses completed TWO-01 and GFX-04 internal capabilities.
- `module_completion_claimed=false`.

## Activated scope

- `docs/adr/0126-two-04-internal-hybrid-composition.md`
- `docs/architecture/two-04-internal-hybrid-composition.md`
- `docs/contracts/two-04-governance-v0.md`
- `docs/work-orders/NLE-PRPLAN-TWO-04-01.md`
- activation evidence/JSON, manifest/validator/tests and checkpoint entry

No source header, executable test, CMake target, workflow target or renderer behavior is authorized. `TWO-04-02` must freeze the exact API before `-03`.

## Gate state after merge

- Manifest root `TWO04_01_APPROVED_GOVERNANCE_ONLY`: **528 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 175 `COMPLETED`, 45 approved gates**.
- `TWO-04-01` becomes `APPROVED_GOVERNANCE`; `TWO-04-02`..`-08` remain `PLANNED_BLOCKED`.
