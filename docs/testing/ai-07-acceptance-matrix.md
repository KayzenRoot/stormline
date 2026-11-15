# AI-07 — 128 Future Transactional Planning, Undo & Recovery Acceptance Tests

**2026-11-15 | P00 DOCUMENTARY RESEARCH ONLY / NOT IMPLEMENTED | research #305 | NLE-P00-WO-002-AI-07 | future code #81 OPEN/BLOCKED | BASE a7d4b3ae7ecab0061ea6d0dd72b2bce3dd185089.** Formal deps **AI-01 + AI-06 ONLY**, ADRs 0060/0065 PROPOSED; 62/80 researched baseline, 18 pending, all 80 code WOs BLOCKED, engine false, NLE-D009 OPEN.

**EXACTLY 128 UNIQUE A07-T001..A07-T128, all FUTURE / NOT EXECUTED. No tests implemented, no PASS, no FAIL, no engine build or conformance.** Eight groups of 16.

## Test oracle and independent fixtures
- Pin a real owner source revision/digest, AI-01 schema and command, AI-06 agent+grant policy epoch, ProjectId, deterministic test fixture seed, OS/architecture and exact storage/JOURNAL configuration before any future run.
- Use **independent canonical source reopen** and outside-project OS sentinel file hash both before/after. A claimed status/receipt is not proof of source atomicity. Never simulate a global ACID result by concatenating unrelated receipts.
- Include owner-scoped atomic fixture and separate multi-owner filesystem/SQLite/external fixture; classify expected outcome OWNER_ATOMIC, RECOVERABLY_COORDINATED, COMPENSATION_ONLY or UNSUPPORTED. Prove `PARTIAL_COMMIT` visibility when a real partial state exists.
- Preview must not alter source, disk or network targets. A derived ephemeral cache may be used only under documented caps, and never mislabeled as a source write.
- One-use consent and grant revocation must be enforced at owner effect, not just at UI. A text model prompt never approves.
- Crash/fault injection tests require actual restart/reopen with poisoned journals, disk-full, canceled and unknown-stage effects, not just unit mock success.
- For undo/redo, verify selective preservation of another actor's intervening changes; changed plan always requires revalidation/consent.
- Tests for future SDK/host/sandbox/durability across Windows/Linux/macOS must specify exact OS feature support and cannot be counted PASS if skipped. Model output and vendor benchmarks are not acceptance oracles.

## Eight groups
| Group | IDs | Count | Principal obligation |
|---|---|---:|---|
| DRAFT-PLAN-DIFF | A07-T001..A07-T016 | 16 | side-effect-free bounded deterministic typed preview |
| AUTH-CONSENT-CAS | A07-T017..A07-T032 | 16 | AI-06 recheck, stale-plan denial, one-use approval |
| ATOMIC-OWNER | A07-T033..A07-T048 | 16 | one-owner atomicity, source CAS, idempotency |
| MULTI-OWNER-EXTERNAL | A07-T049..A07-T064 | 16 | honest partial, coordination, external side effects |
| CONFLICT-MERGE | A07-T065..A07-T080 | 16 | semantic base/ours/theirs, no lost update |
| UNDO-REDO-REPEAT | A07-T081..A07-T096 | 16 | selective current-rights inverse and exact repeat |
| CRASH-RECOVERY | A07-T097..A07-T112 | 16 | fault injection, recovery, journal and durability |
| E2E-PERF-SECURITY | A07-T113..A07-T128 | 16 | OS/host/quality/latency/performance |
 
