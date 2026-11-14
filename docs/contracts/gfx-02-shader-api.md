# GFX-02 — Typed Shader/Material Authoring, Compiler, Reflection and Hot Reload Contracts

**WO:** NLE-P00-WO-002-GFX-02 | **Research:** #126 | **Future code:** #30 BLOCKED.
Logical, versioned **PROPOSAL**, not real C++/MCP ABI, compiler implementation, wire schema or runtime pipeline.

## Schema and explicit ownership

| Type | Proposed fields | Immutable/validation rules |
|---|---|---|
| `ShaderDefinitionV1` | ShaderAssetId (DATA-02), revision, source language/version, domain, stages/entry points, include AssetIds, authored metadata | no file path/hash as permanent ID; unknown required extension fails closed |
| `MaterialDefinitionV1` | MaterialAssetId/revision, ShaderAssetId, parameter schema, render-state and static feature constraints | GFX-05 owns PBR physics/material semantics, EDIT-05 owns visual graph UI |
| `MaterialInstanceV1` | instance id, base definition/revision, typed dynamic parameter overrides, static variant key | preserve overrides across revisions or signal conflict, never auto-compile on ordinary parameter change |
| `ShaderSourceSnapshotV1` | project capability, root AssetId/revision, normalized transitive include graph digests, importer provenance, rights | VFS-scoped, idempotent snapshot, no host absolute include |
| `ShaderTargetProfileV1` | backend Vulkan/D3D12/Metal/WebGPU/WebGL2, shader model/IR version, GPU GFX-01 caps, bound limits, optimized/fallback profile | backend and capability negotiation, no generic OS-only guess |
| `ShaderRecipeV1` | language/edition, entry points, stage list, include policy, compiler frontend+version+binary digest, target backend, flags allowlist, optimization/safety policy | no arbitrary raw compiler flags from MCP, deterministic canonical version |
| `ShaderCompileRequestV1` | request_id/idempotency key, SourceSnapshot + expected revision, recipe/profile, variant budget, CPU/memory/disk/time quotas | read-only plan before privileged execute; stale source refuses commit |
| `ShaderCompilePlanV1` | resolved include DAG, planned variants, phase budgets, missing capability, warning/approval requirements, cache key predictions | preview only, safe even on unsupported target |
| `ShaderReflectionV1` | stage inputs/outputs, resource bindings, resource type/access, arrays/alignment, sampler/storage texture types, specialization constants, feature requirements | reflection from validated generated target artifact, type/shape checks |
| `PipelineLayoutContractV1` | sorted bind groups/sets, register spaces, resource layout signatures, vertex inputs, fragment outputs, push/root constants and layout version | compare GFX-01 and target constraints; mismatch rejects |
| `ShaderVariantKeyV1` | ShaderAssetId/source rev, static switch canonical mapping, entry stages, recipe digest, target profile/layout version | stable across ordered input; no hash collisions tolerated without semantic equality |
| `CompiledShaderArtifactV1` | typed target output SPIR-V/DXIL/MSL/metallib/WGSL/GLSLES, schema, compiler receipt, byte digest/length, validated reflection and source-map id | no universal GPU binary; target-enforced validation; DATA-05 owns bundling |
| `ShaderCacheReceiptV1` | source graph fingerprint, recipe/compiler dependencies, artifact digest, reproducibility class, cache hit provenance, target and error | content hash not trust signature, no cross-project cache leak |
| `ShaderDiagnosticV1` | error code, phase, sanitized project URI, line/column/range, include/source-map chain, severity, target, fix hint, redaction policy | no host paths/secret/shader body in remote diagnostics by default |
| `ShaderHotReloadPlanV1` | old/new shader generation, expected asset revisions, reflection diff, material parameter migration/conflicts and last-good id | no active pipeline mutation before validation |
| `ShaderHotReloadReceiptV1` | old/new GPU generation, verified artifact digests, pipeline creation result, fence-safe activation or rollback state, diagnostics | success only after active generation, old retained until safe retire |
| `ShaderErrorV1` | stable error code, phase, target, source span, retryable, security label, recovery action | bounded and sanitized; no raw compiler native error pointer |

## Semantic pipeline operations
```text
Source AssetId + import revision -> snapshot input includes (scoped VFS)
  -> compile.plan -> variant_budget_check -> compile.preview
  -> compile.execute in permitted worker -> validate IR
  -> reflect -> layout_contract.verify(GFX-01 caps)
  -> stage verified artifact/receipt (DATA-05)
  -> hot_reload.plan -> create candidate GFX-01 pipeline
  -> fence-safe switch/rollback -> GPU generation retirement
```

