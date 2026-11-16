# BIZ-02 — Proposed SDK, Extension, ABI and Developer Evidence Contracts v0.1

**P00 SEMANTIC SCHEMA ONLY, NO IMPLEMENTED C/C++ HEADER, WIT, JS API, SDK OR BINARY.** NLE-P00-WO-002-BIZ-02, issue #366, base `0ee74d476b7c5ff09744b323cfde7423c06673b2`, formal GAME-02 + AI-01 only. Source engine license OPEN. Example names and fields below are conceptual, NOT a frozen publicly supported ABI.

## Core shared contracts and authority
| Proposed record (V1) | Fields / invariants | Owner of truth |
|---|---|---|
| `SdkCapabilityDescriptorV1` | namespace; stable api_id; major/minor/patch; schema_digest; required capabilities; supported OS/backend; lifecycle/thread phase; risk tier | BIZ-02 projection of owner descriptors, not second authority |
| `SdkTargetProfileV1` | platform/architecture/toolchain/compiler version, C runtime/linkage, libc/sysroot, WASI/browser capabilities, immutable engine/SDK build digest | BIZ-02 distribution; QA-05 verifies actual devices |
| `SdkVersionHandshakeV1` | sdk_schema_hash, engine_build, semver, abi_major, struct_size, feature required/optional, target host, requested imports, requested capabilities | both sides reject unknown mandatory bits/mismatch |
| `SdkNativeAbiDescriptorV1` | C entry function symbol, calling convention, fixed-layout types/align/size, function table length, allocator callbacks & ownership | BIZ-02 adapter only, after owner review |
| `SdkOpaqueHandleV1` | stable ID, owner/project/world generation, object kind, lease and expiry, no raw pointer | owning module/epoch |
| `SdkBufferViewV1` | pointer local to call, explicit length, encoding, lifetime, allocator tag, mutability, reserved constraints | host validates size and lifetime, no cross-CRT free |
| `SdkBindingSchemaV1` | canonical semantic types, enums/errors, nullable/array/UTF-8 rules, language generator version, source-map provenance | canonical owner descriptor projected from GAME-02/AI-01 |
| `SdkErrorV1` | stable code (see below), safe message, operation stage, retryable, expected/actual schema, severity and remediation | owner+CORE diagnostics; no secret paths |
| `PluginPackageManifestV1` | plugin id/namespace, publisher, package version, SHA256, source provenance/SPDX, target OS, SDK/ABI range, entrypoints, capability requests, package dependencies | BIZ-02 discovery; BIZ-01 legal clearance future |
| `PluginTrustDecisionV1` | trust tier, integrity/signature receipt, owner actor/role, exact allowed target, dynamic/native/outprocess/wasm mode, review date and expiry | host policy, no signature-based sandbox assertion |
| `PluginCapabilityGrantV1` | issuer/principal/project/workspace, module/plugin digest, scope/operations, target, expiry, quotas, revocation version | GAME-02 and AI-01 owning enforcement, no duplicate auth |
| `PluginInstanceV1` | unique instance + generation, project/world epoch, manifest revision, state/lease, threads/jobs outstanding, active grants and resource budget | BIZ-02 lifecycle view; no raw access |
| `PluginActivationPlanV1` | verified package hashes, required imports, host API feature match, permission grants, safe fence, state migration plan and rollback snapshot | owner controlled, no side-effect at discovery |
| `PluginExecutionReceiptV1` | instance and operation IDs, requested vs applied stage, grant decision, tick/owner snapshot, metrics, faults, trace and actual resource usage | GAME-02 host or AI-01 router owner |
| `PluginUpgradeReceiptV1` | prior/new artifact digests, ABI/schema compatibility, migration plan, staged/swap/restore state and checkpoint | owner storage/transaction/host, never fake rollback |
| `SdkSampleReceiptV1` | example original rights, schema and docs hash, target/compiler, deterministic expected behavior, test receipt/artifact hash | BIZ-02 sample pipeline, BIZ-01 rights |
| `SdkCompatibilityReportV1` | multi-target matrix, confidence/physical vs VM flag, ABI and semantic contract diff, deprecations and migration errors | BIZ-02 reports and QA-05 qualification |
| `SdkDocumentationReceiptV1` | generated docs version/target/hash, API symbol presence, link checks, i18n/a11y proof and stale checks | BIZ-02 docs source |
| `SdkRightsManifestV1` | package/SPDX per redistributable, exact component version/notice/asset and export channel rights | BIZ-01 legal gate, BIZ-02 consumes |

