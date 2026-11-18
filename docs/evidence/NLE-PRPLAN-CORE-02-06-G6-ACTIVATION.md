# NLE-PRPLAN-CORE-02-06 — G6 activation (memory budget)

**Status:** `G6 PROPOSAL / CODE NOT IMPLEMENTED / GATE PENDING AUDIT`. **Base main:** `42ab4b74b686e9856c150101895a9e6182c964b5`. **Formal packet:** `NLE-PRPLAN-CORE-02-06`. **ADR:** [ADR-0098](../adr/0098-core-02-memory-budget.md). **Contract:** [core-02-memory-budget-v0](../contracts/core-02-memory-budget-v0.md). **WO:** [NLE-PRPLAN-CORE-02-06](../work-orders/NLE-PRPLAN-CORE-02-06.md).

## Owner authorization

The owner authorized continuing on 2026-11-18 (`contiue evoluindo`). CORE-02-03/-04/-05 are completed; capability-based L1 and ADR-0086 are ratified. This gate activates only `NLE-PRPLAN-CORE-02-06` after Docs Validation, pt-BR audit and merge.

It does not select an allocator, add interception/SMF/telemetry, approve ADR-0004 or authorize another packet/module.

## Capability admission

Formal `CORE-01` dependency remains. Admitted only via completed `CORE-01-03/-06/-07/-08`, `module_completion_claimed=false`; no window/input/DPI/IME/hotplug/soak capability used.

## Bounded technical slice

- `MemoryBudget` soft/hard accounting; atomic reserve/release; non-mutating hard rejection/underflow; pressure status; owner-thread.
- No allocation interception, SMF, reclaim, telemetry, leak tracking, global budget, ABI or release.
- Exact allowlist: `memory_budget.hpp`, `.cpp`, `tests/core/memory_budget_tests.cpp`, additive CMake/workflow, evidence.

## Gate state after merge

- Manifest root `CORE02_06_READY_L1_CAPABILITY_OVERLAY`: **726 `PLANNED_BLOCKED`, 17 `COMPLETED`, 4 approved gates, 1 `EXECUTOR_READY` (`CORE-02-06`)**.
- Selector `-06` exit 0; all other IDs exit 2; 80/80 WOs BLOCKED; registry unchanged.

## Proof obligations

BGT-01..BGT-06; four CI jobs + ASan/UBSan; existing 80 CTests; no overclaim.

No code/native PASS is claimed by this gate.
