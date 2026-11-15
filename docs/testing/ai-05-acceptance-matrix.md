# AI-05 — 128 Future MCP Context Resource & Template Acceptance Tests

**2026-11-15 | P00 RESEARCH ONLY / NOT IMPLEMENTED | [research #297](https://github.com/KayzenRoot/stormline/issues/297) | WO NLE-P00-WO-002-AI-05 | code #79 OPEN/BLOCKED | BASE `ec1a8efc89de6e90d53f7b56fd31bc874335a2ff`.** Formal dependencies AI-02 + AI-04 only; ADR-0064 PROPOSED, no runtime or test harness.

**Exactly 128 distinct `A05-T001..A05-T128`, all FUTURE / NOT EXECUTED. Zero run, zero PASS, zero FAIL.** Eight groups of sixteen. These are independent future test obligations, not a claim of working MCP resources or server, SDK, source index, or host compatibility.

## Future gate and independent oracle
1. Pin the MCP 2026-07-28 conformance suite revision, SDK/protocol version and real host versions for every scenario; 2025-11-25 legacy only if claimed and explicitly negotiated by AI-04.
2. Use rights-cleared synthetic owner projects of 100 / 10,000 / 100,000 entries with independent labeled scene, asset, script, schema, documentation and license ground truth. A source index entry is not its own coverage oracle.
3. Source fixtures include committed revision and owner digest, AI-02 generation, ACL epoch, actor/project/grant, provider capability, real authorized source ranges and rights classifications.
4. Verify outputs with independent source-owner queries, not just provider self-reported status. For every denied/changed resource, assert zero unauthorized owner read, zero leaked bytes, identifiers, counts and suggestions.
5. Require actual bytes and approximate token reporting. Do not claim exact tokens without pinned target tokenizer. Compare against a rights-equivalent full-project context baseline.
6. All negative security scenarios require no unauthorized file/network/command side effect. A 403/denial alone does not prove safe outcome.
7. Future real host conformance is distinct from green documentation CI. No benchmark threshold is declared before measurements.

## Eight groups
| Group | IDs | Count | Focus |
|---|---|---:|---|
| CATALOG-LIST | A05-T001..A05-T016 | 16 | authorized inventory, deterministic catalog, source metadata |
| TEMPLATES-URI | A05-T017..A05-T032 | 16 | RFC6570, typed opaque IDs, URI traversal and Unicode |
| READ-PROVENANCE | A05-T033..A05-T048 | 16 | owner revisions, citations, rights, bounded hydration |
| PAGINATION-BUDGET | A05-T049..A05-T064 | 16 | actor-scoped cursors, generation, bytes and partial responses |
| AUTH-CACHE-RIGHTS | A05-T065..A05-T080 | 16 | ACL, cacheScope, revocation, secret/IP protection |
| PROMPTS-RECIPES | A05-T081..A05-T096 | 16 | user-controlled prompts, safe interpolation, no execution |
| COMPLETION-SUBS | A05-T097..A05-T112 | 16 | optional completion, notifications, legacy mapping |
| E2E-SECURITY-PERF | A05-T113..A05-T128 | 16 | conformance, Codex/Claude, quality, multi-OS, recovery |

## Complete future test matrix
| Test ID | Group | Scenario / assertion | Required independent evidence | Status |
|---|---|---|---|---|
| A05-T001 | CATALOG-LIST | resources/list emits only authorized project root context entries | AI-02 source inventory+MCP list JSON+principal policy+coverage oracle | FUTURE / NOT EXECUTED |
| A05-T002 | CATALOG-LIST | Listing is deterministic for same source snapshot and policy | AI-02 source inventory+MCP list JSON+principal policy+coverage oracle | FUTURE / NOT EXECUTED |
| A05-T003 | CATALOG-LIST | Empty accessible project returns an honest empty resource page | AI-02 source inventory+MCP list JSON+principal policy+coverage oracle | FUTURE / NOT EXECUTED |
| A05-T004 | CATALOG-LIST | Unavailable optional owner sources mark inventory partial, not complete | AI-02 source inventory+MCP list JSON+principal policy+coverage oracle | FUTURE / NOT EXECUTED |
| A05-T005 | CATALOG-LIST | Schema catalog entry points to approved AI-03 schema digest | AI-02 source inventory+MCP list JSON+principal policy+coverage oracle | FUTURE / NOT EXECUTED |
| A05-T006 | CATALOG-LIST | Scene list names refer to owner-verified authoring scene IDs | AI-02 source inventory+MCP list JSON+principal policy+coverage oracle | FUTURE / NOT EXECUTED |
| A05-T007 | CATALOG-LIST | Asset listing preserves DATA-02 AssetId across rename | AI-02 source inventory+MCP list JSON+principal policy+coverage oracle | FUTURE / NOT EXECUTED |
| A05-T008 | CATALOG-LIST | Script symbol listing uses AI-02 owner source-map references | AI-02 source inventory+MCP list JSON+principal policy+coverage oracle | FUTURE / NOT EXECUTED |
| A05-T009 | CATALOG-LIST | Resource title, MIME and size are bounded and correctly typed | AI-02 source inventory+MCP list JSON+principal policy+coverage oracle | FUTURE / NOT EXECUTED |
| A05-T010 | CATALOG-LIST | Listing filters reject unknown kinds and invalid field selectors | AI-02 source inventory+MCP list JSON+principal policy+coverage oracle | FUTURE / NOT EXECUTED |
| A05-T011 | CATALOG-LIST | Listing of hidden project reveals no names, counts or revisions | AI-02 source inventory+MCP list JSON+principal policy+coverage oracle | FUTURE / NOT EXECUTED |
| A05-T012 | CATALOG-LIST | Resource catalog does not invent executable owner capabilities | AI-02 source inventory+MCP list JSON+principal policy+coverage oracle | FUTURE / NOT EXECUTED |
| A05-T013 | CATALOG-LIST | Listing large project never automatically emits all asset entries | AI-02 source inventory+MCP list JSON+principal policy+coverage oracle | FUTURE / NOT EXECUTED |
| A05-T014 | CATALOG-LIST | Manifest root has a bounded number of typed resource categories | AI-02 source inventory+MCP list JSON+principal policy+coverage oracle | FUTURE / NOT EXECUTED |
| A05-T015 | CATALOG-LIST | Resource catalog version changes are announced only when supported | AI-02 source inventory+MCP list JSON+principal policy+coverage oracle | FUTURE / NOT EXECUTED |
| A05-T016 | CATALOG-LIST | Index status reports partial owner coverage without unapproved guesses | AI-02 source inventory+MCP list JSON+principal policy+coverage oracle | FUTURE / NOT EXECUTED |
| A05-T017 | TEMPLATES-URI | resources/templates/list publishes only allowlisted typed URI templates | RFC6570 input corpus+canonical URI identity+zero external access trace | FUTURE / NOT EXECUTED |
| A05-T018 | TEMPLATES-URI | RFC6570 variable expansion percent-encodes UTF-8 safely | RFC6570 input corpus+canonical URI identity+zero external access trace | FUTURE / NOT EXECUTED |
| A05-T019 | TEMPLATES-URI | Opaque ProjectId and AssetId are required instead of raw file paths | RFC6570 input corpus+canonical URI identity+zero external access trace | FUTURE / NOT EXECUTED |
| A05-T020 | TEMPLATES-URI | Reserved expansion operator is rejected for project resource paths | RFC6570 input corpus+canonical URI identity+zero external access trace | FUTURE / NOT EXECUTED |
| A05-T021 | TEMPLATES-URI | Reject template argument containing parent traversal segments | RFC6570 input corpus+canonical URI identity+zero external access trace | FUTURE / NOT EXECUTED |
| A05-T022 | TEMPLATES-URI | Reject percent-encoded slash traversal and double-decoding attempt | RFC6570 input corpus+canonical URI identity+zero external access trace | FUTURE / NOT EXECUTED |
| A05-T023 | TEMPLATES-URI | Reject invalid percent triplets and invalid UTF-8 URI segments | RFC6570 input corpus+canonical URI identity+zero external access trace | FUTURE / NOT EXECUTED |
| A05-T024 | TEMPLATES-URI | Reject URI scheme change to file, http, https or data | RFC6570 input corpus+canonical URI identity+zero external access trace | FUTURE / NOT EXECUTED |
| A05-T025 | TEMPLATES-URI | Reject duplicate/conflicting query parameters in resource URI | RFC6570 input corpus+canonical URI identity+zero external access trace | FUTURE / NOT EXECUTED |
| A05-T026 | TEMPLATES-URI | Reject NUL, control and bidi override spoofing in URI identity | RFC6570 input corpus+canonical URI identity+zero external access trace | FUTURE / NOT EXECUTED |
| A05-T027 | TEMPLATES-URI | Cross-project URI replay is rejected even when IDs exist | RFC6570 input corpus+canonical URI identity+zero external access trace | FUTURE / NOT EXECUTED |
| A05-T028 | TEMPLATES-URI | Unknown source type or unsupported view returns safe typed error | RFC6570 input corpus+canonical URI identity+zero external access trace | FUTURE / NOT EXECUTED |
| A05-T029 | TEMPLATES-URI | URI template stable ID survives asset rename/move | RFC6570 input corpus+canonical URI identity+zero external access trace | FUTURE / NOT EXECUTED |
| A05-T030 | TEMPLATES-URI | URI template source revision points to exact owner revision | RFC6570 input corpus+canonical URI identity+zero external access trace | FUTURE / NOT EXECUTED |
| A05-T031 | TEMPLATES-URI | Malformed URI fuzz never invokes filesystem or external network | RFC6570 input corpus+canonical URI identity+zero external access trace | FUTURE / NOT EXECUTED |
| A05-T032 | TEMPLATES-URI | Auto-expanded template cannot escape advertised namespace | RFC6570 input corpus+canonical URI identity+zero external access trace | FUTURE / NOT EXECUTED |
| A05-T033 | READ-PROVENANCE | resources/read returns owner-cited exact revision and digest | AI-02 owner citation+exact revision/digest+bounded read receipt | FUTURE / NOT EXECUTED |
| A05-T034 | READ-PROVENANCE | Resource read revalidates permission after initial list discovery | AI-02 owner citation+exact revision/digest+bounded read receipt | FUTURE / NOT EXECUTED |
| A05-T035 | READ-PROVENANCE | Scene outline uses source scene revision, never runtime EntityHandle | AI-02 owner citation+exact revision/digest+bounded read receipt | FUTURE / NOT EXECUTED |
| A05-T036 | READ-PROVENANCE | Script symbol snippet requires verified owner source map | AI-02 owner citation+exact revision/digest+bounded read receipt | FUTURE / NOT EXECUTED |
| A05-T037 | READ-PROVENANCE | Schema resource uses source owner SchemaId and schema digest | AI-02 owner citation+exact revision/digest+bounded read receipt | FUTURE / NOT EXECUTED |
| A05-T038 | READ-PROVENANCE | Asset provenance is bounded and rights-classified | AI-02 owner citation+exact revision/digest+bounded read receipt | FUTURE / NOT EXECUTED |
| A05-T039 | READ-PROVENANCE | Missing source owner returns SOURCE_UNSUPPORTED without fabrication | AI-02 owner citation+exact revision/digest+bounded read receipt | FUTURE / NOT EXECUTED |
| A05-T040 | READ-PROVENANCE | AI-02 incomplete index returns explicit partial coverage | AI-02 owner citation+exact revision/digest+bounded read receipt | FUTURE / NOT EXECUTED |
| A05-T041 | READ-PROVENANCE | Markdown/HTML/control content is escaped as untrusted data | AI-02 owner citation+exact revision/digest+bounded read receipt | FUTURE / NOT EXECUTED |
| A05-T042 | READ-PROVENANCE | Resource read with oversized binary responds bounded metadata/error | AI-02 owner citation+exact revision/digest+bounded read receipt | FUTURE / NOT EXECUTED |
| A05-T043 | READ-PROVENANCE | Multiple sections retain stable provenance and deterministic order | AI-02 owner citation+exact revision/digest+bounded read receipt | FUTURE / NOT EXECUTED |
| A05-T044 | READ-PROVENANCE | Redacted field does not leak in resource text or metadata | AI-02 owner citation+exact revision/digest+bounded read receipt | FUTURE / NOT EXECUTED |
| A05-T045 | READ-PROVENANCE | Read fails closed when canonical owner snapshot is unavailable | AI-02 owner citation+exact revision/digest+bounded read receipt | FUTURE / NOT EXECUTED |
| A05-T046 | READ-PROVENANCE | Source tombstone prevents hydration of deleted asset | AI-02 owner citation+exact revision/digest+bounded read receipt | FUTURE / NOT EXECUTED |
| A05-T047 | READ-PROVENANCE | Resource MIME/encoding matches actual content | AI-02 owner citation+exact revision/digest+bounded read receipt | FUTURE / NOT EXECUTED |
| A05-T048 | READ-PROVENANCE | Source locator readback verifies cited owner revision | AI-02 owner citation+exact revision/digest+bounded read receipt | FUTURE / NOT EXECUTED |
| A05-T049 | PAGINATION-BUDGET | First page returns deterministic bounded resources and nextCursor | cursor envelope+generation/ACL snapshot+byte counter+trace | FUTURE / NOT EXECUTED |
| A05-T050 | PAGINATION-BUDGET | Second page retains stable item order for same generation | cursor envelope+generation/ACL snapshot+byte counter+trace | FUTURE / NOT EXECUTED |
| A05-T051 | PAGINATION-BUDGET | Forged/tampered cursor is rejected before owner hydration | cursor envelope+generation/ACL snapshot+byte counter+trace | FUTURE / NOT EXECUTED |
| A05-T052 | PAGINATION-BUDGET | Cursor for different actor or project is rejected | cursor envelope+generation/ACL snapshot+byte counter+trace | FUTURE / NOT EXECUTED |
| A05-T053 | PAGINATION-BUDGET | Cursor for different query/sort/profile is rejected | cursor envelope+generation/ACL snapshot+byte counter+trace | FUTURE / NOT EXECUTED |
| A05-T054 | PAGINATION-BUDGET | Cursor expired after policy epoch change is rejected | cursor envelope+generation/ACL snapshot+byte counter+trace | FUTURE / NOT EXECUTED |
| A05-T055 | PAGINATION-BUDGET | Cursor for evicted AI-02 generation returns SNAPSHOT_EXPIRED | cursor envelope+generation/ACL snapshot+byte counter+trace | FUTURE / NOT EXECUTED |
| A05-T056 | PAGINATION-BUDGET | Pagination terminates without duplicate or skipped authorized items | cursor envelope+generation/ACL snapshot+byte counter+trace | FUTURE / NOT EXECUTED |
| A05-T057 | PAGINATION-BUDGET | maxBytes caps actual UTF-8 response bytes including metadata | cursor envelope+generation/ACL snapshot+byte counter+trace | FUTURE / NOT EXECUTED |
| A05-T058 | PAGINATION-BUDGET | maxEstimatedTokens is labeled approximate for generic tokenizer | cursor envelope+generation/ACL snapshot+byte counter+trace | FUTURE / NOT EXECUTED |
| A05-T059 | PAGINATION-BUDGET | maxRows and maxPages prevent unbounded repository enumeration | cursor envelope+generation/ACL snapshot+byte counter+trace | FUTURE / NOT EXECUTED |
| A05-T060 | PAGINATION-BUDGET | Context pack truncates at section boundary preserving valid envelope | cursor envelope+generation/ACL snapshot+byte counter+trace | FUTURE / NOT EXECUTED |
| A05-T061 | PAGINATION-BUDGET | Cycle in dependency graph respects maxDepth and maxEdges | cursor envelope+generation/ACL snapshot+byte counter+trace | FUTURE / NOT EXECUTED |
| A05-T062 | PAGINATION-BUDGET | Budget exhaustion reports omissions and partial result truthfully | cursor envelope+generation/ACL snapshot+byte counter+trace | FUTURE / NOT EXECUTED |
| A05-T063 | PAGINATION-BUDGET | Large document cannot cause unbounded memory allocation | cursor envelope+generation/ACL snapshot+byte counter+trace | FUTURE / NOT EXECUTED |
| A05-T064 | PAGINATION-BUDGET | Cancel during context composition returns bounded recoverable state | cursor envelope+generation/ACL snapshot+byte counter+trace | FUTURE / NOT EXECUTED |
| A05-T065 | AUTH-CACHE-RIGHTS | ACL denies project before listing names, totals and suggestions | policy epochs+redacted trace+rights classifier+zero-leak oracle | FUTURE / NOT EXECUTED |
| A05-T066 | AUTH-CACHE-RIGHTS | ACL rechecks each source excerpt during hydration | policy epochs+redacted trace+rights classifier+zero-leak oracle | FUTURE / NOT EXECUTED |
| A05-T067 | AUTH-CACHE-RIGHTS | Grant revoked between list and read blocks read | policy epochs+redacted trace+rights classifier+zero-leak oracle | FUTURE / NOT EXECUTED |
| A05-T068 | AUTH-CACHE-RIGHTS | Grant revoked between pages invalidates cursor | policy epochs+redacted trace+rights classifier+zero-leak oracle | FUTURE / NOT EXECUTED |
| A05-T069 | AUTH-CACHE-RIGHTS | Grant revoked before completion removes hidden suggestions | policy epochs+redacted trace+rights classifier+zero-leak oracle | FUTURE / NOT EXECUTED |
| A05-T070 | AUTH-CACHE-RIGHTS | Source privacy policy changes invalidate server-side cache | policy epochs+redacted trace+rights classifier+zero-leak oracle | FUTURE / NOT EXECUTED |
| A05-T071 | AUTH-CACHE-RIGHTS | Modern private response uses ttlMs zero and cacheScope private by default | policy epochs+redacted trace+rights classifier+zero-leak oracle | FUTURE / NOT EXECUTED |
| A05-T072 | AUTH-CACHE-RIGHTS | Public cache is prohibited for project-specific context | policy epochs+redacted trace+rights classifier+zero-leak oracle | FUTURE / NOT EXECUTED |
| A05-T073 | AUTH-CACHE-RIGHTS | Positive TTL is refused without immutable source and rights proof | policy epochs+redacted trace+rights classifier+zero-leak oracle | FUTURE / NOT EXECUTED |
| A05-T074 | AUTH-CACHE-RIGHTS | Already distributed remote cache is not falsely claimed erased | policy epochs+redacted trace+rights classifier+zero-leak oracle | FUTURE / NOT EXECUTED |
| A05-T075 | AUTH-CACHE-RIGHTS | Cross-tenant cache key collision cannot reveal private content | policy epochs+redacted trace+rights classifier+zero-leak oracle | FUTURE / NOT EXECUTED |
| A05-T076 | AUTH-CACHE-RIGHTS | Denied resource does not reveal forbidden existence in error response | policy epochs+redacted trace+rights classifier+zero-leak oracle | FUTURE / NOT EXECUTED |
| A05-T077 | AUTH-CACHE-RIGHTS | Secrets and PII are redacted before serialization and caching | policy epochs+redacted trace+rights classifier+zero-leak oracle | FUTURE / NOT EXECUTED |
| A05-T078 | AUTH-CACHE-RIGHTS | Third-party asset marked restricted excludes copyrighted source excerpt | policy epochs+redacted trace+rights classifier+zero-leak oracle | FUTURE / NOT EXECUTED |
| A05-T079 | AUTH-CACHE-RIGHTS | Unauthorized actor cannot enumerate a hidden prompt recipe | policy epochs+redacted trace+rights classifier+zero-leak oracle | FUTURE / NOT EXECUTED |
| A05-T080 | AUTH-CACHE-RIGHTS | Logs and traces omit tokens, host paths and raw context secrets | policy epochs+redacted trace+rights classifier+zero-leak oracle | FUTURE / NOT EXECUTED |
| A05-T081 | PROMPTS-RECIPES | prompts/list returns only user-selectable approved recipes | versioned recipe manifest+user selection+no owner dispatch trace | FUTURE / NOT EXECUTED |
| A05-T082 | PROMPTS-RECIPES | Recipe name and semver are stable across compatible revisions | versioned recipe manifest+user selection+no owner dispatch trace | FUTURE / NOT EXECUTED |
| A05-T083 | PROMPTS-RECIPES | prompts/get validates required flat named-string arguments | versioned recipe manifest+user selection+no owner dispatch trace | FUTURE / NOT EXECUTED |
| A05-T084 | PROMPTS-RECIPES | Missing argument reports invalid params rather than guessing | versioned recipe manifest+user selection+no owner dispatch trace | FUTURE / NOT EXECUTED |
| A05-T085 | PROMPTS-RECIPES | Unknown prompt ID returns non-enumerating error | versioned recipe manifest+user selection+no owner dispatch trace | FUTURE / NOT EXECUTED |
| A05-T086 | PROMPTS-RECIPES | Prompt locale falls back only when semantics verified | versioned recipe manifest+user selection+no owner dispatch trace | FUTURE / NOT EXECUTED |
| A05-T087 | PROMPTS-RECIPES | Prompt template interpolation escapes untrusted user text | versioned recipe manifest+user selection+no owner dispatch trace | FUTURE / NOT EXECUTED |
| A05-T088 | PROMPTS-RECIPES | Prompt result includes citations to selected authorized resources | versioned recipe manifest+user selection+no owner dispatch trace | FUTURE / NOT EXECUTED |
| A05-T089 | PROMPTS-RECIPES | Recipe for unsupported source capability is not advertised as runnable | versioned recipe manifest+user selection+no owner dispatch trace | FUTURE / NOT EXECUTED |
| A05-T090 | PROMPTS-RECIPES | Prompts/get does not dispatch an AI-01 command | versioned recipe manifest+user selection+no owner dispatch trace | FUTURE / NOT EXECUTED |
| A05-T091 | PROMPTS-RECIPES | Prompt text cannot grant capability or authorize transaction | versioned recipe manifest+user selection+no owner dispatch trace | FUTURE / NOT EXECUTED |
| A05-T092 | PROMPTS-RECIPES | Prompt containing fake system instructions is treated as data | versioned recipe manifest+user selection+no owner dispatch trace | FUTURE / NOT EXECUTED |
| A05-T093 | PROMPTS-RECIPES | Recipe context dependencies are revision and rights scoped | versioned recipe manifest+user selection+no owner dispatch trace | FUTURE / NOT EXECUTED |
| A05-T094 | PROMPTS-RECIPES | Recursive templates and cyclic partials respect depth limits | versioned recipe manifest+user selection+no owner dispatch trace | FUTURE / NOT EXECUTED |
| A05-T095 | PROMPTS-RECIPES | User must explicitly select recipe before prompts/get | versioned recipe manifest+user selection+no owner dispatch trace | FUTURE / NOT EXECUTED |
| A05-T096 | PROMPTS-RECIPES | Prompt output and content size remain within declared budget | versioned recipe manifest+user selection+no owner dispatch trace | FUTURE / NOT EXECUTED |
| A05-T097 | COMPLETION-SUBS | completion/complete accepts only supported prompt/template refs | completion/suggestion fixture+subscriptions listen trace+policy epoch | FUTURE / NOT EXECUTED |
| A05-T098 | COMPLETION-SUBS | Completion returns only project-authorized argument values | completion/suggestion fixture+subscriptions listen trace+policy epoch | FUTURE / NOT EXECUTED |
| A05-T099 | COMPLETION-SUBS | Completion is bounded to at most 100 values | completion/suggestion fixture+subscriptions listen trace+policy epoch | FUTURE / NOT EXECUTED |
| A05-T100 | COMPLETION-SUBS | Completion ordering is stable for fixed prefix and generation | completion/suggestion fixture+subscriptions listen trace+policy epoch | FUTURE / NOT EXECUTED |
| A05-T101 | COMPLETION-SUBS | Completion partial values are safe and correctly escaped | completion/suggestion fixture+subscriptions listen trace+policy epoch | FUTURE / NOT EXECUTED |
| A05-T102 | COMPLETION-SUBS | Completion context.arguments is validated against recipe manifest | completion/suggestion fixture+subscriptions listen trace+policy epoch | FUTURE / NOT EXECUTED |
| A05-T103 | COMPLETION-SUBS | Completion rate limits and deadlines resist prefix probing | completion/suggestion fixture+subscriptions listen trace+policy epoch | FUTURE / NOT EXECUTED |
| A05-T104 | COMPLETION-SUBS | Completion total does not count hidden ACL-denied matches | completion/suggestion fixture+subscriptions listen trace+policy epoch | FUTURE / NOT EXECUTED |
| A05-T105 | COMPLETION-SUBS | Unavailable completion feature does not break resources or prompts | completion/suggestion fixture+subscriptions listen trace+policy epoch | FUTURE / NOT EXECUTED |
| A05-T106 | COMPLETION-SUBS | Modern subscriptions/listen only delivers opted-in context notifications | completion/suggestion fixture+subscriptions listen trace+policy epoch | FUTURE / NOT EXECUTED |
| A05-T107 | COMPLETION-SUBS | Resource update notification includes correct subscription correlation | completion/suggestion fixture+subscriptions listen trace+policy epoch | FUTURE / NOT EXECUTED |
| A05-T108 | COMPLETION-SUBS | Subscription stops after grant revoke or project switch | completion/suggestion fixture+subscriptions listen trace+policy epoch | FUTURE / NOT EXECUTED |
| A05-T109 | COMPLETION-SUBS | Disconnect requires fresh re-list rather than fake replay guarantee | completion/suggestion fixture+subscriptions listen trace+policy epoch | FUTURE / NOT EXECUTED |
| A05-T110 | COMPLETION-SUBS | Source commit triggers update hint only after owner verification | completion/suggestion fixture+subscriptions listen trace+policy epoch | FUTURE / NOT EXECUTED |
| A05-T111 | COMPLETION-SUBS | Absent notifications never imply unchanged source revision | completion/suggestion fixture+subscriptions listen trace+policy epoch | FUTURE / NOT EXECUTED |
| A05-T112 | COMPLETION-SUBS | Legacy host maps features only according to negotiated AI-04 protocol | completion/suggestion fixture+subscriptions listen trace+policy epoch | FUTURE / NOT EXECUTED |
| A05-T113 | E2E-SECURITY-PERF | Official 2026-07-28 MCP resource/template/prompt conformance passes | official conformance+host/OS/version logs+benchmark and threat fixture | FUTURE / NOT EXECUTED |
| A05-T114 | E2E-SECURITY-PERF | Optional 2025-11-25 compatibility passes pinned suite if advertised | official conformance+host/OS/version logs+benchmark and threat fixture | FUTURE / NOT EXECUTED |
| A05-T115 | E2E-SECURITY-PERF | Pinned Codex host browses bounded resources without full repo copy | official conformance+host/OS/version logs+benchmark and threat fixture | FUTURE / NOT EXECUTED |
| A05-T116 | E2E-SECURITY-PERF | Pinned Claude host selects resource and prompt with correct citations | official conformance+host/OS/version logs+benchmark and threat fixture | FUTURE / NOT EXECUTED |
| A05-T117 | E2E-SECURITY-PERF | Rights-equivalent full-repo comparator shows measured context savings | official conformance+host/OS/version logs+benchmark and threat fixture | FUTURE / NOT EXECUTED |
| A05-T118 | E2E-SECURITY-PERF | Labeled ground-truth recall and relevance meet owner-approved thresholds | official conformance+host/OS/version logs+benchmark and threat fixture | FUTURE / NOT EXECUTED |
| A05-T119 | E2E-SECURITY-PERF | Single committed source edit updates context without full unrelated rebuild | official conformance+host/OS/version logs+benchmark and threat fixture | FUTURE / NOT EXECUTED |
| A05-T120 | E2E-SECURITY-PERF | Freshness-required request returns STALE when index lags source | official conformance+host/OS/version logs+benchmark and threat fixture | FUTURE / NOT EXECUTED |
| A05-T121 | E2E-SECURITY-PERF | Concurrent 32 principals isolate project data and cursor scope | official conformance+host/OS/version logs+benchmark and threat fixture | FUTURE / NOT EXECUTED |
| A05-T122 | E2E-SECURITY-PERF | Prompt injection fixture cannot invoke commands or reveal secrets | official conformance+host/OS/version logs+benchmark and threat fixture | FUTURE / NOT EXECUTED |
| A05-T123 | E2E-SECURITY-PERF | URI traversal and SSRF corpus produces zero filesystem/network bypass | official conformance+host/OS/version logs+benchmark and threat fixture | FUTURE / NOT EXECUTED |
| A05-T124 | E2E-SECURITY-PERF | Cross-project exfiltration test yields zero unauthorized owner reads | official conformance+host/OS/version logs+benchmark and threat fixture | FUTURE / NOT EXECUTED |
| A05-T125 | E2E-SECURITY-PERF | UTF-8, Unicode CJK and emoji citations preserve source spans | official conformance+host/OS/version logs+benchmark and threat fixture | FUTURE / NOT EXECUTED |
| A05-T126 | E2E-SECURITY-PERF | Windows/Linux/macOS Apple Silicon target matrix passes when implemented | official conformance+host/OS/version logs+benchmark and threat fixture | FUTURE / NOT EXECUTED |
| A05-T127 | E2E-SECURITY-PERF | Cold/warm p50 p95 p99 and context bytes recorded reproducibly | official conformance+host/OS/version logs+benchmark and threat fixture | FUTURE / NOT EXECUTED |
| A05-T128 | E2E-SECURITY-PERF | Evidence pins Git, source, spec, host, SDK, license and fixture versions | official conformance+host/OS/version logs+benchmark and threat fixture | FUTURE / NOT EXECUTED |

## Mandatory acceptance criteria for any future code release
- 100% of required conformance tests for actually claimed MCP version/transport pass at exact suite SHA; actual Codex/Claude host scenarios pass at exact releases or explicitly report unsupported.
- 100% of relevant public/approved context resources enumerate through stable typed owner IDs and audited exemptions, not self-defined catalog-only denominator.
- No HIGH/CRITICAL cross-project, prompt injection, SSRF, URI traversal, hidden ACL listing, stale grant, unsafe cache or arbitrary owner dispatch defect.
- All 128 scenarios executed and passing, with unsupported optional capability explicitly NOT SUPPORTED, not fake PASS; benchmarks measured against independently labeled fixtures.
- Mainline engine DoD and predecessor approvals remain additional requirements. This planning PR, its CI and its ADR do not authorize coding.

[Architecture](../architecture/ai-05-context-resources-templates.md) · [Contracts](../contracts/ai-05-context-resource-api.md) · [Benchmarks](../research/ai-05-context-benchmark-protocol.md).
