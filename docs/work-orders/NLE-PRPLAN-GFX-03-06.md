# NLE-PRPLAN-GFX-03-06 — Transient lifetimes and alias planning (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-GFX-03-06`. **Predecessor:** `GFX-03-05` sync. **Issue:** #31. **Base:** `c14cf59`. **ADR:** [ADR-0117](../adr/0117-gfx-03-internal-render-graph.md). **Contract:** [gfx-03-render-graph-internal-v0](../contracts/gfx-03-render-graph-internal-v0.md).

## OBJECTIVE

Implement logical transient lifetimes and conservative alias grouping from the dependency order, with deterministic output and checked savings.

## CONTEXT

GFX-03-01..05 are approved/completed. No native GPU, allocator, submission or renderer exists.

## SCOPE

- `graph_transient.hpp` and TRA-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Budget, qualification; native heap/allocator, GPU, submission, rendering, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0117, internal contract, sync evidence.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0117; TRA-01 and conservative alias rules.

## ARCHITECTURE RULES

Only transient, equal-size/alignment, strictly disjoint lifetimes alias; no native heap claim.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no GPU/allocator/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; TRA-01 valid/invalid fixtures.
- No native GPU/allocator/dependency/native I/O.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

TRA-01: disjoint alias, overlapping no-alias, size/alignment mismatch, persistent/external exclusion, unused transient, invalid dependency order and saved bytes.

## DELIVERABLES

Header, TRA tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, TRA-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, native heap/GPU/allocator, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `c14cf59`; contract blob pinned in activation; GFX-03-05 merge `c14cf59`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-03-06-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-GFX-03-06.md`.
