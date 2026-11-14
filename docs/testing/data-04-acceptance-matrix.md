# DATA-04 — Future Serialization, Migration, Diff and Security Acceptance Matrix

**WO:** NLE-P00-WO-002-DATA-04 | **Research:** #117 | **State:** TESTS SPECIFIED, NONE EXECUTED.
Each scenario needs exact source SHA, fixture digest, schema revision, OS/runtime build, expected semantic or numeric tolerances, real pass/fail evidence and regression tracking.

| ID | Risk | Future fixture | Required proof |
|---|---|---|---|
| SER-001 | STANDARD | 2D layered scene, ordered sprites, entity IDs, authoring metadata | semantic save/load/save equivalent and preserved order/IDs |
| SER-002 | STANDARD | 2.5D mixed sprite/mesh, lighting refs | cross-dimension typed scene hierarchy and references survive |
| SER-003 | STANDARD | 3D transform, prefab, PBR/material/animation references | fields preserve CORE-05 units/precision and DATA-02 references |
| SER-004 | ELEVATED | unknown optional plugin component after open/save | bounded opaque fields survive, no execution/false validation |
| SER-005 | ELEVATED | unknown required plugin component | fail closed/read-only, no destructive silent stripping |
| SER-006 | ELEVATED | duplicate entity/component IDs, missing AssetId, invalid parent cycles | no partial mutation, stable actionable errors |
| SER-007 | STANDARD | order-sensitive children vs orderless maps | canonical writer stable while gameplay ordering remains correct |
| SER-008 | ELEVATED | invalid UTF-8, duplicate keys, NaN/Inf, -0, overflow, huge 64-bit IDs | reject or explicit exact normalization; string ID roundtrip |
| SER-009 | STANDARD | RFC 8785 canonicalization vectors and extended Unicode keys | actual JCS conformance or clearly scoped non-JCS algorithm |
| SER-010 | ELEVATED | N->N+1 migration, old plugin field, user metadata and asset ref | dry-run/receipt/loss report and old-good restore option |
| SER-011 | ELEVATED | unsupported N+1->N downgrade | explicit rejection with original file preserved |
| SER-012 | ELEVATED | migration interrupted at every stage, repeated recovery | idempotent replay/restore, no acknowledged partial scene |
| SER-013 | ELEVATED | disk full, denied VFS, missing backup or stale registry | no data loss, bounded temp, diagnostic and recovery |
| SER-014 | ELEVATED | two author edits on distinct stable-ID fields | correct three-way merge no spurious conflict |
| SER-015 | ELEVATED | human and AI change same field/hierarchy parent concurrently | conflict report and explicit resolution, no last-writer-wins |
| SER-016 | ELEVATED | repeated patch and undo with stale revision | idempotent retry; no unrelated edit removed |
| SER-017 | ELEVATED | hostile scene: million nesting/alias/long string/reference explosion | bounded resource quotas, error without crash/OOM |
| SER-018 | ELEVATED | MCP unauthorized patch/migrate/absolute path/prompt payload | denied without side effects/leaks; text treated as data |
| SER-019 | STANDARD | Windows/Linux/macOS arm64, Intel feasibility, headless and Web | compatible source semantics, unsupported adapter explicit |
| SER-020 | STANDARD | 1k/100k/1m entities, text and candidate binary codecs | p50/p95/p99, peak RSS, load/save/diff/merge, size with reproducible corpus |

## Test protocol and evidence conditions
1. **Golden fixtures:** original or licensed sample scenes with stable IDs, mixed 2D/2.5D/3D components, plugins, unknown fields, migrations and carefully specified numeric equality/tolerance. Persist input/output digests by algorithm and version.
2. **Property/fuzz:** malformed JSON and schema, nested depth/size quotas, duplicate keys/IDs, transforms at min/max finite numeric edges, parent/reference cycles and unknown plugin blobs. Use fuzzing and sanitizers on actual code only.
3. **Durability fault injection:** kill/cancel/disk full/permission revoke at each journal phase; verify both source and registry recovery. Multi-file atomicity must be demonstrated through recovery, not asserted from filesystem rename.
4. **Concurrency:** same-base edits, stale revisions, patch idempotency, conflict resolution, undo with concurrent edits and privileged MCP denial. Preserve old-good revision and audit.
5. **Cross-platform:** C++/headless tools on target native OS, Mac Apple Silicon, proposed Intel feasibility and explicit Web adapter. Host-supported JSON libraries may have different float/string semantics; include exact golden comparison.
6. **Benchmarks:** same scene content and limits for JSON parser/writer, FlatBuffers, Protobuf, Cap'n Proto and owned binary candidate. Include compiler flags, library tag/commit, CPU, OS, sample count, cold/warm caches, RSS and p50/p95/p99. No speed claim without results.
7. **License/supply chain:** pin tested dependency versions and transitive notices, SBOM and open-source policy; generated schema compiler output rights and CVE policies checked before shipping.
8. **CI:** free public GitHub Actions docs-validation remains the only existing test. Later implementation checks must have real commands, artifacts and platform availability; no invented passed status.

**Current:** SER-001..020 NOT RUN. No serializer, migration, compiler, actual test fixture, deployed runtime or benchmark exists.
