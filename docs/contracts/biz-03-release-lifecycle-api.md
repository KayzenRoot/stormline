# BIZ-03 — Versioned Release, Installation, Update, Rollback and Support Semantic Contracts v0.1

**P00 PROPOSED LOGICAL RECORDS, NO REAL API, BINARY, SIGNATURE, INSTALLER, RELEASE, SDK OR DEPLOYMENT.** Research #370, coding #97 BLOCKED, source `3d2ad393ab4b70460e7d5cb46f82e03d2f5c9935`; formal PLAT-05 + BIZ-01 + QA-04 ONLY. NLE-D009 license OPEN, no public MVP.

## Contract inventory and ownership
| Conceptual V1 record | Required fields and rejection invariants | Authority |
|---|---|---|
| `ReleaseIntentV1` | intentId, owner/project/build digest, candidate channel, target OS/arch, source HEAD, expected immutable revision, owner role/capability, dry-run | BIZ-03 routes, owner approval mandatory |
| `ReleasePayloadRefV1` | PLAT-05 export receipt ID, unsigned and signed digest distinct, size, toolchain/profile, signed OS package identity | PLAT-05 immutable export owner; BIZ-03 consumes, cannot rewrite |
| `ReleaseVersionV1` | product SemVer + build metadata, API/ABI major, project/save schema compatibility ranges, target min OS/CPU/GPU/browser flags | BIZ-03 compatibility; no false semver to downgrade data |
| `ReleaseSecurityGateV1` | QA-04 signed evidence identities, severity, coverage/fuzz/SBOM/provenance versions, exact artifact hash, risk exception approval | QA-04 owns security verification; BIZ-03 fails closed |
| `ReleaseRightsGateV1` | BIZ-01 approved engine grant, SPDX notices, creator assets, SDK/runtime redistribution, publisher/trademark consent, privacy obligations | BIZ-01 owns rights, no implicit open-source |
| `ReleaseArtifactManifestV1` | releaseId, platform/profile, hash/byte size, OS package id, SBOM/provenance reference, minimum version and support window, launch entry | PLAT-05 proof + BIZ-03 distribution view |
| `ReleaseChannelRevisionV1` | channel, strictly increasing revision, signed timestamp+root version, immutable artifact digest target matrix, cohort, expiry, owner approval | BIZ-03 signed channel, not writable latest URL |
| `UpdateTrustRootV1` | offline root version, algorithms, threshold, trusted public keys, delegation and rotation policy, verification receipts | security owner-approved policy, no embedded private keys |
| `UpdateMetadataEnvelopeV1` | root/timestamp/snapshot/targets role versions+expiry, signatures+threshold, target path/hash+length, channel, target spec | BIZ-03 future TUF client; reject unsigned/expired/rollback |
| `UpdateCheckReceiptV1` | current+candidate versions, auth signature checks, timestamp freshness, channel/grant, platform, download bytes, eligible/denied reason | BIZ-03 no mutation until verified |
| `UpdateDownloadPlanV1` | immutable source+destination digest/size, temp space, chunk hash, resume offsets, full payload fallback, allowed hosts | BIZ-03 staging only; no arbitrary URL/path |
| `UpdateInstallJournalV1` | transactionId, application/owner, root and install path, stage, prior-good digest, payload digest, synced metadata fences, reboot status | BIZ-03 transaction, platform installer owner final commit |
| `UpdateTransactionReceiptV1` | operationId, actual states, before/after release+signed digest, health check, started/completed/recovery status, no user data claims | BIZ-03 installation observer |
| `RollbackAuthorizationV1` | actor, accepted older artifact digest, new channel revision, security version floor, data schema compatibility, expiry | owner security gate; no forced unsigned downgrade |
| `RollbackReceiptV1` | old/new app revision, intact last-known-good hash, project schema state, restore mode, interrupted/partial/corrupt flags | BIZ-03; project data owner separate |
| `ProjectMigrationPlanV1` | DATA-04 source project ID+CAS revision, schema from/to, preview/diff, backup target rights/quota, irreversible flag | DATA-04/project owner, BIZ-03 cannot rewrite |
| `ProjectMigrationReceiptV1` | backup digest, committed project revision+semantic digest, abort/restore/warnings and confirmation/consent | DATA-04 owner, BIZ-03 only correlates |
| `SaveCompatibilityReceiptV1` | game save schema/source game revision, game engine runtime ABI, target export version, read-only fallback | game/save schema owner not installer |
| `InstallTargetProfileV1` | Windows/Linux/macOS/Web target, OS min and cpu flags, GPU/driver tier, disk permissions, signer channel, architecture | PLAT & QA-05 qualification, BIZ-03 constraints |
| `UninstallPlanV1` | package owner, app data owned vs user assets/projects, preserve default, explicit consent and backup readback | BIZ-03 no silent deletion of creator data |
| `CrashReportConsentV1` | OFF default, purpose-scoped opt-in, data categories, expiry, retention/delete/export/withdraw status, region | BIZ-01 privacy/legal, BIZ-03 local UI |
| `CrashDiagnosticReceiptV1` | opt-in token reference, sanitized crash signature, no project content, client version/channel/target and deletion receipt | BIZ-03 support, local first |
| `ReleaseIncidentV1` | severity, impacted signed digests/cohorts, revocation/feed pause, CVE/advisory proof, rollback plan, communication/retention | owner/security release incident |
| `ReleaseSupportPolicyV1` | active/legacy support windows, EOL, security escalation, offline repair, channel release notes, evidence contacts | BIZ-03 product plan, not real SLA |

