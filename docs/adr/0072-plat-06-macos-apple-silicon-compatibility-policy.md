# ADR-0072 — macOS ARM64 Native Priority, Conditional Intel and Cocoa/Metal Safety

2026-11-15 | P00 DOCUMENTARY RESEARCH ONLY | NLE-P00-WO-002-PLAT-06 | research #329 | future code #87 OPEN/BLOCKED | base 109287f928b4436b31188c1dd8cf4f7a454ad989. Catalog 69/80; formal prerequisites **CORE-01 + GFX-01 + GAME-01 ONLY**, predecessor ADR-0003/0014/0042 PROPOSED, 68/80 researched before PLAT-06, 12 pending, all 80 code packets BLOCKED, zero ready and approved ADR, release classes UNDECIDED, engine_implemented=false and source license NLE-D009 OPEN.


**STATUS: PROPOSED / NOT RATIFIED BY OWNER / NO IMPLEMENTATION APPROVAL.**

## Problem
Stormline must open/build/close the native macOS Editor and exported 2D/2.5D/3D games. Cocoa and Metal lifecycle, Apple Silicon vs Intel OS cutoff, Xcode architecture, GPU tier, input privacy, signed bundle security and App Store vs Developer ID distribution must be explicit. A documentation green check cannot prove real Apple hardware or notarization.

## PROPOSED decisions
1. **Formal prerequisites EXACT CORE-01 + GFX-01 + GAME-01 only.** CORE-01 (ADR-0003 PROPOSED) owns SDL3 process/event/window lifecycle, GFX-01 (ADR-0014 PROPOSED) native Metal RHI, GAME-01 (ADR-0042 PROPOSED) semantic input actions. Do not add PLAT-05/BIZ-03/AUD/EDIT/AI as new formal dependencies, they remain integration owners.
2. **Apple Silicon arm64 mandatory native candidate** on owner-approved named min OS and real M-series machine. Apple [WWDC26](https://developer.apple.com/videos/play/wwdc2026/102/) states macOS Tahoe 26 last Intel Mac major release. macOS27 not Intel-hardware support. Actual Intel x86_64 Mac compatibility for 1.0 is **owner-undecided**, if ratified test actual eligible Intel Macs <=macOS26 and all nested Mach-O libs/slices; optional universal2 arm64+x86_64 only under explicit deployment target.
3. [Xcode27](https://developer.apple.com/documentation/Xcode-Release-Notes/xcode-27-release-notes) runs only on Apple Silicon, may backdeploy universal (12+), and ARCHS_STANDARD excludes x86_64 when target >=27 unless manual. [Rosetta macOS27 last general purpose](https://developer.apple.com/news/?id=w5ngl9k2) is transition support, **not** Stormline primary ARM strategy nor native Intel test. Physical Intel on <=26 and translated x86_64 on Apple Silicon are distinct receipts.
4. Thin Objective-C++ AppKit/QuartzCore host under CORE-01 SDL3. A **single** NSApplication delegate/event authority with quit/open document/unsaved close veto; all AppKit window and SDL_Metal_CreateView on **main thread**. Window/Process epochs, fullscreen Space, occlusion, focus, sleep/wake, hot-plug display and headless/no-window option.
5. PLAT-06 offers NSView/CAMetalLayer, actual backing-pixel extent, display HDR/refresh/scale and per-window SurfaceEpoch to GFX-01. GFX-01 **alone** owns MTLDevice/commands/present/shaders via GFX-02 and device lost/recreation; SDL Metal view creation does not choose MTLDevice. No duplicate Metal renderer. Metal4 and advanced features conditional per actual Apple Silicon/OS/MTLDevice, Intel reduced capabilities if supported, no universal Vulkan translation/hardware ray tracing/FPS claim.
6. GAME-01 owns stable ActionIds, remap, seat and focus. CORE-01 macOS SDL/GameController bridge produces one ordered event stream with modifiers, IME, trackpad, controller remap/device generation. Permission/TCC Accessibility, Input Monitoring and file access may be DENIED; no root, TCC bypass or raw user text/credential logging.
7. PLAT-06 declares ABI/package constraints only; PLAT-05/BIZ-03 own signed release/updates, owner approval of channel. Both app and nested dylib/helpers require compatible CPU slices, tested min macOS APIs, security-scoped user files and license/notice. Mac App Store requires App Sandbox; external Developer ID notarization needs valid Developer ID, hardened runtime, secure timestamp/ticket/stapling/Gatekeeper tests. Apple account/signing costs and enrollment remain unapproved.
8. No false free Apple publishing from public CI, ad-hoc signed debug is not release notarized; hardened runtime excludes unsafe JIT/library injection exceptions without explicit security review. No unrestricted AI/MCP/plugin access, no unsigned executable bundles or private API frameworks.
9. 128 future P06 tests with real physical Apple Silicon/selected Intel, original licensed 2D/2.5D/3D scenes and p50/p95/p99/energy/memory/Metal failure receipts. No implementation or actual benchmark now.
10. ADR remains **PROPOSED** until owner freezes Xcode/OS/Intel class/feature tiers/license/DoD. **ALL 80 code WOs BLOCKED**, approved ADR count 0, executor_ready 0, engine false. Do not advance #87.

## Rejected automatic alternatives and tradeoffs
| Alternative | Pros | Not adopted by this research |
|---|---|---|
| Intel-only binary plus Rosetta | quick old build | Rosetta macOS27 final general support, fails native arm64 requirement |
| Universal2 automatically for macOS27 Intel Macs | familiar distribution | Intel Macs cannot run macOS27; Xcode27 changed standard architectures |
| macOS27 Apple Silicon only with no Intel study | simpler QA | catalog explicitly requires Intel compatibility decision for 1.0, leave conditional |
| Dual AppKit and SDL input loops | native flexibility | duplicate focus/controller actions and unsaved close races |
| Vulkan translation as primary Mac backend | reuse shaders | GFX-01 owns choice; feature/license/maintenance cost, Metal native preferred |
| Metal4 unconditional required tier | advanced graphics | Intel/older devices and family differences, no real proof |
| Self-sign/notary without account | cheap public release | Developer ID/notary/Gatekeeper requirements, owner finance control |
| Disable Hardened Runtime or grant JIT globally | plugin convenience | high security risk/certification failure |
| Gatekeeper quarantine remove in installer | simpler onboarding | bypasses protection; forbidden |
| Hosted Mac CI screenshot as physical evidence | quick | cannot prove real Metal/GPU/input/thermal/Retina device |
| GPU working-set recommendation as hard RAM cap | easy budget | advisory, GPU/CPU unified memory different metrics |
| Full Disk Access/Accessibility by default | easy tooling | violates TCC privacy and least privilege |

## Acceptance and consequences
A new narrow macOS adapter, CPU/OS profile matrix, Metal layer boundary, API/contract and security distribution requirements; architectural complexity is limited by CORE/GFX/GAME owners. Code future gate: selected 1.0 release class and Intel status, actual Apple Silicon and conditional Intel hardware/OS, reproducible universal2 or architecture-specific builds, actual MTL tier, TCC, App sandbox/Developer ID channel, licenses/SBOM, unit/integration/security/benchmarks, independent objective review. Only documentary research APPROVED can be claimed.

[Architecture](../architecture/plat-06-macos-desktop-target.md) · [technology/security matrix](../research/plat-06-macos-technology-license-security-matrix.md) · [API](../contracts/plat-06-macos-target-api.md).
