# PLAT-06 — Real Mac Hardware/Metal Performance & Release Benchmark Protocol

2026-11-15 | P00 DOCUMENTARY PROTOCOL ONLY | NLE-P00-WO-002-PLAT-06 | research #329 | future coding #87 BLOCKED.

**NOT MEASURED:** zero real Mac GPU/ARM64/Intel app builds, frame timing, Metal shader captures, signed/notarized bundles, executable test or public release. A hosted CI runner may compile future code, but cannot substitute real display/GPU/TCC/notary test.

## Real physical Mac target matrix (candidate, not ratified)
| Profile | Hardware/OS | Future test obligation |
|---|---|---|
| MAC-A | physical Apple Silicon M-family, macOS27, Xcode27 host | primary arm64 native Editor and exported 2D/2.5D/3D, Metal family/limits/sleep/input, real FPS samples |
| MAC-B | oldest owner-approved Apple Silicon device with selected min macOS | weak-linked API, low tier GPU, memory/thermal, app compatibility |
| MAC-C | Apple Silicon laptop, battery/AC, Retina built-in + external varied refresh/scale/gamut | multi-window, fullscreen Space, HDR/P3 if supported, input focus, energy and sleep |
| MAC-D CONDITIONAL | actual Intel Mac on supported macOS <=26 with x86_64 native GPU | only if owner selects Intel 1.0, actual x86_64 Editor/game/Metal and input support |
| MAC-E comparison only | x86_64 code under Rosetta on Apple Silicon macOS27 | record translated status; not Intel native machine nor supported future default |
| MAC-CI | public GitHub macOS runner, named SDK/Xcode/runner revision | deterministic docs/build/unit/checks but not Mac GPU/TCC/performance/physical display evidence |
| MAC-SIGN future approved | Apple Developer ID/notary and external Mac launch / or separate App Store sandbox | signing/entitlement/Gatekeeper verification, requires owner-approved account/keys and distribution channel |

## Evidence lock required for each future run
- Base/head source SHA, frozen source hierarchy and raw SHA-256 contract fingerprints; exact third-party version/licenses, C++ compiler/Xcode/macOS SDK/CMake/SDL3/release optimization flags, deployment target, nested Mach-O build slice and Info.plist artifact sha.
- Physical Mac family/model/processor, OS build, actual native vs Rosetta translation state, MTLDevice family/feature/pixel format, Metal shader tier, display point/backing pixel geometry, refresh rate and color profile; any device ID in user-facing telemetry redacted.
- Exact rights-cleared 2D alpha/text, 2.5D layered scene, representative 3D mesh/material/lighting original asset hashes and rendering tiers. Native Editor project open/edit/build/save/close plus exported game startup/input/exit and failure rollback.
- Battery/power/thermal/memory pressure state, external monitor/retina/proMotion and user TCC/VoiceOver/IME conditions; CPU clock, GPU counter and display scanout timing domains may not be directly comparable.
- Signing when approved: Developer ID certificate public fingerprint, hardened runtime+entitlements, nested executable seals, secure timestamp, actual notary ticket/stapling/Gatekeeper first-launch, file scope and Mac Sandbox channel. Never expose private keys.

## Future benchmark suite
| ID | Scenario | Raw measurements / semantic oracle |
|---|---|---|
| MAC-B01 | Cold Editor launch and exit (empty project) | first responsive frame, CPU/IO time, bundle and window epoch |
| MAC-B02 | Warm Editor project reopen | p50/p95 startup, cache hit state, safe file scope |
| MAC-B03 | Exported original 2D scene build/open/close | alpha/glyph golden, CPU/GPU frame and backing pixels |
| MAC-B04 | Exported original 2.5D scene build/open/close | camera/layer quality golden, resource lifetime |
| MAC-B05 | Exported representative 3D scene build/open/close | material/light/pipeline quality, Metal limits |
| MAC-B06 | ARM64 vs conditional native x86_64 Mach-O | lipo/file/otool/vtool slices and actual physical Intel proof |
| MAC-B07 | Retina multi-monitor 1x/2x/scaled | backing conversion, input-to-UI alignment |
| MAC-B08 | Fullscreen/occlusion/variable refresh/wide color | frame pacing, format/gamut only supported |
| MAC-B09 | 1000 cycles hide/resize/sleep/wake/monitor detach | GPU/drawable/window epochs, leak and restart |
| MAC-B10 | GPU missing/Metal invalid pipeline/memory pressure | typed capability decline/recover and present safety |
| MAC-B11 | Cmd/IME/VoiceOver/gamepad/haptics/TCC | GAME-01 action mapping, permission denied and focus |
| MAC-B12 | Unified memory vs Intel GPU memory tiers | current allocated vs recommended advisory, RSS and pressure |
| MAC-B13 | Power/thermal on AC and battery | p50/p95/p99 frames, energy and sustained performance |
| MAC-B14 | Editor multiple windows and project unsaved close | UI responsiveness, event order, no data loss |
| MAC-B15 | Developer ID/notary/quarantine or App Store sandbox | actual approved channel signer/entitlements/ticket/Gatekeeper |
| MAC-B16 | Entire licensed build/export/upgrade/rollback | SHA, SBOM, project integrity, security and owner DoD |

## Statistical and safety protocol
- At least five cold/warm independent trials and enough **raw per-frame and input observations** to estimate p95/p99 with meaningful confidence, record raw outliers, invalid sample count and timing clock precision. Never deduce p99 from five run-level observations.
- CPU/GPU, display and input timestamps have different clocks and observation privilege. GPU counters only if actual MTLDevice supports; never invent physical GPU memory if only process estimates available. Publish measurement uncertainty and cost of instrumentation.
- Randomize comparable tier ordering/AC battery and selected thermal conditions. Compare arm64/Intel only if same scene/asset hashes/feature tiers; reduced Intel quality must be labeled distinct, not performance equivalence.
- Successful free Docs CI is NOT physical GPU, notarization, privacy or commercial release. If no Apple hardware/approved distribution account, mark BLOCKED/NOT_EXECUTED not PASS.
- Original game/user-safe corpus, no real user files/credentials, no unsafe root installer or entitlement bypass. Future release requires independent risk audit, owner-approved Intel scope and 1.0 DoD.

## Future benchmark receipt
MacBenchmarkReceiptV1: source/SDK/SDL/ABI/artifact SHA, actual hw architecture vs translated flag, OS/GPU/MTL family, display/backing and refresh, 2D/2.5D/3D fixture hash, raw frame/input/CPU/GPU samples with clock-domain uncertainty, thermal/battery, memory advisory and actual allocations, device loss and awake/resume journal, rights/SBOM, signature/notary/Gatekeeper status if authorized, verdict and remaining blockers.

[128 tests](../testing/plat-06-acceptance-matrix.md) · [Architecture](../architecture/plat-06-macos-desktop-target.md) · [technology and rights](plat-06-macos-technology-license-security-matrix.md).
