# ADR-0103 — CORE-03 governance gate (planning only)

**Status:** `OWNER_DIRECTION_BOUNDED_GOVERNANCE / PLANNING_ONLY / ADR-0005 REMAINS PROPOSED / NO IMPLEMENTATION AUTHORIZED`. **Does not select Taskflow/enkiTS/oneTBB/SFAS, approve ADR-0005, change CORE-02 status, G3, license or release.**

**Date:** 2026-11-19 | **WO:** `NLE-PRPLAN-CORE-03-01` | **Parent:** `NLE-PRPLAN-CORE-03-01` | **Issue:** #20.

## Context and authority

CORE-02 closed its internal sequence but remains **NOT module-qualified**. The owner authorized preparing the CORE-03 governance gate without implementing CORE-03, and separately authorized preparing the CORE-02 qualification decision dossier. This ADR establishes only the governance boundary for CORE-03.

CORE-03 research/architecture already propose task graphs, priorities, dependencies, affinity, cancellation, data isolation, CORE-01 thread ownership, CORE-02 memory domains and CORE-04 time boundaries. ADR-0005 proposes candidates and proof obligations but remains `PROPOSED`.

## Bounded governance decision

- Approve `NLE-PRPLAN-CORE-03-01` as a **planning governance packet only**.
- Preserve every CORE-03 implementation/qualification/closeout packet (`-02`..`-10`) as `PLANNED_BLOCKED`.
- Require, before any CORE-03 code packet activation:
  1. explicit owner ratification of ADR-0005/architecture scope and release class;
  2. exact contract/API/error model/file allowlist (`-02`) and its audit;
  3. a technology decision or a benchmark plan for Taskflow/enkiTS/oneTBB/SFAS, with licenses/digests/advisories;
  4. formal CORE-02 dependency resolution or an owner-ratified capability admission that does not claim CORE-02 module completion;
  5. risk classification and TSan/race/deadlock/cancellation/overload proof obligations.
- Risk classification: `LOW` for this documentary governance artifact; future CORE-03 implementation is proposed `ELEVATED` because concurrency correctness is safety-critical. This is a proposal, not an activated class.
- Release class for future internal slices: proposed `INTERNAL_ONLY`, not approved for release.

## Explicitly not decided

- No scheduler technology, dependency, license, version or vendoring.
- No public ABI, thread-count default, affinity policy, frame budget or p95/p99 threshold.
- No CORE-02 module completion, G3 clearance, release, deploy or CORE-04 activation.
- No implementation branch, code, test executable or workflow change.

## Consequence

- Manifest root becomes `CORE03_01_APPROVED_GOVERNANCE_ONLY`; `-01` is `APPROVED_GOVERNANCE`; every CORE-03 code packet remains `PLANNED_BLOCKED`.
- No `EXECUTOR_READY` packet exists; selector denies all IDs.
- CORE-02 remains `NOT_QUALIFIED`; CORE-03 implementation requires a later owner authorization after the prerequisites above.

## Rollback

Unmerged: close the branch. After merge: normal revert PR, never force push. Documentary state only; no code, registry, G2 or license change.
