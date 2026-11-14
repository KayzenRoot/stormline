# Research Work Order — NLE-P00-WO-002-TWO-04

**Date:** 2026-11-14 | **Research issue #156** | **Future code issue #40 OPEN/BLOCKED**  
**State:** APPROVED / MERGED FOR RESEARCH DOCS ONLY (PR #157) | **ADR-0025:** PROPOSED | **BASE main:** 73f4826354724ce72a037411eba3dc86174638c3 (TWO-03 research PR #154 and checkpoint PR #155 integrated).  
**Risk:** LOW documentation only; future ELEVATED depth buffer/VRAM, GPU attachments, raster alpha, temporal history, lighting/large-world camera and unsafe authoring.

## OBJECTIVE
Specify first-class original 2.5D hybrid composition allowing 2D sprites/Canvas overlays, 3D world geometry, 2D lighting normals/shadow and VFX to coexist with explicit orthographic/perspective projection, occlusion/alpha rules and pixel-art/UI sharpness. Make exact, security-reviewed contracts/benchmarks for future Zcode implementing only approved code. Catalog acceptance "Projeto mistura sprites e mundo 3D preservando ordem/iluminação" is FUTURE, not proven by design research.

## CONTEXT
Stormline P00 phase DOCUMENTATION ONLY; 80 code WOs BLOCKED and 0 executor-ready, no engine executable, game, GPU binary, demo or real benchmark. Mandatory TWO-01 and GFX-04 code dependencies have only research proposals, not implemented. Research #156 distinct from stable future implementation issue #40. Owner wants original professional 2D/2.5D/3D with Windows/Linux/macOS+Web and AI-native Editor/CLI/MCP at no mandatory paid CI/review.

## SCOPE
- Original typed hybrid mode for SHARED_DEPTH_WORLD, ORDERED_CANVAS_OVERLAY and ISOLATED_SUBVIEW with known limitations and explicit author intent. 2D px↔3D meters/world↔view projection with ortho/perspective, correct glTF imported coordinates, billboard ground-plane and camera-facing orientation, pixel-art/HiDPI/large-origin rebasing.
- Depth/stencil/alpha/transparent 2D+3D order semantics, shared GFX-03 RenderGraph/color/depth/proxy resource lifetimes, stable TWO-01 Canvas layer painter order, GFX-04 3D mesh visibility/culling, GFX-05 alpha/PBR, GFX-06 normal/lit sprites and shadows, GFX-07 HDR/AA/temporal and unjittered UI, GFX-08 VFX depth and reactive masks; WebGL2 non-compute fallback.
- Explicit subviewport render-to-texture and depth-unavailable/camera mismatch constraints, recursion and VRAM budgets, fault/recovery/device loss, safe scene edit staged DATA-04 transactions via Editor/CLI/MCP; no duplicate 2D renderer, physics/collision or shader compiler.
- Tech analysis Godot CanvasItem y/Z-sort/SubViewport MIT design reference, Unity 6 Sort-as-2D depth warning/proprietary reference, WebGPU W3C depth attachment formats, Khronos glTF 2.0 units and McGuire/Bavoil weighted OIT approximation (paper not source code license). No third-party code/art copied.
- ADR-0025 PROPOSED, architecture/technology matrix/typed API, 109 FUTURE NOT EXECUTED acceptance cases and original licensed clean-room benchmark protocol, optional SDOI prove-or-drop; research Work Order/Evidence, 3 additive Architecture/Backlog/future blocked packet links.
- One docs-only research PR (11 files) exact final HEAD CI/objective pt-BR audit/normal squash+main readback; separate same-WO checkpoint reconciliation PR with exact final HEAD CI/audit and only TWO-04 research_status changed.

## OUT OF SCOPE
No C++/shader/renderer implementation, GPU render or hardware test, HDR display calibration, performance superiority, paid SDK/vendor assets, third-party game art, full portal/stereo/AR/VR, 3D UI interactions/raycast, physics/collision, changing previous module approved research, broad unrelated cleanup, earlier WORLD-01 research, mandatory outside reviewer, CodeRabbit, paid CI, bypass, force push or unauthorized release.

## FILES / SOURCES TO READ
Canonical order: docs/11-checkpoint.md > docs/10-decisions-ledger.md + approved ADRs > docs/03-scope.md > docs/09-definition-of-done.md > docs/04-architecture.md > docs/02-requirements.md; then AGENTS.md, docs/product/module-catalog.md, docs/queue/implementation-registry.json, docs/queue/work-orders/TWO-04.md, architecture and typed APIs TWO-01/02/03, GFX-01..08 (esp. GFX-03, GFX-04, GFX-05, GFX-06 and GFX-07), DATA-03/04/05 and WORLD/PHYS safety boundaries. Also W3C WebGPU, Khronos glTF 2.0, Godot 4.6, Unity 6 and JCGT research public sources listed in matrix. Future real source file paths TBD, never fabricate.

## REQUIREMENTS
GOV-001..005, relevant CAP-001/002/004/005/008/009/010/011/012/013/014/016 and NFR-001..005, owner NLE-D013..020. 1.0 release class, exact scene thresholds and DoD for hardware/quality/occlusion still UNDECIDED; 3D+2D order/lighting is catalog candidate acceptance and needs real demonstration later.

## ARCHITECTURE RULES
GFX-01/03 own device/render graph/barriers/VRAM/depth, GFX-04 mesh geometry, GFX-05 material/alpha/lighting context, GFX-06 light/shadows, GFX-07 camera/color/temporal/post, GFX-08 VFX, TWO-01 Canvas, DATA-04 saved scene/undo and PHYS/WORLD gameplay authority. No new renderer, backend, light solver, shader compiler, physics authority or datastore. Shared depth requires compatible camera/projection and format; overlay painter order does not imply depth; subview color not direct parent depth. Alpha blended world sprites must not silently depth-write; OIT only approximate. No unbounded subviews or cross-project source.

## CONSTRAINTS
LOW docs, future ELEVATED code; only GitHub free Docs Validation and existing security checks. 109 scenarios future NOT EXECUTED, no engine, FPS, HDR or GPU quality proof. 80 future implementation WOs remain BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS/executor_ready=false; #40 OPEN/BLOCKED, ADR-0025 PROPOSED, release class UNDECIDED.

## ACCEPTANCE CRITERIA
- [ ] Three explicit hybrid composition modes with depth/view compatibility and color/output ownership, correct alpha/occlusion and stable overlay painter order, no camera “depth magic.”
- [ ] Ortho/perspective bridge, billboards/world-plane anchors, glTF/source axis conversion and 2D pixel/DPI, mirrored normals and large-world origin, camera cut/rebase invalidation.
- [ ] Lighting/shadow/proxy, GFX-07 HDR/temporal flags, WebGL2 fallback and GFX-03 attachment lifetime/budget/subview cycle safety; 3D/2D source and physics owner boundaries.
- [ ] License/tech research labels Godot MIT and Unity proprietary references only, W3C WebGPU/Khronos glTF official standards and weighted OIT approximation without copied source, plus no third-party art.
- [ ] 109 acceptance tests FUTURE/NOT EXECUTED and reproducible original benchmark, optional SDOI prove-or-drop and security authoring quotas, no false superiority/FPS claim.
- [ ] Research docs PR exactly 11 files only docs, exact final-head free CI SUCCESS and pt-BR objective audit no known HIGH/CRITICAL, normal squash and main readback.
- [ ] Separate checkpoint PR same WO modifies only TWO-04.research_status in registry, all 80 coding WOs still BLOCKED, code #40 OPEN and ADR PROPOSED. Only then next WORLD-01 research.

## TESTS
Current Docs Validation via GitHub Actions on exact final HEAD. Local if checkout available: python3 scripts/validate_docs.py, python3 scripts/validate_module_catalog.py, python3 scripts/validate_wo_registry.py, python3 scripts/select_wo.py TWO-04 expected reject blocked. 109 GPU/depth/alpha/camera/lighting/viewport/VRAM/native/Web/security/bench tests are FUTURE NOT RUN, no actual scene or benchmark.

## DELIVERABLES
8 new documents (architecture, technology/licenses, ADR-0025 PROPOSED, typed API, test matrix, benchmark, research Work Order, Evidence Bundle), 3 additive changes to Architecture/Backlog/future blocked packet, research issue #156, research PR with audit+exact-head CI and separate same-WO checkpoint PR+audit, readback and issue closure. No engine code.

## REVIEW FORMAT
Pt-BR objective audit with BASE+HEAD SHA, exact CI run, changed file inventory and registry diff, verified material scope, security/supply chain/ownership, known 109 not-run tests, critical risks and proposed checkpoint delta; verdict APPROVED/CORRECTION REQUIRED/BLOCKED. No review theatre, no human reviewer mandate.

## STOP CONDITION
Stale main/canonical fingerprint, failing CI/unknown required status, unexpected code/assets/source change, HIGH/CRITICAL defect, unlicensed materials or false GPU/quality claims => stop with Correction Delta in same WO/PR. Never start WORLD-01 before checkpoint audit/merge. No force push, bypass or paid CI.

## CONTEXT LOCK
Research BASE main 73f4826354724ce72a037411eba3dc86174638c3. Git blob OID is not raw file SHA-256. Before future runtime work, compute SHA-256 bytes, implement prerequisite TWO-01/GFX-04, freeze exact ABI/files/DoD and revalidate canonical source SHA after all approved changes.

## Verified research receipts
PR #157 BASE main 73f4826354724ce72a037411eba3dc86174638c3, audited final HEAD b9c71e084f95d9aa9b8f371b5f35b85cd69746cb, [Docs Validation #43633197318](https://github.com/KayzenRoot/stormline/actions/runs/43633197318) SUCCESS at exact final HEAD, Socket Security/SonarCloud PASS, pt-BR documentary objective audit APPROVED only docs (11 files, no known HIGH/CRITICAL), normal squash merged main 52d7bb881ab7cd0a323f51a6bf443f3448c6978a. Checkpoint is a separate same-WO PR with independent exact-final-HEAD CI/audit and main readback. All 109 graphics/GPU/native/Web/VRAM tests FUTURE NOT EXECUTED, ADR-0025 PROPOSED, future code #40 OPEN/BLOCKED.
