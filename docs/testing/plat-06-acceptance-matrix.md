# PLAT-06 — Exactly 128 FUTURE macOS Target Acceptance Tests

2026-11-15 | P00 DOCUMENTATION ONLY | NLE-P00-WO-002-PLAT-06 | research #329 | future code #87 OPEN/BLOCKED | source 109287f928b4436b31188c1dd8cf4f7a454ad989. Formal deps CORE-01 + GFX-01 + GAME-01 only.

**P06-T001..P06-T128: eight groups of sixteen, exactly 128 unique tests, ALL FUTURE / NOT EXECUTED. No test binary, macOS Metal device, real Apple Silicon or Intel hardware, project build, signing or notarization executed.**

## Future acceptance rules and independent proof
1. Real physical Apple Silicon arm64 native Editor and exported 2D/2.5D/3D games build/open/close with actual macOS/Metal capabilities. Minimum OS/hardware tiers ratified later by owner; macOS27 Apple Silicon is reference candidate.
2. Intel Mac support for 1.0 is **UNDECIDED**. If required, physical Intel Mac on eligible macOS <=26 with actual x86_64 Mach-O and device smoke, not just Rosetta on ARM or universal2 file metadata. MacOS27 is not an Intel Mac host.
3. CORE-01 owns AppKit/SDL process/delegate/event and window epochs, GFX-01 owns MTLDevice/RHI/loss and CAMetalLayer surface lifetime, GAME-01 owns action remap, focus and permission-bound input. No duplicate event loop or GPU resource owner.
4. Physical keyboard/trackpad/pads, TCC permissions, VoiceOver/IME and user-selected project file scope must be verified on a real Mac, including denied paths and unsaved project close veto.
5. Notarization tests apply only to explicitly owner-approved distribution channel and actual Developer ID credentials. Ad-hoc signing, free Docs Validation and hosted GitHub runner never count as notarized public App or real Metal benchmark.
6. Licenses, source hashes, SDK/Xcode and nested Mach-O slices, entitlements, minimum OS weak linking, user privacy, negative inputs, IO, GPU memory, sleep/wake and device loss require independent oracles.
7. Performance p50/p95/p99 needs adequate raw frame/input samples, known clock domains and target machine/quality tier; no universal 60/120 FPS, HDR, Metal4 or Intel feature guarantee.
8. Block on high/critical, STALE Context Lock, owner unapproved Intel/macos min/release classes, unratified predecessor ADR, source license NLE-D009 OPEN or missing hardware/rights; future statuses PASS/FAIL/UNSUPPORTED/NOT_EXECUTED only based on observations.

## Group 1: ARCH-OS-SDK

