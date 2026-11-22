# CORE-06 INTERNAL_ONLY Diagnostics Governance Contract v0 (NLE-PRPLAN-CORE-06-01)

**Status:** `CONTRACT PROPOSAL / NOT IMPLEMENTED / NO CODE AUTHORIZED`. **Base:** `326f83fdfda026d3eb254010f3a82107c3743eb7`. **ADR:** [ADR-0109](../adr/0109-core-06-governance-slice.md), [ADR-0008](../adr/0008-core-06-observability-policy.md) planning-only. **WO:** [NLE-PRPLAN-CORE-06-01](../work-orders/NLE-PRPLAN-CORE-06-01.md).

## Objective

Record ownership, privacy/security boundaries, release/risk classes and the gates required before CORE-06 implementation. No API, dependency, binary format, network endpoint, crash handler, profiler integration, public ABI or release is authorized.

## Admission and boundaries

- Formal `CORE-01` dependency remains; admission is limited to completed `CORE-01-03/-06/-07/-08/-12/-13` capabilities under ADR-0109/ADR-0086. CORE-01 module completion is **not** claimed.
- CORE-06 owns the typed diagnostic facade, local sink policy, bounded buffers, correlation envelope and local export contract.
- CORE-01 owns OS crash/process lifecycle and native capability signals; CORE-02 memory; CORE-03 job scheduling/IDs; CORE-04 ticks; GFX GPU timing/device loss; AUD realtime constraints; DATA provenance; EDIT/QA/AI authorized projections.
- No editor UI, cloud APM, paid dashboard, graphics device, network, MCP provider or third-party library is a CORE-06 core dependency.

## Policy invariants

1. **Local-first.** Console/local file sinks only in the first slices; no remote telemetry, crash upload, hidden listener or network endpoint.
2. **Typed and bounded.** Events carry schema version, build identity, monotonic timestamp domain, producer sequence, severity, stable reason/code, subsystem and bounded attributes. No unbounded strings, arbitrary maps or secrets.
3. **Per-producer order.** No false total order across worker threads; sequence is preserved per producer.
4. **Fail-closed drops.** Full buffers increment a dropped counter with a bounded reason; critical records get bounded fallback. No silent loss claim.
5. **Redaction at source/export.** Tokens, keys, absolute sensitive paths, project/user content and network identifiers are suppressed by default.
6. **No realtime blocking.** Audio/render hot paths must not log, allocate, block or perform disk I/O; only preallocated/atomic reporting is permitted.
7. **No crash claim.** Crash capture, dump parsing, symbolication and upload are separate future gates; no universal crash-capture guarantee.
8. **No performance claim.** Zero/near-zero disabled cost is a future measurement objective, not a guarantee.
9. **Release boundary.** Internal-only; no public SDK/ABI, distribution, telemetry service or brand claim.

## First-slice scope (future, blocked)

Subject to `CORE-06-02` contract:

- `CORE-06-03` logs: owned severity/reason/code, bounded message/attributes, console/local sink, drop accounting.
- `CORE-06-04` traces/spans: monotonic start/end, parent/child IDs, thread lane, outcome, bounded local export.
- `CORE-06-05` counters: metric ID, numeric value, unit, bounded dimensions, non-finite/overflow rejection.
- `CORE-06-06..08` crashes/profiling/telemetry remain blocked pending separate G6 and security/platform decisions.

No visual, network, cloud, crash-dump or profiler feature is implemented by this governance packet.

## Gate state after merge

- Manifest root `CORE06_01_APPROVED_GOVERNANCE_ONLY`: **691 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 46 `COMPLETED`, 11 approved gates**.
- `CORE-06-01` becomes `APPROVED_GOVERNANCE`; `CORE-06-02`..`-10` remain `PLANNED_BLOCKED`.
- Selector denies every ID; registry byte-identical; 80/80 module WOs `BLOCKED`.

## Stop / rollback / security

Stop on stale source, missing admission, third-party selection, network/telemetry/crash upload enabled by inference, secret/absolute-path exposure, unbounded attributes, realtime blocking, public ABI/release claim or HIGH/CRITICAL. Unmerged: close the branch. After merge: normal revert PR; never force push.

No implementation is authorized by this governance contract. `CORE-06-02` requires its own audited contract and `CORE-06-03` its own G6.
