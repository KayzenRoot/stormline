# NLE-PRPLAN-CORE-06-02 — G6 contract activation

**Status:** `G6 CONTRACT PROPOSAL / NO CODE AUTHORIZED / CORE-01 CAPABILITY ADMISSION`. **Base main:** `9c800e5fb6750dd8e6206e0ea72af7bb9aeabf9a`. **Formal packet:** `NLE-PRPLAN-CORE-06-02`. **ADR:** [ADR-0109](../adr/0109-core-06-governance-slice.md). **Contract:** [core-06-diagnostics-v0](../contracts/core-06-diagnostics-v0.md). **WO:** [NLE-PRPLAN-CORE-06-02](../work-orders/NLE-PRPLAN-CORE-06-02.md).

## Authorization

The owner authorized completion of CORE-06 on 2026-11-22. CORE-06-01 governance is `APPROVED_GOVERNANCE`; this gate prepares only the `CORE-06-02` contract after Docs Validation and pt-BR audit. It does not activate `CORE-06-03`, write diagnostics code, select spdlog/Tracy/Perfetto/Crashpad, add network/crash upload, approve release/ABI or declare CORE-01 complete.

## CORE-01 capability admission

- Formal `CORE-01` dependency remains; CORE-01 is not module-qualified.
- Admission is limited to completed `CORE-01-03` headless build/test, `-06` portable paths, `-07` SDL3 build baseline, `-08` native CI matrix, `-12` lifecycle requests and `-13` capability graph.
- `module_completion_claimed=false`.
- No window/input/DPI/IME/hotplug/sleep-resume/soak/renderer/GPU/audio/network/public ABI/release capability is used.

## Contract scope

- Bounded text and typed `DiagnosticError`.
- Logs, spans, counters, local crash envelope, profile samples and opt-in local telemetry.
- Fixed capacities, drop accounting, per-producer sequence, no network/file I/O.
- LOG/TRACE/COUNTER/CRASH/PROF/TEL and QLF oracles; exact `CORE-06-03`..`-09` allowlists.
- No implementation, dependency, public ABI, serialization format or release.

## Gate state after merge

- Manifest root `CORE06_02_APPROVED_CONTRACT_ONLY`: **690 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 46 `COMPLETED`, 12 approved gates**.
- `CORE-06-02` becomes `APPROVED_CONTRACT`; `CORE-06-03`..`-10` remain `PLANNED_BLOCKED`.
- Selector denies every ID; registry byte-identical; 80/80 module WOs `BLOCKED`.

## Proof obligations

Docs Validation, contract review, selector denial, registry byte-identity, pt-BR audit, no HIGH/CRITICAL. No code/native PASS is claimed by this contract gate.
