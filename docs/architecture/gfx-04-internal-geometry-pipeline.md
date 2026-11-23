# GFX-04 internal logical geometry and visibility pipeline

**Status:** `GOVERNANCE-SCOPED / NOT IMPLEMENTED / NO NATIVE GPU`. **ADR:** [ADR-0118](../adr/0118-gfx-04-internal-geometry-pipeline.md). **Parent research:** [gfx-04-geometry-visibility-lod](gfx-04-geometry-visibility-lod.md), planning only.

## Purpose

Define the first executable GFX-04 slice without selecting a native GPU path or mesh library. The pipeline is bounded, in-memory metadata: instance validation/batching, conservative culling, LOD/HLOD selection, verified-chunk request planning, vegetation classification and geometry budget validation.

## Hard boundaries

- No Vulkan/D3D12/Metal/WebGPU, mesh/task shader, indirect draw or GPU occlusion.
- No meshoptimizer, external codec, cooking, mesh decode/simplification, file or network.
- No command buffer, submission, rendering, pixel output, GPU timing or hardware measurement.
- No authored AssetId rewrite; derived IDs remain logical metadata.
- No public ABI, release, performance or security certification.

## Logical model

- **Instances:** stable instance ID, mesh/material IDs, center/radius bounds, bounds-known flag, vegetation category and scene generation.
- **Batch grouping:** contiguous logical groups by mesh/material, ordered deterministically.
- **Culling:** conservative sphere test against caller-provided frustum planes and a distance limit. Unknown bounds are visible; a failed plane or distance test culls only with a full sphere outside.
- **LOD/HLOD:** bounded LOD chains with nondecreasing geometric error and nonincreasing triangle counts; hierarchy parent links are acyclic. Selection uses a projected-error threshold and conservative fallback to the root/coarse proxy.
- **Streaming:** verified chunk references only; request planning is bounded by byte budget and deterministic priority. Unverified chunks are rejected.
- **Vegetation:** categories and flags (double-sided/alpha-cutout/billboard-eligible) are preserved; classification never silently drops required geometry.
- **Geometry budget:** triangle/vertex/byte totals are checked; requested reductions cannot increase complexity.

## Determinism

- Instance/batch/stream outputs are sorted by stable IDs or declaration order.
- Float comparisons use simple bounded arithmetic; tests use exact fixture values.
- No unordered iteration determines output.
- Repeated planning of unchanged input produces identical output.

## Failure model

Typed errors cover duplicate/unknown IDs, capacity, invalid bounds/camera, generation mismatch, hierarchy cycles, invalid LOD ordering, unverified chunks, stream budget overflow and geometry budget overflow. Unknown bounds are visible; invalid input fails closed.
