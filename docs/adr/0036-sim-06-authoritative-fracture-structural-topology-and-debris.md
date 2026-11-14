# ADR-0036 — Authoritative Structural Damage, Pre-fractured Assets and Non-authoritative VFX

**STATUS: PROPOSED / NOT APPROVED FOR CODE**  
**2026-11-14 | Research #189 | WO NLE-P00-WO-002-SIM-06 | Future coding issue #51 OPEN/BLOCKED.**

## Context
Destruction integrates geometry, physics contacts, streaming, navmesh, surface impact effects, particles and gameplay/network authority. If the GPU can decide collision/damage or a terrain collider disappears before navigation and character support are invalidated, clients may collide with invisible walls or walk into missing ground. Full runtime boolean fracture, unconstrained tiny debris and global persistence are high risk for server CPU/heap and data integrity. SIM-02, GFX-08 and WORLD-03 are documented research only; source licensing and platform acceptance remain unproven.

## PROPOSED decision
1. **Engine-owned versioned contract:** DestructibleAsset, MaterialResponse, DamageIntent, BondState, FractureActivation, StructuralSnapshot, DestructionReceipt and cosmetic-event requests, scoped by World/Entity/Chunk generations, source hash, authority, TickId and origin epoch. No native vendor pointer or third-party ABI in Stormline public SDK.
2. **Prefracture-first:** prefer offline authored deterministic chunk/bond geometry with bounded cooked collision proxy and interior render mesh, over mandatory runtime arbitrary splitting. An explicit no-fracture safe state and multiple damage visual stages are valid capabilities. Live boolean/voxel full material fracture is FUTURE and PROVE-OR-DROP.
3. **Authoritative truth:** GAME/NET validates impact/damage; SIM-02 owns bodies/constraints/contacts and accepts bounded physical chunk activation at safe fixed-tick barrier. SIM-06 evaluates material/bond damage and proposes PHYS changes; reads actual PHYS commit ACK before claiming structural break.
4. **World/nav publication:** WORLD-03 leases and WORLD-04 source delta, DATA-04/05 verified source, SIM-05 nav and SIM-03 ground support invalidation must agree before altered traversable topology becomes active. No partial/invisible collision publication; on missing ACK, fail closed or roll back staged split with typed receipt.
5. **Visual separation:** GFX-08 emits limited cosmetic fragments, smoke, sparks and optional mesh particles from accepted events, never gameplay collisions or hit validation; GFX-04/05/06/07 render geometry, decals, shadows and history. Authoritative solids cannot be culled/despawned solely because render tier changes.
6. **Persistence:** authored structural changes use snapshot/event log under DATA-04/WORLD owner and NET approved replication, with source/cell/generation and migration policy. Cosmetic decals have bounded retention and stable surface IDs; persistent terrain crater only through WORLD-04-owned staged edit. No duplicate asset writer.
7. **Technology comparison not adoption:** NVIDIA Blast prefractured chunk/bond architecture a candidate/reference with its legal/transitive/build graph to audit and no assumed physics renderer; Voro++ modified BSD for offline Voronoi cells; OpenVDB version-dependent license (**12+ Apache-2.0; earlier MPL-2.0 per official release history**); libigl primarily MPL-2.0 with specific GPL/copyright parts to exclude; Jolt candidate only via SIM-02. No Houdini Engine paid runtime dependency.
8. **Safety and tiers:** strict caps on new physical bodies/constraints, chunk/collider complexity, stale source and budgets; downgrade cosmetic detail independently of server structural truth, typed failure on resource exhaustion; numerical limits and OS/Web support established in later runtime benchmarks.

## Rejected alternatives
- GPU particle impacts or renderer occlusion as PHYS/Game authority.
- An always-on physical body per tiny shard and globally persistent unsized decal/impact registry.
- Raw vendor native API, GPU-only physics, proprietary authoring license mandatory or unlicensed sample destructibles.
- Automatic content/terrain collision deletion before streaming, navigation and PHYS publication ACK; unstaged cross-cell mutability.
- Claim that Voro++ alone provides mesh intersection/UV/interior normals, Blast contains own collision renderer, or OpenVDB has a single timeless license.
- Auto-adopting GPL-affected geometry helpers without reviewing distribution choice NLE-D009.

## Consequences and approval gate
Cost: versioned staged writes, conservative physics/nav coordination, extra chunk-cook validation, persistence and replay inputs, CPU-only fallback, profiling across CPU/GPU/VRAM. Benefit: safe visual scalability without gameplay inconsistency.
**PROPOSED only:** no SDK integrated or benchmark executed, no asset/geometry generated, no physics/particle runtime. To approve code: implement upstream SIM-02/GFX-08/WORLD-03 and required WORLD/GAME/DATA barriers, pin licenses/SBOM and ABI, choose one NECESSARY slice, define numerical budgets/platform tests, high-risk rollback plan and objective independent technical evidence. Until then 80 coding WOs remain blocked, #51 OPEN/BLOCKED.
