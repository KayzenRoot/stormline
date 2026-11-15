# AI-04 — Exactly 128 FUTURE MCP Acceptance Tests (A04-T001..A04-T128)

**2026-11-15 | P00 RESEARCH ONLY / NOT IMPLEMENTED | research #293 | NLE-P00-WO-002-AI-04 | code #78 OPEN/BLOCKED | BASE 0cdcef6ae19ba1105667404ed5749ad5155fef0f.** 59/80 researches documented, 21 pending, zero engine, all 80 implementation packets BLOCKED. Formal dependency AI-03 ONLY; ADR-0062 PROPOSED; NLE-D009 OPEN; NLE-D015 OWNER-DIRECTED.

**Exactly 128 unique FUTURE / NOT EXECUTED scenarios. 0 executed, 0 passed, 0 failed.** Eight groups of sixteen. These are obligations, not executable test code or protocol evidence.

## Evaluation rules
1. Test 2026-07-28 modern stateless and 2025-11-25 legacy separately; never combine results.
2. Test stdio and Streamable HTTP independently. No 2024-11-05 HTTP+SSE claim without separate decision/suite.
3. Protected requests use verified synthetic principal/project/grant/policy epoch. Cross-project and revoked cases are mandatory negatives.
4. Tool tests require AI-03 descriptor and AI-01 owner receipt; schema pass alone is not authorization pass.
5. Tasks tests are conditional on durable JobHandle and extension negotiation. If unsupported, server must not advertise or emit a task.
6. Host compatibility requires exact host release and negotiated protocol version. Generic MCP client does not certify Codex or Claude.
7. Security tests assert zero unintended owner dispatch and zero data leakage, not merely HTTP error codes.

## Test groups
| Group | IDs | Count | Coverage |
|---|---|---:|---|
| DISCOVERY-VERSION | A04-T001..016 | 16 | discovery, metadata, legacy fallback, downgrade |
| STDIO-PROCESS | A04-T017..032 | 16 | process lifecycle, framing, stdout, OS isolation |
| HTTP-STATELESS-LEGACY | A04-T033..048 | 16 | POST, headers, statelessness, legacy isolation |
| AUTH-ORIGIN-OAUTH | A04-T049..064 | 16 | Origin, OAuth, audience, scopes, tenant boundaries |
| TOOLS-OWNER-BRIDGE | A04-T065..080 | 16 | AI-03 projection, AI-01 dispatch, schemas/errors |
| RESOURCES-PROMPTS-CACHE | A04-T081..096 | 16 | provider ports, opaque URIs, cache, prompts |
| MRTR-SUBSCRIPTIONS-TASKS | A04-T097..112 | 16 | input rounds, subscriptions, optional tasks |
| CONFORMANCE-OBSERVABILITY-PLATFORM | A04-T113..128 | 16 | conformance, hosts, tracing, limits, OS |

