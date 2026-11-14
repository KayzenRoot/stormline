# WORLD-04 — Future Terrain/Vegetation/Water/Atmosphere Acceptance Matrix

**Research #168 | NLE-P00-WO-002-WORLD-04 | Future code #44 OPEN/BLOCKED**  
**ALL 148 TESTS LISTED ARE FUTURE / NOT EXECUTED.** No terrain code, real biome scene, foliage, water, editor, GPU/PHYS, C++/Web build, perf or visual proof.

| Test ID | Future independent acceptance case | Proof surface |
|---|---|---|
| TIL-001 | Signed tile coordinates preserve stable patch IDs at negative world positions | CPU |
| TIL-002 | Patch ID independent of viewer origin and camera LOD | CPU |
| TIL-003 | Adjacent authored height tiles share exact common border samples | oracle |
| TIL-004 | LOD neighbor left right up down stitched with no visible cracks | GPU golden |
| TIL-005 | Tile transition with different sample resolutions preserves border height | CPU |
| TIL-006 | Terrain patch world transform uses CORE05 origin epoch correctly | integration |
| TIL-007 | Large global coordinate shift does not corrupt height source/edge | CPU |
| TIL-008 | Invalid nonfinite height input rejected before source mutation | fuzz |
| TIL-009 | Heightfield holes explicitly not treated as full cave topology | contract |
| TIL-010 | Cave/overhang authored mesh follows separate topology link | integration |
| TIL-011 | Signed tile multiplication overflow returns typed error | fuzz |
| TIL-012 | Terrain patch removed while loading not resurrected from stale callback | fault |
| TIL-013 | Two viewers same tile share source and do not duplicate patch asset | memory |
| TIL-014 | WORLD03 cell identity mapped unambiguously to terrain tile ID | integration |
| TIL-015 | Missing patch source shows explicit incomplete vs fabricated ground | safety |
| LOD-001 | Quadtree camera screen-space error selects valid tile levels | CPU |
| LOD-002 | Clipmap ring neighbor coverage no gaps under camera motion | GPU |
| LOD-003 | Geomorph transition limits silhouette popping | visual |
| LOD-004 | Skirt stitching hides geometric cracks without shadow leaks | visual |
| LOD-005 | Adjacent two LOD different tessellations remain watertight | GPU golden |
| LOD-006 | LOD downgrade never deletes authoritative collision data | PHYS |
| LOD-007 | Morph shader visual-only displacement marked vs collision height | contract |
| LOD-008 | Low-end WebGL2 tier runs fallback with no mesh/compute shader | browser |
| LOD-009 | Actual feature-probe before optional tessellation/mesh shader use | GPU |
| LOD-010 | Large origin shift resets per-tile clipmap cache epochs safely | GPU |
| LOD-011 | Rapid teleport cancels obsolete LOD tiles and preserves last good | fault |
| LOD-012 | Geometry update respects GFX03 fences/VRAM quotas | GPU |
| LOD-013 | Occlusion and HLOD ownership remains GFX04 alone | architecture |
| LOD-014 | Visual screen-space error measured vs high-detail reference | benchmark |
| LOD-015 | Cave to terrain edge renders without crack at multiple LODs | GPU |
| MAT-001 | Splat weights finite and nonnegative, normalized at each sample | CPU |
| MAT-002 | Zero-sum splat channels use approved default layer | CPU |
| MAT-003 | Height slope procedural mask respects manual overrides | source |
| MAT-004 | Linear working-space blending no double sRGB conversion | color |
| MAT-005 | Triplanar normal transforms correct on tilted/negative slope | GPU |
| MAT-006 | Texture array missing source falls back visibly with receipt | fault |
| MAT-007 | Virtual texture page faults delegated to GFX05 ownership | integration |
| MAT-008 | Terrain PBR roughness/normal under HDR matches GFX05 references | color |
| MAT-009 | Material masks across tile borders do not show sharp discontinuities | golden |
| MAT-010 | Manual paint preserved after asset source revision or generator recook | DATA04 |
| MAT-011 | Unlicensed/missing texture AssetId cannot enter public asset | security |
| MAT-012 | Texture layer count and resolution bounded by device capabilities | budget |
| MAT-013 | No duplicate terrain-exclusive BRDF or shader compiler | architecture |
| EDT-001 | Stage sculpt stroke changes preview but not committed source | unit |
| EDT-002 | Stroke crossing 4 tiles modifies all seam neighbors transactionally | DATA04 |
| EDT-003 | Concurrent editor CLI MCP stroke expected revision CAS rejects stale | concurrency |
| EDT-004 | Undo sculpt layer recovers exact height samples and provenance | DATA04 |
| EDT-005 | Redo after unrelated newer manual edit does not silently overwrite | DATA04 |
| EDT-006 | Imported base height change preserves authored manual layers | migration |
| EDT-007 | Generated base patch change preserves manual adjustment provenance | WORLD05 |
| EDT-008 | Brush radius/strength/falloff max and NaN reject | fuzz |
| EDT-009 | A very large stroke fails quota without partial source mutation | stress |
| EDT-010 | Crash after journal before terrain GPU publish recovers last good | recovery |
| EDT-011 | Brush impacted PHYS collider requires new source revision ACK | PHYS |
| EDT-012 | Undo reverts collision shape only after safe owner barrier | PHYS |
| EDT-013 | Cancelled brush leaves no stale GPU tile staging | fault |
| EDT-014 | Unauthorized actor cannot edit foreign project patch | security |
| EDT-015 | Sculpt edit on streamed-out tile staged via DATA05 and WORLD03 | integration |
| BIO-001 | Biome zone ID stable across editor renames/reparent | source |
| BIO-002 | Biome boundary blending weights normalized and bounded | CPU |
| BIO-003 | Artist biome mask wins over generated source according to policy | DATA04 |
| BIO-004 | Original forest desert snow coast transitional palette preview | visual |
| BIO-005 | Manual placement stable instance GUIDs on reload/revision | source |
| BIO-006 | Generated vegetation instance stable provenance separate WORLD05 | integration |
| BIO-007 | Same tree instance at cell border not double-instantiated | WORLD03 |
| BIO-008 | Large instanced foliage count bounded by scene/per-device policy | stress |
| BIO-009 | Close foliage casts shared GFX06 shadows only within budget | GPU |
| BIO-010 | Far foliage impostor/mesh transition silhouette error measured | visual |
| BIO-011 | Transparent foliage respects alpha cutout/depth/AA | GPU |
| BIO-012 | Foliage overdraw perf vs alpha appearance and shadow tested | benchmark |
| BIO-013 | Wind sway visual displacement does not alter server collision | PHYS |
| BIO-014 | Gameplay tree collider remains pinned outside camera | WORLD03 |
| BIO-015 | Grass with no collision explicitly flagged decorative | contract |
| BIO-016 | Snow on vegetation does not double-apply HDR exposure | GFX07 |
| BIO-017 | Cluster spawn/destroy after cell reload has no resource leaks | ASan |
| WAT-001 | Ocean authored body region stable after source rename | source |
| WAT-002 | River/Lake/Ocean visual source class semantics distinct | CPU |
| WAT-003 | Gerstner visual wave phase deterministic from visual time input | CPU |
| WAT-004 | Shader surface displacement not used as PHYS buoyancy truth | PHYS |
| WAT-005 | Approved PHYS sampled-water contract matches gameplay when used | integration |
| WAT-006 | Coastline intersects heightfield at all relevant LOD without gaps | GPU |
| WAT-007 | Foam/shore masks don't smear after origin rebasing | visual |
| WAT-008 | Reflection SSR failure off-screen disclosed and fallback visible | GPU |
| WAT-009 | Transparency refraction depth alpha layers preserve order | GFX05 |
| WAT-010 | Water scene-linear HDR colors correct under exposure | color |
| WAT-011 | Underwater camera transition uses GFX06 fog GFX07 post | integration |
| WAT-012 | Low-tier water does not require FFT/compute/mesh shaders | browser |
| WAT-013 | Water rain visual splash delegated GFX08 | integration |
| WAT-014 | River flow/wetness cannot authoritatively move gameplay actor | security |
| WAT-015 | Water body streaming out waits for PHYS volume ACK | fault |
| SKY-001 | Time-of-day source visual profile receives CORE clock tick | integration |
| SKY-002 | Sky sun directional light direction from GFX06 coherent | GFX06 |
| SKY-003 | Bruneton LUT optional mode matches reference within quality budget | GPU |
| SKY-004 | Analytic sky fallback works on WebGL2 without volumetric textures | browser |
| SKY-005 | Fog height aerial perspective follows atmosphere source consistently | GFX06 |
| SKY-006 | Weather cloud shadow receives GFX06 budget owner limits | GFX06 |
| SKY-007 | Fast cloud/wind changes invalidate GFX07 temporal history | GFX07 |
| SKY-008 | Rapid sunrise sunset transition no double tone mapping | color |
| SKY-009 | HDR/SDR source output color controls no gamut out of policy | GFX07 |
| SKY-010 | Night sky visual stars do not imply astronomical simulation | contract |
| SKY-011 | Rain and snow VFX belong to GFX08 not WORLD04 emitter | architecture |
| SKY-012 | Network weather gameplay authority cannot be overridden by visual profile | NET |
| SKY-013 | Server headless environment profile readable without GPU | headless |
| SKY-014 | Storm/clear day lighting and wetness use same authoritative tick | integration |
| SKY-015 | Volumetric clouds disabled if unsupported with honest quality receipt | GPU |
| SEC-001 | Untrusted heightmap decompression size limited by DATA05 | security |
| SEC-002 | Malformed component format imported only via DATA03 | security |
| SEC-003 | Brush unknown executable script or shader payload denied | security |
| SEC-004 | External URL/file path from MCP brush cannot fetch arbitrary asset | security |
| SEC-005 | Huge foliage instance IDs and recursion quota enforced | fuzz |
| SEC-006 | Adversarial negative NaN HDR/atmosphere parameters rejected | fuzz |
| SEC-007 | Cross-project biome/world profile leakage denied | security |
| SEC-008 | Imported terrain map/photo licensing and rights documented | license |
| SEC-009 | meshoptimizer and Terrain3D MIT pin and notice gate | license |
| SEC-010 | Bruneton BSD pin and third-party notices verified | license |
| SEC-011 | Unreal proprietary sample terrain art not copied | license |
| SEC-012 | Old published GPU Gems numbers not treated as Stormline results | audit |
| SEC-013 | No high critical vulnerability accepted for code or imported assets | audit |
| SEC-014 | Device loss during terrain upload releases after fence safely | fault |
| INT-001 | WORLD03 cell pin and DATA05 chunk residency source consistency | integration |
| INT-002 | GFX04 geometry culling and LOD owner receives typed hints | integration |
| INT-003 | GFX05 texture color/material owner receives masked weights | integration |
| INT-004 | GFX06 shadows sky fog owner receives weather visual intent | integration |
| INT-005 | GFX07 HDR temporal owner resets on cloud/origin changes | integration |
| INT-006 | GFX08 rain snow dust particle owner receives event intents | integration |
| INT-007 | WORLD05 procedural noise does not overwrite manual terrain layers | integration |
| INT-008 | WORLD01/02 IDs stable after scene prefab reload | integration |
| INT-009 | DATA04 undo journal and CPU/GPU/PHYS state snapshots coherent | integration |
| INT-010 | PHYS collision/nav surface ACK before traversable patch | integration |
| INT-011 | NET weather and GAME authoritative current tick preserved | integration |
| INT-012 | TWO04 sprite terrain depth order under origin changes | integration |
| INT-013 | Windows native Vulkan or DX12 original biome smoke | hardware |
| INT-014 | Linux native Vulkan original biome smoke | hardware |
| INT-015 | macOS Apple Silicon Metal original biome smoke | hardware |
| INT-016 | WebGPU/WebGL2 original biome reduced-tier smoke | browser |
| INT-017 | Dedicated headless server no visual GPU requirement | headless |
| BEN-001 | Original multi-biome traversal p50 p95 p99 full frame CPU GPU | benchmark |
| BEN-002 | Terrain alone patch LOD/vertex cost with measured cracks | benchmark |
| BEN-003 | Foliage memory peak/overdraw and shadow tier vs quality | benchmark |
| BEN-004 | Water SSR/refraction approximations measured vs reference | benchmark |
| BEN-005 | Sky scattering/cloud quality and temporal ghost metric | benchmark |
| BEN-006 | Brush stroke latency and DATA04 journal fsync cost | benchmark |
| BEN-007 | Original coast/cave/snow/forest/desert HDR native captures | benchmark |
| BEN-008 | WebGPU and WebGL2 fallback quality/perf at equal assets | benchmark |
| BEN-009 | PHYS terrain height mismatch error during edit and streaming | benchmark |
| BEN-010 | Origin rebase under fast travel preserves visual+collision | benchmark |
| BEN-011 | SABE prove-or-drop vs simple independent LOD quality/perf | R&D |
| BEN-012 | No advertised better-than-Unreal performance without real matched runs | audit |

