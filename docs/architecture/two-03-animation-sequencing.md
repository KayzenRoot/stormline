# TWO-03 — Stormline Native 2D Animation and Cinematic Sequencing Architecture

**Research WO `NLE-P00-WO-002-TWO-03` | Research issue #153 | Future code #39 OPEN/BLOCKED**  
**BASE main:** `8a104213bdd6d9d6fd88875d12a463200944975b` | **Status: RESEARCH PROPOSED, DOCS ONLY**, no running animator, editor graph, audio mix, cutscene exporter, A/V sync, compiled engine or screenshot. **Risk LOW research, future ELEVATED** for timing/determinism/events/data, cross-platform codecs and audiovisual export.

## 1. Core objective
A **Stormline-owned**, versioned 2D animation and sequencing model that can reproduce animation consistently across project editing, playback, headless logic tests and offline frame schedules. Offer pixel-art sprite/flipbook animation, 2D hierarchical bone/slot/skin/masked mesh deformation, blend/additive/state machine, tracks controlling approved scene properties and cutscene camera/sound cues. Deliver audio-visual sync by matching an explicit authored timeline to **AUDIO-owner audio sample positions**, not by calling a frame callback approximately every 16 ms.

Future catalog acceptance: **"Timeline reproduzível e exportada com sincronismo áudio"**. This means exact timing and reproducible frame/sample mapping with recorded codec evidence and owned/licensed assets, **NOT achieved today**.

### Nonnegotiable invariants
1. Clock and event evaluation are **independent of GPU FPS**. A 20 FPS or 240 FPS render loop cannot alter authored timepoints or silently skip business-critical markers. Headless CPU sampler drives a plan with no GPU available.
2. Source-of-truth revision and asset IDs are durable. Keyframes, bone IDs, track paths, scene references, clip IDs and time bases remain stable across reimport, undo/redo, asset streaming and editor reload (DATA-04).
3. **No gameplay or physics authority in animation render thread**: authored events/cues are typed intents delivered to WORLD/GAME/PHYS/AUDIO owners with explicit dedup/idempotency/cancellation and fixed tick; root motion is proposed transform delta pending authoritative owner acceptance, not a GPU skin-derived player position.
4. No silent timeline drift, integer overflow, nonfinite curves, invalid reversed durations, unconstrained clip nesting, arbitrary function tracks, network fetch/scripts or unauthorized external file access.
5. Canvas/TWO-01 painter order, material/texture atlas/alpha, GFX-07 motion/reactive and GFX-03 GPU fences remain authoritative. TWO-03 emits immutable drawing/pose plans and scene delta intents, not new rasterizer, mesh allocator or texture streaming backend.

## 2. Ownership and boundaries
| Authority | TWO-03 may produce / consume | MUST NOT duplicate |
|---|---|---|
| CORE-04/05/06 | monotonic fixed simulation tick, checked rational clock math, transform/units, profiling | CPU scheduler, world clock, cross-process time service |
| DATA-01/02/03/04/05 | stable ClipId/KeyId/SkeletonId/TrackId/revision/rights, sanitized external source import, journal, cook and streaming | alternate asset registry, file IO, unauthorized codec parser, authoring persistence |
| TWO-01 | `SpriteDrawV1`, ordered Canvas layers, materials, atlas regions/glyphs and clip | separate 2D GPU renderer, GPU atlas owner or layer painter sorting |
| TWO-02 | animated tile frame/variant *lookup* by stable timeline reference | second tile animator or tile map source/collision changes |
| TWO-04 | future depth/hybrid 2.5D composition, 3D camera reference | implement 3D animation renderer or hybrid world here |
| GFX-02/03/05/07/08 | shader variants/RenderGraph/fences, mesh skinning plan optional, texture/sRGB/alpha, HDR/velocity/reactive, VFX emitter event intents | duplicate GPU compiler/pool, tone mapper, particles |
| AUDIO (owner TBD) | sound clip markers, cue schedule at sample offset, bus and seek/mix ACK; valid audio format/loudness | native audio device, mixer, source decoder, wave clock, encoding/codec license |
| WORLD/PHYS/GAME/NET | scene entities/prefab property validation, root motion proposal/consumption, collision/hit truth, authoritative state | direct scene mutation from arbitrary user track, scripts, physics correction, server trust in visual GPU |
| EDIT/UI/AI/MCP | timeline editor/graph GUI, asset authoring/visibility permissions, project transaction and accessibility navigation | standalone UI text input, custom code execution, MCP host shell |
| Export pipeline (future owner) | frame/sample schedule and approved rights-cleared export recipe | owning FFmpeg binaries, encoding, patent/codec distribution, audio-master mux or file destination |

