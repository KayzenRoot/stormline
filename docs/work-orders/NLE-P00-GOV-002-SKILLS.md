# NLE-P00-GOV-002-SKILLS — Original Stormline Agent Skills Pack and Premium Editor UI Proposal

**STATE: DOCUMENTARY + VALIDATOR TOOLING ONLY; owner-requested, not release/engine code.** [Issue #378](https://github.com/KayzenRoot/stormline/issues/378), base Git `356695b078001f4f9caa94d1119ae045bf391375`. 80/80 research documented, 80/80 implementation WOs blocked, 0 executor_ready, approved ADR=0, engine_implemented=false. NLE-D009 source license OPEN, NLE-D010 brand clearance OPEN. The user has requested skills covering design/layout/icons, future engine/backend/QA/testing.

## OBJECTIVE
Deliver 36 repository-native Agent Skills, indexed over the 80-module catalog with precise triggers/stop/evidence, and an original premium dark desktop app design brief, with zero-paid reproducible skill-pack validation in Docs CI. Skills help future Codex/Zcode workers stay specialized without choosing unapproved technology or copying protected OS visuals.

## CONTEXT and Context Lock
Canonical precedence: checkpoint > Ledger/approved ADRs > Scope > DoD > Architecture > Requirements > catalog/technical gate plan > skills. Baseline `356695b078001f4f9caa94d1119ae045bf391375` and Git tree `da705e73c9690834eda40fe1b7c33fc31e64066c`. Critical observed Git blob SHA-1 IDs (NOT raw SHA256): AGENTS `3e57b719f8651407879ebb641707a048773ea4c2`; checkpoint `da206517f3b2f65c75bbd99ce1a00d2e15bdfd53`; ledger `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`; Scope `4ef605c74632ece080b2650e37dd83a415b63310`; DoD `160b3054db9ea1961308934b401488b838d24c3e`; Architecture `df62574cb3956c3ac9881631a4cf66be4e1abff1`; Requirements `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`; registry `abbf8e5f971b8de5d73f55c9ec5a0bd7a2632024`; approved research gate proposal `7b144db5b51b24959f02aa1f1c4082bba4ec070c`; Brand Foundation `3c6f8dc8188edfd24e7394fc0e0f95b967a8aa57`; Docs CI `cbbaf5731de75f1de4bdf8cad6489e6d73681d71`. If source changed => STALE and rebase; future executor computes actual raw SHA256 at activation.

## SCOPE: NECESSARY
- Exactly **36** `.agents/skills/stormline-*/SKILL.md` with YAML `name/description` and focused trigger/workflow/acceptance/stop rules (5 governance, 8 visual, 15 engine, 8 QA).
- [Human catalog](../engineering/stormline-skills-catalog.md), machine manifest mapping 80 modules, [premium UI design proposal](../engineering/stormline-editor-visual-system-proposal.md), this WO and [Evidence](../evidence/NLE-P00-GOV-002-SKILLS.md).
- One new Python stdlib validator `scripts/validate_skills.py` and unit tests `scripts/test_validate_skills.py` for syntax/count/module map/reference/path safety; add **two narrow steps** to existing `.github/workflows/docs.yml` following current controls. Script is repository tooling, **not engine**.
- Commit/PR with exact HEAD Docs Validation including old validators and new skill tests, pt-BR objective audit, squash/main readback; separate checkpoint PR modifies checkpoint/backlog/existing Evidence only after primary merge, with independent CI/audit/readback.

## OUT OF SCOPE
No C++/Vulkan/SDL3 runtime code, no Web UI, no implementation of editor widgets, no generated logo/icon artwork or borrowed Apple assets, no final SVG/PNG, no external paid plug-ins, no Figma work without owner authorization, no new SDK or release, no new dependencies, no automatic Zcode execution, no ADM rulesets/branch settings or license. Future skills are guidance only, not a system capable of implementing engine alone.

## FILES/SOURCES TO READ
AGENTS.md, canonical Sources, 80 registry/catalog, NLE-P00-GOV-001 audit and gates, docs/brand/brand-foundation.md and logo-system.md, docs/engineering/agent-execution.md, free-ci.md, .github/workflows/docs.yml; official [Codex skill docs](https://learn.chatgpt.com/docs/build-skills) and [Agent Skills specification](https://agentskills.io/specification). Consult exact module ADR/contract only on use, not loading all 80 at start.

## REQUIREMENTS / ARCHITECTURE RULES
GOV-001..005, NLE-D003..005, D008/009/010/011/013..020. Repo-scoped skills are a progressive-disclosure instruction layer beneath Source Pack, **not independent policy**. Design must be elegant and original, apple-class craft *without reproducing Apple's UI/icons/fonts*. Keep user assets and fonts original/licensed, accessible contrast, reduced transparency, GPU fallback. User's dark/blue/cyan brand proposal remains PROPOSED, no signoff faked.

## CONSTRAINTS / SECURITY
R$0 public GitHub standard docs CI, Python stdlib only, no pip, no third-party network, no CodeRabbit, no forced push, no destructive code or credentials, no bypass. No automated edits to registry, ADR, ledger, Scope/DoD or any of 80 blocked coding packets. No claim auto-discovery by Zcode without tool proof. Risk LOW for docs/validator, if execution permission or credential issue => BLOCKED.

## ACCEPTANCE CRITERIA
- [ ] 36 unique lower-kebab name/frontmatter under max constraints and obvious trigger descriptions, correct AGENTS Source Pack links and stop conditions.
- [ ] 80 registry module IDs all mapped by machine manifest to existing specialized skills; categories exactly governance 5 / design 8 / engine 15 / QA 8, no duplicate/unlisted/missing skill.
- [ ] Detailed editor UI art-direction proposal with original icon families, design tokens, panel/workspace layouts, contrast and blur-off/low-GPU test plan, screenshots only later by authorized asset WO; does not falsely claim Apple authorization or finished assets.
- [ ] Python stdlib validator + meaningful negative unit tests + two Docs Validation steps, no third-party dependency, full current docs CI remains green.
- [ ] Only skill tooling/docs and minimal CI diff. 80 code packets untouched/blocked; 0 ready, 0 approved tech, no license or release.
- [ ] PR exact-head CI SUCCESS; auditoria independente pt-BR, normal squash and main readback; separate 3 Markdown checkpoint after approval/merge.

## TESTS
`python3 scripts/validate_skills.py`, `python3 -m unittest discover -s scripts -p test_validate_skills.py`, plus existing `python3 scripts/validate_docs.py`, `python3 scripts/validate_module_catalog.py`, `python3 scripts/validate_wo_registry.py`, and negative `python3 scripts/select_wo.py CORE-01 --json` expected exit 2. Each test runner outcome must be observed, not claimed from this proposal.

## DELIVERABLES / REVIEW FORMAT
36 SKILL.md, manifest/catalog, visual spec, scripts/tests, minimal workflow change, this WO+Evidence, issue #378, PR+CI, pt-BR audit APPROVED/CORRECTION REQUIRED/BLOCKED; checkpoint delta **proposed**, not executor-promoted. Git readback records stable SHA/files.

## STOP CONDITION
STALE source, invalid YAML/links/catalog, failed CI, duplicate name, missing one of 80 map, copy of protected icons, licensing uncertainty presented as approved, new implementation code/registry change, paid service or any HIGH/CRITICAL. Correction Delta in same PR; no next increment until approved.
