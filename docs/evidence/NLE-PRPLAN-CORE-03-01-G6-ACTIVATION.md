# NLE-PRPLAN-CORE-03-01 — G6 governance activation

**Status:** `G6 GOVERNANCE PROPOSAL / NO IMPLEMENTATION AUTHORIZED / CORE-02 NOT_QUALIFIED`. **Base main:** `a24d65092da5401b5534a7ba13d3391b991dd94a`. **Formal packet:** `NLE-PRPLAN-CORE-03-01`. **ADR:** [ADR-0103](../adr/0103-core-03-governance-gate.md). **Contract:** [core-03-governance-v0](../contracts/core-03-governance-v0.md). **WO:** [NLE-PRPLAN-CORE-03-01](../work-orders/NLE-PRPLAN-CORE-03-01.md).

## Owner authorization

The owner authorized option 1 (prepare only the CORE-03 governance gate) and option 2 (prepare the CORE-02 qualification dossier) on 2026-11-19. This gate approves only the governance boundary; it does not authorize CORE-03 code, technology selection, API, release or CORE-02 module completion.

## Bounded governance outcome

- `CORE-03-01` becomes `APPROVED_GOVERNANCE`.
- `CORE-03-02`..`-10` remain `PLANNED_BLOCKED`.
- No `EXECUTOR_READY`; selector denies every CORE-03 ID.
- CORE-02 remains `NOT_QUALIFIED`; ADR-0005 remains `PROPOSED`; no scheduler technology selected.

## Required before any CORE-03 code packet

1. Owner ratification of ADR-0005/architecture scope and release class.
2. `-02` exact contract/API/error model/file allowlist audited.
3. Technology decision or benchmark plan with licenses/digests/advisories.
4. CORE-02 formal dependency resolution or owner-ratified capability admission.
5. Risk/proof plan (TSan, races, deadlock, cancellation, overload, deterministic commit).
6. Explicit separate authorization for implementation.

## Gate state after merge

- Manifest root `CORE03_01_APPROVED_GOVERNANCE_ONLY`: **721 `PLANNED_BLOCKED`, 22 `COMPLETED`, 5 approved gates (2 CORE-01 + 2 CORE-02 + 1 CORE-03), 0 `EXECUTOR_READY`**.
- Selector denies all; registry byte-identical; 80/80 module WOs BLOCKED.

## Proof obligations

Docs Validation, selector denial tests, registry byte-identity, pt-BR audit, no HIGH/CRITICAL.

No code/native PASS is claimed by this governance gate.
