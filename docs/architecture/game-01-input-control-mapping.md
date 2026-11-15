# GAME-01 — Input & Control Mapping Architecture

**Research WO:** NLE-P00-WO-002-GAME-01 | **Research issue:** #208 | **Future coding issue:** #56 OPEN/BLOCKED  
**BASE main:** `0a3aa77229f5663e55fdf9b8b99a786c9edb1cc9` | **P00 DOCUMENTATION / ADR-0042 PROPOSED ONLY.** No input backend, key mapping, gamepad/touch action resolver, executable, real device capture, benchmark, platform build, headless action replay or accessibility audit exists. Research LOW risk, future implementation ELEVATED for privacy/focus, device disconnects, input spoofing, inaccessible controls, cross-platform ABI and multiplayer authorization.

## 1. Product objective and acceptance truth
Catalog scope: **"Keyboard/mouse/gamepad/touch, remapping, múltiplos dispositivos, acessibilidade."** Catalog acceptance: **"Mapeamentos consistentes entre editor, runtime e exports."** Provide one *Stormline-owned* input action and device routing model for native Windows/Linux/macOS Editor+exports, and a Web adapter subject to PLAT-03 browser capabilities. The game developer defines semantic actions such as Move, Attack, Dodge, Interact, Menu, Navigate, Confirm and Cancel; an individual player can bind these to physical controls without game code depending on a vendor's button ID.

**Proof boundary:** a well-typed plan does not demonstrate latency, gamepad compatibility, consistent keyboard layouts, accessibility or parity. Only future cross-OS device fixtures, replay/real user tests and actual Editor/client/export builds can meet acceptance.

## 2. Authority and ownership matrix
| System | Owns or contributes | GAME-01 must not duplicate |
|---|---|---|
| **CORE-01 (required catalog dependency)** | OS lifecycle, window focus/visibility/suspend, SDL3 event pump and optional native bridge, platform-provided `PlatformEventV1`, host monotonic timestamp, opaque device/window handles, OS privacy permissions and headless host | independent SDL_PollEvent loop, Windows Raw Input/GameInput global subscription, Cocoa event loop, SDL initialization, OS hook, native host handles |
| **GAME-01** | normalized device/channel states, transient device epoch and player seat routing, semantic action maps, action contexts, chords/composites/analogs, player accessibility profiles and remapping conflicts, deterministic per-tick action resolution and receipts | window/process lifecycle, OS event pump, gameplay authority, arbitrary OS input injection |
| **CORE-04** | fixed simulation TickId, pause/resume, rational tick and input sampling fence | GAME-01-owned independent simulation clock or wall-clock tick |
| **CORE-03/06** | bounded queues, worker compilation and redacted event counters/trace | new job system, unbounded logging/input sample capture |
| **DATA-01/02/04/05** | scoped VFS, durable source/profile IDs/revisions, authored transaction/CAS/journal, cooked target manifest | direct user/home paths, private profile JSON database, arbitrary file write or separate transaction claim |
| **GAME-03 / EDIT/UI owners (future)** | actual focus tree/GUI navigation, text field composition and IME, pointer capture/context, visual control glyphs and accessible settings UI | GAME-01 widget renderer, IME owner, second focus model, accessibility certification |
| **GAME-02/04 / WORLD/NET owners (future)** | gameplay script APIs, authoritative action execution and network validation, state transitions and combat/interaction semantics | client-side action as proof of entitlement or authority; silent gameplay state edits |
| **PLAT-01/02/03/04** | Windows/Linux/macOS platform packaging/backends, browser gesture/security policy, optional mobile target adaptation | required WebHID/WebGPU/phone sensor assumption, browser DOM/OS handles in public engine API |
| **AI-04/06 and CLI/MCP** | scoped public authoring command/inspection parity and authorization | raw input injection, global key logging, secret key capture or arbitrary OS commands |

Dependency caveat: CORE-01 is proposed architecture, not implemented; therefore GAME-01 cannot become EXECUTOR_READY. Other referenced modules are semantic consumers, not extra catalog prerequisites silently made mandatory for P00 research.

## 3. Event path and clock model
Proposed unidirectional pipeline:

