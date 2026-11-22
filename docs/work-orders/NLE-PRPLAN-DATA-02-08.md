# NLE-PRPLAN-DATA-02-08 — ID-based references and identity-preserving rename (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Gate:** G6 implementation + DATA-01 capability admission. **Formal packet:** `NLE-PRPLAN-DATA-02-08`. **Predecessor:** `DATA-02-07` schema. **Issue:** #25. **Base:** `f846dad`. **ADR:** [ADR-0111](../adr/0111-data-02-governance-slice.md). **Contract:** [data-02-registry-v0](../contracts/data-02-registry-v0.md).

## OBJECTIVE

Add ID-based references, typed reference resolution, identity-preserving logical rename with path-collision checks, and bounded transitive impact. No persistence, serialization, native I/O, network or ABI.

## CONTEXT

DATA-02-01..07 are approved/completed. Registry IDs, paths, tombstones, dependencies, tags, queries and metadata exist. DATA-01 is internally complete but not qualified. The owner authorized DATA-01..04 completion on 2026-11-22.

## SCOPE

- `asset_registry.hpp` additive reference/rename/impact methods.
- `tests/core/data02_reference_tests.cpp`: REF-01.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Persistence, serialization, SQLite, native filesystem, network, MCP, transactions, crash recovery, ABI/release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0010/0086/0111, `data-02-registry-v0`, DATA-02-07 evidence, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0111; REF-01; ID-based resolution, kind check, tombstone, rename preserves ID, collision/invalid path rejection, bounded impact.

## ARCHITECTURE RULES

DATA-02 owns references/impact; DATA-01 owns paths; CORE-01 native OS, CORE-02 memory, CORE-03 jobs, CORE-04 ticks, CORE-06 diagnostics, DATA-03/04/05 higher layers. Header-only internal C++20.

## CONSTRAINTS

Risk `ELEVATED`; release `INTERNAL_ONLY`; no dependency/package/secret/paid service/native I/O/network/persistence; CORE-01 not module-qualified; DATA-01 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## ACCEPTANCE CRITERIA

- Exact allowlist; REF-01 resolve/kind/tombstone/rename/collision/impact.
- No persistence/serialization/native I/O/dependency.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; no dependency/ABI/release change; pt-BR audit `APPROVED`.

## TESTS

REF-01 active/missing/tombstoned/kind mismatch, rename preserves ID and references, old path gone, collision and invalid path rejected, impact transitive/sorted/bounded, leaf/self/missing. Existing suite required.

## DELIVERABLES

Additive `asset_registry.hpp`, reference tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, REF-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim. APPROVED/CORRECTION REQUIRED/BLOCKED.

## STOP CONDITION

Stale base, gate not merged, API drift, ID change on rename, persistence/native I/O, unbounded impact, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `f846dad`; contract blob `ada255f8b4dc3d468adabaaecb074bfa3cfdbd1d`; DATA-02-07 code PR #606 merged.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-DATA-02-08-G6-ACTIVATION.md` for the gate; `docs/evidence/NLE-PRPLAN-DATA-02-08.md` for implementation.
