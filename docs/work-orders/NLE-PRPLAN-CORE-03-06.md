# NLE-PRPLAN-CORE-03-06 — Affinity slice satisfaction (INTERNAL_ONLY)

**STATUS: SATISFACTION CLOSEOUT — documentary only; no new code.** **Gate:** continuation after CORE-03-05. **Formal packet:** `NLE-PRPLAN-CORE-03-06`. **Predecessors:** `CORE-03-02` contract and `CORE-03-03` implementation. **Base:** `c26a95999a88cb1e0869a1257cd486e00505d165`. **ADR:** [ADR-0105](../adr/0105-core-03-limited-capability-admission.md). **Contract:** [core-03-task-graph-v0](../contracts/core-03-task-graph-v0.md).

## OBJECTIVE

Record that `CORE-03-06` (“afinidade”) is satisfied by the approved contract and `CORE-03-03`, using JOB-06 as the objective oracle. No OS thread pinning, GPU/audio affinity or new lifecycle model is authorized.

## CONTEXT

The owner instructed continuation after the satisfaction closeouts of `CORE-03-04` and `CORE-03-05`. The frozen contract defines only `JobAffinity::AnyWorker` and `JobAffinity::MainThread`; JOB-06 proves MainThread execution on the owner, worker rejection of `wait` with `DeadlockRisk`, non-owner `wait` with `WrongThread`, and wrong-thread pump as a no-op. CORE-02 remains `NOT_QUALIFIED`; the formal dependency remains recorded.

## SCOPE

- Documentary satisfaction decision, evidence mapping and manifest advance for `CORE-03-06` only.
- New WO/evidence files and Decisions Ledger entry.
- No code, test, CMake, workflow, dependency, ABI or release change.

## OUT OF SCOPE

OS affinity masks, CPU pinning, NUMA policy, performance/efficiency cores, GPU submission affinity, audio thread affinity, cross-process affinity, priority inheritance, performance thresholds, allocator selection, CORE-02 completion and full Q4.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0105, contract `core-03-task-graph-v0`, CORE-03-03 evidence/PR #508, JOB-06/JOB-01/JOB-09 tests, exact-head CI 44959327194, manifest/registry.

## REQUIREMENTS

- GOV-001..005 and the 2026-11-21 continuation instruction; no new technical scope.
- Evidence must cite real test names and CI results.
- Manifest/validator must reflect `CORE-03-06` completed and `CORE-03-07`..`-10` blocked.
- CORE-02 stays `NOT_QUALIFIED`; no OS-affinity, allocator, ABI or release claim.

## ARCHITECTURE RULES

Affinity remains a logical execution-lane property: AnyWorker or owner-only MainThread. CORE-03 does not own OS thread pinning, GPU submission or real-time audio callbacks; those remain with CORE-01/GFX-03/AUD-01.

## CONSTRAINTS

`INTERNAL_ONLY`; risk `ELEVATED` inherited. No secrets, paid services, dependency changes or engine code. No claim of hard real-time affinity.

## ACCEPTANCE CRITERIA

- JOB-06 evidence covers owner-only MainThread execution, non-owner wait, worker wait and pump ownership.
- `CORE-03-06` becomes `COMPLETED` with this closeout PR; `CORE-03-07`..`-10` remain `PLANNED_BLOCKED`.
- Manifest `CORE03_06_COMPLETED_REST_BLOCKED`: **716 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 26 `COMPLETED`, 6 approved gates**.
- Docs Validation and pt-BR audit `APPROVED`; no HIGH/CRITICAL; registry byte-identical.

## TESTS

No new native test. Evidence traces JOB-06 affinity/deadlock/wrong-thread behavior, JOB-01 basic lifecycle and JOB-09 cross-platform stress, plus the existing native matrix.

## DELIVERABLES

WO, evidence, Decisions Ledger entry, checkpoint, manifest/validator/tests updates, Docs Validation and pt-BR audit. No code PR.

## REVIEW FORMAT

pt-BR: base/head, files, evidence fidelity, manifest effect, blocked packets, security/rollback and proposed checkpoint delta. Verdict only `APPROVED`, `CORRECTION REQUIRED` or `BLOCKED`.

## STOP CONDITION

Stale context, unsupported affinity claim, missing JOB evidence, manifest/registry drift, code/dependency change, release/ABI overclaim, HIGH/CRITICAL. Stop and report.

## CONTEXT LOCK

Base `c26a95999a88cb1e0869a1257cd486e00505d165`; contract blob `36b03944504b6b8e74907f773ead6901ce8705b0`; CORE-03-03 merge `3a697f6869f7081d9a05089d84ab6021c6e6a550`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-CORE-03-06.md` with JOB-06 traceability, CI IDs and manifest delta. No native PASS is newly claimed by this documentary packet.
