# PLAT-04 — Mobile Physical Device Vulkan/Metal, Battery, Thermal and Startup Benchmark Protocol

**2026-11-15 | FUTURE PROTOCOL ONLY, NOT MEASURED.** Work Order NLE-P00-WO-002-PLAT-04 | research #333 | coding #88 BLOCKED. No compiled Android/iOS game, actual phone/tablet, signed app, GPU counter, battery instrument, frame data or store submission from P00.

## Objective and truth boundary
After owner selects Android and/or iOS/iPadOS target class/minimum hardware/OS and cost, obtain repeatable, physically measured native GPU and GAME-01 input compatibility of an original licensed **2D and representative 3D scene**, correct foreground/background/OS resume, dynamically selected GPU quality tier, sustained frame-time/power/thermal state and honest store permission/package validation. A headless emulator/simulator cannot certify physical GPU performance, thermal behavior, battery life or accessibility.

## Future device matrix CANDIDATE only
| Device | Real hardware proposal | Required evidence when selected |
|---|---|---|
| AND-HW-A | Android ARM64/API36+ physical Vulkan1.1+ baseline device, named SoC/GPU (Mali/Adreno/other) | real VkPhysicalDevice features+driver, 2D/3D, touch, frame/thermal/battery |
| AND-HW-B | low-RAM 4KiB/16KiB page Android physical device if profile selected | 16KiB ELF/native libs, memory trim, crash/recover, realistic GPU budget |
| AND-HW-C | approved Vulkan-unsupported/reduced-tier OpenGL ES compatible Android device | actual GFX-01 GL renderer, feature/quality explicit reduced and acceptance |
| AND-HW-D | phone/tablet foldable or large-screen orientation/hinge/variable display | safe areas/dp/pixel/rotation/IME/gesture/physical haptics |
| IOS-HW-A | owner-selected physical iPhone ARM64 with named iOS version and Metal GPU family | genuine signed debug app, real MTLDevice/2D/3D, touch, thermals |
| IOS-HW-B | supported iPadOS Metal device, pointer/keyboard/gamepad and multiwindow | UIKit scene lifecycle, accessibility, multi-screen DPI/format |
| SIM-CI | Android emulator/iOS simulator, version-pinned CI if available | only logic/layout/ABI deterministic checks, **not physical GPU/thermal/pass for native store support** |
| PUBLISH-ONLY | Google Play Console and/or Apple Developer account after owner authorization | signed AAB/IPA, targetSDK/SDK, key/Apple provisioning, policy/privacy/asset receipts, no preapproval in P00 |

## Environment/fingerprint lock for each future run
- Exact source base/head SHA, Context Lock raw SHA-256 for critical decisions, engine/project fixture rights and immutable assets manifest; C++ ABI, SDL3/GameActivity/NDK/Gradle/Xcode SDK versions, build flags, artifact hashes/ELF alignment/signature/provisioning if applicable.
- Physical device model reduced privacy, OS/API version/patch level, supported graphics API and GPU family/driver capability/texture formats, CPU clusters and thermals, RAM/working set, Android page-size, battery health/state/charge/ambient and surface refresh/display geometry; simulator explicitly marked.
- Fixed 2D sprite/alpha/text, 3D representative scene with shader/material/texture and quality tier, CPU sim tick, screen/game controls, exact texture asset and cooked target profile hashes; different texture formats or resolution do **not** compare silently as same visual quality.
- Raw lifecycle (background/foreground/rotation/low-memory kill, transient interruption), pointer events, Game ActionIds/IME and accessibility oracle, permission grants/denials, Android ADPF thermal/Performance Hint availability and iOS thermalState/Low Power signals with timestamps/UNKNOWN.
- Networking and assets: cold/warm cache, Play Asset Delivery install/fast-follow/on-demand if selected, lost connection/eviction/offline, received bytes/decode/GPU upload, last-good generation; no untrusted source/private credentials.
- Store route: Android target SDK API36+ as of Aug2026, 16KiB-page ELF requirements for 64-bit native, iOS upload Xcode26+/iOS SDK26 and iOS13+ targeting; verify exact actual submission-date policy not inferred from source date.

