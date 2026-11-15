# EDIT-07 — Debug, Profiling & Preview Architecture v0.1

**2026-11-15 | P00 RESEARCH ONLY / NOT IMPLEMENTED | [research #276](https://github.com/KayzenRoot/stormline/issues/276) | NLE-P00-WO-002-EDIT-07 | [code #74](https://github.com/KayzenRoot/stormline/issues/74) OPEN/BLOCKED | BASE `64c7ea06a547742209cd11f5d949ab9c8989aa66`.** Catalog order 56/80; 55 researched, 25 pending, all 80 coding WOs blocked.

## 1. Mission, catalog acceptance, ownership
Catalog scope: Play-in-editor, breakpoints, render debugger, statistics and memory/GPU/audio inspector. **Acceptance: "Erro rastreável do projeto até subsistema e asset."** An actual fault must be traced to verified build, project scope, subsystem/operation, AssetId/revision and owner evidence. This is **future functional proof**, not satisfied by documentation or mock UI.

**Formal dependencies ONLY EDIT-01 + CORE-06**, both documentary/ADR PROPOSED. EDIT-01 owns toolkit-neutral shell, panels, shared EditorCommandIdV1, focus/IME/shortcuts/accessibility. CORE-06 owns DiagnosticEventV1, CorrelationContextV1, TraceSpanV1, CounterSampleV1, CrashEnvelopeV1, DiagnosticExportV1, bounded sinks, redaction/retention, offline export. **EDIT-07 is a presentation, inspector and isolated preview orchestrator, not a second diagnostics engine, recorder or crash-handler.**

| Integration owner, NOT direct DAG edge | Existing authority / use by EDIT-07 |
|---|---|
| EDIT-02 / EDIT-03 | ProjectId/grants, scene/entity/source selection and editor navigation; never bypass scene owner |
| CORE-01 / CORE-02 / CORE-03 / CORE-04 / CORE-05 | process/OS, allocator tags, job spans, authoritative TickId and math/time |
| GFX-01/02/03/06/07 | GPU device generation, shader source maps, render passes/barriers/resources/fences, timing/capture and color |
| AUD-01/03/04 | device SampleFrameId/DeviceEpoch, mixer/XRUN, DSP graph processing and music/VO diagnostics; snapshot off RT callback |
| GAME-02 / SIM / WORLD / NET | runtime debugger hooks, language/AST source maps, simulation/physics/network authority |
| DATA-01/02/03/04/05 | VFS scope, AssetId/provenance/import, source CAS/journal/migration, cooked package and hash |
| EDIT-05/06 | authoring source revisions and editor preview intent; share owner runtime evaluator |
| EDIT-07 / QA-03/04 / AI-04/09 | this view; benchmarks/security; authorized redacted paginated AI/MCP inspection |

No added formal dependency edges or approved backend. CORE-06 must continue to function without EDIT-07 UI, GPU, cloud service or paid dashboard. CODE issues [#68](https://github.com/KayzenRoot/stormline/issues/68), [#23](https://github.com/KayzenRoot/stormline/issues/23), [#74](https://github.com/KayzenRoot/stormline/issues/74) remain OPEN/BLOCKED.

## 2. Play-in-Editor state machine and isolation
Proposed preview states: `IDLE -> PREPARING -> VALIDATING -> STARTING -> RUNNING <-> PAUSED -> STOPPING -> STOPPED`, plus `CANCELLED/FAILED/CRASHED/DEVICE_LOST`. Session ID + generation, frozen DATA-04 project revision, DATA-05 asset manifest, build/evaluator version, seed, CORE-04 TickId, GFX/AUD device epochs and CORE-06 trace receipt. A restart changes generation; stale handles/events/leases cannot be reused. A pause/stop acknowledgment is not a claim that physical audio output stopped at a particular sample.

Preview reads frozen source and runs the **same owner evaluator** as game runtime, but session state is isolated (process sandbox candidate vs proved isolated in-process owner world), with copy-on-write and restricted DATA-01 VFS. Default side effects DENIED: arbitrary filesystem writes, network, shell/process, microphone, payments, devices and canonical project mutation. Actual process isolation is a future proof obligation, not a feature delivered by documentation. On cancel/timeout/crash, release owned resources, preserve canonical project and DATA-04 recovery journal. Applying a preview edit to source is a **separate explicit owner-reviewed CAS transaction**, not implicit on Stop.

## 3. Debugger contracts and replay
Breakpoint source locators must be validated by owner (GAME-02/other runtime) against exact AssetId/script revision and AST/bytecode source map; stale source is `UNRESOLVED`, not rebound to a guessed line. Step Frame, Step Tick and Step Instruction are separate capability-gated operations; no fabricated instruction debugger or frame==TickId equality. Conditional breakpoint/watch uses bounded, read-only, typed, owner-allowlisted property paths, not arbitrary expression evaluation/function calls/raw memory. Stack/locals are sanitized owner snapshots with per-read quotas.

Deterministic replay stores build SHA, source/evaluator/asset hashes, seed, typed inputs/events, CORE-04 tick, session generation and explicit nondeterminism flags. CPU/tick-based gameplay events may be compared exactly where owner guarantees; GPU rendering, OS scheduling and physical audio cannot be assumed bit-identical. Mismatch yields typed `REPLAY_INCOMPATIBLE`, never false success.

## 4. Real asset traceability and CORE-06 gap
Existing CORE-06 proposed DiagnosticEventV1 includes schema/build/event/monotonic timestamp/producer sequence/severity/code/subsystem/correlation/bounded attributes. CorrelationContextV1 includes ephemeral session_id and optional frame_id/tick_id/job_id/transaction_id/world_revision/trace_id, **but has no explicit canonical ProjectId/AssetId fields**.

Propose a **CORE-06/DATA-02-owned** versioned bounded typed `DiagnosticAssetLinkV1` extension (or owner-approved bounded typed attributes) carrying scoped opaque ProjectId, SubsystemOwnerId, AssetId, exact revision/hash, OperationCode, optional typed SourceLocatorId, event_id/trace_id/span_id/build_id. EDIT-07 may query/visualize it but must not define its own canonical event schema. If not approved or absent, return `ASSET_CORRELATION_UNSUPPORTED` or `AMBIGUOUS`. Never infer AssetId from path strings, high-cardinality free-form tags or session IDs.

Navigation: incident code/severity/build -> CORE-06 trace/span/time domain -> subsystem/operation -> DATA-02 AssetId/revision/provenance -> owner-approved source map/inspector; show `MISSING/STALE/REDACTED/UNSUPPORTED` explicitly. Producer ordering is per producer; do not fabricate universal cross-thread order. Show dropped events, sample confidence, clock uncertainty and redaction. Diagnostic source text is escaped and must never become an executable UI/AI instruction.

## 5. Profilers and inspectors
Professional panels: Incident Timeline, CPU Frame/Job, GFX Render Graph/Frame Capture, Memory/Asset, GPU/VRAM, Audio DSP/XRUN, Debug Source/Stack/Watch, PIE Viewport, Privacy/Bundle Export. Each reads paginated owner snapshots and CORE-06 typed counters:
- **CPU:** frame/tick/job spans, sampling vs instrumentation, p50/p95/p99 with measured observer overhead and dropped count. Monotonic CPU clock != GPU timestamps.
- **GPU:** GFX-03 render-pass/resources/barriers, device generation/fence, optional calibrated timestamps. Never dereference raw GPU pointers or promise WebGPU timestamp-query availability. External RenderDoc is a native Vulkan/D3D/OpenGL developer option, **not Metal/Web universal**.
- **Memory:** CORE-02 allocator tags plus DATA-02 authorized AssetIds; distinguish reserved/committed/resident/VRAM; aggregate read only, no process memory dump.
- **Audio:** AUD-01 DeviceEpoch/SampleFrameId/XRUN and AUD-03 quantum/latency counters snapshotted off realtime thread. Never allocation/lock/IO/logging in callback.
- **Game/scene:** owner-provided bounded entity/component/physics/network projections, not arbitrary pointer inspection, mutation, private packet body or gameplay authority.

## 6. Professional button registry
All buttons use EDIT-01 `EditorCommandIdV1` shared registry and owner-side capability check, with localized accessible role/name/description, tooltip, icon+text, enabled/disabled reason, shortcut, focus/IME, active session/project, busy/progress/cancel, expected revision and confirmation. GUI/keyboard/palette/CLI/MCP use the same semantic operation, no bypass.

| Button / CommandId candidate | Action | Safety |
|---|---|---|
| Start / `edit7.preview.start`, Stop, Restart | launch/terminate isolated frozen session | deny unapproved sandbox/scope, generation & cleanup receipt |
| Pause/Continue / Step Frame/Tick/Instruction | owner-authorized transport | disabled if runtime lacks hook; different time domains |
| Breakpoint / `edit7.breakpoint.toggle` | source AssetId/revision + owner hook | stale map rejected; no evaluation |
| Watch / `edit7.watch.add` | bounded typed read-only projection | no calls, raw memory or private secrets |
| Trace / `edit7.trace.capture` | CORE-06 on-demand sampled/limited trace | local only, bounded and dropped counters |
| Capture Frame / `edit7.frame.capture` | GFX owner output/receipt | device/capture support, sensitive image review |
| Memory Snapshot / Audio Stats | owner aggregate read-only counters | no process dump, no realtime logging |
| Open Asset / Open Source | DATA-02/source map navigation | ProjectId/revision/capability validated |
| Export Redacted Bundle / `edit7.bundle.export` | CORE-06 DiagnosticExport + DATA-01 grant | preview redaction/retention and explicit consent |
| Copy Trace ID / Compare Sessions | bounded nonsecret correlation / comparable snapshots | no hidden bulk log copy |

Keyboard-only incident/stack/watch/tree navigation, high contrast, reduced motion and real screen-reader role/name/focus are necessary; native UIA/macOS AX/AT-SPI/Web requires real OS proof.

## 7. Security, privacy and platform boundaries
Remote telemetry, upload, crash reporting network listener, cloud dashboard, unique user/device identifiers and raw chat prompts **OFF by default**. Local bounded storage, strict retention/quotas and scoped path checks. Crash envelopes may contain raw minidump references, but minidumps can include arbitrary memory, credentials and private assets; raw dump read/export is OUT OF SCOPE pending separate HIGH_ASSURANCE authorization. A redacted event bundle is not equivalent to a safely redacted dump. Crash signal handler uses only OS-safe preinitialized operations; no allocation/locks/log formatting. No arbitrary process attach/watch eval.

Native Windows/Linux X11+Wayland/macOS Apple Silicon, headless and Web differ. RenderDoc lacks Metal; Apple Xcode Metal debugger is developer-side reference. WebGPU GPU timestamp-query is optional/privacy-constrained; Chrome DevTools Protocol is privileged and not a stable public third-party API. Report `UNAVAILABLE/NOT_ENABLED/UNSUPPORTED`, not zero or success.

## 8. Scope and gates
**NECESSARY research:** asset-correlated CORE-06 contract gap, PIE isolation, owner debugger hooks, CPU/GPU/memory/audio inspectors, button semantics, redaction/consent, cross-platform capabilities, 128 future tests and benchmarks. **IMPORTANT:** deterministic replay, GFX frame resource inspection, trace diff/offline viewer, stack/locals with owner proof. **FUTURE:** remote attach, cloud crash dashboard, collaborative debugging, AI privileged writes, live shader patch and full memory debugger. **OUT OF SCOPE:** any runtime/editor code, SDK install, process attach, raw crash export, network/telemetry server, arbitrary eval, numeric performance claims, release approval and unlocking code.

[ADR-0059](../adr/0059-edit-07-isolated-debug-profile-preview.md) · [Technology matrix](../research/edit-07-debug-profile-technology-license-matrix.md) · [API](../contracts/edit-07-debug-profile-api.md) · [128 tests](../testing/edit-07-acceptance-matrix.md) · [Benchmark](../research/edit-07-debug-profile-benchmark-protocol.md).
