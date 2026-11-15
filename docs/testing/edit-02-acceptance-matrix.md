# EDIT-02 — Exactly 128 FUTURE Project Creation, Recovery and Security Acceptance Scenarios

**2026-11-15 | [research #256](https://github.com/KayzenRoot/stormline/issues/256) | WO NLE-P00-WO-002-EDIT-02 | coding #69 OPEN/BLOCKED.** IDs **E02-T001..E02-T128**: exactly **128 UNIQUE**, all **FUTURE / NOT EXECUTED**, **executed 0, passed 0, failed 0**. No editor binary, real project file, VFS code, template generator, SQLite database, OS fault-injection harness, exporter or migration runner currently exists. GitHub Docs Validation can only prove documentation and blocked registry.

## Future evidence/proof format
Each future test must report **exact source Git base/head build SHA**, approved ADR/Scope/DoD and risk class, project schema version and actual template digest/provenance/license, chosen parser/DB/FS libraries exact tags/SPDX/SBOM, OS/version/filesystem/media (NTFS/APFS/ext4/Btrfs, X11/Wayland if launcher UI), allowed DATA-01 root handle/permission, file tree canonical before/after hashes, ProjectId+DATA-02 AssetIds with move/rename dependency graph, transaction ID/phase/flush/rename/commit marker, injection point (process crash/OS-fault simulator only on dedicated fixture), power durability evidence with actual supported storage, recovered project on **fresh restart**, expected error, rollback and no lost preexisting data, measured CPU/heap/bytes/latency where applicable, CI artifacts and objective independent pt-BR audit. Errors and logs redacted, no real user project or private path disclosed.

**Acceptance requires actual filesystem state and hash/reference continuity**, not mock-only API success. Distinguish atomic visibility from power-loss durability; do not claim real power failure safe without hardware/FS-specific evidence. A single writer lock does not imply cross-host distributed transaction consistency. Each mode's feature profile must match implemented GFX/WORLD/TWO/Web capabilities or return an explicit unsupported error. Foreign Godot/Unity/Unreal converter is future separate scope, not automatic import test pass.

| ID | Test domain | Future verifiable assertion | Status |
|---|---|---|---|
## Wizard and project mode
| E02-T001 | Wizard and project mode | create native 2D project with validated feature profile | FUTURE / NOT EXECUTED |
| E02-T002 | Wizard and project mode | create 2.5D project with declared layer and unit profile | FUTURE / NOT EXECUTED |
| E02-T003 | Wizard and project mode | create 3D project with proper required graphics tier | FUTURE / NOT EXECUTED |
| E02-T004 | Wizard and project mode | create Web-target project with explicit browser capability report | FUTURE / NOT EXECUTED |
| E02-T005 | Wizard and project mode | wizard back/cancel before commit leaves no visible project | FUTURE / NOT EXECUTED |
| E02-T006 | Wizard and project mode | wizard unsupported mode refuses without output files | FUTURE / NOT EXECUTED |
| E02-T007 | Wizard and project mode | mode change regenerates only pending plan not committed data | FUTURE / NOT EXECUTED |
| E02-T008 | Wizard and project mode | wizard keyboard and accessibility announce errors and progress | FUTURE / NOT EXECUTED |
## Manifest schema and compatibility
| E02-T009 | Manifest schema and compatibility | new project descriptor valid deterministic UTF-8 roundtrip | FUTURE / NOT EXECUTED |
| E02-T010 | Manifest schema and compatibility | stable ProjectId independent of project folder path | FUTURE / NOT EXECUTED |
| E02-T011 | Manifest schema and compatibility | minimumReaderVersion prevents unsafe old editor write | FUTURE / NOT EXECUTED |
| E02-T012 | Manifest schema and compatibility | unknown required manifest feature fails closed or readonly | FUTURE / NOT EXECUTED |
| E02-T013 | Manifest schema and compatibility | unknown optional manifest field preserved safely across roundtrip | FUTURE / NOT EXECUTED |
| E02-T014 | Manifest schema and compatibility | duplicate JSON keys and numeric overflow rejected | FUTURE / NOT EXECUTED |
| E02-T015 | Manifest schema and compatibility | schema validation and semantic target feature check both required | FUTURE / NOT EXECUTED |
| E02-T016 | Manifest schema and compatibility | corrupt descriptor reports validation not auto rewrite | FUTURE / NOT EXECUTED |
## Template integrity and licensing
| E02-T017 | Template integrity and licensing | first-party original 2D template matches pinned digest | FUTURE / NOT EXECUTED |
| E02-T018 | Template integrity and licensing | first-party original 2.5D template matches approved mode | FUTURE / NOT EXECUTED |
| E02-T019 | Template integrity and licensing | first-party original 3D template has no imported third-party art | FUTURE / NOT EXECUTED |
| E02-T020 | Template integrity and licensing | first-party Web template states unsupported runtime features | FUTURE / NOT EXECUTED |
| E02-T021 | Template integrity and licensing | template tampering changes hash and halts creation | FUTURE / NOT EXECUTED |
| E02-T022 | Template integrity and licensing | template licensing and file provenance visible in preview | FUTURE / NOT EXECUTED |
| E02-T023 | Template integrity and licensing | external untrusted template executable hook never runs | FUTURE / NOT EXECUTED |
| E02-T024 | Template integrity and licensing | remote template download requires explicit permission and license | FUTURE / NOT EXECUTED |
## Creation transactions and idempotency
| E02-T025 | Creation transactions and idempotency | preview creation has zero filesystem side effects | FUTURE / NOT EXECUTED |
| E02-T026 | Creation transactions and idempotency | stage writes into private sibling under approved root | FUTURE / NOT EXECUTED |
| E02-T027 | Creation transactions and idempotency | target existing project cannot be overwritten | FUTURE / NOT EXECUTED |
| E02-T028 | Creation transactions and idempotency | stage file count and disk size remain bounded | FUTURE / NOT EXECUTED |
| E02-T029 | Creation transactions and idempotency | commit on same volume uses verified atomic rename or denies | FUTURE / NOT EXECUTED |
| E02-T030 | Creation transactions and idempotency | duplicate commit operation id returns same receipt no copy | FUTURE / NOT EXECUTED |
| E02-T031 | Creation transactions and idempotency | commit recent-project update does not invalidate valid project | FUTURE / NOT EXECUTED |
| E02-T032 | Creation transactions and idempotency | concurrent create into same name yields one target and conflict | FUTURE / NOT EXECUTED |
## Process crash and recovery
| E02-T033 | Process crash and recovery | crash before stage creation leaves no target | FUTURE / NOT EXECUTED |
| E02-T034 | Process crash and recovery | crash during staging leaves recoverable incomplete temp only | FUTURE / NOT EXECUTED |
| E02-T035 | Process crash and recovery | crash after stage validation before commit safe retry | FUTURE / NOT EXECUTED |
| E02-T036 | Process crash and recovery | crash during commit never exposes falsely valid descriptor | FUTURE / NOT EXECUTED |
| E02-T037 | Process crash and recovery | crash after commit before recent-list update repairs idempotently | FUTURE / NOT EXECUTED |
| E02-T038 | Process crash and recovery | restart finds staged data with valid owner marker only | FUTURE / NOT EXECUTED |
| E02-T039 | Process crash and recovery | rollback preserves preexisting target and prior project data | FUTURE / NOT EXECUTED |
| E02-T040 | Process crash and recovery | recovery from corrupt journal quarantines without arbitrary deletion | FUTURE / NOT EXECUTED |
## OS power loss and durability
| E02-T041 | OS power loss and durability | filesystem FULL flush barrier validated for chosen host | FUTURE / NOT EXECUTED |
| E02-T042 | OS power loss and durability | power failure after file flush before directory flush recovered | FUTURE / NOT EXECUTED |
| E02-T043 | OS power loss and durability | power loss during rename supports documented rollback or fail | FUTURE / NOT EXECUTED |
| E02-T044 | OS power loss and durability | Windows file sharing antivirus interference yields safe retry | FUTURE / NOT EXECUTED |
| E02-T045 | OS power loss and durability | macOS APFS sync assumptions verified on target filesystem | FUTURE / NOT EXECUTED |
| E02-T046 | OS power loss and durability | Linux ext4 or Btrfs durability verified with supported fault harness | FUTURE / NOT EXECUTED |
| E02-T047 | OS power loss and durability | SQLite WAL NORMAL power-loss limitation not misreported as guaranteed | FUTURE / NOT EXECUTED |
| E02-T048 | OS power loss and durability | network filesystem or cloud sync not assumed atomic across machines | FUTURE / NOT EXECUTED |
## VFS path traversal and symlinks
| E02-T049 | VFS path traversal and symlinks | dotdot and absolute path denied outside granted project root | FUTURE / NOT EXECUTED |
| E02-T050 | VFS path traversal and symlinks | Linux openat2 beneath no-symlink capability checked | FUTURE / NOT EXECUTED |
| E02-T051 | VFS path traversal and symlinks | Windows junction and reparse escape denied handle-relative | FUTURE / NOT EXECUTED |
| E02-T052 | VFS path traversal and symlinks | macOS symlink race protected using handle relative open | FUTURE / NOT EXECUTED |
| E02-T053 | VFS path traversal and symlinks | symlink swapped between preview and commit cannot redirect write | FUTURE / NOT EXECUTED |
| E02-T054 | VFS path traversal and symlinks | hardlink to external owned file rejected as policy requires | FUTURE / NOT EXECUTED |
| E02-T055 | VFS path traversal and symlinks | mountpoint or volume change invalidates stage commit | FUTURE / NOT EXECUTED |
| E02-T056 | VFS path traversal and symlinks | NUL control and URL encoded path traversal canonicalized safely | FUTURE / NOT EXECUTED |
## Cross-platform names and permissions
| E02-T057 | Cross-platform names and permissions | Windows reserved device and ADS names rejected | FUTURE / NOT EXECUTED |
| E02-T058 | Cross-platform names and permissions | case-insensitive duplicate filenames diagnosed on Windows | FUTURE / NOT EXECUTED |
| E02-T059 | Cross-platform names and permissions | macOS Unicode normalization NFC NFD collision diagnosed | FUTURE / NOT EXECUTED |
| E02-T060 | Cross-platform names and permissions | Linux case-sensitive rename preserves stable ProjectId | FUTURE / NOT EXECUTED |
| E02-T061 | Cross-platform names and permissions | long path and trailing dot or space tested on Windows | FUTURE / NOT EXECUTED |
| E02-T062 | Cross-platform names and permissions | read-only destination produces nonmutating error | FUTURE / NOT EXECUTED |
| E02-T063 | Cross-platform names and permissions | OS permission revoke during stage yields safe recoverable stop | FUTURE / NOT EXECUTED |
| E02-T064 | Cross-platform names and permissions | owner user ACL does not grant untrusted plugin global disk write | FUTURE / NOT EXECUTED |
## Asset identity and dependency graph
| E02-T065 | Asset identity and dependency graph | asset move preserves DATA-02 stable AssetId references | FUTURE / NOT EXECUTED |
| E02-T066 | Asset identity and dependency graph | asset rename changes path hint not asset identity | FUTURE / NOT EXECUTED |
| E02-T067 | Asset identity and dependency graph | project relocation preserves all referenced assets | FUTURE / NOT EXECUTED |
| E02-T068 | Asset identity and dependency graph | copy project generates new ProjectId only when cloning intended | FUTURE / NOT EXECUTED |
| E02-T069 | Asset identity and dependency graph | duplicate AssetId detected across source references | FUTURE / NOT EXECUTED |
| E02-T070 | Asset identity and dependency graph | dependency lock pin hash mismatch rejects unsafe package | FUTURE / NOT EXECUTED |
| E02-T071 | Asset identity and dependency graph | derived cache deletion retains source asset identity and rebuilds | FUTURE / NOT EXECUTED |
| E02-T072 | Asset identity and dependency graph | missing optional dependency reports degraded feature clearly | FUTURE / NOT EXECUTED |
## Migration and version recovery
| E02-T073 | Migration and version recovery | old compatible descriptor opens readonly before upgrade | FUTURE / NOT EXECUTED |
| E02-T074 | Migration and version recovery | unsupported future descriptor cannot silently downgrade | FUTURE / NOT EXECUTED |
| E02-T075 | Migration and version recovery | dry run shows semantic file and schema change plan | FUTURE / NOT EXECUTED |
| E02-T076 | Migration and version recovery | migration backup immutable snapshot verified before changes | FUTURE / NOT EXECUTED |
| E02-T077 | Migration and version recovery | migration step fails and restores original project files | FUTURE / NOT EXECUTED |
| E02-T078 | Migration and version recovery | schema multistep path missing refuses unknown transforms | FUTURE / NOT EXECUTED |
| E02-T079 | Migration and version recovery | roundtrip migration preserves unknown safe optional fields | FUTURE / NOT EXECUTED |
| E02-T080 | Migration and version recovery | rollforward after interrupted migration validates complete tree | FUTURE / NOT EXECUTED |
## Multi instance and concurrency
| E02-T081 | Multi instance and concurrency | two writers attempt same ProjectId and one is denied | FUTURE / NOT EXECUTED |
| E02-T082 | Multi instance and concurrency | read-only second window can inspect without writer lock | FUTURE / NOT EXECUTED |
| E02-T083 | Multi instance and concurrency | stale lease PID reuse cannot steal active writer | FUTURE / NOT EXECUTED |
| E02-T084 | Multi instance and concurrency | CAS conflict preserves both user changes for review | FUTURE / NOT EXECUTED |
| E02-T085 | Multi instance and concurrency | lock interruption process crash has safe recovery and owner proof | FUTURE / NOT EXECUTED |
| E02-T086 | Multi instance and concurrency | network share does not assume SQLite WAL cross-host correctness | FUTURE / NOT EXECUTED |
| E02-T087 | Multi instance and concurrency | project move during open invalidates stale root reference | FUTURE / NOT EXECUTED |
| E02-T088 | Multi instance and concurrency | workspace EDIT-01 save cannot override project data revision | FUTURE / NOT EXECUTED |
## Archive import and export safety
| E02-T089 | Archive import and export safety | ZIP-slip path outside allowed root rejected | FUTURE / NOT EXECUTED |
| E02-T090 | Archive import and export safety | tar symlink archive member never writes outside root | FUTURE / NOT EXECUTED |
| E02-T091 | Archive import and export safety | archive hardlink and device nodes rejected by policy | FUTURE / NOT EXECUTED |
| E02-T092 | Archive import and export safety | decompression bomb capped by total unpacked bytes | FUTURE / NOT EXECUTED |
| E02-T093 | Archive import and export safety | archive member count and path depth bounded | FUTURE / NOT EXECUTED |
| E02-T094 | Archive import and export safety | export source snapshot excludes ephemeral cache and secrets | FUTURE / NOT EXECUTED |
| E02-T095 | Archive import and export safety | foreign engine project import reports unsupported converter not false lossless | FUTURE / NOT EXECUTED |
| E02-T096 | Archive import and export safety | imported assets preserve provenance/license and no silent scripts | FUTURE / NOT EXECUTED |
## Capability integration boundaries
| E02-T097 | Capability integration boundaries | GFX unsupported feature tier blocks invalid 3D preset | FUTURE / NOT EXECUTED |
| E02-T098 | Capability integration boundaries | TWO 2D feature profile validated by 2D owner | FUTURE / NOT EXECUTED |
| E02-T099 | Capability integration boundaries | WORLD entity types not invented by project wizard | FUTURE / NOT EXECUTED |
| E02-T100 | Capability integration boundaries | DATA-04 scene serializer owns authored scene versions | FUTURE / NOT EXECUTED |
| E02-T101 | Capability integration boundaries | DATA-02 owns asset index not EDIT-02 duplicate registry | FUTURE / NOT EXECUTED |
| E02-T102 | Capability integration boundaries | EDIT-01 owns launcher shell and not project writes | FUTURE / NOT EXECUTED |
| E02-T103 | Capability integration boundaries | EDIT-07 owns runtime preview/cooking and not project descriptor | FUTURE / NOT EXECUTED |
| E02-T104 | Capability integration boundaries | DATA-05 game bundle export not implied by project source snapshot | FUTURE / NOT EXECUTED |
## Accessibility and AI/MCP permissions
| E02-T105 | Accessibility and AI/MCP permissions | keyboard-only wizard reaches review and cancel | FUTURE / NOT EXECUTED |
| E02-T106 | Accessibility and AI/MCP permissions | screen reader announces invalid project folder reason | FUTURE / NOT EXECUTED |
| E02-T107 | Accessibility and AI/MCP permissions | CJK IME and right-to-left display name preserved safely | FUTURE / NOT EXECUTED |
| E02-T108 | Accessibility and AI/MCP permissions | MCP create requires explicit VFS grant and user capability | FUTURE / NOT EXECUTED |
| E02-T109 | Accessibility and AI/MCP permissions | MCP validate preview no filesystem write | FUTURE / NOT EXECUTED |
| E02-T110 | Accessibility and AI/MCP permissions | agent cannot call arbitrary shell/template script | FUTURE / NOT EXECUTED |
| E02-T111 | Accessibility and AI/MCP permissions | destructive delete or overwrite request requires separate consent | FUTURE / NOT EXECUTED |
| E02-T112 | Accessibility and AI/MCP permissions | privacy logs omit personal root path and project tokens | FUTURE / NOT EXECUTED |
## Benchmark resource and scalability
| E02-T113 | Benchmark resource and scalability | 4-mode local create latency and disk bytes measured future | FUTURE / NOT EXECUTED |
| E02-T114 | Benchmark resource and scalability | 100 1000 and 10000 asset metadata fixture load future | FUTURE / NOT EXECUTED |
| E02-T115 | Benchmark resource and scalability | project open cold warm cache measured without false equivalence | FUTURE / NOT EXECUTED |
| E02-T116 | Benchmark resource and scalability | large dependency lock parse bounded CPU RAM future | FUTURE / NOT EXECUTED |
| E02-T117 | Benchmark resource and scalability | 100 forced abort restore cycles leave no leaked temp future | FUTURE / NOT EXECUTED |
| E02-T118 | Benchmark resource and scalability | three OS native VFS and permission paths measured future | FUTURE / NOT EXECUTED |
| E02-T119 | Benchmark resource and scalability | copy backup/migration disk space threshold approved in future | FUTURE / NOT EXECUTED |
| E02-T120 | Benchmark resource and scalability | p95 p99 and maximum storage budgets require owner baseline future | FUTURE / NOT EXECUTED |
## Governance and readiness
| E02-T121 | Governance and readiness | exactly 128 E02 IDs unique and all FUTURE | FUTURE / NOT EXECUTED |
| E02-T122 | Governance and readiness | EDIT-01 DATA-01 formal deps remain research only | FUTURE / NOT EXECUTED |
| E02-T123 | Governance and readiness | ADR-0054 remains PROPOSED no format adopted | FUTURE / NOT EXECUTED |
| E02-T124 | Governance and readiness | engine NLE-D009 license remains OPEN | FUTURE / NOT EXECUTED |
| E02-T125 | Governance and readiness | Docs Validation does not prove file IO or crash durability | FUTURE / NOT EXECUTED |
| E02-T126 | Governance and readiness | all 80 implementation Work Orders remain blocked | FUTURE / NOT EXECUTED |
| E02-T127 | Governance and readiness | no runtime migration or package download during P00 | FUTURE / NOT EXECUTED |
| E02-T128 | Governance and readiness | EDIT-03 research only after EDIT-02 final verified readback | FUTURE / NOT EXECUTED |

## Safe future adversarial and failure test protocol
- Perform only on **owned disposable filesystem fixture/VM/snapshot**, with explicit byte/file/time/cpu budget and test-only generated files; no real user projects or third-party executable templates, no public network targets.
- Inject process termination and emulated storage faults separately; **never intentionally cut power to production hardware** or assume simulating process crash proves power-failure durability.
- On every failure, compare hashes of old committed project, staging state, journal, final root and all asset references; verify recover/rollback after restart. Any permission/path escape, source corruption, unauthorized script, license violation or known HIGH/CRITICAL blocks code release.
- Cross-platform tests must actually exercise Windows reparse/junction/ADS, Linux handle-relative symlink policies and macOS normalization/filesystem, not infer from POSIX mock.
- 128 tests are FUTURE/NOT EXECUTED in P00, no parser/security/migration/integration/benchmark assertion of PASS.
