# NLE-PRPLAN-DATA-03-02 — G6 contract activation

**Status:** `G6 CONTRACT PROPOSAL / NO CODE AUTHORIZED / DATA-02 CAPABILITY ADMISSION`. **Base main:** `ba715a2`. **Formal packet:** `NLE-PRPLAN-DATA-03-02`. **ADR:** [ADR-0112](../adr/0112-data-03-governance-slice.md). **Contract:** [data-03-import-v0](../contracts/data-03-import-v0.md). **WO:** [NLE-PRPLAN-DATA-03-02](../work-orders/NLE-PRPLAN-DATA-03-02.md).

## Authorization

The owner authorized completion of DATA-01..04 on 2026-11-22. DATA-03-01 governance is approved. This gate freezes only the import-planning contract after Docs Validation and pt-BR audit. It does not activate `DATA-03-03`, write importer/decoder code, select dependencies, add native I/O/network, approve release/ABI or declare DATA-02/CORE-01 complete.

## DATA-02 capability admission

- Formal dependency is `DATA-02`, `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`.
- Admission may use completed DATA-02 identity, dependencies, tags, queries, schema, references and qualification.
- `module_completion_claimed=false`.
- No decoder, archive, native filesystem, persistence, serialization, network, MCP or release capability is used.

## Contract scope

- Fixed importer descriptors and bounded signature sniffing (Png/Jpeg/Glb/Wav).
- Import plans tied to a valid DATA-01 `VfsPath`.
- Caller-supplied texture/animation/audio metadata validation with fixed quotas.
- Logical artifact validation and bounded `ImportReceipt` records carrying DATA-02 `AssetId`.
- Exact allowlists for `-03`..`-09` and IMP/TEX/ANIM/AUDIO/VAL/REC/QLF oracles.
- No decoder, conversion, host I/O, persistence, serialization or dependency.

## Gate state after merge

- Manifest root `DATA03_02_APPROVED_CONTRACT_ONLY`: **660 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 70 `COMPLETED`, 18 approved gates**.
- `DATA-03-02` becomes `APPROVED_CONTRACT`; `DATA-03-03`..`-10` remain `PLANNED_BLOCKED`.
- Selector denies every ID; registry byte-identical; 80/80 module WOs `BLOCKED`.

## Proof obligations

Docs Validation, contract review, selector denial, registry byte-identity, pt-BR audit, no HIGH/CRITICAL. No decoder/native PASS is claimed by this contract gate.
