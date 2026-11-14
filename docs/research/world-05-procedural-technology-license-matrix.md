# WORLD-05 — Generator Algorithms, Determinism, Graph Tools and License Matrix

**Research issue #171 | NLE-P00-WO-002-WORLD-05 | ADR-0030 PROPOSED.** All choices are research candidates; no package, source art, graph node or shader installed and **no cross-platform benchmark executed**.

| Technique / provider | Classification / owner | Benefits and technical constraints | Verified rights / future acceptance |
|---|---|---|---|
| Stormline typed pure generator DAG, versioned algorithm/seed/precision + canonical CPU reference | NECESSARY WORLD-05 | stable contracts, deterministic provenance, no execution side effects; typed graph and budget complexity | original contracts, actual golden byte vectors later |
| Keyed/domain-separated counter RNG (e.g. Random123-style) | NECESSARY concept, OPTIONAL library | no shared mutable stream, robust under parallel task/region order; sequence/security not cryptographic | Random123 upstream BSD-style **pin exact LICENSE** if adopted; no arbitrary std::hash |
| FastNoiseLite noise: Perlin/Cellular/Value/warp/fBM | IMPORTANT optional CPU baseline adapter | portable C/C++ and shader variants, but float exactness/versions differ; some cellular output outside [-1,+1] | upstream **MIT**; NOTICE+version+test vector before use |
| OpenSimplex2/Fast/2S | IMPORTANT optional independent reference | 2D/3D/4D and seamless period domain ideas; algorithm/rounding and file-level rights differ | README states most files **CC0**, certain files **Unlicense**, audit selected exact files |
| Height/slope/altitude/biome field masks and domain warp combinations | NECESSARY original graph nodes | reproducible source proposals, requires units, sample grid, range/overflow handling | original implementation with numeric spec/golden |
| Stable point sampling/candidate thinning/vegetation placements | NECESSARY original graph nodes | local reproducibility, avoid global RNG/order coupling and collisions | bound max candidates/regions/ids and biome rights |
| Stable region/windowed cross-cell river and road graph | IMPORTANT conditional algorithms | cannot guarantee local tile independence without region halo/global constraint | explicit shared-region scope, no silent boundary artifacts |
| WaveFunctionCollapse (WFC) tile/constraint algorithms | OPTIONAL bounded graph node | can match local example patterns but may encounter contradictions, no guaranteed solution at arbitrary size | original project **MIT software**, **example tile artwork rights separate**; deterministic failure/budget |
| Procedural mesh/CSG/grammar production | FUTURE submodules or GFX-04 adapters | complex topology, curve/mesh generation, collision, source ownership and memory | do not conflate field+point graph with full CAD/NURBS engine |
| GPU generation or GPU preview | OPTIONAL feature gated | parallel speed hypothesis, float/non-deterministic race, different driver precision | GFX backend owns shader and GPU resources; not canonical unless exact golden pass |
| Worldgen/biome graph in Unreal Engine 5.8 PCG | REFERENCE ONLY | editor UX, graph and async world runtime concepts, rich ecosystem | **Epic proprietary engine**, no code, assets or built-in nodes copied |
| SideFX Houdini PDG/Houdini Engine | REFERENCE ONLY | procedural dependencies and caching by nodes, commercial authoring pipeline | **SideFX proprietary & licensed**, do not require runtime/license or copy HDA assets |
| Blender Geometry Nodes | REFERENCE ONLY | external user workflows and visual graph; baked interchange optional | Blender code/tool GPL and assets rights separate; no linked plugin/vendor copy assumed |
| SCDI canonical subgraph invalidation | OPTIONAL PROVE-OR-DROP | reduces recompute only if dependency/halo hashes exhaustive; stale generated content risks | compare full rebuild golden+performance under edited source |
| LLM/agent procedural rule proposals | FUTURE explicit user-approved authoring | unsafe nonreproducible scripts and licensing/model outputs; must compile to typed validated DSL | never execute arbitrary LLM code, quotas/rights/security + deterministic recipe freeze |

## License, source and determinism detail
- **FastNoiseLite** upstream LICENSE MIT; stable Godot class documents Perlin/Cellular/Value and warns noise may exceed [-1,1] for some cellular settings. An engine adapter must pin the exact algorithm version, code file license and floating profile; “MIT” does not prove CPU, HLSL, GLSL and WASM generate identical bits or samples.
- **OpenSimplex2** source README states most source is CC0, selected directories/files marked Unlicense. The exact used files and third-party contributions/lookup tables need per-file provenance and license receipt. Do not label the entire tree universally MIT or that CC0 equals patent guarantee.
- **WFC** upstream source LICENSE MIT, while README examples include independently credited or third-party tiles/patterns. WFC constraint contradictions are documented; deliberately bound max operations/backtracking/retries/solver memory, provide deterministic negative result and no guarantee the puzzle is solvable.
- **Random123** upstream counter-based RNG source is a possible BSD-style reference only; verify exact license release before source use. A counter PRNG is suitable for reproducible procedural content, **not** access tokens or cryptographic secrets, and seed hashing must use exactly encoded stable bytes.
- **Unreal PCG** and **SideFX Houdini PDG** are proprietary tooling/reference, not open vendor dependencies. A user with Houdini/Unreal license does not automatically grant copying node assets/mesh examples or distributing their SDK in Stormline. Blender GPL tool use does not automatically require every scene asset to be GPL, but linking/shipping code needs separate legal compliance.
- **No technology adopted**, so there is no locked algorithm version, byte portability guarantee, numeric deterministic bound, third-party notice/ SBOM, generated sample image/art/license or performance. Future owner needs explicit choice after CPU golden and memory/latency tests.
- Catalog guarantee is **same seed + full pinned recipe/version/input/source hashes + global scope + numeric profile**, not "a seed number alone makes any changed algorithm identical." DATA-04 manual overlay and source are distinct from generated proposal and retained across regeneration.

## Official research references (not installed, selected or executed)
- FastNoiseLite cross-platform noise library upstream, MIT license: https://github.com/Auburn/FastNoiseLite/blob/master/LICENSE
- Godot stable FastNoiseLite behavior and variable output range: https://docs.godotengine.org/en/stable/classes/class_fastnoiselite.html
- OpenSimplex2 README and mixed CC0 / Unlicense file notice: https://github.com/KdotJPG/OpenSimplex2/blob/master/README.md
- OpenSimplex2 per-file LICENSE and source: https://github.com/KdotJPG/OpenSimplex2/blob/master/LICENSE
- WaveFunctionCollapse MIT code license, examples/assets separately credited: https://github.com/mxgmn/WaveFunctionCollapse/blob/master/LICENSE
- WaveFunctionCollapse original README: constraint contradictions and NP-hardness note: https://github.com/mxgmn/WaveFunctionCollapse/blob/master/README.md
- Unreal Engine 5.8 PCG graph framework, proprietary engine reference: https://dev.epicgames.com/documentation/unreal-engine/procedural-content-generation-overview-for-unreal-engine?lang=pt-BR
- SideFX Houdini PDG node dependency concepts and proprietary licenses: https://www.sidefx.com/products/houdini/pdg/ and https://www.sidefx.com/Support/licensing/
- Random123 official counter-based RNG source, BSD-style license candidate subject to pinned review: https://github.com/DEShawResearch/random123
