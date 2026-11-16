---
name: stormline-2d-hybrid
description: "Use for approved native 2D, tilemaps, UI composition, 2.5D depth and 2D skeletal/flipbook animation."
---
# 2D HYBRID | Stormline Skill

**Category:** engine. **Status:** Versioned instructions only; not engine implementation, an approved ADR, a paid action or release authorization. Trigger only for the task in the description.

## Source and authority
1. Read [AGENTS.md](../../../AGENTS.md) and the [P00 approval gates](../../../docs/engineering/p00-technical-approval-gates.md) before changes. Inspect current main/branch, checkpoint, Ledger/approved ADRs, Scope, DoD, Architecture, Requirements and the smallest relevant module specification.
2. Verify one exact Work Order, context fingerprints and formal dependencies. `research_status=RESEARCH_DOCUMENTED_ADR_PROPOSED` never authorizes implementation. Never widen the approved module DAG or change any of 80 blocked Work Orders based on this skill.

## Workflow
1. Respect TWO-01..04 and GAME-03; keep true 2D APIs separate from 3D-only assumptions while sharing safe graphics resources.
2. Specify pixel snapping, atlas/reimport, text shaping, draw order, parallax, editor preview and input focus.
3. Test DPI/zoom, layer hit-testing, sprite batching, font fallback, localization and mixed 2D/3D scenes.
4. Scope output to the smallest NECESSARY increment and record alternatives and unresolved owner decisions; when executable work is genuinely authorized, inspect Git first, test, capture evidence, PR, pt-BR audit, checkpoint and readback.

## Acceptance and evidence
Record module/WO ID, current BASE/HEAD, filenames, owner and interface authority, error/rollback states, precise future vs real tests, licenses/source provenance, risks and objective acceptance. For visual design, produce references and measured accessible visual proof after an authorized artifact request. A completed SKILL.md is not a completed engine feature.

## Stop condition
No game UI ownership bypass or assumptions that 2D means rendering a flat 3D plane.
Also BLOCK on STALE source, no owner-approved API/ADR/Scope/DoD/risk/release gates, known HIGH/CRITICAL, failed CI, unapproved cost/secrets or attempted public MVP. Never force push or bypass branch protections.
