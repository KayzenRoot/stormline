# NLE-PRPLAN-DATA-05-02 — Bundle contract (INTERNAL_ONLY)

**STATUS: CONTRACT PACKET — documentary only; implementation remains BLOCKED until DATA-05-03 G6.** **Formal packet:** `NLE-PRPLAN-DATA-05-02`. **Predecessor:** `DATA-05-01` governance. **Issue:** #28. **Base:** `23544da`. **ADR:** [ADR-0114](../adr/0114-data-05-governance-slice.md). **Contract:** [data-05-bundle-v0](../contracts/data-05-bundle-v0.md).

## OBJECTIVE

Freeze the DATA-05 logical bundle contract: target/cook plans, owned RLE, chunk store/window, manifest FNV-1a fingerprint and incremental reuse. No external codec.

## CONTEXT

DATA-05-01 is `APPROVED_GOVERNANCE`. ADR-0013 is planning direction; ADR-0114 forbids external codecs/signing/network/persistence. DATA-03/DATA-04 are not qualified.

## SCOPE

- Contract `data-05-bundle-v0`: exact API, semantics, errors, TGT/RLE/MAN/STR/PAT/QLF oracles and allowlists.
- Evidence of contract review and DATA-03/DATA-04 admission boundary.
- No implementation, codec, dependency, CMake target or code test.

## OUT OF SCOPE

Bundle code, zstd/LZ4/Brotli/meshoptimizer/KTX2, archive, signing, persistence, native I/O, network, MCP, public ABI/release, DATA-05-03 or later.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0013/0086/0114, DATA-05 architecture/research/api, governance contract, DATA-04 closeout, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0114; bounded target/RLE/manifest/stream/patch, typed failures, no external codec.

## ARCHITECTURE RULES

DATA-05 owns logical bundle metadata; DATA-03/04 sources; DATA-01/02 identity; CORE boundaries unchanged.

## CONSTRAINTS

Risk `LOW` docs/`ELEVATED` implementation; release `INTERNAL_ONLY`; no codec/signing/dependency/native I/O/network/persistence/ABI/release. DATA-03/04 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## ACCEPTANCE CRITERIA

- Exact API/errors/semantics/test matrix/allowlists.
- No external codec, signing, archive, persistence, native I/O, network or dependency.
- `DATA-05-02` becomes `APPROVED_CONTRACT`; `-03`..`-09` remain `PLANNED_BLOCKED`.
- Manifest `DATA05_02_APPROVED_CONTRACT_ONLY`: **642 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 84 `COMPLETED`, 22 approved gates**.
- Docs Validation + pt-BR audit; no HIGH/CRITICAL; registry byte-identical.

## TESTS

Docs validators, selector denial, contract review. No native code test authorized.

## DELIVERABLES

Contract, G6 activation evidence, activation JSON, manifest/validator/tests/checkpoint.

## REVIEW FORMAT

pt-BR: base/head, contract fidelity, admission, no-codec/signing boundary, blocked packets.

## STOP CONDITION

Stale, missing admission, codec/signing/persistence selected by inference, code implementation, manifest drift, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `23544da`; admission pins DATA-03-03..09 and DATA-04-03..07; contract review required before `-03`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-DATA-05-02-G6-ACTIVATION.md`.
