# NET-06 — Reproducible Isolated Security, Fuzz and Abuse Benchmark Protocol

**P00 protocol ONLY, 2026-11-15.** No server, client, network trace, fuzz process, packet attack, game or measured CPU/RTT/p99 results. All 128 N06 future scenarios NOT EXECUTED. This protocol requires explicit control of test endpoints: **loopback/isolated local virtual networks only, synthetic identities and packet seeds, bounded time/traffic/CPU/memory**. Never aim traffic at public services, live player devices, third-party provider infrastructure or production credentials. No volumetric test/DDoS.

## Hypotheses
H1: valid TLS/QUIC client with invalid game authority never modifies NET-02/GAME-04 world/currency/health. H2: NET-01 QUIC preaddress-validation responses obey protocol-specific RFC9000 3x bound and fail closed without unbounded expensive parsing. H3: NET-05 tickets cannot be reused across epoch/actor/issuer and revoked privilege cannot reconnect without fresh verification. H4: NET-03 decoded wire/logs never contain secret game fields for unauthorized recipients. H5: hierarchical rate, CPU/heap/queue budgets survive synthetic malicious actions without unacceptable legitimate-player starvation; all targets/budgets chosen later. H6: fuzz+sanitizers find/characterize bugs and regression fixes without claims of absolute security. H7: abuse heuristics include fairness/false-positive measurements; app code cannot defeat upstream link saturation.

## Future immutable manifest
`SecurityBenchManifestV1` fields: Git base/head/source SHA, signed or documented build and approved ADR/DoD, exact NET-01 backend/crypto provider/version and path validation, NET-05 token issuer/test keys/session ban/revocation and nonce store, NET-02 match actor/health+world epoch, GAME-04 gameplay state/receipts, NET-03 field ACL and decoder, NET-04 lag policy, CORE-04 TickId/actor count, DATA-04 consistency, QA-04 sanitizer/compiler flags, OS CPU arch RAM NIC browser, synthetic traffic distribution and seed, virtual network isolation proof, max sent packets/bytes/CPU/time/heap/log quota, RTT/loss/jitter, source of actual measured timestamps, exact test commands/CI, corpus hash/minimized crash, security invariants and redacted p50/p95/p99/false-positive logs. No live user IP/JWT/secret data in report.

## Controlled workload axes (NOT target performance promises)
| Workload | Controlled conditions | Required future proof |
|---|---|---|
| SEC01_Authority | local server, two valid principals, one hostile synthetic account, invalid actor and loot | no unauthorized WORLD-01/GAME-04 mutation or second durable reward |
| SEC02_Path | synthetic QUIC unvalidated address/path, migration and byte-count cases | verify address validation and 3x bound before validation, transport-native result |
| SEC03_Session | expired/wrong-issuer/wrong-role/jti replay/ban/key rotation under concurrent join | NET-02 game admission denied correctly and cheaply |
| SEC04_Command | 1/10/100 finite malformed and duplicate commands per controlled tick | resource budgets, authoritative state and retry/idempotency |
| SEC05_Decoder | version/length/varint/decompress corrupt synthetic corpus | parser fail-closed, no OOM/UAF/OOB, sanitizer report and minimized repro |
| SEC06_PrivateData | public/owner/team/spectator/hidden and role revocation while queued | **decoded** recipient packet, response and log classification no secrets |
| SEC07_Fuzz | libFuzzer+ASan/UBSan, TSan separate, MSan supported targets, fixed seeds/time | coverage/reproducer, crash classification and no known uncorrected HIGH/CRITICAL |
| SEC08_Quota | several request classes, shared-NAT cohort and explicit service workload | per-account fairness, false positive rate and correct denial CPU/queue |
| SEC09_Recovery | issuer/nonce-store outage, world restart, key rollover, ticket expiry | no fail-open, no stale replay or double commit, safe rollback |
| SEC10_Load | 8/16/32/64 synthetic users and 1 bounded hostile test client | candidate CPU/memory/p99 and attack denial **not** real max CCU |
| SEC11_Tools | synthetic malicious Editor/CLI/MCP policy or auth operation | no player impersonation/key export/paid provider changes |
| SEC12_Incident | fake token sentinel + synthetic leak to observability | token/PII redacted, incident report, secure retention and operator access |

## Measurement and stop conditions
1. Isolate owned test network and clamp total bytes/time/CPU/RAM before each future run. No third-party IP, public scanning or unsolicited packet send. A failed isolation proof blocks benchmark.
2. Correctness first: inspect NET-02 actual authoritative state and GAME-04 commit receipts. Confirm denied packet did NOT change state; NET-03 actual decoded data for hidden fields; valid players still succeed at permitted gameplay.
3. QUIC amplification analysis counts **actual wire bytes** under unvalidated path only; never generalize RFC9000 to arbitrary UDP, never claim to defeat DDoS above Internet uplink.
4. Resource measurements: pre-auth vs auth CPU, allocations, codec parse time, queue/heap peak, game tick work, log volume and number of active sessions, legitimate request tail latency and deny latency, NAT/RTT cohort false positives. Choose thresholds after owner baseline.
5. Build finite corpus/fuzz plus sanitizer matrix with pinned compiler flags/OS/seed, minimize issues and record exact versions. A finite no-crash run cannot prove bug-free. TSan normally separate from ASan binary.
6. Redact test event logs, use fake tokens and fake IP sentinels only. For privacy, inspect log and packet contents without leaking the test secrets into permanent public artifacts.
7. For every HIGH/CRITICAL security issue, stop the future release/coding increment, create Correction Delta and regression; rollback security policy/provider/keys only with approved owner procedure. No silent weakening of DoD.
8. Optional paid edge mitigation, anti-bot vendors and crypto FIPS claims remain **unapproved** and require explicit license/security/financial review. Document residual risk and operational incident response.

## Current evidence status
No benchmark or attack has been run, zero native/Web/game/server builds, no actual token validator or sanitizer harness, no security proof. N06-T001..T128 strictly FUTURE/NOT EXECUTED. See [128 tests](../testing/net-06-acceptance-matrix.md), [security matrix](../research/net-06-security-technology-threat-license-matrix.md), [ADR-0052](../adr/0052-net-06-defense-in-depth-authority-quotas-privacy.md). Primary references [RFC9000](https://www.rfc-editor.org/rfc/rfc9000.html), [NIST SP800-63B-4](https://csrc.nist.gov/pubs/sp/800/63/b/4/final), [LLVM libFuzzer](https://llvm.org/docs/LibFuzzer.html), [AFL++ licensing](https://github.com/AFLplusplus/AFLplusplus/blob/stable/LICENSING.md).
