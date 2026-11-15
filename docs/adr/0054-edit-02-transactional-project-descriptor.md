# ADR-0054 — Versioned Original Project Descriptor and Staged, Fail-Closed Project Transactions

**Status PROPOSED / NOT ADOPTED / NOT OWNER APPROVED** | 2026-11-15 | research [#256](https://github.com/KayzenRoot/stormline/issues/256) | WO NLE-P00-WO-002-EDIT-02 | code #69 OPEN/BLOCKED | BASE `e234f1054c55880eca01e9bbcbbb9117e6c737bc` | engine source license NLE-D009 OPEN.

## Context
Stormline's native editor needs to create four authoring modes and reopen existing projects without losing files or relying on proprietary third-party project formats. EDIT-01 and DATA-01, the **only formal dependencies**, are documentary proposals, not implemented. Future DATA-02 stable asset IDs, DATA-04 versioned scene serialization, project lifecycle and directory-security requirements have distinct owners. Project creation touches the user's disk and is data-loss/security-sensitive, so a human-readable manifest alone is insufficient.

## Proposed leading design, no implementation approval
Adopt **as a candidate** a deterministic human-diffable UTF-8 JSON project descriptor `stormline.project.json` with stable ProjectId, `schemaVersion` / `minimumReaderVersion`, engine compatibility, mode declaration, target capability profiles, approved template digest/provenance/license, optional dependency lock and DATA-01 mount intents. The named filename and format are **proposed not canonically selected**. The descriptor is a root index, NOT a replacement for DATA-02 asset metadata or DATA-04 scene format. All unknown required features or incompatible newer format => explicit read-only/open-deny, never guessed migration or silent file rewrite. Preserve unrecognized optional fields through deterministic roundtrip when safe.
 
For new projects, use **preview→stage→validate→commit** with idempotent transaction ID and DATA-01 root grant. Staging is private **sibling on the same local volume**, using handle-relative, no-follow creation and file count/size quotas; verify template digest/contents and mode-specific capability without executing scripts. Only commit into a **nonexistent destination** by OS/filesystem-supported atomic rename after appropriate file+directory flush, then publish recent-projects/asset references separately with expected-revision CAS. A rename or SQLite commit is **not automatically power-loss durable** on all OS/filesystems or atomic across network/cloud-sync providers; explicit compatibility and recovery proof required. On failure/quota/interrupt, preserve last-good state and quarantine incomplete staging, no destructive overwrite or blind cleanup.

Migration uses readable compatibility matrix, schema graph and DATA-04 owner transforms, copy-on-write immutable source backup/snapshot, dry-run diff, user approval, validation and rollback/roll-forward markers. Per-project single-active-writer lease with expected version and safe read-only second window; lock stale policy must defend split-brain and TOCTOU. Multi-process/multi-host correctness only if backend explicitly supports it: **SQLite WAL is local-host only on proper supported filesystem, not an implicit network share lock service**. Backup via hardlinks not assumed safe without copy-on-write guarantees.

Security: all paths/templates/manifests/untrusted import considered hostile; enforce DATA-01 OS handle-based relative path resolve, symlink/junction/reparse/device/hardlink policy, ZIP-slip/decompression/recursive format bounds, Unicode/Windows reserved and case-fold collision, root permission and no implicit network/template execution. AI/MCP uses same permissioned semantic public API as UI with preview/stage/validate/commit, no raw shell or arbitrary file/paid operations.

## Alternatives and tradeoffs
| Option | Advantage | Unacceptable limitation / result |
|---|---|---|
| Copy Godot `project.godot`, Unity `.meta` or Unreal `.uproject` as own native format | familiar | license/data coupling, engine-specific semantics, no original design; **reject as canonical format** |
| Plain YAML everywhere | comment-friendly | anchors, implicit typing and parser complexity, canonical/signing ambiguity; **not preferred** |
| Pure JSON/TOML hand edited without schema/revisions | easy | data loss, incompatible versions, refs and migrations unsafe; **reject alone** |
| One SQLite database owns all project source assets | transactional | poor human diff/version control and monolithic corruption lock-in; **reject as default canonical source** |
| Versioned deterministic descriptor, DATA-02 asset IDs, DATA-04 scenes and optional derived cache | original, source-control friendly, separated owners | needs careful multi-file commit and mismatch recovery; **leading PROPOSAL** |
| Unchecked copy-to-final followed by manifest write | simplest | partial visible projects after crash, overwrite risk; **reject** |
| Private staging + validate + idempotent rename/markers with recovery | avoids visible incomplete target where supported | OS/FS durability, Windows locks/network FS need tests; **leading PROPOSAL** |
| Automatically migrate every project on open | convenient | downgrade/destructive breakage and permission risk; **reject default** |
| Mandatory cloud/SQLite WAL multi-host management | shared state | cost, locking and network FS incompatibility; **reject as baseline** |
| Plugin post-create shell hooks or remote templates by default | extensible | RCE/SSRF/licensing and hidden expenses; **reject default**, future separate approval |

## Proof obligations before owner approval
Exact descriptor schema version and validation, ProjectId/AssetId ownership, source-controlled vs cache paths, four-mode capability defaults/DoD, template rights and hash ledger, project move/rename/ref integrity, Windows/macOS/Linux handle based path root security, Unicode cases, fault injection after **each transaction step** and verified file hashes upon restart, process crash vs OS power fail persistence, storage backend fsync/WAL settings, per-project lock/read-only semantics, legal license/tag/SBOM and rollback, project browser keyboard/a11y and AI/MCP authorization. Numeric throughput, p99, sizes and release/risk class TBD owner baseline. **No future migration, tools or project were actually run**; 128 tests FUTURE/NOT EXECUTED and all 80 coding WOs remain blocked. ADR inclusion does NOT activate code issue #69.
