# AI-07 — Reproducible Preview, Commit, Undo, Conflict & Recovery Benchmark Protocol

**2026-11-15 | P00 DOCUMENTARY RESEARCH ONLY / NOT IMPLEMENTED | research #305 | NLE-P00-WO-002-AI-07 | future code #81 OPEN/BLOCKED | BASE a7d4b3ae7ecab0061ea6d0dd72b2bce3dd185089.** Formal deps **AI-01 + AI-06 ONLY**, ADRs 0060/0065 PROPOSED; 62/80 researched baseline, 18 pending, all 80 code WOs BLOCKED, engine false, NLE-D009 OPEN.

**FUTURE ONLY: no executable benchmark, transaction runtime, real source owner, journal, host integration or measured target currently exists.** No numbers claimed.

## 1. Hypothesis and core security conditions
Does a bounded multi-object ChangeSet remain reviewable, owner-authorized, deterministic, source-consistent, recoverable and selectively reversible under real crashes/concurrent agents, with acceptable overhead? Compare with a baseline of **independently source-verified** single owner commands, not fake global ACID. Always report actual operation guarantee class and any PARTIAL state. High performance cannot compensate for one unauthorized write, lost update, false source commit or duplicate external publish.

## 2. Pinned environment and independent truth
- Source Pack/git base/head SHA, AI-01 CommandId/schema+owner implementation revision, AI-06 grant/policy epoch and trusted approval UI verification, DATA-04 owner source schema/SceneRevision, DATA-02 AssetId graph, WORLD-02 Prefab/SceneNode identities.
- OS/arch Windows x64, Linux x64, macOS Apple Silicon, filesystem type (NTFS/APFS/ext4), rename/flush profile, DB SQLite library exact patched version and WAL/synchronous/journal_mode, storage medium/capacity/IO limits.
- If optional PostgreSQL/CRDT evaluated, pin exact release and semantic owner adapter, SBOM/license and source fixtures; do not compare synthetic mock with production owner.
- Include *independently reopened* owner state, redacted outside-project sentinel hashes, per-owner durable intent and canonical source revision, runtime generation, asset catalog and export destination receipt.
- Deterministic seeds, quotas and rights-clear synthetic scenes/assets/scripts, independent expected semantic diffs and safe merge outcomes, concurrent actors/grants, per-task expected conflict and one-use approvals.

## 3. Synthetic fixture tiers
| Tier | Dataset | Purpose |
|---|---|---|
| P0 | 1 scene, 10 nodes, 10 assets, 1 change owner | golden-plan and inverse |
| P1 | 10 scenes, 1k nodes, 100 prefabs, 500 asset refs, one owner | normal editor/CLI/MCP |
| P2 | 100 scenes, 100k nodes, 10k asset refs, multiple owners & derived index | stress limits and partial states |
| P3 | owner plus SQLite WAL metadata and filesystem asset replacements | crash/recovery, no fake atomic scope |
| P4 | 10 actor/agent concurrent edits on 100 overlapping objects | conflict, no lost updates |
| P5 | 32 agents with 1k idempotent retries, revoke/consent races | high assurance |
| P6 | 1k undo/redo actions with disjoint/overlapping other actor edits | selective inverse and retention |
| P7 | synthetic external export/publish destination with idempotency contract | compensating or irreversible effects |
| P8 | corrupted/torn journal, disk-full, power-loss and source migration fixtures | recovery and integrity |

Use no actual customer projects, privileged shell, third-party licensed assets or externally destructive public publish.

## 4. Future scenario metrics
| Benchmark | Execution scenario | Independent metrics |
|---|---|---|
| TX-B01 | cold plan creation/validation | latency p50/p95/p99, CPU/RSS, no source/OS delta |
| TX-B02 | semantic diff 10/1k/100k objects | bytes, field precision, recall vs owner truth, memory |
| TX-B03 | DAG dependency analysis and source owner grouping | deterministic ordering, cycle rejection, nodes/edges cost |
| TX-B04 | owner-atomic batch compare to single command sequence | owner source fingerprints, atomicity under injected failure, latency |
| TX-B05 | AI-06 grant + consent digest/JIT checks | added latency, stale/revoked plan writes = 0 |
| TX-B06 | conflict detection and semantic three-way | false safe merge, overlapping conflict precision, no lost edits |
| TX-B07 | cross-owner file+SQLite with failure between participants | actual PARTIAL count, durable journal readback, reconciliation |
| TX-B08 | derived/runtime publish after source commit | update generation lag, source vs renderer receipt |
| TX-B09 | undo of one actor interleaved with other | preservation ratio, UNDO_CONFLICT truth, inverse storage |
| TX-B10 | redo and duplicate idempotency replay | duplicate commits=0, receipt consistency and latency |
| TX-B11 | crash at every state transition | recovered states vs independent owner truth, time to reconcile |
| TX-B12 | torn journal, WAL fsync loss, disk-full and checkpoint restore | data corruption count, recovery outcomes, flush/power-loss durability |
| TX-B13 | external export and compensating rollback | irreversible destination safety, idempotency and partial evidence |
| TX-B14 | 32 actor contention, 100 project rights and stale policy | p50/p95/p99, conflict/denial and unauthorized writes=0 |
| TX-B15 | pinned Codex/Claude/Editor/CLI same logical operations | semantic fingerprint equality, safe ignored volatility |
| TX-B16 | source history and undo checkpoint retention | storage growth/compact time, recovery and licensed-content controls |

## 5. Statistical/recovery method
At least five independent trial runs per fixture with enough samples to interpret p95 and p99; record raw samples, hardware thermal/IO state, warm vs cold, deadline, owner commit vs derived publish latency. Do not make p99 claims from tiny samples; no invented numerical budget. Fault injection must stop process/OS at state boundaries and inspect reopened DB/source and outside-project sentinel after restart. For WAL, record real sync level (NORMAL can lose recent commits on power loss) and verify patched SQLite version/security. For attached multi-db WAL verify **per-DB atomic but not cross-DB**. For filesystem/SQLite combination, grade recoverability and PARTIAL transparency, not fake all-or-nothing.

Preflight every operation with scoped policy and one-use owner plan; don't allow abusive fault tests on user data. Test canceled, expired and revoked consent separately; if source effect committed before cancellation, report real commit and required later undo.

## 6. Evidence receipt proposal
```text
A07BenchmarkReceiptV1 {
 git_base_sha,git_head_sha,critical_source_oids,owner_api_digests,
 ai01_command_schema,ai06_policy_epoch,grant_consent_plan_digest,
 source_owner_revision_before_after,project_asset_scene_ids,
 sdk_db_version,sbom_cve_license,os_arch_filesystem_sync_profile,
 fixture_seed,expected_semantic_state_digest,guarantee_class,
 plan_bytes,plan_latency_samples,diff_accuracy,
 owner_committed_receipts,actual_source_readback_digest,
 derived_runtime_generation,external_effect_receipt,
 partial_commit_count,unauthorized_file_deltas,
 crash_position,journal_chain_digest,recovery_class_latency,
 undo_redo_conflicts,duplicate_owner_commits,storage_growth,
 p50_p95_p99,verdict,independent_audit_ref
}
```
All measurement fields currently **NOT MEASURED**. No future host or SDK conformance can be inferred from green docs-only CI.

[SQLite WAL](https://www.sqlite.org/wal.html) · [SQLite ATTACH](https://www.sqlite.org/lang_attach.html) · [Git merge](https://git-scm.com/docs/git-merge) · [Architecture](../architecture/ai-07-transactional-planning-undo.md).
