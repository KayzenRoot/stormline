# AI-03 — Schema, Registry, Versioning, Licensing, MCP & Threat Research

**2026-11-15 | P00 RESEARCH ONLY, NOT IMPLEMENTED | [research #289](https://github.com/KayzenRoot/stormline/issues/289) | NLE-P00-WO-002-AI-03 | [future code #77](https://github.com/KayzenRoot/stormline/issues/77) OPEN/BLOCKED | BASE `1db368aa555f7a8eb2fa1a1eb3a38744a23ef6bb`.** 58/80 researched at baseline, 22 pending, zero engine, all 80 implementation packets BLOCKED. Formal dependency **AI-01 ONLY**; ADR-0060 PROPOSED and code #75 OPEN/BLOCKED. NLE-D009 engine license OPEN.

## 1. Evidence sources and candidate comparison (nothing installed)
| Candidate / primary source | License / evidence | Strength | Caveat / disposition |
|---|---|---|---|
| [JSON Schema Draft 2020-12](https://json-schema.org/draft/2020-12/) | Published specification / terms distinct from validator libraries | `$defs`, `$dynamicRef`, `prefixItems`, `unevaluatedProperties`, vocabularies, validation outputs | **Preferred dialect PROPOSED** for portable transport; actual engine use requires approved ADR |
| [jsoncons C++](https://github.com/danielaparker/jsoncons) + [schema support](https://github.com/danielaparker/jsoncons/blob/master/doc/ref/jsonschema/jsonschema.md) | Boost Software License 1.0 per project | C++, validation for draft 4/6/7/2019-09/2020-12, candidate for bounded compiled schemas | Verify exact tag, keyword/test coverage, backtracking, $ref resolver and audit; not chosen or linked |
| [nlohmann/json-schema-validator](https://github.com/pboettch/json-schema-validator) | Repository license needs version-specific verification before adoption | C++ and readable errors, Draft 7 | **NOT 2020-12 equivalent**; cannot claim full coverage for our preferred dialect |
| [JSON Schema Test Suite](https://github.com/json-schema-org/JSON-Schema-Test-Suite) | License and exact suite pin to inspect before vendoring | Language-agnostic official compliance vectors, negative and optional cases | Need vendor hash/test harness and additional adversarial tests |
| [MCP tools specification 2026-07-28](https://github.com/modelcontextprotocol/modelcontextprotocol/blob/main/docs/specification/2026-07-28/server/tools.mdx) | Protocol specification; SDKs have separate licenses | Tool inputSchema root object, outputSchema any JSON; scoped tool lists and deterministic order | MCP adapter is AI-04 future; hosts may negotiate other versions, tool annotations never auth |
| [OpenAPI 3.1.1](https://spec.openapis.org/oas/v3.1.1.html) and [OpenAPI releases](https://spec.openapis.org/oas/) | Published standard, tooling own licensing | HTTP introspection, JSON Schema-based OAS dialect | HTTP-only/Schema Object vocab not a Stormline owner command; optional generated projection |
| [RFC 8785 JCS](https://www.rfc-editor.org/rfc/rfc8785.html) | IETF informational standard | Deterministic JSON canonical byte form for schema digest candidate | Requires I-JSON, unique keys, Unicode validity and IEEE-754 numbers, so **NOT** raw source semantic digest; DATA-04 owner hash separate |
| [Semantic Versioning 2.0.0](https://semver.org/) | Published versioning convention | Major/minor/patch contract compatibility vocabulary | Schema syntactic compatibility != permission/error/side-effect semantic compatibility |
| [OWASP API Security Top 10](https://owasp.org/API-Security/editions/2023/en/0x11-t10/) | Public guidance | Authorization object scope, resource exhaustion, configuration and discovery surface | Security guidance, not a substitute for testable owner gate |

**License gate:** no engine license yet selected (NLE-D009 OPEN), no library installed or shipped; dependency SBOM/license version, transitive notices, file-level audit and C++/native/Web compatibility must be done before adoption. Specification openness does not imply every validator's license/compatibility. No paid SaaS, proprietary hosted schema resolver or mandatory CodeRabbit.

## 2. JSON Schema conformance traps
- Draft 2020-12 `$dynamicRef` and `$dynamicAnchor` resolution differs from simple preprocessor pointer replacement; test cycles with depth/CPU limits and use allowlisted local registry references, never network fetch.
- `format` defaults to annotation unless format-assertion vocabulary explicitly declared/enforced. Do not assume email/URI validation or security semantics simply from format tags.
- `unevaluatedProperties` depends on evaluation results of applicator/composition; naive additionalProperties substitute can pass unsafe fields.
- `oneOf` must enforce exactly one branch; split structural presence and typing carefully; schema validation cannot enforce dynamic project rights or owner CAS.
- Unicode regex semantics and parser duplicate JSON keys differ across libraries; reject invalid UTF-8, ambiguously duplicated keys, depth/length excess and unbounded regex.
- JSON numbers >2^53 risk losing identity; handle exact IDs as strings; JCS numbers have I-JSON IEEE-754 rules and do NOT provide universal semantic equality.
- Payload default annotations are not implicit mutations; no schema-driven default injection or unknown-key deletion without owner-approved migration.

## 3. Threat and policy matrix
| Threat | Proposed enforcement | Proof scenario |
|---|---|---|
| Host SSRF / remote `$ref` | Offline URI allowlist, no HTTP fetch in compilation | Redirect, file://, localhost, encoded traversal rejected |
| Recursive schema/billion-laughs/regex DoS | Compile/validation quotas by depth, nodes, regex complexity, deadline, memory | Max-depth and adversarial schema fuzz |
| Command/owner spoof or plugin shadowing | Unique qualified CommandId, owner-provenance/signature check, reject overlap | Duplicate/overwrite attempt fails before publish |
| Overbroad agent tools | Project+actor grant, target and feature filtered list; owner revalidation | No exposure, no unauthorized invoke |
| Cursor/ETag/aggregate privacy | Actor/policy epoch scoped signed/opaque cursor; redacted counts/schema | Cross-project reuse yields zero leak |
| Tool annotation confusion | Hints not authority; independent side-effect and grant registry | False readOnlyHint still asks consent |
| Breaking schema auto-upgrade | Compatibility classifier, explicit major and client negotiation | Old pinned consumer unchanged or unsupported |
| Metadata prompt injection | Safe description sanitation, no AI instructions as policy, bounded outputs | Malicious descriptions inert |
| Generation crash / stale policy | Atomic staging + prior-good, active revocation invalidates cache | Crash at each publication phase |

## 4. Integration notes / official specs
MCP 2026-07-28 descriptions/annotations expose potentially adversarial content. Tools/list set may vary by authorization per request but must not change per-connection; deterministic ordering improves client caching. No claim selected hosts implement that protocol version. Version negotiation/conformance for Codex/Claude and legacy revisions is AI-04 future. OpenAPI export may describe HTTP but cannot convey full scene revision/consent semantics without extensions. Registry documentation is a derived view, never permission.

## 5. Decision criteria before implementation
A/B compile correct mandatory JSON Schema 2020-12 suite (pin hash), compare jsoncons vs second independent implementation/reference; positive/negative payload conformance, fuzz schema/parser/refs; license/legal gate; C++20 build on Win/Linux/macOS Apple Silicon, headless offline and Web restrictions; deterministic digests across toolchains; time/RSS and discovery budgets; CI security. **No A/B was executed**. Candidate libraries are recommendations to investigate, not selected dependencies.
