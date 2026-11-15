# EDIT-07 — Reproducible PIE, Profiler Overhead, Debug/Asset Trace and Crash Benchmark Protocol

**P00 protocol, NOT EXECUTED | 2026-11-15 | [research #276](https://github.com/KayzenRoot/stormline/issues/276) | code #74 OPEN/BLOCKED.** No editor, binary, debugger, profiler, GPU capture, crash handler, platform test or measured performance data exists.

## 1. Manifest and conditions
Pin engine/editor/CORE-06/EDIT-01 commit, Event/Span/Counter/Asset correlation schema, compiler/optimization flags and PDB/dSYM/DWARF symbols, OS/kernel/display server, CPU/RAM/SSD, GPU/driver/API, audio device/sample rate, asset manifests and licenses, project ProjectId and failing AssetId/revision, deterministic seed, CORE-04 TickId, thread ids, clock domain, sampling/trace settings, privacy policy and exported data hash. Compare release profile with **OFF, MINIMAL, SAMPLED, DEEP** tracing; perform >=3 independent runs/seeds, >=30 warmups and >=1000 measurements for p99. Preserve raw traces/data. Native OS/GPU/headless/Web must be measured independently; CI does not replace physical device and driver proof.

## 2. Workloads and fixtures
| Fixture | Reproducible scenario | Measurements |
|---|---|---|
| DBG-01 | Empty project with one corrupt/incompatible asset, one valid AssetId/revision | project->subsystem->asset causal chain, source map/correlation correctness |
| DBG-02 | GAME-02 script breakpoint/step/watch on exact source revision | latency, stale revision behavior, no side effects |
| PIE-01 | Frozen small 2D project, open/run/pause/stop/restart 100 times | session start time, retained data mutation, handle leaks, cancellation |
| PIE-02 | 3D/VFX/audio multi-owner preview with denied file/network operations | sandbox isolation, world/game authority, cleanup |
| CPU-01 | 2D baseline, mid-tier ARPG 10k VFX, 3D 100k objects with 8/32 threads | frame/tick/job p50/p95/p99, RSS, drops and profiler overhead |
| GFX-01 | Native Vulkan/D3D12/Metal per supported device, 100/1k render passes | render-graph navigation, GPU timing availability, capture size/latency |
| AUD-01 | 32/128/512 DSP nodes, 48/96 kHz, variable callback quantum | XRUN/underrun, no callback allocation/lock/IO and snapshot overhead |
| MEM-01 | 1k/10k/100k AssetIds with allocation/VRAM tags | tag aggregation/query, pagination, memory overhead, no raw memory |
| LOG-01 | 1k/100k/1m events, spam/drop and malformed fields | CORE-06 queue cost, dropped count, UI responsiveness and memory |
| CRASH-01 | isolated child crash/OOM/disk full, symbolication availability | local envelope, no upload, sensitive field handling and recovery |
| PRIV-01 | secret-laden fake paths/tokens/chat prompts/assets, cross-project MCP | redaction correctness, denied actions and bundle readback |
| WEB-01 | WebGPU feature gating and no timestamp-query environment | honest unsupported status, browser privacy, no remote listener |

## 3. Metrics, correctness and observer effect
- Profiling OFF/MINIMAL/SAMPLED/DEEP: delta CPU/frame p50/p95/p99, memory RSS/VRAM, disk and network bytes (expected zero without explicit permission), dropped events, log queue size and throttling.
- PIE: cold/warm start, input-to-paint, stop/cancel p99, crash recovery, process/OS handle leaks and frozen source digest check after every run.
- Breakpoint/step/watch: hit-to-pause delay, source-map precision, step TickId/frame distinction, watch read-only proof and no arbitrary-eval path.
- Asset incident: build SHA, scoped ProjectId, subsystem/OperationCode, exact AssetId/revision, DATA-02 provenance and source locator. Any absent owner-approved correlation type => **unsupported**, cannot pass acceptance.
- CPU/GPU: per-producer sequence, time-domain uncertainty, GPU queue timestamp calibration and capture size/latency, device generation/fence.
- Audio: callback deadline, XRUN, sample-clock epoch, counter snapshot overhead, no callback allocation/locks/IO, never infer audible latency from scheduling.
- UX/accessibility: keyboard-only incident path, screen reader roles/focus, high-contrast labels, native UIA/AX/AT-SPI and Web feature availability.

## 4. Fault/security injection
Inject lost GPU/device epoch, job cancellation/deadlock, stale source and missing AssetId, replay with modified build/seed/asset, malformed trace and high-cardinality labels, log flood/disk full, preview script attempt to access network/file/microphone/process, watch expression attempting function call and secrets read, unauthorized cross-project MCP, crash in isolated child, raw dump export request, missing symbols, revoked consent, race between stop and capture. Confirm owner-side scope/epoch fences, redaction/no upload, last-good data/source integrity, resource cleanup and no crash handler/audio callback unsafe allocations or locks. System crash may prevent flush; mark expected limitations.

## 5. Comparators and exit
Compare stdlib logging, spdlog + Tracy, spdlog + Perfetto under same instrumented workload and exact build/target, with user/permission/network settings explicit. Do not enable remote services to benchmark local profiling. Candidate SDF must **prove** extra actionable correlation compared with simple baseline at acceptable overhead or be dropped.

All numerical budgets are TBD until owner-approved target tier, workload, OS/GPU/driver and DoD. No fabricated claim that Stormline is faster than other engines, zero-cost profiling, perfect crash capture or GPU timing parity. Future benchmark samples: **0**. E07 future tests: **128 NOT EXECUTED**.

[Architecture](../architecture/edit-07-debug-profiling-preview.md) · [Technology matrix](edit-07-debug-profile-technology-license-matrix.md) · [128 tests](../testing/edit-07-acceptance-matrix.md).
