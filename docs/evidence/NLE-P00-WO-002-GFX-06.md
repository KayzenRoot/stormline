# Evidence Bundle — NLE-P00-WO-002-GFX-06 (Research)

**Status:** RESEARCH DRAFT; FIRST OBSERVED CI SUCCESS, FINAL HEAD RECHECK PENDING | **Research #138** | **Future implementation #34 BLOCKED**  
**BASE main:** `59f044b9ac34411bbdd2f0170549bb4a9c78465e` | **Research branch:** `docs/NLE-P00-WO-002-GFX-06-lighting-research`  
**Initial research HEAD:** `b0c9e664cc7f94a4bd661bac59fa453d46d2a75d`. **Corrected research HEAD before evidence edit:** `8b7345c827ece2e487097c408fa7520be6866abf`. **Exact corrected HEAD docs-validation:** [run #43618269399](https://github.com/KayzenRoot/stormline/actions/runs/43618269399), SUCCESS. Final HEAD must be revalidated after this Evidence Bundle update.  
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
- GitHub Actions docs-validation observed at corrected HEAD `8b7345c827ece2e487097c408fa7520be6866abf`: **SUCCESS** [run #43618269399](https://github.com/KayzenRoot/stormline/actions/runs/43618269399). Socket Security PR Alerts and Project Report also SUCCESS on this SHA. New Evidence Bundle edit requires **another exact-HEAD CI**; do not reuse this run as proof for new head.
- All 68 future tests: **NOT EXECUTED**.
- No C++, shaders, Win/Linux/macOS/Web GPU smoke, fuzz, hardware GI screenshot, benchmark, compiler/linker, profiling, driver validation or executable engine.
- Current #34 BLOCKED; 80 total coding WOs `executor_ready=false` should remain so.

## Proposed checkpoint delta, NOT YET APPLIED
After research PR is reviewed/merged, create separate same-WO docs-only checkpoint PR: `GFX-06.research_status: RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED` ONLY; leave work-order status, risk, approved_adr and executor_ready unchanged, record research/CI/merge and next GFX-07 in checkpoint/backlog. Require separate exact-HEAD CI/objective audit and normal squash merge/readback.

## Security/license/portability risks
RTXDI and RTXGI license not MIT, alpha/animated caster cache correctness, VRAM page pressure, unsupported WebGPU RT, 3D Radiance Cascades extrapolation, source rights and GFX-03 fence misuse require future independent evidence. **No final audit verdict asserted until new final HEAD CI and diff review**. No high/critical identified by preliminary documentation review; this is not runtime security attestation.
