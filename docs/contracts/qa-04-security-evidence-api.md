# QA-04 — Versioned Security, Fuzz Corpus, SBOM, Provenance and Incident Evidence Semantic API v0.1

**2026-11-16 | P00 DOCUMENTARY RESEARCH ONLY | [research #353](https://github.com/KayzenRoot/stormline/issues/353) | NLE-P00-WO-002-QA-04 | future code [#93](https://github.com/KayzenRoot/stormline/issues/93) OPEN/BLOCKED | BASE main `04f9ff54875b46fad05941529e1c6719fe79c394`.** Formal deps **QA-01 + NET-06 + AI-06 ONLY**, ADR-0075/0052/0065 PROPOSED. Initial 74/80 researched, six pending, 80/80 future coding WOs BLOCKED, 0 ready/approved_adr, all release classes UNDECIDED, engine=false.


**Design-only logical contract**. No C++ headers, compiled authorization, CI YAML, static scan, runtime policy, SBOM, signed attestation, security incident or 1.0 export produced. Never treat proposal as deployed control.

## Formal upstream authorities, EXACT THREE
| Formal owner | Existing source | QA-04 read-only/verification role |
|---|---|---|
| **QA-01** | [CI receipt contract](qa-01-ci-evidence-api.md), ADR-0075 PROPOSED | source/toolchain/run + CTest/static/SARIF trust evidence; QA-04 writes security quality decision only |
| **NET-06** | [Security validation API](net-06-security-abuse-api.md), ADR-0052 PROPOSED | verify typed SecurityPrincipalContextV1, SecurityValidationEnvelopeV1, trust-state/quotas/replay, never become the network authorization service |
| **AI-06** | [Agent grant API](ai-06-authorization-api.md), ADR-0065 PROPOSED | verify attested agent grant/consent/path/action/expiry/revocation, never create parallel policy evaluator |

Other product owners supply actual input format/shader/media/AI/network/plugin/build after separately approved code and do **not** gain formal QA-04 DAG edges.

## Proposed typed V1 record contracts, NONE IMPLEMENTED
| Record | Proposed required fields | Rejection/integrity |
|---|---|---|
| `SecScopeLockV1` | repo/main base/head SHA, checkpoint/Scope/DoD/ADR fingerprints, QA-01/NET-06/AI-06 contract versions, release profile | STALE stops before any future privileged scan or source mutation |
| `SecThreatBoundaryV1` | untrusted/trusted actor, input/source channel, boundary owner, data type/parser, trust level, assets/rights, permitted side effects, impact class | UNKNOWN trust => deny unscoped operation |
| `SecHarnessManifestV1` | target ID, source HEAD/compiler/ABI/OS, entry symbol and parser owner, expected max input bytes/depth/time/RSS, deterministic state reset, allowed external effects | invalid/infinite harness => BLOCKED, no network/credentials in fuzz runner |
| `SecSeedCorpusV1` | corpus id/version/content SHA, original seed origin/licenses, schema, dictionaries, validity partitions, coverage baseline, retention and privacy classification | unknown provenance or PII => reject seed/public upload |
| `SecFuzzCampaignV1` | engine libFuzzer/AFL++/other pin+license, build flags ASan/UBSan, worker isolation, runs/time, unique crashes, coverage/timeout/RSS, original request/runner trust | no zero-crash=secure claim, failure and limit reason explicit |
| `SecReproducerV1` | private sample hash/size/ACL, minimized bytes and format, exact source/compiler/SAN flags, crash signature/stack redacted, reproduction attempts/outcomes and regression ID | no public exploit dump, no PASS without deterministic replay after patch |
| `SecStaticFindingV1` | tool/version/coverage mode/db SHA, rule ID, affected source/ref, severity, CWE/CVE/GHSA reference if sourced, SARIF artifact digest, suppression justification | no fabricated CVEs or generated-code coverage claim |
| `SecDependencyComponentV1` | package/source/repository/version+commit, direct/transitive, build/runtime classification, integrity hash, SPDX license expression, notices and attribution | missing version/unknown licensing remains explicit and blocks shipping when required |
| `SecVulnerabilityMatchV1` | advisory source/timestamp/identifier, affected version range, fixed version, component digest, reachability/VEX rationale with evidence, status, owner | database absence not absence of risk; defer unknowns |
| `SecSbomReceiptV1` | actual built artifact SHA/target/timestamp, format SPDX-3.0.1/CycloneDX-1.7, schema validation+generator version, dependency closure count, SPDX expression/no NOTICE gaps | P00 no actual subject, cannot claim generated SBOM |
| `SecProvenanceReceiptV1` | verified real subject hash, builder identity, signed in-toto/SLSA v1.2 predicate/track, source ref, workflow/runner trust, verifier result + signature expiration | no SLSA “level” claimed without proven standard requirements |
| `SecGrantBoundaryReceiptV1` | NET-06 principal/session/actor and AI-06 consent/grant scope/test identity, owner, denied operation, revocation epoch, audit hash | rejected test cases must actually deny; prompt text not auth |
| `SecPluginSandboxReceiptV1` | OS/arch/runtime capability/host allowlist, filesystem/network confinement, resource quota and escape denial, supported/unverified flags | unsupported host sandbox => UNSUPPORTED not PASS |
| `SecCiTrustReceiptV1` | event/fork/source ref, token scope, action lock/full SHA, cache trust namespace, artifact ACL, branch ruleset status, OIDC and secrets availability | untrusted fork executes with write/secret => HIGH/CRITICAL gate |
| `SecIncidentCaseV1` | privately tracked ID, first report timestamp, scope/severity+uncertainty, affected builds, triage owner, disclosure channel, containment, verified fix/rollback and user notice | redact sensitive reproducer and no invented response SLA |
| `SecSecurityGateV1` | source/head, required scanners/fuzz targets/sanitizer lanes, observed statuses, unresolved HIGH/CRITICAL, registry queue state, owner audit, PASS/BLOCKED/INCONCLUSIVE | no approval from docs CI or missing required test |
| `SecErrorV1` | SOURCE_STALE, UNSAFE_INPUT, UNTRUSTED_RUNNER, UNSUPPORTED_RUNTIME, NONREPRO_CRASH, FUZZ_BUDGET_EXCEEDED, NO_TESTS_EXECUTED, SBOM_INCOMPLETE, ATTESTATION_INVALID, LICENSING_UNKNOWN, CONSENT_DENIED, CRITICAL_FINDING, COST_GUARD | default fail closed with explicit typed reason |

## Candidate non-executable operations (owner and trust boundary)
| Proposed operation | Responsibility | Result / prohibited side effect |
|---|---|---|
| `identify_sec_trust_boundary` | QA-04 | boundary inventory + owner; not a runtime auth grant |
| `plan_sec_fuzz_targets` | QA-04 + parser owner | small allowlisted targets, corpus rights and budgets, no real user data |
| `execute_sec_fuzz_campaign` | QA-01 CI runner after approved code | actual sanitizer/fuzz coverage or UNSUPPORTED, not a network daemon |
| `triage_sec_fuzz_failure` | QA-04 | minimized private reproducible fixture + negative regression |
| `evaluate_sec_net_policy` | NET-06 actual enforcement, QA-04 testing | use owner principal/session and captured deny receipt |
| `evaluate_sec_agent_grant` | AI-06 actual enforcement, QA-04 testing | consent/grant/expiry/revocation deny and no privilege to QA-04 |
| `check_sec_plugin_sandbox` | host/platform runtime owner | OS-specific confinement evidence, no universal WASM claim |
| `ingest_sec_codeql_sarif` | QA-01 scan, QA-04 triage | verified coverage mode/source/run and real findings |
| `match_sec_dependency_advisories` | QA-04 | real pinned package+OSV/GHSA, false-positive review, not invented vulnerability |
| `generate_sec_sbom` | PLAT-05 release builder, QA-04 checks | schema+digest/license inventory from real artifact, no P00 generation |
| `verify_sec_slsa_provenance` | QA-04 from PLAT-05 builder | actual signature, identity, subject/HEAD, track requirements |
| `audit_sec_actions_trust` | QA-04 risk gate | detect untrusted fork privileges/cache, repository rule status observed |
| `file_sec_private_incident` | owner/high-assurance private path | triage, patch, disclosure, no public proof-of-exploit leak |
| `approve_release_security_gate` | objective QA-04 audit + owner | only with all actual evidence, no known unresolved HIGH/CRITICAL |
| `publish_security_certification` | no current owner | **NOT PERMITTED** from documentary P00 |

## Future proof obligations and stop
A) Security test must execute real approved code+actual QA-01 build, actual scoped NET-06/AI-06 implementation, target/corpus hash and negative case. B) On unsupported sanitizer, missing CodeQL generated coverage or missing input parser, return NOT_EXECUTED/UNSUPPORTED not PASS. C) A SBOM is inventory, not full source license approval nor absence of exploitable CVEs. D) Signed SLSA needs verified real builder, not arbitrary JSON field. E) Privacy: no public attachment of secret/PII/privileged crash; no real user project samples without rights/owner consent. F) Current repo rulesets ZERO and main unprotected, no claim policy enforcement until verified separate admin WO. G) Stop on HIGH/CRITICAL security finding, source STALE, paid tool or malicious/unapproved admin action; keep 80 coding WOs blocked.

[ADR-0078](../adr/0078-qa-04-security-gates-fuzz-sbom-provenance-policy.md) · [128 future tests](../testing/qa-04-acceptance-matrix.md) · [architecture](../architecture/qa-04-security-fuzzing-supply-chain.md).
