# NLE-PRPLAN-CORE-03-07 — Cancellation slice satisfaction (INTERNAL_ONLY)

**STATUS: SATISFACTION CLOSEOUT — documentary only; no new code.** **Gate:** continuation after CORE-03-06. **Formal packet:** `NLE-PRPLAN-CORE-03-07`. **Predecessors:** `CORE-03-02` contract and `CORE-03-03` implementation. **Base:** `1c016b318f55f29ff4539e235925bd466ea89087`. **ADR:** [ADR-0105](../adr/0105-core-03-limited-capability-admission.md). **Contract:** [core-03-task-graph-v0](../contracts/core-03-task-graph-v0.md).

## OBJECTIVE

Record that `CORE-03-07` (“cancelamento”) is satisfied by the approved contract and `CORE-03-03`, using JOB-05/JOB-08 as objective oracles. No OS-level interruption, forced thread termination or new cancellation model is authorized.

## CONTEXT

The owner instructed continuation after the satisfaction closeouts of `CORE-03-04`..`06`. The frozen contract defines cooperative cancellation scopes: pending tasks in scope are cancelled, running tasks observe the scope through their own context, dependents fail, and new submissions after shutdown return `ShuttingDown`. JOB-05 proves scope isolation and pending cancellation; JOB-08 proves stop/shutdown behavior. CORE-02 remains `NOT_QUALIFIED`.

## SCOPE

- Documentary satisfaction decision, evidence mapping and manifest advance for `CORE-03-07` only.
- New WO/evidence files and Decisions Ledger entry.
- No code, test, CMake, workflow, dependency, ABI or release change.

## OUT OF SCOPE

OS-level thread interruption, forced termination of running tasks, preemptive cancellation, cancellation of arbitrary blocking I/O/GPU calls, rollback transactions, priority inheritance, performance thresholds, allocator selection, CORE-02 completion and full Q4.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0105, contract `core-03-task-graph-v0`, CORE-03-03 evidence/PR #508, JOB-05/JOB-06/JOB-08 tests, exact-head CI 44959327194, manifest/registry.

## REQUIREMENTS

- GOV-001..005 and the 2026-11-21 continuation instruction; no new technical scope.
- Evidence must cite real test names and CI results.
- Manifest/validator must reflect `CORE-03-07` completed and `CORE-03-08`..`-10` blocked.
- CORE-02 stays `NOT_QUALIFIED`; no forced-termination, allocator, ABI or release claim.

## ARCHITECTURE RULES

Cancellation remains cooperative and scoped; running functions are never forcibly terminated. CORE-03 does not own OS thread lifecycle, GPU submission or real-time audio callbacks; those boundaries remain with CORE-01/GFX-03/AUD-01.

## CONSTRAINTS

`INTERNAL_ONLY`; risk `ELEVATED` inherited. No secrets, paid services, dependency changes or engine code. No claim of immediate or hard real-time cancellation.

## ACCEPTANCE CRITERIA

- JOB-05/JOB-08 evidence covers scope isolation, pending cancellation, stats, stop idempotence and post-shutdown rejection.
- `CORE-03-07` becomes `COMPLETED` with this closeout PR; `CORE-03-08`..`-10` remain `PLANNED_BLOCKED`.
- Manifest `CORE03_07_COMPLETED_REST_BLOCKED`: **715 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 27 `COMPLETED`, 6 approved gates**.
- Docs Validation and pt-BR audit `APPROVED`; no HIGH/CRITICAL; registry byte-identical.

## TESTS

No new native test. Evidence traces JOB-05 cancellation scope isolation and pending-task cancellation, JOB-08 drain/stop/post-shutdown behavior, JOB-06 deadlock/wrong-thread safety, plus the existing native matrix.

## DELIVERABLES

WO, evidence, Decisions Ledger entry, checkpoint, manifest/validator/tests updates, Docs Validation and pt-BR audit. No code PR.

## REVIEW FORMAT

pt-BR: base/head, files, evidence fidelity, manifest effect, blocked packets, security/rollback and proposed checkpoint delta. Verdict only `APPROVED`, `CORRECTION REQUIRED` or `BLOCKED`.

## STOP CONDITION

Stale context, unsupported cancellation claim, missing JOB evidence, manifest/registry drift, code/dependency change, forced-termination/release/ABI overclaim, HIGH/CRITICAL. Stop and report.

## CONTEXT LOCK

Base `1c016b318f55f29ff4539e235925bd466ea89087`; contract blob `36b03944504b6b8e74907f773ead6901ce8705b0`; CORE-03-03 merge `3a697f6869f7081d9a05089d84ab6021c6e6a550`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-CORE-03-07.md` with JOB-05/JOB-08 traceability, CI IDs and manifest delta. No native PASS is newly claimed by this documentary packet.