## Proposed operations and safety gates
| Operation | Privilege | Required output |
|---|---|---|
| `sdk.discoverCapabilities` | non-mutating, bounded | advertised public API descriptors only, no internal topology/secret |
| `sdk.queryCompatibility` | read-only | target+schema constraints, typed reason unsupported/conditional |
| `plugin.inspectManifest` | non-executing read, package size/time limits | parsed manifest, graph and rights/provenance gaps |
| `plugin.validate` | bounded stage, no world mutation | hash/license/capability/ABI feature results, no auto install |
| `plugin.requestGrant` | owner explicitly authorized | pending/denied/proposed grant, never self-approved by agent |
| `plugin.activate` | privileged owner at safe fence | active instance+lease+receipt or quarantined, no raw world access |
| `plugin.invokeGameplay` | GAME-02 script host with grants/tick budget | authorized typed command buffers and receipts |
| `plugin.invokeAuthoring` | AI-01 canonical kernel with expected revision and idempotency | same typed semantic receipt for Editor/CLI/future MCP |
| `plugin.disable` | owner gated | drains tasks/releases handles, marks restart-required if native unload unsafe |
| `plugin.upgrade.preview` | read + scoped staging | ABI, API, schema and migration compatibility; expected changes |
| `plugin.upgrade.commit` | high privilege, revision-locked | staged safe-fence atomic switch, rollback/readback or explicit RECOVERY_REQUIRED |
| `sdk.sample.verify` | non-mutating artifact build/test when authorized | rights-cleared original sample smoke proof, not dummy PASS |
| `sdk.package.inspect` | read-only | headers/import libs/docs/NOTICE + relocatability and digests |

## Failure taxonomy
`SDK_API_UNSUPPORTED`, `SDK_ABI_MAJOR_MISMATCH`, `SDK_STRUCT_SIZE_INVALID`, `SDK_SCHEMA_HASH_MISMATCH`, `SDK_TARGET_UNSUPPORTED`, `SDK_FEATURE_REQUIRED_UNKNOWN`, `SDK_HANDLE_STALE`, `SDK_BUFFER_OVERFLOW`, `SDK_ALLOCATOR_MISMATCH`, `SDK_PLUGIN_UNTRUSTED`, `SDK_NATIVE_SANDBOX_UNPROVEN`, `SDK_CAPABILITY_DENIED`, `SDK_GRANT_REVOKED`, `SDK_QUOTA_EXCEEDED`, `SDK_CALL_PHASE_INVALID`, `SDK_PACKAGE_RIGHTS_UNKNOWN`, `SDK_PACKAGE_TAMPERED`, `SDK_DEPENDENCY_AMBIGUOUS`, `SDK_UPGRADE_CONFLICT`, `SDK_MIGRATION_FAILED`, `SDK_UNLOAD_REQUIRES_RESTART`, `SDK_WEB_NATIVE_UNAVAILABLE`, `SDK_NOT_RELEASEABLE`.

Every error returns a safe redacted reason and stable type, never stack contents or private project data. Missing required extension features => reject, unknown *optional* forward fields preserved where schema allows. No implicit fallthrough to unsafe raw C++ ABI.

## Lifecycle and data ownership examples (hypothetical, not run)
1. Example `plugin.inspectManifest` detects ARM64-only native DLL requested on Web: `SDK_WEB_NATIVE_UNAVAILABLE`; no install/side effects.
2. A compatible trusted Windows DLL has a manifest but request lacks owner grant: `SDK_CAPABILITY_DENIED`; signature does not grant sandbox restrictions.
3. A plugin sends an authoring command via UI and CLI: both project the **same AI-01 `CommandInvocationV1`** and return semantically equivalent `CommandReceiptV1` under identical revision/grant. MCP adapter is future, not a separate privilege.
4. A script plugin requests direct read/write `WorldSnapshot`: GAME-02 `ScriptHostCallV1` validates existing grant and emits only bounded buffered owner commits, not pointer access.
5. Upgrade fails state-migration check: old plugin remains active/disabled safely, old source project unchanged; result `SDK_MIGRATION_FAILED` with proposed restore receipt, not fictitious automatic rollback.

## Contract restrictions
- No public binding/header is currently shipped and no NLE-D009 rights grant made. ABI versions and SemVer labels are *proposed* not registered release numbers.
- Versioned `Sdk*V1` types are conceptual; consistency with actual GAME-02 and AI-01 final schemas must be tested and approved before Zcode.
- All host operations require ownership by authoritative module, immutable input snapshots, typed scope, cancellation and quota. No process/file/network APIs unless explicitly granted by future owner and OS sandbox with evidence.
- Cleanly separate headless, Editor and Web target availability; neither Linux GitHub docs CI nor wasm compile would establish actual macOS/Windows/Web runtime compatibility.

[Architecture](../architecture/biz-02-sdk-plugin-developer-experience.md) · [research matrix](../research/biz-02-sdk-plugin-technology-security-license-matrix.md) · [128 future tests](../testing/biz-02-acceptance-matrix.md).
