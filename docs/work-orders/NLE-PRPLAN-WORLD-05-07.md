# NLE-PRPLAN-WORLD-05-07 — Geometry recipe metadata (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-WORLD-05-07`. **Predecessor:** `WORLD-05-06` biomes. **Issue:** #45. **Base:** `f542bc6`. **ADR:** [ADR-0131](../adr/0131-world-05-internal-procedural-generation-metadata.md). **Contract:** [world-05-procedural-internal-v0](../contracts/world-05-procedural-internal-v0.md).

## OBJECTIVE

Implement bounded logical geometry recipe metadata with unique recipe identities, allowlisted primitives, source references, finite unit scale and LOD counts.

## CONTEXT

WORLD-05-01..-06 are approved or completed. No mesh generation, geometry pipeline, GPU resource or artifact producer exists.

## SCOPE

- `geometry_plan.hpp` and GEO-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Prior procedural changes, generators, qualification, closeout; mesh generation, geometry buffers, GPU, asset I/O, cook/cache, physics, networking, editor.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0131, internal contract, governance contract, prior procedural headers.

## REQUIREMENTS

GOV-001..007; ADR-0131; GEO-01.

## ARCHITECTURE RULES

WORLD-05 owns logical geometry recipe metadata only; GFX-04 owns mesh generation and rendering.

## CONSTRAINTS

Risk `LOW`; `INTERNAL_ONLY`; no mesh/GPU/asset I/O/cook/physics/network/editor; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; GEO-01 valid/invalid fixtures.
- No mesh, geometry buffer, renderer or artifact.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

GEO-01 graph/revision/count validation, unique recipe IDs, nonzero revisions/sources, primitive allowlist, finite positive unit scale, LOD bounds, primitive counts, reset and determinism.

## DELIVERABLES

Header, GEO-01 tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, GEO-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, mesh/GPU selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `f542bc6`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-WORLD-05-07-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-WORLD-05-07.md`.
