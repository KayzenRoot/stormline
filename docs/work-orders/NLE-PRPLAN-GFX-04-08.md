# NLE-PRPLAN-GFX-04-08 — Geometry budget validation (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-GFX-04-08`. **Predecessor:** `GFX-04-07` vegetation. **Issue:** #32. **Base:** `4036c94`. **ADR:** [ADR-0118](../adr/0118-gfx-04-internal-geometry-pipeline.md). **Contract:** [gfx-04-geometry-internal-v0](../contracts/gfx-04-geometry-internal-v0.md).

## OBJECTIVE

Implement bounded geometry metric validation and triangle/vertex/byte budget admission with checked totals and typed overcommit.

## CONTEXT

GFX-04-01..07 are approved/completed. No native GPU, mesh library, submission or renderer exists.

## SCOPE

- `geometry_budget.hpp` and GEO-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Qualification/closeout; native GPU/mesh optimization/library, submission, rendering, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0118, internal contract, vegetation evidence.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0118; GEO-01.

## ARCHITECTURE RULES

Budget is logical/estimated; checked arithmetic; overcommit fails closed; no mesh modification.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no GPU/mesh codec/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; GEO-01 valid/invalid fixtures.
- No native GPU/mesh optimization/dependency/native I/O.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

GEO-01: valid totals, duplicate IDs, zero/overflow metrics, budget exceed and exact boundary.

## DELIVERABLES

Header, GEO tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, GEO-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, native mesh optimization/GPU, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `4036c94`; contract blob pinned in activation; GFX-04-07 merge `4036c94`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-04-08-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-GFX-04-08.md`.
