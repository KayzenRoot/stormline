# NLE-PRPLAN-DATA-05-01 — G6 governance activation

**Status:** `G6 GOVERNANCE PROPOSAL / NO CODE AUTHORIZED / DATA-03 + DATA-04 CAPABILITY ADMISSION`. **Base main:** `6886f93`. **Formal packet:** `NLE-PRPLAN-DATA-05-01`. **ADR:** [ADR-0114](../adr/0114-data-05-governance-slice.md). **Contract:** [data-05-governance-v0](../contracts/data-05-governance-v0.md). **WO:** [NLE-PRPLAN-DATA-05-01](../work-orders/NLE-PRPLAN-DATA-05-01.md).

## Authorization

The owner authorized continuation on 2026-11-22. DATA-04 is `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`. This gate prepares only DATA-05 governance after Docs Validation and pt-BR audit. It does not activate `DATA-05-02`, write bundle code, select a codec, add signing/network/persistence, approve release/ABI or declare DATA-03/DATA-04 complete.

## Capability admission

- Formal dependencies are `DATA-03` and `DATA-04`; neither is module-qualified.
- Admission may use completed DATA-03 import metadata and DATA-04 scene-document capabilities.
- `module_completion_claimed=false`.
- No codec, signing, archive, native filesystem, network, MCP or release capability is used.

## Governance scope

- ADR-0114 and ADR-0013 as planning direction only.
- Target/cook plans, bounded owned RLE, chunk streaming, non-cryptographic manifest fingerprint and incremental reuse.
- No external codec, archive, signing key, network streaming or durable patching.
- Risk `LOW` docs / `ELEVATED` implementation; release `INTERNAL_ONLY`.

## Gate state after merge

- Manifest root `DATA05_01_APPROVED_GOVERNANCE_ONLY`: **643 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 84 `COMPLETED`, 21 approved gates**.
- `DATA-05-01` becomes `APPROVED_GOVERNANCE`; `DATA-05-02`..`-09` remain `PLANNED_BLOCKED`.
- Selector denies every ID; registry byte-identical; 80/80 module WOs `BLOCKED`.
