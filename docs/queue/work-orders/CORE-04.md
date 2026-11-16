# NLE-EXEC-WO-CORE-04-001 — Time & Simulation Clock

**MODULE:** `CORE-04` | **STATE:** `BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS` | **RELEASE CLASS:** UNDECIDED  
**KIND:** FUTURE IMPLEMENTATION PACKET, **NOT AUTHORIZED FOR EXECUTION**.  
**Owner approval:** pending a module-level technical planning and audit.  
**Source:** [Module Catalog](../../product/module-catalog.md) | [Registry](../implementation-registry.json) | [Zcode protocol](../../engineering/zcode-handoff.md).

## OBJECTIVE
Implement an independently verifiable, production-grade first necessary increment for **Time & Simulation Clock** after detailed technology architecture has been approved. Current candidate capability: Tempo real, tick fixo, interpolação, pausa, stepping, replay determinístico onde exigido.

## CONTEXT
Research-only prerequisites (do not lift this BLOCKED status): [CORE-04 clock architecture](../../architecture/core-04-time-simulation.md), [matrix](../../research/core-04-technology-matrix.md), [ADR-0006 PROPOSED](../../adr/0006-core-04-time-policy.md), and [research WO](../../work-orders/NLE-P00-WO-002-CORE-04.md). These are not approved executable API/file/test contracts.

Stormline is an original commercial 2D/2.5D/3D/Web engine with Windows/Linux/macOS editor and export targets, AI-native Editor/CLI/MCP parity, no public MVP. The approved catalog contains module `CORE-04`, but implementation details and release class are not yet approved.

## DEPENDENCIES
`CORE-01`. Require objective approval and integration evidence for every mandatory predecessor. Dependencies are **capability-level**, and may need finer-grained contract dependencies during module design.

## SCOPE
- Candidate functionality: Tempo real, tick fixo, interpolação, pausa, stepping, replay determinístico onde exigido.
- Final first implementable slice, interfaces and concrete files **must be filled by the planner and audited** before this draft is promoted.
- Integration with other approved modules only through versioned contracts.
- Minimal internal harness, diagnostics and tests for the approved acceptance criteria.

## OUT OF SCOPE
No unapproved subfeatures, unrelated cleanup, "all modules at once", public MVP, paid CI, mandatory outside reviewer, CodeRabbit, protected third-party game content or speculative architecture decisions. Zcode does not choose the product stack.

## FILES / SOURCES TO READ
Read in canonical order: `docs/11-checkpoint.md`, `docs/10-decisions-ledger.md`, applicable approved ADRs, `docs/03-scope.md`, `docs/09-definition-of-done.md`, `docs/04-architecture.md`, `docs/02-requirements.md`, `AGENTS.md`, this module specification (path **TBD**), [Module Catalog](../../product/module-catalog.md) and [Zcode protocol](../../engineering/zcode-handoff.md). Actual source file paths: **TBD BY PLANNER, NOT ZCODE**.

## REQUIREMENTS
Global GOV-001..005, CAP-009 performance, CAP-010 extensibility, NFR-001..005 and NLE-D013..018 where applicable. Specific requirement IDs / user story traces: **TO BE SPECIFIED AND APPROVED**.

## ARCHITECTURE RULES
Core interfaces must not import editor/graphics/networking; headless operation and Windows/Linux/macOS interfaces stay portable. Maintain explicit ownership, typed errors, versioning and platform isolation. Preserve headless server boundary and accessible editor/AI authoring operations when relevant; never expose privileged engine internals directly via MCP.

## CONSTRAINTS
- No engine implementation while P00 remains incomplete.
- Free public-repository CI, no CodeRabbit, no external human reviewer requirement and no bypass of branch/ruleset protections.
- Real platform performance must be measured on approved hardware, not assumed.
- No force-push, destructive operation, publication or paid service without explicit authorization.

## ACCEPTANCE CRITERIA
- [ ] **PRECONDITION:** Approved detailed module specification, technology/license/security ADR, release class, module API/schema, exact files and risk classification are linked.
- [ ] **PRECONDITION:** All predecessor Work Orders integrated; fresh Context Lock BASE SHA and SHA-256 fingerprints recorded.
- [ ] Candidate end-to-end demonstration: **Reproduzir ticks consistentes com FPS variáveis.**
- [ ] Build + unit + integration + error-path tests pass on relevant Windows/Linux/macOS/Web targets as defined in approved DoD (do not invent commands).
- [ ] Data integrity, performance/VRAM/RAM and regression/security gates for selected risk level pass with evidence.
- [ ] Editor/CLI/MCP coverage matrix reviewed where authoring capabilities exist; forbid unsafe raw-internal operations.
- [ ] Documentation, diagnostics, rollback and Evidence Bundle updated, audit APPROVED, PR merged without bypass.

