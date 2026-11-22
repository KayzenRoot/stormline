# DATA-03 INTERNAL_ONLY Import Planning Governance Contract v0 (NLE-PRPLAN-DATA-03-01)

**Status:** `GOVERNANCE PROPOSAL / NOT IMPLEMENTED / NO CODE AUTHORIZED`. **Base:** `26ef854`. **ADR:** [ADR-0112](../adr/0112-data-03-governance-slice.md), [ADR-0011](../adr/0011-data-03-import-policy.md) planning-only. **WO:** [NLE-PRPLAN-DATA-03-01](../work-orders/NLE-PRPLAN-DATA-03-01.md).

## Objective

Record ownership, trust boundaries, release/risk classes and gates before DATA-03 implementation. No decoder, conversion, archive, native I/O, dependency, persistence, MCP tool, network or public ABI is authorized.

## Admission and boundaries

- Formal `DATA-02` dependency; DATA-02 is `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`.
- DATA-03 owns importer descriptors, bounded signature sniffing, metadata validation and logical provenance receipts.
- DATA-01 owns logical VFS; DATA-02 owns identity; CORE-01 native OS; CORE-02 memory; CORE-03 jobs; CORE-04 ticks; CORE-06 diagnostics; DATA-04 serialization; DATA-05 bundles.
- No image/mesh/audio decoder, archive codec, compression library, SDK or network is selected.

## Policy invariants

1. **No real decoding in the first sequence.** Callers supply bounded metadata; the module validates it. No file is read or written.
2. **Untrusted input fails closed.** Unknown/truncated signatures and malformed metadata return typed errors.
3. **Bounded.** Importer count, signature bytes, dimensions, joints, keyframes, audio frames, receipts and warnings are fixed.
4. **No host leakage.** Errors contain codes and safe stages, not host paths, buffers or secrets.
5. **Identity is DATA-02.** Receipts carry `AssetId`; they do not mint identity or persist.
6. **No conversion claim.** Reserved artifact types are logical; no bytes are produced.
7. **Deterministic.** Descriptor lookup and receipt scans use stable insertion/ID order.
8. **No ambient authority.** No shell, plugin execution, network, SQL, MCP or native filesystem.
9. **Release boundary.** Internal-only; no decoder coverage, security certification, ABI or release claim.

## First-slice scope (future, blocked)

- `-03` importer descriptors + bounded signature sniffing + import plan.
- `-04` texture metadata validation.
- `-05` animation metadata validation.
- `-06` audio metadata validation.
- `-07` integrated validation pipeline with quotas.
- `-08` bounded provenance receipts.
- `-09` qualification and `-10` closeout remain blocked.

## Gate state after merge

- Manifest root `DATA03_01_APPROVED_GOVERNANCE_ONLY`: **661 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 70 `COMPLETED`, 17 approved gates**.
- `DATA-03-01` becomes `APPROVED_GOVERNANCE`; `DATA-03-02`..`-10` remain `PLANNED_BLOCKED`.
- Selector denies every ID; registry byte-identical; 80/80 module WOs `BLOCKED`.

## Stop / rollback / security

Stop on stale source, missing admission, decoder/archive/dependency selection, host I/O, unbounded parsing, secret/path leakage, ABI/release or HIGH/CRITICAL. Unmerged: close the branch. After merge: normal revert PR; never force push.

No implementation is authorized by this governance contract. `DATA-03-02` requires its own audited contract and `DATA-03-03` its own G6.
