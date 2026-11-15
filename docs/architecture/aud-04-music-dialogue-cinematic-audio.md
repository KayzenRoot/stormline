# AUD-04 — Music, Dialogue & Cinematic Audio Architecture

**Research WO:** NLE-P00-WO-002-AUD-04 | **Research issue:** #204 | **Future coding issue:** #55 OPEN/BLOCKED  
**BASE main:** `1d0280674385a034b68573aeb6a98db243f34ae1` | **P00 DOCUMENTATION ONLY / ADR-0041 PROPOSED.** No audio playback, music assets, dialogue/voice assets, caption files, runtime, SDK, build, subtitle renderer, timeline integration or benchmark exists. Research risk LOW; future integration ELEVATED because sample synchronization, voice/asset rights, untrusted media, localization fallback, timeline interruption, accessibility and audio starvation can break critical game presentation.

## 1. Mission, product outcome and acceptance truth
Catalog scope: **"Adaptive music, diálogos, legendas/locais e sincronismo com cutscenes."** Catalog acceptance: **"Troca de estado musical sem glitches, acessibilidade e fallback."** Design an original Stormline-owned system that coordinates:
- **Adaptive score:** horizontal resequencing of musical sections, vertical layering of synchronized stems, tempo/beat/bar/loop quantization, transition matrix, transition segments, stingers, snapshots and bounded RTPC.
- **Dialogue and voice-over:** stable line identity, gameplay-context resolution, voice locale variant, priority/interruption/concurrency policy, sample-aware scheduling and authored optional phoneme/viseme markers.
- **Timed text and localization:** subtitles, accessibility captions/SDH, speaker identity, off-screen/directional and non-speech sound cues, audio description and transcript/locale variants with explicit fallback.
- **Cinematic audio:** music, dialogue, sound, caption and audio-description cues coordinated with the existing TWO-03 rational sequence timeline and AUD-01 sample clock, including pause/seek/skip/loop/restart and offline export planning.
- **Accessibility mix:** independently adjustable dialogue/music/SFX/ambience/narration, mono-compatible fallback, reduced-dynamic-range profile, speech-priority/ducking policy and customizable captions.

The system is an **orchestrator and content policy layer**, not a second audio engine, DSP engine, asset importer or cinematic timeline. A transition plan is not proof of an audible, glitch-free transition. Only future PCM/clock/loopback evidence can establish the catalog acceptance.

## 2. Ownership and dependency boundaries
| Owner | AUD-04 consumes / publishes | Must not duplicate or bypass |
|---|---|---|
| **AUD-01 — sole output owner** | `AudioEngineEpoch`, `DeviceEpoch`, `AudioClockMapV1`, `SampleFrameId`, voice handles/states, bus GUIDs, command queues and playback receipts | AudioDevice/backend, PCM callback/mixer, voice allocation, bus topology/routing, sample clock, decoder, streaming ring or a second master bus |
| **AUD-02 — spatial acoustic owner** | read-only listener/spatial voice profiles, room/acoustic snapshot IDs and spatialized voice routing requests | room/portal geometry, HRTF source, acoustic ray/path solver or second spatializer |
| **AUD-03 — DSP owner** | immutable DSP graph revisions, sidechain ports, compressor/ducking node, parameter/automation/snapshot contracts and latency receipts | effect graph/compiler/kernel, second DSP chain, hidden mixer or custom compressor implementation |
| **TWO-03 — sequence/animation owner** | `SequenceAssetV1`, `AnimationTimeV1`, rational track/clip markers, scene/shot/viseme event intents and timeline epoch/revision | second cutscene timeline, animation state, visual frame clock, camera/scene authority |
| **CORE-04 — simulation time owner** | `TickId` and simulation-to-audio mapping through AUD-01 clock map | audio sample clock, wall-clock scheduling or presentation-FPS time |
| **CORE-03/06** | non-RT asset prefetch/transition planning and drained diagnostics/profiling | worker-pool ownership, blocking callbacks, real-time logging/telemetry allocation |
| **DATA-02/03/04/05** | durable `AssetId`/revision/provenance, secure audio/VO/caption import, staged authored dialogue/music/sequence references and target-cooked banks/chunks | alternate asset database, decoder/importer, direct host file/network, private packfile or rights inference |
| **GAME/NET/QUEST** | authenticated immutable context snapshot, conversation/quest/game state and authoritative event sequence | deciding or changing quest outcomes, dialogue choices that mutate game state, client-authoritative gameplay or secret data leakage |
| **EDIT/UI/CLI/MCP** | common typed stage/preview/validate/commit authoring operations and accessibility settings | arbitrary scripts, raw voice/audio buffers, filesystem paths or direct RT callback writes |