Lifecycle stages: `UNRESOLVED -> SNAPSHOTTED -> VALIDATED_SOURCE -> PLANNED -> COMPILING -> VALIDATING_BINARY -> REFLECTING -> STAGED -> VERIFIED -> COMMITTED`, with `FAILED_RETRYABLE/FAILED_PERMANENT/CANCELLED`. An artifact commit is **not** an active native pipeline: pipeline hot reload follows its own `ACTIVE_N -> BUILDING_N1 -> LINKED_N1 -> READY_FENCE_SAFE -> ACTIVE_N1 | KEEP_LAST_GOOD_N` state. A cancelled request must not replace active material state.

## Stable binding/ABI rules
- Compile output is only valid for the explicitly recorded target backend, compiler profile and RHI device feature/layout constraints. SPIR-V binary is not browser WebGPU shader module; WebGPU consumes WGSL validated in browser/runtime.
- Binding reflection maps vendor schemes (HLSL register-space, Vulkan set/binding, Metal buffer/texture/sampler indices, WebGPU bind group) to typed semantic layout. **Mapping is explicit and validated**, no silent arbitrary index conversion, and unsupported constructs fail.
- Driver pipeline caches depend on GPU/backend/driver and are invalidated independently from language compiler artifact cache. Never upload cache binaries to other adapters without declared compatibility checks.
- Include order and static variant order canonicalized, hashes algorithm-tagged; toolchain/library/specialization+target/profile fingerprint every key. Absent dependency/rights => no production cook.
- `SourceSnapshotV1` source maps retain authored project-relative line/column even after macro expansions and graph nodes, with bounded recursion/expansion.

## Editor / CLI / MCP permissions
| Semantic command | Required authorization | Side effects |
|---|---|---|
| `shader.inspect` | project.shader.read | bounded metadata/entry points and supported targets |
| `shader.dependencies.inspect` | project.shader.read | bounded include DAG, no host paths |
| `shader.variants.plan` | project.shader.read | counts/budget with no compile |
| `shader.compile.preview` | project.shader.propose | plan/diagnostics, no file mutation |
| `shader.diagnostics.read` | project.shader.debug.read | sanitized project-relative spans |
| `material.parameters.validate` | project.material.read | typed compatibility check |
| `material.instance.preview` | project.material.propose | merge/override preview only |
| `shader.compile.execute` | project.shader.compile + explicit approved recipe/worker | bounded staged cook, no native GPU dispatch |
| `shader.hot_reload.plan` | project.shader.read | layout compatibility and candidate proof preflight |
| `shader.hot_reload.commit` | privileged Editor/runtime internal approval | GPU validation/fence-safe switch, NOT generic raw MCP |

All operations require scoped project identity, actor context, expected revision, stable request id, quotas, timeout, supported recipe allowlist and redacted log policy. A model may **not** supply arbitrary executable command, host path/URL, compiler flags/plugin path, native pipeline pointer, driver or OS operation. Compiler executable runs only from trusted installed toolchain with bounded process rights, never supplied by shader content.

## Typed failures
`SOURCE_NOT_FOUND`, `SOURCE_REVISION_STALE`, `INCLUDE_OUTSIDE_PROJECT`, `INCLUDE_CYCLE`, `MACRO_EXPANSION_LIMIT`, `SOURCE_RIGHTS_BLOCKED`, `UNSUPPORTED_LANGUAGE`, `UNSUPPORTED_TARGET`, `COMPILER_NOT_PINNED`, `COMPILER_TIMEOUT`, `COMPILER_CRASH`, `COMPILER_RESOURCE_LIMIT`, `INVALID_SHADER`, `INVALID_SHADER_IR`, `INVALID_WGSL`, `SHADER_PROFILE_UNSUPPORTED`, `BINDING_CONFLICT`, `REFLECTION_MISMATCH`, `LAYOUT_INCOMPATIBLE`, `VARIANT_LIMIT`, `CACHE_CORRUPT`, `CACHE_TARGET_MISMATCH`, `DEVICE_LOST`, `HOT_RELOAD_REJECTED`, `CAPABILITY_DENIED`, `CANCELLED`, `RECOVERY_REQUIRED`, `UNKNOWN`. Stable diagnostic context includes phase and sanitized file/line plus suggested remediation, never private source leak.

## Proof / freeze gates
Approve language/frontend/IR/translation and exact version/SDK, transitive SBOM, source ownership and redistribution, target compatibility, variant budgets and quantitative benchmarks, GFX-01/ DATA-03 implemented/merged, compiler isolation/hot-reload tests and frozen source inventory/CI commands. **This document authorizes no shader source compilation.**
