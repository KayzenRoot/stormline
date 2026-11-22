# NLE-PRPLAN-CORE-04-09 — G6 qualification activation

**Status:** `G6 QUALIFICATION PROPOSAL / TEST-ONLY CODE NOT IMPLEMENTED`. **Base main:** `754efc5a1dbf1043f9ae09c8f174d787ea594dc6`. **Packet:** `NLE-PRPLAN-CORE-04-09`. **ADR:** [ADR-0107](../adr/0107-core-04-governance-slice.md). **Contract:** [core-04-qualification-v0](../contracts/core-04-qualification-v0.md). **WO:** [NLE-PRPLAN-CORE-04-09](../work-orders/NLE-PRPLAN-CORE-04-09.md).

## Authorization

The owner instructed continuation on 2026-11-22. This gate activates only `CORE-04-09` test-only qualification after Docs Validation and pt-BR audit. It does not activate `CORE-04-10`, add production code, select a timing SDK, approve release/ABI or declare CORE-01 complete.

## Admission

Same bounded CORE-01 capabilities as CORE-04-01..04; `module_completion_claimed=false`.

## Bounded slice

QLF-01 integrated; QLF-02 24 h rational stress; QLF-03 recovery; QLF-04 overload; QLF-05 report-only benchmark. Exact allowlist: qualification test, CMake, workflow, evidence.

## Gate state after merge

Manifest root `CORE04_09_READY_L1_CAPABILITY_OVERLAY`: **703 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 36 `COMPLETED`, 8 approved gates**; `CORE-04-10` blocked; selector only `-09`; registry byte-identical.

No code/native PASS is claimed by this gate.