**Dependency state:** AUD-01/02/03 and TWO-03 are documentary research only; their runtime APIs are not implemented. The catalog dependencies AUD-03 and AUD-02 are necessary but not sufficient for implementation. AUD-04 must not be marked code-ready because upstream dependencies have not been implemented and no release class/ABI is approved.

## 3. Clock, timebase and synchronization model
- **Live audio master:** AUD-01 `AudioClockMapV1` and `SampleFrameId` are the only source for the actual output timeline. Every accepted voice/music/cinematic cue returns requested vs accepted vs actual sample frame, `DeviceEpoch`, lateness/underrun and fallback reason. Do not claim physical audible time from command submission alone.
- **Simulation:** CORE-04 `TickId` is gameplay intent time. Convert through the versioned AUD-01 clock map with rational remainder/drift estimate; never schedule to `steady_clock`, UTC, render frame or wall clock directly.
- **Sequence/editor:** TWO-03 `AnimationTimeV1` remains rational numerator/denominator with explicit frame-rate/timebase, e.g. 24000/1001, 24/1, 30/1. Use checked reduced rational conversion to sample frames; do not accumulate floating-point seconds or use GPU FPS. Live preview maps sequence time to the actual AUD-01 sample cursor; offline export maps both video frames and audio samples from the same exact rational origin.
- **Musical clock:** `TempoMapV1` uses piecewise tempo markers, rational BPM and time-signature numerator/denominator, beat/bar anchors and explicit pickup/loop semantics. Beat/bar quantization computes a future `SampleFrameId` from AUD-01's current cursor and tempo map. Tempo changes do not reset the device clock. Missing or invalid beat metadata returns a typed unsynchronized fallback, not guessed 120 BPM unless the author explicitly set that tempo.
- **Clock discontinuity:** device hotplug/rate change increments `DeviceEpoch`; invalidate stale pending schedule plans, recompile mapping off-RT and return typed receipts. Pause/seek/skip/reverse/loop and scene reload advance the appropriate sequence/transport epoch and cancel/deduplicate old cues. No silent drift or duplicate line.
- **Audio vs visual sync:** caption onset should follow the actual voice cursor/receipt; cinematic animation can consume authored viseme/phoneme markers mapped from the same sequence/voice sample position. A planned timestamp is not measured speaker output latency.

## 4. Adaptive music transport
### 4.1 Hybrid musical design
Proposed NECESSARY model combines:
1. **Horizontal resequencing:** select a new section/segment at an explicit safe exit cue, loop boundary, beat, bar or immediate quantization.
2. **Vertical layering:** add/remove pre-authored stems/layers that share a declared sample origin, tempo, bar structure and loop region. Gain/intensity changes are parameter automation through AUD-03/AUD-01, not independent unsynchronized playback.
3. **Transition matrix:** explicit source/destination rules with priority, source exit cue, destination entry cue, optional transition segment, optional stinger, quantization, crossfade/fade curve and timeout/fallback. General Any-to-Any is an explicit author fallback, never an implicit default that hides missing authoring.
4. **Stingers and one-shots:** event-triggered musical accents can quantize to next beat/bar or play immediately by authored rule, with bounded overlap/voice priority and cancellation semantics.
5. **Music states/parameters:** exploration, tension, combat, boss, victory, defeat, menu and cinematic are sample vocabulary, not engine-owned gameplay truth. GAME supplies a versioned context snapshot or state intent; AUD-04 resolves it into a musical target and may blend bounded intensity/danger/phase parameters.

