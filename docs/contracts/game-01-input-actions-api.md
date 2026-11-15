# GAME-01 — Device, Action Mapping, Seat, Focus, Replay and Accessibility Semantic Contracts v0.1

**Issue #208 | WO NLE-P00-WO-002-GAME-01 | Future code #56 OPEN/BLOCKED.** Proposed semantic type names, not C++ headers, wire schema, binary ABI, implemented engine, SDK adapter, physical device input or executed tests.

## 1. Versioned typed contract inventory
| Contract | Proposed fields | Owner / validation / failure |
|---|---|---|
| `InputRuntimeHandleV1` | Project/WorldId, EngineEpoch, InputRuntimeGeneration, host/headless tier | GAME-01 consumer lifecycle bound to CORE-01 host; reject stale/foreign world |
| `PlatformInputEventV1` | CORE-01 `PlatformEventV1` adapter, WindowId/WindowEpoch, DeviceId/DeviceEpoch, host monotonic timestamp precision, ordered sequence, origin, payload | CORE-01 sole OS event owner; no native SDL/DOM pointer in API |
| `InputDeviceHandleV1` | transient opaque slot/generation, device class, connection epoch, backend capability tier | GAME-01 private lookup, no serial/MAC/HID path/fingerprint; reject stale |
| `InputDeviceCapabilitiesV1` | keyboard position/logical keys, mouse abs/relative, sticks/triggers, pointer count, optional gyro/haptics, layout, privacy/permissions, confidence | actual CORE-01/PLAT-03 measured support or UNKNOWN, not assumed |
| `InputDeviceStateV1` | last valid sequence/time, digital held edges, signed axes, pointer positions/deltas, status READY/LOST/UNKNOWN, focus epoch | bounded normalized channels, NaN/Inf and illegal transitions rejected |
| `PlayerSeatV1` | PlayerSeatId/epoch, local/server role, active DeviceIds, assignment revision, join/unjoin, primary/secondary device, conflict policy | GAME-01 routing local intent only; GAME/NET ultimate player authority |
| `InputControlTokenV1` | device class, PHYSICAL_KEY/LOGICAL_KEY/MOUSE_BUTTON/RELATIVE_AXIS/GAMEPAD_BUTTON/GAMEPAD_AXIS/POINTER/TOUCH, typed code and unit | stable Stormline enum, never SDL/Windows/DOM raw ABI |
| `InputActionDescriptorV1` | ActionId/GUID, project namespace, DIGITAL/AXIS1D/VECTOR2D, label localization key, allowed contexts, fallback required, revision | DATA-02 stable identity, immutable compiled schema |
| `InputBindingV1` | BindingId, ActionId, control token, modifiers, trigger PRESS/RELEASE/HOLD/TAP/DOUBLE_TAP/TOGGLE, order/priority, consume flag, device predicate | finite graph; bounded chord depth, trigger durations, valid device classes |
| `InputCompositeV1` | axis arrows/trigger pair/vector sources, SUM_CLAMPED/MAX_ABS/FIRST_ACTIVE policy, normalization/inversion | deterministic action type/unit compatible; never unchecked overflow |
| `InputAxisTransformV1` | signed range, deadzone RADIAL/AXIAL, outer zone, sensitivity, inversion, saturation, monotonic curve, enter/exit hysteresis | reject NaN/Inf/deadzone >= 1/nonmonotonic invalid curve |
| `InputActionMapV1` | MapId/AssetId/revision, action descriptors, binding table, conflict policies, required fallback actions, target profile, provenance | DATA-04 authoring CAS, DATA-02 identity, compiled off-frame immutable |
| `InputActionPlanV1` | PlanId/map hash, target capability fingerprint, ordered binding indices, context predicates, state slot offsets, bounded worst work | GAME-01 compiled validated plan; no unbounded per-tick expressions |
| `InputContextV1` | ContextId, GAMEPLAY/MENU/TEXT_EDIT/CINEMATIC/EDITOR/REMAP, owner, priority, activation generation, focus rules | UI/Editor actual focus owner; GAME-01 context eligibility only |
| `InputFocusRouteV1` | WindowEpoch, focus tree revision, modal/dialog/text target, pointer capture token, context consume/propagate masks | UI/Editor owns, GAME-01 read-only; never capture passwords/composition |
| `InputAccessibilityProfileV1` | PlayerSeat/MapId, one-handed preset, hold-toggle, timings, stick inversion/deadzones, pointer alternative, repeated-press mitigation, reset/recovery binding | versioned local user-owned preference, no forced assistive capture |
| `InputRemapRequestV1` | principal/project/user scope, map expectedRevision, capture target ActionId, device class, timeout, conflict SWAP/REPLACE/KEEP/REJECT, preview | UI explicit focus/consent, DATA-04 CAS, never background keyboard |
| `InputRemapReceiptV1` | requested/replaced binding, conflict graph, fallback protected, saved revision, errors/rollback action | deterministic preview/result, last-good recovery on failure |
| `InputActionFrameV1` | TickId, SimulationEpoch, PlayerSeatId/epoch, map hash/revision, DeviceEpoch set, action digital edges, analog vectors, consumer/capture mask, confidence | GAME-01 deterministic resolver; GAME/NET validates external remote action |
| `InputActionReceiptV1` | EventId, source seq/DeviceEpoch, action frame TickId, accepted/consumed/suppressed/late/lost/reset, reason, latency uncertainty | never assert hardware-origin provenance, protected privacy |
| `InputEventJournalV1` | recording schema, approved role, original/normalized event order, profile hashes, epochs, TickId mapping, fixture provenance and optional redaction | CORE-06 opt-in diagnostics or test harness, no text/password/IME/private IDs |
| `InputReplayPlanV1` | journal hash, version compatibility, run seed, tick schedule, expected action-frame digest, strict/tolerant mode | test/headless only by default; not live physical injection |
| `InputMappingMigrationPlanV1` | from/to map/schema revisions, semantic diff, renamed ActionIds, unknown fields, conflict/rollback, project/user scope | DATA-04 migration, last-good, no OS-global config edits |
| `InputCapabilityReceiptV1` | OS/browser/window/device profile, feature supported/unknown/denied, focus/permission, SDL/native/Web adapter revision, fallback | explicit capability and consent; no forced pointer lock or gamepad reads |
| `InputErrorV1` | typed error, operation/role, expected/current revision/epoch, recovery, bounded redacted diagnostics | preserve privacy and typed failure, never silent stuck action |

