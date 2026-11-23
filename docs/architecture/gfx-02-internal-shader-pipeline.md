# GFX-02 internal logical shader pipeline (SSCL-0)

**Status:** `GOVERNANCE-SCOPED / NOT IMPLEMENTED / NO NATIVE COMPILER`. **ADR:** [ADR-0116](../adr/0116-gfx-02-internal-shader-pipeline.md). **Parent research:** [gfx-02-shader-material-compilation](gfx-02-shader-material-compilation.md), planning only.

## Purpose

Define the first executable GFX-02 slice without selecting a native shading language or GPU compiler. SSCL-0 is a bounded declarative contract language used to exercise deterministic parsing, diagnostics, logical IR, reflection metadata, variant planning, cache identity and incremental invalidation.

## Hard boundaries

- No GLSL/HLSL/Slang/WGSL/SPIR-V/DXIL/MSL/Tint/Naga/DXC/glslang.
- No compiler executable, process, driver, GPU, swapchain, pipeline, render or hot reload.
- No include filesystem walk, host path, network or external command.
- No bytecode suitable for any GPU; IR is internal metadata only.
- No public ABI, release, performance or security certification.

## SSCL-0 grammar

```text
module      := "shader" identifier "{" declaration* "}"
declaration := stage | input | output | uniform
stage       := "stage" ("vertex" | "fragment" | "compute") ";"
input       := "input" type identifier ";"
output      := "output" type identifier ";"
uniform     := "uniform" type identifier ";"
type        := "float" | "vec2" | "vec3" | "vec4"
             | "mat3" | "mat4" | "int" | "uint" | "bool"
```

- Optional `//` line comments and ASCII whitespace are allowed.
- Exactly one module and one stage declaration are required.
- Identifier form is `[A-Za-z_][A-Za-z0-9_]*`; shader and binding names are unique.
- `compute` permits uniforms only; vertex/fragment may declare inputs, outputs and uniforms.
- Every declaration ends with `;`; no expressions, control flow, macros or includes exist.

## Limits

| Limit | Value |
|---|---:|
| Source bytes | 4096 |
| Lines | 256 |
| Module name bytes | 32 |
| Binding name bytes | 32 |
| Declarations | 64 |
| Inputs / outputs / uniforms | 32 each |
| Diagnostic message bytes | 96 |

## Pipeline

```text
logical source path + bounded bytes
  -> lexer with line/column
  -> parser and declaration table
  -> validated ShaderIR (stage, bindings, fingerprint)
  -> reflection slots/layout metadata
  -> variant key plan (static switches, canonical ordering)
  -> in-memory cache key (FNV-1a 64 identity, not authentication)
  -> dependency-revision invalidation plan
```

No phase allocates GPU resources or invokes an external program.

## Determinism

- Source bytes, declaration order and variant switch order have canonical forms.
- Diagnostics are emitted in source order with stable typed codes.
- Reflection binding slots are assigned deterministically by declaration order and kind.
- Variant plans sort keys lexicographically by canonical fields; unordered containers are not iterated for output.
- FNV-1a 64 detects accidental mismatch only and is never a signature or trust primitive.

## Ownership

- DATA-02: stable AssetIds and revisions; no path/hash identity substitution.
- DATA-03: import provenance and receipt metadata consumed by callers.
- GFX-01: device capability snapshot is metadata for future compatibility checks, not used by SSCL-0.
- GFX-05/EDIT-05: material/PBR semantics and visual authoring remain outside this slice.
- DATA-05: future cooked artifact packaging remains outside this slice.

## Failure model

Typed failures cover unknown token, malformed module, missing/duplicate stage, unknown type, duplicate binding, stage restriction, capacity, input size/line limits, variant budget and stale revision. Diagnostics include a logical path, 1-based line and column, and a bounded message; they never contain host absolute paths or external compiler output.
