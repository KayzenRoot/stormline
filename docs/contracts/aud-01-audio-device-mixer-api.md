# AUD-01 — Audio Device, Voice, Bus and Clock Semantic API v0.1

**WO NLE-P00-WO-002-AUD-01 | Research #195 | Future code issue #52 OPEN/BLOCKED**. All names are **proposed semantic contracts only**, NOT a C++ ABI, versioned wire format, implemented audio engine, native SDK wrapper or executed test.

## Contract types (versioned, owner and failure)
| Contract | Proposed fields | Validation/authority |
|---|---|---|
| `AudioEngineHandleV1` | ProjectId/WorldId, AudioEngineEpoch, slot/generation, headless flag, target capability tier | isolate world/device lives; stale world returns typed failure |
| `AudioDeviceHandleV1` | backend family/name, transient OS device key (private), public DeviceToken/epoch/generation, device profile and readiness | CORE-01 OS backend owns physical identity; hotplug invalidates epoch; no native pointer public |
| `AudioDeviceProfileV1` | preferred device class, sample format/rate/channels/layout/latency policy, shared/exclusive mode request | explicit negotiated actual profile, no guaranteed format/latency; limits and permissions |
| `AudioClockMapV1` | simulation TickId/revision, sample frame counter, numerator/denominator drift remainder, DeviceEpoch, latency estimate/uncertainty | CORE-04 TickId vs independent device clock; no wall-time sync promise |
| `AudioSourceIdV1` | DATA-02 AssetId/revision/hash, usage rights, cooked AudioCodecId, frame/channels/rate/seek/loop info | DATA-03/05 verified source, finite duration and bounded memory/ratio |
| `AudioVoiceHandleV1` | EngineEpoch, VoiceSlot/generation, AudioSourceId, World/Actor scoped owner, command sequence | stale generation and foreign producer denied, no dangling decoder pointer |
| `AudioVoiceProfileV1` | gain, playback rate, pitch mode, virtualize/steal policy, bus, loop/fade/suspend flag and priority | finite clamped parameters and quota/permissions; advance virtual playhead explicitly |
| `AudioVoiceStateV1` | Audible/Virtual/Paused/Draining/Ended, sample cursor and total frames, source revision, last accepted command | immutable post-block output, duration and virtual completion semantics explicit |
| `AudioBusHandleV1` | AudioEngineEpoch, BusGuid/revision/generation, channels/layout/priority class | correct graph owner, no cycles and quota |
| `AudioBusGraphV1` | ordered DAG, BusGuid nodes, gains/mutes/solos, send edges, layout converter, source and expected revision | DATA-04 authored CAS, finite DAG/no uncontrolled recursion, installed at RT block boundary |
| `AudioCommandV1` | ProducerId/role, WorldId, Seq, CORE-04 TickId, target sample offset and clock epoch, Play/Stop/Fade/Seek/Mute/BusChange, expected refs | non-RT authorization/dedup, bounded queue, exact monotonic order |
| `AudioMixSnapshotV1` | voice/bus states at block fence, active/virtual count, root peak/RMS/clip counter, BusGraphRevision | immutable snapshot, read only, no raw private sample bytes |
| `AudioStreamHandleV1` | AssetId/verified chunk/ring generation, decoder owner, source buffer revision, min queued frames, underflow count | DATA-05 and CORE-03 off-RT decode; never file I/O on callback |
| `AudioEventReceiptV1` | command ID/TickId/device/engine epoch, scheduled/accepted/audible/virtual/stolen/late/error, actual sample cursor, dropped reason | game event ≠ physical audible guarantee, paginated/role-redacted |
| `AudioDeviceEventV1` | device generation, unplug/default changed/rate layout/suspended/failed, old/new epoch and recovery result | CORE-01 owns native event/lifetime; never reuse stale device handle |
| `AudioCapabilitiesV1` | OS/backend/headless/Web features, actual output format, source streams, resampler, device-switch and limits | measured actual runtime support only, not assumed |
| `AudioErrorV1` | typed code, actor/device/world/voice epoch, expected/observed revision and bounded recovery hint | errors never misrepresent underrun/silence as playable sound |

