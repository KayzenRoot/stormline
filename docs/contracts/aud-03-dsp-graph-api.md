# AUD-03 — DSP Effect Graph, Automation and RT Rendering Semantic Contract v0.1

**Research issue #201 | WO NLE-P00-WO-002-AUD-03 | Future coding issue #54 OPEN/BLOCKED.** **PROPOSED SEMANTICS ONLY**, not compiled public C++ API, library ABI, sample/audio output or shipping serialization schema.

## Typed versioned contracts
| Type | Candidate fields | Authority and validation |
|---|---|---|
| `DspGraphHandleV1` | AudioEngineEpoch, DspGraphGuid/revision/generation, attached AUD-01 BusGuid/VoiceHandle, ProjectId, source AssetId/hash | AUD-01 owns lifecycle/PCM, DATA-04 CAS for authored graph; reject foreign/stale handles |
| `DspNodeDescriptorV1` | NodeGuid/type/schema, I/O ports/layouts, sample rate range, max block size, state/scratch bytes, latency/tail, bypass policy, capability tier | allowlisted native built-in types ONLY baseline, no arbitrary executable plugins |
| `DspPortV1` | PortGuid/type AUDIO/CONTROL/SIDECHAIN, channel labels/count, rate and permitted adaptation, producer/consumer IDs | graph compiler checks type, channel maps, fan-in/out and no missing ports |
| `DspEdgeV1` | FromNode/Port to ToNode/Port, send role, gain/mapping, latency compensation, edge revision | finite DAG, no zero-delay cycles, verified bus route ownership |
| `DspGraphSourceV1` | AssetId, graph revision, node/edge lists, topological constraints, effects/tail policy, author role and licenses | DATA-03/04 validated authoring, exact source and rights fingerprint |
| `DspExecutionPlanV1` | DspGraphGuid+hash, DeviceEpoch, SampleRate/ChannelLayout, ordered node schedule, allocated buffer offsets, max scratch, latency/tail, bounded worst work | compiled off-RT CORE-03, immutable verified, atomic swap at AUD-01 quantum boundary |
| `DspProcessBlockV1` | DeviceEpoch, AudioFrameStart, FrameCount, BufferSpan and layout, ParameterSegmentRefs, underrun state, event markers | realtime AUD-01 owner supplies preallocated spans only, no scene/files/OS pointer |
| `DspParameterIdV1` | DspNodeGuid+ParamGuid/revision, name/unit, min/default/max, normalization map, smoothing policy, sample/control-rate capability | schema/role validated, no hidden raw dsp code/direct memory access |
| `DspAutomationEventV1` | ActorId/authority epoch, TickId and/or SampleFrameId, DeviceEpoch, sequence, ParameterId, target, curve/ramp duration/mode and expected revision | authorized GAME/AUD-04/EDIT producer, bounded event count, dedup and clamped floats |
| `DspAutomationLaneV1` | Ordered sample-frame targets, curve segments, control-rate granularity, event priority, combining/preemption rules | precompiled CORE-03 for RT consumption; no unlimited per-frame interpolation objects |
| `DspSidechainV1` | KeySource Bus/Voice, role visibility, channel layout, delay alignment, envelope source revision | AUD-01 authorized source, no private client exposure or invalid feedback |
| `DspSnapshotV1` | Graph+Param revisions, param preset/RTPC blend rules, fade window, cumulative latency/tail, source data rights | immutable off-RT; snapshots AUD-01 buses not duplicated |
| `DspEffectStateV1` | NodeGuid+generation, filter coefficients and bounded state, gain envelopes, DelayRing handle, IR/FIR partition state hashes | preinitialized/off-RT, deferred retirement after callback epoch |
| `DspImpulseResponseV1` | DATA-05 AssetId/hash/provenance, source room Acoustics AUD-02 revision, sample rate/channels/length, partition count/max bytes | no automatic HRTF dataset licensing, validated max length and source rights |
| `DspLatencyTailReceiptV1` | Plan revision, each-node latency, graph compensation and max tail, measured vs estimated frames and fallback reason | no false zero latency; AUD-01 owns output sync accounting |
| `DspParameterReceiptV1` | EventId, requested/applied target, requested/actual AudioFrame, DeviceEpoch, quantized/smoothed/late/drop reason | immutable paged, actor-redacted, no claim sample-accurate when control-rate |
| `DspGraphReceiptV1` | graph source hash, accepted/active/replaced plan, bounded error, RT budget quality tier, clipping/NaN/denormal count, published epoch | evidence of compilation vs actual RT apply separate, not fake completion |
| `DspCapabilitiesV1` | native/Web/headless, built-in effects, plugin isolated support, sample-accurate automation, max nodes/taps/latency, actual device profile | advertise **measured** capabilities only |
| `DspErrorV1` | code, graph/node/port/param, expected/actual revision, last safe plan and recoverability, redacted diagnostic | no vendor ABI or private PCM payload exposed |

