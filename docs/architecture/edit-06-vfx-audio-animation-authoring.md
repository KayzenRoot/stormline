# EDIT-06 — VFX / Audio / Animation Authoring Architecture v0.1

**2026-11-15 | P00 RESEARCH ONLY | [#272](https://github.com/KayzenRoot/stormline/issues/272) | NLE-P00-WO-002-EDIT-06 | code [#73](https://github.com/KayzenRoot/stormline/issues/73) OPEN/BLOCKED | BASE `67e6af436f4985474b2e6dc5aa47183c32113230`.** Catalog 55/80, research 54/80, 26 pending, all 80 coding WOs BLOCKED. Formal dependencies EDIT-02, GFX-08, AUD-04 and SIM-04 are documentary/ADR PROPOSED only. No editor, sequencer, graph runtime, audio playback, particle simulation, animation runtime or export exists.

## 1. Mission and acceptance
Catalog scope: sequencers/timelines, particle editor, audio graphs, state machines. Acceptance: **"Editor e modo runtime reproduzem mesmo conteúdo."** EDIT-06 owns editor presentation, authoring UX, track/lane/graph views, transport controls, selection/inspector and isolated preview controls. It does not own timeline evaluation, particle simulation, DSP/mixer, music state, skeletal animation, simulation/audio clocks, physics root motion or GPU resources.

**Core rule:** editor and runtime load the same versioned source assets and invoke the same owner runtime evaluators. No editor-only duplicate evaluator, timeline, clock, mixer, VFX runtime or animation state machine. Preview is a sandboxed session around the actual owner evaluator.

## 2. Formal dependencies and integration owners
| Owner | Canonical authority | EDIT-06 boundary |
|---|---|---|
| **EDIT-02 (formal)** | ProjectId, project mode, capabilities and scoped VFS root | project/actor scope and safe destination grants |
| **GFX-08 (formal)** | typed VFX/particle graph, CPU reference/optional GPU simulation, budgets/degradation | graph authoring, emitter/parameter inspection and preview through GFX-08 |
| **AUD-04 (formal)** | adaptive music programs/transitions, dialogue/VO, cinematic cues, timed text and accessibility mix | music/dialogue/caption/viseme cue authoring |
| **SIM-04 (formal)** | 3D skeleton/clip/AnimationGraph, state/blend/retarget/IK, root-motion intent and pose/event receipts | edit animation graph/clip/parameters; root motion remains SIM-03-authorized |
| AUD-03 (integration, NOT a new formal edge) | DSP graph, realtime nodes, immutable execution plan, automation and sample-block processing | edit DSP graph source; never mutate live callback or build a second mixer |
| TWO-03 (integration, NOT a new formal edge) | rational SequenceAssetV1, AnimationTimeV1, tracks/clips/cues, playback policy/snapshots | timeline UI edits through TWO-03; no second timeline schema/evaluator |
| AUD-01 / CORE-04 | physical audio device/mixer/SampleFrameId/DeviceEpoch; authoritative TickId/time | exact sample/tick mapping; no render-FPS or wall-clock |
| EDIT-01 / CORE-01 | shared shell, command registry, panels, keyboard/focus/IME/accessibility | host all panels/buttons and command origins |
| DATA-02/03/04/05 | AssetIds/rights, safe import, source schema/CAS/journal/migration, cooked/export packages | owner receipts; no raw paths or private asset database |
| GFX-01/03/06/07 | device capability/generation, render resources/fences, lighting, camera/color | preview only through owner leases/receipts |
| SIM-02/03, GAME/NET/WORLD | physics/contact, accepted character movement, authoritative gameplay/network state | cues/root motion are typed intents, never gameplay truth |
| EDIT-07 / QA-04 / AI-MCP | isolated play/debug, secure SDLC, public command authorization | preview/debug handoff and same permissions |

**Formal DAG remains exactly EDIT-02 + GFX-08 + AUD-04 + SIM-04.** AUD-03 and TWO-03 are integration owners already referenced by predecessor contracts, not new direct edges. EDIT-01, CORE-04, AUD-01, DATA, GFX, EDIT-07, QA-04 and EDIT-05 are integration owners. Research issues #256/#144/#204/#183 are closed; code issues #69/#36/#55/#49 remain OPEN/BLOCKED; EDIT-06 code #73 OPEN/BLOCKED.

## 3. Unified workspace, distinct graph semantics
Shared EDIT-01 shell, command metadata, navigation, diagnostics and graph canvas interactions do not imply one generic graph schema/evaluator.

| View | Canonical owner | Semantics |
|---|---|---|
| Sequencer/multi-track timeline | TWO-03 | rational ordered tracks/clips/cues and playback policy |
| VFX/particle graph | GFX-08 | bounded typed effect DAG, CPU reference, optional GPU; not gameplay authority |
| Audio DSP graph | AUD-03 | finite DSP DAG; feedback only through explicit approved delay; immutable plan at AUD-01 quantum boundary |
| Adaptive music transition graph | AUD-04 | state/transition rules, beat/bar/sample quantization, deterministic priority/fallback |
| Dialogue/timed text | AUD-04 | localized lines, voice/cue timing, subtitles/SDH, speaker and audio description |
| Skeletal animation graph | SIM-04 | state machine, bounded tick transitions, blend trees, pose/events; root motion intent |
| 2D/cinematic animation tracks | TWO-03 | existing sequence/clip semantics, not duplicated SIM-04 skeleton graph |

A common graph canvas is only an interaction component. Do not flatten VFX DAG, DSP DAG, adaptive music transition graph and animation state machine into one evaluator. State-machine cycles are not DSP feedback; DSP feedback needs explicit delay; VFX preserves finite budgets.

## 4. Timeline, clocks and cross-domain events
- Canonical sequence time is TWO-03 AnimationTimeV1: exact rational numerator/positive denominator or frame/timebase, checked arithmetic and explicit rounding. Rates such as 24000/1001 cannot accumulate float drift.
- CORE-04 TickId is simulation time. AUD-01 AudioClockMapV1/SampleFrameId/DeviceEpoch is the only output clock. Map sequence rational time to both through owner-defined rational mapping/remainder; report UNKNOWN when drift/latency is not measured.
- Explicit master policy: SIMULATION_MASTER, AUDIO_MASTER_PREVIEW or OFFLINE_EXPORT. Never use GPU FPS, GUI delta, wall clock or UTC for event time.
- AUD-04 returns requested/accepted/actual sample positions, device/sequence epoch, late/drop/fallback/underrun and audible status. A scheduled command is not proof audio was heard.
- VFX/animation events use stable EventId, source revision, owner, authority epoch, TickId/time, seed, sequence generation and idempotency. Seek/loop/reverse/skip/restart advances epoch and deduplicates old cues.
- Audio hotplug/rate change increments DeviceEpoch; stale schedules are invalidated/re-mapped off the realtime thread. World reload/seek invalidates stale simulation handles.
- Cross-domain markers reference typed owner assets, not arbitrary script names or direct world properties. Event order/tie-break is deterministic and versioned.

## 5. Buttons, transport and authoring controls
**All buttons use EDIT-01's shared EditorCommandIdV1 registry**, never a private toolbar event bus. Metadata: stable CommandId, localized accessible name/description, tooltip, icon+text policy, enabled predicate/disabled reason, shortcut, origin, project context, capability, undo domain, progress/busy/cancel and confirmation. GUI, shortcuts, palette, CLI and MCP call the same typed operation and owner-side authorization.

| Button / CommandId candidate | Purpose | State and safety |
|---|---|---|
| Save / Undo / Redo | persist sequence, graph or cue edits | owner-scoped undo; DATA-04 CAS/readback |
| Add Track / Clip / Marker | create typed lanes/clips/cues | only owner-supported track types; no generic script lane |
| Play / Pause / Stop / Step / Scrub / Loop | transport | explicit master, sequence epoch and cancellation receipt |
| Add Emitter / VFX Node / Connect | GFX-08 authoring | validate node/port/domain/budget before commit |
| Add DSP Node / Connect / Validate | AUD-03 authoring | immutable off-RT plan; never mutate live callback |
| Music Transition / Dialogue / Caption | AUD-04 authoring | sample/locale/rights/overlap validation |
| Add State / Transition / Blend Parameter | SIM-04 authoring | bounded transition guards; no script eval |
| Sync Clock / Timebase / Tempo | inspect/edit mapping | show device epoch, sample/tick mapping and unsynchronized state |
| Validate / Preview / Simulate | owner validation and isolated preview | last-good receipt, cancel and stale-source badge |
| Budget Report / Export Validated | performance/package output | CPU/GPU/VRAM/voice/track budgets and DATA-05 manifest |

No icon-only status; focus/IME text entry must not trigger transport or delete/connect shortcuts. Escape cancels pending drag/wire/clip edit before closing panel. Keyboard-only track/clip/marker list is an alternative to spatial lanes. Color alone never conveys audio/VFX/animation status.

## 6. Editor/runtime parity and preview
- Same source: AssetId/revision/schema/evaluator version/seed/timebase and target profile are identical between preview and runtime. Presentation layout is not runtime content.
- VFX preview uses GFX-08 same CPU reference evaluator. Optional GPU preview is visual-only and may use tolerance across vendors; it never owns gameplay damage/physics.
- DSP is validated/compiled off realtime thread into immutable DspExecutionPlan, installed at AUD-01 quantum boundary with preallocated buffers. No allocation/lock/file/network/logging/rebuild on audio callback. AUD-04 uses actual AUD-01 sample clock.
- Animation preview uses same SIM-04 tick-driven CPU/headless evaluator and pose/event receipts. Root motion produces RootMotionIntent; SIM-03 accepts/constrains it. Editor cannot teleport or mutate world transforms.
- Sequencer uses same TWO-03 SequenceAsset/playback policy in preview, headless tests, runtime and offline schedule. Seek/loop/reverse semantics are explicit per owner; unsupported exact reverse is reported, not guessed.
- Failure/device loss/cancel retains last-good receipt and labels it stale. Cross-owner preview returns separate owner receipts; no atomic multi-owner commit is claimed without DATA-04 proof.

## 7. Interchange, accessibility and security
- OpenTimelineIO is optional editorial interchange, not Stormline runtime. glTF animation, WebVTT and TTML2 are optional adapters with exact loss report. Codecs/encoders/patent obligations are separate; no FMOD/Wwise/FFmpeg bundled.
- Import through DATA-03 with bounded parser, rights/provenance and loss preview. Export through DATA-01 grant and DATA-05 manifest/readback. Unknown required node/track/codec blocks export or reports loss; never silently strip.
- Accessibility: localized dialogue/subtitles, SDH/non-speech cues, speaker, audio description, readable captions, independent mix, reduced motion/flash, keyboard/gamepad, screen-reader track/graph list, high contrast and focus restore. UIA/AX/AT-SPI/Web require real tests.
- Threats: hostile compressed media/captions/graphs, path traversal, oversized timeline, recursive sequence, infinite transition, emitter explosion, DSP starvation, plugin/script, invalid skeleton refs, cue replay, cross-project MCP writes and unlicensed media. Gates: scoped VFS, parser quotas, rights, DATA-04 CAS/journal, VFX/DSP budgets, tick/sample epochs, owner authorization and redacted traces. No arbitrary executable node/plugin/script.

## 8. Scope classification
- **NECESSARY:** unified workspace/buttons, TWO-03 sequencer view, GFX-08/AUD-03/AUD-04/SIM-04 graph authoring, rational time/sample/tick sync, same-runtime preview, validation/export, security/license, 128 tests and benchmarks.
- **IMPORTANT:** waveform overview, nested sequences, beat-grid snap, VFX GPU preview controls, live audio visualization, motion trails, cross-domain dependency view and offline render queue. Evidence required before 1.0.
- **FUTURE:** collaboration, cloud render, AI auto-commit, unrestricted native plugins, live microphone capture, neural animation and remote media-linker execution.
- **OUT OF SCOPE:** runtime/editor code, new timeline/clock/evaluator, mixer, codec, arbitrary scripting, dependency adoption, release or performance claims.

See [ADR-0058](../adr/0058-edit-06-unified-sequencer-vfx-audio-animation-authoring.md), [technology matrix](../research/edit-06-authoring-technology-license-matrix.md), [typed API](../contracts/edit-06-authoring-api.md), [128 tests](../testing/edit-06-acceptance-matrix.md) and [benchmark](../research/edit-06-authoring-benchmark-protocol.md).
