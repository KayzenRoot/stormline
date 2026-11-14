# GFX-08 — Future VFX Graph, Particle and Performance Acceptance Matrix

**WO NLE-P00-WO-002-GFX-08 | Research #144 | Code #36 BLOCKED**.  
**ALL 78 cases below are FUTURE and NOT EXECUTED.** No real VFX visuals, shader, CPU executable, cross-target build, GPU device, VDB asset or benchmark has been created. Exact fixtures, tools, hardware, tolerance and budget thresholds require later owner-approved scope.

| ID | Future acceptance scenario | Evidence type |
|---|---|---|
| GRF-001 | Valid typed node DAG topological order | CPU unit |
| GRF-002 | Cycle/feedback without bounded delay rejected | graph fuzz |
| GRF-003 | Node port type/unit mismatch rejected | unit |
| GRF-004 | Unknown required node/schema version rejected | version |
| GRF-005 | Missing material/asset revision and rights rejected | DATA-02 |
| GRF-006 | Max node/edge depth/total work quotas enforced | fuzz |
| GRF-007 | NaN/Inf lifetime/velocity/color rejected | fuzz |
| GRF-008 | Graph migration and stable node IDs preserve overrides | DATA-04 |
| GRF-009 | Sub-emitter recursion/loop bombs stopped | adversarial |
| GRF-010 | Atomic graph hot reload preserves last good | fault |
| GRF-011 | Editor/CLI/MCP semantic result parity | integration |
| CPU-001 | Spawn fixed-step seed replay reference stable | CPU numeric |
| CPU-002 | Batch bursts vs per-frame emission rate correct | unit |
| CPU-003 | Pause/resume slow frame max substeps bounded | fault |
| CPU-004 | Emitter cancellation releases all child instances | unit |
| CPU-005 | No write past max alive/burst count | fuzz |
| CPU-006 | Checked 64-bit spawn+pool size overflow rejection | security |
| CPU-007 | Local/world transforms + origin rebase correctness | math |
| CPU-008 | Zero-lifetime/death events and 1-frame emission | unit |
| CPU-009 | Tiny particle burst CPU/GPU cost crossover benchmark | hardware |
| CPU-010 | Headless CPU validation without GPU driver | headless |
| CPU-011 | Cosmetic particle collider never game hit authority | security |
| GPU-001 | Compute storage SoA layout alignment across backends | shader |
| GPU-002 | GPU compaction/scan count overflow no OOB | GPU fuzz |
| GPU-003 | GPU load/dispatch bounds and indirect draw safe | GPU |
| GPU-004 | GPU device loss/recovery no stale handles | fault |
| GPU-005 | Frames-in-flight pooling fence reuse safe | GFX-03 |
| GPU-006 | GPU-to-CPU readback not done by default | privacy/perf |
| GPU-007 | GPU and CPU particle distribution visual tolerance | golden |
| GPU-008 | No compute capability -> CPU fallback | WebGL2 |
| GPU-009 | Shader layout/signature version conflict safe | GFX-02 |
| GPU-010 | Offscreen culling conservative trails and emitters | GFX-04 |
| GPU-011 | GPU shader low-end thermal/bandwidth quota | hardware |
| VIS-001 | Sprite/flipbook 2D frame interpolation correct | 2D |
| VIS-002 | Layered 2.5D parallax depth+alpha masks | 2.5D |
| VIS-003 | 3D mesh particles PBR/unlit material parity | 3D |
| VIS-004 | Ribbon fast turn/zero tangent/near-plane no NaN | geometry |
| VIS-005 | Trail capacity rollover no wild triangles | geometry |
| VIS-006 | Trail rebase and camera cut no retained ghost | temporal |
| VIS-007 | Additive alpha skips unnecessary sort | perf |
| VIS-008 | Sorted alpha crossing ribbons and mesh layers | golden |
| VIS-009 | Weighted blended OIT approximation with known losses | golden |
| VIS-010 | AMD Parallel Sort DX12/Vulkan capability/license gate | license/GPU |
| VIS-011 | Soft depth particles with reversed-Z camera | GFX-04/07 |
| VIS-012 | Premultiplied alpha and transparency ownership | GFX-05 |
| VIS-013 | HDR emissive color and reactive mask no ghost trails | GFX-07 |
| VIS-014 | No bloom applied to HUD on top of effects | UI |
| VIS-015 | Overdraw tile worst-case fullscreen transparency | stress |
| VIS-016 | Tiny geometry and pixel-art crisp 2D fallback | 2D |
| LGT-001 | 1000 sparks request bounded proxy lights only | ARPG |
| LGT-002 | GFX-06 light budget degradation recorded | integration |
| LGT-003 | Fog density stamp bounded scattering owner | GFX-06 |
| LGT-004 | Sparse VDB absent -> sprite smoke fallback | low-end |
| LGT-005 | Particle shadows/geometry cascade invalidation policy | GFX-06 |
| LGT-006 | Audio event emission quota and once semantics | AUDIO future |
| LGT-007 | Camera shake reduced-motion policy enforced | accessibility |
| SYS-001 | WebGL2 CPU sprite/limited ribbon fallback | WebGL2 |
| SYS-002 | WebGPU storage/compute WGSL support probes | WebGPU |
| SYS-003 | macOS Metal GPU path and CPU fallback | Apple Silicon |
| SYS-004 | Windows DX12/Vulkan capability and real capture | native |
| SYS-005 | Linux Vulkan fallback and real capture | native |
| SYS-006 | Partial asset streaming/missing flipbook safe | DATA-05 |
| SYS-007 | Invalid/hostile VDB/EXR/texture metadata quotas | fuzz |
| SYS-008 | Effekseer optional MIT/backend dependency audit | license |
| SYS-009 | OpenVDB Apache-2.0 transitive code/asset audit | license |
| SYS-010 | Untrusted graph shader/path/URL injection denied | security |
| SYS-011 | MCP cross-project edit/oversized diff denied | security |
| SYS-012 | Graph rollback after failed staging preserves state | DATA-04 |
| SYS-013 | Native/device version/profile hot reload cancels | recovery |
| SYS-014 | Flash and motion sensitivity limit switches respected | accessibility |
| BEN-001 | ARPG 1/10/100/1000 emitters as workload not promise | bench |
| BEN-002 | Particle count vs overdraw P50/P95/P99 CPU/GPU | hardware |
| BEN-003 | Max trail/sort/fog/VRAM budgets and frame pacing | hardware |
| BEN-004 | Competitor Niagara/GGG-like matched clean-room fixtures | benchmark |
| BEN-005 | SVAG vs fixed-tier prove-or-drop across devices | R&D |
| BEN-006 | GPU low-memory pressure and graceful visual loss | hardware |
| BEN-007 | Effect salience telegraph readability score | UX |
| BEN-008 | Power/temperature/fan cost if available vs quality | hardware |

