# NLE-PRPLAN-SIM-04-02 — Frozen internal skeletal animation contract (INTERNAL_ONLY)

**STATUS: G6 CONTRACT PACKET — no implementation authorized by this WO.** **Formal packet:** `NLE-PRPLAN-SIM-04-02`. **Predecessor:** `SIM-04-01` governance. **Issue:** #49. **Base:** `8a595f95`. **ADR:** [ADR-0135](../adr/0135-sim-04-internal-skeletal-animation-metadata.md). **Contract:** [sim-04-animation-internal-v0](../contracts/sim-04-animation-internal-v0.md).

## OBJECTIVE

Freeze the exact header-only logical API, capacities, error model, oracles and per-slice allowlists for SIM-04 before any code.

## CONTEXT

SIM-04-01 governance is approved. No animation code exists and no runtime capability is claimed.

## SCOPE

- Internal contract document with exact types, functions, capacities and oracles.
- This WO, G6 evidence, activation JSON, checkpoint and manifest/validator bookkeeping.

## OUT OF SCOPE

All code and tests; pose evaluator, blend/IK execution, ragdoll runtime, codecs, root-motion application, ECS mutation, GPU, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0135, internal architecture, governance contract, ADR-0034 research architecture and API.

## REQUIREMENTS

GOV-001..007; oracles RET-01, BLEND-01, IK-01, RAG-01, CMP-01, SYNC-01 and QLF-S401..S404; allowlists `-03`..`-09`.

## ARCHITECTURE RULES

Logical metadata only; no runtime handle, backend type, pointer or runtime behavior; all planners fixed-capacity, `noexcept`, allocation-free and reset on failure.

## CONSTRAINTS

Risk `LOW`; `INTERNAL_ONLY`; no code, CMake or workflow change; CORE-01/02/03 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Contract is exact, deterministic and internally consistent with ADR-0135.
- Manifest root `SIM04_02_APPROVED_CONTRACT_ONLY`; `SIM-04-03` remains `PLANNED_BLOCKED`.
- pt-BR audit `APPROVED`.

## TESTS

Validator and documentation checks only; no executable test is authorized by this packet.

## DELIVERABLES

Contract, WO, G6 evidence, activation JSON and validator updates.

## REVIEW FORMAT

pt-BR: base/head, files, API completeness, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, runtime/animation claim, allowlist violation, failed validator, HIGH/CRITICAL.

## CONTEXT LOCK

Base `8a595f95`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-SIM-04-02-G6-ACTIVATION.md`.
