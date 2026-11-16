---
name: stormline-work-orders
description: "Use to specify or hand off one bounded Stormline Work Order; never use a draft as permission to run code."
---
# WORK ORDERS | Stormline Skill

**Category:** governance. **Status:** Versioned instructions only; not engine implementation, an approved ADR, a paid action or release authorization. Trigger only for the task in the description.

## Source and authority
1. Read [AGENTS.md](../../../AGENTS.md) and the [P00 approval gates](../../../docs/engineering/p00-technical-approval-gates.md) before changes. Inspect current main/branch, checkpoint, Ledger/approved ADRs, Scope, DoD, Architecture, Requirements and the smallest relevant module specification.
2. Verify one exact Work Order, context fingerprints and formal dependencies. `research_status=RESEARCH_DOCUMENTED_ADR_PROPOSED` never authorizes implementation. Never widen the approved module DAG or change any of 80 blocked Work Orders based on this skill.

## Workflow
1. Define OBJECTIVE, CONTEXT, SCOPE, OUT OF SCOPE, FILES, REQUIREMENTS, ARCHITECTURE RULES, CONSTRAINTS, ACCEPTANCE, TESTS, DELIVERABLES, REVIEW FORMAT and STOP CONDITION.
2. Tie one stable WO ID to branch, issue, PR, evidence and proposed checkpoint; preserve the exact approved catalog DAG.
3. Provide a minimal NECESSARY slice, explicit ownership, ready gates, rollback and no unapproved scope growth.
4. Scope output to the smallest NECESSARY increment and record alternatives and unresolved owner decisions; when executable work is genuinely authorized, inspect Git first, test, capture evidence, PR, pt-BR audit, checkpoint and readback.

## Acceptance and evidence
Record module/WO ID, current BASE/HEAD, filenames, owner and interface authority, error/rollback states, precise future vs real tests, licenses/source provenance, risks and objective acceptance. For visual design, produce references and measured accessible visual proof after an authorized artifact request. A completed SKILL.md is not a completed engine feature.

## Stop condition
Do not create executable instructions unless ADR, DoD, release class, risks, sources and all formal dependency approvals are actually ratified.
Also BLOCK on STALE source, no owner-approved API/ADR/Scope/DoD/risk/release gates, known HIGH/CRITICAL, failed CI, unapproved cost/secrets or attempted public MVP. Never force push or bypass branch protections.
