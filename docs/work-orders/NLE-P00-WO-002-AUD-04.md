# Research Work Order — NLE-P00-WO-002-AUD-04

**Date:** 2026-11-14 | **Research issue:** #204 | **Future implementation issue:** #55 OPEN/BLOCKED  
**BASE main:** `1d0280674385a034b68573aeb6a98db243f34ae1`. **P00 DOCUMENTATION ONLY.** Research risk LOW; future implementation risk ELEVATED due to realtime audio, content rights/voice likeness, locale fallback, subtitle parser, timeline synchronization, accessibility and streaming starvation. Release class UNDECIDED; engine software license NLE-D009 OPEN.

## OBJECTIVE
Research and specify a first-party Stormline-owned Adaptive Music, Dialogue/VO, Timed Text/Localization, Cinematic Audio, Accessibility Mix and Ducking orchestration layer. Provide typed versioned contracts, architecture ownership boundaries, official technology/license matrix, 128 prospective acceptance tests and a reproducible benchmark protocol.

## CONTEXT
AUD-03 research #201 and PR #202 were merged; separate checkpoint PR #203 was merged and main readback verified at `1d0280674385a034b68573aeb6a98db243f34ae1`. Checkpoint: **37/80** research documented, **43 pending**, **0/80 runtime modules implemented**. All 80 code packets are `BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`, `executor_ready=false`, `approved_adr=null`. AUD-04 catalog_order=38 depends on AUD-01/02/03, none implemented. Future implementation issue #55 OPEN/BLOCKED. Next catalog module is GAME-01 Input & Control Mapping (#56), not an assumed AUD-05.

## SCOPE
Exactly eight new Markdown documents:
1. [AUD-04 architecture](../architecture/aud-04-music-dialogue-cinematic-audio.md)
2. [ADR-0041 PROPOSED](../adr/0041-aud-04-interactive-music-dialogue-cinematic-audio.md)
3. [technology/license/interchange matrix](../research/aud-04-adaptive-audio-technology-license-matrix.md)
4. [typed semantic contracts](../contracts/aud-04-music-dialogue-cinematic-api.md)
5. [128 future acceptance cases](../testing/aud-04-acceptance-matrix.md)
6. [sync/quality/performance benchmark protocol](../research/aud-04-audio-cinematic-benchmark-protocol.md)
7. this Work Order
8. [Evidence Bundle](../evidence/NLE-P00-WO-002-AUD-04.md)

Create research issue #204 and dedicated research branch/PR, exact-final-HEAD Docs Validation, pt-BR objective audit, normal squash/main readback. Then create a **separate checkpoint PR** with only research status/checkpoint/backlog/WO/evidence reconciliation, its own exact-final-HEAD CI/audit/squash/readback. Close #204 only after successful checkpoint readback.

## OUT OF SCOPE
Any C++/Rust/WASM code, music/VO/SFX/IR/caption assets, voice recording or generation, AI/TTS/voice cloning, microphone capture, audio middleware/SDK/plugin download, FMOD/Wwise/Godot/OTIO integration or distribution, audio playback/physical device, codec/importer implementation, subtitle renderer, cutscene player/editor, mixer/DSP/decoder, actual A/V mux/export, paid CI, external reviewer, deployment, source cleanup, changes to AUD-01/02/03/TWO-03 upstream docs, new canonical Source Pack or modifications to code issue #55.

## FILES / SOURCES TO READ (canonical priority)
`docs/11-checkpoint.md` > `docs/10-decisions-ledger.md` and approved ADRs > `docs/03-scope.md` > `docs/09-definition-of-done.md` > `docs/04-architecture.md` > `docs/02-requirements.md` > `AGENTS.md` > `docs/product/module-catalog.md` > `docs/queue/implementation-registry.json` > existing AUD-01/02/03 and TWO-03, CORE-04, DATA-03/04/05 architecture/contracts. Official vendor, Unicode and W3C URLs are listed in the technology matrix.

