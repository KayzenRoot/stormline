# SIM-06 — Destruction & Environmental Response Architecture

**Research WO:** NLE-P00-WO-002-SIM-06 | **Research issue #189** | **Future implementation issue #51 OPEN/BLOCKED**  
**BASE main:** `1a0fd10dde4f9fa119732d445fbce8499bec29f6` | **P00 PROPOSED / DOCS ONLY**: no destruction runtime, fracture asset, editor, engine build, VFX frame, geometry test, benchmark or actual deployment.  
**Risk:** LOW documentary, future ELEVATED for unsafe mesh/voxel parsing, resource exhaustion, mutable physics/network authority, streaming source publication, persistence and rollback.

## 1. Product goal and boundary
Catalog acceptance: **"Degradação controlada, orçamento de fragmentos e sincronização."** Design dramatic but **measurably bounded** impact, deformation and breakage for original 2D, 2.5D and 3D worlds, Windows/Linux/macOS, conditional Web and CPU/headless server. High-end appearance and gameplay safety come from deliberately separating (A) authoritative topology, collision and gameplay, (B) *physically simulated* chunks with bounded budgets, and (C) **cosmetic** GPU/CPU debris, sparks, dust, audio and decals. Never promise more realistic destruction or faster rendering than third-party engines without matched benchmarks.

Prioritize authored **pre-fractured hierarchy** (asset chunks + adjacency/bonds + material zones) and incremental runtime bond/activation decisions; robust arbitrary boolean cut, dynamic meshing, voxel erosion of entire world and deformable solids are **FUTURE / PROVE-OR-DROP**, not baseline. Visual quality can be enhanced with authored interior surfaces/edge noise, dust/embers/trails and physically plausible impulses while simulation stays bounded and portable.

## 2. Module ownership; no second engine
| Owner | Source/consumer | SIM-06 must NOT own |
|---|---|---|
| CORE-04 | TickId and fixed-step sequencing, bounded catch-up, replay schedule | independent clock, render-frame gameplay step |
| CORE-05 | physical units, origin epoch, global/local transforms and spatial precision | new origin coordinate system |
| CORE-02/03/06 | heap/job budgets, cancellation and diagnostics/profiling | free-running worker pool, allocator, global log |
| WORLD-01/02 | EntityGuid/generation, scene/prefab transforms, stable instance IDs | separate ECS/prefab/scene registry |
| WORLD-03 | CellId, resident leases, staged unload, source revision, publication and cell pins | second world streamer or unsigned residency assumptions |
| WORLD-04/05 | authored terrain/biome procedural sources, damageable target source and edits | second terrain/worldgen authoring data model |
| DATA-02/03/04 | AssetId, rights, validated source import, authoring revisions and journal/CAS | raw host I/O, durable scene writer, foreign importers in runtime |
| DATA-05 | offline target cook, chunk/bundle manifest and bounded verify/load | arbitrary runtime decoder/decompressor, second packfile cache |
| SIM-02 | collision/world/body/constraint handles, contact/forces and safe PHYS barriers | rigid-body solver, physics contact truth, direct reentrant body mutation |
| SIM-03/04 | character motion/ground/ragdoll and visual root motion | motor/ragdoll solver or unsanctioned teleport |
| SIM-05 | safe tile/nav version/edge invalidation and ACK before game-traversable geometry changes | navmesh solver or silent navigation topology edits |
| GAME/NET | server-side hit/damage/ability/team authority, replication/rollback | damage rules, client trust, multiplayer consensus |
| GFX-04/05/06/07 | geometric LOD/render identity, PBR/decals, light/shadow/temporal & color | renderer, shadow solver, material pipeline |
| GFX-08 | cosmetic particles/mesh debris/ribbons/smoke and FX graph receipts | effect graph, GPU particle engine, gameplay collision from visual debris |
| AUD | authored source and spatial one-shot cues | audio engine, voice timing scheduler |
| EDIT/CLI/MCP | one typed authenticated authoring kernel and preview | arbitrary runtime commands, private physics/scene writes |

Mandatory catalog dependencies **SIM-02 + GFX-08 + WORLD-03** are only documentary research; executable code missing. Additional WORLD-04/SIM-05/GAME/Data contracts specify affected owners, not implementation authorization.

