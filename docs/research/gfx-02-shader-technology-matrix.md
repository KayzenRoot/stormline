# GFX-02 — Shader Compiler, IR, Reflection, Cross-Target and License Matrix

**WO:** NLE-P00-WO-002-GFX-02 | **Research issue:** #126 | **Status:** PROPOSED / DOCS ONLY
All options are candidates requiring exact tagged source/toolchain/SBOM, platform builds and tests. **No installed compiler, pinned version or tested shader.**

| Option | Official upstream and stated licensing | Strength / candidate role | Concrete limitation and gate |
|---|---|---|---|
| **Slang compiler** | [shader-slang/slang](https://github.com/shader-slang/slang), **Apache-2.0 WITH LLVM-exception**; build transitive notices | modular shader authoring, generic specialization, reflection and Vulkan/D3D12; supports HLSL-style syntax | project docs say Metal target **experimental**, WebGPU/WGSL output **work in progress**, lower support on macOS than Win/Linux; do NOT select as one compiler with guaranteed 4-target parity |
| **Microsoft DXC** | [DirectXShaderCompiler](https://github.com/microsoft/DirectXShaderCompiler): **University of Illinois Open Source License** + ThirdPartyNotices | HLSL -> DXIL D3D12 and SPIR-V Vulkan; Vulkan Guide recommends DXC for HLSL | DXIL vs SPIR-V binding, shader model, native MSL/WGSL export absent; exact packages and dependency licenses |
| **glslang** | [KhronosGroup/glslang](https://github.com/KhronosGroup/glslang), BSD-style terms per exact file | GLSL/HLSL/ESSL -> SPIR-V reference | HLSL advanced syntax support vs DXC, correct legalization for target SPIR-V/version/extension and validation |
| **shaderc/glslc** | [google/shaderc](https://github.com/google/shaderc), Apache-2.0 upstream with vendored/transitive code review | convenience front-end/wrapper around glslang/SPIRV-Tools | does not eliminate need to pin underlying glslang/SPIRV-Tools; compile performance and runtime footprint |
| **SPIRV-Tools** | [KhronosGroup/SPIRV-Tools](https://github.com/KhronosGroup/SPIRV-Tools), Apache-2.0 | spirv-val/opt, target environment, passes, validator, fuzz helpers | necessary strict validation on SPIR-V artifacts; only proves declared IR well-formed, not correct GPU execution |
| **SPIRV-Cross** | [KhronosGroup/SPIRV-Cross](https://github.com/KhronosGroup/SPIRV-Cross), file-level SPDX Apache-2.0 OR MIT possible; inspect shipped exact files | SPIR-V reflection and translation to MSL/GLSL and other high-level forms | translation not proof of native Metal/WebGL2 compatibility; MSL compile/link on macOS required; license selection/tag review |
| **Tint** | [Dawn / Tint](https://dawn.googlesource.com/dawn/) (Dawn BSD-3-Clause mainly, transitive notices) | WGSL validation/transform and WebGPU backend integration | huge build/dependency tree possible, browser behavior not identical to native tooling; validate same WGSL in intended browsers |
| **Naga** | [wgpu/Naga](https://github.com/gfx-rs/wgpu/tree/trunk/naga), repository MIT OR Apache-2.0 per exact component and dependencies | parse/validate/translate WGSL, SPIR-V/MSL/HLSL/GLSL options conditional on features | exact compiler/backend support matrix changes; C++/Rust ABI & toolchain cost, web conformance needed |
| **WGSL** | [W3C WGSL spec](https://www.w3.org/TR/WGSL/), WebGPU standard | first-class browser shader authoring | WebGPU browser shader modules consume WGSL source, **not SPIR-V** directly; portability feature restrictions |
| **Native Metal toolchain** | [Apple Metal](https://developer.apple.com/metal/), Apple SDK terms | authoritative MSL/metallib build and native shader validation on macOS | macOS/Xcode toolchain, Apple Silicon GPU/OS families; can't claim Linux CI proves native MSL pipeline |
| **HLSL/GLSL/WGSL authoring strategy** | language specs public, implementations subject to license | language-specific source as fallback vs one authoring language | avoid cross-target syntax mismatch, material graph should not assume source text is portable |
| **Owned Stormline semantic IR/material schema** | engine code license OPEN | stable editor/AI user-authored materials, typed parameters and target-independent reflection contracts | high maintenance if evolving into whole compiler; keep narrow schema, use proven compilers |
| **SSVF original proposed experiment** | project hypothesis, **not implemented** | reachability-aware variant pruning / parameter equivalence | compare vs deterministic reachable-only enumeration; never prune required variant or silently affect fidelity |

## Source-backed technical facts, verified November 2026
1. Khronos [Vulkan shader tools](https://www.vulkan.org/tools) and [HLSL guide](https://docs.vulkan.org/guide/latest/hlsl.html) list Slang, DXC, GLSL/glslang and SPIRV-Tools. DXC has supported SPIR-V backend and recommended HLSL->SPIR-V path; SPIR-V is Vulkan IR, not native WGSL.
2. Slang [official README](https://github.com/shader-slang/slang/blob/master/README.md): source **Apache-2.0 WITH LLVM-exception**, Metal support experimental, WGSL work in progress. Build may include glslang, SPIRV-Tools, mimalloc, LLVM and other license-bearing dependencies; audit compiled package, not only header badge.
3. DXC [official README](https://github.com/microsoft/DirectXShaderCompiler) says University of Illinois Open Source License and ThirdPartyNotices; do not incorrectly label the project entirely MIT/Apache-2.0 from LLVM ancestry.
4. Khronos [SPIRV-Cross](https://github.com/KhronosGroup/SPIRV-Cross) has file-level Apache-2.0 OR MIT SPDX examples; never apply a top-level license indiscriminately to all shipped files.
5. [Slang targets docs](https://docs.shader-slang.org/en/stable/external/slang/docs/user-guide/09-targets.html) explain that WebGPU uses WGSL, with Slang WGSL generation still incomplete. Browser WebGPU availability and secure-context policy belongs PLAT-03, not GFX-02.
6. Actual minimum Metal, D3D shader model, SPIR-V and WebGPU limits require the target device/driver/SDK negotiation from GFX-01 and real graphics tests. There is no one-size-fits-all Apple/Web compiler selection.

## Proposed controlled evaluation (not measured)
### Candidate baselines
- A: HLSL + DXC for Windows D3D12 and Vulkan SPIR-V, native MSL/WGSL adapters for macOS/Web; stable Stormline authoring schema.
- B: Slang-centric modular frontend, plus explicit native MSL/WGSL fallbacks and full target conformance/diagnostic proof.
- C: GLSL + glslang for Vulkan, MSL/GLSL via SPIRV-Cross, WGSL native; a more cumbersome multilingual surface.
- D: WGSL-first through Tint/Naga for a cross-platform subset, with native advanced feature gaps acknowledged.
No recommended production winner before exact compile/reflect/native draw results.

### Proposed scoring (unmeasured, not a benchmark)
Correctness/target parity 30%; security/recovery + source rights 20%; compile/variant/cache performance 20%; editor/AI diagnostics/reflection 15%; licensing/maintainability 10%; R&D extension flexibility 5%. Security and incorrect target output are **hard vetoes** regardless of weighted scores.

## Compatibility and license open points
Compiler/tag, shipped binary license notices, shader compiler runtime distribution choice (Editor tools vs shipping game), platform min toolchain/OS requirements, color/coordinate semantics, WebGL2 fallback coverage, Metal backend native tests, source code redistribution rights for imported third-party shaders, GPL/other tooling transitive audit, shader sandboxing and fuzzing.

No API is installed and no shader/cache size, frame rate or compile speed has been measured.
