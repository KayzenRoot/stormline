# TWO-03 — Typed Animation, Rig, State Machine, Timeline and Sync API v0.1

**Research WO NLE-P00-WO-002-TWO-03 | #153 | Future code #39 OPEN/BLOCKED**  
Conceptual semantic contract only. **NO C++ ABI, compiled evaluator, running AUDIO mixer, encoder, timeline editor, Web codec or real animation**.

| Proposed type | Stable fields / semantics | Hard validation and owner boundary |
|---|---|---|
| `AnimationTimeV1` | rational signed64 numerator + positive denominator OR exact frame count/timebase, explicit rounding | reduced fractions, checked intermediates, no float accumulated wall drift |
| `AnimationClipV1` | ProjectId/ClipId/revision, duration, timebase, key/curve tracks and rights | DATA-04 revision + DATA-03 provenance and clip bounds |
| `AnimationKeyframeV1` | stable KeyId, rational timestamp, typed value/curve/tangent, interpolation | ordered time, finite derivatives, no arbitrary script property |
| `FlipbookTrackV1` | per-frame SpriteAssetId+revision, duration/hold, atlas reference, loop policy | TWO-01 sprite/atlas owner, source gutter/UV not duplicated |
| `Skeleton2DV1` | SkeletonId/revision, stable BoneId parent DAG, rest pose and bind transforms, max depth | no cycles/nonfinite, CORE math; WORLD owns game root |
| `BonePosePlanV1` | pose at rational time, slot/skin transforms, local/world output, hierarchy epoch | CPU pure evaluation reference, no direct GPU pointer |
| `SkinMesh2DV1` | mesh, Sprite/Material refs, vertex/index counts, influences/weights, deformation and resource epoch | GFX-03 owns buffers/fences, GFX-05 material and Canvas order |
| `IkConstraint2DV1` | bounded target BoneId, chain, tolerance/iterations, clamp/unreachable policy | no recursive solve/broken chain; no physics authority |
| `AnimationBlendTreeV1` | graph stable NodeId, clip inputs, normalized weights/1D params/masks and additive mode | DAG evaluation; discrete flipbook policy, bounded cost |
| `AnimationStateMachineV1` | states/transition edges, parameter types, priorities, interruption/exits and tick guards | bounded transitions and no arbitrary eval/livelock |
| `AnimationCueV1` | CueId/revision, rational time+phase, one-shot/loop/seek/reverse policy, owner/priority | idempotency key+epoch; AUDIO/VFX/GAME owners acknowledge |
| `SequenceAssetV1` | SequenceId/revision, rational timebase, TrackIds, nested clip refs, camera/cutscene tracks | DATA-04 transactional rights, bounded nesting/time warp |
| `SequencePlaybackPolicyV1` | master mode SIMULATION/AUDIO_MASTER_PREVIEW/OFFLINE_EXPORT, seek/pause/loop/reverse | source of truth+tie-break, audio device drift may be UNKNOWN |
| `SequencePoseSnapshotV1` | time, clip revision/seed, bone/sprite draw+track targets, event intent list | no mutation of authoritative gameplay state or Canvas manager |
| `AudioCuePlanV1` | AudioAssetId, bus, rational start/end, requested sample offset/gain envelope and rights | AUDIO owner owns device clock, decode/mix/latency |
| `AudioScheduleReceiptV1` | audio-owner accepted sample position and actual/estimated/unknown latency + underrun, generation | never claim scheduled cue equals audible hardware proof |
| `SequenceExportPlanV1` | frame-rate rational, frame indexes/time values, image size/color, audio-sample manifest, codec preset/rights | export/FFmpeg separate owner; not encoded media file |
| `TimelineQualityReceiptV1` | scene/timeline/rig rev, CPU eval cost, GPU skin plan cost, event count, clock+sample drift measured/ESTIMATED/UNKNOWN | attach actual provenance, no fabricated latency/frame accuracy |
| `TimelineEditTransactionV1` | project/ClipId or SequenceId, expected revision, staged typed edits and DATA-04 journal token | project role, CAS, rollback, append-only audit |

## Exact time conversion proposal
For source frame `f` at frame rate `num/den`, rational second time `t=f * den/num`. Sample index at audio rate `sr` is `round_policy(f * den * sr/num)` with checked wide intermediate and explicit `round_policy`. Non-integer rates (24000/1001), long timelines and differing audio rates must not accumulate frame-by-frame float error. **Rational time predicts target sample index; AUDIO hardware sync requires actual clock ACK**.

## Deterministic event and editor semantics
Pure `EvaluatePoseAt(clip_rev, time, parameter_snapshot)`, `EvaluateSequenceAt(sequence_rev,time,...)`, `BuildSequenceExportPlan`, `GetTimelineSyncReceipt` should not execute user code or trigger effects as a side effect. Separate `DispatchSequenceCues(playback_epoch, previous_tick, next_tick,seek_policy)` produces owner-approved bounded event intents and idempotent ack keys. Reverse/seek/loop crossing and replay choose explicit `FIRE_ON_CROSSING / SCRUB_PREVIEW_ONLY / SUPPRESS / AUTHORITATIVE_REPLAY` policy per cue type; never duplicate audio/hit markers on dropped frames.

Editor/CLI/MCP (future): `InspectAnimationClip`, `InspectSkeleton2D`, `InspectSequence`, `PreviewTimelinePose`, `PreviewSequenceFrameSchedule`, `InspectSyncSchedule`, `StageAnimationEdit`, `ValidateAnimationEdit`, `CommitAnimationEdit`, `CancelTimelineOperation`, all expected version/project access/data rights with DATA-04 journaling. No direct host command, global project scan or custom script/event handler input; static schedule preview not actual encoded media.

## Typed failures
`ANIM_TIME_OVERFLOW`, `ANIM_TIMEBASE_INVALID`, `ANIM_NONFINITE_CURVE`, `ANIM_KEYFRAME_ORDER_INVALID`, `ANIM_ASSET_NOT_FOUND`, `FLIPBOOK_ATLAS_STALE`, `RIG_BONE_CYCLE`, `RIG_WEIGHTS_INVALID`, `RIG_IK_UNREACHABLE`, `RIG_DEVICE_UNSUPPORTED`, `ANIM_BLEND_GRAPH_CYCLE`, `ANIM_TRANSITION_LIMIT`, `ANIM_EVENT_REPLAY_CONFLICT`, `SEQUENCE_NESTING_LIMIT`, `TIMELINE_PROPERTY_DENIED`, `AUDIO_CLOCK_UNAVAILABLE`, `AUDIO_SYNC_NOT_VERIFIED`, `SEQUENCE_EXPORT_CODEC_UNAPPROVED`, `SEQUENCE_EXPORT_RIGHTS_DENIED`, `VFX_CUE_BUDGET_EXCEEDED`, `ANIM_REVISION_CONFLICT`, `CAPABILITY_DENIED`, `CANCELLED`, `RECOVERY_REQUIRED`. Return safe failing stage, retryability, redacted metadata and owner.

## Freeze before implementation
Final ABI/timebase/encoding schema/asset ID, owner-authorized CODE scope/release DoD; implemented TWO-01, DATA-04, AUDIO+EXPORT interfaces, vendor binary/codec SBOM if ever needed, CPU/audio-clock cross-platform platform tests, measured frame/sample error tolerance, exact C++ files, raw-file SHA-256 Context Lock and independent audit. ADR-0024 PROPOSED, issue #39 BLOCKED, all 80 code WOs executor_ready=false.