| Future case | Assertion / scenario | Independent verification | Status |
|---|---|---|---|
| P06-T001 | Apple Silicon arm64 app and game Mach-O compiled with pinned C++20 toolchain | lipo/file/otool/vtool actual Mach-O/SDK/arch, physical Mac/Rosetta state, pinned build provenance | FUTURE / NOT EXECUTED |
| P06-T002 | Physical Apple Silicon launches native arm64 with no Rosetta | lipo/file/otool/vtool actual Mach-O/SDK/arch, physical Mac/Rosetta state, pinned build provenance | FUTURE / NOT EXECUTED |
| P06-T003 | Xcode27 build host identified as physical Apple Silicon | lipo/file/otool/vtool actual Mach-O/SDK/arch, physical Mac/Rosetta state, pinned build provenance | FUTURE / NOT EXECUTED |
| P06-T004 | Min deployment macOS27 does not imply physical Intel Mac compatibility | lipo/file/otool/vtool actual Mach-O/SDK/arch, physical Mac/Rosetta state, pinned build provenance | FUTURE / NOT EXECUTED |
| P06-T005 | Conditional owner-approved native x86_64 on physical Intel Mac macOS26 or older eligible | lipo/file/otool/vtool actual Mach-O/SDK/arch, physical Mac/Rosetta state, pinned build provenance | FUTURE / NOT EXECUTED |
| P06-T006 | Universal2 main executable contains arm64 and x86_64 slices | lipo/file/otool/vtool actual Mach-O/SDK/arch, physical Mac/Rosetta state, pinned build provenance | FUTURE / NOT EXECUTED |
| P06-T007 | Every nested framework/helper/dylib includes required architecture slices | lipo/file/otool/vtool actual Mach-O/SDK/arch, physical Mac/Rosetta state, pinned build provenance | FUTURE / NOT EXECUTED |
| P06-T008 | Xcode27 ARCHS explicit x86_64 override recorded where required | lipo/file/otool/vtool actual Mach-O/SDK/arch, physical Mac/Rosetta state, pinned build provenance | FUTURE / NOT EXECUTED |
| P06-T009 | Rosetta-translated process identified separately from physical Intel hardware | lipo/file/otool/vtool actual Mach-O/SDK/arch, physical Mac/Rosetta state, pinned build provenance | FUTURE / NOT EXECUTED |
| P06-T010 | Native ARM64 never requires Rosetta at runtime | lipo/file/otool/vtool actual Mach-O/SDK/arch, physical Mac/Rosetta state, pinned build provenance | FUTURE / NOT EXECUTED |
| P06-T011 | Runtime weak-link availability guarded on selected old macOS | lipo/file/otool/vtool actual Mach-O/SDK/arch, physical Mac/Rosetta state, pinned build provenance | FUTURE / NOT EXECUTED |
| P06-T012 | C++ ABI/alignment/calling convention verified across architecture slices | lipo/file/otool/vtool actual Mach-O/SDK/arch, physical Mac/Rosetta state, pinned build provenance | FUTURE / NOT EXECUTED |
| P06-T013 | Mach-O SDK and min deployment LC_BUILD_VERSION proof | lipo/file/otool/vtool actual Mach-O/SDK/arch, physical Mac/Rosetta state, pinned build provenance | FUTURE / NOT EXECUTED |
| P06-T014 | Toolchain/compiler/SDK SHA and external license receipts preserved | lipo/file/otool/vtool actual Mach-O/SDK/arch, physical Mac/Rosetta state, pinned build provenance | FUTURE / NOT EXECUTED |
| P06-T015 | Platform profile rejects Intel Mac macOS27 impossible host combination | lipo/file/otool/vtool actual Mach-O/SDK/arch, physical Mac/Rosetta state, pinned build provenance | FUTURE / NOT EXECUTED |
| P06-T016 | Reproducible artifact hashes or deterministic variation documented | lipo/file/otool/vtool actual Mach-O/SDK/arch, physical Mac/Rosetta state, pinned build provenance | FUTURE / NOT EXECUTED |

## Group 2: COCOA-WINDOWS-LIFECYCLE

