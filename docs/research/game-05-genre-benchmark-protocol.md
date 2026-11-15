# GAME-05 — Genre Composition, Template Creation, Export and Cross-Genre Benchmark Protocol

**P00: SPECIFIED, NOT EXECUTED.** Run count 0, no hardware results, no claimed p50/p95/p99, zero engine, no exported samples. Future implementation #61 BLOCKED. Benchmark harness/tools/packages are unselected, and numeric budgets require later approved ADR.

## 1. Hypotheses and proof obligations
H1: two originally authored and mechanically distinct games can be scaffolded/exported from the **same immutable Stormline Core** without any fork or private engine patch; six reference genre packs can be composed without shared-domain duplicate owner.
H2: declarative capability/right/dependency validation prevents unauthorized asset/VM/native feature execution even under adversarial manifests.
H3: target-cooked templates preserve deterministic authored schema and project asset IDs, with clear desktop/Web/headless capability failures and real export.
H4: pack resolution, creation, migration, runtime fixture scheduling and export costs remain bounded as feature graph/asset count scales, without gross regression on modest hardware tiers.
H5: ECS-based/feature plugin architecture patterns (Bevy/O3DE/Lyra) can inform **design**, but performance quality requires apples-to-apples Stormline implementation.

## 2. Manifest for every future measurement
`GenreBenchManifestV1`: Git base/head/Core build sha and git diff clean, approved ADR and compiler/ABI versions, dependency pins/SPDX/SBOM, project and resolved pack graph hashes, per-asset rights proofs, hardware CPU/RAM/disk/OS/arch/GPU, browser engine/version, build mode, native/Web/headless target, job/cache settings, thermal governor, scene/fixture seed and sizes, CLI/MCP/Editor operation, warmup/repeats, exact command, logs/output artifact digest, missing capability reason, run timestamp and executor. No private key/username/path/media in logs. Need real checkout/build or explicitly `NOT RUN`.

## 3. Fixture workload matrix
| ID | Future suite | Dimensions / controlled variables | Required evidence |
|---|---|---|---|
| `F01_CREATE` | cold vs warm project creation | 1/5/20/100 packs, DAG depth 1/4/16, 10/100/1000 assets, no host IO vs DATA staging | p50/p95/p99 wall and CPU per operation, source staging bytes and receipts, zero unauthorized writes |
| `F02_RESOLVE` | diamond/deep dependencies, version conflict, malicious cycles | 1..10k graph edges, consistent source hashes, optional assets missing | validated closure complexity, peak memory, failure latencies and deterministic resolution |
| `F03_RECIPE` | stable mixins/overrides and migration | number of variant layers, changed fields, hot reload and last-good | diff correctness, no lost data, journal recovery, cross-OS source hash |
| `F04_2D` | 2D platformer + puzzle | ticks, player actions, scene sizes, sprite load vs headless | same-target fixed seed replay hash, gameplay tick CPU, memory |
| `F05_SHOOTER` | arena shooter | actors/projectiles/hitscan count, damage/ability fanout, optional NET simulation | authoritative server validation, event backlog, hit receipt, worst tick |
| `F06_ARPG` | generic original action RPG | mobs/items/skills/status tags/affixes/quest events | entropy stream replay, double grant count=0, inventory/save integrity, CPU p99 |
| `F07_VEHICLES` | racing and vehicles | checkpoints, SIM-05 physics updates, analogue input, animation/audio cues | accepted motion vs render, lap correctness, physics/authoring costs |
| `F08_STRATEGY` | grid strategy | N units, fog-of-war, path query count, turns | authority/visibility, per-tick CPU, role filtering and replay |
| `F09_EXPORT` | native and browser export | Windows x64, Linux x64, macOS Apple Silicon, Web browser matrix, headless | actual build/cook/export launch, hashes, compatible feature report, failures not hidden |
| `F10_MALICIOUS` | untrusted pack/supplier | path traversal, native code, giant blobs, bad SPDX, nested loops, unsupported script | rejection without side effects, bounded memory, fuzz/sanitizer evidence |
| `F11_PARITY` | Editor/CLI/MCP semantic authoring | same blueprint/revision, role/capabilities, 100 runs | identical semantic source result; unauthorized MCP denied |
| `F12_UPGRADE` | pack migration/rollback | missing pinned dependency, old schema, license rights removal, partial IO failure | non-destructive CAS, last-good and recovery receipts |

Numeric dimensions are test axes, **not capability claims**. Assets must be original synthetic placeholders or individually licensed and audited; no proprietary PoE, Unreal, Unity or AAA content.

## 4. Measurement discipline
1. Freeze source package/engine revision and record `CoreShaBefore`; generate per genre with exact same engine binary/commit; record `CoreShaAfter` and verify no Core path diff. A mere empty/untested project cannot count as sample success.
2. Independent fixtures for platformer/puzzle baseline and shooter/ARPG distinct second genre; measure original sample passes, then extend to vehicle/strategy. A genuine genre rule change must be done in project/pack sources, not in engine-owned GAME-04/SIM/AUD code.
3. Source authoring: measure preview, validation, DATA-04 CAS/journal, cook, first play, first export and warm reuse **separately**. Cache hits/misses, source and binary asset digests included. Separate editor UX/performance from headless simulation benchmark and from GPU FPS.
4. Under synthetic light/moderate/heavy tiers, measure CPU elapsed p50/p95/p99 and p99.9 only with sufficient raw samples (do not derive p99 from 10 samples), per-platform RSS/persistent disk+output bytes, peak asset import allocations, tick lateness, sample load and export timings. Report confidence intervals/repetitions, warmup, cold cache and background system load.
5. Cross-target Windows/Linux/macOS and Web: require actual toolchain, OS build, tests and browser version. Web JIT/FS/audio/threads/perms differences handled by explicit capability/asset fallbacks. Do not assert cross-target bitwise float determinism; compare invariant outcomes or pin fixed-point/scalar reference policy if approved.
6. Security and reliability: fuzz manifest graphs, path escaping, schema migration, CPU/memory/asset limit bombs, untrusted scripts, rights and license mismatch, network-cosmetic confusion, canceled staging, partial crash and out-of-order event replay. Inject failures at DATA/NET boundaries and require no duplicate rewards or rewritten user project.
7. Game-genre correctness: gameplay tests tie back to 128 G05 IDs, GAME-04 T IDs, SIM-04 root motion and AUD-04 sample cues, UI focus/caption alternatives, gamepad/mouse/touch remapping; no "works" status without real receipts and user/hardware verification where appropriate.
8. Reproduce on at least two selected hardware tiers and each approved OS target; publish raw samples, failed results and synthetic fixture rights, actual performance budgets only after baseline and owner approval.
9. Stop on known HIGH/CRITICAL integrity/license/authorization issue, full DoD not met, unsupported target hidden as success, copied IP or unverified asset source. Return CORRECTION REQUIRED / BLOCKED for future implementation, never bypass.

## 5. Status / post-P00 gate
No benchmark run. Future reference alternatives [Godot demos](https://github.com/godotengine/godot-demo-projects), [Bevy](https://github.com/bevyengine/bevy), [O3DE samples](https://www.docs.o3de.org/docs/learning-guide/samples/), [Unreal Lyra](https://dev.epicgames.com/documentation/unreal-engine/lyra-sample-game-in-unreal-engine) remain architectural comparisons only. Source and asset/license auditing before adoption. All numerical thresholds, release scope, platform versions and CI harness remain UNDECIDED; this protocol is **not evidence of performance**. See [test matrix](../testing/game-05-acceptance-matrix.md).
