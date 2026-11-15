# Research Work Order — NLE-P00-WO-002-AUD-03

**Date 2026-11-14 | Research #201 | Future coding #54 OPEN/BLOCKED**  
**BASE main:** `f4e954dc41ac86b8b6dfb310743adc27d3ba6d41`. **P00 DOCUMENTATION ONLY**, risk LOW documentary, future ELEVATED for realtime audio safety, arbitrary native plugins, DSP aliasing/hearing hazards, untrusted IR/graph/automation, resource starvation. Release class UNDECIDED, engine software license NLE-D009 OPEN.

## OBJECTIVE
Research an original Stormline-owned low-latency DSP and effect graph with first-party EQ (biquad/shelves), filters, compressor/expander/gate/limiter, saturation/distortion, delays/chorus/flanger, bounded reverb/IR convolution, sidechains/dry-wet, sample-accurate RTPC/parameter automation, immutable graph compilation and snapshots. Define AUD-01 voice/bus/device/sample-clock authority, AUD-02 IR/spatial source, CORE-03 off-RT jobs, plugin execution privacy and licensing, cross-platform/headless safety, measurable original quality/CPU/latency tests.

## CONTEXT
Previous AUD-02 research #198, research PR #199 + checkpoint PR #200 independently audited/normal squash merged and exact main readback; current main `f4e954dc41ac86b8b6dfb310743adc27d3ba6d41`. Baseline **36/80** documentary research documented (45%), **44 pending** incl historical CORE-04 research status gap; **0/80 engine implementations**, all 80 coding packets `BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS` / executor_ready=false / approved_adr=null. AUD-03 catalog_order 37 and mandatory AUD-01 dep researched only, zero executable audio. Future coding issue #54 OPEN/BLOCKED. AUD-04 research is next only after checkpoint.

## SCOPE
Eight new Markdown docs ONLY: [architecture](../architecture/aud-03-dsp-sound-graph.md), [ADR-0040 PROPOSED](../adr/0040-aud-03-realtime-dsp-graph-authority.md), [official upstream technology/license matrix](../research/aud-03-dsp-technologies-license-matrix.md), [typed semantic API](../contracts/aud-03-dsp-graph-api.md), [128 future acceptance cases](../testing/aud-03-acceptance-matrix.md), [reproducible DSP CPU/quality/security benchmark protocol](../research/aud-03-dsp-benchmark-protocol.md), this WO and [Evidence Bundle](../evidence/NLE-P00-WO-002-AUD-03.md). Dedicated research issue/branch/PR with final-exact-HEAD Docs Validation, objective pt-BR audit and normal squash/main readback; separate checkpoint reconciliation PR, separate CI/audit/squash/readback. No runtime/code work.

## OUT OF SCOPE
C++ DSP kernels and AudioWorklet, SDK/plugin downloads or distribution, commercial music/preset/IR assets, actual signal generation/playback, physical audio device/headset, real FFT tests, native/Web/headless builds, untrusted native CLAP/LV2/VST plugin host, third-party cloud audio service, voice chat/microphone, music/dialogue AUD-04, HRTF/room geometry AUD-02, new bus/device layer AUD-01, standalone complete DAW, paid CI/reviewer, unapproved source cleanup, deployment or engine release.

## FILES/SOURCES TO READ (canonical priority)
`docs/11-checkpoint.md` > `docs/10-decisions-ledger.md` and approved ADRs > `docs/03-scope.md` > `docs/09-definition-of-done.md` > `docs/04-architecture.md` > `docs/02-requirements.md` > `AGENTS.md` > `docs/product/module-catalog.md` > `docs/queue/implementation-registry.json` > `docs/queue/work-orders/AUD-03.md`. Required boundaries: [AUD-01](../architecture/aud-01-audio-device-mixer.md), [AUD-02](../architecture/aud-02-spatial-audio-acoustic-world.md), DATA-03/04/05, CORE-02/03/04/06, GAME/NET authority. Official vendor links in research matrix. No exact code source paths/commands approved because no runtime currently.

## REQUIREMENTS
GOV-001..005, CAP-003 audio/DSP, original 2D/2.5D/3D platforms and native Windows/Linux/macOS plus conditional Web/WASM, CPU/headless/NullSink even with GPU absent, user requested best-quality measurable graphics/audio while keeping honest benchmarks, original generated PCM signals/rights, same Editor/CLI/MCP authoring kernel and source CAS, free CI/public repo, no independent external human reviewer or CodeRabbit. Catalog acceptance **"Graph validado, teste de clipping, estabilidade em tempo real"** remains FUTURE/UNMET, not satisfied by docs.

## ARCHITECTURE RULES
AUD-01 **sole** audio PCM/device, sample-clock, voice and bus mixer/RT callback owner; AUD-03 effect graph/RTPC/FX plans only, AUD-02 room HRTF/IR source and spatial authority, AUD-04 adaptive music/dialogue future consumer. CORE-03 compile/FFT/IR decode/validation off-RT, CORE-02 prealloc, CORE-04 TickId rational map to AUD-01 `SampleFrameId`, CORE-06 metrics buffered and drained off RT; DATA-03/04/05 legal asset/authoring CAS/cook. Forbid callback alloc/lock/IO/log/FFT planning or arbitrary executable plugin; DAG with explicit validated causal delays, bounded parameters/nodes/edges/scratch/latency/tail/CPU budgets and epoch-snapshot retirement; no GAME/NET source authority changes. External plugin bridge future proof-or-drop behind actual sandbox and opt-in.

