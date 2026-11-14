# Evidence Bundle — NLE-P00-WO-002-TWO-03 2D Animation Research

**State:** RESEARCH DOCS APPROVED / MERGED; CHECKPOINT PR PENDING INDEPENDENT EXACT-HEAD CI/AUDIT | **Research issue #153** | **Future coding issue #39 OPEN/BLOCKED**.  
**BASE main:** 8a104213bdd6d9d6fd88875d12a463200944975b | **Research branch:** docs/NLE-P00-WO-002-TWO-03-animation-research.

## Context and sources
- Canonical hierarchy confirmed: Checkpoint > Decisions Ledger / approved ADRs > Scope > DoD > Architecture > Requirements > AGENTS, catalog/registry and future coding packet #39. TWO-02 research #150 PR #151 and checkpoint #152 merged; all 80 code WOs BLOCKED, no executor_ready, TWO-01 code and AUDIO-owner export subsystem not built.
- Research sources reviewed: Godot 4.6 AnimationTree and 2D skeleton docs; DragonBonesCPP MIT license; Rive runtime MIT with branded free export splash vs paid clean export; Spine Nov 2026 custom runtime/editor license terms (not MIT); Lottie-web MIT and unsupported embedded audio/video/image sequence in its renderer; FFmpeg LGPLv2.1+ baseline, GPLv2+ when enabled and codec/source redistribution. No media/art files, binaries or vendor code installed.
- New research: rational/integer fixed-tick frame/sample time, CPU deterministic poses/flipbook, 2D bone/IK/skin, state transitions/blending, timeline/cutscene tracks, typed AUDIO-owner ack/export schedule, GPU/WebGL2 fallback, rights/security limits, STS optional prove-or-drop.
- Proposed 11 docs files: 8 new docs (architecture/matrix/ADR-0024/API/tests/benchmark/WO/EB) and 3 additive links in Architecture/Backlog/future blocked TWO-03 packet. Checkpoint and registry MUST remain unchanged in first research PR.

## Canonical Git object fingerprints at the BASE (Git blob OIDs, NOT raw file SHA-256)
- `docs/11-checkpoint.md`: `8c43085a057d544be86a09564e066c522c097368`
- `docs/10-decisions-ledger.md`: `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`
- `docs/03-scope.md`: `4ef605c74632ece080b2650e37dd83a415b63310`
- `docs/09-definition-of-done.md`: `160b3054db9ea1961308934b401488b838d24c3e`
- `docs/04-architecture.md`: `9190948b814153e1d7bf8f60af62a3ef7fcd8a61`
- `docs/queue/work-orders/TWO-03.md`: `fd4e837d5f62308a54caabb4676251d236e45f6e`
These are observed Git blob SHA-1 object IDs, **not SHA-256 of raw file bytes**. Future executor must compute true SHA-256 and re-lock all changed canonical sources before code.

## Truthful evidence status (to fill from GitHub)
- [Research PR #154](https://github.com/KayzenRoot/stormline/pull/154), initial HEAD `77b7e332542e78a16a665b4b70bdaf211e05d10e`, [Docs Validation #43630552127](https://github.com/KayzenRoot/stormline/actions/runs/43630552127) **SUCCESS at INITIAL exact HEAD**; initial Socket Security Project Report SUCCESS. This Evidence edit changes HEAD; a NEW final exact-head CI is required before audit/merge.
- [Research PR #154](https://github.com/KayzenRoot/stormline/pull/154) **APPROVED documentation-only**, normal squash merged 28ade29693e407e781946769b5f559e0ec1d3d9d after final HEAD 9e3d8bc369465311a9bc18602a203cf2c1acaec8 and [Docs Validation #43630601311](https://github.com/KayzenRoot/stormline/actions/runs/43630601311) SUCCESS; Socket Security and SonarCloud SUCCESS, objective pt-BR review no known HIGH/CRITICAL documentary defect. Checkpoint still requires separate CI and audit.
- **All 106 future acceptance tests NOT EXECUTED**, no output animation, audio sample measurement, cutscene export/video, sound file, shader/build/GPU capture, device/codec license test, event replay fuzz or CPU perf benchmark.
- Future risk ELEVATED for clip/event/physics authority, source asset and library/codec licensing, cross-platform audio-clock drift and renderer device loss. None of these risks passed runtime validation.
- ADR-0024 remains PROPOSED, future #39 OPEN/BLOCKED, implementation WOs not promoted; no "sample accurate audio export achieved" claim.

## Proposed checkpoint delta, NOT applied
After research PR approved and squash merged, separate SAME WO checkpoint PR may update ONLY registry TWO-03.research_status from RESEARCH_PENDING to RESEARCH_DOCUMENTED_ADR_PROPOSED, checkpoint/backlog/research WO/evidence to observed true SHA/CI, without changing 80 blocked code WOs, release_class UNDECIDED, approved_adr=null or future implementation #39 OPEN. Require independent exact-final-HEAD docs CI/audit/squash and main readback before TWO-04 next.

## Checkpoint Delta exact semantics, this separate same-WO PR
Only TWO-03.research_status changes RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED; do not change work_order_status/risk/release_class/approved_adr/executor_ready on any of 80 coding WOs. Code #39 OPEN/BLOCKED, ADR-0024 PROPOSED. All 106 CPU/GPU/native/Web/audio-export tests NOT EXECUTED and no playable animation/rendered film. Separate checkpoint PR's own exact-final-HEAD GitHub Docs Validation + objective audit required before squash/readback and next TWO-04.
