# NLE-PRPLAN-CORE-04-02 — Timeline contract (INTERNAL_ONLY)

**STATUS: CONTRACT PACKET — documentary only; implementation remains BLOCKED until CORE-04-03 G6.** **Gate:** G6 contract + CORE-01 capability admission. **Formal packet:** `NLE-PRPLAN-CORE-04-02`. **Predecessor:** `CORE-04-01` governance. **Issue:** #21. **Base:** `7fb0949`. **ADR:** [ADR-0107](../adr/0107-core-04-governance-slice.md). **Contract:** [core-04-timeline-v0](../contracts/core-04-timeline-v0.md).

## OBJECTIVE

Define the first internal CORE-04 timeline contract: injectable monotonic `ClockSource`, rational fixed-step `Timeline`, pause/step, interpolation phase, debt policy, typed errors, replay header and TICK-01..TICK-12 oracles. No implementation.

## CONTEXT

CORE-04-01 is `APPROVED_GOVERNANCE` only. ADR-0006 is ratified as planning direction; CORE-01 is not module-qualified and selected capabilities are admitted. This packet prepares the contract; no code, dependency or timing SDK is selected.

## SCOPE

- Contract `core-04-timeline-v0`: exact logical API, semantics, error model, lifecycle, TICK-01..TICK-12 and allowlists.
- Evidence of contract review and CORE-01 admission boundary.
- No implementation, dependency, CMake target or code test.

## OUT OF SCOPE

Clock/timeline code, SDL3/native timing adapters, third-party time libraries, public ABI, release, CORE-01 completion, physics/netcode determinism, allocator selection, thresholds, CORE-04-03 or any later packet.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0006/0086/0107, CORE-04 architecture/research, governance contract, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0107; ADR-0086 capability rule; no technology/dependency selection.

## ARCHITECTURE RULES

CORE-04 owns tick timeline/debt/interpolation phase; CORE-01 owns OS time; CORE-03 consumes tick IDs; CORE-06 diagnostics; SIM/GFX/NET/AUD boundaries unchanged. Exact rational arithmetic; no float accumulation; no silent authoritative tick loss.

## CONSTRAINTS

Risk `LOW` for this documentary contract; future implementation `ELEVATED`; release `INTERNAL_ONLY`; no code/dependency/secret/paid service; CORE-01 not module-qualified; CORE-02/03 NOT_QUALIFIED; G3 NOT_CLEARED; NLE-D009 OPEN.

## ACCEPTANCE CRITERIA

- Exact contract/API/errors/lifecycle/TICK matrix/allowlists.
- CORE-01 capability admission recorded; no technology or code authorized.
- `CORE-04-02` becomes `APPROVED_CONTRACT`; `-03`..`-10` remain `PLANNED_BLOCKED`.
- Manifest `CORE04_02_APPROVED_CONTRACT_ONLY`: **710 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 30 `COMPLETED`, 8 approved gates**.
- Docs Validation and pt-BR audit; no HIGH/CRITICAL; registry byte-identical.

## TESTS

Docs validators and selector denial; contract review traceability. No native code test is authorized by this packet.

## DELIVERABLES

Contract, G6 activation evidence, activation JSON, manifest/validator/tests/checkpoint. PR, Docs Validation, pt-BR audit, proposed checkpoint only.

## REVIEW FORMAT

pt-BR: base/head, contract fidelity to ADR-0107/0006, admission, no code/technology, blocked packets. APPROVED/CORRECTION REQUIRED/BLOCKED.

## STOP CONDITION

STALE, missing admission, technology selected by inference, API/code implementation, manifest/registry drift, HIGH/CRITICAL, release/ABI claim. No code before CORE-04-03 G6.

## CONTEXT LOCK

Base `7fb0949`; admission pins CORE-01-03/-06/-07/-08/-12/-13; contract review required before `-03`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-CORE-04-02-G6-ACTIVATION.md` with contract review, admission, manifest effect and no-code statement.
