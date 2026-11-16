# NLE-P00-WO-002-PLAT-01 — Windows Desktop Target P00 Research Work Order

**2026-11-15 | P00 DOCUMENTARY RESEARCH ONLY / NOT IMPLEMENTED | [research #317](https://github.com/KayzenRoot/stormline/issues/317) | NLE-P00-WO-002-PLAT-01 | [future code #84](https://github.com/KayzenRoot/stormline/issues/84) OPEN/BLOCKED | BASE `e6ca541df3f08bc46a7f1e5b2f82564cb740f720`.** Catalog 66/80, formal deps **GFX-01 + GAME-01 ONLY**, ADR-0014/0042 PROPOSED, CORE-01 transitive; 65/80 baseline research documented, 15 pending, 80/80 implementation WOs BLOCKED; engine=false, NLE-D009 OPEN.

Research [#317](https://github.com/KayzenRoot/stormline/issues/317) OPEN, future coding [#84](https://github.com/KayzenRoot/stormline/issues/84) OPEN/BLOCKED. Catalog **66/80**, formal dependencies **GFX-01 + GAME-01 ONLY**, both predecessor research ADRs 0014/0042 PROPOSED. CORE-01 ADR-0003 transitive host, not new DAG edge. P00 documentary risk LOW, future Windows executable/driver/installer and privileged distribution **ELEVATED or HIGH_ASSURANCE according to actual change**.

## OBJECTIVE
Specify native Windows desktop/editor+export support: OS lifecycle/Win32+SDL3 bridging, per-monitor DPI, multi-monitor/window focus and power, GFX-01 Windows presentation surface Vulkan/D3D12 candidate and HDR/VRR/device loss, GAME-01 physical/semantic input path and optional GameInput, audio owner Windows endpoint, hardened DLL/UTF-16/VFS/UAC, BIZ-03 packaging/signing/update boundaries and reproducible **real Windows hardware build+smoke**. Catalog acceptance **"Build e smoke test em hardware Windows definido."** Research only; no build executed or hardware declared supported.

## CONTEXT / SOURCE CHECK
Canon order checkpoint > Decisions Ledger/approved ADRs > Scope > DoD > Architecture > Requirements > remaining. Live main matches BASE `e6ca541df3f08bc46a7f1e5b2f82564cb740f720`, no open PRs. Registry 80 entries, **65/80 researched (81.25%), 15 pending**, 80/80 code WOs BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, executor_ready=0, approved_adr=0, release_class 80/80 UNDECIDED, engine_implemented=false. Code #84 OPEN/BLOCKED. NLE-D009 engine license OPEN; NLE-D013 no public MVP; NLE-D017 Windows+Linux+macOS Editor and game exports owner-directed. No executable/SDK license selected.

## CONTEXT LOCK (Git blob SHA-1 OIDs, NOT raw byte SHA-256)
- `AGENTS.md` `3e57b719f8651407879ebb641707a048773ea4c2`; `docs/00-source-hierarchy.md` `58a377bc76cafdd3377d733d4f30ef53661bb034`; `docs/11-checkpoint.md` `e89ae09d9b2a2bb1225d64aba6de5a941474702e`; `docs/10-decisions-ledger.md` `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`.
- `docs/03-scope.md` `4ef605c74632ece080b2650e37dd83a415b63310`; `docs/09-definition-of-done.md` `160b3054db9ea1961308934b401488b838d24c3e`; `docs/04-architecture.md` `df62574cb3956c3ac9881631a4cf66be4e1abff1`; `docs/02-requirements.md` `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`.
- `docs/product/module-catalog.md` `18d69bca439831d65982cb0f8acbca1dbaa2eee9`; `docs/queue/implementation-registry.json` `f55f388b35180faaed685261cf09f36f5adefe33`; `docs/queue/work-orders/PLAT-01.md` `15175b4d0549e7ee158e279653a888aba27f5b64`.
- `docs/architecture/gfx-01-graphics-rhi.md` `4512de487da7df97969b56f8e5f508a56125ab32`; `docs/contracts/gfx-01-rhi-api.md` `822cbd118df75b4acf033443d5f75842d1344ae7`; `docs/adr/0014-gfx-01-rhi-backends.md` `27b3f4533083c6b6a23a989e0eb8661898d44ade`.
- `docs/architecture/game-01-input-control-mapping.md` `5f86d817a26a7142496788963453caf247dbfa50`; `docs/contracts/game-01-input-actions-api.md` `cc2598fe117ae4a60d7746028df084d7be229426`; `docs/adr/0042-game-01-engine-owned-input-actions.md` `377bfee8b464bc7c9dfcaca1f6ff8452a9616441`.
- `docs/architecture/core-01-platform-lifecycle.md` `11c7ec4125f40cf0172aa552a1e9835e84d2c172`; `docs/adr/0003-core-01-platform-technology.md` `2ee92dda5ab81ddcc446b9d5325d29257350e217`.
Change in checkpoint, approved Ledger/ADR, Scope, DoD, Architecture or these critical OIDs => **STALE**: stop, source recheck/rebase/recompile before write/merge. At later code activation use actual SHA-256 of source files.

## SCOPE: precisely eight NEW Markdown research files
1. [Architecture](../architecture/plat-01-windows-desktop-target.md)
2. [ADR-0069 PROPOSED](../adr/0069-plat-01-windows-host-boundaries.md)
3. [Windows technology/license/security matrix](../research/plat-01-windows-technology-license-security-matrix.md)
4. [Versioned Windows target API contracts](../contracts/plat-01-windows-target-api.md)
5. [128 unique FUTURE tests](../testing/plat-01-acceptance-matrix.md)
6. [Hardware smoke and benchmark protocol](../research/plat-01-windows-benchmark-protocol.md)
7. This research Work Order
8. [Evidence Bundle](../evidence/NLE-P00-WO-002-PLAT-01.md)
Research PR only these eight NEW Markdown. No code, CI, registry, checkpoint or backlog changes.

## OUT OF SCOPE
Any new Windows C++ code, native SDL/Win32 binary or GPU/driver feature, GFX-01 backend or GAME-01 input runtime, audio mixer, source file, package, signed artifact, certificate/store account, UAC/admin, paid Windows VM/service, real native build or benchmark run, public release before 1.0, implementation queue unlock, redesign of Linux/macOS modules, synthetic test PASS, licensing decision, force-push, destructive operation, CodeRabbit, mandatory external reviewer.

## FILES / SOURCES TO READ
Above full canonical Source Pack, GFX-01 and GAME-01 architecture/API/ADRs and CORE-01 transitive host, registry/catalog and future code #84, DATA-01/05, AUD, BIZ-03 as integration authority (not new formal prerequisites). External official 2026 Microsoft Windows SDK supported versions/servicing, Windows 10 EOS, PMv2/WM_DPICHANGED, DXGI flip/tearing/Agility, GameInput v4 NuGet/redist, MSIX/Windows App SDK, Win32 DLL security and signing, SDL3 high DPI/main-thread/license, Khronos Vulkan WSI, CMake/MSVC and WASAPI. No existing integration automatically adopted.

## REQUIREMENTS
GOV-001..005, NFR-002..005 and relevant platform/graphics/game input CAP requirements; NLE-D013/014/015/017/018/019/020. Formal deps GFX-01+GAME-01 ONLY, ADR-0014/0042 are PROPOSED and all 80 code WOs remain blocked. Catalog smoke hardware target has to be real and owner-ratified, not a CI emulator.

## ARCHITECTURE RULES
- CORE-01 owns single main-thread SDL event loop/host, PLAT-01 Windows-native bridge only. Formal deps **GFX-01 + GAME-01**, no new DAG edge, no secret OS handles outside host.
- GFX-01 owns device backend/RHI/swapchain; PLAT provides Windows present surface metadata, DPI/present capabilities, redacted feature evidence. Vulkan/D3D12 candidate never implicitly chosen. Device loss/resize increment generations.
- GAME-01 owns semantic ActionMap/InputActionFrame/seat/tick, PLAT translates scoped native physical input via CORE-01, IME/text separately handled UI owner, no keylogger/input injection.
- AUD Windows endpoint capability via audio owner, no blocking realtime callback, local CORE-06 diagnostics only with privacy and no auto upload.
- Per-Monitor DPI v2, monitor HDR/SDR/VRR, fullscreen/occlusion/suspend and background power are owner-cited capability transitions, no universal support claim.
- Scoped DATA-01 Windows path/UTF-16/ACL/reparse defense, safe DLL module load, no privilege elevation or arbitrary shell. BIZ-03 owns installer/update/rollback/signing; PLAT build artifact just reports requirements, unsigned internal smoke not production.
- Windows current support lifecycle/version and GPU hardware tier chosen only after actual evidence; Win10 mainstream EOS and Win ARM64 non-default noted. Windows SDK + SDL3/GameInput/D3D/Windows App SDK exact licensing and release review, engine NLE-D009 OPEN.
- 128 P01 future cases with independent OS/owner oracle, benchmark no measured values, no published compatibility/AAA claim.
- All 80 future implementation WOs BLOCKED, executor_ready=false, approved_adr=null, release_class all UNDECIDED, engine_implemented=false; ADR-0069 PROPOSED.

## CONSTRAINTS
P00 docs LOW; future native code/plugin/signing privilege HIGH_ASSURANCE when needed. Free public GitHub docs CI and no CodeRabbit. No unverified SDK/hardware support nor real tests claims, no paid service/install/irreversible action. No known HIGH/CRITICAL advancement.

## ACCEPTANCE CRITERIA
- [ ] Exactly eight NEW Markdown valid links/Source Pack, no code/registry/checkpoint/backlog/CI change in research PR.
- [ ] ADR-0069 PROPOSED, formal GFX-01+GAME-01 only, CORE-01 transitive, no alteration of ADR-0014/0042 or OS licensing approval.
- [ ] Tech matrix covers Windows OS lifecycle, SDL3/Win32 high DPI, RHI Vulkan/DXGI flip/tearing/HDR/driver loss, GameInput/redist, AUD endpoint, security, SDK/CRT, MSIX/signing/BIZ-03 and real hardware.
- [ ] Exactly 128 P01-T001..P01-T128 ordered unique FUTURE/NOT EXECUTED in eight groups of 16 with independent oracles.
- [ ] Benchmark protocol includes real Editor/Game build & hardware smoke but no fabricated results/target/tier.
- [ ] Exact final HEAD Docs Validation SUCCESS, objective pt-BR documentary audit APPROVED and normal squash/readback.
- [ ] Separate **five-file checkpoint** exactly checkpoint/backlog/registry/WO/Evidence, sole PLAT-01 `research_status RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED`, no other registry fields, own CI/audit/squash/main readback.
- [ ] After checkpoint **66/80 researches (82.5%), 14 pending, all 80 code packets BLOCKED, zero ready/approved ADR, engine false**, NLE-D009 OPEN, ADR-0069 PROPOSED.
- [ ] Research #317 CLOSE only after independent checkpoint proof (restore OPEN if GitHub auto-closes prematurely); future code #84 OPEN/BLOCKED. Historical **four Markdown** PR with independent CI/audit/squash/readback before PLAT-02.

## TESTS
P00: GitHub Docs Validation exact HEAD, Source Pack/local links, module DAG, WO registry and Zcode selector rejecting blocked packets. **FUTURE / NOT EXECUTED:** 128 P01 native tests, Win SDK compile, editor/game launch, physical GPU, real gamepads/USB audio, clean install/signing, security and benchmark. No real Windows supported certification in research.

## DELIVERABLES
Research issue #317, exactly eight docs incl ADR-0069 PROPOSED, tech/license matrix, API, 128 tests and benchmark, research PR/CI/audit/squash/readback, checkpoint 5-file PR with own gates, historical 4-file PR with own gates, Evidence, factual main readback. Zero code or external runtime costs.

## REVIEW FORMAT
pt-BR APPROVED / CORRECTION REQUIRED / BLOCKED, base/head SHAs, precise files, 128 IDs, tool provenance and license/SDK support, risks, CI run/job evidence, owner boundaries, source readback, Checkpoint Delta only after audit, future smoke not executed.

## STOP CONDITION
STALE checkpoint/decision/fingerprint, wrong formal deps, broken links/tests, non-exact diff, false physical hardware/performance/SDK claims, license adopted implicitly, untrusted input/DLL privileges, unauthorized signing/payment, CI failure, HIGH/CRITICAL or unlocked implementation packet. Do not advance PLAT-02 before factual four-Markdown closeout.

## Research #318 verified; independent checkpoint proposed
- [Research PR #318](https://github.com/KayzenRoot/stormline/pull/318): base `e6ca541df3f08bc46a7f1e5b2f82564cb740f720`, final head `a8d2a82d47dffa586a37009ed84f8a0addca25bb`, eight new Markdown; [Docs Validation #43782022164](https://github.com/KayzenRoot/stormline/actions/runs/43782022164) SUCCESS, job #133021145520 (source pack, links, DAG, registry, blocked selector); [pt-BR audit #6904188697](https://github.com/KayzenRoot/stormline/pull/318#issuecomment-6904188697) APPROVED documentary; normal squash/main readback `2d5d5910af38bb04a55ca5a3780b6f6ec3fa057a`. GitHub auto-closed research #317 early on squash; reopened with [governance note #6904211707](https://github.com/KayzenRoot/stormline/issues/317#issuecomment-6904211707), OPEN until independent checkpoint readback. Code [#84](https://github.com/KayzenRoot/stormline/issues/84) OPEN/BLOCKED.
- **Checkpoint proposed 66/80 research (82.5%), 14 pending, all 80/80 code WOs BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, executor_ready=0, approved_adr=0, release_class UNDECIDED all, engine_implemented=false.** ADR-0069 PROPOSED; NLE-D009 license OPEN; P01-T001..P01-T128 FUTURE/NOT EXECUTED; Windows build/real hardware/installer/signing/benchmark NOT EXECUTED. This checkpoint own CI/audit/squash/readback pending. Checkpoint five files and sole PLAT-01 research_status; #317 OPEN until proof, future code #84 BLOCKED.
