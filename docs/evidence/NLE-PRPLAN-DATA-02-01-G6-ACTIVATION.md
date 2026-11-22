# NLE-PRPLAN-DATA-02-01 — G6 governance activation

**Status:** `G6 GOVERNANCE PROPOSAL / NO CODE AUTHORIZED / CORE-01 CAPABILITY ADMISSION`. **Base main:** `9728707`. **Formal packet:** `NLE-PRPLAN-DATA-02-01`. **ADR:** [ADR-0111](../adr/0111-data-02-governance-slice.md). **Contract:** [data-02-governance-v0](../contracts/data-02-governance-v0.md). **WO:** [NLE-PRPLAN-DATA-02-01](../work-orders/NLE-PRPLAN-DATA-02-01.md).

## Authorization

The owner authorized completion of DATA-01..04 on 2026-11-22. DATA-01 is `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`. This gate prepares only DATA-02 governance after Docs Validation and pt-BR audit. It does not activate `DATA-02-02`, write registry code, select SQLite/serialization/dependencies, add persistence/native I/O/network, approve release/ABI or declare CORE-01/DATA-01 complete.

## CORE-01 capability admission

- Formal `CORE-01` dependency remains; CORE-01 is not module-qualified.
- Admission is limited to completed `CORE-01-03` headless build/test, `-06` portable paths, `-07` SDL3 build baseline, `-08` native CI matrix, `-12` lifecycle requests and `-13` capability graph.
- `module_completion_claimed=false`.
- No window/input/DPI/IME/hotplug/sleep-resume/soak/renderer/GPU/audio/network/public ABI/release capability is used.

## Governance scope

- ADR-0111 and ADR-0010 as planning direction only.
- Opaque 128-bit asset identity, logical path mapping, in-memory-only fixed-capacity state, explicit cycle/unresolved policy.
- First slices IDs/dependencies/tags/queries/schema/references only; persistence/SQLite/serialization/recovery/MCP require separate G6.
- Risk `LOW` docs / `ELEVATED` implementation; release `INTERNAL_ONLY`.
- No code, dependency, CMake target, workflow, native filesystem, database or public ABI.

## Gate state after merge

- Manifest root `DATA02_01_APPROVED_GOVERNANCE_ONLY`: **671 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 62 `COMPLETED`, 15 approved gates**.
- `DATA-02-01` becomes `APPROVED_GOVERNANCE`; `DATA-02-02`..`-10` remain `PLANNED_BLOCKED`.
- Selector denies every ID; registry byte-identical; 80/80 module WOs `BLOCKED`.

## Proof obligations

Docs Validation, governance review, selector denial, registry byte-identity, pt-BR audit, no HIGH/CRITICAL. No code/native PASS is claimed by this governance gate.
