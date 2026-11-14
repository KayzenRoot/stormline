# Research Work Order — NLE-P00-WO-002-WORLD-04

**2026-11-14 | Research issue #168 | Future coding #44 OPEN/BLOCKED**  
**State:** RESEARCH IN PROGRESS / DOCS ONLY; **ADR-0029 PROPOSED**; **BASE main:** d6858410a2b5770400e1c6b816db5620264f48b8 (WORLD-03 research PR #166 + checkpoint PR #167 merged).
**Risk:** LOW documentation, future ELEVATED GPU/VRAM and visual fidelity, terrain→PHYS consistency, DATA-04 source mutation, shader/asset security, NET authority and unrecoverable changes.

## OBJECTIVE
Specify first-class original authorable terrain and visual environment data and contracts for 3D multibiome scenes: stable heightfield tiles with distinct cave/overhang mesh path, seam-free LOD hints, splat/material source, vegetation/biome authored placement, ocean/river/coast visual surfaces, atmosphere/sky/day-night/weather visual profiles and reversible layer edits. Preserve exact subsystem owners (WORLD-03 streaming, GFX-04 geometry/visibility, GFX-05 PBR/textures, GFX-06 lights/shadows/sky/fog, GFX-07 HDR/post, GFX-08 weather VFX, WORLD-05 procedural generation, PHYS/GAME/NET authoritative simulation) and specify original benchmark/acceptance gates, without coding.

## CONTEXT
Stormline P00 public repository with Windows/Linux/macOS editor+export, headless and Web reduced tiers, AI-native Editor/CLI/MCP, no mandatory paid CI/reviewers or CodeRabbit. Git registry baseline **25/80 documented technical researches, 55 pending** including historical CORE-04 gap; **all 80 coding WOs BLOCKED/executor_ready=false**, no runnable engine, no actual visual quality or FPS. Mandatory future code dependencies WORLD-03 + GFX-04 are not implemented, and DATA/GFX/PHYS owner contracts must be proven. Future coding #44 separate and OPEN/BLOCKED.

## SCOPE
- Original versioned TerrainAsset/PatchId/HeightTile/Grid schema in checked signed world coordinates, source collision height vs visual geomorph, stable patch border rules and explicit mesh asset path for caves/cliffs/overhang. DATA-04 reversible authored strokes/layers (manual overrides preserved after cook), AssetId and rights, source change CAS and propagation to WORLD-03 cells and PHYS/GFX readiness.
- Quadtree/stitched/skirt/geomorph tile renderer GFX-04 portable baseline compared to optional GPU geometry clipmap plus feature-gated tessellation/mesh shader; seam/normal/motion/LOD/VRAM and WebGL2/WebGPU/backend capability proof, without duplicating shader compiler or GPU allocator.
- Splats with normalized finite mask channels, triplanar/linear PBR layer source linked to GFX-05, optional virtual texturing owned GFX-05/GFX-03/DATA-05, no independent texture residency engine.
- Vegetation manual cluster placement/biome source, stable IDs, GFX-04 instancing/culling, GFX-06 shadow, GFX-07 temporal reactive, visual wind versus PHYS collider and GAME authority; generated spawn/biome/erosion graph WORLD-05 only.
- Water authored body/shores and cheap visual waves with GFX-05/07 reflection/refraction limitations; optional FFT/spectral only after capability+rights benchmark, PHYS/NET gameplay buoyancy/wetness not inferred from shaders.
- Environment visual profile and typed weather intents, time-of-day/sky/cloud/fog/rain/wind with owner CORE/GAME/NET authoritative clock/weather, GFX-06 physical atmosphere and light, GFX-07 HDR output/temporal, GFX-08 particles and AUDIO.
- Technology/rights analysis for GPU Gems 2 clipmaps public academic reference, Terrain3D MIT Godot plugin reference, meshoptimizer MIT optional GFX-04 adapter, Bruneton scattering BSD optional GFX-06/07, Godot 4.6 core MIT environment reference, Unreal Landscape proprietary reference, Khronos glTF instancing public spec. No dependency or assets adopted.
- Research ADR-0029 PROPOSED, typed semantic API and error matrix, **148 FUTURE/NOT EXECUTED tests**, original clean-room biome quality/performance benchmark, SABE optional PROVE-OR-DROP, this WO and Evidence Bundle, additive Architecture/Backlog/blocked coding packet links; 11 docs-only research PR + separate same-WO checkpoint PR with verified exact HEAD CI/audits.

## OUT OF SCOPE
No C++ terrain mesh/shader renderer/physics/NET, actual scene asset, coastline/sky image, 3D model, map, baked texture, deployed Editor/CLI/MCP server, import/source writer, executable benchmark, performance claim or GPU feature certification. No forced Unreal/Godot/Terrain3D/Bruneton/meshoptimizer SDK, no copied proprietary textures/samples, no automatic terrain procedural generator WORLD-05, no second GFX-04 renderer/GFX-05 material system/PHYS collision authority, no unrelated CORE-04 research closure, no WORLD-05 research before checkpoint reconciled, no paid CI/CodeRabbit/reviewer mandate or force-push/bypass.

## FILES/SOURCES TO READ
Canonical Source Hierarchy: docs/11-checkpoint.md > docs/10-decisions-ledger.md/APPROVED ADRs > docs/03-scope.md > docs/09-definition-of-done.md > docs/04-architecture.md > docs/02-requirements.md; then AGENTS.md, docs/product/module-catalog.md, docs/queue/implementation-registry.json, docs/queue/work-orders/WORLD-04.md, WORLD-03 spatial and GFX-04 geometry/visibility/LOD, GFX-05 material, GFX-06 light, GFX-07 color/HDR, GFX-08 VFX, DATA-02/03/04/05, WORLD-01/02 source IDs, WORLD-05 future source ownership, CORE-05/06, PHYS/NET/AUDIO contracts. Primary official references and license pages in technology matrix. Future code file paths TBD until 1.0 DoD, never guessed.

## REQUIREMENTS
GOV-001..005, NLE-D001..020 only as relevant and OWNER-APPROVED in ledger, CAP-001/004/005/008/009/010/011/012/013/014/016 and NFR-001..005 where catalog applies. Target catalog acceptance **"Benchmark de travessia e render de biomas 3D originais"** not achieved by research. Approved numerical quality error, frame p95/p99, texture/memory/collider budgets, target hardware/biome fixture and release 1.0 scope remain UNDECIDED.

## ARCHITECTURE RULES
WORLD-04 authored geometry/environment profiles and render/PHYS intents only. DATA-04 owns source revision/journal/undo, WORLD-03 cell residency, GFX-04 final mesh/LOD/visibility, GFX-05 texture/PBR, GFX-06 sky/fog/light/shadow, GFX-07 color/temporal, GFX-08 precipitation VFX, PHYS actual collision/buoyancy, NET/GAME authoritative weather, WORLD-05 procedural noise. Never mark a streamed terrain patch playable until collider source revision ACK; never treat heightfield as all-cave topology; shader wind/water not game truth; never overwrite manual layer edit with recook.

## CONSTRAINTS
LOW-risk docs-only, future ELEVATED. Free exact final HEAD Docs Validation and available Socket/SonarCloud, solo objective pt-BR review. All 80 implementation WOs `BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`, zero executor_ready, approved_adr=null/release UNDECIDED and code #44 OPEN. ADR-0029 PROPOSED. Historical CORE-04 research gap unchanged. **148 future tests NOT EXECUTED**. No actual heightfield, water, AI/weather, native/Web build, GPU/PHYS test/benchmark or claimed quality.

## ACCEPTANCE CRITERIA
- [ ] Versioned original typed terrain/patch/height tile/biome/vegetation/water/environment/visual weather authoring model, stable source keys and checked signed global units plus explicitly separate cave meshes.
- [ ] Compare tile/quadtree edge stitching/geomorph vs GPU clipmaps/optional mesh shader on equal original scene; GFX-04 owner/feature probe, no false WebGL2 compute/mesh promise; visual seam and physics collider source explicit.
- [ ] Normalized/linear splat and PBR weight/normal space ownership GFX-05, rights-checked textures, virtual residency GFX-05 not duplicated; GFX-06 shadows/sky/fog and GFX-07 HDR/temporal integration and weather GPU VFX GFX-08 ownership.
- [ ] Water visual surface with shoreline and reflection/SSR limitations, cheap baseline and optional spectral prove gate, PHYS/GAME/NET authority separated; biome art edits preserved after WORLD-05 generator proposal and DATA-04 undo/redo source journal.
- [ ] Godot Terrain3D and meshoptimizer MIT, Bruneton atmosphere BSD, Unreal proprietary reference, GPU Gems historic paper and Khronos public instancing rights/versions clearly labeled and no installed vendor code/asset.
- [ ] **148 FUTURE NOT EXECUTED** test matrix and original multi-biome p95/p99 benchmark protocol for high-end/low-Web/headless and authoring, source rights, security/fault and optional SABE PROVE-OR-DROP. No old published FPS or untested superiority claims.
- [ ] Exactly 11 `docs/` files in research PR, 8 new + 3 additive; exact final HEAD free Docs Validation SUCCESS and available Socket/SonarCloud, pt-BR objective audit 0 known HIGH/CRITICAL, normal squash and main readback.
- [ ] Separate same WO checkpoint PR changes ONLY WORLD-04.research_status RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED; code #44 and all 80 code WOs remain BLOCKED, ADR-0029 PROPOSED, CORE-04 research gap pending. Own exact final HEAD CI/audit/squash/main readback before WORLD-05 research.

## TESTS
Only GitHub free `docs-validation` exact final head and any available Socket/SonarCloud in P00. Local if checkout available: `python3 scripts/validate_docs.py`, `python3 scripts/validate_module_catalog.py`, `python3 scripts/validate_wo_registry.py`, `python3 scripts/select_wo.py WORLD-04` expected reject coding branch. **All 148 terrain/environment/CPU/GPU/PHYS/source/native/Web/security/bench tests FUTURE NOT RUN**.

## DELIVERABLES
8 new docs architecture, tech+license, ADR-0029, typed API, 148 case matrix, biome benchmark protocol, research WO, Evidence Bundle; 3 additive Architecture/Backlog/blocked WORLD-04 implementation packet references; research #168, research PR exact HEAD CI/objective audit and separate checkpoint reconciliation PR/CI/audit. No engine code or deploy.

## REVIEW FORMAT
Pt-BR objective BASE/HEAD SHA and source fingerprints, changed file inventory, exact final HEAD CI run and security, source architecture/DoD/copyright/risks, known 148 NOT RUN future scenarios, risks and proposed Checkpoint Delta. Verdict APPROVED/CORRECTION REQUIRED/BLOCKED; no outside human reviewer mandate but objective independent evidence, correct same WO/PR if needed.

## STOP CONDITION
Changed main or canonical fingerprints, unlicensed imported assets, failed Docs Validation or security checks, unknown HIGH/CRITICAL, false GPU/scene claim or unauthorized source/registry/code changes => CORRECTION REQUIRED/BLOCKED, no WORLD-05 until approved checkpoint. No force push, required paid service, CodeRabbit, review bypass or unrelated cleanup.

## CONTEXT LOCK
Research BASE Git main d6858410a2b5770400e1c6b816db5620264f48b8. Git SHA-1 blob hashes are NOT raw byte SHA-256. Future Zcode implementation requires approved Scope/DoD and ADR, observed WORLD-03+GFX-04 implementation, source code file inventory/ABI, actual SHA-256 byte fingerprints and runtime tests with Evidence Bundle.
