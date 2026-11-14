# Work Order — NLE-P00-WO-001-EXT-002
**Name:** Stormline full module taxonomy and AI/MCP-first product specification  
**Status:** PROPOSED / PENDING OWNER REVIEW | **Risk:** LOW (docs only)  
**Baseline SHA:** `9032fe3eeb28ef3ac1ec786387e42a3758ed703a`

## OBJECTIVE
Define the complete modular universe of the Stormline commercial engine, covering 2D/2.5D/3D, web, modern 3D, editors, MCP/LLM integration and no-MVP release requirement, before fixing stack or implementing engine.

## CONTEXT
Existing Source Pack established; owner now requests module-by-module planning before any technology decision, with no public MVP and complete commercial engine at final 1.0. This is a **new owner-requested documentation extension** before previously planned `NLE-P00-WO-002` technology research. Preserve its ID and order after this extension is approved.

## SCOPE
Three proposed docs: module catalog, AI/MCP architecture contract, no-MVP full-release readiness. Register proposal as an explicit extension in Backlog/Scope without silently promoting all 78 module candidates to an approved 1.0 Scope. All text-only.

## OUT OF SCOPE
No executable code, renderer, editor, engine binaries, MCP service, tooling install, API keys, repo settings, architecture/stack approval, brand assets, commercial claim, paid service, or public release.

## FILES / SOURCES TO READ
Checkpoint, Ledger/ADRs, Scope, DoD, Architecture, Requirements, brand, AGENTS, existing Backlog, docs/product new proposals and MCP 2026-07-28 official specification.

## REQUIREMENTS
Trace owner directions to existing GOV/BRAND/CAP/NFR requirements without treating their candidate details as already approved. Document 2D/2.5D/3D, browser and AI-native needs, no MVP, quality/perf, security, licensing, external IP boundaries.

## ARCHITECTURE RULES
- Owned engine core and specialist libraries after future ADR.
- Decouple UI/Editor, command kernel and MCP adapter; no server GPU requirement.
- All approved authoring operations discoverable and authorized; raw unsafe internals do not become tools.
- No copied protected game content. No benchmark/superiority claims without evidence.

## CONSTRAINTS
R$0 mandatory GitHub CI, solo owner approvals, no CodeRabbit, no bypass, no new implementation. Existing P00 decisions remain intact. Do not renumber an earlier planned WO without owner approval.

## ACCEPTANCE CRITERIA
1. Stable IDs and descriptions for all proposed modules and dependency references.
2. Distinct 2D, 2.5D, 3D, browser and multiplayer end-to-end readiness paths.
3. MCP as first-class interface with security, versioning, agent parity and complete authorized authoring coverage.
4. No-MVP internal milestones vs commercial release contract clearly distinguished.
5. Existing README and Checkpoint do not incorrectly claim implementation.
6. Proposed status documented, branch/PR and real CI pass before any potential owner-approved merge.

## TESTS
`python3 scripts/validate_docs.py` through actual GitHub docs-validation job; link and metadata validation; dependency table cross-references; scope diff; source factual review; MCP version source check.

## DELIVERABLES
Module catalog, AI/MCP contract, complete-release DoD candidates, Work Order and PR Draft for owner assessment. Evidence Bundle base/head, CI real results and proposed Checkpoint Delta after review.

## REVIEW FORMAT
pt-BR, APPROVED / CORRECTION REQUIRED / BLOCKED, factual support, risks, exact base/head and tests.

## STOP CONDITION
Do not merge/modify approved canonical decisions or start implementation before owner approves the proposed module universe and required capability classes. Any scope conflict stays in the proposal and is escalated.
