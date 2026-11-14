# Work Order — NLE-P00-WO-002-CORE-03

**Risk:** LOW (planning); future implementation ELEVATED if threading/runtime safety.  
**State:** APPROVED / MERGED (docs only, PR #14); ADR-0005 remains PROPOSED | **Issue:** #13 | **Base SHA:** `b76e7fd9992dcc012c212e8afe3d2836d9776c63`.

## OBJECTIVE
Specify a precise cross-platform job/task scheduling technology decision and future acceptance plan for 2D/3D/VFX workloads, keeping long-tail frame latency low and preventing concurrency bugs.

## CONTEXT
80-module catalog APPROVED AS INDEX. CORE-01 and CORE-02 research/checkpoints integrated. No native engine implementation. NLE-D017 Windows/Linux/macOS, NLE-D018 solo delegated planning apply.

## SCOPE
Research candidate C++20 std::jthread, Taskflow, enkiTS, oneTBB and Tracy; architectural boundary/typed API, main thread/audio GPU ownership, proprietary SFAS hypothesis; benchmark, safety and license matrix; ADR PROPOSED; issue #13 and backlog references; CI docs.

## OUT OF SCOPE
No C++/native scheduler implementation, library installation, build change, hardware benchmark claim, engine release, unrelated modules or paid services.

## FILES / SOURCES TO READ
Checkpoint > Ledger/ADRs > Scope > DoD > Architecture > Requirements > module catalog > CORE-01/02 specs > AGENTS > official candidate docs.

## REQUIREMENTS
GOV-001..005, CAP-004/009/010/016, NFR-001..005, NLE-D017/018. Preserve standalone headless server and future AI authorization.

## ARCHITECTURE RULES
No library types leaking into public engine APIs; deterministic gameplay commits despite work stealing; protected audio RT and GPU boundaries; bounded queues; cancellation with safe ownership; CORE-04 supplies time.

## CONSTRAINTS
No MVP, CI R$0, no CodeRabbit or required human reviewer, no bypass or destructive Git, no claims of native build or perf success without evidence.

## ACCEPTANCE CRITERIA
- [ ] Candidates, licenses, compiler/OS support, alternatives and selection criteria documented.
- [ ] Typed job graph, cancellation, result/errors and task lifetime contract documented.
- [ ] Low-core hardware, background resource quotas, frame-critical jobs and deterministic simulation covered.
- [ ] Stress, sanitizers, p50/p95/p99, memory/CPU, benchmarks and reference conditions defined.
- [ ] ADR-0005 stays PROPOSED for final implementation and no unapproved dependency is introduced.
- [ ] GitHub Actions docs-validation PASS on exact PR HEAD; scoped diff, no secrets.
- [ ] Evidence Bundle, review in pt-BR, squash merge and checkpoint delta after approval.

## TESTS
Real docs and dependency-DAG validation now. Future native compiler, TSAN/ASAN, low-core tests are specified but NOT RUN.

## DELIVERABLES
Architecture spec, technology matrix, ADR-0005, Work Order, Evidence Bundle, issue #13 linkage, updated backlog/checkpoint after audit.

## REVIEW FORMAT
pt-BR: APPROVED/CORRECTION REQUIRED/BLOCKED, severity and exact SHA/CI evidence.

## STOP CONDITION
Stale checkpoint, scope creep, implementation attempt, invalid license, CI red, HIGH/CRITICAL defect, unauthorized cost, incomplete evidence. No subsequent module until reconciled.

