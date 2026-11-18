# NLE-CORE01-QUAL-001 — Exploratory Runtime Baseline Evidence

**Status:** 4/4 NATIVE CI VERIFIED ON EVIDENCE-PRIOR HEAD / FINAL EVIDENCE-ONLY COMMIT CHECKS PENDING / NOT MODULE QUALIFICATION.  
**Risk:** STANDARD. **Scope:** test-only, owner-authorized 2026-11-18.  
**Main/base:** `80f1610f4ac6da8b8daf7f98bbb4ef209963ad6c`.  
**Tested implementation HEAD:** `673ebc8790c974c5cf14af663545108e31798e68` (C++ code frozen). **Latest evidence-prior HEAD:** `4ee390fb96b7f9eb38f72b948da0369e377b5ead`.  
**PR:** [#479](https://github.com/KayzenRoot/stormline/pull/479) Draft; not merged.  
**Native CI on latest evidence-prior HEAD:** [run #44387891808](https://github.com/KayzenRoot/stormline/actions/runs/44387891808) `SUCCESS` (4/4 jobs, full logs verified). Prior implementation run [#44384571286](https://github.com/KayzenRoot/stormline/actions/runs/44384571286) was also 4/4 SUCCESS.  
**Docs Validation on latest evidence-prior HEAD:** [run #44387891902](https://github.com/KayzenRoot/stormline/actions/runs/44387891902) `SUCCESS`. Prior run [#44384571437](https://github.com/KayzenRoot/stormline/actions/runs/44384571437) also SUCCESS.

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
- All 120 paired time/RSS samples per runner are printed as `BASELINE_RAW_NS` and `BASELINE_RAW_PEAK_RSS_BYTES` in the linked **build logs**; this table records the observed summary, not substitute invented data.

### Latest executed Native CTest and executable provenance (run #44387891808)
| Runner | Job | Full CTest | Sanitizer | Benchmark executable SHA256 |
|---|---|---|---|---|
| Ubuntu 24.04 x86_64, GCC 13.3.0, CMake 3.31.6, 4 logical CPUs | [linux #135097318194](https://github.com/KayzenRoot/stormline/actions/runs/44387891808/job/135097318194) | **95/95 PASS** | Not enabled on this job | `08fa29a875fba31d352f3f0748b87a239832640192434c10b12b81f278e19041` |
| Ubuntu 24.04 x86_64, GCC 13.3.0, 4 logical CPUs | [linux-sanitizers #135097318124](https://github.com/KayzenRoot/stormline/actions/runs/44387891808/job/135097318124) | **95/95 PASS** | **ASan+UBSan enabled**, zero error observed | `53f676120a9ee0b37280ffb480413497742ef1ed88208a6e8303dda647414bf5` |
| Windows x86_64, MSVC observed compiler build 195136260, CMake 4.5.0, 4 logical CPUs | [windows #135097317479](https://github.com/KayzenRoot/stormline/actions/runs/44387891808/job/135097317479) | **94/94 PASS** | No Linux ASan/UBSan claim | `28a42ffc4b56e3517f6a1709ea6ae21d2b483961cd9e5c8e0ebf501eb4f9eb42` |
| macOS 15 arm64, AppleClang 17.0.0 (clang-1700.0.13.5), CMake 4.4.5, 3 logical CPUs | [macos #135097318411](https://github.com/KayzenRoot/stormline/actions/runs/44387891808/job/135097318411) | **94/94 PASS** | No Linux ASan/UBSan claim | `cb915cb9bc8cf24724387f178aee3322dba0e3cd7dd66a5ef3c7cd26fdc5758f` |

SDL3 runtime reported version **3.4.20** across all. Real CPU SKU, driver/physical GPU and clock behavior under thermal throttling are **NOT_QUALIFIED**. Observed CTest PASS is not G3 full clearance or physical acceptance.

### Observed lifecycle latency (milliseconds)
| Runner/mode | Cold p50 | Cold p95 | Warm p50 | Warm p95 |
|---|---:|---:|---:|---:|
| Linux headless | 0.000591 | 0.000721 | 0.000080 | 0.000130 |
| Linux window | 16.229971 | 21.413473 | 14.976803 | 22.780761 |
| Linux ASan headless | 0.001957 | 0.002862 | 0.000271 | 0.001297 |
| Linux ASan window | 25.446631 | 33.407488 | 20.945814 | 22.304871 |
| Windows headless | 0.001600 | 0.002100 | 0.000200 | 0.000400 |
| Windows window | 60.466800 | 78.958500 | 53.655900 | 63.875500 |
| macOS arm64 headless | 0.000750 | 0.002250 | 0.000125 | 0.000167 |
| macOS arm64 window | 141.245792 | 180.362833 | 30.077459 | 95.787750 |

### Observed process peak memory, max of 30 samples (bytes)
| Runner | Headless cold | Headless warm | Window cold | Window warm |
|---|---:|---:|---:|---:|
| Linux | 4,558,848 | 4,558,848 | 9,658,368 | 11,714,560 |
| Linux ASan+UBSan | 13,365,248 | 13,365,248 | 24,477,696 | 117,809,152 |
| Windows | 8,179,712 | 8,318,976 | 20,455,424 | 20,967,424 |
| macOS arm64 | 3,309,568 | 3,145,728 | 56,934,400 | 59,473,920 |

**Neither cross-OS timings nor peak memory are comparable product benchmarks.** There is no owner-ratified p95/RSS threshold, hardware tier, CPU model, driver/physical session qualification or reliable p99 claim.

## Linux negative no-display proof
On Linux and sanitizer CI, a *dedicated process* removes `DISPLAY` and `WAYLAND_DISPLAY`, selects native `SDL_VIDEODRIVER=x11` (never dummy), verifies headless lifecycle works, and requires SDL video initialize to return typed `SdlError::InitFailed` with `SDL_WasInit(SDL_INIT_VIDEO)==0` within 5,000 ms. Observed **2 ms** Linux, **5 ms** Linux ASan on latest run #44387891808; both well below 5,000 ms. **Windows/macOS physical missing-display behavior: NOT_QUALIFIED**, not falsely counted PASS; their standard headless child clears both environment variables without proving lack of physical GPU/display.

## Security, audit and checkpoint
- No production code touched; no shell-command interpolation; spawn only self; outputs bounded to 64KiB; read-only CI token, no new secrets/paid runner/install/upload/network/library. Existing pinned SDL FetchContent configuration unchanged.
- SonarCloud and Socket checks returned SUCCESS on tested HEAD; these do not establish security clearance. No known HIGH/CRITICAL introduced by this bounded test-only diff. No performance PASS outside execution correctness.
- **Exact-final-PR-HEAD native CI and Docs, pt-BR audit, merge and independent checkpoint are PENDING** following this evidence-only amendment. The latest table is from actual run #44387891808 against HEAD `4ee390fb...`, with unchanged C++ implementation first committed by `673ebc8790...`; it is not automatically proof of the resulting Evidence-only commit. If final-head CI or Docs fail, correct in this same WO/PR before approval.
- Proposed Checkpoint Delta: record PR, exact implementation SHA and binary hashes, four-platform CTest, Linux 5s negative, real raw metrics and limitations, but no changes to core source/ADR/registry/manifest/G3/80 WOs or module completion. Promote only after APPROVED and squash.

## Final-readiness audit evidence, pending final-commit revalidation
The evidence-prior run #44387891808 has all four native jobs `conclusion=success` and full CTest counts **95/95 Linux, 95/95 Linux ASan+UBSan, 94/94 Windows, 94/94 macOS**, zero observed sanitizer errors, and Docs Validation #44387891902 SUCCESS. Ubuntu x86_64, Windows x86_64 and macOS arm64 all report SDL 3.4.20. Linux missing-display typed InitFailed measured 2 ms (normal) and 5 ms (sanitized). The original Windows `0 ns` test-oracle defect was corrected as a censored observation, not engine code. The **current modification is solely this final evidence readback**; re-run CI for the resulting exact SHA and keep PR Draft until every check and audit is green.
