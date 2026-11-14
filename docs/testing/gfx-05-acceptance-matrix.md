# GFX-05 — Future Acceptance Matrix (NOT EXECUTED)

**WO:** NLE-P00-WO-002-GFX-05 | **Research:** #135 | **Code:** #33 BLOCKED.  
All 44 cases below are **future test specifications**. Neither golden pixel comparisons nor codecs, GPU hardware, CI test binaries or performance trials ran in P00. Before executable implementation pin fixtures, golden baseline/CRC, per-test numeric tolerance, approved feature tier, hardware/browser, exact commands and authoritative rights.

| ID | Test contract | Proof surface |
|---|---|---|
| PBR-001 | glTF base metallic-roughness defaults | headless math + real GPU reference |
| PBR-002 | GGX/Smith/Fresnel output finite at grazing angles | CPU numeric/reference |
| PBR-003 | energy conservation roughness/metallic sweep | reference numeric and GPU |
| PBR-004 | sRGB baseColor decoded once | known reference pixel |
| PBR-005 | linear ORM/normal texture never gamma decoded | numeric+GPU |
| PBR-006 | emissive HDR semantics against GFX-07 tonemap boundary | golden |
| PBR-007 | normal tangent handedness and flipped-green provenance | golden |
| PBR-008 | degenerate tangent/NaN material rejected or typed fallback | fuzz/error |
| PBR-009 | roughness/metallic/ior edge values finite and validated | table-driven |
| PBR-010 | KHR clearcoat/sheen independent feature gating | golden |
| PBR-011 | KHR iridescence/anisotropy optional capability fallback | golden |
| PBR-012 | KHR volume/transmission optical vs alpha distinction | reference refraction |
| PBR-013 | unlit stylized/2D sprite unaffected by PBR lighting | 2D/2.5D goldens |
| PBR-014 | MaterialX imported graph round-trip semantic compatibility | offline, if adopted |
| PBR-015 | material graph cycle/size/budget and forbidden node rejected | security |
| PBR-016 | MaterialInstance dynamic edits don't explode GFX-02 variants | compiler integration |
| TEX-017 | KTX2 truncated/corrupt level index and DFD rejected | codec fuzz |
| TEX-018 | decompression bomb/size multiply overflow rejected before GPU | resource safety |
| TEX-019 | ETC1S/UASTC transcode respects target format query | Win/Linux/Mac/Web |
| TEX-020 | BCn/ASTC/ETC2 unavailable -> bounded fallback/typed error | feature tiers |
| TEX-021 | mipmap gamma-correct filtering at gradients | image goldens |
| TEX-022 | normal-map mip renormalization + reduced specular aliasing | image goldens |
| TEX-023 | MASK alpha coverage preserved with mip change | vegetation golden |
| TEX-024 | sampler address/filter/aniso clamps per device | GPU and Web |
| TEX-025 | nonpower-of-two/cube-array/3D texture limits honored | boundary |
| TEX-026 | texture asset move/reimport maintains DATA-02 identity | integration |
| TEX-027 | stale GPU-generation residency receipt refused | GPU recovery |
| TEX-028 | missing chunk and interrupted upload keeps coarse mip | stream fault |
| TEX-029 | GPU fence in flight prevents early eviction/free | GPU sync |
| TEX-030 | residency pressure/cancel honors RAM/VRAM/IO budgets | stress |
| ALP-031 | OPAQUE/MASK/BLEND distinct depth/alpha behavior | golden |
| ALP-032 | sorted alpha order reference / OIT error quantified | golden optional OIT |
| ALP-033 | foliage alpha MASK never trusted as solid occluder | GFX-04 integration |
| ALP-034 | decal normal/depth/overlap/sort limits | golden+stress |
| ALP-035 | transmission multi-layer limitations explicit | reference+receipt |
| SYS-036 | Windows Vulkan/D3D12 shader layout and format probe | real hardware |
| SYS-037 | Linux Vulkan and macOS Metal shader/format probe | real hardware |
| SYS-038 | WebGPU/browser WGSL and WebGL2 reduced contract | browser smoke |
| SYS-039 | 2D 2.5D 3D mixed material scene and target export | integration |
| SYS-040 | rights-cleared fixture attribution/SBOM and KTX ETC exclusion | legal |
| SYS-041 | MCP staged edit rejects scope/role/revision bypass | security |
| SYS-042 | device-loss + hot reload last-good material works | fault injection |
| SYS-043 | actual CPU/GPU p50/p95/p99, overdraw & peak VRAM logged | named GPU benchmark |
| SYS-044 | STAM optional vs ordinary mip streaming prove-or-drop | A/B only if selected |

## Measurement protocol (future)
- Golden scenes with rights-cleared sources: reference Khronos glTF/PBR and explicit fixture licenses, PBR sphere material grid, color checker, normal-tangent mirror, masked foliage, translucent layers, decals, 2D sprites, 2.5D mixed, large textured terrain.
- Compare linear HDR reference under known illuminants with deterministic scene/view/texture inputs before GFX-07 tone mapping; record numeric/SSIM/perceptual metrics **only after thresholds are approved**, and include expected approximation losses for unsupported extension tiers.
- Report p50/p95/p99 frame CPU/GPU, VRAM (actual/estimated source), upload throughput/bytes, peak residency and overdraw for specified resolutions/presets/driver versions; repeat warm/cold/device-loss runs. No unnamed 'AAA FPS' claim.
- Run build + sanitizer/fuzz on host supported CI; run native real Windows/Linux/macOS Apple Silicon and WebGPU/WebGL2 browsers on named devices; recorded unsupported/missing hardware is BLOCKED for that obligation rather than claimed PASS.
- Record mismatch/failure receipt and ensure rollback, error taxonomy and ownership boundaries. `STAM` optional cannot become prerequisite for baseline correctness.
