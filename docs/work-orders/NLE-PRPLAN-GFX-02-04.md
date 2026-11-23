# NLE-PRPLAN-GFX-02-04 — Logical reflection (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-GFX-02-04`. **Predecessor:** `GFX-02-03` parser/IR. **Issue:** #30. **Base:** `49dde88`. **ADR:** [ADR-0116](../adr/0116-gfx-02-internal-shader-pipeline.md). **Contract:** [gfx-02-shader-internal-v0](../contracts/gfx-02-shader-internal-v0.md).

## OBJECTIVE

Implement deterministic logical reflection over validated SSCL-0 IR: slots, sizes, alignment and module metadata. No native layout, compiler or GPU.

## CONTEXT

GFX-02-01/-02 approved and -03 parser/IR merged. No compiler or GPU exists.

## SCOPE

- `shader_reflection.hpp` and REF-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Variants/cache/incremental/qualification; native compiler/GPU, material/PBR, renderer, dependencies, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0116, contract, governance contract, GFX-02-03 evidence.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0116; REF-01 and exact type table.

## ARCHITECTURE RULES

GFX-02 owns logical reflection; no native compiler/GPU; GFX-01 capabilities remain metadata only.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no compiler/GPU/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; REF-01 valid/invalid fixtures.
- No native compiler/GPU/dependency/native I/O.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

REF-01: slot order by kind, size/alignment table, module/stage/fingerprint preservation, empty reflection, invalid IR names/types/kinds and capacity.

## DELIVERABLES

Header, REF tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, REF-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, native compiler/GPU, host I/O, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `49dde88`; contract blob pinned in activation; GFX-02-03 merge `49dde88`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-02-04-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-GFX-02-04.md`.
