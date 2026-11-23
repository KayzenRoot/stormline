# NLE-PRPLAN-TWO-02-05 — Collision authoring shapes (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-TWO-02-05`. **Predecessor:** `TWO-02-04` tiles. **Issue:** #38. **Base:** `29a812a`. **ADR:** [ADR-0124](../adr/0124-two-02-internal-tilemap-pipeline.md). **Contract:** [two-02-tilemap-internal-v0](../contracts/two-02-tilemap-internal-v0.md).

## OBJECTIVE

Implement bounded logical tile collision-authoring metadata (rect/segment, solidity/one-way).

## CONTEXT

TWO-02-01/-04 are approved/completed. No collision solver, contact, physics activation, GPU or render exists.

## SCOPE

- `collision_plan.hpp` and COL-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Qualification, closeout; collision solver, contacts, broadphase, physics activation, navigation, GPU, render, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0124, internal contract, PHYS boundary.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0124; COL-01.

## ARCHITECTURE RULES

TWO-02 authors collision metadata only; PHYS owns solver and authoritative contacts.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no solver/physics/GPU/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; COL-01 valid/invalid fixtures.
- No solver/contact/physics execution.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

COL-01 IDs, rect/segment bounds, finite values, solid/one-way flags, capacity.

## DELIVERABLES

Header, COL tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, COL-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, solver/physics/GPU selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `29a812a`; contract blob pinned in activation; TWO-02-04 merge `29a812a`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-TWO-02-05-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-TWO-02-05.md`.
