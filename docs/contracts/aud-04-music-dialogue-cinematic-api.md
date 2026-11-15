# AUD-04 — Adaptive Music, Dialogue, Timed Text and Cinematic Audio Semantic Contracts v0.1

**Research issue #204 | WO NLE-P00-WO-002-AUD-04 | Future code #55 OPEN/BLOCKED.** **PROPOSED semantic contracts only**, not compiled C++ ABI, wire format, serialization schema, authoring implementation or tested playback.

## 1. Versioned contract inventory
| Contract | Proposed fields / responsibility | Owner and required validation |
|---|---|---|
| `MusicProgramV1` | ProjectId, ProgramId/revision, default locale-independent score identity, segment/stem/loop/tempo/transition references, seed policy, source rights | AUD-04 authored semantics; DATA-04 CAS, DATA-02 AssetId, DATA-05 cooked readiness |
| `MusicSegmentV1` | SegmentId, AssetId/stem set, exact duration/loop start/end, tempo-map ref, entry/exit cues, phase/loop policy, sample rate/layout | DATA-03/05 source validation, finite duration, sample alignment and compatible stems |
| `MusicStemGroupV1` | StemGroupId, shared sample origin, BPM/time signature, phase, loop bounds, intensity parameter, required/optional stem flags | AUD-01 sample-frame alignment; AUD-03 parameter/automation; reject mismatched loop/tempo metadata |
| `TempoMapV1` | TempoMarkerId, rational BPM numerator/denominator, time-signature numerator/denominator, beat/bar origin, pickup, loop anchor, sample/rational mapping | validated finite positive tempo and meter, no float accumulation, bounded marker count |
| `MusicTransitionRuleV1` | source/destination SegmentId, priority, exit/entry cue, quantization IMMEDIATE/NEXT_BEAT/NEXT_BAR/NEXT_LOOP_END/EXPLICIT_SAMPLE, optional bridge/stinger, fade curve/duration, phase policy, fallback | AUD-04 graph compiler, deterministic tie-break and fallback, DATA-04 revision |
| `MusicStateIntentV1` | EventId, source authority/epoch, sequence, GAME state snapshot revision, target state/parameters, priority, expiry/dwell/hysteresis | GAME/NET authoritative read-only producer; reject unauthorized client state |
| `MusicTransportV1` | EngineEpoch, ProgramId/revision, transport generation, current/target segment, loop iteration, beat/bar/phase, deterministic seed, DeviceEpoch/SampleFrame anchor | AUD-04 transport state, AUD-01 sample clock; stale generation rejected |
| `MusicTransitionPlanV1` | PlanId, source/destination segment revisions, exact source exit/destination start frames, fade/bridge/stinger frame ranges, prefetch status, latency/phase compatibility, fallback | compiled off-RT CORE-03, immutable and bounded; AUD-01 publishes command |
| `MusicTransportReceiptV1` | EventId, requested/accepted/actual sample frame, DeviceEpoch, segment revision, exact/quantized/late/fallback/failed status, underrun/missing asset reason | AUD-01 playback evidence; receipt distinguishes schedule accepted from actually audible |
| `DialogueLineIdV1` | stable DialogueId + LineId + content revision independent of filename/locale | DATA-02 AssetId linkage; stable through reimport and localization |
| `DialogueArgumentSchemaV1` | typed argument IDs/enums, allowed values, fallback path, required context version and sensitivity label | authored DATA-04 schema; no raw script/expression or arbitrary property lookup |
| `DialogueContextSnapshotV1` | GAME/QUEST authoritative snapshot ID/revision, approved argument values, actor/speaker context, sequence epoch | GAME/NET owns truth; least-privilege fields, no hidden quest/relationship data |
| `DialogueEventV1` | DialogueEventId, LineId candidates, typed condition paths, weights/probabilities, default fallback, priority class, expiry | deterministic resolution with recorded seed and source revision; no gameplay mutation |
| `DialogueResolutionReceiptV1` | requested LineId/event, selected variant, locale, fallback path, context revision, exact asset hash/rights and reason | auditable choice; unresolved path returns typed error, never invent dialogue |
| `VoicePlaybackRequestV1` | EventId, LineId, speaker/performer ID, AssetId/locale/revision, priority, concurrency class, interrupt policy, expiry, bus and ducking policy | AUD-04 scheduler, DATA-02/03/05 rights/readiness; AUD-01 actual voice handle |
| `DialoguePlaybackReceiptV1` | VoiceHandle/generation, requested/actual SampleFrameId, DeviceEpoch, started/queued/stolen/interrupted/late/ended/missing, last cursor | AUD-01 source of playback truth; safe cancellation and idempotent event |
| `LocalizedAudioManifestV1` | LineId/CueId, BCP-47 locale, text/caption/audio/AD AssetIds, translator/performer, revision, reference locale, rights, status | DATA-02 provenance, DATA-03 import, DATA-04 authored CAS, DATA-05 cook |
| `LocaleResolutionReceiptV1` | requested/effective locale, fallback chain, voice/caption/text readiness, EXACT/PARENT_FALLBACK/REFERENCE_FALLBACK/TEXT_ONLY/MISSING | no silent wrong-language swap; explicit user/project fallback policy |
| `TimedTextCueV1` | CueId, LineId/AssetId, cue kind SUBTITLE/CAPTION_SDH/SOUND/MUSIC/AD/TRANSCRIPT, BCP-47, speaker, rational start/end or SampleFrameId, text key/text, safe spans, direction/category, region/overlap group | AUD-04 content, DATA-04 revision, W3C adapter validation; actual voice cursor drives dialogue caption |
| `TimedTextTrackV1` | TrackId, sequence/locale/revision, cue list, kind, default visibility, safe styling, export adapter version | one declared WebVTT kind per file, overlapping cue policy and stable ordering |
| `CinematicAudioTrackV1` | TrackId, SequenceId/revision, rational timebase, type MUSIC/DIALOGUE/VO/SFX/CAPTION/AD/AUTOMATION, cue refs, track priority | TWO-03 owns timeline; AUD-04 validates audio-specific track semantics |
| `CinematicAudioCueV1` | CueId, sequence epoch, rational start/end, AssetId/LineId/ProgramId, sample offset policy, pause/seek/skip/loop/branch behavior, caption/viseme refs | TWO-03 source revision, AUD-01 sample mapping and command receipt |
| `CinematicAudioReceiptV1` | CueId, sequence/device epoch, requested/actual sample and sequence position, playback/caption/viseme state, late/drop/fallback reason | actual output vs planned time clearly separated |
| `VisemeMarkerTrackV1` | LineId/voice asset hash, authored marker IDs/viseme IDs, sample/rational offsets, language/phoneme schema revision | AUD-04 maps authored markers, TWO-03 consumes animation intents; no automatic speech recognition |
| `DuckingPolicyV1` | PolicyId/revision, key BusGuid/VoiceHandle, target BusGuid set, depth ceiling, threshold/ratio, attack/hold/release, priority and overlap arbitration, pre-roll | AUD-04 policy, AUD-03 sidechain node/parameter automation, AUD-01 bus graph |
| `AccessibilityAudioProfileV1` | independent dialogue/music/SFX/ambience/narration gains, mono preference, reduced-range mode, captions/SDH/AD visibility, locale and text preferences | user-authorized persistent settings; AUD-01 gains, AUD-03 dynamics, UI owner accessible controls |
| `AudioRightsManifestV1` | AssetId/hash, composition, master/recording, performer/voice likeness, translation, subtitle/SDH, library, territory/term/platform, attribution, edit/sublicense/redistribute, consent and revocation | DATA-02 provenance and DATA-03/05 pipeline; code license is separate |
| `Aud04CapabilitiesV1` | native/Web/headless, audio clock precision, quantization, stem count, voice count, locale/caption formats, timeline sync, audio-description, accessibility mix, streaming and actual fallback support | advertise only measured target capabilities |
| `Aud04ErrorV1` | typed error code, object/revision/epoch, source authority, expected/actual sample or locale, safe fallback and recoverability | no private PCM, hidden gameplay context or raw paths in diagnostics |

