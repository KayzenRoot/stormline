# NLE-CORE01-QUAL-001 — Exploratory Runtime Baseline Evidence

**Status:** NATIVE CODE-HEAD QUALIFIED FOR EXPLORATORY MEASUREMENT / FINAL PR HEAD CHECKS PENDING / NOT MODULE QUALIFICATION.  
**Risk:** STANDARD. **Scope:** test-only, owner-authorized 2026-11-18.  
**Main/base:** `80f1610f4ac6da8b8daf7f98bbb4ef209963ad6c`.  
**Tested implementation HEAD:** `673ebc8790c974c5cf14af663545108e31798e68`.  
**PR:** [#479](https://github.com/KayzenRoot/stormline/pull/479) Draft; not merged.  
**Native CI:** [run #44384571286](https://github.com/KayzenRoot/stormline/actions/runs/44384571286) `SUCCESS` (4/4 jobs).  
**Docs Validation on tested implementation HEAD:** [run #44384571437](https://github.com/KayzenRoot/stormline/actions/runs/44384571437) `SUCCESS`.

## Source Check / lock
Canonical hierarchy checked against main before changes: checkpoint `f74c4df1c5af4ea2b0c7b644f81fa27b8a1e211e`, Ledger `01aa967790dc1ea5e72c2ebebae7b832ec579981`, Scope `0b65820507d946d2b2b4ed3a2b869e60cafaaf22`, DoD `e0b7c2466ebec9790a715e47490c015cfb502db4`, Architecture `df62574cb3956c3ac9881631a4cf66be4e1abff1`, Requirements `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`. Git blob IDs are *not* binary SHA256.

**Allowlist (4/4):** new `tests/core/core01_runtime_baseline_tests.cpp`, additive `CMakeLists.txt`, `docs/work-orders/NLE-CORE01-QUAL-001.md`, this Evidence. No edits to any `src/` files, CI workflow, CMakePresets, dependencies, SDK/toolchains, ADRs, license, manifest, registry, source hierarchy, G2 or other modules.

**Frozen canonical data, checked on branch:** manifest blob `dc01d3ccc62e857feeb61b3be599f66ae2c08c44` (748 packets, 19 COMPLETED, 725 PLANNED_BLOCKED, two each approved governance/contracts, 0 EXECUTOR_READY); registry blob `abbf8e5f971b8de5d73f55c9ec5a0bd7a2632024` (80/80 module WOs BLOCKED, 0 ready, `engine_implemented=false`). CORE-01-03..16 already COMPLETED; ADR-0003/0075 PROPOSED, G3 global NOT_CLEARED, NLE-D009 OPEN.

## Reproduction and correction delta CD-01
- **First native run:** [#44383510514](https://github.com/KayzenRoot/stormline/actions/runs/44383510514) reproduced a new *test-harness oracle* defect on Windows job 135081790463: 93/94 CTests passed, with `core01_runtime_baseline` alone failing when the fast headless warm operation actually measured `0 ns` on `steady_clock`. All 92 pre-existing regression tests passed. Linux ASan/UBSan and macOS on that superseded code also passed, but these are not evidence for the final implementation.
- **Correction within the same WO/PR:** accept actual zero-ns samples as **clock-censored**, explicitly report `below_clock_tick` count; no fabricated positive latency, no false infinite-speed claim. Reject zero/unknown memory or malformed sample; self-test includes zero duration and invalid input. Readings below clock tick are not high-precision performance proof. Metadata additionally prints architecture and observed logical CPU count. No production code changed.
- **Latest implementation run:** [#44384571286](https://github.com/KayzenRoot/stormline/actions/runs/44384571286) **SUCCESS**, 4/4. Windows now 94/94 PASS; Linux/macOS/ASan all PASS. New benchmark and no-display checks execute as real CTests; raw arrays and SHA256 printed during build.

## Measurement protocol / interpretation
- Both modes: `headless` (`HeadlessHost.start/stop`) and `window` (`SdlRuntime.initialize + Window.create/show/destroy + runtime.shutdown`), 30 cold samples in 30 separate exact-binary processes and 30 warm lifecycles in one reused child per mode. Child spawning uses `posix_spawn`/Win32 `CreateProcessW`, no shell, no arbitrary path/command or network.
- Duration: `std::chrono::steady_clock` in **ns** from lifecycle begin through teardown, **excludes process launch**; cold does **not** mean physical OS cold boot or uncached files. Nearest-rank p50 (15th) and p95 (29th) for n=30; no p99 confidence or absolute threshold claim.
- Memory: per-child **process peak** resident bytes from Linux `getrusage.ru_maxrss` (KiB ×1024), macOS `getrusage.ru_maxrss` (bytes), Windows `PeakWorkingSetSize` (bytes). These are not continuous idle RSS, VRAM, fragmentation or a conclusive leak detector. Sanitizer overhead distorts cross-mode and cross-run memory comparisons.
- All 120 sample time/RSS values per runner are printed as `BASELINE_RAW_NS` and `BASELINE_RAW_PEAK_RSS_BYTES` in the linked **build logs**; this table records the observed summary, not substitute invented data.

### Native CTest and executable provenance
| Runner | Job | Full CTest | Sanitizer | Benchmark executable SHA256 |
|---|---|---|---|---|
| Ubuntu 24.04 x86_64, GCC 13.3.0, CMake 3.31.6, 4 logical CPUs | [linux #135085671160](https://github.com/KayzenRoot/stormline/actions/runs/44384571286/job/135085671160) | **95/95 PASS** | Not enabled on this job | `08fa29a875fba31d352f3f0748b87a239832640192434c10b12b81f278e19041` |
| Ubuntu 24.04 x86_64, GCC 13.3.0, 4 logical CPUs | [linux-sanitizers #135085670847](https://github.com/KayzenRoot/stormline/actions/runs/44384571286/job/135085670847) | **95/95 PASS** | **ASan+UBSan enabled**, zero error observed | `53f676120a9ee0b37280ffb480413497742ef1ed88208a6e8303dda647414bf5` |
| Windows x86_64, MSVC 19.52.37029, CMake 4.5.0, 4 logical CPUs | [windows #135085671076](https://github.com/KayzenRoot/stormline/actions/runs/44384571286/job/135085671076) | **94/94 PASS** | No Linux ASan/UBSan claim | `51781225e3e1d372f9d3db33cead2d8a7aaefd6caaba023591ace44d0f2900ed` |
| macOS 15 arm64, AppleClang 17.0.0 (clang-1700.0.13.5), CMake 4.4.5, 3 logical CPUs | [macos #135085670599](https://github.com/KayzenRoot/stormline/actions/runs/44384571286/job/135085670599) | **94/94 PASS** | No Linux ASan/UBSan claim | `ed9be704bbe1151a9198cbc675ebf244436cc7c3bfc7ae8f4d5ef8a53641b143` |

SDL3 runtime reported version **3.4.20** across all. Real CPU SKU, driver/physical GPU and clock behavior under thermal throttling are **NOT_QUALIFIED**. Observed CTest PASS is not G3 full clearance or physical acceptance.

### Observed lifecycle latency (milliseconds)
| Runner/mode | Cold p50 | Cold p95 | Warm p50 | Warm p95 |
|---|---:|---:|---:|---:|
| Linux headless | 0.000611 | 0.000641 | 0.000110 | 0.000230 |
| Linux window | 23.551446 | 24.993117 | 22.388785 | 23.221850 |
| Linux ASan headless | 0.001921 | 0.002579 | 0.000270 | 0.001175 |
| Linux ASan window | 25.791276 | 34.737384 | 19.919000 | 23.991788 |
| Windows headless | 0.001200 | 0.001700 | 0.000200 | 0.000300 |
| Windows window | 65.940300 | 73.838200 | 55.778000 | 69.167400 |
| macOS arm64 headless | 0.001083 | 0.002292 | 0.000125 | 0.000167 |
| macOS arm64 window | 153.328583 | 224.281375 | 32.138208 | 40.129500 |

### Observed process peak memory, max of 30 samples (bytes)
| Runner | Headless cold | Headless warm | Window cold | Window warm |
|---|---:|---:|---:|---:|
| Linux | 4,530,176 | 4,530,176 | 9,478,144 | 11,636,736 |
| Linux ASan+UBSan | 13,402,112 | 13,402,112 | 24,322,048 | 118,005,760 |
| Windows | 8,146,944 | 8,298,496 | 20,566,016 | 21,237,760 |
| macOS arm64 | 3,407,872 | 3,194,880 | 58,146,816 | 56,295,424 |

**Neither cross-OS timings nor peak memory are comparable product benchmarks.** There is no owner-ratified p95/RSS threshold, hardware tier, CPU model, driver/physical session qualification or reliable p99 claim.

## Linux negative no-display proof
On Linux and sanitizer CI, a *dedicated process* removes `DISPLAY` and `WAYLAND_DISPLAY`, selects native `SDL_VIDEODRIVER=x11` (never dummy), verifies headless lifecycle works, and requires SDL video initialize to return typed `SdlError::InitFailed` with `SDL_WasInit(SDL_INIT_VIDEO)==0` within 5,000 ms. Observed **3 ms** Linux, **4 ms** Linux ASan. **Windows/macOS physical missing-display behavior: NOT_QUALIFIED**, not falsely counted PASS; their standard headless child clears both environment variables without proving lack of physical GPU/display.

## Security, audit and checkpoint
- No production code touched; no shell-command interpolation; spawn only self; outputs bounded to 64KiB; read-only CI token, no new secrets/paid runner/install/upload/network/library. Existing pinned SDL FetchContent configuration unchanged.
- SonarCloud and Socket checks returned SUCCESS on tested HEAD; these do not establish security clearance. No known HIGH/CRITICAL introduced by this bounded test-only diff. No performance PASS outside execution correctness.
- **Exact-final-PR-HEAD CI, pt-BR audit, merge and independent checkpoint are PENDING** after this evidence-only update. The numbers above are true **at code HEAD `673ebc8790...`**, not automatically proofs for a later changed HEAD. If CI or docs on this new HEAD fail, correct within same PR before approval.
- Proposed Checkpoint Delta: record PR, exact implementation SHA and binary hashes, four-platform CTest, Linux 5s negative, real raw metrics and limitations, but no changes to core source/ADR/registry/manifest/G3/80 WOs or module completion. Promote only after APPROVED and squash.
