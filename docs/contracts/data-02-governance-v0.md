# DATA-02 INTERNAL_ONLY Asset Registry Governance Contract v0 (NLE-PRPLAN-DATA-02-01)

**Status:** `GOVERNANCE PROPOSAL / NOT IMPLEMENTED / NO CODE AUTHORIZED`. **Base:** `9728707`. **ADR:** [ADR-0111](../adr/0111-data-02-governance-slice.md), [ADR-0010](../adr/0010-data-02-asset-identity.md) planning-only. **WO:** [NLE-PRPLAN-DATA-02-01](../work-orders/NLE-PRPLAN-DATA-02-01.md).

## Objective

Record ownership, identity invariants, security boundaries, release/risk classes and gates before DATA-02 implementation. No registry API, persistence, dependency, native I/O, serialization, MCP tool, network or public ABI is authorized.

## Admission and boundaries

- Formal `CORE-01` dependency remains; admission is limited to completed `CORE-01-03/-06/-07/-08/-12/-13` capabilities under ADR-0111/ADR-0086. CORE-01 module completion is **not** claimed.
- Internal predecessor DATA-01 is `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`; no DATA-01 code is reopened or redefined.
- DATA-02 owns asset identity, logical path mapping, tombstones, dependency edges, tags, bounded queries, typed metadata schema and ID-based references.
- CORE-01 owns native OS; CORE-02 memory; CORE-03 jobs/cancellation; CORE-04 ticks; CORE-06 diagnostics; DATA-01 logical VFS; DATA-03 import/decode; DATA-04 serialization/transactions; DATA-05 bundles/streaming.
- No SQLite, BLAKE3, UUID library, JSON/CBOR codec, archive, network, cloud, editor UI or MCP raw access is selected.

## Policy invariants

1. **Identity is not location.** `AssetId` is opaque, stable across logical move/rename and distinct from any path, digest or runtime handle.
2. **Logical state only.** The first sequence is fixed-capacity in-memory state; no host path, file handle, database or serialized byte format appears in the API.
3. **No persistence claim.** There is no survival across process restart, crash recovery, migration or data-loss guarantee in the first sequence.
4. **Bounded.** Assets, edges, tags, metadata entries, path prefix and query output have fixed caps; overflow is typed and never evicts silently.
5. **Deterministic order.** Queries and dumps use stable `AssetId` ordering, never hash-table iteration order.
6. **Explicit graph truth.** Missing targets and cycles are reported as typed results; no unbounded traversal and no silent auto-repair.
7. **Typed failures.** Duplicate ID/path, tombstone, invalid schema, quota and unresolved reference are distinct errors with sanitized context.
8. **No ambient authority.** Project/workspace scoping is explicit; no privileged filesystem, network or MCP access exists in this scope.
9. **Release boundary.** Internal-only; no public ABI, persistence, data-loss, security certification or release claim.

## First-slice scope (future, blocked)

Subject to `DATA-02-02` contract:

- `DATA-02-03` stable IDs and path mapping: `AssetId`, `ProjectId`, asset kind/status/revision, add/find/path lookup/tombstone.
- `DATA-02-04` dependency graph: typed edges, cycle detection, unresolved edges, bounded traversal.
- `DATA-02-05` tags: normalized bounded tags, add/remove/has, per-asset quota.
- `DATA-02-06` queries: project/kind/tag/path-prefix filters, stable order, cursor and bounded output.
- `DATA-02-07` schema: bounded typed metadata entries and supported schema revision.
- `DATA-02-08` references: ID-based reference resolution, rename preserving identity and dependency impact.
- `DATA-02-09` qualification and `-10` closeout remain blocked.

## Gate state after merge

- Manifest root `DATA02_01_APPROVED_GOVERNANCE_ONLY`: **671 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 62 `COMPLETED`, 15 approved gates**.
- `DATA-02-01` becomes `APPROVED_GOVERNANCE`; `DATA-02-02`..`-10` remain `PLANNED_BLOCKED`.
- Selector denies every ID; registry byte-identical; 80/80 module WOs `BLOCKED`.

## Stop / rollback / security

Stop on stale source, missing admission, host path/I/O, database/serialization/dependency selection, ID reuse, path collision acceptance, unbounded traversal, secret/path leakage, MCP/network/editor work, public ABI/release or HIGH/CRITICAL. Unmerged: close the branch. After merge: normal revert PR; never force push.

No implementation is authorized by this governance contract. `DATA-02-02` requires its own audited contract and `DATA-02-03` its own G6.
