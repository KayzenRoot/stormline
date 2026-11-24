# NLE-PRPLAN-WORLD-03-02 — G6 contract activation

**Status:** `G6 CONTRACT ACTIVATION / DOCUMENTATION ONLY / NO CODE AUTHORIZED BY THIS RECORD`. **Base main:** `ac9e864`. **Formal packet:** `NLE-PRPLAN-WORLD-03-02`. **ADR:** [ADR-0129](../adr/0129-world-03-internal-spatial-streaming-metadata.md). **Contract:** [world-03-spatial-internal-v0](../contracts/world-03-spatial-internal-v0.md). **WO:** [NLE-PRPLAN-WORLD-03-02](../work-orders/NLE-PRPLAN-WORLD-03-02.md).

## Authorization

The owner authorized continuation on 2026-11-24. WORLD-03-01 is approved. This gate freezes the exact API and allowlists; it does not authorize code.

## Capability admission

- Formal dependencies are `WORLD-02` and `DATA-05`; neither is module-qualified.
- Admission uses completed internal capabilities.
- `module_completion_claimed=false`.

## Frozen surface

- `stormline::spatial` common types, errors, capacities and diagnostic.
- `cell_floor_div`/`plan_cells` (CEL-01), `plan_interest` (INT-01), `plan_origin_change` (ORG-01), `plan_streaming` (STR-01).
- QLF-W301..W304 integrated qualification definitions.
- Exact per-slice allowlists for `-03`..`-07`; no production `.cpp`.

No async task, I/O, decode, cache, origin rebase, spatial query result, physics/network coordination, renderer, editor, GPU, performance, ABI or release is authorized.

## Gate state after merge

- Manifest root `WORLD03_02_APPROVED_CONTRACT_ONLY`: **501 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 195 `COMPLETED`, 52 approved gates**.
- `WORLD-03-02` becomes `APPROVED_CONTRACT`; `WORLD-03-03`..`-08` remain `PLANNED_BLOCKED`.
