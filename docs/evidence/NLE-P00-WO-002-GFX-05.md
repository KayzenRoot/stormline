# Evidence Bundle — NLE-P00-WO-002-GFX-05 (Research)

**Status:** RESEARCH DOCS APPROVED / MERGED; checkpoint reconciliation PR subject to separate exact-head CI and audit. No engine implementation, GPU image output or benchmark.  
**Research issue:** #135 | **Future code issue:** #33 remains BLOCKED  
**Base main:** `ace3355583dd1f83d2d483081184d665fa2229fa` | **Working branch:** `docs/NLE-P00-WO-002-GFX-05-materials-research`  
**Audited research PR final HEAD:** `084292f57182ec54fdde0a91cdf7f22f39c13ad2`; research squash main merge `694bb961066631f84a38008a268ede3bb7c60693`.  
**Risk:** LOW documentation; future ELEVATED runtime.

## Source check / context lock
- Git tree base verified: `ace3355583dd1f83d2d483081184d665fa2229fa`. Affected existing docs (prechange Git blob SHA): `docs/11-checkpoint.md` = `6001ba04dbb0cd52128188705da7ded81f74f53c`; `docs/03-scope.md` = `4ef605c74632ece080b2650e37dd83a415b63310`; `docs/09-definition-of-done.md` = `160b3054db9ea1961308934b401488b838d24c3e`; `docs/04-architecture.md` = `d43f848bc3a34bebe263311568fbaed29d94b329`; `docs/10-decisions-ledger.md` = `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`.
- These are Git **blob** object IDs, NOT byte SHA-256. Production Context Lock SHA-256 still unprepared because implementation WO #33 remains blocked.
- Previous research GFX-04 PRs #133/#134 integrated; ADR-0017 remains PROPOSED; research #135 is unique and code #33 separate.

## Intended documentation diff
Architecture `gfx-05-materials-textures-pbr.md`; matrix `gfx-05-material-technology-matrix.md`; ADR-0018; semantic API `gfx-05-material-texture-api.md`; 44 future tests; research WO; this bundle; minimal additive GFX-05 linkage in top-level architecture/backlog and blocked code packet.

## Research evidence, not native tests
Official Khronos glTF/PBR and KTX2/KHR_texture_basisu; KTX license exception `etcdec`; Basis Universal Apache-2.0/NOTICE with transitives; MaterialX 1.39.5 Apache-2.0; Khronos render fidelity samples with per-asset licenses (links in architecture/matrix). No dependency installed; no runtime compiled.

## Tests and CI
- Local Python docs validators: **NOT RUN locally**; GitHub docs-validation above is the actual observed CI proof at the specified SHA.
- GitHub Actions `Docs Validation` run [#43615938781](https://github.com/KayzenRoot/stormline/actions/runs/43615938781), job `docs-validation` **SUCCESS** at audited initial PR HEAD `4dc579507e1a7a7f5f78b85933a5e0e6e7200a2f`; final PR HEAD reverified at [CI #43616014685](https://github.com/KayzenRoot/stormline/actions/runs/43616014685) with SUCCESS.
- Future material/texture PBR-001..SYS-044: **NOT RUN**, designed only.
- Win/Linux/macOS/Web GPU, texture transcoding, fuzz, device-loss and benchmark: **NOT RUN**.
- Evidence on PR can be added as documented observed delta, not as claimed success in advance.

## Checkpoint reconciliation delta (this separate docs-only PR, pending its own audit/merge)
After research PR #136 APPROVED/merged at main `694bb961066631f84a38008a268ede3bb7c60693`, in this separate same-WO docs PR: set only `GFX-05.research_status` from `RESEARCH_PENDING` to `RESEARCH_DOCUMENTED_ADR_PROPOSED`, note research PR/CI in checkpoint and backlog, preserve implementation `work_order_status=BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`, `executor_ready=false`, all 80 blocked, no build/benchmark assertion. Next topological GFX-06.

## Risks / review
PBR transport portability, alpha/overdraw approximations, codec security, mixed license and third-party content rights require future actual proofs. Objective pt-BR reviewer must check diff/security/license and exact CI. Initial documentary risk assessment: 10 docs files; no code, no vendor/codec import; mixed-license KTX ETC flagged; MaterialX optional and Web feature gates explicit. Research PR #136 final-HEAD CI passed and objective pt-BR audit **APPROVED docs-only**; no HIGH/CRITICAL identified, normal squash merge confirmed. The new checkpoint PR requires **its own** exact-HEAD CI, objective audit and merge.

## Audit and merge receipts for research PR #136
- Initial proposal HEAD `4dc579507e1a7a7f5f78b85933a5e0e6e7200a2f` had docs CI [#43615938781](https://github.com/KayzenRoot/stormline/actions/runs/43615938781) SUCCESS; evidence corrected on same PR to final HEAD `084292f57182ec54fdde0a91cdf7f22f39c13ad2`.
- Final docs CI [#43616014685](https://github.com/KayzenRoot/stormline/actions/runs/43616014685) SUCCESS at exact final HEAD; check runs SonarCloud, Socket Security PR Alerts and Socket Security Project Report SUCCESS. Only 10 `docs/` files; `docs/queue/implementation-registry.json` untouched by research PR.
- Objective pt-BR audit comment on [PR #136](https://github.com/KayzenRoot/stormline/pull/136): APPROVED research documentation, no HIGH/CRITICAL known. Squash merge GitHub receipt `694bb961066631f84a38008a268ede3bb7c60693`. Future GPU/codec/benchmark tests NOT RUN.
