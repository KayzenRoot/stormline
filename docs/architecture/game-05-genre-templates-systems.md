# GAME-05 — Genre Templates & Composable Game Systems Architecture v0.1

**Research WO:** NLE-P00-WO-002-GAME-05 | **Research issue:** #224 | **Future implementation:** #61 OPEN/BLOCKED | **BASE main:** `3101c3c956d4fa876261433ee258fe174e00cf77` | **2026-11-15 P00 PROPOSED / DOCUMENTATION ONLY**. There are **no template files, playable demos, engine libraries, compiled exports, benchmarks or genre modules actually implemented**. Release class UNDECIDED, engine license OPEN NLE-D009, all 80 coding work orders blocked.

## 1. Objective and proof boundary
Deliver an original engine-owned *template recipe contract*, not a second gameplay framework, for creating projects in many genres with **zero edits to CORE**: shooter, vehicle driving/racing, action RPG (abilities, loot and inventory), 2D/2.5D platformer, strategy and puzzle. A template consists of stable manifest/source assets/typed behavior recipes, capability requirements, declarative input/gameplay/scene/animation/audio profiles, authored starter content and test fixtures, all versioned and locally reproducible. New game genre is a project asset extension, not a fork of Stormline.

**Required catalog proof in future:** "Amostras originais cobrem gêneros e exportam sem alterar Core." Mere design and other engines' samples cannot satisfy that. Each original sample requires a runnable Editor play session, native Windows/Linux/macOS exported binary, Web export when capability-supported, headless deterministic fixture, clean build/target provenance, licensed source assets and actual test/evidence. No claim of AAA parity, 60 FPS, PoE/Unreal equivalence, multi-OS support or cross-platform deterministic byte equality from P00 planning.

## 2. Ownership boundaries: GAME-05 is composer, never a new engine
| Module | Owner truth, consumed by genre packs | Forbidden duplication |
|---|---|---|
| **GAME-05** | genre recipe schema, pack composition/variants/capability constraints, template generator semantics, sample fixture/test catalog, public authoring operations | hardcoded new physics/ECS, second dispatcher, importer, network bus, scene graph, editor or renderer |
| **GAME-04 (catalog prerequisite)** | typed immutable gameplay events, versioned abilities/inventory/quests/state FSM, command validation/receipts, ticks/events | copy ability system, loot ledger or permission gateway; clients self-mint items |
| **SIM-04 (catalog prerequisite)** | skeleton/clip/animation graph, retarget, IK, motion/root-motion *intent*, ragdoll integration | own bone graph, direct animation pose writes, unversioned animation event |
| **AUD-04 (catalog prerequisite)** | adaptive music, VO/captions/cinematic cue and sample clock mapping via AUD-01 | own audio mixer, new dialogue engine or audio clock |
| GAME-01/02/03 | action frames and remapping, sandbox script/visual graph and secure API, widget/HUD/locale semantic tree | raw input polling, code eval, HTML/JS injection, own UI compositor |
| WORLD-01/02/03 + DATA-01..05 | ECS identity/commit, scene/prefab variants, spatial streaming, scoped VFS, AssetId/right/canonical CAS/import/source/cook | new entity storage, direct host file writes, unmanaged third-party assets or raw resource pointers |
| SIM-02/03/05, CORE-03/04/05/06 | physics/character motors/vehicles/nav as applicable, fixed ticks/jobs/units/diagnostics | direct collision writes, second scheduler/clock, position hacks or homemade async workers |
| GFX/TWO/AUD/PLAT | graphics/audio/2D/native + Web exports, target capability reporting | custom renderer per genre, second audio loop, unverified browser API |
| NET-01..06 | authoritative server/replication/interest/prediction/abuse where **selected** by a sample | mandatory network for offline puzzle; assuming local authority is multiplayer-safe |
| EDIT, AI-01, CLI/MCP | single validated semantic author/preview/commit API with role-scoped capability and data CAS | direct filesystem shell, arbitrary plugin/native code or bypass of authoring validation |

**Dependencies remain only catalog GAME-04 · SIM-04 · AUD-04**, all research-only; other modules are interface consumers/providers. Their unimplemented state prevents coding activation of GAME-05.

