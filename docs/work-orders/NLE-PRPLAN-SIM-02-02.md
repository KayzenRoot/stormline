# NLE-PRPLAN-SIM-02-02 — Frozen internal 3D physics metadata contract (INTERNAL_ONLY)

**STATUS: G6 CONTRACT PACKET — no implementation authorized by this WO.** **Formal packet:** `NLE-PRPLAN-SIM-02-02`. **Predecessor:** `SIM-02-01` governance. **Issue:** #47. **Base:** `229e2ff9`. **ADR:** [ADR-0133](../adr/0133-sim-02-internal-physics-3d-metadata.md). **Contract:** [sim-02-physics3d-internal-v0](../contracts/sim-02-physics3d-internal-v0.md).

## OBJECTIVE

Freeze the exact header-only logical API, capacities, error model, oracles and per-slice allowlists for SIM-02 before any code.

## CONTEXT

SIM-02-01 governance is approved. No 3D physics code exists and no runtime capability is claimed.

## SCOPE

- Internal contract document with exact types, functions, capacities and oracles.
- This WO, G6 evidence, activation JSON, checkpoint and manifest/validator bookkeeping.

## OUT OF SCOPE

All code and tests; solver/backend, broadphase/narrowphase execution, query execution, contacts, simulation, ECS mutation, GPU, editor, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0133, internal architecture, governance contract, ADR-0032 research architecture and API.

## REQUIREMENTS

GOV-001..007; oracles BODY3-01, SHAPE3-01, BROAD3-01, QUERY3-01, CONSTRAINT3-01, INTEGRATION3-01 and QLF-S201..S204; allowlists `-03`..`-09`.

## ARCHITECTURE RULES

Logical metadata only; no solver handle, backend type, pointer or runtime behavior; all planners fixed-capacity, `noexcept`, allocation-free and reset on failure.

## CONSTRAINTS

Risk `LOW`; `INTERNAL_ONLY`; no code, CMake or workflow change; CORE-01/02/03 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Contract is exact, deterministic and internally consistent with ADR-0133.
- Manifest root `SIM02_02_APPROVED_CONTRACT_ONLY`; `SIM-02-03` remains `PLANNED_BLOCKED`.
- pt-BR audit `APPROVED`.

## TESTS

Validator and documentation checks only; no executable test is authorized by this packet.

## DELIVERABLES

Contract, WO, G6 evidence, activation JSON and validator updates.

## REVIEW FORMAT

pt-BR: base/head, files, API completeness, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, runtime/physics claim, allowlist violation, failed validator, HIGH/CRITICAL.

## CONTEXT LOCK

Base `229e2ff9`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-SIM-02-02-G6-ACTIVATION.md`.