## 2. Semantic operations and ownership
1. `StageMusicProgram(program, expectedRevision, principal)` → DATA-04 CAS, schema/tempo/transition/stem/rights validation, dry-run and bounded graph.
2. `CompileMusicTransition(programRevision, from, to, deviceProfile)` → CORE-03 non-RT compile, phase/loop/tempo/voice/asset/prefetch and sample-clock plan. Does not schedule from wall time.
3. `SubmitMusicStateIntent(intent, authoritativeSnapshot)` → validate GAME authority, priority, hysteresis, dedup and expiry; resolve to precompiled transition plan.
4. `ScheduleMusicTransition(plan, expectedDeviceEpoch)` → AUD-01 bounded sample-target command, returns accepted/late/fallback receipt; AUD-04 never writes PCM.
5. `ResolveDialogueEvent(event, contextSnapshot, locale)` → typed argument path, selected LineId/variant, explicit fallback receipt; GAME state remains unchanged.
6. `QueueDialogueVoice(request, expectedLocaleRevision)` → prefetch via DATA-05/CORE-03 and scheduler priority/interrupt/expiry; AUD-01 owns actual playback.
7. `ResolveTimedText(lineId, locale, cueKind, playbackReceipt)` → matching caption/SDH/AD/transcript and actual voice sample cursor; no raw HTML.
8. `StageLocaleBundle(bundle, expectedRevision, principal)` → BCP-47/CLDR normalization, text/voice/caption completeness and rights; commit locale at safe boundary.
9. `StageCinematicAudioTrack(track, expectedSequenceRevision, principal)` → TWO-03 sequence CAS + rational timebase/asset/cue validation; no second timeline.
10. `ScheduleCinematicCue(cue, sequenceClockMap, audioClockMap)` → rational-to-sample conversion, AUD-01 command, receipt; stale sequence/device epochs rejected.
11. `StageDuckingPolicy(policy, expectedDspGraphRevision)` → AUD-03 sidechain/parameter plan and AUD-01 target bus validation; no second mixer or compressor.
12. `ApplyAccessibilityAudioProfile(profile, expectedUserSettingsRevision)` → independent bus gains and optional AUD-03 dynamics parameters, mono/caption/AD settings; never alter gameplay authority.
13. `ExportTimedText(track, format, locale)` → bounded WebVTT/TTML adapter with explicit cue kind and validation; no file path or export shell.
14. `ReadAud04Telemetry(cursor, limit, principal)` → CORE-06 counters for transition lateness, dialogue fallback, caption sync, voice starvation and asset readiness; no private audio or personal voice recording.

