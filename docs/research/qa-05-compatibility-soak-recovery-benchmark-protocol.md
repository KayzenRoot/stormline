# QA-05 — Future Cross-Platform Soak, Crash-Recovery and Release Qualification Benchmark Protocol

**2026-11-16 | FUTURE RESEARCH ONLY, NO EXECUTABLE/DEVICE OR RECOVERY TEST.** Research #357, coding #94 OPEN/BLOCKED, source HEAD `a42519c8a79346a4974fa74c44f7cac26f4ad43c`, formal **QA-02 + PLAT-05 ONLY**. All status results here are **NOT EXECUTED**. This specification supplies future measured acceptance evidence requirements but not any fabricated duration, frame rate, crash result or physical hardware inventory.

## Intended qualification fleet, conditional until owner approval
| Future profile | Actual target required to qualify | Qualified limitations |
|---|---|---|
| QUAL-WIN-PHYSICAL-INTEL | affordable real Intel iGPU/dGPU Windows x64 D3D12/Vulkan | measure actual GPU driver, feature level and QA-02 2D/2.5D/3D golden, high DPI, input/audio, device removal |
| QUAL-WIN-PHYSICAL-AMD | real AMD APU or entry Radeon approved device | DXGI/Vulkan profile, VRAM and correctly installed game/editor |
| QUAL-WIN-PHYSICAL-NVIDIA | real NVIDIA GPU approved budget class | D3D12/Vulkan features, shader/stutter/driver after load, no claim all GeForce |
| QUAL-WIN-WARP | Windows D3D12 WARP CPU/software adapter | functional/render smoke only, explicit SOFTWARE flag and no vendor physical certification |
| QUAL-LNX-MESA-INTEL | Linux approved distro/glibc Wayland or X11 real Intel GPU | Mesa/loader/ICD/distribution ABI and actual display |
| QUAL-LNX-MESA-AMD | real Linux AMD RADV GPU and chosen compositor | Vulkan profile/shaders/device-loss/storage/OSS notices |
| QUAL-LNX-NVIDIA | real Linux NVIDIA driver and approved distro | loader/capabilities/native libs and real present |
| QUAL-LNX-SOFTWARE | Linux llvmpipe/SwiftShader or Xvfb CPU fixture | headless/CPU-only, not physical GPU claim |
| QUAL-MAC-ARM64 | actual native Apple Silicon Mac current owner-approved OS | MTLDevice.supportsFamily, app bundle, data FS, screenshot/a11y/Metal device |
| QUAL-MAC-INTEL | **conditional** actual Intel Mac x86_64 eligible <= macOS 26 | never substitute Rosetta translation on ARM or assume included in mandatory 1.0 minimum |
| QUAL-WEB-CHROMIUM | actual Chrome/Chromium OS/browser versions with HTTPS | WebGPU adapter features and loss, WebGL2 only if owner-approved fallback, QA-02 originals |
| QUAL-WEB-GECKO | actual Firefox browser/OS build and WebGPU feature tests | no assumption of universal API availability based solely on branding |
| QUAL-WEB-SAFARI | actual Safari macOS on approved Apple device | browser WebGPU+origin/privacy/snapshot and native Mac ability separate |
| QUAL-HEADLESS | real approved CPU target runtime w/o graphics stack | simulations/saves only, no display/GPU proof |
| QUAL-MOBILE | Android/iOS only on later explicit owner-approved release class | no implied mobile release tests, fees or signed packages in this module |

## Fixture and source/version locks
- Actual PLAT-05 exported binary/game/editor target digest, build HEAD/SDK/compiler, complete runtime dependency versions, manifests, signature/notarization as appropriate, binary arch/ABI; QA-02 rights-cleared original scene+input/audio/screenshot/semantic baseline snapshot/consent, seed and tick, accepted intended UI and gameplay.
- Hardware actual CPU/GPU/VRAM physical vs software driver, OS build/ABI/kernel/macOS/Windows, graphics feature/profile family, display/refresh/HDR/input/font/locale, browser/secure origin+features, disk/file system, power state, installed runtime and permission. Missing required fingerprint/source => STALE/INCOMPARABLE/NOT_QUALIFIED.
- Freeze releases by *artifact SHA*, not mutable “latest”; never reinterpret a browser update or driver replacement as same test environment. Subject signatures and SPO/NOTICE owner rules require actual verification.

