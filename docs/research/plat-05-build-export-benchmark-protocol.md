# PLAT-05 — Future Reproducible Multi-Target Export, Supply-Chain, Install and Rollback Benchmark Protocol

**2026-11-15 | FUTURE BENCHMARK DESIGN ONLY, NOT EXECUTED.** Research issue #337; future code #89 OPEN/BLOCKED; base `d1369e8101ea86e2a14a4a12e9581fb8df4fa478`. No real compiler run, duplicate reproducible builds, output artifact, code signature/notary ticket, web deployment, Windows/Linux/macOS physical smoke or numerical measurement.

## Goal and authority
For owner-approved native Windows/Linux/macOS Editor+exported 2D/2.5D/3D games and planned browser game target, obtain **repeatable unsigned build output under pinned inputs**, target-appropriate package/capability, license/SBOM/provenance truth, actual signature/sandbox/host installation/browser headers and recoverable updates after BIZ-03 authorization. Android/iOS excluded until 1.0 release class and separate approved PLAT-04 contract. Toolchain/export reproducibility, installer distribution, asset cooking and user storage are separate owners.

## Proposed build and recipient matrix (future only)
| Profile | Build host and target | Required independent evidence |
|---|---|---|
| EXP-WIN-A | approved Windows x64 MSVC or clang-cl SDK, x64 clean VM/physical Windows | Win CRT/DLL/PE imports, Editor and exported 2D/2.5D/3D smoke, MSIX if selected trusted signer |
| EXP-WIN-B conditional | Windows arm64 native package if approved | exact PE arch and actual arm64 Windows clean machine |
| EXP-LNX-A | pinned Linux oldest supported glibc sysroot and GNU x86_64 with AppImage/portable tar comparator | ldd/readelf GLIBC symbols, Wayland/X11 GPU, XDG portals and startup |
| EXP-LNX-B | Flatpak pinned org.freedesktop runtime/SDK sandbox profile | sandbox/portal/device perms and clean distro install/repo trust |
| EXP-MAC-A | Apple Silicon Xcode27 macOS host, native arm64 `.app` | Mach-O/Info.plist, Cocoa/Metal and Developer ID/notary Gatekeeper only if owner approves |
| EXP-MAC-B conditional | same Apple Silicon builder universal2 plus actual Intel Mac <=macOS26 for native x86_64 | lipo nested slices, deployment version, Rosetta different class |
| EXP-WEB-A | pinned Emscripten wasm32/JS/worker/asset bundle, actual HTTPS origin/browser GPU | correct MIME/CSP/isolation, WebGPU/WebGL2 variants, SW caching and real launch |
| EXP-TOOLS | two isolated clean builders per approved target with pinned toolchain/cache | reproducible unsigned payload hash/diffoscope result; no signing timestamp sameness promise |
| EXP-RELEASE | permissioned distribution channel/signing host (future) and BIZ-03 installer | validated supply-chain attestation, final signed subject, real install/update/rollback; no public MVP before version-1.0 DoD |
| EXP-MOBILE-OPTIONAL | Android/iOS hardware+store only after owner ratified separate PLAT-04 | not a mandatory PLAT-05 benchmark at P00 |

## Evidence lock for each future run
- Git BASE/HEAD, source SHA-256 Context Lock, approved ADR/release class/DoD, scene asset original rights and source project revision; DATA-05 cook manifest immutable hash, build/export template signed revision.
- CMake preset/toolchain SHA and compiler/SDK/native target ABI, C++/CRT/glibc/Mach-O Emscripten versions, local/UTC SOURCE_DATE_EPOCH, locale/TZ, CPU/OS/runner id, sandbox/container image digest, cache trust class, and two independent build environments with no shared mutable artifacts.
- Actual stage tree file paths/permissions/size/SHA and normalized unsigned payload, source map/Debug/DSYM/PDB separated, reproducibility differences in timestamps/archive entries/build-id/absolute paths. Binary package and final signed/notarized/stored hashes independently recorded; SLSA attestation subject must be **exact** artifact.
- SPDX3 or CycloneDX1.7 schema revision and validated transitive libraries/SDK/fonts/images/shaders/notices; public asset rights; source license NLE-D009 must be resolved by owner before any release.
- Real OS/arch clean host, GPU/driver/browser/HTTPS origin, install permission, Windows Store/App Installer or Linux sandbox/ABI or Mac Gatekeeper/signing/entitlement or Web SW/COOP/COEP headers; no VM-only claim of physical GPU test when physical required.
- Source user data and signing secret redacted; release actor/owner authorization, BIZ-03 current/next version and rollback journal security restrictions.

