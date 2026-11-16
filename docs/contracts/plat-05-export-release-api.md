# PLAT-05 — Versioned Export, Package, Supply-Chain and Distribution Semantic Contracts v0.1

**2026-11-15 | DOCUMENTARY RESEARCH ONLY | [research #337](https://github.com/KayzenRoot/stormline/issues/337) | NLE-P00-WO-002-PLAT-05 | future coding [#89](https://github.com/KayzenRoot/stormline/issues/89) OPEN/BLOCKED | baseline `d1369e8101ea86e2a14a4a12e9581fb8df4fa478`.** Formal catalog prerequisites **PLAT-01 + PLAT-02 + PLAT-03 + PLAT-06 + DATA-05 EXACT**; prior ADR-0069/0070/0071/0072/0013 PROPOSED. 70/80 research documented before this module, 10 pending, 80/80 code WOs BLOCKED, approved ADR=0, ready=0, release classes UNDECIDED, engine_implemented=false, NLE-D009 source license OPEN.


**Logical future API only. No C++ class/IDL/CI workflow/binary, signing transaction, software artifact or live release generated.** External OS/SDK/driver structures must not escape as raw types; callers require authorized versioned operations with immutable receipts.

## Formal contract owners (exact five)
| Formal edge | Proposed source semantic contract | PLAT-05 consumes, never duplicates |
|---|---|---|
| **PLAT-01** | [Windows target](plat-01-windows-target-api.md), ADR-0069 | PE x64/arm64 architecture candidate, Win runtime/presentation requirements, MSIX/EXE/MSI manifest and signing capabilities |
| **PLAT-02** | [Linux target](plat-02-linux-target-api.md), ADR-0070 | ELF/GLIBC/Wayland/X11 runtime and Flatpak/AppImage/portable archive support and portals |
| **PLAT-03** | [Browser target](plat-03-browser-target-api.md), ADR-0071 | Emscripten Wasm/JS/worker and WebGPU/WebGL2 capability, MIME/COOP-COEP/CSP, content-origin caching |
| **PLAT-06** | [macOS target](plat-06-macos-target-api.md), ADR-0072 | Apple Silicon native and Intel conditional, per-slice Mach-O, Developer ID/notary/App Store differences |
| **DATA-05** | [Cook/bundle](data-05-cook-bundle-api.md), ADR-0013 | validated `TargetProfileV1`, `CookReceiptV1`, `BundleManifestV1`, `ChunkDescriptorV1`, `PatchReceiptV1` and snapshot hashes |

CORE-01 build, QA-01 CI execution and QA-04 security audit, BIZ-03 installer/publish/rollback, mobile PLAT-04, AI capability, EDIT/DATA-02 source, GFX/GAME runtime and NET/CDN are transitive/integration owners, **not formal edges**.

## Typed logical contract inventory
| Contract | Proposed mandatory fields | Owner, invariants and fail-closed result |
|---|---|---|
| `ExportRequestV1` | projectId, owner authorization scope, expected immutable source revision, target profile id/version, export mode INTERNAL_SMOKE/RELEASE_CANDIDATE, quality tier, operationId | reject stale snapshot, unknown target/release class and untrusted instructions before running any command |
| `ExportTemplateRefV1` | templateID/revision/hash, allowed source path/globs, approved stage layout, launch entry, plugin caps, nested dependency policy | signed/allowlisted template only; no arbitrary CMake snippet or shell injection |
| `ToolchainLockV1` | compiler/linker/SDK/sysroot/NDK if approved versions and SHA, CMake preset/config, arch triple, SOURCE_DATE_EPOCH, env allowlist, container image digest | exact host vs target; no mutable latest/download w/o pin |
| `TargetPackageProfileV1` | PLAT target owner id, architecture, OS version floor, GPU/browser capability tier, package format, project assets profile, release class, distribution channel, owner decision revision | reject unsupported OS/ABI/browser/FeatureTier; mobile blocked unless separately authorized |
| `ExportBuildPlanV1` | source/cook snapshot hashes, toolchain/template locks, task DAG, resource/time budget, tool invocation tokenized (not shell), sandbox/permissions flags | typed plan, deterministic ordering, no ambient root/credentials/network |
| `CookInputReceiptV1` | DATA-05 target and bundle generation, immutable manifest/chunk digests/length/codec, asset provenance and validation status | DATA-05 owns cooking; reject mutable or missing dependency/rights |
| `BuildJobReceiptV1` | source/toolchain/head fingerprints, builder identity, job run/attempt, OS/arch, stdout/stderr redaction, exit codes, selected target, duration and status | immutable record, never auto PASS from docs job |
| `StagedPayloadManifestV1` | stage version, ordered virtual files/path/permissions/length/sha256/entrypoint, cooked asset generation/ABI deps, symbol bundle, source notices and SBOM ref | path canonicalization/symlink/case collision bounded; unsigned staging read-only after seal |
| `BuildReproducibilityReceiptV1` | first/second independent builder source/toolchain/template/cook hashes, normalized unsigned payload hashes, equality/diffoscope summary, excluded nondeterminism | bytewise "REPRODUCIBLE" only if observed; signed package compared by signature+payload not same bytes |
| `PackageArtifactV1` | target platform/arch, type MSIX/EXE/MSI/Flatpak/AppImage/TAR/MAC_APP/DMG/WEB_ASSETS or conditional MOBILE, unsigned payload hash, final artifact hash, SBOM/provenance ids, symbols | package format must match signed/installed target; no mobile approval implicit |
| `SupplyChainSbomV1` | schema SPDX3/CycloneDX1.7, package relationships, transitive system/native/JS/Wasm/asset/fonts deps, license IDs/NOTICE and provenance, hash | reject unresolved required redistribution right, no engine license auto selection |
| `SlsaAttestationV1` | in-toto v1 Statement, predicateType `https://slsa.dev/provenance/v1`, subject SHA256, builder/ref/buildDefinition/resolved deps, signature identity and verification policy | no SLSA level claim unless specific requirements/build platform independently met |
| `SigningRequirementV1` | platform/channel, publisher identity fingerprint, certificate type/root, hardened/entitlements, timestamp/notary/Store flag, owner approval and permitted cost | no signing without explicit owner-approved credentials; private key never in receipt |
| `SignedArtifactReceiptV1` | pre-sign payload hash, final distribution hash, signer certificate public fingerprint/chain, timestamp, notary ticket/Gatekeeper or MSIX trust, verification tool result | failed/no signer => release candidate BLOCKED; notarization != App Review |
| `BrowserReleaseManifestV1` | HTTPS origin, app shell/wasm/js/workers/assets hashes, MIME/compression and isolation policy, preload graph, ServiceWorker scope/cache generation and fallback id | same origin and closed asset graph; no mixed executable generations across SW updates |
| `DistributionCandidateV1` | channel INTERNAL/CANARY/BETA/STABLE, immutable artifact+manifest, OS/arch target, version monotonicity, security approvals, rollback pointer, DoD gate | BIZ-03 owns actual publishing, PLAT-05 may only handoff verified candidate |
| `UpdateAndRollbackPlanV1` | current/next immutable generation, signing/authorization/anti-replay, asset dependency closure, download budget, staging fs, checksum, journal, rollback security exception | no cross-device atomicity false promise, no overwrite running binary/project |
| `TargetExportErrorV1` | code SOURCE_STALE/TARGET_UNSUPPORTED/TOOLCHAIN_MISSING/LICENSE_UNCLEAR/COOK_MISMATCH/ABI_MISMATCH/REPRO_DIVERGENCE/SIGNING_REQUIRED/HASH_FAILED/STORE_BLOCKED/ROLLBACK_UNSAFE, stage/owner/retry/recovery | typed and redacted; preserve last-good/reject side effects |
| `ReleaseEvidenceReceiptV1` | approved version DoD, actual build binaries/host installation/browser smoke, diff/CI/security/SBOM/signature checks, actual release authorization, pending policy risks | no "DONE" from planning docs or ad hoc unsigned smoke; owners sign their gates |

## Logical operations (not implemented)
| Operation | Allowed owner | Precondition and result |
|---|---|---|
| `request_export(request, expected_rev)` | PLAT-05 authorized export service | immutable SourceSnapshot or SOURCE_STALE |
| `resolve_target_package_profile(id)` | PLAT-05 + five owners | runtime OS/arch/feature/format profile, mobile only owner-ratified |
| `bind_toolchain_and_template(profile)` | PLAT-05 + CORE/QA integration | ToolchainLock/ExportTemplateRef, digest-validated |
| `consume_cooked_generation(receipt)` | DATA-05 -> PLAT-05 | verified immutable BundleManifest/ChunkDescriptors |
| `plan_export_dag(inputs)` | PLAT-05 | bounded ExportBuildPlanV1 with explicit allowed operations |
| `run_sandboxed_export(plan)` | future executor under QA-01 | BuildJobReceipt, no trusted creds |
| `stage_and_seal_payload(job, cook)` | PLAT-05 | StagedPayloadManifest+SHA256/NOTICE after asset scan |
| `compare_independent_unsigned_builds(a,b)` | QA-01/PLAT-05 | BuildReproducibilityReceipt; mismatches explicitly fail |
| `generate_sbom_and_provenance(artifact)` | QA-04/PLAT-05 | SBOM and in-toto/SLSA attestation only if builder actually ran |
| `request_platform_signing(candidate, owner_auth)` | PLAT-05/BIZ-03 controlled signer | signed receipt or SIGNING_REQUIRED, separate hash |
| `verify_platform_signature(artifact)` | independent verifier | public trust chain / notarization / Store status, no private key |
| `prepare_release_candidate(artifact, rights, risk)` | PLAT-05 | immutable DistributionCandidateV1 for BIZ-03, never publishes |
| `publish_release(candidate, approval)` | **BIZ-03 only** | release channel transition after owner gate |
| `plan_update_or_rollback(active,next)` | **BIZ-03 only**, DATA-05 for asset patches | journal/checksum/anti-replay policy with rollback exception |
| `read_export_evidence(id)` | owner/QA | final hashes/actual tests/CI and clear missing proofs, no secrets |

## Cross-platform invariant checks
- Platform binary/container/asset must be versioned and individually hashed: **source != cook != unsigned payload != signed artifact != release channel**. Never mix a two-phase sign transform with deterministic pre-sign build or reuse unsigned hash as final signed digest. Actual SLSA trusted attestation binds its subject to the **precise artifact hash**; additional signed stage needs its own provenance/link.
- Path/Unicode/case sensitivity: reject collisions on Windows case-insensitive targets, macOS filesystem variants and Linux case-sensitive paths; no `../`, ADS/reparse, symlink/hardlink escape, zip-slip or unapproved system root. Stage under clean workspace and revalidate after filesystem operations, safe file bytes/limits.
- No OS platform library with wrong ABI/tier. Native target OS/hardware/CI smoke proof distinct; cross compilation alone is insufficient. No compiled engine presently.
- Web bundle executable JS/WASM cannot be downloaded from untrusted project-controlled URL or combined with stale Service Worker cache; browser features/headers verified at approved origin. Partial assets never advance active release.
- Refuse unauthorized public channel, paid signing, unlicensed content, unapproved source license, HIGH/CRITICAL, missing DoD. AI/MCP never silently signs/releases/deletes. Mobile target unapproved -> TARGET_UNSUPPORTED.
- Never expose full project home path, private signing keys, AI text/credentials, internal SBOM restricted packages to untrusted release; sanitize diagnostics and use owner-approved privacy channel.
- Version incompatible contract -> hard-fail and keep existing last-good; rollback security vulnerable version requires signed audited override. BIZ-03 installation and repair not performed in PLAT-05 research.

[Architecture](../architecture/plat-05-build-export-distribution.md) · [128 future tests](../testing/plat-05-acceptance-matrix.md) · [ADR](../adr/0074-plat-05-reproducible-export-release-policy.md).