## 3. Typed errors
`UNAUTHORIZED_AUDIO_STATE`, `MUSIC_PROGRAM_REVISION_STALE`, `MUSIC_TEMPO_INVALID`, `MUSIC_METER_INVALID`, `MUSIC_STEM_PHASE_MISMATCH`, `MUSIC_TRANSITION_UNDEFINED`, `MUSIC_TRANSITION_PLAN_LATE`, `MUSIC_ASSET_NOT_READY`, `MUSIC_LOOP_INVALID`, `MUSIC_CLOCK_EPOCH_STALE`, `MUSIC_TRANSPORT_GENERATION_STALE`, `MUSIC_STATE_FLAPPING`, `DIALOGUE_ARGUMENT_SCHEMA_INVALID`, `DIALOGUE_CONTEXT_UNAUTHORIZED`, `DIALOGUE_VARIANT_UNAVAILABLE`, `DIALOGUE_FALLBACK_MISSING`, `DIALOGUE_VOICE_RIGHTS_MISSING`, `VOICE_CONCURRENCY_LIMIT`, `VOICE_EXPIRED`, `VOICE_INTERRUPTED`, `VOICE_ASSET_NOT_READY`, `LOCALE_TAG_INVALID`, `LOCALE_FALLBACK_UNCONFIGURED`, `LOCALE_BUNDLE_INCOMPLETE`, `CAPTION_CUE_INVALID`, `CAPTION_KIND_MIXED`, `CAPTION_PARSE_LIMIT`, `CAPTION_ASSET_MISSING`, `TIMED_TEXT_UNSAFE_MARKUP`, `TTML_XML_EXTERNAL_ENTITY`, `SEQUENCE_REVISION_STALE`, `SEQUENCE_TIMEBASE_INVALID`, `CINEMATIC_CUE_LATE`, `CINEMATIC_EPOCH_STALE`, `VISEME_TRACK_MISMATCH`, `DUCKING_POLICY_INVALID`, `DUCKING_TARGET_UNAUTHORIZED`, `DSP_GRAPH_REVISION_STALE`, `ACCESSIBILITY_PROFILE_INVALID`, `AUDIO_RIGHTS_REVOKED`, `AUDIO_DEVICE_UNAVAILABLE`, `AUDIO_CAPABILITY_UNAVAILABLE`, `STREAM_PREFETCH_LATE`, `INTERNAL_FAILURE`.

## 4. Cross-module invariants
- AUD-01 is sole live playback/sample-clock/mixer/voice owner; actual sample cursor/DeviceEpoch comes only from AUD-01 receipt.
- AUD-02 spatial profile and room context are read-only input; AUD-04 cannot duplicate spatialization.
- AUD-03 owns DSP/ducking/automation; AUD-04 owns policy and triggers only.
- TWO-03 owns sequence/timebase and consumes authored viseme cues; AUD-04 supplies audio tracks/cues and receipts.
- CORE-04 TickId is not an audio clock; rational mapping uses AUD-01 AudioClockMap. No graphics frame or wall-clock drift.
- GAME/QUEST/NET own gameplay decisions; dialogue argument snapshots are role-limited and immutable.
- DATA-02/03/04/05 own AssetId, rights/provenance, import, authored revision and cooked stream. No direct file/path/network/decoder call.
- Every queued event is versioned, deduplicated, bounded, cancellable and reports fallback/late/missing states. No arbitrary script, raw PCM, native plugin or generated voice.
- Timed text is safe text with explicit locale/kind; caption cues are not automatically equivalent to translated dialogue or audio description.
- Contract names/fields are semantic proposals only; final schema, ABI, limits and serialization require a later approved coding Work Order.
