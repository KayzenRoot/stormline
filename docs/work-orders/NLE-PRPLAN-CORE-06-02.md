# NLE-PRPLAN-CORE-06-02 — Diagnostics contract (INTERNAL_ONLY)

**STATUS: CONTRACT PACKET — documentary only; implementation remains BLOCKED until CORE-06-03 G6.** **Gate:** G6 contract + CORE-01 capability admission. **Formal packet:** `NLE-PRPLAN-CORE-06-02`. **Predecessor:** `CORE-06-01` governance. **Issue:** #23. **Base:** `9c800e5fb6750dd8e6206e0ea72af7bb9aeabf9a`. **ADR:** [ADR-0109](../adr/0109-core-06-governance-slice.md). **Contract:** [core-06-diagnostics-v0](../contracts/core-06-diagnostics-v0.md).

## OBJECTIVE

Freeze the CORE-06 internal diagnostics contract: bounded text, typed errors, logs, spans, counters, local crash envelope, profile samples and opt-in local telemetry. No implementation.

## CONTEXT

CORE-06-01 is `APPROVED_GOVERNANCE` only. ADR-0008 is planning direction; ADR-0109 limits admission to completed CORE-01 capabilities. CORE-01 is not module-qualified. No third-party library, network endpoint, crash upload or profiler is selected.

## SCOPE

- Contract `core-06-diagnostics-v0`: exact API, semantics, errors, LOG/TRACE/COUNTER/CRASH/PROF/TEL oracles and exact allowlists.
- Evidence of contract review and CORE-01 admission boundary.
- No implementation, dependency, CMake target or code test.

## OUT OF SCOPE

Diagnostics code, spdlog/Tracy/Perfetto/Crashpad, network/telemetry upload, crash handler/dump parsing, profiler listener, serialization format, public ABI/release, CORE-01 completion, CORE-06-03 or later.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0008/0086/0109, CORE-06 architecture/research, governance contract, module catalog, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0109; ADR-0086; local-first, bounded text, drop accounting, no network/file/crash-handler claim.

## ARCHITECTURE RULES

CORE-06 owns facade/semantics/local sink policy; CORE-01 OS crash/lifecycle; CORE-02 memory; CORE-03 jobs; CORE-04 ticks; GFX GPU; AUD realtime; DATA provenance; EDIT/QA/AI projections. No architecture cycle.

## CONSTRAINTS

Risk `LOW` docs/`ELEVATED` implementation; release `INTERNAL_ONLY`; no code/dependency/secret/paid service/network/ABI/release. CORE-01 not module-qualified; CORE-02 NOT_QUALIFIED; CORE-03/04/05 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## ACCEPTANCE CRITERIA

- Exact API/errors/semantics/test matrix/allowlists.
- No third-party/network/crash-upload/profiler selection.
- `CORE-06-02` becomes `APPROVED_CONTRACT`; `-03`..`-10` remain `PLANNED_BLOCKED`.
- Manifest `CORE06_02_APPROVED_CONTRACT_ONLY`: **690 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 46 `COMPLETED`, 12 approved gates**.
- Docs Validation + pt-BR audit; no HIGH/CRITICAL; registry byte-identical.

## TESTS

Docs validators, selector denial, contract review. No native code test authorized.

## DELIVERABLES

Contract, G6 activation evidence, activation JSON, manifest/validator/tests/checkpoint. PR, Docs Validation, pt-BR audit, proposed checkpoint only.

## REVIEW FORMAT

pt-BR: base/head, contract fidelity to ADR-0109/0008, admission, no code/technology, blocked packets. APPROVED/CORRECTION REQUIRED/BLOCKED.

## STOP CONDITION

STALE, missing admission, technology/network selected by inference, code implementation, manifest/registry drift, HIGH/CRITICAL, release/ABI/crash-capture claim. No code before CORE-06-03 G6.

## CONTEXT LOCK

Base `9c800e5`; admission pins CORE-01-03/-06/-07/-08/-12/-13; contract review required before `-03`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-CORE-06-02-G6-ACTIVATION.md`.