## 3. Destructible asset and material response
Versioned `DestructibleAssetV1` refers DATA-02 AssetId/hash and approved source rights; non-executable recipe with material layers, chunk hierarchy, stable ChunkGuid/BondGuid, local pivots/rest transforms, closed or repairable geometry with clearly declared acceptance, interior PBR material references, chunk bounds/inertia/mass (checked), collision proxy IDs, accumulated damage stages and author-defined visual fallback LODs. A cooked `FractureCookManifestV1` records source revision, generator/seed, units/axis and toolchain, original mesh, chunk count/topology bounds, connectivity map, collider convex source, render LOD, visual FX and staged startup body-count limits. This is **DATA-03/05 authored/cooked and immutable at runtime**, not SIM-06 raw arbitrary asset import.

Candidate offline cook families: designer-sliced chunks, Voronoi cells and bounded clipping of original mesh, volume/SDF voxel extraction for unusual forms only where legal library/ABI and memory budgets allow, and manual multi-level authored destruction LOD. Voro++ computes 3D cells, **not a complete robust cutting/interior meshing pipeline**. OpenVDB can help sparse volume operations; converting to crack-free collision-safe meshes and correctly attributed interior UV is an independent proof obligation. No self-intersecting unbounded output or implicit inverse-mass coercion.

A material response profile encodes thresholds, bond toughness, anisotropic direction/material layers, radial blast vs localized impulse, surface wear/heat/crack pre-state, cap on secondary fragment activation and plausible scaling; candidate steel, wood, glass, stone and brittle props receive **different authored** patterns. Damage energy semantics must be GAME/SIM-02 sourced with checked units; contact impulses do not silently grant player combat damage.

## 4. Authoritative event and fracture transaction pipeline
```text
GAME/NET-authorized hit or SIM-02 validated contact event, TickId
  -> validated DamageIntent with actor/target generations, material/profile source
  -> canonical bounded accumulator, bond threshold and split candidate
  -> stage Chunk/BondStateChange and validated PHYS Body/Shape/Constraint requests
  -> stage WORLD-03 leases + WORLD-04 collider/terrain topology revision
  -> invalidate affected SIM-05 navigation links/coverage and SIM-03 ground support
  -> safe CORE-04 + SIM-02 pre/post-step transaction and owner acknowledgments
  -> atomic valid World/Collider/Topology epoch publication or PENDING/ROLLBACK
  -> immutable DestructionReceipt (actual collision/active fragment changes)
  -> nonauthoritative GFX-08/AUD/GFX-05 cosmetic VFX/decal requests from receipt
  -> persistence via DATA-04 journal and NET-approved replication/snapshot
```
The sequence is a **proposed phase contract**, not a compiled same-tick order. A runtime must specify whether mutations take effect at next fixed tick and how commit/ack prevents a one-frame inconsistency. A chunk cannot be depicted as traversable until PHYS collider and WORLD/terrain/nav safe publication agree. If nav/physics source is unready, **fail closed**: preserve safe old collider state or mark region unavailable, no path/ground success.

**Damage idempotency:** stable `DamageEventId` = World/target generation, AuthorityEpoch, TickId and producer sequence. Duplicate input must not fracture twice. On invalid target, nonfinite damage, stale contact or unauthorized principal, reject before state modification; partial asset/physics deployment returns typed degraded status with rollback/roll-forward plan, never a misleading success receipt.

## 5. Bodies, debris and deterministic limits
- 3D physical debris are **SIM-02-owned dynamic rigid bodies** with finite piece count, bounded impulse/velocity, collision layer/filter and service lifetime; fraction of chunks may remain kinematic/anchored/static clusters to avoid 1000 bodies on a small GPU/mobile tier.
- Batching/aggregation: break a parent into major hero fragments (simulated) and many tiny pieces (GFX-08 visual-only), with hash/seed anchored to accepted DestructionReceipt. Visual-only pebbles **never obstruct a character or grant damage**; headless server skips them entirely.
- Budget dimensions: per EventId max newly activated bodies, chunks, bonds, contact pairs, convex hull complexity, solver iterations, per-cell active debris, total world count, memory, time and CPU jobs, pending structural recalculations, GPU mesh instances, VFX spawns and persistence bytes. Quotas and escalation policy **numerical values UNAPPROVED**; no fake 60 FPS claim.
- Eviction: cosmetic chunks can fade/pool by owned GFX policy. Authoritative solid collision chunks **cannot silently despawn** while a player/NPC rests on them or when game mechanics rely on them. Deactivate/reaggregate only after ownership, support, persistence and streamed cell ACK policy, with explicit reason.
- Repeated high-frequency impacts throttle without dropping gameplay-critical server truth. If budget exhausted, choose bounded simplified/aggregated collision outcome with a typed receipt and identical owner acknowledgment; **never** mark dramatic VFX as a physical split when none occurred.
- Gravity/sleeping, collision generation, hot-reload and WorldOrigin shifts are inherited from SIM-02/CORE-05. Active ragdolls and character contacts need safe barrier and no UAF.

