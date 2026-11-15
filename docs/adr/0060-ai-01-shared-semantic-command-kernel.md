# ADR-0060 — Stormline-Owned Shared Semantic Command Kernel with Owner-Checked Transactions

**STATUS: PROPOSED / NOT ADOPTED / NOT OWNER-APPROVED / NO CODE AUTHORIZATION | 2026-11-15 | [research #281](https://github.com/KayzenRoot/stormline/issues/281) | WO NLE-P00-WO-002-AI-01 | code #75 OPEN/BLOCKED | BASE `dd59a60d4280884dacbb2ec1834a4a5023d9b90c` | NLE-D009 engine license OPEN.**

## Context
The candidate AI-01 Headless Command Kernel must guarantee **"Mesma operação manual/CLI produz estado semanticamente igual."** WORLD-02 owns scene/prefab semantics and three-way override conflicts; DATA-04 owns canonical source, revision, semantic delta/CAS/journal/migration; GAME-02 owns ScriptApiSchema, sandbox and capability-checked host calls. EDIT-01 already proposes shared button CommandIds, while AI-03/04/06/07 are later modules relying on AI-01; making them mandatory first would create circular dependencies. Product AI/MCP contract mandates one shared authority, not an AI-only source writer. **None of these contracts are compiled or owner-approved.**

## Proposed decision, NOT approved
1. **AI-01 owns a minimal typed command router**, descriptor/handler binding, uniform validation/receipt/async operation handle and transport-neutral invocation. It does not own project source, ECS state, script VM, platform build/export, MCP server or independent security root.
2. **Formal dependencies remain exactly WORLD-02 + DATA-04 + GAME-02.** Other EDIT/DATA/CORE/PLAT/AI/MCP systems are integration owners only and do not enlarge the DAG.
3. Descriptor contains stable CommandId + schema/major/minor versions, input/result shapes, owner, required capability, side-effect/risk tier, scope, available target, undo policy, idempotency/retry semantics, cancellation and error model. AI-03 future reflection must **derive** schema from bootstrap descriptor, no second authoritative registry.
4. EditorCommandIdV1, headless CLI and future MCP tool adapter normalize to the **same InvocationV1** and call the **same owning module validator/commit entry**; adapters never perform direct VFS/ECS/VM writes or privileged shell.
5. Every mutating command is project-/actor-/role-/capability-scoped with expected revision/typed IDs, authenticated principal and owner-side fail-closed authorization. AI-06's later richer policy cannot be used as excuse for allowing mutations without enforcement.
6. Use **DATA-04-owned** semantic digest/canonicalization and CAS/journal for source. WORLD-02 handles prefab instance/variant/rebase and runtime publish receipts separately. GAME-02 handles script modules/host calls and does not grant raw VM eval. Preview/dry-run bound to exact revision/plan digest, stage/validate/intend/commit/readback with explicit conflict/recovery.
7. Idempotency key scoped to owner/principal+project+command version+payload digest+revision; duplicate request resumes/returns prior receipt, incompatible same key fails. Cancellation before intent can abort; after durable intent returns recoverable status, not fictitious rollback.
8. GUI/CLI semantic equivalence means same validated authored graph/refs/rights/order (or explicit stable-ID remap proof), not identical JSON bytes, timestamps, logs, OS exit code, runtime publication, or GPU/audio output.
9. Long-running build/export is a **future authorized owner job** with accepted/running/validated/published/failed/recovery receipts. AI-01 does not compile/package scenes itself or invoke arbitrary subprocess/host executable. CLI structured events are bounded, stable and scrubbed.
10. MCP compatibility: canonical kernel is transport-independent. MCP **2026-07-28 stateless core** and 2025 handshake-era compatibility are *adapter* negotiations. No hidden HTTP listener, automated sampling, task extension assumption or LLM-specific authority.
11. Unknown major versions, required features, owner unavailable, schema coercion and unapproved target fail closed with typed errors; optional unknown source fields preserved by DATA-04 rules, never silently dropped.
12. All 128 parity/security/transactional tests, latency/throughput/cold-start benchmarks, license/SBOM, exact file ABI, owner-approved ADR and release class are pending; no code unlocked.

## Alternatives/trade-offs
| Option | Benefit | Rejected as unconditional default |
|---|---|---|
| Direct UI callbacks and separate CLI commands | fast first prototype | divergent validation/transactions, fails parity |
| MCP-first internal kernel | leverages LLM tools | makes editor depend on rapidly evolving external protocol and AI authority |
| JSON-RPC 2.0 as internal engine ABI | familiar messages | protocol transport/batch semantics do not prove scene transactions or idempotency; notifications lack receipt |
| Protobuf/FlatBuffers for user-authored source | fast binary | contradicts proposed DATA-04 human-reviewable strict JSON; may remain optimized transport candidate |
| Raw JSON Patch and filesystem writer | flexible | array indices, idempotency, prefab override and CAS are unsafe vs typed owner changes |
| Global singleton superuser kernel | little auth plumbing | confused-deputy, cross-project privilege escalation |
| Best-effort async fire-and-forget writes | low latency | cannot verify readback or undo/recovery, contradicts DoD |
| AI-03/AI-06 prerequisite of AI-01 | full registry/security first | circular catalog dependencies; bootstrap must fail closed, later systems enhance |
| Naive byte-hash equality for GUI/CLI | simple oracle | UI/transport and generated IDs differ while semantic graph can be equal, and vice versa |
| Distributed multi-owner ACID guarantee | convenient user story | unsupported by DATA-01/04/WORLD publication; separate receipts and recovery instead |

## Proof obligations and unresolved choices
Owner-approved bootstrap descriptor schema, command IDs/freeze/semver, exact policy/grant interface, DATA-04 semantic digest canonicalization and ID remapping, WORLD-02 source vs runtime receipt, GAME-02 public scripting subset, source/asset rights, GUI click to semantic command mapping, CLI parser and stdio policy, MCP 2026/legacy host tests, cancellation/idempotency durable store and retention, crash replay, multiple projects and agents, per-platform headless/Web capability, no hidden network/shell, SBOM/per-file license, 128 unit/integration/e2e future tests and measured p50/p95/p99. Any irreversible/export action requires explicit owner scope and confirmation. Release class UNDECIDED, NLE-D009 OPEN, all coding packets BLOCKED.

**ADR-0060 remains PROPOSED. No routing backend, serializer, CLI, transport, build/export implementation, library or license is approved or implemented.**