## REQUIREMENTS
GOV-001..005, CAP-003 audio/DSP, NLE-D013 1.0 DoD, NLE-D014 native 2D/2.5D/3D + Web, NLE-D015 AI/MCP only through authorized public APIs, NLE-D016 80-module catalog, NLE-D017 Windows/Linux/macOS desktop and planned Web, NLE-D018 autonomy bounded by governance, NLE-D019 complete Work Orders before execution, NLE-D020 blocked code queue. Same authoring semantics for Editor/CLI/MCP; no unrestricted host access or gameplay authority. Original legally cleared media fixtures only in future testing.

## ARCHITECTURE RULES
- AUD-01 is the sole audio device/PCM/voice/bus/mixer/sample-clock owner; use `AudioClockMapV1` and `SampleFrameId`.
- AUD-02 owns spatial/acoustic/HRTF source. AUD-03 owns DSP graph, sidechain/ducking kernels and parameter automation.
- AUD-04 owns music state/transport, dialogue/VO resolution and scheduling policy, captions/localization, accessibility mix intent and cinematic audio cue orchestration only.
- TWO-03 owns sequence/cutscene timeline and rational timebase; CORE-04 owns simulation `TickId` only. Convert rational sequence/game time through AUD-01's measured clock map; never render FPS/wall-clock audio scheduling.
- GAME/QUEST/NET own authoritative game state; dialogue context is read-only. DATA-02 owns AssetId/revision/provenance, DATA-03 import/validation, DATA-04 authored CAS, DATA-05 cooked/streamed bundles. CORE-03 non-RT prefetch/compile; CORE-06 drained telemetry.
- Music uses horizontal resequencing + vertical stems, explicit tempo/transition matrix/beat-bar/loop markers, deterministic seed, hysteresis and fallback. Voice has bounded priorities/concurrency/interruption and receipts. Captions/subtitles/SDH/audio-description/transcript are distinct tracks; BCP-47/CLDR locale resolution and explicit fallback. Cinematic cues integrate TWO-03 rational time and AUD-01 actual sample receipts. Ducking policy is AUD-04, DSP is AUD-03 and buses are AUD-01.
- FMOD/Wwise/Godot/OTIO are references only. FMOD EULA limits game runtime grant away from game-engine/toolset distribution; Wwise SDK agreement consulted is plugin-application scope, not general runtime embedding. No middleware is adopted. Music, master recording, voice/likeness, translation, subtitle and code rights remain separate.
- No scripts/host paths/network, arbitrary plugin or microphone/voice upload. Safe WebVTT/TTML parsing, XML external entity disable, quotas, role/privacy and content rights are required.

## CONSTRAINTS
P00 documentation only. ADR-0041 stays PROPOSED. 128 tests FUTURE/NOT EXECUTED. No assets, SDK, runtime, playback, actual synchronization, latency, clipping, accessibility or benchmark proof. Do not claim W3C/WCAG certification. Do not change any upstream canonical doc or code issue #55. Registry status may change only in separate audited checkpoint PR after research PR merge. All 80 implementation packets remain BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, executor_ready=false, approved_adr=null, release_class UNDECIDED. No force-push, ruleset bypass or destructive action.

## ACCEPTANCE CRITERIA
- [ ] Exactly eight new scoped Markdown docs, with valid local links, no source/runtime code or unrelated changes.
- [ ] ADR-0041 remains **PROPOSED**; architecture respects AUD-01/02/03, TWO-03, CORE-04 and DATA-02/03/04/05; no duplicate mixer, clock or timeline.
- [ ] Music, voice/VO, captions/subtitles/SDH/AD/transcript, locale fallback, cinematic seek/skip/loop, viseme handoff, ducking, accessibility and rights/privacy contracts are explicit and typed.
- [ ] FMOD/Wwise licensing accurately bounded; OTIO/WebVTT/TTML/CLDR/WCAG status/licensing is not overstated; no middleware, codec or content adopted.
- [ ] Exactly 128 future test cases and a reproducible sync/audio/CPU/memory/streaming/accessibility benchmark protocol; all marked NOT EXECUTED.
- [ ] Research PR exact-final-HEAD Docs Validation SUCCESS, no known HIGH/CRITICAL documentary defect, pt-BR audit APPROVED, normal squash and main readback.
- [ ] Separate checkpoint PR exact-final-HEAD Docs Validation/audit/squash/readback; only AUD-04 research_status changes to RESEARCH_DOCUMENTED_ADR_PROPOSED; tally becomes **38/80 (47.5%)**, **42 pending**, **0 runtime modules**.
- [ ] All 80 coding packets remain `BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`, `executor_ready=false`, `approved_adr=null`; issue #55 OPEN/BLOCKED. Next research module is **GAME-01 #56** only after checkpoint approval/readback.

