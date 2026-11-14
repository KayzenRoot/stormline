# WORLD-02 — Reproducible Prefab 3-Way Rebase, Save/Reload and Graph Benchmark Protocol

**Research #162 | NLE-P00-WO-002-WORLD-02 | FUTURE ONLY / NOT EXECUTED**. No stopwatch/CPU/memory/IO measurements, rendered scene, editor, prefab or recovered file exists.

## Clean-room source scenes
- Build original rights-cleared small scene `S` with root R→children A,B and nested prefab `B` with local NodeGuid; variant V overrides a single Color and adds child C; place 100/1000/10000+ instances in independent synthetic workloads. Exact source IDs, component schema, parent/sibling order and user-owned asset provenance pinned.
- Base version B0→B1 updates unmodified field f1 and simultaneously conflicts with variant override f2; perform base/ours/theirs three-way field merge and node-add/removal conflict, replay stable source revisions, compare to independent reference. Proposed SIOP incremental propagator vs simple complete recompose oracle, with identical resulting identities, override masks and conflict receipts.
- Reparent with KEEP_LOCAL/KEEP_WORLD, singular parent inverse, shear, mirror and huge-world origin, under both ECS and future PHYS authority. Independently calculate affine reference matrices and precision tolerances.
- Crash/fault injection: before DATA-04 fsync, after durable source commit but before WORLD-01 instance publish, halfway nested cook, GPU/device loss after scene revision and auth/CAS conflict. Prove no partial published scene, journal redo/replay idempotent and no silent override/reference loss.
- Hostile third-party inputs only through sandboxed DATA-03 importer: crafted nested cycles, duplicate IDs, huge arrays, path traversal/script, incompatible variants; test rejection without OOM or cross-project asset leakage. No actual USD/O3DE/Unity/Godot code/asset required for clean-room original format oracle.
- Test actual windows/MSVC, Linux/GCC+Clang, macOS ARM64 and Web/WASM with same serialized golden fixture; compare encoded field semantics, not raw ABI bytes or native pointers.

## Measurement
Freeze base+head SHA, source format/schema versions, compiler/runtime/OS CPU/DRAM/storage, DATA-04 journal fsync, dataset source hash/licensing, prefab depth/width/fanout/variant number/instance count, patch distribution, all field identity and component owner semantics, cache warm/cold, job scheduler concurrency seed and budget.
- Collect rebase correctness: exact field and hierarchy diff, local override preservation, orphan/conflict counts, GUID mapping and replay nondeterminism. If a faster implementation loses one local override or creates cycle, **FAIL** regardless of throughput.
- Collect time CPU p50/p95/p99 (preview and rebase), I/O fsync/serialize, runtime ECS publish latency, dirty-cooked invalidation, peak allocated and resident bytes, dependency cache invalidation count and user-visible incomplete/stale state.
- Compare full recompose+3-way merge baseline with optional SIOP incremental plan at equal correctness; provide worst-case source change touching all instances and best-case one field. Drop optional complexity if correctness/maintenance/performance benefits not repeatable.
- Source provenance, exact device+toolchain, raw logs, rerunnable fixtures/seed, target quality/perf and CRITICAL/HIGH resolution must appear in a future Evidence Bundle. **ZERO tests executed, ZERO measured performance now**.
