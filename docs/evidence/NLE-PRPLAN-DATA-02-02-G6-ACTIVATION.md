# NLE-PRPLAN-DATA-02-02 — G6 contract activation

**Status:** `G6 CONTRACT PROPOSAL / NO CODE AUTHORIZED / CORE-01 CAPABILITY ADMISSION`. **Base main:** `5443021`. **Formal packet:** `NLE-PRPLAN-DATA-02-02`. **ADR:** [ADR-0111](../adr/0111-data-02-governance-slice.md). **Contract:** [data-02-registry-v0](../contracts/data-02-registry-v0.md). **WO:** [NLE-PRPLAN-DATA-02-02](../work-orders/NLE-PRPLAN-DATA-02-02.md).

## Authorization

The owner authorized completion of DATA-01..04 on 2026-11-22. DATA-02-01 governance is approved. This gate freezes only the registry contract after Docs Validation and pt-BR audit. It does not activate `DATA-02-03`, write registry code, select SQLite/serialization/dependencies, add persistence/native I/O/network, approve release/ABI or declare CORE-01/DATA-01 complete.

## CORE-01 capability admission

- Formal `CORE-01` dependency remains; CORE-01 is not module-qualified.
- Admission is limited to completed `CORE-01-03` headless build/test, `-06` portable paths, `-07` SDL3 build baseline, `-08` native CI matrix, `-12` lifecycle requests and `-13` capability graph.
- `module_completion_claimed=false`.
- No window/input/DPI/IME/hotplug/sleep-resume/soak/renderer/GPU/audio/network/public ABI/release capability is used.

## Contract scope

- Opaque 128-bit `AssetId`, `ProjectId`, `AssetRecord` and typed `RegistryError`.
- Project-scoped path mapping with tombstones and stable identity.
- Bounded dependency edges, tags, deterministic queries, schema-versioned metadata and ID-based references.
- Fixed capacities and stable `AssetId` ordering; no persistence or serialization.
- Exact allowlists for `DATA-02-03`..`-09` and ID/DEP/TAG/QUERY/SCHEMA/REF/QLF oracles.
- Risk `LOW` docs / `ELEVATED` implementation; release `INTERNAL_ONLY`.
- No code, dependency, CMake target, workflow, native filesystem, database or public ABI.

## Gate state after merge

- Manifest root `DATA02_02_APPROVED_CONTRACT_ONLY`: **670 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 62 `COMPLETED`, 16 approved gates**.
- `DATA-02-02` becomes `APPROVED_CONTRACT`; `DATA-02-03`..`-10` remain `PLANNED_BLOCKED`.
- Selector denies every ID; registry byte-identical; 80/80 module WOs `BLOCKED`.

## Proof obligations

Docs Validation, contract review, selector denial, registry byte-identity, pt-BR audit, no HIGH/CRITICAL. No code/native PASS is claimed by this contract gate.
