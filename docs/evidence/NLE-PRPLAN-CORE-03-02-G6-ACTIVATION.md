# NLE-PRPLAN-CORE-03-02 — G6 contract activation

**Status:** `G6 CONTRACT PROPOSAL / NO CODE AUTHORIZED / D2 LIMITED ADMISSION`. **Base main:** `dcb2cbd7739d44d09f432621d2dbd0acdef14cb1`. **Formal packet:** `NLE-PRPLAN-CORE-03-02`. **ADR:** [ADR-0105](../adr/0105-core-03-limited-capability-admission.md). **Contract:** [core-03-task-graph-v0](../contracts/core-03-task-graph-v0.md). **WO:** [NLE-PRPLAN-CORE-03-02](../work-orders/NLE-PRPLAN-CORE-03-02.md).

## Authorization

Owner ratified A+B+C+D2 on 2026-11-21 (NLE-D022). This gate prepares only the `CORE-03-02` contract after Docs Validation and pt-BR audit. It does not activate `CORE-03-03`, choose Taskflow/enkiTS/oneTBB/SFAS, write scheduler code, approve release/ABI or declare CORE-02 complete.

## D2 capability admission

- Formal `CORE-02` dependency remains; CORE-02 is **NOT_QUALIFIED** as a module.
- Admission is limited to completed `CORE-02-03..09` capabilities: ownership, system baseline, arena, budget, leak tracker, telemetry and integrated qualification.
- No core scheduling capability is claimed; `module_completion_claimed=false`.
- Any implementation must still pass `CORE-03-03` G6, contract audit, TSan/race/deadlock/cancellation/overload proof and owner authorization.

## Contract scope

- Logical `TaskGraph`/`JobExecutor` API, fixed capacity/workers, priorities, dependencies, cancellation scopes, fences, affinity, deterministic commit order, bounded queue, typed errors and report-only stats.
- JOB-01..JOB-10 test matrix and future allowlist.
- No third-party type, no code, no public ABI, no release.

## Gate state after merge

- Manifest root `CORE03_02_APPROVED_CONTRACT_ONLY`: **720 `PLANNED_BLOCKED`, 22 `COMPLETED`, 6 approved gates (2 CORE-01 + 2 CORE-02 + 1 CORE-03 governance + 1 CORE-03 contract), 0 `EXECUTOR_READY`**.
- `CORE-03-02` becomes `APPROVED_CONTRACT`; `CORE-03-03`..`-10` remain `PLANNED_BLOCKED`.
- Selector denies every ID; registry byte-identical; 80/80 module WOs BLOCKED.

## Proof obligations

Docs Validation, contract review, selector denial, registry byte-identity, pt-BR audit, no HIGH/CRITICAL.

No code/native PASS is claimed by this contract gate.
