# Evidence Bundle — NLE-P00-WO-002-GFX-06 (Research)

**Status:** DRAFT / CI AND AUDIT NOT YET RECORDED | **Research #138** | **Future implementation #34 BLOCKED**  
**BASE main:** `59f044b9ac34411bbdd2f0170549bb4a9c78465e` | **Research branch:** `docs/NLE-P00-WO-002-GFX-06-lighting-research`  
**Final research HEAD / docs-validation run:** PENDING observational readback.  
**Risk:** LOW documentation, future ELEVATED GPU/temporal/codec/provenance security.

## Context fingerprints
Observed base main and canonical Git file objects (Git **blob** SHAs; NOT literal SHA-256 of file bytes). SHA-256 Context Lock is required before future code, **not claimed here**.
- `docs/11-checkpoint.md`: `214cf33ca4436327cf06c7c763b1e16ac75bdd3b`
- `docs/10-decisions-ledger.md`: `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`
- `docs/03-scope.md`: `4ef605c74632ece080b2650e37dd83a415b63310`
- `docs/09-definition-of-done.md`: `160b3054db9ea1961308934b401488b838d24c3e`
- `docs/04-architecture.md`: `0dd4e846c210b124a0aea66b83b6567ca94cdbb3`
- GFX-05 approved-docs checkpoint main: `59f044b9ac34411bbdd2f0170549bb4a9c78465e`; ADR-0018 still PROPOSED.

## Documentary research performed
Official Epic Lumen/VSM, GGG 2023 Radiance Cascades presentation + author WIP working paper, Vulkan/DXR/Metal/WebGPU feature specifications, AMD Brixelizer GI and MIT SDK description, NVIDIA RTXDI/RTXGI restrictive SDK license. Exact dependency tags, runtime redistribution, fixture rights and OS support remain future freeze decisions. No packages installed or source/assets from these engines copied.

## Proposed diff
New GFX-06 architecture/matrix/ADR-0019/API/68 future test cases/competitive protocol/research WO/Evidence Bundle; additive index entries to Architecture and Backlog plus existing GFX-06 code-packet research links. `docs/queue/implementation-registry.json` and checkpoint are NOT modified in research PR.

## Tests, clear truth
- GitHub Actions docs-validation: **PENDING**, never invent pass.
- All 68 future tests: **NOT EXECUTED**.
- No C++, shaders, Win/Linux/macOS/Web GPU smoke, fuzz, hardware GI screenshot, benchmark, compiler/linker, profiling, driver validation or executable engine.
- Current #34 BLOCKED; 80 total coding WOs `executor_ready=false` should remain so.

## Proposed checkpoint delta, NOT YET APPLIED
After research PR is reviewed/merged, create separate same-WO docs-only checkpoint PR: `GFX-06.research_status: RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED` ONLY; leave work-order status, risk, approved_adr and executor_ready unchanged, record research/CI/merge and next GFX-07 in checkpoint/backlog. Require separate exact-HEAD CI/objective audit and normal squash merge/readback.

## Security/license/portability risks
RTXDI and RTXGI license not MIT, alpha/animated caster cache correctness, VRAM page pressure, unsupported WebGPU RT, 3D Radiance Cascades extrapolation, source rights and GFX-03 fence misuse require future independent evidence. **No audit verdict asserted yet**.
