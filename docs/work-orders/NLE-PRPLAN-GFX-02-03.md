# NLE-PRPLAN-GFX-02-03 — SSCL-0 parser and IR (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-GFX-02-03`. **Predecessor:** `GFX-02-02` contract. **Issue:** #30. **Base:** `5cadb01`. **ADR:** [ADR-0116](../adr/0116-gfx-02-internal-shader-pipeline.md). **Contract:** [gfx-02-shader-internal-v0](../contracts/gfx-02-shader-internal-v0.md).

## OBJECTIVE

Implement the bounded SSCL-0 lexer/parser and validated shader IR with typed diagnostics over in-memory source only.

## CONTEXT

GFX-02-01 governance and -02 contract are approved. No compiler, GPU, driver or artifact exists.

## SCOPE

- `shader_types.hpp`, `shader_parser.hpp` and PAR-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Reflection, variants, cache, incremental, qualification/closeout; native compiler/GPU, material/PBR, renderer, dependencies, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0015/0116/0086, internal architecture, contract, governance contract, GFX-02 plan.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0116; PAR-01 and exact API.

## ARCHITECTURE RULES

GFX-02 owns SSCL-0 parser/IR; no native compiler/GPU; DATA/GFX boundaries unchanged.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no compiler/GPU/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; PAR-01 valid/invalid fixtures.
- No external compiler/GPU/dependency/native I/O.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

PAR-01: valid vertex/fragment/compute modules, comments/whitespace, all types, missing/duplicate stage, invalid token/name/module, unknown type, duplicate binding, stage restriction, source/line/capacity limits, diagnostics line/column/path.

## DELIVERABLES

Headers, PAR tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, PAR-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, native compiler/GPU, host I/O, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `5cadb01`; contract blob pinned in activation; GFX-02-02 merge `5cadb01`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-02-03-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-GFX-02-03.md`.
