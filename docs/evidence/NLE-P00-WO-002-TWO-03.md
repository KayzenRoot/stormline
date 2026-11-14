# Evidence Bundle — NLE-P00-WO-002-TWO-03 2D Animation Research

**State:** DRAFT DOCS ONLY, research PR/CI/AUDIT PENDING | **Research issue #153** | **Future coding issue #39 OPEN/BLOCKED**.  
**BASE main:** 8a104213bdd6d9d6fd88875d12a463200944975b | **Research branch:** docs/NLE-P00-WO-002-TWO-03-animation-research.

## Context and sources
- Canonical hierarchy confirmed: Checkpoint > Decisions Ledger / approved ADRs > Scope > DoD > Architecture > Requirements > AGENTS, catalog/registry and future coding packet #39. TWO-02 research #150 PR #151 and checkpoint #152 merged; all 80 code WOs BLOCKED, no executor_ready, TWO-01 code and AUDIO-owner export subsystem not built.
- Research sources reviewed: Godot 4.6 AnimationTree and 2D skeleton docs; DragonBonesCPP MIT license; Rive runtime MIT with branded free export splash vs paid clean export; Spine Nov 2026 custom runtime/editor license terms (not MIT); Lottie-web MIT and unsupported embedded audio/video/image sequence in its renderer; FFmpeg LGPLv2.1+ baseline, GPLv2+ when enabled and codec/source redistribution. No media/art files, binaries or vendor code installed.
- New research: rational/integer fixed-tick frame/sample time, CPU deterministic poses/flipbook, 2D bone/IK/skin, state transitions/blending, timeline/cutscene tracks, typed AUDIO-owner ack/export schedule, GPU/WebGL2 fallback, rights/security limits, STS optional prove-or-drop.
- Proposed 11 docs files: 8 new docs (architecture/matrix/ADR-0024/API/tests/benchmark/WO/EB) and 3 additive links in Architecture/Backlog/future blocked TWO-03 packet. Checkpoint and registry MUST remain unchanged in first research PR.

## Truthful evidence status (to fill from GitHub)
- Research PR number, final HEAD, docs-validation exact-head, security/Sonar checks: **PENDING**.
- Objective pt-BR audit, merge SHA and main readback: **PENDING**.
- **All 106 future acceptance tests NOT EXECUTED**, no output animation, audio sample measurement, cutscene export/video, sound file, shader/build/GPU capture, device/codec license test, event replay fuzz or CPU perf benchmark.
- Future risk ELEVATED for clip/event/physics authority, source asset and library/codec licensing, cross-platform audio-clock drift and renderer device loss. None of these risks passed runtime validation.
- ADR-0024 remains PROPOSED, future #39 OPEN/BLOCKED, implementation WOs not promoted; no "sample accurate audio export achieved" claim.

## Proposed checkpoint delta, NOT applied
After research PR approved and squash merged, separate SAME WO checkpoint PR may update ONLY registry TWO-03.research_status from RESEARCH_PENDING to RESEARCH_DOCUMENTED_ADR_PROPOSED, checkpoint/backlog/research WO/evidence to observed true SHA/CI, without changing 80 blocked code WOs, release_class UNDECIDED, approved_adr=null or future implementation #39 OPEN. Require independent exact-final-HEAD docs CI/audit/squash and main readback before TWO-04 next.
