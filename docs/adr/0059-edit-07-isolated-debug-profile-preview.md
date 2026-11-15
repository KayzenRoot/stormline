# ADR-0059 — Isolated PIE and Typed Diagnostic/Profiler View over CORE-06

**STATUS: PROPOSED / NOT ADOPTED / NOT OWNER-APPROVED / NO CODE AUTHORIZATION | 2026-11-15 | [research #276](https://github.com/KayzenRoot/stormline/issues/276) | NLE-P00-WO-002-EDIT-07 | code #74 OPEN/BLOCKED | BASE `64c7ea06a547742209cd11f5d949ab9c8989aa66` | NLE-D009 license OPEN.**

## Context
Catalog acceptance: **"Erro rastreável do projeto até subsistema e asset."** EDIT-01 owns shell/EditorCommandIdV1, CORE-06 owns events/spans/counters/crash/offline export. Current CORE-06 CorrelationContextV1 has session/frame/tick/job/transaction/world/trace references but **no formal ProjectId/AssetId link**. The editor must not invent that authority. Neither GUI/runtime nor profiler SDK is built.

## Proposed decision, not adopted
1. EDIT-07 owns visualization, isolated preview orchestration and inspector UX only; **CORE-06 owns canonical DiagnosticEventV1, CorrelationContextV1, TraceSpanV1, CounterSampleV1, CrashEnvelopeV1, DiagnosticExportV1**, buffering, redaction, retention, collection/exports. No second telemetry engine.
2. Formal DAG stays **EDIT-01 + CORE-06 only**. EDIT-02/03/05/06, GAME-02, DATA, GFX, AUD, CORE, SIM/WORLD/NET, QA, AI/MCP are integration owners, not additional formal edges.
3. CORE-06/DATA-02 must approve a **versioned bounded typed asset-correlation extension** or typed attributes carrying scoped ProjectId, SubsystemOwnerId, AssetId, revision/hash, OperationCode and trace/span/event/source refs. Until approved: CORRELATION_UNSUPPORTED/AMBIGUOUS; never infer assets from raw path strings or create a parallel EDIT-07 event schema.
4. PIE uses frozen DATA-04 source revision, immutable owner assets, versioned session generation and **proved isolation** (process sandbox candidate or rigorously tested world isolation); copy-on-write runtime state, denied external side effects by default, bounded stop/crash cleanup, no implicit project commit. Same owner runtime evaluators used by export.
5. Breakpoint/step/stack/watch uses only GAME-02/owner-approved hooks. Watch is allowlisted bounded read-only typed path, **not arbitrary evaluation**; unsupported instruction stepping disabled and clearly explained.
6. CPU/GPU/memory/audio panels present CORE-06 and owner-specific snapshots only. Compare Tracy/Perfetto/minimal native baseline objectively; no mandated remote profiler listener. GFX owns GPU capture/fences/calibration, AUD owns realtime counters and atomic nonblocking snapshot.
7. Crash/local diagnostic export is OFFLINE-FIRST. No hidden telemetry, cloud, listener, upload or user/machine fingerprint. Raw dumps/frame captures can leak secrets and require separate HIGH_ASSURANCE decision, not ordinary redacted bundle permission.
8. All toolbar buttons use EDIT-01 shared EditorCommandIdV1, localized accessible labels/disabled reasons, focus/IME, progress/cancel, shortcut, undo scope, owner actor and same GUI/CLI/MCP checks.
9. Replay evidence pins build/evaluator/AssetId revisions/seed/CORE-04 ticks and device epochs, with explicit nondeterminism: CPU owner tick receipts may match; GPU visuals and physical audio not presumed identical.
10. Every metric has units, time domain, availability, sampling/overhead/drop count and confidence. UNKNOWN/REDACTED/UNSUPPORTED/NOT_ENABLED must never be shown as measured zero.

## Alternatives and trade-offs
| Alternative | Benefit | Rejection/constraint |
|---|---|---|
| New profiler/trace engine in EDIT-07 | full control | duplicates CORE-06, breaks canonical contracts |
| Always-on Tracy listener | deep interactive profiling | networking/privacy/footprint, must be opt-in |
| Always-on Perfetto SDK | offline trace inspection | footprint and backend permissions, owner chooses after evidence |
| Logs-only printf | minimal dependency | inadequate asset/project/trace correlation |
| PIE shares authoritative editor world and files | easy setup | risks source corruption and external side effects |
| Arbitrary watch eval / remote attach | power | RCE/privilege and nondeterministic mutations |
| Auto-upload minidumps | rich diagnosis | may upload secrets/private memory, consent violation |
| Universal RenderDoc capture | powerful native GFX | no Metal; WebGPU timing optional |
| Privileged Chrome DevTools Protocol listener | browser debugging | unsupported public integration, security risk |

## Risks and proof before approval
Project corruption on preview stop/crash, process escape, watch-eval RCE, stale source-map binding, source/asset misattribution, trace-cardinality flood, GPU/device loss, audio callback stall, minidump/privacy leak, Web high-resolution timing and AI/MCP cross-project access. Require owner-approved CORE-06 asset correlation, EDIT-01 buttons, actual preview/game runtime hooks and sandbox, DATA/GFX/AUD owner receipts, crash-safe local collection, verified redaction, multi-OS/headless/Web and accessibility tests, measured profiler overhead p50/p95/p99, exact SDK licenses/SBOM and 128 acceptance tests. Release class UNDECIDED; NLE-D009 OPEN.

**No technology or API is approved. ADR-0059 remains PROPOSED; research cannot unblock code #74 or any 80 coding packets.**
