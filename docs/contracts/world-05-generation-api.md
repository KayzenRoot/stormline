# WORLD-05 — Typed Generator Recipe, Graph, Determinism and Regeneration API v0.1

**Research #171 | NLE-P00-WO-002-WORLD-05 | Future coding #45 OPEN/BLOCKED.** Semantic proposed types, **not** compiled C++ ABI, actual graph interpreter, editor, WebGPU kernel, serializer or active MCP service.

| Proposed type | Fields and role | Exact invariant / owner |
|---|---|---|
| \`MasterSeed128V1\` | author input 128 bits and display encoding, never treated as a secret | reproducible entropy key, explicit endianness and 128-bit serialization |
| \`SeedDerivationV1\` | project/world/GraphGuid/NodeGuid, output domain, CellId/PatchId, sample coords/counter, algorithm version | no global state, stable ordering and integer overflow policy |
| \`DeterminismProfileV1\` | canonical CPU, numeric fixed/quantized format, float flag rules, compiler/toolchain, rounding, algorithm revision | \`BIT_EXACT_VERIFIED\` only from actual golden tests; GPU preview otherwise NON_CANONICAL |
| \`GenerationGraphAssetV1\` | GraphAssetId/GraphRevision, NodeGuid and typed edges/ports/asset links, project roles | acyclic graph, stable IDs, no arbitrary script node |
| \`GenerationNodeV1\` | AlgorithmId+Version, params/units/port TypeId, allowed domain, cost and dependency manifest | known schema, range and rights checks, bounded iteration |
| \`GenerationPortV1\` | port semantic \`ScalarField\`/\`Mask\`/\`HeightDelta\`/\`BiomeWeights\`/\`PointSet\`/\`TileRules\`/\`MeshRecipe\`/\`InstancePlacement\`, units and resolution | explicit adapter for cross-unit/coordinate/resolution |
| \`GenerationRegionV1\` | WorldId/OriginEpoch, globally signed CellId/PatchId, sample grid, halo, region solver extent and expected revision | negative coordinates checked, overlap stable across stream order |
| \`GeneratorRecipeV1\` | MasterSeed128, pinned graph/algorithm/data schema/asset/input versions, numeric/coordinate profile and canonical byte encoding | same entire pinned recipe+scope = same canonical bytes, no seed-only claim |
| \`GraphDependencyManifestV1\` | immutable node and AssetId source hash chain, region footprint and output tags | DATA-02 rights and DATA-05 content-addressed cache owner |
| \`GeneratorPreviewV1\` | immutable proposed source diffs, estimated count/CPU/memory, visual-only proxy and provenance | does not update DATA-04 scene/source or WORLD-01 entities |
| \`GeneratedArtifactProposalV1\` | source recipe hash, schema+type, stable generated ID, payload byte hash, provenance and affected IDs | no direct asset DB/scene writer, hash against canonical output bytes |
| \`GeneratedPlacementIdV1\` | graph/node/channel/source region and stable global candidate key | dedup and no collision; never iteration ordinal alone |
| \`GenerationEvaluationReceiptV1\` | graph/version, seed derivation version, source hashes, region, exact output hash, status and frame/cost measurements | status VERIFIED/NOT_VERIFIED/NON_CANONICAL_PREVIEW, never fake verified |
| \`GenerationFailureV1\` | typed graph/constraint/limit/cancellation failure, source hash, retries and redacted diagnostics | deterministic bounded failure and no partial publish |
| \`GeneratedBaseRebaseV1\` | old generated base, new generated base, DATA-04 manual overlay and per-field/instance orphan conflicts | manual edit and suppressions preserved, three-way decision with permissions |
| \`GenerationEditTransactionV1\` | owner/project/scene/graph expected source CAS, staged change, limits, affected cells/assets | DATA-04 journaling, generation cannot commit unilaterally |
| \`GenerationPublishReceiptV1\` | source committed revision, DATA-05 cooked hash, WORLD-03 loaded staged revision, PHYS/GFX ACKs and last-good state | source commit != live runtime publish, separate acknowledgements |

## Typed graph execution (FUTURE; no actual interpreter)
\`Inspect/LoadRecipe -> ValidateGraphDAG/PortTypes/Units/SourceRights/AlgorithmPins -> CanonicalizeInputs -> DeriveIndependentNode/RegionCounterStreams -> EvaluateCpuReference(nodes stable order, bounded pure effects) -> CanonicalSerialize+HashOutputs -> PreviewGeneratedBaseVsManualOverlay -> DATA04 CAS-commit (only after explicit authorized intent) -> DATA05 cook -> WORLD03 stage and WORLD04/PHYS/GFX accept -> Publish coherent source/runtime receipts\`. All exceptions/cancellation before commit retain source; crash post source commit uses journal+outbox and version-gated idempotent publish, not pretend disk+GPU+PHYS atomic.

A graph output claiming deterministic equality MUST compare source hash with actual identical golden vectors across approved builds/platforms. Same seed but different GraphVersion/AlgorithmId/SourceAsset/hash/numeric profile is **a different recipe**. Unsupported platform numerical profile returns \`NOT_CANONICAL_SUPPORTED\`, may allow visual-only preview but not authored source.

## Editor / CLI / MCP parity (proposed)
Readonly \`InspectGenerationGraph\`, \`GetGeneratorRecipe\`, \`PreviewGenerationRegion\`, \`CompareGeneratorVersions\`, \`InspectGeneratedProvenance\`, \`InspectGeneratedArtifacts\`, \`PreviewGenerationRebase\`, \`GetGenerationQualityReceipt\`. Mutations \`StageGenerationGraphEdit\`, \`StageGenerationRecipeEdit\`, \`StageAcceptGeneratedProposal\`, \`StageResolveManualOverlayConflict\`, \`ValidateGenerationTransaction\`, \`CommitGenerationTransaction\`, \`UndoGenerationTransaction\`, \`RedoGenerationTransaction\`, \`CancelGenerationRequest\`. All ProjectId/AssetId/world/scene/source-CAS and role+quota; preview never commits, no arbitrary files/remote endpoints/script execution or NET/PHYS privileged world authority.

## Typed errors
\`GEN_GRAPH_CYCLE\`, \`GEN_NODE_TYPE_UNKNOWN\`, \`GEN_PORT_TYPE_MISMATCH\`, \`GEN_UNITS_INCOMPATIBLE\`, \`GEN_GRAPH_SIZE_LIMIT\`, \`GEN_ITERATION_BUDGET_EXCEEDED\`, \`GEN_MEMORY_BUDGET_EXCEEDED\`, \`GEN_OUTPUT_COUNT_LIMIT\`, \`GEN_SOURCE_ASSET_RIGHTS_DENIED\`, \`GEN_SOURCE_HASH_MISMATCH\`, \`GEN_SEED_FORMAT_INVALID\`, \`GEN_SEED_DERIVATION_VERSION_UNKNOWN\`, \`GEN_ALGORITHM_UNSUPPORTED\`, \`GEN_NUMERIC_PROFILE_UNSUPPORTED\`, \`GEN_FLOAT_NAN_NONFINITE\`, \`GEN_COORD_OVERFLOW\`, \`GEN_REGION_HALO_INSUFFICIENT\`, \`GEN_DETERMINISM_NOT_VERIFIED\`, \`GEN_GPU_NON_CANONICAL_PREVIEW\`, \`GEN_CONSTRAINT_CONTRADICTION\`, \`GEN_CONSTRAINT_NO_SOLUTION_WITHIN_BUDGET\`, \`GEN_GENERATED_ID_COLLISION\`, \`GEN_MANUAL_OVERLAY_ORPHAN_CONFLICT\`, \`GEN_MANUAL_OVERRIDE_PRESERVED\`, \`GEN_STALE_CELL_EPOCH\`, \`GEN_STALE_RECIPE_REVISION\`, \`GEN_STALE_ASYNC_REQUEST\`, \`GEN_CACHE_PROVENANCE_MISMATCH\`, \`GEN_DATA04_CAS_CONFLICT\`, \`GEN_UNAUTHORIZED_APPLY\`, \`GEN_PREVIEW_CAPABILITY_DENIED\`, \`GEN_UNTRUSTED_SCRIPT_FORBIDDEN\`, \`GEN_CANCELLED\`, \`GEN_PUBLISH_OWNER_ACK_PENDING\`, \`GEN_RECOVERY_REQUIRED\`. Safe structured errors include scope/version/trace hash and retryable flag, not secret assets/host paths/byte pointers.

## Future implementation freeze conditions
Owner-approved Scope and 1.0 DoD/ADR-0030 and output formats, real merged WORLD-04+DATA-03 dependencies, DATA-04/05, CORE numeric and job, exact compiler target+raw file SHA-256 Context Lock, third-party pinned license/SBOM, golden CPU vectors and manual editing/crash recovery/security tests. **None achieved now.**

## Official research references (not installed, selected or executed)
- FastNoiseLite cross-platform noise library upstream, MIT license: https://github.com/Auburn/FastNoiseLite/blob/master/LICENSE
- Godot stable FastNoiseLite behavior and variable output range: https://docs.godotengine.org/en/stable/classes/class_fastnoiselite.html
- OpenSimplex2 README and mixed CC0 / Unlicense file notice: https://github.com/KdotJPG/OpenSimplex2/blob/master/README.md
- OpenSimplex2 per-file LICENSE and source: https://github.com/KdotJPG/OpenSimplex2/blob/master/LICENSE
- WaveFunctionCollapse MIT code license, examples/assets separately credited: https://github.com/mxgmn/WaveFunctionCollapse/blob/master/LICENSE
- WaveFunctionCollapse original README: constraint contradictions and NP-hardness note: https://github.com/mxgmn/WaveFunctionCollapse/blob/master/README.md
- Unreal Engine 5.8 PCG graph framework, proprietary engine reference: https://dev.epicgames.com/documentation/unreal-engine/procedural-content-generation-overview-for-unreal-engine?lang=pt-BR
- SideFX Houdini PDG node dependency concepts and proprietary licenses: https://www.sidefx.com/products/houdini/pdg/ and https://www.sidefx.com/Support/licensing/
- Random123 official counter-based RNG source, BSD-style license candidate subject to pinned review: https://github.com/DEShawResearch/random123
