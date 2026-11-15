# EDIT-07 — Typed Debug, Profiling, Preview and Asset Correlation API v0.1

**P00 PROPOSAL ONLY | 2026-11-15 | [research #276](https://github.com/KayzenRoot/stormline/issues/276) | BASE `64c7ea06a547742209cd11f5d949ab9c8989aa66`.** Logical schema and commands, not compiled C++ headers, stable ABI, actual debug service, profiler SDK or privilege grant. CORE-06 owns diagnostics; EDIT-01 commands; EDIT-07 orchestration and visualization only.

## 1. Existing owner contracts reused without redefinition
| Type | Existing proposed fields and invariants | Owner |
|---|---|---|
| `DiagnosticEventV1` | schema_version, build_id/commit, event_id, monotonic_time_ns, per-producer sequence, subsystem, severity/code, correlation, bounded typed attributes | CORE-06 |
| `CorrelationContextV1` | ephemeral session_id, optional frame_id/tick_id/job_id/transaction_id/world_revision/trace_id | CORE-06; currently **no canonical ProjectId/AssetId** |
| `TraceSpanV1` | start/end monotonic time domain, parent/child span IDs, thread lane, outcome | CORE-06; no universal total thread order |
| `CounterSampleV1` | metric_id, units, sample time, bounded dimensions, confidence/availability, value | CORE-06; reject NaN/Inf/overflow |
| `CrashEnvelopeV1` | build/symbol/platform, stack/local minidump ref, bounded recent events | CORE-06; minidump sensitive |
| `DiagnosticExportV1` | version/schema, redaction profile, encoding, data scope, manifest checksum, build IDs | CORE-06; local consent required |
| `EditorCommandIdV1` / `EditorCommandInvocationV1` / `EditorCommandReceiptV1` | stable registry ID, MENU/SHORTCUT/PALETTE/MCP/CLI origin, focus scope, actor, expected revision and owner receipt | EDIT-01 |

## 2. Proposed integration types (NOT adopted ABI)
| Type | Fields, invariants and security | Required owner |
|---|---|---|
| `DiagnosticAssetLinkV1` | scoped opaque ProjectId, SubsystemOwnerId, AssetId, exact AssetRevisionHash, OperationCode, optional SourceLocatorId, event/trace/span/build refs, bounded version | **CORE-06/DATA-02 extension request**, not an EDIT-07 diagnostic schema |
| `AssetDiagnosticResolveReceiptV1` | actor/project grant, AssetId+revision, importer/cook/source provenance, FOUND/STALE/MISSING/REDACTED/UNSUPPORTED | DATA-02/EDIT-02/EDIT-03; no arbitrary host path |
| `DebugPreviewSessionV1` | session ID/generation, ProjectId/grant, frozen source/asset manifest digest, target, seed, CORE-04 TickId, device/audio epochs, sandbox policy, owner evaluator/version and cancel lease | CORE-01/EDIT-02/DATA-04 plus runtime owner |
| `DebugPreviewReceiptV1` | PREPARING/VALIDATING/STARTING/RUNNING/PAUSED/STOPPING/STOPPED/CANCELLED/FAILED/CRASHED/DEVICE_LOST, generation, source/evaluator digest, cleanup proof, last-good | preview runtime owner; not UI assertion |
| `DebuggerBreakpointV1` | breakpoint ID, ScriptAssetId/revision, AST/instruction/source-map locator, resolved status, optional owner-condition capability | GAME-02/runtime owner; no arbitrary eval |
| `DebuggerWatchRefV1` | typed read-only allowlisted property path, owner, depth/cardinality/time cap, schema/revision, redaction | GAME-02/WORLD/data owner, no raw pointer or function |
| `DebuggerStackFrameV1` | thread/tick, source-map line/column/instruction, owner build, locals snapshot ref and confidence | runtime owner |
| `DebugStepRequestV1` | CONTINUE/PAUSE/STOP/STEP_FRAME/STEP_TICK/STEP_INSTRUCTION/STEP_OVER/INTO/OUT, generation/owner capability | runtime owner, scopes/time domains distinct |
| `DebugReplayManifestV1` | build/evaluator/asset hashes, seed, input/event log, TickId/frame/timebase, owner device epochs, nondeterminism flags | CORE-04/runtime owner/CORE-06 |
| `ProfilerCapturePlanV1` | OFF/MINIMAL/SAMPLED/DEEP, metric categories, duration/sampling, memory/disk quota, clock domains, redaction and consent | CORE-06 policy |
| `ProfilerCaptureReceiptV1` | capture ID, schema/build, start/end, event samples/drops, overhead, files/bytes, availability and clock confidence | CORE-06 |
| `GpuFrameDebugReceiptV1` | GFX frame/pass/resource IDs, device generation/fence, optional queue calibrated timestamps, availability, capture ID | GFX-01/03, opaque GPU IDs |
| `MemoryAssetSnapshotV1` | CORE-02 reserved/committed/resident tagged totals, DATA-02 scoped AssetIds, units/confidence | CORE-02/DATA-02/GFX-03, aggregate only |
| `AudioProfilingSnapshotV1` | AUD-01 DeviceEpoch/SampleFrameId/XRUN, AUD-03 quantum/latency/tail counters with off-RT snapshot provenance | AUD-01/03 |
| `DebugBundleExportPreviewV1` | selected event IDs, redaction manifest, privacy warnings, byte quota, retention, scoped local target | CORE-06/DATA-01 |
| `DebugBundleExportReceiptV1` | DiagnosticExportV1, policy version, manifest/readback hash and DATA-01 destination grant | CORE-06/DATA-01, no network |
| `Edit7CommandInvocationV1` | shared EditorCommandIdV1, UI/SHORTCUT/PALETTE/CLI/MCP origin, actor, project/session generation, expected revision, idempotency | EDIT-01 + owner authorization |
| `Edit7CommandReceiptV1` | ACCEPTED/REJECTED/CANCELLED, owner, operation/session IDs, safe trace/correlation ID, cleanup/readback and reason | target owner |
| `Edit7ErrorV1` | code, owner/stage, incident/session/source locator, retryability, redacted diagnostics | owning service |

## 3. Shared button/command operations
Every toolbar button is an EDIT-01 EditorCommandIdV1 registration with localized role/name/description, tooltip, icon+text, shortcut, enabled predicate/disabled reason, focus/IME, actor/capability, expected project/source revision, undo domain, busy/progress/cancel and confirmation. Owner rechecks permission on CLI/MCP even if UI disables the button.

| CommandId candidate | Input -> typed output | Guard |
|---|---|---|
| `edit7.preview.start` / `edit7.preview.stop` / `edit7.preview.restart` | frozen source/sandbox/target -> preview lifecycle receipt | PREVIEW_ISOLATED, deny host effects, bounded cleanup |
| `edit7.preview.pause` / `edit7.preview.continue` | generation/tick -> owner transport receipt | explicit runtime support, no gameplay writes |
| `edit7.debug.step.frame` / `edit7.debug.step.tick` / `edit7.debug.step.instruction` | DebugStepRequest -> owner acknowledgment | separate time domains, disabled if unsupported |
| `edit7.debug.breakpoint.toggle` | exact ScriptAssetId/source-map/revision -> owner breakpoint receipt | source validation; no arbitrary condition eval |
| `edit7.debug.watch.add` / `edit7.debug.watch.remove` | read-only typed allowlisted property -> bounded snapshot | no functions, raw memory or secret access |
| `edit7.trace.capture` / `edit7.trace.cancel` | ProfilerCapturePlan -> CORE-06 receipt | local bounded ring, dropped samples and retention |
| `edit7.frame.capture` | GFX frame/pass IDs/device generation -> GFX receipt | device capability/fence, privacy review |
| `edit7.memory.snapshot` / `edit7.audio.inspect` | scoped owner snapshot request -> aggregates/counters | no minidump or callback logging |
| `edit7.incident.open` / `edit7.asset.navigate` / `edit7.source.navigate` | event ID, typed AssetId/source locator -> sanctioned view | exact source revision and ProjectId scope |
| `edit7.bundle.preview` / `edit7.bundle.export` | redaction/retention/local destination -> CORE-06 manifest/readback | explicit consent; raw dumps need separate HIGH_ASSURANCE |
| `edit7.trace.copy-id` / `edit7.session.compare` | safe trace ID/two schema-compatible sessions -> copy/diff | no hidden bulk log/secret copy |

## 4. Invariants and fault taxonomy
- CORE-06 asset correlation **requires explicit owner approval**. If missing, return `E07_ASSET_CORRELATION_UNSUPPORTED` and never fabricate AssetId from path. Stable source AssetId/revision navigates DATA-02 after scope check.
- PIE state `IDLE -> PREPARING -> VALIDATING -> STARTING -> RUNNING <-> PAUSED -> STOPPING -> STOPPED`; crash/cancel/device loss invalidates generation and preserves canonical DATA-04 source. If isolation unproved => no preview start.
- Debugger watch is bounded typed read-only projection, not eval or side effects; instruction-stepping unsupported by runtime returns explicit status.
- CPU/GPU/AUD measurements include units/clock/calibration/availability/confidence/drops. `NOT_ENABLED/REDACTED/UNSUPPORTED/UNKNOWN` are not zero.
- Bundle preview/consent/export is local and redacted; a binary crash dump is not safe to export via ordinary diagnostics permission.
- No hidden telemetry/network listener, process attach, full memory read, unsandboxed script execution, GPU pointer or audio callback I/O.
- Error names: `E07_PREVIEW_ISOLATION_UNPROVEN`, `E07_SESSION_GENERATION_STALE`, `E07_RUNTIME_HOOK_UNSUPPORTED`, `E07_BREAKPOINT_SOURCE_STALE`, `E07_WATCH_EVAL_FORBIDDEN`, `E07_ASSET_CORRELATION_UNSUPPORTED`, `E07_ASSET_AMBIGUOUS`, `E07_PROJECT_SCOPE_DENIED`, `E07_METRIC_NOT_ENABLED`, `E07_GPU_TIMESTAMPS_UNAVAILABLE`, `E07_AUDIO_SNAPSHOT_UNAVAILABLE`, `E07_CAPTURE_BUDGET_EXCEEDED`, `E07_MINIDUMP_SENSITIVE`, `E07_EXPORT_CONSENT_REQUIRED`, `E07_REDACTION_UNVERIFIED`, `E07_REPLAY_INCOMPATIBLE`, `E07_RECOVERY_REQUIRED`.

[Architecture](../architecture/edit-07-debug-profiling-preview.md) · [ADR-0059](../adr/0059-edit-07-isolated-debug-profile-preview.md) · [Tests](../testing/edit-07-acceptance-matrix.md) · [Benchmark](../research/edit-07-debug-profile-benchmark-protocol.md).
