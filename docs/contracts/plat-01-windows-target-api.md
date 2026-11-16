# PLAT-01 — Proposed Windows Target Capability, Window, Input, GPU Present and Packaging Contracts v0.1

**2026-11-15 | P00 DOCUMENTARY RESEARCH ONLY / NOT IMPLEMENTED | [research #317](https://github.com/KayzenRoot/stormline/issues/317) | NLE-P00-WO-002-PLAT-01 | future code [#84](https://github.com/KayzenRoot/stormline/issues/84) OPEN/BLOCKED | BASE `e6ca541df3f08bc46a7f1e5b2f82564cb740f720`.** Catalog 66/80, **formal dependencies GFX-01 + GAME-01 ONLY**, both prior ADR-0014/0042 PROPOSED; CORE-01 transitive ADR-0003 PROPOSED. Baseline research 65/80, 15 pending; 80/80 future coding WOs BLOCKED; engine_implemented=false; NLE-D009 license OPEN.

**FUTURE LOGICAL CONTRACTS ONLY, no compiled C++ ABI/IDL, DLL, Windows executable, Windows API bridge, package, SDK integration or tested hardware.**

## 1. Formal input contracts and OS authority
| Owner | Existing versioned contract | PLAT-01 adapter limit |
|---|---|---|
| **GFX-01 FORMAL** | `GpuAdapterInfoV1`, `GpuFeatureProfileV1`, `RhiDeviceHandle`, `PresentSurfaceV1`, typed RHI surface status/capabilities | Windows surface metadata/display state only; no native GPU pointer/command/shader API in public contract |
| **GAME-01 FORMAL** | `PlatformInputEventV1`, `InputDeviceCapabilitiesV1`, `InputDeviceHandleV1`, `InputActionFrameV1`, `InputFocusRouteV1`, device/WindowEpoch | Windows physical input translated by CORE-01 into typed event source; no gameplay map, no global hooks |
| CORE-01 transitive | `PlatformEventV1`, host lifetime, event pump, window focus, mono clock, `PlatformCapabilitySnapshot` | ONLY OS event pump/main-thread authority; PLAT-01 integrates as bridge |
| CORE-06, AUD, DATA-01/05, BIZ-03 transitive | redacted diagnostics, audio ownership, VFS and cook manifests, installer/update plans | Windows target data only, no duplicate source or updater authority |

## 2. Proposed versioned types
| Type | Required fields (candidate only) | Invariant |
|---|---|---|
| `WindowsTargetProfileV1` | targetId, Windows OS min/current build+SKU/arch, support tier/service date, engine ABI, release profile Editor/Game/Headless, feature negotiation revision | supported status evidence and owner-approved minimum; no implicit Windows 10 promise |
| `WindowsHostIdentityV1` | session/window process epoch, platform host version, scope, nonprivileged role, build binary SHA, measured architecture, capability rights | no HWND/PID/User SID/serial in externally exposed engine API |
| `WindowsWindowHandleV1` | opaque WindowId/generation, host epoch, lifetime status, creating thread identity (internal), window type (Editor/Game/tool) | SDL/Win32 handles private; stale generation rejected |
| `WindowsDisplayCapabilityV1` | opaque display ID/epoch, per-monitor content scale, pixel density, DPI/refresh, SDR/HDR color/VRR, orientation, connector class, measured/unknown | no display serial/EDID/device fingerprint by default; refresh measured/unknown |
| `WindowsWindowMetricsV1` | logical/physical dimensions, framebuffer px extent, scaling revision, monitor safe rect, fullscreen/borderless, focus/minimize/occlusion flags | zero extent suspends GPU present, no division by zero/double scale |
| `WindowsWindowLifecycleEventV1` | WindowEpoch, event sequence, owner host monotonic time, WM/SDL normalized kind, previous/new state, safe requested next action | one CORE-01-owned order, no duplicate event pump |
| `WindowsPresentSurfaceV1` | WindowId+epoch, native-surface token internal to GFX-01, pixel extent, backend capability hints, SDR/HDR/color and actual present generation, reason status | GFX-01 sole swapchain/adapter owner, stale swapchain invalidated |
| `WindowsPresentCapabilityV1` | WSI backend Vulkan/D3D12/SDL_GPU available/denied, flip/tearing/VRR/HDR hints, query evidence, GPU feature tier, driver revision | unknown feature not enabled; never infer from GPU brand |
| `WindowsNativeInputEventV1` | source SDL/Win32/GameInput enum, event seq/WindowEpoch/DeviceEpoch, physical scancode or logical key/typed pointer+device state, mono time accuracy and privacy class | converted via CORE-01, consumed GAME-01; no text/pwd capture |
| `WindowsInputAdapterCapabilityV1` | current keyboard/mouse/touch/pen/gamepad/haptics APIs, runtime version, USB/BT availability, duplicate-source policy and user permission | no raw HID identifier/fingerprint, missing GameInput runtime => unsupported fallback |
| `WindowsAudioEndpointCapabilityV1` | redacted endpoint class, default/active status, sample formats, shared/exclusive candidate, generation, hotplug and privacy | AUD owns actual sample playback, callback real-time, no PLAT mixer |
| `WindowsHostPathPolicyV1` | app/project/settings paths as scoped VFS capabilities, UTF-8<>UTF-16 error, long-path/reparse/disconnected remote drive policy, ACL availability | no arbitrary raw host path in MCP and no DLL from project |
| `WindowsPlatformErrorV1` | error code/owner stage, source revision/WindowEpoch, retryability, OS cause redacted, explicit recover vs restart | no unbounded system formatted messages/secret paths |
| `WindowsBuildArtifactV1` | build SHA, binary digests, compiler/SDK/CRT/SDL/redist dependency lock, x64/arm64, Editor/Game role, symbols, unsigned dev flag | Dev smoke artifact not release-ready unless separately signed/packaged |
| `WindowsDistributionPlanV1` | BIZ-03-owned channel ref, MSIX/portable/EXE/Msi kind, package identity requirement, required CRT/GameInput/SDK runtime, signer/rollback/permissions | PLAT only supplies requirements, not installer/updates or publication |
| `WindowsSmokeReceiptV1` | actual OS SKU/build, target CPU/GPU/driver, display DPI/HDR, input/audio devices redacted, artifact+source hashes, launch/exit, 2D/3D owner captures, status and failures, headless/runtime distinction | future evidence must be from actual hardware; no hosted CI hardware claim |
| `WindowsHardwareBenchmarkReceiptV1` | environment, cold/warm, frame p50/p95/p99, present/input latency, device loss, CPU/GPU memory/clock, power availability, raw samples, validity | no invented metrics, actual CORE-06 clock domain and GFX owner timestamps |

## 3. Future logical host APIs
```text
inspect_windows_target(VerifiedHostScope)
   -> WindowsTargetProfileV1 | WIN_OS_UNSUPPORTED
create_window_via_core01(HostOwner, WindowsWindowSpec, DPIProfile)
   -> WindowsWindowHandleV1 | WindowsPlatformErrorV1
get_window_metrics(HostOwner, OpaqueWindowId)
   -> WindowsWindowMetricsV1 | WINDOW_STALE
observe_window_event(HostOwner, OrderedNormalizedEvent)
   -> WindowsWindowLifecycleEventV1
get_present_surface(HostOwner, GFX01AdapterScope, WindowId, Epoch)
   -> WindowsPresentSurfaceV1 | PRESENT_SURFACE_INVALID
inspect_present_capabilities(VerifiedScope, RhiAdapterId, DisplayEpoch)
   -> WindowsPresentCapabilityV1 | GPU_BACKEND_UNSUPPORTED
translate_native_input_event(CORE01Owner, ScopedEvent)
   -> GAME01PlatformInputEventV1 | INPUT_PERMISSION_DENIED
inspect_input_adapter_capabilities(VerifiedScope, WindowId)
   -> WindowsInputAdapterCapabilityV1
inspect_audio_endpoint(VerifiedScope)
   -> WindowsAudioEndpointCapabilityV1 | AUDIO_DEVICE_LOST
resolve_host_path_via_data01(AuthorizedVFSRoot, WindowsPathPolicy)
   -> ScopedPathHandleV1 | PATH_SCOPE_DENIED
prepare_windows_build_artifact(BuildOwner, ToolchainLock, Target)
   -> WindowsBuildArtifactV1 | WIN_BUILD_NOT_SUPPORTED
describe_windows_distribution_requirements(BIZ03Owner, WindowsBuildArtifact, Channel)
   -> WindowsDistributionPlanV1 | SIGNATURE_REQUIRED
smoke_windows_hardware(AuthorizedIsolatedFixtureRunner, Artifact, HardwareProfile)
   -> WindowsSmokeReceiptV1 | UNSUPPORTED_HARDWARE
```
These are **proposed conceptual operations**, not a tool/plugin callable today. No user agents may call raw Win32 message dispatch, GPU commands, DLL loading or background input reading.

## 4. Host lifecycle contract
```text
CREATED -> OS_NEGOTIATED -> HOST_READY -> WINDOW_VISIBLE
  -> [WINDOW_OCCLUDED | MINIMIZED | RESIZING | DPI_CHANGED | FOCUS_LOST]
  -> SURFACE_REVALIDATING -> WINDOW_VISIBLE -> DESTROYING -> CLOSED
fail: OS_UNSUPPORTED, WINDOW_STALE, AUDIO_DEVICE_LOST,
      GPU_DEVICE_LOST, RESTART_REQUIRED, RIGHTS_DENIED
```
Host emits one event stream CORE-01 main thread; `WindowEpoch`, `DisplayEpoch`, `DeviceEpoch`, `PresentGeneration` increment as appropriate. No reuse of freed native handle, driver resource or old input window. Headless mode skips display/audio/GPU cleanly with actual capability status. On SUSPEND/CLOSE, GAME-01 releases all held actions, GFX-01 stops presenting and AUD flushes/pauses using its own safe APIs. No game logic on Win32 callback thread.

## 5. Input, timing and rendering invariants
- CORE-01 events contain stable ordering/clock confidence, GAME-01 translates scancode vs logical, text/IME separate, deterministic action-frame resolution by CORE-04 tick. SDL3 main thread only and GameInput optional runtime cannot create a second event pump.
- DPI physical frame extent != UI content scale; Windows desktop per-monitor v2 dynamic changes, mouse window coordinates and hit-testing use explicit conversion and owner UI scale.
- D3D12/DXGI flip/tearing/HDR modes capability guarded; Vulkan WSI surface created only by GFX-01 adapter. Surface generation, resize/device loss never silently recover; `RESTART_REQUIRED` valid.
- Audio endpoint capabilities no promise of OS callback latency; reality requires AUD owner hardware test.
- No uniform guarantee Windows 10/11/ARM64, signing success, correct installer or native game fps from a Windows CI compilation.

## 6. Distribution and security decisions remain open
No raw host path, SID/HWND/COM pointer, Windows device serial, DXGI handle, executable plugin or OS power action in public MCP. Windows install/updates/rollback remain BIZ-03; unsigned internal smoke is not production readiness. Require exact SDK, SDL, GFX backend, optional GameInput/Windows App SDK, CRT, signing and OS support evidence before approving changes. 128 planned P01 future tests all NOT EXECUTED.

[Architecture](../architecture/plat-01-windows-desktop-target.md) · [ADR-0069](../adr/0069-plat-01-windows-host-boundaries.md) · [Testing](../testing/plat-01-acceptance-matrix.md).
