# NLE-PRPLAN-GFX-03-04 — Hazard dependency DAG (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-GFX-03-04`. **Predecessor:** `GFX-03-03` definitions. **Issue:** #31. **Base:** `0342cc5`. **ADR:** [ADR-0117](../adr/0117-gfx-03-internal-render-graph.md). **Contract:** [gfx-03-render-graph-internal-v0](../contracts/gfx-03-render-graph-internal-v0.md).

## OBJECTIVE

Implement writer/reader hazard analysis, deterministic dependency edges, cycle detection and stable topological ordering over validated logical graph definitions.

## CONTEXT

GFX-03-01..03 are approved/completed. No native GPU, allocator, submission or renderer exists.

## SCOPE

- `graph_dependency.hpp` and DEP-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Sync transitions, transients, budget, qualification; native GPU/allocator, submission, rendering, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0117, internal contract, graph definitions evidence.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0117; DEP-01 and exact hazard/topology semantics.

## ARCHITECTURE RULES

GFX-03 owns logical DAG compilation; no native GPU/submission; one writer per resource in v0.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no GPU/allocator/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; DEP-01 valid/invalid fixtures.
- No native GPU/allocator/dependency/native I/O.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

DEP-01: RAW edges, ambiguous writer, uninitialized transient read, cycle, pre-initialized external read, stable topological tie-break and capacity.

## DELIVERABLES

Header, DEP tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, DEP-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, native GPU/allocator, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `0342cc5`; contract blob pinned in activation; GFX-03-03 merge `0342cc5`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-03-04-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-GFX-03-04.md`.
