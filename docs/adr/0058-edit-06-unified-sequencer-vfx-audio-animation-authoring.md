# ADR-0058 — Unified Authoring Workspace over Owner-Owned VFX, Audio, Animation and Sequence Runtimes

**STATUS: PROPOSED / NOT ADOPTED / NOT OWNER-APPROVED / NO CODE AUTHORIZATION** | 2026-11-15 | research [#272](https://github.com/KayzenRoot/stormline/issues/272) | Work Order NLE-P00-WO-002-EDIT-06 | code #73 OPEN/BLOCKED | BASE `67e6af436f4985474b2e6dc5aa47183c32113230` | NLE-D009 OPEN.

## Context
EDIT-06 acceptance is **"Editor e modo runtime reproduzem mesmo conteúdo."** Existing owners define the semantics: GFX-08 VFX graph/CPU reference/optional GPU; AUD-03 DSP graph and immutable realtime plan; AUD-01 mixer/sample clock; AUD-04 adaptive music/dialogue/cinematic cues/timed text; SIM-04 skeletal AnimationGraph/state/pose/root intent; TWO-03 rational SequenceAsset; CORE-04 TickId. A second editor evaluator, graph IR, mixer, timeline clock or state machine would make preview diverge from runtime and compromise determinism, audio stability and gameplay authority. No editor/runtime exists.

## Proposed decision (not adopted)
1. EDIT-06 is a unified **authoring workspace only**, hosted by EDIT-01 with shared panels, buttons, palette, keyboard and accessibility.
2. Formal dependencies stay **EDIT-02 + GFX-08 + AUD-04 + SIM-04 only**. AUD-03/TWO-03 are integration owners already used by predecessor contracts; no new direct DAG edge. CORE-04/AUD-01/EDIT-01/DATA/GFX/EDIT-07/QA-04/EDIT-05 are integration owners.
3. Sequencer UI authors/inspects TWO-03 SequenceAssetV1 with rational time, typed tracks/clips/cues and explicit master policy. EDIT-06 creates no timeline schema/evaluator.
4. VFX editor uses GFX-08 typed bounded graph and same CPU reference evaluator; GPU preview is optional, visual-tolerance only and never gameplay-authoritative.
5. Audio DSP editor uses AUD-03 source and off-realtime immutable plan, installed only at AUD-01 quantum boundary. AUD-04 music/dialogue/caption orchestration consumes actual AUD-01 sample clock. No callback allocations/locks/IO/logging or graph rebuild.
6. Animation editor uses SIM-04 AnimationGraph and CPU/headless evaluator with CORE-04 TickId. Root motion remains intent accepted/constrained by SIM-03.
7. Preview invokes same owner evaluators with exact asset/schema revisions, seed/timebase and target. Per-owner receipts; no cross-owner atomic transaction without DATA-04 proof.
8. Rational sequence time maps to AUD-01 SampleFrameId with exact remainder and DeviceEpoch, and to CORE-04 TickId. Never use render FPS or wall clock. Unknown drift/latency remains UNKNOWN.
9. Every button is an EDIT-01 EditorCommandIdV1 with accessible name, tooltip, disabled reason, progress/cancel, undo domain and owner capability. UI/CLI/MCP use same commands.
10. OpenTimelineIO, glTF animation, WebVTT and TTML2 are optional interchange. Codec/runtime SDK/license decisions stay with owners; no proprietary SDK or media linker bundled.

## Alternatives
| Alternative | Advantage | Rejection |
|---|---|---|
| One generic graph model/evaluator for all domains | common code | destroys VFX/DSP/state-machine semantics and duplicates owner runtimes |
| New EDIT-06 timeline runtime | simpler editor preview | duplicates TWO-03 and creates timing divergence |
| Render-frame-driven clock | simple UI loop | drift/skip at variable FPS; no sample sync/headless determinism |
| Editor-only preview simulator | fast prototype | fails same-content acceptance |
| Mutable DSP graph in audio callback | immediate effect edits | deadline failure; compile off-RT and swap immutable plan at quantum boundary |
| GPU-only VFX preview | fast high-end visuals | no CPU/headless/Web fallback and no authoritative determinism |
| FMOD/Wwise/Effekseer as complete engine stack | mature tools | licensing/redistribution and owner/runtime divergence; no adoption |
| OpenTimelineIO as runtime sequence schema | broad interchange | editorial format is not game runtime/evaluator |
| Vendor cinematic editor embedding | mature UX | proprietary source/assets/ABI and divergent runtime semantics |

## Risks and proof obligations
Rational overflow/drift, audio DeviceEpoch discontinuity, duplicate cue on seek/loop, state-machine livelock, root-motion bypass, DSP callback overrun, VFX budget/VRAM exhaustion, preview/runtime divergence, nondeterministic GPU particles, caption locale loss, media rights and MCP cross-project access.

Before owner approval: actual GFX-08/AUD-03/AUD-04/SIM-04/TWO-03/CORE-04/AUD-01 runtime APIs/builds; EDIT-01 accessible command host; DATA-03/04/05 import/persistence/cook; sample/tick synchronization and loopback receipts; editor/runtime parity fixture on native OS and Web; event dedup/crash recovery/audio realtime tests; licensed media/codec SBOM; p50/p95/p99 CPU/GPU/VRAM/voice/track budgets. Release class UNDECIDED, NLE-D009 OPEN.

**ADR-0058 remains PROPOSED. No graph schema, runtime, timeline, clock, toolkit, codec, SDK or license is selected. Research does not unlock #73 or any implementation packet.**
