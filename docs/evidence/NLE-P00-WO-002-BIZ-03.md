# Evidence Bundle — NLE-P00-WO-002-BIZ-03 Release, Installer & Lifecycle P00

**2026-11-16 · research #370 OPEN until approved checkpoint · future code #97 OPEN/BLOCKED · BASE `3d2ad393ab4b70460e7d5cb46f82e03d2f5c9935` · formal PLAT-05 + BIZ-01 + QA-04 only.** Current status: RESEARCH and independent CHECKPOINT PRs MERGED/READBACK, ADR remains PROPOSED, no public license/installer/engine. Historical PR-specific CI/audit is pending independent observation.

## 1. Source Check observed
- Repo GitHub `KayzenRoot/stormline` `main` exact `3d2ad393ab4b70460e7d5cb46f82e03d2f5c9935`; initial 0 open PR, tree `eac5c67cfae7f44e0604986e1894cf974350e638`. Source hierarchy checkpoint, Decisions Ledger, Scope, DoD, Architecture, Requirements, catalog, existing upstream ADR and contracts checked. Owner NLE-D009 engine source license **OPEN**, NLE-D010 brand OPEN, NLE-D013 no public MVP until full v1.0 DoD, D017 Windows/Linux/macOS editor and game export, Web targeted.
- Registry **80 total**, **78 research documented**, **2 pending BIZ-03 and CORE-04**. BIZ-03 `catalog_order=79` **zero-based** means last item (80th) rather than ordinal 79/80. `CORE-04 catalog_order=3` remains RESEARCH_PENDING even though historical ADR-0006 and [research PR #100](https://github.com/KayzenRoot/stormline/pull/100) were integrated; investigate this separately as possible checkpoint drift, do NOT mark 80/80 on BIZ-03. 80/80 future implementation WOs `BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`, zero executor_ready/approved ADR, all release classes UNDECIDED, engine_implemented=false.
- Formal BIZ-03 deps **PLAT-05 + BIZ-01 + QA-04** only. ADR-0074/0080/0078 all PROPOSED and NOT CODE. PLAT-05 proposed API owns immutable build/export manifest, BIZ-01 owns rights and source distribution, QA-04 security/SBOM/provenance. BIZ-03 owns installer/update/channel/lifecycle only.
- Source critical observed Git blob SHA-1 IDs are in [Work Order](../work-orders/NLE-P00-WO-002-BIZ-03.md); no false SHA-256 claim, future executor must compute source fingerprints freshly.

## 2. Primary official technical references
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
- Current research: TUF threshold root/targets/snapshot/timestamp, metadata expiration/monotonic and hash; MSIX Store re-signing **not** for MSI/EXE; Apple Developer ID/notarization `notarytool` plus actual Developer Program registration; Sparkle MIT candidate not adopted; SLSA v1.2 provenance for actual built artifact, not Docs CI; no rights granted by public GitHub.

## 3. Exactly EIGHT NEW Markdown research
1. [Architecture](../architecture/biz-03-release-installer-lifecycle.md)
2. [ADR-0082 PROPOSED](../adr/0082-biz-03-release-update-trust-policy.md)
3. [Technology/signing/security/license matrix](../research/biz-03-installer-updater-security-licenses-matrix.md)
4. [Versioned semantic release/installer/update API](../contracts/biz-03-release-lifecycle-api.md)
5. [128 FUTURE tests B03-T001..B03-T128](../testing/biz-03-acceptance-matrix.md)
6. [Future fault-injection and benchmark protocol](../research/biz-03-release-fault-injection-benchmark-protocol.md)
7. [Research Work Order](../work-orders/NLE-P00-WO-002-BIZ-03.md)
8. This Evidence Bundle.

## 4. Explicit limitations, zero PASS
| Planned | ACTUAL evidence absent |
|---|---|
| Windows installers MSIX/MSI/EXE | no compiled/signed Windows binaries or install test |
| Linux Flatpak/AppImage/DEB/RPM | no built/exported game or installed package |
| macOS .app/DMG/PKG + Developer ID and notarization | no Apple certificate, developer account, Mac CI, notarization or ticket |
| Web immutable JS/WASM deployment | no CDN, service worker, browser acceptance |
| TUF-style signed updater, delta patch and rollback | no root keys, threshold, secure feed, verified downloaded content |
| Crash-safe transactional update and project/save migration | no live project/save data, injected crashes, backups or rollback implementation |
| SHA/SBOM/SLSA provenance | no real built artifact, SBOM or attestation/trusted build proof |
| original samples/SDK redistributables | no signed SDK binary, original sample code or rights grant |
| privacy/telemetry opt-in accessibility | no crash reporter or user testing, telemetry currently nonexistent |
| 128 tests B03-T001..128 | future NOT EXECUTED, zero PASS |
| license commercial release | NLE-D009 OPEN and BIZ-01 ADR-0080 PROPOSED, not authorized |
| security/perf/OS qualification | docs CI only, no native C++/GPU/browser/hardware benchmarks |

## 5. Research PR and independently audited checkpoint completed; history still pending
- Research branch `docs/NLE-P00-WO-002-BIZ-03-research`, BASE `3d2ad393ab4b70460e7d5cb46f82e03d2f5c9935`, HEAD `1e3b21ccebd1619a868c9e78bb180258dbc2f18b`, [PR #371](https://github.com/KayzenRoot/stormline/pull/371) EXACTLY EIGHT ADDED Markdown and no registry/code/license edits, [Docs Validation #43848200892](https://github.com/KayzenRoot/stormline/actions/runs/43848200892) SUCCESS job #133233677478, [pt-BR objective audit #6913747938](https://github.com/KayzenRoot/stormline/pull/371#issuecomment-6913747938) APPROVED documentary, normal squash/main readback `afccb5872603b845b449a43b48f3d2fab206e1c9` observed.
- After research green CI/objective pt-BR APPROVED audit and normal squash/main readback, separate 5-MODIFIED checkpoint with sole semantic registry BIZ-03 `research_status RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED`, all other 79 module objects and root untouched. Target **79/80 researched, 1 pending CORE-04**, **80/80 coding WOs blocked**, zero ready/approved ADR, license OPEN. Close #370 only after verified checkpoint readback; code #97 OPEN/BLOCKED.
- Third historical closeout four Markdown only checkpoint/backlog/BIZ-03 future blocked WO/Evidence, own CI/audit/squash/readback; no premature "catalog 80/80 researched" statement. Next actual work candidate **CORE-04 Source Check / registry checkpoint reconciliation** (history PR #100/doc ADR-0006 already exists, but research status pending); avoid duplicating approved prior work without proof.

## 6. Independent checkpoint proposal awaiting own audited GitHub proof
- BASE `afccb5872603b845b449a43b48f3d2fab206e1c9`, research PR #371 already green/audited/merged/readback. This checkpoint should change FIVE MODIFIED files checkpoint/backlog/registry/BIZ-03 blocked future code WO/Evidence. Registry sole semantic BIZ-03 research_status RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED; other 79 full module records/root fields unchanged. Expected 79/80 documented, CORE-04 sole pending, 80/80 coding WOs BLOCKED, zero ready/approved ADR, license OPEN, engine false. No tests actually executed.
- Checkpoint PR number/head/run/job/audit/merge/readback must be written only after observed, then close #370 if verified (coding #97 stays OPEN/BLOCKED). Historical closure follows with a separate FOUR-Markdown-only PR and own CI/audit/squash/readback. CORE-04 next must reconcile existing historical research rather than blindly duplicating 8 docs.

## 7. Independent checkpoint actual evidence; historical closure scoped to FOUR Markdown
- [Checkpoint PR #372](https://github.com/KayzenRoot/stormline/pull/372) based on [research main readback `afccb5872603b845b449a43b48f3d2fab206e1c9`](https://github.com/KayzenRoot/stormline/commit/afccb5872603b845b449a43b48f3d2fab206e1c9) HEAD `d819c226cc11dbd694b31949b095bde3414e6f07`, exactly FIVE MODIFIED. **Only semantic registry delta BIZ-03 `research_status RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED`**, other 79 modules and root unchanged. [Docs Validation #43848562912](https://github.com/KayzenRoot/stormline/actions/runs/43848562912) SUCCESS job #133234909510, [objective pt-BR audit #6913797089](https://github.com/KayzenRoot/stormline/pull/372#issuecomment-6913797089) APPROVED documentary; normal squash/main readback `4a2c38cd36820dead3ebb6488dca7f05ef827fc6`.
- [Research issue #370](https://github.com/KayzenRoot/stormline/issues/370) CLOSED/completed at 2026-11-16T10:25:30Z **AFTER** checkpoint verification, implementation issue #97 OPEN/BLOCKED. Current registry **79/80** documented, **CORE-04 only pending**, **80/80 coding WOs blocked**, 0 ready, 0 approved ADR, release classes UNDECIDED, engine_implemented=false; BIZ-03 formal PLAT-05+BIZ-01+QA-04 only, ADR-0082 PROPOSED, engine NLE-D009 license OPEN.
- This historical closure is **FOUR existing Markdown MODIFIED** checkpoint/backlog/BIZ-03 blocked code WO/Evidence; no registry/CI/code/ADR/LICENSE/source changes. History PR exact head and CI/audit/squash/readback must be observed before marking history complete, no provisional PASS or product-release claim.
- Exactly 128 future B03-T001..B03-T128 cases all NOT EXECUTED and zero PASS; no OS installer, security signature, certified updater/TUF client, notarized Mac app, provenance/SBOM real artifact, SDK redistribution, real save migration or public launch. Next pending **CORE-04** requires source reconciliation since historical ADR-0006 and PR #100 exist.
