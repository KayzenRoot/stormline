# NLE-PRPLAN-WORLD-05-03 — Seed/domain metadata (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-WORLD-05-03`. **Predecessor:** `WORLD-05-02` contract. **Issue:** #45. **Base:** `e65560c`. **ADR:** [ADR-0131](../adr/0131-world-05-internal-procedural-generation-metadata.md). **Contract:** [world-05-procedural-internal-v0](../contracts/world-05-procedural-internal-v0.md).

## OBJECTIVE

Implement bounded logical seed/domain metadata with explicit seed halves, project/graph identity, unique domains and channel bounds.

## CONTEXT

WORLD-05-01/-02 are approved. No RNG, noise, graph evaluator or artifact producer exists.

## SCOPE

- `procedural_types.hpp`, `seed_plan.hpp` and SEED-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Graphs, rules, biomes, geometry, generators, qualification, closeout; RNG/noise execution, asset I/O, cook/cache, GPU, physics, networking, editor.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0131, internal contract, governance contract, WORLD-05 architecture.

## REQUIREMENTS

GOV-001..007; ADR-0131; SEED-01.

## ARCHITECTURE RULES

WORLD-05 owns logical seed intent only; no random stream is produced and CORE-05/06 own numeric infrastructure.

## CONSTRAINTS

Risk `LOW`; `INTERNAL_ONLY`; no RNG/noise/WFC/asset I/O/GPU/physics/network/editor; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; SEED-01 valid/invalid fixtures.
- No random stream, noise, asset read or artifact.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

SEED-01 project/graph/seed validation, domain uniqueness, derivation versions, channel bounds, checked total channels, capacity, reset and determinism.

## DELIVERABLES

Headers, SEED-01 tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, SEED-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, RNG/noise/evaluation selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `e65560c`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-WORLD-05-03-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-WORLD-05-03.md`.
