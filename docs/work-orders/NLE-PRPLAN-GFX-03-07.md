# NLE-PRPLAN-GFX-03-07 — Logical VRAM budget admission (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-GFX-03-07`. **Predecessor:** `GFX-03-06` transients. **Issue:** #31. **Base:** `953d785`. **ADR:** [ADR-0117](../adr/0117-gfx-03-internal-render-graph.md). **Contract:** [gfx-03-render-graph-internal-v0](../contracts/gfx-03-render-graph-internal-v0.md).

## OBJECTIVE

Implement bounded logical VRAM admission: persistent/transient accounting, alias savings, checked arithmetic and typed unknown/overcommit failures.

## CONTEXT

GFX-03-01..06 are approved/completed. No native GPU, allocator, submission or renderer exists.

## SCOPE

- `graph_budget.hpp` and BUD-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Qualification/closeout; native heap/allocator, GPU, submission, rendering, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0117, internal contract, transient evidence.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0117; BUD-01 and exact accounting.

## ARCHITECTURE RULES

Budget is logical/estimated; unknown fails closed; external resources excluded; no native allocation.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no GPU/allocator/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; BUD-01 valid/invalid fixtures.
- No native GPU/allocator/dependency/native I/O.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

BUD-01: known/within, unknown, zero headroom, headroom>total, overcommit, external exclusion, history accounting, alias savings copy and overflow rejection.

## DELIVERABLES

Header, BUD tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, BUD-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, native heap/GPU/allocator, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `953d785`; contract blob pinned in activation; GFX-03-06 merge `953d785`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-03-07-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-GFX-03-07.md`.
