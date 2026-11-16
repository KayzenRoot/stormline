# BIZ-03 — Future Platform Installation, Update, Rollback, Security and Performance Protocol

**NOT EXECUTED; NO NUMERIC THRESHOLD APPROVED.** 2026-11-16, issue #370, BASE `3d2ad393ab4b70460e7d5cb46f82e03d2f5c9935`, future code #97 OPEN/BLOCKED, formal PLAT-05 + BIZ-01 + QA-04 ONLY. Docs-only CI, NLE-D009 license OPEN.

## Pre-registered future experiments
| Experiment | Mandatory comparison and evidence | Danger / abort |
|---|---|---|
| Clean native install/uninstall | Windows MSIX/MSI/EXE candidate, macOS DMG/PKG app, Linux Flatpak/AppImage/deb/rpm; real supported OS arch, non-admin/admin, offline | unsigned/not qualified/cost/account blocked, no user files deleted |
| Target launch & requirements | CPU SIMD flags, GPU drivers/VRAM, OS baseline, MSVC/libc/Apple runtime, browser feature probes | unsupported target must be reported before install, do not pretend emulator certifies physical hardware |
| Full vs delta verified update | signed TUF metadata, exact old/new digests/size, 5/25/100 MB or realistic assets, cold/warm CDN caches, network offline/loss | reconstruct full signed hash, expired/suspicious feed reject, fallback to full |
| Interrupted transactional install | process kill/power-loss simulation at every journal barrier, damaged disk/ACL, boot fail, cross-volume path | no last-good loss, no project writes without consent, otherwise REPAIR_REQUIRED |
| Project/save schema migration | golden original project fixtures, N-1/N/N+1 versions, CAS conflict, disk full, incompatible rollback, consent withdrawal | backup hash preserved, no silent irreversible downgrade |
| TUF trust compromise exercises | leaked delegated targets key, expired timestamp, old root, mismatch snapshot, wrong platform, malicious mirror | trust root protected; abort without applying bytes |
| OS signing and notarization | Windows CA / Store-MSIX signer differences, macOS Developer ID signed + notarized/stapled, Linux repo trust | actual credential/account/OS approval, no mock claim of production entitlement |
| Build/SBOM/provenance | QA-04 security receipt + PLAT-05 actual binary SHA from pinned toolchain vs external attestation and SPDX3/CycloneDX1.7 | provenance signature and identity must independently verify; SLSA level not claimed without full controls |
| Crash report diagnostics | opt-in OFF/ON, redact secret keys/token/project/source paths, consent revoke/delete request, fail network | zero outgoing events with opt-out; no private user data in public CI artifacts |
| Web rollout | content hash manifest, service worker activation/safe rollback, offline stale cache, CSP/COOP/COEP, WebGPU if actual target requires | cache incoherence and user data loss block release |
| Accessibility and support | real keyboard only + screen reader install/update error and localization; offline repair/rollback docs | no dependency on authoring/dev tools; thresholds future user study |
| Release channel incident | signed canary->stable promotion, cohort pauses, revoke signing key, synthetic crash spike | public channel prohibited by NLE-D013 until v1.0 approved, test only isolated internal fake service |

## Measurement method
- Separate future product **runtime proof** from documentary validation. Pin exact SHA, compiler, code signing cert identity/timestamp without secret, notarization ticket, OS patch/driver/GPU tier, physical vs VM/CI, target package manager, schema, original samples provenance and consent/rights.
- Perform independent iterations, cold start and warmed updates with controlled bandwidth/latency/jitter/packet loss; p50/p95/p99 installation and first-run times, full/delta bytes, temp disk peak, RAM/CPU, error rate, crash recoverability, support workflow success, time-to-repair distribution with sample size/variance. No made-up latency budgets; owner sets thresholds after baseline.
- Threat/fault matrix: hash mismatch, signature replay/expiry, revoked delegate, rogue mirror, metadata rollback, wrong OS/arch, decompression/path traversal, unauthorized install escalation, compromised CI runner, disk full, EOF midstream, power kill at commit boundaries, nested symlink, user concurrent save edit, post-upgrade boot fail, plugin misversion, backup restore, privacy leak and account/Store denial.
- Prioritize real OS: Windows x64 native plus ARM conditional, Linux supported glibc/distros and both Wayland/X11, macOS Apple arm64 and conditional Intel, actual browser Chrome/Firefox/Safari profiles; support qualification via QA-05 integration, not additional formal dependency.
- Safety thresholds HIGH/CRITICAL vulnerability, data loss, installer requiring unexpected root, unaudited license or signing key compromise, misleading public release, unmet OS min, failed required test => BLOCKED, not waived by docs Green. Independent rollback drill must verify source and save digest at each boundary; older binary may not read newer schema, explicit recovery receipt.
- CI R$0 is a constraint: existing GitHub public docs-only actions can verify links/DAG/registry; future Windows/macOS/Linux builders and Apple certificate/notary fees, physical devices, storage/CDN need separate approval. Do not auto-publish a signed release or require paid service.
- User release and generated games must remain private/internal until NLE-D009 licensing and BIZ-01 actual rights/notice proof, full v1.0 DoD approval, future QA-04 scans/attestations and PLAT-05 export proof.

## Evidence Bundle future
Each future B03-T### must capture exact artifact hash(s), target and owner versions, package/installer/uninstall logs, signer/trust chain, before/after user data digest, screenshots for accessibility if rights cleared, redacted crash traces, failure and retry causes, CI build job/run and trusted provenance, risks/rollback/owner approval. This P00 research does not satisfy any future runtime tests.

[Full 128 future cases](../testing/biz-03-acceptance-matrix.md) · [release API](../contracts/biz-03-release-lifecycle-api.md) · [research matrix](../research/biz-03-installer-updater-security-licenses-matrix.md).
