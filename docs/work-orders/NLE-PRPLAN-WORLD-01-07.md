# NLE-PRPLAN-WORLD-01-07 — Reflection field metadata (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-WORLD-01-07`. **Predecessor:** `WORLD-01-06` queries. **Issue:** #41. **Base:** `47b19a0`. **ADR:** [ADR-0127](../adr/0127-world-01-internal-entity-metadata.md). **Contract:** [world-01-entity-internal-v0](../contracts/world-01-entity-internal-v0.md).

## OBJECTIVE

Implement bounded logical reflection field metadata with allowlisted names, kinds, units, bounds and edit/serialization flags.

## CONTEXT

WORLD-01-01..-06 are approved. No RTTI, object addresses, callbacks, editor UI or serializer exists.

## SCOPE

- `reflection_plan.hpp` and REF-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Qualification, closeout; RTTI/addresses/callbacks, dynamic reflection, editor UI, serializer, migration, storage, GPU.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0127, internal contract, query boundary.

## REQUIREMENTS

GOV-001..007; ADR-0127; REF-01.

## ARCHITECTURE RULES

WORLD-01 owns logical reflection metadata; no runtime reflection, object access or dynamic code is created.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no RTTI/address/callback/dynamic code/serializer/network/dependency; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; REF-01 valid/invalid fixtures.
- No RTTI, addresses, callbacks, editor or serializer.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

REF-01 type/field/name identity, kinds, finite ordered ranges, flags, capacity, reset and determinism.

## DELIVERABLES

Header, REF tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, REF-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, RTTI/callback/serializer selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `47b19a0`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-WORLD-01-07-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-WORLD-01-07.md`.