## Proposed future benchmark suite
| Protocol | Scenario | Independent outputs |
|---|---|---|
| MOB-B01 | cold-start real Android ARM64 Vulkan or approved GL game | first-interactive p50/p95, app/asset/GPU init bytes |
| MOB-B02 | warm-start Android same signed build hash | cached asset startup delta and offline state |
| MOB-B03 | cold/warm native iPhone Metal | CPU/Metal init, UIKit scene activation and start p50/p95 |
| MOB-B04 | original 2D alpha/UI/glyph scene on Android/iOS selected | pixel golden, DPR/touch hit tests, actual GPU/CPU frame |
| MOB-B05 | original representative 3D scene on selected Android Vulkan/iOS Metal | material/geometry/fallback quality, frame p50/p95/p99 |
| MOB-B06 | 30-60min sustained Android game battery/AC | raw thermal headroom/status, frame degradation/energy/pacing |
| MOB-B07 | 30-60min sustained iPhone game battery/AC | thermalState/Low Power, CPU/GPU frame+power and stable quality |
| MOB-B08 | Android 16KiB page/native memory stress | ELF alignment, real 16KiB device or emulator auxiliary + alloc/mmap |
| MOB-B09 | Android activity stop/surface destroy/rotation/fold | resource generation and input cancel/last-good save |
| MOB-B10 | iOS scene background/suspended/memory pressure | resource epoch, saved session, user-visible resume |
| MOB-B11 | multitouch/stylus/controller/IME physical gesture maps | GAME ActionIds, latency/contact CANCEL and accessibility |
| MOB-B12 | memory trim/asset decode/low RAM | peak RSS, GPU estimate/alloc, OOM/jet-sam recovery |
| MOB-B13 | Play Asset Delivery/on-demand/offline/eviction if approved | verified immutable manifest, storage bytes, bytes-per-frame stalls |
| MOB-B14 | dynamic resolution and GPU tier/fold safe areas | no text blur, 2D/3D golden, touch/VoiceOver labels |
| MOB-B15 | signed AAB/IPA store policy/privacy proof if owner authorizes | exact uploaded targetSDK/SDK/provisioning, Play/App review outcome |
| MOB-B16 | end-to-end source/license/security release review | SBOM, privacy permission, anti-injection, rollback and owner verdict |

## Statistical and power methodology
- Specify numeric min device/test scene/budget **before** future benchmarking, with target sustained p50/p95/p99, cold/warm startup, energy per gameplay minute, RAM, GPU allocation and asset download, thermal state and user-facing quality. No fixed universal "60FPS", "120FPS" or ARM/Metal/Vulkan performance parity.
- For p99 provide thousands of per-frame samples across 30-60-minute sustained periods and multiple runs (e.g. ≥5 independent trials) with confidence bounds and warm-up/thermal control. Five run-level samples cannot establish p99. Use calibrated CPU/GPU/event/display clock domains, label unsupported GPU counters and privacy restrictions. Avoid falsifying battery mWh values from charge percentage alone.
- Apply identical original fixture/quality tier/target resolution/frame cap for fair A/B comparisons; publish reduced graphics/ASTC differences explicitly. Record display refresh, OS low power policy, environmental/ambient temperature, battery charge/health, device case and thermal throttle and whether official ADPF/iOS thermal API was actually supported. No altering safety protections or OS governor with root.
- Security: no real user data, account credentials, unauthorized store/billing or per-user telemetry in public artifacts. Any hardware fleet or paid account provision subject to owner approval; if absent, mark BLOCKED/NOT_EXECUTED.

## Future receipt and Stop Condition
`MobileSustainedBenchmarkReceiptV1`: source/build+SDK/artifact hashes, real device and OS/GPU/driver/page-size, approved supported target profile, source scene assets, full quality settings, safe-area/display metrics, start/stop/foreground epochs, raw frame/GPU-input/energy/thermal/memory samples with uncertainty and missing-sensor flags, store policy and signature only when authorized, failure/rollback logs, privacy rights/security/SBOM, owner target class and threshold verdict. **Not produced in P00**.

[128 future tests](../testing/plat-04-acceptance-matrix.md) · [architecture](../architecture/plat-04-mobile-target-adaptation.md) · [license/security](plat-04-mobile-technology-license-security-matrix.md).
