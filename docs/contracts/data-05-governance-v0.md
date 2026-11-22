# DATA-05 INTERNAL_ONLY Bundle Governance Contract v0 (NLE-PRPLAN-DATA-05-01)

**Status:** `GOVERNANCE PROPOSAL / NOT IMPLEMENTED / NO CODE AUTHORIZED`. **Base:** `6886f93`. **ADR:** [ADR-0114](../adr/0114-data-05-governance-slice.md), [ADR-0013](../adr/0013-data-05-cooking-policy.md) planning-only. **WO:** [NLE-PRPLAN-DATA-05-01](../work-orders/NLE-PRPLAN-DATA-05-01.md).

## Objective

Record ownership, trust boundaries, release/risk classes and gates before DATA-05 implementation. No codec, archive, signing, persistence, network, native I/O, dependency, MCP tool or public ABI is authorized.

## Admission and boundaries

- Formal dependencies are `DATA-03` and `DATA-04`; neither is qualified.
- DATA-05 owns target profiles, cook plans, bounded RLE, chunk streaming window, manifests and incremental chunk reuse.
- DATA-01 VFS; DATA-02 identity; DATA-03 import metadata; DATA-04 scene documents; CORE-01 native OS; CORE-02 memory; CORE-03 jobs; CORE-04 ticks; CORE-06 diagnostics.
- No zstd/LZ4/Brotli/meshoptimizer/KTX2, archive library, signing key, HTTP stack or dependency is selected.

## Policy invariants

1. **In-memory only.** No host file, archive, network, persistence or signed artifact.
2. **Owned RLE only.** Compression is a bounded Stormline-owned RLE codec for tests; no external codec or wire-format claim.
3. **Fingerprint is not authentication.** FNV-1a 64 detects accidental mismatch only; no trust/signature claim.
4. **Stable identity.** Asset references use DATA-02 `AssetId`; chunk IDs are opaque 64-bit values.
5. **Bounded.** Target profiles, assets, chunks, streaming window, manifest entries, patch reuse and warnings are fixed.
6. **Range safety.** Chunk offset/length arithmetic is checked; overlap and overflow fail closed.
7. **Stale generations fail closed.** Streaming/patch operations bind a generation.
8. **No persistence/recovery claim.** Patch planning is logical; no durable journal, commit or rollback.
9. **Release boundary.** Internal-only; no codec compatibility, signature, security, ABI or release claim.

## First-slice scope (future, blocked)

- `-03` target profile and cook plan.
- `-04` bounded RLE encode/decode.
- `-05` chunked streaming window with budget.
- `-06` manifest with FNV-1a fingerprint and verification.
- `-07` incremental chunk reuse plan.
- `-08` qualification and `-09` closeout remain blocked.

## Gate state after merge

- Manifest root `DATA05_01_APPROVED_GOVERNANCE_ONLY`: **643 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 84 `COMPLETED`, 21 approved gates**.
- `DATA-05-01` becomes `APPROVED_GOVERNANCE`; `DATA-05-02`..`-09` remain `PLANNED_BLOCKED`.

## Stop / rollback / security

Stop on stale source, missing admission, external codec/signing/archive/network/persistence, host I/O, unbounded input, ABI/release or HIGH/CRITICAL. Revert normally; never force push.

No implementation is authorized by this governance contract.