| Future case | Assertion / scenario | Independent verification | Status |
|---|---|---|---|
| P06-T017 | One SDL3/NSApplicationDelegate event pump authority | single CORE SDL/NSApplication event journal, main-thread/window epoch, saved-document oracle | FUTURE / NOT EXECUTED |
| P06-T018 | AppKit window creation only on main thread | single CORE SDL/NSApplication event journal, main-thread/window epoch, saved-document oracle | FUTURE / NOT EXECUTED |
| P06-T019 | SDL Metal view created exclusively on main thread | single CORE SDL/NSApplication event journal, main-thread/window epoch, saved-document oracle | FUTURE / NOT EXECUTED |
| P06-T020 | Custom app delegate forwards quit and open-file events | single CORE SDL/NSApplication event journal, main-thread/window epoch, saved-document oracle | FUTURE / NOT EXECUTED |
| P06-T021 | Editor unsaved project vetoes close without data loss | single CORE SDL/NSApplication event journal, main-thread/window epoch, saved-document oracle | FUTURE / NOT EXECUTED |
| P06-T022 | Closing game window does not kill unrelated Editor windows | single CORE SDL/NSApplication event journal, main-thread/window epoch, saved-document oracle | FUTURE / NOT EXECUTED |
| P06-T023 | Window epochs reject post-destroy async callbacks | single CORE SDL/NSApplication event journal, main-thread/window epoch, saved-document oracle | FUTURE / NOT EXECUTED |
| P06-T024 | Fullscreen Space/mission control transitions preserve session | single CORE SDL/NSApplication event journal, main-thread/window epoch, saved-document oracle | FUTURE / NOT EXECUTED |
| P06-T025 | Occluded/minimized window throttles presents without busy-loop | single CORE SDL/NSApplication event journal, main-thread/window epoch, saved-document oracle | FUTURE / NOT EXECUTED |
| P06-T026 | Monitor movement updates NSView backing pixel geometry | single CORE SDL/NSApplication event journal, main-thread/window epoch, saved-document oracle | FUTURE / NOT EXECUTED |
| P06-T027 | Retina and display scaling conversions preserve mouse hit tests | single CORE SDL/NSApplication event journal, main-thread/window epoch, saved-document oracle | FUTURE / NOT EXECUTED |
| P06-T028 | Zero backing area emits resize error without invalid drawable | single CORE SDL/NSApplication event journal, main-thread/window epoch, saved-document oracle | FUTURE / NOT EXECUTED |
| P06-T029 | External monitor hotplug does not crash Editor/game | single CORE SDL/NSApplication event journal, main-thread/window epoch, saved-document oracle | FUTURE / NOT EXECUTED |
| P06-T030 | Sleep/wake rehydrates or requires typed restart | single CORE SDL/NSApplication event journal, main-thread/window epoch, saved-document oracle | FUTURE / NOT EXECUTED |
| P06-T031 | Headless tool starts without visible NSApplication windows | single CORE SDL/NSApplication event journal, main-thread/window epoch, saved-document oracle | FUTURE / NOT EXECUTED |
| P06-T032 | Application terminate during async save obeys owner transaction | single CORE SDL/NSApplication event journal, main-thread/window epoch, saved-document oracle | FUTURE / NOT EXECUTED |

## Group 3: METAL-GRAPHICS

| Future case | Assertion / scenario | Independent verification | Status |
|---|---|---|---|
| P06-T033 | CAMetalLayer lease associated with GFX-01-selected MTLDevice | actual GFX-01 Metal device/layer capability and original licensed 2D/2.5D/3D golden scenes | FUTURE / NOT EXECUTED |
| P06-T034 | SDL Metal view alone does not incorrectly assume assigned device | actual GFX-01 Metal device/layer capability and original licensed 2D/2.5D/3D golden scenes | FUTURE / NOT EXECUTED |
| P06-T035 | Actual Metal family/features/limits determine RHI tier | actual GFX-01 Metal device/layer capability and original licensed 2D/2.5D/3D golden scenes | FUTURE / NOT EXECUTED |
| P06-T036 | Metal4 advanced feature disabled when MTL/OS unsupported | actual GFX-01 Metal device/layer capability and original licensed 2D/2.5D/3D golden scenes | FUTURE / NOT EXECUTED |
| P06-T037 | Intel legacy reduced Metal path only with real GPU capability | actual GFX-01 Metal device/layer capability and original licensed 2D/2.5D/3D golden scenes | FUTURE / NOT EXECUTED |
| P06-T038 | Invalid shader/pipeline returns typed GFX-02 error | actual GFX-01 Metal device/layer capability and original licensed 2D/2.5D/3D golden scenes | FUTURE / NOT EXECUTED |
| P06-T039 | Physical arm64 2D alpha/painter order passes golden test | actual GFX-01 Metal device/layer capability and original licensed 2D/2.5D/3D golden scenes | FUTURE / NOT EXECUTED |
| P06-T040 | Real 2.5D layer/camera scene passes golden test | actual GFX-01 Metal device/layer capability and original licensed 2D/2.5D/3D golden scenes | FUTURE / NOT EXECUTED |
| P06-T041 | Representative real 3D scene renders/builds/closes | actual GFX-01 Metal device/layer capability and original licensed 2D/2.5D/3D golden scenes | FUTURE / NOT EXECUTED |
| P06-T042 | Retina text/UI does not blur when 3D resolution reduces | actual GFX-01 Metal device/layer capability and original licensed 2D/2.5D/3D golden scenes | FUTURE / NOT EXECUTED |
| P06-T043 | sRGB/P3 conversion tested, HDR optional after capability query | actual GFX-01 Metal device/layer capability and original licensed 2D/2.5D/3D golden scenes | FUTURE / NOT EXECUTED |
| P06-T044 | Variable/ProMotion refresh measured instead of hard-coded 60/120Hz | actual GFX-01 Metal device/layer capability and original licensed 2D/2.5D/3D golden scenes | FUTURE / NOT EXECUTED |
| P06-T045 | No drawable after minimize/resize handled safely | actual GFX-01 Metal device/layer capability and original licensed 2D/2.5D/3D golden scenes | FUTURE / NOT EXECUTED |
| P06-T046 | Display detach/device epoch invalidates stale GPU handles | actual GFX-01 Metal device/layer capability and original licensed 2D/2.5D/3D golden scenes | FUTURE / NOT EXECUTED |
| P06-T047 | Metal command/device failure rehydrates or RESTART_REQUIRED | actual GFX-01 Metal device/layer capability and original licensed 2D/2.5D/3D golden scenes | FUTURE / NOT EXECUTED |
| P06-T048 | Recommended GPU working set treated advisory not RAM/VRAM promise | actual GFX-01 Metal device/layer capability and original licensed 2D/2.5D/3D golden scenes | FUTURE / NOT EXECUTED |

