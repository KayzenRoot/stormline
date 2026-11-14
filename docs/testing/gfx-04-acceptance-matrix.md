# GFX-04 — Future Geometry Visibility, Instancing, HLOD and Streaming Acceptance Matrix

**WO:** NLE-P00-WO-002-GFX-04 | **Issue:** #132 | **Current status:** 36 SPECIFIED FUTURE TESTS, **NONE RUN**.
Future execution must document fixture SHA/source rights, GFX-01 capability snapshot, real OS/GPU/driver/browser, baseline release state, committed code SHA, native validation and numerical error thresholds; current CI is documentation-only.

| ID | Risk | Future scenario | Required evidence / correctness oracle |
|---|---|---|---|
| GEO-001 | STANDARD | static one-mesh CPU frustum inside/outside | deterministic conservative bounding decision vs draw-all oracle |
| GEO-002 | ELEVATED | negative/nonuniform scale and floating-origin rebase | bounds conservatively transformed, no visible object missing |
| GEO-003 | ELEVATED | camera teleport, jump in FOV/projection and Hi-Z stale frame | invalidate history, draw/rebuild; no false occlusion/popping |
| GEO-004 | ELEVATED | reversed-Z near/far and incorrect depth hierarchy direction | explicit depth convention, reject stale/incompatible evidence |
| GEO-005 | STANDARD | multi-view/viewport Editor resize and camera jitter | per-view epoch/proxy validity; no cross-camera occlusion |
| GEO-006 | ELEVATED | alpha-cutout foliage as proposed solid occluder | reject unsafe occluder and preserve geometry behind holes |
| GEO-007 | ELEVATED | transparent/glass surface and double-sided leaves | never treat transparent as opaque occluder; no false cone cull |
| GEO-008 | ELEVATED | animated/skinned mesh moving beyond rest AABB | envelope/refit keeps animated mesh visible |
| GEO-009 | ELEVATED | morph target/WPO/displacement unknown bound | fail conservative visible, no silent disappearance |
| GEO-010 | STANDARD | meshoptimizer offline vertex/index locality and simplification | original licensed source, attribute integrity/quantized error receipts |
| GEO-011 | STANDARD | meshlet generation and cone/sphere bounds | exact vertex/index ranges, safe one-sided cone applicability |
| GEO-012 | ELEVATED | invalid meshlet indices/corrupted compressed buffer | reject before GPU upload; no memory overflow or crash |
| GEO-013 | STANDARD | imported glTF EXT_meshopt_compression verified decode | codec tag/ABI/endian/memory bounds + DATA-05 hash |
| GEO-014 | STANDARD | glTF EXT_mesh_gpu_instancing with custom per-instance colors | transform/rotation/scale and metadata preserved |
| GEO-015 | STANDARD | coarse LOD transitions with screen-space error/hysteresis | measured silhouette error and bounded visibility popping |
| GEO-016 | ELEVATED | HLOD adjoining clusters at different levels | no visible cracks/seams or documented fallback within tolerance |
| GEO-017 | ELEVATED | interaction/picking/collision object within HLOD merged proxy | authored identity/picking semantics retained or object explicitly excluded |
| GEO-018 | STANDARD | tree/grass billboards vs instanced mesh and meshlets | alpha overdraw, wind deformation, shadow and pixel quality budget |
| GEO-019 | STANDARD | duplicate objects sharing mesh but different material state | instancing grouping preserves reflection/binding, per-instance colors |
| GEO-020 | ELEVATED | GPU indirect count buffer overflow or stale draw buffer | bounded stage/counters and correct GFX-03 barriers, no invalid dispatch |
| GEO-021 | STANDARD | GPU mesh shader supported/not supported on Vulkan and D3D12 | optional feature query, vertex/index/indirect fallback produces correct scene |
| GEO-022 | STANDARD | Apple Silicon Metal native GPU geometry path | real Apple GPU test, no assumed Vulkan task/mesh parity |
| GEO-023 | STANDARD | Windows Vulkan/D3D12 and Linux Mesa/vendor Vulkan | device version, correctness/driver validation, feature-tier receipts |
| GEO-024 | STANDARD | WebGPU supported/unsupported and WebGL2 degraded | actual browser/API capability, no unsupported mesh-shader draw |
| GEO-025 | ELEVATED | high LOD chunk delayed/network timeout/corrupted | root/last-good LOD still visible; typed missing-content if none |
| GEO-026 | ELEVATED | streaming cancellation/rapid camera movement | prioritized visible items within IO/CPU/VRAM budget, no starved required geometry |
| GEO-027 | ELEVATED | DATA-05 bundle generation patch fail / unauthorized source | preserve signed trust model, last-good data and AssetIds |
| GEO-028 | ELEVATED | GFX-03 upload fence pending, device lost/resize/hot reload | no stale GPU buffer, no premature eviction; explicit re-request after loss |
| GEO-029 | STANDARD | 2D sprites/2.5D hybrid are in scene | preserve TWO ordering/picking/depth; no 3D-only occlusion suppression |
| GEO-030 | STANDARD | large city/vegetation scene draw-all, CPU frustum, GPU Hi-Z A/B | correct visible set, draw/triangles/overdraw/VRAM and p95/p99 by hardware |
| GEO-031 | ELEVATED | malicious/huge cluster DAG and adversarial bounds | limits/overflow/cycle/fuzz, bounded decode and no remote code execution |
| GEO-032 | ELEVATED | MCP attempts raw GPU pointers, arbitrary geometry file/URL, shader | deny with no native GPU/filesystem/network side effects |
| GEO-033 | STANDARD | cross-platform deterministic cook with pinned meshoptimizer tag | byte equivalence when actually reproducible or semantic fidelity envelope declared |
| GEO-034 | ELEVATED | third-party mesh model rights and SPDX/SBOM exact releases | allowed assets, meshoptimizer MIT notice, license of decoder/transitives and Epic no-copy |
| GEO-035 | STANDARD | hidden-object cull and visual frame-time regression tracking | measured p50/p95/p99 CPU+GPU+IO, peak resident bytes, pop-in count and sample sizes |
| GEO-036 | STANDARD | SVCG predictive/hysteresis hypothesis vs conservative baseline | zero false negative + measured benefit or drop hypothesis; no ML-required mode |

