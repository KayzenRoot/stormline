# GAME-05 — Versioned Genre Pack, Sample Fixture and Project Creation Semantic Contracts v0.1

**Research issue #224 | WO NLE-P00-WO-002-GAME-05 | Future code #61 BLOCKED. NOT C++ headers, binaries, wire schema, MCP server or tested API.** Any name suffixed V1 is a conceptual design requiring downstream approval.

## 1. Authored types and contracts
| Proposed type | Fields / meaning | Must be validated / ownership |
|---|---|---|
| `GenrePackIdV1` | stable project+namespace-scoped ID, semantic version, source AssetId/revision | DATA-02 resolves identity; no path-only IDs / C++ RTTI |
| `GameProjectBlueprintV1` | BlueprintId, revision, name/locale defaults, platform/quality/a11y profile, root scene, license inventory, game mode intent | GAME-05 semantic source, DATA-04 CAS and rights |
| `GenrePackManifestV1` | PackId/version/hash, required/optional dependencies, exported FeatureId/schema, declared target capabilities, compatibility range, rights/attribution, max budgets | cycle-free resolved dependency DAG, no automatic remote fetch/exec |
| `GenreFeaturePackV1` | FeatureId, references to scripts/rules/abilities/scenes/animation/audio/input/UI, typed overrides and exported extension ports | authoring composition only, GAME-04/SIM-04/AUD-04 retain behavioral authority |
| `GenreRecipeV1` | ordered FeaturePack refs and pinned revisions, overlay rules, independent game seed, supported target modes, test fixture bindings | deterministic canonical composition, no implicit last-writer-wins |
| `GenreOverrideV1` | {PackId, ResourceId, FieldId}, expected source revision, operation, typed value/tombstone, original provenance | DATA-04 source transaction and validated schema; reject unknown required fields |
| `GenreDependencyResolutionV1` | closure/DAG, exact resolved IDs/revisions/hashes, target compatibility, conflict report | fail on missing/cyclic/incompatible licenses/versions |
| `GameGenreCapabilityV1` | rendering 2D/2.5D/3D, platform, native/Web/headless, physics/nav/net/audio/UI, critical/optional, reason | actual feature report must come from owning subsystem; UNKNOWN is not READY |
| `GenreCompositionPlanV1` | resolved pack graph, staged file/asset count/size, role/rights, semantic diff, estimated cost, source fingerprints | plan is read-only and never file write; quotas applied before commit |
| `GenreStageReceiptV1` | stage ID, expected project and source revisions, typed conflicts, rights/target deficits, recoverability | STAGED is not persisted/exported/playable |
| `GenreCommitReceiptV1` | source CAS commit ID, revision, DATA-04 journal, created/updated AssetIds, partial/recovery condition | source commit not equivalent to loaded scene or compiled build |
| `GenreSampleFixtureV1` | sample ID, genre, original authored seed/assets, scenario script, acceptance IDs, provenance | only future tested fixture assets; no copied commercial game content |
| `GenreExportPlanV1` | target OS/arch, build toolchain preset, capability matrix, manifest/cooked content digests, expected receipts | PLAT/QA/DATA-05 own build and target pack; no unknown becomes success |
| `GenreExportReceiptV1` | COMPILED/COOKED/EXPORTED/FAILED stages, binary hash, toolchain/OS/arch, link to test evidence | approved export only after real target build/launch proof |
| `GenreMigrationPlanV1` | old/new PackIds/schema, source diff, conflict/removed fields, last-good/snapshot, explicit loss policy | DATA-04 owns CAS/rollback; never auto-run code during migration |
| `GenreAuthoringPrincipalV1` | project scope, authenticated identity/role, capabilities, expected source revision, audit correlation | no generic MCP shell, untrusted native extension or client gameplay privileges |
| `GenreProofReceiptV1` | Core SHA before/after, project refs, target profile, test IDs, observed/future proof status, evidence links | cannot set PASSED/COMPATIBLE absent real runner outputs |

## 2. Genre-specific typed recipe adapters (semantic; reused core)
| Typed template binding | Fields / game-specific content | Owner and safety |
|---|---|---|
| `Platformer2DRecipeV1` | ActionIds move/jump, coyote/buffer durations in ticks, contact/moving-platform rules, checkpoints | GAME-01 controls, SIM-03 collision, CORE-04 time; GAME-05 data only |
| `ShooterRecipeV1` | aim/fire/reload ActionId, weapon AbilityId, projectile/hitscan selector, damage/LOS policy, ammo resource | GAME-04 verifies damage, PHYS hit, NET-02 server; no client-confirmed hits |
| `ARPGRecipeV1` | original ability/skill tree schema, typed loot table weights, inventory/quest defs, affix caps, RNG stream/seed | GAME-04 loot/ability/inventory and deterministic rewards; no branded mechanics/assets |
| `VehicleRaceRecipeV1` | VehicleControllerId, checkpoint ordered graph, lap/penalty, role, accessibility driving profile | SIM-05 physics, GAME-04 race state; no custom tire physics |
| `StrategyRecipeV1` | grid/turn FSM, action-point rules, visibility filters, nav query policy, unit templates | WORLD/SIM navigation + GAME-04 state, NET ACL for hidden info |
| `PuzzleRecipeV1` | typed switch graph, state goal/undo scope, deterministic finite seed, reveal/accessibility hints | GAME-04 pure state and event DAG, explicit side effects not undoable |

