# ADR-0009 — VFS Namespace, Mounts and File System Security Policy

**Date:** 2026-11-14 | **Status:** PROPOSED / NOT APPROVED FOR ENGINE IMPLEMENTATION  
**Work Order:** NLE-P00-WO-002-DATA-01 | **Research issue:** #108 | **Future implementation issue:** #24

## Decision context

Stormline must provide safe project/engine/editor/runtime storage across Windows, Linux, macOS and future Web. The engine is intended to support user-generated projects and AI/MCP automation, so filesystem access is a high-value attack surface. No current C++ implementation exists; this is a documented architectural proposal.

## Proposed decision

1. **Own the VFS API and typed logical namespace** with explicit `VfsPathV1`, `MountDescriptorV1`, capabilities, read/write modes, quotas, typed errors and mount generations. Vendor libraries must be behind backend adapters.
2. **Default to read-only mounted packs** and restrict writes to workspace-scoped directories with allowlisted paths/operations. No ambient access to host personal files, absolute path names or external URLs.
3. Use **C++20 `std::filesystem` only as a trusted path/metadata baseline**, not as a security sandbox. Platform-native handle-based resolution must contain symlink/junction/race escapes. Fail closed if OS lacks a proven confinement path for an untrusted mount.
4. Evaluate **PhysicsFS (zlib)** as an archive/mount backend. Evaluate **libzip (BSD-3-Clause)** only where ZIP write/modify capabilities justify a separate dependency. No bundled library or version is approved yet.
5. Explicit overlay precedence and shadowing errors; mount IDs + generations in caches/handles. Writes must target the authorized mount, never an implicit first match.
6. Use staged, verifiable, rollback-capable writes and per-OS durability testing. A filesystem rename is not a universal atomic multi-file transaction.
7. Archive reads must enforce entry/count/size/ratio/time budgets, reject zip-slip, case/Unicode collisions, traversal and malformed entries; do not equate hash with authenticity.
8. AI/editor/CLI operations must use validated scoped API commands with auditability, no unrestricted `filesystem.*` MCP tool or raw OS path exposure.
9. The **Stormline Asset Mount Graph (SAMG)** is a research proposal, retained only if real comparisons demonstrate better correctness/diagnosis/performance than a simple mount table plus cache.
10. Exact license, versions, minimum OS support, native filesystem strategy and release class remain open until independent risk/benchmark/architecture audits.

## Alternatives considered

- **PhysicsFS as public API and sole security authority:** attractive ease, but library-specific search and symlink semantics could leak into SDK, and no tested sandbox proof exists.
- **libzip for all file operations:** handles ZIP archives, not complete VFS namespace or host filesystem permission boundaries.
- **Always untrusted native filesystem access:** too risky for user-generated projects and AI workflows; reject until safe confinement proven.
- **Always use `std::filesystem::canonical` then open path:** reject because path can change between validation and I/O.
- **Custom proprietary archive/compression format immediately:** avoid maintenance and unproven advantages; prefer benchmark and capability gaps first.
- **Cloud storage as default:** violates local-first/no-paid-provider intent; reject.
- **Writeable mounts selected implicitly by search order:** reject due to shadowing/write escalation.

## Proof obligations for future implementation approval

- Source lock and exact versions/licenses/CVEs/third-party notices; no data loss under failure tests.
- Cross-OS handle-based containment with symlink/junction/concurrent replacement tests and fail-closed unsupported OS behavior.
- Golden path and Unicode/case collision matrix; Windows reserved names/drive/UNC/ADS, Linux NUL/paths, macOS normalization and sensitive symlink tests.
- Mount shadowing, generation, unmount with live handles, cache invalidation, IO cancellation and quotas.
- Zip-slip/bomb/truncated/corrupt archive, memory/CPU budget and parser fuzzing.
- Crash-safe staged save and forced interruption/recovery fixtures, data integrity and no premature project mutation.
- Game/Editor/CLI/MCP/headless capability scope tests; no unrestricted file access.
- Real CPU/RAM/storage p50/p95/p99 workloads on named hardware and file systems; Web adapter separately accepted.

## Consequences and state semantics

This ADR may be merged as **approved planning documentation** while remaining `PROPOSED` for software. The existence of research issue #108 and implementation issue #24 is not authorization to code. Every future Zcode WO requires concrete source files, APIs, tests/benchmarks, approved Scope/DoD/ADR, and a fresh Context Lock. No claimed verified sandbox or performance until native tests exist.
