# NLE-PRPLAN-GFX-02-06 — In-memory shader cache identity (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-GFX-02-06`. **Predecessor:** `GFX-02-05` variants. **Issue:** #30. **Base:** `b414cb4`. **ADR:** [ADR-0116](../adr/0116-gfx-02-internal-shader-pipeline.md). **Contract:** [gfx-02-shader-internal-v0](../contracts/gfx-02-shader-internal-v0.md).

## OBJECTIVE

Implement bounded in-memory cache identity over logical variant keys: deterministic FNV-1a 64 keys, capacity, idempotent insert, mismatch rejection and miss semantics.

## CONTEXT

GFX-02-01..05 are approved/completed. No compiler, GPU or artifact exists.

## SCOPE

- `shader_cache.hpp` and CAC-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Incremental/qualification; persistence, compiler/GPU, driver cache, signing, dependency, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0116, contract, governance contract, GFX-02-05 evidence.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0116; CAC-01 and exact cache semantics.

## ARCHITECTURE RULES

GFX-02 owns logical cache identity; no persistence or native cache; keys are not authentication.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no compiler/GPU/persistence/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; CAC-01 valid/invalid fixtures.
- No native compiler/GPU/persistence/dependency/native I/O.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

CAC-01: deterministic key, put/get, idempotent duplicate, payload mismatch, capacity, miss, invalid key/payload and clear.

## DELIVERABLES

Header, CAC tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, CAC-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, persistence/compiler/GPU, host I/O, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `b414cb4`; contract blob pinned in activation; GFX-02-05 merge `b414cb4`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-02-06-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-GFX-02-06.md`.
