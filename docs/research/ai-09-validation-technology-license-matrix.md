# AI-09 — 2026 Validation, Profiling, Rendering Comparison, Licenses and Threat Matrix

**2026-11-15 | P00 DOCUMENTARY RESEARCH ONLY / NOT IMPLEMENTED | research [#313](https://github.com/KayzenRoot/stormline/issues/313) | NLE-P00-WO-002-AI-09 | future code [#83](https://github.com/KayzenRoot/stormline/issues/83) OPEN/BLOCKED | BASE `84eb288251684ed68311887b1c7901d49c44a2c3`.** Catalog 65/80, formal deps **AI-07 + CORE-06 ONLY**, predecessors ADR-0066/0008 PROPOSED; 64/80 researched at baseline, 16 pending, 80/80 coding WOs BLOCKED. NLE-D009 engine license OPEN.

## 1. Current technical evidence (primary references)
| Technology/standard | Primary source and verified capability | Valid usage and fundamental limit |
|---|---|---|
| CORE-06 v0.1 | [CORE-06 architecture](../architecture/core-06-diagnostics-observability.md), [ADR-0008](../adr/0008-core-06-observability-policy.md) | proposed typed bounded local events, spans, correlation, redaction, crash envelopes; no runtime implementation |
| AI-07 v0.1 | [AI-07 architecture](../architecture/ai-07-transactional-planning-undo.md), [ADR-0066](../adr/0066-ai-07-recoverable-owner-changesets.md) | proposed typed ChangeSet and owner CAS/consent/undo; AI-09 can generate preview only, no commit |
| [Google Benchmark](https://github.com/google/benchmark/blob/main/docs/user_guide.md) | supports `--benchmark_repetitions`, `--benchmark_min_warmup_time`, `--benchmark_enable_random_interleaving`, JSON output, `UseManualTime` and statistical summaries | native microbenchmark framework; measure GPU separately via hardware timestamps, avoid compiler optimization removing workload |
| [Vulkan Profiling Guide](https://docs.vulkan.org/guide/latest/profiling.html) | GPU query pool timestamps and `timestampPeriod`, debug labels and platform GPU tooling | CPU queue submit time not GPU execution time; compare device time domains only when calibrated and available |
| [Vulkan vkCmdWriteTimestamp2](https://docs.vulkan.org/refpages/latest/refpages/source/vkCmdWriteTimestamp2.html) | pipeline stage timestamps with query availability and time domain semantics | async GPU queries, potential timestamp wrap/disjoint, unsupported queue query bits |
| [Tracy Profiler](https://github.com/wolfpld/tracy) | CPU/GPU zones, frame, memory, locks/context switches and screenshots, remote capture features | dev-only candidate with explicit listener privacy; [BSD-3-Clause license](https://github.com/wolfpld/tracy/blob/master/LICENSE) |
| [Perfetto SDK](https://perfetto.dev/docs/instrumentation/tracing-sdk) | in-process tracing, offline trace/SQL analysis | offline candidate, [Apache-2.0 root](https://github.com/google/perfetto/blob/main/LICENSE) and file-level notices; system backend permissions vary |
| [spdlog](https://github.com/gabime/spdlog) | formatted native logs, sinks and bounded/async profiles | MIT at repo; CORE-06 primary logging candidate, not a separate mandatory AI-09 dependency |
| [RenderDoc](https://renderdoc.org/) | GPU frame capture/debugging and API marker inspection | optional development capture, target/platform/driver support must be checked; may contain proprietary assets, shipping not presumed |
| [OpenTelemetry](https://opentelemetry.io/docs/languages/cpp/) | common trace/metric semantics and SDK/exploration | optional trace interoperability, no always-on exporter or remote dashboard required |
| [SSIM](https://ece.uwaterloo.ca/~z70wang/research/ssim/) | structural similarity between images (luminance, contrast, structure) | screen metric only, not semantic/aesthetic/temporal/accessibility guarantee |
| [LPIPS](https://github.com/richzhang/PerceptualSimilarity) | pretrained perceptual feature similarity research | model/checkpoint/asset license and calibration; may not cover small UI/text/temporal defects |
| [OpenCV](https://opencv.org/license/) | image registration/masks/diff, contour and color transforms | Apache-2.0 for current OpenCV family subject to exact-tag review; not a QA authority |
| [Catch2](https://github.com/catchorg/Catch2) | C++ unit/integration test framework | BSL-1.0 per upstream, exact tag/license compatibility review |
| [GoogleTest](https://github.com/google/googletest) | C++ unit/integration harness | BSD-3-Clause per upstream, candidate not installed |
| [Hypothesis](https://hypothesis.readthedocs.io/en/latest/) | property-based testing/shrinking for fixture generators | Python runtime license/embedded toolchain needs separate approval, native alternatives possible |

Sources are about *external technologies*, not Stormline runtime adoption. Do not infer that a named tool's newest GitHub main builds on all targets or comes without other file-level licences.

## 2. Candidate selection and tradeoff matrix, NO ADOPTION
| Candidate | SPDX/review | Strength | Limitations/gate |
|---|---|---|---|
| Pure Stormline typed fixture runner with CORE-06 spans | future code license NLE-D009 OPEN | owner schema, local/offline, source provenance | bespoke validation workload design and deterministic fixture proof |
| Google Benchmark microbench | Apache-2.0 root, exact tag/NOTICE/SBOM | repetitions, warmup, random interleaving, low setup | per-frame visual/game simulation needs separate harness |
| Tracy | BSD-3-Clause root, exact tag/legal | detailed CPU/GPU zones, frame timings, developer flame graphs | sampling/capture overhead and privacy/listener; not a default user telemetry service |
| Perfetto | Apache-2.0 root with third-party notices | offline cross-thread traces and SQL slicing | SDK footprint, clock domains and trace processing memory/cost |
| RenderDoc | project repo license and exact build/package notices to audit | GPU frame capture shader/overdraw/barrier diagnosis | platform restrictions and massive sensitive captured frame data |
| Vulkan timestamp + platform tools | official API, SDK/driver terms | accurate GPU stage time on supported queue, low-level measurement | queries/fence availability and calibrated CPU↔GPU uncertainty |
| SSIM/structural pixel masks | algorithm use/implementation license depends chosen library | fast reproducible screening for same renderer | fails human semantics and temporal ghosting; wrong color space masks defects |
| LPIPS | implementation/model weights/license review | perceptual similarity candidate | model bias, GPU/dependency footprint, UI text/temporal errors and deterministic dependency |
| Manual/heuristic model "looks good" | no real test owner | fast explanation | **not accepted as correctness or independent score** |
| OpenTelemetry C++ | Apache-2.0 root, exact tag | optional standardized metrics for headless | cloud exporter, privacy and added dependency; no mandatory listener |
| OS native ETW/Instruments/perf | OS platform tooling/privacy terms | independent performance oracle | version/SKU entitlement differences and unsupported headless targets |

**No library chosen**. Before future adoption verify exact version, file-level SPDX, transitive SBOM and security advisories, necessary notices, MSVC/Clang/GCC build, Windows/Linux/macOS, optional Web/GPU driver and owner test replay. NLE-D009 engine source license remains OPEN.

## 3. Correctness and statistical fallacies to test
| Threat/fallacy | Protection / independent future oracle |
|---|---|
| Candidate changes tests along with code, then claims success | immutable harness/fixture digest outside candidate branch |
| Incomparable GPU/OS/resolution/VSync/power cap | `NOT_COMPARABLE`, block gain claim |
| Mean FPS improved but p99 worsened | multi-metric tail and frame pacing gate |
| CPU/GPU clocks conflated, uncalibrated timestamps | separate clock domain, uncertainty, query availability |
| One repeated lucky sample chosen | randomized order, all runs retained, CI/statistical intervals |
| Instrumentation changes runtime | diagnostics-off vs dev profile overhead characterization |
| Stochastic TAA/VFX compared one frame | frame sequence alignment with explicit random seeds and masks |
| SSIM high despite invisible HUD | independent semantic UI/accessibility and visual sequence tests |
| Source commit but derived runtime stale | owner source vs renderer/export receipt check |
| Missing trace samples dropped due full ring buffer | `INCOMPLETE_EVIDENCE`, no fake clean pass |
| Malicious prompt or game script executes shell | sandboxed owner fixture with no arbitrary host access |
| Source path/secrets leaked via dump/profiler | CORE-06 bounded redaction, no network default, owner permission |
| Agent automatically lowers quality or test coverage for speed | AI-07 preview only, human consent and no silent test alteration |
| Agent declares gain without actual before/after | require two owner-verified measurement sets and report `INCONCLUSIVE` otherwise |
| Crash/driver device loss in benchmark | invalid/partial run, source traces retained safely, no zeros |
| False negative performance regression due thermal drift | controlled env and paired randomization, intervals, not just percent |

## 4. Decision matrix, open items and acceptance
Choose the simplest toolset that supplies *actual needed evidence*: baseline CORE-06 local events plus trusted QA owner tests; add Tracy for developer CPU/GPU only if measured value; Perfetto for timeline/offline trace if distinct benefit; Google Benchmark only for microbench; Vulkan GPU query for GPU timings; visual comparison library under rights-checked deterministic renderer. **Never build a duplicate telemetry service inside AI-09** or enable always-on profiler/listener.

Candidate sample sizes, p99 confidence, visual tolerance masks, practical regression budgets, latency thresholds, retention and supported hardware tiers require real baseline and owner decision. All 128 A09 test descriptions are future only, not execution. No real frame captures, generated golden image or validated renderer exists.

[Architecture](../architecture/ai-09-validation-optimization.md) · [ADR-0068](../adr/0068-ai-09-evidence-first-human-gated-optimization.md) · [Contracts](../contracts/ai-09-validation-optimization-api.md).
