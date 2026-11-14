# GFX-06 — Future Correctness, Performance and Security Test Matrix

**WO:** NLE-P00-WO-002-GFX-06 | Research #138 | Future code #34 BLOCKED.  
**All 68 cases are FUTURE NOT EXECUTED**: no GPU build, C++ tests, benchmarks or screenshots have been produced. Each test needs exact dataset/rights/golden reference, numeric tolerances, OS/browser/hardware, driver, shader/backend, command and expected output when implementation activation is approved.

| ID | Required future proof | Surface |
|---|---|---|
| LGT-001 | DIRECTIONAL lux vs direct numerical model | CPU reference |
| LGT-002 | POINT candela inverse square with finite source radius | CPU numeric |
| LGT-003 | SPOT angular cutoff and invalid angle rejection | CPU/unit |
| LGT-004 | Area light size influence and energy bounds | CPU/golden |
| LGT-005 | NaN/Inf/negative brightness, transform rejected | fuzz |
| LGT-006 | Color linear/scene HDR integration GFX-05/07 | golden |
| LGT-007 | Light channel masks and 2.5D layer selection | 2D/3D scene |
| LGT-008 | Dynamic create/destroy 100 spell lights without ghosting | ARPG stress |
| LGT-009 | Sorted many-light cluster list and deterministic error | unit |
| LGT-010 | Cluster index overflow, prefix sum bounds and fallback | fuzz |
| LGT-011 | Compute feature absent -> CPU/forward fallback | Web/low-end |
| LGT-012 | Many moving spot lights shadow cap receipts | stress |
| SHD-001 | CSM cascade split and stable texel snapping | camera oracle |
| SHD-002 | Reversed-Z depth and near/far conventions | native/Web |
| SHD-003 | Shadow bias acne/peter-panning regression | image goldens |
| SHD-004 | Cascade transition visible seam/flicker | motion sequence |
| SHD-005 | Spot atlas and point cubemap face seam | goldens |
| SHD-006 | Opaque vs alpha MASK foliage caster preservation | GFX-04/05 |
| SHD-007 | Transparent/transmission behavior documented | material |
| SHD-008 | Skinned mesh animated bounds & shadows | animated |
| SHD-009 | WPO/morph invalidation and no stale shadows | stress |
| SHD-010 | Screen-space contact shadows offscreen fallback | oracle |
| SHD-011 | PCSS penumbra quality and sample budget | GPU |
| SHD-012 | Variance/EVSM light leaking vs PCF reference | golden |
| SHD-013 | Virtual shadow page missing -> coarse fallback | fault injection |
| SHD-014 | Virtual shadow pool overcommit -> no corruption | fault injection |
| SHD-015 | Moving light invalidates cache & generations | GPU |
| SHD-016 | Camera cut, teleport, FOV, origin rebase invalidation | GPU |
| SHD-017 | LODs/streaming chunk invalidation under shadows | DATA-05 |
| SHD-018 | Device loss & alias/frames-in-flight fences | GFX-03 |
| GI-001 | IBL/probe lighting stable under missing bake | low-end |
| GI-002 | Incorrect/stale lightmap version rejection | DATA-05 |
| GI-003 | Probe relocation avoids wall/door light leak | golden |
| GI-004 | SSGI visible-only vs offscreen fallback | golden |
| GI-005 | Radiance Cascades 2D immediate on/off light | 2D golden |
| GI-006 | Radiance Cascades 2D contact and penumbra | 2D golden |
| GI-007 | Radiance Cascades 2.5D layer and camera | 2.5D |
| GI-008 | Radiance Cascades 3D EXPERIMENTAL perspective test | A/B hypothesis |
| GI-009 | SDF sparse GI animated emitter / occluder missing | fault |
| GI-010 | Brixelizer native DX12/Vulkan and no Mac/Web claim | platform |
| GI-011 | GI many lights multi-bounce color bleeding | offline reference |
| GI-012 | GI frame responsiveness / temporal ghosting | ARPG stress |
| GI-013 | RT available/unavailable mode parity with explicit loss | native |
| GI-014 | ReSTIR optional reference has bounded ray count | R&D |
| REF-001 | IBL + SSR mirror offscreen miss declared | golden |
| REF-002 | Rough gloss with optional RT vs SSR baseline | golden |
| REF-003 | Metallic/dielectric GFX-05 BRDF conservation | numeric |
| REF-004 | Transmission/refraction not silently equated alpha | golden |
| VOL-001 | Fog scattering/extinction numerical bounds | unit |
| VOL-002 | Froxel fog light shafts compared analytic fallback | golden |
| VOL-003 | Volume history resets on camera cut and lost GPU | fault |
| VOL-004 | Particles emissive flood cannot allocate unbounded lights | GFX-08 |
| TWO-001 | 2D normal mapped sprite with moving light | 2D |
| TWO-002 | 2.5D parallax layered cast and receiver mask | 2.5D |
| TWO-003 | WebGL2 no-compute light/shadow fallback | browser |
| PLT-001 | Win Vulkan / D3D12 adapter feature and real GPU capture | native |
| PLT-002 | Linux Vulkan real capture and shader validation | native |
| PLT-003 | macOS Apple Silicon Metal fallback and ray feature probe | native |
| PLT-004 | WebGPU browser WGSL limits and no RT presumption | browser |
| PLT-005 | WebGL2 reduced tier shadow sampler behavior | browser |
| PLT-006 | Hardware RT AS and alpha culling failure path | native |
| SEC-001 | MCP project/role/revision/batch quota bypass rejected | security |
| SEC-002 | Malicious IES/cookie/probe input sandbox rights | fuzz |
| SEC-003 | RTXDI/RTXGI proprietary license flagged; SBOM | license |
| BEN-001 | P50/P95/P99 direct/shadow/GI/volume/total and VRAM | hardware |
| BEN-002 | Unreal reference: comparable-scene quality/perf disclosure | benchmark |
| BEN-003 | GGG Radiance Cascades screen-space/2D comparison | benchmark |
| BEN-004 | SLRG vs static budget PROVE-OR-DROP | benchmark |

## Mandatory future acceptance matrix
- Fixed rights-cleared scenes: Cornell-box-like calibrated reference with own geometry/permission, day-night outdoor sun+CSM, reflective room/metallic materials, fog shafts, planar 2D, layered 2.5D, streaming large world, ARPG spell barrage (multiple dynamic emitters, foliage, skinned mobs).
- Freeze camera path, resolutions, render scale/upscaler, light values/units, scene camera cuts and occluder epochs. Score **temporal** ghosting/disocclusion, page pool/cache eviction, visual image difference against independent offline/analytic reference and fidelity of low-end fallback.
- Real p50/p95/p99 CPU/GPU pass timing, integrated frame-time, VRAM/UMA/unknown-source, shader compile costs and power/thermal where available. No benchmark result can be inferred from a document or from marketing numbers.
- Golden image metrics include approved HDR-linear error, perceptual/SSIM or equivalent where meaningful plus silhouettes, depth/shadow coverage, response frames to a destroyed light and color bleeding; thresholds are **TBD BY OWNER BEFORE CODING**.
- Windows Vulkan/DX12, Linux Vulkan, macOS Metal Apple Silicon, browsers WebGPU and WebGL2 with tested adapters; missing hardware is BLOCKED evidence, not PASS. Document fallback and headless-only smoke separately.
- Security fuzz light/probe/IES asset decoding, integer overflow and index, shader layout mismatch, native GPU-device loss, content rights/SBOM and authorized semantic MCP edits.
