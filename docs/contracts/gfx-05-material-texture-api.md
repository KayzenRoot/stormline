# GFX-05 — Versioned Material / Texture Semantic Contracts (PROPOSED v0.1)

**WO:** NLE-P00-WO-002-GFX-05 | **Research issue:** #135 | **Code issue:** #33 BLOCKED.  
Conceptual interface proposal, **not** compiled C++ API, native GPU ABI, generated MCP server, stable wire schema or runnable renderer.

## Ownership and common schemas
**Reuse** GFX-02 `MaterialDefinitionV1`, `MaterialInstanceV1`, `ShaderReflectionV1`, `PipelineLayoutContractV1` and GFX-01 DeviceCapabilities. Store GFX-05 semantics as a versioned referenced subobject, not a second identity or material compiler. DATA-02 AssetId and revision are authoritative; DATA-05 cooked target artifacts are derived.

| Proposed logical type | Fields | Validation |
|---|---|---|
| `MaterialSurfaceProfileV1` | material_asset_id, revision, model PBR_METALLIC_ROUGHNESS / UNLIT / STYLIZED, supported_ext_set, double_sided, normal_profile, alpha_profile, energy_policy | finite values, invalid model/unsupported required ext rejected, no duplicate permanent ID |
| `PbrParametersV1` | base_color_linear, metallic, roughness, ior?, specular?, clearcoat?, sheen?, iridescence?, transmission?, emissive_linear, occlusion_strength | bounded authored physical domains, NaN/Inf rejected, extension-dependent parameters gated |
| `MaterialTextureBindingV1` | texture_asset_id/revision, usage role BASE_COLOR/NORMAL/ORM/EMISSIVE/OCCLUSION/HEIGHT/etc, UV set/transform, channel mapping, sampler id, expected alpha/color semantics | correct sRGB/linear mapping and channel contract, missing required texture explicit |
| `TextureSourceDescriptorV1` | texture_asset_id, source_import_receipt, width/height/depth/layers, ICC/color space/transfer, orientation, alpha convention, HDR/data-kind, rights | DATA-03 validated only; no hostile file or arbitrary URL |
| `TextureCookProfileV1` | immutable recipe id, target capabilities digest, KTX2/format candidate, quality goal, mip algorithm, alpha coverage, normal renormalization, encode/transcode versions | DATA-05 owns derived output, bounded work and exact versions before code |
| `CookedTextureManifestV1` | DATA-05 artifact id/digest, dimensions, levels/offsets/sizes, format, color-profile, required features, provenance, target-specific fallback chain | checked arithmetic/index, format and RHI feature validation, content digest is not publisher auth |
| `TextureSamplerProfileV1` | min/mag/mip filter, address modes, LOD range/bias, compare mode?, requested anisotropy | GFX-01 clamps supported anisotropy; data/comparison sampling compatibility |
| `MaterialQualityProfileV1` | render tier, allowed material features, shading-cost policy, max sampled textures, fallback map and diagnostics | feature tier strictly based on device snapshot, no guessed OS proxy |
| `AlphaAndDecalProfileV1` | OPAQUE/MASK/BLEND/TRANSMISSION, cutoff, blend equation, premultiply state, depth policy, sort key, decal overlap limit | alpha MASK foliage classification matches GFX-04; no invalid blending |
| `TextureResidencyRequestV1` | project+AssetId/revision, target artifact, desired min/max mip, priority, GPU generation, deadline/quotas, cancel token | bounded, authorized; DATA-05 and GFX-03 own scheduling and fences |
| `TextureResidencyReceiptV1` | request_id, verified chunk set, actual mip range, format, RHI generation, completion fence, bytes/quality metadata, fallback/typed failure | no activation before verified completion; stale generations rejected |
| `MaterialVariantPlanV1` | expected material rev, semantic/static feature set, GFX-02 ShaderVariantKey, reflection/layout signatures, requested targets | explicit variant budget and compile route; dynamic edits do not trigger static compile |
| `MaterialValidationReceiptV1` | material/texture revisions, checked feature/cook/usage contracts, fallback or losses, diagnostics, deterministic receipt digest | redacted semantic metadata; not real render evidence |

## State transitions
`IMPORTED_VALIDATED (DATA-03) -> COOK_PLANNED (DATA-05) -> COOKED_VERIFIED (DATA-05) -> UPLOAD_QUEUED (GFX-03) -> FENCE_COMPLETE (GFX-03) -> RESIDENT_ACTIVE (GFX-05 logical view)`. On cancel/error/evict/device-loss, pin last-good coarse mip or publish explicit `MISSING_TEXTURE` / `DEVICE_GENERATION_STALE` state. Never silently substitute stale handles. Reimport produces new revision and mismatch returns conflict, not overwrite.

## Semantic Editor/CLI/MCP commands
| Command | Permission / result |
|---|---|
| `InspectMaterial`, `InspectTextureProfile` | capability-scoped readonly IDs/parameters/rights summary, no raw image bytes or host path |
| `PreviewMaterialVariant`, `PreviewTextureCook` | readonly predicted features, bytes/quality estimates labeled estimates, unsupported-target warnings |
| `PreviewMaterialCost`, `GetMaterialValidation`, `GetResidencyReceipt` | readonly bounded metrics/redacted diagnoses, pagination/rate limits |
| `StageMaterialEdit` | write capability + expected revision + typed normalized params; workspace-local staged changes only |
| `ValidateMaterialEdit` | check schema, required extension, source rights, shader variant budget, affected dependents without publication |
| `CommitMaterialEdit` | explicitly authorized, compare-and-swap revision; durable DATA-01/02/04 policy and rollback/repair receipts |
| `CancelMaterialOperation` | scoped idempotent cancellation; no half-published GPU object |

No arbitrary shader string upload, host path read, URL fetch, OS command, direct GPU pointer, pipeline cache access, cross-project batch edit or unrestricted material export via MCP. No unsupervised rights bypass.

## Typed error taxonomy
`MATERIAL_INVALID`, `NON_FINITE_PARAMETER`, `UNSUPPORTED_REQUIRED_EXTENSION`, `SHADER_LAYOUT_MISMATCH`, `VARIANT_BUDGET_EXCEEDED`, `INVALID_COLOR_PROFILE`, `INVALID_NORMAL_CONVENTION`, `INVALID_ALPHA_MODE`, `TEXTURE_FORMAT_UNSUPPORTED`, `TEXTURE_MANIFEST_INVALID`, `DECOMPRESSION_LIMIT`, `RESIDENCY_BUDGET_EXCEEDED`, `MISSING_TEXTURE`, `UPLOAD_PENDING`, `DEVICE_GENERATION_STALE`, `SOURCE_REVISION_CONFLICT`, `UNTRUSTED_CONTENT`, `LICENSE_DENIED`, `CAPABILITY_DENIED`, `CANCELLED`, `RECOVERY_REQUIRED`. Errors carry safe stage/retryability, correlation ID and redacted diagnostic. Web unsupported features must be explicit.

## Evidence gates
GFX-02 reflection/variant test, DATA-03 importer/reimport validation, DATA-05 target codec/hash/rights receipt, GFX-01 format queries, GFX-03 GPU fence/device-loss, GFX-04 foliage classification, GFX-06 lighting ownership, GFX-07 tone-mapping boundary. All remain future tests until compiled and integrated.
