# SIM-06 — Acceptance Matrix: 120 FUTURE Cases, NONE EXECUTED

**Research #189 | WO NLE-P00-WO-002-SIM-06 | Coding #51 BLOCKED | P00 DOCUMENTARY ONLY.** All **120** candidate tests are **FUTURE / NOT EXECUTED**; there is no engine, physical fracture, artwork, scene, runtime stress, Web build, GPU benchmark or security-test result.

## Prospective test matrix
| ID | Scenario | Status |
|---|---|---|
| SIM06-SRC-01 | Authored wall and stone/glass/wood material profile source | FUTURE / NOT EXECUTED |
| SIM06-SRC-02 | Reject unlicensed/missing provenance in fracture fixture | FUTURE / NOT EXECUTED |
| SIM06-SRC-03 | Stable AssetId/ChunkGuid across compatible reimport | FUTURE / NOT EXECUTED |
| SIM06-SRC-04 | Reject cyclic chunk hierarchy and duplicate BondGuid | FUTURE / NOT EXECUTED |
| SIM06-SRC-05 | Reject NaN/Infinity/negative mass inertia | FUTURE / NOT EXECUTED |
| SIM06-SRC-06 | Check manifold/winding/interior normals and bounded mesh errors | FUTURE / NOT EXECUTED |
| SIM06-SRC-07 | Reject forged collision proxy hash and shape mismatch | FUTURE / NOT EXECUTED |
| SIM06-SRC-08 | Reject oversized chunk count, index overflow and rogue VFS path | FUTURE / NOT EXECUTED |
| SIM06-COOK-01 | Voro++ seed cells require valid mesh clipping stage | FUTURE / NOT EXECUTED |
| SIM06-COOK-02 | Exact source/cook version and seed produce equivalent chunk map | FUTURE / NOT EXECUTED |
| SIM06-COOK-03 | Reject narrow sliver producing invalid collider shape | FUTURE / NOT EXECUTED |
| SIM06-COOK-04 | Convex collision proxy generation with correct physical units | FUTURE / NOT EXECUTED |
| SIM06-COOK-05 | Interior UV/tangent and material reference survive baking | FUTURE / NOT EXECUTED |
| SIM06-COOK-06 | Validate two-tier fracture LOD vs one-tier fallback | FUTURE / NOT EXECUTED |
| SIM06-COOK-07 | Reject corrupt compressed fracture bundle/chunk manifest | FUTURE / NOT EXECUTED |
| SIM06-COOK-08 | Bounds on cook CPU/time/memory and cancellation cause no output | FUTURE / NOT EXECUTED |
| SIM06-BOND-01 | Strong vs brittle material threshold relationship | FUTURE / NOT EXECUTED |
| SIM06-BOND-02 | Impact normal influences prescribed anisotropic damage | FUTURE / NOT EXECUTED |
| SIM06-BOND-03 | Stable graph traversal and allowed connected components | FUTURE / NOT EXECUTED |
| SIM06-BOND-04 | Contact and attack damage source authority separated | FUTURE / NOT EXECUTED |
| SIM06-BOND-05 | Accumulated tiny impacts capped and decay policy explicit | FUTURE / NOT EXECUTED |
| SIM06-BOND-06 | Duplicate DamageEventId does not fracture twice | FUTURE / NOT EXECUTED |
| SIM06-BOND-07 | Reject negative/NaN damage and invalid bond index | FUTURE / NOT EXECUTED |
| SIM06-BOND-08 | Bond break under budget creates only permitted physical chunks | FUTURE / NOT EXECUTED |
| SIM06-PHYS-01 | SIM-02 rejects stale Body/Shape/WorldEpoch | FUTURE / NOT EXECUTED |
| SIM06-PHYS-02 | Pre-step body creation returns real PHYS ack | FUTURE / NOT EXECUTED |
| SIM06-PHYS-03 | Reentrant contact listener cannot mutate chunk graph | FUTURE / NOT EXECUTED |
| SIM06-PHYS-04 | Dynamic major chunk and static anchored remain distinct | FUTURE / NOT EXECUTED |
| SIM06-PHYS-05 | True contacts on exposed convex collision proxies | FUTURE / NOT EXECUTED |
| SIM06-PHYS-06 | Fragment speed/impulse/collision layers clamped and valid | FUTURE / NOT EXECUTED |
| SIM06-PHYS-07 | Sleep/wake and static reaggregation preserve contact correctness | FUTURE / NOT EXECUTED |
| SIM06-PHYS-08 | No false simulated break if physics activation rejected | FUTURE / NOT EXECUTED |
| SIM06-BUD-01 | Max chunks per hit and per world cell bound | FUTURE / NOT EXECUTED |
| SIM06-BUD-02 | Max dynamic rigid body/constraint count bound | FUTURE / NOT EXECUTED |
| SIM06-BUD-03 | Burst stress throttles without world physical lie | FUTURE / NOT EXECUTED |
| SIM06-BUD-04 | Physics budget exhaustion returns explicit simplification or failure | FUTURE / NOT EXECUTED |
| SIM06-BUD-05 | Cosmetic shard count scales by tier but GAME outcome same | FUTURE / NOT EXECUTED |
| SIM06-BUD-06 | Budget upgrades/downgrades cannot change authoritative collider | FUTURE / NOT EXECUTED |
| SIM06-BUD-07 | Fairness across concurrent destructible events and cell budget | FUTURE / NOT EXECUTED |
| SIM06-BUD-08 | One-hour lifecycle never leaks retired body or source lease | FUTURE / NOT EXECUTED |
| SIM06-WORLD-01 | Unloaded target impact returns CELL_UNREADY or queued policy | FUTURE / NOT EXECUTED |
| SIM06-WORLD-02 | Cross-cell object has one canonical owner and no duplicate split | FUTURE / NOT EXECUTED |
| SIM06-WORLD-03 | Cell eviction waits for physical/support leases and journal | FUTURE / NOT EXECUTED |
| SIM06-WORLD-04 | Origin rebase preserves chunk/PHYS colliders position | FUTURE / NOT EXECUTED |
| SIM06-WORLD-05 | Stale OriginEpoch damage intent is rejected | FUTURE / NOT EXECUTED |
| SIM06-WORLD-06 | Load/stream staged chunk source hash validated | FUTURE / NOT EXECUTED |
| SIM06-WORLD-07 | Evict/destroy race cannot dereference freed chunk or tile | FUTURE / NOT EXECUTED |
| SIM06-WORLD-08 | Nonresident ground never marked traversable due to VFX | FUTURE / NOT EXECUTED |
| SIM06-TOPO-01 | PHYS and NavTopologyEpoch commit barrier matched | FUTURE / NOT EXECUTED |
| SIM06-TOPO-02 | Remove wall invalidates SIM-05 path before new traversability | FUTURE / NOT EXECUTED |
| SIM06-TOPO-03 | Terrain crater journal stage blocked if collider rebuild absent | FUTURE / NOT EXECUTED |
| SIM06-TOPO-04 | Rollback retains last-safe collision and nav topology | FUTURE / NOT EXECUTED |
| SIM06-TOPO-05 | NPC does not enter unloaded floor after fracture | FUTURE / NOT EXECUTED |
| SIM06-TOPO-06 | Character grounded support rejects retired chunk BodyHandle | FUTURE / NOT EXECUTED |
| SIM06-TOPO-07 | Dynamic door/bridge destruction updates nav offmesh link | FUTURE / NOT EXECUTED |
| SIM06-TOPO-08 | Failure in one owner ACK aborts or safe PENDING complete receipt | FUTURE / NOT EXECUTED |
| SIM06-VFX-01 | GFX-08 dust/sparks from accepted DestructionReceipt only | FUTURE / NOT EXECUTED |
| SIM06-VFX-02 | CPU headless run identical authoritative structural state | FUTURE / NOT EXECUTED |
| SIM06-VFX-03 | Visual shards do not collide or grant damage | FUTURE / NOT EXECUTED |
| SIM06-VFX-04 | GFX-04 mesh LOD fallback keeps material chunk identity | FUTURE / NOT EXECUTED |
| SIM06-VFX-05 | GFX-05 interior PBR/decals bound to correct surface revision | FUTURE / NOT EXECUTED |
| SIM06-VFX-06 | GFX-06 shadow/probe invalidation after topology change | FUTURE / NOT EXECUTED |
| SIM06-VFX-07 | GFX-07 reactive/velocity history avoids stale ghost fragment | FUTURE / NOT EXECUTED |
| SIM06-VFX-08 | GPU device loss degrades cosmetic effects not PHYS state | FUTURE / NOT EXECUTED |
| SIM06-MARK-01 | Bullet mark on stable surface/generation with expiry | FUTURE / NOT EXECUTED |
| SIM06-MARK-02 | Reload restores canonical structural state without decal explosion | FUTURE / NOT EXECUTED |
| SIM06-MARK-03 | Surface topology change invalidates stale triangle attachment | FUTURE / NOT EXECUTED |
| SIM06-MARK-04 | Stage cosmetic material scorch without mutating collider | FUTURE / NOT EXECUTED |
| SIM06-MARK-05 | Persistent crack stage from damage threshold reconciles with GAME | FUTURE / NOT EXECUTED |
| SIM06-MARK-06 | Decal quotas LRU protected gameplay mark policy | FUTURE / NOT EXECUTED |
| SIM06-MARK-07 | Cross-cell impact mark belongs exactly one world owner | FUTURE / NOT EXECUTED |
| SIM06-MARK-08 | Undo/redo revision merge does not duplicate structural effects | FUTURE / NOT EXECUTED |
| SIM06-NET-01 | Server accepted DamageIntent produces one stable event receipt | FUTURE / NOT EXECUTED |
| SIM06-NET-02 | Client-forged DamageIntent rejected without mutation | FUTURE / NOT EXECUTED |
| SIM06-NET-03 | Out-of-order and duplicated network events idempotent | FUTURE / NOT EXECUTED |
| SIM06-NET-04 | Replay fixed TickId input logs stable structural graph per profile | FUTURE / NOT EXECUTED |
| SIM06-NET-05 | Client graphics tier cannot change server collision timeline | FUTURE / NOT EXECUTED |
| SIM06-NET-06 | Disconnect/reconnect snapshot checks source/revision compatibility | FUTURE / NOT EXECUTED |
| SIM06-NET-07 | Source migration conflict requires explicit reject/repair | FUTURE / NOT EXECUTED |
| SIM06-NET-08 | Cross-OS bit-identical replay not claimed without numeric proof | FUTURE / NOT EXECUTED |
| SIM06-ENV-01 | Static cosmetic crack before structural split | FUTURE / NOT EXECUTED |
| SIM06-ENV-02 | Limited authored crater edit with WORLD-04 CAS and rollback | FUTURE / NOT EXECUTED |
| SIM06-ENV-03 | Large arbitrary runtime boolean cut explicitly unsupported | FUTURE / NOT EXECUTED |
| SIM06-ENV-04 | Runtime full-world volumetric voxel edit requires future capability | FUTURE / NOT EXECUTED |
| SIM06-ENV-05 | Water/cloth/deformable effects not silently implemented by SIM-06 | FUTURE / NOT EXECUTED |
| SIM06-ENV-06 | 2D wall crack/2.5D prop respects TWO/GFX ownership | FUTURE / NOT EXECUTED |
| SIM06-ENV-07 | HLOD/stream border invalidation remains conservative | FUTURE / NOT EXECUTED |
| SIM06-ENV-08 | Damage-to-light/exposure change stays GFX-06/07-owned | FUTURE / NOT EXECUTED |
| SIM06-SEC-01 | Malformed Blast-like asset and random chunks fail closed | FUTURE / NOT EXECUTED |
| SIM06-SEC-02 | Unknown third-party license or unsupported codec rejected | FUTURE / NOT EXECUTED |
| SIM06-SEC-03 | Decompression bomb bounded at DATA-05 ingress | FUTURE / NOT EXECUTED |
| SIM06-SEC-04 | Overlapping chunks and degenerate triangles cannot crash cook | FUTURE / NOT EXECUTED |
| SIM06-SEC-05 | Arbitrary AI/MCP damage command denied by GAME | FUTURE / NOT EXECUTED |
| SIM06-SEC-06 | Stale generation/epoch UAF fuzz and ASan in future runtime | FUTURE / NOT EXECUTED |
| SIM06-SEC-07 | Race TSan between split/cancel/stream unloading future test | FUTURE / NOT EXECUTED |
| SIM06-SEC-08 | No asset path traversal, signature or hidden data leak | FUTURE / NOT EXECUTED |
| SIM06-PLT-01 | Windows x64/ARM headless CPU policy evaluated | FUTURE / NOT EXECUTED |
| SIM06-PLT-02 | Linux x64/ARM headless CPU policy evaluated | FUTURE / NOT EXECUTED |
| SIM06-PLT-03 | macOS ARM64/Intel physical baseline checked | FUTURE / NOT EXECUTED |
| SIM06-PLT-04 | Browser WASM scalar fallback and memory cap tested | FUTURE / NOT EXECUTED |
| SIM06-PLT-05 | No mandatory CUDA/PhysX extension for cross-platform baseline | FUTURE / NOT EXECUTED |
| SIM06-PLT-06 | No mandatory GPU raster for headless physics truth | FUTURE / NOT EXECUTED |
| SIM06-PLT-07 | Editor/CLI/MCP authoring same schema, rights and CAS | FUTURE / NOT EXECUTED |
| SIM06-PLT-08 | Same physics case across render 20/60/240 FPS has stable tick log | FUTURE / NOT EXECUTED |
| SIM06-BEN-01 | One wall 16/64 major fragments physics CPU p50/p95/p99 | FUTURE / NOT EXECUTED |
| SIM06-BEN-02 | 100 simultaneous impacts with bounded actor allocation | FUTURE / NOT EXECUTED |
| SIM06-BEN-03 | 1000 cosmetic shards visual only GPU/VRAM measurement | FUTURE / NOT EXECUTED |
| SIM06-BEN-04 | Fracture cook CPU/memory/asset bytes cold/warm | FUTURE / NOT EXECUTED |
| SIM06-BEN-05 | Streamer/nav/physics publish latency under repeated damage | FUTURE / NOT EXECUTED |
| SIM06-BEN-06 | 10-minute destruction and restore regression trace | FUTURE / NOT EXECUTED |
| SIM06-BEN-07 | Visual quality rubric shards/dust/cracks with original scenes | FUTURE / NOT EXECUTED |
| SIM06-BEN-08 | Per-tier body/particle counts and frame-time budgets measured | FUTURE / NOT EXECUTED |
| SIM06-REC-01 | Kill process mid staged damage before commit and recover | FUTURE / NOT EXECUTED |
| SIM06-REC-02 | Kill after PHYS ack but before scene journal and reconcile safely | FUTURE / NOT EXECUTED |
| SIM06-REC-03 | Reopen incompatible fracture asset revision with typed conflict | FUTURE / NOT EXECUTED |
| SIM06-REC-04 | Replay structural snapshot before final source load rejects missing source | FUTURE / NOT EXECUTED |
| SIM06-REC-05 | Chunk instance reference retired only after consumer acknowledgment | FUTURE / NOT EXECUTED |
| SIM06-REC-06 | Save/restore twice does not multiply active bodies | FUTURE / NOT EXECUTED |
| SIM06-REC-07 | Repair versioned terrain source preserves unrelated edits | FUTURE / NOT EXECUTED |
| SIM06-REC-08 | Rollback/roll-forward restores physically safe collider and nav state | FUTURE / NOT EXECUTED |

