# Evidence Bundle — NLE-P00-WO-002-AUD-01 Audio Device & Mixer Research

**STATUS: RESEARCH BRANCH IN PROGRESS, PR/CI/AUDIT/MERGE/CHECKPOINT PENDING. NO ENGINE CODE.**  
**Date:** 2026-11-14 | Research [#195](https://github.com/KayzenRoot/stormline/issues/195) | Future implementation [#52](https://github.com/KayzenRoot/stormline/issues/52) OPEN/BLOCKED.  
**BASE main:** `21e50e73cf1f5f3a3c01bb2f869422161b28e248` | branch `docs/NLE-P00-WO-002-AUD-01-audio-device-mixer-research`.

## 1. Source check and lock
Prior SIM-07 research PR #193 and checkpoint PR #194 independently audited/merged, main readback verified. At BASE, 34/80 researched, 46 pending including historic CORE-04 research_status gap, zero engine runtime, 80 implementation WOs blocked executor_ready=false, approved_adr=null. Catalog AUD-01 deps CORE-01/CORE-03 only researched, none implemented. Future coding issue #52; AUD-02 is next catalog research candidate.
Critical blob lock: checkpoint `319a05d912a548057465944f4874ac7549272b70`; ledger `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`; Scope `4ef605c74632ece080b2650e37dd83a415b63310`; DoD `160b3054db9ea1961308934b401488b838d24c3e`; Architecture `df62574cb3956c3ac9881631a4cf66be4e1abff1`; Requirements `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`; catalog `18d69bca439831d65982cb0f8acbca1dbaa2eee9`; registry `1f0ff0da0a8408d33f71a75f8c8060451ce0abc3`. No compiler/engine/runtime/OS audio device available as project evidence.

## 2. Artifacts (all proposals)
- [Architecture](../architecture/aud-01-audio-device-mixer.md): owned mixer/bus/voice/clock, strict real-time callback, job workers, decoder, hotplug and headless/browser.
- [ADR-0038 PROPOSED](../adr/0038-aud-01-real-time-audio-mixer-and-device-authority.md): single mixer/device adapter and bounded RT voice lifecycles, no adopted backend.
- [Technology and license matrix](../research/aud-01-audio-technologies-license-matrix.md): SDL3 zlib/miniaudio Unlicense/MIT-0 leading alternatives; PortAudio MIT/cubeb ISC comparators; dr_libs/Opus/libsamplerate optional, AudioWorklet Web future, no SDK.
- [Semantic API](../contracts/aud-01-audio-device-mixer-api.md): AudioDevice/Voice/Bus/Clock/Stream events, generational handles, typed error and staged Editor/CLI/MCP authoring.
- [128 FUTURE tests](../testing/aud-01-acceptance-matrix.md) all NOT EXECUTED.
- [Benchmark protocol](../research/aud-01-audio-benchmark-protocol.md): synth original fixtures, underruns/latency/CPU/voice/hotplug/codec, no measured data.
- [Research WO](../work-orders/NLE-P00-WO-002-AUD-01.md) and this Evidence Bundle.

## 3. Verification receipts (only actual observations appended)
| Gate | Current state |
|---|---|
| Research issue #195, branch created from checked main | OBSERVED |
| Research PR exact HEAD and file diff | PENDING |
| GitHub Docs Validation exact final HEAD | NOT VERIFIED |
| SonarCloud/Socket other security CI | NOT VERIFIED |
| Actual native/Web/NullSink/audio software, audio device, callback, underruns/latency | NOT IMPLEMENTED / NOT TESTED |
| 128 future acceptance cases, fuzz/ASan/TSan, audio samples/performance | ALL FUTURE / NOT EXECUTED |
| Objective pt-BR audit | PENDING |
| Research PR normal squash/readback | PENDING |
| Separate checkpoint PR with CI/audit/squash/readback | PENDING |

## 4. Threat and risk register
Future HIGH concerns: RT callback blocks/allocation/data race, malicious codec and decompression bombs, device callback uses freed stream pointer on hotplug, audio event storms starve other engine tasks, untrusted MCP input/capture/microphone permissions, speech/private sound telemetry leak, channel layout mixup hearing volume spikes, wrong source license or SDL double mix. Only proposed mitigations: fixed RT buffers, bounded queue, immutable snapshots, generation/epoch and consumer-retire gates, DATA sandbox, off-RT decode, user permission and fuzz/sanitizer, hardware loopback measurements; **none implemented**. Current docs LOW risk.

## 5. Checkpoint Delta PROPOSED, not approved before independent checkpoint PR
After research PR exact-head CI/audit/squash/readback and then separate checkpoint PR exact-head CI/audit/squash/readback, update only AUD-01 `research_status` to `RESEARCH_DOCUMENTED_ADR_PROPOSED`. Total **35/80 researched (43.75%)**, **45 pending** including historical CORE-04 gap, 0 executable engine modules, all 80 implementation packets `BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`, `executor_ready=false`, `approved_adr=null`. Future code #52 stays OPEN/BLOCKED, ADR-0038 PROPOSED, release class UNDECIDED. Next research AUD-02 Spatial Audio & Acoustic World; do not advance before checkpoint.

## 6. Objective review
APPROVED/CORRECTION REQUIRED/BLOCKED only on observed source, exact SHA/CI and scoped diff; no claims real audio played, tested, installed or published.
