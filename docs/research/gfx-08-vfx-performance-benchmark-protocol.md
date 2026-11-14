# GFX-08 — Reproducible ARPG VFX Visual and Cost Benchmark Protocol

**Research #144** | NLE-P00-WO-002-GFX-08 | PROPOSED ONLY, **NONE RUN**.

## Comparison tracks
1. **Deterministic graph and simulation reference**: same seed/tick, one-shot burst, long running emitter, cancellations, subemit recursive attack, trail/ribbon degenerate cases. Headless CPU simulation against mathematical bounds/golden counters; GPU probability/distribution visual tolerance, no requirement bit-exact floating point GPU cross-device.
2. **Equivalent VFX art scene**: self-created rights-cleared 2D, 2.5D and 3D spawns, color/alpha/lights/volumetric assets with matching camera/exposure/shadow and equal output/render resolutions, materials and effect lifetime. Unrelated gameplay frame rate must not be used to claim Stormline VFX superiority.
3. **ARPG spell storm**: preset bursts (1, 10, 100, 1000 emitters as *test workload*, not product commitment), multi-stage explosion with tiny sparks + huge transparent cloud, mesh/ribbon + GFX-06 bounded light requests, motion VFX reactive masks and GFX-07 HDR/exposure. Score animation clarity/camera speed and occluded particles.
4. **Adversarial cases**: VRAM pressure/rapid scene unload/device loss, full-screen transparent overdraw, alpha sort intersection, tail near camera, graph > quotas, WebGL2 no compute, low-power integrated GPU; compare correct degraded rendering not crashes or hidden vital gameplay telegraphs.
5. **Competitor reference**: Niagara scalability GPU/CPU and Godot particle path are design baselines. Comparison with Path of Exile 2 only using public, lawful visual reference and independently authored matched workload, no game shader/code/art extraction, anti-cheat or EULA bypass. Mark non-comparable internals as NON-COMPARABLE, not Stormline win.

## Fixed evidence controls
- For all runs capture exact hardware GPU/CPU/driver/OS and render backend, monitor, resolution/render scale/frame cap/vsync/AA, graphics/texture/lighting/profile, asset hash and licenses, seed/camera path, test count and warm-up duration. Record shader compile/startup vs steady state separately.
- Per-effect and scene `CPU spawn/update/submit`, `GPU simulation/compaction/sort/draw`, alpha coverage and overdraw, GFX-06 light cost, GFX-07 reactive mask cost, VRAM resident bytes vs inferred/UNKNOWN. p50/p95/p99 and full frame time with confidence if multiple runs; frame pacing/tails and crash count.
- Compare visual quality at same budget and GPU cost at same perceptually accepted quality (Pareto frontier). **Particles/second or 1000k count alone are not quality**; screen coverage, opacity, light response and telegraph readability must be scored. Claim “better” only if controlled rights-cleared scene parity, comparable settings and independent images/logs on at least two hardware classes with approved numeric acceptance.
- SVAG hypothesis PROVE-OR-DROP if flicker, adaptation overhead, unrecoverable visual loss or cross-tier portability regressions occur vs static tiers/area heuristics. Every selected degrade recorded.
- All figures and screenshots in this protocol are proposed outputs; **zero captured data, zero tests executed**.

## Primary references and upstream licensing evidence
- Epic Niagara scalability and GPU/CPU budget caveats: https://dev.epicgames.com/documentation/en-us/unreal-engine/scalability-and-best-practices-for-niagara
- Godot stable GPU/CPU particles (independent reference): https://docs.godotengine.org/en/stable/tutorials/3d/particles/index.html
- Godot GPUParticles3D trails and restart semantics: https://docs.godotengine.org/en/stable/classes/class_gpuparticles3d.html
- Effekseer MIT runtime code: https://github.com/effekseer/Effekseer/blob/master/LICENSE
- Effekseer Tool runtime/backend license notices: https://effekseer.github.io/Help_Tool/en/overview.html
- Effekseer platform and source compatibility: https://github.com/effekseer/Effekseer
- AMD GPUOpen FidelityFX Parallel Sort (MIT DX12/Vulkan): https://gpuopen.com/fidelityfx-parallel-sort/
- AMD FidelityFX Parallel Sort documentation: https://gpuopen.com/manuals/fidelityfx_sdk/techniques/parallel-sort/
- OpenVDB Apache-2.0 current upstream LICENSE: https://github.com/AcademySoftwareFoundation/openvdb/blob/master/LICENSE
- W3C WebGPU GPU compute/capability standard: https://www.w3.org/TR/webgpu/
