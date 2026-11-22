# ADR-0114 — DATA-05 governance and bounded bundle direction

**Status:** `OWNER-RATIFIED_BOUNDED_PLANNING_ONLY / NO CODE AUTHORIZED`. **Subordinate to ADR-0013 (planning only) and ADR-0086 (capability admission). Does not declare DATA-03/DATA-04 complete, select a codec, approve signing, public ABI, release or license.**

**Date:** 2026-11-22 | **WO:** `NLE-PRPLAN-DATA-05-01` | **Parent:** DATA-05 | **Issue:** #28.

## Context

DATA-04 closed its internal logical sequence as `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`. DATA-05 (`Cooking, Streaming Bundles & Patching`) has research, architecture, ADR-0013 `PROPOSED`, a semantic contract and a blocked WO; no executable cook or bundle exists. Real compression, signing, network streaming and durable patching are high-risk boundaries.

## Decision

- **A:** ADR-0013 is ratified only as planning direction. No zstd/LZ4/Brotli/meshoptimizer/KTX2, archive library, signing key, HTTP stack or third-party dependency is selected.
- **B:** The first DATA-05 sequence is an in-memory logical bundle model: target profile/cook plan, a bounded Stormline-owned RLE codec for tests, chunked streaming window, manifest with a non-cryptographic FNV-1a 64-bit fingerprint, and incremental chunk reuse.
- **C:** No host file, archive, network, persistence, signature, encryption, canonicalization or public wire format is implemented. No bytewise or interoperability claim is made.
- **D:** Content fingerprints prove only accidental integrity/equality in this sequence; they are **not** authentication and **not** a publisher trust decision.
- **E:** Risk is `LOW` for documentation and `ELEVATED` for implementation/state handling. Release class is `INTERNAL_ONLY`; no public ABI, bundle compatibility, security, data-loss or release claim.
- **F:** DATA-03 import metadata; DATA-04 scene documents; DATA-02 identity; DATA-01 VFS; CORE-01 native OS; CORE-02 memory; CORE-03 jobs; CORE-04 ticks; CORE-06 diagnostics; DATA-05 derives bundle metadata.
- **G:** Oversized chunks, range overflow, stale generations, malformed manifests and patch conflicts fail closed with typed errors.

## Required before code

1. `DATA-05-02` contract with exact C++ API, error model, capacities, RLE/manifest/stream/patch semantics and per-slice test oracles.
2. Individual G6 activation and explicit owner authorization per implementation slice.
3. Tests for target profiles, RLE bounds, chunk ranges, stale generation, manifest mismatch and incremental reuse.
4. Separate G6 for real codecs, signing/trust, network streaming, persistence and native I/O.
5. GCC/Clang/MSVC/AppleClang CI; no HIGH/CRITICAL; no codec/signing/release claim.

## Consequence

- `DATA-05-01` may be prepared as `APPROVED_GOVERNANCE`; `DATA-05-02`..`-09` remain `PLANNED_BLOCKED`.
- DATA-04/03/02/01 remain `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`; CORE-01 not module-qualified.
- G3 `NOT_CLEARED`; NLE-D009 `OPEN`; 80/80 module WOs `BLOCKED`; engine not released.