## State machines and precise errors
- Release: `DRAFT -> CANDIDATE -> QUALIFYING -> RIGHTS_SECURITY_APPROVED -> OWNER_APPROVED -> STAGED -> GA -> DEPRECATED -> RETIRED`; any unsafe/revoked condition => `BLOCKED`. No real product occupies these stages.
- Update install: `CHECK -> VERIFIED_FEED -> FETCHING -> STAGED -> VERIFIED_PAYLOAD -> APPLYING -> BOOT_HEALTH -> COMMITTED`. Interruptions to `ABORTED/REPAIR_REQUIRED/ROLLBACK_STAGED`. Do not claim binary rollback also rolls back source project/save.
- Migration: `INSPECT -> PREVIEW -> BACKUP -> STAGE -> VERIFY -> CAS_COMMIT -> READBACK`; failed commit must yield local backup and typed recovery; irreversible migration must require explicit consent and compatibility.
- Errors: `REL_LICENSE_OPEN`, `REL_RELEASE_CLASS_UNDECIDED`, `REL_NOT_QUALIFIED`, `REL_SIGNATURE_INVALID`, `REL_NOTARIZATION_MISSING`, `REL_TRUST_ROOT_UNKNOWN`, `REL_METADATA_EXPIRED`, `REL_METADATA_ROLLBACK`, `REL_WRONG_TARGET`, `REL_HASH_MISMATCH`, `REL_DELTA_BASE_MISMATCH`, `REL_CHANNEL_BLOCKED`, `REL_SECURITY_HIGH_CRITICAL`, `REL_INSUFFICIENT_DISK`, `REL_PERMISSION_DENIED`, `REL_JOURNAL_RECOVERY_REQUIRED`, `REL_MIGRATION_INCOMPATIBLE`, `REL_USER_DATA_UNSAFE`, `REL_CONSENT_REQUIRED`, `REL_PRIVACY_REDACTION_FAILED`, `REL_REDIS_PERMISSIONS_UNKNOWN`, `REL_BUILD_PROVENANCE_UNVERIFIED`, `REL_SDK_ABI_INCOMPATIBLE`.

## Golden adversarial examples (FUTURE, not executed)
1. A valid HTTPS URL presents an older unsigned feed: fail `REL_METADATA_ROLLBACK`, even if payload hash matches HTTPS-provided value.
2. Release signed for Windows x64 attempts macOS ARM64 update: `REL_WRONG_TARGET`; no writes.
3. New app version boots but requires irreversible project migration: first preview+backup+explicit creator consent; refusing consent preserves old project and app fallback only when compatible.
4. Mac binary has a SHA256 digest but lacks appropriate Developer ID signing/notary authorization: reject public channel `REL_NOTARIZATION_MISSING`.
5. Existing installed game is removed: default uninstaller deletes only owned package files, not creator save data.
6. User declines crash report: no network request/upload or hidden persistent identifier, no report sent.
7. Docs-only CI returns SUCCESS: cannot produce `ReleaseSecurityGateV1 APPROVED` nor valid signed `ReleaseChannelRevisionV1`.

## No code authorization
All records are conceptual and must reconcile actual PLAT-05 `ExportRequestV1`/`StagedPayloadManifestV1`, QA-04 `SecSbomReceiptV1` and BIZ-01 rights gate, without additional formal dependencies. Future authoring CLI/MCP integration cannot bypass user rights, passwords, OS signing or install confirmations. No open/public release for Stormline before full DoD/legal approvals.

[Architecture](../architecture/biz-03-release-installer-lifecycle.md) · [policy ADR](../adr/0082-biz-03-release-update-trust-policy.md) · [acceptance plan](../testing/biz-03-acceptance-matrix.md).
