# Evidence Bundle — NLE-P00-WO-002-SIM-04 Skeletal Animation & Motion Research

**Status: RESEARCH PR #184 OPEN DRAFT; INITIAL DOCS CI PASS; FINAL EXACT-HEAD CI/AUDIT, MERGE AND CHECKPOINT PENDING. NO ENGINE CODE.**  
**Date:** 2026-11-14 | **Issue:** [#183](https://github.com/KayzenRoot/stormline/issues/183) | **Coding #49:** [OPEN/BLOCKED](https://github.com/KayzenRoot/stormline/issues/49).  
**Base main:** `4dc7060fc0de16c036364a7363755a9ec4ea9144`; research branch `docs/NLE-P00-WO-002-SIM-04-skeletal-motion-research`.

## 1. Source check and Context Lock
Actual starting state on main: SIM-03 documentary research PR #181 and checkpoint PR #182 squash-merged; checkpoint 30/80 documented (37.5%), 50 pending and historical CORE-04 research gap. 80 implementation WOs blocked, zero runtime code modules ready. SIM-04 implementation #49 OPEN/BLOCKED. Snapshot: checkpoint blob `8d526251d2766db97bc23ebedb7cb76fde7e0184`; Ledger `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`; Scope `4ef605c74632ece080b2650e37dd83a415b63310`; DoD `160b3054db9ea1961308934b401488b838d24c3e`; Architecture `df62574cb3956c3ac9881631a4cf66be4e1abff1`; Requirements `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`; module catalog `18d69bca439831d65982cb0f8acbca1dbaa2eee9`.

## 2. Proposed documentary deliverables
- [Architecture](../architecture/sim-04-skeletal-animation-motion.md): original graph, stage/tick ordering, authority boundary, retarget/IK/ragdoll/security/perf tiers.
- [ADR-0034 PROPOSED](../adr/0034-sim-04-animation-authority-retarget-ik-and-ragdoll.md).
- [Technology/license matrix](../research/sim-04-skeletal-animation-technology-license-matrix.md): ozz MIT sampling candidate, ACL MIT **optional incompatible-without-adapter** compression candidate, glTF official specification, Jolt only via SIM-02.
- [API contract](../contracts/sim-04-skeletal-animation-api.md): typed assets, generations, graph command, root motion intent/ack, pose and event receipt, PHYS ragdoll receipt and errors.
- [96 FUTURE acceptance cases](../testing/sim-04-acceptance-matrix.md): NONE EXECUTED.
- [Benchmark protocol](../research/sim-04-animation-benchmark-protocol.md): original synthetic licensed fixtures and future objective/subjective measurements.
- [Research WO](../work-orders/NLE-P00-WO-002-SIM-04.md) and this Evidence Bundle.

No source, compiled runtime, third-party library, actual fixture or benchmark installed. No numeric KPI, codec accuracy, visual or performance superiority asserted. No change to implementation issue #49 or executor readiness.

## 3. Verification ledger (update only on observed results)
| Gate | Actual result at initial drafting |
|---|---|
| Source Pack/Decisions/Module catalog | READ in main as above |
| Research issue/branch | #183 created, scoped branch based on main SHA |
| Research PR number/initial head | [PR #184](https://github.com/KayzenRoot/stormline/pull/184) Draft; initial HEAD `ec7e02850bc443e174a3feac8525457397c4fd49`; 8 added docs files, 0 executable paths |
| Initial CI Docs Validation | [Run 43647075521](https://github.com/KayzenRoot/stormline/actions/runs/43647075521) SUCCESS at initial PR HEAD `ec7e02850bc443e174a3feac8525457397c4fd49`; job `132607157833` all steps SUCCESS: Source Pack/link, dependency DAG, registry, blocked Zcode selector. **After this evidence revision, final HEAD requires a new CI result**. |
| Other security CI/Sonar/Socket | NOT VERIFIED |
| Engine/native/Web/headless tests | NOT EXECUTED |
| 96 runtime acceptance cases | NOT EXECUTED |
| Objective pt-BR diff/architecture/security audit | PENDING on revised exact HEAD; source diff confirmed eight new docs, no runtime or registry flag change |
| Normal squash merge/readback | PENDING |
| Separate checkpoint PR/CI/audit/squash | PENDING |

## 4. Risks
**Possible HIGH in future implementation:** malformed/cyclic joint graph memory attacks, compressed data expansion, stale World/OriginEpoch use-after-free, unauthorized marker/AI node execution, unsafe Ragdoll PHYS mutation, root motion overwriting physics, fake grounded contact, ABI/codec incompatibility and rights violations in sample content. Planned mitigations: bounds, schema/generation/permissions checks, PHYS barriers, engine-owned schemas, import rights manifests, fuzzing, sanitizers, explicit measured capabilities. These are documentary plans, not tested controls.

## 5. Checkpoint delta PROPOSED, not promoted
After research CI/audit/merge success and a separate audited checkpoint PR: mark **SIM-04 research_status only** `RESEARCH_DOCUMENTED_ADR_PROPOSED`, tally 31/80 documented (38.75%) / 49 pending, zero engine, 80 implementation packets still BLOCKED `executor_ready=false`, approved_adr=null; ADR-0034 PROPOSED, coding issue #49 OPEN/BLOCKED; next SIM-05 Navigation & Behavior. Record exact research and checkpoint CI SHA and links. If check fails, do not claim completion.

## 6. Verdict template
APPROVED / CORRECTION REQUIRED / BLOCKED in pt-BR, with exact HEAD/BASE SHA, changed paths, CI run/jobs, scoped defects, licensing and risks, implementation NOT RUN and next allowed action. The executor may propose this delta but cannot self-promote without objective audit.
