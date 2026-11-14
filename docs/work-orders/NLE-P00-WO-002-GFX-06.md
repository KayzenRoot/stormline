# Research Work Order — NLE-P00-WO-002-GFX-06

**Issue:** #138 | **Future code issue:** #34 BLOCKED | **Date:** 2026-11-14  
**State:** RESEARCH IN PROGRESS / DOCS ONLY | **ADR-0019:** PROPOSED | **Risk:** LOW docs; future ELEVATED GPU memory/temporal/driver.  
**Context Lock BASE main:** `59f044b9ac34411bbdd2f0170549bb4a9c78465e` (GFX-05 research PR #136 & checkpoint PR #137 merged).

## OBJECTIVE
Define high-fidelity, responsive, portable lighting and shadows that can *eventually* compete against Unreal Lumen/VSM and GGG Radiance Cascades on objective benchmarks. The executor later should code against bounded architecture, typed contracts and accepted tests, not choose the lighting system from scratch.

## CONTEXT
Stormline P00 research only; 80 future implementation WOs are BLOCKED; #34 code is not executable; GFX-03/GFX-05 prior studies are NOT implemented. Owner decisions include Windows/Linux/macOS, web, 2D/2.5D/3D, AI-native, no public MVP and free GitHub CI/solo objective audit.

## SCOPE
- Light types/photometric units, many-light clustered/Forward+ strategy and explicit low-end fallback.
- Stable CSM/PCF and local shadow atlas, optional PCSS/contact/Virtual Shadow Maps with cache validation and GPU fencing; RT hardware shadows optional by capability.
- Hybrid GI: IBL/probes/lightmaps, SSGI/SSR and offscreen fallback, DDGI/SDF/Brixelizer native candidates, Radiance Cascades 2D/2.5D priority R&D with full 3D experiment guarded, hardware RT GI/reflections optional.
- Volumetric/fog and ARPG many-dynamic-emissive light stress; temporal invalidation, device loss, 2D/2.5D layering, quality tier/budget/profiling and secure Editor/CLI/MCP semantics.
- ADR-0019 PROPOSED, original research architecture, license/technology matrix, conceptual typed API, 68 future test cases and independent competitor benchmark protocol, evidence, minimal Architecture/Backlog links and existing #34 blocked packet update. SLRG optional PROVE-OR-DROP.

## OUT OF SCOPE
No source code/runtime/shaders/GPU tests/deployment, no library download/vendor SDK/credentials, no live game comparison/rights-restricted assets, no GFX-07 color implementation, no stage beyond GFX-06, no paid CI, CodeRabbit, mandatory external reviewer, bypass/force push, marketing claim better than Unreal or GGG.

## FILES / SOURCES TO READ
Canonical precedence: `docs/11-checkpoint.md` > `docs/10-decisions-ledger.md` and approved ADRs > `docs/03-scope.md` > `docs/09-definition-of-done.md` > `docs/04-architecture.md` > `docs/02-requirements.md`. Then AGENTS, module catalog/registry, GFX-01/02/03/04/05 & DATA-02/03/04/05 typed contracts, GFX-06 packet and official sources in tech matrix. Git tree/issue/PR must be inspected before changes.

## REQUIREMENTS
GOV-001..005, CAP-001/002/004/005/008/009/010/011/012/013/014/016, NFR-001..005, NLE-D013..020 when applicable. Catalog acceptance: future visual/temporal quality and budgets per hardware tier, not already achieved. Numeric performance target, release-class, min GPU, exact SDK/compiler/asset versions: UNDECIDED.

## ARCHITECTURE RULES
No duplicate GPU allocator, shader compiler, BRDF, asset store or scene; GFX-03 GPU life/budget and GFX-05 material physics authoritative. Correct portable fallback, explicit native/Web capability queries, ray tracing OPTIONAL and no corruption/ghosting under temporal invalidate; mixed-licensed NVIDIA SDK forbidden by default.

## CONSTRAINTS
Docs-only, no unapproved expenses, no external human review requirement, 0 executor-ready, no HIGH/CRITICAL known, SHA Context Lock. Future work risk ELEVATED with actual hardware/fuzz and platform tests, not implied from CI docs.

## ACCEPTANCE CRITERIA
- [ ] Architecture covers light units, clustered/Forward+, stable CSM/PCF, optional Virtual Shadow Maps distinct from variance, GPU page invalidation and safe fallback.
- [ ] GI tracks include portable baked/probes, offscreen limitations, GGG Radiance Cascades 2D and 3D caveats, Brixelizer native, hardware ray optional and volumetric/2D.
- [ ] ADR-0019 PROPOSED, all technology/security/SDK license gates exact, no presumed MIT RTXDI/RTXGI.
- [ ] Versioned contracts, secure MCP semantics, 68 future **NOT RUN** tests and objective Unreal/GGG comparison protocol.
- [ ] No implemented graphics, licenses/versions/hardware claims made without evidence; #34 and all 80 coding WOs remain BLOCKED/`executor_ready=false`.
- [ ] Free exact-final-HEAD GitHub docs-validation SUCCESS, security/architecture/licensing pt-BR objective audit no HIGH/CRITICAL, normal squash merge and main readback.
- [ ] Separate same-WO checkpoint/registry reconciliation PR before beginning GFX-07.

## TESTS
For docs, GitHub Actions `Docs Validation` with Source Pack/link checks, catalog DAG/registry, blocked selector. Locally (if repo cloned) `python3 scripts/validate_docs.py`, `python3 scripts/validate_module_catalog.py`, `python3 scripts/validate_wo_registry.py`, and `scripts/select_wo.py GFX-06` must refuse coding. None of the 68 future graphics tests actually run in P00.

## DELIVERABLES
Architecture, license/technology matrix, ADR-0019, API, test matrix, benchmark protocol, this research WO and Evidence Bundle, minimal Architecture/Backlog and existing blocked #34 links, research PR then separately audited checkpoint PR. No engine executable.

## REVIEW FORMAT
pt-BR, base/head SHA, exact CI links, diff, security/license risks, test truth, target compatibility, risk grading, scope, proposed checkpoint delta and APPROVED/CORRECTION REQUIRED/BLOCKED verdict.

## STOP CONDITION
STALE canonical SHA, wrong license/cross-platform claim, HIGH/CRITICAL defect, CI failure, code implementation, unapproved cost/proprietary content or attempt to activate #34 stops immediately. Do not advance to GFX-07 before checkpoint audit.

## CONTEXT LOCK / EVIDENCE
Base `59f044b9ac34411bbdd2f0170549bb4a9c78465e`; Git blob SHAs in Evidence Bundle are not file-byte SHA-256. Code activation later requires SHA-256 fingerprints. Research/CI and merge status must be observed and recorded, not asserted beforehand.
