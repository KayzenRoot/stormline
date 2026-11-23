# NLE-PRPLAN-GFX-02-05 — Deterministic variants (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-GFX-02-05`. **Predecessor:** `GFX-02-04` reflection. **Issue:** #30. **Base:** `d82bdea`. **ADR:** [ADR-0116](../adr/0116-gfx-02-internal-shader-pipeline.md). **Contract:** [gfx-02-shader-internal-v0](../contracts/gfx-02-shader-internal-v0.md).

## OBJECTIVE

Implement deterministic logical variant planning over validated SSCL-0 IR: bounded static-switch combinations, canonical ascending keys and stable source/recipe/stage identity.

## CONTEXT

GFX-02-01..04 are approved/completed. No compiler, GPU or artifact exists.

## SCOPE

- `shader_variant.hpp` and VAR-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Cache/incremental/qualification; native compiler/GPU, pipeline specialization, material/PBR, renderer, dependencies, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0116, contract, governance contract, GFX-02-04 evidence.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0116; VAR-01 and exact variant key semantics.

## ARCHITECTURE RULES

GFX-02 owns logical variant planning; no native compiler/GPU; variant keys are metadata only.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no compiler/GPU/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; VAR-01 valid/invalid fixtures.
- No native compiler/GPU/dependency/native I/O.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

VAR-01: 0/1/8/16 switches, ascending stable keys, source/recipe/stage identity, zero recipe, invalid counts and variant limit.

## DELIVERABLES

Header, VAR tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, VAR-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, native compiler/GPU, host I/O, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `d82bdea`; contract blob pinned in activation; GFX-02-04 merge `d82bdea`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-02-05-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-GFX-02-05.md`.