## 2. Semantic operations and authority
1. `RegisterInputHost(hostEventBridge, engineEpoch)` → CORE-01-provided event source/FocusEpoch/DeviceEpoch; no independent SDL init/pump.
2. `InspectInputCapabilities(principal, deviceClass)` → scoped CORE-01/PLAT-03 feature report without hardware fingerprint or untrusted raw HID.
3. `ObserveDeviceEvent(platformEvent)` → normalized state and bounded edge journal, reject stale/foreign window/connection.
4. `AssignDeviceToSeat(device, seat, expectedRevision, role)` → idempotent ownership, conflict/join/unjoin and disconnect fallback.
5. `StageActionMap(sourceMap, expectedRevision, principal)` → DATA-04 CAS, action schema/chord/analog safety, no private filesystem access.
6. `CompileActionMapPlan(map, capabilities, contextPolicy)` → worker validation/compilation, fixed bounded per-tick work; publish immutable plan at fence.
7. `ActivateInputContext(context, expectedFocusRevision, principal)` → UI focus owner approval, safe held-release on context change, no gameplay action while text/IME/modal active.
8. `SampleInputFrame(tickPlan, currentDevices, focusRoute, seat)` → consume ordered edges and sample analog to one `InputActionFrameV1` for CORE-04 TickId; preserve button press+release within same tick.
9. `ResolveActionFrame(frame, consumer, role)` → apply capture/consumption, gameplay/GUI routing and authorized GAME/NET action intents; no direct game state mutation.
10. `BeginRemapCapture(focusedView, actionId, deviceClass, deadline, principal)` → explicit scoped capture UI consent; cancel/timeout, never capture a password field.
11. `PreviewRemapAndConflicts(request, map, activeContexts)` → deterministic conflict graph with protected Back/Cancel and accessible fallback.
12. `CommitRemap(request, previewHash, expectedMapRevision)` → DATA-04 staged CAS/rollback, persist user profile separately from developer defaults.
13. `ApplyAccessibilityInputProfile(seat, profile, expectedUserSettingsRevision)` → bounded hold/deadzone/toggle/alternatives with tested recovery binding.
14. `RecordInputTrace(scope, consent, redactionPolicy)` → CORE-06 redacted/opt-in input event trace; default telemetry contains counters only.
15. `ReplayInputJournal(testHarness, compatibleSchema, exactTicks)` → headless controlled test injection, deterministic resolver checks; live injection remains disabled.
16. `SuspendOrDeviceLost(windowOrDeviceEpoch)` → synthetic releases, zero axes, cancel gestures and invalidate stale mappings/seat handles.