### 4.2 Transport and transition guarantees
- `MusicProgramV1` is a versioned authored graph of segments, stems, loop regions, tempo maps, markers, transitions and asset-rights references.
- `MusicTransportV1` has transport generation, current/target segment, loop iteration, beat/bar/phase, deterministic seed and sample-clock epoch. Repeated request with the same command/event ID is idempotent.
- `MusicTransitionPlanV1` is compiled/validated off-RT. It contains exact source exit frame, destination start frame, quantization rule, fade duration in beats and frames, transition/stinger refs, prefetch deadline and bounded voice/buffer budget.
- **No-click proof:** crossfade must use phase/loop metadata where available, authored fades or bounded equal-power/linear curves, and a future output golden/loopback test. If metadata or prefetch is late, keep current safe loop or use an authored fallback. Never abruptly stop the current theme merely because a new segment is unavailable.
- **No state flapping:** state requests use priority, hysteresis, minimum dwell/cooldown, explicit interruption and deterministic tie-break. Repeated enemy threat changes or network jitter must not produce rapid music churn.
- **Deterministic variation:** random choices use a recorded project/program/sequence seed plus stable event/loop identifiers. No unseeded worker scheduling or wall-clock randomness in replayable music.
- **Prefetch:** DATA-05 and CORE-03 prepare banks/chunks before the scheduled boundary. Music start/transition returns READY, PENDING, LATE, FALLBACK or FAILED receipt. The callback never loads media, parses tempo maps or resolves a transition graph.

## 5. Dialogue, voice-over and narrative scheduling
### 5.1 Dialogue resolution
- `DialogueLineIdV1` is stable across locale versions, transcript, captions, voice recordings and reimport. `DialogueEventV1` contains a finite typed argument schema (speaker, quest/gameplay state, relationship/branch, line purpose), source revision and allowed fallback paths.
- GAME/QUEST provides an authoritative, immutable `DialogueContextSnapshotV1`; AUD-04 may select a matching authored line/variant but **cannot mutate quest, inventory, relationship, combat or server state**.
- A default/fallback line is authored for missing or unmatched arguments. If no legal line exists, return `DIALOGUE_VARIANT_UNAVAILABLE`; do not improvise a line, synthesize voice or silently play a different semantic response.
- Spoken dialogue and non-verbal vocalizations have separate locale policies. Non-verbal grunts/breaths may be locale-neutral only when the asset's rights and authoring manifest say so.
- Voice variants reference DATA-02 AssetId/revision, source hash, language tag, speaker/performer ID, recording provenance, rights and duration/seek/loop metadata. No direct filenames or arbitrary paths.

### 5.2 Voice scheduler
- Priority classes are proposed: accessibility audio description and critical cinematic/narrative line; mission-critical gameplay dialogue; normal conversation; barks/reactions; ambient/non-verbal voice. Exact priority ordering and mix treatment remain PROPOSED.
- Every line declares concurrency class, max instances, interruption policy (NEVER, AT_SAFE_MARKER, FADE, REPLACE_IF_HIGHER_PRIORITY), expiry/deadline, ducking profile and whether it is allowed to overlap. No hidden infinite queue.
- Dialogue can be queued, cancelled, resumed or expired by stable command/event ID and transport epoch. If a line is stolen/late/unavailable, publish a typed receipt and matching caption policy.
- Prefetch localized voice assets before dialogue windows; CORE-03/DATA-05 decode/stream outside RT. AUD-01 alone owns the playback voice and actual sample cursor.
- Dialogue subtitles bind to the same `DialogueLineIdV1` and actual playback receipt; if a voice is interrupted, captions stop/continue only according to explicit cue policy. Lip-sync uses authored viseme/phoneme markers consumed by TWO-03, not a new animation system or mandatory speech-recognition/voice-AI pipeline.

## 6. Subtitles, captions, localization and timed text
### 6.1 Distinct content modes
- **Subtitle:** spoken dialogue text in the selected language.
- **Caption / SDH:** speech plus meaningful non-speech audio such as music cues, sound effects, laughter, speaker identity and off-screen/directional cues required to understand the scene.
- **Audio description:** a separately authored narration track describing meaningful visual action, characters, scene changes and on-screen text not conveyed by dialogue/audio. It needs its own priority, transcript and mix policy.
- **Transcript / time-based media alternative:** a complete textual description of relevant synchronized content for users who cannot use captions/audio description alone.
- These are not interchangeable flags on one string. Each cue has a typed content mode, locale, speaker/source, start/end, display group, style intent and provenance.