## TESTS
P00: Docs Validation (Source Pack/local links, module taxonomy/dependency DAG, WO registry, Zcode blocked selector). No audio playback, voice/subtitle/cutscene runtime, C++/Web/headless build, codec/asset import, fuzz/sanitizer, accessibility user testing, A/V loopback, CPU/memory/latency or benchmark is run. 128 prospective runtime/security/performance cases remain FUTURE.

## DELIVERABLES
Research issue #204, exactly eight documents, research PR exact-head CI/audit/squash/readback, separate checkpoint PR exact-head CI/audit/squash/readback, issue closure after checkpoint readback, accurate Evidence Bundle and no implementation unlock.

## REVIEW FORMAT
pt-BR **APPROVED / CORRECTION REQUIRED / BLOCKED**. State exact BASE/HEAD SHA, eight-file diff, Source Pack fingerprints, official source/license interpretation, ownership/timebase/privacy/rights/fallback risks, actual workflow/job and conclusion, future-not-executed tests, rollback/readback and exact checkpoint delta. No claims based on "completed" without evidence.

## STOP CONDITION
Checkpoint/Scope/DoD/Architecture/approved decision drift marks Context Lock STALE; unexpected code/assets/SDK/credential changes, any high/critical risk, license ambiguity, exact-head CI failure, registry safety invariant violation or mergeability/ruleset failure means same-WO correction or BLOCKED. Do not start GAME-01 until AUD-04 checkpoint is independently reconciled and read back.

## CONTEXT LOCK — preflight fingerprints
BASE main `1d0280674385a034b68573aeb6a98db243f34ae1`.
- Checkpoint `6bc5e1d41f2316a97107668784cd2010c092873c`
- Ledger `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`
- Scope `4ef605c74632ece080b2650e37dd83a415b63310`
- DoD `160b3054db9ea1961308934b401488b838d24c3e`
- Architecture `df62574cb3956c3ac9881631a4cf66be4e1abff1`
- Requirements `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`
- AGENTS `3e57b719f8651407879ebb641707a048773ea4c2`
- Backlog `770d74e3eeda51411871579173754b0919143444`
- Module catalog `18d69bca439831d65982cb0f8acbca1dbaa2eee9`
- Implementation registry `f60cc24e93cb2e5ebca41e63e6e97330a99d3f75`
- AUD-01 architecture/API `2967a42d44d115cfaf85ff9576e431c732daaf4e` / `49d358a883f9342710e725867c1bf26a2c089dea`
- AUD-02 architecture `2eeeaac87cd33ae6a316f1ce7b311c851bdfa4a0`
- AUD-03 architecture/API/ADR `0847210bdfdcc7545a67695c4a0c46361f92e3c0` / `32a7be50b61b1829d5f11af32f6dc816fe06899d` / `b36bba1c6a00e686b21669af2d2cb9e9cc7cb293`
- CORE-04 `b40b1bf97b934a883d6bb99e45bd40de6711912c`
- TWO-03 `f900c6b60e5d218723f985d4c518193ec09c1dee`
- DATA-03/04/05 `d7a31bf99f7eae0458f4b344cd94cbeea3f26699` / `7e88d4fecaa83c9922f255087df9f97f6300b61f` / `0e77be93e7d0fa2404acd297b98c1ef4545cb948`

Revalidate all critical hashes against Git immediately before PR review/merge; any changed canonical source requires a new Context Lock.

## EVIDENCE
[Evidence Bundle](../evidence/NLE-P00-WO-002-AUD-04.md). CI/PR/audit/merge statuses are pending until observed.
