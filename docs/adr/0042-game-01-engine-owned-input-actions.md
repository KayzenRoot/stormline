# ADR-0042 — Engine-Owned Semantic Input Actions and Deterministic Device/Context Routing

**STATUS: PROPOSED / NOT APPROVED FOR CODE**  
2026-11-15 | Research issue #208 | WO NLE-P00-WO-002-GAME-01 | Future coding issue #56 OPEN/BLOCKED.

## Context
Stormline needs keyboard/mouse/gamepad/touch controls, multi-device players, consistent Editor/runtime/export mapping, accessible remapping and safe tick-scoped input. CORE-01 already proposes SDL3 for native OS event pumping, but neither CORE-01 nor any engine runtime exists. OS APIs, Web APIs, keyboard layouts, focus, gamepad variants and assistive devices differ. Naively keying gameplay logic on raw device codes creates portability, security, stuck-input and accessibility problems.

## PROPOSED decision
1. **Single OS event authority:** CORE-01 exclusively owns SDL3/native event pump, lifecycle, window/focus epoch and opaque device handles. GAME-01 consumes typed `PlatformEventV1` and cannot initialize SDL or poll OS independently. Browser adapter belongs PLAT-03 and reports browser permission/gesture/capabilities.
2. **Stormline-owned semantic ActionMap:** Author stable ActionId and versioned DIGITAL/AXIS1D/VECTOR2D types, InputBinding, composite axes, chord/hold/toggle, context stack, remapping and conflict resolution. Separate physical scancode, logical key, text/IME and user-facing label. No SDL/XInput/DOM types escape public gameplay/Editor/CLI/MCP APIs.
3. **Deterministic fixed-tick resolver:** normalize ordered input events with source/device/window epochs, preserve all button edges, map to CORE-04 TickId at a defined sampling fence, compile immutable bounded `ActionMapPlanV1` off update path and publish `InputActionFrameV1`/receipt. Mouse motion coalescing and analog sampling must declare loss policy; no claim of hardware interrupt determinism or zero latency. Recorded frames permit resolver replay, not whole-game equivalence.
4. **Focus and security:** UI/Editor owns actual focus and text/IME; GAME-01 only applies its immutable scoped route and context consumption. Focus loss, device removal, suspend, UI modal capture, event overflow and browser pointer lock denial yield fail-safe release/reset and typed receipts. No global keylogger, OS event injection or uncontrolled background capture.
5. **Multi-player device routing:** opaque transient DeviceId+DeviceEpoch with explicit PlayerSeat assignment, hotplug and conflict handling. No cross-session HID serial/fingerprint by default. Physical keyboard separation may be UNKNOWN on aggregated backends. One player can use keyboard+gamepad; multiple gamepads cannot silently share a conflicting seat.
6. **Accessible default:** allow multiple bindings and alternate controls, one-handed layouts, adjustable deadzone/hysteresis/sensitivity/invert, hold-toggle, non-time-critical/menu alternatives, pointer-gesture/drag alternatives and reset-to-safe defaults. W3C WCAG 2.2 criteria inform design without claiming native or Web certification.
7. **User-owned safe persistence:** DATA-02 stable input-map/profile ID, DATA-04 staged CAS, semantic diff/migration and last-good rollback, DATA-01 scoped VFS. Game/local user settings are separate from project defaults. Editor/CLI/MCP have the same validated authoring commands, but no arbitrary physical input injection; assistant permissions are scoped.
8. **SDKs remain candidates:** SDL3 zlib is leading native backend candidate already proposed in CORE-01; no adoption/pin/ship. Microsoft GameInput/GDK and Apple Game Controller are optional isolated platform adapters with own SDK/entitlement terms. W3C Pointer Events Level 3 Recommendation (2026-06-30), Gamepad Working Draft (2026-11-14) and Web keyboard/pointer-lock docs are reference specifications. Community SDL_GameControllerDB dataset rights/notices must be verified before use; do not copy automatically.
9. **No anti-cheat/privilege guarantee:** client InputActionFrame is not proof of a human device or authorized action. GAME/NET owns player authority and validation. Do not expose passwords/text input, OS user IDs or raw HID descriptors in default telemetry.
10. **Evidence before availability claims:** native Windows/Linux/macOS keyboard layouts and gamepads, browser compatibility, headless replay, hotplug recovery, user accessibility testing, throughput/latency p50/p95/p99, 128 prospective cases and defined hardware targets must be tested. No device compatibility or performance claims from Docs Validation.

## Alternatives considered but not selected
- Make SDL3 (or XInput/GameInput/DOM) button IDs the public game action API.
- Implement separate platform loops in GAME-01 or duplicate CORE-01 window/device lifecycles.
- Use raw key press as text input, ignoring dead keys/IME and keyboard layouts.
- Sample only held states each tick and lose press+release between fences.
- Treat browser Gamepad exposure, pointer lock or keyboard `code` as universally available/permissionless.
- Force one input device per player or infer personal identity from a device GUID.
- Automatically replace accessibility/escape/menu bindings with no recovery.
- Give MCP/AI agents privileged global keyboard or HID input injection.
- Claim zero latency, perfect controller support or WCAG compliance without evidence.

## Consequences, risks and approval gate
This adds a vendor-neutral semantic action layer, explicit device-seat lifetimes, event-to-tick mapping and authoring/migration policy. It reduces duplicated platform code and supports game genres without changes to core device APIs. Costs include integration tests across native/Web, controller profile coverage, focus/input-capture complexity, and accessibility review. Future runtime implementation risk **ELEVATED**, documentation LOW. Require CODE owner approval of ADR, implemented CORE-01, exact SDL3 and optional SDK pin/target terms, action-map migration format, first small NECESSARY slice, quantitative budgets, original device/keyboard/touch fixtures and independent evidence. Nothing here licenses a third-party mapping dataset, approves any SDK or unblocks code.
**STATUS remains PROPOSED. Release class UNDECIDED. Software license NLE-D009 OPEN. All 80 coding work orders BLOCKED; #56 OPEN/BLOCKED.**
