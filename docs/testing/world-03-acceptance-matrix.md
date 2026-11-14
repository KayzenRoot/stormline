# WORLD-03 — FUTURE Spatial Streaming & Origin Acceptance Matrix

**Research #165 | WO NLE-P00-WO-002-WORLD-03 | code #43 OPEN/BLOCKED**  
**ALL 132 CASES ARE FUTURE / NOT EXECUTED.** No spatial engine, streaming asset, origin-rebase code, GPU/PHYS integration, C++ binary, browser test or measured stall/performance.

| Test ID | Future acceptance condition | Proof surface |
|---|---|---|
| IDX-001 | Sparse hashed grid maps signed negative cell coords using floor division | CPU property |
| IDX-002 | Origin rebase does not change canonical cell ID for same global point | CPU |
| IDX-003 | Huge coordinate near signed overflow rejects rather than wraps | fuzz |
| IDX-004 | AABB exactly on cell border covered by adjacent candidate cells | oracle |
| IDX-005 | Multi-cell giant actor indexed once with stable owner and proxy refs | oracle |
| IDX-006 | Repeated crossing of boundary does not duplicate ECS EntityGuid | integration |
| IDX-007 | Moving object updates old and new index atomically per tick | concurrency |
| IDX-008 | Clustering worst-case spatial hash collision remains bounded | stress |
| IDX-009 | Dynamic local BVH insert/update/remove candidate set correct | oracle |
| IDX-010 | Loose octree/quadtree compared with same brute force oracle | benchmark |
| IDX-011 | Boost R tree candidate querying correct with pinned license build | optional |
| IDX-012 | libspatialindex R star candidate optional exact version/license | optional |
| IDX-013 | Hierarchy level changes maintain global membership identity | CPU |
| IDX-014 | 2D XZ and 3D XYZ layouts preserve declared cell semantics | CPU |
| IDX-015 | Index rebuild after world reload matches source manifest | replay |
| QRY-001 | AABB exact loaded-world spatial query matches brute-force oracle | CPU |
| QRY-002 | Sphere query conservative candidate then exact refinement correct | CPU |
| QRY-003 | Capsule query bound approximation clearly labeled candidate | contract |
| QRY-004 | Point within unloaded cell does not return false COMPLETE empty | safety |
| QRY-005 | Exact query requiring nonresident data returns typed incomplete | safety |
| QRY-006 | Result pagination prevents unbounded memory/secret leak | security |
| QRY-007 | Stable ordering only when explicitly requested and deterministic | replay |
| QRY-008 | Query from wrong world/project epoch denied | security |
| QRY-009 | Query with stale index snapshot rejects and retries | concurrency |
| QRY-010 | Large overlapping results dedup by EntityGuid and source | CPU |
| QRY-011 | Frustum visibility remains GFX04 authority not WORLD03 | architecture |
| QRY-012 | Physics contact broadphase remains PHYS authority | architecture |
| QRY-013 | Nearest neighbor ranking across cells matches reference | oracle |
| INT-001 | Player and camera interest union includes both regions | CPU |
| INT-002 | Physics critical cell pinned even outside current camera | safety |
| INT-003 | Active quest/AI/nav pin cannot be evicted by render interest | integration |
| INT-004 | Audio active content pin respects AUDIO owner lease | integration |
| INT-005 | Multiple camera split screen uses union without duplication | CPU |
| INT-006 | Untrusted client cannot pin arbitrary huge interest radius | security |
| INT-007 | NET replication interest respects server authenticated authority | NET |
| INT-008 | Hysteresis enter/exit minimizes border thrash without hiding required | stress |
| INT-009 | Min dwell/cooldown avoid request churn on oscillating camera | stress |
| INT-010 | Velocity predicted prefetch stays within request and memory quota | budget |
| INT-011 | Fast motion direction reversal cancels obsolete prefetched cells | fault |
| INT-012 | Teleport changes source plan and invalidates queued old gen work | fault |
| INT-013 | Loading when critical cell absent yields safe loading barrier | safety |
| INT-014 | Editor camera never changes gameplay simulation authority | security |
| INT-015 | Interest fairness prevents one remote player starving local core | stress |
| INT-016 | Required pin priority survives memory and I/O contention | stress |
| LIF-001 | Cell state transitions reject skipping validation to ACTIVE | unit |
| LIF-002 | Cell request token binds WorldEpoch CellGeneration and AssetRevision | CPU |
| LIF-003 | Cancelled read completes late and cannot resurrect unloaded cell | concurrency |
| LIF-004 | Duplicate async completion idempotently ignored after publish | unit |
| LIF-005 | Unloaded world invalidates all outstanding cell tasks | fault |
| LIF-006 | Corrupted cooked hash rejected before CPU entity staging | DATA05 |
| LIF-007 | Staged entity manifests validated against WORLD02 source revision | integration |
| LIF-008 | CPU stage never exposes incomplete ECS entities early | safety |
| LIF-009 | GPU staged state optional for headless server | headless |
| LIF-010 | PHYS collision insert ACK required before sim ACTIVE | PHYS |
| LIF-011 | GFX GPU fence/readiness receipt separate from simulation ACTIVE | GFX03 |
| LIF-012 | NET clients not told ACTIVE before server authority completeness | NET |
| LIF-013 | Cell publication at CORE tick barrier one complete snapshot | concurrency |
| LIF-014 | Multi-tick commit retains previous coherent scene until complete | recovery |
| LIF-015 | Crash after asset decode before ECS commit recovery idempotent | recovery |
| LIF-016 | Crash after source commit while GPU lost reports pending | recovery |
| LIF-017 | Evict cell waits for all owner leases and GPU fences | fault |
| LIF-018 | Pinned collision cell returns PINNED under eviction attempt | safety |
| LIF-019 | Lease expiry and owner release can never underflow ref count | property |
| LIF-020 | Failed critical load returns typed failure/backoff rather than stall forever | fault |
| LIF-021 | Retry exponential backoff bound avoids CPU busy loop | stress |
| LIF-022 | Device loss during upload rolls back stale VRAM references | GFX03 |
| ORG-001 | Absolute EntityGuid and CellId survive origin relocation | CPU |
| ORG-002 | Negative world coordinate rounding remains invariant after rebase | CPU |
| ORG-003 | Origin shift request waits for CORE05 and PHYS ACK | integration |
| ORG-004 | Origin epoch update is atomic for published scene transforms | concurrency |
| ORG-005 | GPU camera historic reprojection invalidated by origin jump | GFX07 |
| ORG-006 | NET payload global semantic position independent of client local origin | NET |
| ORG-007 | Split screen separate view origins without world identity conflict | integration |
| ORG-008 | Ultra far position float-to-local epsilon error below approved bound | benchmark |
| ORG-009 | Very large coordinate plus cell size refuses overflow | fuzz |
| ORG-010 | Teleport across multiple cells cannot leave stale physics objects | PHYS |
| ORG-011 | Origin shift while cell decode is queued never changes asset identity | fault |
| ORG-012 | Two competing rebase requests serialize with epoch conflict receipt | concurrency |
| MEM-001 | Peak decoded and staged byte limits enforced before allocation | stress |
| MEM-002 | Compressed zip-bomb decompression limit fails closed | security |
| MEM-003 | GPU memory pressure never silently deletes required collider | safety |
| MEM-004 | Unpinned cells evicted only after all leases/fences clear | fault |
| MEM-005 | Resident cells and CPU staging bytes tracked independently | metrics |
| MEM-006 | Deduplicated DATA05 cached bundle not loaded twice per camera | DATA05 |
| MEM-007 | Shared cache cannot cross project rights or content hashes | security |
| MEM-008 | No leaked asset lease after failed request cancellation | ASan |
| MEM-009 | No leaked GPU resource after cell eviction and device loss | GFX03 |
| MEM-010 | Unsatisfiable critical residency returns safe loading barrier | safety |
| MEM-011 | Queue fairness under multi-world request storms measured | stress |
| MEM-012 | Main tick respects admitted staging CPU millisecond quota | benchmark |
| MEM-013 | Memory fallback receipts report actual or UNKNOWN not fabricated | audit |
| SEC-001 | Malicious negative radius or NaN bounds rejected | fuzz |
| SEC-002 | Untrusted giant integer/float cell indexes fail before allocation | fuzz |
| SEC-003 | External URL/path asset loads forbidden to WORLD03 policy tools | security |
| SEC-004 | Untrusted dependency graph cycles rejected by DATA05 | fuzz |
| SEC-005 | Asset hash/source revision mismatch not loaded silently | security |
| SEC-006 | MCP cross project cell query and diagnostics denied | security |
| SEC-007 | MCP can edit policy only with source CAS and owner role | security |
| SEC-008 | Remote player cannot spoof QUEST/PHYS critical cell pin | security |
| SEC-009 | Unauthorized request cannot enumerate private scene manifests | privacy |
| SEC-010 | Untrusted interest floods quotas and does not starve critical local | stress |
| SEC-011 | No C++ script execution from cooked cell metadata | security |
| SEC-012 | libspatialindex pre 1.8 LGPL excluded without explicit rights review | license |
| SEC-013 | Boost BSL1 and Zstd BSD license versions notices pinned before use | license |
| SEC-014 | Proprietary Unreal Unity docs never copied into source assets | license |
| INTG-001 | WORLD01 generational handles invalidated after legitimate cell unload | integration |
| INTG-002 | WORLD02 scene variants retain GUID and source revision after reload | integration |
| INTG-003 | DATA05 cooker/cache owns asynchronous IO decode and dependency pins | integration |
| INTG-004 | DATA04 durable authored source remains after streamed cell eviction | integration |
| INTG-005 | CORE06 scheduler job budgets and fixed tick barriers respected | integration |
| INTG-006 | PHYS server authority controls collision state and rebase | integration |
| INTG-007 | NET interest serializer and server authorization unchanged | integration |
| INTG-008 | GFX04 HLOD and occlusion culling remain external | integration |
| INTG-009 | WORLD04 terrain content can map to same cells without geometry owner leak | integration |
| INTG-010 | TWO02 2D chunk content residency uses typed 2D cell policy | integration |
| INTG-011 | Headless dedicated server streams sim without GFX backend | headless |
| INTG-012 | Windows native cold/warm streaming end to end | hardware |
| INTG-013 | Linux x64 and ARM64 native streaming end to end | hardware |
| INTG-014 | macOS Apple Silicon native streaming end to end | hardware |
| INTG-015 | Web limited browser with no shared buffer honors safe fallback | browser |
| BEN-001 | Original large traversal including fast flight and teleport replay | benchmark |
| BEN-002 | Frame and physics stall p50 p95 p99 by end to end stage | benchmark |
| BEN-003 | SSD cold and warm I/O/decode times and peak staged bytes | benchmark |
| BEN-004 | HDD simulated slow I/O priority misses recorded | benchmark |
| BEN-005 | Network throttled asset source trace with packet loss | benchmark |
| BEN-006 | Web browser fetch/decode under low memory cap | benchmark |
| BEN-007 | Grid and BVH/R tree oracle memory/time under clustered load | benchmark |
| BEN-008 | CPU memory GPU VRAM peak and overlap across cell cuts | benchmark |
| BEN-009 | Lease/fence eviction lag and misses under stress | benchmark |
| BEN-010 | Predictive SIP prove or drop vs velocity lookahead baseline | R&D |
| BEN-011 | No claims zero stall one million cells or fixed FPS without actual runs | audit |
| BEN-012 | Same seed and source hashes reproduce global interest plan | replay |

