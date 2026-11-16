# BIZ-03 — 2026 Installer, Update Trust, Supply Chain and Licensing Research Matrix

**2026-11-16 P00, issue #370, BASE `3d2ad393ab4b70460e7d5cb46f82e03d2f5c9935`. No tools adopted or executed, source license NLE-D009 OPEN.** Formal PLAT-05 + BIZ-01 + QA-04 only (all PROPOSED ADRs); repo docs CI not a native build. Upstream docs are current research leads, not verified Stormline support.

## Native installer and channel alternatives
| Target / mechanism | Candidate attributes and licenses | Specific threats and decision gate |
|---|---|---|
| Windows MSIX (Store) | Package identity/updates and **Store re-signs MSIX packages** after certification; platform account/review separate | Do not confuse with automatic signing of MSI/EXE; Store fees/eligibility and long-term support undecided |
| Windows MSIX sideload | sign package yourself with recognized certificate; app identity, install and update policy | cert lifetime/rotation, trust store, signed min OS/device profile, no cert available today |
| Windows MSI/EXE (WiX Toolkit/NSIS/Inno candidate) | own installer conditions and upgrade/removal semantics; exact upstream SPDX/version audited | Store MSI/EXE must be CA-signed, immutable versioned HTTPS, offline and silent per Microsoft program, UAC eligible; not Store re-signed |
| macOS Developer ID .app/DMG/PKG | Hardened Runtime, timestamp, `notarytool`, stapling, Gatekeeper; Apple Developer Program Account Holder gate | notary service does NOT certify security, App Store route separate; Xcode/notary certificate not free guaranteed |
| macOS Sparkle update | MIT upstream at [Sparkle project](https://sparkle-project.github.io/); appcast Ed25519/EdDSA, binary delta support | distinct signing and TUF feed integration, exact framework tag/MIT transitive dependencies, supported macOS >=12 per upstream |
| Linux Flatpak/OSTree | packages via signed repository, sandbox portals & app update ownership, Flatpak site-based protocol | Linux distro/runtimes, permissions, external repo trust and app ID/a11y tested; no automatic full Linux compatibility |
| Linux AppImage | portable package, update mechanism varies by release tool and FUSE | host libc baseline, FUSE version, self-update authenticity and delta scheme not assumed; audit exact tool/license |
| Linux .deb/.rpm | distro package manager owns upgrades/uninstall/dependency | distro-supported repos/signing, deb/rpm scripts elevated privileges and open-ended maintainer script execution risk |
| Linux portable tar | useful offline/internal smoke | no automatic update, no desktop associations without consent, ownership/uninstall and trust explicit |
| Web version manifest/service worker | immutable JS/WASM/assets from PLAT-05, cache version scheme and atomic activation | stale SW and cross-version game data; browser service worker updating != native installer, hosting/HTTPS/CSP costs |

## Secure update specifications
- [The Update Framework specification](https://theupdateframework.github.io/specification/latest/) uses root, targets, snapshot, timestamp metadata roles; threshold signatures, hashes/lengths, timestamp expiry and monotonic metadata versions address arbitrary software, rollback/freeze and mix-and-match. **TUF is not installed or certified in Stormline**.
- Treat channel pointer to digest and per-OS/arch/feature target as immutable signed statement; nested plugin and SDK packages require own signed scope and BIZ-01 redistribution grant. Reject unknown required metadata and cross-target patch.
- Delta optimizations (binary diff/bsdiff/zsync/Rsync candidates) are not inherently authentic: validate **full reconstructed artifact hash and signature** against trusted manifest and support full-download fallback for mismatched base, interrupted transfer, incompatible algorithm, excessive scratch/disk use.
- Rotation: separate offline trusted root threshold and online timestamps, minimize key exposure in CI, plan key compromise, revocation, escrow/recovery for lost root and threshold validation; unsupported cryptographic primitives/generation require owner security choice.

## Source, provenance, SBOM and rights
| Area | Authoritative current reference | Stop gate |
|---|---|---|
| SLSA build and source tracks | [SLSA v1.2](https://slsa.dev/spec/v1.2/), [provenance](https://slsa.dev/spec/v1.2/build-provenance) | artifacts must really be built, attested, independently verified; no invented SLSA L2/L3, GitHub docs CI ≠ provenance |
| GitHub public artifact attestations | [GitHub docs](https://docs.github.com/en/actions/how-tos/secure-your-work/use-artifact-attestations/use-artifact-attestations) available in public repo plan | actionable later for *actual* artifact binary digest; verify trusted workflow/identity, public repository doesn't equal open license |
| SBOM | [SPDX 3.x](https://spdx.github.io/spdx-spec/) vs [CycloneDX 1.7](https://cyclonedx.org/specification/overview/) from QA-04 | exact per-file/component asset font SDK & runtime provenance, transitive closure, package notices; SBOM is inventory, not commercial rights |
| Mac signatures | [Apple notarization](https://developer.apple.com/documentation/security/notarizing-macos-software-before-distribution/), [Developer ID](https://developer.apple.com/developer-id/) | valid developer account, signing certificate, Hardened Runtime, ticket stapled where needed, native machine verification |
| Windows Store packaging | [Microsoft MSIX](https://learn.microsoft.com/en-us/windows/apps/publish/publish-your-app/package-version-numbering), [MSI/EXE Store](https://learn.microsoft.com/en-us/windows/apps/publish/publish-your-app/msi/app-package-requirements) | distinguish Store-re-signed MSIX from CA-signed third-party MSI/EXE; do not publish unsigned |
| Legal source rights | BIZ-01 ADR-0080 PROPOSED, NLE-D009 OPEN | engine, game exports, bundled SDK/plugins/assets and crash consent need approved contracts; public repo != reuse grant |
| Original demo/sample | BIZ-02 ADR-0081 PROPOSED | owner-created originals only, material license clearance and attribution, no third-party ripped assets |
| Secrets and store accounts | OS platform/QA-04 | no secrets to PR forks, runner logs or unsigned artifacts, explicit cost/funding approval |

## Operational security, privacy and support
- Native installers must protect local user data, install with least privilege, avoid elevation when user-scoped paths suffice, defend symlink/hardlink/race attacks, zip-slip/decompression bombs, stale ACL and writable install directories; never overwrite user-owned projects or delete on default uninstall.
- Crash reports **OFF by default**, reason/consent, OS error registers, stack sanitized, no arbitrary project files or source, token/email/path redaction, retention and safe deletion; consider LGPD/GDPR compliance requirements with BIZ-01 legal review. Crash reporter cannot be used as covert always-on telemetry.
- Accessibility: keyboard traversal, screen reader roles, scalable text, high contrast and localized messages for installer/update/recovery/rollback/consent. Error codes actionable; no noninteractive "developer needed" baseline.
- Conditional security updates carry signed urgency and reproduction evidence; public release only after full 1.0 DoD; zero user base / zero measured MTTR today.
- Licensing of candidate tools must be verified at exact tag and *redistributed components* separated from internal tool usage. Sparkle upstream MIT noted as candidate; don't assume WiX/NSIS/Inno/Flatpak/AppImage/bsdiff/TUF clients share same license.
- GitHub public standard runner docs CI currently free-constraint; Windows/macOS build minutes, Apple account, signing certificates, hosted CDNs and physical QA may require costs, **not authorized**.

## Compatibility minima and release channels
Windows/x64 mandatory, Windows ARM conditional; Linux x86_64 plus ARM conditional, Wayland/X11 and glibc/libstdc++ baselines; macOS Apple Silicon native, Intel conditional; Web Chrome/Firefox/Safari if target feature supported with no native installer. OS and GPU versions NOT FIXED before PLAT/QA-05 evidence. INTERNAL only current release class, future BETA/CANARY/PUBLIC only owner-approved and legally cleared. Any unverified platform support label = NOT_QUALIFIED.

## Primary official URLs
- [Microsoft MSIX package distribution](https://learn.microsoft.com/en-us/windows/apps/publish/publish-your-app/package-version-numbering)
- [Windows MSI/EXE Store distribution requirements](https://learn.microsoft.com/en-us/windows/apps/publish/publish-your-app/msi/app-package-requirements)
- [Apple notarization and notarytool](https://developer.apple.com/documentation/security/notarizing-macos-software-before-distribution/)
- [Apple Developer ID trust](https://developer.apple.com/developer-id/)
- [The Update Framework spec](https://theupdateframework.github.io/specification/latest/)
- [SLSA v1.2 official](https://slsa.dev/spec/v1.2/)
- [SLSA v1.2 build provenance](https://slsa.dev/spec/v1.2/build-provenance)
- [GitHub artifact attestations public repositories](https://docs.github.com/en/actions/how-tos/secure-your-work/use-artifact-attestations/use-artifact-attestations)
- [Sparkle macOS updater](https://sparkle-project.github.io/)
- [SPDX specifications](https://spdx.github.io/spdx-spec/)
