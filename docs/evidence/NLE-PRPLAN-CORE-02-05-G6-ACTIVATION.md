# NLE-PRPLAN-CORE-02-05 — G6 activation (monotonic arena)

**Status:** `G6 PROPOSAL / CODE NOT IMPLEMENTED / GATE PENDING AUDIT`. **Base main:** `9d49dc3da22d245daf1df95d0f27ee56588904af`. **Formal packet:** `NLE-PRPLAN-CORE-02-05`. **ADR:** [ADR-0097](../adr/0097-core-02-monotonic-arena.md). **Contract:** [core-02-monotonic-arena-v0](../contracts/core-02-monotonic-arena-v0.md). **WO:** [NLE-PRPLAN-CORE-02-05](../work-orders/NLE-PRPLAN-CORE-02-05.md).

## Owner authorization

The owner authorized continuing on 2026-11-17 (`continue`). CORE-02-03/-04 are completed; capability-based L1 and ADR-0086 are ratified. This gate activates only `NLE-PRPLAN-CORE-02-05` after Docs Validation, pt-BR audit and merge.

It does not select an allocator, add pools/budgets/leaks/telemetry, override global allocation, approve ADR-0004 or authorize another packet/module.

## Capability admission

Formal `CORE-01` dependency remains. Admitted only via completed `CORE-01-03/-06/-07/-08`, `module_completion_claimed=false`; no window/input/DPI/IME/hotplug/soak capability used.

## Bounded technical slice

- `MonotonicArena` with one `MemoryBlock` backing allocation, bump allocation, alignment, reset/high-water, typed overflow/errors, owner-thread.
- No per-slice free, pools, budgets, leak tracking, telemetry, global/static arena, third-party, ABI or release.
- Exact allowlist: `monotonic_arena.hpp`, `.cpp`, `tests/core/monotonic_arena_tests.cpp`, additive CMake, additive workflow filters, evidence.

## Gate state after merge

- Manifest root `CORE02_05_READY_L1_CAPABILITY_OVERLAY`: **727 `PLANNED_BLOCKED`, 16 `COMPLETED`, 4 approved gates, 1 `EXECUTOR_READY` (`CORE-02-05`)**.
- Selector `-05` exit 0; all other IDs exit 2; 80/80 WOs BLOCKED; registry unchanged.

## Proof obligations

ARN-01..ARN-06; four CI jobs + ASan/UBSan; existing 73 CTests; no overclaim.

No code/native PASS is claimed by this gate.
