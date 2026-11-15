# EDIT-05 — Visual Shader / Material Graph Technology, License, Security and Interoperability Matrix

**2026-11-15 | P00 research only | [#268](https://github.com/KayzenRoot/stormline/issues/268) | BASE `7034fdce1d1d0220b349e8b333dc67cc6d19c515`.** Everything below is a candidate or behavior reference. No compiler, toolkit, graph library, package, asset, shader, SDK or dependency was installed, pinned, built or adopted. Verify exact tag, per-file SPDX, transitive SBOM, notices and provenance at activation. NLE-D009 engine source license remains OPEN.

## 1. Graph schema and interchange candidates
| Candidate | Official evidence and role | License / limitations / verdict |
|---|---|---|
| [MaterialX 1.39 specification](https://materialx.org/Specification.html) and [core graph model](https://github.com/AcademySoftwareFoundation/MaterialX/tree/main/documents/Specification) | Standard node definitions, typed inputs/outputs, nodegraphs and shader-generation interfaces; current published specification is v1.39 | Optional interoperability research; do not declare Stormline canonical runtime schema or compiler |
| [MaterialX 1.39.5 release](https://github.com/AcademySoftwareFoundation/MaterialX/releases/tag/v1.39.5) | 22 May 2026 release adds Slang generation, compound material graph hardware generation and graph-refactoring work | MaterialX upstream Apache-2.0; generated shader code, transitive dependencies and included assets need separate review. Native Metal/Web parity still needs GFX-02 tests |
| [MaterialX Graph Editor guide](https://github.com/AcademySoftwareFoundation/MaterialX/blob/main/documents/DeveloperGuide/GraphEditor.md) | Example app has load/save/new, node property editor, render view, nested subgraphs, graph hierarchy, search, pan, frame, minimap and clipboard | Uses ImGui plus extensions including a Node Editor; reference only, no copying app code/assets or automatic toolkit selection |
| [glTF 2.0 material schema](https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/material.schema.json) and [PBR schema](https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/material.pbrMetallicRoughness.schema.json) | Standard material parameters and channel/color/alpha semantics | Interchange baseline for supported material projection; not a general-purpose procedural shader graph |
| [KHR_materials_variants](https://github.com/KhronosGroup/glTF/tree/main/extensions/2.0/Khronos/KHR_materials_variants) | Ratified extension mapping named material assignments to glTF primitives | Asset-level material mapping, not compiler static shader permutation |
| [Khronos extension registry](https://github.com/KhronosGroup/glTF/blob/main/extensions/README.md) | Lists ratified material extensions including clearcoat, sheen, IOR, specular, transmission, volume, iridescence, anisotropy, emissive strength, unlit and variants | Verify each extension's current status, semantics and target support; vendor extensions need separate rights/provenance |

## 2. Node canvas/UI candidates
| Candidate | Useful capability | License / platform caveat / verdict |
|---|---|---|
| [ImNodes](https://github.com/Nelarius/imnodes) | C++ immediate-mode node/pin/link editor extension; application owns state; minimap available | MIT. Depends on Dear ImGui, which EDIT-01 has not selected. Upstream README explicitly says Linux has not been tested and its example build is likely to fail there. Native spike candidate only if EDIT-01 backend and cross-platform/accessibility proof pass |
| [Dear ImGui](https://github.com/ocornut/imgui) | Immediate-mode host UI candidate already compared by EDIT-01 | MIT upstream, but docking branch, OS accessibility bridge, IME/RTL, native focus and viewport interop require tests; no toolkit selection here |
| [xyflow / React Flow](https://github.com/xyflow/xyflow) | React graph UI with zoom/pan, multi-select, custom nodes/edges, minimap and keyboard support | MIT for core React Flow/Svelte Flow packages. Browser UI candidate only; does not supply native C++ desktop shell, shader graph schema, compiler or accessibility certification |
| [imgui-node-editor](https://github.com/thedmd/imgui-node-editor) | Dear ImGui node editor alternative | Repository and source headers expose different license statements/dual terms; inspect exact shipped file-level license before use. No adoption |
| [MaterialX Graph Editor](https://materialx.org/Rendering.html) | End-to-end reference for graph editing plus node properties and rendered preview | Example application, not a Stormline runtime dependency or evidence of our cross-platform quality |

## 3. Compiler and target compatibility (GFX-02 remains owner)
| Candidate | Existing GFX-02 evidence | EDIT-05 consequence |
|---|---|---|
| Slang | Apache-2.0 WITH LLVM exception; official targets mark Metal experimental and WGSL work-in-progress | Do not promise a single Slang pipeline covers Windows/Linux/macOS/Web |
| DXC | University of Illinois Open Source License + ThirdPartyNotices; HLSL to DXIL/SPIR-V | Candidate for relevant native targets, not universal MSL/WGSL exporter |
| glslang / shaderc / SPIRV-Tools / SPIRV-Cross | BSD/Apache/mixed per-file terms already recorded in GFX-02 matrix | Keep compiler, validation, translation and license review in GFX-02 |
| Tint / Naga / WGSL | browser WebGPU consumes WGSL; target/backend support must be validated against current spec and actual browser/device | Web target profile may reject unsupported graph features; no native parity inference |
| Native Metal | Apple's MSL toolchain is authoritative for macOS validation | Real macOS compiler/driver tests required; Linux CI cannot prove Metal output |
| WebGL2 | reduced shader/material capability tier | explicit feature loss or typed unsupported response; no assumed compute/sparse feature |

Official GFX-02 sources: [architecture](../architecture/gfx-02-shader-material-compilation.md), [matrix](../research/gfx-02-shader-technology-matrix.md), [typed API](../contracts/gfx-02-shader-api.md), [ADR-0015 PROPOSED](../adr/0015-gfx-02-shader-compilation-policy.md).

## 4. Reference editors and workflow lessons
- [Godot VisualShaders](https://docs.godotengine.org/en/stable/tutorials/shaders/visual_shaders.html) documents file panel, toolbar, graph, optional material preview, node palette, stage selection, zoom/grid/minimap, arrange, varying controls and generated-source view. Workflow comparison only; no source/art copy or Godot dependency.
- [Unreal material parameters/static switches](https://dev.epicgames.com/documentation/en-us/unreal-engine/material-parameter-expressions-in-unreal-engine) show dynamic parameter grouping and compile-time static switches. Epic warns each used static combination can create shader permutations and compile costs; use as a warning/reference, not copied implementation.
- [MaterialX Graph Editor](https://github.com/AcademySoftwareFoundation/MaterialX/blob/main/documents/DeveloperGuide/GraphEditor.md) illustrates subgraph drill-in, node search, frame selection, pinning output and saving node positions. Useful UX tests, not a mandate to copy its toolkit.

## 5. Threat and licensing matrix
| Threat / legal area | Attack or failure | Proposed gate |
|---|---|---|
| MaterialX XML/JSON and clipboard | entity/path traversal, malformed references, huge/deep docs, malicious URLs | DATA-03 bounded non-executable parser, DATA-01 VFS grants, quota and loss preview |
| Node registry / custom implementation | arbitrary code, spoofed node ID, unsigned native module | trusted immutable registry with exact version/digest/provenance; no executable custom node in EDIT-05 |
| Shader source / compiler | hostile source/include, compiler escape, driver crash, command flags, cache poisoning | GFX-02 isolated process, allowlisted inputs, CPU/RSS/time limits, no network/host paths, signed cache metadata |
| Graph topology / variants | cycle, recursive subgraph, huge graph, variant bomb, pathological type inference | bounded node/edge/depth/variant count; deterministic graph validation; early cancellation |
| Preview/GPU | stale generation, freed resource, device loss, unsupported feature | GFX-01/03 handles/fences; last-good preview and typed unsupported receipt |
| AI/MCP/CLI | cross-project writes, arbitrary file/source injection, hidden compile costs | same scoped command API and actor checks as GUI; preview before write/compile; quota and explicit consent |
| Copyright and provenance | unlicensed node code, texture/font/sample material or generated code | DATA-02/03 rights receipt and exact license manifest; only original/redistributable fixtures |
| Engine/SDK licenses | mixing Apache/MIT/GPL/LGPL/proprietary terms or unknown transitive components | exact tag, per-file SPDX/REUSE, NOTICE, SBOM, license compatibility and owner approval before vendoring |

### License decision posture
- MaterialX upstream is Apache-2.0; its graph editor uses ImGui extensions. SDK transitive dependencies and generated output need their own review.
- ImNodes MIT is permissive, but its upstream Linux note makes cross-platform viability unproven. Dear ImGui is a candidate already compared by EDIT-01, not selected.
- xyflow/React Flow core is MIT; optional Pro/commercial offerings are not needed for this evaluation. A web library cannot substitute native EDIT-01 shell.
- Godot is MIT and Unreal is under Epic proprietary EULA; both are behavior references only. Do not copy their code, editor assets or branded UX.
- imgui-node-editor file-level headers expose dual/public-domain wording while repository metadata lists MIT; this discrepancy must be resolved against exact shipped files before use.
- NLE-D009 source license remains OPEN. No dependency or format becomes mandatory by appearing in this table.

## 6. Primary sources
- MaterialX [Specification v1.39](https://materialx.org/Specification.html), [Graph Editor guide](https://github.com/AcademySoftwareFoundation/MaterialX/blob/main/documents/DeveloperGuide/GraphEditor.md), [Shader Generation guide](https://github.com/AcademySoftwareFoundation/MaterialX/blob/main/documents/DeveloperGuide/ShaderGeneration.md), [Apache-2.0 license](https://github.com/AcademySoftwareFoundation/MaterialX/blob/main/LICENSE), [1.39.5 release](https://github.com/AcademySoftwareFoundation/MaterialX/releases/tag/v1.39.5).
- Khronos [glTF material schema](https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/material.schema.json), [PBR schema](https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/material.pbrMetallicRoughness.schema.json), [extension registry](https://github.com/KhronosGroup/glTF/blob/main/extensions/README.md), [KHR_materials_variants](https://github.com/KhronosGroup/glTF/blob/main/extensions/2.0/Khronos/KHR_materials_variants/README.md).
- Shader compilers: [Slang README](https://github.com/shader-slang/slang/blob/master/README.md), [Slang targets](https://shader-slang.org/slang/user-guide/targets), [W3C WGSL CRD 2026-08-25](https://www.w3.org/TR/2026/CRD-WGSL-20260825/), [WebGPU](https://www.w3.org/TR/webgpu/).
- UI candidates: [ImNodes](https://github.com/Nelarius/imnodes), [xyflow](https://github.com/xyflow/xyflow), [Godot VisualShaders](https://docs.godotengine.org/en/stable/tutorials/shaders/visual_shaders.html), [Unreal static switch docs](https://dev.epicgames.com/documentation/en-us/unreal-engine/material-parameter-expressions-in-unreal-engine).

**Unresolved:** exact compiler/node schema versions, material graph extension versions, editor toolkit, native/web node canvas backend, minimum GPU/OS/browser, supported graph domains, import loss policy, exact variant budgets, compiler isolation mechanism, numeric latency/VRAM budgets and 1.0 release class. All remain open.
