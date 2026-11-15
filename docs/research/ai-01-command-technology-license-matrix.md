# AI-01 — Command Kernel Technology, Protocol, Interop, License and Threat Matrix

**P00 research only | 2026-11-15 | [research #281](https://github.com/KayzenRoot/stormline/issues/281) | BASE `dd59a60d4280884dacbb2ec1834a4a5023d9b90c`.** No library, SDK, CLI, parser, interpreter, transport or subprocess installed; NLE-D009 engine source license remains OPEN. All tags/redistribution and transitive notices must be separately pinned/reverified before code activation.

## 1. Semantic schema, transport and CLI candidates
| Candidate and primary source | Role and verified characteristics | License/compatibility/gate |
|---|---|---|
| [JSON Schema Draft 2020-12](https://json-schema.org/draft/2020-12) | structural validation, $defs/$ref, vocabularies, unevaluatedProperties; `format` annotation vs assertion explicit | freely published spec, **not owner semantic validation**; entity references, CAS, rights and permission checked by owner |
| [RFC 8785 JCS](https://www.rfc-editor.org/rfc/rfc8785) | deterministic JSON canonicalization for digest/signature comparisons | I-JSON constraints: no duplicate keys, Unicode preservation, IEEE-754 representability; IDs/big ints encoded strings, **DATA-04 owns digest/version policy** |
| [JSON-RPC 2.0](https://www.jsonrpc.org/specification) | JSON request IDs/result/error model, batch and notification support | standard transport comparator; notification no acknowledgment and batch **not atomic**, unsuitable as implicit durable command transaction |
| [MCP 2026-07-28 official release](https://blog.modelcontextprotocol.io/posts/2026-07-28/) | stateless, self-describing per-request metadata, cacheable list and extensions incl Tasks; migration from 2025-era handshake | protocol adapter only, host support/version negotiation by test; no server/session assumption |
| [MCP TypeScript SDK v2 migration](https://ts.sdk.modelcontextprotocol.io/v2/migration/support-2026-07-28) | explicit opt-in for 2026-07-28; old handshake support differs | TS SDK ecosystem Apache-2.0 candidate, verify specific package/version/file licenses; no JS dependency in native kernel |
| [MCP JSON Schema/security](https://modelcontextprotocol.io/specification/2025-11-25) | older clients/tools/resource authorization/host consent baseline | spec/SDK integration only; no presumed universal 2026 host support |
| [CLI11](https://github.com/CLIUtils/CLI11) | strongly featured C++ subcommands/options/validators | BSD-3-Clause, candidate **CLI adapter only**, never semantic command authority |
| [nlohmann/json](https://github.com/nlohmann/json) | C++ JSON parsing/serialization baseline | MIT, API/alloc/perf/duplicate-key behavior must be validated against strict DATA-04 rules |
| [simdjson](https://github.com/simdjson/simdjson) | fast JSON parsing with CPU dispatch and ondemand support | dual Apache-2.0/MIT main code, transitive Dragonbox Boost/Apache LLVM exceptions and BSD code; speed/strict security comparisons needed |
| [Protocol Buffers](https://protobuf.dev/programming-guides/proto3/) | typed efficient internal transport/cross-language SDK candidate | BSD-3-Clause project + vendored per-file review; *not canonical scene source*, unknown-field/JSON mapping/version semantics to test |
| [FlatBuffers](https://flatbuffers.dev/) | zero-copy-oriented binary layout/cross-language tooling | Apache-2.0 upstream; potentially useful DATA-05/runtime IPC, not replacement for DATA-04 authored source |
| owned C++20 structs + stdlib CLI/parser reference | minimizes third-party APIs and compiler requirements | no extra license dependency; parser, docs and JSON validation must still be safe/tested |

**Technology selection is PROPOSED ONLY.** JSON Schema does not grant capability or guarantee semantic consistency; no third-party SDK types enter public Stormline authoring ABI.

## 2. Official MCP and interoperability status
The **2026-07-28** MCP update introduced a stateless per-request core, optional discovery, header-based routing and MRTR/extension behavior; official Tier 1 TS/Python/Go/C# SDKs were updated. The 2025-11-25 era used initialize/handshake. Both eras require **explicit peer capability negotiation**. The [TS v2 migration guide](https://ts.sdk.modelcontextprotocol.io/v2/migration/support-2026-07-28) notes a manually constructed SDK client does **not** automatically speak 2026 without opting in. No assumption that all host brands or tools support every revision/Tasks, and no MCP subscription, network service or provider-specific API is required to call AI-01.

MCP *tools* are external request wrappers, *resources* are bounded read-only views, *prompts* are optional scaffolds. This layer must never become a new source of truth or bypass owner capability. For long-running jobs, use Stormline-owned JobHandle/status/poll/cancel; map to MCP Tasks only if negotiated. The network/stdio transport and OAuth/token management are separate AI-04/AI-06 future integration, **not** new AI-01 formal dependencies.

## 3. Rights, security and availability matrix
| Threat | Failure | Proposed control |
|---|---|---|
| GUI/CLI/MCP origin spoof | AI/CLI gains privileged editor context | authenticated principal + source-independent owner-side capability, grant/expiry/scope |
| LLM/prompt injection | user-controlled names/comments become instructions | parse as untrusted data, no shell/eval, escape log/UI/CLI/MCP output |
| JSON request DoS | deeply nested input, giant numbers, invalid Unicode, duplicate keys, schema confusion | bounded parser, strict UTF-8, no duplicate keys, finite numbers, integer-as-string for > IEEE-754 safe range, known required versions |
| Arbitrary path/process | `../../` traversal, symlink, command injection, OS shell | DATA-01 scoped VFS grants; no arbitrary file URI, subprocess or raw paths |
| Replay/timeout | duplicate create/delete/import, stale CAS, late cancel | scoped idempotency key/payload digest/revision, DATA-04 journal/readback and RECOVERY_REQUIRED |
| Concurrency | scene/prefab overrides lost; last writer silently wins | WORLD-02 3-way conflict and expected revisions, DATA-04 typed semantic diff/CAS |
| Source/runtime gap | source committed but runtime not published | distinct owner receipts/source+runtime epochs, no cross-service ACID claim |
| MCP/batch fanout | unbounded LLM/agent edits or hidden network | bounded rate/cost/fanout, confirmation/approval for destructive actions, local stdio default |
| Build/export abuse | arbitrary compiler/signer/shell or external deployment | PLAT/DATA-05 owner allowlisted targets and job plans; no ambient executable path |
| Data/provenance leak | project secrets, absolute paths, private assets in CLI stdout or model context | CORE-06 redaction, scope-limited paginated outputs and explicit bundle consent |
| Supply chain | dependencies/license drift/known CVEs | pin exact tags, SPDX/SBOM/NOTICE, source provenance and vulns review |
| AI-03/06 circular deps | kernel can't boot or bypasses auth | minimal bootstrap descriptor, mandatory owner-side fail-closed checks; enhanced AI-03/06 later |

## 4. Deliberate no-selection and comparative scoring
Future score weights (TBD owner): correctness/parity 30%, security 25%, portable maintenance 15%, latency/alloc/cost 10%, license/SBOM 10%, host compatibility 10%. **No scores/results have been measured**; decide parser/CLI stack based on actual strictness/performance, not popularity. Evaluate stdlib-only parser stub vs nlohmann/json vs simdjson for strict object duplicate keys, speed, CPU tiers and memory; CLI11 vs minimal parser for help/completions; JSON-RPC vs owned envelope for transport; MCP SDK adapter versions per actual peer.

Primary sources: [JSON Schema](https://json-schema.org/draft/2020-12), [RFC 8785](https://www.rfc-editor.org/rfc/rfc8785), [JSON-RPC 2.0](https://www.jsonrpc.org/specification), [MCP 2026-07-28](https://blog.modelcontextprotocol.io/posts/2026-07-28/), [CLI11 license](https://github.com/CLIUtils/CLI11/blob/main/LICENSE), [simdjson license](https://github.com/simdjson/simdjson/blob/master/LICENSE), [nlohmann-json license](https://github.com/nlohmann/json/blob/develop/LICENSE.MIT), [FlatBuffers](https://github.com/google/flatbuffers), [Protobuf](https://github.com/protocolbuffers/protobuf). All remain candidates only.