```text
Keyboard / Mouse / Gamepad / Touch / Accessibility Device
   -> CORE-01 platform bridge (SDL3 native or PLAT-03 browser adapter)
   -> PlatformEventV1 (window, device, ordered event, host time, focus epoch)
   -> GAME-01 InputDeviceRegistry + normalized raw channels (not OS handles)
   -> bounded InputEventJournal / stable ordering and input-frame fence
   -> PlayerSeat + InputContextStack + immutable ActionMapPlanV1
   -> InputActionFrameV1 (TickId, actions, edges, analog values, provenance)
   -> authorized GAME / UI / NET consumers
```

1. **Ingest:** CORE-01 alone pumps SDL3 (main-thread only; SDL_PollEvent may pump internally) and publishes checked PlatformEvents with host monotonic timestamp and per-source ordered sequence. Distinguish unknown timestamp precision from exact hardware interrupt time; no fantasy nanosecond-latency claims.
2. **Normalize:** GAME-01 maps physical key position, logical key symbol, mouse button/absolute vs relative motion, wheel units, touch pointer ID/lifetime, joystick/gamepad button/axis into versioned tokens with `DeviceEpoch`, `WindowEpoch`, origin adapter, focus state, availability and confidence; no driver/vendor ABI leaks.
3. **Lifecycle:** connect/ready/disconnect/reconnect and focus loss are explicit. On focus loss or device removal, synthesize deterministic logical release/zero-axis transitions, clear gesture/chord holds, drop stale generation, invalidate seat routing and emit a receipt. Never leave a stuck attack/move key. No background global key capture.
4. **Sample:** CORE-04 defines fixed-tick boundaries, GAME-01 emits one action frame per authorized PlayerSeat+TickId using immutable previous/current raw state and *all edge transitions* since the prior tick. Preserve rapid down/up pairs even if both occurred between ticks. Coalesce motion values only with declared loss/accumulation policies, never clicks/key edges, menu confirm or hotplug.
5. **Route:** UI/editor focus owner publishes an immutable `InputFocusRouteV1`. GAME-01 applies precedence and consumes actions only in allowed contexts, e.g. modal text edit > focused UI > gameplay, with explicit propagation/consumption; a chat field does not trigger gameplay shortcuts. Gamepad menu focus is an owner-validated context, not a separate key driver.
6. **Replay:** record schema version, adapter capability profile, ordered normalized events or tick action frames, map hash, calibration, scope, source TickId, per-device epoch and PRNG seed if used. Replay can reproduce the input resolver's intended results; this is NOT proof of whole-game determinism or real hardware sampling uniformity.
7. **Headless:** no physical device or global input backend is required; tests/server consume validated recorded `InputActionFrameV1` or authorized synthetic fixture through a separately permissioned test-only interface. Server remains GAME/NET authority and must not treat client action frames as trusted OS-origin proof.

## 4. Keyboard, mouse, pointers and text/IME separation
- **Physical binding:** layout-independent key position/scancode for movement or reflex actions (e.g. WASD physical positions). **Logical binding:** named key/character for locale-aware shortcuts. Preserve both; never infer a printable character from raw scancode, especially dead keys/AltGr/IME/non-US keyboards.
- **Unicode/IME:** CORE-01 provides separate text-input/composition events; UI/text owner handles grapheme composition, on-screen keyboard, dead keys, candidate selections and keyboard locale. SDL3 `SDL_StartTextInput(window)` is window-scoped and may swallow keydown during IME. GAME-01 must not turn composition/typed text into gameplay.
- **Keyboard repeat:** distinguish OS auto-repeat from physical held state. GAME-01 defines its own optional repeated action timing anchored to TickId; no duplicate "jump" on auto-repeat unless authored policy.
- **Mouse:** absolute position in explicit window-local logical/physical pixels, DPI/scale rev, relative deltas, wheel direction/units and button edges; use scoped cursor capture/relative mode via CORE-01 permissioned host request, with accessible cursor/focus restoration on ESC, focus loss, exit.
- **Touch/pen:** stable pointer lifetime/generation, touch target, pressure/tilt optional capabilities; multiple contacts, cancel, palm rejection handled by platform capability. Two-finger pinch/rotate/swipes can be opt-in and have keyboard/single-pointer alternative where the gameplay operation permits. Never assume every native platform delivers pressure or raw high-frequency samples.
- **Web:** W3C Pointer Events Level 3 Recommendation (2026-06-30) is a strong adapter basis for touch, pen, mouse and coalesced events; Gamepad spec 2026-11-14 is a Working Draft, browser implementation differs. Pointer Lock can require a user gesture, be denied or unsupported. DOM key `code` vs `key` parallels physical vs logical but is not universally feature-identical. Permission policy, focus, cross-origin iframe/sandbox and browser security restrictions are typed capability outcomes, not bypassed.

