# NLE-PRPLAN-DATA-04-02 — G6 contract activation

**Status:** `G6 CONTRACT PROPOSAL / NO CODE AUTHORIZED / CORE-05 + DATA-02 CAPABILITY ADMISSION`. **Base main:** `50836b4`. **Formal packet:** `NLE-PRPLAN-DATA-04-02`. **ADR:** [ADR-0113](../adr/0113-data-04-governance-slice.md). **Contract:** [data-04-scene-v0](../contracts/data-04-scene-v0.md). **WO:** [NLE-PRPLAN-DATA-04-02](../work-orders/NLE-PRPLAN-DATA-04-02.md).

## Authorization

The owner authorized completion of DATA-01..04 on 2026-11-22. DATA-04-01 governance is approved. This gate freezes only the scene-document contract after Docs Validation and pt-BR audit. It does not activate `DATA-04-03`, write scene code, select a codec, add persistence/native I/O/network, approve release/ABI or declare CORE-05/DATA-02 complete.

## Capability admission

- Formal dependencies are `CORE-05` and `DATA-02`; neither is module-qualified.
- Admission uses completed CORE-05 typed math/IDs and DATA-02 identity/schema capabilities.
- `module_completion_claimed=false`.
- No codec, persistence, native filesystem, network, MCP or release capability is used.

## Contract scope

- Schema ID 1, version 1..3, capability subset and canonicalization version.
- Scene/entity/component IDs and declarative entities/components/asset refs.
- Fixed 64 entities, 128 components, 64 asset refs, 64 patch ops, 128 diffs.
- Atomic patches with stale-revision rejection and semantic entity diffs.
- Exact allowlists and SCH/DOC/PATCH/DIFF/QLF oracles.
- No JSON/CBOR, persistence, serialization or dependency.

## Gate state after merge

- Manifest root `DATA04_02_APPROVED_CONTRACT_ONLY`: **650 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 78 `COMPLETED`, 20 approved gates**.
- `DATA-04-02` becomes `APPROVED_CONTRACT`; `DATA-04-03`..`-08` remain `PLANNED_BLOCKED`.
- Selector denies every ID; registry byte-identical.
