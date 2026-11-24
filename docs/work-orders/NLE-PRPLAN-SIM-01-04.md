# NLE-PRPLAN-SIM-01-04 — Collision shape metadata (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-SIM-01-04`. **Predecessor:** `SIM-01-03` bodies. **Issue:** #46. **Base:** `94998e8`. **ADR:** [ADR-0132](../adr/0132-sim-01-internal-physics-2d-metadata.md). **Contract:** [sim-01-physics2d-internal-v0](../contracts/sim-01-physics2d-internal-v0.md).

## OBJECTIVE

Implement bounded logical collision-shape metadata with unique IDs, body references, allowlisted shape kinds, finite dimensions, density and sensor flags.

## CONTEXT

SIM-01-01..-03 are approved or completed. No broadphase, narrowphase, contact manifold or solver exists.

## SCOPE

- `shape_plan.hpp` and COL-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Body changes, queries, joints, triggers, masks, qualification, closeout; broadphase/narrowphase, contacts, simulation, ECS mutation, GPU, physics runtime.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0132, internal contract, governance contract, `physics2d_types.hpp`, `body_plan.hpp`.

## REQUIREMENTS

GOV-001..007; ADR-0132; COL-01.

## ARCHITECTURE RULES

SIM-01 owns logical shape descriptors only; no collision is computed and GFX owns rendering.

## CONSTRAINTS

Risk `LOW`; `INTERNAL_ONLY`; no solver/backend/broadphase/narrowphase/contacts/GPU/physics runtime/editor; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; COL-01 valid/invalid fixtures.
- No broadphase, narrowphase, contact or simulation.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

COL-01 world/revision/count validation, unique shape IDs, nonzero body refs/revisions, kind allowlist, dimension rules per kind, density bounds, kind/sensor counts, capacity, reset and determinism.

## DELIVERABLES

Header, COL-01 tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, COL-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, solver/backend selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `94998e8`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-SIM-01-04-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-SIM-01-04.md`.
