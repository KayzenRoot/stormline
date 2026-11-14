# NLE-EXEC-WO-TWO-01-001: 2D Renderer & Canvas
**STATUS: BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS. NOT EXECUTOR_READY.** **Release:** UNDECIDED. **Module:** `TWO-01`.
[Catalog](../../product/module-catalog.md) | [Registry](../implementation-registry.json) | [Zcode Handoff](../../engineering/zcode-handoff.md).

## OBJECTIVE
Deliver the first **approved**, independently testable implementation increment for the 2D Renderer & Canvas capability, after architecture, technology and DoD are locked. Candidate feature: Sprites, atlases, layers, câmera, pixel snapping, lights, shadows e batching.

## CONTEXT
Stormline is a planned original 2D/2.5D/3D/Web game engine, Windows/Linux/macOS editor+export, human and MCP authoring, no public MVP. This draft is **not** authorization to code.

## RESEARCH CONTEXT ONLY (NOT EXECUTOR READY)
[TWO-01 architecture](../../architecture/two-01-renderer-canvas.md), [technology/license research](../../research/two-01-renderer-technology-license-matrix.md), [ADR-0022 PROPOSED](../../adr/0022-two-01-native-2d-renderer-policy.md), [typed Canvas API](../../contracts/two-01-canvas-api.md), [81 FUTURE NOT RUN tests](../../testing/two-01-acceptance-matrix.md), [reproducible 2D benchmark](../../research/two-01-benchmark-protocol.md), [research WO](../../work-orders/NLE-P00-WO-002-TWO-01.md) and [Evidence Bundle](../../evidence/NLE-P00-WO-002-TWO-01.md) are proposals only, **not** approved implementation contracts or C++/GPU source. Font/Rive rights, exact ABI, dependencies GFX-01/DATA-03 and target hardware 60FPS proof TBD. #37 and all 80 future code WOs remain BLOCKED/`executor_ready=false`.

## DEPENDENCIES
`GFX-01`, `DATA-03`. All mandatory predecessor WOs must be APPROVED/MERGED with evidence before activation.

## SCOPE
Sprites, atlases, layers, câmera, pixel snapping, lights, shadows e batching. Contract, smaller necessary increment, APIs, files and acceptance benchmarks: **TO BE SPECIFIED BY PLANNER AND AUDITED**, not guessed by Zcode.

## OUT OF SCOPE
No unapproved features, premature third-party dependency, broad cleanup, extra modules, paid infrastructure, outside human reviewer, CodeRabbit, bypass, force-push, public release or third-party proprietary assets.

## FILES / SOURCES TO READ
`docs/11-checkpoint.md` > `docs/10-decisions-ledger.md` / approved ADR > `docs/03-scope.md` > `docs/09-definition-of-done.md` > `docs/04-architecture.md` > `docs/02-requirements.md`; then `AGENTS.md`, this WO, [catalog](../../product/module-catalog.md), approved module spec (TBD), exact code paths (TBD).

## REQUIREMENTS
Global GOV-001..005, CAP-009/010 and domain-specific CAP IDs (TBD), NFR-001..005, owner directions NLE-D013..018. Map each to objective evidence before activation.

## ARCHITECTURE RULES
Typed contracts and errors, explicit ownership/security, decoupled editor/runtime/headless server, native desktop and web target feature tiers, Editor/CLI/MCP parity for public authoring actions, performance and accessibility as relevant. No third-party internal types leaking into public SDK.

## CONSTRAINTS
R$0 mandatory CI, solo owner approval, no paid code review, no destructive change, no silent ADR promotion. Zcode codes **only** after planner supplies actual API, concrete files, approved tech, test commands and BASE SHA.

## ACCEPTANCE CRITERIA
- [ ] **PRECONDITION:** approved technology ADR/versions/licenses, 1.0 release class, module Scope/Requirements/DoD and interface contract
- [ ] **PRECONDITION:** predecessors complete, module risk assigned and fresh source fingerprints/context lock captured
- [ ] Candidate functional verification: Cena 2D 60 FPS sob cenário/hardware definidos; texto e sprites sem artifacts.
- [ ] Relevant cross-OS build, unit, integration, failure and security/regression tests pass with logs
- [ ] Representative CPU/GPU/memory/VRAM/latency benchmarks and fallback tiers verified where applicable
- [ ] Editor/CLI/MCP operation matrix implemented and tested for public authoring functions where applicable
- [ ] Evidence Bundle, documentation, PR and audit APPROVED, no HIGH/CRITICAL defect, squash merge and checkpoint

## TESTS
Detailed executable commands/hardware/fixtures **TBD BY PLANNER**. Do not replace unrun tests with claims. Candidate proof: Cena 2D 60 FPS sob cenário/hardware definidos; texto e sprites sem artifacts.

## DELIVERABLES
Only approved code/files, contract, tests and docs, PR, CI results, pt-BR audit, rollback and proposed checkpoint delta.

## REVIEW FORMAT
Português brasileiro; APPROVED/CORRECTION REQUIRED/BLOCKED, severity, base/head, commands/results, diff, license/security, risk and recovery evidence.

## STOP CONDITION
BLOCKED while any unresolved TBD, unsupported architecture, missing dependency or permissions, stale SHA, failed CI, unapproved cost or HIGH/CRITICAL defect exists. No code branch from this draft.

## CONTEXT LOCK
BASE/HEAD and SHA-256 critical source fingerprints: TBD at activation and revalidate on change.

## EVIDENCE BUNDLE
Actual base/head SHA, files/diffs, tests/lint/build/benchmarks, errors and corrections, security/architecture/ABI, rollback, risks and proposed checkpoint delta.

*Future packet only; it must not be treated as a completed executable Work Order.*
