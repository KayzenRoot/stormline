# GFX-02 — Shader & Material Compilation, Reflection, Deterministic Variants and Secure Hot Reload

**Research WO:** NLE-P00-WO-002-GFX-02 | **Issue:** #126 | **Future implementation:** #30 BLOCKED  
**State:** RESEARCH PROPOSED, DOCS ONLY | **BASE main:** d968809bc4869a3a39f1fb1f82f75d5a212dfbda  
**Risk:** LOW current documentation, future ELEVATED for untrusted shader compiler/driver, GPU pipeline, cache poisoning and project source integrity.

## Mission and hard boundaries
Enable safe, reproducible and debuggable shader authoring across Stormline's 2D, 2.5D, 3D, Windows/Linux/macOS native and Web runtimes without forcing a single vendor language/IR onto platforms where its backend is experimental. Offer a **Stormline-owned stable semantic shader/material compilation contract**, not a new low-level compiler, owned shading language or automatic adoption of Slang.

- **GFX-01** owns GPU adapter/device capability snapshots, typed pipeline creation, resource and layout validation, device loss and generation-tagged handles. GFX-02 produces validated artifacts, layout contracts and proposed pipeline recipes; it does not call arbitrary native driver APIs through Editor/MCP.
- **DATA-01** owns scoped VFS opens and staged writes; never follow shader include/URI outside trusted project mounts or allow host paths in graph nodes.
- **DATA-02** owns persistent ShaderAssetId / MaterialAssetId, revision, provenance and dependency graph. File path, source digest, compiler binary checksum or pipeline cache key are **not** permanent asset IDs.
- **DATA-03** imports validated material/texture/shader-source references and resolves owner-controlled reimports; GFX-02 does not replace imported source or user overrides.
- **DATA-04** owns authored scene/material references and revisioned semantic edits. Material graph source documents may use DATA-04 schema policy; GFX-02 doesn't reinterpret scene as compiled binary.
- **DATA-05** owns target cook bundles, immutable byte blobs and release manifests; GFX-02 supplies shader cook recipe/artifacts/receipts, not its own distribution channel, patch installer or signing policy.
- **CORE-02/03/06** own bounded allocators, job/cancellation/backpressure, diagnostics/tracing and privacy filters; GFX-02 follows their budgets and error taxonomy.
- **GFX-03** owns render graph/barriers/transient VRAM scheduling. GFX-02 owns shader/pipeline reflection contract and preflight compatibility, not pass graph scheduling.
- **GFX-05** owns actual material/PBR shading semantics; **EDIT-05** owns visual editor graphs and UX; **AI** can call authorized semantic material/compiler operations only; **PLAT-03** owns browser runtime availability and WebGPU/WebGL2 fallback policy.

## Proposed compilation architecture: semantic authoring to native artifact

```text
Authoritative ShaderAssetId / MaterialAssetId, DATA-02 revision
  -> DATA-01 scoped include/dependency walk and provenance/rights snapshot
  -> Typed ShaderRecipe/GraphInput + target feature/capability profile
  -> Validate stages / type and parameter graph / domain restrictions
  -> Derive normalized ShaderIR / MaterialParameterSchema + variant budget
  -> Choose pinned frontend (Slang / DXC-HLSL / glslang-GLSL / WGSL)
  -> Compile/translate to target-specific IR/source, validate output IR
  -> Reflect resources, entry points, layouts, stage IO, alignment and capability
  -> Compare semantic layout, binding remap and GFX-01 DeviceCapabilities
  -> Apply explicit allowed optimization/specialization & verify again
  -> Stage compiled artifact + diagnostics and toolchain/cache receipt
  -> Package via DATA-05 in versioned target cook manifest
  -> Renderer GFX-01 loads compatible verified artifact, creates pipeline
```

The authoring schema must be stable independently from vendor AST or generated code. ShaderIR is a **design abstraction**, not a claim that one compiler IR can directly serve Vulkan, Metal, D3D12 and browser WebGPU. Preserve source maps to original project-relative shader file/line, generated specialization and include chain; never leak native absolute paths.

