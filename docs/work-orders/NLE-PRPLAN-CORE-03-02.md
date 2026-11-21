# NLE-PRPLAN-CORE-03-02 — Task graph & executor contract (INTERNAL_ONLY)

**STATUS: CONTRACT PACKET — documentary only; implementation remains BLOCKED until CORE-03-03 G6 and owner authorization.** **Gate:** G6 contract + D2 capability admission. **Formal packet:** `NLE-PRPLAN-CORE-03-02`. **Predecessor:** `CORE-03-01` governance. **Issue:** #20. **Base:** `dcb2cbd7739d44d09f432621d2dbd0acdef14cb1`. **ADR:** [ADR-0105](../adr/0105-core-03-limited-capability-admission.md). **Contract:** [core-03-task-graph-v0](../contracts/core-03-task-graph-v0.md).

## OBJECTIVE

Define the first internal CORE-03 task-graph/executor contract with typed errors, priorities, dependencies, cancellation, fences, affinity, bounded queue, deterministic commit order and report-only stats. No implementation.

## CONTEXT

CORE-03-01 governance is approved only as planning. Owner ratified A+B+C+D2 (NLE-D022): ADR-0005 planning direction, risk/release proposals, benchmark-only candidate program and limited capability admission from completed CORE-02-03..09. CORE-02 remains NOT_QUALIFIED. This packet prepares only the contract; no code or technology selection.

## SCOPE

- Contract `core-03-task-graph-v0`: exact logical API, semantics, error model, lifecycle, JOB-01..JOB-10 and future allowlist.
- Evidence of contract review and D2 admission boundary.
- No implementation, dependency, workflow target or code test.

## OUT OF SCOPE

Scheduler code, Taskflow/enkiTS/oneTBB/SFAS integration, third-party types, public ABI, release, CORE-02 module completion, thresholds, CORE-04, manifest/registry beyond the `-02` approval.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0005/0086/0105, CORE-03 architecture/plan, Q1/Q2/Q3/Q4/Q7 and A/B/C/D2 ratification, CORE-02-03..09 evidence, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0105 D2; ADR-0086 capability rule; no technology selection.

## ARCHITECTURE RULES

Internal namespace/header; no third-party types; CORE-01 thread/lifecycle, CORE-02 memory, CORE-04 time, CORE-06 diagnostics, GFX-03 GPU and AUD-01 real-time boundaries preserved; deterministic commit order; bounded queue; no worker fence wait.

## CONSTRAINTS

Risk LOW for this documentary contract; future implementation ELEVATED; release INTERNAL_ONLY; no code/dependency/secret/paid service; CORE-02 NOT_QUALIFIED; G3 NOT_CLEARED; NLE-D009 OPEN; 80/80 WOs BLOCKED.

## ACCEPTANCE CRITERIA

- Exact contract/API/errors/lifecycle/test matrix/allowlist.
- D2 capability admission recorded; no technology selected or code authorized.
- Manifest `-02` approved contract only; `-03`..`-10` remain blocked.
- Docs Validation + pt-BR audit; no HIGH/CRITICAL; registry byte-identical.

## TESTS

Docs validators and selector denial; contract review traceability. No native code test is authorized by this packet.

## DELIVERABLES

Contract, G6 activation evidence, activation JSON, manifest/validator/tests/checkpoint. PR, Docs Validation, pt-BR audit, proposed checkpoint only.

## REVIEW FORMAT

pt-BR: base/head, contract fidelity to ADR-0105/0005, admission, no code/technology, blocked packets. APPROVED/CORRECTION REQUIRED/BLOCKED.

## STOP CONDITION

STALE, missing D2 ratification, technology selected by inference, API/code implementation, manifest/registry drift, HIGH/CRITICAL, release/ABI claim. No code before CORE-03-03 G6.

## CONTEXT LOCK

Base `dcb2cbd…`; D2 admission pins CORE-02-03..09; contract review required before `-03`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-CORE-03-02-G6-ACTIVATION.md` with contract review, admission, manifest effect and no-code statement.
