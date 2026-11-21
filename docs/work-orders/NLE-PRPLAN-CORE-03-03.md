# NLE-PRPLAN-CORE-03-03 — Task graph & executor scheduler (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate is merged, audited and the exact-head CI is green.** **Gate:** G6 implementation + D2 capability admission. **Formal packet:** `NLE-PRPLAN-CORE-03-03`. **Predecessors:** `CORE-03-02` contract, `CORE-02` limited capability admission. **Issue:** #20. **Base:** `38d73bd46fc66cc4f83294bcad44e7e310534013`. **ADR:** [ADR-0105](../adr/0105-core-03-limited-capability-admission.md). **Contract:** [core-03-task-graph-v0](../contracts/core-03-task-graph-v0.md).

## OBJECTIVE

Implement the first internal CORE-03 scheduler slice exactly as frozen by `core-03-task-graph-v0`: bounded `TaskGraph`, dependency validation, deterministic commit order and a fixed-worker `JobExecutor` with priorities, MainThread affinity, cancellation scopes, fences, typed errors, bounded queue and report-only statistics. No third-party scheduler, public ABI or release is authorized.

## CONTEXT

`CORE-03-02` was approved and merged in PR #505 (`aa97b23`), then recorded by PR #506 (`38d73bd`). ADR-0105 D2 admits only completed `CORE-02-03..09` capabilities; CORE-02 remains `NOT_QUALIFIED` and its formal dependency remains recorded. The owner explicitly authorized unblocking the continuation on 2026-11-21 through `STORM-CORE-01-IMPL-001` (issue #387). This WO activates only `CORE-03-03`.

## SCOPE

- Implement the exact logical API in `docs/contracts/core-03-task-graph-v0.md`: `TaskGraph`, `JobExecutor`, enums, handles, budget, stats and error model.
- Implement JOB-01..JOB-10 oracles in `tests/core/job_executor_tests.cpp`.
- Add additive CMake target/test wiring and CORE-03 workflow path filters; add a CORE-03 thread-sanitizer job only inside the existing native workflow.
- Record evidence in `docs/evidence/NLE-PRPLAN-CORE-03-03.md`.

## OUT OF SCOPE

Taskflow/enkiTS/oneTBB/SFAS integration, third-party scheduler types, public ABI, release, GPU/audio/network work, CORE-02 module completion, allocator selection, Q4 physical qualification, thresholds, performance ranking, CORE-04, changes to approved ADRs or the frozen contract, and any packet after `CORE-03-03`.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0005/0086/0103/0105, `core-03-task-graph-v0`, CORE-03 architecture/plan, NLE-PRPLAN-CORE-03-02 WO/evidence/gate, CORE-02-03..09 evidence, manifest/registry, existing CORE-01/CORE-02 code and CMake/test conventions.

## REQUIREMENTS

- GOV-001..005, CAP-009/010, NFR-001..005; ADR-0105 D2; ADR-0086 capability rule; contract semantics and exact allowlist.
- Fixed graph capacity 256; workers 1..32; no dynamic graph growth; bounded executor queue; typed errors; no exception across the API.
- Deterministic commit order; MainThread tasks never run on workers; worker `wait` rejected with `DeadlockRisk`; shutdown joins every thread and never detaches.
- No new dependency, no allocator override, no secret, no paid service, no public ABI or release claim.

## ARCHITECTURE RULES

Internal namespace `stormline::core::jobs`; CORE-01 owns OS threads/lifecycle, CORE-02 owns memory domains, CORE-04 owns time/tick, CORE-06 owns instrumentation, GFX-03 owns GPU submission and AUD-01 owns real-time audio. CORE-03 must not create a cycle into those owners. The executor uses only the C++20 standard library.

## CONSTRAINTS

Risk `ELEVATED`; release class `INTERNAL_ONLY`; no public ABI. CORE-02 `NOT_QUALIFIED`; G3 `NOT_CLEARED`; NLE-D009 `OPEN`; 80/80 module WOs remain `BLOCKED`. No technology selection is made by writing this scheduler.

## ACCEPTANCE CRITERIA

- Contract API implemented without signature drift; exact allowlisted files only.
- JOB-01..JOB-10 pass with valid/invalid fixtures, lifecycle, cancellation, affinity, backpressure, determinism and stress.
- Linux GCC, Linux ASan/UBSan, Linux TSan, Windows MSVC and macOS AppleClang exact-head CI pass.
- No data race, deadlock, detached thread, leak, queue overrun, reordered commit or wrong-thread MainThread execution observed.
- pt-BR audit `APPROVED`; manifest advances only to `CORE03_03_COMPLETED_REST_BLOCKED`; `CORE-03-04`..`-10` stay `PLANNED_BLOCKED`; registry byte-identical.

## TESTS

JOB-01 basic graph; JOB-02 dependency/commit order; JOB-03 cycle/invalid graph; JOB-04 priority/TaskId dispatch; JOB-05 cancellation; JOB-06 affinity/deadlock; JOB-07 backpressure; JOB-08 shutdown/lifetime; JOB-09 determinism/stress (TSan/ASan/UBSan); JOB-10 report-only benchmark. Also rerun the full existing CTest suite on every target.

## DELIVERABLES

Code PR with `task_graph.hpp/.cpp`, `job_executor.hpp/.cpp`, tests, additive CMake/workflow, evidence, exact-head CI and pt-BR audit. Checkpoint/readback PR only after merge. No release, ABI or technology claim.

## REVIEW FORMAT

pt-BR: base/head SHA, file diff, contract fidelity, allowlist, JOB-01..JOB-10 results, sanitizer/CI evidence, errors/corrections, security/architecture concerns, rollback, licensing, open risks and proposed checkpoint delta. Verdict only `APPROVED`, `CORRECTION REQUIRED` or `BLOCKED`.

## STOP CONDITION

Stale base/context, missing G6 activation, signature/contract drift, third-party type, code outside allowlist, dynamic graph growth, unbounded queue, worker fence wait, detached thread, memory leak, data race, deadlock, failed test, HIGH/CRITICAL, release/ABI/license overclaim. Stop and report; do not advance.

## CONTEXT LOCK

Base `38d73bd46fc66cc4f83294bcad44e7e310534013`; contract blob `36b03944504b6b8e74907f773ead6901ce8705b0`; ADR-0105 blob `a87906e17b5e393a9b3cc500840e14b42f7ac858`. Fresh context lock is mandatory before code.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-CORE-03-03-G6-ACTIVATION.md` for the gate; `docs/evidence/NLE-PRPLAN-CORE-03-03.md` for implementation. No native PASS is claimed by the gate itself.
