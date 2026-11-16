---
name: stormline-release-lifecycle
description: "Use for future approved versioned build/export, installer, signed release feeds, updates, rollback and support."
---
# RELEASE LIFECYCLE | Stormline Skill

**Category:** qa. **Status:** Versioned instructions only; not engine implementation, an approved ADR, a paid action or release authorization. Trigger only for the task in the description.

## Source and authority
1. Read [AGENTS.md](../../../AGENTS.md) and the [P00 approval gates](../../../docs/engineering/p00-technical-approval-gates.md) before changes. Inspect current main/branch, checkpoint, Ledger/approved ADRs, Scope, DoD, Architecture, Requirements and the smallest relevant module specification.
2. Verify one exact Work Order, context fingerprints and formal dependencies. `research_status=RESEARCH_DOCUMENTED_ADR_PROPOSED` never authorizes implementation. Never widen the approved module DAG or change any of 80 blocked Work Orders based on this skill.

## Workflow
1. Follow PLAT-05, QA-05, BIZ-01/03; map immutable digest, provenance, license grant, target matrix, signing/notarization and channel owner.
2. Require TUF-grade metadata verification, delta full-hash check, OS package manager ownership, creator data protection and incident pause.
3. Verify real packaging/updates on platforms and full v1.0 DoD before any public release.
4. Scope output to the smallest NECESSARY increment and record alternatives and unresolved owner decisions; when executable work is genuinely authorized, inspect Git first, test, capture evidence, PR, pt-BR audit, checkpoint and readback.

## Acceptance and evidence
Record module/WO ID, current BASE/HEAD, filenames, owner and interface authority, error/rollback states, precise future vs real tests, licenses/source provenance, risks and objective acceptance. For visual design, produce references and measured accessible visual proof after an authorized artifact request. A completed SKILL.md is not a completed engine feature.

## Stop condition
No public MVP, license grant, paid certificate, telemetry upload or binary release from a successful docs CI.
Also BLOCK on STALE source, no owner-approved API/ADR/Scope/DoD/risk/release gates, known HIGH/CRITICAL, failed CI, unapproved cost/secrets or attempted public MVP. Never force push or bypass branch protections.
