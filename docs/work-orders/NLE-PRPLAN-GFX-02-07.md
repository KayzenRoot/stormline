# NLE-PRPLAN-GFX-02-07 — Dependency-revision incremental invalidation (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-GFX-02-07`. **Predecessor:** `GFX-02-06` cache. **Issue:** #30. **Base:** `ff683bb`. **ADR:** [ADR-0116](../adr/0116-gfx-02-internal-shader-pipeline.md). **Contract:** [gfx-02-shader-internal-v0](../contracts/gfx-02-shader-internal-v0.md).

## OBJECTIVE

Implement bounded dependency-revision fingerprinting and incremental rebuild decisions over logical metadata. No files, compiler, GPU or persistence.

## CONTEXT

GFX-02-01..06 are approved/completed. Logical cache identity exists.

## SCOPE

- `shader_incremental.hpp` and INC-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Qualification/closeout; file watching, persistence, compiler/GPU, dependency manager, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0116, contract, governance contract, GFX-02-06 evidence.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0116; INC-01 and canonical dependency ordering.

## ARCHITECTURE RULES

GFX-02 owns logical invalidation; no host I/O or file watching; dependency IDs are opaque metadata.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no compiler/GPU/persistence/dependency manager/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; INC-01 valid/invalid fixtures.
- No native compiler/GPU/persistence/native I/O.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

INC-01: stable/order-insensitive fingerprint, duplicate IDs, zero ID/revision, capacity, rebuild on changed revision/fingerprint/cache key, no rebuild on equal state.

## DELIVERABLES

Header, INC tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, INC-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, persistence/compiler/GPU, host I/O, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `ff683bb`; contract blob pinned in activation; GFX-02-06 merge `ff683bb`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-02-07-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-GFX-02-07.md`.
