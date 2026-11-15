# AUD-04 — Reproducible Adaptive Music, Dialogue, Cinematic Sync and Accessibility Benchmark Protocol

**P00 research only | 2026-11-14 | issue #204 | WO NLE-P00-WO-002-AUD-04 | ZERO benchmark runs.** No adaptive music engine, voice playback, subtitle renderer, timeline integration, audio assets or device output has been implemented.

## Questions to prove in a future runtime
1. Can horizontal music resequencing and vertical stem changes hit authored beat/bar/sample targets without clicks, gaps, duplicates or phase drift?
2. Does dialogue resolution/scheduling keep critical VO available, respect priority/interrupt policy and produce captions aligned to the **actual** AUD-01 voice cursor?
3. Can TWO-03 rational cutscene time, AUD-01 sample clock and offline frame schedule remain aligned across 24000/1001, 24, 25, 30, 50, 60 fps and 44.1/48/96 kHz?
4. Does dialogue/audio-description ducking apply one bounded AUD-03 sidechain policy while preserving critical gameplay warnings and user volume choices?
5. Are locale fallback, WebVTT/TTML import/export, SDH/audio-description and mono/reduced-range profiles complete and accessible?
6. Are voice/music assets prefetched and streamed without callback I/O, excessive memory, privacy leak or unlicensed content?

## Original legal fixtures (none generated)
- **MUS-REF1:** original synthesized 4/4 and 3/4 stems, known BPM/tempo change, loop points, entry/exit markers, bridge segment and stinger; distinct phase and deliberately mismatched stems.
- **MUS-REF2:** seeded original multi-layer score with quiet/exploration, tension, combat and victory layers; fixed random seed and expected transition state trace.
- **VO-REF1:** synthetic test tones/envelopes and generated non-human placeholder voice waveform; authored line IDs, speaker IDs, actual sample starts/ends and transcript fixtures. No actor recording or synthetic voice clone.
- **TXT-REF1:** legally original multilingual strings, BCP-47 locale variants, SDH non-speech cues, speaker/direction cues, audio description and long/CJK/RTL/combining-mark strings; WebVTT and TTML fixtures with malicious variants.
- **CINE-REF1:** original rational sequence timeline with 24000/1001, 24, 25, 30, 50 and 60 fps tracks; audio cue/voice/caption/viseme markers and seek/loop/skip/device-loss traces.
- **DUCK-REF1:** original test signal with controlled dialogue/AD envelopes and critical warning cues; expected attack/hold/release and target bus curves.
- All fixtures carry source/license manifest, source hash, generator version, expected independent oracle, no copyrighted soundtrack, commercial voice recording or third-party dialogue.

## Workload and metrics
| Workload | Proposed load | Required evidence |
|---|---|---|
| Music transport | 2/8/16/32 stems, 4/16/64 transitions, tempo changes and loops | exact requested/accepted/actual SampleFrameId, beat/bar drift, phase and loop continuity, crossfade discontinuity/peak |
| Music state | 10/100/1000 state/RTPC events per minute, competing priorities | deterministic resolver trace, hysteresis/dwell, queue overflow, fallback and CPU |
| Dialogue/VO | 4/8/16/32 concurrent voices, barks+critical lines, interruption and expiry | actual voice start/end cursor, queue wait, stolen/late/underrun counts, decoder memory and CPU |
| Captions/localization | 1/2/8 simultaneous cues, locale bundles and long strings | cue-vs-actual-voice offset in samples, parse/resolve latency, locale fallback counts, memory |
| Cinematic sync | 1/10/30-minute sequences, multiple frame rates, seek/loop/skip and audio master | frame-to-sample mapping error, cumulative drift, duplicate/missed cue count, actual output latency |
| Ducking/accessibility | dialogue/AD overlap, critical SFX, profile switching | sidechain envelope, target dB attenuation, recovery and protected cue audibility, mono/range profile output |
| Streaming/device | cold/warm locale bank load, chunk prefetch, device rate/loss/reopen | prefetch deadline misses, stream under/overruns, memory/IO, stale epoch rejections and fallback |
| Endurance/replay | 60-minute continuous transport, scene changes, locale switches, fixed seed replay | deterministic event sequence, leaks, xrun count, clock drift, asset/voice retirement and crash recovery |

## Method and reporting
Record exact Git base/head SHA, runtime/backend/OS/CPU/architecture, sample rate/channel layout/block size, device profile and driver, callback deadline, voice/stem/asset counts, source/rights hashes, import/cook/compiler versions, tempo/timebase rational values, deterministic seed, locale/CLDR version, sequence and device epochs, audio loopback permission and capture chain.
Run separate cold/warm, offline NullSink and physical-device loopback profiles. Repeat each workload; report p50/p95/p99/max CPU and schedule jitter, callback duration/xruns, stream underruns, voice queue wait, sample scheduling error, crossfade peak discontinuity, memory high-water, cue/caption offset, tempo drift and fallback counts. Include the raw event trace and original reference PCM, not only a dashboard screenshot.
Thresholds for sample offset, acceptable discontinuity, loudness, speech intelligibility, stream lead time, max stems/voices, callback budget and memory are **UNDECIDED**; set them only after a real baseline on minimum target hardware and independent golden oracles. Do not promise "zero glitches", sample-exact audible output or cross-platform bit-identical PCM from documentation.
**Future Evidence Bundle:** original fixture hashes/provenance, source/rights, build/test/lint/typecheck, native/Web/headless results, output captures, p50/p95/p99 and xrun traces, caption/accessibility matrix, fuzz/sanitizer/security tests, fallback/recovery and objective pt-BR audit. This P00 has none of those artifacts.
