# Evidence Bundle — NLE-P00-WO-002-PLAT-01 Windows Desktop Target Research

**2026-11-15 | P00 DOCUMENTARY RESEARCH ONLY / NOT IMPLEMENTED | [research #317](https://github.com/KayzenRoot/stormline/issues/317) | NLE-P00-WO-002-PLAT-01 | [future code #84](https://github.com/KayzenRoot/stormline/issues/84) OPEN/BLOCKED | BASE `e6ca541df3f08bc46a7f1e5b2f82564cb740f720`.** Catalog 66/80, formal deps **GFX-01 + GAME-01 ONLY**, ADR-0014/0042 PROPOSED, CORE-01 transitive; 65/80 baseline research documented, 15 pending, 80/80 implementation WOs BLOCKED; engine=false, NLE-D009 OPEN.

## 1. Source Check and Context Lock, observed live
- Live main matches requested BASE `e6ca541df3f08bc46a7f1e5b2f82564cb740f720`, zero open PR before research branch. Module catalog PLAT-01 66/80 formal deps **GFX-01 + GAME-01 ONLY**, acceptance **"Build e smoke test em hardware Windows definido."**
- Registry preflight: 80 modules, **65/80 research documented, 15 pending, all 80/80 future coding WOs BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS**, executor_ready=0, approved_adr=0, release_class 80/80 UNDECIDED, engine_implemented=false. Future code [#84](https://github.com/KayzenRoot/stormline/issues/84) OPEN/BLOCKED. GFX-01 ADR-0014, GAME-01 ADR-0042 and CORE-01 ADR-0003 remain PROPOSED, no runtime.
- Precedence Source Pack checkpoint > Decisions Ledger/approved ADRs > Scope > DoD > Architecture > Requirements. AGENTS/catalog, GFX-01/GAME-01 architecture/API/ADRs and CORE-01 host read. Full Context Lock Git blob SHA-1 OIDs (not raw SHA-256) in [Work Order](../work-orders/NLE-P00-WO-002-PLAT-01.md) and [research issue #317](https://github.com/KayzenRoot/stormline/issues/317). Critical drift => STALE/rebase.
- Approved NLE-D017 requires Windows Editor and exported games, not Windows 10/ARM64 unrestricted. NLE-D009 engine license OPEN, no publisher signing/SDK license adopted and no public MVP before full 1.0 DoD.

## 2. External research evidence, not a claim of implemented system
- [Windows SDK releases](https://learn.microsoft.com/en-us/windows/apps/windows-sdk/downloads) 10.0.28000.2957/26100.9457 listed Sep 2026; exact supported toolchain/OS profile remains unchosen. [Windows OS servicing](https://learn.microsoft.com/en-us/windows/apps/windows-app-sdk/support), [Win10 MSIX EOS](https://learn.microsoft.com/en-us/windows/apps/package-and-deploy/msix-windows10-windows11) non-LTSC mainstream ended Oct 14 2025, exceptions require conscious decision.
- [Win32 PMv2 High DPI](https://learn.microsoft.com/en-us/windows/win32/hidpi/high-dpi-desktop-application-development-on-windows), [SDL3 high DPI](https://wiki.libsdl.org/SDL3/README-highdpi) distinguishes physical framebuffer pixels and UI scale; [SDL3 SDL_PumpEvents](https://wiki.libsdl.org/SDL3/SDL_PumpEvents) main-thread only, preserving CORE-01 event ownership. [SDL3 zlib license](https://github.com/libsdl-org/SDL/blob/main/LICENSE.txt) root, exact tag/third-party notices not yet selected.
- [DXGI flip model](https://learn.microsoft.com/en-us/windows/win32/direct3ddxgi/for-best-performance--use-dxgi-flip-model) and [tearing flags](https://learn.microsoft.com/en-us/windows/win32/direct3ddxgi/dxgi-present) require capability/flag constraints and flip-model/MSAA behavior. [DirectX Agility](https://devblogs.microsoft.com/directx/directx12agility/) optional version 1.620.2 Nov 9 2026; GFX-01 backend choice still proposed, not adopted.
- [GameInput PC NuGet/redist](https://learn.microsoft.com/en-us/gaming/gdk/docs/features/common/input/overviews/input-nuget?view=gdk-2510) PC install runtime included with NuGet MSI but not auto-installed; [GameInput 4.0](https://learn.microsoft.com/en-us/gaming/gdk/docs/features/common/input/overviews/input-agility-redistributable?view=gdk-2610) side-load optional with license and source-dedup complexity. GAME-01 remains owner of semantic input and CORE-01 of OS pumping.
- [MSIX/Win32 packaging](https://learn.microsoft.com/en-us/windows/apps/package-and-deploy/packaging/) and [Windows App SDK deployment](https://learn.microsoft.com/en-us/windows/apps/windows-app-sdk/deployment-architecture) optional, do not imply runtime included or signer identity. [DLL security](https://learn.microsoft.com/en-us/windows/desktop/dlls/dynamic-link-library-security) CWD DLL planting, [Smart App Control code signing](https://learn.microsoft.com/en-us/windows/apps/develop/smart-app-control/code-signing-for-smart-app-control) trusted publisher requirements. Future packaging/signing/update belongs BIZ-03, no cost authorized.
- Audio owner handles WASAPI/miniaudio, source VFS and game artifact DATA/BIZ owner. PLAT-01 merely records native capabilities and RHI/input bridge. No license/SDK/OS version pinned.

## 3. Exactly eight research Markdown
1. [Windows architecture](../architecture/plat-01-windows-desktop-target.md)
2. [ADR-0069 PROPOSED](../adr/0069-plat-01-windows-host-boundaries.md)
3. [Technology/license/security](../research/plat-01-windows-technology-license-security-matrix.md)
4. [Typed Windows target API](../contracts/plat-01-windows-target-api.md)
5. [128 P01 future tests](../testing/plat-01-acceptance-matrix.md)
6. [Windows hardware smoke benchmark protocol](../research/plat-01-windows-benchmark-protocol.md)
7. [Research Work Order](../work-orders/NLE-P00-WO-002-PLAT-01.md)
8. This Evidence Bundle.

Research PR exactly these eight NEW Markdown and **NO code, SDK, CI, registry, checkpoint or backlog mutation**.

## 4. Honest evidence status
- Exactly **P01-T001..P01-T128** future individually numbered tests, eight groups of sixteen, **FUTURE / NOT EXECUTED**; no test code/OS run, no PASS/FAIL and no actual Windows hardware smoke/build, game export, GPU screenshot, audio sample, controller device, installer, signing or benchmark result.
- ADR-0069 PROPOSED, third-party SDK/licenses and OS support matrix UNSELECTED, engine license NLE-D009 OPEN. P00 doc CI cannot prove Windows functionality.
- Research PR CI/run/job/audit/squash/readback PENDING until observed; checkpoint target merely proposed and cannot be treated promoted by research.

## 5. Proposed checkpoint delta only, no promotion in research PR
After exact-head research PR Docs Validation SUCCESS, objective pt-BR audit APPROVED documentary, normal squash/main readback:
- Separate **five-file checkpoint** modifying only `docs/11-checkpoint.md`, `docs/08-backlog.md`, `docs/queue/implementation-registry.json`, this WO and Evidence.
- Only registry semantic mutation **PLAT-01 research_status `RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED`**. All 79 other modules and ALL work_order_status/risk/deps/approved_adr/executor_ready/release_class/engine_implemented flags unchanged.
- Target **66/80 research documented (82.5%), 14 pending, all 80 implementation WOs BLOCKED, ready=0, approved_adr=0, release_class UNDECIDED all, engine false**.
- Checkpoint own exact HEAD CI/audit/squash/main readback. Close issue #317 only after verified checkpoint (reopen if auto-closed by GitHub on earlier PR); code #84 remains OPEN/BLOCKED.
- Historical closeout **four Markdown** (checkpoint/backlog/WO/Evidence), own CI/audit/squash/main readback before PLAT-02 Linux Desktop Target (67/80, formal deps GFX-01+GAME-01).

## 6. Risk, defect and rollback
P00 docs LOW; actual native Windows executable, injected scripts/plugins, DLL search, installer/UAC and publisher signing can be HIGH_ASSURANCE. Risks include unsupported Windows 10 build promises, DPI invalid click/overflow, event double-processing, GPU stale swapchain after monitor hotplug, background raw input/IME credential leakage, audio realtime blocking, DLL planting, reparse escape, missing runtimes/unsigned release, auto update without owner and false CI hardware claims. No known HIGH/CRITICAL *documentary* defect accepted, but no future vulnerabilities proven absent.
Rollback documentary via normal audited revert, no source migration or Windows host artifacts changed.

## Research #318 factual CI/audit/squash readback, checkpoint delta proposed
- [Research PR #318](https://github.com/KayzenRoot/stormline/pull/318): base `e6ca541df3f08bc46a7f1e5b2f82564cb740f720`, final head `a8d2a82d47dffa586a37009ed84f8a0addca25bb`, eight new Markdown; [Docs Validation #43782022164](https://github.com/KayzenRoot/stormline/actions/runs/43782022164) SUCCESS, job #133021145520 (source pack, links, DAG, registry, blocked selector); [pt-BR audit #6904188697](https://github.com/KayzenRoot/stormline/pull/318#issuecomment-6904188697) APPROVED documentary; normal squash/main readback `2d5d5910af38bb04a55ca5a3780b6f6ec3fa057a`. GitHub auto-closed research #317 early on squash; reopened with [governance note #6904211707](https://github.com/KayzenRoot/stormline/issues/317#issuecomment-6904211707), OPEN until independent checkpoint readback. Code [#84](https://github.com/KayzenRoot/stormline/issues/84) OPEN/BLOCKED.
- **Checkpoint proposed 66/80 research (82.5%), 14 pending, all 80/80 code WOs BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, executor_ready=0, approved_adr=0, release_class UNDECIDED all, engine_implemented=false.** ADR-0069 PROPOSED; NLE-D009 license OPEN; P01-T001..P01-T128 FUTURE/NOT EXECUTED; Windows build/real hardware/installer/signing/benchmark NOT EXECUTED. This checkpoint own CI/audit/squash/readback pending. Checkpoint based on `2d5d5910af38bb04a55ca5a3780b6f6ec3fa057a`, five files, only PLAT-01 research_status registry mutation; own CI/audit/squash/readback pending.
