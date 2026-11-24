# NLE-PRPLAN-SIM-01-02 — Physics 2D internal contract (INTERNAL_ONLY)

**STATUS: G6 CONTRACT PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-SIM-01-02`. **Predecessor:** `SIM-01-01` governance. **Issue:** #46. **Base:** `64eeff5`. **ADR:** [ADR-0132](../adr/0132-sim-01-internal-physics-2d-metadata.md). **Contract:** [sim-01-physics2d-internal-v0](../contracts/sim-01-physics2d-internal-v0.md).

## OBJECTIVE

Freeze the exact header-only logical API, capacities, error model, test oracles and per-slice allowlists for SIM-01 implementation.

## CONTEXT

SIM-01-01 governance is approved. ADR-0031 remains `PROPOSED`; no solver, backend, simulation or runtime physics exists.

## SCOPE

- `docs/contracts/sim-01-physics2d-internal-v0.md`.
- WO, G6 evidence, activation JSON, checkpoint line and manifest/validator wiring.
- No code.

## OUT OF SCOPE

All implementation slices `-03`..`-09`; solver/backend, simulation, broadphase/narrowphase, query execution, contacts/events, ECS mutation, tilemap bridge, GPU, performance.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0132, governance contract, SIM-01 architecture/API/plan.

## REQUIREMENTS

GOV-001..007; ADR-0132; BODY-01, COL-01, QRY-01, JNT-01, TRG-01, MSK-01, QLF-S101..S104.

## ARCHITECTURE RULES

Header-only metadata under `src/stormline/physics2d/`; no runtime owner is duplicated and no simulation is introduced.

## CONSTRAINTS

Risk `LOW`; `INTERNAL_ONLY`; ADR-0031 remains PROPOSED; no engine code/backend/simulation/GPU/assets/physics runtime/editor; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact contract; no code.
- Fixed capacities, typed errors, deterministic oracles and exact allowlists per slice.
- Validators pass; pt-BR audit `APPROVED`.

## TESTS

Validator suite, docs validation and manifest counts only; implementation tests are defined for later gates.

## DELIVERABLES

Frozen contract, WO, evidence, activation JSON, checkpoint and validator wiring, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, contract exactness, validators/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift beyond governance, runtime scope expansion, allowlist violation, validator failure, HIGH/CRITICAL or release/ABI claim.

## CONTEXT LOCK

Base `64eeff5`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-SIM-01-02-G6-ACTIVATION.md`.
