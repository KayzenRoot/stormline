# TWO-02 — Future Tilemap & 2D World Acceptance Matrix

**Research #150 | WO NLE-P00-WO-002-TWO-02 | Code #38 BLOCKED**.

**ALL 93 TEST SCENARIOS ARE FUTURE / NOT EXECUTED.** There is no tilemap engine, GPU draw, editor save/reopen, data importer, running physics owner, benchmark or real device evidence today.

| Test ID | Future acceptance scenario | Required evidence |
|---|---|---|
| CRD-001 | Negative chunk floor division -1 -32 -33 with C32 | CPU golden |
| CRD-002 | Int64 signed limits and multiplication overflow rejected | fuzz |
| CRD-003 | Signed16 boundary -32769 and +32768 persists unchanged | persistence |
| CRD-004 | Far cell exceeding 2^31 has exact chunk key | CPU golden |
| CRD-005 | Rebase 64-bit world cells to bounded local GPU positions | math/GPU |
| CRD-006 | Zero negative and huge chunk widths rejected | fuzz |
| CRD-007 | Randomized global-to-chunk-to-global property | property |
| CRD-008 | Empty sentinel distinct from first valid TileId | unit |
| CRD-009 | Negative coordinates in multiple layer grids | CPU |
| CRD-010 | Camera parallax does not change collision space | integration |
| DAT-001 | Create edit save reopen finite map unchanged | DATA04 |
| DAT-002 | Create edit save reopen negative infinite sparse map unchanged | DATA04 |
| DAT-003 | Undo redo batch crossing chunk seam atomic | journal |
| DAT-004 | Crash during staged edit restores source snapshot | recovery |
| DAT-005 | Concurrent CAS revision conflict rejected | concurrency |
| DAT-006 | Dirty chunk never evicted before durable commit | stream |
| DAT-007 | Corrupted cooked cache rejected without source loss | integrity |
| DAT-008 | Version migration and unknown schema rejection | migration |
| DAT-009 | Tileset rename ID mapping stays stable | asset |
| DAT-010 | Duplicate and overlapping chunk index rejected | fuzz |
| DAT-011 | Imported image asset rights preserved | security |
| GRD-001 | Orthogonal rectangle cell/world inverse including corners | CPU |
| GRD-002 | Isometric cell/world inverse tie-break | CPU |
| GRD-003 | Staggered negative parity inverse | CPU |
| GRD-004 | Hex axial/cube/offset inverse signed coordinates | CPU |
| GRD-005 | Tile flip rotate transforms also update metadata geometry | golden |
| GRD-006 | Tall sprite across chunk remains visible | render |
| GRD-007 | Canvas painter order preserved across chunk batching | TWO01 |
| GRD-008 | Parallax scroll/repeat seamless camera pan | video |
| GRD-009 | DPI zoom does not alter world cell collision coordinates | camera |
| GRD-010 | Animated tile metadata delegated to TWO03 | architecture |
| GRD-011 | Hybrid 2.5D depth delegated to TWO04 | architecture |
| RUL-001 | Wang edge and corner match deterministic seeded rule | unit |
| RUL-002 | 4-neighbor bitmask selection exact | unit |
| RUL-003 | 8-neighbor terrain transition exact | unit |
| RUL-004 | Rule edit invalidates both seam neighbors | integration |
| RUL-005 | Ambiguous terrain variant deterministic tie-break | CPU |
| RUL-006 | Flood fill bounded by max cell time and visited quota | security |
| RUL-007 | Brush stamp line rectangle erase undo/redo | editor |
| RUL-008 | Unknown neighbor in unloaded chunk produces pending state | stream |
| RUL-009 | Terrain rule migration warns on missing TileId | migration |
| RUL-010 | Negative weights NaN and invalid rule rejected | fuzz |
| STR-001 | Visible plus prefetch rings prioritized | CPU |
| STR-002 | Teleport cancels stale chunks and GPU submit | async |
| STR-003 | Hysteresis prevents boundary load thrashing | performance |
| STR-004 | Loading state machine validates generation transitions | state |
| STR-005 | Missing empty corrupt canceled chunks differentiated | fault |
| STR-006 | Compressed zlib gzip zstd bomb blocked by quotas | security |
| STR-007 | Hash mismatch on chunk revision rejected | integrity |
| STR-008 | GPU device loss retires old resources after fence | GFX03 |
| STR-009 | Unknown VRAM reported UNKNOWN not fabricated | budget |
| STR-010 | Camera pan has no seam pop when budget is sufficient | visual |
| STR-011 | Over budget has typed fallback and receipt | stress |
| STR-012 | Uncommitted dirty chunks protected under pressure | recovery |
| STR-013 | WebGL2 does not require compute for chunk rendering | WebGL2 |
| COL-001 | Rect polygon slope and one-way transforms align tiles | PHYS |
| COL-002 | Flip and hex orientation collision mapping exact | PHYS |
| COL-003 | Malformed polygon or nonfinite vertices rejected | fuzz |
| COL-004 | Physics ack generation must match rendered map revision | integration |
| COL-005 | No physics ack blocks interaction on critical tile | fault |
| COL-006 | Collision seam updates atomically across chunks | integration |
| COL-007 | No physics contact solver inside tile renderer | architecture |
| COL-008 | Navigation solver remains separate owner | architecture |
| COL-009 | Chunk unload cannot create invisible walkable wall gap | recovery |
| COL-010 | GPU visuals never authoritative collision truth | security |
| IMP-001 | Tiled GID top four flag bits stripped before lookup | TMX |
| IMP-002 | Tiled diagonal flip order orthogonal/isometric correct | TMX |
| IMP-003 | Tiled hex 60 120 rotation differs from diagonal flip | TMX |
| IMP-004 | Tilesets firstgid only map-local lookup | TMX |
| IMP-005 | Tiled infinite chunks negative coords from XML JSON | TMX |
| IMP-006 | Tiled CSV Base64 zlib gzip zstd decode length exact | TMX fuzz |
| IMP-007 | Tiled external TSX XML entity traversal denied | security |
| IMP-008 | Tiled editor GPL versus libtiled BSD2 license check | license |
| IMP-009 | LDtk JSON stable IID and external ldtkl import | LDtk |
| IMP-010 | LDtk externalRelPath escapes and missing files denied | security |
| IMP-011 | Tiled Wang and LDtk AutoLayer lossy conversion warns | interop |
| IMP-012 | Imported tile texture copyright and scripts inert | license |
| SYS-001 | MCP cross-project edits and oversized batches denied | security |
| SYS-002 | Duplicate source map ID handled safely | data |
| SYS-003 | Unload chunk fence and cancellation valid | fault |
| SYS-004 | Windows D3D12 Vulkan original map capture | hardware |
| SYS-005 | Linux Vulkan original map capture | hardware |
| SYS-006 | macOS Metal original map capture | hardware |
| SYS-007 | WebGPU adapter plus WebGL2 fallback proven | browser |
| SYS-008 | Headless world math save/reopen needs no GPU | headless |
| BEN-001 | Million-tile input is test load not product claim | stress |
| BEN-002 | Chunk 16 32 64 cell size p95 p99 comparison | benchmark |
| BEN-003 | Cold/warm disk load CPU GPU memory frames recorded | hardware |
| BEN-004 | Camera teleport high priority load latency | hardware |
| BEN-005 | Far-world save/reopen deterministic replay | benchmark |
| BEN-006 | Physics activation latency compared to visual ready | benchmark |
| BEN-007 | SWSP prove-or-drop versus radius prefetch | R&D |
| BEN-008 | Matched Godot Tiled LDtk reference without copied art | reference |

## Future proof obligations

- All source assets and fixture maps must be independently authored and rights-cleared: finite/infinite layouts, layers, parallax, terrain, one-way/slope collision, negative cell keys (-1/-32/-33), signed16 and signed32 boundaries, Godot TileMapLayer contrast.
- CPU oracle checks signed division, chunk borders, deterministic seeded Wang rules, exact save/reopen/undo+recovery; these are not GPU or PHYS readiness proof.
- Tiled XML/JSON/TSX and LDtk JSON/ldtkl fuzz and sandbox, quotas for compressed base64/zlib/gzip/zstd, external path traversal and rights. No scripts or arbitrary host file access.
- Future real PHYS service must confirm matching collision revision and block interaction on critical unavailable chunks, and DATA-04 journal commit must survive crash/reload.
- Platform fixtures require named Windows DX12/Vulkan, Linux Vulkan, macOS Metal Apple Silicon, WebGPU and WebGL2 browsers, real disk+GPU measurements, VRAM/UMA known vs UNKNOWN.
- 60 FPS or seamless streaming requires owner-approved scene/hardware and numeric frame p95/p99, I/O stalls, visible seam score, asset types, shader/device revisions and ground-truth visuals. These thresholds are NOT approved, so no test is PASS now.
