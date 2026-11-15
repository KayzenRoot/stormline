# AUD-04 — Acceptance Matrix: 128 FUTURE Tests, NONE EXECUTED

**Research issue #204 | WO NLE-P00-WO-002-AUD-04 | Future coding #55 OPEN/BLOCKED.** Exactly **128 prospective cases** (16 suites × 8). All are **FUTURE / NOT EXECUTED**. Catalog acceptance "Troca de estado musical sem glitches, acessibilidade e fallback" is **NOT MET** by this research. No music program, VO asset, subtitle renderer, cinematic playback, device output, mixer or benchmark exists.

| Case | Prospective test | Status |
|---|---|---|
| AUD04-MUS-01 | Ambient→combat switches at the declared next bar with correct source exit/destination entry marker | FUTURE / NOT EXECUTED |
| AUD04-MUS-02 | Explicit transition segment bridges two incompatible harmonic/phrase sections | FUTURE / NOT EXECUTED |
| AUD04-MUS-03 | Missing transition rule returns authored fallback or holds current loop, never arbitrary silence | FUTURE / NOT EXECUTED |
| AUD04-MUS-04 | Stinger quantizes to the next declared beat and is not replayed after duplicate EventId | FUTURE / NOT EXECUTED |
| AUD04-MUS-05 | Immediate transition interrupts only when policy permits and applies click-safe fade | FUTURE / NOT EXECUTED |
| AUD04-MUS-06 | Source/destination phase and loop-point mismatch is rejected before schedule publish | FUTURE / NOT EXECUTED |
| AUD04-MUS-07 | Transition prefetch miss keeps current safe loop and reports MUSIC_ASSET_NOT_READY | FUTURE / NOT EXECUTED |
| AUD04-MUS-08 | Pause/stop/restart increments transport generation and rejects stale queued transitions | FUTURE / NOT EXECUTED |
| AUD04-TMP-01 | Tempo marker changes BPM at exact authored beat/bar boundary using rational arithmetic | FUTURE / NOT EXECUTED |
| AUD04-TMP-02 | Time signature change maps bar numbering and pickup beats without cumulative drift | FUTURE / NOT EXECUTED |
| AUD04-TMP-03 | 23.976 (24000/1001) sequence frame converts to sample frame with bounded rounding rule | FUTURE / NOT EXECUTED |
| AUD04-TMP-04 | 48 kHz and 44.1 kHz mappings retain exact rational remainder over long timeline | FUTURE / NOT EXECUTED |
| AUD04-TMP-05 | DeviceEpoch/sample-rate change invalidates pending old sample targets and recompiles mapping | FUTURE / NOT EXECUTED |
| AUD04-TMP-06 | CORE-04 TickId intent maps through AUD-01 AudioClockMap without becoming audio clock | FUTURE / NOT EXECUTED |
| AUD04-TMP-07 | No tempo marker uses only explicit author default; never implicit guessed tempo | FUTURE / NOT EXECUTED |
| AUD04-TMP-08 | Overflow/negative duration/zero denominator/invalid BPM return typed errors | FUTURE / NOT EXECUTED |
| AUD04-STM-01 | All stems start at same declared SampleFrameId and retain phase | FUTURE / NOT EXECUTED |
| AUD04-STM-02 | Optional layer fades in/out without altering base segment loop position | FUTURE / NOT EXECUTED |
| AUD04-STM-03 | Required stem unavailable prevents unsafe transition and reports fallback | FUTURE / NOT EXECUTED |
| AUD04-STM-04 | Stem group with mismatched BPM/time signature/loop start rejected | FUTURE / NOT EXECUTED |
| AUD04-STM-05 | Crossfade across loop wrap does not duplicate or skip samples | FUTURE / NOT EXECUTED |
| AUD04-STM-06 | Intensity automation is bounded, smoothed and deduplicated | FUTURE / NOT EXECUTED |
| AUD04-STM-07 | Random stem selection replays identically with fixed project/program seed | FUTURE / NOT EXECUTED |
| AUD04-STM-08 | Voice/stem count budget rejects excessive simultaneous layers | FUTURE / NOT EXECUTED |
| AUD04-STA-01 | Combat/tension/boss state changes resolve from immutable GAME snapshot revision | FUTURE / NOT EXECUTED |
| AUD04-STA-02 | Client-supplied forged quest or boss state cannot trigger authoritative score change | FUTURE / NOT EXECUTED |
| AUD04-STA-03 | Rapid state oscillation is suppressed by hysteresis/minimum dwell | FUTURE / NOT EXECUTED |
| AUD04-STA-04 | Higher-priority cinematic/victory event wins deterministic tie-break | FUTURE / NOT EXECUTED |
| AUD04-STA-05 | Expired or stale state intent is rejected without changing transport | FUTURE / NOT EXECUTED |
| AUD04-STA-06 | Same event ID/revision is idempotent across replay/rollback | FUTURE / NOT EXECUTED |
| AUD04-STA-07 | Random transition selection is stable for same recorded seed and event order | FUTURE / NOT EXECUTED |
| AUD04-STA-08 | Unknown state/parameter uses explicit authored default or typed fallback | FUTURE / NOT EXECUTED |
| AUD04-DIA-01 | Exact typed argument path resolves correct DialogueLineId and variant | FUTURE / NOT EXECUTED |
| AUD04-DIA-02 | Missing argument resolves authored default path only | FUTURE / NOT EXECUTED |
| AUD04-DIA-03 | No default path returns DIALOGUE_VARIANT_UNAVAILABLE | FUTURE / NOT EXECUTED |
| AUD04-DIA-04 | Dialogue resolver cannot mutate quest/inventory/relationship/game state | FUTURE / NOT EXECUTED |
| AUD04-DIA-05 | Context snapshot revision mismatch rejects stale branch resolution | FUTURE / NOT EXECUTED |
| AUD04-DIA-06 | Sensitive quest/relationship arguments are redacted from telemetry and unauthorized caller | FUTURE / NOT EXECUTED |
| AUD04-DIA-07 | Non-verbal voice line follows explicit locale-neutral policy | FUTURE / NOT EXECUTED |
| AUD04-DIA-08 | Line selection is deterministic with recorded context and weighting seed | FUTURE / NOT EXECUTED |
| AUD04-VOI-01 | Critical cinematic line is not stolen by ambient bark at concurrency cap | FUTURE / NOT EXECUTED |
| AUD04-VOI-02 | Interruptible bark fades at approved safe marker when higher-priority line arrives | FUTURE / NOT EXECUTED |
| AUD04-VOI-03 | NEVER interrupt dialogue remains active until end or explicit sequence cancellation | FUTURE / NOT EXECUTED |
| AUD04-VOI-04 | Expired queued line reports VOICE_EXPIRED and does not play after scene change | FUTURE / NOT EXECUTED |
| AUD04-VOI-05 | Duplicate voice command does not spawn duplicate AudioVoiceHandle | FUTURE / NOT EXECUTED |
| AUD04-VOI-06 | Missing/prefetch-late localized line follows configured fallback/text-only policy | FUTURE / NOT EXECUTED |
| AUD04-VOI-07 | Voice start receipt aligns caption start to actual AUD-01 sample cursor | FUTURE / NOT EXECUTED |
| AUD04-VOI-08 | Voice concurrency and decoder prefetch stay within per-target memory/voice quotas | FUTURE / NOT EXECUTED |
| AUD04-LOC-01 | Valid BCP-47 language-script-region tag resolves exact localized voice and caption | FUTURE / NOT EXECUTED |
| AUD04-LOC-02 | pt-BR requested with configured pt fallback returns explicit PARENT_FALLBACK receipt | FUTURE / NOT EXECUTED |
| AUD04-LOC-03 | Unconfigured fallback to another language is rejected, not silently substituted | FUTURE / NOT EXECUTED |
| AUD04-LOC-04 | Voice file exists but translated caption missing reports incomplete bundle | FUTURE / NOT EXECUTED |
| AUD04-LOC-05 | Locale switch during active dialogue follows finish/cancel safe-boundary policy | FUTURE / NOT EXECUTED |
| AUD04-LOC-06 | New locale bundle CAS conflict does not partially replace old locale | FUTURE / NOT EXECUTED |
| AUD04-LOC-07 | CLDR data version/pinning change is recorded in build/content fingerprint | FUTURE / NOT EXECUTED |
| AUD04-LOC-08 | Right-to-left, CJK, combining marks and long text survive import/render without normalization loss | FUTURE / NOT EXECUTED |
| AUD04-TXT-01 | Subtitle track contains spoken dialogue only and remains distinct from SDH captions | FUTURE / NOT EXECUTED |
| AUD04-TXT-02 | SDH cue includes meaningful non-speech sound and speaker identity | FUTURE / NOT EXECUTED |
| AUD04-TXT-03 | Overlapping cues preserve order, timing and overlap-group policy | FUTURE / NOT EXECUTED |
| AUD04-TXT-04 | WebVTT import/export roundtrip preserves cue times, kind and safe speaker spans | FUTURE / NOT EXECUTED |
| AUD04-TXT-05 | One WebVTT file cannot mix caption/subtitle/audio-description data kinds | FUTURE / NOT EXECUTED |
| AUD04-TXT-06 | TTML external DTD/entity/network payload is rejected before parsing | FUTURE / NOT EXECUTED |
| AUD04-TXT-07 | Invalid timestamp, nested markup, huge cue count and malformed Unicode are bounded/rejected | FUTURE / NOT EXECUTED |
| AUD04-TXT-08 | Actual voice interruption updates the caption according to explicit stop/continue policy | FUTURE / NOT EXECUTED |
| AUD04-ACC-01 | Caption text size/background/position preferences persist and can be reset | FUTURE / NOT EXECUTED |
| AUD04-ACC-02 | Non-speech audio and off-screen direction are represented in SDH mode | FUTURE / NOT EXECUTED |
| AUD04-ACC-03 | Audio description track is independently selected and scheduled | FUTURE / NOT EXECUTED |
| AUD04-ACC-04 | Transcript/time-based alternative includes dialogue, visual description and relevant non-speech cues | FUTURE / NOT EXECUTED |
| AUD04-ACC-05 | Dialogue/music/SFX/ambience/narration sliders operate independently through AUD-01 | FUTURE / NOT EXECUTED |
| AUD04-ACC-06 | Mono output profile preserves dialogue intelligibility and critical cues | FUTURE / NOT EXECUTED |
| AUD04-ACC-07 | Reduced-dynamic-range profile uses AUD-03 approved graph and has measured output, not a medical claim | FUTURE / NOT EXECUTED |
| AUD04-ACC-08 | Keyboard/gamepad/accessibility navigation exposes caption and audio options without focus trap | FUTURE / NOT EXECUTED |
| AUD04-DUC-01 | Dialogue onset triggers one AUD-03 sidechain policy on approved music/ambience targets | FUTURE / NOT EXECUTED |
| AUD04-DUC-02 | Attack/hold/release envelope matches configured ramp and does not zipper | FUTURE / NOT EXECUTED |
| AUD04-DUC-03 | Critical gameplay warning SFX remains protected from standard dialogue ducking | FUTURE / NOT EXECUTED |
| AUD04-DUC-04 | Audio-description priority ducks target buses under explicit accessibility policy | FUTURE / NOT EXECUTED |
| AUD04-DUC-05 | Overlapping dialogue lines combine by deterministic max/priority envelope, not double attenuation | FUTURE / NOT EXECUTED |
| AUD04-DUC-06 | Ducking policy graph revision mismatch returns typed stale receipt | FUTURE / NOT EXECUTED |
| AUD04-DUC-07 | User music volume and cinematic snapshot compose deterministically with ducking | FUTURE / NOT EXECUTED |
| AUD04-DUC-08 | Dialogue stop/cancel releases attenuation and restores exact base mix without click | FUTURE / NOT EXECUTED |
| AUD04-CIN-01 | TWO-03 rational cue at 24000/1001 maps to expected AUD-01 sample target | FUTURE / NOT EXECUTED |
| AUD04-CIN-02 | Actual audio start receipt is used to align dialogue caption, not requested command time | FUTURE / NOT EXECUTED |
| AUD04-CIN-03 | Pause/resume does not duplicate stingers or captions | FUTURE / NOT EXECUTED |
| AUD04-CIN-04 | Seek/scrub recomputes active music/voice/caption cue state at new sequence position | FUTURE / NOT EXECUTED |
| AUD04-CIN-05 | Skip/fast-forward cancels skipped one-shots and never triggers gameplay mutations | FUTURE / NOT EXECUTED |
| AUD04-CIN-06 | Loop boundary replays only cues explicitly marked LOOP_RETRIGGER | FUTURE / NOT EXECUTED |
| AUD04-CIN-07 | Device loss/reopen increments epoch and rejects stale cutscene audio cues | FUTURE / NOT EXECUTED |
| AUD04-CIN-08 | Offline frame schedule and audio sample schedule share one rational origin | FUTURE / NOT EXECUTED |
| AUD04-LIP-01 | Authored viseme markers map to correct line asset hash and TWO-03 sequence revision | FUTURE / NOT EXECUTED |
| AUD04-LIP-02 | Voice asset reimport with changed hash invalidates stale phoneme marker track | FUTURE / NOT EXECUTED |
| AUD04-LIP-03 | Missing viseme track falls back to non-lip-synced animation without blocking dialogue | FUTURE / NOT EXECUTED |
| AUD04-LIP-04 | Seek/scrub recomputes viseme state at current voice sample cursor | FUTURE / NOT EXECUTED |
| AUD04-LIP-05 | Two dialogue lines with same speaker do not leak previous viseme state | FUTURE / NOT EXECUTED |
| AUD04-LIP-06 | No untrusted speech recognition or automatic voice inference runs in baseline | FUTURE / NOT EXECUTED |
| AUD04-LIP-07 | Marker offsets beyond clip duration are rejected | FUTURE / NOT EXECUTED |
| AUD04-LIP-08 | Viseme event queue is bounded, deduplicated and not tied to render FPS | FUTURE / NOT EXECUTED |
| AUD04-AST-01 | Music composition/master/stem rights are distinct from code-library license | FUTURE / NOT EXECUTED |
| AUD04-AST-02 | Voice actor consent/likeness rights/locale/territory/term are recorded on AssetId revision | FUTURE / NOT EXECUTED |
| AUD04-AST-03 | Unlicensed or revoked VO/music asset cannot be cooked into shipping bundle | FUTURE / NOT EXECUTED |
| AUD04-AST-04 | DATA-03 audio importer validates duration, channels, sample rate and decompression quotas | FUTURE / NOT EXECUTED |
| AUD04-AST-05 | DATA-05 prefetch/decode deadline miss returns explicit fallback without RT file I/O | FUTURE / NOT EXECUTED |
| AUD04-AST-06 | Same source bytes/options/importer version yield equivalent semantic import receipt | FUTURE / NOT EXECUTED |
| AUD04-AST-07 | Locale bank hot swap retires old chunk only after AUD-01 stream/voice references drain | FUTURE / NOT EXECUTED |
| AUD04-AST-08 | User-created audio bundle remains project-scoped and cannot escape VFS namespace | FUTURE / NOT EXECUTED |
| AUD04-SEC-01 | WebVTT text/script-like payload is rendered as safe text and never executed | FUTURE / NOT EXECUTED |
| AUD04-SEC-02 | TTML XML external entity, DTD, entity expansion and deep nesting are rejected | FUTURE / NOT EXECUTED |
| AUD04-SEC-03 | Oversized subtitle cue/locale/branch graph is quota-rejected before publish | FUTURE / NOT EXECUTED |
| AUD04-SEC-04 | Malicious audio/container header/decompression bomb cannot exhaust RAM/CPU | FUTURE / NOT EXECUTED |
| AUD04-SEC-05 | MCP/CLI cannot issue arbitrary GAME context or raw SampleFrame commands | FUTURE / NOT EXECUTED |
| AUD04-SEC-06 | No microphone capture, voice upload, cloning or biometric inference is enabled by default | FUTURE / NOT EXECUTED |
| AUD04-SEC-07 | Voice/PCM/transcript content is absent from telemetry absent explicit privacy policy | FUTURE / NOT EXECUTED |
| AUD04-SEC-08 | Stale sequence/device/voice epoch and replayed command are rejected idempotently | FUTURE / NOT EXECUTED |
| AUD04-PLT-01 | Windows x64 native NullSink schedule and PCM golden test | FUTURE / NOT EXECUTED |
| AUD04-PLT-02 | Linux x64/ARM native schedule and codec/capability fallback | FUTURE / NOT EXECUTED |
| AUD04-PLT-03 | macOS x64/ARM audio device switch/reopen and sample-rate epoch | FUTURE / NOT EXECUTED |
| AUD04-PLT-04 | Web Audio user-gesture activation failure keeps captions/timeline usable | FUTURE / NOT EXECUTED |
| AUD04-PLT-05 | Web codec unsupported path uses declared fallback, not hidden proprietary decoder | FUTURE / NOT EXECUTED |
| AUD04-PLT-06 | Headless server resolves music/dialogue/caption state without GPU or sound device | FUTURE / NOT EXECUTED |
| AUD04-PLT-07 | Channel layouts mono/stereo/surround are explicitly mapped without hidden channel swap | FUTURE / NOT EXECUTED |
| AUD04-PLT-08 | Suspend/resume and streaming cancellation do not leak voices, banks or stale cues | FUTURE / NOT EXECUTED |
| AUD04-BEN-01 | 16 synchronized stems plus transition matrix CPU p50/p95/p99 and peak memory | FUTURE / NOT EXECUTED |
| AUD04-BEN-02 | Concurrent 4/8/16/32 dialogue voices and stream prefetch budget benchmark | FUTURE / NOT EXECUTED |
| AUD04-BEN-03 | Long-running tempo map and sample-clock drift over 30/60 minutes | FUTURE / NOT EXECUTED |
| AUD04-BEN-04 | Transition/crossfade loopback or offline PCM golden detects discontinuity and duplicate frames | FUTURE / NOT EXECUTED |
| AUD04-BEN-05 | Caption-vs-actual-voice start/end offset measured in sample frames | FUTURE / NOT EXECUTED |
| AUD04-BEN-06 | Ducking attack/release and protected SFX envelope measured against golden | FUTURE / NOT EXECUTED |
| AUD04-BEN-07 | Rapid locale/device/sequence changes plus one-hour soak reports leak/drop/fallback | FUTURE / NOT EXECUTED |
| AUD04-BEN-08 | Reproducible replay and offline cinematic export records build/source/fixture/codec hashes | FUTURE / NOT EXECUTED |

