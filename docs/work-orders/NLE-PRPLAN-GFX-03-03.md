# NLE-PRPLAN-GFX-03-03 — Graph definitions and passes (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-GFX-03-03`. **Predecessor:** `GFX-03-02` contract. **Issue:** #31. **Base:** `3523c7e`. **ADR:** [ADR-0117](../adr/0117-gfx-03-internal-render-graph.md). **Contract:** [gfx-03-render-graph-internal-v0](../contracts/gfx-03-render-graph-internal-v0.md).

## OBJECTIVE

Implement bounded logical graph definitions: pass/resource/use tables, add operations, validation and typed diagnostics.

## CONTEXT

GFX-03-01/-02 are approved. No native GPU, allocator, submission or renderer exists.

## SCOPE

- `graph_types.hpp`, `graph_definition.hpp` and DEF-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Dependencies, sync, transients, budget, qualification; native GPU/allocator, submission, rendering, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0117, internal contract, governance contract, GFX-01 RHI types.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0117; DEF-01 and exact API.

## ARCHITECTURE RULES

GFX-03 owns logical definitions; no native GPU/submission; GFX/CORE boundaries unchanged.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no GPU/allocator/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; DEF-01 valid/invalid fixtures.
- No native GPU/allocator/dependency/native I/O.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

DEF-01: valid definitions, duplicate IDs, capacities, invalid sizes/alignment/enums, unknown references, no partial mutation and error names.

## DELIVERABLES

Headers, DEF tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, DEF-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, native GPU/allocator, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `3523c7e`; contract blob pinned in activation; GFX-03-02 merge `3523c7e`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-03-03-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-GFX-03-03.md`.
