# DATA-05 — Semantic Cooking, Bundle, Streaming and Patching Contracts

**WO:** NLE-P00-WO-002-DATA-05 | **Research:** #120 | **Code:** #28 BLOCKED.
This is a **proposed semantic design** only, not a runnable API, generated schema, signed artifact, C++ ABI, MCP server or final wire format.

## Versioned logical entities

| Type | Proposed mandatory fields / meaning | Validation and failure behavior |
|---|---|---|
| `TargetProfileV1` | id/version; OS/arch/ABI/runtime, feature flags, texture/audio/mesh/shader capabilities, quality/performance tier and safe fallbacks | unsupported required feature rejects; never infer GPU capability from OS only |
| `CookRequestV1` | project_id, source graph revision, authorized asset/scene roots, target profile, recipe id+version, operation_id, resource budget, expected source revision | only DATA-01 scoped input, stable AssetId, no host paths, source revisions immutable during cook |
| `CookPlanV1` | input snapshot, resolved deps, cook DAG, chosen codec profiles, estimated output bytes, warnings, skipped/unsupported features, dry-run digest | preview-only and bounded; no writes or arbitrary plugins |
| `CookArtifactV1` | AssetId + source revision + subasset key + target variant, typed media contract, loader min version, codec/encoder metadata and logical digest | original AssetId preserved, no silent quality loss |
| `CookReceiptV1` | operation ID, input/dependency/recipe/toolchain hashes, profile, output manifest digest, reproducibility class, timing, errors and generated artifacts | retry idempotency and audit; output hash must match produced bytes |
| `BundleManifestV1` | schema + generation + base release refs, target profile, required loader/features, canonicalization_version, digest algorithm, roots/chunks/asset mappings, resource limits, trust_policy | bad digest, unsigned remote distribution, unknown required schema fails closed |
| `ChunkDescriptorV1` | bundle id, bounded offset/length/alignment, stored digest/encoded bytes, decoded length, codec/dictionary version, optional decoded digest and priority group | checked addition/offset ranges, no overlap unless valid, decompression limits and dictionary trust |
| `BundleVerifyReportV1` | trust status separately from byte integrity, target capability, checked chunks, schema/codec errors, warnings, last-good generation | `DIGEST_VALID` is NOT `TRUSTED_PUBLISHER`; ambiguous state fail closed for remote activation |
| `StreamRequestV1` | generation id, AssetId variant, consumer id, priority/deadline, cancellation, IO/RAM/CPU and expected GPU residency hint | bounded queues, no quota bypass; limited retries and no leak |
| `StreamReceiptV1` | requested/verified/cpu-ready/device-ready amounts, cache provenance, status, latency and discarded prefetch | no false GPU-ready claim before consumer acknowledges upload |
| `PatchPlanV1` | verified base/target generation, manifest trust, old/new/reused chunk set, patch method, estimated bytes and budget, rollback constraints | reject incompatible/downgrade/unsigned new version; no mutation in preview |
| `PatchReceiptV1` | idempotency key, installed manifest digest, prior-good generation, verified chunk count, journal/ref, staged/commit state | COMMITTED only after content readback/reconcile, recovery idempotent |
| `BundleErrorV1` | stable code, stage, context ids (sanitized), retryable, severity and optional recovery requirement | never leak absolute paths, tokens, prompts or binary data |

## Proposed loader and index semantics
- `AssetLocator`: `{asset_id, source_revision, subasset_key?, target_profile_id, cook_variant_id}` resolves via trusted `BundleManifestV1` to typed chunks. AssetId is **not** hash/path or runtime handle.
- Immutable `generation_id` refers to one consistent manifest + dependency/codec snapshot. A cache hit must verify expected digest, version and trust before reuse. Multi-generation read operations pin the generation to avoid concurrent update races.
- Loader version negotiation checks bundle schema, codec version, dictionary integrity, target feature flags and instance-specific GPU compatibility; incompatible path returns error and suggested fallback, **not** silently wrong format.
- Chunk offsets use integer checked arithmetic, validated totals and independent compressed/uncompressed-size caps; `decompress` does not trust serialized length alone.
- `content_digest` identifies bytes but does not prove who published them. Remote distribution trust/anti-rollback is a separately approved PLAT-05 signed manifest policy; this research provisions no keys.
- Explicit primary/secondary groups: BOOTSTRAP_REQUIRED, SCENE_VISIBLE, NEXT_REGION, BACKGROUND_OPTIONAL. Fair queue and startup deadlines never override hard resource limits.
- Cached bytes and warm chunks are untrusted until verified for the currently pinned generation; partial transfer is never marked READY.

