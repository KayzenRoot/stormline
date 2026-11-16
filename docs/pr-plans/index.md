# Stormline — 80 module future PR decomposition
DOCUMENTARY ONLY. 748 future candidate packet IDs; **zero actual implementation pull requests were opened**. BASE bc11813de9e8eb2bc7ffd4c2941b7b8653a23701; issue #381. No approved technical ADR, risk, release class or engine runtime. All 80 original coding WOs remain BLOCKED.
## Why plan instead of hundreds of live empty PRs?
Real PRs need nonempty code/docs diffs, owner-approved contracts, a fresh context lock and testable CI. Opening hundreds of stale placeholders conflicts with the one-increment-at-a-time governance. Packet IDs are stable but not GitHub PR numbers. Each future packet is PLANNED_BLOCKED, with github_pr null.
## 80 module directory
| Index | Module | Formal predecessors | Planned packet count | Original blocked issue |
|---:|---|---|---:|---|
| 0 | [CORE-01](CORE-01.md) Platform & Lifecycle | None | 16 | [#18](https://github.com/KayzenRoot/stormline/issues/18) |
| 1 | [CORE-02](CORE-02.md) Memory & Allocators | CORE-01 | 10 | [#19](https://github.com/KayzenRoot/stormline/issues/19) |
| 2 | [CORE-03](CORE-03.md) Jobs & Concurrency | CORE-02 | 10 | [#20](https://github.com/KayzenRoot/stormline/issues/20) |
| 3 | [CORE-04](CORE-04.md) Time & Simulation Clock | CORE-01 | 10 | [#21](https://github.com/KayzenRoot/stormline/issues/21) |
| 4 | [CORE-05](CORE-05.md) Math / Coordinates / Types | CORE-01 | 10 | [#22](https://github.com/KayzenRoot/stormline/issues/22) |
| 5 | [CORE-06](CORE-06.md) Diagnostics & Observability | CORE-01 | 10 | [#23](https://github.com/KayzenRoot/stormline/issues/23) |
| 6 | [DATA-01](DATA-01.md) Virtual File System | CORE-01 | 10 | [#24](https://github.com/KayzenRoot/stormline/issues/24) |
| 7 | [DATA-02](DATA-02.md) Asset Registry & Metadata | DATA-01 | 10 | [#25](https://github.com/KayzenRoot/stormline/issues/25) |
| 8 | [DATA-03](DATA-03.md) Import & Conversion Pipeline | DATA-02 | 10 | [#26](https://github.com/KayzenRoot/stormline/issues/26) |
| 9 | [DATA-04](DATA-04.md) Serialization & Scene Format | CORE-05, DATA-02 | 8 | [#27](https://github.com/KayzenRoot/stormline/issues/27) |
| 10 | [DATA-05](DATA-05.md) Cooking, Streaming Bundles & Patching | DATA-03, DATA-04 | 9 | [#28](https://github.com/KayzenRoot/stormline/issues/28) |
| 11 | [GFX-01](GFX-01.md) Graphics Abstraction (RHI) | CORE-01, CORE-02 | 10 | [#29](https://github.com/KayzenRoot/stormline/issues/29) |
| 12 | [GFX-02](GFX-02.md) Shader & Material Compilation | GFX-01, DATA-03 | 9 | [#30](https://github.com/KayzenRoot/stormline/issues/30) |
| 13 | [GFX-03](GFX-03.md) Render Graph & GPU Resource Manager | GFX-01, CORE-03 | 9 | [#31](https://github.com/KayzenRoot/stormline/issues/31) |
| 14 | [GFX-04](GFX-04.md) Geometry, Occlusion & LOD | GFX-03, DATA-05 | 10 | [#32](https://github.com/KayzenRoot/stormline/issues/32) |
| 15 | [GFX-05](GFX-05.md) Materials, Texture Systems & PBR | GFX-02, DATA-03 | 10 | [#33](https://github.com/KayzenRoot/stormline/issues/33) |
| 16 | [GFX-06](GFX-06.md) Lighting & Shadows | GFX-03, GFX-05 | 10 | [#34](https://github.com/KayzenRoot/stormline/issues/34) |
| 17 | [GFX-07](GFX-07.md) Camera, Color & Post-processing | GFX-06 | 10 | [#35](https://github.com/KayzenRoot/stormline/issues/35) |
| 18 | [GFX-08](GFX-08.md) VFX & Particle Graph | GFX-03, GFX-05 | 10 | [#36](https://github.com/KayzenRoot/stormline/issues/36) |
| 19 | [TWO-01](TWO-01.md) 2D Renderer & Canvas | GFX-01, DATA-03 | 10 | [#37](https://github.com/KayzenRoot/stormline/issues/37) |
| 20 | [TWO-02](TWO-02.md) Tilemaps & 2D Worlds | TWO-01, DATA-04 | 9 | [#38](https://github.com/KayzenRoot/stormline/issues/38) |
| 21 | [TWO-03](TWO-03.md) 2D Animation & Sequencing | TWO-01 | 9 | [#39](https://github.com/KayzenRoot/stormline/issues/39) |
| 22 | [TWO-04](TWO-04.md) 2.5D Hybrid Composition | TWO-01, GFX-04 | 8 | [#40](https://github.com/KayzenRoot/stormline/issues/40) |
| 23 | [WORLD-01](WORLD-01.md) Entity Component Model | CORE-05, DATA-04 | 9 | [#41](https://github.com/KayzenRoot/stormline/issues/41) |
| 24 | [WORLD-02](WORLD-02.md) Scene & Prefab Hierarchy | WORLD-01, DATA-02 | 9 | [#42](https://github.com/KayzenRoot/stormline/issues/42) |
| 25 | [WORLD-03](WORLD-03.md) Spatial Index & World Streaming | WORLD-02, DATA-05 | 8 | [#43](https://github.com/KayzenRoot/stormline/issues/43) |
| 26 | [WORLD-04](WORLD-04.md) Terrain & Environment | WORLD-03, GFX-04 | 10 | [#44](https://github.com/KayzenRoot/stormline/issues/44) |
| 27 | [WORLD-05](WORLD-05.md) Procedural Generation Framework | WORLD-04, DATA-03 | 10 | [#45](https://github.com/KayzenRoot/stormline/issues/45) |
| 28 | [SIM-01](SIM-01.md) Physics 2D | WORLD-01, TWO-01 | 10 | [#46](https://github.com/KayzenRoot/stormline/issues/46) |
| 29 | [SIM-02](SIM-02.md) Physics 3D | WORLD-02, CORE-03 | 10 | [#47](https://github.com/KayzenRoot/stormline/issues/47) |
| 30 | [SIM-03](SIM-03.md) Character Controller & Movement | SIM-01, SIM-02 | 8 | [#48](https://github.com/KayzenRoot/stormline/issues/48) |
| 31 | [SIM-04](SIM-04.md) Skeletal Animation & Motion | SIM-03, DATA-03 | 10 | [#49](https://github.com/KayzenRoot/stormline/issues/49) |
| 32 | [SIM-05](SIM-05.md) Navigation & Behavior | WORLD-03, SIM-02 | 8 | [#50](https://github.com/KayzenRoot/stormline/issues/50) |
| 33 | [SIM-06](SIM-06.md) Destruction & Environmental Response | SIM-02, GFX-08, WORLD-03 | 9 | [#51](https://github.com/KayzenRoot/stormline/issues/51) |
| 34 | [SIM-07](SIM-07.md) Vehicles & Flight Dynamics | SIM-02, SIM-03, GAME-01 | 10 | [#57](https://github.com/KayzenRoot/stormline/issues/57) |
| 35 | [AUD-01](AUD-01.md) Audio Device & Mixer | CORE-01, CORE-03 | 10 | [#52](https://github.com/KayzenRoot/stormline/issues/52) |
| 36 | [AUD-02](AUD-02.md) Spatial Audio & Acoustic World | AUD-01, WORLD-02 | 9 | [#53](https://github.com/KayzenRoot/stormline/issues/53) |
| 37 | [AUD-03](AUD-03.md) DSP & Sound Graph | AUD-01 | 9 | [#54](https://github.com/KayzenRoot/stormline/issues/54) |
| 38 | [AUD-04](AUD-04.md) Music, Dialogue & Cinematic Audio | AUD-03, AUD-02 | 8 | [#55](https://github.com/KayzenRoot/stormline/issues/55) |
| 39 | [GAME-01](GAME-01.md) Input & Control Mapping | CORE-01 | 8 | [#56](https://github.com/KayzenRoot/stormline/issues/56) |
| 40 | [GAME-02](GAME-02.md) Gameplay Scripting & API | WORLD-01, CORE-03 | 9 | [#58](https://github.com/KayzenRoot/stormline/issues/58) |
| 41 | [GAME-03](GAME-03.md) Game UI, Text & Localization | GFX-07, TWO-01 | 10 | [#59](https://github.com/KayzenRoot/stormline/issues/59) |
| 42 | [GAME-04](GAME-04.md) Gameplay Systems & Event Bus | GAME-02, GAME-01, WORLD-02 | 10 | [#60](https://github.com/KayzenRoot/stormline/issues/60) |
| 43 | [GAME-05](GAME-05.md) Genre Templates & Systems | GAME-04, SIM-04, AUD-04 | 10 | [#61](https://github.com/KayzenRoot/stormline/issues/61) |
| 44 | [NET-01](NET-01.md) Transport & Connection Layer | CORE-01 | 9 | [#62](https://github.com/KayzenRoot/stormline/issues/62) |
| 45 | [NET-02](NET-02.md) Authoritative Dedicated Server | NET-01, WORLD-01, CORE-04 | 8 | [#63](https://github.com/KayzenRoot/stormline/issues/63) |
| 46 | [NET-03](NET-03.md) Replication & Interest Management | NET-02, DATA-04 | 9 | [#64](https://github.com/KayzenRoot/stormline/issues/64) |
| 47 | [NET-04](NET-04.md) Prediction, Reconciliation & Lag | NET-03, SIM-03 | 8 | [#65](https://github.com/KayzenRoot/stormline/issues/65) |
| 48 | [NET-05](NET-05.md) Sessions & Lobby Interfaces | NET-01, NET-02 | 8 | [#66](https://github.com/KayzenRoot/stormline/issues/66) |
| 49 | [NET-06](NET-06.md) Network Security & Abuse Control | NET-02, NET-05 | 10 | [#67](https://github.com/KayzenRoot/stormline/issues/67) |
| 50 | [EDIT-01](EDIT-01.md) Editor Shell & Workspace | CORE-01 | 10 | [#68](https://github.com/KayzenRoot/stormline/issues/68) |
| 51 | [EDIT-02](EDIT-02.md) Project Creation & Management | EDIT-01, DATA-01 | 8 | [#69](https://github.com/KayzenRoot/stormline/issues/69) |
| 52 | [EDIT-03](EDIT-03.md) Scene/World/Terrain Editor | EDIT-02, WORLD-04 | 10 | [#70](https://github.com/KayzenRoot/stormline/issues/70) |
| 53 | [EDIT-04](EDIT-04.md) 2D & UI Editor | EDIT-02, TWO-02 | 8 | [#71](https://github.com/KayzenRoot/stormline/issues/71) |
| 54 | [EDIT-05](EDIT-05.md) Visual Shader & Material Graph | EDIT-02, GFX-05 | 8 | [#72](https://github.com/KayzenRoot/stormline/issues/72) |
| 55 | [EDIT-06](EDIT-06.md) VFX/Audio/Animation Authoring | EDIT-02, GFX-08, AUD-04, SIM-04 | 9 | [#73](https://github.com/KayzenRoot/stormline/issues/73) |
| 56 | [EDIT-07](EDIT-07.md) Debug, Profiling & Preview | EDIT-01, CORE-06 | 9 | [#74](https://github.com/KayzenRoot/stormline/issues/74) |
| 57 | [AI-01](AI-01.md) Headless Command Kernel | WORLD-02, DATA-04, GAME-02 | 8 | [#75](https://github.com/KayzenRoot/stormline/issues/75) |
| 58 | [AI-02](AI-02.md) Project Semantic Index | AI-01, DATA-02 | 10 | [#76](https://github.com/KayzenRoot/stormline/issues/76) |
| 59 | [AI-03](AI-03.md) Capability Registry & Schemas | AI-01 | 10 | [#77](https://github.com/KayzenRoot/stormline/issues/77) |
| 60 | [AI-04](AI-04.md) MCP Server & Protocol Adapter | AI-03 | 8 | [#78](https://github.com/KayzenRoot/stormline/issues/78) |
| 61 | [AI-05](AI-05.md) MCP Context Resources & Templates | AI-02, AI-04 | 10 | [#79](https://github.com/KayzenRoot/stormline/issues/79) |
| 62 | [AI-06](AI-06.md) Agent Security & Authorization | AI-04, AI-01 | 10 | [#80](https://github.com/KayzenRoot/stormline/issues/80) |
| 63 | [AI-07](AI-07.md) Transactional Planning & Undo | AI-01, AI-06 | 10 | [#81](https://github.com/KayzenRoot/stormline/issues/81) |
| 64 | [AI-08](AI-08.md) AI Authoring Workflows | AI-05, AI-07 | 10 | [#82](https://github.com/KayzenRoot/stormline/issues/82) |
| 65 | [AI-09](AI-09.md) AI Validation & Optimization | AI-07, CORE-06 | 8 | [#83](https://github.com/KayzenRoot/stormline/issues/83) |
| 66 | [PLAT-01](PLAT-01.md) Windows Desktop Target | GFX-01, GAME-01 | 8 | [#84](https://github.com/KayzenRoot/stormline/issues/84) |
| 67 | [PLAT-02](PLAT-02.md) Linux Desktop Target | GFX-01, GAME-01 | 8 | [#85](https://github.com/KayzenRoot/stormline/issues/85) |
| 68 | [PLAT-03](PLAT-03.md) Browser Runtime (WebAssembly/WebGPU/WebGL) | TWO-01, GFX-01, DATA-05 | 8 | [#86](https://github.com/KayzenRoot/stormline/issues/86) |
| 69 | [PLAT-06](PLAT-06.md) macOS Desktop Target (Apple Silicon + Intel compatibility) | CORE-01, GFX-01, GAME-01 | 10 | [#87](https://github.com/KayzenRoot/stormline/issues/87) |
| 70 | [PLAT-04](PLAT-04.md) Mobile Target Adaptation | GFX-01, GAME-01 | 9 | [#88](https://github.com/KayzenRoot/stormline/issues/88) |
| 71 | [PLAT-05](PLAT-05.md) Build, Export & Distribution | PLAT-01, PLAT-02, PLAT-03, PLAT-06, DATA-05 | 10 | [#89](https://github.com/KayzenRoot/stormline/issues/89) |
| 72 | [QA-01](QA-01.md) Build & Continuous Integration | CORE-01 | 10 | [#90](https://github.com/KayzenRoot/stormline/issues/90) |
| 73 | [QA-02](QA-02.md) Automated Functional & Visual Tests | QA-01, GFX-03 | 10 | [#91](https://github.com/KayzenRoot/stormline/issues/91) |
| 74 | [QA-03](QA-03.md) Performance Lab & Scalability Tiers | QA-02, CORE-06, GFX-08 | 9 | [#92](https://github.com/KayzenRoot/stormline/issues/92) |
| 75 | [QA-04](QA-04.md) Security, Fuzzing & Supply Chain | QA-01, NET-06, AI-06 | 10 | [#93](https://github.com/KayzenRoot/stormline/issues/93) |
| 76 | [QA-05](QA-05.md) Compatibility & Release Qualification | QA-02, PLAT-05 | 9 | [#94](https://github.com/KayzenRoot/stormline/issues/94) |
| 77 | [BIZ-01](BIZ-01.md) Commercial Licensing & Compliance | QA-05 | 10 | [#95](https://github.com/KayzenRoot/stormline/issues/95) |
| 78 | [BIZ-02](BIZ-02.md) SDK, Plugins & Developer Experience | GAME-02, AI-01 | 9 | [#96](https://github.com/KayzenRoot/stormline/issues/96) |
| 79 | [BIZ-03](BIZ-03.md) Release, Installer & Lifecycle | PLAT-05, BIZ-01, QA-04 | 9 | [#97](https://github.com/KayzenRoot/stormline/issues/97) |
## Future activation
G1 Scope/DoD and release class, G2 repo rules/CI, G3 toolchain ABI decisions, then G4/G5 per-module ADR/risk/contract/test proof and G6 authorized individual WO. Only after this may an executor create one real code PR, test, audit, squash/readback and move to the next.
CORE-01 is the unique dependency-free root, with 16 packet IDs and 12 feature implementation slices. This is provisional until the owner selects ABI/toolchain/support profiles.
[Process policy](../engineering/pr-decomposition-policy.md) | [Work Order](../work-orders/NLE-P00-GOV-003-PRMAP.md) | [Evidence](../evidence/NLE-P00-GOV-003-PRMAP.md).
