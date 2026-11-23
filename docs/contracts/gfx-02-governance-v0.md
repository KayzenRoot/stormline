# GFX-02 INTERNAL_ONLY Shader Pipeline Governance Contract v0 (NLE-PRPLAN-GFX-02-01)

**Status:** `GOVERNANCE PROPOSAL / NOT IMPLEMENTED / NO CODE AUTHORIZED`. **Base:** `a4c37e3`. **ADR:** [ADR-0116](../adr/0116-gfx-02-internal-shader-pipeline.md), [ADR-0015](../adr/0015-gfx-02-shader-compilation-policy.md) planning-only. **WO:** [NLE-PRPLAN-GFX-02-01](../work-orders/NLE-PRPLAN-GFX-02-01.md).

## Objective

Record ownership, trust boundaries, release/risk classes and gates before GFX-02 implementation. No native shader compiler, frontend, GPU artifact, driver, renderer, dependency, public ABI or release is authorized.

## Admission and boundaries

- Formal dependencies are `GFX-01` and `DATA-03`; neither is module-qualified.
- GFX-02 owns the logical shader pipeline: SSCL-0 parsing, IR, reflection metadata, variant planning, cache identity and incremental invalidation.
- DATA-02 identity; DATA-03 import provenance; GFX-01 device capabilities; CORE-01 OS; CORE-02 memory; CORE-03 jobs; CORE-06 diagnostics; GFX-05 material semantics; EDIT-05 graph UX; DATA-05 cook.
- No GLSL/HLSL/Slang/WGSL/SPIR-V/DXIL/MSL/Tint/Naga/DXC/glslang or vendor SDK is selected.

## Policy invariants

1. **No native compiler or GPU.** SSCL-0 only; no external compiler, driver, pipeline, render or hot reload.
2. **Declarative subset.** No expressions, control flow, macros, includes, host paths or executable code.
3. **Bounded input.** Fixed source, line, name, declaration and variant limits.
4. **Deterministic output.** Canonical declaration/variant ordering and stable diagnostics.
5. **Typed fail-closed errors.** Unknown syntax/types, duplicates, stage violations, overflow and stale revisions fail explicitly.
6. **No artifact claim.** IR/reflection/cache metadata is not SPIR-V, DXIL, MSL, WGSL, GLSL or a GPU pipeline.
7. **Sanitized diagnostics.** Logical project-relative path, line/column and bounded message; no host path or source leak.
8. **Identity distinction.** FNV-1a 64 is accidental-identity only, not authentication or trust.
9. **Release boundary.** `INTERNAL_ONLY`; no ABI, performance, security, release or production claim.

## First-slice scope (future, blocked)

- `-03` SSCL-0 lexer/parser and validated IR.
- `-04` reflection/layout metadata.
- `-05` deterministic variant planning.
- `-06` in-memory cache identity.
- `-07` dependency-revision incremental invalidation.
- `-08` qualification and `-09` closeout remain blocked.

## Gate state after merge

- Manifest root `GFX02_01_APPROVED_GOVERNANCE_ONLY`: **624 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 99 `COMPLETED`, 25 approved gates**.
- `GFX-02-01` becomes `APPROVED_GOVERNANCE`; `GFX-02-02`..`-09` remain `PLANNED_BLOCKED`.

## Stop / rollback / security

Stop on stale source, missing admission, native compiler/GPU/API selection, executable shader content, host I/O, public ABI/release or HIGH/CRITICAL. Revert normally; never force push.

No implementation is authorized by this governance contract.