## Proposed future benchmark scenarios
| ID | Run / fixture | Timing, size, security and quality oracle |
|---|---|---|
| EXP-B01 | Cold pinned Windows x64 Editor build/export from fresh source and no cache | wall/CPU/peak RAM, native payload SHA, dependency ABI/arch, 2D/3D smoke |
| EXP-B02 | Second independent Windows build with identical inputs | unsigned content byte diff, SOURCE_DATE_EPOCH and nondeterministic fields |
| EXP-B03 | Windows MSIX vs unpackaged staged candidate if selected | package bytes, signature/trust when authorized, clean host first launch |
| EXP-B04 | Linux oldest-supported glibc cross/same distro compile | ELF symbols, builder time, loader dependencies |
| EXP-B05 | Linux Flatpak sandbox vs AppImage comparator | package size, build/install/load time, GPU/portals and failure |
| EXP-B06 | macOS arm64 native+optional universal2 packaging | Xcode SDK/ABI/slice proof, startup and notarization/Gatekeeper if selected |
| EXP-B07 | Browser Emscripten WebGPU and WebGL2 variant builds | wasm/js/data bytes, network waterfall, gzip/br, origin headers |
| EXP-B08 | DATA-05 target cook/generation reuse vs invalidation | asset CPU/IO/cache and content digest/cook expiry |
| EXP-B09 | Open Source/SBOM and binary provenance attest candidate | SPDX/CycloneDX errors, verified SLSA subject/builder/source, time/size |
| EXP-B10 | Artificial toolchain / malicious cache / provenance drift | rejection and unchanged source, no privileged action |
| EXP-B11 | User project with path traversal, malicious archive and codec bomb | bound resource, fail-closed and clean last-good source |
| EXP-B12 | Interrupted release candidate signing/no certificate | typed SIGNING_REQUIRED with retained unsigned/internal stage and no publish |
| EXP-B13 | Clean OS machine install/build/run/close Editor and exported games | target-appropriate visual golden, file/permission/launcher trust |
| EXP-B14 | Interrupted update after 10/50/90% bytes, disk full and power cut | staged manifest, rollback/roll-forward, protected user files |
| EXP-B15 | Web SW mixed/old cache under offline and concurrent tabs | active-generation closure, no mixed code/assets, explicit typed error |
| EXP-B16 | Complete security/owner release-class+DoD approval gate | no public publish unless license, signing, QA, risk and owner approval |

## Sampling and reproducibility criteria
- **Two** independent clean unsigned builds per frozen toolchain+profile, ideally different isolated runners but *identical inputs*, compare SHA-256 of staged canonical tree, per-file manifest, normalizations, and diffoscope if mismatch. A single cache hit does not count as reproducibility. If platform-specific debug IDs/signing prevent byte equality, report exact reason, separate unsigned payload and final signed output with distinct receipts; no invented 100% reproducibility.
- Across ≥5 independent cold/warm runs for duration distribution (startup/build/cook/install), record compiler cache, I/O bytes, CPU/RAM/latency, artifact payload and compressed bytes and variance. p95/p99 measured from enough actual independent samples to be meaningful; do not derive p99 from five summary trials alone.
- Clean hardware smoke for Editor plus exported game, browser real GPU/OS support and end-to-end failed-target and success-target oracles after binary exists; CI docs validation cannot substitute.
- Cross-target comparisons normalize original scene/data and quality tier; OS-specific formats/feature differences and signing/notary tasks must be separated as different benchmark phases, not hidden in single “export speed.”
- Threat injection results are evidence receipts, no real secrets, no demo upload/signed publication without owner. Performance thresholds, storage/CDN cost budgets, min OS/support matrix, source license and release class **not fixed** in P00.

## Future BuildExportBenchmarkReceiptV1
Source/project revision + full SHA-256, target profile/arch/OS, toolchain/template/cook licenses and digests, reproducibility independent runs with byte diff and confidence, unsigned stage manifest, signed final digest/verification/notary where approved, SPDX/CycloneDX and SLSA statement subject/issuer verification, actual clean host/browser smoke, CPU/RAM/io/network/storage/battery if applicable, issue severity/mitigations, rollback/staging journal, owner approval and category NOT_EXECUTED/PASS/FAIL/UNSUPPORTED/BLOCKED.

[128 future tests](../testing/plat-05-acceptance-matrix.md) · [architecture](../architecture/plat-05-build-export-distribution.md) · [supply-chain](plat-05-toolchain-license-supply-chain-matrix.md).
