# QA-05 — Platform Qualification, Recovery and Release Evidence Semantic Contracts v0.1

**2026-11-16 | P00 DOCUMENTARY RESEARCH | [research #357](https://github.com/KayzenRoot/stormline/issues/357) | NLE-P00-WO-002-QA-05 | future coding [#94](https://github.com/KayzenRoot/stormline/issues/94) OPEN/BLOCKED | base `a42519c8a79346a4974fa74c44f7cac26f4ad43c`.** QA-05 ordinal 76/80; formal dependencies **QA-02 + PLAT-05 ONLY**, predecessor ADR-0076/0074 PROPOSED. Initial 75/80 researched, 5 pending, 80 code WOs BLOCKED, 0 ready/approved ADR, all release classes UNDECIDED, engine_implemented=false.


**Logical design only**: no C++ API/IDL, actual OS/GPU/browser instance, signed executable, installer, tested disk image, runtime test, support policy or CI workflow. Never expose raw D3D12/Vulkan/Metal/browser handles in public Stormline API.

## Only TWO formal prior owners
| Formal | Existing PROPOSED contract | QA-05 responsibility |
|---|---|---|
| **QA-02** | [semantic fixture API](qa-02-test-fixture-evidence-api.md), [ADR-0076](../adr/0076-qa-02-deterministic-golden-regression-policy.md) | consume pinned originals, deterministic replay, visual/audio/semantic goldens, keyboard/a11y and failure traces; never silently modify baseline |
| **PLAT-05** | [export release contract](plat-05-export-release-api.md), [ADR-0074](../adr/0074-plat-05-reproducible-export-release-policy.md) | consume immutable source/artifact/package digest, C++ ABI/toolchain and OS bundle/dependency/signing/rollback plan; never implement compiler or sign distribution |

Other GFX/CORE/GAME/DATA/QA-01/03/04/PLAT and BIZ are transitive or integration only, no new DAG edges.

## Candidate logical types and invariants
| Type | Required fields | Invariant/reject |
|---|---|---|
| `QualTargetCellV1` | qualification ID, product role Editor/Game/Headless, OS family/version/patch, arch/ABI, GPU API+physical/software, required vs planned status, release class owner decision | owner undecided cannot label mandatory support matrix fully qualified |
| `QualSourceLockV1` | Git base/head and critical Source Pack hashes, QA-02 fixture/golden SHA+approval, PLAT-05 manifest/build/export/toolchain+asset SHA | mismatch => STALE before tests, no false attested build |
| `QualHardwareProfileV1` | CPU arch/model/cores/RAM, GPU vendor/device/driver/OS API, physical/VM/CPU software flag, discrete/unified VRAM, OS kernel/libc/DPI/display/audio/input | hardware absence or generic “GPU capable” => NEEDS_HOST |
| `QualGpuCapabilityV1` | D3D12 adapter+feature level/SM, Vulkan API/profile/extension/queue/swapchain, Metal MTLGPUFamily and supported formats, WebGPU features/limits/browser privacy buckets | feature not actually queried => UNKNOWN; unsupported => UNSUPPORTED |
| `QualInstallManifestV1` | PLAT-05 artifact checksums/signature/notarization status, packaging format, OS min, ABI/runtime dependencies, permissions, installation user/path | invalid identity/runtime dep => PACKAGE_INVALID |
| `QualFixtureRunV1` | QA-02 original FixtureId/SceneRevision/source rights, input trace+seed/tick, screenshot/audio/ARIA expectations, actual device receipt and CI/hardware host | no screenshot-only semantic substitute, wrong source or software backend => mismatched |
| `QualCoverageMatrixV1` | target cells+requiredness and owner, actual executed/skip/unsupported status, hardware/device availability, baseline provenance, gaps and explicit exclusions | missing required device cannot be PASS; percentage cannot hide critical gap |
| `QualSustainedSessionV1` | real hardware ID class (redacted), source+artifact SHA, timed warmup/soak phases, restarts/crashes, heap/VRAM trend, frame pacing/IO, temp if permitted, logs and durations | Docs CI cannot produce real 24h soak claim; invalid session => INCONCLUSIVE |
| `QualFaultInjectionV1` | fault type crash/kill/OOM/disk-full/GPU device-loss/abrupt power/browser suspension/network, injected vs observed source, attack surface, phase/tick and authorized sandbox | simulated GPU loss distinct from actual driver reset, irreversible test needs owner |
| `QualProjectStateV1` | project/save ID+schema, last-good hash+backup location/ACL, staged temp write/journal/transaction version, commit point and validation, storage FS semantics | never overwrite good data with corrupted partial save; no universal atomic rename guarantee |
| `QualMigrationEdgeV1` | from/to data format/schema, migrator digest, reversible flag, pre-migration backup, idempotency key, tests and failed transition code | downgrade nonreversible => explicit DENIED + safe restore, no lossy silent downgrade |
| `QualRecoveryReceiptV1` | fault ID, final process+install version, recognized last-good snapshot, replayed changes with checksums, result recovery time and user-visible data retained/lost | no recovered data claim without readback and compare exact bytes/semantic state |
| `QualBrowserReceiptV1` | browser/vendor/version, OS, HTTPS origin/security isolation, WebGPU adapter limits+features, WebGL2 if approved, tab resume/storage quota/cache migration, network offline | browser optional features and privacy-bucketed GPU metrics not assumed real VRAM |
| `QualRuntimeDependencyReceiptV1` | binary architecture/ABI, imports/linked .so/.dll/.dylib versions, shader/device SDK, bundled OSS license/NOTICE, runtime/permissions probe, missing dependencies | no “clean install PASS” on development machine only |
| `QualReleaseCandidateV1` | immutable PLAT-05 artifact subject SHA, build manifest, tested platform cells, security status, license, support/rollback manifest, release channel and owner, signature/notarization verified | never treat code signing as granted; no public version 1.0 until full DoD |
| `QualPlatformVerdictV1` | target cell, actual evidence bundle and layers L0-L6, status PASS/FAIL/INCONCLUSIVE/UNSUPPORTED/NOT_QUALIFIED/BLOCKED, risk and owner review, expiry/source SHA | required layers missing => NOT_QUALIFIED, no conditional mobile implied mandatory |
| `QualErrorV1` | SOURCE_STALE, NO_PHYSICAL_GPU, GPU_CAP_UNSUPPORTED, BROWSER_FEATURE_UNKNOWN, PACKAGE_INVALID, MISSING_RUNTIME, RECOVERY_FAILED, DATA_CORRUPTION, DOWNGRADE_UNSAFE, CRASH_DUMP_PRIVACY, CI_NOT_RUNTIME, COST_GUARD, TARGET_UNAPPROVED, NOT_QUALIFIED | typed fail closed, no fake tests |

## Future operations, no implementations
| Proposed operation | Owner and future evidence |
|---|---|
| `lock_qual_source_and_references` | QA-05 verifies QA-02 approved fixture and PLAT-05 signed/artifact manifest + Git hashes |
| `enumerate_qual_target_matrix` | QA-05 owner classification required/planned, releases undecided cannot be self-ratified |
| `probe_qual_device_capabilities` | GFX/PLAT runtime integration real physical hardware, response includes software/virtual flag |
| `validate_qual_clean_install` | QA-05 through PLAT-05 actual artifact, isolated clean OS/ABI/driver/dependency path |
| `run_qual_scene_and_playback` | QA-02 owner golden and gameplay fixtures against actual device |
| `run_qual_soak_and_faults` | QA-05 bounded real host; QA-03 integration performance metrics but no extra formal dep |
| `verify_qual_crash_project_recovery` | GAME/DATA owner transaction and QA-05 independent last-good checksum readback |
| `verify_qual_migration_downgrade` | DATA/PLAT-05 artifact versioning and safe backup/restore on clean test project |
| `verify_qual_browser_resume` | Web deployment PLAT owner with optional WebGPU feature probe, viewport/input/DB quotas |
| `evaluate_qual_release_gate` | QA-05 synthesis only, actual PLAT-05 subject, QA-02 green and security/license owner gates |
| `emit_qual_evidence_bundle` | QA-05 redacted actual artifacts/logs/host and tests, no invented hardware |
| `approve_public_release` | BIZ-03/owner only after full 1.0 DoD, not QA-05 P00 |

## Stop conditions
- No system declaration `PASS` from documentation, successful compilation alone, virtual raster GPU or absent screen-reader/physical host, unknown browser features/driver, missing package signature or untested data migration. Safety HIGH/CRITICAL / privacy and corrupted backup block release.
- The 128 tests in [matrix](../testing/qa-05-acceptance-matrix.md) FUTURE/NOT_EXECUTED. R$0 conditional public compute, no paid hardware/device farm. All 80 coding WOs still BLOCKED; ADR-0079 PROPOSED.

[Architecture](../architecture/qa-05-compatibility-release-qualification.md) · [ADR-0079](../adr/0079-qa-05-platform-compatibility-qualification-policy.md) · [benchmark](../research/qa-05-compatibility-soak-recovery-benchmark-protocol.md).
