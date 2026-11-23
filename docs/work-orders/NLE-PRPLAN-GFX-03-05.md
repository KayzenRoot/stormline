# NLE-PRPLAN-GFX-03-05 — Logical synchronization transitions (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-GFX-03-05`. **Predecessor:** `GFX-03-04` dependencies. **Issue:** #31. **Base:** `d12d56b`. **ADR:** [ADR-0117](../adr/0117-gfx-03-internal-render-graph.md). **Contract:** [gfx-03-render-graph-internal-v0](../contracts/gfx-03-render-graph-internal-v0.md).

## OBJECTIVE

Implement deterministic logical synchronization transitions from the dependency order: initialization, access changes and queue handoffs. No native barrier or submission.

## CONTEXT

GFX-03-01..04 are approved/completed. No native GPU, allocator, submission or renderer exists.

## SCOPE

- `graph_sync.hpp` and SYN-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Transients, budget, qualification; native barriers/fences, GPU/allocator, submission, rendering, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0117, internal contract, dependency evidence.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0117; SYN-01 and exact transition semantics.

## ARCHITECTURE RULES

GFX-03 owns logical sync metadata; no native barrier/fence; transitions are not execution evidence.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no GPU/allocator/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; SYN-01 valid/invalid fixtures.
- No native GPU/allocator/dependency/native I/O.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

SYN-01: first use, access change, queue handoff, no-op same access/queue, invalid dependency order and transition capacity boundary.

## DELIVERABLES

Header, SYN tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, SYN-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, native barrier/GPU/allocator, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `d12d56b`; contract blob pinned in activation; GFX-03-04 merge `d12d56b`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-03-05-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-GFX-03-05.md`.
