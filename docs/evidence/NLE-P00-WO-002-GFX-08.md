# Evidence Bundle — NLE-P00-WO-002-GFX-08 Research

**Status:** RESEARCH PR OPEN, INITIAL EXACT-HEAD DOCS CI SUCCESS, FINAL HEAD CI/AUDIT PENDING | **Research #144** | **Implementation #36 BLOCKED**  
**BASE main:** `729f111d30fe927107f42fe6e4b951d17f357e10` | **Branch:** `docs/NLE-P00-WO-002-GFX-08-vfx-research`. No library, scene assets, graphics code, test, demo or benchmark created.

## Context and sources
- Checked canonical `docs/11-checkpoint.md` -> decisions/ADRs -> scope -> DoD -> architecture -> requirements, approved catalog, registry, GFX-03/05/06/07 and blocked #36 packet. Main `729f111d30fe927107f42fe6e4b951d17f357e10`, GFX-07 research #141/PRs #142/#143 completed. **80 code WOs BLOCKED** and 0 executor-ready before changes.
- Public sources checked: Epic Niagara runtime scalability notes, Godot GPU/CPU and trail behavior, Effekseer MIT `LICENSE` and backend license guide, AMD FidelityFX Parallel Sort MIT Vulkan/DX12, OpenVDB Apache-2.0 license, W3C WebGPU. Versions/source rights/third-party artifacts not frozen.
- Proposed 11-file diff (8 new research documents plus links to Architecture, Backlog and `docs/queue/work-orders/GFX-08.md`). No registry or checkpoint edit in initial research PR. Future separate checkpoint PR may alter **only** `GFX-08.research_status` to `RESEARCH_DOCUMENTED_ADR_PROPOSED` after doc audit/merge.
- Research subjects: typed VFX graph + bounded subemitters, CPU/GPU hybrid with WebGL2 fallback, ribbons/trails/alpha/overdraw, GPU sort/OIT optional, GFX-06 light/volumetric and GFX-07 HDR/motion reactives, secure Editor/CLI/MCP, SVAG prove-or-drop.

## Truthful evidence status
- [Research PR #145](https://github.com/KayzenRoot/stormline/pull/145) BASE `729f111d30fe927107f42fe6e4b951d17f357e10`; initial HEAD `b13299c23040b6172617a542eafd8a74b61cf56d`, 11 scoped `docs/` files. [Docs Validation run #43625459746](https://github.com/KayzenRoot/stormline/actions/runs/43625459746) **SUCCESS on initial exact HEAD**. This Evidence Bundle update requires NEW final-head CI before audit; do not reuse initial result as final proof.
- Research objective pt-BR audit, risk, merge SHA and main readback: **PENDING**.
- All 78 future tests, GPU/C++/WebGL2/Metal/Vulkan builds, visual screenshot, ARPG FPS p50/p95/p99, fuzz, shader variants and license source vendoring: **NOT EXECUTED**.
- Future implementation #36 remains blocked; ADR-0021 PROPOSED, numeric target/release class and exact hardware UNDECIDED. No claim of superiority to Unreal/GGG or commercial effect delivery.

## Observed Git file object fingerprints (NOT raw-file SHA-256)
- `docs/11-checkpoint.md`: `d8c73f69445d0bd56d8cf7ab2eacff63df0c4baf`
- `docs/10-decisions-ledger.md`: `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`
- `docs/03-scope.md`: `4ef605c74632ece080b2650e37dd83a415b63310`
- `docs/09-definition-of-done.md`: `160b3054db9ea1961308934b401488b838d24c3e`
- `docs/04-architecture.md`: `5ac0dad7c9bb4f5908954111a18204a4052fd126`
- `docs/queue/work-orders/GFX-08.md`: `7eed4db88232ab5f02aa27ab27959487e6d3f8b5`
Git blob hashes only; the executor must later compute **actual SHA-256 bytes** and recompile Context Lock on any canonical source update.

## Next checkpoints (proposed only)
Exact-head CI, diff security/license checks and review on research PR -> normal squash merge -> separate same-WO checkpoint/registry PR -> exact head CI/audit/merge -> verify main and issue close. Never automatically authorize code or advance before final reconciliation.
