# ADR-0077 — Evidence-First Performance Lab, Statistically Valid Frame Budgets and Quality Tiers

**2026-11-16 | P00 DOCUMENTARY RESEARCH ONLY | [research #349](https://github.com/KayzenRoot/stormline/issues/349) | NLE-P00-WO-002-QA-03 | future coding [#92](https://github.com/KayzenRoot/stormline/issues/92) OPEN/BLOCKED | BASE main `a81a924b921da629c74ca6d3f4ccb7a2a72e3c19`.** QA-03 order 74/80. Formal dependencies **QA-02 + CORE-06 + GFX-08 ONLY**, ADR-0076/0008/0021 PROPOSED. Initial registry 73/80 researched, 7 pending, 80/80 code WOs BLOCKED, executor_ready=0, approved_adr=0, release_class UNDECIDED all, engine_implemented=false, NLE-D009 source license OPEN and NLE-D013 no public MVP.


**STATUS: PROPOSED / NOT RATIFIED / NOT IMPLEMENTED / NO BENCHMARK MEASURED.**

## Problem
Stormline targets visually rich 2D, 2.5D and 3D content on affordable hardware. Frame rate averages conceal stutter; rendering and presentation are asynchronous; OS GPU allocations aren't fixed VRAM entitlements; cooling and clock behavior change during tests; false confidence can arise from 5 runs, shared video frames or cloud VMs without physical GPU. A quality-tier claim made without a stable scene, trace provenance and QA-02 fidelity oracle is not reliable.

## Proposed decisions, subject to owner approvals
1. **Exact formal dependencies: QA-02 + CORE-06 + GFX-08**. QA-02 fixture+golden+state/integration correctness, CORE-06 typed monotonic local diagnostics, GFX-08 VFX graph/particle simulation and budgets; predecessor ADR-0076/0008/0021 all PROPOSED. QA-01/GFX-01/03/PLAT/QA-04/05 and others only transitive/integration; do not rewrite catalogue DAG.
2. **Typed raw event/experiment ownership:** QA-03 owns benchmark plan/statistics/quality-tier comparison, CORE-06 owns low-overhead event schema and export privacy, QA-02 owns rights-cleared fixtures and golden correctness, GFX-08 owns effect graph constraints. Use pure versioned logical receipts; no third-party tracing types in public engine ABI or MCP contracts.
3. **Three independent timings** always distinguished: CPU simulation/render/submit wall span with thread work, GPU queue/pass start/end timestamp (supported calibrated per backend, fence readback), and actual present/display interval where observable. Standard FPS and profiler UI ≠ proof of user-visible presentation smoothness.
4. **GPU timestamp capability limits**: Vulkan `timestampValidBits >0` and `timestampPeriod` convert to time; separate queue domains/calibrations/wrap. D3D12 timestamp query heap + `GetTimestampFrequency/ClockCalibration` and optional copy-queue support. Metal counterSets + `MTLCounterSampleBuffer` and sampling boundary, clock correlation. WebGPU `timestamp-query` optional and privacy-quantized, no permission/feature -> UNSUPPORTED; CPU surrogate separately labeled, never passed as actual GPU timestamp. No physical hardware result claimed by standard hosted CI.
5. **Memory budgets dynamic, not installed VRAM**: Vulkan `VK_EXT_memory_budget` approximate heap budget/usage, DXGI `QueryVideoMemoryInfo` current OS budget and usage, Metal `currentAllocatedSize/recommendedMaxWorkingSetSize` and unified memory. Track resident/workset, peak allocation, leaks, back-pressure and fragmentation, distinguish CPU RAM+unified GPU shared pages, no false double-count.
6. **Well-powered/statistically honest experiments**: deterministic QA-02 original scene/seed and actual quality tier locked. Warmup and cold-start separate; record frame-level ordered timestamps, profiler-on/off overhead, thermal and power context, valid samples and dropped frames. Multiple independent runs, paired ABBA/randomized order, block bootstrap across sessions (account for time correlation), p50/p95/p99 with explicit quantile formula and uncertainty/effect size. Never infer p99 significance from five summary runs or falsely treat each frame as independent.
7. **Owner-calibrated quality tiers only**: LOW/BALANCED/HIGH/CINEMATIC candidate scene presets with explicit feature/texture/VFX/shadow/upscaler/readability changes and 2D/2.5D/3D visual fidelity QA-02 acceptance. Target 60 Hz ~16.67ms, 30 Hz ~33.33ms are arithmetic examples only, not adopted target budgets nor mandatory release class. Infer neither FPS from GPU query alone nor “better game” from lower resolution/disabled effects without comparative golden and gameplay semantics.
8. **R$0 and secure profiling**: default locally capturable nonprivileged tracing with optional Tracy (BSD-3-Clause candidate), Google Benchmark (Apache-2.0 candidate), PresentMon (MIT candidate Windows ETW), RenderDoc (MIT own app only), Xcode Instruments/Metal developer tooling (Apple terms), Linux perf_event_open CAP/perf_event_paranoid limitations, browser DevTools/WebGPU privacy limits. Pin exact version/license; no paid SaaS/GPU cloud, automatic privileged driver, screenshots of commercial games, secret/PII capture, hidden telemetry, or unbounded trace upload. Free compute on public standard runners does not certify physical GPU, thermal or artifact storage quota.
9. **Accuracy beats pass rate**: energy sensors/power and thermal readings must be real and tagged; no guessed Joules from TDP, no interpolation across missing/invalid counters. If hardware pool insufficient or system/driver class mismatched, output INCOMPARABLE/INSUFFICIENT_DATA/UNSUPPORTED, not PASS.
10. **128 future tests and documentary stage**: exactly 8×16 Q03 future scenarios; all NOT EXECUTED. No actual benchmark or GPU data, no true CPU performance, no HW budget or source code approved. Keep all 80 code WOs BLOCKED and ADR-0077 PROPOSED; no public MVP.

## Alternatives deferred or rejected
| Shortcut | Why unsafe/incomplete |
|---|---|
| Frame FPS mean as only metric | hides long-frame stutter/pacing and duplicates |
| Compare p99 of 1,000 adjacent frames as 1,000 independent experiments | autocorrelation and one-session thermal/driver confounding |
| All frames timestamped by `steady_clock` as GPU elapsed | CPU submission/asynchrony not GPU execution |
| Sum GPU pass times as unique frame GPU latency | async overlap and multiple queues can double count |
| Compare raw Vulkan timestamp bits across unsynchronized queues | different epoch, wrap and clock domains |
| Treat Chrome `timestamp-query` always available | optional and intentionally privacy-quantized |
| Treat installed VRAM capacity as application budget | OS budget dynamic, unified memory shared |
| Evaluate graphics speed by disabling every quality feature | fails QA-02 fidelity/readability |
| Declare tier requirements before acquiring any reference hardware | no empirical evidence |
| Accept GPU render results from unaccelerated hosted runner as physical device | software/VM ≠ actual GPU, thermal and display |
| Force paid benchmark hardware or proprietary cloud | GOV-003 R$0, owner approval absent |
| Enable system-wide profiler root/capture of unrelated process | privacy and security |
| Send continuous user machine data to centralized service | CORE-06 local/offline privacy ownership |
| Ignore missing frame timestamps, test crashes or profiler dropped events | makes slow or invalid runs look good |
| Mandatory Tracy SDK in public engine ABI | violates type independence and library licensing/adoption |
| Overwrite approved golden baseline to make perf faster | QA-02 owns intentional change and review |
| Mark code WOs approved after eight docs + 128 future tests | planning evidence is not implementation |

## Future decision gates
Owner ratifies exact hardware/OS+driver+quality tiers, baseline thresholds and statistical effect policy, profiling compiler flags/tracing overhead, test time/energy measurement safety, source license and original scene rights, free hardware availability, release class/DoD after independent code gates. Current P00 only research/ADR proposal.

[Architecture](../architecture/qa-03-performance-lab-scalability.md) · [license/cost research](../research/qa-03-profilers-gpu-counters-license-cost-matrix.md) · [semantic contract](../contracts/qa-03-performance-evidence-api.md).
