# NLE-PRPLAN-CORE-02-07 — G6 activation (leak tracking)

**Status:** `G6 PROPOSAL / CODE NOT IMPLEMENTED / GATE PENDING AUDIT`. **Base main:** `74524e55237436a6b4501aab58b31e76cd1d5479`. **Formal packet:** `NLE-PRPLAN-CORE-02-07`. **ADR:** [ADR-0099](../adr/0099-core-02-leak-tracking.md). **Contract:** [core-02-leak-tracking-v0](../contracts/core-02-leak-tracking-v0.md). **WO:** [NLE-PRPLAN-CORE-02-07](../work-orders/NLE-PRPLAN-CORE-02-07.md).

## Owner authorization

The owner authorized continuing on 2026-11-18 (`continue`). CORE-02-03/-04/-05/-06 are completed; capability-based L1 and ADR-0086 are ratified. This gate activates only `NLE-PRPLAN-CORE-02-07` after Docs Validation, pt-BR audit and merge.

It does not add allocation interception, pointer tracking, telemetry/export, SMF, approve ADR-0004 or authorize another packet/module.

## Capability admission

Formal `CORE-01` dependency remains. Admitted only via completed `CORE-01-03/-06/-07/-08`, `module_completion_claimed=false`; no window/input/DPI/IME/hotplug/soak capability used.

## Bounded technical slice

- `LeakTracker` fixed-capacity explicit tokens; track/release; generation-checked stale/double-release rejection; capacity exhaustion/reuse; live/peak counters; owner-thread.
- A leak means an outstanding tracked token at a checkpoint, not proof of process-wide/third-party leaks.
- No allocation interception, pointer map, telemetry, reporting, global tracker, ABI or release.
- Exact allowlist: `leak_tracker.hpp`, `.cpp`, `tests/core/leak_tracker_tests.cpp`, additive CMake/workflow, evidence.

## Gate state after merge

- Manifest root `CORE02_07_READY_L1_CAPABILITY_OVERLAY`: **725 `PLANNED_BLOCKED`, 18 `COMPLETED`, 4 approved gates, 1 `EXECUTOR_READY` (`CORE-02-07`)**.
- Selector `-07` exit 0; all other IDs exit 2; 80/80 WOs BLOCKED; registry unchanged.

## Proof obligations

LKT-01..LKT-06; four CI jobs + ASan/UBSan; existing 86 CTests; no overclaim.

No code/native PASS is claimed by this gate.
