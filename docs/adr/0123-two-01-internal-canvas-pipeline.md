# ADR-0123 — Bounded internal 2D canvas and sprite metadata planning

**Status:** `APPROVED FOR INTERNAL LOGICAL PIPELINE ONLY` — owner-authorized continuation, 2026-11-23. **Keeps:** [ADR-0022](0022-two-01-native-2d-renderer-policy.md) as planning-only context.

## Context

GFX-08 completed its internal sequence as `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`. TWO-01 research, architecture and ADR-0022 exist, but no native 2D renderer, GPU upload, sprite draw, atlas, text, vector tessellation, lighting or hardware qualification is authorized. A fail-closed logical layer is required before any backend work.

## Decision

Ratify a first TWO-01 internal pipeline that validates and plans metadata only:

1. **Sprites.** Stable sprite/asset IDs and revisions, source/atlas region, UV bounds, pivot, trim/flip, tint and layer references with finite validation. No sprite instance, buffer or draw is produced.
2. **Atlases.** Atlas ID/revision, region bounds, gutter/edge extrusion, mip policy and UV texel-center metadata with checked arithmetic. No atlas is packed, uploaded or sampled.
3. **Layers.** Stable layer IDs/order, visibility, opacity, blend and clip-depth metadata preserving semantic painter order. No layer is rendered or reordered for batching.
4. **Camera.** Orthographic 2D view metadata: viewport/design pixels, position/zoom, DPI scale, letterbox policy and finite bounds. No projection matrix, GPU view or swapchain is created.
5. **Pixel snapping.** Integer/continuous sampling policy, nearest/smooth filtering declaration and snap offset metadata for pixel-perfect and high-DPI modes. No pixel is sampled.
6. **2D lights.** Typed light requests with bounded intensity/radius/color/layer references for the GFX-06-owned lighting path. No light, shadow, normal map or scissor mask is created.
7. **Boundaries.** DATA-02/03/04/05 own asset identity/import/authoring/cook; GFX-01 device/presentation; GFX-02 shaders; GFX-03 resources/fences; GFX-05 textures/materials; GFX-06 lighting; GFX-07 output/post. TWO-01 owns only logical canvas/effect plans.

## Non-decisions

- No Vulkan/D3D12/Metal/WebGPU, swapchain, GPU buffer, texture upload, sampler, draw call or fence.
- No sprite/atlas/vector/text rendering, tessellation, glyph shaping, font rasterization, MSDF or text layout.
- No ThorVG/Skia/Blend2D/lyon/Rive/HarfBuzz/FreeType/msdfgen integration.
- No 2D lighting, shadows, normal maps, clipping execution or batching.
- No visual golden, 60 FPS, hardware, driver, DPI, VRAM or performance qualification.
- No public ABI, release class beyond `INTERNAL_ONLY`, engine license decision or production-readiness claim.

## Ownership

- TWO-01 owns logical canvas sprite/atlas/layer/camera/snap/light plans and their typed fallback metadata.
- It does not own devices, shaders, GPU resources, render passes, materials, lighting, post-processing, durable assets or gameplay state.
- Painter order is semantic and must never be reordered for batching in this logical layer.

## Consequences

- The layer is deterministic and testable on every CI platform without a GPU, font engine or image codec.
- Any future 2D renderer, text/vector path, atlas upload, lighting or visual comparison requires a new owner-approved contract/slice and platform evidence.
- ADR-0022 remains planning context; this ADR neither ratifies its renderer/text/vendor decisions nor selects any dependency.

## Evidence gates

Contract `TWO-01-02`, six implementation slices `-03`..`-08`, qualification `-09`, closeout `-10`, exact-head native CI and pt-BR audit. Stop on stale source, native GPU/vector/text/SDK selection, released ABI or HIGH/CRITICAL.