## 3. Time model: rational sample-accurate timeline
- Canonical `AnimationTimeV1`: signed 64-bit **rational time** numerator + positive nonzero denominator (or exact tick time-base for a project) with normalization, bounded conversion and checked 128-bit intermediate if available; **never float seconds as canonical serialization**. For authoring clip frames keep `frame_rate_num/den` e.g. 24000/1001 or 60/1 and `frame_index`, plus exact clip origin. For audio cues retain source sample rate and canonical mapping to sample position, not frame-time accumulation.
- Each sequence stores its **explicit timebase** and rational conversions. Resampling from sequence frame to audio samples uses checked integer rational comparison/tie rule, with signed sample offsets and specific rounding mode. Avoid unbounded global LCM of unrelated rates (can overflow or explode); use rational reduced arithmetic and bounded validation.
- Runtime has `TimeDomainV1` modes: fixed simulation-time, presentation-time for cosmetic interpolation, audio-master preview (with verified device clock feedback), and offline deterministic export. Define **who is master** for each mode. GPU frame arrival jitter cannot decide event time; offline frame schedule fully deterministic and independent of realtime wall clock. Do not promise global sample-exact audio hardware playback from a scheduling plan alone.
- Fixed tick `EvaluatePoseAt(time)` is pure/reference and deterministic given frozen source/parameters/seed; render interpolation between sampled poses visual-only. All asynchronous asset and audio clocks carry generation/revision and event sequence number; pause/seek/loop/reverse/disconnect requires event policy.

## 4. Clips, curves and keyframe authoring
- `AnimationClipV1`: stable asset+revision, duration/timebase, tracks and keyframes; typed targets (validated Canvas transform/color/layer/material-compatible properties, bone/slot mesh transforms, camera request, VFX/audio marker). For parameter curves allow STEP/LINEAR/CUBIC_BEZIER/HERMITE with finite tangents, monotonic key ordering, duration bounds and semantic type/unit compatibility.
- Flipbooks store referenced SpriteAssetId/AtlasRegionId+revision and **frame duration in rational ticks**, not assuming uniform sheet rate, including holds, 0/1-frame boundaries, variant selection and last frame inclusive/exclusive rule. Texture atlas repack invalidates GPU descriptor but not animation frame ID.
- Keyframe editing is staged and journaled through DATA-04 (revision compare-and-swap). Markers have stable EventId, intended tick+phase+scope, policy across seek/loop/reverse and dedup id/epoch. Typed scene property allowlist prevents arbitrary function calls in animation assets.
- Curves on scale/transparency/color/pivot must respect GFX-05 premultiplied scene-linear color and TWO-01 painter alpha order; negative mirrored transforms and zero-scale/degenerate paths must be handled robustly. Audio property gain automation belongs AUDIO, not renderer.

## 5. 2D skeleton, slots, meshes and deformation
- Bone hierarchy of unique stable BoneIds with parent DAG, reference pose, local transform/pivot, fixed joint limits and optional authoring IK constraints. Reject cycles, negative/NaN weights, zero/invalid determinants and excessive bone depth. Distinguish authored bone transform from physics/collision proxy.
- Skin/slot references DATA-02 Sprite/MaterialId with ordered Canvas layer; swap sprites/skins and material variants at exact clip ticks. Weighted mesh skinning candidate **CPU baseline** producing vertex transforms and bounds; GPU skinning optional via GFX-02/03 when adapter capabilities and real microbench justify. WebGL2 reduced CPU skinning/rig simplification avoids mandatory compute.
- Constraints candidate: two-bone IK, aim, path constraint and deform keyed vertex shape, tested for unreachable target and numerical stability; **rigging editor/production mesh deformer** beyond DoD is IMPORTANT/FUTURE until owner approves. Motion blur and reactive masks via GFX-07, no private post stack.
- Blend chains may interpolate local bone pose, additive delta relative to reference, per-bone masks and attach/visibility discrete policies. Weighted sum normalized or priority-specified; never linearly interpolate sprite IDs or event IDs. Root motion transform **proposal** with source clip revision/tick, separate authoritative WORLD/PHYS acceptance.

