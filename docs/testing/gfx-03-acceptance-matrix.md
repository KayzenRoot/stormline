# GFX-03 — Future Render Graph and GPU Resource Acceptance Matrix

**Research WO:** NLE-P00-WO-002-GFX-03 | **Issue:** #129 | **State:** TEST SCENARIOS ONLY, **NOT EXECUTED**.
Real future tests must record exact C++/shader/bundle SHA, GPU API/OS/driver/SDK, adapter capacity or unknown, target profile, fixture license and CI/hardware-run traces. Mock/CPU tests do not prove actual GPU synchronization.

| ID | Risk | Future exercise | Required proof |
|---|---|---|---|
| RGP-001 | STANDARD | deterministic DAG with stable PassIds and two independent passes | same topology and stable tie-break plan across runs |
| RGP-002 | ELEVATED | cycle A->B->A, self-write/read invalid dependency | reject cycle with bounded path diagnostics, never submit GPU work |
| RGP-003 | ELEVATED | transient resource read before defining write/clear | hard `GRAPH_UNINITIALIZED_READ`, no undefined pixel usage |
| RGP-004 | ELEVATED | RAW overlapping texture mip/layer | correct hazard edge and stage/access visibility |
| RGP-005 | ELEVATED | WAR and WAW mixed writers across overlapping buffer ranges | deterministic dependencies, no missed write ordering |
| RGP-006 | STANDARD | RAR non-overlapping subresources / legal same-state read | coalesce without unsafe suppression of required barriers |
| RGP-007 | ELEVATED | out-of-bounds mip/layer/plane/buffer slice and bytes multiplication overflow | reject before allocation/driver with typed diagnostic |
| RGP-008 | STANDARD | pass with external presentation/readback side effects and dead-pass cull | observable pass always retained, unobservable dead pass safely removed |
| RGP-009 | STANDARD | ShaderReflectionV1 stage/bind layout mismatch | fail preflight with pass/resource IDs, no native command |
| RGP-010 | ELEVATED | Vulkan Synchronization2 RAW/WAW/queue ownership across graphics+transfer | Vulkan validation layers report no sync hazards on real adapter |
| RGP-011 | ELEVATED | D3D12 legacy transition/UAV/alias barriers | real D3D12 debug layer accepts tested graph with correct results |
| RGP-012 | STANDARD | D3D12 enhanced barrier optional support absent/present | legacy fallback on unsupported, proof of enhanced parity where supported |
| RGP-013 | ELEVATED | Metal native MTLHeap with tracked/untracked modes | actual Apple Silicon heap/fence tests, no undefined aliased reuse |
| RGP-014 | ELEVATED | WebGPU usage-scope conflicting sampled+attachment resource | browser validator rejects/splits safely, no invented native barrier |
| RGP-015 | STANDARD | WebGL2 degraded path for 2D/3D subset | explicit supported capabilities, no async compute parity |
| RGP-016 | ELEVATED | transient two resources same CPU DAG disjoint but async GPU overlap | reject alias until real queue/fence completion proof |
| RGP-017 | ELEVATED | 2-4 frames-in-flight with history/readback persistent across frame | no cross-frame alias corruption and correct history generation |
| RGP-018 | ELEVATED | alias incompatible format, alignment, heap/memory type | fallback separate allocation, no invalid native heap offsets |
| RGP-019 | ELEVATED | GPU fence never signaled / queue wait cycle | bounded timeout/restart-required, no permanent deadlock |
| RGP-020 | ELEVATED | device lost during allocate/submit or resize | invalidate resources/graph plan, no stale handle, safe replan or restart |
| RGP-021 | STANDARD | persistent DATA-05 streamed asset used alongside transient target | shared texture never aliased/evicted while pinned/in-flight |
| RGP-022 | ELEVATED | VRAM pressure, reported budget unknown or UMA shared memory | conservative reserve and explicit no-silent-data-loss failure |
| RGP-023 | STANDARD | optional postprocess under pressure and quality fallback | only authorized optional stages reduced, required depth/scene retained |
| RGP-024 | ELEVATED | allocation failure midway through frame-graph staging | rollback staged resources, no leaked GPU handles or half-success |
| RGP-025 | STANDARD | partial resize/dynamic resolution invalidates layout and plan cache | old in-flight generations retire correctly, no cross-resolution artifact |
| RGP-026 | STANDARD | 2D sprite atlas render with alpha/sRGB/golden image | correct resource transitions/pixel tolerance across real backends |
| RGP-027 | STANDARD | 2.5D hybrid layered passes + depth/sorting | correct graph dependencies and visual golden, no lost passes |
| RGP-028 | STANDARD | 3D depth/shadows/postfx and compute stages | cross-pass barrier/layout and golden fixtures with feature fallback |
| RGP-029 | ELEVATED | malicious graph via plugin/MCP with 1M passes / raw pointer / native callback | quota/capability denial, no GPU/OS side effect or private log leak |
| RGP-030 | ELEVATED | unsafe native alias after makeAliasable / stale GPU generation | driver validation/guards catch before corruption, crash/recovery behavior tested |
| RGP-031 | STANDARD | CPU graph compile and real GPU submit p50/p95/p99, peak VRAM & RSS | documented OS/GPU/driver/sample count + confidence envelopes, no unsupported claims |
| RGP-032 | STANDARD | VMA MIT, D3D12MA MIT, Apple SDK and Web target exact tags/SBOM | file-level legal notices, version & shipped binary proof |
| RGP-033 | STANDARD | SAFG R&D vs simple deterministic scheduler, no-alias and safe alias | same fixtures, pass correctness plus p95 stalls/bytes saved; drop if no measured benefit |
| RGP-034 | ELEVATED | GPU resource version change during GFX-02 hot reload and device reset | generation plan invalidation & fence-safe last-good pipeline, no invalid submit |

