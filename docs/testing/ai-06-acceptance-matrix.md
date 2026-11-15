# AI-06 — Exactly 128 FUTURE Security Acceptance Tests (A06-T001..A06-T128)

**2026-11-15 | P00 RESEARCH ONLY / NOT IMPLEMENTED | research #301 | NLE-P00-WO-002-AI-06 | future code #80 OPEN/BLOCKED | BASE 886f8c8687c4c79a18a3cb3b7e82a26a054eb656.** Formal deps AI-04 + AI-01 ONLY; 61/80 research at baseline, all 80 future code WOs BLOCKED; ADR-0065 PROPOSED; NLE-D009 OPEN.

**128 UNIQUE FUTURE / NOT EXECUTED scenarios, zero executed, zero PASS, zero FAIL.** Eight groups of sixteen. The tests are *specifications only*, not code or proof of authorization/security compliance.

## Independent future test oracle
1. Fix Git/SBOM/policy/schema versions, MCP 2026-07-28 or explicitly proven legacy version, selected host release, OS/kernel/sandbox ABI, source revisions and synthetic ProjectIds/AgentInstanceIds. Never infer host support from generic SDK.
2. Use rights-cleared synthetic projects with **unrelated outside-project sentinels**, hidden resources, symlinks, junctions, Unicode/case aliases, a separate human principal, two client instances and multi-agent delegation tree.
3. For each deny scenario assert **zero AI-01 owner commit, zero outside-project filesystem state change, zero unauthorized OS open/network request and zero leaked resource identity/secret**. A policy DENY response alone is insufficient.
4. For valid operations independently reopen canonical source, compare owner receipt/source revision and ensure correct audit trace. No false positive permit in absence of owner.
5. Consent tests use real trusted UI security origin/fixture and one-use owner-bound approval receipt, never model chat or MCP MRTR string.
6. Sandbox tests run on the actual Windows/Linux/macOS feature matrix, with explicit "unsupported" when mandatory isolation absent; do not call a skipped path PASS.
7. Every future test has a unique ID and frozen fixture/expected result. Absent implementation or owner API => NOT EXECUTED. Documentation CI does not run these tests.

## Eight groups of sixteen
| Group | IDs | Count | Security focus |
|---|---|---:|---|
| IDENTITY-TRANSPORT | A06-T001..016 | 16 | MCP OAuth resource auth, stdio peer identity, stateless request |
| GRANTS-POLICY | A06-T017..032 | 16 | deny overrides, command/ProjectId scope and side effects |
| DELEGATION-REVOKE | A06-T033..048 | 16 | attenuation, child lineage, expiry and policy epoch |
| CONSENT-PLANS | A06-T049..064 | 16 | trusted UI, plan digest/revision and single-use approval |
| OWNER-PATH-TOCTOU | A06-T065..080 | 16 | canonical source owner and OS filesystem scope |
| SANDBOX-EXECUTION | A06-T081..096 | 16 | Landlock/AppContainer/App Sandbox/WASM guard |
| AUDIT-SECRETS | A06-T097..112 | 16 | redacted audit, keys, integrity and recovery |
| ENDTOEND-ADVERSARIAL | A06-T113..128 | 16 | OWASP/host/conformance/latency/OS isolation |

