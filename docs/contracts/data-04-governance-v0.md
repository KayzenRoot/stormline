# DATA-04 INTERNAL_ONLY Scene Document Governance Contract v0 (NLE-PRPLAN-DATA-04-01)

**Status:** `GOVERNANCE PROPOSAL / NOT IMPLEMENTED / NO CODE AUTHORIZED`. **Base:** `a26e463`. **ADR:** [ADR-0113](../adr/0113-data-04-governance-slice.md), [ADR-0012](../adr/0012-data-04-scene-schema-policy.md) planning-only. **WO:** [NLE-PRPLAN-DATA-04-01](../work-orders/NLE-PRPLAN-DATA-04-01.md).

## Objective

Record ownership, format trust boundaries, release/risk classes and gates before DATA-04 implementation. No JSON/CBOR codec, schema validator, persistence, migration journal, native I/O, dependency, MCP tool, network or public ABI is authorized.

## Admission and boundaries

- Formal dependencies are `CORE-05` and `DATA-02`; both are not qualified modules.
- DATA-04 owns versioned scene schema descriptors, declarative in-memory documents, bounded patches and semantic diffs.
- DATA-01 logical VFS; DATA-02 identity; DATA-03 import metadata; CORE-05 typed math/IDs; CORE-01 native OS; CORE-02 memory; CORE-03 jobs; CORE-04 ticks; CORE-06 diagnostics; DATA-05 bundles.
- No JSON/CBOR library, schema validator, database, serialization codec or network is selected.

## Policy invariants

1. **No byte format in the first sequence.** Scene documents are in-memory logical values; no parse/serialize/canonicalize claim.
2. **Stable opaque IDs.** Scene/entity/component IDs are not array indices or pointer values.
3. **Versioned schema.** Only declared schema versions and capability bits are accepted; unsupported versions fail closed.
4. **Bounded.** Entities, components, asset references, patch operations and diff entries are fixed.
5. **Atomic patches.** A failed patch leaves the document unchanged; stale base revision is rejected.
6. **Explicit graph truth.** Duplicate IDs and parent cycles are rejected; no silent repair.
7. **Identity via DATA-02.** Asset references carry `AssetId`; no path/hash identity.
8. **No persistence or format claim.** No file, JSON/CBOR, migration journal, recovery or roundtrip.
9. **Release boundary.** Internal-only; no public ABI, format compatibility, security certification or release claim.

## First-slice scope (future, blocked)

- `-03` versioned schema descriptors and capability checks.
- `-04` declarative scene/entity/component/asset-ref document.
- `-05` bounded atomic patches with stale-revision rejection.
- `-06` semantic entity diffs over stable IDs.
- `-07` qualification and `-08` closeout remain blocked.

## Gate state after merge

- Manifest root `DATA04_01_APPROVED_GOVERNANCE_ONLY`: **651 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 78 `COMPLETED`, 19 approved gates**.
- `DATA-04-01` becomes `APPROVED_GOVERNANCE`; `DATA-04-02`..`-08` remain `PLANNED_BLOCKED`.

## Stop / rollback / security

Stop on stale source, missing admission, format/codec/dependency selection, host I/O, unbounded input, ABI/release or HIGH/CRITICAL. Revert normally; never force push.

No implementation is authorized by this governance contract.