## 3. Three-layer composition model
1. **Base `GameProjectBlueprintV1`:** template ID, semantic version, source revision, compatibility/target/rights and initial scene/project settings; does not encode all genres in a giant class hierarchy.
2. **Composable `GenreFeaturePackV1`:** named package with authored assets, dependency manifest, required/optional capabilities, event/ability/rule/scene/animation/audio binding slots, conflict strategy, resource budgets and defined extension points. Features are declared as data and/or GAME-02 sandboxed programs; **not unrestricted native plugins**. Pack can be reused between sample games.
3. **Project-specific `GenreRecipeV1` / `GenreOverrideV1`:** select packs + parameters with typed versioned merge and explicit precedence; project overrides do not mutate base pack or CORE. Game-specific gameplay remains authored or scripted; a generic command gateway validates it.

```text
GAME-05 ProjectBlueprint / GenreFeaturePack / GenreRecipe
    -> DATA-02 stable AssetId + license/provenance + DATA-03 import
    -> DATA-04 versioned CAS, reference/override/diff, DATA-05 target cook
    -> static capability/ABI/dependency DAG + conflict/ownership validator
    -> GAME-01 maps + GAME-02 sandbox/visual graphs + GAME-04 typed rule bus
    -> WORLD-02 scene/prefab composition; SIM-04 animation; AUD-04 audio/caption profile
    -> EDIT/CLI/MCP semantic preview / staged commit (no live runtime mutate)
    -> native/Web/headless target capability validation and reproducible export receipt
```

Composition is a DAG of stable PackId/FeatureId/AssetId. Validate cycles, missing required capability, restricted transitive assets, identifier collisions, conflicting actions/system writes, schema/ABI and unresolved version range. Precedence: base -> feature declared defaults -> project overrides -> scoped user preferences only where allowed (e.g. input), with explicit stable conflict resolution and receipts. No runtime type reflection as version key. Reject malformed/trust-unknown packs before running content; admission of arbitrary native plugins requires separate ABI, security and permission ADR.

## 4. Original genre sample matrix (planned, not built)
| Sample | Shared baseline | Genre-specific authored rules / fixtures | Gate before delivery |
|---|---|---|---|
| `S01_PLATFORMER_2D` | GAME-01 jump/move, GAME-04 state/score, TWO-01/03 sprites, WORLD-02 scene | coyote-time/buffered jump, one-way platforms/moving platforms, checkpoints and timer, accessible bindings | SIM-03 motor collision receipts, orientation 2D coordinates and replay, keyboard/gamepad/touch fallback |
| `S02_SHOOTER_ARENA` | GAME-04 authoritative ability damage/cooldown, GAME-01 aim/fire, SIM-04 locomotion, AUD-04 cues | projectile vs hitscan alternative, cooldown/ammo/reload/line-of-sight, team rules, original enemy dummy, optional NET server | physics query validated; no client-authoritative damage; occlusion/targets/dedupe and explicit shooter safety |
| `S03_ARPG_SANDBOX` | GAME-04 abilities/inventory/quests, GAME-02 graph/rules, GAME-03 equipment UI, SIM-04 motion | original loot table weighted by typed RNG, affix budgets, status/equipment/skill synergies, level scaling, dungeon fixture | no copied PoE/GGG systems/assets or trademark; item/reward idempotency, bounded proc chains, serialized provenance |
| `S04_VEHICLE_RACER` | SIM-05 vehicle controller, SIM-02 rigid bodies, GAME-01 analog input, GAME-04 race FSM | lap checkpoint ordering, track bounds, penalties, deterministic result policy, speed/gear HUD | no own tire model in GAME-05; server/physics authority and cross-tick checkpoint validation |
| `S05_STRATEGY_GRID` | WORLD-02 grid authored scene, GAME-04 action budgets/turn FSM, GAME-02 AI rules | grid coordinate/unit semantics, fog authorization, path requests to nav owner, turn resolution/rules and sandbox opponent | no duplicate spatial index, hidden enemy visibility leak, path determinism/DoS budgets |
| `S06_PUZZLE_2D` | GAME-04 pure state and scene flow, GAME-01 input, AUD-04 cue | original switch/door/pressure puzzle, undo/redo at authored safe state, solvability fixture and hint metadata | avoid unrestricted state revert of external side effects; zero mandatory internet/network |

Additional optional demonstrators: racing vs generic vehicle, third-person action, tile tactics and headless minimal template. **No samples exist** in this research, and sample asset names above are draft fixture IDs, not produced binaries or assets.

