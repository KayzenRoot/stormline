# AUD-03 — Reproducible Low-Latency DSP, Graph Safety and Sound Quality Benchmark Protocol

**P00 research only | 2026-11-14 | issue #201 | WO NLE-P00-WO-002-AUD-03 | ZERO benchmark runs.** No generated signals, FFT/PCM buffers, plugins, audio hardware or compiled DSP kernel in current engine.

## Questions
- Can built-in EQ/filter, dynamics and delay execute on AUD-01's single audio callback under **measured** bounded CPU, heap and underrun budgets, including denormals and 256/512-frame and unusual block sizes?
- Does graph compile/swap and RTPC automation produce sample-correct scheduling, no discontinuities/UAF, stable filters, correct channel labels and aligned wet/dry/sidechain/IR latencies?
- What is true output quality for source EQ response, compressor envelopes/gain reduction, limiter sample peak vs reconstructed true peak, distortion THD/alias, delay timing and reverb T60 using **original synthetic signals**?
- Is an external plugin bridge safe, recoverable and sufficiently low latency, or should it remain unsupported?

## Future original fixture suite (none created)
- **DSP-SIGNAL1:** legally original/generated 100Hz, 1kHz, 10kHz sine, log sweep 20Hz-20kHz, impulse, square/step, seeded white/pink noise, DC, silence, denormal, NaN/Inf/f32 overflow wave arrays. Generator script/hash, sample rate and bit depth recorded.
- **DSP-EQ1:** reference analytic RBJ biquad low/high/band-pass, notch, peaking + shelves, Q and frequency sweeps at original sample rates 44.1/48/96 kHz, reference difference equations and tolerance.
- **DSP-DYNAMICS1:** controlled envelope attack/release, threshold, ratio, knee, sidechain key, lookahead limiter and oversampled true-peak check. Signal independently computed in offline oracle.
- **DSP-DELAY1:** 10ms/100ms/1s delay rings, feedback [0, 0.5, 0.9] and illegal >1, chorus/flanger modulation, stereo crossfeed, ring crossing and ramped bypass.
- **DSP-IR1:** synthetic original 0.25s/1s/4s impulse response with independent direct linear convolution oracle; partition sizes 64/128/256/512 proposed workloads, zero stale reuse and known tail frames.
- **DSP-GRAPH1:** 4, 16, 32, 64, 128 built-in nodes in dry/wet, buses, sidechain, nested sends, versions, illegal cycles, channel errors, explicit delay feedback, and signed DATA-04 source.
- **DSP-RTPC1:** 10/100/1000 events/sec with samples mapped from CORE-04 TickId, duplicate/out-of-order/conflicting source commands, quantized segment vs sample-accurate node.
- **DSP-PLUGIN1:** mock stub that crashes, hangs, allocates, tries unauthorized file/network/PCM read; **only in a future externally isolated test harness**, never execute arbitrary downloaded plugin in production or main callback.
- **DSP-RT1:** physical or NullSink AUD-01 callback 32–512 buffer sizes and forced scheduling pressure with SOURCE epoch/DeviceEpoch changes, late graph publish and one-hour endurance.

All future fixtures newly generated with legal hash/provenance, independent reference output and no copyrighted songs, plugins, commercial IR recordings or non-public code.

## Workload/metric matrix
| Workload | Proposed condition | Evidence and oracle |
|---|---|---|
| Filter/EQ | 1/8/32 biquads, parameter sweeps, Q extremes | frequency magnitude/phase, stability/pole radius, CPU p50/p95/p99 and clip/denormal counters |
| Dynamics | 4/16 compressors and sidechains, transient threshold changes | gain-reduction envelope, attack/release/knee tolerance, reported latency and CPU |
| Limiter/saturation | sample-peak vs true-peak oversampled 4x candidate, distortion curves | measured intersample overs, THD+N and alias ratio, output peak safety and latency |
| Delay/reverb | 0.25/1/4s IR, 1/8/32 reverb effects, variable feedback | FIR convolution golden vs FFT, T60 and energy, memory ring size, tail and impulse-to-output offset |
| Graph/automation | 4→128 nodes, serial/parallel/dry-wet, 100→1000 param events/s | compilation time/memory off RT, sample-accurate vs quantized event receipt, p95/p99 callback and reported graph latency |
| Device/CPU tiers | 44.1/48/96kHz, buffer size 128/256/512 frames, x64/ARM scalar/SIMD | real callback duration vs audio block deadline, xrun count, heaps, clock drift and output correctness |
| Failure/security | malformed IR/graph, illegal cycles, plugin crash, hot reload | no buffer/heap/CPU overflow, expected typed errors, sandbox denies I/O, restored old plan, no UAF |
| Platforms | Windows/Linux/macOS native, headless NullSink, optional Web AudioWorklet | actual build/test/feature matrix, byte-vs-numeric tolerance and latency, browser activation/fallback |
| Endurance | 60min graph replacement, device switch, RTPC and IR refill | callback dropouts, memory growth, permission checks, stale generation/DeviceEpoch rejection |

## Method and evidence integrity
Pin future source Git base/head SHA, DSP algorithm/vendor exact commit SPDX/NOTICE/SBOM, source signal hash, floating-point compiler options/SIMD CPU, OS driver/backend/buffer latency/sample rate, core/core-affinity power and thermals, callback thread scheduling priority, sanitizer mode, output channel layouts, RTPC trace and exact graph profile revisions. Execute N cold/warm repeats per workload and record all failures, p50/p95/p99/max callback and worker CPU separately, total heap/state/IR bytes, xrun/min and signal analytic error bars. Identify precision of measurement tools/loopback and audio capture permission (no input/recording by default). Compare actual samples/FFT/click measurement to independent analytic/original golden, not memory of a sound.
Production CPU/latency/voice/node/IR budgets, acceptable spectral error, peak safety and external plugin startup/isolation overhead are **UNDECIDED**, to be set after a measured runtime baseline. No fixed zero-latency, guaranteed no-xrun, true-peak protection or best-of-AAA DSP claim. If latency/callback budget can't accommodate untrusted plugin bridge, feature remains disabled.
**Evidence bundle for future code:** sample/render captures, real commands, hashes/license, compiler/tests/lint/typecheck/build, xrun/RT output, fuzz/ASan/TSan, device/hot-reload recovery, best/worst cases, benchmark raw traces, pt-BR objective reviewer and rollback. This P00 performs **none** of those tests.
