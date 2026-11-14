# WORLD-01 — Future ECS Identity, Lifecycle, Schema and Concurrency Test Matrix

**Research #159 | NLE-P00-WO-002-WORLD-01 | Future code issue #41 OPEN/BLOCKED.**  
**ALL 117 TEST CASES ARE FUTURE / NOT EXECUTED.** No ECS runtime, compiled C++/WASM, world state serialization, sanitizer, CPU benchmark, hot reload or editor has been run.

| Test ID | Future objective acceptance test | Evidence expected |
|---|---|---|
| IDN-001 | Create entity with unique GUID and live local handle | CPU |
| IDN-002 | Destroyed slot reuse increments generation before use | CPU |
| IDN-003 | Stale handle from old generation cannot read new entity | property |
| IDN-004 | World teardown and reinstantiate reject handle of old epoch | CPU |
| IDN-005 | Cloned world shares GUID only when contract allows and never handles | CPU |
| IDN-006 | Handle invalid zero sentinel cannot be allocated | unit |
| IDN-007 | Generation max wrap permanently retires slot no ABA | property |
| IDN-008 | Multiple free-list allocators deterministic under identical seed | replay |
| IDN-009 | GUID collision/duplicate imported entity fails typed | DATA02 |
| IDN-010 | Cross-project same GUID scoped and permission checked | security |
| IDN-011 | Unloaded GUID resolves UNLOADED not DELETED and no stale handle | stream |
| IDN-012 | Entity GUID save reload preserves logical identity but changes handle | DATA04 |
| IDN-013 | Slot/generation numeric raw never serialized or exposed as stable ID | audit |
| IDN-014 | World epoch stale pointers cannot be resurrected after rollback | fault |
| LIF-001 | Create sets ALIVE and component constructors exactly once | CPU |
| LIF-002 | Destroy request during query is deferred to safe boundary | concurrency |
| LIF-003 | Destroy twice reports typed idempotent receipt and no double free | unit |
| LIF-004 | Destroy component destructor exactly once on commit | ASan |
| LIF-005 | Component move and relocation releases old resource safely | ASan |
| LIF-006 | Observer reentry during destruction cannot mutate live iterator | fuzz |
| LIF-007 | Delete referenced child leaves WORLD-02 ownership policy separate | integration |
| LIF-008 | Tombstone prevents late GPU/PHYS/NET reader resurrection | integration |
| LIF-009 | Component destructor throw/fail safe policy explicit | fault |
| LIF-010 | World shutdown with pending jobs cancels then retires safely | TSan |
| LIF-011 | Memory pressure during destroy keeps registry consistent | fault |
| SCH-001 | Stable TypeId across compiler builds and plugin load order | portable |
| SCH-002 | TypeId collision with incompatible schema rejected | fuzz |
| SCH-003 | Schema version upgrade migration explicit or quarantine | DATA04 |
| SCH-004 | Schema checksum and field TypeId stable across rename | serialization |
| SCH-005 | Unknown component type on load never reinterprets binary bytes | security |
| SCH-006 | Invalid alignment/size/construct metadata rejected | fuzz |
| SCH-007 | C++ padding vtable and pointer state not memcpy serialized | audit |
| SCH-008 | Enum range/units and nested field bounds validated | unit |
| SCH-009 | Secret fields redacted in inspect and export rights | security |
| SCH-010 | Runtime-only components excluded from persistence and NET raw | contract |
| SCH-011 | Replicated authoritative subset cannot be set by client | security |
| SCH-012 | C++26 reflection optional compiles with fallback toolchain | compiler |
| SCH-013 | Source generated reflection has deterministic manifest across OS | build |
| SCH-014 | Component registration hot reload invalidates query schema caches | integration |
| SCH-015 | Plugin unload refuses live component destructor code invalidation | security |
| STO-001 | Archetype dense iteration returns matching component rows | CPU |
| STO-002 | Sparse-set insertion/removal preserves liveness invariants | CPU |
| STO-003 | Archetype transition add/remove relocates data once safely | ASan |
| STO-004 | Sparse stable-address component view still enforces borrow epoch | concurrency |
| STO-005 | Hot 3-component join iter correctness vs golden entity list | benchmark |
| STO-006 | High-churn toggles and structural moves have bounded memory | benchmark |
| STO-007 | Archetype explosion quota fail safe with typed error | stress |
| STO-008 | Sparse pagination grows only as allowed and cap enforced | stress |
| STO-009 | Memory allocator OOM rolls back atomic command batch | fault |
| STO-010 | Fragmentation after mass destroy measured not assumed zero | benchmark |
| STO-011 | Cache pages and empty archetype cost reported explicitly | benchmark |
| STO-012 | No third-party entity type exposed in stable public ABI | architecture |
| QUE-001 | Include/exclude/optional query returns exact matching entities | CPU |
| QUE-002 | Changed/added/removed query semantics defined and correct | unit |
| QUE-003 | Default iteration order unspecified and documented | contract |
| QUE-004 | Requested deterministic GUID order stable across replay | replay |
| QUE-005 | Query cache invalidates when type registered mid-run | CPU |
| QUE-006 | Query epoch invalidated after applied structural change | concurrency |
| QUE-007 | Old raw component reference never valid across compaction | ASan |
| QUE-008 | Read many queries coexist without write borrower | TSan |
| QUE-009 | Conflicting read/write query access rejected or sequenced | TSan |
| QUE-010 | Paged query response cannot leak foreign world data | security |
| QUE-011 | Large optional-only query bounded by pagination quota | stress |
| QUE-012 | Query changed tick wrap and missed frame correct | property |
| QUE-013 | Swap-remove storage never falsely promises stable order | CPU |
| QUE-014 | Query exit and buffer rollback clears read/write locks | fault |
| CMD-001 | Create/destroy commands issued concurrently buffer by issuer | TSan |
| CMD-002 | Command buffer merge uses deterministic tick and sequence policy | replay |
| CMD-003 | Create duplicate GUID in same tick rejects whole atomic unit | unit |
| CMD-004 | Destroy and update same handle ordered per policy | unit |
| CMD-005 | Add/remove same TypeId resolves declared order | CPU |
| CMD-006 | Command from wrong world epoch rejected before mutation | security |
| CMD-007 | Failing transaction never leaves half-committed live components | recovery |
| CMD-008 | Buffer exceeding bytes/count quota rejects without allocation bomb | security |
| CMD-009 | Concurrent job buffer observer cannot bypass commit barrier | TSan |
| CMD-010 | Command replay idempotency and epoch prevents double apply | replay |
| CMD-011 | One synchronization boundary instead of per-entity stall tracked | benchmark |
| CMD-012 | Read-only stage cannot register queries/systems unsafely | security |
| CMD-013 | OOM at commit rolls back or records atomic failure | fault |
| CMD-014 | Notification lifecycle receipt published only after commit | contract |
| CMD-015 | Entity create pending cannot be resolved as alive prematurely | unit |
| PER-001 | Save to DATA04 source retains stable GUID schema and values | DATA04 |
| PER-002 | Reload creates new ephemeral handles and remaps references | DATA04 |
| PER-003 | Journal crash recovery preserves last-good snapshot | recovery |
| PER-004 | Undo/redo entity destruction reconciles GUID mapping | DATA04 |
| PER-005 | Expected revision CAS conflicts across Editor/CLI/MCP | concurrency |
| PER-006 | Serialized data byte endian and pointer absence portable | serialization |
| PER-007 | Unknown source migration cannot silently discard fields | migration |
| PER-008 | Multi-world stream unload and reload never cross alias entities | WORLD03 |
| PER-009 | Prefab hierarchy changes owned WORLD02 not WORLD01 | architecture |
| PER-010 | Entity PHYS root motion not applied without authority ACK | integration |
| PER-011 | Network packets cannot impersonate server entity GUID authority | security |
| PER-012 | Save during structural changes takes safe consistent snapshot | concurrency |
| SYS-001 | Headless ECS spawns and runs queries with no graphics backend | headless |
| SYS-002 | Windows x64 native CPU sanitizers and memory smoke | hardware |
| SYS-003 | Linux x64 and ARM64 CPU sanitizer/ABI smoke | hardware |
| SYS-004 | macOS Apple Silicon CPU runtime memory smoke | hardware |
| SYS-005 | Web Emscripten/WASM CPU no GPU registry smoke | browser |
| SYS-006 | C++ standard compiler matrix no mandatory C++26 reflection | build |
| SYS-007 | MCP cross-project entity introspection denied | security |
| SYS-008 | MCP unknown schema/script registration denied | security |
| SYS-009 | Untrusted nested schema recursion maximum depth enforced | fuzz |
| SYS-010 | Untrusted massive component arrays/ranges bounded | fuzz |
| SYS-011 | Sensitive reflection fields not returned by query tool | security |
| SYS-012 | No high critical security issues in exact code diff | audit |
| BEN-001 | Ten hundred thousand million entities are synthetic load only | benchmark |
| BEN-002 | Table vs sparse query p50 p95 p99 and cache miss | benchmark |
| BEN-003 | Create destroy churn p50 p95 p99 per 1000 operations | benchmark |
| BEN-004 | Query views vs deterministic sorted snapshots cost | benchmark |
| BEN-005 | Archetype count vs peak resident bytes at controlled mix | benchmark |
| BEN-006 | Structural command buffer sync boundary wall latency | benchmark |
| BEN-007 | World clone/save reload typed GUID resolve latency | benchmark |
| BEN-008 | Entity generation overflow and huge sparse allocations safe | stress |
| BEN-009 | No claimed million entities per frame without actual proof | audit |
| BEN-010 | STLG prove-or-drop vs baseline stale-handle detection | R&D |
| BEN-011 | Flecs EnTT Bevy independent comparable original workload | reference |
| BEN-012 | Record code SHA/toolchain/cache/CPU and stable seed | protocol |

