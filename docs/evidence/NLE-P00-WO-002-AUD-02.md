# Evidence Bundle — NLE-P00-WO-002-AUD-02 Spatial Audio & Acoustic World

**STATUS: RESEARCH BRANCH IN PROGRESS; RESEARCH PR/CI/AUDIT/MERGE AND SEPARATE CHECKPOINT PENDING. NO ENGINE CODE.**  
2026-11-14 | Research [#198](https://github.com/KayzenRoot/stormline/issues/198) | Future implementation [#53](https://github.com/KayzenRoot/stormline/issues/53) OPEN/BLOCKED. BASE main `90125e6885603ad260f0d355067991699577a9f6`. Branch `docs/NLE-P00-WO-002-AUD-02-spatial-acoustics-research`.

## 1. Source check, Context Lock, planning baseline
Predecessor AUD-01 research #195 and PR #196/checkpoint PR #197 exact-head Docs Validation/audit normal squash/readback verified. Base 35/80 research documented, 45 pending (historic CORE-04 gap), 0 runtime modules, all 80 coding WOs BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS/executor_ready=false/approved_adr=null. AUD-02 catalog deps AUD-01 and WORLD-02 research documented but no executable engine, SIM-02/ WORLD-03/04 streams and GFX-04 docs conceptual. Coding #53 OPEN/BLOCKED.
Preflight blob hashes: checkpoint `7d6f5dd9969d42c77874075ca3a5762cbdcb2af5`, Ledger `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`, Scope `4ef605c74632ece080b2650e37dd83a415b63310`, DoD `160b3054db9ea1961308934b401488b838d24c3e`, Architecture `df62574cb3956c3ac9881631a4cf66be4e1abff1`, Requirements `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`, Catalog `18d69bca439831d65982cb0f8acbca1dbaa2eee9`, registry `37b264f486c367755cf6a8c0c8ccbe51e9bc5c06`, AUD-01 architecture `2967a42d44d115cfaf85ff9576e431c732daaf4e`.

## 2. Research artifacts documented (proposals only)
- [Original architecture](../architecture/aud-02-spatial-audio-acoustic-world.md): listener/source multi-domain coordinate frames; headphone/speaker/HRTF, audio geometry, material bands, room/portal/pathing/early+late IR, async jobs, source/Cell/Origin/DeviceEpoch publication, data rights and privacy.
- [ADR-0039 PROPOSED](../adr/0039-aud-02-engine-owned-acoustics-and-binaural-authority.md): AUD-01 single voice/device/mixer owner; AUD-02 spatial plans; WORLD-02/03/04 source, SIM-02 physics query optional, DATA-05 cook, no ray or HRTF parse on RT callback; source authority and security.
- [Upstream/license matrix](../research/aud-02-spatial-audio-technologies-license-matrix.md): Steam Audio Apache-2.0 leading reference, libmysofa BSD3 candidate, Embree Apache2 ray candidate, OpenAL Soft LGPL2-or-later comparator with separate Apache2 HRTF source, archived Resonance Audio Apache2 and Project Acoustics docs/code binary caveat; no adoption.
- [Versioned typed contracts](../contracts/aud-02-spatial-acoustics-api.md): Actor/Listener/World/Surface/Room/Portal/Query/HRTF/RenderPlan IDs, epochs, bounded errors and role-scoped results.
- [128 FUTURE cases](../testing/aud-02-acceptance-matrix.md), all NOT EXECUTED.
- [Benchmark protocol](../research/aud-02-acoustic-benchmark-protocol.md): original legally-clear synthetic signal/geometry/HRTF where permitted, CPU/headless/native/Web/IR/RT and blind listening, no actual results.
- [Research Work Order](../work-orders/NLE-P00-WO-002-AUD-02.md) and this Evidence Bundle.

No imported third-party vendor sources, SOFA HRTF datasets, real recording/IR, 3D scene, executable, GUI, CPU ray simulation, sound output, device access, browser build, benchmark, fuzz/ASan/TSan or listening proof.

## 3. Verified gate ledger (append observations only)
| Gate | Observation |
|---|---|
| Research issue #198 and branch from exact main base | OBSERVED |
| Research PR number, exact HEAD and diff | PENDING |
| GitHub Docs Validation final exact HEAD | NOT VERIFIED |
| Other SonarCloud/Socket/security CI at exact HEAD | NOT VERIFIED |
| Native/Web/headless audio engine or DSP performance | NOT IMPLEMENTED / NOT TESTED |
| 128 future runtime/perceptual/security/benchmark cases | ALL FUTURE / NOT EXECUTED |
| Objective pt-BR audit | PENDING |
| Research PR normal squash/main readback | PENDING |
| Distinct checkpoint PR exact HEAD CI/audit/squash/readback | PENDING |

## 4. Security and error risks, explicitly NOT mitigated yet
FUTURE HIGH concerns: malicious SOFA/HDF5 metadata and decompression bombs, IR/path/room graph DoS, unbounded ray jobs starving AUD-01 decoder, stale acoustic mesh/World/Origin/DeviceEpoch causing use-after-free, client/acoustic debug leaking hidden NPC positions, personal biometric-like HRTF profile handling without consent, inaccurate fallback in unloaded world, proprietary/dataset redistribution. Architectural mitigations include DATA-03 sandbox/quotas/rights, CORE-03 bounded ray jobs, WORLD-03 leases, generation-scoped accepted acoustic samples, AUD-01 RT immutable plans and deferred lifetime, privacy roles and opt-in personalized HRTF; **none implemented or security-tested**. No claim engine ready.

## 5. Checkpoint Delta PROPOSED only (not self-promoted)
After final research exact-head CI/audit/squash/main readback and **separate checkpoint PR with independent CI/audit/squash/readback**, change AUD-02 only from RESEARCH_PENDING to RESEARCH_DOCUMENTED_ADR_PROPOSED, count **36/80 (45%) researched, 44 pending** including historical CORE-04 research gap, zero engine implementations. All 80 coding packets BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, executor_ready=false, approved_adr=null. Future coding #53 remains OPEN/BLOCKED, release class UNDECIDED, ADR-0039 PROPOSED. Next catalog research AUD-03 DSP & Sound Graph (future code #54), only after checkpoint approved.

## 6. Review contract
Objective report pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED, BASE+final HEAD, eight new docs changed, actual CI workflows/jobs, licensing/privacy/ownership issues, known HIGH/CRITICAL, 128 runtime tests NOT EXECUTED and separate checkpoint diff. Do not count research as code or claim any device/headset output.
