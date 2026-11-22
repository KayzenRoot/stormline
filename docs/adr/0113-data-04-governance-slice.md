# ADR-0113 — DATA-04 governance and bounded scene-document direction

**Status:** `OWNER-RATIFIED_BOUNDED_PLANNING_ONLY / NO CODE AUTHORIZED`. **Subordinate to ADR-0012 (planning only) and ADR-0086 (capability admission). Does not declare DATA-03 or CORE-05 complete, approve a serialization format, dependency, public ABI, release or license.**

**Date:** 2026-11-22 | **WO:** `NLE-PRPLAN-DATA-04-01` | **Parent:** DATA-04 | **Issue:** #27.

## Context

DATA-03 closed its internal logical sequence as `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`. DATA-04 (`Serialization & Scene Format`) has research, architecture, ADR-0012 `PROPOSED`, a semantic contract and a blocked WO; no executable scene document exists. Real JSON/CBOR decoding and durable migrations are untrusted-input and persistence boundaries.

## Decision

- **A:** ADR-0012 is ratified only as planning direction. No JSON/CBOR library, schema validator, serialization codec, database or third-party dependency is selected.
- **B:** The first DATA-04 sequence is a logical in-memory scene document: versioned schema descriptor, stable scene/entity/component IDs, declarative entities/components/asset references, bounded typed patches and semantic entity diffs.
- **C:** No bytes are parsed or produced. No JSON schema, binary format, canonicalization, persistence, migration journal, filesystem, network or MCP tool is implemented.
- **D:** Identity remains DATA-02 `AssetId`/project values; scene/entity/component IDs are opaque 64-bit values in this first sequence.
- **E:** Risk is `LOW` for documentation and `ELEVATED` for implementation/state handling. Release class is `INTERNAL_ONLY`; no public ABI, format compatibility, roundtrip, data-loss or release claim.
- **F:** CORE-05 owns typed math/ID conventions; CORE-01 native OS; CORE-02 memory; CORE-03 jobs; CORE-04 ticks; CORE-06 diagnostics; DATA-01 VFS; DATA-02 identity; DATA-03 import metadata; DATA-04 scene document; DATA-05 bundles.
- **G:** Invalid schemas, duplicate IDs, entity parent cycles, stale revisions and capacity overflow fail closed with typed errors.

## Required before code

1. `DATA-04-02` contract with exact C++ API, error model, capacities, patch/diff semantics and per-slice test oracles.
2. Individual G6 activation and explicit owner authorization per implementation slice.
3. Tests for schema versions, duplicate IDs, parent cycles, stale revision, atomic patch failure and bounded diffs.
4. Separate G6 for real JSON/CBOR, canonicalization, persistence, migrations, recovery, MCP and native I/O.
5. GCC/Clang/MSVC/AppleClang CI; no HIGH/CRITICAL; no format/roundtrip/release claim.

## Consequence

- `DATA-04-01` may be prepared as `APPROVED_GOVERNANCE`; `DATA-04-02`..`-08` remain `PLANNED_BLOCKED`.
- DATA-03 remains `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`; DATA-02/DATA-01 not qualified; CORE-01 not module-qualified.
- G3 `NOT_CLEARED`; NLE-D009 `OPEN`; 80/80 module WOs `BLOCKED`; engine not released.
