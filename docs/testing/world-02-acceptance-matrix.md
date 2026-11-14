# WORLD-02 — Future Scene Hierarchy, Prefab Propagation and Undo/Redo Acceptance Matrix

**Research #162 | WO NLE-P00-WO-002-WORLD-02 | Future code #42 OPEN/BLOCKED**.  
**ALL 122 CASES BELOW ARE FUTURE / NOT EXECUTED.** There is no implemented prefab editor, scene graph, serialization, undo journal, ECS runtime or cross-platform benchmark.

| ID | Future acceptance scenario | Future evidence |
|---|---|---|
| IDN-001 | Scene node rename preserves stable NodeGuid and refs | CPU |
| IDN-002 | Node reparent keeps source identity and changes only parent link | CPU |
| IDN-003 | Copy prefab instance gets new InstanceId and mapped children | CPU |
| IDN-004 | Two instances of same source cannot share live ECS Handle | integration |
| IDN-005 | Persistent EntityGuid map remaps on clone without collision | WORLD01 |
| IDN-006 | Duplicate source NodeGuid import fails or scoped remaps | fuzz |
| IDN-007 | Asset name/path not sole identity during file moves | DATA02 |
| IDN-008 | Cross-scene reference loading returns typed UNLOADED | WORLD03 |
| IDN-009 | Cross-project prefab source ID rights denied | security |
| IDN-010 | Source prefab deleted does not silently unlink instances | fault |
| IDN-011 | Missing child reference yields conflict with original provenance | recovery |
| HIE-001 | One parent per structural node invariant | unit |
| HIE-002 | Self parent forbidden | unit |
| HIE-003 | Ancestor reparent creates cycle and is rejected atomically | property |
| HIE-004 | Multiple roots handled by declared scene root policy | unit |
| HIE-005 | Stable sibling order preserved on save/reopen | DATA04 |
| HIE-006 | Large flat scene traverses iteratively without stack overflow | stress |
| HIE-007 | Extremely deep tree rejects depth quota | fuzz |
| HIE-008 | Old parent has child removed after reparent commit | unit |
| HIE-009 | Graph snapshot cannot expose halfway hierarchy move | concurrency |
| HIE-010 | Component parent relation owned WORLD02 not WORLD01 storage | architecture |
| HIE-011 | Child alive while parent destroyed follows owner policy | integration |
| HIE-012 | Multi-root imported scene preserves namespaces | import |
| TRF-001 | KEEP_LOCAL retains local transform exact on reparent | math |
| TRF-002 | KEEP_WORLD retains world affine matrix within tolerance | math |
| TRF-003 | KEEP_WORLD singular parent inverse typed failure | math |
| TRF-004 | Sheared transform nonrepresentable in TRS rejected or matrix | math |
| TRF-005 | Negative mirrored scale preserves handedness and winding | math |
| TRF-006 | 2D and 3D pivot hierarchy conversion correct | math |
| TRF-007 | Far 64bit origin relative position stable under camera pan | GFX |
| TRF-008 | Nonfinite position rotation scale invalid before commit | fuzz |
| TRF-009 | Reparent under physics control requests owner ack | PHYS |
| TRF-010 | Prefab variant local transform preserved after base rebase | unit |
| TRF-011 | Partial lazy-loaded parent transform not inferred zero | stream |
| TRF-012 | World update invalidates descendant transform epochs | integration |
| VAR-001 | Base template default fills non-overridden instance field | unit |
| VAR-002 | Base edit propagates only to non-overridden instance field | property |
| VAR-003 | Local override survives unrelated base edit | unit |
| VAR-004 | Local override survives simultaneous same-field base edit with conflict | merge |
| VAR-005 | Variant inherited value applied before instance override | unit |
| VAR-006 | Nested child prefab own source link survives parent edit | unit |
| VAR-007 | Nested A to B to A prefab references rejected before expansion | fuzz |
| VAR-008 | Variant self-parent cycle rejected | fuzz |
| VAR-009 | Variant 3 level precedence deterministic replay | replay |
| VAR-010 | Base removes referenced node produces typed orphan conflict | merge |
| VAR-011 | Base adds new node and instance gains it without duplicate | unit |
| VAR-012 | Base adds new component without clobbering local fields | unit |
| VAR-013 | Base removes component with local modified field conflicts | merge |
| VAR-014 | Override set can be explicitly reverted to latest base | unit |
| VAR-015 | Apply selected override to base requires authorized owner | security |
| VAR-016 | Apply all to wrong nested source denied by scope | security |
| VAR-017 | Structural move conflicts with competing child move | merge |
| VAR-018 | Sibling reorder uses stable NodeIds not integer indexes only | unit |
| VAR-019 | Tombstone remove remains across subsequent base versions | unit |
| VAR-020 | Prefab structural patch on missing source node resolves safely | fault |
| VAR-021 | Variant expansion quotas and depth limits enforced | stress |
| VAR-022 | Breaking link requires dry-run and explicit approval | security |
| MRG-001 | Three way merge base ours theirs typed property conflict exact | CPU |
| MRG-002 | Non-overlapping base and local edits merge without conflict | CPU |
| MRG-003 | Same field same proposed value idempotent merge | CPU |
| MRG-004 | Type migration of base+variant incompatible fails typed | migration |
| MRG-005 | Three-way merge source revision change restarts CAS validation | concurrency |
| MRG-006 | Unordered worker scheduling does not alter rebase receipts | replay |
| MRG-007 | Deleted node reference mapped or reported not silently dropped | integrity |
| MRG-008 | Conflicting array reorder uses identity and stable order | property |
| MRG-009 | Change to base causes bounded affected-instance fanout | budget |
| MRG-010 | Unchanged instances not rewritten needlessly | perf |
| MRG-011 | Incremental rebase result equals full rebuild oracle | R&D |
| MRG-012 | Repeated rebase of same revision is idempotent | replay |
| TXN-001 | Editor stage preview does not mutate live or durable scene | unit |
| TXN-002 | Validate before source commit checks graph, rights and quotas | security |
| TXN-003 | DATA04 commit CAS conflict causes no clobber | concurrency |
| TXN-004 | Crash between journal and runtime ECS publish recovers | recovery |
| TXN-005 | Runtime outbox replay idempotently applies committed changes | recovery |
| TXN-006 | Undo base edit preserves newer unrelated instance overrides | DATA04 |
| TXN-007 | Redo on changed base version revalidates conflicts | DATA04 |
| TXN-008 | Undo of reparent restores parent/sibling order and world pose | math |
| TXN-009 | Copy-paste prefab instance undo cleans its entity mapping | WORLD01 |
| TXN-010 | Partial runtime publish never claims complete scene revision | safety |
| TXN-011 | Cancelled staged edit leaves source and runtime last-good | fault |
| TXN-012 | Hot-reload source invalidates stale cooked scene snapshot | DATA05 |
| TXN-013 | Concurrent editor CLI MCP same source revision CAS conflict | security |
| TXN-014 | Memory OOM during expansion reports failure and rolls back | fault |
| INT-001 | WORLD01 GUID and ephemeral generational handle never serialized | integration |
| INT-002 | WORLD01 deferred create/destroy barrier maps instance child IDs | integration |
| INT-003 | DATA02 asset rights and provenance retained across nested import | integration |
| INT-004 | DATA04 migration of source schema preserves node stable IDs | integration |
| INT-005 | WORLD03 streamed unloaded child has typed readiness | integration |
| INT-006 | TWO02 tile maps as prefab children retain tile asset refs | integration |
| INT-007 | TWO03 animation track targets stable source IDs after edit | integration |
| INT-008 | TWO04 hybrid anchor continues to point to moved scene node | integration |
| INT-009 | GFX visibility consumes committed revision not half applied | integration |
| INT-010 | PHYS collision scene authority acknowledges rebuild cutover | integration |
| INT-011 | NET clients cannot control server-owned components via prefab | security |
| INT-012 | Headless server can instantiate without editor/GPU | headless |
| INT-013 | Windows native scene import and serialization smoke | hardware |
| INT-014 | Linux native scene import and serialization smoke | hardware |
| INT-015 | macOS Apple Silicon scene import and serialization smoke | hardware |
| INT-016 | Browser WebAssembly headless scene resolve smoke | browser |
| SEC-001 | Malicious prefab dependency cycle denied before allocating entities | fuzz |
| SEC-002 | Untrusted deep nested expansion quota enforced | fuzz |
| SEC-003 | Untrusted source path/URL traversal denied via DATA03 | security |
| SEC-004 | Arbitrary script/expression component in prefab blocked | security |
| SEC-005 | Cross-project asset reference and source view denied | security |
| SEC-006 | MCP prefab edit requires project and asset role | security |
| SEC-007 | Unauthorized apply/revert override to base asset denied | security |
| SEC-008 | Sensitive component field redacted in scene preview | security |
| SEC-009 | Huge structural patches and member count bounded | fuzz |
| SEC-010 | Source hash mismatch and corrupt snapshot fail closed | integrity |
| SEC-011 | OpenUSD TOST1 license versus Apache2 verified for exact release | license |
| SEC-012 | O3DE core dual and transitive Qt/other terms reviewed | license |
| SEC-013 | Godot MIT and Unity proprietary references not vendored | license |
| BEN-001 | One thousand to million instances are stress inputs not guarantees | stress |
| BEN-002 | One hundred thousand node deep and wide variants budget measured | benchmark |
| BEN-003 | Base edit fanout cost p50 p95 p99 and bytes written | benchmark |
| BEN-004 | Full rebuild versus incremental SIOP result and CPU cost | R&D |
| BEN-005 | Undo/redo journal fsync latency and exact state restore | benchmark |
| BEN-006 | Save reopen cold/warm import load headless p95 | benchmark |
| BEN-007 | Transform reparent costs versus depth and sibling count | benchmark |
| BEN-008 | Prefab memory instances vs shared template dedup measured | benchmark |
| BEN-009 | Multi-platform Win Linux macOS Web serializer parity | benchmark |
| BEN-010 | No invented FPS superiority or prefab throughput claims | audit |