## CONSTRAINTS
P00 research-only, no adopted library/asset rights/no SDK pins, Faust generated code may have input-based GPL and FFTW GPL/commercial complications, CLAP/LV2 license only for standard not plugins. 128 prospective tests **FUTURE / NOT EXECUTED**, performance/latency/clipping/audio quality NOT measured. `research_status` can change only in separately audited checkpoint PR; all 80 coding WOs remain BLOCKED, executor_ready=false, approved_adr=null, code issue #54 OPEN/BLOCKED and release_class UNDECIDED. No force-push/ruleset bypass/destructive merge or credential changes.

## ACCEPTANCE CRITERIA
- [ ] Exactly 8 new scoped Markdown docs with valid Source Pack local links, no executable/source code or unrelated file.
- [ ] ADR-0040 remains **PROPOSED**, technology/license/source rights matrix accurate: DSPFilters/Airwindows MIT, KissFFT BSD-3, Soundpipe archived MIT, Faust generated library dependence, CLAP MIT spec only, LV2 ISC spec, FFTW GPL/commercial never silently adopted.
- [ ] Typed graph/node/port/sidechain/RTPC/automation/IR/latency/tail/plan receipt API, single AUD-01 mixer, off-RT compile, prealloc process, secure sandbox plugin boundary, voice privacy and typed errors.
- [ ] 128 cases FUTURE NOT EXECUTED, full benchmark protocol incl goldens/THD+N/true-peak/p95/p99/native/Web/audio-golden/security/rollback; zero actual engine tests claimed.
- [ ] Research PR final exact-HEAD Docs Validation SUCCESS, pt-BR objective audit APPROVED without known HIGH/CRITICAL documentary defects, normal squash + main readback.
- [ ] SEPARATE checkpoint PR own exact-HEAD CI/audit/squash/readback: only AUD-03 research_status from RESEARCH_PENDING to RESEARCH_DOCUMENTED_ADR_PROPOSED, total **37/80 researches (46.25%)**, **43 pending** including CORE-04 historical research gap, **0 engine code**.
- [ ] All 80 coding packets still `BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`, `executor_ready=false`, `approved_adr=null`; future coding #54 remains OPEN/BLOCKED, no Zcode code; research issue #201 closes only after checkpoint verified, next AUD-04 research only.

## TESTS
P00: Github Docs Validation checks Source Pack/local links, catalog dependencies/DAG, work-order registry and Zcode blocked selector only. No actual signal processing, C++/WASM, native/Web, audio playback, plugin execution, fuzz/sanitizer, CPU/heap/audio latency/clipping/THD benchmark run. **128 runtime cases FUTURE/NOT EXECUTED.** Record actual final HEAD workflow/jobs after evidence updates.

## DELIVERABLES
Eight links above, research issue #201, research PR with exact-HEAD CI/pt-BR audit/squash/main readback, separately reconciled checkpoint PR and main readback, explicit evidence/risks/future test count and next AUD-04 research only; leave coding issue #54 untouched.

## REVIEW FORMAT
pt-BR **APPROVED / CORRECTION REQUIRED / BLOCKED**, exact BASE/HEAD SHA and file diff, Source Pack fingerprints, official license/source and plugin isolation threats, actual CI workflow/job & results, future NOT EXECUTED tests, no fabricated quality, rollback/readback and proposed checkpoint delta. No automatic new WO while correction is needed.

## STOP CONDITION
STALE main or checkpoint/ledger/Scope/DoD/Architecture, unexpected code/source diff, unapproved copyleft license/plugin ABI, private plugin/security leak, CI not exact head or failed, known HIGH/CRITICAL, code-ready mutation or unreviewed merge => Correction Delta SAME WO/PR or BLOCKED, do not start AUD-04.

## CONTEXT LOCK (preflight)
BASE main `f4e954dc41ac86b8b6dfb310743adc27d3ba6d41`; checkpoint blob `74101c643c2a0c05752fb58a49bc41bae859479a`, Ledger `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`, Scope `4ef605c74632ece080b2650e37dd83a415b63310`, DoD `160b3054db9ea1961308934b401488b838d24c3e`, Architecture `df62574cb3956c3ac9881631a4cf66be4e1abff1`, Requirements `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`, catalog `18d69bca439831d65982cb0f8acbca1dbaa2eee9`, registry `790c2b6d1f512869e10a5e197c0631733efd7c9c`, AUD-01 `2967a42d44d115cfaf85ff9576e431c732daaf4e`, AUD-02 `2eeeaac87cd33ae6a316f1ce7b311c851bdfa4a0`. Revalidate against Git/source if any approved source changes.

## EVIDENCE
[Evidence Bundle](../evidence/NLE-P00-WO-002-AUD-03.md). Pending PR/CI/merge statuses cannot be claimed before actually observed.
