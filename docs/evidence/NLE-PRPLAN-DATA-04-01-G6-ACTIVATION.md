# NLE-PRPLAN-DATA-04-01 — G6 governance activation

**Status:** `G6 GOVERNANCE PROPOSAL / NO CODE AUTHORIZED / CORE-05 + DATA-02 CAPABILITY ADMISSION`. **Base main:** `a26e463`. **Formal packet:** `NLE-PRPLAN-DATA-04-01`. **ADR:** [ADR-0113](../adr/0113-data-04-governance-slice.md). **Contract:** [data-04-governance-v0](../contracts/data-04-governance-v0.md). **WO:** [NLE-PRPLAN-DATA-04-01](../work-orders/NLE-PRPLAN-DATA-04-01.md).

## Authorization

The owner authorized completion of DATA-01..04 on 2026-11-22. DATA-03 is `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`. This gate prepares only DATA-04 governance after Docs Validation and pt-BR audit. It does not activate `DATA-04-02`, write scene code, select a codec, add persistence/native I/O/network, approve release/ABI or declare CORE-05/DATA-02 complete.

## Capability admission

- Formal dependencies are `CORE-05` and `DATA-02`; neither is module-qualified.
- Admission may use completed CORE-05 typed math/IDs and DATA-02 identity/schema capabilities.
- `module_completion_claimed=false`.
- No codec, persistence, native filesystem, network, MCP or release capability is used.

## Governance scope

- ADR-0113 and ADR-0012 as planning direction only.
- In-memory scene schema/document, declarative entities/components/asset refs, atomic patches and semantic diffs.
- No JSON/CBOR codec, schema validator, persistence, migration journal or byte-format claim.
- Risk `LOW` docs / `ELEVATED` implementation; release `INTERNAL_ONLY`.

## Gate state after merge

- Manifest root `DATA04_01_APPROVED_GOVERNANCE_ONLY`: **651 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 78 `COMPLETED`, 19 approved gates**.
- `DATA-04-01` becomes `APPROVED_GOVERNANCE`; `DATA-04-02`..`-08` remain `PLANNED_BLOCKED`.
- Selector denies every ID; registry byte-identical; 80/80 module WOs `BLOCKED`.
