# NET-06 — Technology, Licensing and Multiplayer Threat Matrix

**2026-11-15 | P00 RESEARCH ONLY.** All technology/standards are comparative candidates, no code, SDK, crypto provider, CI scanner, credential, key or software has been adopted. Exact version/LICENSE/SPDX/NOTICE/SBOM, transitive dependencies and OS/CPU rights need verification before future selection. Engine source license decision NLE-D009 **OPEN**. Proposed ADR-0052 not approved.

## Primary standards and boundaries
| Standard/reference | Relevant security invariant; not embedded code license |
|---|---|
| [RFC 9000 `8](https://www.rfc-editor.org/rfc/rfc9000.html) | QUIC peer address validation and **3x bytes-received bound before peer address is validated**; transport-specific, does NOT stop upstream volumetric DDoS |
| [RFC 9001 QUIC TLS](https://www.rfc-editor.org/rfc/rfc9001.html), [RFC 8446 TLS 1.3](https://www.rfc-editor.org/rfc/rfc8446.html), [RFC 9147 DTLS 1.3](https://www.rfc-editor.org/rfc/rfc9147.html) | secure transport configuration/key phases, separate from actor/game-command authorization |
| [RFC 8725 JWT BCP](https://www.rfc-editor.org/rfc/rfc8725.html), [RFC 9700 OAuth Security BCP](https://www.rfc-editor.org/rfc/rfc9700.html) | issuer/audience/token-type/algorithm confusion, redirects, trust anchors; must ALSO check game actor, ban and revoked ticket |
| [NIST SP 800-63B-4 FINAL July 2025](https://csrc.nist.gov/pubs/sp/800/63/b/4/final) and [replay resistant authenticators](https://pages.nist.gov/800-63-4/sp800-63b/authenticators/) | challenge freshness/nonces and assurance; transport replay protection alone does not mean identity proof secure |
| [RFC 9449 DPoP](https://www.rfc-editor.org/rfc/rfc9449.html) | proof-of-possession HTTP OAuth token; **not** an automatic QUIC/UDP datagram authentication protocol |
| [RFC 8445 ICE](https://www.rfc-editor.org/rfc/rfc8445.html), [RFC 8489 STUN](https://www.rfc-editor.org/rfc/rfc8489.html), [RFC 8656 TURN](https://www.rfc-editor.org/rfc/rfc8656.html) | NAT traversal/relay confidentiality, abuse/amplification risk and relay bandwidth costs, NET-01 owner |
| [OWASP API Top 10 2023](https://owasp.org/API-Security/editions/2023/en/0x11-t10/) and [OWASP Cheat Sheet Series](https://cheatsheetseries.owasp.org/) | broken object authorization, unrestricted work, log/redaction and secure coding; security advice not a product assurance certificate |
| [MITRE CWE](https://cwe.mitre.org/) and [NVD](https://nvd.nist.gov/) | issue classification/known affected versions, not proof bug-free after scanner PASS |

## Candidate tools and code licenses (NEITHER USED NOR APPROVED)
| Candidate and primary upstream | Source license verified at primary URL | Potential role and critical caveat |
|---|---|---|
| [MsQuic](https://github.com/microsoft/msquic), [LICENSE](https://github.com/microsoft/msquic/blob/main/LICENSE) | **MIT** | NET-01 QUIC backend candidate, no GAME-04 authority and no general DDoS immunity; pin TLS provider/transitives |
| [OpenSSL](https://github.com/openssl/openssl), [LICENSE](https://github.com/openssl/openssl/blob/master/LICENSE.txt) | current 3.x+ **Apache-2.0**; older series different license | possible TLS/DTLS provider NET-01, FIPS claims require exact validated module/config and proof, not generic logo |
| [libsodium](https://github.com/jedisct1/libsodium) | **ISC** | cryptographic primitives, not a replacement for audited transport protocol; no custom cipher recommendation |
| [LLVM/libFuzzer](https://llvm.org/docs/LibFuzzer.html), [LLVM LICENSE](https://github.com/llvm/llvm-project/blob/main/LICENSE.TXT) | **Apache-2.0 WITH LLVM-exception** to pin exact toolchain | coverage-guided in-process fuzz, ASan/UBSan often combined where supported, TSan separate |
| [LLVM sanitizers](https://clang.llvm.org/docs/AddressSanitizer.html), [UBSan](https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html), [MSan](https://clang.llvm.org/docs/MemorySanitizer.html), [TSan](https://clang.llvm.org/docs/ThreadSanitizer.html) | toolchain LLVM license and binary libraries per release | ASan/UAF and OOB, UBSan UB, MSan uninitialized, TSan races; not all targets/binaries interoperable |
| [OSS-Fuzz](https://github.com/google/oss-fuzz), [LICENSE](https://github.com/google/oss-fuzz/blob/master/LICENSE) | **Apache-2.0** OSS-Fuzz project; eligibility/host terms separate | future continuous fuzzing, not free universal private service or assurance guarantee |
| [AFL++ licensing details](https://github.com/AFLplusplus/AFLplusplus/blob/stable/LICENSING.md) | **combined tool AGPL-3.0-or-later**; per-file license varies AGPL or Apache-2.0 and transitive others | can be external test tool after license evaluation; **never label entire AFL++ Apache/MIT** |
| [GoogleTest](https://github.com/google/googletest), [LICENSE](https://github.com/google/googletest/blob/main/LICENSE) | **BSD-3-Clause** | future typed negative unit tests, not evidence of real hostile game security |
| [Google Benchmark](https://github.com/google/benchmark), [LICENSE](https://github.com/google/benchmark/blob/main/LICENSE) | **Apache-2.0** | future CPU denial/parse work measurement, no DDoS mitigation |
| [Zeek](https://github.com/zeek/zeek) / [Suricata](https://github.com/OISF/suricata) | file-level/third-party rights to verify; Suricata generally GPL-family | optional security monitoring on owned test network; no uncontrolled decrypted packet/PII logging |
| upstream DDoS/anti-cheat services | provider terms/pricing/privacy/SDK separately | network edge might need paid upstream help; **never mandatory or auto-provisioned** |

## Threat register (risk taxonomy, all FUTURE implementation)
| Threat ID | Boundary and sensitive asset | Mitigation owner and proof |
|---|---|---|
| TH01 | spoofed source / reflection, pre-auth path | NET-01 RFC9000-specific path validation and NET-06 bounded counters; synthetic byte ratio |
| TH02 | handshake/connection flood and CPU/memory | NET-01 cheap state/NET-06 hierarchy, host work/heap/queue load |
| TH03 | authenticated client forged actor health/loot/hit | NET-02 GAME-04 authoritative command reject, actual server state unchanged |
| TH04 | stolen/expired/mismatched token or role | NET-05 issuer/jti/revocation/NET-02 independent match join validation |
| TH05 | replay packet/game event/economy award | separate NET-01/05/02/GAME-04/DATA-04 replay domains and durable receipt |
| TH06 | malformed length/decompression/UB/race | NET-03/01 codec bounds, libFuzzer+sanitizers after approved build |
| TH07 | cross-recipient private entity, role, presence | NET-03 field allowlist before cache, NET-05 privacy; inspect decoded actual wire |
| TH08 | fake RTT and lag-comp peeker exploit | NET-04 bounded server observed query, NET-02/GAME-04 current game rules |
| TH09 | lobby invite enumeration/spam | NET-05 privacy/NET-06 scoped rate/ban, safe denial timing and size |
| TH10 | privileged MCP/editor/CLI agent injection | capability and DATA-04 CAS, no player impersonation or secret export |
| TH11 | logs/traces leak PII or secret/token/IP | structured redaction and data retention, no hidden object data |
| TH12 | stale/vulnerable dependency and key compromise | NET-01/05 key rotation, QA-04 SBOM/patch/provenance/incident |
| TH13 | volumetric attack saturates upstream link | optional network edge provider and incident playbook; app cannot guarantee shield |
| TH14 | false positives, shared IP unfair bans | per-principal policies, staged review/appeal, cohort metrics |
| TH15 | compression length and response timing side channel | NET-03 secret separation and NET-06 actual payload/timing differential tests |
| TH16 | state recovery/old token after server restart | NET-05 revocation/lease, NET-02 world epoch, DATA-04 durable consistency |

## Licenses, zero-claims and adoption conditions
Check precise SPDX tag/LICENSE at release and transitive dependencies, platform/vendor rights, CVE posture and crypto module claims. Security policy proposals may **not** authorize adopting AFL++ AGPL binaries into a proprietary-distribution engine or claiming FIPS/SOC2/LGPD certification. No source/SDK/vendor selection, real attack/load test or security assurance has occurred. Risks HIGH_ASSURANCE for future auth/game/durable-state implementation, documentation-only scope LOW.
