# AI-09 — Future Reproducible Functional/Visual/Performance A-B Benchmark Protocol

**2026-11-15 | P00 DOCUMENTARY RESEARCH ONLY / NOT IMPLEMENTED | research [#313](https://github.com/KayzenRoot/stormline/issues/313) | NLE-P00-WO-002-AI-09 | future code [#83](https://github.com/KayzenRoot/stormline/issues/83) OPEN/BLOCKED | BASE `84eb288251684ed68311887b1c7901d49c44a2c3`.** Formal deps AI-07 + CORE-06 only, ADRs 0066/0008 PROPOSED; 64/80 research at baseline, 16 pending, all 80 code packets BLOCKED, no engine; NLE-D009 OPEN.

**FUTURE ONLY. No compiled Stormline engine, no CORE-06 tracing or AI-07 ChangeSet runtime, no actual GPU/CPU samples, no benchmark, no visual captures or optimization measured.** Numerical target budgets, practical thresholds and technology selection remain UNDECIDED.

## 1. Falsifiable question and proof hierarchy
Can an agent *actually measure* source-equivalent functional/visual/gameplay correctness, frame-time and resource effects before and after a candidate optimization, with reproduced environment and human approval of any source ChangePlan? Hard gate order: (1) ownership/security/privacy/legal; (2) functional/visual/accessibility correctness; (3) comparable measured environment; (4) statistically and practically meaningful performance; (5) human proposal review. A faster candidate that fails an earlier gate is NOT an optimization success.

`PROPOSED` means recommendation only, `APPROVED` requires trusted human action on exact plan, and `APPLIED` requires a *separate* AI-07 owner source receipt and new independent after-run. Do not conflate these.

## 2. Pin reproducibility manifest
| Dimension | Mandatory fields |
|---|---|
| Git and build | source baseline SHA, candidate SHA, tests/goldens separate revision, build binary hash, compiler/link flags, sanitizer mode, branch/PR provenance |
| Scene and rights | source scene/project/AssetId IDs and revisions, fixture seed, source content/golden digests, synthetic/rights-cleared media, game behavior/profile and schema |
| Hardware | CPU model/microcode, GPU model/driver/firmware, memory/storage size, OS/kernel/arch, battery/AC mode, power governor, thermal telemetry availability |
| Renderer | API/backend, resolution scale, HDR/SDR color/tone mapping, AA/TAA history seeds, MSAA, VSync/cap, frame generation/upscaling, GPU clock period and uncertainty |
| Timing | CORE-06 span schema, CPU monotonic clock units, GPU timestamp query availability/time domain, frame/tick/job correlation, calibration error and dropped count |
| Tooling | exact Google Benchmark/Tracy/Perfetto/GPU tool tag, build flags, sampling period, enabled probes, SBOM/SPDX/NOTICE/security advisories |
| Capture | actual baseline+candidate raw sample sequences, capture files/hashes, screenshot sequence and golden region mask, retention/privacy/redaction |
| Consent | verified actor/project scope, source proposal AI-07 plan digest, current AI-06 grant/policy, separate human decision receipt when relevant |

## 3. Workload fixtures, rights-cleared and reproducible
| Tier | Benchmark workload | Correctness and performance gates |
|---|---|---|
| F0 | 2D camera/tilemap/UI/Unicode/focus + animations | scene/AssetId integrity, text accessibility and frame pacing |
| F1 | ARPG 3D dense geometry, shadows, lighting, instancing, VFX, GPU texture streaming | true GPU query and CPU job, color/golden temporal frames and 1% slow frames |
| F2 | headless fixed-tick simulation with AI/jobs and realtime audio event fixture | deterministic replay/owner digest, job wait and audio underruns without GPU |
| F3 | shader compile, material graph, large 100k asset stream/cook | source/cooked output revisions, cache cold/warm and IO tail |
| F4 | adversarial stutter with periodic main thread stalls and GPU shader cache misses | synthetic injected hitch detectable in p99 and trace correlation |
| F5 | multi-actor 32 agents/editors, repeated AI-07 preview/conflict/undo | no source overwrite, trace completeness and grant scope |
| F6 | low-memory/low-VRAM and disk/network unavailable sandbox | fail-safe and truthful unsupported/incomplete evidence |
| F7 | temporally changing TAA/particles/motion blur/tonemapping | aligned frame sequence, independent dynamic/semantic ROI |
| F8 | synthetic prompt injection/private resource/hostile crash dump | zero unauthorized source/filesystem/secret upload, bounded logs |
| F9 | unsupported Web GPU/Metal/Vulkan feature combinations | honest availability and no fake calibrated times |

Each fixture must be actually supported by owner modules and source verified; P00 has no runnable fixture. No real user projects, restricted IP or remote uploads allowed.

## 4. Statistical experiment design
- Define **primary outcome** (e.g., frame p99) before measurement, secondary p50/p95, CPU/GPU per-pass, RSS/VRAM and functional gate list. Report practical deltas and confidence intervals. Do not treat single p99 difference as proof.
- Warmup pipeline/cache and separate cold-start. Randomize A/B order with interleaved paired blocks to mitigate temperature/load drift. At least five independent repetitions as *study minimum*, but **quantile confidence needs many frame samples**, not just five trials.
- Store *all* valid and censored frames, outliers, runtime failures, dropped samples, sampling frequencies and thermal/power telemetry; do not remove slow runs silently. P99.9 only when enough samples with uncertainty; otherwise INCONCLUSIVE.
- Use appropriate pairing/bootstrapping with independent run blocks rather than treating millions of correlated frames as independent samples. Account for statistical dependence/autocorrelation, multiple comparisons and controlled false positive risk. Report raw units ms, MB, W, counts and fraction, and uncertainty bound.
- Compare diagnostic-off versus enabled/profiler capture independently to characterize **observer effect**. CPU time vs wall-clock vs GPU query are not interchangeable.
- If target/driver/renderer/tick/AA differs, report NOT_COMPARABLE or stratified analysis, not unqualified % speedup. Human signoff remains required despite measured win.
- Quantitative pass/fail thresholds and hardware tiers **to be adopted after a real baseline study**, never invented in this research.

## 5. Future benchmark cases and evidence
| ID | Planned experiment | Oracle and measurements |
|---|---|---|
| V-B01 | Source/build/fixture preflight | immutable source harness SHA, rights, zero hidden incompatibility |
| V-B02 | CORE-06 disabled/low/high tracing overhead | p50/p95/p99 frame delta, CPU/RSS, dropped event counts |
| V-B03 | Vulkan GPU/CPU clock split, unsupported queries | validated query timestamps vs independent CPU monotonic |
| V-B04 | Tracy vs Perfetto offline correlation | identifiable frame/job/GPU events, overhead and privacy |
| V-B05 | 2D UI/text/golden tests | pixel profiles, semantic text/focus, frame pacing |
| V-B06 | 3D dense lighting/VFX shadow sequence | HDR color/tone mapping and aligned temporal images |
| V-B07 | Headless simulation/audio performance | CPU tick consistency, job stalls, callback underruns |
| V-B08 | Asset streaming/cook memory and IO | owner source/cooked digest, cold/warm, p99 IO |
| V-B09 | Recovery on crash/GPU device loss/disk-full | actual error/status, no fabricated clean trace |
| V-B10 | Frozen functional harness before/after | regression count and deterministic owner source state |
| V-B11 | 32-agent operation/trace ACL | zero cross-project data exposure and unauthorized edit |
| V-B12 | Paired randomized A/B candidate performance | raw full distributions, confidence/thermal/observer bias |
| V-B13 | False positive score injection/candidate tampering | reject changed golden/fake metric/checksum |
| V-B14 | LPIPS/SSIM optional image assessment | independent semantic ROI/temporal failures even with high similarity |
| V-B15 | AI-07 proposed ChangePlan preview/human review | exact-source plan digest, source unchanged until approval |
| V-B16 | Independent replay of Evidence Bundle | same pinned data and verified trace/cook/approval references |

## 6. Report receipt prototype (not implemented)
```text
A09BenchmarkReceiptV1 {
  git_base_sha, git_head_sha, frozen_test_harness_sha,
  tool_schema_source_fingerprints, scene_asset_rights_revisions,
  build_id_compiler_flags_target_arch, hardware_cpu_gpu_driver_kernel,
  power_thermal_vsync_render_aa_hdr_profile, fixture_seed_data_digest,
  core06_schema_trace_digest_dropped_events_clock_domains,
  baseline_run_hashes, candidate_run_hashes, raw_ordered_samples,
  sample_count_valid_invalid_censored, warmup_method_run_order,
  frame_p50_p95_p99_ms, cpu_gpu_mem_vram_audio_io_metrics,
  confidence_interval_method_result, primary_endpoint,
  visual_reference_golden_hashes_temporal_align_roi,
  functional_security_accessibility_regressions,
  instrumentation_overhead, actual_owner_source_digest,
  ai07_proposed_plan_digest_and_state, verified_human_approval_ref,
  privacy_redaction_license_sbool, report_status, reviewer_verdict
}
```
All fields are candidate evidence schema and **NOT MEASURED** in P00. A source file added under docs cannot substitute for real trace samples.

## 7. Redaction and acceptable failure
CRASH/RAW dumps and GPU captures can contain confidential source, media, file paths/PII; require project-authorized strictly local encrypted/retained fixture or reject; do not upload automatically. If evidence source absent, trace dropped, disjoint GPU domain, cross-hardware changes, flaky test or incomplete correctness => explicit `INCONCLUSIVE`, `NOT_COMPARABLE`, `UNSUPPORTED` or `BLOCKED` with no misleading success. No paid tool required.

[Google Benchmark guide](https://github.com/google/benchmark/blob/main/docs/user_guide.md) · [Vulkan profiling](https://docs.vulkan.org/guide/latest/profiling.html) · [Perfetto](https://perfetto.dev/docs/instrumentation/tracing-sdk) · [ADR-0068](../adr/0068-ai-09-evidence-first-human-gated-optimization.md).
