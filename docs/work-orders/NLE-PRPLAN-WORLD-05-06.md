# NLE-PRPLAN-WORLD-05-06 — Biome classification metadata (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-WORLD-05-06`. **Predecessor:** `WORLD-05-05` rules. **Issue:** #45. **Base:** `c512595`. **ADR:** [ADR-0131](../adr/0131-world-05-internal-procedural-generation-metadata.md). **Contract:** [world-05-procedural-internal-v0](../contracts/world-05-procedural-internal-v0.md).

## OBJECTIVE

Implement bounded logical biome classification metadata with unique zones, palette references, finite weights, priorities and enabled-state counts.

## CONTEXT

WORLD-05-01..-05 are approved or completed. No biome solver, classification, noise or artifact producer exists.

## SCOPE

- `biome_plan.hpp` and BIOME-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Seeds/graph/rules changes, geometry, generators, qualification, closeout; classification, RNG/noise, WFC, asset I/O, cook/cache, GPU, physics, networking, editor.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0131, internal contract, governance contract, prior procedural headers.

## REQUIREMENTS

GOV-001..007; ADR-0131; BIOME-01.

## ARCHITECTURE RULES

WORLD-05 owns logical biome descriptors only; no classification is computed and WORLD-04 owns authored biomes.

## CONSTRAINTS

Risk `LOW`; `INTERNAL_ONLY`; no classification/RNG/noise/WFC/asset I/O/GPU/physics/network/editor; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; BIOME-01 valid/invalid fixtures.
- No classification, solver, noise or artifact.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

BIOME-01 graph/revision/count validation, unique zones, nonzero palettes/revisions, finite weight ranges, enabled counts, total weight, max priority, capacity, reset and determinism.

## DELIVERABLES

Header, BIOME-01 tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, BIOME-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, classification/solver selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `c512595`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-WORLD-05-06-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-WORLD-05-06.md`.
