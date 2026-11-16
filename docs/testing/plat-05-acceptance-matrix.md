# PLAT-05 — Exactly 128 FUTURE Build/Export/Distribution Acceptance Tests (P05-T001..P05-T128)

**P00 RESEARCH ONLY, NO ENGINE OR REAL EXPORT.** [Research #337](https://github.com/KayzenRoot/stormline/issues/337), [future coding #89](https://github.com/KayzenRoot/stormline/issues/89) OPEN/BLOCKED, Work Order NLE-P00-WO-002-PLAT-05, base main `d1369e8101ea86e2a14a4a12e9581fb8df4fa478`. Exact formal DAG **PLAT-01 + PLAT-02 + PLAT-03 + PLAT-06 + DATA-05**, all predecessor ADRs PROPOSED. `P05-T001..P05-T128` **eight groups × sixteen unique cases; ALL FUTURE / NOT EXECUTED**. No app build, pair of reproducible unsigned builds, SBOM, SLSA/GitHub attestation, signed/notarized package, browser deploy, hardware install or release test was performed.

## Proof hierarchy and failure rules for future code work
1. Freeze owner-approved target release classes/min OS+ABI/capability, signed toolchains, Source Pack/ADR versions and raw SHA-256 context fingerprints; current code WOs (80/80) BLOCKED and NLE-D009 engine license OPEN. No version 1.0 public MVP.
2. Distinguish source/cook/unsigned stage/signed final/store receipt and actual deployed runtime. Build success on host or Docs CI cannot verify clean target OS hardware, signing trust or browser headers.
3. Independently reproduce **unsigned payload** with pinned toolchain and SOURCE_DATE_EPOCH and normalized tree. If signing/notary timestamp or store transforms final archive, capture **new** SHA and verification oracle; do not demand bytewise signed output match.
4. Windows x64 and selected arm64 if approved, Linux x86_64 GNU chosen glibc and Wayland/X11, macOS arm64 native and actual Intel Mac conditional OS<=26, Web actual WebGPU and WebGL2 fallback where approved. 2D/2.5D/3D Editor & exports desktop, Web game browser when planned, mobile only after explicit owner scope/cost decision.
5. DATA-05 immutable CookReceipt & bundle dependency closure, project source never overwritten, secure archives/symlinks/casesensitive collisions and bounded untrusted assets, original rights-cleared scene fixtures and notices.
6. Trust proof: exact SPDX/CycloneDX validated SBOM, SLSA v1 provenance buildDefinition/builder/subject digest, GitHub attest verified with trusted workflow if configured, secure code-sign identity and key separation. No self-asserted SLSA high level; no license/legal adoption by documentation.
7. Rollback performed under BIZ-03 after own ADR/DoD: authenticated version/channel, staging and journals, crash/disk-full/power-off, store permission and installer sandbox. Browser SW cache swap is not POSIX rename; avoid active generation mix. Zero silent root/admin or credential use.
8. Negative tests and adversarial supply-chain fixtures must fail closed and restore previous valid binary and user authored project. Capture actual artifact/source SHA, environment, CI run/job, permissions, timings, real clean host and acceptance verdict. No future PASS may be marked without evidence.

## Group 1 — SOURCE-CONTEXT-REPRODUCIBILITY

| Future case | Objective and scenario | Independent oracle | Status |
|---|---|---|---|
| P05-T001 | Exact Git HEAD and approved project revision frozen before export request | two independent clean builders/source hash + compiler/SDK/version/env logs, unsigned byte compare/diffoscope and STALE reject | FUTURE / NOT EXECUTED |
| P05-T002 | Critical Source Pack SHA256 fingerprint revalidated against expected snapshot | two independent clean builders/source hash + compiler/SDK/version/env logs, unsigned byte compare/diffoscope and STALE reject | FUTURE / NOT EXECUTED |
| P05-T003 | Target profile release class UNDECIDED rejects public export authorization | two independent clean builders/source hash + compiler/SDK/version/env logs, unsigned byte compare/diffoscope and STALE reject | FUTURE / NOT EXECUTED |
| P05-T004 | Pinned C++20 compiler/linker/SDK/sysroot version and SHA recorded | two independent clean builders/source hash + compiler/SDK/version/env logs, unsigned byte compare/diffoscope and STALE reject | FUTURE / NOT EXECUTED |
| P05-T005 | Host and cross-compile target ABI distinguished in CMake toolchain | two independent clean builders/source hash + compiler/SDK/version/env logs, unsigned byte compare/diffoscope and STALE reject | FUTURE / NOT EXECUTED |
| P05-T006 | No cross-built target binary executed on incompatible build host | two independent clean builders/source hash + compiler/SDK/version/env logs, unsigned byte compare/diffoscope and STALE reject | FUTURE / NOT EXECUTED |
| P05-T007 | Toolchain download with unpinned latest version rejected | two independent clean builders/source hash + compiler/SDK/version/env logs, unsigned byte compare/diffoscope and STALE reject | FUTURE / NOT EXECUTED |
| P05-T008 | SOURCE_DATE_EPOCH stable last-source-modified timestamp used | two independent clean builders/source hash + compiler/SDK/version/env logs, unsigned byte compare/diffoscope and STALE reject | FUTURE / NOT EXECUTED |
| P05-T009 | Archive file order/locale/uid/gid/mode/mtime normalized in unsigned payload | two independent clean builders/source hash + compiler/SDK/version/env logs, unsigned byte compare/diffoscope and STALE reject | FUTURE / NOT EXECUTED |
| P05-T010 | Absolute project or temporary path removed from distributable build ID | two independent clean builders/source hash + compiler/SDK/version/env logs, unsigned byte compare/diffoscope and STALE reject | FUTURE / NOT EXECUTED |
| P05-T011 | Second independent unsigned rebuild hashes match when deterministic contract met | two independent clean builders/source hash + compiler/SDK/version/env logs, unsigned byte compare/diffoscope and STALE reject | FUTURE / NOT EXECUTED |
| P05-T012 | Two builds disagree due to compiler nondeterminism and mismatch is reported | two independent clean builders/source hash + compiler/SDK/version/env logs, unsigned byte compare/diffoscope and STALE reject | FUTURE / NOT EXECUTED |
| P05-T013 | Run-local random UUID/debug build ID deterministic or justified separately | two independent clean builders/source hash + compiler/SDK/version/env logs, unsigned byte compare/diffoscope and STALE reject | FUTURE / NOT EXECUTED |
| P05-T014 | CI cache poisoned cross-trust or cross-SDK reuse rejected | two independent clean builders/source hash + compiler/SDK/version/env logs, unsigned byte compare/diffoscope and STALE reject | FUTURE / NOT EXECUTED |
| P05-T015 | Unsupported version of build template or compiler returns typed failure | two independent clean builders/source hash + compiler/SDK/version/env logs, unsigned byte compare/diffoscope and STALE reject | FUTURE / NOT EXECUTED |
| P05-T016 | Reproducibility report never claims signed outputs must equal unsigned bytes | two independent clean builders/source hash + compiler/SDK/version/env logs, unsigned byte compare/diffoscope and STALE reject | FUTURE / NOT EXECUTED |

## Group 2 — DATA-COOK-TEMPLATE-STAGING

| Future case | Objective and scenario | Independent oracle | Status |
|---|---|---|---|
| P05-T017 | DATA-05 immutable CookReceipt source AssetId and scene snapshot validated | DATA-05 immutable cook manifest and actual target stage filesystem/hash/path rights, source snapshot unchanged | FUTURE / NOT EXECUTED |
| P05-T018 | Wrong AssetId generation/hash or target tier rejected before package | DATA-05 immutable cook manifest and actual target stage filesystem/hash/path rights, source snapshot unchanged | FUTURE / NOT EXECUTED |
| P05-T019 | All bundled chunks sha256 length and codec/dictionary verified | DATA-05 immutable cook manifest and actual target stage filesystem/hash/path rights, source snapshot unchanged | FUTURE / NOT EXECUTED |
| P05-T020 | Cooked bundle dependency DAG cycles or missing chunk rejected | DATA-05 immutable cook manifest and actual target stage filesystem/hash/path rights, source snapshot unchanged | FUTURE / NOT EXECUTED |
| P05-T021 | Target-specific textures/fonts/shader variants selected by measured capabilities | DATA-05 immutable cook manifest and actual target stage filesystem/hash/path rights, source snapshot unchanged | FUTURE / NOT EXECUTED |
| P05-T022 | Unsupported GPU codec or required data tier returns clear target failure | DATA-05 immutable cook manifest and actual target stage filesystem/hash/path rights, source snapshot unchanged | FUTURE / NOT EXECUTED |
| P05-T023 | Unlicensed image/font/sample or missing required notice blocks export | DATA-05 immutable cook manifest and actual target stage filesystem/hash/path rights, source snapshot unchanged | FUTURE / NOT EXECUTED |
| P05-T024 | Path traversal ../ or absolute export template entry rejected | DATA-05 immutable cook manifest and actual target stage filesystem/hash/path rights, source snapshot unchanged | FUTURE / NOT EXECUTED |
| P05-T025 | Windows-casefold and Unicode-normalization filename collisions blocked | DATA-05 immutable cook manifest and actual target stage filesystem/hash/path rights, source snapshot unchanged | FUTURE / NOT EXECUTED |
| P05-T026 | Symlink/hardlink or ZIP-slip staging escape fails closed | DATA-05 immutable cook manifest and actual target stage filesystem/hash/path rights, source snapshot unchanged | FUTURE / NOT EXECUTED |
| P05-T027 | Decompression bomb/oversize bundle refused within budget | DATA-05 immutable cook manifest and actual target stage filesystem/hash/path rights, source snapshot unchanged | FUTURE / NOT EXECUTED |
| P05-T028 | Staged output isolated read-only and never overwrites authored source | DATA-05 immutable cook manifest and actual target stage filesystem/hash/path rights, source snapshot unchanged | FUTURE / NOT EXECUTED |
| P05-T029 | Immutable stage file manifest ordered and includes permissions/length/hash | DATA-05 immutable cook manifest and actual target stage filesystem/hash/path rights, source snapshot unchanged | FUTURE / NOT EXECUTED |
| P05-T030 | Debug symbols kept in separate privacy-controlled artifact from release | DATA-05 immutable cook manifest and actual target stage filesystem/hash/path rights, source snapshot unchanged | FUTURE / NOT EXECUTED |
| P05-T031 | Corrupted staged file after seal detected before optional signing | DATA-05 immutable cook manifest and actual target stage filesystem/hash/path rights, source snapshot unchanged | FUTURE / NOT EXECUTED |
| P05-T032 | Project editable source remains unchanged after canceled failed export | DATA-05 immutable cook manifest and actual target stage filesystem/hash/path rights, source snapshot unchanged | FUTURE / NOT EXECUTED |

## Group 3 — WINDOWS-PACKAGING-CODESIGN

| Future case | Objective and scenario | Independent oracle | Status |
|---|---|---|---|
| P05-T033 | Native Windows x64 Editor and exported game build artifacts typed correctly | actual Windows OS clean install and PE/MSIX signed root/trust/CRT code+store/channel receipt, no unauthorized spend | FUTURE / NOT EXECUTED |
| P05-T034 | Windows runtime WinCRT/DLL import/dependency checks on clean target | actual Windows OS clean install and PE/MSIX signed root/trust/CRT code+store/channel receipt, no unauthorized spend | FUTURE / NOT EXECUTED |
| P05-T035 | MSIX manifest identity version architecture and file entries validated | actual Windows OS clean install and PE/MSIX signed root/trust/CRT code+store/channel receipt, no unauthorized spend | FUTURE / NOT EXECUTED |
| P05-T036 | Direct MSI/EXE alternative considered only with explicit channel selection | actual Windows OS clean install and PE/MSIX signed root/trust/CRT code+store/channel receipt, no unauthorized spend | FUTURE / NOT EXECUTED |
| P05-T037 | MSIX unsigned public installer rejected before deployment | actual Windows OS clean install and PE/MSIX signed root/trust/CRT code+store/channel receipt, no unauthorized spend | FUTURE / NOT EXECUTED |
| P05-T038 | Self-signed development MSIX only installs under explicitly trusted test root | actual Windows OS clean install and PE/MSIX signed root/trust/CRT code+store/channel receipt, no unauthorized spend | FUTURE / NOT EXECUTED |
| P05-T039 | Production CA trusted signature chain and timestamp verified if authorized | actual Windows OS clean install and PE/MSIX signed root/trust/CRT code+store/channel receipt, no unauthorized spend | FUTURE / NOT EXECUTED |
| P05-T040 | Microsoft Store MSIX re-signing treated as separate final digest | actual Windows OS clean install and PE/MSIX signed root/trust/CRT code+store/channel receipt, no unauthorized spend | FUTURE / NOT EXECUTED |
| P05-T041 | Azure Artifact Signing geographic eligibility and cost gate enforced | actual Windows OS clean install and PE/MSIX signed root/trust/CRT code+store/channel receipt, no unauthorized spend | FUTURE / NOT EXECUTED |
| P05-T042 | Unapproved code signing service rejected without account creation | actual Windows OS clean install and PE/MSIX signed root/trust/CRT code+store/channel receipt, no unauthorized spend | FUTURE / NOT EXECUTED |
| P05-T043 | Windows SmartScreen reputation never claimed instant from signature | actual Windows OS clean install and PE/MSIX signed root/trust/CRT code+store/channel receipt, no unauthorized spend | FUTURE / NOT EXECUTED |
| P05-T044 | DLL search order and project-controlled native module injection rejected | actual Windows OS clean install and PE/MSIX signed root/trust/CRT code+store/channel receipt, no unauthorized spend | FUTURE / NOT EXECUTED |
| P05-T045 | Windows PE executable and embedded symbol/debug privacy scanned | actual Windows OS clean install and PE/MSIX signed root/trust/CRT code+store/channel receipt, no unauthorized spend | FUTURE / NOT EXECUTED |
| P05-T046 | Signed package after post-sign tampering fails independent verification | actual Windows OS clean install and PE/MSIX signed root/trust/CRT code+store/channel receipt, no unauthorized spend | FUTURE / NOT EXECUTED |
| P05-T047 | Atomic update/repair preserves Windows saved project and launcher identity | actual Windows OS clean install and PE/MSIX signed root/trust/CRT code+store/channel receipt, no unauthorized spend | FUTURE / NOT EXECUTED |
| P05-T048 | Clean Windows build/open/close 2D/2.5D/3D editor/game smoke if approved | actual Windows OS clean install and PE/MSIX signed root/trust/CRT code+store/channel receipt, no unauthorized spend | FUTURE / NOT EXECUTED |

## Group 4 — LINUX-FLATPAK-APPIMAGE

| Future case | Objective and scenario | Independent oracle | Status |
|---|---|---|---|
| P05-T049 | ELF x86_64 GNU/glibc floor checked against chosen oldest supported distro | actual Linux distro ELF/glibc/Wayland/X11, Flatpak/portals/AppImage runtime source and checksum smoke | FUTURE / NOT EXECUTED |
| P05-T050 | ELF DT_NEEDED and symbol versions verified on clean supported Linux | actual Linux distro ELF/glibc/Wayland/X11, Flatpak/portals/AppImage runtime source and checksum smoke | FUTURE / NOT EXECUTED |
| P05-T051 | AppImage built against old baseline not newer glibc toolchain | actual Linux distro ELF/glibc/Wayland/X11, Flatpak/portals/AppImage runtime source and checksum smoke | FUTURE / NOT EXECUTED |
| P05-T052 | AppImage excludes host-dependent GPU driver and Vulkan ICD libraries | actual Linux distro ELF/glibc/Wayland/X11, Flatpak/portals/AppImage runtime source and checksum smoke | FUTURE / NOT EXECUTED |
| P05-T053 | AppImage runtime relative paths and FUSE compatibility smoke evaluated | actual Linux distro ELF/glibc/Wayland/X11, Flatpak/portals/AppImage runtime source and checksum smoke | FUTURE / NOT EXECUTED |
| P05-T054 | Flatpak manifest app id runtime SDK and module versions pinned | actual Linux distro ELF/glibc/Wayland/X11, Flatpak/portals/AppImage runtime source and checksum smoke | FUTURE / NOT EXECUTED |
| P05-T055 | Flatpak sandbox permissions minimize filesystem and portal grants | actual Linux distro ELF/glibc/Wayland/X11, Flatpak/portals/AppImage runtime source and checksum smoke | FUTURE / NOT EXECUTED |
| P05-T056 | Flatpak Wayland plus fallback X11 permissions tested independently | actual Linux distro ELF/glibc/Wayland/X11, Flatpak/portals/AppImage runtime source and checksum smoke | FUTURE / NOT EXECUTED |
| P05-T057 | Flatpak GPU Vulkan render node/portal profile supports selected GPU tier | actual Linux distro ELF/glibc/Wayland/X11, Flatpak/portals/AppImage runtime source and checksum smoke | FUTURE / NOT EXECUTED |
| P05-T058 | Flatpak app and exported game start/close on actual supported distro | actual Linux distro ELF/glibc/Wayland/X11, Flatpak/portals/AppImage runtime source and checksum smoke | FUTURE / NOT EXECUTED |
| P05-T059 | Linux portable tar package lacks sudo/setuid installer side effect | actual Linux distro ELF/glibc/Wayland/X11, Flatpak/portals/AppImage runtime source and checksum smoke | FUTURE / NOT EXECUTED |
| P05-T060 | XDG paths, symlink race and nonroot installation validated | actual Linux distro ELF/glibc/Wayland/X11, Flatpak/portals/AppImage runtime source and checksum smoke | FUTURE / NOT EXECUTED |
| P05-T061 | Linux package checksum/registry readback detects corrupt library | actual Linux distro ELF/glibc/Wayland/X11, Flatpak/portals/AppImage runtime source and checksum smoke | FUTURE / NOT EXECUTED |
| P05-T062 | Untrusted environment LD_PRELOAD/ICD path cannot alter signed release trust | actual Linux distro ELF/glibc/Wayland/X11, Flatpak/portals/AppImage runtime source and checksum smoke | FUTURE / NOT EXECUTED |
| P05-T063 | Arch/version mismatch Linux error preserves existing release generation | actual Linux distro ELF/glibc/Wayland/X11, Flatpak/portals/AppImage runtime source and checksum smoke | FUTURE / NOT EXECUTED |
| P05-T064 | Linux update or package manager and BIZ-03 owner boundaries respected | actual Linux distro ELF/glibc/Wayland/X11, Flatpak/portals/AppImage runtime source and checksum smoke | FUTURE / NOT EXECUTED |

## Group 5 — MACOS-ARM-INTEL-NOTARY

| Future case | Objective and scenario | Independent oracle | Status |
|---|---|---|---|
| P05-T065 | Apple Silicon arm64 native Editor/game Mach-O generated with pinned Xcode SDK | actual Apple Silicon and conditional Intel Mac Mach-O slice, notarization/Gatekeeper/entitlement proof if channel approved | FUTURE / NOT EXECUTED |
| P05-T066 | Xcode27 build host not claimed compatible with Intel physical host | actual Apple Silicon and conditional Intel Mac Mach-O slice, notarization/Gatekeeper/entitlement proof if channel approved | FUTURE / NOT EXECUTED |
| P05-T067 | Conditional universal2 x86_64/arm64 main executable includes both slices | actual Apple Silicon and conditional Intel Mac Mach-O slice, notarization/Gatekeeper/entitlement proof if channel approved | FUTURE / NOT EXECUTED |
| P05-T068 | All embedded Mach-O frameworks/plugins/helpers preserve required slices | actual Apple Silicon and conditional Intel Mac Mach-O slice, notarization/Gatekeeper/entitlement proof if channel approved | FUTURE / NOT EXECUTED |
| P05-T069 | Intel native physical Mac smoke limited to owner-approved eligible macOS <=26 | actual Apple Silicon and conditional Intel Mac Mach-O slice, notarization/Gatekeeper/entitlement proof if channel approved | FUTURE / NOT EXECUTED |
| P05-T070 | Rosetta translated x86_64 on Apple Silicon not confused with Intel native | actual Apple Silicon and conditional Intel Mac Mach-O slice, notarization/Gatekeeper/entitlement proof if channel approved | FUTURE / NOT EXECUTED |
| P05-T071 | macOS min version LC_BUILD_VERSION and weak-linked symbol availability checked | actual Apple Silicon and conditional Intel Mac Mach-O slice, notarization/Gatekeeper/entitlement proof if channel approved | FUTURE / NOT EXECUTED |
| P05-T072 | macOS app bundle Info.plist id/icons/locale/resources checks pass | actual Apple Silicon and conditional Intel Mac Mach-O slice, notarization/Gatekeeper/entitlement proof if channel approved | FUTURE / NOT EXECUTED |
| P05-T073 | Nested code signatures and hardened runtime entitlements verified when authorized | actual Apple Silicon and conditional Intel Mac Mach-O slice, notarization/Gatekeeper/entitlement proof if channel approved | FUTURE / NOT EXECUTED |
| P05-T074 | Ad-hoc debug signature rejected for Developer ID external distribution | actual Apple Silicon and conditional Intel Mac Mach-O slice, notarization/Gatekeeper/entitlement proof if channel approved | FUTURE / NOT EXECUTED |
| P05-T075 | Developer ID certificate type and secure timestamp required for external app | actual Apple Silicon and conditional Intel Mac Mach-O slice, notarization/Gatekeeper/entitlement proof if channel approved | FUTURE / NOT EXECUTED |
| P05-T076 | Apple notarytool submission ticket actually verified before claim | actual Apple Silicon and conditional Intel Mac Mach-O slice, notarization/Gatekeeper/entitlement proof if channel approved | FUTURE / NOT EXECUTED |
| P05-T077 | Gatekeeper/stapling clean actual Mac verification done if release channel approved | actual Apple Silicon and conditional Intel Mac Mach-O slice, notarization/Gatekeeper/entitlement proof if channel approved | FUTURE / NOT EXECUTED |
| P05-T078 | Mac App Store App Sandbox channel distinct from Developer ID notary flow | actual Apple Silicon and conditional Intel Mac Mach-O slice, notarization/Gatekeeper/entitlement proof if channel approved | FUTURE / NOT EXECUTED |
| P05-T079 | Missing Apple Developer account/fee approval produces SIGNING_REQUIRED without spend | actual Apple Silicon and conditional Intel Mac Mach-O slice, notarization/Gatekeeper/entitlement proof if channel approved | FUTURE / NOT EXECUTED |
| P05-T080 | macOS update/rollback handles saved Editor projects and signed generations | actual Apple Silicon and conditional Intel Mac Mach-O slice, notarization/Gatekeeper/entitlement proof if channel approved | FUTURE / NOT EXECUTED |

## Group 6 — BROWSER-WASM-DELIVERY

| Future case | Objective and scenario | Independent oracle | Status |
|---|---|---|---|
| P05-T081 | Pinned Emscripten/LLVM wasm32 JS/worker build records toolchain digest | actual HTTPS origin response headers and real browser Wasm/JS/Service Worker/golden 2D/3D run | FUTURE / NOT EXECUTED |
| P05-T082 | WebGPU enabled bundle requires actual browser runtime capability query | actual HTTPS origin response headers and real browser Wasm/JS/Service Worker/golden 2D/3D run | FUTURE / NOT EXECUTED |
| P05-T083 | WebGL2 explicit reduced asset/shader path packaged if selected | actual HTTPS origin response headers and real browser Wasm/JS/Service Worker/golden 2D/3D run | FUTURE / NOT EXECUTED |
| P05-T084 | Threads and no-threads wasm builds have separate logical variant and manifest | actual HTTPS origin response headers and real browser Wasm/JS/Service Worker/golden 2D/3D run | FUTURE / NOT EXECUTED |
| P05-T085 | COOP COEP CORP and SharedArrayBuffer prerequisites tested for threaded delivery | actual HTTPS origin response headers and real browser Wasm/JS/Service Worker/golden 2D/3D run | FUTURE / NOT EXECUTED |
| P05-T086 | Wasm Content-Type application/wasm and gzip/br Encoding headers correct | actual HTTPS origin response headers and real browser Wasm/JS/Service Worker/golden 2D/3D run | FUTURE / NOT EXECUTED |
| P05-T087 | JavaScript Content-Type and CSP wasm-unsafe-eval conditional checked | actual HTTPS origin response headers and real browser Wasm/JS/Service Worker/golden 2D/3D run | FUTURE / NOT EXECUTED |
| P05-T088 | HTTPS/CORS/Permissions-Policy boundary verified on selected browser origin | actual HTTPS origin response headers and real browser Wasm/JS/Service Worker/golden 2D/3D run | FUTURE / NOT EXECUTED |
| P05-T089 | Immutable hashed JS Wasm worker and DATA-05 chunks version closure complete | actual HTTPS origin response headers and real browser Wasm/JS/Service Worker/golden 2D/3D run | FUTURE / NOT EXECUTED |
| P05-T090 | ETag/Cache-Control/hash versioning prevents mixed old/new shader assets | actual HTTPS origin response headers and real browser Wasm/JS/Service Worker/golden 2D/3D run | FUTURE / NOT EXECUTED |
| P05-T091 | Service Worker install validates entire new generation before activation | actual HTTPS origin response headers and real browser Wasm/JS/Service Worker/golden 2D/3D run | FUTURE / NOT EXECUTED |
| P05-T092 | Offline second-load uses verified last-good generation or typed unavailable | actual HTTPS origin response headers and real browser Wasm/JS/Service Worker/golden 2D/3D run | FUTURE / NOT EXECUTED |
| P05-T093 | Network interrupted mid-download cannot advance active cache generation | actual HTTPS origin response headers and real browser Wasm/JS/Service Worker/golden 2D/3D run | FUTURE / NOT EXECUTED |
| P05-T094 | Browser cache quota eviction does not destroy source/project last-good | actual HTTPS origin response headers and real browser Wasm/JS/Service Worker/golden 2D/3D run | FUTURE / NOT EXECUTED |
| P05-T095 | Unknown or unsupported browser/GPU tier gives explicit fallback error | actual HTTPS origin response headers and real browser Wasm/JS/Service Worker/golden 2D/3D run | FUTURE / NOT EXECUTED |
| P05-T096 | Real supported browser executes exported 2D/2.5D/3D game smoke if approved | actual HTTPS origin response headers and real browser Wasm/JS/Service Worker/golden 2D/3D run | FUTURE / NOT EXECUTED |

## Group 7 — SBOM-PROVENANCE-SECURITY

| Future case | Objective and scenario | Independent oracle | Status |
|---|---|---|---|
| P05-T097 | SPDX3 or CycloneDX1.7 SBOM schema selected with validated version | verifiable SPDX/CycloneDX SBOM/in-toto-SLSA builder trust/subject hashes and adversarial sandbox security tests | FUTURE / NOT EXECUTED |
| P05-T098 | Every native/JS/Wasm transitive library and runtime dependency inventoried | verifiable SPDX/CycloneDX SBOM/in-toto-SLSA builder trust/subject hashes and adversarial sandbox security tests | FUTURE / NOT EXECUTED |
| P05-T099 | Bundled fonts/images/samples/shaders have redistributable rights/NOTICE | verifiable SPDX/CycloneDX SBOM/in-toto-SLSA builder trust/subject hashes and adversarial sandbox security tests | FUTURE / NOT EXECUTED |
| P05-T100 | NLE-D009 engine source license OPEN blocks public artifact promotion | verifiable SPDX/CycloneDX SBOM/in-toto-SLSA builder trust/subject hashes and adversarial sandbox security tests | FUTURE / NOT EXECUTED |
| P05-T101 | Generated SBOM subject hash matches actual staged package content | verifiable SPDX/CycloneDX SBOM/in-toto-SLSA builder trust/subject hashes and adversarial sandbox security tests | FUTURE / NOT EXECUTED |
| P05-T102 | In-toto Statement v1 predicateType exact slsa.dev/provenance/v1 | verifiable SPDX/CycloneDX SBOM/in-toto-SLSA builder trust/subject hashes and adversarial sandbox security tests | FUTURE / NOT EXECUTED |
| P05-T103 | SLSA buildDefinition parameters and resolvedDependency digests verified | verifiable SPDX/CycloneDX SBOM/in-toto-SLSA builder trust/subject hashes and adversarial sandbox security tests | FUTURE / NOT EXECUTED |
| P05-T104 | SLSA runDetails builder identity and source ref verified independently | verifiable SPDX/CycloneDX SBOM/in-toto-SLSA builder trust/subject hashes and adversarial sandbox security tests | FUTURE / NOT EXECUTED |
| P05-T105 | GitHub attestations only generated from authorized trusted build context | verifiable SPDX/CycloneDX SBOM/in-toto-SLSA builder trust/subject hashes and adversarial sandbox security tests | FUTURE / NOT EXECUTED |
| P05-T106 | Untrusted fork PR lacks signing tokens and cloud deploy privileges | verifiable SPDX/CycloneDX SBOM/in-toto-SLSA builder trust/subject hashes and adversarial sandbox security tests | FUTURE / NOT EXECUTED |
| P05-T107 | SLSA L2 or L3 grade never asserted by merely existing JSON file | verifiable SPDX/CycloneDX SBOM/in-toto-SLSA builder trust/subject hashes and adversarial sandbox security tests | FUTURE / NOT EXECUTED |
| P05-T108 | Signer private key and credentials never emitted to logs/artifacts | verifiable SPDX/CycloneDX SBOM/in-toto-SLSA builder trust/subject hashes and adversarial sandbox security tests | FUTURE / NOT EXECUTED |
| P05-T109 | Malicious project postbuild script/shell token cannot execute arbitrary code | verifiable SPDX/CycloneDX SBOM/in-toto-SLSA builder trust/subject hashes and adversarial sandbox security tests | FUTURE / NOT EXECUTED |
| P05-T110 | Dependency confusion unpinned tag/mirror or poisoned cache rejected | verifiable SPDX/CycloneDX SBOM/in-toto-SLSA builder trust/subject hashes and adversarial sandbox security tests | FUTURE / NOT EXECUTED |
| P05-T111 | Malicious updater replay/downgrade/counterfeit signer key denied | verifiable SPDX/CycloneDX SBOM/in-toto-SLSA builder trust/subject hashes and adversarial sandbox security tests | FUTURE / NOT EXECUTED |
| P05-T112 | Signed package missing matching final subject digest rejected | verifiable SPDX/CycloneDX SBOM/in-toto-SLSA builder trust/subject hashes and adversarial sandbox security tests | FUTURE / NOT EXECUTED |

## Group 8 — RELEASE-ROLLBACK-CLEANMACHINE

| Future case | Objective and scenario | Independent oracle | Status |
|---|---|---|---|
| P05-T113 | Immutable INTERNAL/CANARY/BETA/STABLE release class approved by owner | actual BIZ-03 authorized release generation/journal/clean-machine install/update/rollback and owner DoD evidence | FUTURE / NOT EXECUTED |
| P05-T114 | Only BIZ-03 may request actual publish after full 1.0 DoD | actual BIZ-03 authorized release generation/journal/clean-machine install/update/rollback and owner DoD evidence | FUTURE / NOT EXECUTED |
| P05-T115 | Owner cost and security signoff required before paid certificate or hosting | actual BIZ-03 authorized release generation/journal/clean-machine install/update/rollback and owner DoD evidence | FUTURE / NOT EXECUTED |
| P05-T116 | Staging uses content digest and size limits before activation | actual BIZ-03 authorized release generation/journal/clean-machine install/update/rollback and owner DoD evidence | FUTURE / NOT EXECUTED |
| P05-T117 | Download partial/corrupt artifact never becomes active generation | actual BIZ-03 authorized release generation/journal/clean-machine install/update/rollback and owner DoD evidence | FUTURE / NOT EXECUTED |
| P05-T118 | Atomic pointer swap only on same volume where guarantees exist | actual BIZ-03 authorized release generation/journal/clean-machine install/update/rollback and owner DoD evidence | FUTURE / NOT EXECUTED |
| P05-T119 | Multi-file/cross-volume update maintains journal not false atomicity | actual BIZ-03 authorized release generation/journal/clean-machine install/update/rollback and owner DoD evidence | FUTURE / NOT EXECUTED |
| P05-T120 | Power loss during stage returns to last-good runnable generation | actual BIZ-03 authorized release generation/journal/clean-machine install/update/rollback and owner DoD evidence | FUTURE / NOT EXECUTED |
| P05-T121 | Disk-full or quota failure preserves previous installed app and assets | actual BIZ-03 authorized release generation/journal/clean-machine install/update/rollback and owner DoD evidence | FUTURE / NOT EXECUTED |
| P05-T122 | Untrusted rollback to revoked vulnerable version blocked or audited exception | actual BIZ-03 authorized release generation/journal/clean-machine install/update/rollback and owner DoD evidence | FUTURE / NOT EXECUTED |
| P05-T123 | Channel pin and monotonic version anti-downgrade verified | actual BIZ-03 authorized release generation/journal/clean-machine install/update/rollback and owner DoD evidence | FUTURE / NOT EXECUTED |
| P05-T124 | Signer compromise revoke/denylist leads fail-closed update and roll-forward | actual BIZ-03 authorized release generation/journal/clean-machine install/update/rollback and owner DoD evidence | FUTURE / NOT EXECUTED |
| P05-T125 | Windows/Linux/macOS clean install/start/update/rollback smoke on actual OS | actual BIZ-03 authorized release generation/journal/clean-machine install/update/rollback and owner DoD evidence | FUTURE / NOT EXECUTED |
| P05-T126 | Browser version/cached service worker offline upgrade and rollback tested | actual BIZ-03 authorized release generation/journal/clean-machine install/update/rollback and owner DoD evidence | FUTURE / NOT EXECUTED |
| P05-T127 | Mobile distribution absent unless separate owner release approval is explicit | actual BIZ-03 authorized release generation/journal/clean-machine install/update/rollback and owner DoD evidence | FUTURE / NOT EXECUTED |
| P05-T128 | Final real evidence bundle license/signature/CI/DoD/approval required for DONE | actual BIZ-03 authorized release generation/journal/clean-machine install/update/rollback and owner DoD evidence | FUTURE / NOT EXECUTED |


## Current status
128 unique candidate tests, all FUTURE/NOT EXECUTED. **Catalog acceptance "Export reprodutível de aplicações aprovadas; falhas claras por target" remains NOT IMPLEMENTED/NOT VERIFIED**. No release, source license, platform package format, publisher credentials or signed artifact approved. `ADR-0074 PROPOSED`, 80/80 future code WOs BLOCKED.

[Architecture](../architecture/plat-05-build-export-distribution.md) · [benchmark protocol](../research/plat-05-build-export-benchmark-protocol.md) · [semantic API](../contracts/plat-05-export-release-api.md).