## 5. Gameplay systems and genre-safe rules
- **Action/motion:** GAME-01 action intent + CORE-04 TickId + SIM-03/05 accepted movement state; mouse/controller/keyboard/touch no raw OS hooks. 2D/2.5D/3D coordinate adapters reference CORE-05; project cannot mutate global handedness or unit rules.
- **Combat/loot:** GAME-05 authored definitions consume GAME-04 `AbilityDefinitionV1`, `DamageIntentV1`, `StatusEffectDefinitionV1`, `InventoryOperationV1`, `QuestDefinitionV1`; no second combat engine. Loot table `LootTableRecipeV1` uses stable, versioned numeric weights, seed and RNG stream separated from presentation; outcomes can be server-authorized and must not double-grant on retries/rollback.
- **Animation:** authored bind-map connects GAME-04 committed event IDs to SIM-04 validated graph state/marker. Pose/root motion can request SIM-03 moves, never directly teleport entities or grant damage. Animation/presentation-only markers cannot themselves cause authoritative attack in multiplayer unless GAME-04 validates an intended command.
- **Audio:** map committed/cosmetic cues through AUD-04 transition/dialogue/caption policy; missing audio content fallback must not stop headless simulation or affect quest/score.
- **HUD:** GAME-03 read-only view model uses safe localized labels and focus; user-facing language/input accessibility is not implemented by a recipe manifest alone. Editor project templates and runtime HUD are separate.
- **Multiplayer:** optional `TargetRoleProfileV1`, NET-02 server validates authoritative state. Offline samples MUST run without NET; online variants MUST prove the NET capability before release. A recipe cannot assert network safety, anti-cheat, crossplay or deterministic rollback without tests.
- **World:** stable project and scene identities, versioned prefab overrides, world streaming-ready loading. Broken genre package cannot silently update multiple saved scene assets or leave partial reparenting.
- **Security:** all packages and asset manifests are untrusted input, even if available locally. Limit graph depth, file counts/bytes, nested prefabs, texture/audio/script import, paths, names, rule fanout and tool-call side effects. Symlink/traversal, YAML/JSON bombs, type confusion, script capability escalation, rogue remote dependencies, oversized procedural generation and hidden shell commands fail closed with typed denial and redacted logs. No automatic downloads by templates.
- **Recovery:** project creation/upgrade uses DATA-04 stage/validate/CAS + per-asset journal/outbox and explicit `SOURCE_COMMITTED_RUNTIME_PENDING`; cannot claim cross-asset filesystem and DB atomicity. Cancel before commit or return typed partial-recovery plan; do not destructively overwrite existing user project.

## 6. Versioning, migration, SDK and export
`GenrePackManifestV1`/`GameProjectBlueprintV1` are source schema, not a portable binary ABI or preselected JSON/TOML/FlatBuffers format. Pin resolved PackId, feature versions, content hashes, target platforms, compiler/cook provenance and original-asset licenses. Reject incompatible required feature versions and missing target capabilities; migration emits semantic diff, expected source revision, backup and explicit user approval for lossy changes. Deprecations require migration receipts, not silent upgrades.

**Export and parity:** Editor, CLI and MCP call same `PreviewTemplateCreate/Stage/Validate/Commit` engine core semantics under role-scoped rights. Building/exporting belongs PLAT/DATA-05/QA owners and may be unavailable on target. Native Windows/Linux/macOS and Web require real builds, target packaging, no engine Core forks, correct input/audio/renderer fallbacks, headless deterministic seed fixtures and measured performance. Never claim Web gameplay is feasible if a required library needs JIT or unsupported threading.

## 7. Future increments and constraints
**NECESSARY after separate approval only:** manifest schema+resolver+capability/rights checks; one minimal original 2D puzzle/platformer sample with headless deterministic test; a second distinct genre sample requiring no CORE changes; Editor/CLI/MCP parity for creation; DATA-04 CAS and reproducible content hashes; native target feasibility proof. **IMPORTANT:** shooter/ARPG/vehicle/strategy full original sample suite, audio and animation cross-module binding, upgrades/migrations and Web export proof. **FUTURE:** visual genre authoring market, marketplace, mod distribution, multiplayer full clients, procedural world expansion, mature game catalog. No runtime priority can be inferred from the catalog being a research index.

See [ADR-0046](../adr/0046-game-05-declarative-composable-genre-packs.md), [technology/license matrix](../research/game-05-genre-technology-license-matrix.md), [typed contracts](../contracts/game-05-genre-template-api.md), [128 FUTURE cases](../testing/game-05-acceptance-matrix.md), and [benchmarks](../research/game-05-genre-benchmark-protocol.md).