## 6. Animation state machine and blend trees
- Typed `AnimStateMachineV1`: stable states, clip/blend nested references, guarded transitions and parameters (bool, enum, finite float/int), explicit interruption/priority/exit windows, normalized phase and time sync groups; no arbitrary scripts, cycles of unbounded instantaneous transitions, untrusted property expressions or floating feedback.
- Blend types baseline: 1D parameter crossfade and weighted tracks, optional 2D blend spaces after reproducibility quality proof (Godot AnimationTree as conceptual reference). For sprite flipbooks **DISCRETE/CARRY** frame behavior and explicit alternate transitions, not accidental interpolated atlas UV between incompatible images.
- Consume root parameter/state from authoritative gameplay, produce pose/draw and cue intents. Machine reevaluations at the same tick and revision must be idempotent. Complex graphs bounded by nodes, transitions per tick, stack depth, active blends, skeleton bones, curve keys, events and memory.
- Transition interruption policy MUST specify events crossing boundary and interrupted one-shot; no duplicated footstep/audio cue or missed action markers. Rollback/resimulation dedup uses stable event ID+sequence epoch, not ad hoc frame-fired callback.

## 7. Cutscenes and nested sequences
- `SequenceAssetV1`: timeline tracks shot/camera, 2D sprite and skeletal pose, layer/opacity, audio cue and VFX intent, optional subtitles and game cue, with stable TrackId/ClipRef/time offsets and nested clip depth/loop cap. No silent overlaps violating painter or audio ownership; explicit priorities and scene-ownership conflict resolution.
- Transitions: camera blend/cut and time remap, fade/hold, scene visibility, audio crossfade **request**; GFX-07 owns camera and HDR compositing, AUDIO owns mixing. Gameplay/script tracks become allowlisted safe event intents and cannot directly grant inventory/money/network authority. Localization/subtitle timing/accessible captions must use published text keys and separate locale service.
- Supported editing: timeline zoom/snap multi-FPS, ripple edit bounded, keyframe move/split/trim, content provenance, scene-affecting track preview using sandbox and DATA-04 transaction. Headless build can render a deterministic cue schedule without GPU but **not** an actual cutscene video.
- Asset changes or streaming interruptions yield typed partial/missing cue readiness, never forged "perfectly synced" export; maintain correct frame/sample schedule with freeze/abort policies.

## 8. Audio and offline export contract
- `AudioCuePlanV1` carries source clip ID/rights, intended rational start/end, bus/sends/pan and sample-rate conversion request to AUDIO. AUDIO returns `AudioScheduleReceiptV1`: accepted/rejected, exact sample start (if known), buffer/hardware latency evidence and any underrun. Timeline compiler cannot claim actual hardware A/V sync until native AUDIO clock feedback recorded.
- Offline export `SequenceExportPlanV1`: exact frame size/rate, range, frame index-to-rational timestamp list, color profile, audio-sample range and list of sample-accurate cue positions; render frames via actual future GFX pipeline and mux/codec via **separate authorized export owner**, with matched audio sample count, no implicit default output file path. Output rights, fonts, sound/media licensing, FFmpeg LGPL/GPL/patents and OS codec configuration require explicit version+SBOM+artifact verification.
- `Render frame n` is deterministic schedule but GPU pixels need platform/driver evidence. Seeking across a sound cue does not automatically replay historical sound. When exporting, use separate synthetic 1kHz pulse/timecode reference to measure A/V drift and difference in sample offsets (never pretend real sync from video metadata alone).
- Editor live preview can select AUDIO-master with user sound hardware latencies measured (or UNKNOWN); pause/mute/reverse/slow playback must have explicit audio policy; not all codecs support arbitrary reverse realtime. Reduced-motion and flash-sensitive timeline playback honored by scene owners without changing gameplay authority.

