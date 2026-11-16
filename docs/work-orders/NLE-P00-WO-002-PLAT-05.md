# NLE-P00-WO-002-PLAT-05 — Reproducible Build, Export & Distribution Planning Work Order

**2026-11-15 | P00 DOCS ONLY | [Research issue #337](https://github.com/KayzenRoot/stormline/issues/337) OPEN until audited independent checkpoint | [future code #89](https://github.com/KayzenRoot/stormline/issues/89) OPEN/BLOCKED | Source main `d1369e8101ea86e2a14a4a12e9581fb8df4fa478`.** Risk LOW for documentary research; future native multi-OS build/install ELEVATED; signing private keys, paid publisher accounts and live releases HIGH_ASSURANCE, requiring specific authorization and independent review.

## OBJECTIVE
Create source-verified 2026 reproducible export architecture and contract for approved Windows/Linux/macOS **Editor and exported 2D/2.5D/3D games** and approved planned browser game; Windows MSIX/EXE alternatives, Linux AppImage/Flatpak/portable packages, macOS native/universal2 signed/notarized alternatives and browser Emscripten/Wasm+JS/data immutable deployment; DATA-05 immutable cooked profiles and verified bundles, SDK toolchain locks and normalized unsigned build, signing/Store separately, SPDX/CycloneDX SBOM, SLSA v1.2 provenance and optional GitHub attestations, SHA256 and security, user-consented BIZ-03 distribution/update/rollback; 128 objective future tests and benchmark. **Catalog acceptance:** "Export reprodutível de aplicações aprovadas; falhas claras por target." No engine code or real build exists in P00.

## CONTEXT & SOURCE CHECK
Source hierarchy: checkpoint > Decisions Ledger/approved ADRs > Scope > DoD > Architecture > Requirements > other. GitHub main exactly **d1369e8101ea86e2a14a4a12e9581fb8df4fa478**, **zero open PRs**; 80 registered modules, **70/80 research documented, 10 pending; PLAT-05 catalog order 71 RESEARCH_PENDING; ALL 80/80 code WOs BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, executor_ready=0, approved_adr=0, release classes all UNDECIDED, engine_implemented=false**. NLE-D009 engine license OPEN. NLE-D013 no public MVP until full 1.0 DoD; D014 2D/2.5D/3D and Web; D015 authorized AI-native operations; D016 80-module catalog; D017 Windows/Linux/macOS Editor+games mandatory, Web planned; D018 documented autonomy limited to safe free changes/no payment/high risk; D019/020 do not unblock future code. Formal prereqs **EXACT PLAT-01 + PLAT-02 + PLAT-03 + PLAT-06 + DATA-05** with source ADR-0069/0070/0071/0072/0013 all PROPOSED, no engine binary or benchmark. QA-01/QA-04, CORE-01, GFX/GAME, BIZ-03, PLAT-04 mobile, CI and NET are transitive/integration owners, NOT new formal catalog edges.

## CONTEXT LOCK (verified Git blob SHA-1 identifiers, NOT raw SHA-256)
If checkpoint, Ledger/approved ADR, Scope, DoD, Architecture, Requirements, catalog, registry, critical predecessor contract or HEAD changes unexpectedly, stop as STALE and rebuild context. Fingerprint source by exact Git OIDs below. Future code activation must compute **raw-file SHA-256** fingerprints (not claimed here).
- `AGENTS.md`: `3e57b719f8651407879ebb641707a048773ea4c2`
- `docs/00-source-hierarchy.md`: `58a377bc76cafdd3377d733d4f30ef53661bb034`
- `docs/11-checkpoint.md`: `19a505ddd842c53926618aefed695b42fc2ff668`
- `docs/10-decisions-ledger.md`: `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`
- `docs/03-scope.md`: `4ef605c74632ece080b2650e37dd83a415b63310`
- `docs/09-definition-of-done.md`: `160b3054db9ea1961308934b401488b838d24c3e`
- `docs/04-architecture.md`: `df62574cb3956c3ac9881631a4cf66be4e1abff1`
- `docs/02-requirements.md`: `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`
- `docs/product/module-catalog.md`: `18d69bca439831d65982cb0f8acbca1dbaa2eee9`
- `docs/queue/implementation-registry.json`: `0dcb1c317f82c646474638f86369f0d677e5df43`
- `docs/queue/work-orders/PLAT-05.md`: `c2cc732c8cc3334f112192dcd287972b2b5ef6bc`
- `docs/adr/0069-plat-01-windows-host-boundaries.md`: `f66b0ef162c36e28740855ebb98094fa9af8a85c`
- `docs/adr/0070-plat-02-linux-host-compatibility-policy.md`: `309a6278b446a2bb396cac2e37f7c6692b64f11b`
- `docs/adr/0071-plat-03-browser-runtime-capability-policy.md`: `c0034eb7eca99a1c2d724a5be625232d0d7c2ff3`
- `docs/adr/0072-plat-06-macos-apple-silicon-compatibility-policy.md`: `ef2e6211fa2bdb8951844d1a1cf99f7a72adee99`
- `docs/adr/0013-data-05-cooking-policy.md`: `ab661c5111a1d4aebf79381c0a3834e572c0c762`
- `docs/contracts/plat-01-windows-target-api.md`: `0abc9de156907125f7344de356b161b8aab36f41`
- `docs/contracts/plat-02-linux-target-api.md`: `a42ad1b6220dfbbf40d63bf29ae6e5c58afdff1e`
- `docs/contracts/plat-03-browser-target-api.md`: `8157d3b9ea1b9bd67b85f83628e0817f60d11d46`
- `docs/contracts/plat-06-macos-target-api.md`: `95f8c6e180877e8f12efea734f02bccd73394aca`
- `docs/contracts/data-05-cook-bundle-api.md`: `f78d246ac2730f503ede0a1823334a39ba4040e7`

## SCOPE — EXACTLY eight NEW Markdown only, NECESSARY
1. [Architecture](../architecture/plat-05-build-export-distribution.md).
2. [ADR-0074 PROPOSED](../adr/0074-plat-05-reproducible-export-release-policy.md).
3. [2026 technology/license/security supply-chain research](../research/plat-05-toolchain-license-supply-chain-matrix.md).
4. [Versioned export/distribution API semantics](../contracts/plat-05-export-release-api.md).
5. [Exactly 128 future P05-T001..P05-T128](../testing/plat-05-acceptance-matrix.md).
6. [Reproducible multi-target benchmark protocol](../research/plat-05-build-export-benchmark-protocol.md).
7. This Work Order.
8. [Evidence Bundle](../evidence/NLE-P00-WO-002-PLAT-05.md).

Research PR may only add these eight markdown, not modify checkpoint/registry/CI/backlog, no new approved tech/license or code. Independent later 5-file checkpoint and separate 4-Markdown closeout are sequential gates, NOT first PR scope.

## OUT OF SCOPE
No engine C++/SDL/NDK/Swift, desktop project build, Wasm compilation, installation SDK/compiler, GitHub Actions workflow change, app signing or notarization, Apple Developer paid membership/Windows Artifact Signing/Store account, release channel or CDN deployed, source license adoption, live package, actual platform/GPU test, update installer, private key/CI secret, authenticated cloud, mobile Android/iOS unless owner-approved PLAT-04, QA-01 future implementation, AI/MCP publish capability, “free public MVP,” forced cleanup or force push.

## FILES/SOURCES TO READ
AGENTS, all Context Lock source path/Git blobs, future code #89, predecessor ADR-0069/0070/0071/0072/0013 and platform semantic contracts, DATA-05 cooking plan, GFX/UI/NET and transitive QA-01/QA-04/BIZ-03 for **ownership only**. Primary current tech references: [CMake toolchains](https://cmake.org/cmake/help/latest/manual/cmake-toolchains.7.html), [SOURCE_DATE_EPOCH](https://reproducible-builds.org/docs/source-date-epoch/), [SLSA v1.2 provenance](https://slsa.dev/spec/v1.2/build-provenance), [GitHub attestations](https://docs.github.com/en/actions/how-tos/secure-your-work/use-artifact-attestations/use-artifact-attestations), [SPDX](https://spdx.dev/use/specifications/), [CycloneDX](https://cyclonedx.org/specification/overview/), [Windows MSIX signing](https://learn.microsoft.com/en-us/windows/msix/package/signing-package-overview), [Windows distribution paths](https://learn.microsoft.com/en-us/windows/apps/package-and-deploy/choose-distribution-path), [Flatpak](https://docs.flatpak.org/en/latest/building.html), [AppImage](https://docs.appimage.org/introduction/concepts.html), [Apple notarytool](https://developer.apple.com/documentation/security/notarizing-macos-software-before-distribution/), [Emscripten deployment](https://emscripten.org/docs/compiling/Deploying-Pages.html) and [GitHub immutable releases](https://docs.github.com/en/code-security/concepts/supply-chain-security/immutable-releases). Revalidate exact policy near implementation/release.

## REQUIREMENTS
GOV-001..005, approved owner NLE-D013..020 and catalog acceptance. Build/export reproducibility **only for owner-approved target application and exact toolchain recipe**, explicit fail for unsupported targets, signed artifact and unsigned reproducible payload separate. No automatic payment, publisher identity, privilege or release classification. Windows/Linux/macOS Editor and exported games mandated by owner; Web planned; mobile not mandatory.

## ARCHITECTURE RULES
1. Treat five formal predecessor contracts as immutable owner boundaries. DATA-05 cooks immutable chunks, PLAT-05 packages; BIZ-03 owns user installer/live release/update rollback (integration only), QA-01 CI runner and QA-04 security integration not automatic code scope.
2. Source asset revision and approved target profile -> toolchain+template hash -> DATA-05 CookReceipt -> normalized immutable unsigned package stage -> SHA256 and license/SBOM/SLSA provenanced subject -> security/signing channel optional -> separate final signed digest/attestation -> authorized BIZ-03 release candidate. Raw user project source preserved.
3. C++20 CMake Presets/Ninja, native Windows SDK/MSVC or clang-cl, Linux pinned glibc/sysroot, Xcode27 Apple Silicon host native arm64 and conditional Intel Mac <=macOS26 through universal2, Web Emscripten wasm32+JS and browser security/COOP+COEP only when approved. Toolchain versions and packages candidates only, no stack adopted without ADR/rights/hardware.
4. SOURCE_DATE_EPOCH, locale/TZ/file mode/path prefix map/archive timestamps/dependency order normalization, **two independent unsigned builds**. Sign/Notary timestamps and store re-sign mutate final bytes; maintain separate output identity and proof, not false byte-equality.
5. License source NLE-D009 OPEN, redistributable components/assets/fonts/shaders/SBOM/NOTICE and ABI verified before public release. SPDX3 vs CycloneDX1.7 candidate, SLSA provenance in-toto `https://slsa.dev/provenance/v1`; no invented SLSA level or GitHub signed artifact from Docs CI.
6. No ambient script execution, privileged/root package manager, untrusted AI/MCP arbitrary release, CI fork secrets, mutable dependency tags, package path traversal/symlink/zip-slip/decompression bomb, signing key exposure or automatic spend.
7. Platform store/certificate/manifest/installer and Web SW origin policies dedicated: Windows signed MSIX and CA trust, Linux AppImage ABI or Flatpak permission, macOS Developer ID hardened notary or App Store distinct, Web MIME/CSP/COOP+COEP/Service Worker/asset integrity. No universal OS feature assumption.
8. BIZ-03 staged immutable versioned updates with download hashes, anti-downgrade, transactional journal and last-good recovery; cross-volume multi-file operations not automatically atomic; rollback of known compromised package only with signed policy/security approval.

## CONSTRAINTS
Research docs risk LOW, CI free docs validation, no external mandatory reviewer or paid CodeRabbit. Future signing/provisioning/publish HIGH_ASSURANCE. GitHub branch/PR no force push, no prior decision rewrite, no paper claimed runtime benchmark or signed artifact. Owner must approve expenditures/risky writes/high issues. No work on QA-01 until PLAT-05 full historical gate complete.

## ACCEPTANCE CRITERIA
- [ ] Exactly **eight NEW Markdown** in research PR, links valid, no code/CI/registry/checkpoint/backlog or existing ADR.
- [ ] ADR-0074 **PROPOSED**, source hierarchy/owner directives honored, five **formal dependencies exact**, existing predecessor decisions unchanged.
- [ ] Current official technical research covers toolchains, cross-compile ABI, deterministic pre-sign vs signed/notary artifacts, four targets, mobile contingent, SBOM SPDX/CycloneDX, provenance in-toto/SLSA/GitHub, SHA256 and signed identity, platform software/right licenses, privacy and recovery.
- [ ] **P05-T001..P05-T128**, 8×16 unique, FUTURE/NOT EXECUTED and actual benchmark protocol, no false tests or hardware/security results.
- [ ] Research PR exact-head Docs Validation SUCCESS, objective pt-BR audit APPROVED, squash and verified main readback, no implementation.
- [ ] Independent checkpoint in **five modified files only** docs/11-checkpoint.md, docs/08-backlog.md, docs/queue/implementation-registry.json, this WO, Evidence. **Sole semantic registry PLAT-05 research_status RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED**, other 79 module objects and root unchanged. Expect **71/80 researched (88.75%), 9 pending, all 80 WOs blocked, ready=0, approved_adr=0, release classes UNDECIDED, engine=false**. Own CI/audit/squash/main readback, then research issue #337 CLOSED; code #89 stays OPEN/BLOCKED.
- [ ] **Historical closeout only four Markdown** checkpoint/backlog/WO/Evidence with own CI/audit/squash/main readback, and NEXT REAL module **QA-01 Build & Continuous Integration** order 72/80 formal **CORE-01**, future code #90 OPEN/BLOCKED.

## TESTS
In P00 only GitHub Docs Validation Source Pack, links, catalog DAG and 80 registry blocked selector; API check PR changed filenames statuses, independent JSON semantic diff, exactly 128 unique future IDs. NO actual build, binary, signed/notary package, SPDX/SLSA artifact, clean install, browser deployment or physical device tests. Future CODE tests require target signed/no-sign staged variants, two independent build comparisons, license/security, OS+browser smoke and update/rollback, p95/p99 with real samples and owner DoD.

## DELIVERABLES
Research issue #337, 8 new docs, research PR with exact source/head/diff and CI run/job, pt-BR verdict, normal squash/main readback; independently CI/audited checkpoint PR and research closure only after readback; historical closeout separate 4 Markdown PR own CI/pt-BR audit/squash/main readback; final state and next-module actual button.

## REVIEW FORMAT
pt-BR, exact branch/source/head/test counts and changed files, source blob OIDs vs raw SHA256 distinction, prior approved ADR scope, FIVE formal deps, source/target ABI/signing credentials and quotas/licensing/rights/SBOM/provenance/rollback, CI actual run/job and evidence readback, HIGH/CRITICAL defects and recovery, verdict **APPROVED / CORRECTION REQUIRED / BLOCKED**, proposed Checkpoint Delta, never claim code allowed.

## STOP CONDITION
STALE critical source, non-equal formal deps, wrong 8/128, missing/failing CI, unapproved expense/signing/publish/coding/privacy bypass, HIGH/CRITICAL without mitigation, source license open and public release, unverified signed artifact or fake SLSA => BLOCKED or CORRECTION REQUIRED same WO/PR. No advancing QA-01 until historical closeout is approved and read back.

## CHECKPOINT DELTA PROPOSAL (NOT SELF-PROMOTED)
Only after research CI+audit+normal squash/main readback: five-file independent checkpoint, one PLAT-05 research_status in registry, its own CI/audit/squash/main readback then close #337; final four-Markdown factual history its own gates; next REAL QA-01 order 72/80. Keep 80 future code WOs BLOCKED and ADR/license/release classes untouched.


## Research PR #338 factual results; independent checkpoint delta proposed
- [Research PR #338](https://github.com/KayzenRoot/stormline/pull/338): BASE `d1369e8101ea86e2a14a4a12e9581fb8df4fa478`, HEAD `ae748fa417789993b8f8aa8db71e26e69b55564a`, **exactly eight NEW Markdown**: architecture, ADR-0074 PROPOSED, technology/license/supply-chain security, export/distribution semantic API, 128 future P05 tests, benchmark protocol, Work Order, Evidence. [Docs Validation run #43795314090](https://github.com/KayzenRoot/stormline/actions/runs/43795314090) **SUCCESS** job #133062693133 (Source Pack/links, catalogue DAG, 80-registry and Zcode blocked selector), [objective pt-BR audit #6906046148](https://github.com/KayzenRoot/stormline/pull/338#issuecomment-6906046148) **APPROVED documentary**, normal squash/main readback `cd22e6c35583ed661b034a92838cb8001af77e90` with ADR-0074 PROPOSED and original 70/80 registry unchanged at research integration.
- Independent checkpoint PROPOSAL: **SINGLE registry semantic field** PLAT-05 `research_status: RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED`, other 79 full module objects and root fields unchanged. Target **71/80 researched (88.75%), 9 pending, all 80/80 future code WOs BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, executor_ready=0, approved_adr=0, all release classes UNDECIDED, engine_implemented=false**. Formal DAG PLAT-01+PLAT-02+PLAT-03+PLAT-06+DATA-05 unchanged, NLE-D009 source license OPEN, 128 tests P05-T001..P05-T128 FUTURE/NOT EXECUTED, no actual toolchain build, reproducibility comparison, SBOM, SLSA attestation, signature, notarization, installer, browser deployment or clean host smoke.
- [Research issue #337](https://github.com/KayzenRoot/stormline/issues/337) remains OPEN until independently validated checkpoint with its own Docs CI/audit/squash/main readback; future coding [#89](https://github.com/KayzenRoot/stormline/issues/89) remains OPEN/BLOCKED. After verified checkpoint close #337 then independent factual historical PR **4 Markdown only** (checkpoint/backlog/WO/Evidence), own CI/audit/squash/main readback. Next actual catalog **QA-01 Build & Continuous Integration** ordinal **72/80**, formal **CORE-01 only**, future code #90 remains OPEN/BLOCKED.
- This checkpoint own CI/audit/squash/main readback PENDING. All 80 implementation WOs remain BLOCKED.


## PLAT-05 factual historical closeout after independent checkpoint #339
- [Research PR #338](https://github.com/KayzenRoot/stormline/pull/338) BASE `d1369e8101ea86e2a14a4a12e9581fb8df4fa478`, HEAD `ae748fa417789993b8f8aa8db71e26e69b55564a`, **exactly EIGHT NEW Markdown** (architecture, ADR-0074 PROPOSED, technical/license/supply-chain security, typed export/distribution API, 128 P05 tests future, benchmark, Work Order, Evidence). [Docs Validation #43795314090](https://github.com/KayzenRoot/stormline/actions/runs/43795314090) **SUCCESS** job #133062693133 (Source Pack/links, catalog DAG, 80 modules and blocked selector), [objective pt-BR audit #6906046148](https://github.com/KayzenRoot/stormline/pull/338#issuecomment-6906046148) APPROVED documentary; normal squash/main readback `cd22e6c35583ed661b034a92838cb8001af77e90` with no registry mutation in research PR.
- [Independent checkpoint PR #339](https://github.com/KayzenRoot/stormline/pull/339): BASE `cd22e6c35583ed661b034a92838cb8001af77e90`, HEAD `dbd13f1d7b4baeb1d0af1528bac9f574f9287275`, exactly **FIVE MODIFIED** (checkpoint, backlog, registry, PLAT-05 WO, Evidence); **ONLY semantic registry PLAT-05 research_status RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED**, other 79 modules/root fields unchanged. [Docs Validation #43795558129](https://github.com/KayzenRoot/stormline/actions/runs/43795558129) **SUCCESS** job #133063452755, [pt-BR audit #6906077140](https://github.com/KayzenRoot/stormline/pull/339#issuecomment-6906077140) APPROVED documentary; normal squash/main readback `0ac47a2c5881af4c2748315beb6216fd02062535`.
- [Research issue #337](https://github.com/KayzenRoot/stormline/issues/337) **CLOSED** after independently approved checkpoint merge and verified main readback; [future coding #89](https://github.com/KayzenRoot/stormline/issues/89) remains OPEN/BLOCKED. Main registry **71/80 research documented (88.75%), 9 pending, all 80/80 implementation code WOs BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, executor_ready=0, approved_adr=0, release_class UNDECIDED all, engine_implemented=false**; NLE-D009 engine source license OPEN, ADR-0074 PROPOSED; P05-T001..P05-T128 FUTURE/NOT EXECUTED. **No actual Windows/Linux/macOS/browser binary, reproducibility A/B comparison, SBOM, SLSA trusted attestation, code signature/notary ticket, installer, updater, rollback, browser deploy or real hardware benchmark performed.**
- PLAT-05 catalog formal dependencies **PLAT-01 + PLAT-02 + PLAT-03 + PLAT-06 + DATA-05 exactly**, prior ADRs PROPOSED. BIZ-03 public release/install/update and QA-01/04 build security are integration only; mobile PLAT-04 unapproved 1.0. Reproducibility is for normalized unsigned payload; signing/notarization may change final digest, must verify independently. No accidental public MVP, source release license or cost.
- Next REAL catalog module **QA-01 Build & Continuous Integration**, ordinal **72/80**, formal dependency **CORE-01 ONLY**, future coding [#90](https://github.com/KayzenRoot/stormline/issues/90) remains BLOCKED. Historical closeout itself must change **exactly FOUR Markdown only** checkpoint/backlog/WO/Evidence, with independent own exact-head Docs Validation, pt-BR audit, squash and main readback; no JSON, code, CI, ADR or registry change.
