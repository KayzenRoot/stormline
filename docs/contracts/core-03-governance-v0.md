# CORE-03 Governance Contract v0 (NLE-PRPLAN-CORE-03-01)

**Status:** `GOVERNANCE CONTRACT / PLANNING ONLY / NO IMPLEMENTATION`. **Base:** `a24d65092da5401b5534a7ba13d3391b991dd94a`. **ADR:** [ADR-0103](../adr/0103-core-03-governance-gate.md). **WO:** [NLE-PRPLAN-CORE-03-01](../work-orders/NLE-PRPLAN-CORE-03-01.md).

## Objective

Approve only the CORE-03 governance boundary: scope, ownership boundaries, risk/release proposals, dependency and proof obligations. Do not approve ADR-0005, a scheduler technology, public API, code or release.

## Scope boundary

- Task submission, scheduling, priorities, dependency DAG, affinity, cancellation, data isolation and bounded diagnostics are future CORE-03 concerns.
- CORE-01 owns OS threads/lifecycle; CORE-02 owns memory domains/arenas; CORE-04 owns time/tick; CORE-06 owns instrumentation; GFX-03 owns GPU submission; AUD-01 owns real-time audio callbacks; NET-02 owns authoritative server transport.
- No editor/graphics/network imports into core interfaces; headless and Windows/Linux/macOS portability remain constraints.
- Determinism means defined observable commit order where required, not fixed thread scheduling.

## Gate checklist before any CORE-03 code packet

1. ADR-0005/architecture explicitly ratified by the owner for the implementation scope.
2. `CORE-03-02` exact contract/API/error model/file allowlist approved and audited.
3. Scheduler technology decision or benchmark plan approved, with licenses, versions/digests and vulnerability review; no third-party type in the public contract.
4. CORE-02 dependency resolved formally or by an owner-ratified capability admission that does not claim CORE-02 module completion.
5. Risk class, release class, proof obligations, hardware matrix and thresholds explicitly approved.
6. TSan/race/deadlock/cancellation/overload and deterministic-commit test plan approved.
7. No HIGH/CRITICAL known; no release/deploy claim.

## Manifest effect of this governance packet

- `CORE-03-01` becomes `APPROVED_GOVERNANCE` after gate Docs Validation, pt-BR audit and merge.
- `CORE-03-02`..`-10` stay `PLANNED_BLOCKED`.
- No `EXECUTOR_READY`; selector denies all.
- CORE-02 remains `NOT_QUALIFIED`; G3/license unchanged.

## Exact allowlist for packet -01

1. `docs/adr/0103-core-03-governance-gate.md`
2. `docs/contracts/core-03-governance-v0.md`
3. `docs/work-orders/NLE-PRPLAN-CORE-03-01.md`
4. `docs/evidence/NLE-PRPLAN-CORE-03-01-G6-ACTIVATION.md`
5. `docs/queue/packet-activation-core-03-01.json`
6. `docs/pr-plans/manifest.json`
7. `docs/11-checkpoint.md`
8. `scripts/validate_pr_plans.py`
9. `scripts/test_validate_pr_plans.py`

No engine code, registry, workflow, dependency, G2, license or release change.

## Stop / rollback

Stop on stale source, missing owner authorization, ready CORE-03 code packet, technology selection by inference, CORE-02 completion claim, HIGH/CRITICAL, registry change or release overclaim. Unmerged: close branch; after merge: normal revert PR, never force push.
