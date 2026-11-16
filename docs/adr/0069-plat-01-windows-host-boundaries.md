# ADR-0069 — Windows Target Host Bridges, Capability-Gated Presentation and Distribution Boundaries

**2026-11-15 | P00 DOCUMENTARY RESEARCH ONLY / NOT IMPLEMENTED | [research #317](https://github.com/KayzenRoot/stormline/issues/317) | NLE-P00-WO-002-PLAT-01 | future code [#84](https://github.com/KayzenRoot/stormline/issues/84) OPEN/BLOCKED | BASE `e6ca541df3f08bc46a7f1e5b2f82564cb740f720`.** Catalog 66/80, **formal dependencies GFX-01 + GAME-01 ONLY**, both prior ADR-0014/0042 PROPOSED; CORE-01 transitive ADR-0003 PROPOSED. Baseline research 65/80, 15 pending; 80/80 future coding WOs BLOCKED; engine_implemented=false; NLE-D009 license OPEN.

**STATUS: PROPOSED / NOT OWNER RATIFIED / NOT ADOPTED / NO IMPLEMENTATION AUTHORIZATION.**

## Context
Windows desktop is required for Stormline Editor and exported games. GFX-01 already proposes a vendor-neutral C++20 RHI, GAME-01 a semantic action map/input resolver, and transitive CORE-01 a single SDL3 native host/pump. A poorly scoped Windows module would duplicate event loops/input mappers or GPU backends, assume a proprietary Windows SDK/installer/signing identity, mis-handle multi-monitor DPI/alt-tab/device loss, or claim PC support from CI compilation alone. All predecessors are PROPOSED research, no native engine runtime exists.

## Proposed decision
1. **Formal dependencies exactly GFX-01 + GAME-01**. No new DAG edges. PLAT-01 is Windows-specific target adapter and capability contract **beneath** these owners, not a new engine-wide RHI, GAME input map or CORE-01 event service. CORE-01 process/SDL3 event pump, AUD owner, DATA, BIZ-03 package/update and AI authorization are **transitive/integration owners**, not new formal requirements.
2. **Preferred narrow Windows host candidate**: SDL3 (zlib) via CORE-01, with audited Win32 interop only for gaps (DPI/WM messages/device/display/COM). No independent PLAT event poller, SDL_Init instance, global HID hooks or direct WindowHandle in public gameplay/MCP contracts. Windows 11 serviced x64 as *candidate initial smoke target*, not frozen minimum OS; Windows 10 main support ended 2025-10-14 and exceptions/ARM64 require separate owner decision and evidence.
3. **Typed Windows capability and epoch boundary**: Windows OS build/architecture, display/pixel/DPI/content scale/HDR/VRR, window/focus/suspend epoch, native input/audio endpoint/driver and package capability status. Unknown/denied/unsupported always explicit, no guesswork based on SKU or marketing GPU.
4. **Per-monitor DPI v2 candidate**: each multi-monitor window owns logical/pixel surface and scale revision; handle WM_DPICHANGED, fullscreen/borderless, minimize zero extent, monitor/rotation/hotplug, remote desktop as explicit event transitions. Do not double-scale mouse/UI or pretend high-DPI works because a manifest says so.
5. **RHI choice stays GFX-01**: Windows PLAT provides present surface and observed swapchain environment; Vulkan Windows WSI and D3D12/DXGI flip-model are research candidates. Feature query and explicit fallback (tearing/VRR/HDR/multi-GPU) prevent capability forgery. Resource generations on resize/device loss and actual renderer/cook smoke must be verified, not presumed. No default "D3D12 wins" or Vulkan-only policy imposed.
6. **Input semantics stay GAME-01**, OS events/IME text/focus owned CORE-01/UI, gamepad/GameInput optional and subject to SDK runtime and redistribution license. SDL3+GameInput sources deduplicated to prevent doubled actions. On focus loss/USB/Bluetooth disconnect, GAME-01 revokes hold states and DeviceEpoch. Never expose global physical input injection/keyboard logging to agent.
7. **Audio semantics stay AUD owner**: WASAPI shared/optional XAudio2/miniaudio compared behind audio backend, no alternate PLAT mixer. No logging/COM blocking from realtime audio callback, truthful endpoint loss/switch errors.
8. **Security/local-first**: nonadmin runtime by default, path/UTF-16 to UTF-8/scoped VFS, reparse/junction/long path review, strict DLL load path allowlisting (no current working directory or project-controlled DLL injection), signed third-party binaries, crash diagnostics local and redacted under CORE-06. No shell/script/UAC elevation triggered by untrusted assets or LLM.
9. **Packaging separation**: PLAT defines Windows-specific build/package capability and unsigned INTERNAL smoke artifact, BIZ-03 owns installer/update/rollback/production release. MSIX/package identity vs unpackaged MSI/EXE and Windows App SDK 2.x runtime/CRT need an explicit later ADR based on rights, clean machine, Store choice and support. Real publisher certificate/Smart App Control signing costs cannot be silently incurred; unsigned internal test != signed release.
10. **Reproducibility and proof**: pinned Windows SDK (check Microsoft supported servicing, SDK 28000+ and 26100+ candidate), MSVC/Clang-cl, SDL3 and optional Vulkan/D3D/GameInput versions, CPU/GPU/driver/OS builds, symbols and test fixture. Hosted Windows CI can show build/headless smoke only; **real physical Windows GPU/display/input/audio hardware smoke is essential** to accept PLAT-01.
11. **No binding technology choice in P00**: SDL3/Win32 preferred *evaluation* only; choice of D3D Agility v1.620.2 (as of 2026-11-09) vs pinned Vulkan loader, GameInput v4 and Windows App SDK 2.x remain optional and subject to exact-tag security/license/redistribution, toolchain/driver and practical A/B. NLE-D009 license OPEN.
12. **128 P01 future tests**, objective benchmark, source/rights and clean hardware proof needed before approval; code issue #84 and 79 other code WOs remain BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, ready=false, approved_adr=null, release_class UNDECIDED, engine_implemented=false.

## Alternatives and disposition
| Candidate | Why potentially valuable | Why NOT automatically selected |
|---|---|---|
| Native Win32 window, RawInput, XInput and D3D12-only engine | maximum native control and feature availability | duplicates CORE-01/GAME-01, multiplies cross-platform code, disregards GFX-01 ownership |
| SDL3 through CORE-01, narrow Win32 bridge | consistent window/input/lifecycle, cross-target reuse | needs version/real hardware/API capability proof; cannot hide native edge cases |
| Windows App SDK/WinUI 3 as whole editor shell | Windows-native UI and integrations | Windows-only dependency and runtime bootstrap, separate editor/renderer integration, conflicts with shared editor architecture |
| Windows 10/11 all builds supported with same profile | broader user pool | Windows 10 mainstream EOS, version/feature disparities, unvalidated security/driver and SDK support |
| Auto-enable HDR, tearing, fullscreen exclusive | ambitious visuals | feature/monitor/OS/driver dependent, tearing flag/present semantics invalid if unsupported |
| Enforce D3D12 Agility latest preview | fast newest GPU features | requires redistribution/version/driver validation, cannot drive GFX-01 backend decision |
| GameInput v4 as mandatory physical input backend | modern haptics and sensors | PC redistributable/sideload terms and possible SDL duplicate events, optional adapters |
| Always-on Windows audio backend inside PLAT | simple integration | duplicates AUD owner, concurrency and real-time hazards |
| Make MSIX + Store a default release | package identity/update | publishing/signing/fees/Store and framework runtime, cannot preempt BIZ-03/NLE-D009 |
| Package unsigned binary as commercial-ready | trivial CI output | signing reputation/Smart App Control/clean-machine failures, security/DoD violation |
| Assume GPU smoke on hosted CI = device proof | cheap automation | GPU/headless/monitor/input unavailable or virtualized in hosted runners |
| Allow arbitrary project DLLs or untrusted scripts to load | plugin flexibility | DLL planting, arbitrary code execution and privilege escalation |
| Premature Windows ARM64 native mandatory target | broad architecture | new ABI/third-party binary/QA/cost matrix not owner-approved |
| Auto-elevate installer/runtime with UAC | fewer prompts | privileged state irreversible without consent and BIZ-03 owner |

## Consequences and proof obligations
Narrow typed boundary improves cross-OS portability and future GFX/GAME owner parity; costs include complex high DPI/hybrid GPU/device loss/IME/hotplug and clean-machine packaging tests. Require license and security exact tags, Windows servicing/min build, hardware BOM, real smoke both Editor + exported game, x64 and agreed ARM64 or Windows 10 tiers, native build CI, rollback/uninstall, external code-signing approval if shipping, and no HIGH/CRITICAL. Until independently validated, **ADR PROPOSED** and **NO CODE**.

[Architecture](../architecture/plat-01-windows-desktop-target.md) · [Contracts](../contracts/plat-01-windows-target-api.md) · [Technology/license matrix](../research/plat-01-windows-technology-license-security-matrix.md).
