# CORE-02 Isolated Allocator Benchmark Contract v0 (NLE-CORE02-ALLOC-001)

**Status:** `CONTRACT / REPORT_ONLY / NO SELECTION`. **Base:** `358bca21352df5a0ccf7380c2f40472e8e8f031e`. **ADR:** [ADR-0104](../adr/0104-core-02-allocator-benchmark.md). **WO:** [NLE-CORE02-ALLOC-001](../work-orders/NLE-CORE02-ALLOC-001.md).

## Objective

Provide an optional, isolated, reproducible harness comparing the approved baseline allocators with pinned mimalloc 3.7.0 and rpmalloc 2.0.1 under explicit APIs. No default replacement, production integration, threshold or selection.

## Dependencies (pinned)

| Dependency | Version | Commit | License |
|---|---|---|---|
| mimalloc | v3.7.0 | `1ed67b5156a763441d2ec3c20221a7b3cd866129` | MIT |
| rpmalloc | 2.0.1 | `beef233c176b235587c0145f765e4316e5ca60d1` | MIT |

Build-time FetchContent only when `STORMLINE_CORE02_ALLOC_BENCH=ON`; `MI_OVERRIDE=OFF`; rpmalloc compiled with `ENABLE_OVERRIDE=0`; no global symbol override.

## Harness executable

`stormline_core02_allocator_bench` with modes:

1. `correctness` — allocate/write/read/free for every allocator, size and alignment; non-null and 64-byte alignment verified; failure exits non-zero.
2. `bench` — fixed sizes 16/64/256/1024/4096 bytes, 1 thread, report `ns_per_pair`.
3. `bench_mt` — same sizes with 4 threads, report aggregate `ns_per_pair`.
4. `aligned` — 64-byte aligned allocation/free for baseline `operator new(align_val_t)`/pmr and explicit mimalloc/rpmalloc aligned APIs.
5. `full` — correctness + bench + bench_mt + aligned.

Allocators compared:

- `malloc/free`;
- `::operator new/delete`;
- `std::pmr::new_delete_resource`;
- `SystemMemoryResource`;
- `mimalloc` (`mi_malloc`/`mi_free`, `mi_malloc_aligned`/`mi_free_aligned`);
- `rpmalloc` (`rpmalloc`/`rpfree`, `rpaligned_alloc`/`rpfree`), with `rpmalloc_initialize`, per-thread init/finalize and finalize.

Workload warm-up and checksum sinks prevent dead-code elimination. No timing threshold, winner, speedup, RSS, p95/p99 or physical claim. Output lines:

```text
ALLOC_BENCH_CONFIG compiler=... pointer_bits=... hardware_threads=...
ALLOC_BENCH allocator=... size=... threads=... ns_per_pair=... checksum=...
ALLOC_BENCH_OK
```

Exit non-zero only on correctness/build failure; timing lines are report-only.

## CMake and CI

- `STORMLINE_CORE02_ALLOC_BENCH` default `OFF`.
- New configure preset `core02-alloc-bench` (Release, option ON) and build preset.
- CI job `allocator-benchmark` on Linux, Windows and macOS runs only `ctest -R core02_allocator_bench -V` in the isolated build; no artifact upload and no paid runner.
- Existing default builds and tests remain unchanged; option OFF adds no FetchContent.

## Exact allowlist

1. `benchmarks/core02/allocator_compare.cpp`
2. `CMakeLists.txt` (option/FetchContent/target/preset wiring)
3. `CMakePresets.json` (additive benchmark preset)
4. `.github/workflows/core01-internal-headless.yml` (additive path filter/job)
5. `docs/adr/0104-core-02-allocator-benchmark.md`
6. `docs/contracts/core-02-allocator-benchmark-v0.md`
7. `docs/work-orders/NLE-CORE02-ALLOC-001.md`
8. `docs/evidence/NLE-CORE02-ALLOC-001.md`
9. `docs/legal/third-party-notices-core02-benchmark.md`

No `src/stormline` change, manifest, registry, G2, license decision or release change.

## Stop / rollback

Stop on stale base, unratified decision, global override, production integration, unpinned dependency, missing license/notice, correctness failure, CI red, HIGH/CRITICAL, threshold/winner/physical claim, or manifest/registry change. Revert PR or remove the optional target; production behavior is unchanged.
