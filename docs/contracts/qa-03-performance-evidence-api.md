# QA-03 — Typed Performance Experiment, Frame/Memory/Stats and Evidence Semantic API v0.1

**2026-11-16 | P00 DOCUMENTARY RESEARCH | [research #349](https://github.com/KayzenRoot/stormline/issues/349) | NLE-P00-WO-002-QA-03 | future code [#92](https://github.com/KayzenRoot/stormline/issues/92) OPEN/BLOCKED | source HEAD `a81a924b921da629c74ca6d3f4ccb7a2a72e3c19`.** QA-03 order 74/80, formal **QA-02 + CORE-06 + GFX-08 ONLY**, ADR-0076/0008/0021 PROPOSED. Baseline 73/80 researched, 7 pending, 80/80 code packets BLOCKED, 0 ready/approved_adr, all release classes UNDECIDED, engine=false.


**Logical design only: no executable C++ ABI/IDL/wire schema/runtime profiler, GPU timestamps, quality presets, actual hardware trace or CI workflow.** Prefer Stormline-owned versioned records, no vendor-native handles in public API.

## Exactly three FORMAL owner inputs
| Formal | Proposed prior contract | QA-03 consumes; never duplicates |
|---|---|---|
| **QA-02** | [Fixture & evidence API](qa-02-test-fixture-evidence-api.md), ADR-0076 | deterministic `QaFixtureManifestV1/QAInputReplayV1/QAImageDiffReceiptV1` and golden correctness/fidelity; benchmark invalid if content changed unexpectedly |
| **CORE-06** | [Diagnostics architecture](../architecture/core-06-diagnostics-observability.md), ADR-0008 | monotonic typed event/trace/metric facade and local privacy guard; no second global event bus or hidden remote telemetry |
| **GFX-08** | [VFX graph API](gfx-08-vfx-api.md), ADR-0021 | immutable VFX graph/particle budget and simulation counters with bounded field names and effect-set hash, not owner of rendering backend |

GFX-01/03, PLAT-01/02/03/06, CORE-02/03, GAME, DATA, QA-01/04/05 and BIZ-03 are integration/transitive consumers, NOT additional QA-03 formal DAG edges.

## Proposed semantic type inventory
| Type | Mandatory logical fields | Invariant and fail-closed result |
|---|---|---|
| `PerfExperimentRequestV1` | authorized owner/operation, experiment ID, source HEAD, fixture+golden IDs, backend/OS/hardware profile, target quality tier/scene scale, measured phase, run count and data/energy caps | requires owner-ratified tier and original QA02 fixture before any run |
| `PerfSourceLockV1` | git baseline/head/critical file hashes, compiler/flags/linker build/SDK, QA-02 fixture SHA, GFX-08 VFX graph SHA, CORE-06 event schema, backend shader digest | stale/unknown fingerprints => SOURCE_STALE |
| `PerfHardwareProfileV1` | CPU architecture/cores/clock, GPU vendor/device/family/driver+API, physical vs virtual/software, OS kernel/compositor, RAM, CPU/GPU memory unified, display Hz/VRR/HDR, power/thermal sensor support | no device PII exposed publicly; physical flag not inferred from runner label |
| `PerfQualityTierV1` | tier ID revision and owner decision, target resolution+DPR/refresh/cap, quality settings asset tier/shaders/VFX budget/postprocess, equivalence rules from QA-02 | tier not a release class; unknown or changed fidelity -> QUALITY_TIER_UNAPPROVED |
| `PerfWorkloadFixtureV1` | QA-02 original scene/asset/cook rights SHA, category 2D/2.5D/3D/Web, seed/fixed ticks and replay, camera path, duration/warmup, QA-02 correctness receipts, GFX-08 effect graph & population | invalid source/semantic oracle -> RENDER_CORRECTNESS_FAIL |
| `PerfClockDomainV1` | CPU monotonic clock ID/frequency, GPU device queue/time domain/validBits/timestampPeriod or frequency, present event source, calibration pairs/uncertainty | no GPU-to-CPU subtract without calibration or queue matching |
| `PerfFrameRecordV1` | run+frame ID, sim tick, CPU start/update/render/submit monotonic spans, present request/completion/display time if known, GPU queue/pass timestamp refs, validity flags, dropped/duplicated/late classification | signed ns integers or validated float, no negative/NaN and no fake filled gaps |
| `PerfGpuQueryReceiptV1` | API Vulkan/D3D12/Metal/WebGPU, pass/queue ID, query slots/count/fence availability, validBits/frequency/calibration, start/end raw ticks and decoded ns, measurement uncertainty/overhead | UNSUPPORTED for missing optional WebGPU/Metal counters, zero Vulkan bits or invalid fence |
| `PerfMemoryBudgetV1` | source DXGI/Vulkan/Metal, device/heap/node, allocated/resident/current usage/OS dynamic budget/working set, sampler time, unified/CPU shared flag, fragmentation and peak | bytes nonnegative and comparable dimensions, no VRAM allocation = OS budget conflation |
| `PerfVfxScalabilityV1` | GFX-08 graph rev/particle live/emitted/killed/culling/draw/overdraw/VRAM, pass GPU time and CPU simulation time, effect fidelity checks | never silently change effect population or disable fidelity |
| `PerfThermalPowerV1` | sensor origin and permissions, battery/AC/charger, temp/clock/utilization/power W or energy J with confidence, ambient if available, sampled time and throttle state | absent sensor => UNKNOWN, no synthetic joule from TDP |
| `PerfSessionV1` | session/group ID, source/ref hardware and workload, cold/warm profile, start/stop timestamps and reason, ordered raw frame series hash, dropped sample count, profiler on/off, background load and clock/temperature | invalidate partial runs or report them explicitly, never silently discard poor frames |
| `PerfStatisticsV1` | quantile definition, raw sample count/independent session count, p50/p95/p99 ns, mean/SD/CV, stutter ratio and frame thresholds, sample quality/missing fraction, confidence interval method & effect size | p99 unsupported when inadequate independent sample count, intervals not fake precision |
| `PerfPairedRegressionV1` | base/current Git heads, paired hardware/quality/scene/driver runs, randomized ABBA block IDs, effect median/percent/absolute ns, bootstrap CI and multiple comparison policy, failure reason | INCOMPARABLE for hardware/scene drift, uncertainty overlap => INCONCLUSIVE |
| `PerfTraceEvidenceV1` | CORE-06 local trace source+hash, consent/redaction, timestamp clocks, compressed bytes/retention, GFX/VFX markers, raw frame/memory/power files and quality receipt links | private paths/assets/traces not uploaded to untrusted CI |
| `PerfBudgetDecisionV1` | owner ratified tier limits and uncertainty, required p95/p99/stutter/memory/safety checks, pass/fail/inconclusive/unsupported, no HIGH/CRITICAL, DoD and required independent reviewer verdict | no “PASS” from planned or uncalibrated targets |
| `PerfErrorV1` | SOURCE_STALE/NO_PHYSICAL_GPU/CLOCK_DOMAIN_UNKNOWN/GPU_QUERY_UNSUPPORTED/QUERY_UNAVAILABLE/VRAM_BUDGET_INVALID/THERMAL_UNSTABLE/TRACE_DROPPED/INSUFFICIENT_DATA/QUALITY_TIER_UNAPPROVED/RENDER_CORRECTNESS_FAIL/COST_GUARD/SECURITY_BLOCKED | typed stop, no silent fallback |

## Future semantics, NOT implemented
| Proposed operation | Authority | Preconditions / results |
|---|---|---|
| `lock_perf_inputs(request)` | QA-03 | owner-approved QA02 fixture + quality tier, source/head and rights |
| `resolve_perf_hardware_and_clocks()` | QA-03 + PLAT/GFX integration | real device/driver and timestamp query capabilities or UNSUPPORTED |
| `plan_perf_matrix()` | QA-03 | bounded hardware/scenes/tiers/run count/retention, budget R$0 |
| `warmup_perf_workload()` | QA-03+QA02 runner | predeclared cold/warm and thermal checks, finite timeout |
| `capture_perf_frame_trace()` | CORE-06 data owner, QA-03 consumer | ordered monotonic frame series and loss count |
| `resolve_gpu_query_with_fence()` | GFX-03/RHI backend owned | valid queue clock duration and calibration receipt only |
| `sample_memory_budget()` | GFX/PLAT backend | dynamic heap/node usage; shared RAM documented |
| `record_vfx_scaling()` | GFX-08 owner, QA-03 consumer | graph/particle fidelity counts, CPU+GPU cost per scene |
| `report_power_and_thermal()` | PLAT sensors/QA-03 optional | actual sensor or UNKNOWN |
| `compare_benchmark_sessions()` | QA-03 stats | p50/p95/p99/bootstrap paired and source evidence; inconclusive when data weak |
| `compare_visual_fidelity()` | QA-02 owner | approved goldens/semantic result gate, no perf PASS if wrong picture |
| `emit_perf_evidence_bundle()` | QA-03 under CORE-06 privacy | actual raw traces SHA, conditions, stats, failures, costs |
| `approve_quality_tier()` | **owner only** after objective review | versioned decision; not in P00 |
| `promote_public_release()` | **BIZ-03 only** | no QA-03 authorization or P00 public MVP |

## Invariant: statistics and time
- Frame intervals use **same source/event type and clock domain** and full raw series; CPU render complete, GPU pass elapsed, frame submitted, actual screen present are *different observables*. Correlated CPU/GPU time only with multiple calibrated samples. GPU queues can overlap and execution durations are not additive frame wall time.
- Choose quantile method (nearest rank or type-7 interpolation) and freeze; p99 needs enough raw frames **AND independent sessions** to justify uncertainty. A “0.1% low FPS” rate requires explicit inverse/time definition, not blindly `1 / p99` labeling. Collect power, thermal and profiled/nonprofiled context.
- If QA-02 semantic fidelity/golden fails, status RENDER_CORRECTNESS_FAIL regardless of raw speed; no adaptive quality tier lower than owner constraint. All thresholds and hardware-release classes currently UNDECIDED.
- Absence/permissions of WebGPU timestamp or hardware counters -> UNSUPPORTED, never assume frequency. Missing sensor -> UNKNOWN, not zero. On unified GPUs, memory budget and CPU RAM can represent shared bytes and must not be double-counted.
- Privacy: default local-only trace, explicit owner telemetry consent, redaction of paths/screen/input, restricted retention, no root/privileged process attach on public forks and no cloud spend.

[Architecture](../architecture/qa-03-performance-lab-scalability.md) · [future benchmark](../research/qa-03-benchmark-statistical-protocol.md) · [ADR-0077](../adr/0077-qa-03-statistical-performance-tier-policy.md).
