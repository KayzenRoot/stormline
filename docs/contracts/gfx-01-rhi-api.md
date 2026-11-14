# GFX-01 — Typed Render Hardware Interface (RHI) Semantic Contract

**Work Order:** NLE-P00-WO-002-GFX-01 | **Research issue:** #123 | **Implementation:** #29 BLOCKED.
**Status:** PROPOSED logical contract, not executable API/ABI, shader compiler, GPU wrapper, MCP server or selected backend.

## Logical public contract entities

| Type | Required proposed fields | Invariant / failure |
|---|---|---|
| `GpuAdapterInfoV1` | opaque adapter_id, OS/backend, GPU vendor/device family, driver/API version, memory estimates, features, limits and privacy class | diagnostic identifiers may be sensitive; no name-only capability inference |
| `GpuDeviceCreateRequestV1` | preferred backend list, required/optional capability set, surface/offscreen mode, feature tier, memory policy, debug flags from trusted config | feature unsupported fails or explicitly degrades with receipt; no untrusted flags |
| `DeviceCapabilitiesV1` | device id/generation, supported features, numeric limits, texture formats/sample counts, shader feature profile, queue families, memory pressure, timestamp support | read-only snapshot tied to generation, re-query after loss |
| `GpuDeviceStateV1` | generation, state, initialized/failed reason, lost count, recovery eligible, restart required | states monotonic and error on stale resources |
| `GpuBufferDescV1` | size, usage, CPU visibility/mapping, alignment, initial access, label redaction policy | checked overflow/bounds/lifetime, no unbounded allocation |
| `GpuTextureDescV1` | dimensions, levels, layers, format, sample count, usage, color transfer and origin | validate format/shape/budget, fallback only with explicit authorization |
| `GpuResourceHandleV1` | device generation, resource class, stable slot + slot generation, owner/capability, status | invalid after device reset; cannot dereference raw GPU pointer |
| `GpuQueueV1` | role (graphics/compute/transfer), supported stage flags, ownership, family and concurrency policy | no promised dedicated queues when driver lacks feature |
| `CommandEncoderV1` | device/queue id, command generation, declared resource access, recording state | cannot submit while invalid/unended, cross-generation or after loss |
| `SyncBarrierV1` | resource handle, range/subresource, old/new access, stages, queue transfer, fence/timeline requirements | validate transitions and owner; no hidden unsafe races |
| `SurfaceDescV1` | trusted platform window capability, dimensions, color space, present mode, HDR preference and version | no raw foreign OS handle via MCP; resize invalidates swapchain generation |
| `SwapchainStatusV1` | surface version, image sequence, acquire/present error, present mode/latency | no deadlock on minimize/occlusion/out-of-date |
| `DeviceLostReportV1` | reason code, last device generation, affected resources count, retry/restart option and redacted driver context | no false restoration of in-flight resources |
| `RhiHealthSnapshotV1` | queue submits, CPU/GPU timings if supported, allocation/VRAM pressure, errors, build SHA and capture mode | GPU timing unavailable distinguished from measured zero |
| `RhiErrorV1` | stable code, backend, stage, generation, retryability, security-sensitive detail flag | sanitized, no driver pointer, shader binary or secret leak |

## API service operations (owned and versioned, not final C++ signatures)
- `adapter.list` / `adapter.inspect` / `device.capabilities.inspect`: read-only, bounded and redacted discovery with no auto-device open to prevent probe side effects.
- `device.open` / `device.close` / `device.reprobe`: privileged engine-internal lifecycle; errors include capability negotiation/unsupported tier.
- `buffer.create` / `texture.create` / `resource.release`: engine-internal, versioned descriptors validated against budgets; deferred destroy until GPU ownership/fence complete.
- `commands.begin` / `commands.encode` / `commands.submit`: typed internal queue operations, barriers and fence contracts. Never exposed as raw MCP general commands.
- `surface.attach` / `surface.resize` / `surface.present`: valid trusted window context, versioned swapchain resource dependency.
- `device.lost.inspect` / `device.recovery.plan` / `device.recovery.execute`: privileged recovery, explicit restart fallback, invalidate previous generation; no promise recoverability on all drivers.
- `rhi.diagnostics.snapshot` / `rhi.preview.capability`: safe user/LLM-viewable bounded operations. Only analysis/preview, no arbitrary native API.

