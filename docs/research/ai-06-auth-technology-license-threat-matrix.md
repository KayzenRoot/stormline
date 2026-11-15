# AI-06 — Security Research: MCP Authorization, Policy Technology, Sandboxes and Licenses

**2026-11-15 | P00 RESEARCH ONLY / NOT IMPLEMENTED | research #301 | NLE-P00-WO-002-AI-06 | future code #80 OPEN/BLOCKED | BASE 886f8c8687c4c79a18a3cb3b7e82a26a054eb656.** 61/80 researched baseline, 19 pending, all 80 implementation WOs BLOCKED, zero engine, NLE-D009 license OPEN. Formal dependencies **AI-04 + AI-01 ONLY**; predecessor ADR-0063/ADR-0060 PROPOSED.

## 1. Primary sources and concrete implications
| Source | Evidence | AI-06 implication |
|---|---|---|
| [MCP 2026-07-28 Authorization](https://modelcontextprotocol.io/specification/2026-07-28/basic/authorization) | HTTP MCP resource server with OAuth 2.1 draft, RFC 6750/8414/8707/9728/9207; stdio uses local credential context, not HTTP OAuth protocol | AI-04 transport authentication separate from AI-06 semantic grant; token is not universal project right |
| [MCP security best practices](https://modelcontextprotocol.io/docs/2026-07-28/tutorials/security/security_best_practices) | confused deputy, token passthrough, SSRF, local server hijack, auth mix-up, state handle leakage and scope minimization | require issuer+audience/resource checks, no token forwarding, client/agent identity and grant binding |
| [MCP 2026 release](https://blog.modelcontextprotocol.io/posts/2026-07-28/) | stateless per-request metadata, MRTR, opt-in Tasks and subscriptions | no hidden authenticated session; MRTR is not a consent receipt; task authorization per call |
| [OWASP Agentic Top 10 2026](https://genai.owasp.org/resource/owasp-top-10-for-agentic-applications-for-2026/) | agent goal hijack, tool misuse, privilege abuse, supply-chain, unexpected code execution, memory poisoning, insecure interagent communication, cascading failures, human trust abuse and rogue agents | threat-map positive/negative security tests, not prompt-only filters |
| [Cedar policy engine](https://github.com/cedar-policy/cedar) | Rust typed policy language, explicit principal/action/resource, Apache-2.0 repository license | PDP candidate for fine-grained owner grants; not selected |
| [Open Policy Agent](https://www.openpolicyagent.org/docs) | Rego general purpose policy, structured input and decision queries; repository Apache-2.0 | PDP candidate; local embedding vs service/runtime and determinism require benchmarking |
| [Wasmtime Security](https://docs.wasmtime.dev/security.html) | WASM memory/control flow isolation and host imports capability model | guest WASM containment candidate, not protection for arbitrary native plugins or privileged host |
| [Linux Landlock](https://docs.kernel.org/userspace-api/landlock.html) | unprivileged stackable filesystem/network/IPC restrictions depend kernel ABI | sandbox defense-in-depth; probe actual host support and inherited FD handling |
| [macOS App Sandbox](https://developer.apple.com/documentation/security/app-sandbox/) | entitlements and user-scoped resource access for macOS apps | signed helper/entitlement/bookmark profile; must verify packaging |
| [Windows AppContainer](https://learn.microsoft.com/en-us/windows/win32/secauthz/appcontainer-isolation) | isolated app process token/resource model | candidate restricted helper broker and low-integrity process, target SKU/version proof needed |

All references are **research**, not evidence that Stormline has implemented these controls or that an SDK works on every OS.

## 2. Policy evaluator candidates, unadopted
| Candidate | Licensing note | Strength | Operational gap |
|---|---|---|---|
| **Cedar** | current cedar-policy repository declares Apache-2.0; exact crate tag/transitive licenses and notices to verify | principal/action/resource/entity schema and policy validation, narrow authorization semantics | Rust/C++ FFI/sidecar, performance, entities/unknown attrs behavior, error semantics, migration and packaging |
| **OPA/Rego** | OPA repo Apache-2.0; exact release/transitive SPDX to verify | mature generic policy-as-code, complex structured rules, tooling and profiling | Go/embedded Wasm runtime, cold start, policy complexity, offline availability and decision cache risks |
| **Minimal Stormline typed evaluator** | own code license still NLE-D009 OPEN | small offline footprint, tightly scoped deny-overrides and deterministic decisions | bespoke policy language/security proof and maintenance burden; must not become undisclosed superuser |
| **Static ACL/RBAC baseline** | no new interpreter | simple and transparent | insufficient alone for time/resource/delegation/consent/target/side effects; use benchmark baseline |
| **Casbin or other RBAC/ABAC tool** | exact release/license independently verify | ecosystem models and enforcement helpers | adapter/identity+OS sandbox still required; not a drop-in complete security solution |
| **Remote managed authorization SaaS** | vendor contract and data privacy obligations | policy centralization | out of P00 default, owner forbids paid dependencies and offline unavailability |

**NO selection** until exact tag, policy semantic equivalence, license/SBOM/CVE, incident response support, Windows/Linux/macOS footprint and latency measurements. A textual policy ALLOW is not an owner permission receipt.

## 3. Identity and grant scope matrix
| Layer | Proof source | May authorize |
|---|---|---|
| HTTP client transport | AI-04 OAuth resource-server checks: signature, iss/aud/resource, expiry/scopes, TLS/Origin | request admission to specific MCP server, **not automatically project write** |
| Local stdio transport | OS peer/process provenance, controlled launcher, explicit selected workspace | local channel identity; no administrative grant |
| Human/project owner | authenticated account and canonical project ACL/rights | upper bound on agent grant; not bypassable by subagent |
| Agent instance | Stormline-minted instance ID, parent delegation lineage | scoped operation under attenuated grant, only if human and owner rights permit |
| AI-06 grant/policy | immutable policy version, grant ID and epoch, action/resource/target conditions | ALLOW/DENY/REQUIRE_CONSENT advice to owner PEP, never direct mutation |
| AI-01 command and owner | CommandId/typed schema/target/revision/side-effect/owner ACL/CAS and receipt | actual permissible read/commit/export under full verified context |
| OS sandbox | process/FD/mount/network restrictions | defense against native/guest code bypass; cannot grant semantic ProjectId rights |

## 4. OAuth and confused-deputy risks
Modern MCP remote resource servers must validate authorization server issuer and resource audience. **Do not pass through** incoming bearer tokens to upstream services. A public MCP token's scope is a coarse admission condition and should not encode all fine-grained project authority in uncontrolled host text. Per-tool scope step-up may require HTTP challenge and user-driven authorization flow (AI-04's responsibility). Distinguish a newly issued authorization token from a trusted **Stormline consent receipt** tied to one exact mutation; neither alone substitutes the other.

MCP stdio is not protected by the HTTP OAuth flow; it must have controlled launch, OS identity and workspace selection. Authentication must not rely on human-readable clientInfo or model names. Treat agent-to-agent delegation as an impersonation risk; no inherited ambient cloud credentials.

## 5. OS sandbox candidate comparison, unadopted
| Platform | Candidate primitives | Known limitations / proof |
|---|---|---|
| Windows x64 | AppContainer/restricted token, Job Objects, ACLs, broker handle allowlist, controlled child process | per-SKU policy/CI and filesystem/network checks; DLL/plugins running inside privileged editor defeat helper containment |
| Linux x64 | Landlock, seccomp BPF, namespaces, cgroups, rlimits, no-new-privileges, close inherited FDs | kernel/LSM ABI varies; deny unavailable primitive or use proven alternative, never silently elevate |
| macOS Apple Silicon | App Sandbox entitlements, sandboxed helper/XPC, security-scoped bookmarks, hardened runtime | entitlement distribution/signing, process isolation and scope prove on real macOS target |
| Cross-platform guest WASM | WASI/Wasmtime capability preopens, no ambient network, fuel/epoch budgets | only protects guest imports/linear memory, not arbitrary native host code; exact runtime/library licenses and OS tests |
| Container or VM | namespaces/container policy, virtualized isolation | deployment and availability burden; no guarantees by mere container label |

## 6. Threat control table / OWASP Agentic classification
| Risk ID | Example | Control | Future independent oracle |
|---|---|---|---|
| ASI01 goal hijack | injected scene note asks agent to export secrets | data untrusted, owner PEP, no arbitrary egress | no export/net and denied trace |
| ASI02 tool misuse | authorized inspection tricked into delete | side-effect policy and typed CommandId | no owner delete receipt/diff |
| ASI03 identity privilege | child agent steals parent approval | scoped delegation/nonce/epoch | invalid chain denied |
| ASI04 supply chain | malicious MCP tool manifest/plugin | signed/trusted tool registry, least privilege, SBOM | hash mismatch/no tool dispatch |
| ASI05 unexpected code execution | prompt produces shell command | no generic exec, OS sandbox and allowlist | no subprocess/external process |
| ASI06 memory/context poisoning | fake "admin grant" in resource | no policy from model text, source labels | owner grant unchanged |
| ASI07 insecure interagent | forged handoff with another project ID | authenticated agent lineage, no ambient token | cross-project denied |
| ASI08 cascading failure | thousands of recursive agent calls | quotas, budgets, monotonic attenuation | bounded owner calls and no privilege increase |
| ASI09 human trust | misleading confirmation UI hides export | exact plan diff/target, trusted consent binding | changed plan invalidates receipt |
| ASI10 rogue agents | agent persists after revoke | revocation epoch plus per-request owner check | denied all later calls and tasks |

## 7. License, privacy and open decisions
- Engine source license **NLE-D009 OPEN**; public GitHub repo is not open-source approval. No runtime library or policy interpreter installed or selected.
- Cedar and OPA repo roots declare Apache-2.0; Wasmtime repository uses Apache-2.0 with LLVM exception/MIT dual licensing in typical distributions, **verify exact tag and file-level license**. System APIs have OS SDK redistribution constraints; security fixtures and generated source examples may have separate rights.
- If embedding policy code or using Wasmtime, capture exact package tags, transitive SPDX/SBOM, notices, CVEs, supported target builds, signed artifacts and deterministic repeatability. No promise of zero vulnerabilities.
- Audit logs can reveal project filenames, agent behavior and personal data; use least disclosure, retention/legal review, redacted actor/project pseudonyms and access controls. Append-only/tamper-evident is a design hypothesis, not verified cryptographic guarantee.
- Policy AST, consent UI, credential broker, OS sandbox architecture, key provider, actor identity derivation, risk classification, workspace ACL resolution and performance thresholds require future approved decisions.

## 8. Sources and next evidence
Official [MCP authorization](https://modelcontextprotocol.io/specification/2026-07-28/basic/authorization), [MCP security](https://modelcontextprotocol.io/docs/2026-07-28/tutorials/security/security_best_practices), [OWASP Agentic 2026](https://genai.owasp.org/resource/owasp-top-10-for-agentic-applications-for-2026/), [Cedar](https://github.com/cedar-policy/cedar), [OPA](https://www.openpolicyagent.org/docs), [Wasmtime](https://docs.wasmtime.dev/security.html), [Linux Landlock](https://docs.kernel.org/userspace-api/landlock.html), [macOS App Sandbox](https://developer.apple.com/documentation/security/app-sandbox/), [Windows AppContainer](https://learn.microsoft.com/en-us/windows/win32/secauthz/appcontainer-isolation). Future code must pin official releases and reproduce negative oracles; **128 tests are future only, NOT EXECUTED**.

[Architecture](../architecture/ai-06-agent-security-authorization.md) · [ADR-0065](../adr/0065-ai-06-agent-grant-consent-policy.md) · [API contracts](../contracts/ai-06-authorization-api.md).