## Future verification structure
- **Structural CPU-only deterministic tests:** fuzz a rights-cleared `RenderGraphDefinitionV1` corpus (mixed 2D/2.5D/3D) and compare generated edges, stable topological schedule, alias compatibility, stage/barrier sets. This can run headlessly but makes **zero** driver-correctness claims.
- **Native API conformance:** Windows Vulkan + D3D12 legacy/enhanced conditional; Linux Vulkan Mesa/vendor; macOS Apple Silicon native Metal MTLHeap/fence; Web browser WebGPU usage scopes and reduced WebGL2. Tests require real hardware/driver/device reset and exact runner fingerprint.
- **Fault injection:** forced GPU device loss, memory exhaustion, invalid shader reflection/format, timeout/queue deadlock, frame-in-flight schedule overlaps, resize/hot reload and async readback. Maintain full evidence, no success on partial GPU completion.
- **Security:** malicious pass DAG, oversized subresources/format overflow, untrusted plugin graph, arbitrary MCP command/resource pointer, privacy of GPU diagnostics; only authorized read-only semantic preview.
- **Performance:** compare full no-alias+serial baseline, conservative alias-only and optional async queues on identical fixture corpus/hardware, record CPU graph compilation, p50/p95/p99 frame-time and GPU stall/submit latency, transient peak, residency peak, alias bytes saved, allocation fragmentation/driver memory budget confidence and thermal/power where possible.
- **Legal/supply chain:** exact VMA/D3D12MA MIT tags and shipped files, SDK license requirements, Apple toolchain, validated transitive dependency notices, original asset fixture rights.
- **Existing CI:** GitHub public docs-validation checks only Source Pack/links, module DAG, 80 registry and blocked selector. No GPU test runner, C++ build or real VRAM benchmark runs exist now.

**RGP-001..RGP-034 ALL NOT EXECUTED.** The table states *future acceptance*, not completed graphics performance.
