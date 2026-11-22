# NLE-PRPLAN-GFX-01-01 — G6 governance activation

**Status:** `G6 GOVERNANCE PROPOSAL / NO CODE AUTHORIZED / CORE-01 + CORE-02 CAPABILITY ADMISSION`. **Base main:** `c87e9f7`. **Formal packet:** `NLE-PRPLAN-GFX-01-01`. **ADR:** [ADR-0115](../adr/0115-gfx-01-governance-slice.md). **Contract:** [gfx-01-governance-v0](../contracts/gfx-01-governance-v0.md). **WO:** [NLE-PRPLAN-GFX-01-01](../work-orders/NLE-PRPLAN-GFX-01-01.md).

## Authorization

The owner authorized continuation on 2026-11-22. No native graphics backend was selected. This gate prepares only GFX-01 governance after Docs Validation and pt-BR audit; it does not authorize GPU code, rendering, shader, swapchain, dependency, release or ABI.

## Capability admission

- Formal dependencies are `CORE-01` and `CORE-02`; neither is module-qualified.
- Admission uses completed CORE-01 headless/CI/path/lifecycle and CORE-02 memory capabilities.
- `module_completion_claimed=false`.
- No GPU/driver/shader/swapchain/network/release capability is used.

## Governance scope

- ADR-0115 and ADR-0014 as planning direction only.
- Backend-neutral logical RHI and Null/reference backend.
- Device generations, queues, resources, barriers and feature tiers; no native GPU.
- Risk `LOW` docs / `ELEVATED` implementation; release `INTERNAL_ONLY`.

## Gate state after merge

- Manifest root `GFX01_01_APPROVED_GOVERNANCE_ONLY`: **634 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 91 `COMPLETED`, 23 approved gates**.
- `GFX-01-01` becomes `APPROVED_GOVERNANCE`; `GFX-01-02`..`-10` remain `PLANNED_BLOCKED`.
- Selector denies every ID; registry byte-identical; 80/80 module WOs `BLOCKED`.
