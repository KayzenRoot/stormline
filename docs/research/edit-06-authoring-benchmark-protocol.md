# EDIT-06 — Reproducible Sequencer, VFX, Audio, Animation and Runtime-Parity Benchmark Protocol

**P00 proposal, NOT EXECUTED | 2026-11-15 | [#272](https://github.com/KayzenRoot/stormline/issues/272) | code #73 BLOCKED.** No editor/runtime binary, sequence evaluator, DSP callback, particle simulator, animation pose evaluator, native/Web preview, measured latency, GPU/audio output or accepted budget exists.

## 1. Environment and clock manifest
Pin engine/editor SHA, owner evaluator versions, schema/node registry, OS/window system, CPU/RAM, GPU/driver/VRAM, audio device/backend/sample rate/block size, browser/WebGPU/WebAudio adapter, display DPI, timebase/FPS, seed, asset/license hashes, locale/voice, DeviceEpoch, TickId and trace ID. Separate offline/null-device from realtime audio/GPU preview. Record cold/warm cache. Use 3 independent runs/seeds and 30 warmups; >=1000 observations for p99. Keep raw traces and digests.

## 2. Fixtures
| Fixture | Scale/content | Measurements |
|---|---|---|
| SQ-01 | 20 tracks, 100 clips, 24000/1001, nested cue markers | scrub/seek/edit, rational conversion, source digest |
| SQ-02 | 100 tracks, 1k clips, 10k markers, mixed 24/30/60/24000/1001 | layout/selection, event order, memory/p99 |
| SQ-03 | nested sequences depth 1/4/8, loop/reverse/seek | overflow/quota, epoch/idempotency |
| VF-01 | GFX-08 graph 32/128/512 nodes, 1k/10k/100k particles | CPU reference, GPU, spawn, overdraw, VRAM, degradation |
| AU-01 | AUD-03 DSP graph 16/32/128/512 nodes, 1/2/4/8 channels | callback quantum, XRUN, latency/tail, scratch/memory |
| AU-02 | AUD-04 1/8/32 stems, 100/1k dialogue/caption cues, tempo changes | sample mapping, transitions, voice count, caption sync |
| AN-01 | SIM-04 2/20/100 states, 100/1k/10k keys, 1/10/100 skeleton instances | tick evaluation, pose, allocation and event dedup |
| SY-01 | sequence with VFX, DSP, music, dialogue, captions and animation | A/V sync, owner receipts, preview/runtime parity |
| EX-01 | OTIO, glTF animation, WebVTT/TTML2 supported/unsupported fixtures | round-trip hashes, loss report, rights/export time |
| SC-01 | hostile media, malformed graphs, infinite transition, invalid rational, stale handles | parser CPU/RSS, callback safety, recovery |

Synthetic stress fixtures may be generated, but GUI-only acceptance must create tracks/nodes/transitions/captions/markers through actual editor UI, no manual source-file edit.

## 3. Metrics
- Sequencer: input-to-paint/transport p50/p95/p99, tracks/clips/markers, rational conversion, dirty region, undo bytes, save/reopen.
- VFX: spawn/particle/sort/draw, CPU/GPU/VRAM, overdraw, emitters, fallback, degradation and preview/runtime tolerance.
- DSP: callback worst-case/percentiles per quantum, allocations target zero, locks/IO target zero, XRUN, latency/tail, scratch memory, compile/swap time.
- Music/dialogue: requested/accepted/actual SampleFrameId, DeviceEpoch, beat/bar quantization, voice count, late/drop/underrun and loopback latency where measured.
- Animation: TickId evaluation, pose sampling, transitions, blend/IK, retarget memory, root intent/acceptance and duplicate events.
- Parity: compare source/schema/evaluator digests, seed, rational time, TickId/sample frames, owner receipts and pose/PCM/VFX output. GPU visuals use approved tolerance; event/time must match owner contract.
- Platform/a11y: Windows, Linux X11/Wayland, macOS Apple Silicon, WebGPU/WebAudio; keyboard, screen reader, captions/SDH, reduced motion/flash, text scale and device loss.

## 4. Fault injection
Crash editor during clip trim/multi-asset staging; crash VFX compile; lose GPU; hotplug/change audio rate during music/dialogue; starve callback; inject DSP zero-delay cycle/oversized IR; infinite animation transition; invalidate skeleton/AssetId; seek/loop during cue; corrupt caption markup; cancel export; disk full during DATA-04/05; race CLI/MCP edit; fuzz import/nested sequence. Verify last-good, receipts, no duplicate events, no world mutation, no RT allocation/lock, journal recovery and rights manifest.

## 5. Thresholds
Numeric limits for tracks, nodes, particles, DSP callback, XRUN, audio latency, sync drift, VRAM, animation instances, nesting, file size and p50/p95/p99 are **TBD** until measured on declared hardware and owner-approved release tiers. Do not infer zero glitches from unit tests or scheduling timestamps. No competitor superiority claim without matched licensed fixtures and repeatable runs.

At P00: editor builds 0; sequence/runtime evaluator builds 0; audio runs 0; particle runs 0; animation runs 0; parity tests 0; benchmark samples 0; E06 tests 128 NOT EXECUTED.

[Tests](../testing/edit-06-acceptance-matrix.md) · [Technology matrix](edit-06-authoring-technology-license-matrix.md) · [Architecture](../architecture/edit-06-vfx-audio-animation-authoring.md).
