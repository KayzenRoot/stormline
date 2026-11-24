# NLE-PRPLAN-SIM-03-02 — Frozen internal character motor contract (INTERNAL_ONLY)

**STATUS: G6 CONTRACT PACKET — no implementation authorized by this WO.** **Formal packet:** `NLE-PRPLAN-SIM-03-02`. **Predecessor:** `SIM-03-01` governance. **Issue:** #48. **Base:** `c36e620a`. **ADR:** [ADR-0134](../adr/0134-sim-03-internal-character-motor-metadata.md). **Contract:** [sim-03-character-internal-v0](../contracts/sim-03-character-internal-v0.md).

## OBJECTIVE

Freeze the exact header-only logical API, capacities, error model, oracles and per-slice allowlists for SIM-03 before any code.

## CONTEXT

SIM-03-01 governance is approved. No character code exists and no runtime capability is claimed.

## SCOPE

- Internal contract document with exact types, functions, capacities and oracles.
- This WO, G6 evidence, activation JSON, checkpoint and manifest/validator bookkeeping.

## OUT OF SCOPE

All code and tests; motor/sweeper, contact execution, solver/backend, input devices, camera update, animation root motion, ECS mutation, GPU, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0134, internal architecture, governance contract, ADR-0033 research architecture and API.

## REQUIREMENTS

GOV-001..007; oracles CTRL-01, LOCO-01, INPUT-01, CAM-01 and QLF-S301..S304; allowlists `-03`..`-07`.

## ARCHITECTURE RULES

Logical metadata only; no motor handle, backend type, pointer or runtime behavior; all planners fixed-capacity, `noexcept`, allocation-free and reset on failure.

## CONSTRAINTS

Risk `LOW`; `INTERNAL_ONLY`; no code, CMake or workflow change; CORE-01/02/03 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Contract is exact, deterministic and internally consistent with ADR-0134.
- Manifest root `SIM03_02_APPROVED_CONTRACT_ONLY`; `SIM-03-03` remains `PLANNED_BLOCKED`.
- pt-BR audit `APPROVED`.

## TESTS

Validator and documentation checks only; no executable test is authorized by this packet.

## DELIVERABLES

Contract, WO, G6 evidence, activation JSON and validator updates.

## REVIEW FORMAT

pt-BR: base/head, files, API completeness, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, runtime/motor claim, allowlist violation, failed validator, HIGH/CRITICAL.

## CONTEXT LOCK

Base `c36e620a`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-SIM-03-02-G6-ACTIVATION.md`.
