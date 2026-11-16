# Evidence Bundle — QA-05 Compatibility & Release Qualification | NLE-P00-WO-002-QA-05

**2026-11-16 | P00 DOCUMENTARY RESEARCH ONLY | [research issue #357](https://github.com/KayzenRoot/stormline/issues/357) OPEN until independent checkpoint readback | future code [#94](https://github.com/KayzenRoot/stormline/issues/94) OPEN/BLOCKED | BASE main `a42519c8a79346a4974fa74c44f7cac26f4ad43c`.** QA-05 order 76/80, **FORMAL DEPENDENCIES EXACT QA-02 + PLAT-05**, predecessor ADR-0076/0074 both PROPOSED. Baseline 75/80 researched, 5 pending, all 80 implementation WOs BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, 0 ready/approved ADR, releases UNDECIDED all, engine=false, NLE-D009 source license OPEN, no public MVP D013.


**NO ACTUAL QA-05 ENGINE, COMPILATION, TESTING, QUALIFIED HARDWARE, MAC BUNDLE, BROWSER DEPLOYMENT, MIGRATION FAULT INJECTION, INSTALLER, WARRANTY, SIGNATURE, SOAK OR RELEASE.** The 128 cases and benchmark protocol are intentions, not empirical results.

## 1. Source Check actually observed
- HEAD main exact **a42519c8a79346a4974fa74c44f7cac26f4ad43c**, zero open PRs, public repo, main protected=false/zero active rulesets, existing `.github/workflows/docs.yml` only Docs Validation (links/catalog/80-registry/Zcode selector). No QA-05 research files/ADR-0079 existed on baseline.
- GitHub registry 80 modules; QA-05 catalog **76 RESEARCH_PENDING**, **75/80 researched, 5 pending, ALL 80 future code WOs BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, executor_ready=0, approved_adr=0, release_class UNDECIDED all, engine_implemented=false**, NLE-D009 license OPEN and D013 no public MVP. [Research #357](https://github.com/KayzenRoot/stormline/issues/357) OPEN until audited checkpoint, [code #94](https://github.com/KayzenRoot/stormline/issues/94) OPEN/BLOCKED.
- Formal dependencies **EXACT QA-02 + PLAT-05**, prior [ADR-0076](../adr/0076-qa-02-deterministic-golden-regression-policy.md) and [ADR-0074](../adr/0074-plat-05-reproducible-export-release-policy.md) both PROPOSED, no actual native code or source licensed. QA-02 owns fixture/visual/audio oracles and PLAT-05 owns build/export/sign/distribution; QA-05 owns qualification evidence, other modules integration only.
- [WO Context Lock](../work-orders/NLE-P00-WO-002-QA-05.md) records Git blob SHA-1 object IDs, **NOT raw SHA256 of file bytes**; later executor must recalculate before any implementation.

## 2. Official 2026 research evidence and limitations
- [Microsoft WARP](https://learn.microsoft.com/en-us/windows/win32/direct3darticles/directx-warp): CPU software DirectX raster, no physical GPU proof. [Vulkan Profiles](https://docs.vulkan.org/guide/latest/vulkan_profiles.html): feature/profile conformance metadata not render/driver certification. Windows/D3D12 actual driver/features, Linux ABI/Mesa/ICD/Wayland/X11 and NVIDIA/AMD/Intel GPU cases are future.
- [Apple Metal MTLGPUFamily](https://developer.apple.com/documentation/metal/mtldevice/supportsfamily(_:)), [Xcode 27 release notes](https://developer.apple.com/documentation/Xcode-Release-Notes/xcode-27-release-notes), [Sept 2026 Rosetta](https://developer.apple.com/news/?id=w5ngl9k2): distinguish native arm64 on real Mac from conditional Intel x86_64 actual machine, universal2 only if approved, no Rosetta false support. No macOS hardware/notarization or signing tested.
- [WebGPU](https://www.w3.org/TR/webgpu/) optional per-browser adapter/feature set and secure context with privacy-bucketed limits, [MDN GPUAdapter](https://developer.mozilla.org/en-US/docs/Web/API/GPUAdapter/limits) browser limits not raw device GPU model, [Playwright snapshots](https://playwright.dev/docs/test-snapshots) OS/browser variation. No actual Chrome/Firefox/Safari WebGPU/WebGL2 test, Web release class pending.
- [Windows recovery](https://learn.microsoft.com/en-us/windows/win32/recovery/using-application-recovery-and-restart), [POSIX rename](https://pubs.opengroup.org/onlinepubs/9799919799/functions/rename.html): recovery callbacks/atomic visibility do not prove durable power-cut persistence. Future must test staged writes/file+directory sync, last-good checksum/backup, migration safe downgrade and clean rollback. No real backup/restores done.
- [GitHub Actions billing](https://docs.github.com/en/billing/concepts/product-billing/github-actions): standard hosted public compute free conditional, artifacts and paid devices not automatically free. No hardware purchase/service cost initiated, no release or installer rights ratified.
- Third-party OS/browser/graphics SDK/distribution notices/legal terms vary; NLE-D009 source license still OPEN, no rights to publish engine asserted.

## 3. Exactly EIGHT NEW research Markdown
1. [Architecture](../architecture/qa-05-compatibility-release-qualification.md).
2. [ADR-0079 PROPOSED](../adr/0079-qa-05-platform-compatibility-qualification-policy.md).
3. [Platform/hardware/tool/license/R$0 matrix](../research/qa-05-platform-hardware-tool-license-cost-matrix.md).
4. [Versioned qualification/recovery evidence API](../contracts/qa-05-qualification-evidence-api.md).
5. [Exactly 128 future acceptance tests Q05-T001..Q05-T128](../testing/qa-05-acceptance-matrix.md).
6. [Future compatibility/soak/recovery benchmark protocol](../research/qa-05-compatibility-soak-recovery-benchmark-protocol.md).
7. [Work Order](../work-orders/NLE-P00-WO-002-QA-05.md).
8. This Evidence Bundle.

## 4. What has and has not been proven
| Factual research scope | Missing actual evidence |
|---|---|
| main Git SHA/source hierarchy/regression ownership | no engine/executable/editor/game exports |
| native Windows/Linux/macOS desktop scope and candidate hardware matrices | no GPU/CPU/driver/browser physical qualification |
| WARP/SwiftShader software separate and WebGPU conditional | no actual D3D12/Vulkan/Metal/WebGPU runtime smoke test |
| QA-02 golden and PLAT-05 manifests and support contracts PROPOSED | no deterministic scene, real golden, signed export/install |
| recovery/soak tests, failure stages and transaction policy future | no save backup, actual crash, disk-full/migration rollback |
| copyright/license/cost/privacy and 128 future tests | no PASS, no product license, no release/Apple account |
| Docs Validation once PR run appears | **not compiled C++ or QA-05 runtime acceptance** |

## 5. Actual research PR, CI and audit PENDING until observed
Research branch `docs/NLE-P00-WO-002-QA-05-research`, BASE `a42519c8a79346a4974fa74c44f7cac26f4ad43c`. PR number/HEAD, exactly eight new files, exact-head Docs Validation run/job SUCCESS, pt-BR audit, squash/main readback to be logged **after** occurrence only. Risk LOW P00, native migration/graphics ELEVATED and privileged signing/real crash tests HIGH_ASSURANCE; no owner approval of hardware purchase.

## 6. Checkpoint Delta proposed only
After observed research CI/audit/squash/readback, independent **five MODIFIED** files checkpoint/backlog/registry JSON/WO/Evidence with **SOLE semantic QA-05 research_status `RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED`**, other 79 module objects and root unchanged. Expected **76/80 researched (95%), 4 pending, 80/80 coding WOs BLOCKED, 0 ready/approved_adr, releases UNDECIDED, engine=false**. Own CI/audit/squash/main readback BEFORE close research #357; code #94 OPEN/BLOCKED. Then **FOUR Markdown history** checkpoint/backlog/WO/Evidence own CI/audit/squash/main readback, next real **BIZ-01 Commercial Licensing & Compliance** ordinal 77/80 formal **QA-05 ONLY**, future coding [#95](https://github.com/KayzenRoot/stormline/issues/95) OPEN/BLOCKED.
