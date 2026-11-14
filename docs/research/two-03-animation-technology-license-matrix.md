# TWO-03 — 2D Animation, Sequencing, Import and Export Technology/License Matrix

**Research #153 | WO NLE-P00-WO-002-TWO-03 | PROPOSED / NO PACKAGE INSTALLED, RUNTIME/ENGINE CODE WRITTEN OR MEDIA RIGHTS GRANTED.**

| Candidate | Scope classification | Platform/technical tradeoff | License/rights gate | Future evidence |
|---|---|---|---|---|
| Stormline typed AnimationClip/Timeline with rational timestamps | NECESSARY | pure CPU math/fixed-step, headless, all desktop/Web; GPU-independent schedule | original engine-owned, 1.0 timebase to freeze | exact frame/sample mapping, no drift |
| Sprite flipbooks variable frame duration | NECESSARY | TILE TWO-02 and Canvas TWO-01 stable Sprite IDs/atlas, WebGL2 CPU fallback | owned sprite art and DATA-03/05 rights | pause/seek/loop/reverse and atlas repack |
| Native hierarchical 2D bones/slots/skins | IMPORTANT proposed | CPU reference/deformation, optional GPU feature-proved skinning, 2D Canvas painter order | own code, no licensed asset assumed | weights, IK bounds, blend masks |
| Native Animation State Machine and 1D Blend Trees | IMPORTANT proposed | bounded transitions/active clips, deterministic fixed ticks, no graph scripts | own code, Godot comparison only | interrupted/crossfaded marker dedup |
| 2D blend spaces, additive/IK/mesh deformation | IMPORTANT conditional | cost/quality crossover must be measured, 2D atlas discrete frame policy | own implementation; avoid copying competitor node models | CPU/GPU pose oracle and frame p95 |
| Cutscene multiclip tracks and nested sequences | NECESSARY concept for catalog | AUDIO, GFX-07 camera, VFX/GAME intents not direct calls | assets/licenses per track, no codec bundled | repeatable seek+export cue schedule |
| DragonBonesCPP | OPTIONAL import/reference | C++ runtime with legacy supported engines, exact build/Web portability unproved | **MIT C++ runtime**; pinned dependency + editor/art licenses separately | stable bone/slot mappings, supported subset |
| Godot 4.6 AnimationTree/2D skeletons | COMPARATIVE REFERENCE | rich 1D/2D blend space, state graph, skeletons; engine integration very different | Godot engine MIT; no source/assets copied | reference behavior not proof of Stormline |
| Rive C++ runtime | OPTIONAL interoperability | MIT renderer/runtime, .riv semantics and GPU adapters may be heavy; authored contents and splash | **MIT runtime**; free exported .riv may show branded splash, paid no-splash authoring/export; asset rights distinct | only if zero-cost native core preserved |
| Spine Runtimes / Editor | OPTIONAL external authored data only; no bundled runtime | runtime/editor pairing; version-specific binary and format, licensing restrictions | **custom license** Nov 2026 requires editor license/compliant conditions for integration, derivative products must not replace Editor and license notice redistribution | explicit legal approval before any integration |
| Lottie / Bodymovin JSON | OPTIONAL import of noncritical vector/UI sequences | Lottie-web JS runtime/JSON, feature support varies; README says audio/video/image sequences not supported | Lottie-web MIT code, original JSON/art/font/export rights separate; JSON malicious/unbounded rejected | feature capability/loss report before conversion |
| FFmpeg-based offline video mux/encode | OPTIONAL separate export module | codec, linkage, legal and patent/OS differences; no mandatory native/Web FFmpeg | **LGPLv2.1+ default**, optional `--enable-gpl` GPLv2+ and nonfree flags/notice; source+build+codec obligations | configure+SBOM, actual output and A/V drift |
| GFX-03 optional GPU skinning of 2D meshes | IMPORTANT performance optional | Metal/Vulkan/DX12/WebGPU shader and buffer layout, WebGL2 CPU fallback | own shaders via GFX-02; no proprietary compute library | GPU vs CPU quality and p95/p99 |
| AUDIO sample-accurate cue owner integration | NECESSARY for future export acceptance | sample clock/device timing separate from timeline schedule, latency measured/UNKNOWN | AUDIO CODEC and sound content rights, own typed cue intent | audiovisual actual sample offset, underrun |
| STS timeline verifier | OPTIONAL PROVE-OR-DROP | extra static analysis CPU/evaluation cost; unknown novelty | original research hypothesis, not proven | extra defect capture vs trivial oracle |

## Legal and technical discriminators
- **Spine is NOT MIT:** official [Spine Runtimes License](https://en.esotericsoftware.com/spine-runtimes-license) updated November 2026 conditions runtime integration on editor licensing/compliant terms, prohibits replacing editor and requires notice. Bundling its runtime in commercial or open-core engine without rights is not authorized by an online source read.
- **Rive runtime is MIT** but distribution of authored free .riv files includes branded splash according to current [upstream README](https://github.com/rive-app/rive-runtime/blob/main/README.md). No dependency on paid authoring, splash output, user account or Rive proprietary editor in Stormline native animation.
- **DragonBonesCPP MIT** applies runtime source (and required notice), not automatically to created skeleton/image assets or all upstream editors/plugins. Its availability does not prove 2026 maintenance, any portability to Metal/Web, or compatibility with modern engine ABI.
- **Lottie-web MIT** is a specific JS renderer, not universal C++ animation runtime or guarantee of all Adobe After Effects/Bodymovin feature fidelity; its README lists unsupported embedded audio/video/image sequences. Conversion must explicitly report unsupported art/effect/track features. No dynamic expressions/scripts or remote assets executed by import.
- **FFmpeg LGPL/GPL:** rights vary by configure flags, linkage, enabled GPL and "nonfree" features and codecs/redistribution; project may need a separate legal review of patents/source distribution. Runtime and authoring core must function with no FFmpeg. Frame+sample **schedule** is not encoded A/V export.
- Godot MIT 4.6 design reference for state graph/blending/cutouts is not an authorization to copy its editor/scene code or example artwork. Its frame semantics may differ; qualify comparisons.
- All imported media and scores, font/subtitles, copyrighted animation content, audio stems, sound cues, executable data and codecs require independent rights+provenance. No direct file path/URL or unrestricted user script accepted in Editor/CLI/MCP.

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
