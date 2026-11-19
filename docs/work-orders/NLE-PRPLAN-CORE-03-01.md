# NLE-PRPLAN-CORE-03-01 — Governance gate (planning only)

**STATUS: APPROVED_GOVERNANCE ONLY AFTER THE GATE PR PASSES DOCS VALIDATION, PT-BR AUDIT AND SQUASH MERGE. NO CORE-03 CODE IS AUTHORIZED.** **Gate:** G6 governance + capability boundary. **Formal packet:** `NLE-PRPLAN-CORE-03-01`. **Predecessor:** none (governance). **Issue:** #20. **Base:** `a24d65092da5401b5534a7ba13d3391b991dd94a`. **ADR:** [ADR-0103](../adr/0103-core-03-governance-gate.md). **Contract:** [core-03-governance-v0](../contracts/core-03-governance-v0.md).

## OBJECTIVE

Approve only the CORE-03 governance boundary: scope, ownership, dependency, risk/release proposals and proof obligations, leaving every implementation packet blocked.

## CONTEXT

CORE-02 internal sequence is closed but CORE-02 is NOT module-qualified. ADR-0005 remains PROPOSED and no scheduler technology is selected. The owner authorized preparing this governance gate without authorizing CORE-03 code.

## SCOPE

- Governance decision/contract/WO/evidence/activation for `-01` only.
- Record LOW planning risk, proposed ELEVATED implementation risk and proposed `INTERNAL_ONLY` future slices.
- Require ADR-0005 ratification, `-02` contract, technology/license decision, CORE-02 dependency resolution, proof plan and explicit owner authorization before code.
- Manifest `-01` APPROVED_GOVERNANCE; `-02`..`-10` remain PLANNED_BLOCKED.

## OUT OF SCOPE

Scheduler implementation, Taskflow/enkiTS/oneTBB/SFAS selection, dependencies, code/tests, public ABI, CORE-02 completion, G3/license change, CORE-04, release/deploy.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, Decisions Ledger, Scope/DoD, ADR-0005, CORE-03 architecture/plan, CORE-02 closeout, queue registry, manifest/activation, issues #13/#20.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0005 proposed; ADR-0086 capability rule; ADR-0103 governance boundary.

## ARCHITECTURE RULES

Preserve CORE-01 thread/lifecycle, CORE-02 memory, CORE-04 time, CORE-06 diagnostics, GFX-03 GPU and AUD-01 real-time ownership; no new module edges or third-party types in the future public contract.

## CONSTRAINTS

Documentary only; no code/dependency/secrets/paid service; no technology selection by inference; CORE-02 NOT_QUALIFIED; G3 global NOT_CLEARED; NLE-D009 OPEN; 80/80 WOs BLOCKED; engine=false.

## ACCEPTANCE CRITERIA

- Exact allowlist; `-01` approved governance; `-02`..`-10` blocked; zero EXECUTOR_READY.
- ADR/contract/WO/evidence/activation consistent; no technology/release/API claim.
- Docs Validation + audit; no HIGH/CRITICAL; registry byte-identical.

## TESTS

Docs validators, selector denial for every CORE-03 ID, counts (5 approved / 22 completed / 721 blocked), registry hash.

## DELIVERABLES

ADR-0103, contract, WO, G6 activation evidence, activation JSON, manifest/validator/tests/checkpoint. PR, Docs Validation, pt-BR audit, proposed checkpoint only.

## REVIEW FORMAT

pt-BR: base/head, counts, blocked code packets, no technology/release overclaim. APPROVED/CORRECTION REQUIRED/BLOCKED.

## STOP CONDITION

STALE, ready CORE-03 code packet, missing owner authorization, technology selection, CORE-02 completion claim, HIGH/CRITICAL, registry change. No merge without audit.

## CONTEXT LOCK

Gate base `a24d650…`; activation pins ADR/contract/source blobs.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-CORE-03-01-G6-ACTIVATION.md` with gate SHA/PR, counts, selector denial and explicit `NO IMPLEMENTATION AUTHORIZED` statement.
