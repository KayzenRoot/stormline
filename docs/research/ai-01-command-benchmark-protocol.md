# AI-01 — Reproducible Headless Kernel, Transaction, Parity and Security Benchmark Protocol

**P00 PROTOCOL ONLY | 2026-11-15 | [research #281](https://github.com/KayzenRoot/stormline/issues/281) | code #75 OPEN/BLOCKED.** No CLI/editor/MCP adapter/command bus, scene runtime or build/export binary exists. No performance, security or compatibility test has been run; numeric targets TBD.

## 1. Reproducibility manifest and target split
For every future run pin main/engine SHA, CommandId/descriptor+schema hash, CORE/DATA/WORLD/GAME versions, dataset/source semantic digests, project/asset IDs, platform OS/kernel/compiler/CPU/RAM/SSD, editor/window or true headless mode, locale/timezone/UTF-8, storage/fsync settings, seed/ID strategy, host authentication/grants, MCP protocol/SDK/peer version, CLI flags, cold/warm cache, number of workers, requested side effects, provenance/rights and trace scope. Native Windows/Linux X11/Wayland/macOS Apple Silicon and browser adapter separately, never infer all supported from Linux CI. Compare genuine GUI/CLI/MCP with same versioned semantic operation on **fresh clones of identical source**.

Use >=3 independent runs/seeds, >=30 warmups for steady-state and >=1000 timings when reporting p99. Record exact raw logs, statistical assumptions, checksums and owner receipts; trials that fail validation do not count as successes. Cold start includes process spawn, schema/bootstrap setup and first command; warm request separately excludes transport start.

## 2. Fixtures
| ID | Scene/data and operation | Measurements |
|---|---|---|
| PA-01 | blank project creation/open, simple scene with 50 entities via UI and CLI | source semantic digest, operation/receipt parity and UI time-to-confirm |
| PA-02 | 10k entities with stable IDs, components, typed asset refs and explicit child order | inspect/query, patch preview/commit, CAS conflicts and p50/p95/p99 |
| PA-03 | 100k entities/10k prefabs, nested variants depth 1/4/8 | WORLD-02 fanout/rebase 3-way conflicts, source/runtime receipts |
| PA-04 | 2D/UI scene, 2.5D world and 3D prefab fixtures with imported asset rights | parity and source reference integrity |
| PA-05 | GAME-02 typed script source/graph validation and revision bump | authoring operation parity, sandbox rejection, compile validation cost |
| TX-01 | 32 concurrent patchers same expected revision with distinct idempotency keys | one accepted source CAS, conflict/rebase receipts, no lost update |
| TX-02 | 100 repeated same-key retries across timeout, worker restart and durable intent | exactly-once **effect** within owner receipt policy, recovery/duplicate rate |
| TX-03 | crash between stage/intent/fsync/readback, simulated disk full | recovery_required, prior-good source, journal replay and no false commit |
| JOB-01 | allowlisted future build/export valid+unsupported target | async JobHandle progress/cancel/owner manifest, no host shell process injection |
| SEC-01 | hostile deep JSON, duplicate keys, invalid UTF-8, huge int/float/NaN, unknown required schema | parser CPU/RSS/byte quotas and stable denial codes |
| SEC-02 | cross-project actor, revoked grant, forged origin, symlink/path traversal, MCP prompt injection | no side effects, redacted audit, no unintended network |
| MCP-01 | genuine 2026-07-28 stateless peer vs real older 2025 handshake peer | declared support, compatibility/denial and tool/task semantics |
| UI-01 | keyboard/IME/screen-reader button workflow, no-GUI CPU-only CLI, Web feature fallback | accessibility/manual parity and truthful availability |

## 3. Metrics and oracles
- **Correctness:** independently reopen DATA-04 source and compute algorithm/version-tagged semantic digest, inspect stable Scene/Prefab/AssetId graph, typed field units/order/reference integrity. If owner allocates new IDs, require explicit bijective remap and graph equivalence. Manual vs CLI vs authorized MCP **same semantic outcome** on equal initial state.
- **Performance:** decode/schema validate, owner lookup/authz/preview, commit/CAS/flush/reopen, human click-to-receipt, CLI cold/warm request, MCP local stdio round trip, async queued/running/verify latency, request throughput, CPU p50/p95/p99, heap RSS, allocations, I/O bytes and payload size.
- **Durability:** source committed vs runtime published separate, journal readback/digest, idempotent retry, conflict rate, stale revision handling, cancellation cut point, committed/outbox recovery and data-loss incident count.
- **Security:** denied mutation changes zero source bytes/semantic state, no cross-project asset disclosure, no arbitrary shell/network/file access, safe log redaction and bounded parser/response memory.
- **Compatibility:** major/minor+unknown required field fallback, MCP stateless and handshake versions, OS/headless, empty GUI/GPU targets and declared owner unavailable states.
- **Instrumentation:** CORE-06 trace correlation and redaction; measurement overhead and sampling reported, no false zero for missing clock/hardware.

## 4. Failure injection and exact acceptance
During `stage->verify->intent->source commit->derived index->runtime publish`, inject SIGKILL/child restart, fsync failure, device loss, disk-full/read-only mount, permission revocation, timeout/cancel, torn cache/stale input, simultaneously conflicting edits, duplicate idempotency, serialization schema migration and malformed prefab. For build/export requests, inject missing toolchain, unsupported target, rights failure, cancel-after-submission and partial package write. Verify no unreviewed file/OS/network effects, retained prior-good source and owner recovery status. Unsafe script injection through names/JSON/CLI flags/MCP tool args must remain data.

### Metrics must not become invented targets
p50/p95/p99 threshold for decode, request, script validation, source CAS, UI-to-commit, CLI cold start, 10k/100k entity patch and job wait are all **TBD** until measured by declared OS/CPU/SSD tier and user-approved DoD. Stress at 100k is a comparative scenario, **not** a v1 capacity guarantee. No claim of exactly-once network delivery; define idempotent *effect* within journal/retention guarantees. Compare JCS/RFC8785 against DATA-04 semantic hashing only under declared algorithm/version.

## 5. Exit criteria and existing evidence
Before implementation approval: actual owner semantics WORLD-02/DATA-04/GAME-02, independent GUI/CLI routing, candidate CLI/parser dependency/license/SBOM, replay/undo proof, permission/consent, true Windows/Linux/macOS/Apple Silicon/headless and genuine MCP 2026/2025 peer conformance, 128 future tests run with real artefacts and signed audit. Documentation CI cannot substitute for source parity or platform performance.

Current: runtime builds 0, command kernel 0, GUI/CLI/MCP operational runs 0, source parity evidence 0, OS/browser tests 0, benchmarks 0; **128 A01 tests FUTURE/NOT EXECUTED**.

[API](../contracts/ai-01-command-kernel-api.md) · [Tests](../testing/ai-01-acceptance-matrix.md) · [Technology matrix](ai-01-command-technology-license-matrix.md).
