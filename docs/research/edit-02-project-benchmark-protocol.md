# EDIT-02 — Reproducible Cross-Platform Project, VFS, Migration and Fault-Injection Benchmark Protocol

**P00 DESIGN ONLY 2026-11-15.** No native editor, file generator, project, SQLite, OS test VM or runtime benchmark executed. All 128 E02-T001..128 scenarios FUTURE/NOT EXECUTED; zero actual p50/p95/p99 or crash recovery proof.

## 1. Hypotheses (not measured)
H1: four modes can create valid native Stormline project skeletons with stable ID and capability profile offline without third-party binaries. H2: staged+validated commit on DATA-01 granted local filesystem avoids externally visible incomplete projects across process crashes, and the prior valid target is never overwritten. H3: real Windows/Linux/macOS path semantics, Unicode case/symlink/junction and archive attacks fail closed while legitimate user-granted paths work. H4: DATA-02 asset IDs survive rename/move, DATA-04 versioned schema upgrade with backup/rollback and fresh restart verifies hashes. H5: project manager/CLI/MCP share permissions and do not block UI, incur unwanted remote cost or leak personal paths. H6: optional SQLite cache and manifest parsers can be compared without assuming WAL multi-host FS or power-loss durability.

## 2. Immutable future run manifest
`ProjectBenchmarkManifestV1`: Git base/head and compiler binary hashes, owner-approved ADR schema and exact version, mode and target GFX/Web capabilities, local template digest/asset notices, descriptor canonical rules, DATA-01 VFS OS root permission and symlink policy, DATA-02 AssetId fixtures, DATA-04 migration graph and copy-on-write strategy, OS Windows/Linux/macOS version, filesystem NTFS/APFS/ext4/Btrfs or declared test target, local vs network mount and storage device durability model, SSD/NVMe/VM memory CPU temperature, security settings/antivirus/windowing where relevant, template file count/source bytes/dependency lock/hashes, 0/100/1000/10000 asset reference axes, synthetic rollback/recovery state, test seed/cancel/kill/fsync fault-point, buffer+disk quotas and expected transaction state, performance p50/p95/p99 with warmup and repeats, signed log redacted artifact, independent audit/rollback findings. No private end-user folders or third-party account keys in public evidence.

## 3. Reproducible workload matrix
| Fixture | Controlled axes, no performance promise | Required proof after real run |
|---|---|---|
| E02_CREATE_4 | 2D/2.5D/3D/Web original local first-party skeleton | all four descriptors valid, correct actual feature selection or honest unsupported |
| E02_TEMPLATE | 1/4/16 templates, pinned file hash and notices | offline provenance/declared rights and no script execution |
| E02_FILES | 0/100/1000/10000 synthetic assets and metadata refs | DATA-02 stable ref validation and peak CPU/RAM/storage |
| E02_MANIFEST | 1k/10k/100k lines or byte/complexity limits approved by owner later | parse/validation p50/p95/p99 and depth+size rejects |
| E02_STAGE | create into absent vs existing target, same vs cross volume | atomicity capability, no existing overwrite and consistent receipt |
| E02_CRASH | abort after preview/stage/file write/flush/rename/recent-list | nonmutating old tree, recover/quarantine, stage cleanup under consent |
| E02_POWER | explicit **owned** FS power-fault simulator or crash harness | distinguish visible atomic rename from durable commit, no blanket ACID claim |
| E02_RENAME | rename/move asset and project folder with changed path/casing | stable ProjectId and DATA-02 AssetId across dependency graph |
| E02_MIGRATE | N→N+1 and two steps with missing transform/backup failure | dry-run diff, immutable backup and rollback/rollforward verified hashes |
| E02_LOCK | two GUI instances and CLI/MCP concurrent writer | single writer with versioned CAS, secondary read-only and no stale lock theft |
| E02_ARCHIVE | ZIP/tar with safe and malicious paths/symlink/high compression | extraction quotas, fail closed and no outside writes |
| E02_PLAT | Windows NTFS, macOS APFS, Linux ext4/Btrfs, path edge cases | real handle-based secure path containment, mode-specific evidence |
| E02_ACCESS | keyboard+screen reader wizard/IME and permissions | accessible inline validation/status, no surprise filesystem modification |
| E02_DEP | offline pinned dependency lock vs unavailable/mismatch | deterministic plan, no unexpected remote download or script |
| E02_EXPORT | source snapshot excludes cache/secrets while preserving ids | verified manifest, license notice, no fabricated game build |
| E02_QUOTA | low disk space/permission revocation/antivirus file locked | failure receipt and no corrupt existing project, bounded retry |