## Group 4: INPUT-TCC-A11Y

| Future case | Assertion / scenario | Independent verification | Status |
|---|---|---|---|
| P06-T049 | SDL3 and Apple Game Controller events deduplicated | CORE single input journal and GAME-01 action oracle, physical controllers/TCC user consent/VoiceOver | FUTURE / NOT EXECUTED |
| P06-T050 | GAME-01 semantic ActionId stable between Editor and exported game | CORE single input journal and GAME-01 action oracle, physical controllers/TCC user consent/VoiceOver | FUTURE / NOT EXECUTED |
| P06-T051 | Cmd/Option/Control physical and logical modifiers accurate | CORE single input journal and GAME-01 action oracle, physical controllers/TCC user consent/VoiceOver | FUTURE / NOT EXECUTED |
| P06-T052 | Keyboard scancode and IME composition events separated | CORE single input journal and GAME-01 action oracle, physical controllers/TCC user consent/VoiceOver | FUTURE / NOT EXECUTED |
| P06-T053 | CJK and RTL keyboard composition preserves text and game focus | CORE single input journal and GAME-01 action oracle, physical controllers/TCC user consent/VoiceOver | FUTURE / NOT EXECUTED |
| P06-T054 | Trackpad scroll momentum/gesture units normalized | CORE single input journal and GAME-01 action oracle, physical controllers/TCC user consent/VoiceOver | FUTURE / NOT EXECUTED |
| P06-T055 | Relative mouse mode denied on unsupported/TCC scope without privilege | CORE single input journal and GAME-01 action oracle, physical controllers/TCC user consent/VoiceOver | FUTURE / NOT EXECUTED |
| P06-T056 | Focus loss releases held keys/buttons and axes | CORE single input journal and GAME-01 action oracle, physical controllers/TCC user consent/VoiceOver | FUTURE / NOT EXECUTED |
| P06-T057 | Controller detach/reconnect invalidates device epochs | CORE single input journal and GAME-01 action oracle, physical controllers/TCC user consent/VoiceOver | FUTURE / NOT EXECUTED |
| P06-T058 | User-remapped gamepad buttons resolve via GAME-01 mapping | CORE single input journal and GAME-01 action oracle, physical controllers/TCC user consent/VoiceOver | FUTURE / NOT EXECUTED |
| P06-T059 | Controller haptics unavailable degrades without crash | CORE single input journal and GAME-01 action oracle, physical controllers/TCC user consent/VoiceOver | FUTURE / NOT EXECUTED |
| P06-T060 | TCC Input Monitoring denial prevents background keystroke capture | CORE single input journal and GAME-01 action oracle, physical controllers/TCC user consent/VoiceOver | FUTURE / NOT EXECUTED |
| P06-T061 | TCC Accessibility denied yields accessible fallback | CORE single input journal and GAME-01 action oracle, physical controllers/TCC user consent/VoiceOver | FUTURE / NOT EXECUTED |
| P06-T062 | VoiceOver keyboard navigation and focus assertions pass | CORE single input journal and GAME-01 action oracle, physical controllers/TCC user consent/VoiceOver | FUTURE / NOT EXECUTED |
| P06-T063 | Microphone/camera capture impossible without separately approved consent | CORE single input journal and GAME-01 action oracle, physical controllers/TCC user consent/VoiceOver | FUTURE / NOT EXECUTED |
| P06-T064 | Input traces redact private text and HID hardware identifiers | CORE single input journal and GAME-01 action oracle, physical controllers/TCC user consent/VoiceOver | FUTURE / NOT EXECUTED |

