# NLE-CORE02-ALLOC-Q4-CONSTRAINED-001 — Constrained-profile campaign

**Status:** `CONSTRAINED_PROFILE_CAMPAIGN_PASS / NATIVE_CI_PASS / FULL Q4 STILL BLOCKED / NO ALLOCATOR SELECTION`. **Base:** `6de186a64cebbdbc14026d24d04ceb7f6cbae7b2`. **WO:** [NLE-CORE02-ALLOC-Q4-001](../work-orders/NLE-CORE02-ALLOC-Q4-001.md). **ADR:** [ADR-0106](../adr/0106-core-02-q4-constrained-profile.md). **Issue:** #19.

## 1. Authorization

Owner ratified Q4 option B on 2026-11-21 (NLE-D021/ADR-0106): constrained profiles on an available physical host, with CPU affinity applied before workload, hard memory cap via Job Object, three runs, fail-closed validation and explicit `CONSTRAINED_PROFILE_NOT_EXACT_HARDWARE` labeling. This does not qualify CORE-02 or select an allocator.

## 2. Implementation

New Windows-only `benchmarks/core02/q4_profile_runner.cpp`:

- parses `--profile`, `--cpus`, `--memory-mib`, `--runs`, `--executable`, `--arguments`;
- creates the benchmark **suspended** with redirected stdout/stderr;
- creates a Job Object with `JOB_OBJECT_LIMIT_PROCESS_MEMORY` and `JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE`, applies and queries the memory limit;
- assigns the process to the job, applies `SetProcessAffinityMask`, reads the mask back with `GetProcessAffinityMask`, then resumes;
- validates exit code, empty stderr, exactly 1 `ALLOC_BENCH_CONFIG`, 2 `ALLOC_BENCH_CORRECTNESS=PASS`, 1 `ALLOC_BENCH_OK`, ≥84 result lines and completed runs;
- terminates an orphan child on failure; prints `PROFILE_RUN`/`PROFILE_SUMMARY` with `affinity_coverage=before_resume`.

`benchmarks/core02/test_q4_profile_runner.ps1` covers 9 cases: success, exit 7, missing OK, missing correctness, short results, invalid CPU, invalid memory, invalid runs and missing executable. It runs only on Windows.

## 3. Host

| Item | Observed |
|---|---|
| OS | Windows 11 Pro build 26300 x64 |
| Board/CPU | ASUS PRIME B450M-GAMING/BR; AMD Ryzen 3 4300GE 4C/8T |
| RAM | 15.1 GiB; 2 × 8 GiB 2400 MHz |
| Virtualization | VBS/Hyper-V active; `PHYSICAL_INFERRED_NOT_CERTIFIED` |
| Compiler | MSVC 14.44.35207, Release x64 |
| Runner SHA256 | `5BAC28DD3F902EEBD10BFE597A59D3E0074FBF35217079B749D8B53FEBCA8E07` |
| Benchmark SHA256 | `0DBFC13322DBE39AB5B69599B72BEC2E2C150393C49A80CFAD8DD6510C6EE6BF` |

Ubuntu 24.04 x64 and macOS 15 arm64 physical hosts remain unavailable; they are not emulated or replaced by CI.

## 4. Commands

```powershell
build/core02-alloc-bench/stormline_core02_q4_profile_runner.exe `
  --profile win11_2cpu_4gib --cpus 2 --memory-mib 4096 --runs 3 `
  --executable build/core02-alloc-bench/stormline_core02_allocator_bench.exe `
  --arguments full

build/core02-alloc-bench/stormline_core02_q4_profile_runner.exe `
  --profile win11_4cpu_8gib --cpus 4 --memory-mib 8192 --runs 3 `
  --executable build/core02-alloc-bench/stormline_core02_allocator_bench.exe `
  --arguments full
```

Raw output: [NLE-CORE02-ALLOC-Q4-CONSTRAINED-raw.txt](NLE-CORE02-ALLOC-Q4-CONSTRAINED-raw.txt).

## 5. Results — 64-byte class, report-only

Each profile: 3/3 runs exit 0, `ALLOC_BENCH_CORRECTNESS=PASS`, `ALLOC_BENCH_OK`, `results=84`, `affinity_coverage=before_resume`, memory limit applied. Values are median (min–max) of 3 runs, ns per allocate/free pair.

### 2 CPUs / 4 GiB (`0x3`, Job Object 4096 MiB)