## Operations and ownership
1. `InspectOutputDevices(principal, cursor, limit)` → CORE-01 device enumeration via authorized read, no capture or OS privilege.
2. `StageDeviceProfile(config, expectedRevision, principal)` → DATA-04 profile staging dry-run/CAS, no immediate device reconfiguration from MCP.
3. `OpenOutputAudioDevice(profile, engineEpoch)` → non-RT CORE-01 adapter open/negotiation, `DeviceEpoch` and output sample clock; return actual channels/rate or typed capability failure.
4. `CreateBus/StageBusGraph/StageBusGain(profile, expectedRevision, principal)` → bounded acyclic graph, DATA-04 CAS and immutable snapshot publication at RT quantum barrier; Editor/CLI/MCP parity, no effects plugins as arbitrary code.
5. `RegisterAudioSource(asset, verifiedCookSourceHash, principal)` → DATA-03/05 validated rights/codec/data; audio callback never parses unknown file.
6. `SubmitAudioCommand(actor, seq, tick, action)` → non-RT authorization/idempotence, bounded RT queue with ack; no direct raw Voice pointer or OS call.
7. `InstallMixSnapshotAtQuantumBoundary(graphRevision, voiceCommands)` → internal lock-free/epoch safe, no callback allocation/locking, CPU mixer fills preallocated buffer.
8. `ReadVoiceOrMixTelemetry(engine, cursor, limit, principal)` → CORE-06 bounded aggregated underruns, clip, active/virtual, elapsed CPU and trace; no exposure of private decoded audio or microphone.
9. `StageDecodeJob(asset, chunk, deadline)` → CORE-03 worker and DATA-05 source; ring buffer ahead with cancellation, defer/no RT codec invocation.
10. `Pause/Resume/StopVoice(handle, sampleTarget, actor)` → click-free fades or typed time/permission failure, virtual lifetime consistent, callback never blocks.
11. `HandleDeviceLostAndReopen(deviceEpoch, event)` → non-RT CORE-01 tear down with callback-read epoch guard, NullSink fallback, report new clock map and crossfade policy.
12. `OfflineMixRender(NullSink, frames, seed, eventTrace)` → future deterministic PCM golden harness, no audio device or GPU required; source/build fingerprints mandatory.
13. `ShutdownAudioEngine(engine)` → stop command acceptance, cancel workers, drain RT callback barrier, retire generations and only then free memory/device; bounded failure status.

## Error codes (future)
`AUDIO_DEVICE_UNAVAILABLE`, `AUDIO_DEVICE_LOST`, `AUDIO_DEVICE_EPOCH_STALE`, `UNSUPPORTED_LAYOUT`, `SAMPLE_RATE_UNSUPPORTED`, `CLOCK_DRIFT_LIMIT`, `AUDIO_CALLBACK_BUDGET`, `MIX_UNDERRUN`, `RING_OVERRUN`, `COMMAND_QUEUE_FULL`, `STALE_VOICE`, `STALE_BUS`, `BUS_GRAPH_CYCLE`, `SOURCE_RIGHTS_MISSING`, `SOURCE_REVISION_MISMATCH`, `DECODER_ERROR`, `CODEC_UNSUPPORTED`, `STREAM_PREFETCH_LATE`, `VIRTUAL_VOICE_EXPIRED`, `UNAUTHORIZED_AUDIO_COMMAND`, `INVALID_PCM`, `NONFINITE_GAIN`, `UNTRUSTED_CODEC_INPUT`, `LIMIT_EXCEEDED`, `BROWSER_AUDIO_NOT_ACTIVATED`, `CAPTURE_NOT_AUTHORIZED`, `INTERNAL_FAILURE`.

## Mandatory invariant and risk constraints
- **No blocking/IO/allocation/decoding/logging in RT callback**; hard real-time OS guarantees not claimed. All controls via bounded queues; max worst-case measured on real hardware in future work.
- CORE-04 simulation TickId is not sample clock. DeviceEpoch+ratios map tick to sample frames; device change must not reuse sample counter or native handle across epochs.
- No graphical FPS, GPU, spatial renderer, webcam/mic permission or device selector outside CORE-01 can determine authoritative gameplay.
- Audio output underrun is recorded with silence/typed receipt, not a completed audible event. Virtual voice advances cursor but consumes no full mixing CPU, with explicit protected priority and starvation policy.
- No raw decoder/library pointers or copyrighted sound buffers in Engine Public API; legal source identity and rights independently tracked. Runtime implementation pins exact serialization/ABI/OS capability only with approved ADR and code WO.