## 6. Dynamic environment and persistent impacts
**Three separate persistence tiers:**
1. `COSMETIC_DECAL`: bounded surface crack, scorch, wetness, scorch texture or bullet mark through GFX-05 material/decals, source-bound and never gameplay collision. GFX-08 may spawn dust/embers. LRU/priorities and permanent/temporary policy must be explicit.
2. `STRUCTURAL_STATE`: canonical chunk bonds and active rigid bodies/anchors, saved as revisioned delta events/snapshot via DATA-04 and rebuilt reproducibly on reload, with WORLD-03 leased cell identity. NET server replicates authoritative state, not untrusted client FX.
3. `TERRAIN_EDIT`: limited supported authored hole/crater/deformation expressed as **WORLD-04-owned terrain edit delta** with changed collider/source and WORLD-03 + SIM-02 + SIM-05 invalidation/rebuild/rollback. No guarantee that mesh/voxel terrain can be cut without a future approved implementation and geometry manifold/clearance proof.

No massive unlimited globally persistent decal list. Persistent marks bind to stable affected surface ID/generation/revision and must correctly migrate or drop with a typed reason if triangle topology changes; cannot store only GPU triangle array indices. Render shadows/reflections/GI temporal history for removed geometry must be invalidated by GFX owners at appropriate fences, not hacked in SIM-06.

## 7. Streaming, physics, navigation and origin consistency
Impact to partially resident cell requires source pinned or command staged with region not physically authoritative until ready; mark `CELL_UNREADY` for unsupported offscreen damage requests. World-03 cell leases cover all parent/chunk/prefab dependencies. Cross-cell large object single canonical owner and proxies, no double spawn at seam. Rebase event must transform active BodyHandle/Chunk transforms using CORE-05 OriginEpoch at safe barrier; stale epoch impacts rejected. Sim-05 nav portals and ground support invalidated before/atomically with destroyed collider, independent of visual particles; dynamic paths may remain `PENDING` until safe nav recook. Reimport/scene changes require DATA-04 CAS and explicit rebase/migration of persisted damage state.
Headless and server must use collision/structural receipts without GPU, textures or audio; only client/server-approved cosmetic seed/codecs. Cross-OS bitwise identical physics/fracture outcome **NOT PROVEN**; authoritative multiplayer NET chooses replication/rollback protocol, deterministic event ordering is only a proposed semantic goal.

## 8. Security, legality and safe authoring
Malicious mesh holes/self-intersections/huge vertex indices, weird chunk cycles/overlapping bonds, NaN/Infinity force, negative mass, collider hull explosion, nonresident source, malformed serialized Blast-style data, forged HIT principal, stale physics callback, arbitrary imported VDB decompression and worst-case CPU on dynamic fracture are future HIGH concerns. Proposed guardrails: strict source formats in DATA-03 sandbox (no arbitrary filesystem/network from MCP), bounded importer/cook, checked integer products and index/graph BFS limits, signed versioned source/manifests and rights, optional isolated workers, cancel/timeouts, audited owner permissions, p95/p99/heap guardrails and fuzz/sanitizer tests (future).
Same Editor/CLI/MCP authoring kernel stages/cancels property changes through DATA-04 revision CAS with dry-run and receipts. Runtime action `ApplyDamage` is **privileged GAME/NET** only, never generic MCP shell/script or editable raw PHY body address. Houdini/SideFX reference workflows require separate license/asset rights; must not mandate paid runtime/editor for free Stormline pipeline.

## 9. Hardware profiles and proof boundaries
CPU authoritative reference is required for headless and portable native/Web; GPU particles and compute/VDB/NanoVDB can **only** be optional visual/cook features if actual platform/driver capabilities and data rights are proven. Candidate tiers: `STATIC_DAMAGE_ONLY`, `LOW_PARTICLE`, `RIGID_MAJOR_CHUNKS`, `HIGH_VISUAL_DEBRIS` with guaranteed same GAME structural outcome where server class enables the feature. Visual density can scale; collision gameplay semantics and NET state cannot silently diverge due to GPU tier or user graphic settings. Comparative quality/fps experiments and acceptance thresholds FUTURE only. Next research SIM-07 after separate checkpoint; coding #51 stays BLOCKED.
