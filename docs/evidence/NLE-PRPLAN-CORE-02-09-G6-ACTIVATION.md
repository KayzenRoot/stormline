# NLE-PRPLAN-CORE-02-09 — G6 activation (integrated memory qualification)

**Status:** `G6 PROPOSAL / TEST-ONLY CODE NOT IMPLEMENTED / GATE PENDING AUDIT`. **Base main:** `a20ff42cce2879657d357a52a9ba80052b9f7c02`. **Formal packet:** `NLE-PRPLAN-CORE-02-09`. **ADR:** [ADR-0101](../adr/0101-core-02-integrated-memory-qualification.md). **Contract:** [core-02-integrated-memory-qualification-v0](../contracts/core-02-integrated-memory-qualification-v0.md). **WO:** [NLE-PRPLAN-CORE-02-09](../work-orders/NLE-PRPLAN-CORE-02-09.md).

## Owner authorization

The owner authorized sequential CORE-02-08/-09/-10 on 2026-11-19, each conditioned on its individual gate. CORE-02-08 is completed/merged; ADR-0086 capability admission remains. This gate activates only `NLE-PRPLAN-CORE-02-09` after Docs Validation, pt-BR audit and merge.

It does not add production code, performance thresholds, fragmentation/OS-memory claims, global interception, release qualification or authorize CORE-03 implementation.

## Capability admission

Formal `CORE-01` dependency remains. Admitted only via completed `CORE-01-03/-06/-07/-08`, `module_completion_claimed=false`; no product window/soak capability used.

## Bounded technical slice

- Test-only executable `core02_memory_qualification_test` with QLF-01 integrated, QLF-02 10,000-iteration stress, QLF-03 recovery, QLF-04 2,000+ size-churn and QLF-05 report-only benchmark.
- Exercises block/arena/budget/leak/telemetry together with deterministic counter/state oracles.
- No production source, threshold, fragmentation estimator, OS RSS/VRAM, allocator comparison/selection, export, ABI or release.

## Gate state after merge

- Manifest root `CORE02_09_READY_L1_CAPABILITY_OVERLAY`: **723 `PLANNED_BLOCKED`, 20 `COMPLETED`, 4 approved gates, 1 `EXECUTOR_READY` (`CORE-02-09`)**.
- Selector `-09` exit 0; all other IDs exit 2; 80/80 WOs BLOCKED; registry unchanged.

## Proof obligations

QLF-01..QLF-05; four CI jobs + ASan/UBSan; existing 105 Linux / 104 Windows/macOS CTests; no threshold or overclaim.

No code/native PASS is claimed by this gate.
