# NLE-EXEC-WO-GFX-02-001 — Shader & Material Compilation

**MODULE:** `GFX-02` | **STATE:** `BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS` | **RELEASE CLASS:** UNDECIDED  
**KIND:** FUTURE IMPLEMENTATION PACKET, **NOT AUTHORIZED FOR EXECUTION**.  
**Owner approval:** pending a module-level technical planning and audit.  
**Source:** [Module Catalog](../../product/module-catalog.md) | [Registry](../implementation-registry.json) | [Zcode protocol](../../engineering/zcode-handoff.md).

## OBJECTIVE
Implement an independently verifiable, production-grade first necessary increment for **Shader & Material Compilation** after detailed technology architecture has been approved. Current candidate capability: Linguagem/pipeline de shaders, reflexão, variantes, cache, compilação incremental.

## CONTEXT
Stormline is an original commercial 2D/2.5D/3D/Web engine with Windows/Linux/macOS editor and export targets, AI-native Editor/CLI/MCP parity, no public MVP. The approved catalog contains module `GFX-02`, but implementation details and release class are not yet approved.

## DEPENDENCIES
`GFX-01`, `DATA-03`. Require objective approval and integration evidence for every mandatory predecessor. Dependencies are **capability-level**, and may need finer-grained contract dependencies during module design.

## SCOPE
- Candidate functionality: Linguagem/pipeline de shaders, reflexão, variantes, cache, compilação incremental.
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
Measure GPU timing/VRAM/p95-p99, preserve fallback tiers and leave rendering independent from editor/server. Maintain explicit ownership, typed errors, versioning and platform isolation. Preserve headless server boundary and accessible editor/AI authoring operations when relevant; never expose privileged engine internals directly via MCP.

## CONSTRAINTS
- No engine implementation while P00 remains incomplete.
- Free public-repository CI, no CodeRabbit, no external human reviewer requirement and no bypass of branch/ruleset protections.
- Real platform performance must be measured on approved hardware, not assumed.
- No force-push, destructive operation, publication or paid service without explicit authorization.

## ACCEPTANCE CRITERIA
- [ ] **PRECONDITION:** Approved detailed module specification, technology/license/security ADR, release class, module API/schema, exact files and risk classification are linked.
- [ ] **PRECONDITION:** All predecessor Work Orders integrated; fresh Context Lock BASE SHA and SHA-256 fingerprints recorded.
- [ ] Candidate end-to-end demonstration: **Build determinístico, diagnóstico por arquivo/linha, variantes estáveis.**
- [ ] Build + unit + integration + error-path tests pass on relevant Windows/Linux/macOS/Web targets as defined in approved DoD (do not invent commands).
- [ ] Data integrity, performance/VRAM/RAM and regression/security gates for selected risk level pass with evidence.
- [ ] Editor/CLI/MCP coverage matrix reviewed where authoring capabilities exist; forbid unsafe raw-internal operations.
- [ ] Documentation, diagnostics, rollback and Evidence Bundle updated, audit APPROVED, PR merged without bypass.

## TESTS
Concrete commands, datasets, OS and hardware matrix: **TBD IN APPROVED TECHNICAL PLAN**. Candidate proof scenario: Build determinístico, diagnóstico por arquivo/linha, variantes estáveis. Reuse documented project-wide standard checks; risk-specific tests are additive. Never claim a check passed without run link/log.

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