### Target-specific path proposals
| Native/browser target | Preferred research path | Mandatory boundary |
|---|---|---|
| Vulkan Windows/Linux | Slang -> SPIR-V or DXC HLSL -> SPIR-V, glslang GLSL -> SPIR-V | SPIRV-Tools validator and target environment/extension capability checks; SPIR-V is not assumed valid for other APIs |
| Direct3D 12 Windows | Slang/HLSL -> DXC -> DXIL | DXIL validator and shader-model version; no presumed identical resource binding map with SPIR-V |
| macOS Apple Silicon/Metal | native MSL+Metal compiler or proven Slang/SPIRV-Cross -> MSL then native validation | Slang Metal support **experimental**; genuine Xcode/macOS toolchain and hardware proof required, no silent Vulkan translation requirement |
| Browser WebGPU | first-class WGSL source/IR and validation with Tint or Naga plus browser-native WGSL compilation | Slang -> WGSL support is **work in progress**; WebGPU consumes WGSL source, **not browser SPIR-V modules** |
| WebGL2 degraded target | GLSL ES validated with restricted features/texture and precision support, optional proven translation | No compute parity with Vulkan/WebGPU or unsupported feature use; explicit versioned fallback receipts |
| Headless non-GPU | compile/reflect/validate tools only (trusted offline worker) | no pretend GPU pipeline/golden pixels without real GPU |

A future application **may** choose HLSL-centric, Slang-centric, WGSL-first or mixed authoring; require target-conformance before fixing. Untrusted user-uploaded shader code must be treated as executable *GPU program input* and moved through strict validation and isolation.

## Typed authoring, material specialization and ownership
- **ShaderDefinitionV1**: stable AssetId/revision, source language+edition, stages/entry points, reusable module refs, typed parameter schema, include graph and supported domain tags (sprite, surface, postfx, compute).
- **MaterialDefinitionV1 (compiler-facing)**: material shader identity, stable parameter IDs, type/range/defaults, binding semantics, optional static switches and data-driven render state contract. This is **not** authoring a complete PBR/material system: GFX-05 owns PBR closure, BSDF, layering, textures and quality tiers.
- **MaterialInstanceV1 (compiler-facing)**: material asset ID, base template/revision, authored parameter overrides, only permitted dynamic values and limited specialization context. Changes to a runtime float should **not** automatically trigger shader compilation.
- **ShaderIRV1 proposal**: backend-agnostic typed entry/stage+resources+semantic requirements; no raw native compiler pointer, guest program or unsafe extension. Unknown optional metadata roundtrips, unknown required feature fails closed.
- **PipelineLayoutContractV1**: reflection: descriptor set/group, binding number, type/access/stages, array counts, alignment, push constants/root constants equivalents, vertex inputs/interpolants, fragment outputs, specialization IDs, resource format/access. Missing/ambiguous mapping is a **hard error**, not guessed.
- **Immutable source snapshots** ensure includes and plugin shader modules cannot change under a compile; revisions/contents hashed. Reimport/edit uses expected revision and preserves last-good shader on failure.

## Variant strategy and explosion control
A naive full Cartesian permutation of n static switches can multiply binary count exponentially. Prefer:
1. **Static variants** only for control flow or resource layout requiring different native pipeline, and only those reachable in approved scene/material/target profiles.
2. **Dynamic uniforms/branching** for ordinary numeric values, not compile-on-each-slider movement.
3. **Specialization constants** where target/backend supports them and behavior measured; pipeline specialization costs still counted, and WebGPU override constants have separate semantics.
4. **Variant budget** as a hard ceiling on plan counts, compiled bytes, CPU time, disk cache and storage; report per-material explosion source and fallback to explicitly permitted safe variant or reject.
5. **VariantKeyV1** includes ShaderAssetId/revision, entry/stages, static switch assignment, target capability and layout version, optimization/safety profile and pinned compiler graph. Avoid reliance on unordered iteration or process nondeterminism; stable canonical form is versioned.
6. Original **Stormline Shader Variant Fabric (SSVF)** speculative reachability-aware pruning R&D may compare to simple reachable-key enumeration + LRU. Prove-or-drop on same fixture/quality and no incorrect branch pruning.

