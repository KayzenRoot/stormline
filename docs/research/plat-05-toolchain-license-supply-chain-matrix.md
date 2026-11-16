# PLAT-05 — Reproducible Build, Packaging, Toolchains, License, SBOM and Supply Chain Matrix (2026)

**2026-11-15 | DOCUMENTARY RESEARCH ONLY | [research #337](https://github.com/KayzenRoot/stormline/issues/337) | NLE-P00-WO-002-PLAT-05 | future coding [#89](https://github.com/KayzenRoot/stormline/issues/89) OPEN/BLOCKED | baseline `d1369e8101ea86e2a14a4a12e9581fb8df4fa478`.** Formal catalog prerequisites **PLAT-01 + PLAT-02 + PLAT-03 + PLAT-06 + DATA-05 EXACT**; prior ADR-0069/0070/0071/0072/0013 PROPOSED. 70/80 research documented before this module, 10 pending, 80/80 code WOs BLOCKED, approved ADR=0, ready=0, release classes UNDECIDED, engine_implemented=false, NLE-D009 source license OPEN.


**Research sources/alternative products only, no adopted SDK/tool, purchased code-signing identity, registered store publisher, generated binary, certified SLSA level or publicly distributed engine.** Pin exact tags and rights before any implementation.

## Primary technical research (official upstream 2026)
| Topic/source | Verified technical fact | Engineering gate |
|---|---|---|
| [CMake toolchains cross compile](https://cmake.org/cmake/help/latest/manual/cmake-toolchains.7.html) | host vs target system distinct, toolchain file and `try_compile` context, cross-built executable cannot normally run on host | `CMAKE_TOOLCHAIN_FILE` and target OS/ABI/SDK lock; independent target/device smoke required |
| [SOURCE_DATE_EPOCH](https://reproducible-builds.org/docs/source-date-epoch/) | standardized timestamp in UTC seconds from Unix epoch for reproducible builds | normalize locale/uid/path/archive/metadata; file bytes deterministic only under tested inputs, not code signature |
| [SLSA v1.2 build provenance](https://slsa.dev/spec/v1.2/build-provenance) | in-toto Statement v1, predicateType `https://slsa.dev/provenance/v1`, buildDefinition/buildType/externalParameters/resolvedDependencies, runDetails/builder | exact subject digests, identity and independent verification; self-written JSON != trusted SLSA L2/L3 |
| [SLSA v1.2 build levels](https://slsa.dev/spec/v1.2/build-track-basics) | L1 provenance, L2 hosted/signed provenance, L3 hardened builder | no security-grade claims without actual corresponding provenance and build isolation proof |
| [GitHub artifact attestations](https://docs.github.com/en/actions/how-tos/secure-your-work/use-artifact-attestations/use-artifact-attestations) | `actions/attest@v4` OIDC permissions, signed provenance and SBOM artifacts; Free/Pro/Team only public repo, release subject hash verifiable by gh | future code CI not created now; distinguish docs job from real build attestation and verify trust policy |
| [SPDX specification](https://spdx.dev/use/specifications/) | SPDX 3.0 current spec family, 2.3 older supported ecosystem formats | choose exact validator/tool and serialization after comparison; SPDX ID/relationship/asset licenses checked |
| [CycloneDX specification](https://cyclonedx.org/specification/overview/) | CycloneDX 1.7 published 2025 and current as observed | can model components/services/dependencies/crypto; library font/asset rights need explicit entries |
| [Microsoft MSIX signing](https://learn.microsoft.com/en-us/windows/msix/package/signing-package-overview) | signed package required/trusted chain; development self-signed only machines with explicit trusted cert; timestamp recommended | no “MSIX signed” with unsigned zip or dev cert for global public install |
| [Microsoft Windows distribution choices](https://learn.microsoft.com/en-us/windows/apps/package-and-deploy/choose-distribution-path) | Microsoft Store MSIX can re-sign, direct MSIX needs trusted signing, MSI/EXE external uses own signature; Microsoft Artifact Signing eligible regions/identity constraints | signing route owner-dependent; Azure Artifact Signing not assumed available worldwide or free, SmartScreen not instant |
| [Linux Flatpak builder](https://docs.flatpak.org/en/latest/building.html) + [manifest](https://docs.flatpak.org/en/latest/manifests.html) | flatpak-builder runtime/SDK, builder manifests/modules, `finish-args` sandbox permissions, portals; Flathub has extra policies | distro/architecture/runtime version pin, no broad `--filesystem=host` and no blanket GPU driver bundling |
| [AppImage concept](https://docs.appimage.org/introduction/concepts.html) + [best practices](https://docs.appimage.org/reference/best-practices.html) | build with old supported glibc base, bundle appropriate user deps but **exclude GPU-driver-specific OS libs**; real distribution smoke necessary | glibc version/symbol floor/ldd/objdump, XDG/Wayland/DRI host dependency, no false portable-to-any-Linux claim |
| [Apple Developer ID](https://developer.apple.com/developer-id/) | requires appropriate Apple Developer Program Account Holder team/certificate to sign Developer ID release | account fee/enrollment, credentials and signing capacity not verified/approved, no debug ad-hoc masquerade |
| [Apple notarization](https://developer.apple.com/documentation/security/notarizing-macos-software-before-distribution/) | valid Developer ID + Hardened Runtime + secure timestamp; modern `notarytool`, stapling/ticket, Gatekeeper checks; Mac App Store is separate | actual .app/helper slices/entitlements/notary+Gatekeeper on real Mac required, not just succeeded CI |
| [Emscripten deployment](https://emscripten.org/docs/compiling/Deploying-Pages.html) + [Wasm](https://emscripten.org/docs/compiling/WebAssembly.html) | wasm/JS HTML shell and workers/data variants; correct `application/wasm` MIME and content-encoding; precompress, split preloads, browser cache limits vary | separate threads/no-threads COOP+COEP policies, actual browser/GPU/headers/net tests; no generic WebAssembly binary guarantees |
| [GitHub immutable releases](https://docs.github.com/en/code-security/concepts/supply-chain-security/immutable-releases) | immutable release freezes associated tag and uploaded assets after publication when enabled | explicit permission/owner release gate, do not silently enable or publish; avoid mutable `latest` pointers as trust root |

## Candidate tools and licenses: not adopted or installed
| Tool / component | License/rights or terms to confirm by exact pinned release | Output & proof | Unresolved risk |
|---|---|---|---|
| C++20 CMake Presets + Ninja | CMake BSD-3-Clause, Ninja Apache-2.0, compiler/linker distinct | native target build graph | deterministic flags/PDB/Mach-O UUIDs, absolute build paths, static vs dynamic CRT |
| MSVC + MSBuild + Win SDK / clang-cl | Microsoft SDK/VC redistributable proprietary terms; LLVM/Clang Apache-2.0 with LLVM exceptions for upstream | Windows PE/CRT/dll and debug PDB | toolchain supply-chain drift, redistributable licensing and separate signing key |
| CPack/MSIX packaging & MSI/WiX | CMake CPack upstream BSD, WiX MIT for modern versions (verify pin), MSIX Windows SDK license | proposed Windows app manifest + templates | MSI elevates install path and repair/uninstall, MSIX package identity, code signing |
| Microsoft Artifact Signing/Azure | Microsoft paid managed identity with geographic restrictions | CA trusted signature outside Store where eligible | monthly cost, identity eligibility and SmartScreen trust, owner must authorize |
| Microsoft Store | store policies/account terms | Store signed MSIX and channel-managed update | developer registration/license, Store approval, 1.0 no-public-MVP |
| GNU/LLVM C++ Linux, oldest tested glibc sysroot | GPL with runtime exceptions/LLVM terms by component, sysroot redistribution verify | reproducible ELF symbols/ABI | AppImage driver libs, glibc floor/Wayland runtime missing, dynamic loader injection |
| Flatpak + OSTree | Flatpak LGPL-2.1-or-later family / OSTree LGPL-2.0+ family (verify exact upstream files/tags); runtimes distinct | sandbox package/repo signature | portal/network/XDG permissions, wrong runtimes, Flathub approval |
| AppImageKit / linuxdeploy | tool/project license by pinned version (AppImageKit MIT family verify) | portable one-file AppImage | oldest distro ABI, FUSE availability, update URL and range, wrong GPU lib bundling |
| Apple Xcode27, SDK, codesign/notarytool | Apple proprietary platform SDK/developer terms | arm64/universal2 Mach-O, app/DMG/PKG, notarized Developer ID | Xcode27 ARM host, Intel native physical <=macOS26 conditional, membership and notarization credentials |
| Apple Mac App Store | Apple Developer Program/Store review rules | sandboxed Store-signed/update path | separate entitlements and review, not Developer ID notarization |
| Emscripten LLVM + Binaryen | upstream Emscripten/MIT, LLVM Apache-2.0 LLVM exception, Binaryen Apache-2.0 (verify exact tool versions) | wasm32 code + JS + HTML/worker/data | JS/Wasm debug/path randomization, browser WebGPU/threads and CSP/COOP/COEP |
| SPDX v3 or CycloneDX 1.7 generator | SPDX spec standard; CycloneDX Ecma/OWASP spec; scanner license by pinned tag | SBOM SPDX/CycloneDX for code/asset/fonts | scanner completeness/legal rights not automatically proven |
| SLSA/in-toto/Sigstore tools and GitHub attestations | upstream spec open licenses; tool licenses and GitHub service usage policy verify | provenance/attestation tied to subject hash | identity binding, untrusted fork CI OIDC secrets, fabricated level |
| Diffoscope/reprotest | Debian reproducible-builds tools GPL-family by package tag verify | two build compare/debug nondeterminism | SDK license and resource costs, no magic byte-identical signatures |
| Zstd/LZ4/meshoptimizer/KTX2/Basis | exact DATA-05 upstream tags + dual license cases, texture patents/asset rights | immutable cooked target bundles and notices | oversize/decompression bombs, codec ABI, never ship unlicensed fonts/graphics |
| Mobile SDK/Gradle/NDK/Apple signing | **NOT selected**; PLAT-04 owner/cost/Scope conditional | Android AAB/iOS IPA only later | no automatic new DAG edge or app-store release |

## Supply chain and security threat model
| Adversary/failure | Future blocking oracles |
|---|---|
| Malicious project name, asset path, recipe or LLM-generated shell arguments | canonical path/token schema, no uncontrolled subprocess/shell expansions, sandbox and capability approval, checked root/array |
| Dependency confusion, mutable CDN URL/tag, untrusted package mirror | verify every digest/pinned source, dependency allowlist, private cache isolation, no latest tags |
| CMake configure-time arbitrary command on untrusted project | sandboxed approved template only; no project-provided CMakeLists injection until privilege approval |
| Actions PR/fork untrusted workflow exfiltrates signing keys | read-only untrusted builds, OIDC key permissions only protected release workflow, environment approvals |
| CI cache poisoning across branches/architectures | immutable cache keys include OS/SDK/source/recipes, trust tier segregation, verify restored digest |
| Package timestamps, path/host/locale unpredictable | SOURCE_DATE_EPOCH, environment normalization and two independent build comparison of **unsigned payload** |
| Reproducible code payload != signed package | distinguish pre-sign and final signed hash, certificate, timestamp, notary/store re-sign proof |
| Fake SBOM or provenance | independent hash, source URI/ref/builder identity/predicateType validation, attestation generated by trusted builder |
| Wrong target bitness/ABI/CRT/ELF library/glibc/Mach-O slice | inspect PE/ELF/Mach-O/wasm exports + clean target OS/hardware runtime |
| macOS Developer ID ad-hoc key, disabled hardened runtime | fail gate without real Developer ID, entitlement list, notary ticket/stapler/Gatekeeper |
| Windows MSIX dev/self-signed used for public download | verify root of trust/reputation/channel; do not treat docs CI as signed artifact |
| Linux AppImage bundles GPU ICD/dri driver, Flatpak shares host FS | deny unapproved dynamic loader packages and broad portals; physical Wayland/X11/driver checks |
| Browser served wrong MIME, mixed JS/Wasm/data generation | strict HTTP headers/content-addressed manifest, same-origin verified hashes, atomic cache version and CSP |
| Browser COOP/COEP or service worker old and new code races | versioned app shell + asset closure and cache activation two-phase; offline fallback/eviction |
| Product AssetId/source path identity confused with bundled filename | verify DATA-05 asset IDs, original authoring snapshot unchanged, normalized path traversal and Unicode collision |
| Large content decompression/payload overwritten after download | length/hash/quota bounds, archive traversal/symlink checks, immutable staging before active pointer |
| Compromised signer, malicious rollback/replay | trusted key rotation/revocation, channel pin/sequence and audited signed rollback exception |
| Multi-file cross-volume update mislabeled atomic | journal staged directory and pointer/ref rollback, fsync and disk-full/power-loss recovery |
| Missing licensing of fonts/images/samples or closed engine code | actual redistribution inventory and notices, NLE-D009 LICENSE OPEN -> NO PUBLIC RELEASE |
| AI/MCP automatic publish into release branch | authorized capability and owner release gate; no force push, no silent account creation |
| Release only on unsupported OS/device and no real tests | reject unsupported target profile, physical smoke/compat and BenchmarkReceipt or NOT_EXECUTED |

## Future security grading
Documentation LOW with actual Docs CI only, future native cross-platform build/export ELEVATED, code-signing private keys/credentials/certificate or production publish HIGH_ASSURANCE (strong proof obligations, independent audit and rollback). No HIGH/CRITICAL documentary issue known at source, but **no code security certified**. Always evaluate [SLSA levels](https://slsa.dev/spec/v1.2/build-track-basics) instead of claiming by convention.

[Architecture](../architecture/plat-05-build-export-distribution.md) · [benchmark](plat-05-build-export-benchmark-protocol.md) · [ADR-0074](../adr/0074-plat-05-reproducible-export-release-policy.md).
