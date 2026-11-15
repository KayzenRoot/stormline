# AI-06 — Future Reproducible Authorization, Isolation and Consent Benchmark Protocol

**2026-11-15 | P00 RESEARCH ONLY / NOT IMPLEMENTED | research #301 | NLE-P00-WO-002-AI-06 | future code #80 OPEN/BLOCKED | BASE 886f8c8687c4c79a18a3cb3b7e82a26a054eb656.** Formal deps AI-04 + AI-01 ONLY; 61/80 research at baseline, all 80 future code WOs BLOCKED; ADR-0065 PROPOSED; NLE-D009 OPEN.

**No policy engine, grant store, OS sandbox, trusted approval UI, auth provider, test, build or benchmark exists. No measured times, numerical security claim or approved performance thresholds.**

## 1. Hypotheses and proof obligations
Does an AI-06 policy+owner gate enforce exact agent/workspace/grant boundaries while preserving bounded local authoring latency? A benchmark passes only when:
- a denied agent **cannot mutate or inspect any outside-project sentinel** (verify file hashes and source owner state independently before/after);
- allowed read/preview/edit workflows result in correct source revision and owner receipt, no duplicate commit or privilege inflation;
- key rotation, revocation and consent replay are denied at actual owner side-effect point;
- audit evidence correlates decision/consent/receipt without secrets;
- legitimate actions do not receive unexplained denials and decision latency obeys separately owner-approved tiers.
A fast but leaky evaluator FAILS; test misses and unsupported OS isolation are not PASS.

## 2. Pin environment and fixtures
Git base/head/Source Pack OIDs, policy source hash/schema, runtime evaluator candidate/version (Cedar, OPA, project custom), license/SBOM/SPDX/CVE report, AI-01 CommandId schema and owner source revision, AI-04 MCP version/transport/verified client, selected host versions, OS (Windows/Linux/macOS)/arch/kernel sandbox feature probe, owner project manifests and exact ACL snapshot. Use deterministic synthetic projects and users/agents/delegation trees; never real tokens/passwords or customer source. Separate owner fixture/ACL oracle from AI-06 policy output.

## 3. Benchmark datasets
| Tier | Fixture | Purpose |
|---|---|---|
| A0 | 1 project, 10 commands, 3 agents, 8 grants, 20 resources | cold policy load and basic grant |
| A1 | 10 projects, 100 commands, 32 agents, 1k resources, 1k grants | normal denied/allowed/consent |
| A2 | 100 projects, 1k commands, 1k agents, 100k resources, 100k grants | stress and tenant isolation |
| A3 | 1 project with symlink/junction/UNC/hardlink and Unicode aliases, 10k path mutations | TOCTOU/OS escape regression |
| A4 | 100 delegation chains of depth 1..16 and 10k revocations | attenuation and policy epochs |
| A5 | 10k malformed policy/approval/OAuth token fixtures | fail-closed and parsing |
| A6 | 32 concurrent agents, randomized interrupts/crashes/restarts | race recovery and audit |
| A7 | one approved plan plus forged/stale/expired/replayed approvals | trusted UI and owner commit |

All programs run against **synthetic source owner and filesystem sentinels** under a restricted benchmark account and disconnected/allowlisted network. No live externally destructive tests, real credential leaks or irreversible actions are needed.

