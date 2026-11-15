# AI-02 — Exactly 128 FUTURE Acceptance Tests (A02-T001..A02-T128)

**2026-11-15 | P00 FUTURE DESIGN ONLY | [research #285](https://github.com/KayzenRoot/stormline/issues/285) | NLE-P00-WO-002-AI-02 | code #76 OPEN/BLOCKED.** **128 unique IDs, 0 PASSED, 0 FAILED, all FUTURE / NOT EXECUTED.** These obligations are not executed code/CI tests.

## Evidence, oracle and dependencies
At future execution capture exact engine/owner/schema/index/backend SHAs and license, DATA-02 ProjectId/AssetId/RegistrySnapshotV1/AssetRevision, AI-01 CommandInvocation and principal/grant, DATA-04 source revision, WORLD-02 scene/prefab IDs, GAME-02 source map, index generation/source owner watermark/ACL, tokenizer/Unicode/rank version, budget, OS/CPU/RAM/SSD, seed, owner readback and injected fault. Ground truth is independent canonical owner scan, NEVER the index compared with itself. Rank with labeled synthetic rights-cleared corpus; report recall@k/MRR/nDCG and query cost separately. Missing owner adapter yields PARTIAL/UNSUPPORTED, never invented full coverage.

Groups of 16: G1 command/owner, G2 incremental/graph, G3 freshness/recovery, G4 lexical/ranking, G5 security/ACL/privacy, G6 budget/context/cursor, G7 SQLite/FTS/WAL/license/sandbox, G8 platforms/benchmark/acceptance.

## Complete future matrix
| Test ID | Group | Future scenario/oracle | Required future evidence | Status |
|---|---|---|---|---|
| A02-T001 | COMMAND-OWNER | AI-01 query requires verified read capability and ProjectId | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G1 | FUTURE / NOT EXECUTED |
| A02-T002 | COMMAND-OWNER | Editor button and CLI map same AI-01 query CommandId | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G1 | FUTURE / NOT EXECUTED |
| A02-T003 | COMMAND-OWNER | MCP maps same owner handler with no elevated arguments | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G1 | FUTURE / NOT EXECUTED |
| A02-T004 | COMMAND-OWNER | Descriptor exposes query schema version and target availability | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G1 | FUTURE / NOT EXECUTED |
| A02-T005 | COMMAND-OWNER | Unknown command/version fails closed | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G1 | FUTURE / NOT EXECUTED |
| A02-T006 | COMMAND-OWNER | Exact AssetId resolves DATA-02 rather than name/path | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G1 | FUTURE / NOT EXECUTED |
| A02-T007 | COMMAND-OWNER | Scene/prefab query resolves stable WORLD-02 ID | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G1 | FUTURE / NOT EXECUTED |
| A02-T008 | COMMAND-OWNER | Script symbol refers to GAME-02 module and revision | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G1 | FUTURE / NOT EXECUTED |
| A02-T009 | COMMAND-OWNER | Document result has source owner revision locator | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G1 | FUTURE / NOT EXECUTED |
| A02-T010 | COMMAND-OWNER | Schema result has owner schema ID and version | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G1 | FUTURE / NOT EXECUTED |
| A02-T011 | COMMAND-OWNER | Unavailable source kind has explicit partial coverage | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G1 | FUTURE / NOT EXECUTED |
| A02-T012 | COMMAND-OWNER | Index health is scoped and reports owner watermarks | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G1 | FUTURE / NOT EXECUTED |
| A02-T013 | COMMAND-OWNER | Index rebuild maintenance requires distinct privilege | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G1 | FUTURE / NOT EXECUTED |
| A02-T014 | COMMAND-OWNER | Query never writes project canonical source or journal | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G1 | FUTURE / NOT EXECUTED |
| A02-T015 | COMMAND-OWNER | CLI and editor produce same IDs on pinned generation | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G1 | FUTURE / NOT EXECUTED |
| A02-T016 | COMMAND-OWNER | Prompt injection in content cannot alter command grants | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G1 | FUTURE / NOT EXECUTED |
| A02-T017 | INCREMENTAL-GRAPH | Cold index built from verified canonical RegistrySnapshot | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G2 | FUTURE / NOT EXECUTED |
| A02-T018 | INCREMENTAL-GRAPH | Index generation includes schema/tokenizer/source versions | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G2 | FUTURE / NOT EXECUTED |
| A02-T019 | INCREMENTAL-GRAPH | Only owner SOURCE_COMMITTED receipt advances source watermark | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G2 | FUTURE / NOT EXECUTED |
| A02-T020 | INCREMENTAL-GRAPH | Filesystem watcher hint cannot publish uncommitted source | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G2 | FUTURE / NOT EXECUTED |
| A02-T021 | INCREMENTAL-GRAPH | Single metadata update only invalidates impacted entries | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G2 | FUTURE / NOT EXECUTED |
| A02-T022 | INCREMENTAL-GRAPH | Rename preserves AssetId and references | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G2 | FUTURE / NOT EXECUTED |
| A02-T023 | INCREMENTAL-GRAPH | Reimport changes revision and retains logical AssetId | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G2 | FUTURE / NOT EXECUTED |
| A02-T024 | INCREMENTAL-GRAPH | Duplicate mints distinct AssetId for equal bytes | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G2 | FUTURE / NOT EXECUTED |
| A02-T025 | INCREMENTAL-GRAPH | Tombstone removes FTS postings and snippets | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G2 | FUTURE / NOT EXECUTED |
| A02-T026 | INCREMENTAL-GRAPH | Dependency cycles preserve edges without infinite traversal | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G2 | FUTURE / NOT EXECUTED |
| A02-T027 | INCREMENTAL-GRAPH | Reverse dependency invalidation caps fanout and time | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G2 | FUTURE / NOT EXECUTED |
| A02-T028 | INCREMENTAL-GRAPH | Burst duplicate OperationId coalesced idempotently | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G2 | FUTURE / NOT EXECUTED |
| A02-T029 | INCREMENTAL-GRAPH | READY published only after index integrity/readback | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G2 | FUTURE / NOT EXECUTED |
| A02-T030 | INCREMENTAL-GRAPH | Failed derived update retains verified last-good generation | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G2 | FUTURE / NOT EXECUTED |
| A02-T031 | INCREMENTAL-GRAPH | Tokenizer schema change triggers rebuild | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G2 | FUTURE / NOT EXECUTED |
| A02-T032 | INCREMENTAL-GRAPH | Cold rebuild and incremental index converge to same results | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G2 | FUTURE / NOT EXECUTED |
| A02-T033 | FRESHNESS-RECOVERY | Owner source revision vector distinguishes separate owner epochs | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G3 | FUTURE / NOT EXECUTED |
| A02-T034 | FRESHNESS-RECOVERY | REQUIRE_AT_LEAST source returns current or STALE | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G3 | FUTURE / NOT EXECUTED |
| A02-T035 | FRESHNESS-RECOVERY | SNAPSHOT_EXACT rejects mixed source revisions | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G3 | FUTURE / NOT EXECUTED |
| A02-T036 | FRESHNESS-RECOVERY | ALLOW_STALE shows owner watermark and coverage | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G3 | FUTURE / NOT EXECUTED |
| A02-T037 | FRESHNESS-RECOVERY | No false ACID claim across source/index/runtime | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G3 | FUTURE / NOT EXECUTED |
| A02-T038 | FRESHNESS-RECOVERY | Read-your-writes honors source fence or STALE | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G3 | FUTURE / NOT EXECUTED |
| A02-T039 | FRESHNESS-RECOVERY | Committed source with pending index yields proper state | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G3 | FUTURE / NOT EXECUTED |
| A02-T040 | FRESHNESS-RECOVERY | Crash before index update repairs from owner receipt | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G3 | FUTURE / NOT EXECUTED |
| A02-T041 | FRESHNESS-RECOVERY | Owner sequence gap forces rebuild | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G3 | FUTURE / NOT EXECUTED |
| A02-T042 | FRESHNESS-RECOVERY | Deleted owner source never hydrated as current | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G3 | FUTURE / NOT EXECUTED |
| A02-T043 | FRESHNESS-RECOVERY | Expired generation snapshot rejects cursor | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G3 | FUTURE / NOT EXECUTED |
| A02-T044 | FRESHNESS-RECOVERY | FTS external content integrity discrepancy detected | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G3 | FUTURE / NOT EXECUTED |
| A02-T045 | FRESHNESS-RECOVERY | Existing content backfilled when triggers installed | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G3 | FUTURE / NOT EXECUTED |
| A02-T046 | FRESHNESS-RECOVERY | FTS contentless-delete uses supported SQLite version | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G3 | FUTURE / NOT EXECUTED |
| A02-T047 | FRESHNESS-RECOVERY | Long WAL reader checkpoint bounded or quota error | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G3 | FUTURE / NOT EXECUTED |
| A02-T048 | FRESHNESS-RECOVERY | Rebuild never edits canonical DATA-02/04 state | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G3 | FUTURE / NOT EXECUTED |
| A02-T049 | TEXT-RELEVANCE | Exact typed ID ranked and filtered correctly | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G4 | FUTURE / NOT EXECUTED |
| A02-T050 | TEXT-RELEVANCE | Portuguese accents follow declared tokenizer policy | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G4 | FUTURE / NOT EXECUTED |
| A02-T051 | TEXT-RELEVANCE | Case and Unicode normalization pinned across OS | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G4 | FUTURE / NOT EXECUTED |
| A02-T052 | TEXT-RELEVANCE | RTL source titles return valid bounded excerpts | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G4 | FUTURE / NOT EXECUTED |
| A02-T053 | TEXT-RELEVANCE | CJK tokenization returns expected matches or limitation | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G4 | FUTURE / NOT EXECUTED |
| A02-T054 | TEXT-RELEVANCE | Emoji/combining sequence source spans remain valid | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G4 | FUTURE / NOT EXECUTED |
| A02-T055 | TEXT-RELEVANCE | Trigram one/two character limit has truthful fallback | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G4 | FUTURE / NOT EXECUTED |
| A02-T056 | TEXT-RELEVANCE | Code underscore namespace and punctuation tokenization | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G4 | FUTURE / NOT EXECUTED |
| A02-T057 | TEXT-RELEVANCE | Graph EdgeKind and revision filtering before traversal | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G4 | FUTURE / NOT EXECUTED |
| A02-T058 | TEXT-RELEVANCE | Graph cycle visited set and partial limit receipt | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G4 | FUTURE / NOT EXECUTED |
| A02-T059 | TEXT-RELEVANCE | Combined tag/kind/revision/text filters are conjunctive | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G4 | FUTURE / NOT EXECUTED |
| A02-T060 | TEXT-RELEVANCE | Stable rank tie break on EntryId and source revision | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G4 | FUTURE / NOT EXECUTED |
| A02-T061 | TEXT-RELEVANCE | Raw FTS syntax escaped in typed query AST | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G4 | FUTURE / NOT EXECUTED |
| A02-T062 | TEXT-RELEVANCE | BM25 score not falsely converted to probability | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G4 | FUTURE / NOT EXECUTED |
| A02-T063 | TEXT-RELEVANCE | Unknown source schema fields preserved or unavailable | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G4 | FUTURE / NOT EXECUTED |
| A02-T064 | TEXT-RELEVANCE | Labeled benchmark reports recall MRR nDCG | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G4 | FUTURE / NOT EXECUTED |
| A02-T065 | SECURITY-ACL | Unauthorized project yields no private entry/snippet | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G5 | FUTURE / NOT EXECUTED |
| A02-T066 | SECURITY-ACL | Asset metadata grant not full source code body permission | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G5 | FUTURE / NOT EXECUTED |
| A02-T067 | SECURITY-ACL | Revoked grant invalidates next cursor and hydration | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G5 | FUTURE / NOT EXECUTED |
| A02-T068 | SECURITY-ACL | ACL policy revision change forces authorization recheck | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G5 | FUTURE / NOT EXECUTED |
| A02-T069 | SECURITY-ACL | Guessed cross-project AssetId reveals no existence | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G5 | FUTURE / NOT EXECUTED |
| A02-T070 | SECURITY-ACL | Secret tokens excluded from indexed plaintext cache | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G5 | FUTURE / NOT EXECUTED |
| A02-T071 | SECURITY-ACL | Malicious README prompt text remains untrusted data | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G5 | FUTURE / NOT EXECUTED |
| A02-T072 | SECURITY-ACL | Private host absolute paths redacted from output/log | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G5 | FUTURE / NOT EXECUTED |
| A02-T073 | SECURITY-ACL | Raw SQL regex and FTS injection rejected | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G5 | FUTURE / NOT EXECUTED |
| A02-T074 | SECURITY-ACL | Huge depth/fanout inputs rejected by bounded parser | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G5 | FUTURE / NOT EXECUTED |
| A02-T075 | SECURITY-ACL | Owner source locator reauthorized before each snippet | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G5 | FUTURE / NOT EXECUTED |
| A02-T076 | SECURITY-ACL | Cursor binds query/actor/project/policy/generation | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G5 | FUTURE / NOT EXECUTED |
| A02-T077 | SECURITY-ACL | Forged or expired cursor returns denial | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G5 | FUTURE / NOT EXECUTED |
| A02-T078 | SECURITY-ACL | Counts/rank output cannot reveal disallowed hits | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G5 | FUTURE / NOT EXECUTED |
| A02-T079 | SECURITY-ACL | Licensed source excerpt respects byte/rights limits | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G5 | FUTURE / NOT EXECUTED |
| A02-T080 | SECURITY-ACL | Embedding remote upload disabled without explicit approval | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G5 | FUTURE / NOT EXECUTED |
| A02-T081 | CONTEXT-BUDGET | max_rows capped with stable pagination | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G6 | FUTURE / NOT EXECUTED |
| A02-T082 | CONTEXT-BUDGET | max_bytes counts actual UTF-8 serialized output | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G6 | FUTURE / NOT EXECUTED |
| A02-T083 | CONTEXT-BUDGET | token budget marked estimate without pinned tokenizer | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G6 | FUTURE / NOT EXECUTED |
| A02-T084 | CONTEXT-BUDGET | Unicode substring cap cannot break encoded scalar | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G6 | FUTURE / NOT EXECUTED |
| A02-T085 | CONTEXT-BUDGET | Graph depth/edge/time limits applied | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G6 | FUTURE / NOT EXECUTED |
| A02-T086 | CONTEXT-BUDGET | Truncation yields PARTIAL_BUDGET and omitted count | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G6 | FUTURE / NOT EXECUTED |
| A02-T087 | CONTEXT-BUDGET | Stable keyset paging under fixed generation | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G6 | FUTURE / NOT EXECUTED |
| A02-T088 | CONTEXT-BUDGET | Changing generation invalidates offset-based cursor | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G6 | FUTURE / NOT EXECUTED |
| A02-T089 | CONTEXT-BUDGET | Pack contains exact owner IDs/source revision citations | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G6 | FUTURE / NOT EXECUTED |
| A02-T090 | CONTEXT-BUDGET | No whole-project source dump by default | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G6 | FUTURE / NOT EXECUTED |
| A02-T091 | CONTEXT-BUDGET | Only requested safe fields projected | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G6 | FUTURE / NOT EXECUTED |
| A02-T092 | CONTEXT-BUDGET | Pinned ranking ensures deterministic order | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G6 | FUTURE / NOT EXECUTED |
| A02-T093 | CONTEXT-BUDGET | Unsupported owner listed as PARTIAL coverage | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G6 | FUTURE / NOT EXECUTED |
| A02-T094 | CONTEXT-BUDGET | Stale locator cannot return unverified excerpt | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G6 | FUTURE / NOT EXECUTED |
| A02-T095 | CONTEXT-BUDGET | Redaction consistent across CLI/UI/MCP | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G6 | FUTURE / NOT EXECUTED |
| A02-T096 | CONTEXT-BUDGET | Quality measured against bytes and relevant results | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G6 | FUTURE / NOT EXECUTED |
| A02-T097 | SQLITE-FAILURES | FTS5 external-content backfill performed | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G7 | FUTURE / NOT EXECUTED |
| A02-T098 | SQLITE-FAILURES | FTS delete removes exact old tokens and ghost hits | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G7 | FUTURE / NOT EXECUTED |
| A02-T099 | SQLITE-FAILURES | FTS integrity check detects mismatch | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G7 | FUTURE / NOT EXECUTED |
| A02-T100 | SQLITE-FAILURES | Tokenizer migration triggers fully verified rebuild | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G7 | FUTURE / NOT EXECUTED |
| A02-T101 | SQLITE-FAILURES | Corrupt SQLite cache rebuilds without source loss | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G7 | FUTURE / NOT EXECUTED |
| A02-T102 | SQLITE-FAILURES | Long reader WAL checkpoint pressure bounded | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G7 | FUTURE / NOT EXECUTED |
| A02-T103 | SQLITE-FAILURES | Disk full returns safe status no canonical corruption | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G7 | FUTURE / NOT EXECUTED |
| A02-T104 | SQLITE-FAILURES | SQLite foreign key explicitly enabled if used | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G7 | FUTURE / NOT EXECUTED |
| A02-T105 | SQLITE-FAILURES | Malformed SQLite JSONB never trusted as source | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G7 | FUTURE / NOT EXECUTED |
| A02-T106 | SQLITE-FAILURES | No internet/LLM needed to rebuild project index | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G7 | FUTURE / NOT EXECUTED |
| A02-T107 | SQLITE-FAILURES | Tantivy bridge not implicitly required | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G7 | FUTURE / NOT EXECUTED |
| A02-T108 | SQLITE-FAILURES | GPL Xapian not adopted before license decision | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G7 | FUTURE / NOT EXECUTED |
| A02-T109 | SQLITE-FAILURES | Tree-sitter parser not GAME-02 typechecker | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G7 | FUTURE / NOT EXECUTED |
| A02-T110 | SQLITE-FAILURES | Unknown native grammar plugin cannot run unsandboxed | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G7 | FUTURE / NOT EXECUTED |
| A02-T111 | SQLITE-FAILURES | DATA-01 containment guards index cache path | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G7 | FUTURE / NOT EXECUTED |
| A02-T112 | SQLITE-FAILURES | Cancelled rebuild retains last-good generation | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G7 | FUTURE / NOT EXECUTED |
| A02-T113 | PLATFORM-ACCEPTANCE | Windows native/headless build and query test | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G8 | FUTURE / NOT EXECUTED |
| A02-T114 | PLATFORM-ACCEPTANCE | Linux native/headless build and query test | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G8 | FUTURE / NOT EXECUTED |
| A02-T115 | PLATFORM-ACCEPTANCE | macOS Apple Silicon native/headless test | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G8 | FUTURE / NOT EXECUTED |
| A02-T116 | PLATFORM-ACCEPTANCE | Web unsupported index backend truthful status | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G8 | FUTURE / NOT EXECUTED |
| A02-T117 | PLATFORM-ACCEPTANCE | Small 1k source index/query latency captured | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G8 | FUTURE / NOT EXECUTED |
| A02-T118 | PLATFORM-ACCEPTANCE | 100k corpus memory/disk/query p95 captured | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G8 | FUTURE / NOT EXECUTED |
| A02-T119 | PLATFORM-ACCEPTANCE | 1m stress tier is not a v1 promise | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G8 | FUTURE / NOT EXECUTED |
| A02-T120 | PLATFORM-ACCEPTANCE | 32 readers+writer WAL checkpoint measured | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G8 | FUTURE / NOT EXECUTED |
| A02-T121 | PLATFORM-ACCEPTANCE | Single entry update avoids unrelated 100k parse | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G8 | FUTURE / NOT EXECUTED |
| A02-T122 | PLATFORM-ACCEPTANCE | Crash after commit repairs index transparently | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G8 | FUTURE / NOT EXECUTED |
| A02-T123 | PLATFORM-ACCEPTANCE | ACL revocation during paging blocks data | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G8 | FUTURE / NOT EXECUTED |
| A02-T124 | PLATFORM-ACCEPTANCE | CPU headless no GPU/no display search works | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G8 | FUTURE / NOT EXECUTED |
| A02-T125 | PLATFORM-ACCEPTANCE | Human-labeled relevance and context byte report | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G8 | FUTURE / NOT EXECUTED |
| A02-T126 | PLATFORM-ACCEPTANCE | FTS corruption rebuilt compared to brute-force owner scan | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G8 | FUTURE / NOT EXECUTED |
| A02-T127 | PLATFORM-ACCEPTANCE | CLI/editor/MCP query parity with owner readback | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G8 | FUTURE / NOT EXECUTED |
| A02-T128 | PLATFORM-ACCEPTANCE | Catalog: filtered minimal-context query updated incrementally | Future owner snapshot/ProjectId/grant/source revision, real readback and trace G8 | FUTURE / NOT EXECUTED |

## Final future exit proof
A02-T113..A02-T128 cover real OS/scale/integration. **A02-T128** must prove a real owner-committed change followed by authorized bounded filtered minimal-context query with correct revision-linked results, measured incremental update not full scan, ACL isolation and benchmark evidence. The DATA-02/AI-01 implementation issues #25/#75 are OPEN/BLOCKED. SQLite FTS5 external-content, Unicode61, trigram short tokens and WAL long reader risks need actual pinned-version tests. Numerical budgets are TBD by owner/tier. **All 128 FUTURE / NOT EXECUTED; no native engine, search cache, MCP, data security test or benchmark exists.**

[Architecture](../architecture/ai-02-project-semantic-index.md) · [API](../contracts/ai-02-semantic-index-api.md) · [Benchmark](../research/ai-02-semantic-index-benchmark-protocol.md).
