# NLE-PRPLAN-CORE-02-04 — G6 activation (system allocator baseline)

**Status:** `G6 PROPOSAL / CODE NOT IMPLEMENTED / GATE PENDING AUDIT`. **Base main:** `4920c2f4e3bf787f58c867c2df5bd321eaca8729`. **Formal packet:** `NLE-PRPLAN-CORE-02-04`. **ADR:** [ADR-0096](../adr/0096-core-02-system-allocator-baseline.md). **Contract:** [core-02-system-allocator-v0](../contracts/core-02-system-allocator-v0.md). **WO:** [NLE-PRPLAN-CORE-02-04](../work-orders/NLE-PRPLAN-CORE-02-04.md).

## Owner authorization

The owner authorized continuing on 2026-11-17 (`continue`). The capability-based L1 direction and ADR-0086 rule are ratified; CORE-02-03 is completed. This gate activates only `NLE-PRPLAN-CORE-02-04` after Docs Validation, pt-BR audit and merge.

It does not select mimalloc/rpmalloc, override global allocation, adopt a performance budget, approve ADR-0004 globally, or authorize another packet/module.

## Capability admission

Formal `CORE-01` dependency remains. Admitted only via completed `CORE-01-03/-06/-07/-08`, with `module_completion_claimed=false`; no window/input/DPI/IME/hotplug/soak capability used.

## Bounded technical slice

- `SystemMemoryResource` over ordinary/aligned `::operator new/delete`; zero-byte=1; identity equality.
- `MemoryBlock` integration; 10,000 cycles; cross-thread release.
- Report-only benchmark vs `new_delete_resource`, raw new/delete, malloc/free; no threshold.
- Exact allowlist: `system_memory_resource.hpp`, `.cpp`, `tests/core/system_memory_resource_tests.cpp`, additive CMake, additive workflow filters, evidence.

## Gate state after merge

- Manifest root `CORE02_04_READY_L1_CAPABILITY_OVERLAY`: **728 `PLANNED_BLOCKED`, 15 `COMPLETED`, 4 approved gates, 1 `EXECUTOR_READY` (`CORE-02-04`)**.
- Selector `-04` exit 0; all other IDs exit 2; 80/80 WOs BLOCKED; registry unchanged.

## Proof obligations

SYS-01..SYS-06; four CI jobs + ASan/UBSan; existing 67 CTests; no global/third-party/winner/performance/ABI/release claim.

No code/native/performance PASS is claimed by this gate.