## Group 5: PACKAGE-SIGNING

| Future case | Assertion / scenario | Independent verification | Status |
|---|---|---|---|
| P06-T065 | Info.plist bundle id/version/minimum OS correctly embedded | PLAT-05/BIZ-03 certificate+entitlements/Apple notary/Gatekeeper independent receipt | FUTURE / NOT EXECUTED |
| P06-T066 | All nested Mach-O dependencies and rpaths signed and verified | PLAT-05/BIZ-03 certificate+entitlements/Apple notary/Gatekeeper independent receipt | FUTURE / NOT EXECUTED |
| P06-T067 | Ad-hoc debug signature not labeled Developer ID notarization | PLAT-05/BIZ-03 certificate+entitlements/Apple notary/Gatekeeper independent receipt | FUTURE / NOT EXECUTED |
| P06-T068 | Developer ID certificate type and holder validated when channel approved | PLAT-05/BIZ-03 certificate+entitlements/Apple notary/Gatekeeper independent receipt | FUTURE / NOT EXECUTED |
| P06-T069 | Hardened Runtime enabled for external notarization submission | PLAT-05/BIZ-03 certificate+entitlements/Apple notary/Gatekeeper independent receipt | FUTURE / NOT EXECUTED |
| P06-T070 | Entitlement allowlist minimizes JIT/library validation exceptions | PLAT-05/BIZ-03 certificate+entitlements/Apple notary/Gatekeeper independent receipt | FUTURE / NOT EXECUTED |
| P06-T071 | Signed nested frameworks and secure timestamps validated | PLAT-05/BIZ-03 certificate+entitlements/Apple notary/Gatekeeper independent receipt | FUTURE / NOT EXECUTED |
| P06-T072 | Apple notary success ticket verified on artifact hash | PLAT-05/BIZ-03 certificate+entitlements/Apple notary/Gatekeeper independent receipt | FUTURE / NOT EXECUTED |
| P06-T073 | Stapling/Gatekeeper launch checked on clean actual Mac | PLAT-05/BIZ-03 certificate+entitlements/Apple notary/Gatekeeper independent receipt | FUTURE / NOT EXECUTED |
| P06-T074 | Tampered signed dynamic library rejected by Gatekeeper/release checks | PLAT-05/BIZ-03 certificate+entitlements/Apple notary/Gatekeeper independent receipt | FUTURE / NOT EXECUTED |
| P06-T075 | App Store channel gated on App Sandbox capability | PLAT-05/BIZ-03 certificate+entitlements/Apple notary/Gatekeeper independent receipt | FUTURE / NOT EXECUTED |
| P06-T076 | Sandbox user-selected file scope grants only intended project | PLAT-05/BIZ-03 certificate+entitlements/Apple notary/Gatekeeper independent receipt | FUTURE / NOT EXECUTED |
| P06-T077 | Stale security-scoped bookmark revoked on logout/close | PLAT-05/BIZ-03 certificate+entitlements/Apple notary/Gatekeeper independent receipt | FUTURE / NOT EXECUTED |
| P06-T078 | Downloaded/quarantined external app launches only when approved and verified | PLAT-05/BIZ-03 certificate+entitlements/Apple notary/Gatekeeper independent receipt | FUTURE / NOT EXECUTED |
| P06-T079 | Upgrade/rollback preserves previous authorized project source | PLAT-05/BIZ-03 certificate+entitlements/Apple notary/Gatekeeper independent receipt | FUTURE / NOT EXECUTED |
| P06-T080 | No developer payment/key/signing assumption from free Docs CI | PLAT-05/BIZ-03 certificate+entitlements/Apple notary/Gatekeeper independent receipt | FUTURE / NOT EXECUTED |

