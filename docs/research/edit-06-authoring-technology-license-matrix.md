# EDIT-06 — Sequencer, VFX, Audio and Animation Technology, License, Security and Interoperability Matrix

**2026-11-15 | P00 research only | [#272](https://github.com/KayzenRoot/stormline/issues/272) | BASE `67e6af436f4985474b2e6dc5aa47183c32113230`.** Items are references/candidates, not adopted dependencies, SDKs, runtimes or codecs. Recheck exact version, per-file SPDX, transitive licenses, notices and asset provenance at activation. NLE-D009 engine source license remains OPEN.

## 1. Timeline and interchange
| Candidate | Evidence / role | License and boundary |
|---|---|---|
| [OpenTimelineIO 0.18](https://github.com/AcademySoftwareFoundation/OpenTimelineIO/releases) and [architecture](https://github.com/AcademySoftwareFoundation/OpenTimelineIO/blob/main/docs/tutorials/architecture.md) | timeline/stack/track/clip/gap/transition, RationalTime/TimeRange and editorial adapters | Apache-2.0; optional editorial interchange, not TWO-03 runtime. Media linkers/plugins must not execute or access unscoped paths |
| [glTF 2.0 animation](https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/Specification.adoc) | animation samplers/channels, ordered key times and STEP/LINEAR/CUBICSPLINE interpolation, skins/morph animation | optional DATA-03 import/export with property allowlist |
| [KHR_animation_pointer](https://github.com/KhronosGroup/glTF/tree/main/extensions/2.0/Khronos/KHR_animation_pointer) | optional property animation extension | capability-gated; unknown/vendor paths are not arbitrary scene mutation |
| [WebVTT](https://www.w3.org/TR/webvtt1/) | timed text cues, IDs, start/end, overlapping cues, subtitle/caption/speaker/language spans | web interchange; sanitize markup, preserve accessibility metadata |
| [TTML2 Recommendation](https://www.w3.org/TR/2018/REC-ttml2-20181108/) | timed-text vocabulary and subtitle/caption interchange | optional adapter; profile/region/style support explicit with loss report |

## 2. VFX and particle references
| Candidate | Evidence | License / verdict |
|---|---|---|
| [Effekseer runtime/tool](https://effekseer.github.io/Help_Tool/en/overview.html) | mature VFX editor/runtime comparison and sprite/sheet/video workflow | runtime MIT; DirectX runtime depends on DirectX Tool Kit and Vulkan on glslang; tool/dependency notices separate. Reference/optional adapter only |
| [GFX-08 contract](../contracts/gfx-08-vfx-api.md) and [matrix](../research/gfx-08-vfx-technology-license-matrix.md) | typed VFX graph, CPU reference, optional GPU compute, budgets/degradation receipts | canonical owner; EDIT-06 only authoring UI |
| [Godot particles](https://docs.godotengine.org/en/stable/tutorials/3d/particles/index.html) | editor workflow and particle controls | MIT reference only; no source/assets copied |
| [Unreal Niagara](https://dev.epicgames.com/documentation/en-us/unreal-engine/overview-of-niagara-effects-for-unreal-engine) | scalable VFX authoring and system/emitter concepts | proprietary EULA; behavior reference only |

## 3. Audio and realtime graph references
| Candidate/source | Evidence | License / runtime constraints |
|---|---|---|
| [AUD-03 DSP graph](../architecture/aud-03-dsp-sound-graph.md), [API](../contracts/aud-03-dsp-graph-api.md), [ADR-0040](../adr/0040-aud-03-realtime-dsp-graph-authority.md) | typed DSP DAG, immutable plan compiled off realtime thread, swap at AUD-01 quantum boundary | canonical owner; no graph rebuild/allocation/lock/wait/IO/logging/plugin initialization in callback |
| [Web Audio API 1.1](https://www.w3.org/TR/webaudio/) | control and rendering threads; actual output processing can be realtime | Web-only reference, not common native runtime; UI cannot block audio render thread |
| [FMOD legal terms](https://fmod.com/legal) | free-use grant restricts distributing FMOD Engine as part of a game engine/toolset | proprietary; do not bundle as Stormline engine/editor dependency without separate commercial license/approval |
| Wwise | existing [AUD-04 license matrix](../research/aud-04-adaptive-audio-technology-license-matrix.md) records SDK/editor terms | proprietary; no SDK/editor adoption |
| [miniaudio](https://github.com/mackron/miniaudio) | low-level native audio device/engine reference | MIT/Unlicense options and codec/transitive dependencies require exact review; AUD-01/AUD-03 already own audio |
| [OpenAL Soft](https://github.com/kcat/openal-soft) | spatial audio API reference | LGPL-2.0-or-later; not adopted |

## 4. Animation and state-machine references
| Candidate | Evidence | License / boundary |
|---|---|---|
| [ozz-animation](https://guillaumeblanc.github.io/ozz-animation/documentation/) | renderer-agnostic C++ runtime for loading/sampling/blending; low-level, no high-level blend tree or renderer | MIT; SIM-04 candidate only |
| [Animation Compression Library](https://github.com/nfrechette/acl) | animation compression/decompression, game-provided allocator, multi-platform CI | MIT; optional SIM-04 compression candidate; adapter compatibility with ozz must be proven |
| [Godot AnimationTree](https://docs.godotengine.org/en/stable/tutorials/animation/animation_tree.html) | graph states, nested blend trees, immediate/sync/at-end transitions, crossfade/priority/reset | MIT reference only |
| [Unreal Sequencer](https://dev.epicgames.com/documentation/unreal-engine/sequencer-cinematic-editor-unreal-engine) | multi-track timeline for camera, character, audio/effects with clip/keyframe controls | proprietary EULA; UX reference only |

## 5. Threat and license gates
| Threat | Failure | Proposed control |
|---|---|---|
| Imported sequence/media | decompression/parser exploit, path traversal, corrupt duration/sample metadata | DATA-01 scoped VFS, DATA-03 quotas, decoder isolation and content rights |
| Timeline/events | nested sequence, rational overflow, replay on seek/loop, state livelock | reduced rational math, depth/track/cue quotas, epochs/idempotency and transition guards |
| VFX graph | emitter recursion, huge spawn count, VRAM/overdraw bomb, stale GPU handles | GFX-08 budgets, CPU reference, capability gates, GFX-03 fences |
| DSP graph | zero-delay cycle, unbounded latency, callback allocation/lock/IO, hostile plugin | finite DAG, explicit delay, immutable plan, preallocated callback, no arbitrary plugin |
| Animation graph | state livelock, invalid skeleton refs, root-motion teleport | SIM-04 validation, generation handles, TickId, RootMotionIntent and SIM-03 acceptance |
| Captions/dialogue | markup/script injection, invalid locale, missing SDH/audio-description | safe parser, plain-text fallback, rights/provenance and accessibility review |
| AI/MCP | cross-project writes, unauthorized play/export | shared EditorCommandId, project capability, preview/confirm and owner authorization |
| Licensing | SDK/runtime mismatch, voice/music/media/codec rights, transitive notices | SPDX/SBOM/NOTICE, codec/patent review and original/redistributable fixtures |

## 6. Primary sources
- [OpenTimelineIO architecture](https://github.com/AcademySoftwareFoundation/OpenTimelineIO/blob/main/docs/tutorials/architecture.md), [license](https://github.com/AcademySoftwareFoundation/OpenTimelineIO/blob/main/LICENSE.txt), [releases](https://github.com/AcademySoftwareFoundation/OpenTimelineIO/releases).
- [glTF animation](https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/Specification.adoc), [KHR_animation_pointer](https://github.com/KhronosGroup/glTF/tree/main/extensions/2.0/Khronos/KHR_animation_pointer), [ozz](https://guillaumeblanc.github.io/ozz-animation/documentation/), [ACL](https://github.com/nfrechette/acl).
- [Effekseer](https://effekseer.github.io/Help_Tool/en/overview.html), [Godot particles](https://docs.godotengine.org/en/stable/tutorials/3d/particles/index.html), [Unreal Niagara](https://dev.epicgames.com/documentation/en-us/unreal-engine/overview-of-niagara-effects-for-unreal-engine).
- [Web Audio API](https://www.w3.org/TR/webaudio/), [FMOD legal](https://fmod.com/legal), [WebVTT](https://www.w3.org/TR/webvtt1/), [TTML2](https://www.w3.org/TR/2018/REC-ttml2-20181108/), [Unreal Sequencer](https://dev.epicgames.com/documentation/unreal-engine/sequencer-hotkeys-in-unreal-engine).

**Unresolved:** toolkit, OS/browser minimums, codecs/media licenses, runtime libraries, schema versions, maximum tracks/cues/nodes, VFX/audio/animation budgets, sample/tick drift thresholds, offline mux and 1.0 class. No item is approved.
