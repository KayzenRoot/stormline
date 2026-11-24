# NLE-PRPLAN-WORLD-05-05 — Rule metadata (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-WORLD-05-05`. **Predecessor:** `WORLD-05-04` graph topology. **Issue:** #45. **Base:** `792cdca`. **ADR:** [ADR-0131](../adr/0131-world-05-internal-procedural-generation-metadata.md). **Contract:** [world-05-procedural-internal-v0](../contracts/world-05-procedural-internal-v0.md).

## OBJECTIVE

Implement bounded logical rule metadata with unique rule identities, condition codes, finite weights, precedence and enabled-state counts.

## CONTEXT

WORLD-05-01..-04 are approved or completed. No rule engine, condition evaluator, noise or artifact producer exists.

## SCOPE

- `rule_plan.hpp` and RULE-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Seeds/graph changes, biomes, geometry, generators, qualification, closeout; rule evaluation, RNG/noise, WFC, asset I/O, cook/cache, GPU, physics, networking, editor.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0131, internal contract, governance contract, `procedural_types.hpp`, `seed_plan.hpp`, `graph_plan.hpp`.

## REQUIREMENTS

GOV-001..007; ADR-0131; RULE-01.

## ARCHITECTURE RULES

WORLD-05 owns logical rule descriptors only; no condition is evaluated and no artifact is produced.

## CONSTRAINTS

Risk `LOW`; `INTERNAL_ONLY`; no evaluation/RNG/noise/WFC/asset I/O/GPU/physics/network/editor; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; RULE-01 valid/invalid fixtures.
- No rule engine, condition evaluation, noise or artifact.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

RULE-01 graph/revision/count validation, unique rule IDs, nonzero conditions/revisions, finite weight ranges, enabled counts, total weight, max priority, capacity, reset and determinism.

## DELIVERABLES

Header, RULE-01 tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, RULE-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, rule engine/evaluation selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `792cdca`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-WORLD-05-05-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-WORLD-05-05.md`.