## Group 6: SECURITY-RECOVERY

| Future case | Assertion / scenario | Independent verification | Status |
|---|---|---|---|
| P06-T081 | DYLD injection prohibited by approved hardened security profile | sandboxed denial fixture, no unintended source/system changes, resource/lifetime trace | FUTURE / NOT EXECUTED |
| P06-T082 | Unsigned executable plugin/JIT refused without formal security ADR | sandboxed denial fixture, no unintended source/system changes, resource/lifetime trace | FUTURE / NOT EXECUTED |
| P06-T083 | Untrusted project macro/MCP cannot execute shell by default | sandboxed denial fixture, no unintended source/system changes, resource/lifetime trace | FUTURE / NOT EXECUTED |
| P06-T084 | Architecture-mismatched nested Mach-O fails closed | sandboxed denial fixture, no unintended source/system changes, resource/lifetime trace | FUTURE / NOT EXECUTED |
| P06-T085 | Forged SDL/GC input sequence rejected by GAME owner | sandboxed denial fixture, no unintended source/system changes, resource/lifetime trace | FUTURE / NOT EXECUTED |
| P06-T086 | Unsaved Editor source survives crash and close veto | sandboxed denial fixture, no unintended source/system changes, resource/lifetime trace | FUTURE / NOT EXECUTED |
| P06-T087 | File URL symlink traversal outside user grant prevented | sandboxed denial fixture, no unintended source/system changes, resource/lifetime trace | FUTURE / NOT EXECUTED |
| P06-T088 | TCC/Sandbox denied operation does not request sudo or Full Disk Access | sandboxed denial fixture, no unintended source/system changes, resource/lifetime trace | FUTURE / NOT EXECUTED |
| P06-T089 | Metal drawable released during async resize without use-after-free | sandboxed denial fixture, no unintended source/system changes, resource/lifetime trace | FUTURE / NOT EXECUTED |
| P06-T090 | Late lost-device callback cannot use stale SurfaceEpoch | sandboxed denial fixture, no unintended source/system changes, resource/lifetime trace | FUTURE / NOT EXECUTED |
| P06-T091 | Repeated GPU loss bounded retries and explicit restart | sandboxed denial fixture, no unintended source/system changes, resource/lifetime trace | FUTURE / NOT EXECUTED |
| P06-T092 | Corrupt untrusted asset bundle rejected by DATA owner | sandboxed denial fixture, no unintended source/system changes, resource/lifetime trace | FUTURE / NOT EXECUTED |
| P06-T093 | Installer never silently clears Gatekeeper quarantine | sandboxed denial fixture, no unintended source/system changes, resource/lifetime trace | FUTURE / NOT EXECUTED |
| P06-T094 | Diagnostics redact path/bundle certificates/entitlements secrets | sandboxed denial fixture, no unintended source/system changes, resource/lifetime trace | FUTURE / NOT EXECUTED |
| P06-T095 | GPU memory pressure/thermal throttling bounded and visible | sandboxed denial fixture, no unintended source/system changes, resource/lifetime trace | FUTURE / NOT EXECUTED |
| P06-T096 | Unauthorized AI-native project export/signing action denied and audited | sandboxed denial fixture, no unintended source/system changes, resource/lifetime trace | FUTURE / NOT EXECUTED |

