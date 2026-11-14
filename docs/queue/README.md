# Stormline — Zcode Work Order Queue (80 modules)

**Status:** PROPOSED. Full 80-module **draft packet inventory**, not 80 executable authorizations.  
**Work Order:** NLE-P00-WO-002-QUEUE-001 | **Baseline:** `3db4507ffa99896a799c0da7fe0be738fa4a4f4c`.

## Why this exists
The owner requests every module and corresponding implementation issue/Work Order organized **before** engine coding so Zcode concentrates on implementation once technical planning is approved. Do not confuse **prepared documentation** with a technically locked/codable task.

## Registry
- [Machine-readable implementation registry](implementation-registry.json), topologically ordered from the [approved 80-module catalog](../product/module-catalog.md).
- [Individual Work Order drafts](work-orders/) (one stable `NLE-EXEC-WO-<MODULE_ID>-001` per module), all **BLOCKED** until promoted.
- [Zcode handoff protocol](../engineering/zcode-handoff.md); [Work Order template](../engineering/wo-template.md).
- [Planning research CORE-01, CORE-02 and CORE-03](../research/) already documented and audited, **not equivalent** to implementation approval.

## State machine
`CATALOG_APPROVED -> DRAFT_BLOCKED -> TECH_RESEARCH_APPROVED -> IMPLEMENTATION_CONTRACT_PROPOSED -> OWNER/OBJECTIVE_AUDIT -> EXECUTOR_READY -> IN_PROGRESS -> TESTED -> AUDITED -> APPROVED -> CHECKPOINT_RECONCILED -> NEXT`.

Only one implementation Work Order can be **IN_PROGRESS** per dependency chain. Opening future planning issues does not start work, create branches or authorize code. **No code authoring while P00 architecture is incomplete.** Existing P00 source hierarchy and no-MVP policy remain in force.

### Gates before Zcode is permitted to code
1. Exact module objective, boundaries, released-v1 class and complete approved Requirements/Scope/DoD.
2. Reviewed technology ADR with versions, license/security provenance, OS targets and compatible architecture.
3. API and data contracts, ownership, threading, error codes, migrations and Editor/CLI/MCP coverage where applicable.
4. Concrete affected file inventory based on actual repository tree, with approved build/test commands and benchmarking target hardware.
5. Dependencies approved and merged, no HIGH/CRITICAL; fresh base SHA and source fingerprints in Context Lock.
6. Issue-specific Work Order updated from BLOCKED to EXECUTOR_READY after **objective audit**.
7. Zcode reads only that Work Order plus precise relevant source; implements, tests, commits, pushes, opens PR and supplies Evidence Bundle. No paid tools, no reviewer outside owner.

## What Zcode should NOT do
- Choose the product architecture, tech stack, public API or 1.0 scope on its own.
- Execute all open issues in parallel, branch from stale main or skip dependency gates.
- Claim 3D quality, performance or cross-OS support without actual tests on specified hardware.
- Install paid services, CodeRabbit, force-push, bypass rulesets, publish unfinished engine.
- Treat the draft statuses or GitHub issue count as proof anything is implemented.

## Preparation and checks
`python3 scripts/validate_wo_registry.py` verifies module count, ID uniqueness, dependency order and matching docs.  
`python3 scripts/select_wo.py CORE-01` returns a draft's status and gate blockers; it **will not** authorize execution.

## Roadmap order
Registry is a **topological** suggestion, not a license to perform each module sequentially without its own approved planning. Prefer NECESSARY WOs and small, testable increments. Some advanced systems will require multiple actual implementation WOs and must not be packed into one giant one-shot.

## Issue tracking
Once the registry and docs CI pass, create one planning-only issue per `NLE-EXEC-WO-<MODULE_ID>-001`, with unique IDs, explicit blocked state and links to drafts. Record GitHub issue mappings in a follow-up audited registry update if the available issue API supports reliable readback.
