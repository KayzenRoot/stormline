# GFX-06 internal logical lighting pipeline (INTERNAL_ONLY)

**Status:** `PROPOSED LOGICAL ARCHITECTURE / NO GPU / NO VISUAL QUALIFICATION`. **ADR:** [ADR-0120](../adr/0120-gfx-06-internal-lighting-pipeline.md). **Governance:** [gfx-06-governance-v0](../contracts/gfx-06-governance-v0.md). **Queue:** `NLE-PRPLAN-GFX-06-01`.

## 1. Purpose

Describe the bounded logical model that GFX-06 will implement before any backend, shader or visual work. It validates authored lighting metadata, derives deterministic plans and reports typed fallback/degradation reasons. It does not render light.

## 2. Modules and boundaries

- **GFX-06** owns light definitions, shadow/GI/probe/reflection/volumetric plans and their failure/fallback metadata.
- **DATA-02/04/05** own durable IDs, scene revisions, cooked bakes and stream receipts.
- **GFX-01/02/03** own device capabilities, shaders and graph/resource execution.
- **GFX-04** owns visible casters, LOD and stream generations.
- **GFX-05** owns PBR/alpha semantics.
- **GFX-07** owns exposure/tone mapping/color output.

No dependency is added to a native graphics API, image codec, ray-tracing SDK, vendor SDK, network service or hardware driver.

## 3. Logical model

### 3.1 Light definitions

- Stable `id`, `revision`, declared `LightKind` (directional, point, spot, area rectangle, environment, stylized 2D), finite linear color, finite nonnegative intensity, declared unit, position/direction, range/radius, receiver/channel mask, shadow policy and mobility epoch.
- Fixed capacities and declared units. Unknown kind/unit, zero IDs/revisions, NaN/Inf, negative intensity/attenuation and invalid orientation fail closed.
- Editor-created light identity remains DATA-02/04-authored; GFX-06 never mutates durable identity.

### 3.2 Shadow plan

- Per-light cascade split counts/depths, local shadow request metadata, atlas/page occupancy proposals, filter/bias profiles, generation/epoch and a `coarse_fallback` flag.
- Split distances are finite, positive and strictly increasing; counts are bounded; split weights follow the declared practical split scheme.
- No shadow map, depth texture, PCF kernel, page table, fence or GPU memory object exists.

### 3.3 GI plan

- Declared mode: baked, IBL/environment, logical probe fallback, or unsupported.
- Missing/stale bake returns a typed error or an explicit lower mode; it never silently becomes zero light.
- Dynamic GI, SSGI, DDGI, SDF/voxel caches, Radiance Cascades and ray tracing are not implemented.

### 3.4 Probe volumes

- Bounded probe cells with finite bounds, nonnegative spacing, optional relocation delta and provenance/validity fields.
- Duplicate/unknown IDs, empty bounds, negative spacing and stale scene revisions fail closed.
- No bake, SH evaluation, GPU upload or sampling exists.

### 3.5 Reflection plan

- Probe/environment baseline plus optional logical SSR metadata, material roughness band and explicit offscreen fallback reason.
- A plan never claims that an offscreen reflection was resolved.
- No SSR march, ray query, denoiser or material shader exists.

### 3.6 Volumetric plan

- Density, extinction, scattering, anisotropy/phase and tier metadata (analytic or froxel) with finite nonnegative values.
- Per-frame froxel/step budgets are logical; exceeding them returns `BudgetExceeded`, not a hidden quality drop.
- No froxel buffer, shadowed fog, temporal reprojection or VFX graph exists.

## 4. Determinism and failure

- All plans are pure functions of validated inputs; fixed iteration order and stable IDs determine output.
- Errors are typed and fail closed; partial plans are not emitted.
- `HISTORY_INVALID`/epoch mismatch resets the plan rather than reusing stale metadata.
- No allocation, exception, file, network, thread or global state in the internal implementation.

## 5. Test strategy

- Unit oracles for lights, shadow splits, GI fallbacks, probes, reflections and volumetric budgets.
- Integrated qualification QLF-G601..G604: valid pipeline, deterministic repeat, failure recovery and 10,000 bounded attempts.
- Native CI on Linux/ASan/UBSan/TSan/Windows/macOS; no visual/driver/hardware assertion.

## 6. Explicit non-goals

No GPU implementation, shadow map, ray tracing, GI bake, probe bake, SSR, froxel volume, visual golden, performance, hardware tier, public ABI or release. Those require separate owner-approved gates.
