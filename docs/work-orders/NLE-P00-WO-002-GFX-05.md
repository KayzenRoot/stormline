# Research Work Order — NLE-P00-WO-002-GFX-05

**Research issue:** #135 | **Future implementation issue:** #33 BLOCKED | **Date:** 2026-11-14  
**State:** RESEARCH IN PROGRESS, DOCS ONLY | **ADR-0018:** PROPOSED / NO ENGINE CODE  
**Context Lock BASE main:** `ace3355583dd1f83d2d483081184d665fa2229fa` (GFX-04 research/checkpoint #133/#134 merged).  
**Risk:** LOW docs, future ELEVATED (untrusted image codecs, PBR correctness, GPU resource lifetime, texture streaming).

## OBJECTIVE
Specify materials, texture systems and PBR for Stormline across Windows/Linux/macOS and Web with 2D/2.5D/3D support. Preserve high visual quality, optional innovative streaming and low-end graceful degradation with technical choices, typed interfaces, acceptance tests and licensing explicitly planned. No implementation.

## CONTEXT
Project P00 documentation; solo owner/agent objective audit; free public CI and no public MVP. GFX-01–04, DATA-01–05 and CORE-01–06 are only researched/documented. GFX-02 + DATA-03 future implementations are not integrated. Existing #33 and all 80 code WOs are BLOCKED.

## SCOPE
- glTF metallic-roughness PBR, GGX/Smith/Fresnel linear-light contract, stylized and 2D domains, optional KHR material extensions; source color/sRGB/linear/alpha, normals and mips.
- KTX2/Basis Universal ETC1S/UASTC and BCn/ASTC/ETC2/uncompressed target profile matrix, KTX-Software mixed license/ETC exclusion, MaterialX optional interoperability.
- Alpha OPAQUE/MASK/BLEND vs physical transmission, sorting/OIT candidate, decals, foliage and overdraw budgets.
- Typed semantic material/texture/instance/sampler/cook/profile/residency and Editor/CLI/MCP commands with scope and revision checks.
- DATA-03 import, DATA-05 cook/chunks, GFX-02 shader compile/reflection, GFX-03 GPU/VRAM/fences, GFX-04 visibility boundaries and browser fallback.
- Propose STAM adaptive texture R&D prove-or-drop, 44 future tests, security/legal review, ADR-0018 PROPOSED, research matrix, Evidence Bundle, future blocked packet and architecture/backlog links.

## OUT OF SCOPE
C++/shader runtime, external SDK install, compressed texture assets, image generation, GPU render benchmarking, codecs vendor integration, editing actual game art, GFX-06 lighting implementation, GFX-07 post-processing, paid CI/CodeRabbit, mandatory outside human review, bypass/force push, public engine release or deployment; no code WO unlocked.

## FILES / SOURCES TO READ
Canonical order `docs/11-checkpoint.md` > `docs/10-decisions-ledger.md` and approved ADRs > `docs/03-scope.md` > `docs/09-definition-of-done.md` > `docs/04-architecture.md` > `docs/02-requirements.md`, `AGENTS.md`, `docs/product/module-catalog.md`, `docs/queue/implementation-registry.json`, GFX-02/03/04 & DATA-02/03/05 contracts, current #33 packet and public Khronos/MaterialX/BasisU specifications as cited in matrix. Always inspect Git tree/issue/PR before write.

## REQUIREMENTS
GOV-001..005; CAP-001/002/004/005/008/009/010/011/012/013/014/016; NFR-001..005 and NLE-D013..020 to the extent defined by canonical Requirements/Ledger. Catalog GFX-05 candidate acceptance: **golden material scenes and bounded overdraw** (future physical test). Exact numeric thresholds, minimum hardware, release class and build toolchain remain UNDECIDED.

## ARCHITECTURE RULES
No duplicate import/asset manager/cooker/compiler/VRAM service. Expected revision, rights-aware DATA-02 ID, validated GFX-01 device capabilities, GFX-02 reflection/layout and GFX-03 completion are required before material activation. Color/normal/alpha/transmission semantics explicit; conservative foliage rules; bounded resources/codec work; cross-target clear fallbacks; no MCP raw GPU/host privileges.

## CONSTRAINTS
Docs-only LOW. All 80 future coding WOs remain `executor_ready=false`, release class UNDECIDED, state BLOCKED. No new paid tools, credential, required outside reviewer, bypass, force push, runtime promises or 'benchmark pass' without actual output. Future exact dependency versions/license/SBOM/targets are gating choices, never invented.

## ACCEPTANCE CRITERIA
- [ ] Original GFX-05 architecture, full technology/licensing matrix, ADR-0018 PROPOSED and semantic API with boundary map all present.
- [ ] Texture format/capability/fallback and color/sampler/mipmap/normal/alpha/decal/recovery contract covers real target classes, without imaginary GPU feature guarantees.
- [ ] Legal gate identifies KTX-Software mixed licenses / optional non-open-source ETC decoder; MaterialX/BasisU transitives require exact audit before use.
- [ ] At least 32 future test scenarios, including 2D/2.5D/3D, Win/Linux/Mac/Web, GPU loss and adversarial textures; all explicitly NOT RUN.
- [ ] STAM optional prove-or-drop with objective reference, no false performance invention.
- [ ] Exact final PR HEAD free docs CI successful, scope-only pt-BR security/licensing/architecture review no HIGH/CRITICAL; squash merge normal and readback.
- [ ] SAME-WO separate docs checkpoint reconciliation PR only after research merge, before GFX-06. No code issue activation.

## TESTS
`python3 scripts/validate_docs.py`; `python3 scripts/validate_module_catalog.py`; `python3 scripts/validate_wo_registry.py` and `python3 scripts/select_wo.py GFX-05` should reject blocked code packet (run only if source checkout available). GitHub Actions docs-validation must report success at exact HEAD. All 44 specified PBR/TEX/ALP/SYS tests remain **future NOT EXECUTED**.

## DELIVERABLES
Architecture, matrix, ADR-0018, typed API, 44-test matrix, this research WO, Evidence Bundle; additive source links in architecture/backlog and blocked #33 packet; research PR and separate reconciled checkpoint PR. NO code artifacts.

## REVIEW FORMAT
Pt-BR technical audit: base/head, diff file list, exact successful CI head and runs, source licensing + security, correctness/portability, HIGH/CRITICAL scan, risks, Evidence Bundle and explicit APPROVED/CORRECTION REQUIRED/BLOCKED.

## STOP CONDITION
Do not advance until exact-head CI, scope and review pass. Halt if canonical files move unexpectedly (STALE), license/security claims are false, unsupported platforms are sold as covered, high/critical defect remains, or documents imply functioning engine. Never activate code #33.

## CONTEXT LOCK
BASE main `ace3355583dd1f83d2d483081184d665fa2229fa`, linked critical **Git blob object SHAs**, not claimed byte SHA-256; byte SHA-256 of canonical files required only at later executable activation. Rebase and re-review if Checkpoint/Scope/DoD/Architecture/approved ADR changes.

## EVIDENCE BUNDLE
See [research evidence](../evidence/NLE-P00-WO-002-GFX-05.md). PR CI and audit must be added only after observed; checkpoint delta proposed, never executor-promoted unilaterally.
