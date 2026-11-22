# NLE-PRPLAN-DATA-02-02 — Asset registry contract (INTERNAL_ONLY)

**STATUS: CONTRACT PACKET — documentary only; implementation remains BLOCKED until DATA-02-03 G6.** **Gate:** G6 contract + CORE-01 capability admission. **Formal packet:** `NLE-PRPLAN-DATA-02-02`. **Predecessor:** `DATA-02-01` governance. **Issue:** #25. **Base:** `5443021`. **ADR:** [ADR-0111](../adr/0111-data-02-governance-slice.md). **Contract:** [data-02-registry-v0](../contracts/data-02-registry-v0.md).

## OBJECTIVE

Freeze the DATA-02 logical asset registry contract: 128-bit identity, project/path mapping, tombstones, dependencies, tags, deterministic queries, typed metadata schema and ID-based references. No implementation.

## CONTEXT

DATA-02-01 is `APPROVED_GOVERNANCE` only. ADR-0010 is planning direction; ADR-0111 limits admission to completed CORE-01 capabilities. CORE-01 is not module-qualified. No persistence, SQLite, serialization, dependency or network is selected.

## SCOPE

- Contract `data-02-registry-v0`: exact API, semantics, errors, ID/DEP/TAG/QUERY/SCHEMA/REF oracles and exact allowlists.
- Evidence of contract review and CORE-01 admission boundary.
- No implementation, dependency, CMake target or code test.

## OUT OF SCOPE

Registry code, SQLite/BLAKE3/UUID/serialization selection, native filesystem, persistence, crash recovery, transactions, editor/MCP, network, public ABI/release, CORE-01 completion, DATA-02-03 or later.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0010/0086/0111, DATA-02 architecture/research/api/matrix, governance contract, module catalog, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0111; ADR-0086; opaque identity, project/path uniqueness, tombstones, bounded graph, stable ordering, typed failures, no host leakage.

## ARCHITECTURE RULES

DATA-02 owns logical asset identity/metadata/references; DATA-01 logical VFS; CORE-01 native OS; CORE-02 memory; CORE-03 jobs; CORE-04 ticks; CORE-06 diagnostics; DATA-03/04/05 higher layers. No architecture cycle.

## CONSTRAINTS

Risk `LOW` docs/`ELEVATED` implementation; release `INTERNAL_ONLY`; no code/dependency/secret/paid service/native I/O/network/ABI/release. CORE-01 not module-qualified; CORE-02 NOT_QUALIFIED; CORE-03/04/05/06 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## ACCEPTANCE CRITERIA

- Exact API/errors/semantics/test matrix/allowlists.
- No persistence, SQLite, serialization, native I/O, network or dependency.
- `DATA-02-02` becomes `APPROVED_CONTRACT`; `-03`..`-10` remain `PLANNED_BLOCKED`.
- Manifest `DATA02_02_APPROVED_CONTRACT_ONLY`: **670 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 62 `COMPLETED`, 16 approved gates**.
- Docs Validation + pt-BR audit; no HIGH/CRITICAL; registry byte-identical.

## TESTS

Docs validators, selector denial, contract review. No native code test authorized.

## DELIVERABLES

Contract, G6 activation evidence, activation JSON, manifest/validator/tests/checkpoint. PR, Docs Validation, pt-BR audit, proposed checkpoint only.

## REVIEW FORMAT

pt-BR: base/head, contract fidelity to ADR-0111/0010, admission, no code/technology, blocked packets. APPROVED/CORRECTION REQUIRED/BLOCKED.

## STOP CONDITION

Stale, missing admission, persistence/SQLite/serialization selected by inference, code implementation, ID/path ambiguity accepted, manifest/registry drift, HIGH/CRITICAL, release/ABI/data-loss claim. No code before DATA-02-03 G6.

## CONTEXT LOCK

Base `5443021`; admission pins CORE-01-03/-06/-07/-08/-12/-13; contract review required before `-03`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-DATA-02-02-G6-ACTIVATION.md`.