## Proposed real-code acceptance gates, not passed
- Independently authored rights-cleared original scene fixtures: one player scene, multiple nested weapon prefabs, variant behaviors, cross-scene asset links, stable hierarchy IDs, duplicated instances, 2D/2.5D/3D transforms, deleted base nodes, concurrent Editor/CLI/MCP overrides, an original 1k instance small scene and larger synthetic stress input, plus corrupted untrusted graph cases.
- CPU oracle for stable NodeGuid and parent forest vs separate prefab dependency DAG, no cycles, no accidental EntityGuid alias, correct KEEP_LOCAL/KEEP_WORLD under affine transforms; runtime needs WORLD-01 + DATA-02 and validated CORE-05 implementation before these cases can pass.
- Fixture for base→variant→nested-instance field-level propagation and 3-way base/ours/theirs conflict; check transparent preservation of local overrides, type changes and node deletion, deterministic structural list ordering and undo/redo with real DATA-04 recovery. No pass based on markdown examples.
- Actual native Windows/Linux/macOS and Web/WASM headless serializer/integration tests, permissions/secret/migration/graph-fuzz, CPU/memory and file I/O p50/p95/p99. Numerical bounds/hardware/DoD not yet approved. No claim that 1 million instances is supported just because used as synthetic load.
- Independent source license rights/versions Godot MIT, Unity proprietary (no copying), OpenUSD Tomorrow Open Source Technology License 1.0+third parties and O3DE Apache-2.0 OR MIT+third parties when adopted later. **No imported vendor code/assets now**.
