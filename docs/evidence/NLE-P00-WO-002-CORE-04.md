# Evidence Bundle — NLE-P00-WO-002-CORE-04

**Date:** 2026-11-14 | **Risk:** LOW for documentary research, future implementation risk STANDARD/ELEVATED.  
**Issue:** [#99](https://github.com/KayzenRoot/stormline/issues/99) | **PR:** [#100](https://github.com/KayzenRoot/stormline/pull/100).  
**Status:** APPROVED / MERGED for research docs only; no runtime code/build/release. ADR-0006 remains PROPOSED for implementation.

## Source, context and Git
- Baseline verified after queue reconciliation PR #98: main = `90eaf1b7cef148dfd168e3fa1ac8f7e9be603216`.
- Candidate research content commit: `e95953316947393f33574ddd73aa173a60f22155` (7 Markdown files).
- Branch: `docs/NLE-P00-WO-002-CORE-04-time-research`.
- Source Pack read in priority order; associated Git blob fingerprints at baseline:
  - Checkpoint: `0e2643924f5855b2cc9b28c45f461f22da6b9648`
  - Decisions Ledger: `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`
  - Scope: `4ef605c74632ece080b2650e37dd83a415b63310`
  - DoD: `160b3054db9ea1961308934b401488b838d24c3e`
  - Architecture: `f23c62e572f2f36fd664e786eeca164b72b882bb`
  - Requirements: `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`
  - ADR-0003: `2ee92dda5ab81ddcc446b9d5325d29257350e217`
  - ADR-0004: `e6c1639a96d6d484385476358bde50b38cc5b2ec`
  - ADR-0005: `6302ec933f89733d0f0ed7c1009059b2c0eb15f4`
- Fingerprints above are **Git blob SHAs, not SHA-256**. A future activated executor must capture SHA-256 Context Lock values anew. No false SHA-256 claim.

## Scoped changes
- New architecture `docs/architecture/core-04-time-simulation.md`: source abstraction, rational tick schedule, error/debt contract, server/offline semantics, deterministic scope and future tests.
- New matrix `docs/research/core-04-technology-matrix.md`: C++20 steady_clock, SDL3, Win QPC/native alternatives, sources and selection gates.
- New ADR `docs/adr/0006-core-04-time-policy.md`, PROPOSED only.
- New `docs/work-orders/NLE-P00-WO-002-CORE-04.md`.
- Linked/reconciled docs/04-architecture.md and docs/08-backlog.md; linked proposed research from still-blocked docs/queue/work-orders/CORE-04.md.
- This Evidence Bundle is the eighth documentation file. No C++, binary, shader, editor, physics, network, dependency lockfile, credential, service or user-facing release.

## Observed tests
- [GitHub Actions run #43596800522](https://github.com/KayzenRoot/stormline/actions/runs/43596800522) on exact research content HEAD `e95953316947393f33574ddd73aa173a60f22155`: workflow **Docs Validation**, job **docs-validation**, **SUCCESS**.
- Verified successful steps: Source Pack/local links; module catalog/DAG; 80-blocked-WO registry; Zcode selector rejection of blocked packet.
- Final audited HEAD `27eafe1d514d909a51470766eb4513d4bbf5ef40`: [CI run 43597153261](https://github.com/KayzenRoot/stormline/actions/runs/43597153261) **SUCCESS** (all four validation checks passed).
- Commands described by Work Order are for future/local reproducibility; this evidence does not falsely claim an independent local execution.

## Security, contracts and residual risk
- No paid service, CodeRabbit, secrets, external reviewer requirement, bypass or destructive Git action.
- Clock timing uses local monotonic samples, not calendar timestamps. Future editor/AI control passes only through an authorized command kernel; no direct MCP control added.
- Cross-platform numerical physics determinism, hardware timing precision, FPS, CPU use, server overload throughput and game playability **are not demonstrated**. The spec guarantees nothing about implemented behavior.
- Candidate SDL3 licensing and exact version/pinning/CVE scan remain future gates; no dependency added. Header/SDK choices remain PROPOSED.
- CORE-04 implementation issue #21 stays **BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS**, as all other executor packets do.
- 60 Hz, 4 catch-up steps and 250 ms are **test fixture candidates**, not approved real-world defaults or performance claims.

## Correction history
- Evidence commit `3cc51056559b32ffbf9e8da5837bf5866b423541` failed Docs Validation [run #43596956616](https://github.com/KayzenRoot/stormline/actions/runs/43596956616) because Markdown delimiters were accidentally escaped. Fixed in the same WO/PR; final-head CI must pass before approval. No source or runtime logic changed.

## Objective audit and proposed Checkpoint Delta
**Actual verdict: APPROVED for research documentation only**, on fixed HEAD `27eafe1d514d909a51470766eb4513d4bbf5ef40`, no known HIGH/CRITICAL documentary defect. [Portuguese audit comment on PR #100](https://github.com/KayzenRoot/stormline/pull/100#issuecomment-6877570942). Normal squash merge `17b1a4c75e87fcf424a6cf42f198e72c4da2ea9a` verified on main. The checkpoint is reconciled through this separate follow-up PR under the same WO; neither ADR-0006 nor coding issue #21 is promoted.
Checkpoint Delta applied after approved merge and readback:
1. Record NLE-P00-WO-002-CORE-04 research documentation as merged, link issue #99, PR #100, audited HEAD and final CI.
2. Retain ADR-0006 as **PROPOSED FOR IMPLEMENTATION**, not an approved engine ABI; implementation #21 remains BLOCKED.
3. State no clock code, native compile/benchmark, release, deploy or cross-platform numerical determinism.
4. Next candidate only after checkpoint reconciliation: NLE-P00-WO-002-CORE-05 research Math/Coordinates/Types; keep backlog order and independent module gates.

## 2026-11-16 minimal registry reconciliation — independent documentary evidence (in progress)
Pesquisa original [PR #100](https://github.com/KayzenRoot/stormline/pull/100) base `90eaf1b7cef148dfd168e3fa1ac8f7e9be603216`, HEAD `27eafe1d514d909a51470766eb4513d4bbf5ef40`, 8 arquivos afetados (5 ADDED/3 MODIFIED), [Docs CI #43597153261](https://github.com/KayzenRoot/stormline/actions/runs/43597153261) SUCCESS job #132453994310, [auditoria pt-BR #6877570942](https://github.com/KayzenRoot/stormline/pull/100#issuecomment-6877570942) APPROVED pesquisa documental, squash `17b1a4c75e87fcf424a6cf42f198e72c4da2ea9a`. Checkpoint histórico independente [PR #101](https://github.com/KayzenRoot/stormline/pull/101) base `17b1a4c75e87fcf424a6cf42f198e72c4da2ea9a`, HEAD `7a22759948e4fda7bddf74049e2cb809b8826950`, cinco Markdown MODIFIED, [Docs CI #43597376700](https://github.com/KayzenRoot/stormline/actions/runs/43597376700) SUCCESS job #132454681453, [auditoria pt-BR #6877601472](https://github.com/KayzenRoot/stormline/pull/101#issuecomment-6877601472) APPROVED documental, squash `c96fcc0d5e5094c84cd1e0af9085fba6849bcecb`. [Pesquisa #99](https://github.com/KayzenRoot/stormline/issues/99) CLOSED em 14/11/2026; [execução #21](https://github.com/KayzenRoot/stormline/issues/21) permanece OPEN/BLOCKED.

**Fonte de verdade e Context Lock:** BASE `40a6392360176c3bcb1b8b47e76a2d8fbe769def` (main observada), `docs/queue/implementation-registry.json` blob `9719aff73ff8d5e818f87fccdbe021dff2b58e18`, checkpoint blob `8f32a3ae83bf36b98b2b247ae7d5c88412a75a50`, backlog blob `aadeca8b02b0d61b7e762d0aabdbd5814984b34d`, WO futuro blob `35859e3d67527ebe1a9b35e205f86ee1fc278873`, Evidence blob `1932fd875f069d8f4fb4be20ec4f1eb6dba1f9f1`. Esses são Git blob SHA-1, não hashes SHA-256 de bytes; ativação futura exige novos fingerprints SHA-256 e aprovação do proprietário.

O único delta semântico do registro é `CORE-04.research_status: RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED`; **79 outros objetos completos e todos os campos raiz permanecem idênticos**. Depois de auditado e integrado, o registro indica **80/80 pesquisas documentadas (não implementadas)**, 80/80 futuros WOs `BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`, 0 `executor_ready`, 0 `approved_adr`, 80 classes de release UNDECIDED, engine_implemented=false. Dependência formal CORE-04 **CORE-01 somente**, ADR-0006 PROPOSED; NLE-D009 licença OPEN, NLE-D010 marca OPEN, NLE-D013 proíbe MVP público antes de DoD integral. Nada garante ABI, compilação, desempenho, determinismo numérico entre plataformas, sandbox ou aprovação de código.

**Lacuna não-bloqueante do status de pesquisa:** o CORE-04 foi aprovado no padrão de 14/11/2026, com contratos semânticos e testes conceituais na arquitetura, sem a padronização posterior de 128 casos por módulo ou contrato de API definitivo em arquivo separado. Não retroagir critérios documentais para reescrever pesquisa historicamente aprovada; essa lacuna permanece **BLOCKED como gate de implementação** e exige DoD/ADR final/contratos/testes/targets antes de Zcode. Green Docs CI não é benchmark ou teste de compilação/engine.

**Diff preflight:** five existing files MODIFIED only; registry exact one-line status replacement as verified by object-by-object comparison and unchanged root; no source code, runtime build, new ADR/API schema, release or right to redistribute. No new research issue; this is a canonical status correction of the already CLOSED issue #99, not a research re-execution.

**Own PR:** [#374](https://github.com/KayzenRoot/stormline/pull/374), [Docs Validation preliminar #43850298026](https://github.com/KayzenRoot/stormline/actions/runs/43850298026) **SUCCESS** para o HEAD inicial `2d0c49f72165800b00dd4d26bfd367969123a078`; após esta anotação documental, exigem-se **nova CI no HEAD final**, auditoria pt-BR, squash e main readback. A fonte final de evidência é o status público da PR #374 e os runs reais, não uma afirmação antecipada de aprovação. O run antigo #43596956616 falhou no PR #100 e foi corrigido naquele mesmo PR.
