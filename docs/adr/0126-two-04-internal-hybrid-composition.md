# ADR-0126 — Internal logical 2.5D hybrid composition pipeline

**Status: APPROVED for bounded internal logical metadata only.** **Date:** 2026-11-24. **Module:** `TWO-04` — 2.5D Hybrid Composition. **Issue:** #40. **Supersedes for implementation:** none. **Keeps planning-only:** [ADR-0025](0025-two-04-depth-order-hybrid-composition-policy.md), which remains `PROPOSED / NOT APPROVED FOR ENGINE CODE`.

## Context

TWO-04 must eventually let projects mix 2D sprites/Canvas layers with 3D meshes while preserving explicit order, depth intent and lighting ownership. The full problem spans GPU depth attachments, alpha policy, camera projection, subviews, lighting and temporal history. Those runtime capabilities are not yet qualified and must not be claimed by documentation.

The module's formal predecessors, TWO-01 and GFX-04, have completed their internal sequences and are available as capability sources. Their status is `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`; completion of logical metadata does not qualify rendering.

## Decision

Approve a bounded internal sequence that produces **logical composition metadata only** under `src/stormline/hybrid/`:

1. Camera projection intent metadata (orthographic/perspective, finite parameters, validated ranges).
2. 2D/3D layer intent metadata (composition mode, stable order, depth test/write intent, alpha policy).
3. Deterministic sorting intent metadata over bounded layers/objects.
4. Hybrid effect bridge metadata (lit/unlit intent, shadow proxy intent, subview bounds and fallback receipts).

The sequence must not create a renderer, camera matrix evaluator, GPU resource, depth attachment, shader, draw call, subview execution, lighting evaluation or frame composition. GFX-01/03/04/05/06/07 remain the authorities for any future rendering behavior; TWO-01 remains the Canvas painter authority; ADR-0025 remains the planning authority for the full runtime policy.

## Ownership and boundaries

| Concern | Authority | TWO-04 may produce |
|---|---|---|
| Camera matrices, views, HDR/AA/output | GFX-07 | logical projection intent and validation receipts |
| Depth/stencil attachments, render graph, hazards | GFX-03 | depth policy intent metadata |
| 3D meshes, culling, bounds | GFX-04 | opaque references and sort intents |
| Materials, alpha modes, color space | GFX-05 | alpha/depth policy intent |
| Lighting, shadows | GFX-06 | lit/unlit and proxy intent metadata |
| Canvas painter order, sprites, DPI | TWO-01 | explicit layer order and mode intent |
| Animation, tilemaps | TWO-03, TWO-02 | opaque references only |
| Scene assets, revisions, transactions | DATA-04 | referenced IDs and revisions |
| Physics/collision/gameplay truth | PHYS/WORLD | none; visual metadata is not collision truth |

## Risk and release class

- Planning risk: `LOW` for documentation and logical metadata.
- Future runtime rendering risk: `ELEVATED`, explicitly out of scope for this sequence.
- Release class: `INTERNAL_ONLY`. No public ABI, release, hardware, performance, visual, security or production-readiness claim.

## Rejected alternatives

- Implementing GPU depth/stencil or a render graph inside TWO-04; rejected because GFX-03 owns it.
- Evaluating projection matrices or camera transforms in TWO-04; rejected because GFX-07/CORE-05 own math.
- Treating painter order and world depth as one implicit scalar; rejected because it hides occlusion-mode ambiguity.
- Approving ADR-0025 wholesale for engine code; rejected because its runtime proof obligations are not executed.

## Consequences

- Slice `-02` must freeze an exact header-only logical API, allowlist and test oracles before any code.
- Each implementation slice requires its own G6 activation gate.
- The module can close as `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`; it cannot claim renderer readiness.
- Any future runtime implementation requires a new owner-approved decision that resolves ADR-0025's proof obligations.