## 5. Gamepads, multi-device and player seats
- **First native candidate:** SDL3 official Gamepad/Joystick API through CORE-01. SDL3 gamepad mapping string and SDL_AddGamepadMapping permit fallback community mappings; requires exact version/rights validation. Normalized buttons, sticks, triggers, D-pad and optional gyro/touchpad/rumble/haptics are capability-gated. Haptics OUTPUT control and actuator limits remain host/platform concern, **not necessary for first GAME-01 input increment**.
- **Device identity:** transient opaque runtime DeviceId, per-connection generation and device class/capabilities. Do not expose serial, MAC, full HID report path or hardware fingerprint to game scripts, MCP or logs. OS GUID/vendor info can be stored privately only when justified and consented; avoid cross-session stable fingerprint by default.
- **Multi-device:** allow 2+ gamepads, one player with keyboard+gamepad, dynamic switching from last active device, and hotplug. "Separate keyboard per player" is UNKNOWN unless actual platform backend can identify physical keyboards; aggregated keyboard must not pretend to have device separation.
- **Seat ownership:** authenticated/local `PlayerSeatV1` distinct from device identity and game Entity; explicit join/unjoin/reassign, primary/secondary device, conflict and disconnect policy. No device can be implicitly bound to a second player with conflicting authority. On rejoin, action epoch increments and no stale held action leaks.
- **Calibration:** sticks require deadzones (radial preferred candidate for 2D stick, axial optional), anti-deadzone only if tested, sensitivity/inversion and nonlinear monotonic bounded curves. Triggers are usually [0,1], sticks [-1,1]; normalize from backend units with finite bounds, hysteresis enter/exit, drift compensation with explicit user/device policy. Never silently auto-calibrate from one noisy sample. Physically accessible triggers and stick swap/one-handed profiles are planned.

## 6. Semantic action-map model
- **`InputActionMapV1`** authored stable ActionId, action kind DIGITAL/AXIS1D/VECTOR2D, semantic labels/tags, gameplay namespace, default bindings and required fallback access; DATA-04 compare-and-swap and stable asset/provenance from DATA-02. Importer or game script must not mutate it directly.
- **`InputBindingV1`** maps SourceControl+DeviceClass and optional role/seat to an ActionId with trigger (PRESS/RELEASE/HELD/TAP/HOLD/DOUBLE_TAP), modifier/chord/sequence constraints, analog transform/cap, repeat, consumption and priority. Chords/combos/instant transitions are bounded in depth/time/count.
- **Composite Axis:** keyboard WASD into Vector2, triggers to Axis1D, dual-stick/gyro only where actual capabilities exist. Aggregation FIRST_ACTIVE, MAX_ABS, SUM_CLAMPED or PER_DEVICE with deterministic tie-break; avoid adding two controllers' movement and creating overspeed accidentally.
- **`InputContextStackV1`** scene/UI/gameplay/menu/vehicle/cinematic context layers with activation token, owner, precedence and lifetime. Context switching at tick boundary can generate synthetic release/cancel to avoid inherited held input. Window focus must gate gameplay. Can't use remapping to overwrite privileged Escape/OS-reserved combos without alternative recovery path.
- **Profiles:** project-author defaults -> target capabilities -> user/player profile -> device-class preference; user changes are local/scoped, revisioned, atomic at source transaction layer, import/export allowlisted and backed up with last-known-good plus reset. Developer/editor profiles and runtime user preferences are distinct; UI/CLI/MCP public authoring sees same semantic validation and preview/conflict receipt, not raw OS events.