## Future proof obligations, not passed
- Independent **original rights-cleared** biome fixtures: forest with multilayer foliage, rocky alpine snow/splat, dry canyon/cave entrance with separate mesh, beach/ocean/river shoreline, day/night/cloud/rain transitions and 2D/2.5D coexistence. Pin exact assets, texture licenses, patch/source hashes, cameras, weather ticks and native/Web feature tiers.
- CPU reference patch border/negative global coordinate/LOD neighbor consistency, finite height/weight/normal/origin math; real GPU golden image, HDR/SDR capture, visual quality error and native/Web hardware proof needed separately. Raw source collision profile must agree with PHYS; visual-only water waves and wind cannot become gameplay truth without PHYS contract.
- Authoring tests must perform real DATA-04 CAS, preview/stroke/falloff/cancellation/undo/redo after WORLD-03 asset streaming, verify source rights and preserve manual overrides on WORLD-05 recook. Test missing imported texture/asset and scene rebase, renderer fences, stale PHYS ACK and device loss. **No markdown checklist proves these work today**.
- Numeric screen-space error, seam epsilon, p95/p99 GPU terrain/foliage/water/sky and full frame, CPU edit latency, VRAM/UMA, weather temporal ghost/color and collision discrepancy TBD until approved 1.0 DoD and device matrix. Unsupported WebGL2 optional shader capabilities get documented fallback rather than false parity.
- Threat model: hostile heightmap decompression, malicious shader/script payload, excessive forest instancing, cross-project secret assets, unlicensed 3D/landscape and HTML/MCP data, invalid sky parameters and network authority. Future implementation requires TSan/ASan/fuzz/security and zero known HIGH/CRITICAL.
