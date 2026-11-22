# NLE-PRPLAN-DATA-05-02 — G6 contract activation

**Status:** `G6 CONTRACT PROPOSAL / NO CODE AUTHORIZED / DATA-03 + DATA-04 CAPABILITY ADMISSION`. **Base main:** `23544da`. **Formal packet:** `NLE-PRPLAN-DATA-05-02`. **ADR:** [ADR-0114](../adr/0114-data-05-governance-slice.md). **Contract:** [data-05-bundle-v0](../contracts/data-05-bundle-v0.md). **WO:** [NLE-PRPLAN-DATA-05-02](../work-orders/NLE-PRPLAN-DATA-05-02.md).

## Authorization

The owner authorized continuation on 2026-11-22. DATA-05-01 governance is approved. This gate freezes only the bundle contract after Docs Validation and pt-BR audit. It does not activate `DATA-05-03`, write bundle code, select a codec, add signing/network/persistence, approve release/ABI or declare DATA-03/DATA-04 complete.

## Capability admission

- Formal dependencies are `DATA-03` and `DATA-04`; neither is module-qualified.
- Admission uses completed DATA-03 import metadata and DATA-04 scene-document capabilities.
- `module_completion_claimed=false`.
- No codec, signing, archive, native filesystem, network, MCP or release capability is used.

## Contract scope

- Target profile/cook plan with DATA-02 `AssetId`.
- Bounded Stormline-owned RLE encode/decode.
- Chunk store and generation-fenced streaming window.
- Manifest with checked ranges and non-cryptographic FNV-1a 64 fingerprint.
- Incremental reuse plan by chunk ID/fingerprint.
- Exact allowlists and TGT/RLE/MAN/STR/PAT/QLF oracles.
- No external codec, signing, network, persistence or serialization.

## Gate state after merge

- Manifest root `DATA05_02_APPROVED_CONTRACT_ONLY`: **642 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 84 `COMPLETED`, 22 approved gates**.
- `DATA-05-02` becomes `APPROVED_CONTRACT`; `DATA-05-03`..`-09` remain `PLANNED_BLOCKED`.