## Editor / CLI / MCP parity

| Semantic command | Capability | Effect and limits |
|---|---|---|
| `cook.inspect_capabilities` | `project.cook.read` | list available profiles/features and unsupported formats; no mutation |
| `cook.plan` | `project.cook.read` | resolve immutable snapshot and predicted costs, no file writes |
| `cook.preview` | `project.cook.propose` | generate warnings/diff/fidelity estimates; still no committed changes |
| `cook.execute` | `project.cook.write` + validated approval | stage artifacts and verify; no network/shell/plugin execution |
| `bundle.inspect` | `project.bundle.read` | bounded chunk/index/asset list with redaction and pagination |
| `bundle.verify` | `project.bundle.read` | check digest/schema/compatibility; publisher-trust status separately |
| `bundle.stream_diagnostics` | `project.bundle.read` | bounded staging, latency/cap counters without private content |
| `patch.plan` | `project.patch.read` | compare generations, base/new trust, estimated download |
| `patch.preview` | `project.patch.propose` | dry-run staging/recovery constraints |
| `patch.commit` | `project.patch.install` + explicit release permission | stage, verify and activate; deny unsigned remote target |
| `patch.recover` | `project.patch.recover` privileged | replay journal or rollback verified prior generation; audit receipt |

Every mutation request includes project capability and actor context, expected generation/source revision, stable operation id, bounded options and expiry/cancel policy. An LLM **cannot** supply arbitrary OS path, network URL, signing key, executable script, vendor compiler flags, SQL statement or upload endpoint. All operations share one authorization + validation kernel with Editor and CLI. Preview is not authorization to commit.

## Cook, stream and patch state machines
```text
COOK: INSPECTED -> PLANNED -> PREVIEWED -> STAGING -> VERIFYING -> DERIVED_COMMITTED
          -> error BEFORE_VISIBLE / RECOVERY_REQUIRED after intent
STREAM: MISSING -> FETCH -> STORED_UNVERIFIED -> VERIFIED -> DECODE -> CPU_READY
          -> CONSUMER_UPLOAD -> CONSUMER_READY
PATCH: BASE_VERIFIED -> PLAN -> PREVIEW -> FETCH_REUSE -> STAGED -> VERIFIED
          -> INTENT_RECORDED -> ACTIVATED -> RECONCILED -> COMMITTED
          -> RECOVERY_REQUIRED on post-intent failure
```
Only `COMMITTED`/ `CONSUMER_READY` states may be reported success. Retries with the same operation ID return the same committed receipt or bounded recovery status, not a second independent mutation.

## Typed errors
`INVALID_TARGET_PROFILE`, `SOURCE_REVISION_STALE`, `RECIPE_UNSUPPORTED`, `SOURCE_RIGHTS_BLOCKED`, `MISSING_DEPENDENCY`, `COOK_NONDETERMINISTIC`, `QUALITY_LOSS_UNAPPROVED`, `CODEC_NOT_SUPPORTED`, `LOADER_VERSION_UNSUPPORTED`, `SCHEMA_UNSUPPORTED`, `MANIFEST_UNTRUSTED`, `SIGNATURE_INVALID`, `STALE_GENERATION`, `DOWNGRADE_DISALLOWED`, `HASH_MISMATCH`, `CHUNK_RANGE_OVERFLOW`, `CHUNK_OVERLAP_INVALID`, `DECOMPRESSION_LIMIT`, `NETWORK_RANGE_UNAVAILABLE`, `RESOURCE_LIMIT`, `CAPABILITY_DENIED`, `QUOTA_EXCEEDED`, `DISK_FULL`, `PATCH_CONFLICT`, `CANCELLED`, `STAGE_FAILED`, `COMMIT_FAILED`, `RECOVERY_REQUIRED`, `UNKNOWN`.

Error responses must be typed, bounded, sanitized, correlated with build/operation IDs and identify whether retry/restore is safe. Fake signature success from hash-only verification is a protocol violation.

## Contract freeze gates for future executable #28
Pin exact recipe and codec versions; choose manifest format/validator/canonicalization; specify storage and crypto trust requirements, public API/CLI/MCP binding security, exact future C++/source paths and expected CI commands, real test vectors and risk budgets. Predecessors implemented and APPROVED; fresh base/fingerprint, no HIGH/CRITICAL. Current documentation does **not** authorize software work.