## Group 7: HARDWARE-COMPATIBILITY

| Future case | Assertion / scenario | Independent verification | Status |
|---|---|---|---|
| P06-T097 | Real M-series macOS27 native Editor opens/builds/closes | actual Mac model/OS/GPU with Editor and exported scene build/open/close, not CI simulation | FUTURE / NOT EXECUTED |
| P06-T098 | Real M-series macOS27 exported 2D game opens/builds/closes | actual Mac model/OS/GPU with Editor and exported scene build/open/close, not CI simulation | FUTURE / NOT EXECUTED |
| P06-T099 | Real M-series macOS27 exported 2.5D game opens/builds/closes | actual Mac model/OS/GPU with Editor and exported scene build/open/close, not CI simulation | FUTURE / NOT EXECUTED |
| P06-T100 | Real M-series macOS27 exported 3D game opens/builds/closes | actual Mac model/OS/GPU with Editor and exported scene build/open/close, not CI simulation | FUTURE / NOT EXECUTED |
| P06-T101 | Oldest owner-selected supported Apple Silicon/macOS smoke | actual Mac model/OS/GPU with Editor and exported scene build/open/close, not CI simulation | FUTURE / NOT EXECUTED |
| P06-T102 | Low-RAM Apple Silicon GPU tier explicit supported/unsupported | actual Mac model/OS/GPU with Editor and exported scene build/open/close, not CI simulation | FUTURE / NOT EXECUTED |
| P06-T103 | Conditional native Intel Mac macOS26 Editor smoke if owner ratifies | actual Mac model/OS/GPU with Editor and exported scene build/open/close, not CI simulation | FUTURE / NOT EXECUTED |
| P06-T104 | Conditional native Intel Mac macOS26 2D/2.5D/3D exported game smoke | actual Mac model/OS/GPU with Editor and exported scene build/open/close, not CI simulation | FUTURE / NOT EXECUTED |
| P06-T105 | Owner-declined Intel release scope recorded, never fake PASS | actual Mac model/OS/GPU with Editor and exported scene build/open/close, not CI simulation | FUTURE / NOT EXECUTED |
| P06-T106 | Rosetta translated test separate from Intel-native Mac proof | actual Mac model/OS/GPU with Editor and exported scene build/open/close, not CI simulation | FUTURE / NOT EXECUTED |
| P06-T107 | Built-in/Retina/external display scaling test matrix | actual Mac model/OS/GPU with Editor and exported scene build/open/close, not CI simulation | FUTURE / NOT EXECUTED |
| P06-T108 | Notched Mac safe area/menu/toolbar mouse coordinates accurate | actual Mac model/OS/GPU with Editor and exported scene build/open/close, not CI simulation | FUTURE / NOT EXECUTED |
| P06-T109 | Battery vs AC thermal GPU frames and energy separated | actual Mac model/OS/GPU with Editor and exported scene build/open/close, not CI simulation | FUTURE / NOT EXECUTED |
| P06-T110 | Wired/Bluetooth gamepad reconnect and GAME actions physical device | actual Mac model/OS/GPU with Editor and exported scene build/open/close, not CI simulation | FUTURE / NOT EXECUTED |
| P06-T111 | Keyboard-only VoiceOver/IME accessibility hardware test | actual Mac model/OS/GPU with Editor and exported scene build/open/close, not CI simulation | FUTURE / NOT EXECUTED |
| P06-T112 | Hosted GitHub macOS runner not treated as physical GPU proof | actual Mac model/OS/GPU with Editor and exported scene build/open/close, not CI simulation | FUTURE / NOT EXECUTED |

## Group 8: BENCHMARK-RELEASE

