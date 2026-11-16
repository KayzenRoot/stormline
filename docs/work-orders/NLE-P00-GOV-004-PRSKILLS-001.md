# NLE-P00-GOV-004-PRSKILLS-001 — Per-PR skills traceability and evidence (documentary-only)
**Issue:** [#412](https://github.com/KayzenRoot/stormline/issues/412) | **Base HEAD:** `aa1ee3ccd65897ea2f99c79e9ad23020a2e9a152` | **Risk:** LOW documentation | **Status:** DOCUMENTARY ONLY / no code activation.

## OBJECTIVE
Require an explicit, minimal per-PR record of relevant repository Agent Skills, actual SKILL.md consultation and concrete output, bridging the existing 36-skill/80-module manifest to the PR template without changing implementation authorization.

## CONTEXT
36 versioned `.agents/skills/<slug>/SKILL.md`, 80 mapped modules, 80 blocked code issues #18–#97 and 748 blocked PR packet plans already exist. The PR template lacked any skill-use field; a fabricated list of all 36 would be neither correct nor useful.

## SCOPE
Two existing text files: `.github/PULL_REQUEST_TEMPLATE.md` and `docs/engineering/pr-decomposition-policy.md`; this WO and a minimal Evidence Bundle only.

## OUT OF SCOPE
80 empty module PR shells; any new or activated implementation packet; code, builds, native tests or workflows; module DAG, registry/manifest, ruleset settings, ADR/license approval, CORE-01-02, G3-V01/V02 changes.

## FILES/SOURCES TO READ
Checkpoint > Decisions Ledger/ADRs > Scope > DoD > Architecture > Requirements > AGENTS.md > [skills catalog](../engineering/stormline-skills-catalog.md) and [manifest](../engineering/stormline-skills-manifest.json) > [PR index](../pr-plans/index.md) > [decomposition policy](../engineering/pr-decomposition-policy.md) and PR template.

## REQUIREMENTS
One stable packet/WO per actual future PR; minimal skills selection from module mapping; no assumed invocation; evidence of skill consultation/application per PR; documentation-only work never confers permission to implement.

## ARCHITECTURE RULES
Respect canonical DAG and owners, Source Check/Context Lock and exact-head CI. Keep governance skills `stormline-source-check`, `stormline-work-orders`, `stormline-evidence-audit` identifiable; choose module-specific skills only when directly relevant.

## CONSTRAINTS
Preserve 23 bounded owner directions, G1 PARTIAL, G2 CLEARED ruleset 27393227, G3-V01 AWAITING_OWNER, G3-V02 NOT_AUTHORIZED, ADR-0003/0075 PROPOSED, NLE-D009 OPEN, 80/80 code WOs BLOCKED and 0 ready/approved ADR; CORE-01-01/02 PLANNED_BLOCKED, engine_implemented=false. No paid services or reviewers.

## ACCEPTANCE CRITERIA
Exactly four documentary files changed/added; PR template requires task/skills/evidence selection, policy prevents bulk shells, all canonical gates intact; no changes to skills themselves, registry/manifest or CI workflows; objective pt-BR audit and `docs-validation` SUCCESS on exact PR HEAD.

## TESTS
GitHub Docs Validation and negative diff/status review; no native C++/GPU/security penetration tests were executed.

## DELIVERABLES
This WO, PR template/policy, Evidence Bundle, audited documentation PR, squash/main readback, checkpoint delta only if canonical source needs revision.

## REVIEW FORMAT
`APPROVED DOCUMENTARY ONLY` / `CORRECTION REQUIRED` / `BLOCKED`, with exact base/head SHA, actual CI, affected files and preserved gates.

## STOP CONDITION
Stale source, altered rule/workflow/registry/manifest, missing CI, HIGH/CRITICAL finding, unapproved G3 choice or new code/empty PR proliferation.
