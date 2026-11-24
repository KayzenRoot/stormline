# NLE-PRPLAN-WORLD-01-02 — G6 contract activation

**Status:** `G6 CONTRACT ACTIVATION / DOCUMENTATION ONLY / NO CODE AUTHORIZED BY THIS RECORD`. **Base main:** `76d89dc`. **Formal packet:** `NLE-PRPLAN-WORLD-01-02`. **ADR:** [ADR-0127](../adr/0127-world-01-internal-entity-metadata.md). **Contract:** [world-01-entity-internal-v0](../contracts/world-01-entity-internal-v0.md). **WO:** [NLE-PRPLAN-WORLD-01-02](../work-orders/NLE-PRPLAN-WORLD-01-02.md).

## Authorization

The owner authorized continuation on 2026-11-24. WORLD-01-01 is approved. This gate freezes the exact API and allowlists; it does not authorize code.

## Capability admission

- Formal dependencies are `CORE-05` and `DATA-04`; neither is module-qualified.
- Admission uses completed internal capabilities.
- `module_completion_claimed=false`.

## Frozen surface

- `stormline::world` common types, errors, capacities and diagnostic.
- `plan_world_identity`/`plan_entity_handle` (ENT-01), `plan_component_registry` (CMP-01), `plan_lifecycle` (LIF-01), `plan_entity_query` (QRY-01), `plan_reflection` (REF-01).
- QLF-W101..W104 integrated qualification definitions.
- Exact per-slice allowlists for `-03`..`-08`; no production `.cpp`.

No ECS storage, allocator, threading, serialization, persistence, hierarchy, spatial index, physics, networking, editor, GPU, performance, ABI or release is authorized.

## Gate state after merge

- Manifest root `WORLD01_02_APPROVED_CONTRACT_ONLY`: **519 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 181 `COMPLETED`, 48 approved gates**.
- `WORLD-01-02` becomes `APPROVED_CONTRACT`; `WORLD-01-03`..`-09` remain `PLANNED_BLOCKED`.
