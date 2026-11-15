# NLE-P00-WO-002-NET-06 — Network Security & Abuse Control Documentary Research Work Order

**2026-11-15 | research [#248](https://github.com/KayzenRoot/stormline/issues/248) | coding [#67](https://github.com/KayzenRoot/stormline/issues/67) OPEN/BLOCKED | catalog order 49/80 | BASE main `53ccaec7e60996e0e594415a261c3a3e4c7c54f0`.** Current phase P00 documentation risk LOW. Future privileged network/account/game security implementation is **HIGH_ASSURANCE**. No executor/engine authorization.

## OBJECTIVE
Research threats and design original bounded defense-in-depth for multiplayer trust boundaries: NET-01 TLS/QUIC/DTLS/path, NET-05 identity/short ticket/revocation, NET-02 server command admission, NET-03 secret field egress, NET-04 lag/rewind abuse, GAME-04 durable game rules, privacy and PII, resource/rate/DoS/DDoS limitations, replay domains, fuzz/ASan/UBSan, secure coding/license/incident controls; specify exactly 128 future tests and isolated reproducible security benchmarks. No perfect anti-cheat claim, no actual exploit/sending traffic.

## CONTEXT
NET-05 research/checkpoint/readback PRs #245/#246/#247 completed with actual exact-final-HEAD Docs Validation, pt-BR objective audits and normal squash/readback final main `53ccaec7e60996e0e594415a261c3a3e4c7c54f0`. At base **48/80 researched (60%), 32 pending, zero executable engine**, all 80 code Work Orders blocked. **Formal NET-06 predecessors NET-02 and NET-05** are only research DOCUMENTED_ADR_PROPOSED and lack runnable code. NET-01/03/04, GAME-04, WORLD-01, CORE-04, DATA-04 are integration owners; QA-04 is separate downstream broad secure SDLC owner.

## SCOPE
Exactly **eight NEW Markdown** in research PR branch `docs/NLE-P00-WO-002-NET-06-network-security`:
1. [architecture and threat model](../architecture/net-06-network-security-abuse-control.md)
2. [ADR-0052 PROPOSED](../adr/0052-net-06-defense-in-depth-authority-quotas-privacy.md)
3. [primary-source technology, license and threat matrix](../research/net-06-security-technology-threat-license-matrix.md)
4. [typed semantic SecurityDecision API](../contracts/net-06-security-abuse-api.md)
5. [exactly 128 future tests](../testing/net-06-acceptance-matrix.md)
6. [isolated safe benchmark/fuzz protocol](../research/net-06-security-benchmark-protocol.md)
7. this research Work Order
8. [Evidence Bundle](../evidence/NLE-P00-WO-002-NET-06.md)

Research PR own **exact-final-HEAD Docs Validation**, objective pt-BR audit, normal squash/main/contract readback. **Separate checkpoint PR** with only checkpoint, backlog, registry sole NET-06 research_status, this WO and Evidence, own final-HEAD CI/audit/squash/main readback. Historical four-doc closeout when necessary, own gates. Expected **49/80 research (61.25%), 31 pending, 0 engine**, all 80 implementation WOs BLOCKED. Close research #248 only after verified checkpoint main; code #67 OPEN/BLOCKED. No EDIT-01 until final closeout readback.

## OUT OF SCOPE
No engine C++/Rust/Go/JS, encryption backend, auth server, safe/unsafe sockets, cloud/waf, antivirus or commercial anti-cheat, actual network packet/fuzz runner, real target testing or public scan, production secret, PII, automatic billing/endpoint setup, third-party SDK/source import, changes to any implementation registry code status, native/Web builds, security certification, no high-confidence assertion of absence of cheats. No CodeRabbit, mandatory external human reviewer, paid CI, force push, rewrite or bypass.

## FILES / SOURCES TO READ
Canonical priority `docs/11-checkpoint.md` > `docs/10-decisions-ledger.md` and approved ADRs > `docs/03-scope.md` > `docs/09-definition-of-done.md` > `docs/04-architecture.md` > `docs/02-requirements.md` > `AGENTS.md` > `docs/product/module-catalog.md` > `docs/queue/implementation-registry.json` > `docs/queue/work-orders/NET-06.md`. Read NET-05 [API](../contracts/net-05-session-lobby-api.md), NET-02 [API](../contracts/net-02-dedicated-server-api.md), NET-01 [API](../contracts/net-01-transport-connection-api.md), NET-03 [API](../contracts/net-03-replication-interest-api.md), GAME-04 [API](../contracts/game-04-gameplay-event-api.md) and NET-04/QA-04 ownership; primary RFC/NIST/LLVM/libraries linked from threat/license matrix.

## REQUIREMENTS
GOV-001..005 and current NLE-D013..020 owner decisions. Catalog acceptance: **Testes adversariais e ausência de bypass de autoridade** is a FUTURE executable and audited proof, not fulfilled by plan. Source code license NLE-D009 OPEN, ADR-0052 PROPOSED, release class UNDECIDED. Owner-approved quantitative budgets, risk classification per coding WO and exact crypto backend currently TBD.

## ARCHITECTURE RULES
NET-01 exclusively owns network crypto/path validation, NET-05 identity/ticket/roles, NET-02 actual match/actor/game command validation, GAME-04 rewards/abilities/durable receipts, NET-03 egress secret classification and snapshots, NET-04 client prediction/hit read-only rewind, WORLD-01 ECS, CORE-04 tick, DATA-04 source/CAS/retention and QA-04 general security SDLC/fuzz/SBOM. NET-06 owns typed threat/abuse policy, hierarchical quotas, security denial/correlation, redacted audit and specific adversarial test obligations; **NET-06 ALLOW never authorizes world changes alone**. Distinguish transport ACK/ticket jti/command sequence/game event/durable commit. No generic TLS guarantees game actor. QUIC unvalidated 3x limit protocol-specific, no false blanket DDoS solution. Redaction and fail-closed identities. Admin Editor/CLI/MCP only scoped profile changes under CAS/owner control, never game authority.

## CONSTRAINTS
Documentation P00 only. No live attack, no insecure guest outside loopback, no custom crypto, no copy unlicensed packages, no auto-paid edge service. Security controls at runtime remain NOT IMPLEMENTED. Future HIGH_ASSURANCE requires strong tests/review and key+incident rollback, avoid HIGH/CRITICAL known issues. No runtime pass or measured p99 by Docs Validation.

## ACCEPTANCE CRITERIA
- [ ] Research PR **exactly eight NEW Markdown**, links resolve and no code, SDK, CI, registry or checkpoint altered.
- [ ] Architecture/ADR-0052 **PROPOSED** clearly separate NET-01/02/03/04/05/GAME-04/WORLD-01/CORE-04/DATA-04/QA-04 ownership with STRIDE, privacy, availability and replay threat models.
- [ ] Quantitative limits **TBD**, QUIC-specific RFC9000 prevalidation 3x limit correct, authenticated malicious client still fails NET-02 game rules, fail-closed on malformed data/current session revocation, layered work budget and false positives.
- [ ] Matrix pin-research includes MsQuic MIT, OpenSSL current Apache-2, libsodium ISC, LLVM libFuzzer Apache-2 with LLVM exception, OSS-Fuzz Apache-2 and **AFL++ combined AGPL-3-or-later**; standards and vendor cost distinctions.
- [ ] Typed V1 trust/security/sanction/audit/fuzz contracts; exactly **128 N06-T001..N06-T128 FUTURE/NOT EXECUTED** and safe isolated benchmarks with no attack, runtime or result claims.
- [ ] Research PR own final-HEAD Docs Validation SUCCESS (Source Pack/local links, DAG, registry and blocked Zcode selector), objective pt-BR audit APPROVED DOCS ONLY, normal squash/main/contract readback.
- [ ] Independent checkpoint PR own exact-final-HEAD CI/audit/squash/main readback, sole NET-06 `research_status=RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED`, **49/80 researched (61.25%)**, 31 pending and zero runtime.
- [ ] All 80 `work_order_status=BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`, `executor_ready=false`, `approved_adr=null`, `release_class=UNDECIDED`; code #67 OPEN/BLOCKED, research #248 closes only after checkpoint main readback; no coding unlock.
- [ ] Final closeout/readback before EDIT-01 documentary research; no HIGH/CRITICAL known in scoped doc changes, no runtime security certified.

## TESTS
Actual GitHub Docs Validation for each PR exact HEAD and 128 unique-ID static count; Source Pack links/DAG/registry/blocked Zcode selector. **ZERO** engine/security/crypto/fuzz/sanitizer/network, native/Web builds, gameplay, performance or exploit tests RUN. All 128 cases FUTURE/NOT EXECUTED.

## DELIVERABLES
Research issue #248, eight documents, research PR+CI/objective audit/normal squash/main readback, separate five-file checkpoint own gates, optional four-file historical closeout, Evidence Bundle/Checkpoint Delta and pt-BR audit. Code issue #67 unchanged.

## REVIEW FORMAT
`APPROVED / CORRECTION REQUIRED / BLOCKED` in pt-BR; exact Git base/head and critical blob hashes, file list/diff, CI job/steps and 128 future tests not run, threat and license/IP/security correctness, HIGH/CRITICAL/residual risks, rollback/recovery, proposed vs factual checkpoint and 80-block invariants. Correction Delta only same WO/PR if safe.

## STOP CONDITION
Any canonical STALE, changed approved ADR, code activation/registry unintended mutation, auth bypass or private leak in proposed design, public attack/testing, wrong standard/license, custom crypto, paid side effect, failing CI/audit, known HIGH/CRITICAL => CORRECTION REQUIRED/BLOCKED, no later increment.

## CONTEXT LOCK (Git blob IDs, NOT file SHA256)
BASE `53ccaec7e60996e0e594415a261c3a3e4c7c54f0`; Checkpoint `4698474a4f188fbde2232ed908913d8a5ad0e334`; Ledger `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`; Scope `4ef605c74632ece080b2650e37dd83a415b63310`; DoD `160b3054db9ea1961308934b401488b838d24c3e`; Architecture `df62574cb3956c3ac9881631a4cf66be4e1abff1`; Requirements `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`; Backlog `3c0d5c6e3ce5e3ef1dced7a15b5ff1c0fdd7f752`; Registry `14ea9b2a2ccb0a5498a8f0f559aad1907254effd`; Catalog `18d69bca439831d65982cb0f8acbca1dbaa2eee9`; future code WO `1bdd0e2c563144363d67d0185a3673713c16867a`; AGENTS `3e57b719f8651407879ebb641707a048773ea4c2`; NET-05 API `e65efeae29fd94657841bc1cf3c11bca41751170`; NET-02 API `5e3a5bca27620248bee8f1a9658a760bf728940e`; NET-01 API `a41347d8cc0042d336598af2c5de8b533c91c428`; NET-03 API `686339e0dd32527a878908b093b13a5a1862f498`; GAME-04 API `0f5f2edc888052f401ce1c2fe85828a299f43520`. Rebase if approved critical sources changed. Runtime code sha only after future activation.

## EVIDENCE
[Evidence Bundle](../evidence/NLE-P00-WO-002-NET-06.md) documents actual PR, CI and checkpoint only after observed, not claims of an implemented engine.

## NET-06 research #249 objectively APPROVED/MERGED and separate checkpoint proposed
- [Research PR #249](https://github.com/KayzenRoot/stormline/pull/249) BASE `53ccaec7e60996e0e594415a261c3a3e4c7c54f0`, final HEAD `5867f2e1745a05875b324c13010cd705f698941d`, exactly 8 NEW Markdown (489 adds, 0 deletes), [Docs Validation #43720024171](https://github.com/KayzenRoot/stormline/actions/runs/43720024171) **SUCCESS** job #132829778666 incl Source Pack links/DAG/registry/Zcode blocked selector, [objective pt-BR audit #6895155499](https://github.com/KayzenRoot/stormline/pull/249#issuecomment-6895155499) **APPROVED documentary-only**, normal squash/main/PR/contract readback `c8e59f0a8e57b8492950a78281ea20a670f6aa1f`. Exactly N06-T001..N06-T128 unique and FUTURE/NOT EXECUTED; no real security tests or runtime.
- Independent checkpoint PR BASE `c8e59f0a8e57b8492950a78281ea20a670f6aa1f`, exactly five files checkpoint/backlog/registry/this WO/Evidence, **only NET-06 research_status** change. Expected **49/80 research (61.25%), 31 pending, zero executable engine**, all 80 coding WOs BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, executor_ready=false, approved_adr=null, release_class UNDECIDED. Coding #67 OPEN/BLOCKED, research #248 OPEN until checkpoint actual main readback. ADR-0052 PROPOSED, engine code NLE-D009 OPEN. Independent checkpoint exact-final-HEAD CI/audit/squash/readback **PENDING at creation**. No Zcode coding, crypto or third-party code adopted.
