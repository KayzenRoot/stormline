# Evidence Bundle — NLE-P00-WO-002-AUD-04 Music, Dialogue & Cinematic Audio Research

**STATUS: RESEARCH BRANCH IN PROGRESS; PR/CI/AUDIT/MERGE/CHECKPOINT PENDING. NO ENGINE CODE OR AUDIO CONTENT.**  
**2026-11-14 | Research [#204](https://github.com/KayzenRoot/stormline/issues/204) | Future coding [#55](https://github.com/KayzenRoot/stormline/issues/55) OPEN/BLOCKED | BASE main \`1d0280674385a034b68573aeb6a98db243f34ae1\`**.

## 1. Canonical source check and Context Lock
AUD-03 research #201/PR #202 and separate checkpoint PR #203 were merged; main readback verified at \`1d0280674385a034b68573aeb6a98db243f34ae1\`. Baseline: **37/80** research documented (46.25%), **43 pending**, **0/80 runtime modules implemented**. All 80 implementation packets remain \`BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS\`, \`executor_ready=false\`, \`approved_adr=null\`. AUD-04 catalog_order=38, future coding #55 OPEN/BLOCKED. Registry's next catalog module is **GAME-01 Input & Control Mapping #56**, not AUD-05.
Source Pack fingerprints at preflight are in the Work Order Context Lock. Canonical priority: checkpoint > ledger/approved ADRs > Scope > DoD > Architecture > Requirements > AGENTS > module catalog > registry > relevant module contracts. AUD-01/02/03, TWO-03, CORE-04 and DATA-03/04/05 are dependencies/owners but **not implemented**.

## 2. Proposed artifacts (documentation only)
- [Architecture](../architecture/aud-04-music-dialogue-cinematic-audio.md): adaptive music transport, stems, tempo/beat/bar quantization, transition matrix, dialogue/VO resolution and priority, timed text/locale fallback, TWO-03 cinematic cue integration, accessible mix and AUD-03 ducking policy.
- [ADR-0041 PROPOSED](../adr/0041-aud-04-interactive-music-dialogue-cinematic-audio.md); no owner approval or runtime selection.
- [Technology/license/interchange matrix](../research/aud-04-adaptive-audio-technology-license-matrix.md): FMOD 2.04 EULA game-engine/toolset boundary, Wwise SDK agreement scope, Godot interactive music reference, OpenTimelineIO Apache-2.0, W3C WebVTT/TTML, Unicode CLDR and WCAG references. No middleware or library adopted.
- [Typed contracts](../contracts/aud-04-music-dialogue-cinematic-api.md): MusicProgram/TempoMap/Transition, DialogueLine/Context/Voice, Locale/TimedText, CinematicTrack/Cue, Viseme, Ducking, AccessibilityProfile, rights and receipts.
- [128 future acceptance cases](../testing/aud-04-acceptance-matrix.md), all NOT EXECUTED.
- [Reproducible benchmark protocol](../research/aud-04-audio-cinematic-benchmark-protocol.md), no generated fixture or measurement.
- [Research Work Order](../work-orders/NLE-P00-WO-002-AUD-04.md) and this Evidence Bundle.

## 3. Official research references (consulted 2026-11-14)
- [FMOD 2.04 instruments/tempo/quantization](https://www.fmod.com/docs/2.04/studio/working-with-instruments.html), [dialogue/localization](https://www.fmod.com/docs/2.04/studio/dialogue-and-localization.html), [mixing/snapshots](https://www.fmod.com/docs/2.04/studio/mixing.html), [profiling](https://www.fmod.com/docs/2.04/studio/profiling.html), [EULA](https://www.fmod.com/legal), [pricing](https://fmod.com/licensing).
- [Wwise Project Adventure (historical 2014.1.1 reference)](https://www.audiokinetic.com/download/documents/WwiseProjectAdventure_en.pdf), [Wwise SDK Agreement v3 (2024-07-30)](https://www.audiokinetic.com/download/documents/License_Agreements/Audiokinetic_SDK_Agreement_v3_2024-07-30.pdf).
- [Godot AudioStreamInteractive 4.5](https://docs.godotengine.org/en/4.5/classes/class_audiostreaminteractive.html), [Godot MIT source license](https://github.com/godotengine/godot/blob/master/LICENSE.txt).
- [OpenTimelineIO repository](https://github.com/AcademySoftwareFoundation/OpenTimelineIO), [architecture/RationalTime](https://github.com/AcademySoftwareFoundation/OpenTimelineIO/blob/main/docs/tutorials/architecture.md), [Apache-2.0 license](https://github.com/AcademySoftwareFoundation/OpenTimelineIO/blob/main/LICENSE.txt).
- [W3C WebVTT](https://www.w3.org/TR/webvtt1/), [TTML2](https://www.w3.org/TR/ttml2/), [WCAG 2.2 audio description](https://www.w3.org/WAI/WCAG22/Understanding/audio-description-or-media-alternative-prerecorded), [WCAG 2.2 media alternative](https://www.w3.org/WAI/WCAG22/Understanding/media-alternative-prerecorded.html), [Unicode UTS #35/CLDR](https://unicode.org/reports/tr35/).

## 4. Verification ledger (only observed results)
| Gate | Current evidence |
|---|---|
| Research issue #204 and branch from checked main | OBSERVED |
| Exactly eight docs authored and final PR diff | PENDING |
| GitHub Docs Validation exact final HEAD | PENDING |
| SonarCloud/Socket or additional security check exact HEAD | NOT VERIFIED |
| Native/Web/headless build, playback, assets, codecs | NOT IMPLEMENTED / NOT TESTED |
| 128 future acceptance cases | ALL FUTURE / NOT EXECUTED |
| Accessibility user/assistive-tech test | NOT RUN |
| Audio sync/latency/CPU/memory/xrun benchmark | NOT RUN |
| Objective pt-BR documentary audit | PENDING |
| Research PR squash/main readback | PENDING |
| Separate checkpoint PR CI/audit/squash/readback | PENDING |

## 5. Risk register (future ELEVATED; not runtime mitigated)
- Music transition phase mismatch/click/gap, late stem prefetch, state flapping or duplicate stinger.
- Dialogue priority starvation, wrong line/locale, stale branch context or captions desynchronized from actual voice start.
- Timeline frame/sample drift, device epoch change, seek/skip/loop duplicate cues or mismatched viseme markers.
- Ducking double-applied, critical gameplay cue suppressed, reduced-range mix misrepresented as medical hearing protection.
- Untrusted audio/TTML/WebVTT parser, XML entity/cue bomb, malicious markup, path traversal, hidden gameplay state exposure or voice/performer rights violation.
- FMOD/Wwise license boundary misunderstood; unlicensed music/recording/voice/translation content shipped.
Proposed controls are described in ADR/architecture/contracts. **None is implemented or validated.**

## 6. Proposed checkpoint delta (not promoted)
Only after research PR exact-final-HEAD CI/audit/squash/readback and separate checkpoint PR exact-final-HEAD CI/audit/squash/readback: change only AUD-04 \`research_status\` from \`RESEARCH_PENDING\` to \`RESEARCH_DOCUMENTED_ADR_PROPOSED\`; count becomes **38/80 (47.5%)** documented, **42 pending**, **0 runtime modules implemented**. All 80 coding packets remain blocked, \`executor_ready=false\`, \`approved_adr=null\`; #55 OPEN/BLOCKED; ADR-0041 PROPOSED. Next research is **GAME-01 #56**, subject to checkpoint approval/readback. No implementation authorization.

## 7. Objective review contract
Report pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED with exact base/final SHA, eight-file diff, Source Pack fingerprints, actual Docs Validation workflow/job, license/rights/privacy and ownership review, 128 cases NOT EXECUTED, no runtime/benchmark claims, and exact checkpoint delta.