## 3. Semantic operations exposed to Editor, CLI and MCP
- Read-only: `InspectGenreCatalog(project,filters,page)`; `InspectGenrePack(PackId,version)`; `InspectTemplateCapabilities(target,role)`; `PreviewGenreProject(BlueprintId,Recipe,expectedRevision)` -> composition plan; `PreviewGenreMigration` -> source diff; `InspectGenreProofReceipt`; `InspectGenreExportCompatibility`. No return of secret asset content/unauthorized location.
- Source staging and mutation: `StageGenreProjectCreate(projectName,BlueprintId,Recipe,principal,expectedRevision)` -> StageReceipt; `ValidateGenreComposition(stageId)` -> validated dependency/capability/right plan; `CommitGenreProject(stageId,expectedRevision)` -> DATA-04 journal and stable asset revisions; `CancelGenreStage(stageId)`; `StageGenrePackUpdate`; `CommitGenreMigration` requiring explicit opt-in if destructive.
- Actual play/build/export is separate: `RequestGenreSampleRun(sampleId,target,seed)` calls authorized Editor/headless/test harness; `RequestTargetExport(project,target,approvedPlanId)` delegates to PLAT/QA/DATA-05 and returns actual stage receipt, never fabricated success.
- Runtime game commands remain only GAME-04/NET; an MCP project authoring principal cannot invoke `ApplyDamage`, `SpawnLoot`, `SetHealth` or `WriteFile` directly.

## 4. Lifecycle and transaction boundaries
`UNSEEN -> RESOLVED -> VALIDATED -> STAGED -> SOURCE_COMMITTED -> COOK_PENDING -> PLAYABLE_ON_SUPPORTED_TARGET -> EXPORTED_AND_TESTED`. Unsupported, denied, stale, conflict, failed or rollback-required states are explicit terminal/retryable receipts. Genre pack hot reload requires GAME-02/WORLD/NET version locks and quiescence barrier; compile/build side effects are not rolled back by restoring a source snapshot. A project can import a template but must not claim runnable until scene, script, audio, animation and target packs have passed their owning validations.

## 5. Typed failures and integrity requirements
`TEMPLATE_NOT_FOUND, PACK_SCHEMA_UNSUPPORTED, PACK_VERSION_CONFLICT, PACK_DEPENDENCY_CYCLE, PACK_FEATURE_COLLISION, PACK_CAPABILITY_UNAVAILABLE, PACK_LICENSE_MISSING, PACK_PROVENANCE_UNVERIFIED, PACK_SOURCE_UNTRUSTED, PACK_COUNT_LIMIT, PACK_SIZE_LIMIT, PACK_GRAPH_DEPTH_LIMIT, PACK_PATH_ESCAPE, PACK_SCRIPT_CAPABILITY_DENIED, PACK_NATIVE_CODE_FORBIDDEN, PACK_SAVEDATA_SCHEMA_CONFLICT, SOURCE_REVISION_CONFLICT, SOURCE_COMMITTED_RUNTIME_PENDING, TEMPLATE_OVERWRITE_REQUIRES_APPROVAL, UNSUPPORTED_PLATFORM, WEB_CAPABILITY_DENIED, NO_HEADLESS_RENDER_FALLBACK, GAME_RULE_AUTHORITY_DENIED, GAME_CONTENT_COPYRIGHT_RISK, ANIMATION_BINDING_INVALID, AUDIO_CUE_UNAVAILABLE, PHYSICS_RECEIPT_STALE, NETWORK_AUTHORITY_UNAVAILABLE, CANCELED, MIGRATION_REQUIRED, RECOVERY_REQUIRED`.

Errors have typed reason/retryability/correlation/visibility, no raw host path/secret. Unknown required enum/field/license/ref fails closed; unknown optional fields may be preserved through DATA-04 migration, never silently executed. Canonical serial form, binary ABI, quotas, exact OS version targets, plugin signing, content asset rights and release class remain **TBD / NOT APPROVED**.

## 6. Proof invariants (not achieved)
A template binds to existing GAME/WORLD/SIM/AUD/DATA contracts and never changes Core. A reproducible second **independent original genre** builds from same frozen Core SHA and uses different rule data and asset revisions. Native/Web exports and accessibility require real test artifacts. All [128 planned tests](../testing/game-05-acceptance-matrix.md) **NOT EXECUTED**.
