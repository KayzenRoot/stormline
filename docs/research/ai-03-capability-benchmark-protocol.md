# AI-03 — Reproducible Capability Completeness, Schema, Security and Discovery Benchmark

**2026-11-15 | P00 RESEARCH ONLY, NOT IMPLEMENTED | [research #289](https://github.com/KayzenRoot/stormline/issues/289) | NLE-P00-WO-002-AI-03 | [future code #77](https://github.com/KayzenRoot/stormline/issues/77) OPEN/BLOCKED | BASE `1db368aa555f7a8eb2fa1a1eb3a38744a23ef6bb`.** 58/80 researched at baseline, 22 pending, zero engine, all 80 implementation packets BLOCKED. Formal dependency **AI-01 ONLY**; ADR-0060 PROPOSED and code #75 OPEN/BLOCKED. NLE-D009 engine license OPEN.

**FUTURE PROTOCOL ONLY; 0 native runs, 0 schema validators installed, 0 performance measurements.** Exact performance budgets and tier thresholds require owner approval with measured pilot baselines, not invented targets.

## 1. Baseline and fixture provenance
Capture Git base/head, AI-01 handler/owner manifest SHA, independent eligible public action manifest (Editor menus, toolbar, palette, CLI, command owner), explicit exclusion ledger and module catalog; schema dialect/vocabulary, compiler tag/license/build flags, JSON Schema Test Suite revision/optional cases, source commit/manifest digest, policy/authorization epoch, target feature matrices and ProjectId/principal fixture, C++ compiler/stdlib/OS/CPU/RAM/SSD and filesystem. Record sorted output hashes and cold/warm results. Build a negative test manifest containing orphan/duplicate/hidden actions to test denominator independence.

## 2. Controlled dataset matrix
| Dataset | Size/shape | Goal |
|---|---|---|
| CAP-S | 100 independently authored eligible actions, 20 schema refs, 3 roles, 2 projects | Basic coverage, stable maps, deterministic sorted lists |
| CAP-M | 10,000 command descriptors, 4,000 schema references, 32 principals, 16 targets | Pagination/lookup speed and memory without leakage |
| CAP-L | 100,000 descriptors and deep local reference graph with sparse rights | Stress profile only; NOT claimed v1.0 promise |
| CAP-H | malicious refs, duplicate keys, invalid Unicode, pathological regex, cycles, oversized descriptions | Negative/fuzz bounds and fail-closed behavior |
| CAP-V | old/new major/minor/schema/side-effect/permissions/enum matrices | Compatibility/deprecation correctness |
| CAP-C | concurrent read + staged publish + grant revocation + crash matrix | Atomic generations and security races |

Data should be synthetic and rights-cleared, with deterministic seed, explicit deny-list identities and golden independently generated action inventory. No private project files or secrets copied to public CI artifacts.

## 3. Future scenario and metrics
| Scenario | Action | Required measured results |
|---|---|---|
| REG-01 | full descriptor compile from owner manifest, stage, verify independent coverage | build wall time p50/p95; CPU time; peak RSS; unexpected missing/ghost count = 0 |
| REG-02 | schema validator corpus Draft 2020-12 required tests, differential second oracle | required pass/fail counts by vocabulary, unexpected differential list; optional cases separate |
| REG-03 | cold/warm read describe, list and cursor with varied permissions | p50/p95/p99 per request, bytes, denied counts, quotas, heap/RSS |
| REG-04 | reverse inventory across UI/CLI/owner and generated MCP projection | 100% eligible coverage with approved exclusions; zero duplicated executable handler |
| REG-05 | target/feature/plugin registration and compatibility diff vs prior generation | compile/publish latency, compatibility error classification, deterministic SHA |
| REG-06 | 64 concurrent readers and 1 publisher, crash injection at each staging phase | generation atomicity, rollback success, reader consistency, recovery latency |
| REG-07 | mutate grant/revoke actor/ProjectId during discovery/pagination/invocation | unauthorized names/counts/hash/snippets/operations exposed = 0 |
| REG-08 | remote $ref, file://, recursive/dynamicRef, regex DoS, invalid keys/UTF-8, large instance | bounded latency/RSS; typed rejection; no untrusted IO/exec |
| REG-09 | Windows/Linux/macOS Apple Silicon native offline no-GPU headless discovery | deterministic normalized descriptors and identity under same pinned schema profile |
| REG-10 | MCP 2026-07-28 vs negotiated older host using AI-04 future adapter | faithful object input, output schema any value, no unauthorized tool, explicit mismatch |

## 4. Measurement protocol
Minimum 5 clean runs per toolchain/platform after warmup, record cold and warm separately; preserve raw redacted timing samples, derive p50/p95/p99 **only when sample count supports resolution**. Profile wall/CPU, peak RSS/allocations, descriptor/byte and schema graph size, success/error class, publish availability, fail-closed on exceeded quotas, no network/GPU. Set independent acceptance thresholds *after* environment baseline, by tier and target, in an approved delta to Scope/DoD/ADR. A fast but incomplete registry fails. A 100% registry containing private/unauthorized tool fails. A green docs CI proves only documentation integrity.

## 5. License, security, compatibility and failure gate
For selected JSON Schema compiler record SPDX/license exact pinned release plus transitive components/notice; run official JSON Schema 2020-12 required suite and negative corpus. Test no unrestricted external $ref, no remote listener and no direct handler invoke on discovery, no cross-project count/cursor leak, no privilege escalation from hint metadata or abandoned grant, no unintended source change. CI must reproduce on Windows x64/Linux x64/macOS Apple Silicon when implementation exists. Mock Web adapter only cannot prove native platform support. Any HIGH/CRITICAL failure, schema mismatch or incomplete external inventory => BLOCKED; rollback validated immutable previous generation, but revocation remains effective.

## 6. Artifact receipt format (future)
`{base_sha,head_sha,owner_manifest_sha,action_inventory_sha,schema_bundle_sha,dialect,validator_tag,license_sbom_sha,OS,arch,toolchain,seed,fixture,run_id,actor_scope,policy_epoch,command_count,covered_count,excluded_count,orphan_count,invalid_count,latency_samples,RSS,denied_leaks,crash_steps,raw_logs_digest,verdict}`. No values fabricated at P00.
