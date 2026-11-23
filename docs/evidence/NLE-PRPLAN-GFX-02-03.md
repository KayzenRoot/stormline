# NLE-PRPLAN-GFX-02-03 — SSCL-0 parser and IR evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO NATIVE COMPILER OR GPU`. **Base:** `33f8482`. **Gate:** [NLE-PRPLAN-GFX-02-03-G6-ACTIVATION](NLE-PRPLAN-GFX-02-03-G6-ACTIVATION.md). **Contract:** [gfx-02-shader-internal-v0](../contracts/gfx-02-shader-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-02-03](../work-orders/NLE-PRPLAN-GFX-02-03.md).

## Scope delivered

- `src/stormline/graphics/shader/shader_types.hpp`: limits, errors, names, paths, type metadata.
- `src/stormline/graphics/shader/shader_parser.hpp`: SSCL-0 lexer/parser and validated `ShaderIr`.
- `tests/core/gfx02_shader_tests.cpp`: PAR-01.
- Additive CMake/workflow entries.

No reflection, variants, cache, incremental qualification, native compiler, GPU, dependency, ABI or release.

## Implementation notes

- Lexer handles ASCII whitespace, `//` line comments, identifiers, `{ } ;`, and tracks 1-based line/column.
- Parser requires exactly one `shader <name> { ... }` module and one `stage vertex|fragment|compute`.
- Bindings are `input|output|uniform <type> <name>;`, unique by name, with per-kind and total capacities.
- Compute rejects inputs/outputs; diagnostics carry code, path, line, column and token length.
- Source fingerprint is FNV-1a 64 over exact bytes; this is accidental identity, not authentication.
- No allocation, external compiler, driver, file, network or GPU is used.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/gfx02_shader_tests.cpp -o /tmp/gfx02_shader
/tmp/gfx02_shader par01
```

Exited 0. ASan/UBSan rebuild exited 0. TSan rebuild ran with `setarch -R` and exited 0.

Native CI is executed by the PR workflow; no result is claimed before the exact-head run.

## Errors and corrections

- PAR-01 initially expected four bindings in a module with three; fixture corrected.
- The missing-semicolon fixture accidentally contained a semicolon; corrected before the passing run.
- Local TSan requires ASLR disabled through `setarch -R`; CI already applies this.

## Security and architecture

- Header-only internal C++20; no compiler process, driver, GPU, allocator, file or network.
- SSCL-0 is declarative metadata only and is not a GPU shading language.

## Rollback

Revert normally; remove the two headers/test and additive CMake/workflow entries.

## Open risks / not claimed

- No reflection, variants, cache or incremental invalidation yet.
- No native shader compilation, SPIR-V/DXIL/MSL/WGSL/GLSL artifact, pipeline or GPU execution.
- `GFX-02-04`..`-09` remain blocked until their gates.
- CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `GFX-02-03` as `COMPLETED`, manifest `GFX02_03_COMPLETED_REST_BLOCKED`: **622 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 100 `COMPLETED`, 26 approved gates**.