| Allocator | 1 thread | 4 threads |
|---|---:|---:|
| malloc | 222.527 (34.007–227.946) | 91.982 (87.520–93.478) |
| new | 232.092 (37.974–253.676) | 141.751 (102.936–167.528) |
| pmr | 225.316 (44.068–238.032) | 139.091 (121.477–165.717) |
| system | 235.252 (45.209–243.055) | 108.106 (105.569–171.199) |
| mimalloc | 6.075 (6.035–6.625) | 18.765 (15.232–19.362) |
| rpmalloc | 5.572 (5.570–6.889) | 15.802 (13.443–17.369) |

### 4 CPUs / 8 GiB (`0xF`, Job Object 8192 MiB)

| Allocator | 1 thread | 4 threads |
|---|---:|---:|
| malloc | 227.147 (226.820–236.077) | 77.603 (76.628–78.923) |
| new | 236.297 (230.451–237.668) | 120.374 (118.815–120.689) |
| pmr | 227.932 (227.003–231.332) | 81.700 (77.186–119.061) |
| system | 242.659 (231.321–245.067) | 119.879 (82.777–123.263) |
| mimalloc | 6.650 (6.060–8.003) | 36.526 (21.034–37.072) |
| rpmalloc | 5.580 (5.516–7.230) | 27.392 (13.399–27.603) |

**Observation, not a ranking:** the baseline 1-thread path is mostly ~220–240 ns under the constrained runner, while one 2-CPU run recorded ~34–45 ns for baseline allocators; the cause of this wide run-to-run variance was not investigated. Possible interactions include Job Object accounting, CPU affinity/SMT selection, power state and process startup. No baseline-vs-third-party claim, threshold or winner is made. Allocator selection remains forbidden.

## 6. Stability and integrity

- 6/6 runner executions (2 profiles × 3) exit 0; each validates 84 result lines and all markers.
- Suspended start, affinity mask readback before resume, Job Object limit query and kill-on-close were exercised.
- No crash, null allocation, alignment failure or checksum mismatch; `override=none`.
- The 2-CPU run-to-run baseline variance is significant; results are not a stable performance dataset.
- No RSS/p95/p99/fragmentation claim; timing report-only.

## 7. Full Q4 coverage

| OS/profile | Status |
|---|---|
| Windows 11 x64, 2 CPUs/4 GiB constrained | **PARTIAL_CONSTRAINED** — affinity before resume + Job Object cap; not exact physical 2 vCPU/4 GiB hardware |
| Windows 11 x64, 4 CPUs/8 GiB constrained | **PARTIAL_CONSTRAINED** — same limitation |
| Ubuntu 24.04 x64 | **BLOCKED** — no physical host |
| macOS 15 arm64 | **BLOCKED** — no physical host |

**Full Q4 remains BLOCKED**; Windows is `PHYSICAL_INFERRED_NOT_CERTIFIED` and profiles are constrained, not exact hardware. No `Q4 PASS`, no allocator selection, no module qualification.

## 8. Local/CI verification

- Local Windows full matrix: **111/111 CTests PASS** (109 previous + helper + runner).
- `core02_q4_profile_runner_failclosed`: **PASS**, `Q4_RUNNER_TESTS_OK cases=9`.
- `validate_pr_plans.py`: PASS (721 blocked, 22 completed, 5 approved gates, 0 ready).
- CI [44951302855](https://github.com/KayzenRoot/stormline/actions/runs/44951302855) at HEAD `8fd1921…` SUCCESS:
  - Windows **111/111**, including `core02_q4_profile_runner_failclosed` (10.47 s);
  - Linux and Linux ASan/UBSan **110/110**;
  - macOS **109/109**;
  - `allocator-benchmark` PASS em Ubuntu GCC, Windows MSVC e macOS Clang.
- Docs Validation [44951302784](https://github.com/KayzenRoot/stormline/actions/runs/44951302784) SUCCESS; Sonar/Socket PASS.
- CI não substitui a matriz física; Ubuntu/macOS e perfis exatos continuam BLOCKED.

## 9. Limits and next gate

- Ubuntu/macOS physical hosts and exact 2 vCPU/4 GiB and 4 vCPU/8 GiB machines remain missing.
- No threshold/ranking/winner; no allocator default/integration; CORE-02 NOT_QUALIFIED; CORE-03 unchanged; NLE-D009 OPEN; G3 NOT_CLEARED.
- Next decision: provide exact physical hosts, or expressly accept constrained profiles as the maximum available evidence; numerical thresholds and allocator selection require separate ratification.
