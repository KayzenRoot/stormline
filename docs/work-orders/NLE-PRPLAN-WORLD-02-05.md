# NLE-PRPLAN-WORLD-02-05 — Prefab variant/override metadata (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-WORLD-02-05`. **Predecessor:** `WORLD-02-04` composition. **Issue:** #42. **Base:** `f99e7e1`. **ADR:** [ADR-0128](../adr/0128-world-02-internal-scene-prefab-metadata.md). **Contract:** [world-02-scene-internal-v0](../contracts/world-02-scene-internal-v0.md).

## OBJECTIVE

Implement bounded logical prefab variant/override metadata with stable field keys and conflict rejection.

## CONTEXT

WORLD-02-01..-04 are approved. No override merge, rebase execution, prefab expansion or serializer exists.

## SCOPE

- `prefab_variant_plan.hpp` and VAR-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Instancing, transforms, qualification, closeout; merge/rebase execution, expansion, runtime graph, serializer, journal, spatial, physics, networking, editor, GPU.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0128, internal contract, composition boundary.

## REQUIREMENTS

GOV-001..007; ADR-0128; VAR-01.

## ARCHITECTURE RULES

WORLD-02 owns logical override intent; DATA-04 owns merge/rebase persistence and journal.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no merge/expansion/serializer/thread/network/dependency; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; VAR-01 valid/invalid fixtures.
- No override merge, rebase execution or serializer.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

VAR-01 base identity, override keys, duplicates, conflicts, capacity, reset and determinism.

## DELIVERABLES

Header, VAR tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, VAR-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, merge/serializer selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `f99e7e1`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-WORLD-02-05-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-WORLD-02-05.md`.
