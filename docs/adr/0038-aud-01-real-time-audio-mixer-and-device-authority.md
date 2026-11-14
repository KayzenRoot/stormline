# ADR-0038 — Stormline-owned Real-Time Mixer, Replaceable Device Backend and Bounded Voice Lifecycles

**STATUS: PROPOSED / NOT APPROVED FOR CODE**  
**Date:** 2026-11-14 | Research #195 | WO NLE-P00-WO-002-AUD-01 | Future coding #52 OPEN/BLOCKED.

## Context
The engine needs a deterministic *semantic* schedule of game sound requests while consumer hardware has an independent device callback clock. Device disconnect, sample-rate and layout renegotiation, streaming underruns, game pause, resource quotas and web restrictions cannot be handled by faking sample ticks from frame FPS. SDL3 and miniaudio are promising APIs but should not own Stormline mixer/bus/voice public semantics. Realtime callback safety and audio user privacy are central threats. No engine/runtime audio exists.

## PROPOSED decisions
1. **Stormline owns stable semantic contracts** for `AudioWorld`, `AudioDevice`, `DeviceEpoch`, `AudioVoice`, `MixBus`, `BusSnapshot`, `AudioEventIntent/Receipt`, `AudioClockMapping`, `StreamSource` and `AudioCapabilities`, not vendor SDL/miniaudio pointers/types. DATA-04 owns asset graph persistence, CORE-01 OS/device lifecycle and CORE-03 decode jobs.
2. **Single owner for mixing:** own f32 mixer and validated DAG routing (gain/pan/simple sends/voice priority), one PCM interleaved/planar backend adapter stream. SDL3's own stream mixing is a comparator not a second independent summing layer. Advanced DSP graph is AUD-03 and spatialization is AUD-02; do not duplicate.
3. **Realtime constrained by construction:** callback does only bounded preallocated PCM mixing and counter updates, no blocking locks, filesystem/network/device enumeration, log, allocation, decoding or dynamic object mutation. Non-RT control serializes commands into bounded queue and installs immutable revisioned graph snapshots at block fence. Audio output underflow writes initialized silence and reports failure.
4. **Independent audio clock:** monotonic sample frames per DeviceEpoch, rational validated mapping from CORE-04 `TickId` to audio frame position, explicit nominal latency/drift/uncertainty; simulation and render never directly advance hardware callback clock. Epoch rebase on hotplug/sample-rate changes and bounded smoothing/click-free ramps.
5. **Voice arbitration:** generational VoiceHandle, per-bus/owner prioritization, explicit audible vs virtual state (virtual voice time advances without mixing), bounded channel/memory/decoder/voice budgets and cancellation receipts. Critical dialogue/UI priority protection requires owner-authored policy; never skip gameplay event solely due inaudible audio.
6. **Backend adapter assessment:** SDL3 zlib or miniaudio Unlicense/MIT-0 are **LEADING ALTERNATIVE CANDIDATES, NOT ADOPTED**; PortAudio MIT and cubeb ISC-like are comparators. Use only one audio output backend at a time per device, and avoid duplicate mixing/resampling. Web browser AudioWorklet is a platform-specific future adapter with user activation/secure-context restrictions.
7. **Streaming and codecs:** DATA-03/05 owns trusted import/cooked chunks; dr_libs and Opus candidates only, pin content licenses/codecs and run decoders on CORE-03 workers off callback. Codec/format vulnerabilities require strict size/count bounds and future fuzz/sanitizer proof. Sample content licensing independent of code licensing.
8. **Privacy/security:** output playback only initially; microphone recording/voice chat/loopback capture OUT OF SCOPE. Read-only paged telemetry and authorized Studio commands via shared Editor/CLI/MCP; no arbitrary remote URL, priv-body decode, script, microphone permission, or OS device reconfiguration without user consent.
9. **Portability/quality:** native Win/Linux/macOS and optional WASM Web AudioWorklet, always CPU/headless NullSink. No fixed latency, zero-xrun, sample-exact synchronization across Bluetooth devices or cross-OS identical floating samples assumed. Baselines/thresholds and legality/SDK choice after measured code and platform feature tests.

## Rejected
- Treating CORE-04 fixed tick as callback sample clock or letting render FPS drive audio.
- Doing FFT, filesystem, codec decode, allocations, locks or synchronous multi-device hotplug in realtime callback.
- Letting SDL mix a full set of streams **and** Stormline buses independently sum the same sources without strict design.
- Assuming browser AudioWorklet always available without HTTPS, user activation or proper message/shared memory design.
- Permanently pinning a physical OS endpoint identifier across hotplug, or asserting no dropouts under audio driver interruption.
- Microphone capture by default or exposing private device/source content to untrusted MCP.
- Declaring source audio assets free to redistribute because their decoder is permissively licensed.

## Consequences and approval gates
Additional adapter and queue/snapshot complexity buys independent mixer semantics, replaceability and headless testing; low-latency claims require real device measurement. Future ELEVATED-risk code must prove RT no-wait/no-alloc safety, benign device-loss/recovery, stream/content security, channel/resampler quality, multi-device drift, actual native/Web feature profile and license SBOM plus independent audit and rollback. No backend selected, vendor installed, output recorded, runtime tested or latency measured. **ADR remains PROPOSED; all 80 implementation packets BLOCKED; AUD-01 #52 remains OPEN/BLOCKED.**
