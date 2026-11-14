# AUD-01 — Real-Time Audio Device, Voice and Streaming Benchmark Protocol

**P00 research only | 2026-11-14 | WO NLE-P00-WO-002-AUD-01 | issue #195 | Zero real audio benchmark/test results.**

## Questions
What callback CPU and end-to-end device latency does one authoritative Stormline f32 mixer need for 32/64/128/256 audible sources and up to 512 virtual sources across actual Windows/Linux/macOS audio backends and browser AudioWorklet? Can a bounded callback avoid heap/locks/IO and recover cleanly on source/device change? What is quality/time/CPU tradeoff of native SRC, decoder and streaming cache, and does turning off GFX change nothing about the audio sample schedule?

## Original reproducible FUTURE fixtures (not created)
- **AUDIO-PCM-01:** generated mono/stereo f32 sine 100Hz/1kHz/10kHz, impulses and silence, seeded white/pink noise, multiple levels and clipped/NaN/denormal samples; exact gain/PAN/sum/peak golden vectors. Seed, generator/build SHA, legal zero-dependency provenance.
- **AUDIO-BUS-01:** Master/Music/SFX/UI/Dialogue 5-bus DAG with two sends and protected UI/dialogue priorities; authored gain ramps, solo/mute and stream loop.
- **AUDIO-VOICE-01:** 8/32/64/128/256 simultaneous audible tones and 512 virtual sources; mixed resident/long-stream, priority stealing, re-promotion and end-of-life; reproducible per-event receipt log.
- **AUDIO-STREAM-01:** authored original WAV/FLAC/MP3/Opus content or synthetic compressed versions, 10/100/600 second stream, seek/loop and deliberate worker delay; licensing and compressed source hashes recorded.
- **AUDIO-DEVICE-01:** Windows WASAPI, Linux PipeWire/PulseAudio/ALSA/JACK, macOS CoreAudio, multi-USB/HDMI/Bluetooth switching; no false claim all are available on one test host. Loopback hardware and calibration when measuring output latency.
- **AUDIO-WEB-01:** browser AudioWorklet HTTPS, user gesture and visibility on supported engine browsers with and without SharedArrayBuffer cross-origin isolation.
- **AUDIO-HOSTILE-01:** truncated/corrupted/unbounded codec chunks, huge metadata, command floods, forged handles, high-frequency device switches and callback-after-free scenarios.
- **AUDIO-NULL-01:** offline audio trace to deterministic NullSink with fixed game tick schedule and generator history, no GPU, physical device or user input needed.

## Workload matrix and observables
| Workload | Measures | Correctness oracle |
|---|---|---|
| Device output shared/exclusive | callback p50/p95/p99 and worst, buffer frames, actual hardware API latency, dropouts/min, drift ppm | externally calibrated loopback or OS counter with uncertainty, no wall-clock FPS assumption |
| Headless NullSink | CPU samples/s, block latency, output PCM SHA & sample-error tolerance, leaks | own independent f32 mathematical golden and fixed TickToSample map |
| Voice 8→256, virtual 512 | audible/virtual CPU/heap, stealing fairness, priority, voice dropout | scheduled voice receipts and original generated PCM reference |
| Bus/FX | per-bus DAG gain/mute/pan CPU, dBFS peak/RMS, audible pops/clicks, latency | deterministic signal fixtures and harmonic energy measurement; advanced DSP remains AUD-03 |
| Resampler | 44.1→48, 48→44.1, 48→96 kHz SRC cost, passband, alias rejection, phase/group delay | source/chunk-variant independent golden, future libsamplerate reference where legal |
| Streaming | 2/16/64 simultaneous streams, rate 1x+pitch, seek/loop, delayed decoder | ring underflows, buffer occupancy/lag, correct loop position, memory cap and no RT parse |
| Device failure | 100 hotplug/suspend loops + Bluetooth/USB loss and default switch | no UAF/TSan, epoch progression and bounded audible glitches/recovery |
| Browser | 128/256/512 callback frames candidates, resume/suspend, user gesture and HTTPS | reported AudioWorklet availability, no claimed zero dropouts across browsers |
| Long endurance | 60min constant streams + asset reload, scene change, hotplug under heap cap | no orphan threads, stable memory, source generation/last-safe shutdown, counters |

## Reproducibility and thresholds
Pin exact Git SHA, vendor tag/LIC/SBOM, OS/audio backend+driver versions, CPU architecture, power/thermals, native/browser flags, device ID anonymized, driver buffer sample size, sample rates/channels, program original fixture generators/assets and cryptographic hashes, timeline rational, device clock epoch, run seed, channel map, detected priority policy and callback RT scheduling status. Repeat cold/warm N runs and record full p50/p95/p99, max, mean/variance, failed samples and xrun counters. Disclose measurement overhead, microphone/loopback permission and buffer latency vs measured physical signal latency separately.

Initial proposed `48kHz f32 stereo` and `128/256/512` block sizes are **experimental fixture options**, not guaranteed device defaults. Specific successful concurrency, max voice count, audio latency, dropouts and callback CPU thresholds **remain UNDECIDED** until baseline measured on target hardware. Samples shared for benchmark must have documented rights; microphone/loopback testing requires explicit future user permission and must not capture private audio by default.
Cross-platform bit-exact PCM is not assumed; pin floating profile/compiler and validated sample tolerances. No vendor mixing double count, no GPU requirement, no performance claims comparable to AAA engines without fair matched trials.

## Future evidence and exit
Require command transcript, source/base/head SHA, code changes, compiler/flags/build, test matrix pass/fail, measured loopback calibrations, CPU/heap plots, callback/xrun counters, quality signal graphs, device capability table, ASan/UBSan/TSan/fuzz, rights and privacy receipts, failure recovery/rollback and independent objective review. **NONE EXECUTED** in this P00 research; only GitHub Docs Validation can validate text, graph/registry and link integrity.