### 6.2 Internal canonical cue model and formats
- Internal `TimedTextCueV1` is versioned and independent of vendor ABI: CueId, LineId/AssetId refs, cue kind, BCP-47 language, speaker/voice tag, start/end rational time or actual sample frame, text key/resolved text, safe inline emphasis, optional direction/sound category, display region, overlap group, source/translation revision.
- Keep subtitle, SDH, audio-description and metadata tracks separate. Preserve overlapping cues and original Unicode; do not normalize text as a hidden import side effect.
- **WebVTT** is a candidate import/export adapter for timed captions/subtitles/metadata and speaker/language spans; W3C page consulted is a **Candidate Recommendation Draft dated 2026-05-20**, not a claim that every target renderer conforms. A WebVTT file is one declared data kind; do not mix caption/subtitle/audio-description kinds in a single file.
- **TTML2** is an optional interchange adapter for authoring/distribution workflows where its XML timing/style/language model is required. It is not the canonical Stormline scene schema.
- Editor and runtime rendering must support user-controlled caption size, safe background/contrast, position, speaker labels, language, timing and non-speech descriptions. Captions must not obscure critical HUD/interaction/visual information. Text is treated as text, never executable markup.

### 6.3 Locale and fallback policy
- Locale identifiers use BCP-47 language tags with Unicode CLDR normalization/matching data. Distinguish language tag, locale/region, script and voice locale; do not hardcode a two-letter-only list.
- Dialogue text, voice recording, captions/SDH and audio description are independent assets/translation units linked by stable line/cue keys. A voice file being present does not prove transcript or caption is translated.
- Resolve exact locale first, then only the configured and visible fallback chain (e.g. pt-BR → pt → project reference locale). Return `EXACT`, `PARENT_FALLBACK`, `REFERENCE_FALLBACK`, `TEXT_ONLY` or `MISSING` receipt. Never silently replace a selected language with another locale.
- Runtime locale change is staged and committed at a safe boundary; current line may finish or be cancelled by explicit policy. No mid-phoneme asset swap, duplicate cue or mismatched caption.
- Translation status and voice recording status are versioned; machine translation/TTS is not silently used as final localized content. Human approval and source rights are required.

## 7. Cinematic timeline, cutscenes and lip-sync
- TWO-03 remains the sole owner of `SequenceAssetV1`, rational timebase, shots, animation tracks, camera intents, visual event markers and nested sequence rules. AUD-04 adds semantic audio track/cue definitions and returns playback receipts; it does not implement another timeline editor, cutscene player or clock.
- Tracks may include `MusicTrack`, `DialogueTrack`, `VoiceOverTrack`, `SfxCueTrack`, `CaptionTrack`, `AudioDescriptionTrack` and `AudioAutomationTrack`. All cues carry stable TrackId/CueId, sequence revision, rational start/end, AssetId/LineId and event policy.
- Live playback: sequence cue is translated to an AUD-01 `AudioCommandV1` sample target using `AudioClockMapV1`; actual playback/caption onset uses the accepted/audible cursor receipt. TWO-03 consumes optional authored viseme/phoneme markers at the matching rational/sample position.
- Offline export: a deterministic frame schedule and audio sample schedule share one rational sequence origin and are delivered to a separate authorized future export/mux owner. AUD-04 does not choose a host path, spawn FFmpeg, encode media or promise identical output across codec builds.
- Pause, resume, single-step, seek/scrub, time remap, skip, loop, branch, restart, scene unload and device loss each define whether music holds/fades/restarts, voice is cancelled/completed, stingers are suppressed, captions seek/recompute, and stale event generations are rejected.
- Cutscene skip/fast-forward must not fire skipped dialogue, music stingers or gameplay events twice. Gameplay/quest changes are not authorized by cinematic audio cues.

## 8. Accessibility mix, ducking and user controls
### 8.1 Accessible mix policy
- AUD-04 proposes named user profiles and control groups; AUD-01 owns actual bus/user gain application and AUD-03 owns DSP dynamics/automation. Controls are independently adjustable for dialogue, music, SFX, ambience and narration/audio description, with a safe master limit and reset-to-default.
- Support mono-compatible output/downmix and clear stereo/binaural preference reporting; never force HRTF when AUD-02/output profile says it is unavailable.
- Optional reduced-dynamic-range profile uses AUD-03 dynamics nodes after measured loudness/peak tests; it must not be described as medical hearing protection or guarantee intelligibility.
- Captions and audio description are independently selectable. Text size, background opacity, placement, speaker names and non-speech descriptions are configurable and persistent. Keyboard/gamepad/assistive navigation and focus order are UI owner responsibilities, while this module provides typed accessible settings/content.
- WCAG 2.2 time-based-media criteria are a **design reference**, not a claim of game certification or manual accessibility audit. Scope and target platform determine the applicable conformance work.

