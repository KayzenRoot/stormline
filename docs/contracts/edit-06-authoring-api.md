# EDIT-06 — Sequencer, VFX, Audio and Animation Typed Authoring API v0.1

**P00 RESEARCH PROPOSAL ONLY | 2026-11-15 | [#272](https://github.com/KayzenRoot/stormline/issues/272) | BASE `67e6af436f4985474b2e6dc5aa47183c32113230`.** Logical contracts, not compiled ABI/schema/runtime. EDIT-06 owns UI/authoring intent; TWO-03 sequence source; GFX-08, AUD-03/AUD-04, SIM-04, AUD-01 and CORE-04 own runtime semantics/receipts.

## 1. Owner types
| Proposed type | Invariants | Owner |
|---|---|---|
| `SequenceAssetV1` | SequenceId/revision, rational timebase, stable TrackIds, nested clip refs, duration and source digest | TWO-03 canonical; EDIT-06 edits through owner |
| `SequenceTrackRefV1` | TrackId, type ANIMATION/VFX/AUDIO/MUSIC/DIALOGUE/CAPTION/MARKER, AssetId/revision, priority/policy | TWO-03 structure; domain owner validates |
| `SequenceClipViewV1` | ClipId, source ref, rational start/duration, trim/range, loop/reverse/seek policy | TWO-03 source; EDIT-06 view |
| `SequenceMarkerV1` | MarkerId, rational time, typed owner cue ref, event epoch/idempotency | TWO-03 timeline; owner acknowledges |
| `SequencePlaybackPolicyV1` | SIMULATION_MASTER/AUDIO_MASTER_PREVIEW/OFFLINE_EXPORT, pause/seek/loop/reverse and tie-break | TWO-03 |
| `SequencePresentationStateV1` | timeline zoom/pan, lane heights, grouping, selection, waveform view, layout version | EDIT-06/EDIT-01, separate runtime digest |
| `AnimationTimeV1` | signed64 numerator, positive denominator or exact frame/timebase, explicit rounding | TWO-03 |
| `TickId` / `SimulationTimeMapV1` | CORE-04 fixed tick, epoch, rational sequence mapping and remainder | CORE-04 |
| `AudioClockMapV1` / `SampleFrameId` | AUD-01 DeviceEpoch, sample rate, frame anchor, rational mapping/remainder, drift status | AUD-01 actual device clock |
| `SequenceSyncReceiptV1` | sequence time, TickId, requested/accepted SampleFrameId, DeviceEpoch, mapping error/unknown/stale | CORE-04/AUD-01 |
| `VfxGraphBindingV1` | GFX-08 VFX AssetId/revision, graph digest, seed, budget/quality and target | GFX-08 |
| `VfxPreviewReceiptV1` | graph revision, evaluator version, seed/tick range, CPU/GPU mode, budget/degrade/fence status | GFX-08/GFX-03 |
| `DspGraphBindingV1` | AUD-03 graph AssetId/revision, BusGuid/insert, sample rate/layout and parameters | AUD-03/AUD-01 |
| `DspExecutionPlanReceiptV1` | graph hash, DeviceEpoch, immutable plan, latency/tail/scratch budget, quantum activation | AUD-03/AUD-01 |
| `MusicProgramBindingV1` | AUD-04 ProgramId/revision, segment/stem/tempo map and transition rules | AUD-04 |
| `CinematicAudioTrackV1` | TrackId, SequenceId/revision, rational timebase, MUSIC/DIALOGUE/VO/SFX/CAPTION/AD/AUTOMATION cue refs | AUD-04 semantics, TWO-03 lanes |
| `TimedTextTrackV1` | locale, cue IDs/start/end, speaker/kind/subtitle/SDH/audio-description and safe text/style | AUD-04/DATA-04 |
| `AudioScheduleReceiptV1` | requested/accepted/actual SampleFrameId, DeviceEpoch, late/drop/fallback/underrun, audible UNKNOWN unless measured | AUD-01/AUD-04 |
| `AnimationGraphBindingV1` | SIM-04 AnimationGraph revision, SkeletonHash, clips, graph parameters and target instance | SIM-04 |
| `AnimationPreviewReceiptV1` | graph revision, TickId, pose digest, transitions, marker receipts, root intent and SIM-03 acceptance | SIM-04/SIM-03 |
| `Edit6CommandInvocationV1` | EditorCommandIdV1, GUI/shortcut/palette/CLI/MCP origin, actor capability, ProjectId, refs/revisions, idempotency | EDIT-01 and owner authorization |
| `Edit6CommandReceiptV1` | accepted/rejected/cancelled, owner, transaction, revision, preview/clock/runtime receipts and safe error | each owner |
| `Edit6TransactionV1` | staged typed diff, actor, expected revisions, preview digest, DATA-04 journal/CAS, undo domain | DATA-04; no assumed cross-owner ACID |
| `Edit6ErrorV1` | stable stage/code, safe track/clip/node/state locator, retryable, epoch/revision, redacted diagnostics | owner-specific |

## 2. Shared buttons and commands
All buttons register with EDIT-01 `EditorCommandIdV1`. Metadata: localized label/description, role/name, tooltip, enabled predicate/disabled reason, icon+text, shortcut, focus/IME, origin, project capability, undo domain, busy/progress/cancel and confirmation. Owner validates permission/revision even if UI disables. CLI/MCP uses same command.

| CommandId candidate | Input -> output | Permission / side effect |
|---|---|---|
| `edit6.sequence.save` / `edit6.sequence.undo` / `edit6.sequence.redo` | SequenceId/revision and owner undo token -> DATA-04 receipt | WRITE_SEQUENCE; CAS refuses stale overwrite |
| `edit6.sequence.track.add` / `edit6.sequence.clip.edit` / `edit6.sequence.marker.add` | typed track/clip/cue + rational time -> TWO-03 preview/receipt | only owner-approved track type |
| `edit6.transport.play` / `edit6.transport.pause` / `edit6.transport.stop` | playback master and sequence epoch -> transport receipt | PREVIEW_SESSION, isolated session |
| `edit6.transport.step` / `edit6.transport.scrub` / `edit6.transport.loop` | rational time/frame/tick -> owner seek receipt | explicit seek/loop semantics and event dedup |
| `edit6.sync.inspect` / `edit6.sync.configure` | sequence/tick/sample profile -> mapping report | owner clock permissions; no invented drift |
| `edit6.vfx.node.add` / `edit6.vfx.node.connect` / `edit6.vfx.preview` | GFX-08 NodeId/PortId/revision/seed -> owner validation/preview | WRITE_VFX/PREVIEW_VFX, bounded graph/budget |
| `edit6.audio.dsp.node.add` / `edit6.audio.dsp.connect` / `edit6.audio.dsp.validate` | AUD-03 graph IDs/revision -> DSP validation/plan | WRITE_DSP, immutable off-RT compile |
| `edit6.audio.music.transition.edit` / `edit6.audio.dialogue.cue.edit` / `edit6.caption.cue.edit` | AUD-04 cue/line/locale/sample policy -> owner receipt | WRITE_CINEMATIC_AUDIO, rights/locale/sample checks |
| `edit6.animation.state.add` / `edit6.animation.transition.add` / `edit6.animation.parameter.set` | SIM-04 GraphId/StateId/ParameterId + TickId -> owner receipt | WRITE_ANIMATION, bounded guards, no script eval |
| `edit6.validate.all` / `edit6.preview.run` / `edit6.preview.cancel` | owner refs/revisions/target/time range -> separate receipts | PREVIEW_SESSION, cancel/last-good |
| `edit6.budget.report` / `edit6.export.preview` / `edit6.export.commit` | target/destination grant -> budget/loss report/package receipt | DATA-01/05 authorization and readback |

## 3. Distinct graph semantics
- TWO-03 SequenceAsset is rational ordered track/clip timeline, not graph evaluator.
- GFX-08 VFX is bounded effect DAG with CPU reference and optional GPU path; GPU not gameplay authority.
- AUD-03 DSP is finite DAG; zero-delay cycles rejected, feedback only explicit bounded delay; immutable plan off RT and swap at AUD-01 quantum boundary.
- AUD-04 adaptive music graph has state/transition rules, beat/bar/sample quantization and deterministic fallback; not DSP or mixer.
- SIM-04 AnimationGraph is state machine/blend/pose evaluator with TickId guards; state transitions may cycle but remain bounded/deterministic. RootMotionIntent requires SIM-03 acceptance.
- Shared graph UI does not imply common schema, validator, scheduler or runtime.

## 4. Clock and transport invariants
Rational sequence time maps to CORE-04 TickId and AUD-01 SampleFrameId using checked exact conversions/remainders and explicit rounding. Audio receipts distinguish requested/accepted/actual sample frame, DeviceEpoch, late/drop/underrun and audible UNKNOWN. Offline export derives frames and samples from one rational origin. Device/rate change, world reload, seek/reverse/loop/skip/restart invalidates stale schedules and advances generation. Cue IDs/idempotency prevent duplicate voice, particle or animation markers. Play/pause/step/scrub/loop never mutate authoritative gameplay state.

## 5. Runtime parity and error states
`LOAD_OWNER_SOURCE -> VALIDATE_SOURCE_REVISION -> PREPARE_OWNER_EVALUATORS -> MAP_RATIONAL_TIME -> DISPATCH_TYPED_CUES -> OWNER_EVALUATE -> COLLECT_OWNER_RECEIPTS -> PRESENT_PREVIEW`. Cancel/device loss/stale revision retains last-good and releases only owned leases. Preview identifies evaluator version, source digest, seed, TickId/sample frame, target and device generation.

Error examples: `E06_SEQUENCE_REVISION_CONFLICT`, `E06_RATIONAL_OVERFLOW`, `E06_DEVICE_EPOCH_STALE`, `E06_AUDIO_SYNC_UNKNOWN`, `E06_CUE_DUPLICATE`, `E06_OWNER_RUNTIME_UNAVAILABLE`, `E06_VFX_BUDGET_EXCEEDED`, `E06_DSP_ZERO_DELAY_CYCLE`, `E06_AUDIO_RT_BUDGET_EXCEEDED`, `E06_ANIMATION_STATE_LIVELOCK`, `E06_ROOT_MOTION_NOT_ACCEPTED`, `E06_GRAPH_SCHEMA_UNSUPPORTED`, `E06_MEDIA_RIGHTS_UNKNOWN`, `E06_CAPABILITY_DENIED`, `E06_PREVIEW_STALE`, `E06_EXPORT_NOT_VALIDATED`, `E06_RECOVERY_REQUIRED`.

No arbitrary script/plugin/path/URL/audio callback pointer/GPU handle/direct world mutation through graph or MCP. Media parsers are untrusted/quota-limited. Use DATA-01 scoped VFS, DATA-03 import sandbox, DATA-02 rights, DATA-04 CAS/journal, DATA-05 receipts, CORE-06 redacted logs and owner authorization.

[Architecture](../architecture/edit-06-vfx-audio-animation-authoring.md) · [ADR-0058](../adr/0058-edit-06-unified-sequencer-vfx-audio-animation-authoring.md) · [128 tests](../testing/edit-06-acceptance-matrix.md) · [Benchmark](../research/edit-06-authoring-benchmark-protocol.md).
