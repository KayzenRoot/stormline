# NLE-CORE02-ALLOC-001 — Isolated allocator benchmark

**Status:** `IMPLEMENTED / LOCAL_PASS / NATIVE_CI_PASS / PHYSICAL_Q4_NOT_RUN`. **WO:** [NLE-CORE02-ALLOC-001](../work-orders/NLE-CORE02-ALLOC-001.md). **ADR:** [ADR-0104](../adr/0104-core-02-allocator-benchmark.md). **Contract:** [core-02-allocator-benchmark-v0](../contracts/core-02-allocator-benchmark-v0.md). **Issue:** #19.

Optional, isolated, report-only comparison of baseline allocators with pinned mimalloc 3.7.0 and rpmalloc 2.0.1. Baseline remains default; no allocator is selected; no production target links the benchmark dependencies.

## 1. Authorization and Context Lock

- **Owner ratification 2026-11-19:** Q1=A, Q2=B, Q3=A, Q4=B, Q7=A.
- **Base:** `358bca21352df5a0ccf7380c2f40472e8e8f031e`.
- **Code PR:** [PR #495](https://github.com/KayzenRoot/stormline/pull/495); implementation HEAD `51a2eb640a5389eb6342df2a607a52dc588c06bb`; audit pending at the final documentation head.
- **Scope:** optional harness only; no production integration, default change, threshold, winner, release or CORE-03 change.

## 2. Dependencies and licensing

| Component | Version | Commit | License | Override |
|---|---|---|---|---|
| mimalloc | v3.7.0 | `1ed67b5156a763441d2ec3c20221a7b3cd866129` | MIT | `MI_OVERRIDE=OFF` |
| rpmalloc | 2.0.1 | `beef233c176b235587c0145f765e4316e5ca60d1` | MIT | `ENABLE_OVERRIDE=0` |

- Both build-time FetchContent only with `STORMLINE_CORE02_ALLOC_BENCH=ON`; default builds do not fetch them (verified: no `mimalloc`/`rpmalloc` under the default build `_deps`).
- GitHub Security Advisories query returned zero published advisories for both repositories on 2026-11-19. This is a point-in-time check, not a full SCA.
- Notices: [third-party notices](../legal/third-party-notices-core02-benchmark.md).

## 3. Implemented harness

- Executable `stormline_core02_allocator_bench`, modes `correctness`, `bench`, `bench_mt`, `aligned`, `full`.
- Baseline: `malloc/free`, `::operator new/delete`, `std::pmr::new_delete_resource`, `SystemMemoryResource`.
- mimalloc explicit `mi_malloc`/`mi_free` and aligned variants; rpmalloc explicit `rpmalloc`/`rpfree` and aligned variants, with global/thread init/finalize.
- Fixed sizes 16/64/256/1024/4096; 1 thread and 4 threads; 64-byte aligned path; volatile read/write checksum; report-only output.
- No third-party type in an engine header; no production target links the benchmark dependencies.

## 4. Local results (observed)

- Build: MSVC 19.44, Release, x64; **OK**.
- Correctness: `ALLOC_BENCH_CORRECTNESS=PASS allocators=6` for regular and aligned sets.
- `ctest -R core02_allocator_bench -V`: **PASS**, `ALLOC_BENCH_OK`.
- Default regression with option OFF: **109/109 CTests PASS** (Windows local); no allocator dependencies built.
- Sample output (one local run, report-only, not a threshold):

```text
ALLOC_BENCH_CONFIG compiler=MSVC pointer_bits=64 hardware_threads=8 mimalloc_version=30700 rpmalloc=2.0.1 override=none
ALLOC_BENCH allocator=malloc  size=64 threads=1 ns_per_pair=33.014 checksum=25493856
ALLOC_BENCH allocator=new     size=64 threads=1 ns_per_pair=39.821 checksum=25493856
ALLOC_BENCH allocator=pmr     size=64 threads=1 ns_per_pair=53.433 checksum=25493856
ALLOC_BENCH allocator=system  size=64 threads=1 ns_per_pair=47.480 checksum=25493856
ALLOC_BENCH allocator=mimalloc size=64 threads=1 ns_per_pair=6.141 checksum=25493856
ALLOC_BENCH allocator=rpmalloc size=64 threads=1 ns_per_pair=5.527 checksum=25493856
ALLOC_BENCH_OK
```

These numbers are a single Windows MSVC local observation. They are not physical Q4 evidence, not cross-OS evidence, not a winner and not a performance PASS.

## 5. Native CI (authoritative, observed)

Run [44520035927](https://github.com/KayzenRoot/stormline/actions/runs/44520035927) at implementation HEAD `51a2eb6…`; Docs [44520036058](https://github.com/KayzenRoot/stormline/actions/runs/44520036058) SUCCESS; all jobs SUCCESS.

| Job | Runner | Result |
|---|---|---|
| `docs-validation` | required G2 check | SUCCESS |
| `allocator-benchmark` | ubuntu-24.04 (GCC, 4 threads) | **PASS**, 111/111 CTest |
| `allocator-benchmark` | windows-2025-vs2026 (MSVC, 4 threads) | **PASS**, 110/110 CTest |
| `allocator-benchmark` | macos-15 (Clang, 3 threads) | **PASS**, 110/110 CTest |
| `linux` | ubuntu-24.04 | SUCCESS |
| `linux-sanitizers` | ASan/UBSan | SUCCESS |
| `windows` | MSVC | SUCCESS |
| `macos` | Apple clang | SUCCESS |

CI report-only 64-byte/1-thread samples (ns/pair, one run each; **no threshold/winner**):

| Allocator | Linux GCC | Windows MSVC | macOS Clang |
|---|---:|---:|---:|
| malloc | 11.076 | 22.600 | 28.085 |
| new | 13.617 | 24.233 | 25.220 |
| pmr | 19.655 | 29.895 | 48.352 |
| system | 16.704 | 24.688 | 34.669 |
| mimalloc | 6.362 | 4.394 | 11.472 |
| rpmalloc | 6.954 | 3.170 | 5.925 |

All three benchmark jobs reported `ALLOC_BENCH_CORRECTNESS=PASS` and `ALLOC_BENCH_OK`.

### Corrections during CI (same WO/PR)

- Preset `binaryDir` expanded to `/build/...` due shell interpolation; corrected to `${sourceDir}/build/core02-alloc-bench`.
- Windows benchmark initially selected MinGW; job now invokes the approved MSVC `vcvars64` before configure/build.
- Ubuntu benchmark lacked X11/Wayland packages; benchmark builds SDL in console mode when the option is ON, since the harness creates no window.
- GCC `-Werror=format` rejected `%llu` with `uint64_t`; checksum is now cast to `unsigned long long`.
- First Windows run also exposed `std::aligned_alloc` unavailability under MinGW; Windows path now uses `_aligned_malloc`/`_aligned_free`.

## 6. Limitations

- **Q4 physical matrix NOT_RUN:** no Windows 11 physical machine, Ubuntu 24.04 physical machine, macOS 15 arm64 physical machine, or 2 vCPU/4 GiB and 4 vCPU/8 GiB profiles were executed. CI hosted runners do not satisfy Q4.
- No threshold p50/p95/p99, RSS, overhead or fragmentation; no allocator winner or default selection.
- No process-wide leak detection, telemetry export, SMF, public ABI, release or license decision.
- Upstream advisories were checked only at the pinned commits; re-check before updates/distribution.
- CORE-02 remains NOT_QUALIFIED; no CORE-03 change.

## 7. Rollback

Disable `STORMLINE_CORE02_ALLOC_BENCH` (default OFF) or revert the PR; no production target or default allocator changes. FetchContent sources are build-tree only.

## 8. Proposed checkpoint delta (promoted by independent documentation PR)

Record the optional harness, pinned commits/licenses, report-only CI evidence, default regression and the explicit Q4 physical NOT_RUN boundary. Do not record an allocator winner, threshold, qualification or release.
