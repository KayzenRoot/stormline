# Research Work Order — NLE-P00-WO-002-TWO-01

**Date:** 2026-11-14 | **Research issue #147** | **Future implementation issue #37 BLOCKED**  
**State:** APPROVED / MERGED FOR RESEARCH DOCS ONLY (PR #148) | **ADR-0022:** PROPOSED | **BASE main `2ec91d4cf0f3062745a5d4b6d340da7027317348`**.  
**Risk:** LOW documentation; future ELEVATED GPU/asset parsing/clip/Unicode/toolchain/rights. Research following GFX-08 checkpoint PR #146; code GFX-01/DATA-03 not yet implemented.

## OBJECTIVE
Specify original native Canvas2D for sprites, texture atlas, stable layer alpha batching, 2D camera/pixel snapping and optional vectors/international text that works on Windows/Linux/macOS/Web and integrates lighting/VFX, while retaining safe CPU WebGL2 baseline, typed Editor/CLI/MCP API and objectively measurable 60 FPS target. Zcode's future coding work should follow frozen source contracts, not decide architecture from scratch.

## CONTEXT
Stormline P00 planning only, catalog includes 80 implementation packets as BLOCKED; owner direction: 2D/2.5D/3D first-class, Web and native desktop, no public MVP, solo/free CI and secure AI native authoring. GFX-08 research docs complete but GFX-01/DATA-03 mandatory implementation dependencies remain unavailable. Existing stable code WO `NLE-EXEC-WO-TWO-01-001` #37 OPEN/BLOCKED.

## SCOPE
- 2D Sprite/Canvas layer, painter order and alpha/clip/mask, orthographic camera, pixel snap+HiDPI, UV/gutter/mips/atlas version and bounded GPU instancing/safe WebGL2 CPU and WebGPU feature-gated fallbacks.
- Optional vector paths/gradients and safe SVG Tiny import; compare ThorVG MIT/Skia BSD/Blend2D zlib JIT/lyon Rust FFI but no adopted dependency until test.
- Text drawing, glyph atlases, international shaping/fallback and rights with HarfBuzz, FreeType FTL credit, msdfgen MIT core/ext. Distinguish UI high-level layout/IME from canvas glyph output; optional Rive MIT runtime content/export splash conditions disclosed.
- GFX-03/05/06/07/08 and DATA-02/03/04/05 distinct owners; typed versioned contract, asset/script/privacy security, budgets and p50/p95/p99, 81 future NOT EXECUTED test cases, reproducible benchmark. Optional S2CC prove-or-drop.
- ADR-0022 PROPOSED, architecture, matrix, contracts, tests, benchmark, Evidence Bundle and 3 additive index links. Separate same-WO research PR then checkpoint reconciliation PR, no code.

## OUT OF SCOPE
No shaders/C++, GPU software/SDK/fonts downloaded, license selection for Stormline engine, full UI text editor or IME, tilemaps TWO-02, 2D animation TWO-03, hybrid 2.5D TWO-04, paid Rive exports, unrelated cleanup/CI changes or implementation, no proprietary content copied. No CodeRabbit, mandatory outside reviewer, bypass or force push, no GFX promise.

## FILES / SOURCES TO READ
Canonical: `docs/11-checkpoint.md` > `docs/10-decisions-ledger.md` + approved ADRs > `docs/03-scope.md` > `docs/09-definition-of-done.md` > `docs/04-architecture.md` > `docs/02-requirements.md`, then `AGENTS.md`, `docs/product/module-catalog.md`, `docs/queue/implementation-registry.json`, `docs/queue/work-orders/TWO-01.md`, GFX-01/02/03/05/06/07/08 and DATA-02/03/04/05 contracts, authoritative upstream source/license URLs recorded in tech matrix and Git/pr/issue checks. Exact future runtime source files TBD after implementation gate.

## REQUIREMENTS
GOV-001..005, CAP-001/004/008/009/010/011/012/013/014/016 and NFR-001..005, NLE-D013..020 as applicable; future catalog target 60 FPS named 2D scene/hardware and glyph/sprite correctness. Release class, hardware, numerical 60 FPS p95/p99 and precise API incomplete.

## ARCHITECTURE RULES
2D is native first class. GFX-01 presentation, GFX-03 allocator/RenderGraph, GFX-05 material/texture, GFX-06 light, GFX-07 camera/HDR, DATA-03 import and DATA-05 cook remain owners. Never reorder transparent draws except proven equivalence. Validate SVG/fonts and asset rights, no JIT/vendor tool mandatory, secure project-scoped MCP revision checks, WebGL2 non-compute fallback.

## CONSTRAINTS
Docs-only LOW risk, zero cost CI, solo objective audit, no HIGH/CRITICAL, no code tests claimed. Future implementation #37 remains BLOCKED/`executor_ready=false` and all 80 coding WOs unchanged. ADR-0022 PROPOSED, no released or executable engine.

## ACCEPTANCE CRITERIA
- [ ] Original native Canvas 2D semantics, pixel snap DPI, camera, stable layers/group alpha and batching, atlas/UV/gutters, 2D/2.5D interoperability explicitly designed.
- [ ] Vector paths/safe SVG subset, international text/glyph shaping/raster and licensed fonts with fallback; no duplicate UI/IME and GPU compiler/allocator.
- [ ] Tool/license matrix distinguishes ThorVG MIT SVG Tiny, Skia BSD, Blend2D zlib/JIT, lyon Rust licenses, HarfBuzz, FreeType FTL credit/GPLv2, msdfgen extensions and Rive runtime MIT vs splash/paid authoring restrictions.
- [ ] Versioned semantic Editor/CLI/MCP safe commands, 81 FUTURE NOT RUN tests, reproducible future 60FPS benchmark, optional S2CC prove-or-drop.
- [ ] Exact final HEAD free Docs Validation SUCCESS, 11 scoped docs files, objective pt-BR security/license/architecture audit no HIGH/CRITICAL, normal squash merge/readback.
- [ ] Separate same-WO checkpoint PR and registry delta **only TWO-01 research_status** pending->documented after research approved/merged. All 80 implementation packets blocked and #37 open, ADR PROPOSED, next TWO-02 only after checkpoint merge/audit.

## TESTS
Docs via GitHub Actions `docs-validation` exact HEAD (expected scripts only; actual result must be observed). Local when cloned: `python3 scripts/validate_docs.py`; `python3 scripts/validate_module_catalog.py`; `python3 scripts/validate_wo_registry.py`; `python3 scripts/select_wo.py TWO-01` must reject blocked coding. 81 Canvas/2D/renderer tests are FUTURE NOT RUN, no GPU or pixel test in research.

## DELIVERABLES
Eight research docs (architecture, technology matrix, ADR-0022, semantic API, acceptance 81, benchmark, this WO, Evidence Bundle), 3 index/blocked packet docs updates; GitHub research issue/PR+audit and separate checkpoint PR+audit. No engine software.

## REVIEW FORMAT
pt-BR objective audit, BASE/HEAD and exact CI links, 11-file scope, license/security risks, requirement+DoD alignment, 60FPS artifact evidence truth, proposed Checkpoint Delta and verdict APPROVED / CORRECTION REQUIRED / BLOCKED. No high/critical known may pass.

## STOP CONDITION
Canonically stale base, failing CI, unlicensed code/assets, false benchmark claims or unexpected code/permission/out-of-scope stops and requires Correction Delta same issue/PR; never continue TWO-02 before current approved checkpoint. No force push, bypass or paid tools.

## CONTEXT LOCK
BASE main `2ec91d4cf0f3062745a5d4b6d340da7027317348`; Git blob hashes are not raw file SHA-256. SHA-256 fingerprints and exact ABI/source files are required before implementation activation, not claimed at research stage.

## Observed research PR #148 receipts
BASE `2ec91d4cf0f3062745a5d4b6d340da7027317348`, HEAD `e25399cedab2fddab242ccfa5d562e95513d2c76`, [Docs Validation #43627143316](https://github.com/KayzenRoot/stormline/actions/runs/43627143316) SUCCESS at exact final HEAD; Socket Security/SonarCloud PASS, 11 documents only, objective pt-BR audit APPROVED docs with no HIGH/CRITICAL found, squash merge `7fb41e39a938f94dbe5c6c1fa177174d7f6d0bb0`. Checkpoint is separate same-WO PR with own CI/audit. 81 future tests NOT RUN; ADR-0022 PROPOSED; code #37 BLOCKED.
