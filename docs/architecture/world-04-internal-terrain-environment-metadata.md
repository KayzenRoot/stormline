# WORLD-04 — Internal logical terrain/environment metadata

**Status:** `APPROVED INTERNAL ARCHITECTURE / LOGICAL METADATA ONLY`. **ADR:** [ADR-0130](../adr/0130-world-04-internal-terrain-environment-metadata.md). **Planning policy remains:** [ADR-0029](../adr/0029-world-04-authored-terrain-environment-visual-ownership.md) `PROPOSED`. **Runtime terrain/environment claims:** none.

## 1. Purpose

Define a bounded, deterministic metadata layer for terrain patches, splat/material layers, vegetation placement, water bodies, sky profiles and weather visual intents. It answers what a world authored and requested, not how heights are stored, meshes are built, textures are sampled, water is simulated or weather is rendered.

## 2. Logical model

- **Terrain patch intent:** stable patch identity, signed tile coordinates, LOD level, neighbor references and source revision.
- **Splat layer intent:** bounded normalized channel weights, material asset references and layer precedence metadata.
- **Vegetation intent:** stable group/instance identity, prototype asset references, bounded density and collider declarations.
- **Water intent:** stable body identity, class, finite region/shore metadata and visual wave parameters.
- **Sky intent:** authored time-of-day, finite sun/moon direction, cloud/fog ranges and quality tier metadata.
- **Weather intent:** authoritative source tick/revision, finite precipitation/wind intensities and target visual systems.
- **Diagnostics:** typed error plus source ID and index; outputs reset on failure.

## 3. Runtime non-goals

No heightfield or mesh storage, mesh generation, terrain renderer, GPU LOD, splat texture residency, vegetation instancing, water simulation or rendering, atmosphere renderer, weather simulation, physics collider, editor UI, I/O, decode, cache or public ABI. Those remain future decisions under ADR-0029 and other module owners.

## 4. Ownership boundaries

- WORLD-02/03 own scene identity and spatial/streaming intent; WORLD-01 entity lifecycle.
- GFX-04 owns geometry/LOD/visibility; GFX-05/06/07/08 own materials, lighting, post and VFX.
- DATA-04/05 own persistence, cook, streaming I/O and decoded assets.
- CORE-05 owns coordinate math; CORE-03/06 own scheduling and fixed tick.
- PHYS/GAME/NET own collision, simulation and authority.
- WORLD-04 owns only logical terrain/environment intent metadata.

## 5. Determinism and bounds

All plans are fixed-capacity, header-only, `noexcept` and allocation-free. Capacities are frozen in `-02`; validation and overload behavior must be deterministic across compilers. No clock, random source, file, network, audio, GPU, thread, RTTI hash or global state is allowed.

## 6. Planned slices

| Slice | Logical deliverable | Oracle |
|---|---|---|
| `-03` | terrain patch metadata | TER-01 |
| `-04` | splat/material layer metadata | SPL-01 |
| `-05` | vegetation placement metadata | VEG-01 |
| `-06` | water body metadata | WAT-01 |
| `-07` | sky/environment profile metadata | SKY-01 |
| `-08` | weather visual intent metadata | CLI-01 |
| `-09` | integrated qualification | QLF-W401..W404 |
| `-10` | closeout | evidence/audit |

`-02` must freeze exact types, capacities, error codes, allowlists and test fixtures before `-03` is activated.

## 7. Explicit non-goals

No heightfield/mesh storage, terrain or water rendering, GPU geometry/LOD, texture residency, vegetation instancing, atmosphere/weather simulation, physics collision, benchmark, hardware measurement or public ABI. ADR-0029 remains the separate planning authority for those future runtime decisions.
