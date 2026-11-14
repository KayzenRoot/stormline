# ADR-0015 — GFX-02 Versioned Shader and Material Compilation Policy

**Status:** PROPOSED / NOT APPROVED FOR ENGINE CODE  
**Date:** 2026-11-14 | **WO:** NLE-P00-WO-002-GFX-02 | **Research issue:** #126 | **Future code:** #30 BLOCKED.

## Problem
Stormline's native 2D/2.5D/3D renderer, material editor and Web runtime need advanced shading without silently breaking projects when compilers or native GPU backends change. Shader variants, binding layouts, driver caches, hot reload and untrusted shader input can cause correctness, security and maintenance failures. The chosen source language cannot be assumed portable across native Metal and browser WGSL because upstream support differs.

## Proposed policy, not final technology selection
1. **Owned typed shader/material authoring contract** `ShaderDefinitionV1`, compiler-facing `MaterialDefinitionV1`, `ShaderRecipeV1`, reflection and layout schemas independent of vendor compiler AST, stable DATA-02 AssetId and DATA-04 authored scene references. PBR and material rendering model stay in GFX-05; visual node UX in EDIT-05.
2. **Separate source compiler frontends and output backends:** Slang, DXC/HLSL, glslang/GLSL are candidate paths. Slang is strongly promising but its Metal support is marked experimental and WGSL work-in-progress. Native MSL and WGSL fallbacks must remain first-class until measured proof.
3. **Strict versioned `ShaderReflectionV1` and `PipelineLayoutContractV1`:** entry points, stage IO, resource/bind group layout, alignment/array bounds, texture semantics and specializations match GFX-01 DeviceCapabilities. Layout mismatches fail closed, never guessed.
4. **Deterministic variant planning under declared budgets:** avoid exponential static permutation; dynamic uniforms for ordinary property edits, specialize only when semantically necessary, canonical variant keys under pinned inputs/recipes. Byte-identical output only where measured. Optional SSVF pruning is prove-or-drop against reachable-only baseline.
5. **Content-addressed, provenance-verified cooked shader cache** includes transitive include contents, compiler and dependency tags, target feature tier, output profile, optimization, layout version and flags. Native driver pipeline caches are **separate**, device/driver/UUID-dependent and invalidated when incompatible.
6. **Staged transactional hot reload:** compile candidate, validate reflection/layout/target, create candidate trusted pipeline then generational/fence-safe activate. On compile/layout/device error retain last-good shader/pipeline and preserve authored parameter overrides; no global Scene/VFS/GPU atomicity claim.
7. **Untrusted shader execution boundary:** compiler input is untrusted code for a compiler and possibly GPU driver. Bounded file and include graph, process isolation/quotas and timeouts/fuzzing, no host/network access, no arbitrary compiler flags from MCP, no unchecked shader binary upload.
8. **Editor/CLI/MCP parity by typed semantic operations**: inspect, plan, preview, diagnostics, authorized compile job and controlled material parameter validation, not direct native GPU handles, shader driver execution or OS compiler shell.
9. **Source lineage and error locations:** project-relative include source maps, stable diagnostics, redaction and opt-in telemetry; do not leak absolute paths, shader source, signing secrets or proprietary code to remote services without authorization.
10. **No automatic compiler selection approval** from this research or from ADR status. Release class, target minimums, exact license/SBOM, implementation files/CI commands and REAL target tests must be owner/objectively approved before promoting #30.

## Alternatives / trade-offs
- **Slang-only for all 4 targets:** appealing design, but Metal/WGSL parity not proven. Reject as a forced assumption.
- **HLSL+DXC everywhere:** strong Windows/Vulkan but not native MSL/WebGPU without another path; retain as candidate baseline.
- **GLSL+SPIR-V everywhere:** browser WebGPU does not ingest SPIR-V and Metal needs translation/native compiler.
- **Write proprietary complete compiler now:** huge complexity for no measured benefit; reject as automatic NECESSARY.
- **Runtime compilation of arbitrary user code in game clients:** large driver/crash risk; prefer offline cooked artifacts and trusted pipeline creation, evaluate controlled sandbox authoring separately.
- **Compile every graph parameter tweak into static variant:** variant explosion and frame stalls; prefer uniform dynamic values where valid.
- **GPU pipeline cache shared across drivers and devices:** unsafe incompatible native state; reject.
- **Unvalidated immediate shader hot reload:** loses last-good and risks in-flight GPU use-after-free; reject.

## Deferred decisions
Specific default source language/edition; version-locked Slang/DXC/glslang/Tint/Naga, compiler packaging and notices, exact shader profile and WGSL compatibility, variant count thresholds, CPU/RSS budgets, target hardware/build matrix, schema migration details, reflection binding remap, shader source rights and runtime user-generated shader policy, release class and engine license.

## Required proof before implementation
- Real Windows Vulkan/D3D12, Linux Vulkan, macOS arm64 Metal, browser WebGPU/WGSL/WebGL2 conformance and native draw/compute golden tests with source maps, exact pinned versions.
- Malformed shader fuzzing, compiler isolation, excessive includes/recursion/variants, unauthorized MCP attempts, device loss, cache poison, corrupted IR, driver mismatch.
- Bytewise deterministic output for declared targets or honest semantic reproducibility envelope, incremental rebuild from dependency change, invalidation and cache semantics.
- Stage/link/descriptor reflection, precision/clip/depth/alpha/normal mapping, 2D/2.5D/3D PBR fixture quality under target thresholds.
- Measured p50/p95/p99 cold/warm compile and hot reload and bounded peak RSS/disk, native pipeline creation/VRAM effects on documented devices.
- License/SBOM provenance of exact compiler binaries and dependencies (Slang Apache2 with LLVM exception, DXC Illinois Open Source, SPIRV-Cross mixed file license), source asset rights.
- Fully approved Scope/Requirements/DoD/release class/ADR, integrated implemented GFX-01+DATA-03, exact source files/CI and new SHA-256 Context Lock. `NLE-EXEC-WO-GFX-02-001` remains BLOCKED.

See [architecture](../architecture/gfx-02-shader-material-compilation.md), [matrix](../research/gfx-02-shader-technology-matrix.md), [API](../contracts/gfx-02-shader-api.md), [future tests](../testing/gfx-02-acceptance-matrix.md).
