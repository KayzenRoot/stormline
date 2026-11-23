# NLE-PRPLAN-GFX-08-08 — Pooling and quality budget (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-GFX-08-08`. **Predecessor:** `GFX-08-07` density stamps. **Issue:** #36. **Base:** `6b3f466`. **ADR:** [ADR-0122](../adr/0122-gfx-08-internal-vfx-pipeline.md). **Contract:** [gfx-08-vfx-internal-v0](../contracts/gfx-08-vfx-internal-v0.md).

## OBJECTIVE

Implement bounded logical pool generation and quality-budget metadata with exact admission/degradation receipts.

## CONTEXT

GFX-08-01/-07 are approved/completed. No pool allocation, GPU resource or render exists.

## SCOPE

- `pool_plan.hpp` and POOL-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Qualification, closeout; pool allocation, GPU resource, compute, sorting, rendering, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0122, internal contract, GFX-03 resource boundary.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0122; POOL-01.

## ARCHITECTURE RULES

GFX-08 owns logical admission/quality metadata; GFX-03 owns resources and no pool is allocated.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no GPU/compute/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; POOL-01 valid/invalid fixtures.
- No allocation/GPU/render.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

POOL-01 ID/capacity, generation mismatch, checked total, PoolExhausted, per-domain quality clamp with degraded receipt.

## DELIVERABLES

Header, POOL tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, POOL-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, allocation/GPU/SDK selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `6b3f466`; contract blob pinned in activation; GFX-08-07 merge `6b3f466`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-08-08-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-GFX-08-08.md`.
