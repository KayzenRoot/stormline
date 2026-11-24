# WORLD-03 governance contract v0 — internal logical spatial/streaming metadata

**Status:** `APPROVED GOVERNANCE / INTERNAL_ONLY / NO STREAMING RUNTIME`. **ADR:** [ADR-0129](../adr/0129-world-03-internal-spatial-streaming-metadata.md). **Architecture:** [world-03-internal-spatial-streaming-metadata](../architecture/world-03-internal-spatial-streaming-metadata.md). **Planning-only policy:** [ADR-0028](../adr/0028-world-03-budgeted-spatial-streaming-policy.md) remains `PROPOSED`.

## 1. Scope

This contract governs the internal WORLD-03 sequence: logical cell coordinates/keys, interest queries, spatial origin epoch intent and streaming plan metadata. It does not authorize I/O, decode, caching, threading, async tasks, physics/network coordination, rendering, editor, benchmarks or public ABI.

## 2. Invariants

1. **GOV-001 Fail closed:** invalid coordinates, cell keys, bounds, roles, priorities, generations or budgets produce a typed error and zeroed output; no silent fallback.
2. **GOV-002 Single authority:** DATA-05 owns I/O/decode/cache, CORE-03/06 scheduling, WORLD-02 scene source, WORLD-01 lifecycle, CORE-05 math, PHYS/AI/GAME/NET simulation authority.
3. **GOV-003 Identity separation:** durable cell keys and entity GUIDs are independent of render origin and runtime epochs.
4. **GOV-004 Determinism:** fixed-capacity plans, stable ordering where required, no allocation, exception, file, network, audio, GPU, clock, thread or global state.
5. **GOV-005 No runtime claim:** no async execution, I/O, decompression, cache, origin rebase, spatial query result, physics/network coordination or benchmark.
6. **GOV-006 Diagnostics:** every error carries a typed code, source ID and bounded index; output plans are reset before validation.
7. **GOV-007 Traceability:** one stable Work Order ID across issue, branch, PR, evidence and corrections; exact allowlists per slice.

## 3. Planned API areas (frozen only in `-02`)

- Cell coordinate intent: signed cell X/Z (and policy Y), floor division, overflow checks, unique cell keys.
- Interest query intent: AABB bounds, role, priority, exact/approx, completeness status.
- Origin epoch intent: old/new origin, old/new epoch, owner acknowledgement fields.
- Streaming plan intent: cell states, priorities, request/cancel generations, bounded budgets.
- Common diagnostic and capacity types under `src/stormline/spatial/`.

Exact type names, capacities, error enums and allowlists are frozen by `WORLD-03-02` before implementation. No code may be created from this governance contract alone.

## 4. Slice oracles

| ID | Scenario | Oracle |
|---|---|---|
| CEL-01 | cells | signed coords, floor division, overflow, uniqueness |
| INT-01 | interest | bounds validity, union, role/priority, completeness |
| ORG-01 | origin | epoch/origin change validation, owner ack fields |
| STR-01 | streaming plan | states/priorities, generations, budget bounds |
| QLF-W301 | integrated | cells -> interest -> origin -> streaming |
| QLF-W302 | deterministic repeat | identical plans/counts |
| QLF-W303 | failure recovery | typed error followed by valid operation |
| QLF-W304 | bounded overload | 10,000 attempts keep caps |

## 5. Out of scope

Async tasks/threads, I/O/decode/cache, memory pressure, origin rebase execution, spatial index/query results, physics/network coordination, rendering/GPU, editor, audio, export, performance, ABI, release and production readiness.

## 6. Qualification statement

Passing internal CI qualification is not physical, OS, security, soak, I/O, concurrency, performance or traversal qualification. WORLD-03 may close only as `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`.
