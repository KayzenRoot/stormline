# ADR-0068 — Evidence-First Agent Validation and Human-Gated Optimization Proposals

**2026-11-15 | P00 DOCUMENTARY RESEARCH ONLY / NOT IMPLEMENTED | research [#313](https://github.com/KayzenRoot/stormline/issues/313) | NLE-P00-WO-002-AI-09 | future code [#83](https://github.com/KayzenRoot/stormline/issues/83) OPEN/BLOCKED | BASE `84eb288251684ed68311887b1c7901d49c44a2c3`.** Catalog 65/80, formal deps **AI-07 + CORE-06 ONLY**, predecessors ADR-0066/0008 PROPOSED; 64/80 researched at baseline, 16 pending, 80/80 coding WOs BLOCKED. NLE-D009 engine license OPEN.

**STATUS: PROPOSED / NOT RATIFIED / NOT ADOPTED / NO ENGINE CODE AUTHORIZATION.**

## Problem
AI agents may eventually validate Stormline scenes, games and export builds, profile their rendering/runtime behavior, compare candidate optimizations and suggest source revisions. Without strict evidence and permission separation, agents can fabricate "performance gains", compare incompatible hardware, hide functional/visual regressions, upload sensitive captures, rewrite source or remove test coverage without consent. CORE-06 diagnostic evidence and AI-07 transactional owner ChangeSets are only research proposals at present.

## Proposed decision
1. **Formal dependencies exactly AI-07 + CORE-06**. CORE-06 remains sole owner of diagnostic events/metrics/traces, build+frame/tick/job correlation, privacy/redaction/sinks. AI-07 remains sole versioned owner-aware ChangeSet preview/commit/undo/partial recovery coordinator. QA, GFX, CORE-04, GAME, AUDIO, DATA, EDIT-07, AI-01/06/04 are downstream integration/transitive authorities, not added formal DAG edges.
2. **AI-09 is read/measure/propose by default**: orchestrates bounded authorized test scenarios in isolated fixtures, reads redacted owner diagnostics, records signed/checksummed evidence manifests as future hypotheses and compiles optional typed AI-07 **PREVIEW ONLY** optimization plan. It never independently writes source, auto-approves or applies, merges a PR, changes test baselines, exports private traces or uploads crash data.
3. **Correctness before performance**: any functional, security, accessibility, source or asset integrity regression blocks "optimization pass" even with improved p99. Tests cannot be disabled or golden screenshots silently updated. A flaky or unsupported test becomes INCONCLUSIVE/UNSUPPORTED, not PASS.
4. **Before/after comparability contract** pins source/build SHA, compiler flags, OS/kernel, hardware CPU/GPU/driver, power/thermal governor, resolution, render/AA/HDR profile, frame cap, scene/seed/asset digests, test/metric version, profiler sampling, time domains and fixture license/rights. Unmatched conditions => `NOT_COMPARABLE` unless stratified explicit analysis, not favorable comparison.
5. **Independent measurements and statistics**: control warmup/cold run, randomized interleaving, repetitions, raw sample retention, p50/p95/p99 and confidence/variance plus frame pacing/outliers. Predeclare primary metrics and non-regression tolerances; missing samples, dropped trace events and GPU clock-domain mismatch ⇒ INCONCLUSIVE. No invented benchmark thresholds or "99% faster" from one run. GPU timestamps from actual query/availability separate from CPU.
6. **Visual correctness not one number**: versioned exact/similarity goldens only on supported calibrated comparable render profiles. SSIM and perceptual metrics are screening, not substitutes for semantic UI/lighting/accessibility/temporal checks. Use time-aligned frame sequences for TAA/VFX/motion; no universal pixel-perfect across GPUs.
7. **CORE-06 privacy/local-first**: only redacted bounded offline evidence by default. Crash memory, secret source, logs or GPU capture can expose private project content; export requires explicit appropriate grant/consent and separate owner handling. No always-on network profiler or cloud analytics.
8. **Human approval mandatory for proposed source optimization**: AI-07 ChangePlan exact source revision, owner diff, expected risk and rollback/cancellation attached to report. Trusted AI-06 approval is transitive owner responsibility and cannot be minted by AI-09 report/model text. After approval future executor would run separate WO with tests and independent readback. AI-09 must not automatically apply candidate.
9. **A/B benchmark candidate technology is UNSELECTED**: evaluate Google Benchmark (Apache-2.0), Tracy (BSD-3-Clause), Perfetto (Apache-2.0), spdlog (MIT), OS/GPU profilers RenderDoc, Vulkan timestamps, Web performance interfaces and optional visual SSIM/LPIPS under exact-tag license/security and platform validation. Existing CORE-06 choice is PROPOSED, not approved. NLE-D009 remains OPEN; no library installed.
10. **Report distinguishes measured from inferred**: evidence URLs/hashes and typed metric availability, confidence, statistical vs practical significance, negative regressions, sample sizes, tool overhead, profiling environment, complete audit trace and owner source bounds. The agent may recommend "no change" if evidence weak; optimization need not be forced.
11. **Risk and reproducibility**: P00 documentary LOW; eventual test runners that execute hostile games/scripts or produce privileged optimization source or network exports HIGH_ASSURANCE. OS isolation, remote CI, user data, tests on real machines and profiler integrations require separate approved code ADR and rollback.
12. Exactly **128 A09-T001..A09-T128 FUTURE / NOT EXECUTED**; ADR-0068 remains PROPOSED, future code [#83](https://github.com/KayzenRoot/stormline/issues/83) OPEN/BLOCKED and all other implementation WOs blocked. No production-like benchmark, tested optimizer or tool chain exists.

## Alternatives rejected/deferred
| Alternative | Why it fails or is deferred |
|---|---|
| LLM reads logs and asserts speedup from text summary | no independent measurable evidence, prompt injection and summary hallucination |
| Auto-apply fastest proposed patch | hidden correctness/security/quality regressions, violates human consent and AI-07 source owner |
| Update golden images to candidate automatically | masks actual rendering regressions |
| Mean FPS or single screenshot only | hides frame pacing, p99 spikes, temporal effects, UI text errors |
| Compare different GPU drivers, resolution, VSync and power states unqualified | confounding, false causality |
| Always-on Tracy, Perfetto and crash upload in release | privacy, frame-time perturbation, disk/CPU/network and licensing burden |
| SSIM/LPIPS score alone defines quality | color/semantic/temporal/accessibility defects can survive high score |
| Direct GPU/CPU process memory read by agent | secrets and privilege exposure; CORE-06 owns bounded redacted capture |
| Google Benchmark one repetition and no warmup | noise and nonrepresentative statistical inference |
| Existing CI docs green as evidence of runtime quality | CI is documentary only; no engine exists |
| Remote mandatory benchmark SaaS | violates offline-first/no paid requirement and data locality |
| AI-09 creates independent source edit/journal/undo engine | duplicates AI-07 owner and permits bypass |
| Unbounded benchmark/trace capture | denial of service and source/PII leakage |
| Baseline and candidate using altered tests | unfalsifiable and susceptible to cherry-picking |
| Promise zero instrumentation overhead | unmeasured; CORE-06 docs explicitly forbid assumption |

## Ratification criteria
Before any code: explicitly approved metric/measurement schema and comparison policy, versions/platforms/licenses, QA owner fixture API, isolation and redaction, AI-07 preview-only boundary, independent human consent, test coverage and 128 future scenarios implemented/passing, actual baseline vs candidate hardware measurements with confidence/tier thresholds, security and architecture objective review. No approved decision changed by this proposal. No release class approved.

[Architecture](../architecture/ai-09-validation-optimization.md) · [Contracts](../contracts/ai-09-validation-optimization-api.md) · [Research matrix](../research/ai-09-validation-technology-license-matrix.md).