## Evidence and pass/fail contract
- **Unit:** rational tempo/time conversion, transition graph and fallback, deterministic state selection, dialogue argument matching, locale fallback, caption parser, cue ordering, ducking envelope, accessibility profile validation.
- **Integration:** AUD-01 actual sample-clock/voice/bus receipts, AUD-02 spatial profile, AUD-03 DSP sidechain/automation/snapshot, TWO-03 rational sequence/viseme markers, CORE-04 TickId mapping, DATA-02/03/04/05 assets/rights/cook/prefetch, GAME/NET authoritative snapshots.
- **Security:** malformed audio/TTML/WebVTT, XML external entities, cue/event bombs, path traversal, invalid locale, privacy/voice rights, role/epoch/replay, no script or arbitrary external middleware.
- **Audio quality:** original generated music stems, known beat/loop markers, deterministic test tones/voice-like synthetic fixtures (no real actor), crossfade continuity, sample peak/true peak and loudness measurement, no duplicate/skipped frames, caption/voice offset, mono and reduced-range profile.
- **Performance:** callback and worker CPU p50/p95/p99, voice/stem concurrency, decoded/streaming memory, prefetch lateness, underruns/xruns, schedule jitter, long-run tempo/sample drift and device recovery.
- **Accessibility:** caption visibility/readability/placement, SDH speaker/sound coverage, audio description track, independent mix controls, mono/downmix, reduced dynamic range, keyboard/gamepad and assistive UI navigation. WCAG 2.2 is a design reference; no certification is implied.
- **Missing evidence today:** no case passed, no generated PCM/music/VO/caption asset, no engine build or runtime, no measured latency, no accessibility user test, no device loopback, no benchmark values. Docs Validation validates repository docs/registry only.
