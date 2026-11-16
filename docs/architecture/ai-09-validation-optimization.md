# AI-09 — Evidence-First Automated Validation & Human-Gated Optimization Architecture v0.1

**2026-11-15 | P00 DOCUMENTARY RESEARCH ONLY / NOT IMPLEMENTED | research [#313](https://github.com/KayzenRoot/stormline/issues/313) | NLE-P00-WO-002-AI-09 | future code [#83](https://github.com/KayzenRoot/stormline/issues/83) OPEN/BLOCKED | BASE `84eb288251684ed68311887b1c7901d49c44a2c3`.** Catalog 65/80, formal deps **AI-07 + CORE-06 ONLY**, predecessors ADR-0066/0008 PROPOSED; 64/80 researched at baseline, 16 pending, 80/80 coding WOs BLOCKED. NLE-D009 engine license OPEN.

## 1. Objective and inviolable boundary
Acceptance **"Relatório com antes/depois, evidência reproduzível e aprovação humana."** In future, approved agents should execute bounded visual/functional/performance validation on isolated rights-cleared fixtures and produce an objective baseline-vs-candidate report; propose, not apply, safe optimization deltas for explicit human review. A report must distinguish raw measurements, observed uncertainty, functional correctness, environmental comparability, permissions, source changes, rollback feasibility and owner receipts.

**AI-09 is a validation orchestrator and suggestion service, not a benchmark itself, renderer, physics engine, compiler, test framework, source committer, agent superuser or always-on profiler.** Never mutate canonical source from "optimization" without a separately trusted, consented AI-07 ChangeSet and owner authority. No autonomous merge, CI bypass, destructive change, exploit/secret collection or network export by default.

## 2. Formal dependency graph and owners
Only **AI-07 + CORE-06** are *formal* dependencies:
- **CORE-06** owns typed `DiagnosticEventV1`, `TraceSpanV1`, `CounterSampleV1`, `CorrelationContextV1`, `DiagnosticExportV1`, bounded privacy-aware local evidence, frame/tick/job correlation, monotonic clocks, profile availability and diagnostic drops. It NEVER promises a complete trace when sampling or ring-buffer overflow occurred. AI-09 reads owner-approved redacted diagnostics; it cannot add an independent always-on monitoring daemon.
- **AI-07** owns typed `ChangeSetDraftV1`, `ChangePlanV1`, `ChangeApplyReceiptV1`, semantic diff, source revision CAS, owner journal, undo/partial recovery and approval binding. AI-09 may **propose** a typed optimization plan or compare an isolated *already authorized* candidate. It cannot apply a plan or sign human approval; potential future application goes through AI-07 and transitive AI-06/AI-01 trusted permissions/owner JIT enforcement.
- Transitive/integration owners **not formal new edges**: CORE-04 clock/tick, CORE-03 scheduler, CORE-02 memory, GFX-01/GFX-03 GPU, AUD-01 realtime audio, GAME gameplay, TWO 2D/3D, DATA-04/05 scene/cook, QA-01/02/03 test fixtures/benchmarks, EDIT-07 debug UI, AI-08 authoring, AI-04 MCP adapter, PLAT target exporters. Absent owner test/metric ==> `UNSUPPORTED`, not fabricated PASS.
- Diagnostic transport and proposal workflow remain locally usable offline, model/provider independent. A model may summarize *cited verified evidence* and suggest hypotheses; no LLM-based score or invented trace accepted.

## 3. Validation orchestration and comparison lifecycle
```text
trusted actor goal + permitted ProjectId / source baseline / target
    |
validate fixture manifest + capability profiles + policy + evidence budgets
    |
CORE-06 redacted local diagnostic snapshots (build/clock/frame/tick/job)
    |
owner QA scenarios: unit/integration/playback/visual/audio/asset/benchmark
    |
evidence store [source+build+machine+target+seed+capture manifest hashes]
    |
candidate run on isolated branch/worktree/read-only snapshot (not main)
    |
same suite/profile and documented paired randomization + enough repeats
    |
compare correctness FIRST, then statistical performance/visual deltas
    |
AI-09 typed ValidationReportV1: measured before/after, uncertainty,
     wins/losses, regression severity, missing data, provenance
    |
optional proposed AI-07 OptimizationChangePlan (PREVIEW ONLY)
    |
explicit human approval remains outside AI-09; no self-apply
```
A baseline *must* be runnable and internally valid on the same platform/owner profile. If configurations differ (driver, power limit, build flags, resolution, color management, debug vs release, data set), report `NOT_COMPARABLE` rather than invent cross-device performance gain. Candidate benchmark change cannot weaken the correctness tests being compared; require independent frozen QA harness and fixed artifact fingerprints.

## 4. Reproducibility and evidence integrity contract
**Required per sample:** Source Git SHA, build digest/config, compiler/toolchain, ABI, target OS/arch/CPU/GPU/driver/firmware relevant features, logical and physical frame dimensions, resolution/swapchain/HDR/color space, refresh/VSync/cap/frame generation/DLSS/FSR/TAA profile, scene fixtures/seed/data digest/license, test/metric definitions, profiler version, CPU/GPU clocks/time domain, warmup profile, run order, ambient/thermal/power settings when measurable, fps cap/background load, actual raw samples with timestamps and drop/availability counters.

A report uses actual immutable evidence references/checksums and privacy/redaction policy. SHA-256 proves byte integrity, NOT trusted signer identity; report authenticity requires separately approved signing/provenance/owner verification. Retain source and candidate artifacts under bounded access/size/retention, no unbounded crash dump upload. Evidence generated from mock data must be labeled **SYNTHETIC**, not a validated engine performance result.

## 5. Measurement, clocks and statistical integrity
- Frame time distribution in **milliseconds** based on presented complete frames: frame p50/p95/p99, slow-frame ratio, p99.9 only with adequate samples, stutter cadence/time series, variance and long-tail confidence. **Do not convert mean FPS into proof of frametime performance**; use actual presentation timestamps when possible. Frame-time and render-submit times are different.
- GPU query pool time measures GPU execution on its supported time domain; CPU wall time measures host duration. Cross-domain CPU/GPU alignment demands explicit calibration/uncertainty metadata. Missing calibrated timestamps ⇒ keep separate axes, NOT fabricate combined timeline. Device loss/timestamp overflow/disjoint frames are invalid or partially available, not zeros.
- Worker/job, allocation/VRAM, I/O/streaming, load latency, audio callback underrun and CPU/RSS are owner-provided counters with units+availability. Do not block realtime audio to collect data; counting audio underruns alone doesn't prove perceptual audio integrity.
- Use **controlled repeated tests** with fixed workload and randomized interleaving (A/B or A/B/B/A blocks), appropriate warmup and cold-run study separately. Report raw distributions, median, p95/p99, confidence/bootstrap intervals where meaningful, run-to-run variance and sample count. Multiple comparisons and cherry-picking require predeclared primary outcomes and hold-out regression suite.
- For p99/p99.9 adequate sample count and confidence are necessary; percent improvement based on insufficient tail samples is `INCONCLUSIVE`. Timeouts/drops are censored data and must be reported, never silently removed. One sudden large improvement due to different GPU settings is `NOT_COMPARABLE`.
- Instrumentation overhead must be separately measured **with diagnostics disabled vs enabled**, since CORE-06 logging/tracing can perturb the thing observed. No claim of zero overhead before measurement. Benchmark tool Google Benchmark supports repetitions/warmup/random interleaving, CPU vs manual time; Vulkan timestamps require actual GPU query evidence.

## 6. Functional and deterministic validation
Source owner correctness first: stable IDs, scene refs, source revision parity and asset/scene semantics; command undo/redo (AI-07), deterministic tick/replay where CORE-04 supports, game UI/input/gamepad keyboard/touch, script/physics boundary cases, platform build/launch, serialization/migration/crash recovery, permissions and no source corruption. Unavailable owner harness => UNSUPPORTED/NOT_EXECUTED.

Metamorphic checks on candidate: same scene/seed should preserve required invariants, physics precision/tolerances, camera/animation/lighting behavior, input accessibility, asset privacy/licensing, audio timing and memory/allocator safety. Flaky tests are `FLAKY/INCONCLUSIVE`; **never label a test PASS solely because one retry passed**. Tests that change scene state run only on ephemeral owner-approved fixture sandbox; no live project contamination.

## 7. Visual test policy (no blind pixel perfection)
- **Ground truth**: engine capture with pinned geometry, camera, asset SHA, resolution, GPU/driver, render pipeline/shader, color primaries, transfer function/tone mapping, exposure, AA/TAA jitter/time history, MSAA, sample count, HDR/SDR and screenshot output encoding.
- Exact pixel hash can check deterministic **same-renderer** reference with fixed seed, but across GPUs/drivers/compiler scheduling pixel equality may be invalid. Use structural diff/edge or region-masked thresholds and SSIM perceptual similarity only as *screening*; these do not prove physically correct lighting, absence of ghosting or legible HUD, and can mask thin UI defects.
- For temporal effects (TAA, motion blur, particle VFX, framegen, animation) compare aligned **sequences**, latency and stutter/ghosting masks, not one convenient frame. Tone-mapping/alpha premultiplication, transparent outputs and dynamic resolution require explicit profile.
- High-risk visual regressions (UI invisible, wrong hitbox, flicker, text clipping, shader artifacts, accessibility motion) fail functional/owner semantics even if SSIM high; manual signoff optional only as an additional independent gate, never replaced by model.
- A golden image is an artifact that must be versioned, rights-cleared and owned by a test profile. Test updates to golden set cannot be made automatically to make tests green.

## 8. Optimization proposal classes and safety
AI-09 may recommend hypotheses grouped by **renderer** (GPU-bound passes, overdraw/shader variants, asset streaming), **runtime** (job stalls/alloc pressure), **audio** (underrun, audio thread contention), **data** (cook latency/cache invalidation), **world/physics** (iteration, culling), **UI** (layout/text shaping) and **test build** (compiler flags). Suggestions are evidence-linked **proposals**, not a command to mutate. Classify:
- `NO_CHANGE`: no measured meaningful issue or correctness regression blocks changes;
- `RECOMMEND_ONLY`: cite trace and expected mechanism plus risk/cost, no source edits;
- `AI07_CHANGESET_PREVIEW`: typed owner-safe diff requiring separate human approval with source revision and rollback class;
- `BLOCKED`: data insufficient, flaky, security/privacy problem, unsupported owner, unmeasured target or owner access denied.
No hidden disabling of tests, lowering quality tiers, removing features, changing license, exporting source or broad cleanup as "optimization". A perceived speedup with worse accessibility/visual correctness cannot be promoted as improvement.

## 9. Security, privacy, fail-safe
CORE-06 local/offline diagnostics and export are opt-in. Deny arbitrary process memory/crash dump reads or external listeners; never export private project paths, secrets, prompts, audio samples or unredacted source. Sample redacted metric fields pre-capture and pre-export. Bound trace bytes/samples, label cardinality, GPU capture size, disk retention, CPU budget and retries. Missing permissions/trace losses/clock mismatch lead `INSUFFICIENT_EVIDENCE`, not silent pass. Running untrusted scenes/scripts requires sandboxed owner test process; UI/LLM injection cannot create tool privileges or sign an approval. No paid external telemetry. Cancel tests without claiming a side effect was undone.

## 10. Future acceptance
Three separately pinned tiered scenarios (2D UI/animation, 3D lighting/VFX, headless simulation/audio) with baseline/candidate on same hardware and workload; record actual visual/functional regression, CPU/GPU/frame p50/p95/p99 and confidence, source/target integrity, reproducibility manifest, redacted CORE-06 trace and either genuine `NO_CHANGE` or carefully scoped AI-07 proposed optimization for human acceptance. Approval proof is trusted user action on exact plan, NOT model natural language. 128 unique future A09 scenarios, official tools, security and real OS hardware benchmarks **NOT EXECUTED** in P00.

[ADR-0068](../adr/0068-ai-09-evidence-first-human-gated-optimization.md) · [Technology/license matrix](../research/ai-09-validation-technology-license-matrix.md) · [Typed API](../contracts/ai-09-validation-optimization-api.md) · [128 future tests](../testing/ai-09-acceptance-matrix.md) · [Benchmark](../research/ai-09-validation-benchmark-protocol.md).
