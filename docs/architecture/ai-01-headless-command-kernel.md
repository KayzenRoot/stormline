# AI-01 — Headless Semantic Command Kernel Architecture v0.1

**2026-11-15 | P00 RESEARCH ONLY, NOT IMPLEMENTED | [research #281](https://github.com/KayzenRoot/stormline/issues/281) | WO NLE-P00-WO-002-AI-01 | [future code #75](https://github.com/KayzenRoot/stormline/issues/75) OPEN/BLOCKED | BASE `dd59a60d4280884dacbb2ec1834a4a5023d9b90c`.** Catalog order 57/80; 56 modules researched at baseline, 24 pending, all 80 implementation WOs BLOCKED.

## 1. Product goal and acceptance oracle
**Catalog acceptance: "Mesma operação manual/CLI produz estado semanticamente igual."** Human UI buttons, direct headless CLI calls, MCP/AI tools and test harnesses must invoke one **Stormline-owned typed semantic command** and its owner validation/transaction path. The target of parity is the **authoritative authored state and observable owner receipts**, not byte equality of UI layout, transport envelopes, generated timestamps or backend instrumentation.

Future acceptance fixture: take two fresh project clones with identical DATA-04 semantic source digest/revisions, pin command version, capabilities/actor, typed arguments, target owner schema and deterministic seed/ID allocation where defined; submit the *same logical authoring operation* through Editor and CLI, then validate/read back each independently via DATA-04/WORLD-02/owner. Compare normalized typed scene/prefab/source state, sorted stable references and ordering where semantic, owner transaction outcomes and security denials; exclude explicitly tagged volatile log/trace/timing/job IDs. If new IDs are allocated nondeterministically, compare **declared ID remapping plus graph/reference isomorphism**, not silently ignore broken references. A matching exit code or raw JSON text is insufficient. MCP parity is an additional conformance target, not a parallel execution engine.

**Core architectural thesis (PROPOSED):** thin Editor/CLI/MCP transport adapters -> Stormline-owned versioned command envelope + descriptor lookup -> schema & capability gate -> owner-approved preview/stage/validate/CAS/journal -> owner receipts/readback -> adapter-specific structured output. AI-01 **does not** store canonical scenes, own ECS, become a script VM, create a privileged global superuser or implement a second mutation pipeline.

## 2. Formal dependencies: exactly three
| Formal prerequisite | Owner contract / guaranteed boundary of AI-01 |
|---|---|
| **WORLD-02** | Owns SceneAssetV1, PrefabAssetV1, stable SceneNode/Instance IDs, typed 3-way override rebase and SceneEditTransaction/SceneCommitReceipt; source commit and WORLD-01 runtime publication are **distinct receipts**. AI-01 delegates scene/prefab CRUD/inspect/preview to WORLD-02, not JSON array edits or direct ECS handles |
| **DATA-04** | Owns versioned strict semantic source, ScenePatch/SceneDiff, source revision and CAS, journal/undo/recovery/migrations, canonicalization and digest policy. AI-01 never uses unchecked raw host file overwrite; separate source vs derived-index vs runtime outcomes |
| **GAME-02** | Owns ScriptApiSchemaV1, ScriptCapabilityGrantV1, typed script module/graph/program host calls, sandbox and compile/hot-reload/fault receipts; AI-01 forwards script author/validate requests and never exposes eval, arbitrary shell, VM pointers or gameplay authority |

**All three predecessors are documentary/ADRs PROPOSED only**; future coding issues WORLD-02 #42, DATA-04 #27, GAME-02 #58 OPEN/BLOCKED. No current runnable command bus or dependency code is present. Formal DAG must remain exactly WORLD-02 + DATA-04 + GAME-02.

## 3. Integration owners, NOT extra formal DAG edges
| Integration boundary | Responsibility |
|---|---|
| EDIT-01 | Shared EditorCommandIdV1, buttons, focus/IME/accessibility, localized labels/tooltips/disabled reasons, origin MENU/SHORTCUT/PALETTE; **same semantic kernel command ID mapping** |
| EDIT-02/03/04/05/06/07 | project/create/open authority, scene/2D/shader/VFX/audio/animation/debug authoring intent; each owns domain UI not a direct file/engine mutation shortcut |
| DATA-01/02/03/05 | scoped VFS paths/grants, AssetId registry/provenance, secure import, cooked/export artifact manifests; build/export delegates to owning platform/export backend, not AI-01 |
| WORLD-01/CORE-01/03/04/05/06 | entity lifecycle & barrier, OS/headless process, job scheduling/cancel, TickId, math, diagnostic trace/metrics |
| PLAT-01..06 / QA-01..05 | build target selection, package/export/deployment receipt, test/benchmark authority; AI-01 exposes capability-gated job orchestration **only after those owner APIs exist** |
| AI-02 / AI-03 / AI-04 / AI-05 / AI-06 / AI-07 / AI-08 / AI-09 | future semantic index, capability registry, MCP adapters/resources, dedicated auth policy, planning/undo, agent automation/audit. They depend on AI-01 or other modules; **do not impose retroactive circular direct dependencies** |
| Product AI/MCP contract | requires identical approved public authoring capability across Editor, CLI and MCP with project-scoped permissions and version negotiation; MCP is an adapter, not internal source authority |

The command kernel performs *routing, precondition validation, authorization enforcement according to owner-approved capability policy and audit correlation*. AI-06 may later author the authorization policy engine; **AI-01 cannot defer all checks until AI-06 exists**. A minimal fail-closed owner-checked grant interface is necessary before any mutation is implemented; no blanket "trusted editor" or local-CLI exemption.

## 4. Descriptor registry, no circular AI-03 dependency
Future `CommandDescriptorV1`: stable namespaced CommandId, major/minor API version and schema hash, input/result schema refs, owning module and handler, read/write/irreversible side-effect classification, required capability/role/project grant, target API and release class, idempotency policy, undo/rollback semantics, required source revision, estimate/cost/budget, async/cancel/progress policy, deprecation and permission/availability status.

AI-01 requires a **small bootstrap registry** to route only operations whose owner contracts exist. AI-03 is the **future reflective/introspection registry and schema tooling** depending on AI-01, not a prerequisite and not a second authoritative command table. Later AI-03 must derive from exactly the same owner descriptors, prove coverage and drift detection. Unknown commands/versions fail typed `UNSUPPORTED_COMMAND` / `SCHEMA_VERSION_UNSUPPORTED`; no hidden fallback to a different operation or transport-specific privilege.

A future representative family may include `project.inspect`, `scene.inspect`, `scene.patch.preview`, `scene.patch.commit`, `prefab.rebase.preview`, `script.validate`, `build.request`, `export.request`. **Examples only.** BUILD/EXPORT are advertised only when the owning platform/packaging APIs exist and report availability/capability. AI-01 cannot imply an engine build/export implementation or launch of shell tools.

## 5. Command pipeline and transaction semantics
1. **Decode** bounded adapter input (UTF-8, reject duplicate keys/NaN/Inf, size/nesting/UTF-8 overlong, no implicit type coercion); build typed envelope with protocol and command versions.
2. **Lookup** descriptor and negotiate compatible major/minor/features. No public command bypass by alternate origin; disabled/unknown operations return stable reason.
3. **Authenticate/authorize** principal, ProjectId/workspace and AssetId/SceneId scope, grants, command capability, actor, expected source/owner revision, target platform and quota. UI enabled state is advisory; owner revalidates.
4. **Resolve** owner stable logical IDs; reject host filesystem paths, raw runtime EntityHandle, VM pointer and untrusted script data as command identity.
5. **Preview/plan** typed owner validation, semantic diff, affected counts/rights and risk flags, no side effects; apply to an immutable snapshot. For mutation, explicit plan digest ties confirmation to exact revision/arguments/actor.
6. **Stage/validate** via DATA-04/WORLD-02/GAME-02 owner contracts with idempotency key, expected revision and durable journal; no cross-module "ACID" claim.
7. **Intent-record/commit/readback** at owner-defined durable boundary. `ACCEPTED` (request received) != `STAGED` != `COMMITTED_SOURCE` != `PUBLISHED_RUNTIME` != `EXPORTED_ARTIFACT`. Explicit `RECOVERY_REQUIRED` if a crash happens after durable intent but before all reconciliation.
8. **Receipt** includes operation ID, owner, source before/after revision, semantic digest algorithm + canonicalization version, affected IDs/ref remaps, conflicts, evidence, warnings, undo token if owner, time/correlation status and retryability; adapt to GUI/CLI/MCP without changing semantic result.

**Idempotency:** key scoped to principal+ProjectId+CommandId/major schema+operation/args digest and expected revision, not user-chosen global string. On same key+same intent, return prior committed or recovery receipt; same key+different payload => `IDEMPOTENCY_CONFLICT`. Keys expire only after explicit owner retention/idempotency policy and durable replay window. No double-delete, duplicate prefab instance or double charge.

**Cancellation:** before intent aborts/stages cleanup; after durable intent returns status/operation handle and recovery, **never** claims rollback of already committed side effects. Deadline expiry doesn't imply cancellation succeeded. Owner watchdog/leases and bounded job status replace blocking UI/CLI/MCP calls.

## 6. Manual buttons and headless interface equivalence
EDIT-01 toolbar buttons (Save, Create, Open, Apply, Undo/Redo, Validate, Build, Export) map to shared semantic `CommandId` and owner handler. Button metadata: localized accessible name, tooltip, disabled reason, shortcut, busy/progress/cancel, confirmation, focus/IME and actor scope. The CLI parses subcommands and structured JSON from stdin/file grant, not OS shell interpolation; machine output is bounded **JSON event/receipt** on stdout, diagnostics to stderr, exit codes mapped from typed status, no secrets. GUI success toast only on owner-verified commit/readback, not on click.

MCP 2026-07-28 uses a **stateless protocol core** (official 2026-07-28 revision) with per-request self-describing capability/version and extensions; older 2025-era hosts initialize/handshake. The MCP adapter must negotiate by peer, not assume a session or universal SDK. CLI and Editor do not depend on MCP or an LLM. Local stdio transport default with scoped project grants; remote HTTP/listener requires separate authorization/security approval. MCP Tasks support long-running jobs only if negotiated; internal durable job polling is provider-independent. **No arbitrary command eval, shell, OS path, remote upload, unsigned plugin loader or secret-bearing trace in tool outputs.**

## 7. Equality, determinism and reliability
- The parity oracle is `SemanticStateFingerprintV1` **derived by DATA-04** from owner-validated scene/source graph with algorithm/version, stable IDs, component fields, explicit authored order, required feature sets, asset/prefab references and provenance. If IDs differ by legitimate allocator strategy, emit ID-remap receipt and check graph isomorphism/reference integrity. Compare conflict states/rights and same initial revision; do not ignore structural differences or asset loss.
- Source canonicalization is distinct from byte equality and from gameplay determinism; JSON text pretty printer vs RFC 8785 JCS are separate candidates. Semantic hashes must not include volatile timestamps, UI dock state, process PID, MCP transport ID, trace/span event IDs or wall-clock jitter.
- Platform adapter conformance: native Windows/Linux/macOS Apple Silicon + headless, later Web sandbox. CPU-only scene validates without display/GPU/audio. Build/export target differences are declared capabilities, never claimed identical cross-target binaries.
- Validation/dry-run output is versioned/deterministic for same owner state where contract promises; source commit and runtime publication are different barriers. Exit code 0 without readback receipt is **not** passing parity.

## 8. Threats, licensing, accessibility, scope
Threats: prompt injection in project names/scripts/logs, command spoofing, confused-deputy authorization, path traversal/symlink, schema coercion, integer overflows, duplicate keys, idempotency replay, race/cancel-after-intent, migration loss, workspace crossing, unbounded fanout/cost, JSON deserialization DoS, shell escape through CLI, plugin VM escape, remote MCP listeners, leaked secrets/asset rights, false same-state digest. Gates: deny-by-default owner capabilities, typed IDs, bounded validation, DATA-04 transactional/journal, exact-readback, auditing, redaction, local-first and separate approval for dangerous writes/exports.

- **NECESSARY:** shared command routing, typed schema/envelope/receipts, GUI/CLI parity, grants, owner delegation, preview/CAS/idempotency, reliable cancellation/async job model, deterministic semantic equality, license/security, 128 tests and benchmarks.
- **IMPORTANT:** dry-run cost estimator, offline batch planner with per-op receipts (not implicit atomic batch), tool documentation auto-generation, structured trace comparison, staging/retry fairness. Require evidence before 1.0.
- **FUTURE:** AI-03 reflection, AI-04 MCP server, AI-06 advanced auth, AI-07 multi-object planning, remote build farm, collaborative CRDT authoring, paid/cloud connectors, autonomous uploads.
- **OUT OF SCOPE:** any code/SDK installation, new scene serializer/prefab engine/script VM, unreviewed remote service, live cloud LLM, shell evaluation, engine build/export implementation, license approval, 1.0 release classification, performance claims and code WO unblocking.

[ADR-0060](../adr/0060-ai-01-shared-semantic-command-kernel.md) · [Technology/license matrix](../research/ai-01-command-technology-license-matrix.md) · [API](../contracts/ai-01-command-kernel-api.md) · [128 future tests](../testing/ai-01-acceptance-matrix.md) · [Benchmark](../research/ai-01-command-benchmark-protocol.md).
