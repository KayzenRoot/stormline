# NET-03 — Snapshot/Replication Technologies, Authoritative Visibility and License Matrix

**Primary source research 2026-11-15; technology and library candidates ONLY.** No code, content, SDK, dependency, binary codec or engine license was installed/adopted. Freeze exact upstream source hash, security advisories, file notices, patent/commercial/service terms and target build rights before any future implementation. Engine license NLE-D009 remains **OPEN**.

## 1. Engines and models
| Upstream / official references | Actual licensing and rights boundary | Replication lesson; not a Stormline proof |
|---|---|---|
| [Unreal Engine Iris intro](https://dev.epicgames.com/documentation/unreal-engine/introduction-to-iris-in-unreal-engine), [components](https://dev.epicgames.com/documentation/unreal-engine/components-of-iris-in-unreal-engine), [filtering](https://dev.epicgames.com/documentation/unreal-engine/iris-filtering-in-unreal-engine), [prioritization](https://dev.epicgames.com/documentation/en-us/unreal-engine/iris-prioritization-in-unreal-engine) | **Epic Unreal EULA/engine proprietary licensing**; not automatically permissive to copy from docs or engine source, sample rights separate | shared quantized replication states, dirty masks, owner/group/connection/dynamic filters, network priority, dependency-ordered send and per-connection state, explicit Iris feature-status/experimental caveats |
| [Unity Netcode for Entities ghost snapshots](https://docs.unity.cn/Packages/com.unity.netcode%401.5/manual/ghost-snapshots.html), [relevancy/optimization](https://docs.unity.cn/Packages/com.unity.netcode%401.5/manual/optimizations.html) | **Unity package-specific license and Unity editor/Engine usage terms**; verify exact version LICENSE.md, do not assert MIT or standalone C++ embedding permission | authoritative ghosts, snapshot vs reliable RPC distinction, per-connection importance/relevancy, partial snapshots, quantized components and importance-driven budgets, send rate vs simulation tick |
| [Godot MultiplayerSynchronizer](https://docs.godotengine.org/en/stable/classes/class_multiplayersynchronizer.html), [Godot source](https://github.com/godotengine/godot) | core engine **MIT**; individual demo/assets/fonts and 3P notices separate | per-peer visibility filter, update visibility and replication intervals; direct Godot Node/Object properties/IDs are not Stormline ECS wire IDs |
| [Valve Source Multiplayer Networking](https://developer.valvesoftware.com/wiki/Source_Multiplayer_Networking), [Source SDK license](https://github.com/ValveSoftware/source-sdk-2013/blob/master/LICENSE) | Valve Source SDK 2013 **restricted SDK license; NOT MIT**; engine source/asset not generally reusable | snapshots, delta update, interpolation/lag concepts; **conceptual comparison only, no copying** |
| [Photon Fusion documentation](https://doc.photonengine.com/fusion/current/manual/network-object) | proprietary Photon/Fusion SDK and service EULA/fees; not guaranteed offline/open | interest/area and state authority comparator; NOT a compatible drop-in |
| **Stormline-owned immutable authorized projection** | original code license NLE-D009 **OPEN**, no external adoption | preferred semantic public API under DATA-04 schema and NET-02 server; not yet implemented |

## 2. Schema, quantization, compression and spatial building blocks
| Candidate + upstream license | Rights summary to verify at pin | Pros & constraints for NET-03 |
|---|---|---|
| [Protocol Buffers](https://github.com/protocolbuffers/protobuf), [LICENSE](https://github.com/protocolbuffers/protobuf/blob/main/LICENSE) | **BSD-3-Clause-like Google Protobuf license** (no endorsement), runtime and extensions may have separate terms | explicit versioned schema/codegen and tagged fields, mature tooling; may be too header-heavy for high-frequency tiny bitpacked snapshots, not automatically a delta codec |
| [Google FlatBuffers](https://github.com/google/flatbuffers), [LICENSE](https://github.com/google/flatbuffers/blob/master/LICENSE) | **Apache-2.0**, separately audit code generator, dependencies and generated output | schema evolution, low-copy read potential, portable binary; not built-in per-recipient authority/interest/delta |
| [Zstandard / zstd](https://github.com/meta/zstd), [LICENSE](https://github.com/facebook/zstd/blob/dev/LICENSE) | reference library **dual BSD OR GPLv2**, exact path/file/distribution and option at pin | fast lossless compression, dictionaries; may add CPU/header/side-channel cost; compare real tiny packet sizes |
| [LZ4](https://github.com/lz4/lz4), [LICENSE](https://github.com/lz4/lz4/blob/dev/LICENSE) | **lib BSD-2-Clause**, CLI/tools typically **GPL-2.0-or-later**; do not redistribute CLI source accidentally | very fast lossless library, dictionary possible; no implicit wins for bitpacked snapshots or secret+attacker-text |
| [Zlib](https://github.com/madler/zlib), [LICENSE](https://github.com/madler/zlib/blob/develop/LICENSE) | **zlib license**; source/license exact pin | established baseline compression option, high ratio vs CPU/network byte axes require measurement |
| [EnTT](https://github.com/skypjack/entt), [LICENSE](https://github.com/skypjack/entt/blob/master/LICENSE) | **MIT** | entity change/observer architecture comparator, but WORLD-01 owns ECS and change journal |
| [Flecs](https://github.com/SanderMertens/flecs), [LICENSE](https://github.com/SanderMertens/flecs/blob/master/LICENSE) | **MIT** | change/graph query design comparator, no second ECS in NET-03 |
| [recastnavigation](https://github.com/recastnavigation/recastnavigation) | **Zlib license** (verify exact repo file) | navmesh spatial queries belong SIM/WORLD, not a network interest database |
| [OpenTelemetry C++](https://github.com/open-telemetry/opentelemetry-cpp), [LICENSE](https://github.com/open-telemetry/opentelemetry-cpp/blob/main/LICENSE) | **Apache-2.0** + transitive runtime licenses | optional redacted traces; game/peer private state may not be exported to public collector |

## 3. Technical selection matrix (hypotheses, no test)
| Design choice | Bandwidth/CPU implications | Security / operational gate |
|---|---|---|
| full per-client keyframe every network tick | simple resync, likely heavy bytes at scale | permitted fields only, still cannot broadcast secret |
| deltas vs per-peer acknowledged canonical baseline | fewer bytes if changes sparse, per-client memory and ACK CPU | baseline must bind client+world+role/visibility+schema/epoch; transport ACK not enough |
| dirty masks, quantized field profiles | compact and shared compute for public cohort | endian/float NaN/rounding/overflow, no lossy gameplay-truth reconstruction |
| per-peer spatial relevance via WORLD query | may reduce candidates from total entity count | authorization precedes interest and never bypassed for near objects |
| per-connection priority and age fairness | bounded bandwidth, some objects lower refresh | no starvation of lifecycle/revocation, no unbounded backlog |
| LZ4 or Zstd compression on authorized payload | may help large coherent data | compressor chosen only after CPU+small packet overhead tests, no mixed chosen plaintext and secrets side-channel |
| native QUIC datagram / GNS | best-effort snapshots and reliable lifecycle candidate | negotiated NET-01 caps, MTU, pacing, game ACK separate |
| WebTransport / WebRTC / WSS | browser platform differences | honest per-transport capability; reliable-only WSS cannot emulate unreliable packets |

## 4. Adoption and security checklist
- Exact source tag + blob/file license, SPDX/SBOM/NOTICE, crypto/network provider dependencies and generated-code obligations; *specification and code license are different*. Avoid source/asset import from proprietary engines and do not copy their sample screenshots/assets.
- DATA-04 versioned schema and NET-03 network codec ABI, endian/quantization/compatibility; evaluate encode/decode at actual CPU and target OS; wire format/public API not pinned.
- Security proof on actual decoded payload for permission matrix, absent fields and entity existence, across client role/scene/fog/ownership changes, policy version invalidation, compression length leak and cache cross-tenant. A buffer encrypted to wrong peer remains a leak.
- Confirm network MTU, packet size, throughput, loss and per-client fairness in NET-01 before scoring codec. Reject unknown codec/unsupported Web feature rather than claiming success.
- No tool/cloud/service selected, paid subscription or mandatory external reviewer. Engine license NLE-D009 and production technology choice both unresolved. All future coding WOs blocked.