## 7. Remapping UX, conflicts and migration
- Capture a new binding only when an explicit focused, authorized remap dialog/window has a timeout and cancel option. Display device glyphs/localized labels through GAME-03/EDIT, not hardcode English key names. Password/text fields never become remap capture surfaces.
- Conflicts: same physical control in **mutually exclusive contexts** may be allowed; same active context conflicting actions triggers explicit REVIEW/REPLACE/SWAP/KEEP_BOTH policy with action priority and preview. Never silently overwrite a critical menu Back/Confirm, accessibility escape or anti-stuck recovery binding.
- Action-map edits use DATA-04 CAS expected revision, semantic diff, staged preview and atomic commit/last-good rollback. Persist stable ActionId not keyboard-layout-specific display labels; revisions include action type/unit/glyph schema and target capabilities. Migrate with explicit compatibility and conflict receipts; unknown required actions fail closed.
- Multiplayer seat and controller mappings are separate from user-local preferences and server-authoritative state; cloud sync, account linking, shared accessibility diagnosis and game telemetry are FUTURE/OUT OF SCOPE.

## 8. Accessibility is built into input semantics
- Multiple equivalent bindings per action, keyboard/controller/touch alternatives, one-handed layouts, stick inversion/deadzone, adjustable sensitivity, hold-to-toggle, tap/hold timing adjustment, repeated-press reduction and tremor-safe thresholds. Accessibility parameters are explicit typed transforms with duration/strength bounds and reset controls.
- Provide alternate single-point and keyboard interactions for path/multipoint touch gestures when functionally possible. Do not require time-critical chord, double-tap, long hold or drag as the only means to navigate essential menus. Avoid losing focus when switching input modality.
- WCAG 2.2 Keyboard (2.1.1), Pointer Gestures (2.5.1), Pointer Cancellation (2.5.2), Concurrent Input Mechanisms (2.5.6), Dragging Movements (2.5.7), Target Size Minimum (2.5.8) and Focus Visible are **design guidance**, not blanket certification of a native game or unbuilt interface. UI owner must test target-specific practical assistive navigation and user feedback.
- Game title may offer accessibility profiles, but cannot claim OS screen reader support, switch control, adaptive controller or assistive-device compatibility until tested with real hardware/people.

## 9. Security, privacy and failure handling
- Input must be scoped to a focused active window and authorized local seat. No keyboard snooping outside focus, hidden background capture, OS global hooks, arbitrary HID I/O, privileged synthetic input or unconsented hardware fingerprint export. Do not log keycodes/text/IME/serials by default.
- Touch/pen/pointer/window IDs must be opaque and generation-checked; queue entry sizes, event rate, chord depth, bindings/map count, number of seats/pointers and analog values are bounded. Reject NaN/Inf, invalid pressure, negative duration, malformed binding graph, stack cycles and resource exhaustion.
- Hotplug/focus loss/suspend/window destruction synthesizes safe releases, clears stale axes and active gestures, records overflow/loss receipts. On event queue overflow, reconstruct from verified polling where possible or FAIL_SAFE_RESET; never continue a potentially stuck action without signal.
- Remote/network action intents are **untrusted** and GAME/NET validates player, sequence, rate, game state and constraints. No claim that local input origin proves a legitimate human or that this architecture implements anti-cheat. AI authoring can stage action maps only with scoped Editor/CLI/MCP rights.
- No devtools/browser policy bypass; Web gamepad data can be blocked until user gesture or permission and may be fingerprinting-sensitive. Browser pointer lock denial/focus loss returns typed fallback and visible prompt.

## 10. Future implementation slices, tiers and proof
**NECESSARY first vertical slice (later only after approval):** SDL3 CORE-01 PlatformEvent adapter consumed without new OS event loop; physical keyboard + mouse button/motion + one standard gamepad + pointer/touch semantic baseline where applicable; stable ActionMap/Context/Seat/ActionFrame; remap+conflict+rollback; focus-loss release; headless recorded-input replay; UI/gameplay separation, keyboard alternative and Editor/CLI/MCP authoring parity.
**IMPORTANT:** multiple active gamepads and seat join/reassignment, advanced stick calibration, contextual chords and combos, stick/trigger remapping, touch gestures with accessible alternatives, per-game accessibility preset and robust migration.
**FUTURE/PROVE-OR-DROP:** gyro/accelerometer/motion steering, advanced haptics/force feedback/adaptive triggers/LED, steering wheel/HOTAS/specialized assistive device certification, deep Win GameInput or macOS GCController native bridge, cloud profile sync, third-party controller database updates, touch virtual controller editor, AI-driven adaptive input and anti-cheat.
- No code, actual test, target performance, hardware coverage, accessibility certification, driver or optional dataset is delivered. Exact release class and numerical budgets require owner-approved later increment; all 80 coding WOs remain blocked.