## Complete future matrix
| Test ID | Group | Scenario / assertion | Evidence required | Status |
|---|---|---|---|---|
| A04-T001 | DISCOVERY-VERSION | Modern server implements server/discover with supported versions and capabilities | pinned era + request/response fixtures + discovery result + downgrade trace | FUTURE / NOT EXECUTED |
| A04-T002 | DISCOVERY-VERSION | Every modern request includes required protocolVersion and clientCapabilities metadata | pinned era + request/response fixtures + discovery result + downgrade trace | FUTURE / NOT EXECUTED |
| A04-T003 | DISCOVERY-VERSION | Missing required protocol metadata is rejected before handler dispatch | pinned era + request/response fixtures + discovery result + downgrade trace | FUTURE / NOT EXECUTED |
| A04-T004 | DISCOVERY-VERSION | Server identity metadata is display only and never principal | pinned era + request/response fixtures + discovery result + downgrade trace | FUTURE / NOT EXECUTED |
| A04-T005 | DISCOVERY-VERSION | Modern 2026 request succeeds without initialize handshake | pinned era + request/response fixtures + discovery result + downgrade trace | FUTURE / NOT EXECUTED |
| A04-T006 | DISCOVERY-VERSION | Recognized UnsupportedProtocolVersionError offers supported versions | pinned era + request/response fixtures + discovery result + downgrade trace | FUTURE / NOT EXECUTED |
| A04-T007 | DISCOVERY-VERSION | Client/server era negotiation chooses mutually supported version | pinned era + request/response fixtures + discovery result + downgrade trace | FUTURE / NOT EXECUTED |
| A04-T008 | DISCOVERY-VERSION | Modern unsupported-version response never triggers legacy downgrade | pinned era + request/response fixtures + discovery result + downgrade trace | FUTURE / NOT EXECUTED |
| A04-T009 | DISCOVERY-VERSION | Legacy 2025-11-25 initialize handshake succeeds only on compatibility path | pinned era + request/response fixtures + discovery result + downgrade trace | FUTURE / NOT EXECUTED |
| A04-T010 | DISCOVERY-VERSION | Legacy initialized notification is not required or accepted as modern state | pinned era + request/response fixtures + discovery result + downgrade trace | FUTURE / NOT EXECUTED |
| A04-T011 | DISCOVERY-VERSION | Era detection is cached per configured process/origin and invalidated safely | pinned era + request/response fixtures + discovery result + downgrade trace | FUTURE / NOT EXECUTED |
| A04-T012 | DISCOVERY-VERSION | Unsupported draft/unknown version is rejected with stable error | pinned era + request/response fixtures + discovery result + downgrade trace | FUTURE / NOT EXECUTED |
| A04-T013 | DISCOVERY-VERSION | Protocol version header must match request body metadata | pinned era + request/response fixtures + discovery result + downgrade trace | FUTURE / NOT EXECUTED |
| A04-T014 | DISCOVERY-VERSION | Modern and legacy method capability sets do not bleed into each other | pinned era + request/response fixtures + discovery result + downgrade trace | FUTURE / NOT EXECUTED |
| A04-T015 | DISCOVERY-VERSION | 2024-11-05 HTTP+SSE is rejected unless separately enabled and proven | pinned era + request/response fixtures + discovery result + downgrade trace | FUTURE / NOT EXECUTED |
| A04-T016 | DISCOVERY-VERSION | All advertised features match exact pinned conformance evidence | pinned era + request/response fixtures + discovery result + downgrade trace | FUTURE / NOT EXECUTED |
| A04-T017 | STDIO-PROCESS | STDIO server reads valid UTF-8 JSON-RPC frame | stdin/stdout capture + stderr audit + OS/arch lifecycle trace | FUTURE / NOT EXECUTED |
| A04-T018 | STDIO-PROCESS | STDOUT contains only valid MCP JSON-RPC messages | stdin/stdout capture + stderr audit + OS/arch lifecycle trace | FUTURE / NOT EXECUTED |
| A04-T019 | STDIO-PROCESS | Startup diagnostics and logs go to STDERR only | stdin/stdout capture + stderr audit + OS/arch lifecycle trace | FUTURE / NOT EXECUTED |
| A04-T020 | STDIO-PROCESS | Embedded newline and malformed framing are rejected | stdin/stdout capture + stderr audit + OS/arch lifecycle trace | FUTURE / NOT EXECUTED |
| A04-T021 | STDIO-PROCESS | Invalid UTF-8 and oversized input frame are rejected | stdin/stdout capture + stderr audit + OS/arch lifecycle trace | FUTURE / NOT EXECUTED |
| A04-T022 | STDIO-PROCESS | Unexpected EOF shuts down without fabricated response | stdin/stdout capture + stderr audit + OS/arch lifecycle trace | FUTURE / NOT EXECUTED |
| A04-T023 | STDIO-PROCESS | Host-supplied arguments cannot enable arbitrary shell execution | stdin/stdout capture + stderr audit + OS/arch lifecycle trace | FUTURE / NOT EXECUTED |
| A04-T024 | STDIO-PROCESS | Environment secrets are allowlisted and redacted | stdin/stdout capture + stderr audit + OS/arch lifecycle trace | FUTURE / NOT EXECUTED |
| A04-T025 | STDIO-PROCESS | Local process identity is verified independently of clientInfo | stdin/stdout capture + stderr audit + OS/arch lifecycle trace | FUTURE / NOT EXECUTED |
| A04-T026 | STDIO-PROCESS | Workspace/project selection is explicit and validated | stdin/stdout capture + stderr audit + OS/arch lifecycle trace | FUTURE / NOT EXECUTED |
| A04-T027 | STDIO-PROCESS | STDIO launch does not open TCP/UDP listeners | stdin/stdout capture + stderr audit + OS/arch lifecycle trace | FUTURE / NOT EXECUTED |
| A04-T028 | STDIO-PROCESS | Unexpected child exit returns bounded transport error | stdin/stdout capture + stderr audit + OS/arch lifecycle trace | FUTURE / NOT EXECUTED |
| A04-T029 | STDIO-PROCESS | Concurrent requests respect in-flight request limit | stdin/stdout capture + stderr audit + OS/arch lifecycle trace | FUTURE / NOT EXECUTED |
| A04-T030 | STDIO-PROCESS | Cancellation closes only associated operation/stream | stdin/stdout capture + stderr audit + OS/arch lifecycle trace | FUTURE / NOT EXECUTED |
| A04-T031 | STDIO-PROCESS | Malformed notification cannot invoke mutating owner command | stdin/stdout capture + stderr audit + OS/arch lifecycle trace | FUTURE / NOT EXECUTED |
| A04-T032 | STDIO-PROCESS | Windows/Linux/macOS stdio lifecycle behaves consistently | stdin/stdout capture + stderr audit + OS/arch lifecycle trace | FUTURE / NOT EXECUTED |
| A04-T033 | HTTP-STATELESS-LEGACY | Modern Streamable HTTP exposes a single POST endpoint | HTTP transcript + headers + negotiated version + server logs | FUTURE / NOT EXECUTED |
| A04-T034 | HTTP-STATELESS-LEGACY | Modern GET and DELETE are rejected with specification-compliant status | HTTP transcript + headers + negotiated version + server logs | FUTURE / NOT EXECUTED |
| A04-T035 | HTTP-STATELESS-LEGACY | Modern request does not mint or require session ID | HTTP transcript + headers + negotiated version + server logs | FUTURE / NOT EXECUTED |
| A04-T036 | HTTP-STATELESS-LEGACY | Modern Last-Event-ID is ignored and no resumability claimed | HTTP transcript + headers + negotiated version + server logs | FUTURE / NOT EXECUTED |
| A04-T037 | HTTP-STATELESS-LEGACY | Every modern JSON-RPC request uses its own HTTP POST | HTTP transcript + headers + negotiated version + server logs | FUTURE / NOT EXECUTED |
| A04-T038 | HTTP-STATELESS-LEGACY | Accept header negotiation supports JSON and event-stream | HTTP transcript + headers + negotiated version + server logs | FUTURE / NOT EXECUTED |
| A04-T039 | HTTP-STATELESS-LEGACY | Modern response stream is scoped to originating request | HTTP transcript + headers + negotiated version + server logs | FUTURE / NOT EXECUTED |
| A04-T040 | HTTP-STATELESS-LEGACY | Modern MCP-Protocol-Version is required and matches body metadata | HTTP transcript + headers + negotiated version + server logs | FUTURE / NOT EXECUTED |
| A04-T041 | HTTP-STATELESS-LEGACY | Mcp-Method header matches actual JSON-RPC method | HTTP transcript + headers + negotiated version + server logs | FUTURE / NOT EXECUTED |
| A04-T042 | HTTP-STATELESS-LEGACY | Mcp-Name header matches tools/call resources/read/prompts/get target | HTTP transcript + headers + negotiated version + server logs | FUTURE / NOT EXECUTED |
| A04-T043 | HTTP-STATELESS-LEGACY | Non-ASCII MCP name header uses specified safe encoding | HTTP transcript + headers + negotiated version + server logs | FUTURE / NOT EXECUTED |
| A04-T044 | HTTP-STATELESS-LEGACY | Legacy 2025-11-25 session lifecycle is isolated from modern requests | HTTP transcript + headers + negotiated version + server logs | FUTURE / NOT EXECUTED |
| A04-T045 | HTTP-STATELESS-LEGACY | Legacy GET SSE and session DELETE pass only legacy fixtures | HTTP transcript + headers + negotiated version + server logs | FUTURE / NOT EXECUTED |
| A04-T046 | HTTP-STATELESS-LEGACY | Modern load balancing requires no sticky session | HTTP transcript + headers + negotiated version + server logs | FUTURE / NOT EXECUTED |
| A04-T047 | HTTP-STATELESS-LEGACY | Broken modern SSE stream is treated as lost in-flight request | HTTP transcript + headers + negotiated version + server logs | FUTURE / NOT EXECUTED |
| A04-T048 | HTTP-STATELESS-LEGACY | Retry after stream loss uses new request ID and owner idempotency for mutation | HTTP transcript + headers + negotiated version + server logs | FUTURE / NOT EXECUTED |
| A04-T049 | AUTH-ORIGIN-OAUTH | Invalid Origin is rejected with HTTP 403 | issuer/audience/scope fixtures + Origin matrix + denial trace + zero owner invocations | FUTURE / NOT EXECUTED |
| A04-T050 | AUTH-ORIGIN-OAUTH | Absent Origin follows explicit non-browser policy without wildcard | issuer/audience/scope fixtures + Origin matrix + denial trace + zero owner invocations | FUTURE / NOT EXECUTED |
| A04-T051 | AUTH-ORIGIN-OAUTH | Loopback-only profile binds to 127.0.0.1 | issuer/audience/scope fixtures + Origin matrix + denial trace + zero owner invocations | FUTURE / NOT EXECUTED |
| A04-T052 | AUTH-ORIGIN-OAUTH | Remote HTTP cannot start without explicit owner enablement | issuer/audience/scope fixtures + Origin matrix + denial trace + zero owner invocations | FUTURE / NOT EXECUTED |
| A04-T053 | AUTH-ORIGIN-OAUTH | Remote mode requires trusted HTTPS/TLS ingress | issuer/audience/scope fixtures + Origin matrix + denial trace + zero owner invocations | FUTURE / NOT EXECUTED |
| A04-T054 | AUTH-ORIGIN-OAUTH | CORS rejects unlisted origins and credentialed wildcard | issuer/audience/scope fixtures + Origin matrix + denial trace + zero owner invocations | FUTURE / NOT EXECUTED |
| A04-T055 | AUTH-ORIGIN-OAUTH | Protected Resource Metadata RFC 9728 is served correctly | issuer/audience/scope fixtures + Origin matrix + denial trace + zero owner invocations | FUTURE / NOT EXECUTED |
| A04-T056 | AUTH-ORIGIN-OAUTH | Authorization-server discovery validates RFC 8414/OIDC issuer | issuer/audience/scope fixtures + Origin matrix + denial trace + zero owner invocations | FUTURE / NOT EXECUTED |
| A04-T057 | AUTH-ORIGIN-OAUTH | Missing bearer token produces HTTP 401 metadata challenge | issuer/audience/scope fixtures + Origin matrix + denial trace + zero owner invocations | FUTURE / NOT EXECUTED |
| A04-T058 | AUTH-ORIGIN-OAUTH | Expired or malformed bearer token is rejected | issuer/audience/scope fixtures + Origin matrix + denial trace + zero owner invocations | FUTURE / NOT EXECUTED |
| A04-T059 | AUTH-ORIGIN-OAUTH | Wrong token audience/resource is rejected | issuer/audience/scope fixtures + Origin matrix + denial trace + zero owner invocations | FUTURE / NOT EXECUTED |
| A04-T060 | AUTH-ORIGIN-OAUTH | Untrusted token issuer is rejected | issuer/audience/scope fixtures + Origin matrix + denial trace + zero owner invocations | FUTURE / NOT EXECUTED |
| A04-T061 | AUTH-ORIGIN-OAUTH | Insufficient scopes produce HTTP 403 without owner invocation | issuer/audience/scope fixtures + Origin matrix + denial trace + zero owner invocations | FUTURE / NOT EXECUTED |
| A04-T062 | AUTH-ORIGIN-OAUTH | Incoming bearer token is never passed downstream | issuer/audience/scope fixtures + Origin matrix + denial trace + zero owner invocations | FUTURE / NOT EXECUTED |
| A04-T063 | AUTH-ORIGIN-OAUTH | Every request revalidates actor/project/grant/policy epoch | issuer/audience/scope fixtures + Origin matrix + denial trace + zero owner invocations | FUTURE / NOT EXECUTED |
| A04-T064 | AUTH-ORIGIN-OAUTH | Cross-project token/cursor/task/resource access is denied without enumeration | issuer/audience/scope fixtures + Origin matrix + denial trace + zero owner invocations | FUTURE / NOT EXECUTED |
| A04-T065 | TOOLS-OWNER-BRIDGE | tools/list exposes only AI-03 descriptors visible to verified principal | AI-03 descriptor digest + AI-01 receipt + schema validation + owner readback | FUTURE / NOT EXECUTED |
| A04-T066 | TOOLS-OWNER-BRIDGE | Tool listing order is deterministic | AI-03 descriptor digest + AI-01 receipt + schema validation + owner readback | FUTURE / NOT EXECUTED |
| A04-T067 | TOOLS-OWNER-BRIDGE | Tool cursor is scoped to actor/project/generation/policy epoch | AI-03 descriptor digest + AI-01 receipt + schema validation + owner readback | FUTURE / NOT EXECUTED |
| A04-T068 | TOOLS-OWNER-BRIDGE | Hidden command count and private names are not leaked | AI-03 descriptor digest + AI-01 receipt + schema validation + owner readback | FUTURE / NOT EXECUTED |
| A04-T069 | TOOLS-OWNER-BRIDGE | Every tool maps to one stable AI-01 CommandId and owner | AI-03 descriptor digest + AI-01 receipt + schema validation + owner readback | FUTURE / NOT EXECUTED |
| A04-T070 | TOOLS-OWNER-BRIDGE | Tool inputSchema is object-root and matches AI-03 digest | AI-03 descriptor digest + AI-01 receipt + schema validation + owner readback | FUTURE / NOT EXECUTED |
| A04-T071 | TOOLS-OWNER-BRIDGE | Tool outputSchema and structuredContent conform to AI-03 | AI-03 descriptor digest + AI-01 receipt + schema validation + owner readback | FUTURE / NOT EXECUTED |
| A04-T072 | TOOLS-OWNER-BRIDGE | Structured result includes compatibility text where required | AI-03 descriptor digest + AI-01 receipt + schema validation + owner readback | FUTURE / NOT EXECUTED |
| A04-T073 | TOOLS-OWNER-BRIDGE | Tool annotations do not affect permission or safety | AI-03 descriptor digest + AI-01 receipt + schema validation + owner readback | FUTURE / NOT EXECUTED |
| A04-T074 | TOOLS-OWNER-BRIDGE | tools/call rejects invalid input before owner dispatch | AI-03 descriptor digest + AI-01 receipt + schema validation + owner readback | FUTURE / NOT EXECUTED |
| A04-T075 | TOOLS-OWNER-BRIDGE | tools/call forwards typed arguments and owner revision | AI-03 descriptor digest + AI-01 receipt + schema validation + owner readback | FUTURE / NOT EXECUTED |
| A04-T076 | TOOLS-OWNER-BRIDGE | AI-01 rechecks grant and revision after discovery | AI-03 descriptor digest + AI-01 receipt + schema validation + owner readback | FUTURE / NOT EXECUTED |
| A04-T077 | TOOLS-OWNER-BRIDGE | Mutation cannot bypass owner idempotency or CAS | AI-03 descriptor digest + AI-01 receipt + schema validation + owner readback | FUTURE / NOT EXECUTED |
| A04-T078 | TOOLS-OWNER-BRIDGE | Owner errors map without stack/path leakage | AI-03 descriptor digest + AI-01 receipt + schema validation + owner readback | FUTURE / NOT EXECUTED |
| A04-T079 | TOOLS-OWNER-BRIDGE | Unsupported target or unavailable owner is not executable | AI-03 descriptor digest + AI-01 receipt + schema validation + owner readback | FUTURE / NOT EXECUTED |
| A04-T080 | TOOLS-OWNER-BRIDGE | Tool-name collision is rejected before server discovery | AI-03 descriptor digest + AI-01 receipt + schema validation + owner readback | FUTURE / NOT EXECUTED |
| A04-T081 | RESOURCES-PROMPTS-CACHE | resources/list is filtered by principal and project | provider fixture + project ACL + cache epoch + prompt selection trace | FUTURE / NOT EXECUTED |
| A04-T082 | RESOURCES-PROMPTS-CACHE | resources/templates/list exposes only registered bounded templates | provider fixture + project ACL + cache epoch + prompt selection trace | FUTURE / NOT EXECUTED |
| A04-T083 | RESOURCES-PROMPTS-CACHE | resources/read accepts only opaque Stormline URIs | provider fixture + project ACL + cache epoch + prompt selection trace | FUTURE / NOT EXECUTED |
| A04-T084 | RESOURCES-PROMPTS-CACHE | file URI and arbitrary local path are rejected | provider fixture + project ACL + cache epoch + prompt selection trace | FUTURE / NOT EXECUTED |
| A04-T085 | RESOURCES-PROMPTS-CACHE | Remote resource URI cannot trigger SSRF or credential forwarding | provider fixture + project ACL + cache epoch + prompt selection trace | FUTURE / NOT EXECUTED |
| A04-T086 | RESOURCES-PROMPTS-CACHE | Resource read is bounded by bytes/time/MIME/page limits | provider fixture + project ACL + cache epoch + prompt selection trace | FUTURE / NOT EXECUTED |
| A04-T087 | RESOURCES-PROMPTS-CACHE | Resource response includes valid ttlMs and cacheScope | provider fixture + project ACL + cache epoch + prompt selection trace | FUTURE / NOT EXECUTED |
| A04-T088 | RESOURCES-PROMPTS-CACHE | Private resource cache cannot be reused by another actor/project | provider fixture + project ACL + cache epoch + prompt selection trace | FUTURE / NOT EXECUTED |
| A04-T089 | RESOURCES-PROMPTS-CACHE | Public cache scope requires proof resource is public | provider fixture + project ACL + cache epoch + prompt selection trace | FUTURE / NOT EXECUTED |
| A04-T090 | RESOURCES-PROMPTS-CACHE | Policy epoch change invalidates cache and cursor | provider fixture + project ACL + cache epoch + prompt selection trace | FUTURE / NOT EXECUTED |
| A04-T091 | RESOURCES-PROMPTS-CACHE | Subscription emits only explicitly requested resource updates | provider fixture + project ACL + cache epoch + prompt selection trace | FUTURE / NOT EXECUTED |
| A04-T092 | RESOURCES-PROMPTS-CACHE | Subscription is cancelled on project switch/revocation | provider fixture + project ACL + cache epoch + prompt selection trace | FUTURE / NOT EXECUTED |
| A04-T093 | RESOURCES-PROMPTS-CACHE | prompts/list returns only approved user-selectable templates | provider fixture + project ACL + cache epoch + prompt selection trace | FUTURE / NOT EXECUTED |
| A04-T094 | RESOURCES-PROMPTS-CACHE | prompts/get validates prompt ID and typed arguments | provider fixture + project ACL + cache epoch + prompt selection trace | FUTURE / NOT EXECUTED |
| A04-T095 | RESOURCES-PROMPTS-CACHE | Prompt content cannot grant permission or auto-execute commands | provider fixture + project ACL + cache epoch + prompt selection trace | FUTURE / NOT EXECUTED |
| A04-T096 | RESOURCES-PROMPTS-CACHE | Prompt descriptions/examples are untrusted content | provider fixture + project ACL + cache epoch + prompt selection trace | FUTURE / NOT EXECUTED |
| A04-T097 | MRTR-SUBSCRIPTIONS-TASKS | Modern input_required carries typed inputRequests | MRTR keys + subscription filter + task journal + owner job receipt | FUTURE / NOT EXECUTED |
| A04-T098 | MRTR-SUBSCRIPTIONS-TASKS | MRTR response is bound to original operation and unique key | MRTR keys + subscription filter + task journal + owner job receipt | FUTURE / NOT EXECUTED |
| A04-T099 | MRTR-SUBSCRIPTIONS-TASKS | Duplicate/unknown inputResponses cannot satisfy another request | MRTR keys + subscription filter + task journal + owner job receipt | FUTURE / NOT EXECUTED |
| A04-T100 | MRTR-SUBSCRIPTIONS-TASKS | MRTR input is not transaction approval | MRTR keys + subscription filter + task journal + owner job receipt | FUTURE / NOT EXECUTED |
| A04-T101 | MRTR-SUBSCRIPTIONS-TASKS | Owner permission is revalidated after MRTR round trip | MRTR keys + subscription filter + task journal + owner job receipt | FUTURE / NOT EXECUTED |
| A04-T102 | MRTR-SUBSCRIPTIONS-TASKS | subscriptions/listen requires explicit notification filter | MRTR keys + subscription filter + task journal + owner job receipt | FUTURE / NOT EXECUTED |
| A04-T103 | MRTR-SUBSCRIPTIONS-TASKS | Server never sends unrequested notification type | MRTR keys + subscription filter + task journal + owner job receipt | FUTURE / NOT EXECUTED |
| A04-T104 | MRTR-SUBSCRIPTIONS-TASKS | Subscription notification includes valid subscriptionId | MRTR keys + subscription filter + task journal + owner job receipt | FUTURE / NOT EXECUTED |
| A04-T105 | MRTR-SUBSCRIPTIONS-TASKS | Concurrent subscriptions respect per-principal/global limits | MRTR keys + subscription filter + task journal + owner job receipt | FUTURE / NOT EXECUTED |
| A04-T106 | MRTR-SUBSCRIPTIONS-TASKS | Disconnect and re-subscribe recover from authoritative revision | MRTR keys + subscription filter + task journal + owner job receipt | FUTURE / NOT EXECUTED |
| A04-T107 | MRTR-SUBSCRIPTIONS-TASKS | Tasks is not advertised without durable owner JobHandle | MRTR keys + subscription filter + task journal + owner job receipt | FUTURE / NOT EXECUTED |
| A04-T108 | MRTR-SUBSCRIPTIONS-TASKS | CreateTaskResult is never returned without client Tasks capability | MRTR keys + subscription filter + task journal + owner job receipt | FUTURE / NOT EXECUTED |
| A04-T109 | MRTR-SUBSCRIPTIONS-TASKS | Task handle is durable/queryable before returned | MRTR keys + subscription filter + task journal + owner job receipt | FUTURE / NOT EXECUTED |
| A04-T110 | MRTR-SUBSCRIPTIONS-TASKS | Task IDs are high entropy and not enumerable through list | MRTR keys + subscription filter + task journal + owner job receipt | FUTURE / NOT EXECUTED |
| A04-T111 | MRTR-SUBSCRIPTIONS-TASKS | tasks/get/update/cancel reauthorize every request | MRTR keys + subscription filter + task journal + owner job receipt | FUTURE / NOT EXECUTED |
| A04-T112 | MRTR-SUBSCRIPTIONS-TASKS | Task cancellation/expiry/owner failure return typed terminal state | MRTR keys + subscription filter + task journal + owner job receipt | FUTURE / NOT EXECUTED |
| A04-T113 | CONFORMANCE-OBSERVABILITY-PLATFORM | Official conformance suite passes pinned 2026-07-28 active scenarios | conformance run + host versions + traces/metrics + OS matrix + SBOM | FUTURE / NOT EXECUTED |
| A04-T114 | CONFORMANCE-OBSERVABILITY-PLATFORM | Official legacy conformance passes 2025-11-25 if claimed | conformance run + host versions + traces/metrics + OS matrix + SBOM | FUTURE / NOT EXECUTED |
| A04-T115 | CONFORMANCE-OBSERVABILITY-PLATFORM | Codex pinned release negotiates and calls read-only tool | conformance run + host versions + traces/metrics + OS matrix + SBOM | FUTURE / NOT EXECUTED |
| A04-T116 | CONFORMANCE-OBSERVABILITY-PLATFORM | Claude pinned release negotiates and calls read-only tool | conformance run + host versions + traces/metrics + OS matrix + SBOM | FUTURE / NOT EXECUTED |
| A04-T117 | CONFORMANCE-OBSERVABILITY-PLATFORM | Unsupported host version reports incompatibility without fallback | conformance run + host versions + traces/metrics + OS matrix + SBOM | FUTURE / NOT EXECUTED |
| A04-T118 | CONFORMANCE-OBSERVABILITY-PLATFORM | Tools/resources/prompts parity is verified across selected hosts | conformance run + host versions + traces/metrics + OS matrix + SBOM | FUTURE / NOT EXECUTED |
| A04-T119 | CONFORMANCE-OBSERVABILITY-PLATFORM | Request IDs and trace IDs correlate protocol and owner receipts | conformance run + host versions + traces/metrics + OS matrix + SBOM | FUTURE / NOT EXECUTED |
| A04-T120 | CONFORMANCE-OBSERVABILITY-PLATFORM | Tokens and sensitive arguments are redacted from traces | conformance run + host versions + traces/metrics + OS matrix + SBOM | FUTURE / NOT EXECUTED |
| A04-T121 | CONFORMANCE-OBSERVABILITY-PLATFORM | Per-request logLevel honored only when negotiated and requested | conformance run + host versions + traces/metrics + OS matrix + SBOM | FUTURE / NOT EXECUTED |
| A04-T122 | CONFORMANCE-OBSERVABILITY-PLATFORM | Roots/sampling/logging are not required by modern baseline | conformance run + host versions + traces/metrics + OS matrix + SBOM | FUTURE / NOT EXECUTED |
| A04-T123 | CONFORMANCE-OBSERVABILITY-PLATFORM | Rate limits and backpressure protect against floods | conformance run + host versions + traces/metrics + OS matrix + SBOM | FUTURE / NOT EXECUTED |
| A04-T124 | CONFORMANCE-OBSERVABILITY-PLATFORM | Response bytes and JSON depth caps prevent exhaustion | conformance run + host versions + traces/metrics + OS matrix + SBOM | FUTURE / NOT EXECUTED |
| A04-T125 | CONFORMANCE-OBSERVABILITY-PLATFORM | Cold start/list/read/call latency measured reproducibly | conformance run + host versions + traces/metrics + OS matrix + SBOM | FUTURE / NOT EXECUTED |
| A04-T126 | CONFORMANCE-OBSERVABILITY-PLATFORM | Concurrent request/subscription memory within approved budget | conformance run + host versions + traces/metrics + OS matrix + SBOM | FUTURE / NOT EXECUTED |
| A04-T127 | CONFORMANCE-OBSERVABILITY-PLATFORM | Windows/Linux/macOS packaging and stdio matrix verified | conformance run + host versions + traces/metrics + OS matrix + SBOM | FUTURE / NOT EXECUTED |
| A04-T128 | CONFORMANCE-OBSERVABILITY-PLATFORM | Evidence records exact protocol/host/SDK/license/conformance revisions | conformance run + host versions + traces/metrics + OS matrix + SBOM | FUTURE / NOT EXECUTED |

## Release gate
100% of official required conformance scenarios pass for every advertised protocol/transport version at pinned suite revision; pending/draft cases reported separately. Selected host tests pass or are explicitly unsupported. No HIGH/CRITICAL authorization, SSRF, DNS rebinding, token passthrough, prompt injection, cross-project leak, downgrade or task ownership defect. Tool calls bind AI-03 descriptors and AI-01 receipts. All 128 tests implemented and passing; conditional Tasks tests proven or NOT SUPPORTED. Benchmarks use approved thresholds. Missing implementation is NOT EXECUTED, never PASS. Global engine DoD and predecessor approvals remain required.

[Architecture](../architecture/ai-04-mcp-server-protocol-adapter.md) · [Contracts](../contracts/ai-04-mcp-server-contracts.md) · [Benchmark](../research/ai-04-mcp-benchmark-protocol.md).
