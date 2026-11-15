# ADR-0039 — Engine-owned Acoustic Scene Authority with Binaural & Propagation Tiering

**STATUS: PROPOSED / NOT APPROVED FOR CODE**  
2026-11-14 | Research issue #198 | WO NLE-P00-WO-002-AUD-02 | Future coding issue #53 OPEN/BLOCKED.

## Context and problem
The user wants rich 3D/2D/2.5D spatialization, HRTF, audible object occlusion, reflections and room response, but Stormline has no executable engine, AUD-01 mixer, WORLD-02 scene or physics. Steam Audio/other middleware offers features but may own mixing, ray tracing, audio processing and native lifetimes. Blindly plugging it into AUD-01 might double-process sources, block realtime threads, break streaming cell epochs or expose hidden world details. HRTF/HDF5 datasets have independent rights and potentially sensitive personal profile data.

## Proposed decision (none adopted)
1. **Stormline-owned typed spatial SDK:** AcousticWorld, ListenerHandle, SpatialSourceHandle, acoustic surfaces/materials, Room/Portal graph, source geometry revision, acoustic query/update state, HRTFProfile/OutputLayout, AcousticRenderPlan and measurement receipts. No vendor IPL/AL/Embree native pointers/types in stable public API.
2. **One AUD-01 voice/mixer/output authority:** only AUD-01 owns audio device, voice scheduling/virtualization, bus and sample-frame clock. AUD-02 supplies safe preallocated, bounded spatial processing plans for AUD-01 audio frames. Real-time callback cannot perform scene raycasts, HRTF file/IR parsing, DSP graph compilation, memory allocation, blocking synchronization, network or file I/O.
3. **WORLD-02/03/04 source authority:** use scene/prefab EntityGuid+source generation, World/Cell/Origin epochs/leases and acoustically annotated geometry/material/door/room sources. AUD-02 consumes immutable snapshots and versioned derived acoustic geometry; GFX culling meshes and SIM-02 colliders are **not** automatically acoustically identical or complete.
4. **Tiered output:** base direct attenuation + speaker panning/mono/headless, optional headphone HRTF using rights-validated SOFA profile, then bounded occlusion/transmission, early reflections/rooms/late reverb and optional cooked multi-path propagation/Ambisonics. Graphics tier cannot change authoritative gameplay events. Personalized HRTF and spatial perception features require separate consent/capability.
5. **Non-RT propagation jobs with safe publication:** CORE-03 bounded ray/path/geometry/probe work off audio callback, DATA-05 owned verified bake/package, WORLD-03 leases/stale revision cancellation, atomic AcousticRenderPlan swap and deferred retention. Unloaded/unknown world returns `GEOMETRY_UNREADY` with explicit last verified/fallback, never lies that a missing wall is empty space.
6. **Candidate technology matrix, no SDK adoption:** Steam Audio Apache-2.0 is **leading functional reference/private-adapter candidate** for HRTF, SOFA, raycast occlusion, reflections and pathing. libmysofa BSD-3-Clause candidate for SOFA loading; HRTF **datasets individually licensed**. Intel Embree Apache-2.0 optional ray intersection *not a propagation engine*. Resonance Audio Apache-2.0 source archived since Nov 2023, reference-only. OpenAL Soft LGPL-2.0-or-later has a separate default HRTF dataset Apache-2.0, alternative comparator with legal/duplicate mixer risk. Project Acoustics archived public repo: separate MIT code/docs CC BY 4.0, proprietary integration/runtime license NOT ASSUMED. NLE-D009 engine license remains OPEN.
7. **Security/rights/privacy:** source/life/generation role checks; bounds on geometry/HDF5/SOFA, samples, IR duration, rays, jobs, memory, source count, CPU budgets; zero raw hidden NPC/position leak or unauthorized MCP room source read; future fuzz/sanitizers and GDPR/LGPD-like personal-data consent for individualized datasets. Acoustic output doesn't decide GAME perception/stealth/hit validation or server policy.
8. **Benchmark-gated code and portability:** optional GPU effects never mandatory/headless, native Win/Linux/macOS/Web support only after runtime proof with matched PCM/scene original fixtures. No universal binaural localization, hearing safety, perfect diffraction, bit-exact cross-OS PCM or AAA superiority promise.

## Rejected alternatives
- Second PCM mixer/device stack under Steam Audio/OpenAL Soft, or ray tracing/geometry baking in audio callback.
- Renderer visibility or unloaded PHYS collision cache falsely authoritative for transmission/occlusion; acoustics must carry own revision/coverage.
- Treating SOFA as granting rights to all HRTF datasets; bundling user head/ear scans by default.
- Mandatory GPU ray tracing, closed paid spatial middleware, globally persistent unlimited impulse responses or unbounded source paths.
- Declaring OpenAL Soft LGPL or archived Resonance/Project Acoustics equivalent to permissive embedded commercial source without audit.
- Claiming source's audio audible means AI/GAME can perceive/attack it; GAME controls gameplay semantics.
- Activating coding issue #53 from research ADR PROPOSED.

## Consequences, approval and stop
Chosen design increases adapter, room graph, scene-bake and clock/epoch complexity but protects mixer realtime budget, portable output, game authority and licensed data. Before coding require upstream AUD-01/WORLD-02 implementability, exact pinned vendor licenses/SBOM and HRTF/IR dataset rights, a small NECESSARY first slice, CPU/headless/Win/Linux/macOS/Web capability trials, numerical/perceptual benchmarks, rollback/stream/ownership tests and objective risk review. **No implementation, adopted SDK, measured fidelity or executable engine currently exists. All 80 coding work orders remain BLOCKED; #53 OPEN/BLOCKED.**