## Complete matrix
| Test ID | Group | Scenario and assertion | Independent evidence required | Status |
|---|---|---|---|---|
| A06-T001 | IDENTITY-TRANSPORT | Modern MCP 2026 request verified per-call principal without protocol session | AI-04 authenticated trace + synthetic issuer token fixture + no owner dispatch | FUTURE / NOT EXECUTED |
| A06-T002 | IDENTITY-TRANSPORT | HTTP resource token valid issuer signature audience resource and expiry is admitted | AI-04 authenticated trace + synthetic issuer token fixture + no owner dispatch | FUTURE / NOT EXECUTED |
| A06-T003 | IDENTITY-TRANSPORT | HTTP token with wrong audience resource rejected before AI-01 owner dispatch | AI-04 authenticated trace + synthetic issuer token fixture + no owner dispatch | FUTURE / NOT EXECUTED |
| A06-T004 | IDENTITY-TRANSPORT | HTTP token issued by untrusted issuer rejected before policy evaluation | AI-04 authenticated trace + synthetic issuer token fixture + no owner dispatch | FUTURE / NOT EXECUTED |
| A06-T005 | IDENTITY-TRANSPORT | Expired revoked or signature-invalid token rejected without fallback | AI-04 authenticated trace + synthetic issuer token fixture + no owner dispatch | FUTURE / NOT EXECUTED |
| A06-T006 | IDENTITY-TRANSPORT | Insufficient HTTP scope triggers correct 403 scope challenge and no owner dispatch | AI-04 authenticated trace + synthetic issuer token fixture + no owner dispatch | FUTURE / NOT EXECUTED |
| A06-T007 | IDENTITY-TRANSPORT | Missing token triggers correct 401 protected-resource metadata challenge | AI-04 authenticated trace + synthetic issuer token fixture + no owner dispatch | FUTURE / NOT EXECUTED |
| A06-T008 | IDENTITY-TRANSPORT | OAuth token passthrough to downstream engine or third-party API is impossible | AI-04 authenticated trace + synthetic issuer token fixture + no owner dispatch | FUTURE / NOT EXECUTED |
| A06-T009 | IDENTITY-TRANSPORT | Local stdio OS peer identity validated independently of clientInfo | AI-04 authenticated trace + synthetic issuer token fixture + no owner dispatch | FUTURE / NOT EXECUTED |
| A06-T010 | IDENTITY-TRANSPORT | Unknown stdio launcher project selection rejects read and write | AI-04 authenticated trace + synthetic issuer token fixture + no owner dispatch | FUTURE / NOT EXECUTED |
| A06-T011 | IDENTITY-TRANSPORT | Forged clientInfo agent display name never becomes principal | AI-04 authenticated trace + synthetic issuer token fixture + no owner dispatch | FUTURE / NOT EXECUTED |
| A06-T012 | IDENTITY-TRANSPORT | Conflicting MCP header body metadata rejects routing spoof attempts | AI-04 authenticated trace + synthetic issuer token fixture + no owner dispatch | FUTURE / NOT EXECUTED |
| A06-T013 | IDENTITY-TRANSPORT | 2025 legacy handshake cannot carry grants into modern stateless request | AI-04 authenticated trace + synthetic issuer token fixture + no owner dispatch | FUTURE / NOT EXECUTED |
| A06-T014 | IDENTITY-TRANSPORT | Different clients sharing human account receive independent AgentInstanceIds | AI-04 authenticated trace + synthetic issuer token fixture + no owner dispatch | FUTURE / NOT EXECUTED |
| A06-T015 | IDENTITY-TRANSPORT | Client ID registration issuer mix-up cannot exchange stored credentials | AI-04 authenticated trace + synthetic issuer token fixture + no owner dispatch | FUTURE / NOT EXECUTED |
| A06-T016 | IDENTITY-TRANSPORT | Cross-tenant remote request reauthenticates on every request and task poll | AI-04 authenticated trace + synthetic issuer token fixture + no owner dispatch | FUTURE / NOT EXECUTED |
| A06-T017 | GRANTS-POLICY | Without grant effective capability intersection returns DENY by default | policy fixture + independent permissions oracle + AI-01 owner receipt | FUTURE / NOT EXECUTED |
| A06-T018 | GRANTS-POLICY | Explicit deny rule overrides otherwise matching broad allow | policy fixture + independent permissions oracle + AI-01 owner receipt | FUTURE / NOT EXECUTED |
| A06-T019 | GRANTS-POLICY | Wrong ProjectId grant refuses otherwise valid CommandId | policy fixture + independent permissions oracle + AI-01 owner receipt | FUTURE / NOT EXECUTED |
| A06-T020 | GRANTS-POLICY | Wrong CommandId major version rejects even with broad resource scope | policy fixture + independent permissions oracle + AI-01 owner receipt | FUTURE / NOT EXECUTED |
| A06-T021 | GRANTS-POLICY | Wrong target platform or export destination is rejected | policy fixture + independent permissions oracle + AI-01 owner receipt | FUTURE / NOT EXECUTED |
| A06-T022 | GRANTS-POLICY | READ grant cannot invoke PREVIEW with side effects or MUTATE | policy fixture + independent permissions oracle + AI-01 owner receipt | FUTURE / NOT EXECUTED |
| A06-T023 | GRANTS-POLICY | PREVIEW grant cannot cause canonical project source mutation | policy fixture + independent permissions oracle + AI-01 owner receipt | FUTURE / NOT EXECUTED |
| A06-T024 | GRANTS-POLICY | Scoped MUTATE cannot delete or export unrelated resources | policy fixture + independent permissions oracle + AI-01 owner receipt | FUTURE / NOT EXECUTED |
| A06-T025 | GRANTS-POLICY | Grant resource kind field restrictions redact prohibited source fields | policy fixture + independent permissions oracle + AI-01 owner receipt | FUTURE / NOT EXECUTED |
| A06-T026 | GRANTS-POLICY | Grant with elapsed expiry is refused at owner commit | policy fixture + independent permissions oracle + AI-01 owner receipt | FUTURE / NOT EXECUTED |
| A06-T027 | GRANTS-POLICY | Invocation count and resource byte budget cannot be exceeded | policy fixture + independent permissions oracle + AI-01 owner receipt | FUTURE / NOT EXECUTED |
| A06-T028 | GRANTS-POLICY | Policy bundle invalid schema or signature produces fail-closed DENY | policy fixture + independent permissions oracle + AI-01 owner receipt | FUTURE / NOT EXECUTED |
| A06-T029 | GRANTS-POLICY | Policy timeout does not activate allow-all fallback | policy fixture + independent permissions oracle + AI-01 owner receipt | FUTURE / NOT EXECUTED |
| A06-T030 | GRANTS-POLICY | Policy generation and rule ordering are deterministic for fixed input | policy fixture + independent permissions oracle + AI-01 owner receipt | FUTURE / NOT EXECUTED |
| A06-T031 | GRANTS-POLICY | Hidden capability name and count are not exposed to unauthorized actor | policy fixture + independent permissions oracle + AI-01 owner receipt | FUTURE / NOT EXECUTED |
| A06-T032 | GRANTS-POLICY | Local manual Editor command uses same owner source ACL as MCP | policy fixture + independent permissions oracle + AI-01 owner receipt | FUTURE / NOT EXECUTED |
| A06-T033 | DELEGATION-REVOKE | Child grant action set is subset of parent and human effective rights | grant chain digests + epoch journal + owner recheck after revocation | FUTURE / NOT EXECUTED |
| A06-T034 | DELEGATION-REVOKE | Child project scope cannot expand beyond parent ProjectId | grant chain digests + epoch journal + owner recheck after revocation | FUTURE / NOT EXECUTED |
| A06-T035 | DELEGATION-REVOKE | Child TTL cannot exceed parent expiry or revocation deadline | grant chain digests + epoch journal + owner recheck after revocation | FUTURE / NOT EXECUTED |
| A06-T036 | DELEGATION-REVOKE | Max delegation depth is enforced even across chained subagents | grant chain digests + epoch journal + owner recheck after revocation | FUTURE / NOT EXECUTED |
| A06-T037 | DELEGATION-REVOKE | Self-delegation to higher privilege is rejected | grant chain digests + epoch journal + owner recheck after revocation | FUTURE / NOT EXECUTED |
| A06-T038 | DELEGATION-REVOKE | Forged parent GrantId or AgentInstanceId denies creation | grant chain digests + epoch journal + owner recheck after revocation | FUTURE / NOT EXECUTED |
| A06-T039 | DELEGATION-REVOKE | Parent revocation cascades to every descendant child grant | grant chain digests + epoch journal + owner recheck after revocation | FUTURE / NOT EXECUTED |
| A06-T040 | DELEGATION-REVOKE | Child revocation leaves unrelated siblings scoped and intact | grant chain digests + epoch journal + owner recheck after revocation | FUTURE / NOT EXECUTED |
| A06-T041 | DELEGATION-REVOKE | Policy epoch rotates monotonically after revocation and persists across restart | grant chain digests + epoch journal + owner recheck after revocation | FUTURE / NOT EXECUTED |
| A06-T042 | DELEGATION-REVOKE | Policy epoch change invalidates resource list and completion cursors | grant chain digests + epoch journal + owner recheck after revocation | FUTURE / NOT EXECUTED |
| A06-T043 | DELEGATION-REVOKE | Policy epoch change invalidates tasks and subscriptions at next request | grant chain digests + epoch journal + owner recheck after revocation | FUTURE / NOT EXECUTED |
| A06-T044 | DELEGATION-REVOKE | In-flight mutation checks revocation immediately before owner commit | grant chain digests + epoch journal + owner recheck after revocation | FUTURE / NOT EXECUTED |
| A06-T045 | DELEGATION-REVOKE | Delegated action audit preserves origin actor and complete verified chain | grant chain digests + epoch journal + owner recheck after revocation | FUTURE / NOT EXECUTED |
| A06-T046 | DELEGATION-REVOKE | Agent-to-agent text message cannot transfer ambient bearer privilege | grant chain digests + epoch journal + owner recheck after revocation | FUTURE / NOT EXECUTED |
| A06-T047 | DELEGATION-REVOKE | Revoked grant cannot be restored using previously cached ALLOW decision | grant chain digests + epoch journal + owner recheck after revocation | FUTURE / NOT EXECUTED |
| A06-T048 | DELEGATION-REVOKE | Concurrent revoke and grant attenuation cannot revive rejected rights | grant chain digests + epoch journal + owner recheck after revocation | FUTURE / NOT EXECUTED |
| A06-T049 | CONSENT-PLANS | High-risk delete demands owner-generated preview and trusted UI approval | trusted UI record + owner plan digest/revision + single-use journal + zero mutation | FUTURE / NOT EXECUTED |
| A06-T050 | CONSENT-PLANS | Export to external destination requires explicit destination-bound consent | trusted UI record + owner plan digest/revision + single-use journal + zero mutation | FUTURE / NOT EXECUTED |
| A06-T051 | CONSENT-PLANS | MRTR inputResponses text does not satisfy trusted approval receipt | trusted UI record + owner plan digest/revision + single-use journal + zero mutation | FUTURE / NOT EXECUTED |
| A06-T052 | CONSENT-PLANS | Model-provided yes or instruction cannot sign or issue human approval | trusted UI record + owner plan digest/revision + single-use journal + zero mutation | FUTURE / NOT EXECUTED |
| A06-T053 | CONSENT-PLANS | Approval receipt binds normalized args digest and exact CommandId | trusted UI record + owner plan digest/revision + single-use journal + zero mutation | FUTURE / NOT EXECUTED |
| A06-T054 | CONSENT-PLANS | Changed resource scope invalidates previously issued consent | trusted UI record + owner plan digest/revision + single-use journal + zero mutation | FUTURE / NOT EXECUTED |
| A06-T055 | CONSENT-PLANS | Changed source revision invalidates plan-bound consent | trusted UI record + owner plan digest/revision + single-use journal + zero mutation | FUTURE / NOT EXECUTED |
| A06-T056 | CONSENT-PLANS | Changed export target or destination invalidates consent | trusted UI record + owner plan digest/revision + single-use journal + zero mutation | FUTURE / NOT EXECUTED |
| A06-T057 | CONSENT-PLANS | Changed actor agent or ProjectId invalidates consent | trusted UI record + owner plan digest/revision + single-use journal + zero mutation | FUTURE / NOT EXECUTED |
| A06-T058 | CONSENT-PLANS | Expired consent nonce cannot be consumed | trusted UI record + owner plan digest/revision + single-use journal + zero mutation | FUTURE / NOT EXECUTED |
| A06-T059 | CONSENT-PLANS | Replayed single-use approval cannot commit twice | trusted UI record + owner plan digest/revision + single-use journal + zero mutation | FUTURE / NOT EXECUTED |
| A06-T060 | CONSENT-PLANS | Declined consent yields zero owner commit or export | trusted UI record + owner plan digest/revision + single-use journal + zero mutation | FUTURE / NOT EXECUTED |
| A06-T061 | CONSENT-PLANS | Owner plan must display affected IDs and truthful side-effect/risk class | trusted UI record + owner plan digest/revision + single-use journal + zero mutation | FUTURE / NOT EXECUTED |
| A06-T062 | CONSENT-PLANS | Hidden side effects require stricter review not annotation readOnlyHint | trusted UI record + owner plan digest/revision + single-use journal + zero mutation | FUTURE / NOT EXECUTED |
| A06-T063 | CONSENT-PLANS | Approval cannot override explicit owner ACL denial | trusted UI record + owner plan digest/revision + single-use journal + zero mutation | FUTURE / NOT EXECUTED |
| A06-T064 | CONSENT-PLANS | Cancelled approval or policy epoch change prevents later owner commit | trusted UI record + owner plan digest/revision + single-use journal + zero mutation | FUTURE / NOT EXECUTED |
| A06-T065 | OWNER-PATH-TOCTOU | Canonical ProjectId owner enforces no write outside selected workspace | source owner state hash + filesystem sentinel diff + path race trace | FUTURE / NOT EXECUTED |
| A06-T066 | OWNER-PATH-TOCTOU | Relative parent traversal cannot escape owner-approved project root | source owner state hash + filesystem sentinel diff + path race trace | FUTURE / NOT EXECUTED |
| A06-T067 | OWNER-PATH-TOCTOU | Symlink/junction swap between check and open is rejected | source owner state hash + filesystem sentinel diff + path race trace | FUTURE / NOT EXECUTED |
| A06-T068 | OWNER-PATH-TOCTOU | Case-fold or Unicode equivalent path cannot bypass scope boundary | source owner state hash + filesystem sentinel diff + path race trace | FUTURE / NOT EXECUTED |
| A06-T069 | OWNER-PATH-TOCTOU | UNC or network mounted path cannot bypass project allowlist | source owner state hash + filesystem sentinel diff + path race trace | FUTURE / NOT EXECUTED |
| A06-T070 | OWNER-PATH-TOCTOU | Hardlinked file outside owner scope is not silently mutated | source owner state hash + filesystem sentinel diff + path race trace | FUTURE / NOT EXECUTED |
| A06-T071 | OWNER-PATH-TOCTOU | Directory rename between preview and commit invalidates stale source path | source owner state hash + filesystem sentinel diff + path race trace | FUTURE / NOT EXECUTED |
| A06-T072 | OWNER-PATH-TOCTOU | Direct raw filesystem tool route is absent from public agent capability set | source owner state hash + filesystem sentinel diff + path race trace | FUTURE / NOT EXECUTED |
| A06-T073 | OWNER-PATH-TOCTOU | Owner rechecks source revision and preconditions at actual commit | source owner state hash + filesystem sentinel diff + path race trace | FUTURE / NOT EXECUTED |
| A06-T074 | OWNER-PATH-TOCTOU | Owner receipt independently proves zero outside-project file change | source owner state hash + filesystem sentinel diff + path race trace | FUTURE / NOT EXECUTED |
| A06-T075 | OWNER-PATH-TOCTOU | Index or resource metadata cache cannot authorize source mutation | source owner state hash + filesystem sentinel diff + path race trace | FUTURE / NOT EXECUTED |
| A06-T076 | OWNER-PATH-TOCTOU | Policy ALLOW without owner availability returns UNAVAILABLE not commit | source owner state hash + filesystem sentinel diff + path race trace | FUTURE / NOT EXECUTED |
| A06-T077 | OWNER-PATH-TOCTOU | Owner idempotency key forbids double mutation after retry | source owner state hash + filesystem sentinel diff + path race trace | FUTURE / NOT EXECUTED |
| A06-T078 | OWNER-PATH-TOCTOU | Cross-workspace project switch mid-transaction rejects stale request | source owner state hash + filesystem sentinel diff + path race trace | FUTURE / NOT EXECUTED |
| A06-T079 | OWNER-PATH-TOCTOU | Unsupported owner target does not fall back to host shell command | source owner state hash + filesystem sentinel diff + path race trace | FUTURE / NOT EXECUTED |
| A06-T080 | OWNER-PATH-TOCTOU | Delete or export cancellation reports actual owner commit stage honestly | source owner state hash + filesystem sentinel diff + path race trace | FUTURE / NOT EXECUTED |
| A06-T081 | SANDBOX-EXECUTION | Linux helper with Landlock denies unauthorized filesystem read | OS version + process sandbox policy + syscall/FD/network evidence | FUTURE / NOT EXECUTED |
| A06-T082 | SANDBOX-EXECUTION | Linux helper denies unauthorized filesystem write and file descriptor escape | OS version + process sandbox policy + syscall/FD/network evidence | FUTURE / NOT EXECUTED |
| A06-T083 | SANDBOX-EXECUTION | Linux seccomp profile blocks undeclared process and syscall capabilities | OS version + process sandbox policy + syscall/FD/network evidence | FUTURE / NOT EXECUTED |
| A06-T084 | SANDBOX-EXECUTION | Linux namespaces and network egress rules block unauthorized external connection | OS version + process sandbox policy + syscall/FD/network evidence | FUTURE / NOT EXECUTED |
| A06-T085 | SANDBOX-EXECUTION | Linux unavailable mandatory sandbox ABI prevents untrusted executable launch | OS version + process sandbox policy + syscall/FD/network evidence | FUTURE / NOT EXECUTED |
| A06-T086 | SANDBOX-EXECUTION | Windows restricted token/AppContainer helper cannot read foreign project | OS version + process sandbox policy + syscall/FD/network evidence | FUTURE / NOT EXECUTED |
| A06-T087 | SANDBOX-EXECUTION | Windows Job Object constraints terminate resource quota overrun safely | OS version + process sandbox policy + syscall/FD/network evidence | FUTURE / NOT EXECUTED |
| A06-T088 | SANDBOX-EXECUTION | Windows UNC/junction and alternate data stream escape corpus is denied | OS version + process sandbox policy + syscall/FD/network evidence | FUTURE / NOT EXECUTED |
| A06-T089 | SANDBOX-EXECUTION | macOS App Sandbox helper restricts files not granted by user scope | OS version + process sandbox policy + syscall/FD/network evidence | FUTURE / NOT EXECUTED |
| A06-T090 | SANDBOX-EXECUTION | macOS security-scoped bookmark expired or revoked prevents later file access | OS version + process sandbox policy + syscall/FD/network evidence | FUTURE / NOT EXECUTED |
| A06-T091 | SANDBOX-EXECUTION | macOS signed helper cannot inherit editor ambient privileged handles | OS version + process sandbox policy + syscall/FD/network evidence | FUTURE / NOT EXECUTED |
| A06-T092 | SANDBOX-EXECUTION | WASM WASI preopen scope cannot escape mapped guest directories | OS version + process sandbox policy + syscall/FD/network evidence | FUTURE / NOT EXECUTED |
| A06-T093 | SANDBOX-EXECUTION | WASM guest import table cannot invoke undeclared shell or network host API | OS version + process sandbox policy + syscall/FD/network evidence | FUTURE / NOT EXECUTED |
| A06-T094 | SANDBOX-EXECUTION | Native plugin cannot claim protection merely because WASM path is sandboxed | OS version + process sandbox policy + syscall/FD/network evidence | FUTURE / NOT EXECUTED |
| A06-T095 | SANDBOX-EXECUTION | Runtime sandbox teardown cleans inherited handles and credentials | OS version + process sandbox policy + syscall/FD/network evidence | FUTURE / NOT EXECUTED |
| A06-T096 | SANDBOX-EXECUTION | Across Windows Linux macOS missing containment fails closed rather than unsandboxed fallback | OS version + process sandbox policy + syscall/FD/network evidence | FUTURE / NOT EXECUTED |
| A06-T097 | AUDIT-SECRETS | Grant issue and revoke decisions append redacted audit events | redacted append log + integrity chain + secret scan + crash recovery | FUTURE / NOT EXECUTED |
| A06-T098 | AUDIT-SECRETS | Denied owner command emits reason-class audit without secret arguments | redacted append log + integrity chain + secret scan + crash recovery | FUTURE / NOT EXECUTED |
| A06-T099 | AUDIT-SECRETS | Audit correlates verified AI-04 trace AI-06 decision and AI-01 receipt | redacted append log + integrity chain + secret scan + crash recovery | FUTURE / NOT EXECUTED |
| A06-T100 | AUDIT-SECRETS | Bearer tokens refresh tokens private keys never appear in audit or MCP replies | redacted append log + integrity chain + secret scan + crash recovery | FUTURE / NOT EXECUTED |
| A06-T101 | AUDIT-SECRETS | Agent identity labels not user secrets are pseudonymized by approved policy | redacted append log + integrity chain + secret scan + crash recovery | FUTURE / NOT EXECUTED |
| A06-T102 | AUDIT-SECRETS | Untrusted document prompt injection cannot alter policy bundle or audit reason | redacted append log + integrity chain + secret scan + crash recovery | FUTURE / NOT EXECUTED |
| A06-T103 | AUDIT-SECRETS | Audit monotonic sequence detects missing event and duplicate receipt | redacted append log + integrity chain + secret scan + crash recovery | FUTURE / NOT EXECUTED |
| A06-T104 | AUDIT-SECRETS | Audit chain digest verification detects altered historical event | redacted append log + integrity chain + secret scan + crash recovery | FUTURE / NOT EXECUTED |
| A06-T105 | AUDIT-SECRETS | Audit backend failure uses configured fail-closed policy for high-risk operation | redacted append log + integrity chain + secret scan + crash recovery | FUTURE / NOT EXECUTED |
| A06-T106 | AUDIT-SECRETS | Log quota backpressure does not silently drop required high-risk approval record | redacted append log + integrity chain + secret scan + crash recovery | FUTURE / NOT EXECUTED |
| A06-T107 | AUDIT-SECRETS | Key rotation invalidates stale approval signature without losing proof | redacted append log + integrity chain + secret scan + crash recovery | FUTURE / NOT EXECUTED |
| A06-T108 | AUDIT-SECRETS | Revocation record remains observable after simulated crash and restart | redacted append log + integrity chain + secret scan + crash recovery | FUTURE / NOT EXECUTED |
| A06-T109 | AUDIT-SECRETS | Consent receipt reference never includes full sensitive diff or source text | redacted append log + integrity chain + secret scan + crash recovery | FUTURE / NOT EXECUTED |
| A06-T110 | AUDIT-SECRETS | Workspace-specific audit reader cannot access another project's decisions | redacted append log + integrity chain + secret scan + crash recovery | FUTURE / NOT EXECUTED |
| A06-T111 | AUDIT-SECRETS | Policy rule bundle migration requires explicit schema version and rollback proof | redacted append log + integrity chain + secret scan + crash recovery | FUTURE / NOT EXECUTED |
| A06-T112 | AUDIT-SECRETS | Secret broker never exposes credential bytes to model tool arguments | redacted append log + integrity chain + secret scan + crash recovery | FUTURE / NOT EXECUTED |
| A06-T113 | ENDTOEND-ADVERSARIAL | Agent prompt-injection goal hijack produces zero unauthorized owner side effects | pinned spec/host/OS + malicious fixture + owner/source proof + metrics | FUTURE / NOT EXECUTED |
| A06-T114 | ENDTOEND-ADVERSARIAL | Forged MCP tool annotation read-only cannot bypass destructive classification | pinned spec/host/OS + malicious fixture + owner/source proof + metrics | FUTURE / NOT EXECUTED |
| A06-T115 | ENDTOEND-ADVERSARIAL | Confused deputy proxy wrong-audience token produces zero downstream access | pinned spec/host/OS + malicious fixture + owner/source proof + metrics | FUTURE / NOT EXECUTED |
| A06-T116 | ENDTOEND-ADVERSARIAL | Concurrent 32 agents maintain scope and per-project isolation under load | pinned spec/host/OS + malicious fixture + owner/source proof + metrics | FUTURE / NOT EXECUTED |
| A06-T117 | ENDTOEND-ADVERSARIAL | Policy churn during 10k READ calls never leaks revoked resource | pinned spec/host/OS + malicious fixture + owner/source proof + metrics | FUTURE / NOT EXECUTED |
| A06-T118 | ENDTOEND-ADVERSARIAL | Source commit race plus revocation yields exactly one valid owner outcome | pinned spec/host/OS + malicious fixture + owner/source proof + metrics | FUTURE / NOT EXECUTED |
| A06-T119 | ENDTOEND-ADVERSARIAL | Static labeled project fixture proves zero unauthorized file modified | pinned spec/host/OS + malicious fixture + owner/source proof + metrics | FUTURE / NOT EXECUTED |
| A06-T120 | ENDTOEND-ADVERSARIAL | Authorized bounded file edit succeeds with valid consent and owner receipt | pinned spec/host/OS + malicious fixture + owner/source proof + metrics | FUTURE / NOT EXECUTED |
| A06-T121 | ENDTOEND-ADVERSARIAL | Selected Codex host test pins actual protocol and authorization request chain | pinned spec/host/OS + malicious fixture + owner/source proof + metrics | FUTURE / NOT EXECUTED |
| A06-T122 | ENDTOEND-ADVERSARIAL | Selected Claude host test pins actual protocol and authorization request chain | pinned spec/host/OS + malicious fixture + owner/source proof + metrics | FUTURE / NOT EXECUTED |
| A06-T123 | ENDTOEND-ADVERSARIAL | Official MCP 2026 protected-resource conformance passes pinned suite | pinned spec/host/OS + malicious fixture + owner/source proof + metrics | FUTURE / NOT EXECUTED |
| A06-T124 | ENDTOEND-ADVERSARIAL | Optional MCP 2025 legacy auth conformance passes when advertised | pinned spec/host/OS + malicious fixture + owner/source proof + metrics | FUTURE / NOT EXECUTED |
| A06-T125 | ENDTOEND-ADVERSARIAL | Full agentic OWASP ASI01-ASI10 corpus yields zero escape and truthful denial | pinned spec/host/OS + malicious fixture + owner/source proof + metrics | FUTURE / NOT EXECUTED |
| A06-T126 | ENDTOEND-ADVERSARIAL | Policy latency p50 p95 p99 meets owner-approved tier benchmark | pinned spec/host/OS + malicious fixture + owner/source proof + metrics | FUTURE / NOT EXECUTED |
| A06-T127 | ENDTOEND-ADVERSARIAL | Sandbox security regression tests pass Windows Linux macOS supported profiles | pinned spec/host/OS + malicious fixture + owner/source proof + metrics | FUTURE / NOT EXECUTED |
| A06-T128 | ENDTOEND-ADVERSARIAL | Evidence bundle pins Git policy SDK spec suite OS fixture and owner receipts | pinned spec/host/OS + malicious fixture + owner/source proof + metrics | FUTURE / NOT EXECUTED |

## Future release/security gate
- All 128 scenarios implemented and passed for supported, approved capabilities, with OS-specific mandatory controls proven or explicitly BLOCKED/UNSUPPORTED. Never count skipped conditional cases as PASS.
- Zero known HIGH/CRITICAL bypass, scope escape, privilege escalation, token passthrough, consent spoof, authorization stale-at-commit, arbitrary command or audit proof corruption.
- Official MCP 2026-07-28 auth conformance and selected host versions tested on exact protocol/transport; legacy compatibility only if advertised. Tests validate actual owner result/OS state.
- Explicit owner-verified source revisions, runtime security review and measured policy/OS overhead on target tiers; numerical budgets adopted only after empirical baseline.
- Separate approved SDK/license/ADR, dependencies code implemented and all overall Stormline DoD conditions; research only does not satisfy runtime DoD.

[Architecture](../architecture/ai-06-agent-security-authorization.md) · [Contracts](../contracts/ai-06-authorization-api.md) · [Benchmarks](../research/ai-06-security-benchmark-protocol.md).
