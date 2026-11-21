# NLE-PRPLAN-CORE-03-05 — Dependency slice satisfaction (INTERNAL_ONLY)

**STATUS: SATISFACTION CLOSEOUT — documentary only; no new code.** **Gate:** continuation decision after CORE-03-04. **Formal packet:** `NLE-PRPLAN-CORE-03-05`. **Predecessors:** `CORE-03-02` contract and `CORE-03-03` implementation. **Base:** `2ad1b55a3478b0468702ea0daad9a845760ec249`. **ADR:** [ADR-0105](../adr/0105-core-03-limited-capability-admission.md). **Contract:** [core-03-task-graph-v0](../contracts/core-03-task-graph-v0.md).

## OBJECTIVE

Record that `CORE-03-05` (“dependências”) is satisfied by the approved contract and the `CORE-03-03` implementation, using JOB-02, JOB-03 and JOB-09 as objective evidence. No additional dependency engine, dynamic graph or resource policy is authorized.

## CONTEXT

The owner declared `CORE-03-04` satisfied and instructed continuation on 2026-11-21. The frozen contract already assigns DAG validation, cycle detection, dependency-failure propagation, deterministic commit order and bounded graph storage to `CORE-03-03`. JOB-02, JOB-03 and JOB-09 prove those behaviors. CORE-02 remains `NOT_QUALIFIED`; the formal dependency and D2 admission remain recorded.

## SCOPE

- Documentary satisfaction decision, evidence mapping and manifest advance for `CORE-03-05` only.
- New WO/evidence files and Decisions Ledger entry.
- No code, test, CMake, workflow, dependency, ABI or release change.

## OUT OF SCOPE

Dynamic graph mutation after finalize, subgraph replacement, cross-graph dependencies, resource read/write conflict analysis, dependency-aware priority inheritance, performance thresholds, allocator selection, CORE-02 completion, full Q4 and any packet after `CORE-03-05`.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0105, contract `core-03-task-graph-v0`, CORE-03-03 evidence/PR #508, JOB-02/JOB-03/JOB-09 tests, exact-head CI 44959327194, manifest/registry.

## REQUIREMENTS

- GOV-001..005 and the 2026-11-21 continuation instruction; no new technical scope.
- Evidence must cite real test names and CI results.
- Manifest/validator must reflect `CORE-03-05` completed and `CORE-03-06`..`-10` blocked.
- CORE-02 stays `NOT_QUALIFIED`; no allocator, technology, ABI or release claim.

## ARCHITECTURE RULES

Dependencies remain inside one bounded `TaskGraph`; capacity is fixed at 256 tasks; no dynamic growth after `finalize()`. CORE-03 does not gain ownership of CORE-01 threads, CORE-02 memory domains, CORE-04 time or CORE-06 instrumentation.

## CONSTRAINTS

`INTERNAL_ONLY`; risk `ELEVATED` inherited. No secrets, paid services, dependency changes or engine code. No claim of dependency-aware GPU/audio/resource scheduling.

## ACCEPTANCE CRITERIA

- JOB-02/JOB-03/JOB-09 evidence covers ordering, cycles, invalid edges, dependency failure and repeated determinism.
- `CORE-03-05` becomes `COMPLETED` with this closeout PR; `CORE-03-06`..`-10` remain `PLANNED_BLOCKED`.
- Manifest `CORE03_05_COMPLETED_REST_BLOCKED`: **717 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 25 `COMPLETED`, 6 approved gates**.
- Docs Validation and pt-BR audit `APPROVED`; no HIGH/CRITICAL; registry byte-identical.

## TESTS

No new native test. Evidence traces JOB-02 dependency/commit order, JOB-03 cycle/dangling/duplicate/self-edge typed errors, JOB-09 layered DAG determinism and concurrent jobs, plus existing cross-platform CI.

## DELIVERABLES

WO, evidence, Decisions Ledger entry, checkpoint, manifest/validator/tests updates, Docs Validation and pt-BR audit. No code PR.

## REVIEW FORMAT

pt-BR: base/head, files, evidence fidelity, manifest effect, blocked packets, security/rollback and proposed checkpoint delta. Verdict only `APPROVED`, `CORRECTION REQUIRED` or `BLOCKED`.

## STOP CONDITION

Stale context, unsupported dependency claim, missing JOB evidence, manifest/registry drift, code/dependency change, release/ABI overclaim, HIGH/CRITICAL. Stop and report.

## CONTEXT LOCK

Base `2ad1b55a3478b0468702ea0daad9a845760ec249`; contract blob `36b03944504b6b8e74907f773ead6901ce8705b0`; CORE-03-03 merge `3a697f6869f7081d9a05089d84ab6021c6e6a550`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-CORE-03-05.md` with JOB-02/JOB-03/JOB-09 traceability, CI IDs and manifest delta. No native PASS is newly claimed by this documentary packet.
