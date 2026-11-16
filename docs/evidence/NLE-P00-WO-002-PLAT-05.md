# Evidence Bundle — NLE-P00-WO-002-PLAT-05 Reproducible Build, Export & Distribution Planning

**2026-11-15 | P00 DOCUMENTARY RESEARCH ONLY | [Research #337](https://github.com/KayzenRoot/stormline/issues/337) OPEN pending independent checkpoint | [future coding #89](https://github.com/KayzenRoot/stormline/issues/89) OPEN/BLOCKED.** Absolutely no engine build, signed artifact, SBOM file, attestation, actual package/install, browser deploy, hardware benchmark, user-facing distribution or owner-paid account action in this research.

## 1. Source Check OBSERVED before writing
- Exact requested main HEAD **d1369e8101ea86e2a14a4a12e9581fb8df4fa478**, zero open PR, no filename collision with PLAT-05 research/ADR-0074. Canonical source hierarchy checked checkpoint > Ledger/approved ADR > Scope > DoD > Architecture > Requirements.
- Catalog ordinal **71/80** PLAT-05, acceptance "Export reprodutível de aplicações aprovadas; falhas claras por target". Formal graph **PLAT-01 + PLAT-02 + PLAT-03 + PLAT-06 + DATA-05 EXACT**, predecessor ADR-0069/0070/0071/0072/0013 all PROPOSED and no implemented code. QA-01/QA-04/BIZ-03 and mobile PLAT-04 only integration/transitive, NOT formal edges.
- Registry 80 entries, **70 researches documented, 10 pending, PLAT-05 RESEARCH_PENDING, 80/80 future code WOs BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, executor_ready=0, approved_adr=0, release_class UNDECIDED all, engine_implemented=false**. Source code license NLE-D009 OPEN, owner public MVP prohibited before approved 1.0 DoD.
- [Research Work Order](../work-orders/NLE-P00-WO-002-PLAT-05.md) contains exact pre-write Git blob **SHA-1 object IDs** for source lock, not raw SHA-256; future executor must compute raw SHA-256 before code activation and stop when STALE.

## 2. External technical sources checked, not adopted software
- [CMake target toolchain](https://cmake.org/cmake/help/latest/manual/cmake-toolchains.7.html) distinct host-vs-target ABI and source recipes; [SOURCE_DATE_EPOCH](https://reproducible-builds.org/docs/source-date-epoch/) reproducible pre-sign metadata.
- [SLSA v1.2 build provenance](https://slsa.dev/spec/v1.2/build-provenance) specifies in-toto `Statement/v1` and predicateType `https://slsa.dev/provenance/v1` with buildDefinition/buildType/externalParameters/resolvedDependencies, runDetails/builder; [GitHub artifacts](https://docs.github.com/en/actions/how-tos/secure-your-work/use-artifact-attestations/use-artifact-attestations) `actions/attest@v4` available under specific repository/permission plans but no actual trusted build job currently. [SPDX3](https://spdx.dev/use/specifications/) and [CycloneDX 1.7](https://cyclonedx.org/specification/overview/) SBOM format candidates, no SBOM generated.
- [Windows MSIX signing](https://learn.microsoft.com/en-us/windows/msix/package/signing-package-overview) production trust chain/self-signed only trusted development, Store re-signing/CA and Azure Artifact Signing eligibility and cost; no publisher ID/certificate or Store account.
- [Flatpak builder](https://docs.flatpak.org/en/latest/building.html) runtime/SDK/manifest and portals vs [AppImage old glibc baseline](https://docs.appimage.org/introduction/concepts.html), exclude GPU driver-specific libraries; no distro ABI test.
- [Apple Developer ID notarization](https://developer.apple.com/documentation/security/notarizing-macos-software-before-distribution/) valid Developer ID/hardened runtime/notarytool+stapler/Gatekeeper; separate App Store channel, Apple Developer enrollment/fees and Xcode user access not approved. macOS native Apple Silicon arm64 vs Intel Mac eligible <=26 conditional from predecessor PLAT-06.
- [Emscripten deploy](https://emscripten.org/docs/compiling/Deploying-Pages.html) wasm/JS/data/worker, MIME, precompression and browser cache; PLAT-03 origin/CSP/COOP+COEP/WebGPU/WebGL2 and asset-generation stability, none hosted/verified.
- [GitHub immutable releases](https://docs.github.com/en/code-security/concepts/supply-chain-security/immutable-releases) potential protected asset/channel, NO release generated/enabled.
- Exact third-party versions/licensing, asset/font rights/SBOM, source license NLE-D009, actual signing availability/cost, OS min versions, publisher support, performance and 1.0 classes **UNDECIDED/NOT VERIFIED**.

## 3. Eight ADD-ONLY Markdown research documents
1. [Architecture](../architecture/plat-05-build-export-distribution.md).
2. [ADR-0074 PROPOSED](../adr/0074-plat-05-reproducible-export-release-policy.md).
3. [Technology/license/supply-chain/security matrix](../research/plat-05-toolchain-license-supply-chain-matrix.md).
4. [Versioned semantic export/release contracts](../contracts/plat-05-export-release-api.md).
5. [Exactly 128 FUTURE/NOT EXECUTED P05 test objectives](../testing/plat-05-acceptance-matrix.md).
6. [Multi-target real benchmark protocol](../research/plat-05-build-export-benchmark-protocol.md).
7. [Work Order](../work-orders/NLE-P00-WO-002-PLAT-05.md).
8. This Evidence Bundle.

## 4. Current truth and non-evidence
| Documentary support | What has NOT been demonstrated |
|---|---|
| Toolchain and source lock receipts proposed from real Git files | no CMake/MSVC/GCC/Xcode/Emscripten compile or two real independent builds |
| Windows/Linux/macOS/browser package alternatives mapped | no PE/ELF/Mach-O/wasm output or live device test |
| DATA-05 immutable cooking consumed in proposed API | no actual cooked bundle/manifest data, CDN, cache, assets |
| SPDX/CycloneDX/SLSA/GitHub attest standards researched | no real SBOM/provenance attestation/verified builder identity |
| Windows/MSIX, macOS developer notary, Linux sandbox/Gatekeeper evidence gates | no certificate, signed package, notary ticket, Store/AppImage/Flatpak release or OS install |
| Update/rollback crash and last-good contract proposed | no package manager, software updater or user project transaction |
| 128 future P05 tests/benchmark protocol | zero P05 tests executed; no CPU/RAM/bytes/p95/p99/reproducibility measurements |
| GitHub Doc CI | **PENDING actual research PR run/job, observed later**, does NOT certify binaries/security or performance |

## 5. PR/CI/audit and merge observations PENDING
Research branch `docs/NLE-P00-WO-002-PLAT-05-export-research`, BASE **d1369e8101ea86e2a14a4a12e9581fb8df4fa478**. Do **not** claim PR/head, Docs Validation success, pt-BR audit, squash SHA or main readback before these actual operations occur. Research issue #337 OPEN until independently audited checkpoint; coding issue #89 OPEN/BLOCKED. Documentation LOW risk; future native export ELEVATED, signing/private credentials/publication HIGH_ASSURANCE. No harmful or high/critical changes, no shell execution or payments. If failing audit/CI, correct in same PR; no force push.

## 6. Checkpoint Delta PROPOSAL ONLY, NOT SELF-PROMOTED
After research PR exact-head CI SUCCESS + objective pt-BR APPROVED + squash/main readback, create **separate five-file checkpoint PR**: docs/11-checkpoint.md, docs/08-backlog.md, docs/queue/implementation-registry.json, this WO, Evidence. Sole registry semantic PLAT-05 `research_status RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED`, other 79 modules and root fields unchanged. Target **71/80 researches documented (88.75%), 9 pending, ALL 80 future coding WOs BLOCKED, executor_ready=0, approved_adr=0, all release_class UNDECIDED, engine_implemented=false**. ADR-0074 PROPOSED; P05-T001..P05-T128 FUTURE/NOT EXECUTED; no real release. Its own Doc CI/audit/squash/main readback required before close research issue #337, #89 remains OPEN/BLOCKED.
Then **four-Markdown-only factual historical closeout** in new PR checkpoint/backlog/WO/Evidence with own Docs CI/pt-BR audit/squash/main readback. Next REAL catalog **QA-01 Build & Continuous Integration**, ordinal **72/80**, formal dependency **CORE-01** only; future code [#90](https://github.com/KayzenRoot/stormline/issues/90) remains OPEN/BLOCKED.


## Research #338 completed documentation; checkpoint independently proposed
- [Research PR #338](https://github.com/KayzenRoot/stormline/pull/338): BASE `d1369e8101ea86e2a14a4a12e9581fb8df4fa478`, HEAD `ae748fa417789993b8f8aa8db71e26e69b55564a`, **exactly eight NEW Markdown**: architecture, ADR-0074 PROPOSED, technology/license/supply-chain security, export/distribution semantic API, 128 future P05 tests, benchmark protocol, Work Order, Evidence. [Docs Validation run #43795314090](https://github.com/KayzenRoot/stormline/actions/runs/43795314090) **SUCCESS** job #133062693133 (Source Pack/links, catalogue DAG, 80-registry and Zcode blocked selector), [objective pt-BR audit #6906046148](https://github.com/KayzenRoot/stormline/pull/338#issuecomment-6906046148) **APPROVED documentary**, normal squash/main readback `cd22e6c35583ed661b034a92838cb8001af77e90` with ADR-0074 PROPOSED and original 70/80 registry unchanged at research integration.
- Independent checkpoint PROPOSAL: **SINGLE registry semantic field** PLAT-05 `research_status: RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED`, other 79 full module objects and root fields unchanged. Target **71/80 researched (88.75%), 9 pending, all 80/80 future code WOs BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, executor_ready=0, approved_adr=0, all release classes UNDECIDED, engine_implemented=false**. Formal DAG PLAT-01+PLAT-02+PLAT-03+PLAT-06+DATA-05 unchanged, NLE-D009 source license OPEN, 128 tests P05-T001..P05-T128 FUTURE/NOT EXECUTED, no actual toolchain build, reproducibility comparison, SBOM, SLSA attestation, signature, notarization, installer, browser deployment or clean host smoke.
- [Research issue #337](https://github.com/KayzenRoot/stormline/issues/337) remains OPEN until independently validated checkpoint with its own Docs CI/audit/squash/main readback; future coding [#89](https://github.com/KayzenRoot/stormline/issues/89) remains OPEN/BLOCKED. After verified checkpoint close #337 then independent factual historical PR **4 Markdown only** (checkpoint/backlog/WO/Evidence), own CI/audit/squash/main readback. Next actual catalog **QA-01 Build & Continuous Integration** ordinal **72/80**, formal **CORE-01 only**, future code #90 remains OPEN/BLOCKED.
- Documentation CI and issue audit do NOT certify cross-platform compilers, physical GPUs, independent build equality, SLSA signing or software security. Research #337 open until checkpoint proof.
