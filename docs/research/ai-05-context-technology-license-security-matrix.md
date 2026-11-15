# AI-05 — Context Resources, Templates, Security and License Research Matrix

**2026-11-15 | RESEARCH-ONLY | [#297](https://github.com/KayzenRoot/stormline/issues/297) | NLE-P00-WO-002-AI-05 | future code #79 OPEN/BLOCKED | BASE `ec1a8efc89de6e90d53f7b56fd31bc874335a2ff`.** AI-02 + AI-04 formal predecessors; ADR-0061/0063 PROPOSED; ADR-0064 PROPOSED; NLE-D009 license OPEN. No implementation or benchmark.

## 1. Primary specification, scope and evidence
| Subject | Authoritative evidence | Design implication |
|---|---|---|
| MCP dated current spec | [MCP 2026-07-28 specification](https://modelcontextprotocol.io/specification/2026-07-28) | modern stateless protocol metadata; AI-04 handles wire |
| MCP resources | [Resources spec](https://modelcontextprotocol.io/specification/2026-07-28/server/resources) | resources/list/read, resources/templates/list, URI identity, pagination, capabilities and client app selection |
| MCP prompt control | [Server overview](https://modelcontextprotocol.io/specification/2026-07-28/server) and [Prompts](https://modelcontextprotocol.io/specification/2026-07-28/server/prompts) | prompts user-controlled; must not be treated as tools or grants |
| Prompt argument format | [Python SDK prompts](https://py.sdk.modelcontextprotocol.io/servers/prompts/) / [TypeScript prompts](https://ts.sdk.modelcontextprotocol.io/v2/servers/prompts) | MCP prompts list flat named-string arguments, rich internal typed recipe schema separate |
| Resource templates | [Resources spec](https://modelcontextprotocol.io/specification/2026-07-28/server/resources) | use RFC6570 URI templates; do not expose arbitrary host path |
| URI templates | [RFC 6570](https://www.rfc-editor.org/rfc/rfc6570) | strict validated template subset; reserved expansion can carry unsafe URI separators |
| Completion | [completion/complete](https://modelcontextprotocol.io/specification/2026-07-28/server/utilities/completion) | prompt/resource arguments only; max 100 values; permission-safe suggestions |
| Caching | [2026 release notes](https://blog.modelcontextprotocol.io/posts/2026-07-28/) / [SDK cache hints](https://py.sdk.modelcontextprotocol.io/client/caching/) | modern eligible lists/reads require ttlMs/cacheScope; default private/0 |
| Subscriptions | [2026 resource spec](https://modelcontextprotocol.io/specification/2026-07-28/server/resources) | AI-04 serves opted-in subscriptions/listen; notifications are non-authoritative hints |
| Security | [MCP authorization security considerations](https://github.com/modelcontextprotocol/modelcontextprotocol/blob/main/docs/specification/2026-07-28/basic/authorization/security-considerations.mdx) | token audience/resource validation, consent and least privilege |
| Index ownership | [AI-02 architecture](../architecture/ai-02-project-semantic-index.md) / [AI-02 API](../contracts/ai-02-semantic-index-api.md) | source generation, owner citations, ACL, context pack and ranked search are AI-02-owned |
| Protocol ownership | [AI-04 architecture](../architecture/ai-04-mcp-server-protocol-adapter.md) / [AI-04 API](../contracts/ai-04-mcp-server-contracts.md) | JSON-RPC and modern/legacy era handling owned by AI-04 |

## 2. Technology candidates (none adopted)
| Option | Known rights / license caveats | Uses | Trade-offs / gate |
|---|---|---|---|
| Owner-defined typed C++20 structs plus stdlib UTF-8 serializer | engine code license NLE-D009 OPEN; stdlib distribution/license depends toolchain | deterministic context envelope/URI ID formatter | minimize dependencies; validate JSON correctness, Unicode, MIME, output escaping |
| AI-04 selected MCP SDK (TypeScript v2 or Python v2 candidate) | exact SDK tag, transitive SBOM/SPDX/NOTICE/license must be reviewed; AI-04 not approved yet | wire resources/templates/prompts/completion | AI-05 must not pick or vendor second SDK; expose provider port |
| Reuse AI-02 structured/FTS index projection | AI-02's candidates SQLite FTS5/public domain core and optional parsers not adopted; owner DATA-02 data rights independent | source retrieval and compact citations | no AI-05-owned SQLite DB or vector store; verify source revision/ACL |
| [uriparser](https://github.com/uriparser/uriparser) | runtime BSD-3-Clause; its test suite LGPL-2.1-or-later; fuzz code Apache-2.0 | RFC3986 URI parsing candidate | not necessarily RFC6570 expander; exact package/file-level licensing, CVE, cross-OS review |
| RFC6570 limited author-owned expander | no external dependency but test/maintenance burden | small allowlisted typed URI template subset | safer subset than full arbitrary reserved expansion; RFC6570 suite/negative fuzz needed |
| URI Template third-party library | license/version not selected | full RFC6570 expansion | only if proven necessary and secure; exact tag/license audit; may widen URI injection surface |
| Mustache-style logicless templates | Mustache spec separate from implementation and each renderer's license | curated text recipe formatting | variable escaping, partials, lambda/extension support and signed manifests must be reviewed; never execute code |
| Static declarative recipe manifests | engine/project rights and publisher/source license separate | default recipes and locales | no arbitrary script/eval, semantic version, safe placeholders, user selection |
| Markdown/commonmark renderer/parser | implementation license/version/HTML/URL handling varies | optional readable excerpts | prefer plain text structured output; no unsafe HTML or external image auto-fetch |
| ICU Unicode normalization/segmentation | ICU uses ICU License (per exact release); data/OS packaging large | mixed-script/case/UTF-8 handling | pin Unicode version; compare stdlib and existing project Unicode owner policies; no new vendor by default |
| Hosted vector/embedding/LLM provider | unknown third-party data/model terms, privacy/cost | fuzzy discovery/summaries | excluded as default; separately approved future prove-or-drop |
| RE2 for regex | BSD-3-Clause implementation plus transitive dependency review | optional bounded search | AI-05 does not accept arbitrary regex; AI-02 retains query grammar; no regex library selected |

**Do not infer the license of all SDK or test files from a repository root license.** For example, uriparser separates runtime, test and fuzz licenses. All exact releases, dependencies, notices and patent obligations are unresolved until implementation gate. No licensing decision for Stormline engine is implied.

## 3. Alternative packaging approaches
| Approach | Discovery cost | Correctness/security | Conclusion |
|---|---|---|---|
| Progressive resource inventory + typed templates + targeted read | small catalog and bounded exact excerpts | owner-proven source IDs/ACL/revisions; pageable and cacheable | **PROPOSED** baseline |
| Unlimited single-resource repository dump | huge payload, no progressive selection | leak secrets/rights; impossible to bound context | rejected |
| Precomputed per-project context blob | fast but can go stale | stale owner/ACL, untraceable content freshness | rejected as authority |
| Automatic AI summaries | potentially compact | hallucinated facts/source provenance and model network cost | future optional, never source authority |
| AI-05 local FTS index | duplicates AI-02 | index generation drift, rights inconsistencies | rejected |
| Global multi-tenant context cache | high hit rate | cross-project/principal cache poisoning and access leaks | rejected |
| Static curated examples/recipes only | simple offline | does not discover actual project source | complement, not complete AI-05 acceptance |

## 4. Identity and citation policy
- ProjectId, AssetId, SourceRevision, ScriptModule and schema digests must come from canonical owners via AI-02; a display path, filename, integer runtime handle or title is never durable identity.
- AI-05 citations reference exact owner source and revision and optionally bounded range/field. Required rights/ACL prove read availability, not redistribution rights; license/provenance enforcement is separate. If no owner-signed source locator or legal grant, do not emit excerpt.
- Context Capsule renderers preserve section order and typed metadata. Incomplete index gives typed PARTIAL/UNSUPPORTED and missing coverage; do not claim 100% query recall.
- Excerpts and snippets are bytes bounded and escaped as data, not model/system directives; if rendered to Markdown, neutralize control characters and unsafe embedded HTML/links.

## 5. Caching, revocation and subscriptions
Default for project-sensitive lists, templates, resources and prompts in MCP 2026: `ttlMs=0`, `cacheScope=private`. Positive TTL requires immutable owner revision, valid rights and explicit risk assessment; a host may have copied previous content and cannot be forced to delete it. Revoke stops future reads and invalidates server-side cursors/cache/subscriptions; this does not retroactively erase client memory. `public` cache only for demonstrably identical, no-personal/project-specific content. List-changed notification is a hint requiring full auth/owner re-read, not guaranteed replay.

MCP 2025-11-25 responses use older result shape without modern required caching fields; AI-04 adapts by negotiated version. AI-05 emits only logical data/hints; it must not forge a wire-era response.

## 6. Threat-driven security research
| Attack | Prevention and future test |
|---|---|
| Cross-project enumeration through resource count, error, cursor or completion | before-candidate authorization; safe generic denial and no hidden count |
| Prompt injection in source/docs | label as untrusted, no tool dispatch, no system-role interpolation |
| URI template SSRF/path traversal/double decoding | strict scheme, allowed named scalar IDs, canonical percent encoding, owner resolution |
| Hidden secrets in source/schema/paths | field-level redaction and rights allowlist before compose and cache |
| Unicode normalization/bidi confusables | stable typed IDs; safe display escaping; reject ambiguous URI forms |
| Unbounded resource/prompt expansion | max result bytes/rows/depth/pages, deadline, recursion/cycle limits |
| Stale index projection of revoked/deleted asset | reauthorize owner source before hydration; revision/ACL epoch binding |
| Cursor replay and stale ACL | non-forgeable principal/project/generation/policy/query/expiry binding |
| Unsafe remote images/icons | no auto-fetch/remote credentials; allowlisted immutable local icon assets only if approved |
| Hidden prompt/tool capability via recipe | safe user selection; typed owner tools separately authorized |
| Third-party copyright/PII export | rights classification, redaction, only approved excerpts, audit minimal metadata |
| Faked citations by LLM | citations from owner locators/digests; never free-form model evidence |

## 7. Future benchmark and licensing gates
Record host/version/protocol, exact owner/source fixtures, scenario ground truth, project size, rights grant, index generation and source revisions. Compare resource-read workflow against authorized full-project baseline. Measure bytes, estimated tokens (provider-neutral estimate is not exact), recall@k/MRR, p50/p95/p99, freshness, CPU/RSS, security negative cases and on-disk cache storage. No numerical winner/target claimed until real measurements. All 128 tests remain FUTURE/NOT EXECUTED. For each adopted dependency require exact tag/lockfile, SBOM/SPDX, NOTICE/license/CVE/patent review and Windows/Linux/macOS packaging evidence.

[ADR-0064](../adr/0064-ai-05-authorized-context-projections.md) · [Contracts](../contracts/ai-05-context-resource-api.md) · [Benchmark](ai-05-context-benchmark-protocol.md).
