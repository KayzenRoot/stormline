# Research Work Order — NLE-P00-WO-002-GFX-01

**Research issue:** #123 | **Future implementation issue:** #29 BLOCKED | **Date:** 2026-11-14  
**State:** APPROVED / MERGED FOR RESEARCH DOCS ONLY (PR #124) | **ADR-0014:** PROPOSED / NO ENGINE CODE  
**Context Lock BASE main:** `36f08368be2c1d1cdd8aa7bd553f4fed7d610d56` after DATA-05 checkpoint PR #122. Risk LOW docs, future ELEVATED native GPU.

## OBJECTIVE
Specify Stormline's cross-platform, capability-driven graphics Render Hardware Interface for Windows/Linux/macOS native, Web browser and headless, including backends, lifecycle, GPU resource/sync/feature tiers, recovery, secure Editor/CLI/MCP inspection, technology evaluation and future real GPU proof. Make later Zcode code work deterministic and architecture-led without selecting untested vendor stacks.

## CONTEXT
Owner vision: fully functional 2D/2.5D/3D/Web engine, Editor and exports Windows/Linux/macOS (Apple Silicon mandatory), AI-native MCP scoped, no public MVP until v1.0 DoD; zero mandatory paid CI, solo audited PRs. P00 architecture documentation only. CORE-01/02 research approved/documented (not code); existing 80 implementation WOs BLOCKED.

## SCOPE
- Compare thin custom C++20 RHI against SDL3 GPU, bgfx, native Vulkan Windows/Linux, native Metal macOS, D3D12 optional Windows, Dawn/wgpu-native WebGPU adaptation, browser WebGPU and WebGL2 fallback.
- Document Khronos current MoltenVK deprecation and KosmicKrisp Apple Silicon guidance, Intel macOS conditions and native Metal baseline.
- Device/adapters/queues/resource descriptors and generational handles/command encoding/fence/sync/presentation; GPU device-loss/restart-safe recovery.
- Independent feature sets and quantitative limits; CPU-GPU budgets; 2D/2.5D/3D shared ABI, explicit clip-space/coordinate transforms, color/alpha, shader pipeline boundaries with GFX-02/03.
- Typed GpuDevice/Adapter/Resource/Surface/Errors, read-only scoped semantic Editor/CLI/MCP introspection; no raw driver commands.
- Matrix of library/API compatibility/license/risk/performance, ADR-0014 PROPOSED, 28 future tests, SCGF prove-or-drop, Evidence Bundle, links and audit/CI.

## OUT OF SCOPE
No C++, GPU SDK install, GPU test run, shader compilation, framebuffer rendering, GFX-02/03 implementation, image/VRAM benchmark, signed release, production browser, cloud service, proprietary driver, paid CI/CodeRabbit, mandatory external reviewer, bypass, force-push or extra unrelated module.

## FILES / SOURCES TO READ
Canonical: `docs/11-checkpoint.md` > `docs/10-decisions-ledger.md` / approved ADRs > `docs/03-scope.md` > `docs/09-definition-of-done.md` > `docs/04-architecture.md` > `docs/02-requirements.md` > `docs/00-source-hierarchy.md`; `AGENTS.md`, Module Catalog/registry, CORE-01/02, CORE-05/06, DATA-05 architecture/contracts, `docs/queue/work-orders/GFX-01.md` and #29, official Vulkan/Khronos/SDL/Apple/Microsoft/Dawn/wgpu/bgfx/MDN sources.

## REQUIREMENTS
GOV-001..005, CAP-001/002/004/008/009/010/011/012/013/014/016, NFR-001..005; owner decisions NLE-D013..020, catalog GFX-01 acceptance: resource lifetime, device loss/recovery, API validation in future. Release class UNDECIDED and 1.0 feature tiers pending.

## ARCHITECTURE RULES
- Platform lifecycle CORE-01; CPU memory CORE-02; world coordinates CORE-05; diagnostics CORE-06; DATA-05 cooked asset capability variants.
- GFX-01 only low-level RHI, shader compile GFX-02, render graph/VRAM transient hazards GFX-03, high-end render techniques GFX-04+. Do not duplicate.
- Explicit native GPU capability queries/limits and fallback, no global Vulkan-on-Mac shortcut or WebGPU always-available promise.
- No native third-party GPU type exposed via Stormline public interface; typed generation handles, checked resource lifetime/sync, device-lost safe-fail.
- Editor/CLI/MCP inspect/preview authorized with redacted metadata, never arbitrary driver/shader/native pointer execution.
- Exact licenses, tags and SBOM before including deps; physical platform support confirmed with real hardware/CI and traces before any performance claim.

## CONSTRAINTS
P00 research-only docs; free GitHub docs-validation, no C++/shader install or fake build; zero mandatory external reviewer or CodeRabbit, no paid service, no credentials, no unapproved release or bypass. Stop upon stale main/Scope/DoD/architecture/ADR or HIGH/CRITICAL.

## ACCEPTANCE CRITERIA
- [ ] Architecture provides RHI responsibility/lifecycle/resource/fence/feature tiers and 2D/3D/Web target boundaries.
- [ ] Matrix compares SDL3 GPU, native Vulkan/D3D12/Metal, bgfx, Dawn/wgpu-native, browser WebGPU/WebGL2; accurately records MoltenVK deprecation/KosmicKrisp guidance and license gates.
- [ ] ADR-0014 remains PROPOSED; API typed adapters/devices/resources/sync/surfaces/loss reports and scoped MCP commands.
- [ ] At least 20 future scenarios (28 specified) incl Windows/Linux/macOS/Web/headless, device lost, resource hazards, NDC, image goldens, benchmarks, license/privacy and MCP denial.
- [ ] No C++/shader/SDK runtime work; future #29 and all 80 code WOs BLOCKED/executor_ready=false.
- [ ] Free GitHub docs-validation SUCCESS on final exact HEAD; Evidence Bundle, diff + objective pt-BR review no HIGH/CRITICAL.
- [ ] After audit, normal squash merge/readback and checkpoint reconciliation in **same WO**, separate audited docs PR before GFX-02.

## TESTS
Current docs CI: Source Pack/links, module taxonomy DAG, 80-WO registry and read-only selector refuses blocked. RHI-001..028 are **future NOT RUN**, no real GPU or Windows/Linux/macOS/Web hardware tests.

## DELIVERABLES
`docs/architecture/gfx-01-graphics-rhi.md`; `docs/research/gfx-01-rhi-technology-matrix.md`; `docs/adr/0014-gfx-01-rhi-backends.md`; `docs/contracts/gfx-01-rhi-api.md`; `docs/testing/gfx-01-acceptance-matrix.md`; research WO; Evidence Bundle; Architecture/Backlog/blocked packet links; audited PR; proposed Checkpoint Delta.

## REVIEW FORMAT
pt-BR objective APPROVED / CORRECTION REQUIRED / BLOCKED with base/head SHA, exact doc diff, CI run, license/security/feature/driver risks, missing real hardware, source fingerprints and checkpoint delta; no false feature delivery.

## STOP CONDITION
Stop for STALE context, incomplete requirement/source, prohibited library/license, unsafe MCP/native privileges, unverified GPU/driver compatibility advertised as real, failed CI, known HIGH/CRITICAL, secret/paid/dangerous action, scope creep or implementation branch. Corrections stay same WO/PR; no next increment before approval.

## CONTEXT LOCK
BASE `36f08368be2c1d1cdd8aa7bd553f4fed7d610d56`. Capture critical source Git blob fingerprints in Evidence Bundle **label Git hashes, not file SHA-256**. At future code activation require fresh SHA-256 of actual source bytes and approved technology/Scope/DoD/precedent code.

## CHECKPOINT
After approved docs PR squash merge/readback, reconcile Checkpoint/Backlog/research WO/Evidence/registry `GFX-01.research_status` in separate audited docs PR of the **same** WO; ADR-0014 PROPOSED and #29/other 79 WOs BLOCKED.
