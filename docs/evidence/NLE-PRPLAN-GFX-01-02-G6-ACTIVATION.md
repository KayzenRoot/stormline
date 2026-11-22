# NLE-PRPLAN-GFX-01-02 — G6 contract activation

**Status:** `G6 CONTRACT PROPOSAL / NO CODE AUTHORIZED / CORE-01 + CORE-02 CAPABILITY ADMISSION`. **Base main:** `0282408`. **Formal packet:** `NLE-PRPLAN-GFX-01-02`. **ADR:** [ADR-0115](../adr/0115-gfx-01-governance-slice.md). **Contract:** [gfx-01-rhi-v0](../contracts/gfx-01-rhi-v0.md). **WO:** [NLE-PRPLAN-GFX-01-02](../work-orders/NLE-PRPLAN-GFX-01-02.md).

## Authorization

The owner authorized continuation on 2026-11-22. GFX-01-01 governance is approved. This gate freezes only the backend-neutral RHI contract after Docs Validation and pt-BR audit; it does not authorize native GPU, rendering, shader, swapchain, dependency, release or ABI.

## Capability admission

- Formal dependencies are `CORE-01` and `CORE-02`; neither is module-qualified.
- Admission uses completed CORE-01 and CORE-02 capabilities.
- `module_completion_claimed=false`.
- No native GPU, driver, shader, swapchain, network or release capability is used.

## Contract scope

- One Null adapter and backend-neutral device lifecycle/generation.
- Queue roles/submit accounting, buffer/texture descriptors and handles, barrier validation and feature tiers.
- Fixed capacities and typed errors.
- Exact allowlists and DEV/QUE/BUF/TEX/SYN/TIER/QLF oracles.
- No Vulkan/D3D12/Metal/SDL GPU/Dawn/wgpu/bgfx or rendering.

## Gate state after merge

- Manifest root `GFX01_02_APPROVED_CONTRACT_ONLY`: **633 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 91 `COMPLETED`, 24 approved gates**.
- `GFX-01-02` becomes `APPROVED_CONTRACT`; `GFX-01-03`..`-10` remain `PLANNED_BLOCKED`.
