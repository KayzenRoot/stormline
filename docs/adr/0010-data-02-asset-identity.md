# ADR-0010 — Persistent Asset Identity, Registry Index and Provenance

**Status:** PROPOSED / NOT APPROVED FOR PRODUCTION IMPLEMENTATION  
**Date:** 2026-11-14 | **Research WO:** NLE-P00-WO-002-DATA-02 | **Issues:** #111 (research) / #25 (BLOCKED implementation)

## Problem

Stormline's editor, generated games and future AI-native project tools need stable references to assets after moving, renaming, reimporting and rebuilding metadata. The registry must survive crashes, project copying and source-control merges without silent reference corruption. No engine runtime or tests exist yet.

## Proposed direction
1. **Own a versioned `AssetId` and typed registry API**, independent of VFS path, content hash, runtime handle and third-party database types.
2. **Evaluate UUIDv7 (RFC 9562)** as candidate persistent 128-bit identity, comparing to UUIDv4. Do not infer authorization or perfect collision-free behavior.
3. **Prefer research into portable canonical project metadata** with a **rebuildable SQLite derived index**. Benchmark against SQLite-authoritative and manifest/in-memory alternatives; never promise DB+file atomic commit.
4. Use DATA-01 staged filesystem operations + a versioned, idempotent transaction/recovery journal to reconcile rename/move and index invalidation after interruption.
5. Use **content digests tagged with algorithm** for revision/cache/verification, compare BLAKE3 and SHA-256; no digest-as-AssetId, no security/authenticity claims from hashes alone.
6. Store typed dependency edges, ownership/source provenance, revisions and tombstones; preserve identity on move/reimport, create new ID on duplicate; report and resolve conflicts from merged/copied projects.
7. Expose semantic, capability-scoped Editor/CLI/MCP operations with revision preconditions, preview for writes, redaction and bounded/paginated results; never give raw SQL/file handle access.
8. Explicit local SQLite/WAL safety policies, foreign key enforcement, integrity checks and backup/rebuild scenarios. WAL mode has a single writer and is unsuitable for shared network filesystems; **`synchronous=NORMAL` can lose durability after power failure**.
9. Treat **Stormline Asset Provenance Graph (SAPG)** as optional R&D requiring measured improvement over a conventional indexed dependency table and provenance records.

## Alternatives and rejection conditions

- **Path as asset identity:** reject; moving files would break references.
- **Content hash as asset identity:** reject; edits would replace identity, identical independent assets can share bytes and malicious input can collide.
- **SQLite as the only irreplaceable metadata store:** not ruled out, but requires robust backups, source-control strategy and independent cross-file recovery tests.
- **Only plain JSON sidecars:** baseline; query scalability and atomic move of sidecar + source need proof.
- **Hosted database / cloud mandatory:** reject zero-cost/local-first requirement.
- **Automatic identity remapping on conflict:** reject without audited, versioned, user-visible impact analysis.
- **Full custom graph database:** avoid until required and measured.

## Proof obligations before promotion
- Lock exact SQLite/BLAKE3 versions/licenses/provenance, compiler and OS compatibility.
- Document authoritative metadata/source file format with DATA-04 alignment and define cross-file DB reconciliation state machine.
- Measure rename/reimport preserving IDs and references, duplicate/conflict/missing ID cases and dependency cycles.
- Run crash injection, disk-full, WAL recovery, index-corruption rebuild, migration from N to N+1 and backup restore.
- Demonstrate security for project merges, untrusted metadata, SQL injection, large/cyclic graphs, MCP read/write permission checks, redaction.
- Record hardware/OS and p50/p95/p99 at 1k/100k/1m assets; test headless and web adapter strategy.
- Objective audit, no HIGH/CRITICAL, approved DoD/Scope and source SHA-256 fingerprints before executor activation.

## Consequences and status

Merging this ADR is **approval of the research artifact only**. It does not freeze a database, schema, license, serialization strategy, hardware limits or implementation. Issue #25 remains `BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`, `executor_ready=false`. Future code WOs need concrete files/APIs/tests before Zcode can build.