## Future acceptance details (not yet implemented)
- Use independently created **rights-cleared** 2D, 2.5D and 3D world fixtures: uniform/nonuniform/negative-coordinate cells, large inter-cell objects, dynamic actors, teleports, physics boundary, two cameras, sound and quest/server pins, unloaded content, streaming asset dependency DAG, intentionally corrupt and oversized content.
- CPU brute-force oracle must validate candidate spatial index completeness and dedup, and exact loaded query intersections vs source geometry. A nonresident query is never “no objects” with COMPLETE. World origins are separate global/source vs local physics/render representations; precision thresholds numeric TBD.
- Model-based cell state-machine property/fuzz plus actual DATA-05 hash/cancellation/fence/lease and WORLD-01/ECS safe-tick integration before any acceptance. Testing in the registry markdown is **not** execution. GPU/PHYS/NET must independently ACK readiness; delayed async tasks may never resurrect stale cell.
- Measure **entire** frame/physics p50/p95/p99 including commit, not merely async I/O throughput. Burst memory, IO, CPU decode, staging, GPU upload/fence, late collision and safe loading gates after teleport, peak VRAM/UMA must be inspected on named machines. Owner must choose numeric p95/p99, max safe memory, cold/warm device and 1.0 DoD before real proof.
- Actual Win/Linux/macOS/Web/headless builds and fault injection/security fuzz/asset source rights tests are FUTURE. No million-cell or 60fps capability is claimed now.