## 3. Typed failure conditions
`INPUT_HOST_UNAVAILABLE`, `INPUT_HOST_EPOCH_STALE`, `INPUT_WRONG_WINDOW`, `INPUT_WINDOW_NOT_FOCUSED`, `INPUT_DEVICE_GONE`, `INPUT_DEVICE_GENERATION_STALE`, `INPUT_UNKNOWN_CAPABILITY`, `INPUT_PERMISSION_DENIED`, `INPUT_WEB_GESTURE_REQUIRED`, `INPUT_POINTER_LOCK_UNAVAILABLE`, `INPUT_TEXT_COMPOSITION_ACTIVE`, `INPUT_EVENT_QUEUE_FULL`, `INPUT_EVENT_ORDER_INVALID`, `INPUT_EVENT_TIMING_UNCERTAIN`, `INPUT_DEVICE_UNASSIGNED`, `INPUT_SEAT_CONFLICT`, `INPUT_ACTION_NOT_FOUND`, `INPUT_ACTION_TYPE_MISMATCH`, `INPUT_BINDING_CONFLICT`, `INPUT_BINDING_UNSAFE`, `INPUT_CHORD_LIMIT_EXCEEDED`, `INPUT_ANALOG_NONFINITE`, `INPUT_DEADZONE_INVALID`, `INPUT_ACTION_MAP_REVISION_STALE`, `INPUT_CONTEXT_STALE`, `INPUT_CONTEXT_NOT_AUTHORIZED`, `INPUT_CAPTURE_NOT_FOCUSED`, `INPUT_REMAP_TIMEOUT`, `INPUT_REMAP_CANCELLED`, `INPUT_USER_SETTINGS_CONFLICT`, `INPUT_RECOVERY_BINDING_REQUIRED`, `INPUT_REPLAY_SCHEMA_MISMATCH`, `INPUT_REPLAY_NOT_AUTHORIZED`, `INPUT_CLIENT_ACTION_UNTRUSTED`, `INPUT_RIGHTS_OR_PRIVACY_DENIED`, `INPUT_RESOURCE_EXHAUSTED`, `INPUT_INTERNAL_FAILURE`.

## 4. Required invariants
- CORE-01 exclusively pumps native OS input and manages focus/lifecycle; GAME-01 never calls SDL_PollEvent or native keyboard hooks as a separate owner.
- CORE-04 is sole simulation TickId authority. Bounded normalized input edge journal publishes action frames on tick fence; render FPS cannot advance gameplay actions.
- No key/IME/password text content, persistent HID serial or raw OS handle in public ActionMap, journal, telemetry or MCP.
- UI/Editor owns actual focus and composition; GAME-01 consumes a versioned route. Text edit context suppresses gameplay shortcuts.
- Device loss/focus loss/overflow leads to deterministic release/reset and receipt; no stuck action or stale seat reuse.
- Remapping uses revisioned DATA-04 transactions with preview/rollback, protected recovery/Back/Cancel and explicit user intent.
- External network action frames are untrusted and GAME/NET checks authority. MCP can only author authorized maps, not inject live physical input.
- Native/Web/headless capabilities are reported separately; no universal guarantee for physical keyboard separation, Web Gamepad, pointer lock, gyro, haptics, accessibility hardware or low latency.
- Names here are only semantic proposals; exact ABI, codec, package, schema and performance thresholds require later approval.
