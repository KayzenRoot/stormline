# ADR-0116 — GFX-02 internal logical shader pipeline

**Status:** `OWNER-RATIFIED_BOUNDED_PLANNING_ONLY / NO CODE AUTHORIZED`. **Subordinate to ADR-0015 (planning only) and ADR-0086 (capability admission). Does not select GLSL, HLSL, Slang, WGSL, SPIR-V, DXIL, MSL, a vendor compiler, a GPU backend, public ABI or release.**

**Date:** 2026-11-22 | **WO:** `NLE-PRPLAN-GFX-02-01` | **Parent:** GFX-02 | **Issue:** #30.

## Context

GFX-01 and DATA-03 completed their internal logical sequences as `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`. GFX-02 has research, architecture, ADR-0015 `PROPOSED`, a semantic contract and a blocked WO; no executable shader compiler exists. ADR-0015 explicitly defers native frontend/compiler selection, target conformance, sandbox, license/SBOM and physical GPU qualification.

## Decision

- **A:** ADR-0015 remains planning direction only. No GLSL, HLSL, Slang, DXC, glslang, WGSL, Tint, Naga, SPIR-V, DXIL, MSL, Metal compiler, GPU driver or external compiler dependency is selected.
- **B:** The first GFX-02 sequence is an in-memory **logical shader pipeline** over a bounded declarative source format, `SSCL-0` (Stormline Shader Contract Language v0): deterministic lexer/parser, validated logical IR, reflection/layout metadata, variant planning, in-memory cache keys and dependency-revision invalidation.
- **C:** `SSCL-0` is not a GPU shading language. It contains no expressions, control flow, macros, includes, native pointers or executable code, and its output is not SPIR-V, DXIL, MSL, WGSL, GLSL or a pipeline artifact.
- **D:** No native shader compilation, pipeline creation, rendering, hot reload on GPU, driver execution, performance timing or physical hardware is implemented or claimed.
- **E:** Native shader compilation requires a separate approved ADR/G6 with exact frontend/compiler pins, versioned SBOM/licenses, sandbox/isolation, target conformance, fixture corpus and real GPU/hardware matrix.
- **F:** Risk is `LOW` for documentation and `ELEVATED` for parser/IR/cache implementation. Release class is `INTERNAL_ONLY`; no artifact, ABI, performance, security or release claim.
- **G:** Ownership: DATA-02 asset identities; DATA-03 import provenance/receipts; GFX-01 device capabilities consumed as metadata; GFX-02 logical source/IR/reflection/variant/cache; GFX-05 material/PBR semantics; EDIT-05 graph UX; DATA-05 cook bundles.
- **H:** All input is bounded and in-memory; invalid syntax, unknown types, duplicate names, stage violations, variant overflow, stale revisions and cache mismatches fail closed with typed errors. Diagnostics use logical project-relative paths and line/column only.

## Required before code

1. `GFX-02-02` contract with exact C++ API, error model, capacities, canonical form and per-slice test oracles.
2. Individual G6 activation and explicit owner authorization per implementation slice.
3. Tests for parser diagnostics, IR invariants, reflection determinism, variant stability, cache keys and incremental invalidation.
4. GCC/Clang/MSVC/AppleClang CI; no HIGH/CRITICAL; no native compiler/GPU/artifact/ABI/release claim.

## Consequence

- `GFX-02-01` may be prepared as `APPROVED_GOVERNANCE`; `GFX-02-02`..`-09` remain `PLANNED_BLOCKED`.
- GFX-01 and DATA-01..05 remain `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`; CORE-01 not module-qualified.
- G3 `NOT_CLEARED`; NLE-D009 `OPEN`; 80/80 module WOs `BLOCKED`; no shader compiler or renderer is claimed.
