# GFX-06 — Reproducible Lighting Quality / Performance Competition Protocol

**Status:** PROPOSED, research only. **No comparison executed; no superiority claim established.**  
**Comparator candidates:** Unreal Lumen/Virtual Shadow Maps, GGG Path of Exile 2 Radiance Cascades, independent offline/raster reference, portable Stormline baseline and optional Stormline hybrid tiers.

## Disentangle incomparable benchmarks
- Unreal is a general-purpose engine with Lumen lighting/reflections and virtual paged shadows. GGG game renderer optimizes a narrower ARPG camera/content; same-looking screenshot is not equal scene geometry, visibility, illumination or cost.
- **Two test tracks:** (A) *algorithmic apples-to-apples* common authored original scene import/export and matching camera/material/lights/quality, comparing direct/shadow/GI passes; (B) *real-player ARPG workload* matched action/particle/light counts and perceived quality, with honest reporting of differences/unavailable internals. An in-game FPS comparison alone is never proof of GI superiority.
- Radiance Cascades 2D(screen-space) and 3D full-world methods should never be treated as directly equivalent. Validate 2D/2.5D reactive performance separately from 3D perspective/open-world.
- No proprietary Unreal, GGG game code/shaders/assets copied; use independently created rights-cleared scenes and publicly available references. No violating game EULA, anti-cheat, reverse engineering or telemetry capture.

## Mandatory fixture suites (all future)
| Fixture | Conditions | Primary metrics / failure |
|---|---|---|
| Calibrated room/materials | known luminaires, BRDF, occluders, reference path tracing | radiance/delta, reflection and shadow fidelity |
| Dynamic ARPG arena | 1/10/100+ light-casting spells as **test loads not product promises**, moving agents/foliage | frame p50/p95/p99, light response frames, ghosting/overdraw |
| Outdoor world | kilometer-scale coordinates, moving sun, changing weather, foliage | stable cascade, VRAM cache churn, shadows after rebase |
| Multi-room offscreen | occluder and light out-of-view, emissive reflected into view | screen-space missed illumination, light leaks |
| Alpha foliage/animated | skinned actors, WPO, masked branches and camera motion | temporal invalidation, silhouette omissions |
| 2D/2.5D RC reference | authored 2D occlusion and offscreen light transitions | no temporal ghosts vs radiance cascades |
| Transparent/volumetric | fog shafts, glass and particles | fog scatter and alpha/transmission consistency |
| Extreme VRAM | pages/arrays/rays exceed actual budget, resize/device loss | typed failure, graceful fallback, crash-free |

## Controls and reporting
1. Record OS/build/toolchain/driver/GPU, memory size and power settings; render resolution, scaler mode (including none), AA, settings, frame cap, vsync and measured number of frames/warmup, shader compilation/cache cold vs warm.
2. Report median/p95/p99 GPU pass and full CPU/GPU frame time; VRAM (source KNOWN/ESTIMATED/UNKNOWN), noise/flicker/SSIM/linear HDR/color bleed and screenshots/video only if they actually exist. Provide raw logs, frame captures and reproducibility artifacts.
3. Compare CPU/lighting-only work separately from total engine CPU/render, game sim/network and upscaler latency. Report missing proprietary exact features as **NON-COMPARABLE**, not automatically won.
4. For all gains define Pareto frontier on cost versus quality; a cheaper but blurry/lights-missing renderer isn't a win. Report 95% confidence intervals/multi-run variability when sample size supports; no fabricated significance.
5. **Proposed owner approval gate** for claiming superiority: predefined matched fixtures and quality tolerance, >=2 independent hardware classes including a modest GPU, repeatable runs and no HIGH/CRITICAL, plus explicit third-party mode/version disclosure. Numeric thresholds/target hardware are TBD until version release DoD.
6. Optional SLRG wins only if it beats baseline at comparable approved visual quality and stability with no resource/failure regressions. Otherwise PROVE-OR-DROP.

## No performance fiction
Any “Radiance Cascades costs 1–2ms” quote is speaker/content/hardware-specific and not a Stormline result. Unreal Lumen data and GGG presentations are design references, not controlled independent measurements of Stormline.
