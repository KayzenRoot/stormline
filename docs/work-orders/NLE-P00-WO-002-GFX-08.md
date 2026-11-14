# Research Work Order — NLE-P00-WO-002-GFX-08

**Research issue #144 | Future implementation #36 BLOCKED** | Date 2026-11-14  
**State:** RESEARCH IN PROGRESS, DOCS ONLY | **ADR-0021:** PROPOSED | **BASE main:** `729f111d30fe927107f42fe6e4b951d17f357e10` (GFX-07 research PR #142 and checkpoint PR #143 merged).  
**Risk:** LOW documentation; future ELEVATED GPU memory/synchronization, untrusted assets/graph and visual collision/authority isolation.

## OBJECTIVE
Specify Stormline-owned, versioned, secure and visually ambitious 2D/2.5D/3D VFX graph, portable hybrid particle engine and ARPG-grade ribbons/volumes/mesh/spells; guarantee planned resource bounds and graceful native/Web fallback, prove any quality superiority only by actual future benchmarks. Leave detailed architecture contracts to Zcode, not product/SDK invention.

## CONTEXT
P00 documentation phase. GFX-03/05/06/07 research is documented, **code implementations not integrated**. 80 implementation WOs remain BLOCKED, #36 NOT EXECUTOR READY. OWNER-DIRECTED Windows/Linux/macOS, Web, 2D/2.5D and 3D, no public MVP, AI-native Editor/CLI/MCP, free public CI/solo objective audit.

## SCOPE
- Graph DAG with typed node families and constrained subemitter loops, stable IDs, DATA-04 revisions and DAG validation; CPU fixed step reference and optional GPU SoA compute.
- Bounded spawn/lifetime/pooling/ribbon/trail/mesh/flipbook/sprite, optional depth-sort/OIT and alpha/overdraw; compare AMD GPUOpen Parallel Sort MIT and Effekseer runtime MIT optional interoperability with transitive backend legal gates.
- GFX-06 bounded particle light requests and VFX fog density (not a second light/volumetric integrator); GFX-07 HDR reactive masks/velocity and reduced-flash; cosmetic non-authoritative visual collision.
- Security/scalability, low-tier WebGL2 CPU, WebGPU actual compute feature gates, Metal native fallback, Win/Linux native, hardware budgets/quality receipts.
- ADR-0021 PROPOSED, architecture, matrix, semantic API, 78 future tests, research benchmark, Work Order/Evidence Bundle, index links and existing blocked #36 packet. SVAG experimental prove-or-drop.

## OUT OF SCOPE
C++/shader/driver/device code, vendor SDK downloading, GPU binary/visual assets/render demo, sound/gameplay/net authority, editing unrelated modules, GFX-09/TWO-01 research before checkpoint, external paid CI/CodeRabbit/mandatory human reviewer, bypass/force push, commercial launch or claim proven 1m particles/benchmark superiority.

## FILES / SOURCES TO READ
Canonical: `docs/11-checkpoint.md` > `docs/10-decisions-ledger.md`+approved ADRs > `docs/03-scope.md` > `docs/09-definition-of-done.md` > `docs/04-architecture.md` > `docs/02-requirements.md`; then AGENTS.md, catalog, registry, GFX-02/03/04/05/06/07/DATA-02/03/04/05 contracts, existing `docs/queue/work-orders/GFX-08.md` and official sources in research matrix. Check Git base/tree/issue/PR before writing.

## REQUIREMENTS
GOV-001..005, CAP-001/002/004/005/008/009/010/011/012/013/014/016 and NFR-001..005, NLE-D013..020 as applicable. Catalog future acceptance: ARPG stress visuals, CPU/GPU p95/p99, VRAM, tier and quality comparisons. Exact max particles, throughput, GPU hardware minimum, release class, version/SBOM and benchmarks **UNDECIDED**.

## ARCHITECTURE RULES
GFX-03 RenderGraph/VRAM/fences authoritative, GFX-02 shader compile, GFX-05 texture/alpha, GFX-06 lights/volumetric solver, GFX-07 output/AA, DATA-04/05 asset edit/cook, WORLD/gameplay authority. VFX may only declare bounded plans, no direct GPU resource ownership or arbitrary scripts. WebGL2/2D portable baseline must work without compute. Correct error/fallback and clear performance data provenance.

## CONSTRAINTS
Docs-only LOW; future ELEVATED and requires real fuzz/device/platform tests. All 80 implementation packets `BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`, `executor_ready=false`, issue #36 open, ADR-0021 PROPOSED. Do not infer code approval from research integration.

## ACCEPTANCE CRITERIA
- [ ] VFX graph typed DAG/schema, bounded child events and source rights, CPU/GPU simulation tiers and correct non-authoritative visual collision.
- [ ] Transparency/sorting/OIT approximation, ribbons/trails/2D/2.5D/3D, HDR/alpha/reactive mask, volumetric/light owner boundaries and device loss/fences contract.
- [ ] Technology/licensing review includes Effekseer runtime MIT with backend transitive gate, GPUOpen Parallel Sort MIT DX12/Vulkan, OpenVDB upstream Apache2 but asset/codec caveats, Niagara/Godot as references only.
- [ ] 78 future NOT EXECUTED cases, clean-room ARPG same-scene benchmarking, SVAG optional prove-or-drop with no claimed wins.
- [ ] Typed Editor/CLI/MCP revision+capability safe commands, no untrusted path/bytecode or unlimited emitter creation.
- [ ] Final research PR exact-head docs-validation SUCCESS, 11 docs-only files, objective pt-BR audit no HIGH/CRITICAL and normal squash merge/main readback.
- [ ] Separate same-WO checkpoint PR after research merge, only GFX-08 research_status changes, 80 code WOs still blocked, no next module before checkpoint approved.

## TESTS
Docs via free GitHub Actions `docs-validation` at exact HEAD. Local scripts if checkout: `python3 scripts/validate_docs.py`, `python3 scripts/validate_module_catalog.py`, `python3 scripts/validate_wo_registry.py`, `python3 scripts/select_wo.py GFX-08` expected refuse blocked. All 78 GPU/CPU/color/visual tests **FUTURE NOT EXECUTED**.

## DELIVERABLES
8 research documents (architecture, technology/license matrix, ADR-0021, semantic API, test matrix, benchmark protocol, this WO, Evidence Bundle), 3 index/blocked packet link edits, research PR then separately checkpoint PR. No GPU/software deliverable.

## REVIEW FORMAT
Pt-BR audit of BASE/HEAD and diff, exact docs CI/security checks, architecture/law/permissions/budget/temporal risks, 78 future tests truth, proposed checkpoint delta, severity/no HIGH/CRITICAL and explicit APPROVED / CORRECTION REQUIRED / BLOCKED.

## STOP CONDITION
Any canonical stale base, unlicensed source, missing links/failing CI, unauthorized code or claims of hardware proof or HIGH/CRITICAL defects requires correction on same WO/PR; no activation #36 or next TWO-01 until audited checkpoint.

## CONTEXT LOCK
BASE main `729f111d30fe927107f42fe6e4b951d17f357e10`; Git blob hashes used for documentation fingerprints are **not** raw SHA-256 file checksums; future code requires SHA-256 source fingerprints, approved contracts/versions and integrated predecessors.