## Cache and reproducibility: two different caches
**Cooked shader artifact cache**: content-addressed based on full transitive include graph and pinned compiler/source edition, reflection/schema/target/flags, optimization, binding remap, feature profile, and toolchain binary+dependency manifests. Cache byte integrity and source provenance readback mandatory; cold vs warm compile metrics recorded. Compiler outputs may vary across OS/lib/driver due to nondeterminism. Bytewise reproducibility is a conditional proof, not automatic promise.

**Native pipeline/driver cache** (later GFX-01/GFX-03 integration): additionally bound to backend, device/driver identifier, pipeline layout, render state, shader model, adapter/driver versions and relevant UUID/header restrictions; never blindly distribute a Vulkan/D3D/Metal opaque pipeline blob from one GPU to another. On mismatch/corruption reject and recreate from trusted cooked shader, with time limits; invalid caches cannot crash a renderer by assumption.

Source code, generated IR, GPU binaries, diagnostics and cache metadata may contain IP; logs and optional shared remote caches require permission/provenance controls. Cross-tenant caching prohibited by default.

## Hot reload and failure recovery
```text
ACTIVE_GEN N -> snapshot revision+recipe+target
 -> BUILDING candidate N+1 -> VERIFY_REFLECTION+FEATURES+LINK
 -> CREATE_CANDIDATE_PIPELINE in trusted GFX-01 context -> GPU_FENCE_SAFE_READY
 -> COMMIT generation N+1 | REJECT/KEEP N
```
If compile, reflection, linkage, semantic override mapping or device capabilities fail: keep last-good render pipeline and last-valid material parameter state. No destructive swap while in-flight GPU references point to old generation. Incompatible layout changes produce explicit migration/conflict preview; no silent parameter loss. Device loss invalidates all GPU pipeline generations; reload from verified source/artifact and re-probe features or report restart-required per GFX-01. Never assert that host scene edits and GPU pipeline swap are one atomic transaction.

## Diagnostics and AI-native workflow
`ShaderDiagnosticV1`: stable error code, sanitized project-relative file+line+column, include/specialization source-map spans, severity, variant key, target/backend+compiler identifier, actionable suggestion and redacted context. Do not leak raw source or absolute host paths in MCP and telemetry by default. Unsupported Metal/WGSL translation reported as **UNSUPPORTED_TARGET** with alternative validated fallback, not declared as working.

Editor, CLI and MCP share safe semantic kernel:
- `shader.inspect` / `shader.dependencies` / `shader.variants.plan` / `shader.compile.preview` / `shader.diagnostics.read` read-only/proposal actions with typed quotas;
- `shader.compile.execute` only authorized project scope, pinned compiler execution environment and allowed ShaderAssetId, no arbitrary command flags, plugin executable, OS path or network host;
- `material.parameters.validate` / `material.instance.preview` use typed schemas and source-revision preconditions;
- `shader.hot_reload.commit` a privileged Editor/runtime boundary with GPU fence+last-good checks, **not** a direct generic MCP native-driver command.

Untrusted shaders through compiler and GPU constitute a high-risk boundary: process sandbox where supported, separate worker privilege, cancel/time/memory/disk/instruction limits, parser fuzzing, include path traversal and recursive macro include caps, no network/external command, signed/allowed plugin list and GPU hardware driver constraints. Headless verification cannot substitute for native graphics driver testing.

## Future experimental claims and acceptance gates
A/B Slang vs DXC/glslang on pinned native fixture corpus, plus explicit native Metal MSL and WebGPU WGSL tests (Slang target support does not imply production). Measure correctness/per-target semantics, variant count, unique shader bytes, p50/p95/p99 compile time, hot reload latency, peak RSS, cache hit/miss, device lost and GPU frame-time impact *on real hardware*.

Before future code #30: approve target/feature/language choices and exact pinned version/SBOM; freeze requirements and 1.0 class, module APIs + CI source paths/fixtures, sandbox and proof obligations, transitive GPU shader compilation/cross-platform conformance, implement/merge GFX-01 and DATA-03 prerequisites, fresh SHA-256 Context Lock and objective owner audit. No code, SDK install or shader compilation authorized by this research.

See [technology matrix](../research/gfx-02-shader-technology-matrix.md), [ADR-0015](../adr/0015-gfx-02-shader-compilation-policy.md), [typed contract](../contracts/gfx-02-shader-api.md), [future tests](../testing/gfx-02-acceptance-matrix.md).
