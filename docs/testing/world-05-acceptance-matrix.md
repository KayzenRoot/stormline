# WORLD-05 — Future Determinism, Graph, Editing and Provenance Test Matrix

**Research #171 | NLE-P00-WO-002-WORLD-05 | Future coding #45 OPEN/BLOCKED.**  
**ALL 160 CASES BELOW ARE FUTURE / NOT EXECUTED.** No generator, golden vectors, C++/WASM, procedural world, graph runner, CPU/GPU benchmark, renderer or editor implemented.

| ID | Future independent acceptance test | Evidence |
|---|---|---|
| SEE-001 | Exact same master seed and pinned recipe hashes produce identical canonical bytes | CPU golden |
| SEE-002 | Same seed but different graph revision changes recipe fingerprint | CPU |
| SEE-003 | Same seed with changed algorithm version not mislabeled compatible | contract |
| SEE-004 | Same seed with changed asset content hash invalidates output cache | DATA05 |
| SEE-005 | 128bit master seed encoding roundtrips endian independently | CPU |
| SEE-006 | Seed derivation domain labels distinguish height from foliage streams | CPU |
| SEE-007 | ProjectId scope separates identical seed outputs across projects | security |
| SEE-008 | WorldId and GraphGuid each independently alter derived key | CPU |
| SEE-009 | NodeGuid change touches only intended substream outputs | property |
| SEE-010 | CellId negative grid values use signed floor coordinate encoding | CPU |
| SEE-011 | Sample global coords invariant under origin rebase | CPU |
| SEE-012 | Stable candidate counter yields same value when workers reorder | replay |
| SEE-013 | Parallel worker counts 1 2 8 give identical canonical hashes | replay |
| SEE-014 | Random traversal order of cells does not change output bytes | replay |
| SEE-015 | New unrelated graph node cannot advance existing global RNG stream | property |
| SEE-016 | Default C++ std hash/process clock never used in canonical generator | audit |
| SEE-017 | Seed key bit width overflow and collision strategy specified and tested | property |
| SEE-018 | Cryptographic access tokens never produced by content RNG | security |
| DAG-001 | Graph topological sort deterministic for nodes with equal dependencies | CPU |
| DAG-002 | NodeGuid stable after renaming or UI layout change | CPU |
| DAG-003 | Directed graph cycle rejected prior to side effects | fuzz |
| DAG-004 | Self dependency graph node rejected | CPU |
| DAG-005 | Disconnected nodes have isolated output and cache scope | CPU |
| DAG-006 | Unknown AlgorithmId or Version rejected with typed receipt | CPU |
| DAG-007 | Port scalar to vector mismatch rejected | CPU |
| DAG-008 | World meters versus centimeters requires explicit converter | CPU |
| DAG-009 | Field resolution adapter explicit and versioned | CPU |
| DAG-010 | Mismatched coordinate handedness rejected before evaluate | CPU |
| DAG-011 | Graph depth and node-edge count limit bounded | stress |
| DAG-012 | Exponential fanout graph denied before OOM | fuzz |
| DAG-013 | Graph asset dependencies with cycles reported in manifest | DATA05 |
| DAG-014 | Invalid source asset rights fail graph validation | security |
| DAG-015 | Graph edge reorder not changing semantics preserves canonical hash | property |
| DAG-016 | Canonical serialization ignores object memory layout padding | serialization |
| DAG-017 | Unicode map key order normalization deterministic and stable | serialization |
| NUM-001 | Fixed-point add multiply rounding profile golden vectors | CPU |
| NUM-002 | Signed integer overflow rejected rather than wrap silently | fuzz |
| NUM-003 | Floating point NaN infinity input forbidden | fuzz |
| NUM-004 | Float precision and quantization profile recorded in recipe hash | CPU |
| NUM-005 | C++ compiler fast-math incompatibility caught by golden proof | compiler |
| NUM-006 | Fused multiply add difference cannot silently claim bit exact | CPU |
| NUM-007 | WASM and native CPU compare canonical output bytes on same recipe | browser |
| NUM-008 | Windows Linux macOS native byte exact golden tests | hardware |
| NUM-009 | Endianness and serialization field order stable cross-platform | serialization |
| NUM-010 | GPU HLSL GLSL WebGPU preview labeled NON_CANONICAL absent proof | GPU |
| NUM-011 | GPU approximated noise never writes server-authoritative collider | PHYS |
| NUM-012 | Determinism receipt UNKNOWN never presented as VERIFIED | contract |
| NUM-013 | Version upgrade requires explicit migration acceptance | migration |
| CEL-001 | Adjacent height tile border samples identical with shared halo | CPU |
| CEL-002 | Negative region coordinates preserve sample continuity | CPU |
| CEL-003 | Per-cell load/unload order does not change world content hash | replay |
| CEL-004 | World origin shift never changes generated placement IDs | WORLD03 |
| CEL-005 | Large world coordinate signed overflow typed error | fuzz |
| CEL-006 | Seeded neighbor foliage dedup resolves owner cell exactly once | CPU |
| CEL-007 | River region solver declares shared region scope across cells | contract |
| CEL-008 | Cross-cell road geometry contiguous when generated in region scope | oracle |
| CEL-009 | Too small halo rejected rather than silently produce seam | CPU |
| CEL-010 | Independent tile generation not claimed for globally constrained solver | architecture |
| CEL-011 | Teleport cancels obsolete generation without stale publish | concurrency |
| CEL-012 | World unload invalidates late generator callback epoch | concurrency |
| CEL-013 | Generated asset source hashes track world cell source revision | DATA05 |
| ALG-001 | Pinned FastNoiseLite CPU noise sample vector compared exactly | optional |
| ALG-002 | OpenSimplex2 source algorithm selected file-level license verified | optional |
| ALG-003 | Cellular noise output not falsely assumed within minus1 plus1 | property |
| ALG-004 | Domain warp and fractal octave caps prevent huge work | budget |
| ALG-005 | Noise seed derived from stable graph node domain | CPU |
| ALG-006 | Ridged fBM output under negative coords stable | CPU |
| ALG-007 | Original biome altitude slope masks normalized and finite | CPU |
| ALG-008 | Weighted placement density respects source mask bounded count | CPU |
| ALG-009 | Candidate thin and delete keyed stable IDs unaffected by worker order | replay |
| ALG-010 | Generated stable instance GUID never aliases authored manual instance | WORLD04 |
| ALG-011 | Procedural mesh recipe does not directly allocate renderer GPU buffers | architecture |
| ALG-012 | Manual artist placement remains distinct from algorithm proposal | WORLD04 |
| ALG-013 | Graph sample seed use not derived from wall-clock | audit |
| ALG-014 | Time-varying decorative preview explicitly nonauthoritative | contract |
| WFC-001 | Tile adjacency valid input yields matching edge constraints | oracle |
| WFC-002 | Unsatisfiable tile graph yields CONTRADICTION not invalid result | CPU |
| WFC-003 | Bounded retry count generates stable failed receipt | replay |
| WFC-004 | Solver iteration budget returns NO_SOLUTION_WITHIN_BUDGET | stress |
| WFC-005 | Stable entropy tie-break preserves result under worker variations | replay |
| WFC-006 | Backtracking memory cap prevents exponential allocation bomb | security |
| WFC-007 | WFC output pattern respects licensed input rights | license |
| WFC-008 | Contradiction does not mutate scene or crash editor | fault |
| WFC-009 | Input sample tiles never copied from unlicensed reference assets | license |
| WFC-010 | Alternative deterministic fallback explicit rather than silent substitution | contract |
| SRC-001 | Generator preview makes no DATA04 or WORLD01 mutations | unit |
| SRC-002 | Old generated base and new generated base diff respects author overlay | DATA04 |
| SRC-003 | Untouched artist layer sees new base field only | merge |
| SRC-004 | Manually painted terrain height retained after recipe rerun | DATA04 |
| SRC-005 | Manual foliage instance retained after generated placement refresh | DATA04 |
| SRC-006 | Artist-deleted generated rock stays suppressed via stable tombstone | DATA04 |
| SRC-007 | Regenerated base removed manually modified tree returns orphan conflict | merge |
| SRC-008 | Explicit orphan map to replacement requires user scope authorization | security |
| SRC-009 | Recipe version change preserving ID maps explicit migration or conflicts | migration |
| SRC-010 | Artist added instance never wiped by generated base replacement | DATA04 |
| SRC-011 | Undo recipe change restores prior source and manual overlays | DATA04 |
| SRC-012 | Redo after concurrent authoring edit checks revision conflict | DATA04 |
| SRC-013 | Cross-editor CLI MCP concurrent commit CAS prevents lost update | concurrency |
| SRC-014 | Failed regeneration does not destroy last-good published runtime scene | recovery |
| SRC-015 | Crash after source commit before runtime publish replays idempotently | recovery |
| SRC-016 | Source committed runtime pending receipt is truthful | contract |
| SRC-017 | Rendered world/PHYS collision remains on coherent revision until ack | PHYS |
| SRC-018 | Undo deletion tombstone restores or suppresses according to journal | DATA04 |
| SRC-019 | Manual edits to linked prefab variant retain WORLD02 target IDs | WORLD02 |
| CAC-001 | Node dependency hash covers all changed graph parameters | CPU |
| CAC-002 | Dependency hash covers algorithm and numeric version | CPU |
| CAC-003 | Source asset hash mismatch invalidates generated cache | DATA05 |
| CAC-004 | Deleted asset cannot reuse stale content cache after revocation | security |
| CAC-005 | Cell-local changes invalidate only proven affected output region | R&D |
| CAC-006 | Neighbor halo invalidation included in incremental dependency graph | R&D |
| CAC-007 | SCDI incremental output equals full rebuild oracle on all edits | R&D |
| CAC-008 | SCDI failure abandons incremental strategy without losing scene | R&D |
| CAC-009 | Duplicate concurrent request shares immutable correctly keyed result | concurrency |
| CAC-010 | Cancelled task cannot insert poisoned stale cache artifact | fault |
| CAC-011 | Output serializer hashes canonical source not GPU preview bytes | CPU |
| CAC-012 | Cache provenance receipt records full source license and revision | integrity |
| CAC-013 | Memory and IO cache physical ownership remains DATA05 | architecture |
| SEC-001 | Malicious graph embedded script or executable shader never evaluated | security |
| SEC-002 | Arbitrary file path remote URL from generator node forbidden | security |
| SEC-003 | Untrusted serialized graph node count and recursion cap | fuzz |
| SEC-004 | Untrusted seeded region radius and output count constrained | fuzz |
| SEC-005 | Huge WFC or erosion solver computation cancelled at budget | stress |
| SEC-006 | Invalid graph type schema cannot reinterpret raw pointer bytes | security |
| SEC-007 | Cross-project generator source asset view denied | security |
| SEC-008 | MCP edit requires author role and DATA04 expected revision | security |
| SEC-009 | Remote client cannot authoritatively regenerate server quest world | NET |
| SEC-010 | Sensitive graph/asset references redacted in public preview | privacy |
| SEC-011 | Generated asset sample and tile pattern provenance preserved | license |
| SEC-012 | FastNoiseLite MIT license notice when pinned adapter adopted | license |
| SEC-013 | WFC MIT software vs sample art rights independently reviewed | license |
| SEC-014 | OpenSimplex2 per-file CC0/Unlicense marked correctly | license |
| SEC-015 | SideFX Houdini Unreal PCG proprietary code never vendored | license |
| SEC-016 | No high critical dependency/security finding in exact implementation | audit |
| INT-001 | WORLD04 biome height material and vegetation proposal typing | integration |
| INT-002 | WORLD03 cell streaming origin epoch and generator cancel aligned | integration |
| INT-003 | WORLD02 prefab override provenance and manual edits preserved | integration |
| INT-004 | WORLD01 stable ECS EntityGuid generated placements mapped safely | integration |
| INT-005 | DATA03 imported graph/assets validated before generating | integration |
| INT-006 | DATA04 journal source revision and undo/redo owner preserved | integration |
| INT-007 | DATA05 asset cook cache has actual source license and hash | integration |
| INT-008 | CORE05 fixed coordinates and numeric precision shared | integration |
| INT-009 | CORE06 tasks and cancellation quotas integrated | integration |
| INT-010 | PHYS collision source generated only after approved owner ACK | integration |
| INT-011 | NET gameplay server authority not replaced by client procedural output | integration |
| INT-012 | GFX04 geometry GFX05 PBR GFX07 HDR remain sole rendering owners | architecture |
| INT-013 | TWO02 tiles from generated rules retain authored tile source | integration |
| INT-014 | Dedicated headless server canonical CPU generation no GPU | headless |
| INT-015 | Windows Linux macOS and Web WASM same recipe hash smoke | hardware |
| BEN-001 | Fresh and warm generation CPU p50 p95 p99 per patch | benchmark |
| BEN-002 | Peak memory and output byte size for 100 1k 10k cells | benchmark |
| BEN-003 | Different worker and cell order canonical output hashes equal | benchmark |
| BEN-004 | Graph node count versus peak memory and compile/eval time | benchmark |
| BEN-005 | WFC success failure rate and bounded retries at varying constraints | benchmark |
| BEN-006 | Full recompute vs SCDI incremental with source edits | R&D |
| BEN-007 | Cross-OS compiler math profile and WASM byte equality | benchmark |
| BEN-008 | GPU preview mismatch measured without authoring source corruption | benchmark |
| BEN-009 | Procedural biome image quality compared to manual original fixtures | visual |
| BEN-010 | Manual layer protection and deterministic undo after regeneration | benchmark |
| BEN-011 | Streaming teleport and cancelled request no p99 gameplay stall proof | benchmark |
| BEN-012 | No infinite generation zero stutter or byte guarantee without real tests | audit |

