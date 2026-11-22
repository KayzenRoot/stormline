# NLE-PRPLAN-GFX-01-01 — GFX-01 governance (INTERNAL_ONLY)

**STATUS: GOVERNANCE PACKET — documentary only; no implementation authorized.** **Formal packet:** `NLE-PRPLAN-GFX-01-01`. **Predecessor:** DATA-05 internal sequence complete. **Issue:** #29. **Base:** `c87e9f7`. **ADR:** [ADR-0115](../adr/0115-gfx-01-governance-slice.md). **Contract:** [gfx-01-governance-v0](../contracts/gfx-01-governance-v0.md).

## OBJECTIVE

Record bounded governance for GFX-01: backend-neutral logical RHI with Null/reference backend, device generations, queues, resources, barriers and feature tiers. No native GPU or rendering.

## CONTEXT

DATA-05 closed as `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`. GFX-01 research/architecture/ADR-0014 exist; no code. No graphics API is selected; physical GPU qualification unavailable.

## SCOPE

- ADR-0115 governance and ADR-0014 planning-only ratification.
- Governance contract: no-native-GPU boundary, generation/fencing policy, release/risk, admission, gates.
- WO/G6 evidence, manifest/validator/tests/checkpoint.

## OUT OF SCOPE

GFX-01 implementation, Vulkan/D3D12/Metal/SDL GPU, shader/pipeline, swapchain, rendering, GPU timing, physical hardware, MCP GPU access, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0014/0086/0115, GFX-01 architecture/research/api, DATA-05 closeout, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0115; no backend/dependency selection; fail-closed generations/descriptors/features.

## ARCHITECTURE RULES

GFX-01 owns logical RHI; CORE-01 native OS; CORE-02 memory; CORE-03 jobs; CORE-04 ticks; CORE-05 math/IDs; CORE-06 diagnostics; DATA-05 bundles; GFX-02/03 higher graphics.

## CONSTRAINTS

Risk `LOW` documentary / `ELEVATED` implementation; release `INTERNAL_ONLY`; no native GPU/dependency/secret/paid service/network/ABI/release. CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## ACCEPTANCE CRITERIA

- ADR-0115/governance contract record no-native-GPU boundary, generations, quotas and admission.
- `GFX-01-01` becomes `APPROVED_GOVERNANCE`; `GFX-01-02`..`-10` remain `PLANNED_BLOCKED`.
- Manifest `GFX01_01_APPROVED_GOVERNANCE_ONLY`: **634 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 91 `COMPLETED`, 23 approved gates**.
- Docs Validation + pt-BR audit; no HIGH/CRITICAL; registry byte-identical.

## TESTS

Docs validators, selector denial, manifest/validator tests. No native GPU test authorized.

## DELIVERABLES

ADR-0115, governance contract, WO, G6 evidence, manifest/validator/tests/checkpoint.

## REVIEW FORMAT

pt-BR: base/head, governance fidelity, admission, no-native-GPU boundary, no backend/dependency, blocked packets.

## STOP CONDITION

Stale context, missing owner continuation, backend/API selected by inference, GPU/render code, ABI/release, drift, HIGH/CRITICAL.

## CONTEXT LOCK

Base `c87e9f7`; ADR-0014 planning-only; no native graphics API selected.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-01-01-G6-ACTIVATION.md`.