| Future case | Assertion / scenario | Independent verification | Status |
|---|---|---|---|
| P06-T113 | Cold Editor launch on real arm64 Mac and clean cache measured | physical Mac raw memory/CPU/GPU/thermal/timing samples and signing/license/owner proof | FUTURE / NOT EXECUTED |
| P06-T114 | Warm launch separated from cold exact binary build hash | physical Mac raw memory/CPU/GPU/thermal/timing samples and signing/license/owner proof | FUTURE / NOT EXECUTED |
| P06-T115 | Exported 2D game startup-to-interactive sampled with fixture hash | physical Mac raw memory/CPU/GPU/thermal/timing samples and signing/license/owner proof | FUTURE / NOT EXECUTED |
| P06-T116 | Exported 2.5D game startup-to-interactive measured | physical Mac raw memory/CPU/GPU/thermal/timing samples and signing/license/owner proof | FUTURE / NOT EXECUTED |
| P06-T117 | Exported 3D game startup-to-interactive measured | physical Mac raw memory/CPU/GPU/thermal/timing samples and signing/license/owner proof | FUTURE / NOT EXECUTED |
| P06-T118 | CPU frame p50/p95/p99 with enough raw physical samples | physical Mac raw memory/CPU/GPU/thermal/timing samples and signing/license/owner proof | FUTURE / NOT EXECUTED |
| P06-T119 | GPU counter timestamp queried only when hardware supports | physical Mac raw memory/CPU/GPU/thermal/timing samples and signing/license/owner proof | FUTURE / NOT EXECUTED |
| P06-T120 | Input-to-display latency clock domains calibrated or UNKNOWN | physical Mac raw memory/CPU/GPU/thermal/timing samples and signing/license/owner proof | FUTURE / NOT EXECUTED |
| P06-T121 | RAM/currentAllocated/recommendedMaxWorkingSet tracked separately | physical Mac raw memory/CPU/GPU/thermal/timing samples and signing/license/owner proof | FUTURE / NOT EXECUTED |
| P06-T122 | Battery draw/thermal event and power profile tied to frame samples | physical Mac raw memory/CPU/GPU/thermal/timing samples and signing/license/owner proof | FUTURE / NOT EXECUTED |
| P06-T123 | Sleep/wake/resume 1000-cycle long-run device-resource audit | physical Mac raw memory/CPU/GPU/thermal/timing samples and signing/license/owner proof | FUTURE / NOT EXECUTED |
| P06-T124 | Multiple Editor windows/resize/occlusion no unbounded leak | physical Mac raw memory/CPU/GPU/thermal/timing samples and signing/license/owner proof | FUTURE / NOT EXECUTED |
| P06-T125 | Intel vs Apple Silicon comparison same declared feature tier only | physical Mac raw memory/CPU/GPU/thermal/timing samples and signing/license/owner proof | FUTURE / NOT EXECUTED |
| P06-T126 | Approved distribution signature/ticket/Gatekeeper receipt present if released | physical Mac raw memory/CPU/GPU/thermal/timing samples and signing/license/owner proof | FUTURE / NOT EXECUTED |
| P06-T127 | SBOM/licenses/fonts/shaders/SDK redistribution rights checked | physical Mac raw memory/CPU/GPU/thermal/timing samples and signing/license/owner proof | FUTURE / NOT EXECUTED |
| P06-T128 | Full owner-approved 1.0 DoD and independent security audit gate release | physical Mac raw memory/CPU/GPU/thermal/timing samples and signing/license/owner proof | FUTURE / NOT EXECUTED |


## Catalog acceptance remains unverified
"Editor and exported 2D/2.5D/3D game open/build/close on a macOS test matrix, with platform-native graphics checks and recoverable errors." All checks documented above are FUTURE. ADR-0072 PROPOSED, all 80 future implementation WOs BLOCKED, no engine code or hardware proof.

[Architecture](../architecture/plat-06-macos-desktop-target.md) · [benchmark](../research/plat-06-macos-benchmark-protocol.md) · [API](../contracts/plat-06-macos-target-api.md).
