# NLE-PRPLAN-DATA-01-02 — VFS contract (INTERNAL_ONLY)

**STATUS: CONTRACT PACKET — documentary only; implementation remains BLOCKED until DATA-01-03 G6.** **Gate:** G6 contract + CORE-01 capability admission. **Formal packet:** `NLE-PRPLAN-DATA-01-02`. **Predecessor:** `DATA-01-01` governance. **Issue:** #24. **Base:** `626a11c4c198a8eb32373b733b7353c84980f4a0`. **ADR:** [ADR-0110](../adr/0110-data-01-governance-slice.md). **Contract:** [data-01-vfs-v0](../contracts/data-01-vfs-v0.md).

## OBJECTIVE

Freeze the DATA-01 logical VFS contract: ASCII path validation, read-only mount table, deterministic overlay, capabilities, bounded cache and memory-only storage interface. No implementation.

## CONTEXT

DATA-01-01 is `APPROVED_GOVERNANCE` only. ADR-0009 is planning direction; ADR-0110 limits admission to completed CORE-01 capabilities. CORE-01 is not module-qualified. No native filesystem, archive library, dependency or network is selected.

## SCOPE

- Contract `data-01-vfs-v0`: exact API, semantics, errors, PATH/MOUNT/OVERLAY/CAP/CACHE/STORAGE oracles and exact allowlists.
- Evidence of contract review and CORE-01 admission boundary.
- No implementation, dependency, CMake target or code test.

## OUT OF SCOPE

VFS code, native filesystem, PhysicsFS/libzip, archive extraction, writes/deletes, network/cloud, serialization, public ABI/release, CORE-01 completion, DATA-01-03 or later.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0009/0086/0110, DATA-01 architecture/research, governance contract, module catalog, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0110; ADR-0086; ASCII path rules, read-only mounts, deterministic overlay, bounded capacity, no host path leakage.

## ARCHITECTURE RULES

DATA-01 owns logical VFS; CORE-01 native OS bridge, CORE-02 memory, CORE-03 jobs, CORE-04 ticks, CORE-06 diagnostics, DATA-02..05 higher layers. No architecture cycle.

## CONSTRAINTS

Risk `LOW` docs/`ELEVATED` implementation; release `INTERNAL_ONLY`; no code/dependency/secret/paid service/native I/O/network/ABI/release. CORE-01 not module-qualified; CORE-02 NOT_QUALIFIED; CORE-03/04/05/06 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## ACCEPTANCE CRITERIA

- Exact API/errors/semantics/test matrix/allowlists.
- No native I/O, archive, write, network or dependency.
- `DATA-01-02` becomes `APPROVED_CONTRACT`; `-03`..`-10` remain `PLANNED_BLOCKED`.
- Manifest `DATA01_02_APPROVED_CONTRACT_ONLY`: **680 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 54 `COMPLETED`, 14 approved gates**.
- Docs Validation + pt-BR audit; no HIGH/CRITICAL; registry byte-identical.

## TESTS

Docs validators, selector denial, contract review. No native code test authorized.

## DELIVERABLES

Contract, G6 activation evidence, activation JSON, manifest/validator/tests/checkpoint. PR, Docs Validation, pt-BR audit, proposed checkpoint only.

## REVIEW FORMAT

pt-BR: base/head, contract fidelity to ADR-0110/0009, admission, no code/technology, blocked packets. APPROVED/CORRECTION REQUIRED/BLOCKED.

## STOP CONDITION

STALE, missing admission, technology/native I/O selected by inference, code implementation, traversal acceptance, manifest/registry drift, HIGH/CRITICAL, release/ABI/sandbox claim. No code before DATA-01-03 G6.

## CONTEXT LOCK

Base `626a11c4c198a8eb32373b733b7353c84980f4a0`; admission pins CORE-01-03/-06/-07/-08/-12/-13; contract review required before `-03`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-DATA-01-02-G6-ACTIVATION.md`.