## Complete future acceptance matrix
| Test ID | Group | Scenario / assertion | Required independent evidence | Status |
|---|---|---|---|---|
| A07-T001 | DRAFT-PLAN-DIFF | Draft accepts bounded validated semantic owner commands and rejects unknown command | owner snapshot/diff golden master + filesystem sentinel before/after + typed digest | FUTURE / NOT EXECUTED |
| A07-T002 | DRAFT-PLAN-DIFF | Draft references exact canonical ProjectId instead of arbitrary filesystem path | owner snapshot/diff golden master + filesystem sentinel before/after + typed digest | FUTURE / NOT EXECUTED |
| A07-T003 | DRAFT-PLAN-DIFF | Draft uses stable AssetId/SceneNodeId and source revision vector | owner snapshot/diff golden master + filesystem sentinel before/after + typed digest | FUTURE / NOT EXECUTED |
| A07-T004 | DRAFT-PLAN-DIFF | Draft command graph rejects cyclic dependency without source mutation | owner snapshot/diff golden master + filesystem sentinel before/after + typed digest | FUTURE / NOT EXECUTED |
| A07-T005 | DRAFT-PLAN-DIFF | Draft rejects incompatible CommandId major or required schema hash | owner snapshot/diff golden master + filesystem sentinel before/after + typed digest | FUTURE / NOT EXECUTED |
| A07-T006 | DRAFT-PLAN-DIFF | Preview returns deterministic affected owner IDs and semantic diff for fixed snapshot | owner snapshot/diff golden master + filesystem sentinel before/after + typed digest | FUTURE / NOT EXECUTED |
| A07-T007 | DRAFT-PLAN-DIFF | Preview correctly distinguishes ADD MODIFY DELETE MOVE and RELINK | owner snapshot/diff golden master + filesystem sentinel before/after + typed digest | FUTURE / NOT EXECUTED |
| A07-T008 | DRAFT-PLAN-DIFF | Preview displays prefab variant ancestry and reference graph impacts | owner snapshot/diff golden master + filesystem sentinel before/after + typed digest | FUTURE / NOT EXECUTED |
| A07-T009 | DRAFT-PLAN-DIFF | Preview source and filesystem state remain unchanged for every proposed command | owner snapshot/diff golden master + filesystem sentinel before/after + typed digest | FUTURE / NOT EXECUTED |
| A07-T010 | DRAFT-PLAN-DIFF | Preview does not execute imported project scripts or arbitrary shell | owner snapshot/diff golden master + filesystem sentinel before/after + typed digest | FUTURE / NOT EXECUTED |
| A07-T011 | DRAFT-PLAN-DIFF | Preview rejects unsupported owner port rather than fabricating derived results | owner snapshot/diff golden master + filesystem sentinel before/after + typed digest | FUTURE / NOT EXECUTED |
| A07-T012 | DRAFT-PLAN-DIFF | Preview reports rights license and export impacts without hiding restricted fields | owner snapshot/diff golden master + filesystem sentinel before/after + typed digest | FUTURE / NOT EXECUTED |
| A07-T013 | DRAFT-PLAN-DIFF | Plan digest binds source revision owner schema operation order and typed args | owner snapshot/diff golden master + filesystem sentinel before/after + typed digest | FUTURE / NOT EXECUTED |
| A07-T014 | DRAFT-PLAN-DIFF | Plan expires and rejects stale owner source revision before apply | owner snapshot/diff golden master + filesystem sentinel before/after + typed digest | FUTURE / NOT EXECUTED |
| A07-T015 | DRAFT-PLAN-DIFF | Large preview is truncated only at valid typed diff entry boundary with receipt | owner snapshot/diff golden master + filesystem sentinel before/after + typed digest | FUTURE / NOT EXECUTED |
| A07-T016 | DRAFT-PLAN-DIFF | Plan clearly labels OWNER_ATOMIC RECOVERABLY_COORDINATED or COMPENSATION_ONLY | owner snapshot/diff golden master + filesystem sentinel before/after + typed digest | FUTURE / NOT EXECUTED |
| A07-T017 | AUTH-CONSENT-CAS | AI-06 scoped grant denies plan affecting wrong ProjectId | AI-06 grant epoch/consent record + owner JIT decision and zero-delta oracle | FUTURE / NOT EXECUTED |
| A07-T018 | AUTH-CONSENT-CAS | AI-01 owner checks current grant policy epoch before source commit | AI-06 grant epoch/consent record + owner JIT decision and zero-delta oracle | FUTURE / NOT EXECUTED |
| A07-T019 | AUTH-CONSENT-CAS | Changed actor or agent invalidates consent for prior plan | AI-06 grant epoch/consent record + owner JIT decision and zero-delta oracle | FUTURE / NOT EXECUTED |
| A07-T020 | AUTH-CONSENT-CAS | Changed command args or operation order invalidates consent digest | AI-06 grant epoch/consent record + owner JIT decision and zero-delta oracle | FUTURE / NOT EXECUTED |
| A07-T021 | AUTH-CONSENT-CAS | Changed source revision invalidates approved plan | AI-06 grant epoch/consent record + owner JIT decision and zero-delta oracle | FUTURE / NOT EXECUTED |
| A07-T022 | AUTH-CONSENT-CAS | Changed destination or target invalidates approval for export | AI-06 grant epoch/consent record + owner JIT decision and zero-delta oracle | FUTURE / NOT EXECUTED |
| A07-T023 | AUTH-CONSENT-CAS | Owner rechecks asset rights before performing relink and commit | AI-06 grant epoch/consent record + owner JIT decision and zero-delta oracle | FUTURE / NOT EXECUTED |
| A07-T024 | AUTH-CONSENT-CAS | MRTR inputResponses and model yes cannot replace trusted UI approval | AI-06 grant epoch/consent record + owner JIT decision and zero-delta oracle | FUTURE / NOT EXECUTED |
| A07-T025 | AUTH-CONSENT-CAS | Risk-class escalation from preview to delete requires new consent | AI-06 grant epoch/consent record + owner JIT decision and zero-delta oracle | FUTURE / NOT EXECUTED |
| A07-T026 | AUTH-CONSENT-CAS | One-use consent cannot be consumed by two simultaneous apply calls | AI-06 grant epoch/consent record + owner JIT decision and zero-delta oracle | FUTURE / NOT EXECUTED |
| A07-T027 | AUTH-CONSENT-CAS | Approval from another project or another client agent is rejected | AI-06 grant epoch/consent record + owner JIT decision and zero-delta oracle | FUTURE / NOT EXECUTED |
| A07-T028 | AUTH-CONSENT-CAS | Expired plan and approval are refused before source owner write | AI-06 grant epoch/consent record + owner JIT decision and zero-delta oracle | FUTURE / NOT EXECUTED |
| A07-T029 | AUTH-CONSENT-CAS | Policy unavailable denies rather than silently applying old ALLOW | AI-06 grant epoch/consent record + owner JIT decision and zero-delta oracle | FUTURE / NOT EXECUTED |
| A07-T030 | AUTH-CONSENT-CAS | Hidden resources cannot be enumerated through dry-run or diff error | AI-06 grant epoch/consent record + owner JIT decision and zero-delta oracle | FUTURE / NOT EXECUTED |
| A07-T031 | AUTH-CONSENT-CAS | Cross-project ChangeSet rejected without explicit approved owner scope | AI-06 grant epoch/consent record + owner JIT decision and zero-delta oracle | FUTURE / NOT EXECUTED |
| A07-T032 | AUTH-CONSENT-CAS | Revocation between PREPARED and owner commit prevents unauthorized effect | AI-06 grant epoch/consent record + owner JIT decision and zero-delta oracle | FUTURE / NOT EXECUTED |
| A07-T033 | ATOMIC-OWNER | Single owner multi-object batch commits all or none under proven ACID | independent source reopen + atomic owner DB/journal and crash state/receipt | FUTURE / NOT EXECUTED |
| A07-T034 | ATOMIC-OWNER | Owner rejects one invalid resource and leaves entire atomic batch unchanged | independent source reopen + atomic owner DB/journal and crash state/receipt | FUTURE / NOT EXECUTED |
| A07-T035 | ATOMIC-OWNER | Owner commit CAS rejects concurrent source revision advancement | independent source reopen + atomic owner DB/journal and crash state/receipt | FUTURE / NOT EXECUTED |
| A07-T036 | ATOMIC-OWNER | Owner journal record is durable before actual effects when claimed | independent source reopen + atomic owner DB/journal and crash state/receipt | FUTURE / NOT EXECUTED |
| A07-T037 | ATOMIC-OWNER | Owner receipt before and after revisions match independent source reopen | independent source reopen + atomic owner DB/journal and crash state/receipt | FUTURE / NOT EXECUTED |
| A07-T038 | ATOMIC-OWNER | Owner source commit does not falsely claim runtime publication complete | independent source reopen + atomic owner DB/journal and crash state/receipt | FUTURE / NOT EXECUTED |
| A07-T039 | ATOMIC-OWNER | Owner-generated minted stable IDs propagate to all scene and asset references | independent source reopen + atomic owner DB/journal and crash state/receipt | FUTURE / NOT EXECUTED |
| A07-T040 | ATOMIC-OWNER | Owner schema migration conflict yields typed abort without partial source | independent source reopen + atomic owner DB/journal and crash state/receipt | FUTURE / NOT EXECUTED |
| A07-T041 | ATOMIC-OWNER | Owner rejects operation on tombstoned AssetId without raw path fallback | independent source reopen + atomic owner DB/journal and crash state/receipt | FUTURE / NOT EXECUTED |
| A07-T042 | ATOMIC-OWNER | Owner idempotency same payload retry yields same canonical commit receipt | independent source reopen + atomic owner DB/journal and crash state/receipt | FUTURE / NOT EXECUTED |
| A07-T043 | ATOMIC-OWNER | Owner idempotency same key different payload produces conflict | independent source reopen + atomic owner DB/journal and crash state/receipt | FUTURE / NOT EXECUTED |
| A07-T044 | ATOMIC-OWNER | Owner commit order deterministic for fixed owner operation DAG | independent source reopen + atomic owner DB/journal and crash state/receipt | FUTURE / NOT EXECUTED |
| A07-T045 | ATOMIC-OWNER | Nested SQLite SAVEPOINT release not mistaken for durable outer commit | independent source reopen + atomic owner DB/journal and crash state/receipt | FUTURE / NOT EXECUTED |
| A07-T046 | ATOMIC-OWNER | SQLite WAL synchronous profile tested for claimed power-loss durability | independent source reopen + atomic owner DB/journal and crash state/receipt | FUTURE / NOT EXECUTED |
| A07-T047 | ATOMIC-OWNER | SQLite ATTACH WAL cannot be reported as global crash-atomic | independent source reopen + atomic owner DB/journal and crash state/receipt | FUTURE / NOT EXECUTED |
| A07-T048 | ATOMIC-OWNER | Owner committed state and receipt remain coherent after restart | independent source reopen + atomic owner DB/journal and crash state/receipt | FUTURE / NOT EXECUTED |
| A07-T049 | MULTI-OWNER-EXTERNAL | Multiple owners require per-participant guarantee classes before preparation | per-owner receipt + external sentinel + explicit PARTIAL recovery journal | FUTURE / NOT EXECUTED |
| A07-T050 | MULTI-OWNER-EXTERNAL | Unsupported owner staging contract yields ATOMIC_SCOPE_UNSUPPORTED | per-owner receipt + external sentinel + explicit PARTIAL recovery journal | FUTURE / NOT EXECUTED |
| A07-T051 | MULTI-OWNER-EXTERNAL | Owner A commit followed by B failure yields explicit PARTIAL_COMMIT | per-owner receipt + external sentinel + explicit PARTIAL recovery journal | FUTURE / NOT EXECUTED |
| A07-T052 | MULTI-OWNER-EXTERNAL | Durable intent tracks each owner committed revision without inventing global atomicity | per-owner receipt + external sentinel + explicit PARTIAL recovery journal | FUTURE / NOT EXECUTED |
| A07-T053 | MULTI-OWNER-EXTERNAL | Filesystem asset replacement and SQLite registry update receive truthful guarantee label | per-owner receipt + external sentinel + explicit PARTIAL recovery journal | FUTURE / NOT EXECUTED |
| A07-T054 | MULTI-OWNER-EXTERNAL | Failure between file replacement and metadata commit is recoverably classified | per-owner receipt + external sentinel + explicit PARTIAL recovery journal | FUTURE / NOT EXECUTED |
| A07-T055 | MULTI-OWNER-EXTERNAL | Derived FTS index/cache refresh is not counted as source commit | per-owner receipt + external sentinel + explicit PARTIAL recovery journal | FUTURE / NOT EXECUTED |
| A07-T056 | MULTI-OWNER-EXTERNAL | GPU renderer publish lag yields DERIVED_PUBLISH_PENDING rather than COMPLETE | per-owner receipt + external sentinel + explicit PARTIAL recovery journal | FUTURE / NOT EXECUTED |
| A07-T057 | MULTI-OWNER-EXTERNAL | External export requires separate destination approval and receipt | per-owner receipt + external sentinel + explicit PARTIAL recovery journal | FUTURE / NOT EXECUTED |
| A07-T058 | MULTI-OWNER-EXTERNAL | External publish success and subsequent failure are marked irreversible/compensation | per-owner receipt + external sentinel + explicit PARTIAL recovery journal | FUTURE / NOT EXECUTED |
| A07-T059 | MULTI-OWNER-EXTERNAL | Compensating action uses fresh owner grants and source revision | per-owner receipt + external sentinel + explicit PARTIAL recovery journal | FUTURE / NOT EXECUTED |
| A07-T060 | MULTI-OWNER-EXTERNAL | Compensation failure remains RECOVERY_REQUIRED and visible to operator | per-owner receipt + external sentinel + explicit PARTIAL recovery journal | FUTURE / NOT EXECUTED |
| A07-T061 | MULTI-OWNER-EXTERNAL | Distributed 2PC is not advertised when owner lacks true prepare vote | per-owner receipt + external sentinel + explicit PARTIAL recovery journal | FUTURE / NOT EXECUTED |
| A07-T062 | MULTI-OWNER-EXTERNAL | Untrusted tool call cannot inject new network destination into plan | per-owner receipt + external sentinel + explicit PARTIAL recovery journal | FUTURE / NOT EXECUTED |
| A07-T063 | MULTI-OWNER-EXTERNAL | Cross-filesystem rename cannot be assumed atomic in all target OS | per-owner receipt + external sentinel + explicit PARTIAL recovery journal | FUTURE / NOT EXECUTED |
| A07-T064 | MULTI-OWNER-EXTERNAL | Uncertain external request is not retried without destination idempotency evidence | per-owner receipt + external sentinel + explicit PARTIAL recovery journal | FUTURE / NOT EXECUTED |
| A07-T065 | CONFLICT-MERGE | Changed field since base snapshot produces typed overlapping conflict | base/ours/theirs owner ground truth + stable-ID graph and source hashes | FUTURE / NOT EXECUTED |
| A07-T066 | CONFLICT-MERGE | Disjoint compatible owner fields merge only if owner semantics prove safety | base/ours/theirs owner ground truth + stable-ID graph and source hashes | FUTURE / NOT EXECUTED |
| A07-T067 | CONFLICT-MERGE | Deleted scene object conflicts with later move operation | base/ours/theirs owner ground truth + stable-ID graph and source hashes | FUTURE / NOT EXECUTED |
| A07-T068 | CONFLICT-MERGE | Asset reference relink conflicts with target asset tombstone | base/ours/theirs owner ground truth + stable-ID graph and source hashes | FUTURE / NOT EXECUTED |
| A07-T069 | CONFLICT-MERGE | Prefab base revision conflict preserves override intent and ancestry | base/ours/theirs owner ground truth + stable-ID graph and source hashes | FUTURE / NOT EXECUTED |
| A07-T070 | CONFLICT-MERGE | Schema migration incompatibility rejects blind auto-merge | base/ours/theirs owner ground truth + stable-ID graph and source hashes | FUTURE / NOT EXECUTED |
| A07-T071 | CONFLICT-MERGE | Base ours theirs include exact committed owner revision IDs | base/ours/theirs owner ground truth + stable-ID graph and source hashes | FUTURE / NOT EXECUTED |
| A07-T072 | CONFLICT-MERGE | Conflict diff redacts unauthorized private fields and paths | base/ours/theirs owner ground truth + stable-ID graph and source hashes | FUTURE / NOT EXECUTED |
| A07-T073 | CONFLICT-MERGE | Last-write-wins is rejected for protected SceneIR and AssetId graph | base/ours/theirs owner ground truth + stable-ID graph and source hashes | FUTURE / NOT EXECUTED |
| A07-T074 | CONFLICT-MERGE | Three-way text merge not used as universal semantic scene merge | base/ours/theirs owner ground truth + stable-ID graph and source hashes | FUTURE / NOT EXECUTED |
| A07-T075 | CONFLICT-MERGE | User conflict resolution creates new plan digest and requires fresh approval | base/ours/theirs owner ground truth + stable-ID graph and source hashes | FUTURE / NOT EXECUTED |
| A07-T076 | CONFLICT-MERGE | Concurrent Editor and MCP apply cannot overwrite each other silently | base/ours/theirs owner ground truth + stable-ID graph and source hashes | FUTURE / NOT EXECUTED |
| A07-T077 | CONFLICT-MERGE | Unknown owner merge rules yield UNSUPPORTED not optimistic success | base/ours/theirs owner ground truth + stable-ID graph and source hashes | FUTURE / NOT EXECUTED |
| A07-T078 | CONFLICT-MERGE | Stable IDs in merged result never silently collide or lose references | base/ours/theirs owner ground truth + stable-ID graph and source hashes | FUTURE / NOT EXECUTED |
| A07-T079 | CONFLICT-MERGE | Undo conflict after collaborator edit preserves unrelated user change | base/ours/theirs owner ground truth + stable-ID graph and source hashes | FUTURE / NOT EXECUTED |
| A07-T080 | CONFLICT-MERGE | Resolved conflict source readback matches owner semantic fingerprint | base/ours/theirs owner ground truth + stable-ID graph and source hashes | FUTURE / NOT EXECUTED |
| A07-T081 | UNDO-REDO-REPEAT | Undo captures before-after owner revisions and reversible inverse metadata | before/after owner revisions + unrelated actor changes + inverse receipt | FUTURE / NOT EXECUTED |
| A07-T082 | UNDO-REDO-REPEAT | Undo preview is side-effect free and reports affected stable IDs | before/after owner revisions + unrelated actor changes + inverse receipt | FUTURE / NOT EXECUTED |
| A07-T083 | UNDO-REDO-REPEAT | Undo of actor A change preserves disjoint actor B edits | before/after owner revisions + unrelated actor changes + inverse receipt | FUTURE / NOT EXECUTED |
| A07-T084 | UNDO-REDO-REPEAT | Undo of overlapping actor B edit returns UNDO_CONFLICT without overwrite | before/after owner revisions + unrelated actor changes + inverse receipt | FUTURE / NOT EXECUTED |
| A07-T085 | UNDO-REDO-REPEAT | Undo requires current AI-06 authorization not historical actor grant | before/after owner revisions + unrelated actor changes + inverse receipt | FUTURE / NOT EXECUTED |
| A07-T086 | UNDO-REDO-REPEAT | Undo of destructive operation requires fresh trusted consent when risk requires | before/after owner revisions + unrelated actor changes + inverse receipt | FUTURE / NOT EXECUTED |
| A07-T087 | UNDO-REDO-REPEAT | Undo produces a new owner commit preserving history rather than reset-hard | before/after owner revisions + unrelated actor changes + inverse receipt | FUTURE / NOT EXECUTED |
| A07-T088 | UNDO-REDO-REPEAT | Redo of successful undo uses current source revision and new plan digest | before/after owner revisions + unrelated actor changes + inverse receipt | FUTURE / NOT EXECUTED |
| A07-T089 | UNDO-REDO-REPEAT | Redo after third-party modification reports conflict rather than replay | before/after owner revisions + unrelated actor changes + inverse receipt | FUTURE / NOT EXECUTED |
| A07-T090 | UNDO-REDO-REPEAT | Repeated apply with same idempotency key does not duplicate owner mutation | before/after owner revisions + unrelated actor changes + inverse receipt | FUTURE / NOT EXECUTED |
| A07-T091 | UNDO-REDO-REPEAT | Different args with same idempotency key are rejected | before/after owner revisions + unrelated actor changes + inverse receipt | FUTURE / NOT EXECUTED |
| A07-T092 | UNDO-REDO-REPEAT | Undo after renamed asset preserves stable owner ID and reference graph | before/after owner revisions + unrelated actor changes + inverse receipt | FUTURE / NOT EXECUTED |
| A07-T093 | UNDO-REDO-REPEAT | Undo unavailable after permitted history retention floor is explicit | before/after owner revisions + unrelated actor changes + inverse receipt | FUTURE / NOT EXECUTED |
| A07-T094 | UNDO-REDO-REPEAT | Irreversible export advertises COMPENSATION_ONLY never undo success | before/after owner revisions + unrelated actor changes + inverse receipt | FUTURE / NOT EXECUTED |
| A07-T095 | UNDO-REDO-REPEAT | History cursor and audit are scoped to actor/project policy epoch | before/after owner revisions + unrelated actor changes + inverse receipt | FUTURE / NOT EXECUTED |
| A07-T096 | UNDO-REDO-REPEAT | UI CLI and MCP same typed operations yield owner-equivalent semantic state | before/after owner revisions + unrelated actor changes + inverse receipt | FUTURE / NOT EXECUTED |
| A07-T097 | CRASH-RECOVERY | Crash before durable intent leaves zero committed source effect | fault injection crash trace + restarted canonical source and journal verification | FUTURE / NOT EXECUTED |
| A07-T098 | CRASH-RECOVERY | Crash immediately after intent replays only after owner state inspection | fault injection crash trace + restarted canonical source and journal verification | FUTURE / NOT EXECUTED |
| A07-T099 | CRASH-RECOVERY | Crash after owner A commit before B reports PARTIAL and owner A revision | fault injection crash trace + restarted canonical source and journal verification | FUTURE / NOT EXECUTED |
| A07-T100 | CRASH-RECOVERY | Crash after owner commit before receipt recovery reconstructs actual state | fault injection crash trace + restarted canonical source and journal verification | FUTURE / NOT EXECUTED |
| A07-T101 | CRASH-RECOVERY | Crash after source commit before derived publish yields pending derived state | fault injection crash trace + restarted canonical source and journal verification | FUTURE / NOT EXECUTED |
| A07-T102 | CRASH-RECOVERY | Crash during undo avoids duplicate inverse owner commit | fault injection crash trace + restarted canonical source and journal verification | FUTURE / NOT EXECUTED |
| A07-T103 | CRASH-RECOVERY | Corrupt journal checksum enters RECOVERY_REQUIRED without unsafe replay | fault injection crash trace + restarted canonical source and journal verification | FUTURE / NOT EXECUTED |
| A07-T104 | CRASH-RECOVERY | Torn journal append is detected and safely truncated or quarantined by owner | fault injection crash trace + restarted canonical source and journal verification | FUTURE / NOT EXECUTED |
| A07-T105 | CRASH-RECOVERY | Disk full during staging returns failure without false source commit | fault injection crash trace + restarted canonical source and journal verification | FUTURE / NOT EXECUTED |
| A07-T106 | CRASH-RECOVERY | OS power loss with WAL NORMAL does not claim guaranteed durable last commit | fault injection crash trace + restarted canonical source and journal verification | FUTURE / NOT EXECUTED |
| A07-T107 | CRASH-RECOVERY | Owner journal compaction preserves unreconciled intents and undo floor | fault injection crash trace + restarted canonical source and journal verification | FUTURE / NOT EXECUTED |
| A07-T108 | CRASH-RECOVERY | Source checkpoint migration crash reopens last verified generation | fault injection crash trace + restarted canonical source and journal verification | FUTURE / NOT EXECUTED |
| A07-T109 | CRASH-RECOVERY | Clock rollback does not revive expired grant or idempotency scope | fault injection crash trace + restarted canonical source and journal verification | FUTURE / NOT EXECUTED |
| A07-T110 | CRASH-RECOVERY | Same ChangeSet replay across two agents is rejected or receipt-reused safely | fault injection crash trace + restarted canonical source and journal verification | FUTURE / NOT EXECUTED |
| A07-T111 | CRASH-RECOVERY | Retries after unknown external publish do not duplicate export | fault injection crash trace + restarted canonical source and journal verification | FUTURE / NOT EXECUTED |
| A07-T112 | CRASH-RECOVERY | Windows Linux macOS restart tests verify declared fsync/rename guarantees | fault injection crash trace + restarted canonical source and journal verification | FUTURE / NOT EXECUTED |
| A07-T113 | E2E-PERF-SECURITY | Full scene prefab asset multi-object fixture previews changes with zero source diff | pinned Git/OS/host/SDK + independent semantic/OS proof and performance samples | FUTURE / NOT EXECUTED |
| A07-T114 | E2E-PERF-SECURITY | Single owner apply+source readback matches expected semantic fingerprint | pinned Git/OS/host/SDK + independent semantic/OS proof and performance samples | FUTURE / NOT EXECUTED |
| A07-T115 | E2E-PERF-SECURITY | Independent owner/OS sentinel oracle detects zero unauthorized outside-project effects | pinned Git/OS/host/SDK + independent semantic/OS proof and performance samples | FUTURE / NOT EXECUTED |
| A07-T116 | E2E-PERF-SECURITY | Simulated prompt injection cannot invent owner operation or consent | pinned Git/OS/host/SDK + independent semantic/OS proof and performance samples | FUTURE / NOT EXECUTED |
| A07-T117 | E2E-PERF-SECURITY | Targeted fault injection at every state transition matches guarantee matrix | pinned Git/OS/host/SDK + independent semantic/OS proof and performance samples | FUTURE / NOT EXECUTED |
| A07-T118 | E2E-PERF-SECURITY | Concurrent 32 agents produce no lost update privilege escalation or duplicate commit | pinned Git/OS/host/SDK + independent semantic/OS proof and performance samples | FUTURE / NOT EXECUTED |
| A07-T119 | E2E-PERF-SECURITY | Selected Codex host plan-apply-undo flow verified with pinned protocol version | pinned Git/OS/host/SDK + independent semantic/OS proof and performance samples | FUTURE / NOT EXECUTED |
| A07-T120 | E2E-PERF-SECURITY | Selected Claude host plan-apply-undo flow verified with pinned protocol version | pinned Git/OS/host/SDK + independent semantic/OS proof and performance samples | FUTURE / NOT EXECUTED |
| A07-T121 | E2E-PERF-SECURITY | Three-way/CRDT optional case does not bypass structured owner conflict rules | pinned Git/OS/host/SDK + independent semantic/OS proof and performance samples | FUTURE / NOT EXECUTED |
| A07-T122 | E2E-PERF-SECURITY | Owner crash recovery and source data integrity pass cold restart fixture | pinned Git/OS/host/SDK + independent semantic/OS proof and performance samples | FUTURE / NOT EXECUTED |
| A07-T123 | E2E-PERF-SECURITY | 128 test suite under Windows Linux macOS supported targets has real evidence | pinned Git/OS/host/SDK + independent semantic/OS proof and performance samples | FUTURE / NOT EXECUTED |
| A07-T124 | E2E-PERF-SECURITY | Future engine undo UI accurately displays irreversible side effects | pinned Git/OS/host/SDK + independent semantic/OS proof and performance samples | FUTURE / NOT EXECUTED |
| A07-T125 | E2E-PERF-SECURITY | Preview p50/p95/p99 measured using pinned hardware and realistic owner counts | pinned Git/OS/host/SDK + independent semantic/OS proof and performance samples | FUTURE / NOT EXECUTED |
| A07-T126 | E2E-PERF-SECURITY | Commit and recovery latency/space overhead compared to owner baseline | pinned Git/OS/host/SDK + independent semantic/OS proof and performance samples | FUTURE / NOT EXECUTED |
| A07-T127 | E2E-PERF-SECURITY | License/SBOM/CVE/reproducibility acceptance recorded for selected technologies | pinned Git/OS/host/SDK + independent semantic/OS proof and performance samples | FUTURE / NOT EXECUTED |
| A07-T128 | E2E-PERF-SECURITY | Test evidence pins source owner versions policy epoch log digests and final verdict | pinned Git/OS/host/SDK + independent semantic/OS proof and performance samples | FUTURE / NOT EXECUTED |

## Future mandatory gates
1. Every required supported test passes with real compiled owner functionality; unsupported optional features must be explicitly UNSUPPORTED rather than marked PASS. **Zero** HIGH/CRITICAL known cross-project write, consent bypass, source/asset corruption, silent partial transaction or duplicate irreversible side effect.
2. Owner-atomic claims validated on selected real storage mode with power-loss and OS failure injection. Multi-owner partial recovery demonstrated, not hidden. Required derived publish evaluated separately.
3. Conflict and redo under concurrent editors/agents preserve owner semantic state or report conflict; no silent last-write-wins.
4. Exact source scope/digest, journal state, consent/actor ID, idempotency, OS and host versions pinned; audit pt-BR with independent readback.
5. Technology/ADR license and engineering DoD separately ratified. These P00 test **specifications were not executed**.

[Architecture](../architecture/ai-07-transactional-planning-undo.md) · [Contracts](../contracts/ai-07-changeset-transaction-api.md) · [Benchmark](../research/ai-07-transaction-benchmark-protocol.md).
