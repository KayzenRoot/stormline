# ADR-0130 — Internal logical terrain and environment metadata pipeline

**Status: APPROVED for bounded internal logical metadata only.** **Date:** 2026-11-24. **Module:** `WORLD-04` — Terrain & Environment. **Issue:** #44. **Keeps planning-only:** [ADR-0029](0029-world-04-authored-terrain-environment-visual-ownership.md), which remains `PROPOSED / NOT APPROVED FOR ENGINE CODE`.

## Context

WORLD-04 must eventually provide authorable multi-biome terrain, splat/material masks, vegetation placement, water, sky and weather intent without duplicating rendering, physics, streaming, persistence or simulation owners. The full problem includes heightfield storage, GPU geometry, textures, atmosphere rendering, physics collision, weather authority and original-asset benchmarks. Those runtime capabilities are not qualified and must not be claimed.

The module's formal predecessors, WORLD-03 and GFX-04, have completed their internal sequences and are available as capability sources. Their status is `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`.

## Decision

Approve a bounded internal sequence that produces **logical terrain/environment metadata only** under `src/stormline/terrain/`:

1. Terrain patch identity, signed tile coordinates, LOD/neighborhood and revision intent metadata.
2. Splat/material weight layer metadata with bounded normalized channel descriptors; no texture residency.
3. Vegetation placement group metadata with stable instance identity and density bounds.
4. Water body and shoreline intent metadata; no simulation or surface rendering.
5. Sky/environment profile metadata with finite visual parameters; no atmospheric renderer.
6. Weather visual intent metadata with authoritative source tick acknowledgement; no climate simulation.
7. Integrated deterministic, failure-recovery and bounded-overload qualification.

The sequence must not create heightfield storage, mesh generation, terrain rendering, texture sampling, vegetation instancing, water simulation, atmosphere rendering, weather simulation, physics colliders, editor UI or public ABI. GFX-04 owns geometry/LOD/visibility, GFX-05/06/07/08 own materials/lighting/post/VFX, WORLD-03 owns cells/origin/streaming intent, DATA-04/05 own persistence/cook/streaming, PHYS/GAME/NET own simulation and authority.

## Ownership and boundaries

| Concern | Authority | WORLD-04 may produce |
|---|---|---|
| Scene/prefab source | WORLD-02 | opaque terrain asset and patch references |
| Spatial cells, origin, streaming | WORLD-03 | cell-relative patch intent metadata |
| Geometry, LOD, visibility, instancing | GFX-04 | patch/vegetation hints only |
| Materials, textures, alpha | GFX-05 | bounded weight/layer descriptors |
| Sky light, fog, atmosphere | GFX-06 | authored profile parameters |
| HDR, post, color | GFX-07 | quality intents only |
| Weather VFX | GFX-08 | precipitation/weather visual intents |
| Persistence, cook, streaming I/O | DATA-04/05 | source revisions and receipts |
| Physics, gameplay, network authority | PHYS/GAME/NET | ack placeholders; no truth |
| Coordinate math | CORE-05 | checked tile coordinates; no transforms |

## Risk and release class

- Planning risk: `LOW` for documentation and logical metadata.
- Future runtime terrain/environment risk: `ELEVATED`, explicitly out of scope for this sequence.
- Release class: `INTERNAL_ONLY`. No public ABI, release, hardware, performance, security or production-readiness claim.

## Rejected alternatives

- Implementing terrain rendering or GPU LOD in this sequence; rejected because GFX-04 owns geometry and ADR-0029's proof obligations are not executed.
- Treating a heightfield as complete topology for caves/overhangs; rejected because distinct mesh surfaces are required.
- Owning texture residency or shader blending; rejected because GFX-05/07 own materials and color.
- Owning weather truth or water physics; rejected because GAME/NET/PHYS own authority.
- Approving ADR-0029 wholesale for engine code; rejected because its runtime proof obligations are not executed.

## Consequences

- Slice `-02` must freeze an exact header-only logical API, allowlist and test oracles before any code.
- Each implementation slice requires its own G6 activation gate.
- The module can close as `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`; it cannot claim terrain rendering, biome traversal or performance readiness.
- Any future runtime terrain/environment implementation requires a new owner-approved decision that resolves ADR-0029's proof obligations.
