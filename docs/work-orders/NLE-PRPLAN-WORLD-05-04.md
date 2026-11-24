# NLE-PRPLAN-WORLD-05-04 — Generator graph topology metadata (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-WORLD-05-04`. **Predecessor:** `WORLD-05-03` seeds. **Issue:** #45. **Base:** `9067e51`. **ADR:** [ADR-0131](../adr/0131-world-05-internal-procedural-generation-metadata.md). **Contract:** [world-05-procedural-internal-v0](../contracts/world-05-procedural-internal-v0.md).

## OBJECTIVE

Implement bounded logical generator graph topology metadata with stable node/edge identities, typed ports, acyclicity, depth and fan-out limits.

## CONTEXT

WORLD-05-01..-03 are approved or completed. No graph interpreter, node evaluation, noise or artifact producer exists.

## SCOPE

- `graph_plan.hpp` and GRAPH-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Seeds changes, rules, biomes, geometry, generators, qualification, closeout; graph evaluation, RNG/noise, WFC, asset I/O, cook/cache, GPU, physics, networking, editor.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0131, internal contract, governance contract, `procedural_types.hpp`, `seed_plan.hpp`.

## REQUIREMENTS

GOV-001..007; ADR-0131; GRAPH-01.

## ARCHITECTURE RULES

WORLD-05 owns logical graph topology only; CORE-06 owns jobs and no node is executed.

## CONSTRAINTS

Risk `LOW`; `INTERNAL_ONLY`; no evaluation/RNG/noise/WFC/asset I/O/GPU/physics/network/editor; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; GRAPH-01 valid/invalid fixtures.
- No graph evaluation, interpreter, noise or artifact.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

GRAPH-01 graph/node/edge validation, unique IDs, endpoints, self/duplicate edges, cycle rejection, depth and fan-out bounds, roots/leaves, capacity, reset and determinism.

## DELIVERABLES

Header, GRAPH-01 tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, GRAPH-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, evaluation/interpreter selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `9067e51`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-WORLD-05-04-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-WORLD-05-04.md`.
