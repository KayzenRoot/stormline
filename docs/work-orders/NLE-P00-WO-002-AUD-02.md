# Research Work Order — NLE-P00-WO-002-AUD-02

**2026-11-14 | Research issue #198 | Future coding issue #53 OPEN/BLOCKED**  
**BASE main:** `90125e6885603ad260f0d355067991699577a9f6`. **P00 DOCUMENTATION ONLY**. Risk LOW documentary, future ELEVATED for realtime/geometry/HRTF/importer/stream+privacy. Release class UNDECIDED; engine license NLE-D009 OPEN.

**RESEARCH RESULT APPROVED/MERGED:** [PR #199](https://github.com/KayzenRoot/stormline/pull/199), final audited HEAD `5ddd0fb31fdcb0fb245ffd59e611d8966cfc6820`, [Docs Validation #43656427484](https://github.com/KayzenRoot/stormline/actions/runs/43656427484) SUCCESS job #132635839155, objective pt-BR audit #6886329762, normal squash main `cf781105e653a67d646aa97ff3ec72a8124c2686` and main readback. Separate checkpoint PR still requires own CI/audit/squash/readback. 128 runtime tests NOT RUN; coding #53 BLOCKED.

## OBJECTIVE
Specify original engine-owned 2D/2.5D/3D spatial acoustics: listener/source pose, headphone HRTF and validated SOFA datasets, speaker panning, direction/directivity/Doppler, geometry- and material-dependent occlusion/transmission, early reflections and late room reverberation/portal/pathing, bounded non-RT ray tracing and offline bakes, validated streaming and versioned/source-accurate AUD-01 render plans. Preserve GAME/NET authority, source rights, security, headless and original measurable benchmark scope.

## CONTEXT
At start, AUD-01 issue #195 and research PR #196 plus checkpoint PR #197 objective-audited and squash merged, main SHA `90125e6885603ad260f0d355067991699577a9f6`. Exactly **35/80 documentary researches**, **45 pending**, including historic CORE-04 research-status gap. No executable engine/SDK/game, **all 80** coding WOs `BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`, executor_ready=false, approved_adr=null. AUD-02 catalog order 36; mandatory dependencies AUD-01+WORLD-02 research only, NO runtime. Future coding #53 OPEN/BLOCKED.

## SCOPE
Exactly eight new research-only Markdown docs: original spatial/acoustic architecture, **ADR-0039 PROPOSED**, upstream technology/legal matrix (Steam Audio Apache2, libmysofa BSD3, Embree Apache2, OpenAL Soft LGPL 2+ with separate SADIE HRTF license, Resonance Audio archived Apache2, Project Acoustics archived docs/code with binary license caveats), typed versioned API/receipts/errors, **128 prospective test matrix**, reproducible acoustic CPU/IR/perceptual/privacy benchmark protocol, this Work Order and Evidence Bundle. Separate GitHub research issue/branch/PR, exact-final-HEAD Docs Validation, pt-BR objective audit and normal squash/readback, then distinct checkpoint PR with independent exact-head CI/audit/squash/readback.

## OUT OF SCOPE
C++ engine, SDK installs, public runtime HRTF/audio callback, external asset/music/voice dataset import, real acoustic ray tracing/bake, GPU accelerated wave solver, AI gameplay audio detection, microphone/headscan without consent, source rights decision, generalized DSP graph AUD-03, audio device/mixer AUD-01, dialogue/music AUD-04, proprietary/paid services, unrelated cleanup and direct coding ticket #53 activation. No automatic scope expansion to perfect hearing/AAA superiority.

## FILES / SOURCES TO READ
Strict source hierarchy: `docs/11-checkpoint.md` > `docs/10-decisions-ledger.md` and approved ADRs > `docs/03-scope.md` > `docs/09-definition-of-done.md` > `docs/04-architecture.md` > `docs/02-requirements.md` > `AGENTS.md` > `docs/product/module-catalog.md` > `docs/queue/implementation-registry.json` > `docs/queue/work-orders/AUD-02.md`. Existing [AUD-01](../architecture/aud-01-audio-device-mixer.md), [SIM-02](../architecture/sim-02-physics-3d.md), [WORLD-03](../architecture/world-03-spatial-index-streaming.md), [WORLD-04](../architecture/world-04-terrain-environment.md), GFX-04 and DATA-05 documented source boundaries. Official vendor links in technology matrix. Future coding source paths/methods and actual commands TBD only after approved code Work Order.

## REQUIREMENTS
GOV-001..005, CAP-003 audio/spatial quality, original 2D/2.5D/3D native Win/Linux/macOS, Web capability fallback and headless CPU; no public MVP, free GitHub CI, solo governance. Objective acceptance **"Cenário de posições/obstáculos com áudio validado e custos medidos"** FUTURE, not met by research docs. User data/biometric-like personalized HRTFs explicitly authorized or never collected, original audio geometry/IR fixture rights, accessible speaker/mono/dialogue intelligibility.

## ARCHITECTURE RULES
AUD-01 owns PCM voice/device/bus, realtime sample clock/callback and mix; AUD-02 computes bounded spatial profile/render plan and uses immutable acoustic geometry from WORLD-02, cell leasing and epochs WORLD-03, terrain/material WORLD-04, validated source/cook DATA-03/04/05, optional SIM-02 collider version; CORE-03 bounded off-RT ray/path jobs, CORE-02 buffers, CORE-04 tick, CORE-05 coords, CORE-06 safe metering. AUD-03 generic DSP convolution/advanced effects, AUD-04 music/dialogue future. No second mixer or callbacks doing raytracing/HDF5 decode/FFT planning/log/alloc/IO. Unknown/unloaded geometry ≠ no wall; GAME/NET own gameplay and client acoustic source privacy. No native vendor pointers in public semantic ABI.

## CONSTRAINTS
No source/SOFA data/vendor SDK adopted, no runtime tests, 128 cases FUTURE/NOT EXECUTED, no native/Web validation, no real HRTF subjective test or sound/IR benchmark, no numerical budgets claimed. Apache/BSD/LGPL notices and HRTF dataset individual rights need pinned tag/SBOM review; no paid services or CodeRabbit, no force push or ruleset bypass, no external mandatory human reviewer. ADR-0039 remains PROPOSED.

## ACCEPTANCE CRITERIA
- [ ] Exactly eight Markdown docs in research PR, all Source Pack links/catalog/registry consistent.
- [ ] ADR-0039 PROPOSED, upstream license matrix names data rights and archived project caveats, no tech adoption.
- [ ] Versioned typed listener/emitter/room/portal/surface/IR/HRTF/source epoch/RT plan contracts with error semantics and privacy.
- [ ] 128 future tests and full repeatable source/acoustic/CPU/perception benchmark protocol explicitly **NOT EXECUTED**.
- [ ] GitHub Docs Validation SUCCESS at **final exact research HEAD**, objective pt-BR audit APPROVED and no known HIGH/CRITICAL in scope, normal squash merge and readback.
- [ ] SEPARATE checkpoint PR same WO with own final-head CI/audit/squash/readback, research count **36/80 (45%)**, pending **44** incl CORE-04 gap, zero runtime.
- [ ] AUD-02 future coding #53 remains OPEN/BLOCKED; **all 80 coding packets** still `BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`, `executor_ready=false`, `approved_adr=null`; release class UNDECIDED and no Zcode unlock. Only then research #198 can close and AUD-03 begin research.

## TESTS
Only P00 GitHub Docs Validation: Source Pack/local links, module catalog DAG, registry and Zcode blocked-selector. No actual code, acoustic renderer, headless mix, native/Web/codec, geometry bake, perceptual listening, latency/CPU/IR benchmark or fuzz/ASan/TSan test run. All 128 acceptance cases FUTURE NOT EXECUTED.

## DELIVERABLES
Architecture, ADR-0039, license-tech matrix, typed API, future 128 test matrix, acoustic benchmark protocol, full Work Order, Evidence Bundle, research issue #198, research PR and separate checkpoint PR; actual observed CI run/job + SHA and objective audit comments; main/registry readback. Future coding #53 untouched.

## REVIEW FORMAT
pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED with BASE/HEAD, exact changed files, CI runs/jobs/results, legal/data rights/biometric privacy, contract ownership/streaming/RT correctness risk, unexecuted tests, missing evidence, proposed Checkpoint Delta and stop condition. "Documented" is not "implemented".

## STOP CONDITION
If Source Pack drift/BASE stale, undocumented license, HRTF dataset/geometry invalid claim, unexpected executable diff, CI not exact HEAD/failed, known HIGH/CRITICAL documentary defect, unauthorized code unlock or bad checkpoint registry: SAME WO/PR Correction Delta or BLOCKED, do not advance to AUD-03.

## CONTEXT LOCK
BASE main `90125e6885603ad260f0d355067991699577a9f6`; preflight blobs: checkpoint `7d6f5dd9969d42c77874075ca3a5762cbdcb2af5`, ledger `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`, Scope `4ef605c74632ece080b2650e37dd83a415b63310`, DoD `160b3054db9ea1961308934b401488b838d24c3e`, architecture `df62574cb3956c3ac9881631a4cf66be4e1abff1`, requirements `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`, catalog `18d69bca439831d65982cb0f8acbca1dbaa2eee9`, registry `37b264f486c367755cf6a8c0c8ccbe51e9bc5c06`, AUD-01 architecture `2967a42d44d115cfaf85ff9576e431c732daaf4e`. Revalidate if any critical source changes.

## EVIDENCE
See [Evidence Bundle](../evidence/NLE-P00-WO-002-AUD-02.md); actual PR, CI and review recorded only after verification.
