# NLE-P00-WO-002-PLAT-02 — Linux Desktop Target P00 Research Work Order

**2026-11-15 | P00 DOCUMENTARY RESEARCH ONLY / NOT IMPLEMENTED | research [#321](https://github.com/KayzenRoot/stormline/issues/321) | NLE-P00-WO-002-PLAT-02 | future code [#85](https://github.com/KayzenRoot/stormline/issues/85) OPEN/BLOCKED | BASE 6271e5482e02fbc575d401feb2d72a24eaff2854.** Catalog 67/80; formal dependencies **GFX-01 + GAME-01 ONLY** (ADR-0014/0042 PROPOSED), CORE-01 transitive; 66/80 research documented at source, 14 pending, all 80 coding WOs BLOCKED; engine_implemented=false; engine license NLE-D009 OPEN.


**Research #321 OPEN; future code #85 OPEN/BLOCKED.** Risk P00 documentation LOW; future native runtime/device/sandbox/pkg ELEVATED or HIGH_ASSURANCE depending scope. Formal deps GFX-01+GAME-01 ONLY.

## OBJECTIVE
Deliver source-verified Linux desktop target research design with typed boundary across SDL3 Wayland/X11 compositor, Vulkan/GPU loader, GAME-01 input, AUD audio, XDG filesystem/portals, ELF security/ABI and package candidates, objective future real Linux hardware Editor + exported Game smoke, 128 future acceptance tests. Catalog acceptance: "Build e smoke test em Linux definido." Never claim runnable code.

## CONTEXT / SOURCE CHECK
Live main matches BASE **6271e5482e02fbc575d401feb2d72a24eaff2854** and is a factual PLAT-01 historical closeout; no open PRs at start. Main registry 80 modules: 66 documented research, 14 pending, 80/80 BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, executor_ready=0, approved_adr=0, release_class UNDECIDED for all, engine=false. PLAT-02 is order 67, deps GFX-01+GAME-01 only, coding issue #85 blocked. Both prior ADR-0014/0042 remain PROPOSED. CORE-01 SDL3 bridge is *transitive*, no formal edge. NLE-D009 engine license OPEN; NLE-D013 no public MVP; NLE-D017 native Linux Editor+game mandatory. Research #321 owns documentation only.

## CONTEXT LOCK
These are **Git blob SHA-1 object IDs, not raw-byte SHA-256**, fixed at BASE. Any change in checkpoint, approved ADR/Ledger, Scope, DoD, Architecture, contract or critical OID => mark STALE, halt writes and rebase/recompile:
- AGENTS.md=3e57b719f8651407879ebb641707a048773ea4c2
- docs/00-source-hierarchy.md=58a377bc76cafdd3377d733d4f30ef53661bb034
- docs/11-checkpoint.md=75ef743ac2dc61a46eb943ebf226c5969abd02ea
- docs/10-decisions-ledger.md=d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e
- docs/03-scope.md=4ef605c74632ece080b2650e37dd83a415b63310
- docs/09-definition-of-done.md=160b3054db9ea1961308934b401488b838d24c3e
- docs/04-architecture.md=df62574cb3956c3ac9881631a4cf66be4e1abff1
- docs/02-requirements.md=14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b
- docs/product/module-catalog.md=18d69bca439831d65982cb0f8acbca1dbaa2eee9
- docs/queue/implementation-registry.json=registry fetched 80 entries, PLAT-02 RESEARCH_PENDING
- docs/queue/work-orders/PLAT-02.md=dc03209c47bf53f5b25366c4464249ea0df4614e
- docs/architecture/gfx-01-graphics-rhi.md=4512de487da7df97969b56f8e5f508a56125ab32
- docs/contracts/gfx-01-rhi-api.md=822cbd118df75b4acf033443d5f75842d1344ae7
- docs/adr/0014-gfx-01-rhi-backends.md=27b3f4533083c6b6a23a989e0eb8661898d44ade
- docs/architecture/game-01-input-control-mapping.md=5f86d817a26a7142496788963453caf247dbfa50
- docs/contracts/game-01-input-actions-api.md=cc2598fe117ae4a60d7746028df084d7be229426
- docs/adr/0042-game-01-engine-owned-input-actions.md=377bfee8b464bc7c9dfcaca1f6ff8452a9616441
- docs/architecture/core-01-platform-lifecycle.md=11c7ec4125f40cf0172aa552a1e9835e84d2c172
- docs/adr/0003-core-01-platform-technology.md=2ee92dda5ab81ddcc446b9d5325d29257350e217

## SCOPE — exactly eight NEW Markdown only
1. [Architecture](../architecture/plat-02-linux-desktop-target.md).
2. [ADR-0070 PROPOSED](../adr/0070-plat-02-linux-host-compatibility-policy.md).
3. [Linux technical/license/security matrix](../research/plat-02-linux-technology-license-security-matrix.md).
4. [Typed Linux target API](../contracts/plat-02-linux-target-api.md).
5. [Exactly 128 future tests](../testing/plat-02-acceptance-matrix.md).
6. [Linux physical hardware benchmark protocol](../research/plat-02-linux-benchmark-protocol.md).
7. This research Work Order.
8. [Evidence Bundle](../evidence/NLE-P00-WO-002-PLAT-02.md).

Only eight NEW Markdown in research PR. No changes to source code, CMake, CI, registry, checkpoint, backlog or prior approved ADRs.

## OUT OF SCOPE
C++ engine code or SDL/Vulkan/Wayland bridge implementation, actual executable build, new unit/hardware tests, GPU results, real installers/Flatpak/AppImage upload, native OS target freeze, BIZ-03 updater, cross-platform RHI redesign, GAME-01 action mapper, AUD mixer, automatic root permissions, licensing decision, no paid services, code-issue #85 activation, 80 queue mutation, new DAG edges, public early product release.

## FILES / SOURCES TO READ
Source hierarchy, checkpoint, Ledger/ADRs, Scope, DoD, Architecture, Requirements, AGENTS.md; catalog and implementation registry; GFX-01/GAME-01 architecture/API/ADRs, CORE-01 transitive, queue #85. Official SDL3 Linux/Wayland/hints/migration/license, Khronos WSI and Vulkan ICD loader, freedesktop XDG directories/Desktop Entry/portals, PipeWire/Flatpak/AppImage/glibc/CMake. Recheck versions, licenses and CVEs before future code.

## REQUIREMENTS
GOV-001..005, NFR security/compatibility/performance and Linux target acceptance; NLE-D013/D014/D015/D017/D018/D019/D020. Preserve formal deps GFX-01+GAME-01. Support must be declared against owner-frozen distro+hardware; no unverified distributions/gaming platform claims.

## ARCHITECTURE RULES
- CORE-01 single main-thread SDL3 host; prefer Wayland when available, X11/XWayland conditional fallback, compositor capabilities explicit and lifecycle epochs checked.
- GFX-01 sole RHI/surface/queue/swapchain/driver selection; Vulkan Linux WSI and ICD provenance observed. Software fallback not physical GPU proof.
- GAME-01 sole semantic inputs; CORE-01 physical event host. No keylogger, invalid /dev/input privileges or IME password logging; focus/device failure releases actions.
- AUD owns PipeWire/Pulse/ALSA endpoints; UI owns locale/IME; DATA-01 scoped XDG VFS and portal grants; no PLAT-owned file/io/plugin policy bypass.
- PLAT-05 exports, BIZ-03 packaging/update/signature; PLAT only build/ABI/package capability. No sudo, setuid, arbitrary executable, unsafe LD_PRELOAD/lib load or trusted ICD override from project.
- Test Wayland fractional scale, compositor restrictions, clean glibc symbol floor, user permissions, packaging and GPU error/driver loss on actual hardware.
- ADR-0070 PROPOSED; no code approvals, no paid dependency, all 80 coding WOs blocked and no engine.

## CONSTRAINTS
P00 documentation risk LOW, CI free public repository; no CodeRabbit, external required reviewer, force push or bypass. No secret exports, unlicensed artifacts, expensive runners or irrevocable install. High assurance for future root/supply chain/auto update/privilege when applicable.

## ACCEPTANCE CRITERIA
- [ ] Eight NEW Markdown, valid internal/external references, no source/CI/registry/checkpoint/backlog edits in research PR.
- [ ] ADR-0070 PROPOSED, GFX-01 + GAME-01 exact formal edges, CORE-01 transitive; no approved technology or release class.
- [ ] Linux ABI/Wayland/X11/WSI/DRM/ICD/input/IME/audio/XDG/portals/sandbox/AppImage/Flatpak/security/vendor license matrix, threat/failure state and division of owner responsibilities.
- [ ] 128 unique sequential P02-T001..P02-T128, all FUTURE/NOT EXECUTED, 8x16 and future real hardware benchmark protocol; no fake PASS.
- [ ] Source/Context Lock, security/rollback, review and proposed independent checkpoint preserving all 80 coding statuses.
- [ ] Research PR CI/docs-validation SUCCESS exact head; audit pt-BR APPROVED with objective evidence; squash/main readback.
- [ ] Independent subsequent five-file checkpoint own CI/audit/squash/readback, then issue #321 close and four-Markdown historical closeout PR independently validated.
- [ ] Next real catalog module PLAT-03 Browser Runtime, order 68/80; no arbitrary invented module.

## TESTS
P00: GitHub Actions Docs Validation (Source Pack/relative links/module DAG/80 registry/block selector), exactly 8-new-file diff and 128 unique ID/NOT EXECUTED review. P01 future: Linux GCC/Clang CMake/CTest/sanitizers plus real physical GNOME/KDE Wayland/X11 Editor+Game smoke and benchmarks under [protocol](../research/plat-02-linux-benchmark-protocol.md). No native Linux test has executed now.

## DELIVERABLES
Eight versioned Markdown docs, issue #321, PR with base/head SHA and CI run/job, pt-BR audit APPROVED/CORRECTION REQUIRED/BLOCKED, Evidence Bundle and proposed Checkpoint Delta. No native binary/SDK/installer.

## REVIEW FORMAT
Pt-BR; verify stable WO, base/head, diff, linked Sources, scope/owners, license/sandbox, security negatives, exact case count, docs CI and no High/Critical; declare objective verdict only. Research approval is not tech approval.

## STOP CONDITION
Any stale checkpoint/Scope/DoD/Architecture/ADR/OID, unverified CI, wrong 8-file diff, missing 128 unique future cases, contradictory owner permissions, high/critical, running/signed code or unapproved spend => BLOCKED or same PR CORRECTION REQUIRED.

## CHECKPOINT AND EVIDENCE CONTROL
Research PR must NOT promote checkpoint. Once audited/merged, separate PR modifies exactly checkpoint/backlog/registry/WO/Evidence, with sole PLAT-02 research_status transition RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED; other 79 registry modules untouched. Close #321 only after this evidence. Four-Markdown historical closeout separately. Every later PR requires its own source check/CI/pt-BR audit/squash/readback. No engine implementation authorization.


## Research PR #322 verified; independent checkpoint delta in review
- [Research PR #322](https://github.com/KayzenRoot/stormline/pull/322) base `6271e5482e02fbc575d401feb2d72a24eaff2854`, head `cbc96c4b0245b19484458cfd4e725fd4c997e601`, exactly eight new Markdown, [Docs Validation run #43786413485](https://github.com/KayzenRoot/stormline/actions/runs/43786413485) SUCCESS job #133034958213 including Source Pack/links, catalog DAG, 80 registry and blocked selector, [objective pt-BR audit #6904800530](https://github.com/KayzenRoot/stormline/pull/322#issuecomment-6904800530) APPROVED documentary, squash/main readback `2f30d8613209739e15a025ebb5c68abc341b8b05`.
- Independent research checkpoint target **67/80 documented (83.75%), 13 pending; all 80/80 implementation WOs BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, executor_ready=0, approved_adr=0, release_class UNDECIDED all, engine_implemented=false**. Sole registry semantic mutation PLAT-02 `research_status: RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED` (all other 79 module entries and flags preserved). ADR-0070 PROPOSED, formal deps GFX-01+GAME-01 only, CORE-01 transitive, NLE-D009 license OPEN, P02-T001..P02-T128 future NOT EXECUTED, no Linux native code/build/hardware result.
- [Research issue #321](https://github.com/KayzenRoot/stormline/issues/321) OPEN pending own checkpoint CI/audit/squash/readback; future code [#85](https://github.com/KayzenRoot/stormline/issues/85) OPEN/BLOCKED. After verification close #321 and independently document history in a four-Markdown-only PR. Next PLAT-03 Browser Runtime 68/80 deps TWO-01+GFX-01+DATA-05.
- Checkpoint is separate exactly five modified files. Own CI/audit/squash/main readback pending before issue closure.


## Historical factual closure after independent checkpoint #323
- [Research PR #322](https://github.com/KayzenRoot/stormline/pull/322): BASE `6271e5482e02fbc575d401feb2d72a24eaff2854`, HEAD `cbc96c4b0245b19484458cfd4e725fd4c997e601`, eight NEW Markdown, [Docs Validation #43786413485](https://github.com/KayzenRoot/stormline/actions/runs/43786413485) SUCCESS job #133034958213, [audit pt-BR #6904800530](https://github.com/KayzenRoot/stormline/pull/322#issuecomment-6904800530) APPROVED documentary; normal squash/main `2f30d8613209739e15a025ebb5c68abc341b8b05` read back.
- [Independent checkpoint PR #323](https://github.com/KayzenRoot/stormline/pull/323): BASE `2f30d8613209739e15a025ebb5c68abc341b8b05`, HEAD `b7180d720de9a6b7beed8f12686c7ae19aa826f1`, exactly five modified files with **only** PLAT-02 registry research_status RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED, other 79 entries/flags unchanged; [Docs Validation #43786703741](https://github.com/KayzenRoot/stormline/actions/runs/43786703741) SUCCESS job #133035857205, [audit pt-BR #6904840249](https://github.com/KayzenRoot/stormline/pull/323#issuecomment-6904840249) APPROVED documentary; normal squash/main verified `92c0e4106c1ae54121b8de588766a6e855b9eb2c`.
- [Research issue #321](https://github.com/KayzenRoot/stormline/issues/321) CLOSED **after** checkpoint proof; future coding [#85](https://github.com/KayzenRoot/stormline/issues/85) remains OPEN/BLOCKED. Main registry **67/80 researched (83.75%), 13 pending**, all **80/80 implementation WOs BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS**, executor_ready=0, approved_adr=0, release_class UNDECIDED all, engine_implemented=false. ADR-0070 PROPOSED, NLE-D009 engine license OPEN, P02-T001..P02-T128 FUTURE/NOT EXECUTED, zero Linux Editor/Game native build, real GPU/Wayland/X11/audio smoke or benchmark.
- Next REAL catalog module **PLAT-03 Browser Runtime (WebAssembly/WebGPU/WebGL)**, order **68/80**, formal dependencies **TWO-01 + GFX-01 + DATA-05**. Research historical closeout only four Markdown; no new ADR/CI/registry or source changes. Its separate CI/audit/squash/main readback must be performed before advancing.
