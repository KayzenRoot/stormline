# NLE-PRPLAN-WORLD-05-08 — Content generator metadata (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-WORLD-05-08`. **Predecessor:** `WORLD-05-07` geometry. **Issue:** #45. **Base:** `024a815`. **ADR:** [ADR-0131](../adr/0131-world-05-internal-procedural-generation-metadata.md). **Contract:** [world-05-procedural-internal-v0](../contracts/world-05-procedural-internal-v0.md).

## OBJECTIVE

Implement bounded logical content-generator metadata with unique IDs, allowlisted categories, seed-domain references, per-generator caps and a checked total cap.

## CONTEXT

WORLD-05-01..-07 are approved or completed. No artifact producer, cache, asset I/O or generation runtime exists.

## SCOPE

- `generator_plan.hpp` and GEN-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Prior procedural changes, qualification, closeout; artifact production, RNG/noise, WFC, asset I/O, cook/cache, GPU, physics, networking, editor.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0131, internal contract, governance contract, prior procedural headers.

## REQUIREMENTS

GOV-001..007; ADR-0131; GEN-01.

## ARCHITECTURE RULES

WORLD-05 owns logical generator descriptors only; no artifact is produced and DATA-05 owns cook/cache.

## CONSTRAINTS

Risk `LOW`; `INTERNAL_ONLY`; no production/RNG/noise/WFC/asset I/O/GPU/physics/network/editor; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; GEN-01 valid/invalid fixtures.
- No artifact, generator execution, cache or asset write.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

GEN-01 graph/revision/count validation, unique generator IDs, nonzero revisions/seed domains, category allowlist, per-generator cap bounds, checked total cap, category counts, reset and determinism.

## DELIVERABLES

Header, GEN-01 tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, GEN-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, artifact/runtime selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `024a815`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-WORLD-05-08-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-WORLD-05-08.md`.
