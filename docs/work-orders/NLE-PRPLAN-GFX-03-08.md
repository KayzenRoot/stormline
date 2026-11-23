# NLE-PRPLAN-GFX-03-08 — Logical render graph qualification (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-GFX-03-08`. **Predecessor:** `GFX-03-07` budget. **Issue:** #31. **Base:** `8da2f35`. **ADR:** [ADR-0117](../adr/0117-gfx-03-internal-render-graph.md). **Contract:** [gfx-03-render-graph-internal-v0](../contracts/gfx-03-render-graph-internal-v0.md).

## OBJECTIVE

Add CI-only qualification QLF-G301..G304 over the complete logical render graph pipeline: integrated flow, deterministic repeat, failure recovery and bounded overload.

## CONTEXT

GFX-03-01..07 are approved/completed. No native GPU, allocator, submission or renderer exists.

## SCOPE

- `tests/core/gfx03_graph_qualification_tests.cpp`: QLF-G301..G304.
- Additive CMake target/tests and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Closeout (`-09`); native GPU/hardware, allocator, submission, rendering, performance, ABI or release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0117, contract, budget evidence.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0117; QLF-G301..G304.

## ARCHITECTURE RULES

GFX-03 owns logical qualification; no native GPU/allocator/submission; qualification is not hardware proof.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no GPU/allocator/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; QLF-G301..G304 pass.
- 10,000 graph attempts keep capacities.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

QLF-G301 integrated; QLF-G302 deterministic snapshot; QLF-G303 typed failure followed by valid operation; QLF-G304 10,000 bounded graph attempts.

## DELIVERABLES

Qualification test, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, QLF-G301..G304, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, native GPU/allocator/performance claim, unbounded input, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `8da2f35`; contract blob pinned in activation; GFX-03-07 merge `8da2f35`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-03-08-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-GFX-03-08.md`.
