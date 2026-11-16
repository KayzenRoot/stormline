# NLE-P00-WO-002-QA-05 — Compatibility & Release Qualification: Research Work Order

**2026-11-16 | P00 DOCUMENTARY RESEARCH ONLY | [research issue #357](https://github.com/KayzenRoot/stormline/issues/357) OPEN until independent checkpoint readback | future code [#94](https://github.com/KayzenRoot/stormline/issues/94) OPEN/BLOCKED | BASE main `a42519c8a79346a4974fa74c44f7cac26f4ad43c`.** QA-05 order 76/80, **FORMAL DEPENDENCIES EXACT QA-02 + PLAT-05**, predecessor ADR-0076/0074 both PROPOSED. Baseline 75/80 researched, 5 pending, all 80 implementation WOs BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, 0 ready/approved ADR, releases UNDECIDED all, engine=false, NLE-D009 source license OPEN, no public MVP D013.


**Risk LOW documentary.** Future multidevice native/graphics/data migration STANDARD/ELEVATED; actual privileged OS signing, destructive recovery/power tests, private user data/money/HIGH_CRITICAL security HIGH_ASSURANCE with owner authorization. No real game execution or release proof.

## OBJECTIVE
Research and architect evidence-backed, reproducible Windows/Linux/macOS/Web compatibility and release qualification for Editor and game exports: hardware/OS/driver/GPU API feature matrices (Vulkan/D3D12/Metal/WebGPU, CPU iGPU and discrete Intel/AMD/NVIDIA/Apple), physically tested vs headless/software VM, portable C++ runtime/ABI and clean package/install, original QA-02 deterministic scene/audio/input/golden tests, soak/stress/thermal and crash device loss, transactional save/project recovery, backward compatibility and safe migration/downgrade/rollback, rights/licensing, a11y, p50/p95/p99 QA-03 integration, security/risks, R$0 constraints and owner release support gates. Propose ADR-0079 and 128 FUTURE cases, **NOT actual hardware qualification**.

## CONTEXT & SOURCE CHECK
Authority order checkpoint > Decisions Ledger/approved ADRs > Scope > DoD > Architecture > Requirements > rest. Requested main SHA `a42519c8a79346a4974fa74c44f7cac26f4ad43c` matched, zero open PR, public repo main protected=false and zero rulesets; only `.github/workflows/docs.yml` Docs Validation, no executable QA-05/C++ engine or approved release. Registry: 80 modules, QA-05 ordinal **76** RESEARCH_PENDING, 75/80 research documented, 5 pending, **80/80 code WOs BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS**, 0 ready, 0 approved ADR, all release_class UNDECIDED, engine_implemented=false. NLE-D009 source license OPEN, D013 no public MVP until full 1.0 DoD, D014 original 2D/2.5D/3D/Web, D017 required native desktop Windows/Linux/macOS Editor and exported games, Web planned but release minimums owner-open, D018 autonomous safe docs only R$0, D019/020 80 future coding packets blocked. **Exactly FORMAL QA-02 + PLAT-05**, ADR-0076/0074 PROPOSED, semantic contracts proposed not implemented. CORE/GFX/PLAT OS/DATA/QA-01/03/04/BIZ integration/transitive only, no extra catalog DAG dependency. Coding [#94](https://github.com/KayzenRoot/stormline/issues/94) OPEN/BLOCKED, next real [BIZ-01](https://github.com/KayzenRoot/stormline/issues/95) ordinal 77/80 formal QA-05 only.

## CONTEXT LOCK
Base commit `a42519c8a79346a4974fa74c44f7cac26f4ad43c`. **Observed Git blob SHA-1 object identifiers, NOT SHA-256 digests of raw file bytes**. Future executor must compute raw SHA-256 and abort STALE on critical checkpoint, ledger/approved ADR, Scope, DoD, architecture, requirements, catalog, registry, QA-02/PLAT-05 semantic contract changes.
- `AGENTS.md`: `3e57b719f8651407879ebb641707a048773ea4c2`
- `docs/00-source-hierarchy.md`: `58a377bc76cafdd3377d733d4f30ef53661bb034`
- `docs/11-checkpoint.md`: `bb749089cceaf1ba23c1788f217184c6c0272d8c`
- `docs/10-decisions-ledger.md`: `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`
- `docs/03-scope.md`: `4ef605c74632ece080b2650e37dd83a415b63310`
- `docs/09-definition-of-done.md`: `160b3054db9ea1961308934b401488b838d24c3e`
- `docs/04-architecture.md`: `df62574cb3956c3ac9881631a4cf66be4e1abff1`
- `docs/02-requirements.md`: `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`
- `docs/product/module-catalog.md`: `18d69bca439831d65982cb0f8acbca1dbaa2eee9`
- `docs/queue/implementation-registry.json`: `289eed7200fc8189c2fab463316515f00c312529`
- `docs/queue/work-orders/QA-05.md`: `c74cec213ecac21436b3b5d3a00319d1ccee49af`
- `.github/workflows/docs.yml`: `cbbaf5731de75f1de4bdf8cad6489e6d73681d71`
- `docs/adr/0076-qa-02-deterministic-golden-regression-policy.md`: `3b26fb16204369b015d2c4b66aaa37c7592cb57f`
- `docs/adr/0074-plat-05-reproducible-export-release-policy.md`: `b9ad6bbfc9cd4434d83167f03c73e50307aedfea`
- `docs/contracts/qa-02-test-fixture-evidence-api.md`: `0ca60bab3a5474339e2ab977ac6a0ca57754804c`
- `docs/contracts/plat-05-export-release-api.md`: `764713955d50ca963db76ffc9a7281aba9bb6259`

## SCOPE — NECESSARY, EXACTLY EIGHT NEW Markdown
1. [Architecture](../architecture/qa-05-compatibility-release-qualification.md).
2. [ADR-0079 PROPOSED](../adr/0079-qa-05-platform-compatibility-qualification-policy.md).
3. [2026 platform/hardware/backend/license/R$0 matrix](../research/qa-05-platform-hardware-tool-license-cost-matrix.md).
4. [Typed semantic platform qualification/recovery API](../contracts/qa-05-qualification-evidence-api.md).
5. [Exactly 128 unique FUTURE Q05-T001..Q05-T128](../testing/qa-05-acceptance-matrix.md).
6. [Future soak, stress, migration and rollback benchmark](../research/qa-05-compatibility-soak-recovery-benchmark-protocol.md).
7. This Work Order.
8. [Evidence Bundle](../evidence/NLE-P00-WO-002-QA-05.md).
Initial research PR **only 8 ADDED .md**, no modification to existing Source Pack/checkpoint/backlog/registry, no C++/CMake/CI workflow/release/SDK. Separate independent checkpoint and historical closeout PRs later.

## OUT OF SCOPE
No actual engine binary/Editor/export/installer, Windows/Linux/macOS/Web browser runtime or physical hardware tests, no collected crash logs, performance p99, GPU profiling, SDK install, original image or audio fixture, migrator, user project copy, real power fault injection, public beta/MVP, code signing/notarization account, hardware purchase/cloud subscription/App Store, license approval, mandatory mobile release, GitHub ruleset/admin or branch changes, cleanup or rewrites of existing approved ADRs. No real test claims.

## FILES/SOURCES TO READ
All Context Lock sources, prior [QA-02 ADR](../adr/0076-qa-02-deterministic-golden-regression-policy.md)+[API](../contracts/qa-02-test-fixture-evidence-api.md) and [PLAT-05 ADR](../adr/0074-plat-05-reproducible-export-release-policy.md)+[API](../contracts/plat-05-export-release-api.md), blocked implementation issues #94 and #95. External authoritative 2026: [Microsoft WARP](https://learn.microsoft.com/en-us/windows/win32/direct3darticles/directx-warp), [Vulkan Profiles](https://docs.vulkan.org/guide/latest/vulkan_profiles.html), [Apple supportsFamily](https://developer.apple.com/documentation/metal/mtldevice/supportsfamily(_:)), [Apple Xcode 27](https://developer.apple.com/documentation/Xcode-Release-Notes/xcode-27-release-notes), [Apple Rosetta news](https://developer.apple.com/news/?id=w5ngl9k2), [WebGPU spec](https://www.w3.org/TR/webgpu/), [MDN adapter limits](https://developer.mozilla.org/en-US/docs/Web/API/GPUAdapter/limits), [Playwright screenshots](https://playwright.dev/docs/test-snapshots), [Windows recovery](https://learn.microsoft.com/en-us/windows/win32/recovery/using-application-recovery-and-restart), [GitHub billing](https://docs.github.com/en/billing/concepts/product-billing/github-actions), [POSIX rename](https://pubs.opengroup.org/onlinepubs/9799919799/functions/rename.html). Verify exact latest versions/licenses before activating code.

## REQUIREMENTS
Catalog acceptance **"Cenários de compatibilidade e recuperação aprovados por plataforma."** Native desktop Windows/Linux/macOS Editor and game exports owner-required, Web planned but future approved release class, no mandatory mobile until owner; no blanket physical GPU coverage from host VM/software, require actual QA-02 original scene and PLAT-05 artifact evidence before claiming support; v1.0 full DoD, minimum requirements and source license owner approval. R$0 public hosted standard compute with artifact storage and GPU fleet cost controls.

## ARCHITECTURE RULES
1. Exactly QA-02+PLAT-05 predecessors; QA-05 is acceptance/evidence authority, not image-golden editor/compiler/packager/runtime renderer, preserve native owner boundaries.
2. Capability probes D3D12 feature-level/adapter/driver; Vulkan profiles+ICD/queue/swapchain; Metal supportsFamily and ARM/Intel native distinction; WebGPU secure feature/limit/privacy bucket and WebGL2 fallback only if owner approved. Windows WARP/SwiftShader/llvmpipe Xvfb CPU-software cannot be counted as physical GPU.
3. Clean-room Windows/Linux/macOS build/installer/ABI runtime, user paths/permissions/locale/fonts/audio/keyboard/gamepad/a11y, verified signed/notarization only when owner. OS minima/driver/hardware requirements remain UNDECIDED, Web browsers independent class.
4. QA-02 deterministic original fixtures with source rights and golden state, 2D/2.5D/3D/Web input/audio/visual, cold/warm asset/shader, game and Editor separate. No untested unknown tier silently PASS.
5. Fault injection actual vs simulated clearly typed, soak/stress and GPU device loss, disk full, suspension, power/reboot *only on approved disposable hardware*; independent last-good backup checksum and migration transaction, safe downgrade denied if irreversible, avoid blanket atomic rename = power durable claim.
6. Release qualification L0..L6 actual layers, QA-03 perf integration optional but owner thresholds not adopted, QA-04 security/DoD future; no HIGH/CRITICAL, no corrupted project release. Support matrix explicit missing OS/GPU/driver/browser, neither green Docs Validation nor CTest on software alone is platform-qualified.
7. Private user data dumps redacted/opt-in, no unauthorized real telemetry or copyrighted assets; source licenses and third-party notices/installer rights unresolved until owner. R$0 service constraint, no hardware cloud purchase.
8. Typed `QualTargetCellV1`, `QualSourceLockV1`, `QualHardwareProfileV1`, `QualGpuCapabilityV1`, `QualInstallManifestV1`, `QualFixtureRunV1`, `QualRecoveryReceiptV1`, `QualMigrationEdgeV1`, `QualPlatformVerdictV1`; only proposals with fail-closed NOT_QUALIFIED status and no external SDK handles.

## CONSTRAINTS
Only P00 documentation, no new real checks/CI beyond already running Docs Validation, no credentials/paying for devices/SaaS, branch protection/ruleset unchanged, no force push/historical rewriting, no HIGH/CRITICAL known defect, no unapproved new release target or license. Context STALE blocks future executor.

## ACCEPTANCE CRITERIA
- [ ] Exactly **EIGHT ADDED .md**, ADR-0079 `PROPOSED`, no modified registry/CI/checkpoint/backlog in research PR, source hierarchy and links valid.
- [ ] Deep accurate sources 2026 Windows/Linux/macOS/Web, physical Intel AMD NVIDIA Apple GPU and D3D12/Vulkan/Metal/WebGPU, Windows ARM/Linux ARM/Intel Mac conditional, no Rosetta or software WARP false qualification, clean runtime/ABI/export, 2D/2.5D/3D and Web, browser version/adapter privacy, long soak, crash+data backup/migration/rollback, CI R$0, security/licenses/a11y.
- [ ] Exactly 128 unique sequential Q05-T001..Q05-T128 in 8 groups×16, all FUTURE/NOT EXECUTED, no fabricated PASS or numerical benchmark.
- [ ] Research PR own exact HEAD Docs Validation SUCCESS, objective pt-BR audit APPROVED, normal squash and main readback.
- [ ] Independent checkpoint PR exactly **FIVE MODIFIED** files checkpoint/backlog/registry JSON/this WO/Evidence; **SOLE semantic JSON QA-05 research_status RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED** other 79/root unchanged, **76/80 researched (95%), 4 pending, ALL 80 coding WOs BLOCKED, executor_ready=0, approved_adr=0, releases UNDECIDED, engine=false**; own CI/audit/squash/readback, close research #357 ONLY AFTER checkpoint.
- [ ] Final factual **FOUR Markdown-only historical PR** checkpoint/backlog/WO/Evidence with own exact-head Docs CI/audit pt-BR/squash/main readback and next REAL BIZ-01 Commercial Licensing & Compliance ordinal 77/80 formal QA-05 only, future coding #95 BLOCKED.

## TESTS
P00 actual GitHub Doc Validation (source pack/local links, module catalog DAG, 80 registry, blocked selector) and exact changed files/status, 128 Q05 ID uniqueness, sole registry semantic delta, issue states, PR CI run/job and main readback. **NO actual C++/hardware/render/soak/recovery/clean export or installer tests.** Tests in docs are FUTURE/NOT_EXECUTED; current code WOs blocked.

## DELIVERABLES
Research issue #357 and exactly eight Markdown, audited research PR CI/squash/main readback, independent audited five-file checkpoint then close research #357, independent factual four-Markdown historical PR with own CI/audit/squash/readback and next-module button. Coding #94 OPEN/BLOCKED.

## REVIEW FORMAT
Objective pt-BR **APPROVED / CORRECTION REQUIRED / BLOCKED**, actual base/head and Git blob OIDs vs raw SHA256 future, file changed status, exact QA-02+PLAT-05 DAG, future 128 tests and no PASS, actual Docs CI/run/job, source rights/OS API claims, physical-vs-software distinction, clean room/migration/data security, cost, known HIGH/CRITICAL, truthful checkpoint delta and readback. Independent audit not an external human reviewer requirement.

## STOP CONDITION
STALE checkpoint/ADR/Scope/DoD, incorrect 8/128, wrong formal deps, generated fake binary/device/measurements, CI failure, unapproved paid/cloud or hardware reset, privacy/security HIGH/CRITICAL or license right gap, source proof mismatch => CORRECTION REQUIRED same WO/PR if safe or BLOCKED. Do not advance BIZ-01 while current research/checkpoint/history gate incomplete; never unlock 80 code WOs.

## CHECKPOINT DELTA PROPOSAL ONLY
After audited research PR CI/squash/main readback, independent exactly five-file PR with only QA-05 research_status update, 76/80 researched, 4 pending, all 80 code WOs BLOCKED. Own CI/audit/squash/readback THEN close research #357, coding #94 OPEN/BLOCKED. Separate four-Markdown historical closing PR own gates then BIZ-01 formal QA-05 only.