## Future acceptance obligations and quality gates
- Independent reference model/oracle of GUID/WorldEpoch/slot/generation and recycling; freeze handle bit layout and wrap/exhaustion policy before coding. Compare random seed create/destroy/reuse to oracle, no stale handle alias/ABA, correct cross-world denial, dynamic load/unload and future undo/reload.
- Schema/serialization tests: stable TypeId and schema migration, field rights/restrict authoring, no pointer or ABI memory serialized; test source version conflict and DATA-04 crash rollback. Headless CPU can validate without GPU, but it cannot certify future PHYS/NET/EDITOR integration without the actual service.
- Parallel job/structural commit: captured repeatable schedule with read/write footprints, deterministic command issuer ordering where required, TSan/ASan/UBSan or target-appropriate sanitizers (future), batch atomicity, lifecycle observer recursion, OOM cancellation and query iterator epoch invalidation. Tests must run on actual supported compilers/OS, not be marked passed by a document.
- Performance: compare identical synthetic original entity/component workloads across table/archetype, sparse and optional hybrid storage, including high-churn and query-heavy; count of entities is **an input**, not a claimed supported capacity. Capture p50/p95/p99 CPU and allocator/peak memory; actual numeric acceptance thresholds and platform minimum are **UNDECIDED**.
- Security: malicious schema/size/TypeId/migration, cross-project Editor/CLI/MCP permissions, untrusted query/filter/large world exhaustion, client-owned vs server component mutation, secrets redaction, unauthorized plugin script execution and stale pointer use.
- Actual code activation requires CORE-05+DATA-04 integrated/audited, approved ADR-0026, 1.0 Scope/DoD/requirements/ownership/ABI and fresh raw SHA-256 Context Lock. All 117 tests **NOT EXECUTED**.
