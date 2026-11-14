# Work Order — NLE-P00-WO-002-CORE-02

**Parent:** NLE-P00-WO-002 | **Module:** CORE-02 Memory & Allocators | **Issue:** #10  
**Risk:** LOW (docs), future implementation STANDARD/ELEVATED.  
**Context Lock base SHA:** 98738969c970c2f04cfaa35c84da86ab41688744

## OBJECTIVE
Research and specify a measurable cross-platform memory management strategy and candidate unique technology for Stormline's C++ engine, without programming or selecting a production allocator prematurely.

## CONTEXT
The 80-module candidate catalog is approved as planning. CORE-01 technology study PR #8 and checkpoint PR #9 were audited and merged, with issue #6 closed as research-only. Windows/Linux/macOS and no-MVP product contract remain binding.

## SCOPE
Memory domain classification; C++20 PMR and lifetime contracts; system baseline; mimalloc/rpmalloc alternatives; arenas and budget graphs; AI-readable diagnostics, OOM and security plan; ADR-0004; research matrix; issue #10; linkage to backlog and architecture.

## OUT OF SCOPE
No C++ code, no library install/override, no API implementation, no build/CI expansion beyond docs, no final allocator/SDK policy, no GFX VRAM allocator, no paid monitoring, no external reviewers.

## FILES / SOURCES TO READ
Checkpoint > Ledger/ADRs > Scope > DoD > Architecture > Requirements > CORE-01 and 80-module catalog > docs/engineering/agent-execution.md > official allocator docs and licenses.

## REQUIREMENTS
GOV-001..005, NLE-D002/017/018, NFR-001/002/003/005, CAP-009 performance in lower-end hardware, CAP-016 Windows/Linux/macOS.

## ARCHITECTURE RULES
Explicit memory ownership, headless support, no OS-type leakage in game/agent SDK, no allocator ABI mismatch across plugins, no realtime audio allocation, frame reset fences and no unproven innovation claim.

## CONSTRAINTS
Zero mandatory paid service, no CodeRabbit/external reviewer, no bypass or irreversible writes, no pressure to launch MVP, exact Git base SHA verification.

## ACCEPTANCE CRITERIA
- [ ] Candidate matrix includes system baseline, std::pmr, mimalloc and rpmalloc with license and maintenance considerations.
- [ ] Lifecycle, ownership and memory budget contracts identified for editor/server/client/game.
- [ ] Stutter/RSS/fragmentation benchmark plan with low-end tiers; no fabricated numbers or win claims.
- [ ] SMF research hypothesis with stop rule and comparison baseline.
- [ ] OOM and realtime safety, plugin ABI, cross-thread and platform-specific risks.
- [ ] ADR-0004 PROPOSED, no code implementation.
- [ ] GitHub Actions docs-validation green on HEAD, diff limited to documentation, Evidence Bundle, pt-BR audit.
- [ ] No advance to CORE-03 until this WO approved and checkpoint reconciled.

## TESTS
Existing docs-validation (Source Pack + 80 module DAG) in CI; inspect links, source status, licenses, issue, diff. Future allocator benchmark/sanitizer tests are only planned, not executed.

## DELIVERABLES
CORE-02 architecture, research matrix, ADR-0004, Work Order, issue #10, evidence bundle and post-merge checkpoint delta.

## REVIEW FORMAT
Português brasileiro: APPROVED/CORRECTION REQUIRED/BLOCKED. Cite SHA, CI, requirements, risks and unsupported assumptions.

## STOP CONDITION
STALE source, undocumented license conflict, accidental C++, high/critical defect, paid tool, unauthorized release or global allocator replacement. Correct within same WO/PR before advancing.

## CONTEXT LOCK
Only main SHA 98738969c970c2f04cfaa35c84da86ab41688744 is baseline for this draft. Any approved ADR/Scope/Checkpoint changes require recompilation of source context.
