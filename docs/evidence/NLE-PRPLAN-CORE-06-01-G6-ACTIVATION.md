# NLE-PRPLAN-CORE-06-01 — G6 governance activation

**Status:** `G6 GOVERNANCE PROPOSAL / NO CODE AUTHORIZED / CORE-01 CAPABILITY ADMISSION`. **Base main:** `326f83fdfda026d3eb254010f3a82107c3743eb7`. **Formal packet:** `NLE-PRPLAN-CORE-06-01`. **ADR:** [ADR-0109](../adr/0109-core-06-governance-slice.md). **Contract:** [core-06-governance-v0](../contracts/core-06-governance-v0.md). **WO:** [NLE-PRPLAN-CORE-06-01](../work-orders/NLE-PRPLAN-CORE-06-01.md).

## Authorization

The owner instructed continuation on 2026-11-22 after CORE-05 closed. This gate prepares only CORE-06 governance after Docs Validation and pt-BR audit. It does not activate `CORE-06-02`, write diagnostics code, select spdlog/Tracy/Perfetto/Crashpad, add network/crash upload, approve release/ABI or declare CORE-01 complete.

## CORE-01 capability admission

- Formal `CORE-01` dependency remains; CORE-01 is not module-qualified.
- Admission is limited to completed `CORE-01-03` headless build/test, `-06` portable paths, `-07` SDL3 build baseline, `-08` native CI matrix, `-12` lifecycle requests and `-13` capability graph.
- `module_completion_claimed=false`.
- No window/input/DPI/IME/hotplug/sleep-resume/soak/renderer/GPU/audio/network/public ABI/release capability is used.

## Governance scope

- ADR-0109 and ADR-0008 as planning direction only.
- Owned typed diagnostic facade; no third-party type in core/ABI.
- Local-first; remote telemetry, crash upload, analytics, profiler listeners and network export OFF/not authorized.
- First slices logs/traces/counters only; crashes/profiling/telemetry remain blocked for separate G6.
- Risk `LOW` docs / `ELEVATED` implementation; release `INTERNAL_ONLY`.
- No code, dependency, CMake target, workflow, schema, binary format or public ABI.

## Gate state after merge

- Manifest root `CORE06_01_APPROVED_GOVERNANCE_ONLY`: **691 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 46 `COMPLETED`, 11 approved gates**.
- `CORE-06-01` becomes `APPROVED_GOVERNANCE`; `CORE-06-02`..`-10` remain `PLANNED_BLOCKED`.
- Selector denies every ID; registry byte-identical; 80/80 module WOs `BLOCKED`.

## Proof obligations

Docs Validation, governance review, selector denial, registry byte-identity, pt-BR audit, no HIGH/CRITICAL. No code/native PASS is claimed by this governance gate.