## Candidate future scenario protocol (all NOT EXECUTED)
| ID | Future workload | Proposed raw evidence |
|---|---|---|
| QUAL-B01 | independent PLAT-05 clean builder Windows Linux macOS/Web | actual hashes, reproducible build material differences and source lock |
| QUAL-B02 | clean VM install of Editor + Game per target OS | install/uninstall and full manifest/required library resolution, not real GPU pass |
| QUAL-B03 | real entry physical Intel/AMD/NVIDIA D3D12/Vulkan | capability/tier and QA-02 2D/2.5D/3D sequence with actual screenshot/readback |
| QUAL-B04 | real Apple Silicon Metal+optional Intel | MTLGPUFamily and OS/cert/TCC/a11y, no Rosetta substitution |
| QUAL-B05 | Web three browsers+HTTPS adaptive feature query | exact browser/adapter/lost/origin, QA-02 golden ARIA/control |
| QUAL-B06 | software renderer WARP/SwiftShader smoke | CPU only, expect no physical hardware label |
| QUAL-B07 | sustained room/scene streaming long soak | wall duration/frame count, uncensored crashes/VRAM/CPU heap and first fail |
| QUAL-B08 | renderer device loss/resize/suspend/resume | actual vs injected fault flagged, restore original scene/state |
| QUAL-B09 | unexpected process termination during asset/save write phases | independent last-good snapshot/checksum and recovery time/bytes |
| QUAL-B10 | power cut/restart real FS in safe test host | backup/rename/fsync stage outcome, actual filesystem and no user data |
| QUAL-B11 | approved format migration N→N+1 interrupts each step | idempotent checkpoint + original test project before/after |
| QUAL-B12 | unsafe format rollback N+1→N | explicit denied if irreversible + restore last-good pre-migration data |
| QUAL-B13 | locale/Unicode/RTL and accessibility | keyboard/screen reader/contrast actual OS, browser ARIA separately |
| QUAL-B14 | update/install/signature and license/NOTICE | actual native bundle/export/install/permissions artifact verification |
| QUAL-B15 | R$0 hosted artifact storage vs access to real hardware | actual GitHub minutes/artifact bytes and owner physical device permission |
| QUAL-B16 | owner gated release decision and roll-forward | full 128 future-case actual statuses + exact original artifact/host and no HIGH/CRITICAL |

## Statistics, reliability and failure criteria
- Predeclare total soak wall time and rounds by target risk **before** measuring. The QA-03 performance integration can provide p50/p95/p99 from ordered real frames if available, but QA-05 must distinguish that from functional QA-02 pass, crash/hang frequency, resource growth, memory release and stall counts. **No invented minimum hours or percentiles**.
- For rare crash rate (k) in (T) hours, report source+CI host/actual duration and uncertainty; zero observed crashes in short run is not proof of zero failure rate. Multiple independent sessions and hardware/driver classes needed; no synthetic VM proxy for physical GPU.
- Thermal/power/driver events may be unavailable or vendor proprietary, mark unknown rather than 0. Missing physical hardware => NOT_QUALIFIED for target cell, no PASS.
- Fault injection includes controlled exceptions/process terminate, temporary failure after flush/rename/directory metadata, storage full/permission denied, old-binary rollout and untrusted browser tab interruption; **real power-off fault injection requires explicit owner approval on isolated disposable host** and never targets private/live users.
- Compare actual restore result both byte-level/checksum and semantic state with expected last-good across independent backup read, validate that successful migration doesn't break old saves or permissions; never auto-update golden or delete original pre-migration backup during testing. Report unrecoverable data loss, how many bytes and exact source, blocking release.
- CI and build tests: GitHub public hosted standard runner compute may be R$0, artifact storage/cache/larger runners billing and physical device farm not automatically free. Use only owner devices with authorized locally executed hardware tests. Security report: no known unresolved HIGH/CRITICAL, accepted dependency/license/signature/provenance after actual artifact. No public release until engine source license and full 1.0 DoD approved.

## Future `QualBenchmarkReceiptV1` required
Source+toolchain+export manifest/artifact SHA and signature verification, QA-02 fixture rights+goldens, host OS/CPU/GPU/driver/physical flag/OS build/browser features, scene seed/input/audio, runner/job/source, actual start/end and soak duration, failed/recovered save checksum, fault injection identity and stage, p95/p99 if truly collected, thermal source/notes, dependency/notice/signing, release gating owner status, CI cost/retention and pt-BR independent audit. No receipt produced in P00.

[128 tests](../testing/qa-05-acceptance-matrix.md) · [technology/legal matrix](qa-05-platform-hardware-tool-license-cost-matrix.md) · [Architecture](../architecture/qa-05-compatibility-release-qualification.md).