## Semantic operations
1. `StageDspGraph(graph, expectedSourceRevision, principal)` → authenticated common Editor/CLI/MCP DATA-04 CAS, schema+rights, static node list, port/channel/rate layout validation and dry-run.
2. `CompileDspPlan(graph, profile, expectedDeviceEpoch)` → CORE-03 non-RT topological sort, cycle/latency/sidechain/tail/CPU/heap estimation, prealloc ring/scratch/IR FFT plan; no third-party code loaded by default.
3. `StageDspNodeParameter(param, expectedRevision, principal)` → validate unit/range and finite value, compile smoothing/ramp off-RT; no raw callback state mutation.
4. `StageDspAutomation(lane, expectedRevision, principal)` → map CORE-04 TickId to AUD-01 sample clock rationally, enforce max segment count, deterministic precedence, duplicate idempotency, allowed parameter roles.
5. `SubmitAuthorizedDspRtpc(actor, tick, target, curve)` → trusted GAME/AUD-04 command route, verify source authority and quota; no unauthenticated remote/MCP raw PCM effects.
6. `PublishDspPlanAtAudioQuantum(plan, expectedGraphAndDeviceEpoch)` → AUD-01 callback fence with immutable state, bounded crossfade/latency compensation and old-buffer retirement ack; return accepted vs pending/failed.
7. `ProcessDspAudioBlock(plan, AudioFrameStart, Span, Params)` → RT-internal bounded prealloc processing, finite safety, no wait/allocation/IO/log/FFT plan creation.
8. `ReadDspTelemetry(graph, cursor, principal)` → CORE-06 post-RT safe redacted CPU/clip/denormal/latency/tail/events per node, never raw private audio or editor secret.
9. `StageDspImpulseResponse(ir, expectedAssetRevision, principal)` → DATA-03/05 validates licensed IR/audio and memory cap; AUD-02 owns acoustic geometry selection, CORE-03 non-RT partition precompute.
10. `RequestEffectBypass(node, rampFrames, actor)` → click-free wet/dry/crossfade, explicit latency/tail and failure; cannot grant gameplay effects.
11. `StageExternalPluginBridge(descriptor, rights, principal)` → **FUTURE, unsupported until separately approved** capability gate, never direct native arbitrary path loads; required sandbox and crash/timeout/cost evidence.
12. `DetachDspGraph/RecoverDeviceEpoch` → stop events, freeze last safe mute/dry plan, retire state after AUD-01 callback ack, recompile sample-rate-specific plan off-RT, release DATA asset/IR leases.

## Typed errors and invariants
`UNAUTHORIZED_DSP_COMMAND`, `INVALID_NODE_SCHEMA`, `UNKNOWN_NODE_TYPE`, `PORT_LAYOUT_MISMATCH`, `BUS_OWNER_CONFLICT`, `SIDECHAIN_UNAUTHORIZED`, `GRAPH_CYCLE`, `ZERO_DELAY_FEEDBACK`, `UNBOUNDED_TAIL`, `INVALID_SAMPLE_RATE`, `INVALID_COEFFICIENT`, `POLE_UNSTABLE`, `NAN_OR_INF_GAIN`, `DELAY_OUT_OF_RANGE`, `IR_SOURCE_RIGHTS_MISSING`, `IR_BUDGET_EXCEEDED`, `AUTOMATION_OVERFLOW`, `PARAMETER_REVISION_STALE`, `CLOCK_EPOCH_MISMATCH`, `STALE_GRAPH_HANDLE`, `STALE_NODE_GENERATION`, `RT_BUDGET_EXCEEDED`, `GRAPH_SNAPSHOT_PENDING`, `PLUGIN_DISABLED`, `PLUGIN_ISOLATION_UNPROVEN`, `PLUGIN_TIMEOUT`, `ALLOCATION_IN_REALTIME`, `DEVICE_RECONFIGURATION_PENDING`, `DSP_BACKEND_UNSUPPORTED`, `CAPABILITY_UNAVAILABLE`, `INTERNAL_FAILURE`.

- AUD-01 remains sole owner of PCM mixing, devices and sample clock, RT schedule; AUD-03 cannot reown voice/bus lifecycle or bypass audio output validation.
- Each active plan version must be immutable for a full audio quantum; no raw lib/plugin pointer/public ABI. Callback only finite preallocated work, no host I/O/allocation/lock/block.
- No zero-delay graph feedback; if a graph change fails or is too expensive, keep last safe plan or bounded dry bypass and emit a typed receipt.
- Output clipping/NaN/DC and dangerous gain must fail closed/limiter policy with explicit algorithm and measured quality; sample-peak limiter ≠ true-peak limiter.
- CODE/third-party plugin source license, per-asset licenses and privacy role checked independently, no dynamic native untrusted code accepted by baseline.
- Schemas are **not implemented, versioned serialized layouts or final public ABI**. Exact fields/limits, callback grain and wire bytes require separately approved coding WO.