## Device state machine
```text
UNINITIALIZED -> DISCOVERED -> INITIALIZING -> READY -> SUSPENDED -> READY
                                                 -> LOST -> RECOVERY_PREPARED
                                                     -> RECREATING -> READY (new generation)
                                                     -> FAILED / RESTART_REQUIRED
          any valid initialized state -> SHUTDOWN_PENDING -> DISPOSED
```
Every API call validates device generation, resource slot generation, ownership and current state. Resource stale after device loss is not made valid just because a new device has same backend/adapter name. Pending submissions complete, abort, or fail explicitly and provide predictable retirement semantics. Reopen must recheck feature support and reload verified DATA-05 immutable artifacts where needed.

## Capabilities and fallback
Feature classes are logical identifiers, not generic all-on tiers: raster_base, compute, indirect_draw, descriptor_indexing, async_compute, texture_compression_BC, texture_compression_ASTC, texture_compression_ETC2, timestamp_query, raytracing, mesh_shader, variable_rate_shading, sparse_resources, HDR_present. Each records availability plus quantitative limit and fallbacks. Tier decisions belong renderer/PLAT policy; baseline must not silently upgrade scene requirements or deliver a corrupt rendering substitute.

Typed coordinate properties declare viewport origin, clip depth range, winding, texture origin, color transfer. CORE-05 world RH Y-up policy **not overwritten** by backend GPU NDC.

## Editor/CLI/MCP command parity, with strict access
| Command | Capability | Mutation |
|---|---|---|
| `rhi.adapters.list` | project.graphics.inspect | read-only bounded list |
| `rhi.capabilities.inspect` | project.graphics.inspect | read-only scoped feature snapshot |
| `rhi.device.health` | project.graphics.inspect | read-only state and safe error code |
| `rhi.diagnostics.snapshot` | project.graphics.debug.read | bounded redacted counters and optional GPU timings |
| `rhi.device.preview_fallback` | project.graphics.inspect | simulate tier selection, **never** apply |
| `rhi.device.recovery.plan` | project.graphics.debug.read | no device changes |
All active native device creation, commands, resource writes and recovery execution are **not a public MCP surface**. If future authoring commands require GPU preview rendering, they must be mediated by approved semantic Editor services with limited quotas, not raw GPU controls.

Errors: `ADAPTER_MISSING`, `GPU_DISABLED`, `UNSUPPORTED_BACKEND`, `UNSUPPORTED_FEATURE`, `RESOURCE_LIMIT`, `ALLOCATION_FAILED`, `INVALID_DESC`, `INVALID_ALIGNMENT`, `INVALID_FORMAT`, `STALE_HANDLE`, `STALE_GENERATION`, `DEVICE_LOST`, `RESTART_REQUIRED`, `QUEUE_UNSUPPORTED`, `SYNC_INVALID`, `MAP_CONFLICT`, `SURFACE_OUT_OF_DATE`, `SURFACE_NOT_PRESENTABLE`, `PRESENT_FAILED`, `TIMING_NOT_AVAILABLE`, `CAPABILITY_DENIED`, `OPERATION_CANCELLED`, `BACKEND_ERROR`, `UNKNOWN`. Each tagged by stage/retryability, no unbounded native error strings.

## Integration and security gates
No native vendor ABI types cross the public RHI layer. No reentrant callback use-after-free, GPU pointer exposure, arbitrary shader dispatch through MCP or untrusted compiler flags. Verify loader/pipeline/format versions and CPU-side/VRAM budgets. Physical GPU tests and architecture/SDK approval required to freeze real API/ABI. This is conceptual, **not a working renderer or benchmark**.

See [architecture](../architecture/gfx-01-graphics-rhi.md), [future tests](../testing/gfx-01-acceptance-matrix.md), [ADR-0014](../adr/0014-gfx-01-rhi-backends.md).
