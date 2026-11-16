# PLAT-02 — Proposed Linux Target Semantic Host/ABI/WSI/Input/Audio/Package API v0.1

**2026-11-15 | P00 DOCUMENTARY RESEARCH ONLY / NOT IMPLEMENTED | research [#321](https://github.com/KayzenRoot/stormline/issues/321) | NLE-P00-WO-002-PLAT-02 | future code [#85](https://github.com/KayzenRoot/stormline/issues/85) OPEN/BLOCKED | BASE 6271e5482e02fbc575d401feb2d72a24eaff2854.** Catalog 67/80; formal dependencies **GFX-01 + GAME-01 ONLY** (ADR-0014/0042 PROPOSED), CORE-01 transitive; 66/80 research documented at source, 14 pending, all 80 coding WOs BLOCKED; engine_implemented=false; engine license NLE-D009 OPEN.


**Logical future API only; no actual C++ headers, IPC/IDL, daemon, ELF binary, SDL initialization, Vulkan surface, GPU driver or tests.** These types are candidate information boundaries, NOT approved ABI.

## Formal owners and exclusivity
| Authority | Input contract | PLAT-02 contract |
|---|---|---|
| GFX-01 **FORMAL** | RhiDeviceHandle, GpuAdapterInfoV1, PresentSurfaceV1, resource generation | supply typed native Linux WSI capability and internal surface lease; GFX owns queues, VkSurface and swapchains |
| GAME-01 **FORMAL** | PlatformInputEventV1, InputDeviceHandleV1, InputActionFrameV1, WindowEpoch | CORE-01-derived physical events and DeviceEpoch, GAME owns semantic actions |
| CORE-01 transitive | PlatformEventV1, host/window lifecycle, sole SDL event pump | never call extra SDL_Init or independent Wayland event loop |
| AUD, CORE-06, DATA-01/05, BIZ-03, PLAT-05 | endpoint, audit redaction, scoped VFS, packaging/export policy | observations, errors and delegated receipts only |

## Proposed versioned records
| Type | Required fields | Fail-safe invariant |
|---|---|---|
| LinuxTargetProfileV1 | target_id, distro ID/release, architecture, kernel build, libc family/version, compiler/runtime ABI, candidate support tier, Editor/Game role | UNKNOWN is not SUPPORTED; never infer distribution from uname alone |
| LinuxSessionCapabilityV1 | session_epoch, compositor kind WAYLAND/X11/XWAYLAND/HEADLESS/UNKNOWN, protocol versions, sandbox kind, seat accessibility, confidence/evidence timestamp | no display server is explicit, no x11 fallback if X server absent |
| LinuxWindowTokenV1 | opaque WindowId, window_epoch, owner CORE-01, main-thread provenance, lifecycle state | native wl_surface/Display/XCB handles private ephemeral, stale use rejected |
| LinuxDisplayMetricsV1 | display_epoch, logical_size, framebuffer_pixel_size, scale_fraction, transform, refresh_hz?, SDR/HDR/VRR flags (supported/denied/unknown), measurement source | 0x0 never present; no fake Wayland minimize/position state |
| LinuxWindowTransitionV1 | ordered_event_seq, SessionEpoch/WindowEpoch, transition kind CREATE/CONFIGURE/FOCUS/SCALE/DESTROY/SUSPEND, monotonic_time, resulting state | one CORE-01 event sequence; configure must be acknowledged before unsafe present |
| LinuxPresentSurfaceOfferV1 | opaque surface lease, WindowEpoch, SurfaceEpoch, backend WAYLAND_VK/XCB_VK/NONE, pixel extent, color/present restrictions, expiry | GFX-01 owns actual VkSurface/queue/swapchain and resource retirement |
| LinuxGpuProbeV1 | candidate RHI adapter ID, loader/ICD provenance, driver/firmware redacted, hardware vs software classification, WSI ext set, queue support, feature/tier status | no physical GPU pass using lavapipe, no untrusted ICD loaded without policy |
| LinuxInputBridgeEventV1 | source SDL3/CORE-01, device_id+DeviceEpoch, seat/window epochs, sequence, scancode/logical-key/pointer or gamepad physical data, privacy class | no passwords/text/IME/cross-user HID, no duplicate GAME actions |
| LinuxInputCapabilitiesV1 | XKB layout/locale, IME route, pointer confinement availability, gamepad/udev permissions, focus provenance, denied reason | no global hooks or privileged input fallback |
| LinuxAudioEndpointOfferV1 | AUD-owned endpoint token, PipeWire/Pulse/ALSA capability, sample rate/format candidates, generation, access state | no PLAT audio callback/mixer or blocking realtime calls |
| LinuxPortalRequestV1 | purpose FILE_CHOOSER/OPEN_URI/SCREENCAST, user gesture/owner intent, portal version, parent window token, scoped request id | user denial terminal, no silent host-wide permission |
| LinuxXdgPathPolicyV1 | config/data/state/cache/runtime directory roots, absolute/path_owner flags, VFS capability and read/write/atomicity restrictions | ignore invalid relative XDG vars, reject traversal/symlink escape |
| LinuxElfRuntimeProfileV1 | GNU/musl family, GLIBC and GLIBCXX/CXXABI required symbols, ELF arch, PIE/hardening flags, DT_RUNPATH/RPATH manifest, dep digests | no arbitrary project-owned shared libraries or env hijack |
| LinuxDistributionPlanV1 | PLAT-05/BIZ-03 owner refs, portable/AppImage/Flatpak/native candidate, sandbox/portal permissions, runtime/deps/SBOM and signature/rollback | proposal, not permission to package/release/update |
| LinuxPlatformErrorV1 | code, subsystem, retryability, WindowEpoch/SurfaceEpoch/DeviceEpoch, known errno/redacted driver details, owner correction hint | distinguish UNSUPPORTED/UNKNOWN/DENIED/STALE/RESTART_REQUIRED |
| LinuxSmokeReceiptV1 | source/ELF hashes, distro/kernel/glibc, real-vs-CI provenance, compositor/backend, hardware GPU driver/monitor, input/audio, Editor/Game launch+exit, test fixture/license | no virtual GPU equivalence, no synthetic success |
| LinuxBenchmarkReceiptV1 | same pinned environment, monotonic CPU/GPU/display clock domains, raw trials, p50/p95/p99/uncertainty, CPU RSS, VRAM/power if available, rights/privacy/redaction | no invented metric or unsupported GPU timestamps |

## Future semantic procedures (not C++ ABI signatures)
| Operation | Owner/caller | Return or failure |
|---|---|---|
| inspect_linux_target(host_scope) | CORE-01 -> PLAT | LinuxTargetProfileV1 / PROFILE_UNKNOWN |
| negotiate_compositor(host_scope, allowed_backends) | CORE-01, before SDL_Init | LinuxSessionCapabilityV1 / NO_DISPLAY_SERVER; no implicit privileged fallback |
| create_window(host_owner, request) | CORE-01 SDL host | LinuxWindowTokenV1 / WINDOW_UNSUPPORTED |
| observe_window_transition(window_token) | CORE-01 event pump | ordered LinuxWindowTransitionV1 / STALE_EPOCH |
| query_pixel_scale(window_token) | CORE-01 -> PLAT | LinuxDisplayMetricsV1 / UNKNOWN_SCALE |
| offer_present_surface(window_token, backend) | CORE-01/PLAT -> GFX-01 | LinuxPresentSurfaceOfferV1 / WSI_UNSUPPORTED or WINDOW_STALE |
| query_gpu_provenance(surface_lease) | GFX-01 probe with PLAT host metadata | LinuxGpuProbeV1 / ICD_INVALID |
| publish_physical_input(event) | CORE-01 -> GAME-01 | accepted ordered event / SOURCE_DUPLICATE or DEVICE_STALE |
| query_audio_endpoint(scope) | PLAT capability -> AUD | LinuxAudioEndpointOfferV1 / ENDPOINT_DENIED |
| request_user_portal(scope, purpose) | Editor -> portal, user gesture | scoped grant / USER_DENIED; must not bypass |
| resolve_xdg_scope(scope) | PLAT -> DATA-01 | LinuxXdgPathPolicyV1 / PATH_UNTRUSTED |
| inspect_elf_requirements(artifact) | PLAT-05 packaging -> PLAT | LinuxElfRuntimeProfileV1 / ABI_UNSUPPORTED |
| describe_distribution_plan(ref) | PLAT-05/BIZ-03 | LinuxDistributionPlanV1 / OWNER_APPROVAL_REQUIRED |
| make_linux_smoke_receipt(evidence) | QA + CORE-06 | LinuxSmokeReceiptV1 / HARDWARE_UNVERIFIED |

## State/error invariants
- WindowEpoch change invalidates all surface leases tied to previous window. GFX-01 device generation is independent; they only compose using checked pairs. Zero framebuffer extent suspends present. Do not free GPU resources without completion fence.
- CORE-01 event pump supplies strict sequence, ONE source per physical device. GAME-01 maps into ActionFrame at its sampling fence; repeated source sequence or post-focus stale DeviceEpoch is rejected.
- Compositor UNKNOWN never collapses into generic X11; Wayland protocols/caps not assumed. Backend negotiation failure does not automatically spawn nested X server, shell or install packages.
- Denied portal/file permission is a first-class safe error. Saved portal grants have scope/expiry/revocation; DATA-01 VFS must enforce permissions again before every write.
- Missing Vulkan ICD/incorrect ELF ABI is typed launch failure, not a crash-loop auto install. Never inject VK_DRIVER_FILES or LD_LIBRARY_PATH from an untrusted project setting.
- Data exposed to Editor/CLI/MCP is redacted and semantic; native file descriptors, raw handles, GPU/Vulkan pointers, user home paths, hardware serials, full IME composition, /dev/input buffers and credential material are not exposed.
- Schema negotiation must reject incompatible major versions and preserve safe optional unknown flags. Native backend lifetime and OS errno are internal; public error text bounded and scrubbed.
- Audit receipt must state hardware provenance: REAL_PHYSICAL / HOSTED_CI / VIRTUAL / SOFTWARE_RENDERER. Only REAL_PHYSICAL can satisfy physical smoke.
- Headless smoke never implies GUI/GPU/audio passed; unsupported feature not counted as PASS; pending tests P02-T001..T128 remain NOT EXECUTED.

[Architecture](../architecture/plat-02-linux-desktop-target.md) · [ADR-0070](../adr/0070-plat-02-linux-host-compatibility-policy.md) · [128 future tests](../testing/plat-02-acceptance-matrix.md).
