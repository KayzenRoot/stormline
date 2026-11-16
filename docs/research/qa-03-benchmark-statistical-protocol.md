# QA-03 — Future Statistical Hardware/Quality Tier Benchmark and Regression Protocol

**2026-11-16 | RESEARCH PROTOCOL ONLY, NO MEASUREMENTS OR RUNS.** [Research #349](https://github.com/KayzenRoot/stormline/issues/349), code [#92](https://github.com/KayzenRoot/stormline/issues/92) OPEN/BLOCKED, base `a81a924b921da629c74ca6d3f4ccb7a2a72e3c19`. Formal **QA-02 + CORE-06 + GFX-08 only**. This file contains **zero actual frames, FPS values, GPU query data, VRAM/power numbers, confidence intervals or hardware tests**.

## Goal and experiment design
Compare p50/p95/p99 frame/presentation intervals across **identical** original QA-02 2D/2.5D/3D/Web work fixtures, approved runtime/quality tier and driver/hardware classes. Capture CPU/GPU/present/memory/thermal independently with CORE-06 metrics and GFX-08 effect occupancy, and include correctness/visual fidelity. No invalid mixed-vendor benchmark or absent-GPU green. Future base-to-head regression must be reproducible and statistically defensible with actual independent hardware sessions.

## Future hardware/target matrix (none currently acquired/tested)
| Profile | Approved hardware/source conditional | Evidence before label comparison |
|---|---|---|
| PERF-SW-CPU | software-only/headless CPU reference of approved renderer | CPU simulation workload and software pixels, **not** GPU frame/present FPS |
| PERF-WIN-IGPU | owner-controlled affordable real Intel/AMD integrated GPU Windows | actual CPU/GPU/driver/RAM/shared memory/refresh/VRR and present via PresentMon |
| PERF-WIN-DGPU-ENTRY | owner-controlled low VRAM discrete AMD/NVIDIA Windows | DXGI dynamic budget and D3D12/Vulkan query, actual display pacing |
| PERF-LNX-IGPU | Linux Mesa integrated hardware on approved distro/compositor | Vulkan timestamps, memory budget, Wayland/X11 actual presentation |
| PERF-LNX-DGPU | Linux real AMD/NVIDIA GPU, pinned vendor driver/VRAM | Vulkan+GPU timestamp and actual thermal under nonprivileged capture |
| PERF-MAC-ARM | actual macOS Apple Silicon native arm64 | Metal counter feature set, unified memory, MTL working set, power/thermal sensors with permissions |
| PERF-MAC-INTEL | conditional Intel real Mac if owner selects eligible OS floor | native x86_64 vs translated Rosetta separated; no hosted-only substitute |
| PERF-WEB | Chrome/Firefox/Safari approved real browser GPU tiers | WebGPU `timestamp-query` optional/quantized or surrogate labeled, performance.now/rAF throttling, WebGL2 fallback distinct |
| PERF-MOBILE | Android/iOS only after future owner scope ratification | not mandatory P00 or hidden QA-03 dependency |
| PERF-THERMAL | same owner-approved physical machine AC/battery/ambient sequence | true sensor origin, clock/temperature/energy; no fake watt estimate |
| PERF-VFX | deterministic GFX-08 particle graph 2D/2.5D/3D profile | live/spawn/draw/overdraw and visibility correct by QA-02 |

## Experiment locks, sampling and statistical equations
- **Immutable source+content**: Git head compiler/shader, QA-02 original fixture/golden raw SHA, scene 2D/2.5D/3D category, seed/camera/tick/action trace/asset and VFX-08 graph ID/count. Same resolution, upscaler, HDR/exposure, culling/occlusion/shadows/VFX population per profile. Independently certify actual image/scene correctness before considering performance.
- **Environment**: OS build/GPU vendor/PCI device/driver/CPU/APU/NUMA/RAM/unified, display Hz/VRR/vsync/latency, GPU power state and clocks, battery AC, background processes/compositor, CPU affinity/scheduler if allowed, build debug/release and sanitizer validation separately. Note if sensors missing.
- **Phase**: cold startup (I/O/PSO compilation) measured separately; warm cache/graph stable steady run. Predefine warmup count/time/thermal stabilization and abort/flag if unstable, not “wait until output passes”. Never cherry pick a fast area of scene/camera trace.
- **Sampling**: raw ordered `t_i` for valid actual presented frames from the same monotonic source, `d_i=t_i-t_{i-1}` ns. Invalid negative/missing/duplicate frame gets typed failure/classification, not filled with mean. p50/p95/p99 quantiles of `d_i` by declared method (nearest rank or type-7), report ms with unit and sample count. Raw fps rate = count / elapsed time **only as complementary**, not replacement for p99 frame time or actual input-to-display.
- **Regressions**: for each matched hardware/driver/quality/scene run A and B in randomized ABBA sequences across independent sessions and, if possible, machines. Compute paired deltas `Δ_p = p_current - p_baseline` in ms and ratio%; report confidence interval from **block/session bootstrap** (blocks longer than measured autocorrelation window), not IID bootstrap over every adjacent frame. Control multiple hypothesis risk across scenes/p95/p99, record pre-registered margins and sample/exclusion criteria. Insufficient independent repeats -> INCONCLUSIVE. p99 requires adequate tail sample counts and confidence, **5 repeats alone cannot justify precise p99**.
- **Thermal**: staged power supply, clocks, ambient and on-device sensors as reported, throttling/temperature/time windows. Never imply full CPU/GPU render equivalence for low energy if battery status different. GPU workload pauses/counters may change energy and clocks; sample profiler-off reference.
- **Proposed target frame durations**: 60Hz ~16.67ms, 30Hz ~33.33ms, 120Hz ~8.33ms are arithmetic **illustrations only**, **not approved engine DoD/tier budgets**. Minimum acceptable p95/p99 and stutter counts await actual hardware calibration and owner decision.

## Candidate protocol cases, future only
| Bench | Future measurement | Gate and evidence |
|---|---|---|
| PERF-B01 | 2D 10k sprites/tilemap original scene at fixed viewport | draw batching+CPU and GPU pass/present, correctness before speed |
| PERF-B02 | 2.5D isometric scene parallax/transparency | overdraw, sort cost, input-to-present pacing |
| PERF-B03 | 3D PBR 100-material original test library and shadows | GPU pass duration, PSO/shader warmup, VRAM budget |
| PERF-B04 | GFX-08 particle graph 1x/2x/4x populations (bounded) | GPU simulation/VFX overdraw/frame and correct visual output |
| PERF-B05 | GPU geometry/meshlet/occlusion LOD scaling | real visible object count and drawcall overhead |
| PERF-B06 | shader/texture stream cold/warm and scene transition | stutters, IO, residency, dynamic budget change |
| PERF-B07 | native Windows PresentMon + D3D12 query | CPU/render/present clocks/pacing + frequency/calibration |
| PERF-B08 | Linux Vulkan query + VK_EXT_memory_budget | validBits/timestampPeriod/queue and heap usage |
| PERF-B09 | native Apple Metal counters/recommendedMaxWorkingSetSize | real Apple Silicon and optional Intel, shared-memory caveats |
| PERF-B10 | WebGPU optional timing + browser rAF and visibility | privacy-quantized GPU vs browser surrogate, no false GPU Pass |
| PERF-B11 | idle/stabilized/thermally throttled 3D sustained | real temp/power/clock and p95/p99 drift |
| PERF-B12 | profiler instrumentation before/after and sampled trace cap | overhead and lost events separately |
| PERF-B13 | scripted wrong-image/perf improvement adversarial fixture | QA-02 fidelity fail overrides speed-up |
| PERF-B14 | paired release candidate regressions with order randomization | independent A/B sessions, quantile confidence, p-value uncertainty |
| PERF-B15 | affordable hardware and public CI R$0 boundary | no unapproved paid runner/host and signed cost class |
| PERF-B16 | complete evidence audit and owner tier ratification | risk/DoD/scene rights/actual hardware proof, QA-03 code separate |

## Bench validity and data controls
- Restrict file paths, timestamps and sensor device fingerprint in public reports; raw trace SHA and access ACL, no remote continuous monitoring by default. Avoid posting private shaders or original game assets with unverified redistribution rights. No benchmark with unknown proprietary sample.
- Test harness can report `UNSUPPORTED`, `INCOMPARABLE`, `THERMAL_UNSTABLE`, `CLOCK_INVALID`, `TRACE_DROPPED`, `RENDER_CORRECTNESS_FAIL`, `INSUFFICIENT_DATA`, `COST_GUARD` instead of a fake 0% regression. QA-02 golden assertions required first. CPU/GPU pass sums don't measure overall frame pipeline due to overlap.
- Future `PerfBenchmarkReceiptV1` must provide build SHA/scene+VFX graph original rights, actual hardware/OS/driver/physical vs software flag, clock domain and valid bits, observed memory budget, session conditions, ordered raw intervals and independent replications, stats method p50/p95/p99/CI, actual CPU/GPU/VRAM/thermal readings (or missing marker), perf sampling overhead, quality owner decision and independent objective pt-BR audit.

[128 future cases](../testing/qa-03-acceptance-matrix.md) · [architecture](../architecture/qa-03-performance-lab-scalability.md) · [tools/license matrix](qa-03-profilers-gpu-counters-license-cost-matrix.md).