## TESTS
Concrete commands, datasets, OS and hardware matrix: **TBD IN APPROVED TECHNICAL PLAN**. Candidate proof scenario: Reproduzir ticks consistentes com FPS variáveis. Reuse documented project-wide standard checks; risk-specific tests are additive. Never claim a check passed without run link/log.

## DELIVERABLES
Scoped code and tests, API and data contracts, updated documentation, deterministic build/benchmark evidence if applicable, PR, CI, pt-BR audit and **proposed** Checkpoint Delta; actual artifacts only after execution.

## REVIEW FORMAT
Final review in Brazilian Portuguese; severities, base/head SHA, test commands and outcomes, regression/security/license notes, diff, remaining risks and explicit `APPROVED / CORRECTION REQUIRED / BLOCKED` verdict.

## STOP CONDITION
Immediately BLOCKED while any `TBD`, incomplete approved ADR, missing dependency, stale Context Lock, HIGH/CRITICAL defect, unapproved cost, absent OS/AI contracts, or failed required test remains. Do not create a code branch just because this draft exists.

## CONTEXT LOCK
Base commit SHA: **TBD AT ACTIVATION**. Source hash fingerprints: **TBD AT ACTIVATION**. New checkpoint/Scope/DoD/Architecture/ADR invalidates the packet until reconfirmed.

## EVIDENCE BUNDLE
Future executor records base/head SHA, changed files, dependency provenance, commands and real outputs, builds/lint/typecheck/tests/benchmarks, security and licensing, error/correction log, risk, rollback and proposed checkpoint delta. No evidence exists yet.

**Status reminder:** this is a **prepared shell**, not an executable Work Order. Technology and API decisions remain with the architecture/planning flow; Zcode's role starts only after the package is fully approved.

## CORE-04 documentary research status reconciliation (2026-11-16) — STILL BLOCKED FOR ZCODE
Pesquisa original [PR #100](https://github.com/KayzenRoot/stormline/pull/100) base `90eaf1b7cef148dfd168e3fa1ac8f7e9be603216`, HEAD `27eafe1d514d909a51470766eb4513d4bbf5ef40`, 8 arquivos afetados (5 ADDED/3 MODIFIED), [Docs CI #43597153261](https://github.com/KayzenRoot/stormline/actions/runs/43597153261) SUCCESS job #132453994310, [auditoria pt-BR #6877570942](https://github.com/KayzenRoot/stormline/pull/100#issuecomment-6877570942) APPROVED pesquisa documental, squash `17b1a4c75e87fcf424a6cf42f198e72c4da2ea9a`. Checkpoint histórico independente [PR #101](https://github.com/KayzenRoot/stormline/pull/101) base `17b1a4c75e87fcf424a6cf42f198e72c4da2ea9a`, HEAD `7a22759948e4fda7bddf74049e2cb809b8826950`, cinco Markdown MODIFIED, [Docs CI #43597376700](https://github.com/KayzenRoot/stormline/actions/runs/43597376700) SUCCESS job #132454681453, [auditoria pt-BR #6877601472](https://github.com/KayzenRoot/stormline/pull/101#issuecomment-6877601472) APPROVED documental, squash `c96fcc0d5e5094c84cd1e0af9085fba6849bcecb`. [Pesquisa #99](https://github.com/KayzenRoot/stormline/issues/99) CLOSED em 14/11/2026; [execução #21](https://github.com/KayzenRoot/stormline/issues/21) permanece OPEN/BLOCKED.

O único delta semântico do registro é `CORE-04.research_status: RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED`; **79 outros objetos completos e todos os campos raiz permanecem idênticos**. Depois de auditado e integrado, o registro indica **80/80 pesquisas documentadas (não implementadas)**, 80/80 futuros WOs `BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`, 0 `executor_ready`, 0 `approved_adr`, 80 classes de release UNDECIDED, engine_implemented=false. Dependência formal CORE-04 **CORE-01 somente**, ADR-0006 PROPOSED; NLE-D009 licença OPEN, NLE-D010 marca OPEN, NLE-D013 proíbe MVP público antes de DoD integral. Nada garante ABI, compilação, desempenho, determinismo numérico entre plataformas, sandbox ou aprovação de código.

**Lacuna não-bloqueante do status de pesquisa:** o CORE-04 foi aprovado no padrão de 14/11/2026, com contratos semânticos e testes conceituais na arquitetura, sem a padronização posterior de 128 casos por módulo ou contrato de API definitivo em arquivo separado. Não retroagir critérios documentais para reescrever pesquisa historicamente aprovada; essa lacuna permanece **BLOCKED como gate de implementação** e exige DoD/ADR final/contratos/testes/targets antes de Zcode. Green Docs CI não é benchmark ou teste de compilação/engine.

`NLE-EXEC-WO-CORE-04-001` issue #21 remains OPEN/BLOCKED with context_lock_sha=null, risk UNCLASSIFIED, release class UNDECIDED, approved_adr=null, executor_ready=false and all implementation acceptance checkboxes pending. Only research_status is reconciled. Research completed is **NOT** an authority to code or install dependencies.