### 8.2 Ducking ownership and priority
- AUD-04 owns the **policy** (when dialogue/AD starts, target buses, priority and release conditions), AUD-03 owns the **sidechain/ducking DSP node and parameter automation**, and AUD-01 owns buses/routing/mix application.
- Proposed dialogue key input is the dialogue/AD bus or voice envelope. Targets may include music and ambience; ordinary gameplay SFX are ducked only by an explicit profile. Critical gameplay warning cues must remain audible by priority policy.
- `DuckingPolicyV1` declares depth ceiling, threshold, ratio, attack, hold, release, lookahead/latency, pre-roll and overlap arbitration. All parameters are finite, bounded and versioned. Multiple voices use max/priority/combined envelope rules declared in authoring; no uncontrolled double ducking.
- Crossfades and user volume settings combine deterministically with accessibility profile, cinematic snapshot and gameplay snapshot. No competing AUD-04/AUD-03/AUD-01 volume owners or hidden double gain.

## 9. Asset provenance, rights, security and privacy
- DATA-03 imports untrusted audio, subtitles, TTML/WebVTT and metadata in a sandbox with bounded parsing, file sizes, cue counts, duration, sample rate, channels and decompression ratio. DATA-05 cooks verified immutable banks/chunks and target codecs; AUD-04 never opens a host path or arbitrary URL.
- DATA-02 provenance records code/library license separately from composition, master recording, sound recording, performer/voice actor, translation, subtitle, music stem, cue sheet, sample library and synthetic content rights. Track territory, term, platforms, attribution, edits, sublicensing, redistribution, revocation and usage limits.
- Voice/performer consent and permitted likeness/synthetic use must be explicit. No voice cloning, synthetic voice generation, biometric inference, microphone capture or remote voice upload in this module's baseline.
- WebVTT text is rendered as safe text/limited approved inline semantics, never raw HTML/script. TTML XML parser disables DTD/external entities/network resolution and enforces depth/attribute/text limits. Malformed timestamps, overlaps, invalid BCP-47, invalid Unicode, markup injection and cue bombs return typed errors.
- Dialogue context snapshots are role-scoped and read-only; clients/MCP cannot submit arbitrary gameplay branch values or inspect hidden quest/relationship data. Server-authoritative state remains GAME/NET. No voice PCM or personal transcript appears in default telemetry.
- Avoid path traversal, archive bombs, untrusted codec plugins, unbounded event queues, audio buffer exhaustion and stale sequence/device generation. Fail with a typed fallback while preserving last safe music/voice state.

## 10. Platform and fallback model
Native Windows/Linux/macOS and headless NullSink are mandatory design targets; Web is conditional on actual browser/audio activation, supported codec, streaming and timing capabilities. Headless mode validates deterministic scheduling, receipts, caption tracks and graph decisions without an audio device/GPU; it does not prove audible output.
- Missing localized voice: configured fallback locale or explicit text-only; do not silently substitute.
- Missing music transition segment/stem: hold current valid loop or authored safe fallback.
- Missing subtitle/SDH asset: report missing translation; never hide that content was not localized.
- Missing audio device/stream: NullSink/headless receipt, keep timeline and caption schedule according to policy.
- Unsupported platform codec or media feature: capability report and approved fallback, not an OS-specific hidden dependency.
- Web browser activation/permission may prevent sound until a user gesture; captions and timeline metadata remain functional.

## 11. Future implementation slices and proof boundaries
**NECESSARY first vertical slice (future, not authorized now):** one two-section adaptive music program with one beat/bar-quantized transition and one synchronized layer; one localized dialogue line with stable LineId and caption/SDH cue; one TWO-03 cinematic audio marker scheduled through AUD-01 sample-clock receipt; dialogue ducking routed through AUD-03 sidechain/automation; one accessible mix profile and deterministic headless NullSink golden.
**IMPORTANT:** branching dialogue conditions, multi-locale voice banks, advanced stingers/transition bridges, overlapping voice priority, full audio-description workflow, timeline viseme handoff, rich caption styling and additional mix snapshots.
**FUTURE / PROVE-OR-DROP:** procedural score generation, AI/TTS/voice cloning, speech recognition, cloud voice services, live voice chat, sign-language video track, external audio middleware runtime, broad DCC interchange adapters and advanced offline media mux. Any voice-generation feature needs separate rights/privacy/safety approval.
No source code, runtime, audio assets, middleware, tests or measured performance have been delivered. ADR-0041 remains PROPOSED; future code #55 remains BLOCKED.