Fixture counts are experimental **axes**, not supported capacity or SLO guarantees. Numeric commit/parse throughput, project asset limits and p99 targets require owner-approved hardware and baseline.

## 4. Controlled test process
1. **Authorization and isolation:** create disposable scratch root under test-owned VFS grant; never operate on real user project, system directory, network share or mounted cloud folder without explicit separate sandbox approval. Record clean baseline checksums, free space and OS capabilities.
2. **Correctness first:** run preview (no disk mutations), stage/validate/commit and fresh-restart open for all modes, compare complete file tree hashes, ProjectId and asset GUID graph, readable schema and template provenance. Code-level unit tests are insufficient without real filesystem.
3. **Crash injection:** controlled test process kill at each transaction phase and injected ENOSPC/rename/close/fsync error; re-open with new process, verify prior project untouched and orphan stage quarantine. For power-loss, use documented VM/filesystem fixture and clearly label emulation vs physical durability.
4. **Platform path security:** test Windows junction/reparse/ADS/UNC/reserved name/case, macOS Unicode normalization/symlink/race, Linux openat2 RESOLVE_BENEATH/NO_SYMLINKS plus mount and hardlink. Verify actual handle identity at commit; no string-only check.
5. **Dependency and asset:** simulate 1k/10k refs, rename/move/import/export, invalid/missing dependency and permission grants, measure closure/validation CPU/heap/disk. DATA-02 owns identity, DATA-04 owns serializer and migration, EDIT-02 only orchestrates.
6. **Measurement:** partition time for planning/schema parse, directory handle resolution, template instantiation, hash and validation, flush/rename/atomic marker, UI progress, reopen and repair. Pin cache warmup/cold stats, I/O counters, SSD filesystem writeback and repeated 20+ samples before meaningful tail claims; control background antivirus/indexing variation.
7. **Fail-safe thresholds and regression:** new code only with owner-approved max bytes/files/rename and acceptable p99, security and original project hashes. Any HIGH/CRITICAL data loss, path escape, wrong-license starter asset, concurrent writer corruption or untrusted script executes => stop, correction/regression and rollback before further WO. No license/threshold invented.
8. **Report:** signed redacted evidence with Git SHAs, OS/media/hardware, exact test commands, future/ran test counts, measurable latency/error histograms, crash stage artifact/hash, rebuild output, risk severity, independent objective pt-BR audit and checkpoint delta. No personal project paths or keys.

## 5. Reference-backed limitations and P00 truth
[SQLite WAL](https://www.sqlite.org/wal.html) is local-host only, not multi-host network filesystem coordination. [SQLite synchronous pragma](https://www.sqlite.org/pragma.html) WAL NORMAL can lose recent commits on power failure vs FULL uses more sync operations; not an automatic directory-level transaction. [Linux openat2](https://man7.org/linux/man-pages/man2/openat2.2.html) is Linux-specific; Windows [reparse handling](https://learn.microsoft.com/windows/win32/fileio/reparse-point-operations) differs. [Godot](https://docs.godotengine.org/en/stable/tutorials/editor/project_manager.html), [Unity asset GUID](https://docs.unity3d.com/jp/current/Manual/asset-database-contents.html) and [Unreal projects](https://dev.epicgames.com/documentation/pt-br/unreal-engine/working-with-projects-and-templates-in-unreal-engine) are architecture references, not integrated formats.

**No project created, schema migrated, filesystem path probed, archive extracted, CPU measured, real GUI launched, or power failure tested in P00.** All E02-T001..128 FUTURE/NOT EXECUTED. Only GitHub documentation CI counts as actual test.