## Execution plan and acceptance gates
- **Reference visibility oracle**: draw-all with depth and camera metadata for each right-cleared fixture, CPU full-resolution membership test and ground-truth object identity. If occlusion classification has uncertain coverage/bounds, conservative visible fallback prevents false-negative. Avoid asserting perfect numerical pixel matching across vendors where precision differs.
- **Geometry fidelity:** verify OBJ/glTF/world surface and source rights; vertex/index/UV/normal/color/skin/morph and alpha materials under HLOD simplification; no ownership losses. Record source and derived binary version.
- **Platforms:** Windows x64 Vulkan and D3D12, Linux x64 Mesa/vendor Vulkan, macOS arm64 Metal, WebGPU/WGSL browser plus explicit WebGL2; optional advanced mesh/task if supported, never baseline. Compare low-end iGPU vs modern discrete GPU and UMA.
- **Memory/stream:** DATA-05 manifest/chunk digests+publisher trust, root fallback and recovery, GFX-03 alias/fence/VRAM budgets, CPU scheduler, network stalling, chunk failure, content patch rollback, staged graphics buffer validation.
- **Performance:** clean cold cache and warmed scene with identical camera path/LOD error & image golden, p50/p95/p99 CPU geometry planning, GPU cull/draw, frame time, VRAM/RAM peaks, disk/network bytes, geometry error, triangles, draw/dispatches, popping and correctness.
- **Security:** mutated meshlet buffer, index overflow, malicious huge DAG and shader/material bound invalidation, object rights and MCP semantic authorization, source-layout leak/telemetry.
- **OSS/legal:** pin exact meshoptimizer/clusterlod source tag and licenses, compiled dependencies and asset redistribution permissions. glTF KHR draft cannot be treated as ratified by assumption.
- **CI today:** checks Source Pack/links and module DAG/registry/blocked selector only; no C++/codec/real GPU/browser/benchmark run.

**GEO-001..036 ALL FUTURE, NONE EXECUTED.** No tests provide an actual FPS or VRAM result yet.
