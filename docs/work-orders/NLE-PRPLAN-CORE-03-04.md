# NLE-PRPLAN-CORE-03-04 — Priorities slice satisfaction (INTERNAL_ONLY)

**STATUS: SATISFACTION CLOSEOUT — documentary only; no new code.** **Gate:** owner decision recorded after CORE-03-03. **Formal packet:** `NLE-PRPLAN-CORE-03-04`. **Predecessors:** `CORE-03-02` contract and `CORE-03-03` implementation. **Base:** `386fa7faba3912d697dbdd404a0b2619df8779c0`. **ADR:** [ADR-0105](../adr/0105-core-03-limited-capability-admission.md). **Contract:** [core-03-task-graph-v0](../contracts/core-03-task-graph-v0.md).

## OBJECTIVE

Record that `CORE-03-04` (“prioridades”) is satisfied by the already approved contract and the `CORE-03-03` implementation, with objective JOB-03/JOB-04 evidence. No additional scheduler code is authorized by this packet.

## CONTEXT

The owner declared the priorities slice satisfied on 2026-11-21 (“satisfeito continue”) after reviewing the CORE-03-03 checkpoint. The frozen contract assigns priority behavior and invalid-priority handling to `CORE-03-03`; JOB-04 proved FrameCritical > High > Normal > Background dispatch with TaskId tie-break, and JOB-03 proved invalid priority rejection with a typed error. The formal dependency `CORE-02` and D2 capability admission remain recorded; CORE-02 is not declared complete.

## SCOPE

- Documentary satisfaction decision, evidence mapping and manifest advance for `CORE-03-04` only.
- New WO/evidence files and Decisions Ledger entry.
- No code, test, CMake, workflow, dependency, ABI or release change.

## OUT OF SCOPE

Priority aging, fairness weights, deadline scheduling, starvation metrics, priority inheritance, performance thresholds, allocator selection, CORE-02 completion, full Q4 and any packet after `CORE-03-04`.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0105, contract `core-03-task-graph-v0`, CORE-03-03 evidence and PR #508, JOB-03/JOB-04 tests, exact-head CI run 44959327194, manifest/registry.

## REQUIREMENTS

- GOV-001..005 and the owner decision of 2026-11-21; no new technical scope.
- Evidence must cite real test names and CI results, not infer behavior.
- Manifest and validator must reflect `CORE-03-04` completed and `CORE-03-05`..`-10` blocked.
- CORE-02 stays `NOT_QUALIFIED`; no allocator, technology, public ABI or release claim.

## ARCHITECTURE RULES

The satisfaction decision inherits the frozen CORE-03-03 architecture and boundaries. No new CORE-01/02/04/06/GFX-03/AUD-01 dependency or cycle is introduced. Priority remains a dispatch preference, not a hard real-time guarantee.

## CONSTRAINTS

Status/release class `INTERNAL_ONLY`; risk `ELEVATED` inherited from implementation. No secrets, paid services, dependency changes or engine code. No self-promotion beyond the owner’s explicit satisfaction decision.

## ACCEPTANCE CRITERIA

- JOB-04 and JOB-03 evidence is sufficient for the stated priorities scope.
- `CORE-03-04` becomes `COMPLETED` with this closeout PR; `CORE-03-05`..`-10` remain `PLANNED_BLOCKED`.
- Manifest `CORE03_04_COMPLETED_REST_BLOCKED`: **718 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 24 `COMPLETED`, 6 approved gates**.
- Docs Validation and pt-BR audit `APPROVED`; no HIGH/CRITICAL; registry byte-identical.

## TESTS

No new native test is required. Evidence traces JOB-04 priority/TaskId ordering and background-worker reservation, JOB-03 invalid-priority typed rejection, and the existing cross-platform CI suite.

## DELIVERABLES

WO, evidence, Decisions Ledger entry, checkpoint, manifest/validator/tests updates, Docs Validation and pt-BR audit. No code PR.

## REVIEW FORMAT

pt-BR: base/head, files, evidence fidelity, manifest effect, blocked packets, security/rollback and proposed checkpoint delta. Verdict only `APPROVED`, `CORRECTION REQUIRED` or `BLOCKED`.

## STOP CONDITION

Stale context, unsupported priority claim, missing JOB evidence, manifest/registry drift, code/dependency change, release/ABI overclaim, HIGH/CRITICAL. Stop and report.

## CONTEXT LOCK

Base `386fa7faba3912d697dbdd404a0b2619df8779c0`; contract blob `36b03944504b6b8e74907f773ead6901ce8705b0`; CORE-03-03 merge `3a697f6869f7081d9a05089d84ab6021c6e6a550`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-CORE-03-04.md` with owner decision, JOB-03/JOB-04 traceability, CI IDs and manifest delta. No native PASS is newly claimed by this documentary packet.
