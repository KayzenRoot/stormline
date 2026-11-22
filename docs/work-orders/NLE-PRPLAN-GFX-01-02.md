# NLE-PRPLAN-GFX-01-02 — Backend-neutral RHI contract (INTERNAL_ONLY)

**STATUS: CONTRACT PACKET — documentary only; implementation remains BLOCKED until GFX-01-03 G6.** **Formal packet:** `NLE-PRPLAN-GFX-01-02`. **Predecessor:** `GFX-01-01` governance. **Issue:** #29. **Base:** `0282408`. **ADR:** [ADR-0115](../adr/0115-gfx-01-governance-slice.md). **Contract:** [gfx-01-rhi-v0](../contracts/gfx-01-rhi-v0.md).

## OBJECTIVE

Freeze the logical backend-neutral RHI: adapters, device generations/lifecycle, queues, buffers, textures, barriers and feature tiers, with Null/reference backend. No native GPU.

## CONTEXT

GFX-01-01 is `APPROVED_GOVERNANCE`. ADR-0014 is planning direction; ADR-0115 forbids native GPU/rendering. CORE-01/CORE-02 are not qualified.

## SCOPE

- Contract `gfx-01-rhi-v0`: exact API, semantics, errors, DEV/QUE/BUF/TEX/SYN/TIER/QLF oracles and allowlists.
- Evidence of contract review and CORE-01/CORE-02 admission boundary.
- No implementation, backend, dependency, CMake target or code test.

## OUT OF SCOPE

RHI code, Vulkan/D3D12/Metal/SDL GPU, shader/pipeline, swapchain, rendering, GPU timing, persistence, network, ABI/release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0014/0086/0115, GFX-01 architecture/research/api, governance contract, DATA-05 closeout, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0115; bounded generations/descriptors/barriers/features, typed errors.

## ARCHITECTURE RULES

GFX-01 owns logical RHI; CORE-01 native OS; CORE-02 memory; CORE-03 jobs; CORE-04 ticks; CORE-05 math/IDs; CORE-06 diagnostics; DATA-05 bundles; GFX-02/03 higher graphics.

## CONSTRAINTS

Risk `LOW` docs/`ELEVATED` implementation; release `INTERNAL_ONLY`; no native GPU/dependency/native I/O/network/ABI/release. CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## ACCEPTANCE CRITERIA

- Exact API/errors/semantics/test matrix/allowlists.
- No native GPU, shader, swapchain, rendering, dependency or network.
- `GFX-01-02` becomes `APPROVED_CONTRACT`; `-03`..`-10` remain `PLANNED_BLOCKED`.
- Manifest `GFX01_02_APPROVED_CONTRACT_ONLY`: **633 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 91 `COMPLETED`, 24 approved gates**.
- Docs Validation + pt-BR audit; no HIGH/CRITICAL; registry byte-identical.

## TESTS

Docs validators, selector denial, contract review. No native GPU test authorized.

## DELIVERABLES

Contract, G6 activation evidence, activation JSON, manifest/validator/tests/checkpoint.

## REVIEW FORMAT

pt-BR: base/head, contract fidelity, admission, no-native-GPU boundary, blocked packets.

## STOP CONDITION

Stale, missing admission, native GPU/API/shader selected by inference, code implementation, manifest drift, HIGH/CRITICAL, rendering/ABI/release claim.

## CONTEXT LOCK

Base `0282408`; admission pins CORE-01-03/06/08/12/13 and CORE-02-03/04/08/10; contract review required before `-03`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-01-02-G6-ACTIVATION.md`.
