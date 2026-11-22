# ADR-0112 — DATA-03 governance and bounded import-planning direction

**Status:** `OWNER-RATIFIED_BOUNDED_PLANNING_ONLY / NO CODE AUTHORIZED`. **Subordinate to ADR-0011 (planning only) and ADR-0086 (capability admission). Does not declare DATA-02 or CORE-01 complete, approve decoders, dependencies, public ABI, release, G3 or license.**

**Date:** 2026-11-22 | **WO:** `NLE-PRPLAN-DATA-03-01` | **Parent:** DATA-03 | **Issue:** #26.

## Context

DATA-02 closed its internal logical registry sequence as `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`. DATA-03 (`Import & Conversion Pipeline`) has research, architecture, ADR-0011 `PROPOSED`, a conceptual API and a blocked WO; no executable importer exists. Real 2D/3D/image/audio decoding is a large untrusted-input and licensing boundary.

## Decision

- **A:** ADR-0011 is ratified only as planning direction. No image/mesh/audio decoder, archive codec, compression library, asset SDK or third-party dependency is selected by this ADR.
- **B:** The first DATA-03 sequence is a logical import-planning layer: fixed importer descriptors, bounded format sniffing by byte signatures, caller-supplied texture/animation/audio metadata validation, typed validation results and bounded provenance receipts.
- **C:** No actual file is read, decoded, converted or written. No parser executes embedded data. Real decoding and conversion require separate G6/security/licensing gates with fuzzing and platform evidence.
- **D:** Identity remains DATA-02 `AssetId`; paths remain DATA-01 `VfsPath`. Receipts reference identity but do not persist or serialize.
- **E:** Risk is `LOW` for documentation and `ELEVATED` for implementation/input validation. Release class is `INTERNAL_ONLY`; no public ABI, SDK, release, decoder-coverage or data-loss claim.
- **F:** DATA-01 logical VFS; CORE-01 native OS; CORE-02 memory; CORE-03 jobs; CORE-04 ticks; CORE-06 diagnostics; DATA-02 identity; DATA-03 logical import planning/validation; DATA-04 serialization/scene transactions; DATA-05 bundles/streaming.
- **G:** Malformed metadata must fail closed with typed errors; quotas bound dimensions, joints, keyframes, audio frames, receipts and warnings.

## Required before code

1. `DATA-03-02` contract with exact C++ API, error model, capacities, sniffing signatures, validation rules and per-slice test oracles.
2. Individual G6 activation and explicit owner authorization per implementation slice.
3. Tests for unknown/truncated signatures, malformed metadata, quota boundaries, duplicate receipts and bounded overload.
4. Separate G6 for real decoders, archive codecs, conversion, native I/O, fuzzing and licensing.
5. GCC/Clang/MSVC/AppleClang CI; no HIGH/CRITICAL; no decoder/release/ABI claim.

## Consequence

- `DATA-03-01` may be prepared as `APPROVED_GOVERNANCE`; `DATA-03-02`..`-10` remain `PLANNED_BLOCKED`.
- DATA-02 remains `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`; DATA-01 not qualified; CORE-01 is not module-qualified; CORE-02 `NOT_QUALIFIED`.
- G3 `NOT_CLEARED`; NLE-D009 `OPEN`; 80/80 module WOs `BLOCKED`; engine not released.
- No implementation packet becomes `EXECUTOR_READY` by this ADR.