## Future acceptance evidence that does NOT exist yet
- Produce independent byte-level golden corpus of `RecipeV1 + MasterSeed128 + Graph/Asset hashes + AlgorithmId/Version + global Cell/Patch/halo + numeric profile`, for original licensed forest/desert/alpine/river/tile motifs. Reject claim “same seed same result” if graph algorithm/asset/version/toolchain profile changed. Validate CPU canonical outputs on **actual** Windows/Linux/macOS and WASM/browser targets with two compiler suites where supported. Native GPU sample equality only if proven; otherwise mark noncanonical preview.
- Typed graph model oracle for DAG topo order, optional bounded constraint WFC, source rights, numeric/units/ports and negative world coordinate/neighbor seams, worker/cell iteration permutations, fixed seed derivation vectors, stable generated EntityGuid/placement identities and no runtime authority leak.
- DATA-04 manual source and generated base versioned *separately*. Golden scenario: artist sculpts mountain, paints snow, deletes generated rock, adds hand-placed tree, changes prefab variant. Re-generating an unrelated or changed recipe MUST preserve those edits, or return typed orphan conflict and require explicit resolution. Require real stage/preview/commit/undo/redo/crash recovery tests and source/GPU/PHYS acknowledgements.
- Security/fuzz test malicious imported graph, huge node/fanout/cycle/WFC unsolvable, sensitive private source and arbitrary external code/script. No graph side effects, SSH/shell, client-auth gameplay manipulation or unlicensed example tiles. Rights/security audit after code, no HIGH/CRITICAL.
- Real CPU p50/p95/p99 and peak memory per original benchmark workload, DATA-05 cache invalidation with exact provenance, WORLD-03 streaming load/cancel, consistent generated content and visual quality. SCDI optional incrementality only if full-rebuild equality and measured benefit. Quantitative thresholds and target hardware still **UNDECIDED**.
