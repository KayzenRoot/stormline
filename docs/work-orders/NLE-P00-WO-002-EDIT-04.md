# NLE-P00-WO-002-EDIT-04 — 2D & UI Editor P00 Documentary Research Work Order

**2026-11-15 | Research [#264](https://github.com/KayzenRoot/stormline/issues/264) | catalog 53/80 | future implementation [#71](https://github.com/KayzenRoot/stormline/issues/71) OPEN/BLOCKED.** Verified BASE main `8036d723dbf07c13020536cf9a0550bb5afb4b32`, 52/80 research documented, 28 pending, all 80/80 coding WOs BLOCKED; formal EDIT-02/TWO-02 documented ADR PROPOSED only. Risk LOW (documentation). Future source writes ELEVATED, privileged foreign asset/AI paths potentially HIGH_ASSURANCE as separately classified.

## OBJECTIVE
Research original professional 2D Canvas/viewport and UI editor: zoom/pan, grid and snap, atlas/sprite selection, tilemap brush/Wang autotile/negative chunk edges, layers/parallax, responsive UI anchor/constraints/flex and conditional grid, Unicode shaping/RTL/a11y/IME, pointer/touch/keyboard/gamepad control/button patterns, flipbook/tween/timeline/keyframe/conditional skeletal rigs, isolated previews, undo/redo, DATA-04 versioned save/recovery/migrations, import/export, security/license, multi-OS/Web quality. Specify exactly 128 future acceptance cases with repeatable benchmarks. **No engine source code**.

## CONTEXT
EDIT-03 research #260, PR #261 and checkpoint PR #262 followed by audited closeout main `8036d723dbf07c13020536cf9a0550bb5afb4b32`. Formal dependency graph for EDIT-04 contains **EDIT-02 and TWO-02 ONLY**; both unimplemented, ADRs proposed. Integration owners EDIT-01/02/03/07, TWO-01/02/03, GAME-01/03, GFX-01/07, CORE-04/05/06, DATA-01/02/03/04/05, QA-04 and AI/MCP are NOT new DAG predecessor edges. Source of truth must not split.

## SCOPE (NECESSARY, exactly eight NEW Markdown files)
1. [Original architecture](../architecture/edit-04-2d-ui-editor.md)
2. [ADR-0056 PROPOSED](../adr/0056-edit-04-transactional-2d-ui-authoring.md)
3. [Primary-source technology/license/threat matrix](../research/edit-04-2d-ui-technology-license-matrix.md)
4. [Versioned typed semantic API and error contracts](../contracts/edit-04-2d-ui-api.md)
5. [Exactly 128 FUTURE tests E04-T001..T128](../testing/edit-04-acceptance-matrix.md)
6. [Reproducible benchmark/fault protocol](../research/edit-04-2d-ui-benchmark-protocol.md)
7. This Work Order
8. [Evidence Bundle](../evidence/NLE-P00-WO-002-EDIT-04.md)

Only these eight new docs in research PR; **no** checkpoint/backlog/registry/source/CI changes. After research PR own exact-final-HEAD Docs Validation, objective pt-BR audit, squash and merged-main/contract readback, create **independent checkpoint PR** changing exactly checkpoint/backlog/implementation registry **SOLE EDIT-04 research_status**, this WO and Evidence. Future code #71 remains blocked. Optional four-doc closeout requires own gates before next module. Target after independently verified checkpoint: **53/80 research documented (66.25%), 27 pending, 0 engine**.

## OUT OF SCOPE
No C++ editor, Qt/ImGui/SDL/GPU/renderer import, original 2D project generation, asset/font download, 3rd party scenes, shader or Web app, validation of performance or a11y, skeletal/physics runtime, AI/MCP server, game server, dependency install, SBOM adoption, branch protection bypass, force push, paid CI/CodeRabbit/external reviewer mandate or premature code unlock. No official IP, license, 1.0 release class decision or GUI-only achievement may be inferred.

## FILES / SOURCES TO READ
In canonical priority: `docs/11-checkpoint.md` > `docs/10-decisions-ledger.md` and approved ADRs > `docs/03-scope.md` > `docs/09-definition-of-done.md` > `docs/04-architecture.md` > `docs/02-requirements.md` > `docs/00-source-hierarchy.md` > `AGENTS.md` > `docs/product/module-catalog.md` > `docs/queue/implementation-registry.json` > `docs/queue/work-orders/EDIT-04.md`. Consult EDIT-02 project and TWO-02 tilemap formal contracts; EDIT-01/03/07, TWO-01/03, GAME-01/03, GFX-01/07, CORE-04/05/06, DATA-01/02/03/04/05 and QA-04 as integration owner specs. Official Godot 4.6, Tiled, LDtk, Dear ImGui, Qt, Yoga, HarfBuzz, FreeType, Unicode, W3C, Spine runtime license and SDL3 sources linked in matrix.

## REQUIREMENTS
GOV-001..005; CAP-008/009/010/011/012/013/014/016; NFR-001..005; NLE-D013..020, with NLE-D009 source license OPEN. Catalog acceptance exactly `Projeto 2D completo construído pela interface sem acesso direto a arquivos.` is future executable proof. No released engine, game, editor, build or graphics benchmark. Specific target OS and version minimum / release class / codec license approval TBD.

## ARCHITECTURE RULES
EDIT-04 only semantic tool state/interaction and validated authoring facade; EDIT-01 commands/shell/input host, EDIT-02 project, TWO-02 canonical signed64 tiles, TWO-01 draws, TWO-03 animation evaluator, GAME-03 UI tree/layout/shaping/focus, GFX-07 camera, DATA-04 storage/CAS/undo, DATA-01 VFS and DATA-02 assets, CORE-04 time, CORE-05 math, CORE-06 diagnostics, QA-04 threats, AI/MCP scoped public commands. All destructive edits through preview/confirm/stage/CAS; no untrusted script, path bypass, GPU source, direct world writes or duplicated layout/asset authoring engines.

## CONSTRAINTS
Source Pack precedence, exact source SHA/fingerprints before mutation, context STALE on relevant approved changes, free docs CI only, no imaginary benchmark or proof. Do not claim Tiled GPL editor, Qt GPL-only module, Spine proprietary runtime freely embeddable; version/license and font rights need owner review. Unknown required schema -> read-only or reject. All 80 implementation statuses remain BLOCKED; never flip executor_ready/approved_adr/release class.

## ACCEPTANCE CRITERIA
- [ ] Exactly eight NEW scoped Markdown with official sources, ADR PROPOSED, compatibility/license/risk and all integration owners clear.
- [ ] Exactly **128 distinct** E04-T001..E04-T128, all **FUTURE/NOT EXECUTED**, reproducible benchmark/failure/OS/a11y/GUI-only proof plan.
- [ ] Research PR exact final HEAD Docs Validation SUCCESS, actual file count and tests/link/DAG/registry selector verified; objective independent diff pt-BR audit and no HIGH/CRITICAL.
- [ ] Normal squash merge then main API/readback; independent 5-file checkpoint PR with own CI/audit/squash/main and sole EDIT-04 registry research status, no code unlock.
- [ ] Research #264 closed only after checkpoint factual merged-main readback, future code #71 still OPEN/BLOCKED; optional closeout independently audited.

## TESTS
Research only: run/verify actual `python3 scripts/validate_docs.py` via GitHub Actions docs-validation at exact PR final SHA (includes local MD links, 80-module DAG, registry schema and blocked Zcode selection). Static check eight files, unique E04 IDs and ADR state. No C++ unit/integration, source save, screenshot, GPU/OS/perf or native accessibility tests occurred. Future fixture matrix and operations in testing/benchmark docs, thresholds TBD owner.

## DELIVERABLES
Eight new docs, issue/branch/PR links, actual Git base/head, diff, CI/job evidence, risks and audit, proposal for checkpoint delta then verified independent checkpoint and historical readback. No GUI binary or public app.

## REVIEW FORMAT
Português brasileiro: APPROVED / CORRECTION REQUIRED / BLOCKED; exact base/head/hash, touched paths/links/CI job, 128 not executed proof, architecture/rights/security/a11y, defect severity, risks, proposed checkpoint delta and next stop. Corrections in same WO/PR.

## STOP CONDITION
Stop on source STALE/unexpected diff, any unapproved owner decision, 80 code unlock, evidence missing for merge, failed CI, known HIGH/CRITICAL, security/asset license issue, wrong future test count or scope leak.

## CONTEXT LOCK (planning baseline)
Verified main base `8036d723dbf07c13020536cf9a0550bb5afb4b32`; on research branch re-fetch canonical source blob SHA fingerprints and compare before writes. Checkpoint/Scope/DoD/Architecture/approved ADR relevant change invalidates lock and requires rebase. **Not an executor code context lock.**

## EVIDENCE BUNDLE
[Evidence](../evidence/NLE-P00-WO-002-EDIT-04.md) records known baseline, what is verified now, proposed future gates, actual hashes/CI/PR to append ONLY when observed.

## EDIT-04 research PR #265 objectively approved and merged, checkpoint proposed
- [#265](https://github.com/KayzenRoot/stormline/pull/265): BASE `8036d723dbf07c13020536cf9a0550bb5afb4b32`, audited HEAD `b11310f737cec2d3d51dd6aaab8d25cd63f0cd1a`, **exactly eight NEW Markdown**. [Docs Validation #43731437609](https://github.com/KayzenRoot/stormline/actions/runs/43731437609) SUCCESS job 132864517052; Source Pack, links, 80-module DAG, registry and selector rejecting blocked WOs all SUCCESS. [Objective pt-BR audit comment #6897060553](https://github.com/KayzenRoot/stormline/pull/265#issuecomment-6897060553) APPROVED documentary only; normal squash merged and actual main/typed API readback `2dd707f86106df30b9a01e82dcdb5d1a6a64774e`. All 128 E04 cases remain future/not executed, 0 engine/GUI/GPU/OS tests.
- **Separate checkpoint PR BASE** `2dd707f86106df30b9a01e82dcdb5d1a6a64774e`, changes exactly checkpoint/backlog/implementation-registry/**this WO**/**Evidence**, SOLE EDIT-04 `research_status` transition to `RESEARCH_DOCUMENTED_ADR_PROPOSED`. Pending its own exact-final-HEAD Docs Validation, independent pt-BR audit, squash/main readback. Target 53/80 documented (66.25%), 27 pending, zero engine; all 80 implementation packets blocked, `executor_ready=false`, `approved_adr=null`, release class UNDECIDED. #264 closes ONLY after verified checkpoint readback; coding #71 OPEN/BLOCKED. No premature owner approval of ADR-0056.