## 9. Technology/license research and no vendor lock-in
- Original clip/skeleton/timeline/state machine as **necessary architecture proposal**. **DragonBonesCPP MIT** optional format import/runtime study, but source maturity/version/dependencies and art rights need exact scan. **Godot MIT** AnimationTree and skeleton as comparative design reference, not code copied.
- **Spine runtime license** is not MIT/open unlimited: per official Nov 2026 terms integration requires editor license or alternative compliant arrangement, cannot substitute editor, redistribution notice. Treat Spine import only as future optional *data interoperability* after legal gate, not embedded runtime or baked requirement.
- **Rive MIT runtime** but current README says free exports include branded splash and paid export removes it; do not require Rive license/account for native Stormline keyframe/skeleton authoring. **Lottie-web MIT** renderer/Bodymovin JSON may omit audio/video/image-sequence and has differing feature support; optional import after safe JSON and feature compatibility gate.
- **FFmpeg** has LGPLv2.1+ baseline and GPLv2+ with optional build parts, licensing and codec/patent hazards. Never automatically bundle/embed decoder/encoder/renderer in TWO-03; treat export as separate service contract. Original authored media/art rights are independent of runtime license.
- GPU skinning optional and device-specific, shader compiler GFX-02 and allocator GFX-03 owner. Cross-platform Windows/Linux/macOS/WebGL2/WebGPU cannot rely on proprietary SDK or 3D Vulkan-only capabilities.

## 10. Scalability, safety and AI-native authoring
- Bounded clip durations, keys/curves/active tracks, bones, mesh vertices/skin influences, nested clips, events/second, transition count, CPU p95/p99 evaluation, GPU skin bytes, texture atlas revisions; unknown hardware VRAM explicitly UNKNOWN. Deterministic graph evaluation and fallback to CPU/ref/draw-only for low-end; renderer draw-painter order never sacrificed.
- Inputs from external animation JSON/rig/timeline are **untrusted**: no JS expressions/executable function tracks, external file/remote URL, huge JSON/zip decompression, invalid quaternions/positions, excessive skin arrays, duration overflows, recursive nested sequences or cross-project asset references. DATA-03 import sanitizer, DATA-04 revisioned transactions and DATA-05 cook retain rights.
- Editor/CLI/MCP unified safe authoring: inspect/preview/validate, stage/CAS/commit/revert bounded graph changes; project roles+per-asset rights, audit logs, cancellation and secrets redaction. Unrendered preview outputs are labeled ESTIMATED, not produced video.
- Accessibility: timeline keyboard controls, captions/subtitles cues, reduced motion, no unavoidable flashes; UI/EDIT owns actual text input/assistive tech and GFX-07 owners display.

## 11. Optional research: STS (Stormline Temporal Sequencing Verifier)
Proposed **STS** analyzes authoring schedule for rational sample/frame alignment, unbounded loop/seek markers and cross-track timing/cue ownership before gameplay/export. Compare to simple integer-time validation and basic event list oracle. **PROVE-OR-DROP** if false positives, authoring latency or complexity outweigh benefit; not claimed novel/implemented.

## 12. Future code activation (NOT READY)
TWO-01 code MUST be integrated/audited, DATA-04/05 and GFX/AUDIO/WORLD/EXPORT contracts frozen; owner-approved Scope/DoD/1.0 release class, exact files/ABI/timebase thresholds/codec licenses and font/media rights, exact Win/Linux/macOS/Web fixtures, sample offset tolerance, CPU/GPU/VRAM budgets and security tests, fresh SHA-256 Context Lock. All 80 code WOs `BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`, `executor_ready=false`, #39 OPEN/BLOCKED, ADR-0024 PROPOSED. No claimed exported synchronized sequence.

## Primary official references researched (documentation only)
- Godot 4.6 AnimationTree/blend machines, track ownership and blending: https://docs.godotengine.org/en/4.6/tutorials/animation/animation_tree.html
- Godot 2D skeletons/cutouts: https://docs.godotengine.org/en/latest/tutorials/animation/2d_skeletons.html
- DragonBonesCPP MIT C++ runtime source license: https://github.com/DragonBones/DragonBonesCPP/blob/master/LICENSE
- DragonBones C++ supported integration context: https://github.com/DragonBones/DragonBonesCPP
- Rive runtime MIT vs free export splash and paid export terms: https://github.com/rive-app/rive-runtime/blob/main/README.md
- Spine Runtimes legal integration/editor license restrictions (Nov 2026): https://en.esotericsoftware.com/spine-runtimes-license
- Spine Editor terms/license: https://esotericsoftware.com/spine-editor-license
- Lottie-web MIT runtime and supported features/known unsupported media: https://github.com/airbnb/lottie-web/blob/master/README.md
- Lottie-web license: https://github.com/airbnb/lottie-web/blob/master/LICENSE.md
- FFmpeg upstream LGPL/GPL config and redistribution: https://ffmpeg.org/legal.html