## 4. Future measurement matrix
| ID | Experiment | Independent metrics |
|---|---|---|
| SEC-B01 | cold local policy load and 100k fixed decisions | startup, median/p95/p99, CPU/RSS; deterministic verdict |
| SEC-B02 | READ/PREVIEW/MUTATE owner authorization vs direct owner baseline | added latency, owner revision validity, false allow/deny |
| SEC-B03 | 32 agent concurrency and 10 project isolation | cross-project leaked bytes/commits = 0, memory and backpressure |
| SEC-B04 | parent revoke while child calls and owner commit race | grant stop latency, unauthorized commit count = 0 |
| SEC-B05 | consent mint/review/consume/replay/expiry | UI/owner digest validation, replayed commit count = 0 |
| SEC-B06 | policy fallback timeout/crash/malformed bundle | reject rate, bounded outage, zero unauthorized commits |
| SEC-B07 | symlink/junction/hardlink/mount/Unicode path swaps | outside-project path opened/mutated = 0 |
| SEC-B08 | local stdio launch verified peer vs spoofed process | invalid admission = 0, launch overhead |
| SEC-B09 | remote OAuth token negative issuer/audience/scope/expiry/iss mixup | unauthorized dispatch = 0, challenge correctness |
| SEC-B10 | Linux Landlock/seccomp/namespaces sandboxed helper | forbidden syscall/file/network = 0, syscall overhead |
| SEC-B11 | Windows AppContainer/restricted-token/Job Object helper | denied foreign filesystem/network, process startup |
| SEC-B12 | macOS App Sandbox/XPC security-scoped resource helper | denied foreign filesystem/network, start/memory |
| SEC-B13 | Wasmtime/WASI capability guest vs unsandboxed baseline (only if selected) | allowed host imports, escape count, fuel/memory |
| SEC-B14 | audit append/verify, key rotation, crash recovery, quota | missing/duplicate events, tamper-detection, disk I/O |
| SEC-B15 | OWASP ASI01..10 adversarial corpus and multi-agent handoff | goal hijack escape count, policy bypass count, manual labels |
| SEC-B16 | policy migration/rollback and fail-closed inconsistent generation | old/new generation boundary integrity, denial latency |

## 5. Scientific method and reporting
- Fix deterministic seeds, source revisions and approved policy manifest for all comparisons. At least five isolated repetitions plus enough samples to interpret p95/p99; report raw sample distribution, not invented p99 precision.
- Compare **owner with and without AI-06 advisory policy** only in controlled synthetic harness; never disable security in a live service. Separately compare Cedar vs OPA vs minimal static ACL under the same semantic policy AST and independent expected outcomes.
- Measure actual owner/OS state after each negative test, hash outside-project files, inspect process/socket/file handles where OS allows; log only counts/pseudonyms and trace hashes.
- Run cold/warm, cache hit/miss and policy epoch churn separately. A cached ALLOW may never bypass JIT owner recheck. Report privacy-safe denial count and ratio but do not claim 0 false denies without labeled baseline.
- Reproduce on Windows/Linux/macOS Apple Silicon (where supported), and record target CPU/kernel/ABI/sandbox ability. Missing mandatory sandbox -> BLOCKED, not performance pass. Record remote RTT and issuer test fixture separately from local stdio.
- Thresholds are **TBD owner-approved after measured baseline**. Latency cannot outweigh zero unauthorized commits. Any observed grant/consent/owner bypass is HIGH/CRITICAL blocker.

## 6. Future evidence receipt fields
```text
A06SecurityBenchmarkReceiptV1 {
  git_base_sha, git_head_sha, policy_bundle_digest, policy_engine_tag,
  sbom_license_cve_digest, ai01_owner_api_digest, ai04_mcp_version,
  subject_agent_grant_epoch, owner_project_revision_vector,
  host_name_version, transport_auth_profile, os_arch_kernel_sandbox_probe,
  fixture_seed, expected_decisions_digest, owner_truth_snapshot_digest,
  operations_allowed_denied, false_allow_false_deny, scope_escape_count,
  unauthorized_owner_commits, outside_project_file_diff_count,
  unauthorized_fd_network_count, approval_replay_commits,
  revocation_race_failures, audit_integrity_failures,
  latency_raw_samples, p50_p95_p99, rss_cpu_io, failure_trace_digest,
  verdict, independent_audit_reference
}
```
All fields except conceptual schema are **NOT MEASURED / NOT EXECUTED** in this P00 research step.

[OWASP Agentic](https://genai.owasp.org/resource/owasp-top-10-for-agentic-applications-for-2026/) · [MCP security](https://modelcontextprotocol.io/docs/2026-07-28/tutorials/security/security_best_practices) · [Linux Landlock](https://docs.kernel.org/userspace-api/landlock.html) · [Architecture](../architecture/ai-06-agent-security-authorization.md).
