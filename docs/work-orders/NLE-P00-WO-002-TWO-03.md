# Research Work Order — NLE-P00-WO-002-TWO-03

**2026-11-14 | Research issue #153 | Future implementation issue #39 OPEN/BLOCKED**  
**State:** APPROVED / MERGED FOR RESEARCH DOCS ONLY (PR #154) | **ADR-0024:** PROPOSED | **Context Lock BASE main:** 8a104213bdd6d9d6fd88875d12a463200944975b (TWO-02 research PR #151 and checkpoint PR #152 merged).  
**Risk:** LOW research docs; future ELEVATED audiovisual time accuracy, untrusted animation assets, authored events/gameplay authority, GPU animation buffers and codecs/export licensing.

## OBJECTIVE
Specify original C++-candidate 2D animation and sequencing architecture with variable frame-duration flipbooks, bone/slot/skin/mesh+IK plans, CPU deterministic pose evaluation, blends/state machines, typed cutscene tracks and exact rational frame/audio sample schedule. Future Zcode executor should be handed approved frozen contracts and be limited to implementing them. Catalog acceptance: reproducible timeline **actually exported with audio sync** on named platforms only after real A/V evidence, not achieved in P00.

## CONTEXT
Stormline P00 docs-only phase; Windows/Linux/macOS and Web with native 2D/2.5D/3D; AI-native Editor/CLI/MCP, free CI and solo objective audit, no public MVP. Catalog 80 code WOs all BLOCKED/executor_ready=false. TWO-01 is researched but its code and AUDIO export owner required for the real A/V proof are not implemented; future code #39 open. Research #153 is a separate documentation increment.

## SCOPE
- Rational/integer canonical time, fixed-step CPU replay and frame/audio sample tick converters; explicit jitter/rounding/seek/loop/reverse/rollback event idempotency.
- Versioned flipbook SpriteAssetId/AtlasRegion references, 2D skeleton/bone DAG/skin/slot and CPU mesh pose+bounded IK; optional GPU skinning with portable WebGL2 CPU fallback, additive/1D blend/state machine and optional 2D blend spaces after benchmark.
- Typed timeline clips/keys/curves, nested cutscene property tracks, camera/subtitle/audio/VFX/gameplay cue intents with owner acknowledgements and no arbitrary function/property/asset permissions.
- AUDIO-owner sample positioning and actual callback/latency receipts, offline frame/sample schedule for future authorized export module; FFmpeg codec/legal build optional and not bundled. Deterministic schedule does not claim encoded file or audible perfect synchronization.
- Tech/license matrix for DragonBonesCPP MIT, Godot MIT comparison, Rive runtime MIT/free splash vs paid export, Spine runtime custom editor-license requirements, Lottie-web MIT/feature gaps, FFmpeg LGPL/GPL config; all content/media/font rights separate and no binaries installed.
- Future 106 NOT EXECUTED tests, controlled audiovisual reference waveform/flash benchmark and STS PROVE-OR-DROP optional.
- 8 new research docs (architecture, matrix, ADR-0024, typed API, tests, benchmark, this WO, Evidence Bundle), 3 additive index/blocked packet links; research PR with exact-head CI/audit/squash then separate same-WO checkpoint PR.

## OUT OF SCOPE
No engine C++/shader/assets downloaded/copied, no animation editor, rig, game video, audio playback or real export implementation. No mandatory Spine/Rive subscription/branding, no third-party artifacts or nonfree codec, no event scripts/network authority/physics, no broad cleanup or TWO-04 early start. No paid CI, CodeRabbit, mandatory external reviewer, bypass, force-push or unauthorized execution.

## FILES / SOURCES TO READ
Canonical hierarchy: docs/11-checkpoint.md > docs/10-decisions-ledger.md + approved ADRs > docs/03-scope.md > docs/09-definition-of-done.md > docs/04-architecture.md > docs/02-requirements.md; then AGENTS.md, docs/product/module-catalog.md, docs/queue/implementation-registry.json, docs/queue/work-orders/TWO-03.md, TWO-01 Canvas API and TWO-02 tilemap research, DATA-02/03/04/05, GFX-02/03/05/07/08, AUDIO/WORLD/PHYS/NET/EDIT planned boundaries and all official references in technology matrix. Inspect main/issue/rules and exact PR diff. Concrete future C++ files/source ABI TBD when implementation gate approved.

## REQUIREMENTS
GOV-001..005; CAP-003/004/009/010/011/012/013/014/016 and NFR-001..005 and NLE-D013..020 as applicable. Future catalog acceptance "Timeline reproduzível e exportada com sincronismo áudio." Exact owner-approved hardware, maximum drift (samples or ms), frame pacing p95/p99, copyright and codec distribution/1.0 release class UNDECIDED.

## ARCHITECTURE RULES
No duplicate Canvas renderer (TWO-01), audio engine/clock (AUDIO), scene/PHYS authority, texture manager (GFX-05), RenderGraph/VRAM/fence (GFX-03), database/journal (DATA-04), asset cooker (DATA-05) or camera/GFX-07 post. Pure rational CPU evaluation; explicit fixed-tick event dispatch from correct owner with idempotent ack; clip/rig graph bounds; security caps and authoring rights. Do not pass third-party runtime structs into public SDK, do not assume FFmpeg or licensed Spine runtime.

## CONSTRAINTS
Docs-only LOW risk, no real CPU/GPU/AUDIO/codec tests claimed, solo free CI, all 80 future code WOs BLOCKED/executor_ready=false, #39 stays open, ADR-0024 PROPOSED, no automatic scope/class promotion. Independent approved AUDIO owner and exact 1.0 DoD required for actual export claim.

## ACCEPTANCE CRITERIA
- [ ] Versioned rational time/tick/frame/sample contract with checked overflow and explicit event seek/loop/reverse policies; timeline export plan versus real audio ACK distinction.
- [ ] Flipbooks/atlases, skeleton DAG and bounded CPU pose/IK, additive/1D blend machines, clip curves, nested cutscene tracks/markers and future WebGL2 fallback planned without duplicating owners.
- [ ] Multimedia and code licensing differentiates DragonBones MIT, Godot reference MIT, Rive MIT runtime vs free export splash, Spine custom runtime/editor requirement, Lottie MIT but feature limits, FFmpeg LGPL/GPL varying build and separate audio/art rights.
- [ ] 106 **FUTURE NOT EXECUTED** cases, repeatable A/V frame/sample alignment benchmark and STS prove-or-drop; no measured GPU/media/60fps claim.
- [ ] 11 docs-only research files (8 new, 3 links), exact final-head Docs Validation success, pt-BR objective architecture/DoD/license/security audit no known HIGH/CRITICAL and normal squash readback.
- [ ] Separate same-WO checkpoint PR with only TWO-03 research_status pending -> documented, all 80 coding WOs stay blocked, #39 open, ADR proposed; no TWO-04 research before checkpoint reviewed/merged.

## TESTS
Current documentation CI GitHub Actions docs-validation at exact final HEAD; supplementary Socket/SonarCloud when present. If a clone is available: python3 scripts/validate_docs.py, python3 scripts/validate_module_catalog.py, python3 scripts/validate_wo_registry.py and scripts/select_wo.py TWO-03 should refuse blocked code selection. 106 animation/event/audio/cross-platform/codec security test cases are FUTURE NOT RUN, no GPU screenshots or decoded mux output.

## DELIVERABLES
Research issue #153, 8 new docs, 3 links to existing Architecture/Backlog/blocked packet #39, evidence + BASE/HEAD, research PR/audit and separate checkpoint reconciliation PR/audit. No executable or media assets.

## REVIEW FORMAT
Pt-BR objective audit with BASE/main and exact HEAD, changed files, CI/security check run links, source fingerprint/decisions consistency, license and security risks, truthful 106 future tests, proposed Checkpoint Delta and verdict APPROVED / CORRECTION REQUIRED / BLOCKED. Never advance on HIGH/CRITICAL.

## STOP CONDITION
Stale Git canonical source, unsupported licensing or artificial synced-export claim, unexpected engine code/assets, invalid tested evidence, failing CI or HIGH/CRITICAL => corrections on same WO/PR and no next TWO-04. No force-push, bypass, paid CI or mandatory external human reviewer.

## CONTEXT LOCK
BASE main 8a104213bdd6d9d6fd88875d12a463200944975b. Git blob IDs (when captured) are NOT raw file SHA-256; future executor must capture SHA-256 from real source byte content and rebase after any relevant approved DoD/Scope/ADR change. No activated code packet in this phase.

## Verified research merge receipt
Research BASE main 8a104213bdd6d9d6fd88875d12a463200944975b, audited final HEAD 9e3d8bc369465311a9bc18602a203cf2c1acaec8; [Docs Validation #43630601311](https://github.com/KayzenRoot/stormline/actions/runs/43630601311) SUCCESS at final exact HEAD, Socket Security and SonarCloud PASS, pt-BR objective audit APPROVED exclusively docs, no HIGH/CRITICAL in scope. Normal squash merged PR #154 into main 28ade29693e407e781946769b5f559e0ec1d3d9d. This checkpoint PR requires its own exact HEAD CI/audit, no automatic code approval. All 106 prospective tests NOT EXECUTED, ADR-0024 PROPOSED and #39 still OPEN/BLOCKED.
