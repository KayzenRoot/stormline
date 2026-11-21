# NLE-PRPLAN-CORE-03-08 — Data isolation slice satisfaction (INTERNAL_ONLY)

**STATUS: SATISFACTION CLOSEOUT — documentary only; no new code.** **Gate:** continuation after CORE-03-07. **Formal packet:** `NLE-PRPLAN-CORE-03-08`. **Predecessors:** `CORE-03-02` contract and `CORE-03-03` implementation. **Base:** `049e9295c783b8cc68593b75d012eb7b1d1a41b7`. **ADR:** [ADR-0105](../adr/0105-core-03-limited-capability-admission.md). **Contract:** [core-03-task-graph-v0](../contracts/core-03-task-graph-v0.md).

## OBJECTIVE

Record the bounded v0 meaning of `CORE-03-08` (“isolamento de dados”) and close it as satisfied for that scope: executor-owned state is per-job and mutex-protected; task contexts are caller-owned and passed unchanged; externally visible commits are serialized by the commit lane. Resource read/write conflict declaration is explicitly **not** part of v0.

## CONTEXT

The owner instructed continuation after the satisfaction closeouts of `CORE-03-04`..`07`. The frozen v0 contract defines no resource read/write policy or shared-context enforcement; those are absent from `TaskGraph`/`JobExecutor`. Therefore this packet cannot claim resource conflict detection. It can and does claim executor-internal isolation and caller-owned context boundaries, with JOB-02/JOB-03/JOB-09 and TSan/ASan evidence. CORE-02 remains `NOT_QUALIFIED`.

## SCOPE

- Documentary satisfaction decision for `CORE-03-08` limited to executor-state and caller-owned-context isolation.
- Evidence mapping and manifest advance.
- New WO/evidence files and Decisions Ledger entry.
- No code, test, CMake, workflow, dependency, ABI or release change.

## OUT OF SCOPE

Resource read/write declarations, conflict detection, aliasing analysis, memory-domain isolation (CORE-02), shared-mutable-context safety, GPU/audio data isolation, transactional rollback, serialization formats, MCP context isolation, performance thresholds, allocator selection, CORE-02 completion and full Q4.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0105, contract `core-03-task-graph-v0`, CORE-03 architecture, CORE-03-03 evidence/PR #508, JOB-01/JOB-02/JOB-03/JOB-09 tests, exact-head CI 44959327194, manifest/registry.

## REQUIREMENTS

- GOV-001..005 and the 2026-11-21 continuation instruction; no new technical scope.
- Evidence must not imply resource conflict detection or memory-domain isolation.
- Manifest/validator must reflect `CORE-03-08` completed and `CORE-03-09`/`-10` blocked.
- CORE-02 stays `NOT_QUALIFIED`; no allocator, ABI or release claim.

## ARCHITECTURE RULES

CORE-03 owns scheduling and work lifetime, not task data ownership. Each `JobState` is private to one job and guarded by the executor mutex; each task receives its own caller-supplied context pointer unchanged. Commit callbacks are the only executor-provided cross-task visibility point and run in ascending order. CORE-02 owns memory domains; CORE-03 does not attempt cross-domain isolation.

## CONSTRAINTS

`INTERNAL_ONLY`; risk `ELEVATED` inherited. No secrets, paid services, dependency changes or engine code. No claim of safe arbitrary shared mutable contexts.

## ACCEPTANCE CRITERIA

- JOB-09 concurrent isolated counters, JOB-02 serialized commits and JOB-03 non-execution evidence support the bounded isolation claim.
- `CORE-03-08` becomes `COMPLETED` with this closeout PR for the explicit scope; `CORE-03-09`/`-10` remain `PLANNED_BLOCKED`.
- Manifest `CORE03_08_COMPLETED_REST_BLOCKED`: **714 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 28 `COMPLETED`, 6 approved gates**.
- Docs Validation and pt-BR audit `APPROVED`; no HIGH/CRITICAL; registry byte-identical.

## TESTS

No new native test. Evidence traces JOB-09 (10 concurrent jobs with separate atomic counters, each exactly 16), JOB-02 (ascending commit order), JOB-03 (invalid graphs execute nothing), JOB-01 (caller-owned shared counter), and TSan/ASan/CI.

## DELIVERABLES

WO, evidence, Decisions Ledger entry, checkpoint, manifest/validator/tests updates, Docs Validation and pt-BR audit. No code PR.

## REVIEW FORMAT

pt-BR: base/head, files, evidence fidelity, explicit scope exclusions, manifest effect, blocked packets, security/rollback and proposed checkpoint delta. Verdict only `APPROVED`, `CORRECTION REQUIRED` or `BLOCKED`.

## STOP CONDITION

Stale context, resource-conflict overclaim, memory-domain isolation overclaim, missing JOB evidence, manifest/registry drift, code/dependency change, release/ABI overclaim, HIGH/CRITICAL. Stop and report.

## CONTEXT LOCK

Base `049e9295c783b8cc68593b75d012eb7b1d1a41b7`; contract blob `36b03944504b6b8e74907f773ead6901ce8705b0`; CORE-03-03 merge `3a697f6869f7081d9a05089d84ab6021c6e6a550`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-CORE-03-08.md` with the bounded isolation claim, JOB traceability, CI IDs and manifest delta. No native PASS is newly claimed by this documentary packet.
