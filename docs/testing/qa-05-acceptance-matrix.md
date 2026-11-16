# QA-05 — Exactly 128 FUTURE Compatibility, Soak, Recovery and Release Qualification Tests (Q05-T001..Q05-T128)

**2026-11-16 | P00 DOCS ONLY, NO TEST RUN OR IMPLEMENTED ENGINE.** Research [#357](https://github.com/KayzenRoot/stormline/issues/357); future code [#94](https://github.com/KayzenRoot/stormline/issues/94) OPEN/BLOCKED, base `a42519c8a79346a4974fa74c44f7cac26f4ad43c`. QA-05 order 76/80; formal predecessors **QA-02 + PLAT-05 EXACT**, ADR-0076/0074/0079 PROPOSED. All 80 future implementation WOs BLOCKED, release class UNDECIDED all, engine false. **EXACTLY EIGHT groups of sixteen scenarios, Q05-T001 through Q05-T128, all FUTURE/NOT EXECUTED and zero PASS.**

## What a future PASS must prove
1. Owner chooses required OS/arch/backend/driver/hardware and Web eligibility; native Windows/Linux/macOS Editor+game destination classes owner-directed, **exact versions/minima unratified**, Intel Mac conditional, mobile out of scope until new decision.
2. QA-02 original deterministic rights-cleared 2D/2.5D/3D/Web scene with audio/input/visual golden approvals and PLAT-05 actual immutable source/export/manifest/ABI/signature used, **not** a doc CI or hypothetical artifact.
3. Hardware true GPU model/driver/version/physical flag and D3D12/Vulkan profile/Metal supportsFamily/WebGPU secure adapter features queried. Software Windows WARP/SwiftShader/llvmpipe/browser synthetic or CI headless cannot qualify real graphics device.
4. Fresh installation in isolated OS with nondev runtime dependencies, C++ toolchain/ABI/SDL/fonts, path/Unicode/permissions, actual signature/notarization once approved, reproducible clean build and asset hashes separate checks.
5. Soak and stress with predefined duration/error metrics per owner and hardware, memory/VRAM/IO/thermal/power if actual sensor, QA-03 p95/p99 optional integration only. No numerical performance targets invented in P00; incomplete/unavailable hardware -> NOT_QUALIFIED.
6. Recovery with original dummy project/save, fail injection after write/rename/migration stages, independent checksum/semantic readback of last-good and backup, no blind “atomic rename makes power safe.” Unsafe downgrade denied with safe backup restore.
7. Web Playwright screenshot per pinned OS/browser, secure context/feature queries and device loss, verified cache update/storage/resume and semantics; browser visual success not native screen-reader or vendor physical graphics equivalent.
8. Real test receipt with source/artifact/fixture SHA and versions, host device/physical flag, logs/failure trace, user privacy, actual job counts and owner audit. No HIGH/CRITICAL known and license rights before public release. Docs Validation only checks Markdown/catalog/blocked selector.

## Group 1 — WINDOWS-CPU-GPU-DRIVERS

| Future ID | Testable objective | Independent future oracle | Status |
|---|---|---|---|
| Q05-T001 | Windows native x86_64 Editor clean boot from actual PLAT-05 export on clean OS | future real Windows physical/software-labeled host, PLAT-05 artifact and QA-02 fixtures | FUTURE / NOT EXECUTED |
| Q05-T002 | Windows native x86_64 exported Game launch and filesystem paths independent of editor | future real Windows physical/software-labeled host, PLAT-05 artifact and QA-02 fixtures | FUTURE / NOT EXECUTED |
| Q05-T003 | Windows x86_64 D3D12 GPU adapter feature levels Shader Model and driver queried | future real Windows physical/software-labeled host, PLAT-05 artifact and QA-02 fixtures | FUTURE / NOT EXECUTED |
| Q05-T004 | Windows Vulkan physical GPU loader ICD extensions and swapchain capability queried | future real Windows physical/software-labeled host, PLAT-05 artifact and QA-02 fixtures | FUTURE / NOT EXECUTED |
| Q05-T005 | Intel integrated GPU physical D3D12 scene/golden and UI/font/input verification | future real Windows physical/software-labeled host, PLAT-05 artifact and QA-02 fixtures | FUTURE / NOT EXECUTED |
| Q05-T006 | AMD Radeon physical D3D12 or Vulkan original 3D material/shadow QA-02 oracle | future real Windows physical/software-labeled host, PLAT-05 artifact and QA-02 fixtures | FUTURE / NOT EXECUTED |
| Q05-T007 | NVIDIA GeForce physical GPU shader/swapchain/device and driver QA-02 oracle | future real Windows physical/software-labeled host, PLAT-05 artifact and QA-02 fixtures | FUTURE / NOT EXECUTED |
| Q05-T008 | Windows WARP CPU-only fallback clearly labeled SOFTWARE not vendor hardware pass | future real Windows physical/software-labeled host, PLAT-05 artifact and QA-02 fixtures | FUTURE / NOT EXECUTED |
| Q05-T009 | Windows native Windows ARM64 build and supported device marked CONDITIONAL until owner | future real Windows physical/software-labeled host, PLAT-05 artifact and QA-02 fixtures | FUTURE / NOT EXECUTED |
| Q05-T010 | Windows high DPI multi-monitor and swapchain resize/hotplug no stale device | future real Windows physical/software-labeled host, PLAT-05 artifact and QA-02 fixtures | FUTURE / NOT EXECUTED |
| Q05-T011 | Windows raw keyboard IME Unicode gamepad input replay consistent with QA-02 | future real Windows physical/software-labeled host, PLAT-05 artifact and QA-02 fixtures | FUTURE / NOT EXECUTED |
| Q05-T012 | Windows missing VC runtime DLL or incompatible ABI triggers clear install failure | future real Windows physical/software-labeled host, PLAT-05 artifact and QA-02 fixtures | FUTURE / NOT EXECUTED |
| Q05-T013 | Windows 2D alpha 2.5D layer 3D PBR original golden results under declared driver tier | future real Windows physical/software-labeled host, PLAT-05 artifact and QA-02 fixtures | FUTURE / NOT EXECUTED |
| Q05-T014 | Windows graphics device-removed/hung recovery handles invalid fences and resources | future real Windows physical/software-labeled host, PLAT-05 artifact and QA-02 fixtures | FUTURE / NOT EXECUTED |
| Q05-T015 | Windows crash restart/recovery opt-in preserves last-good project bytes and ACL | future real Windows physical/software-labeled host, PLAT-05 artifact and QA-02 fixtures | FUTURE / NOT EXECUTED |
| Q05-T016 | Windows installer uninstall/reinstall retains user data without signature bypass | future real Windows physical/software-labeled host, PLAT-05 artifact and QA-02 fixtures | FUTURE / NOT EXECUTED |

## Group 2 — LINUX-ABI-COMPOSITOR-GPU

| Future ID | Testable objective | Independent future oracle | Status |
|---|---|---|---|
| Q05-T017 | Linux native x86_64 Editor clean launch on approved distro glibc runtime baseline | future actual distro/ABI/driver/Wayland/X11 host with original QA-02 tests | FUTURE / NOT EXECUTED |
| Q05-T018 | Linux native x86_64 exported Game clean launch independent of dev toolchain | future actual distro/ABI/driver/Wayland/X11 host with original QA-02 tests | FUTURE / NOT EXECUTED |
| Q05-T019 | Linux ARM64 native target remains CONDITIONAL until owner release-class approval | future actual distro/ABI/driver/Wayland/X11 host with original QA-02 tests | FUTURE / NOT EXECUTED |
| Q05-T020 | Linux Vulkan Intel Mesa physical GPU profile/extensions/device generation verified | future actual distro/ABI/driver/Wayland/X11 host with original QA-02 tests | FUTURE / NOT EXECUTED |
| Q05-T021 | Linux Vulkan AMD RADV actual driver device and shader results validated | future actual distro/ABI/driver/Wayland/X11 host with original QA-02 tests | FUTURE / NOT EXECUTED |
| Q05-T022 | Linux NVIDIA proprietary GPU ICD loader version and surface presentation verified | future actual distro/ABI/driver/Wayland/X11 host with original QA-02 tests | FUTURE / NOT EXECUTED |
| Q05-T023 | Linux llvmpipe software Vulkan distinguished from real Intel AMD NVIDIA GPU | future actual distro/ABI/driver/Wayland/X11 host with original QA-02 tests | FUTURE / NOT EXECUTED |
| Q05-T024 | Linux Wayland compositor scale input focus and surface resize tested on actual host | future actual distro/ABI/driver/Wayland/X11 host with original QA-02 tests | FUTURE / NOT EXECUTED |
| Q05-T025 | Linux X11 compositor keyboard IME gamepad/display mode tested separately | future actual distro/ABI/driver/Wayland/X11 host with original QA-02 tests | FUTURE / NOT EXECUTED |
| Q05-T026 | Linux glibc and libstdc++ symbol version mismatch caught on clean target image | future actual distro/ABI/driver/Wayland/X11 host with original QA-02 tests | FUTURE / NOT EXECUTED |
| Q05-T027 | Linux SDL/Wayland/X11 audio font shared library dependencies verified in package | future actual distro/ABI/driver/Wayland/X11 host with original QA-02 tests | FUTURE / NOT EXECUTED |
| Q05-T028 | Linux read-only directory nonASCII username and XDG data/cache paths supported | future actual distro/ABI/driver/Wayland/X11 host with original QA-02 tests | FUTURE / NOT EXECUTED |
| Q05-T029 | Linux missing Vulkan ICD/device yields explicit no-GPU-safe failure path | future actual distro/ABI/driver/Wayland/X11 host with original QA-02 tests | FUTURE / NOT EXECUTED |
| Q05-T030 | Linux memory pressure GPU OOM and disk-full recovery does not corrupt last-good | future actual distro/ABI/driver/Wayland/X11 host with original QA-02 tests | FUTURE / NOT EXECUTED |
| Q05-T031 | Linux package extracted/uninstalled preserves owned project saves and notices | future actual distro/ABI/driver/Wayland/X11 host with original QA-02 tests | FUTURE / NOT EXECUTED |
| Q05-T032 | Linux crash core dump retention sanitizes paths tokens and private project data | future actual distro/ABI/driver/Wayland/X11 host with original QA-02 tests | FUTURE / NOT EXECUTED |

## Group 3 — MACOS-METAL-APPLE-INTEL

| Future ID | Testable objective | Independent future oracle | Status |
|---|---|---|---|
| Q05-T033 | macOS Apple Silicon native arm64 Editor runs on real eligible Mac target | future actual Apple native arm64/optional Intel device and signed bundle/QA-02 | FUTURE / NOT EXECUTED |
| Q05-T034 | macOS native arm64 exported Game launches with signed bundle status explicit | future actual Apple native arm64/optional Intel device and signed bundle/QA-02 | FUTURE / NOT EXECUTED |
| Q05-T035 | Metal MTLDevice supportsFamily and real GPU capabilities recorded with OS version | future actual Apple native arm64/optional Intel device and signed bundle/QA-02 | FUTURE / NOT EXECUTED |
| Q05-T036 | Apple Silicon unified memory working set and GPU device loss handled explicitly | future actual Apple native arm64/optional Intel device and signed bundle/QA-02 | FUTURE / NOT EXECUTED |
| Q05-T037 | Real Apple Silicon Retina high DPI color EDR and fullscreen resize scene QA-02 oracle | future actual Apple native arm64/optional Intel device and signed bundle/QA-02 | FUTURE / NOT EXECUTED |
| Q05-T038 | macOS audio keyboard Unicode IME screen reader and gamepad sample validated | future actual Apple native arm64/optional Intel device and signed bundle/QA-02 | FUTURE / NOT EXECUTED |
| Q05-T039 | macOS TCC denied access to project path fails without leaking private data | future actual Apple native arm64/optional Intel device and signed bundle/QA-02 | FUTURE / NOT EXECUTED |
| Q05-T040 | macOS notarization signature Hardened Runtime validation only when owner approved | future actual Apple native arm64/optional Intel device and signed bundle/QA-02 | FUTURE / NOT EXECUTED |
| Q05-T041 | macOS app sandbox entitlement/resource file access matches documented policy | future actual Apple native arm64/optional Intel device and signed bundle/QA-02 | FUTURE / NOT EXECUTED |
| Q05-T042 | macOS installer/dmg/bundle moved folder and clean machine dep closure validated | future actual Apple native arm64/optional Intel device and signed bundle/QA-02 | FUTURE / NOT EXECUTED |
| Q05-T043 | Intel native x86_64 Mac with macOS <=26 class remains CONDITIONAL and actually tested | future actual Apple native arm64/optional Intel device and signed bundle/QA-02 | FUTURE / NOT EXECUTED |
| Q05-T044 | Universal2 bundle includes arm64+x86_64 slices only if owner explicitly selected | future actual Apple native arm64/optional Intel device and signed bundle/QA-02 | FUTURE / NOT EXECUTED |
| Q05-T045 | Xcode 27 Apple Silicon host cannot be misreported as Intel-host CI proof | future actual Apple native arm64/optional Intel device and signed bundle/QA-02 | FUTURE / NOT EXECUTED |
| Q05-T046 | Rosetta translated x86_64 execution never substitutes Apple Silicon native arm64 | future actual Apple native arm64/optional Intel device and signed bundle/QA-02 | FUTURE / NOT EXECUTED |
| Q05-T047 | macOS crash power interruption recovery restores checksum validated last-good save | future actual Apple native arm64/optional Intel device and signed bundle/QA-02 | FUTURE / NOT EXECUTED |
| Q05-T048 | macOS update and rollback preserves keychain TCC settings and project data safely | future actual Apple native arm64/optional Intel device and signed bundle/QA-02 | FUTURE / NOT EXECUTED |

## Group 4 — WEB-BROWSER-EXPORT-INPUT

| Future ID | Testable objective | Independent future oracle | Status |
|---|---|---|---|
| Q05-T049 | Web game HTTPS secure context and actual approved artifact digest loaded | future actual browser/OS/version/feature/origin and QA-02 web fixture receipt | FUTURE / NOT EXECUTED |
| Q05-T050 | Chrome stable browser WebGPU adapter features limits and device requested supported | future actual browser/OS/version/feature/origin and QA-02 web fixture receipt | FUTURE / NOT EXECUTED |
| Q05-T051 | Firefox current approved browser WebGPU availability determined at runtime | future actual browser/OS/version/feature/origin and QA-02 web fixture receipt | FUTURE / NOT EXECUTED |
| Q05-T052 | Safari current approved browser WebGPU feature availability determined separately | future actual browser/OS/version/feature/origin and QA-02 web fixture receipt | FUTURE / NOT EXECUTED |
| Q05-T053 | WebGPU adapter feature unavailable returns typed UNSUPPORTED not automatic success | future actual browser/OS/version/feature/origin and QA-02 web fixture receipt | FUTURE / NOT EXECUTED |
| Q05-T054 | WebGPU privacy bucketed limits not interpreted as raw physical GPU capacity | future actual browser/OS/version/feature/origin and QA-02 web fixture receipt | FUTURE / NOT EXECUTED |
| Q05-T055 | WebGL2 fallback only enabled if separately approved release/export contract | future actual browser/OS/version/feature/origin and QA-02 web fixture receipt | FUTURE / NOT EXECUTED |
| Q05-T056 | Chromium unsafe SwiftShader fallback never silently enabled on untrusted scene | future actual browser/OS/version/feature/origin and QA-02 web fixture receipt | FUTURE / NOT EXECUTED |
| Q05-T057 | Browser tab background suspension resume preserves fixed tick/input state | future actual browser/OS/version/feature/origin and QA-02 web fixture receipt | FUTURE / NOT EXECUTED |
| Q05-T058 | Browser device lost recovers render resource and QA-02 scene correctness | future actual browser/OS/version/feature/origin and QA-02 web fixture receipt | FUTURE / NOT EXECUTED |
| Q05-T059 | Browser service worker cache version/manifest integrity on update validates | future actual browser/OS/version/feature/origin and QA-02 web fixture receipt | FUTURE / NOT EXECUTED |
| Q05-T060 | Browser no storage quota/offline mode correctly reports save recovery state | future actual browser/OS/version/feature/origin and QA-02 web fixture receipt | FUTURE / NOT EXECUTED |
| Q05-T061 | Browser DPR font Unicode RTL screenshot per OS/browser golden tier validated | future actual browser/OS/version/feature/origin and QA-02 web fixture receipt | FUTURE / NOT EXECUTED |
| Q05-T062 | Browser keyboard pointer touch gamepad input focus navigation and ARIA verified | future actual browser/OS/version/feature/origin and QA-02 web fixture receipt | FUTURE / NOT EXECUTED |
| Q05-T063 | Browser sandbox origin CSP and remote asset restrictions respected with owner policy | future actual browser/OS/version/feature/origin and QA-02 web fixture receipt | FUTURE / NOT EXECUTED |
| Q05-T064 | Browser Web export works in actual physical browser class not Playwright VM alone | future actual browser/OS/version/feature/origin and QA-02 web fixture receipt | FUTURE / NOT EXECUTED |

## Group 5 — ORIGINAL-SCENE-SOAK-REGRESSION

| Future ID | Testable objective | Independent future oracle | Status |
|---|---|---|---|
| Q05-T065 | 2D tilemap sprites font/shaping deterministic frame and scene restore over soak | future repeated independent real host session/QA-02 semantics and QA-03 integration | FUTURE / NOT EXECUTED |
| Q05-T066 | 2.5D transparent parallax sprite layering viewport and camera route stable | future repeated independent real host session/QA-02 semantics and QA-03 integration | FUTURE / NOT EXECUTED |
| Q05-T067 | 3D PBR textures material lighting shadows geometry golden on approved GPU tier | future repeated independent real host session/QA-02 semantics and QA-03 integration | FUTURE / NOT EXECUTED |
| Q05-T068 | 3D particle VFX graphics CPU GPU memory bounded in sustained scene run | future repeated independent real host session/QA-02 semantics and QA-03 integration | FUTURE / NOT EXECUTED |
| Q05-T069 | Shader PSO warmup compile vs cold launch recorded separately on actual host | future repeated independent real host session/QA-02 semantics and QA-03 integration | FUTURE / NOT EXECUTED |
| Q05-T070 | Scene streaming load unload cycles capture allocation leak and memory trend | future repeated independent real host session/QA-02 semantics and QA-03 integration | FUTURE / NOT EXECUTED |
| Q05-T071 | GPU swapchain resize minimize alt-tab device loss repeated for defined duration | future repeated independent real host session/QA-02 semantics and QA-03 integration | FUTURE / NOT EXECUTED |
| Q05-T072 | Render frame pacing p95 p99 actual trace captured on physical host if required | future repeated independent real host session/QA-02 semantics and QA-03 integration | FUTURE / NOT EXECUTED |
| Q05-T073 | CPU/GPU/VRAM usage and dynamic budget recorded where hardware counter supported | future repeated independent real host session/QA-02 semantics and QA-03 integration | FUTURE / NOT EXECUTED |
| Q05-T074 | Audio offline/actual device channel timing latency drift after extended play | future repeated independent real host session/QA-02 semantics and QA-03 integration | FUTURE / NOT EXECUTED |
| Q05-T075 | Headless physics server soaks without implicit GPU desktop claim | future repeated independent real host session/QA-02 semantics and QA-03 integration | FUTURE / NOT EXECUTED |
| Q05-T076 | Repeated app launch shutdown and hot reload cleanly release resources | future repeated independent real host session/QA-02 semantics and QA-03 integration | FUTURE / NOT EXECUTED |
| Q05-T077 | OS suspend resume and user logout login do not corrupt active project | future repeated independent real host session/QA-02 semantics and QA-03 integration | FUTURE / NOT EXECUTED |
| Q05-T078 | Thermal throttle battery AC state labelled on real accessible device sensors | future repeated independent real host session/QA-02 semantics and QA-03 integration | FUTURE / NOT EXECUTED |
| Q05-T079 | Crash hang watchdog/fault run retains first failure trace without false skip | future repeated independent real host session/QA-02 semantics and QA-03 integration | FUTURE / NOT EXECUTED |
| Q05-T080 | Unsupported target or unavailable physical hardware yields NOT_QUALIFIED not PASS | future repeated independent real host session/QA-02 semantics and QA-03 integration | FUTURE / NOT EXECUTED |

## Group 6 — PROJECT-SAVE-MIGRATION-ROLLBACK

| Future ID | Testable objective | Independent future oracle | Status |
|---|---|---|---|
| Q05-T081 | Savegame schema Vn valid snapshot checksum and ownership rights verified | future transaction fault injection exact save/backup hash/migration reversible proof | FUTURE / NOT EXECUTED |
| Q05-T082 | Write interruption before new staging file finish retains old last-good | future transaction fault injection exact save/backup hash/migration reversible proof | FUTURE / NOT EXECUTED |
| Q05-T083 | Fault after flush before atomic replacement restores valid known-good state | future transaction fault injection exact save/backup hash/migration reversible proof | FUTURE / NOT EXECUTED |
| Q05-T084 | Fault after rename but before directory sync detects durability outcome on real FS | future transaction fault injection exact save/backup hash/migration reversible proof | FUTURE / NOT EXECUTED |
| Q05-T085 | Corrupt/truncated project file hash rejected without clobbering healthy backup | future transaction fault injection exact save/backup hash/migration reversible proof | FUTURE / NOT EXECUTED |
| Q05-T086 | Disk full quota or read-only FS triggers typed save failure and clean recovery | future transaction fault injection exact save/backup hash/migration reversible proof | FUTURE / NOT EXECUTED |
| Q05-T087 | Multiple edits concurrent save transaction conflict handled without stale writes | future transaction fault injection exact save/backup hash/migration reversible proof | FUTURE / NOT EXECUTED |
| Q05-T088 | Project schema upgrade N to N+1 idempotent when interrupted then repeated | future transaction fault injection exact save/backup hash/migration reversible proof | FUTURE / NOT EXECUTED |
| Q05-T089 | Project schema downgrade permitted only when reversible owner migration exists | future transaction fault injection exact save/backup hash/migration reversible proof | FUTURE / NOT EXECUTED |
| Q05-T090 | Nonreversible downgrade denied with explicit restore from pre-migration backup | future transaction fault injection exact save/backup hash/migration reversible proof | FUTURE / NOT EXECUTED |
| Q05-T091 | Legacy version metadata unknown requires safe skip and does not destroy bytes | future transaction fault injection exact save/backup hash/migration reversible proof | FUTURE / NOT EXECUTED |
| Q05-T092 | Backup itself corrupted yields restore failure and preserves independent copy | future transaction fault injection exact save/backup hash/migration reversible proof | FUTURE / NOT EXECUTED |
| Q05-T093 | App update process crash midway recovers signed last-good release slot | future transaction fault injection exact save/backup hash/migration reversible proof | FUTURE / NOT EXECUTED |
| Q05-T094 | OS restarts after power failure loads correct version/artifact and last-good save | future transaction fault injection exact save/backup hash/migration reversible proof | FUTURE / NOT EXECUTED |
| Q05-T095 | Rollback test confirms installed binaries signature+assets+settings coherent | future transaction fault injection exact save/backup hash/migration reversible proof | FUTURE / NOT EXECUTED |
| Q05-T096 | User-facing data loss risk receipts report restored changed bytes and limitations | future transaction fault injection exact save/backup hash/migration reversible proof | FUTURE / NOT EXECUTED |

## Group 7 — PACKAGING-SECURITY-SUPPORT-LICENSE

| Future ID | Testable objective | Independent future oracle | Status |
|---|---|---|---|
| Q05-T097 | PLAT-05 export manifest source SHA matches actual clean binary artifact digest | future actual PLAT-05 clean export/install/signing/notice plus owner security approval | FUTURE / NOT EXECUTED |
| Q05-T098 | Reproducible clean rebuild source/toolchain/linker/asset checks independently measured | future actual PLAT-05 clean export/install/signing/notice plus owner security approval | FUTURE / NOT EXECUTED |
| Q05-T099 | Windows package imports runtime and authentic signature when applicable approved | future actual PLAT-05 clean export/install/signing/notice plus owner security approval | FUTURE / NOT EXECUTED |
| Q05-T100 | Linux package libc/RPATH/SONAME/driver deps and third-party notices complete | future actual PLAT-05 clean export/install/signing/notice plus owner security approval | FUTURE / NOT EXECUTED |
| Q05-T101 | macOS universal slices signing notarization and OS permissions actually verified | future actual PLAT-05 clean export/install/signing/notice plus owner security approval | FUTURE / NOT EXECUTED |
| Q05-T102 | Web content manifest hashed and cache/origin policy validated on clean session | future actual PLAT-05 clean export/install/signing/notice plus owner security approval | FUTURE / NOT EXECUTED |
| Q05-T103 | Missing native binary library or GPU driver failure has actionable user error | future actual PLAT-05 clean export/install/signing/notice plus owner security approval | FUTURE / NOT EXECUTED |
| Q05-T104 | Original scenes font textures audio license and asset notices approved per artifact | future actual PLAT-05 clean export/install/signing/notice plus owner security approval | FUTURE / NOT EXECUTED |
| Q05-T105 | Engine source license NLE-D009 OPEN prevents unauthorized public shipping claim | future actual PLAT-05 clean export/install/signing/notice plus owner security approval | FUTURE / NOT EXECUTED |
| Q05-T106 | Private project/log/crash dumps never uploaded to public CI without consent | future actual PLAT-05 clean export/install/signing/notice plus owner security approval | FUTURE / NOT EXECUTED |
| Q05-T107 | QA-04 security known HIGH CRITICAL blocks release even if compatibility passed | future actual PLAT-05 clean export/install/signing/notice plus owner security approval | FUTURE / NOT EXECUTED |
| Q05-T108 | Platform support window owner min OS driver hardware declared with evidence | future actual PLAT-05 clean export/install/signing/notice plus owner security approval | FUTURE / NOT EXECUTED |
| Q05-T109 | Unsupported fallback mode excluded from published supported configuration | future actual PLAT-05 clean export/install/signing/notice plus owner security approval | FUTURE / NOT EXECUTED |
| Q05-T110 | Install/uninstall leaves no executable vulnerable orphan/privilege resources | future actual PLAT-05 clean export/install/signing/notice plus owner security approval | FUTURE / NOT EXECUTED |
| Q05-T111 | Clean-room user permissions and nonadmin installation tested per target | future actual PLAT-05 clean export/install/signing/notice plus owner security approval | FUTURE / NOT EXECUTED |
| Q05-T112 | R$0 hosted runner compute/storage and physical hardware access verified separately | future actual PLAT-05 clean export/install/signing/notice plus owner security approval | FUTURE / NOT EXECUTED |

## Group 8 — GATES-TRACEABILITY-QUALIFICATION

| Future ID | Testable objective | Independent future oracle | Status |
|---|---|---|---|
| Q05-T113 | Matrix product role Editor vs Game vs headless targets separately verified | future full source/host/fixture/export receipt, actual CI runner and objective pt-BR audit | FUTURE / NOT EXECUTED |
| Q05-T114 | Target OS arch driver GPU backend browser feature identity recorded in receipt | future full source/host/fixture/export receipt, actual CI runner and objective pt-BR audit | FUTURE / NOT EXECUTED |
| Q05-T115 | Actual host SOFTWARE/VM/PHYSICAL evidence prevents false hardware claim | future full source/host/fixture/export receipt, actual CI runner and objective pt-BR audit | FUTURE / NOT EXECUTED |
| Q05-T116 | QA-02 fixture/golden version rights SHA and actual test result linked | future full source/host/fixture/export receipt, actual CI runner and objective pt-BR audit | FUTURE / NOT EXECUTED |
| Q05-T117 | PLAT-05 reproducible export manifest checksum signing provenance linked | future full source/host/fixture/export receipt, actual CI runner and objective pt-BR audit | FUTURE / NOT EXECUTED |
| Q05-T118 | CI CTest nonzero executed tests distinguished from Docs Validation pipeline | future full source/host/fixture/export receipt, actual CI runner and objective pt-BR audit | FUTURE / NOT EXECUTED |
| Q05-T119 | Per target required L0-L6 release gate reports PASS only if actual layers complete | future full source/host/fixture/export receipt, actual CI runner and objective pt-BR audit | FUTURE / NOT EXECUTED |
| Q05-T120 | Skipped unsupported physical class can't count in denominator as a qualified PASS | future full source/host/fixture/export receipt, actual CI runner and objective pt-BR audit | FUTURE / NOT EXECUTED |
| Q05-T121 | Test coverage report includes untested drivers/OS versions and known exclusions | future full source/host/fixture/export receipt, actual CI runner and objective pt-BR audit | FUTURE / NOT EXECUTED |
| Q05-T122 | Recovery first fail tick/crash logs checksum and backup restoration proof archived | future full source/host/fixture/export receipt, actual CI runner and objective pt-BR audit | FUTURE / NOT EXECUTED |
| Q05-T123 | Regression baseline changed only via QA-02 owner audited separate approval | future full source/host/fixture/export receipt, actual CI runner and objective pt-BR audit | FUTURE / NOT EXECUTED |
| Q05-T124 | Compatibility result expires or becomes STALE after driver/SDK/fixture changes | future full source/host/fixture/export receipt, actual CI runner and objective pt-BR audit | FUTURE / NOT EXECUTED |
| Q05-T125 | Release version platform minima owner scope no unapproved automatic expansion | future full source/host/fixture/export receipt, actual CI runner and objective pt-BR audit | FUTURE / NOT EXECUTED |
| Q05-T126 | Security HIGH CRITICAL or corrupted save gives BLOCKED rather than owner waiver | future full source/host/fixture/export receipt, actual CI runner and objective pt-BR audit | FUTURE / NOT EXECUTED |
| Q05-T127 | All 128 FUTURE QA-05 test cases marked NOT_EXECUTED during research gate | future full source/host/fixture/export receipt, actual CI runner and objective pt-BR audit | FUTURE / NOT EXECUTED |
| Q05-T128 | All 80 code packets remain BLOCKED after independent documentary checkpoint | future full source/host/fixture/export receipt, actual CI runner and objective pt-BR audit | FUTURE / NOT EXECUTED |


## Current truth and stop
These 128 rows specify FUTURE tests, **NONE EXECUTED**. No real build/export, screenshot, OS/browser/hardware lab, benchmark, original sample, installer/notarization, crash recovery, asset migration or restore proof exists. Catalog acceptance **"Cenários de compatibilidade e recuperação aprovados por plataforma" NOT IMPLEMENTED/NOT QUALIFIED**. Keep ADR-0079 PROPOSED, all 80 code WOs BLOCKED, owner source license OPEN, no public MVP.

[Architecture](../architecture/qa-05-compatibility-release-qualification.md) · [benchmark protocol](../research/qa-05-compatibility-soak-recovery-benchmark-protocol.md) · [semantic API](../contracts/qa-05-qualification-evidence-api.md).
