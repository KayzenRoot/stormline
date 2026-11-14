# Research Work Order — NLE-P00-WO-002-GFX-07

**Research issue #141** | **Future code issue #35 BLOCKED** | **Date:** 2026-11-14  
**State:** APPROVED / MERGED FOR RESEARCH DOCS ONLY (PR #142) | **ADR-0020:** PROPOSED | **Context Lock BASE:** `bd45e076f789e0b934076a1973139400d3eb382b` (GFX-06 PRs #139/#140 merged).  
**Risk:** LOW documentation; future ELEVATED GPU memory/history, HDR output correctness, potentially hostile LUTs and binary SDK rights.

## OBJECTIVE
Specify professional original camera, color management and post-processing, with safe 2D/2.5D/3D and Win/Linux/macOS/Web paths, HDR/SDR fidelity, crisp UI, optional stable TAAU and vendor-neutral baseline. Zcode must eventually implement frozen contracts rather than decide technical architecture.

## CONTEXT
Stormline phase P00 documentation, 80 future code WOs BLOCKED, #35 blocked, GFX-06 architecture researched but **no implemented lighting**. User requests premium visuals compared to Unreal/GGG, subject to real objective measurements. No public MVP, free repo CI and owner-led objective audit.

## SCOPE
- Camera perspective/orthographic/2.5D, lens, projection, jitter/motion-vector and temporal epochs.
- Explicit scene-linear color/OETF/gamut/HDR10 SDR/ACES2/OCIO candidate, histogram EV exposure/grade, safe monitor/Web canvas HDR fallback and screenshot conversion.
- Native/spatial AA and upscaling, optional TAA/TAAU with reactive/velocity/lighting history, FSR SDK v2.4 optional signed native backend, DLSS/Streamline/XeSS vendor terms, dynamic res and FUTURE optional frame generation with latency.
- Bloom, DoF, optional motion blur/FX, accessibility, secure typed Editor/CLI/MCP, budgets and device recovery.
- ADR-0020 **PROPOSED**, architecture, license matrix, semantic API, 77 future tests, independent quality benchmark protocol, Evidence Bundle and minimal Architecture/Backlog + existing #35 blocked packet links; SRCC optional prove-or-drop.

## OUT OF SCOPE
No C++/shader/GPU code, signed binary install/SDK download, LUT copying, live color display capture, native benchmarks, GFX-08 VFX implementation, paid CI, CodeRabbit, external human reviewer requirement, bypass/force push, public release or claim current visual superiority.

## FILES / SOURCES TO READ
Canonical hierarchy `docs/11-checkpoint.md` > `docs/10-decisions-ledger.md` + approved ADRs > `docs/03-scope.md` > `docs/09-definition-of-done.md` > `docs/04-architecture.md` > `docs/02-requirements.md`, then AGENTS, module catalog/registry, GFX-01/02/03/04/05/06 and DATA-02/03/04/05 semantic contracts, existing #35 packet and official sources in tech matrix. Check Git tree/issue/PR before writing.

## REQUIREMENTS
GOV-001..005, CAP-001/002/004/005/008/009/010/011/012/013/014/016, NFR-001..005 and NLE-D013..020 as applicable to candidate module. Catalog candidate acceptance color/stability/compatibility/device loss. Exact hardware, release class, final gamut/HDR and tolerance/benchmark goals UNDECIDED.

## ARCHITECTURE RULES
No duplicate GPU allocator/RenderGraph, compiler, asset loader/cooker, scene editor, native display backend or HDR light solver. GFX-04 velocity semantics, GFX-05 material/alpha, GFX-06 scene linear and GFX-01 present must be consistent. Native/spatial safe fallback independent from vendor signed DLLs and from temporal history.

## CONSTRAINTS
Docs-only, LOW risk and free CI. 80 implementation modules remain BLOCKED, 0 executor-ready, #35 remains open; ADR-0020 proposal only. Don’t claim tests/software/hardware or source licenses beyond verified legal terms.

## ACCEPTANCE CRITERIA
- [ ] Architecture camera, scene-linear color, ACES2/OCIO/SDR/HDR target modes and typed source/transform/presentation owners covers Windows/Linux/macOS/Web and 2D/2.5D/3D.
- [ ] Camera/depth/velocity/jitter, reactive/transparent motion, GFX-06 flash/history, reconstruction AA and native/spatial fallback specify no silent ghosting or blurred UI.
- [ ] License matrix discriminates FSR SDK 2.4 **signed DLL** from MIT samples, binary-only XeSS, DLSS-G and Streamline framework; no vendor SDK automatically installed.
- [ ] HDR10 vs display-P3 vs raw scene FP16 distinguished; screenshots, gamma and double transfer guarded, accessibility opt-outs.
- [ ] Typed semantic Editor/CLI/MCP contract, 77 future **NOT EXECUTED** cases, competitor benchmarks and SRCC prove-or-drop all linked.
- [ ] GitHub final exact-head Docs Validation CI success, scoped diff, pt-BR security/architecture/license audit no HIGH/CRITICAL; normal squash merge, readback.
- [ ] Separate same-WO checkpoint/registry PR before GFX-08; all 80 coding WOs and #35 remain blocked.

## TESTS
Docs tests via GitHub `docs-validation` workflow on exact HEAD. If local checkout present: `python3 scripts/validate_docs.py`, `python3 scripts/validate_module_catalog.py`, `python3 scripts/validate_wo_registry.py`; blocked selector `python3 scripts/select_wo.py GFX-07` expected REJECT. The 77 graphics test cases are **FUTURE NOT RUN**.

## DELIVERABLES
8 research docs (architecture, technology, ADR-0020, semantic API, acceptance matrix, benchmark protocol, this WO, Evidence Bundle), 3 minimal index/blocked packet docs updates, PR research and separately checkpoint PR. No engine executable.

## REVIEW FORMAT
Pt-BR objective audit: base/head SHA, exact successful CI, scope diff and no HIGH/CRITICAL, copyright/licensing, native/Web fallback, future tests honestly labeled, risks and checkpoint delta, APPROVED / CORRECTION REQUIRED / BLOCKED.

## STOP CONDITION
Failing exact-HEAD CI, stale source hierarchy, unlicensed binary/asset, unsupported HDR or GPU claim, unexpected code or unapproved cost means BLOCKED/CORRECTION REQUIRED on same WO/PR. No GFX-08 before checkpoint audit and merge.

## CONTEXT LOCK
Base main `bd45e076f789e0b934076a1973139400d3eb382b`; repository Git blob SHAs are NOT raw-file SHA-256. Freeze exact SHA-256 fingerprints before code activation, when approved dependencies/DoD are implemented.

## Observed research merge receipt
Research BASE `bd45e076f789e0b934076a1973139400d3eb382b`, final HEAD `830ddbe54b56825bfd902faa2b273d68532a2b99`. [Docs Validation #43624090643](https://github.com/KayzenRoot/stormline/actions/runs/43624090643) SUCCESS at exact HEAD; Socket Security/SonarCloud SUCCESS, objective pt-BR audit APPROVED docs-only, 11 docs files, no HIGH/CRITICAL known. Normal squash merge PR #142 as `5bab9b54b83cfb48a8591e040a3f3e4ecd4a69c3`. This separate checkpoint PR remains subject to exact-HEAD CI/audit. Code #35 BLOCKED, 77 tests NOT RUN, ADR-0020 PROPOSED.
