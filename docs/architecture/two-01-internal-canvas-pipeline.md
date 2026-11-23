# TWO-01 internal 2D canvas and sprite metadata pipeline (INTERNAL_ONLY)

**Status:** `PROPOSED LOGICAL ARCHITECTURE / NO GPU / NO RENDER / NO TEXT`. **ADR:** [ADR-0123](../adr/0123-two-01-internal-canvas-pipeline.md). **Governance:** [two-01-governance-v0](../contracts/two-01-governance-v0.md). **Queue:** `NLE-PRPLAN-TWO-01-01`.

## 1. Purpose

Describe the bounded logical model TWO-01 will implement before any 2D renderer, atlas upload, text/vector path or visual work. It validates canvas metadata, derives deterministic plans and reports typed fallback/degradation reasons. It does not draw a sprite or produce an image.

## 2. Modules and boundaries

- **TWO-01** owns logical sprite, atlas, layer, camera, pixel-snap and 2D-light request plans.
- **GFX-01** owns device/presentation; **GFX-02** shaders; **GFX-03** resources/fences; **GFX-05** textures/materials; **GFX-06** lighting; **GFX-07** output/post.
- **DATA-02/03/04/05** own asset identity, import, durable authoring and cook receipts.
- **TWO-02/03/04** own tilemaps, animation and hybrid 2.5D in later modules.

No dependency is added to a native graphics API, text/font engine, vector library, atlas cooker, codec or hardware driver.

## 3. Logical model

### 3.1 Sprite draw metadata

- Sprite/asset ID and revision nonzero; source atlas region and UV bounds finite.
- Pivot, trim/flip, tint and layer references validated; unknown layers fail closed.
- No instance, vertex, buffer or draw is created.

### 3.2 Atlas metadata

- Atlas ID/revision, region bounds inside declared atlas size, nonnegative gutter and mip count.
- UV texel-center and checked region arithmetic; overlap/duplicate IDs fail closed.
- No atlas is packed, uploaded or sampled.

### 3.3 Layers

- Stable layer ID/order, visibility, opacity, blend and clip-depth metadata.
- Duplicate IDs and order conflicts fail closed; declared painter order is preserved exactly.
- No layer is composited, sorted or reordered for batching.

### 3.4 Camera

- Orthographic viewport/design pixels, position, zoom, DPI scale and letterbox metadata.
- Finite positive viewport, zoom and DPI; invalid combinations fail closed.
- No projection matrix, GPU view or swapchain is created.

### 3.5 Pixel snapping

- Integer snap vs continuous mode, nearest/smooth declaration and snap offsets.
- Non-integer scale in integer mode degrades explicitly; invalid offsets fail closed.
- No pixel is sampled or snapped in an image.

### 3.6 2D light requests

- Typed light ID/revision, intensity/radius/color, layer and falloff metadata for GFX-06.
- Finite nonnegative intensity/radius and bounded color; over-budget requests degrade with a receipt.
- No light, shadow, normal map or scissor mask is created.

## 4. Determinism and failure

- All plans are pure functions of validated inputs; stable IDs and declared order determine output.
- Errors are typed and fail closed; partial plans are not emitted.
- Stale asset revisions, atlas generations and layer/clip conflicts select a declared safe path rather than stale metadata.
- No allocation, exception, file, network, GPU, thread or global state in the internal implementation.

## 5. Test strategy

- Unit oracles for sprites, atlases, layers, camera, pixel snapping and light requests.
- Integrated qualification QLF-T101..T104: valid pipeline, deterministic repeat, failure recovery and 10,000 bounded attempts.
- Native CI on Linux/ASan/UBSan/TSan/Windows/macOS; no renderer, text, GPU or visual assertion.

## 6. Explicit non-goals

- No GPU renderer, swapchain, shader, buffer, texture upload or draw.
- No atlas packing/upload, sprite batching, clipping execution or compositing.
- No text shaping, font rasterization, vector tessellation or SVG/Rive import.
- No 2D lighting/shadow/normal-map execution.
- No hardware, DPI, 60 FPS or visual qualification.
- No public ABI, release or production readiness.

## 7. Failure and stop conditions

Stop on stale source, attempted native GPU/text/vector/SDK selection, painter-order violation, unbounded geometry, failed tests, HIGH/CRITICAL findings or any release/ABI claim.