## Future proof suite
- Use original, rights-cleared fixtures for ARPG arena with spells/explosions, crossing alpha ribbons, impact sparks, foliage, fog walls, 2D pixel arena and 2.5D parallax layers. `1/10/100/1000` is an artificial stress load, NOT an implemented capacity promise.
- CPU fixed-seed golden and reference smoke tests do not count as GPU visual/throughput evidence. Set CPU/GPU distribution tolerance and hardware microbench baselines before accepting.
- Graphics targets: actual Win DX12/Vulkan, Linux Vulkan, macOS Apple Silicon Metal, WebGPU adapter/browser and WebGL2 fallback. No substitution of synthetic GPU features or assumed backend compatibility.
- Capture P50/P95/P99 individual passes (spawn, GPU update, compaction, alpha sort, render/overdraw, fog, GFX-06 lights, GFX-07 masks), total CPU/GPU frame and VRAM/UMA budget with known/estimated/unknown data provenance. Include cold/warm shader+texture cache and device loss.
- Score visual correctness plus gameplay telegraph salience, ghosting/frame pacing, alpha and refraction limitations, readability in reduced flashes/motion, device recovery without memory damage. Numeric image/temporal/readability thresholds remain UNDECIDED.
- Fuzz hostile and cyclic graph, integer overflow, asset parser rights/SBOM/transitive licenses, cross-project MCP, fake shader/plugin path and high-rate event recursion. Approval requires no known HIGH/CRITICAL regressions.