## Criteria and evidence policy
1. **Unit**: validate bounds/units, chunk/bond DAG, material stages, unique EventId, source-hash/epoch, clipping source oracle and typed error results.
2. **Integration**: GAME/NET damage authority; SIM-02 physics safe step, GFX-08 cosmetic VFX, WORLD-03/04 residency/terrain, SIM-05 navigation invalidation, SIM-03 support, DATA-03/04/05 asset/cook/journal.
3. **Stress/security**: exploit corpus for malicious chunks, compressed bombs and stale callbacks; fuzz parsers and versioned geometry, ASan/UBSan/TSan and persistent load/restart/rollback with exact build/seed.
4. **Performance/quality**: CPU p50/p95/p99, allocated/peak bytes, physics bodies/contact count, VFX GPU/VRAM/frame times, nav publish latency, assets, retention and subjective quality blind review, all scoped by original scene, hardware/driver and feature tier.
5. **Platform and reproducibility**: native Win/Linux/macOS, CPU headless and optional browser Web; source, compiler and vendor pins, physics numeric profile, original asset rights, capture/trace, thresholds and tolerances all future acceptance evidence.

**No results have PASS/FAIL classification**, other than later documentary CI unrelated to runtime. All numeric performance budgets, device support and cross-OS bitwise deterministic claims remain **UNDECIDED** until built/tested. Source physics and visual ownership cannot be waived to satisfy cinematic quality or particle count.
