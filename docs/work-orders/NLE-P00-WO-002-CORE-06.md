# Work Order — NLE-P00-WO-002-CORE-06

**Stable ID:** NLE-P00-WO-002-CORE-06 | **Issue:** #105 | **Risk:** LOW documentation, future ELEVATED native/crash/privacy implementation  
**State:** PROPOSED RESEARCH / AUDIT PENDING  
**Context Lock baseline SHA:** `cc18ce33a05cbadac330effcc7ad6ddf29380721`

## OBJECTIVE
Produce a detailed and verifiable technology research specification for Stormline's diagnostics, logs, performance traces, memory/cpu/gpu counters, local crash envelopes and secure offline evidence export, minimizing future Zcode architecture work.

## CONTEXT
CORE-01..05 documentation and checkpoints are APPROVED/MERGED; 80 implementation WOs remain BLOCKED. No C++ engine, build, telemetry backend or profiler has been installed or verified. Owner requires high-performance 2D/2.5D/3D/Web and native Windows/Linux/macOS, AI/MCP, no public MVP and zero mandatory paid tooling.

## SCOPE
- Architecture of typed/versioned diagnostic events, spans, counters, crash envelopes and build-id/tick/job correlation.
- Candidate comparison: stdlib reference, spdlog, Tracy, Perfetto, Crashpad, native crash tools, optional OpenTelemetry and security/license considerations.
- Offline-first privacy, no hidden listeners or upload, bounded backpressure, redaction and failure handling.
- Original SDF R&D hypothesis with measurable evaluation/kill criteria.
- ADR-0008 PROPOSED, tests/benchmarks/OS matrix, issue mapping and Source Pack links, docs-only CI and Evidence Bundle.

## OUT OF SCOPE
No native engine code, profiler install, third-party vendoring, remote crash/analytics service, actual GPU benchmark, dashboard product, MCP server, release, subscription, external required reviewer, CodeRabbit or bypass.

## FILES / SOURCES TO READ
Checkpoint > Ledger and approved ADRs > Scope > DoD > Architecture > Requirements > CORE-01/02/03/04/05 research and docs/product/module-catalog.md > AGENTS.md > docs/queue/work-orders/CORE-06.md > official technology docs.

## REQUIREMENTS
GOV-001..005, CAP-001/002/003/007/008/009/010/013/016, NFR-001..005 and NLE-D013..020. Maintain public-authoring operation parity via safe diagnostics, headless server and privacy.

## ARCHITECTURE RULES
- No logging vendor types in SDK/API/AI. CORE-01 supplies clock/process signals; CORE-04 TickId; CORE-03 job metadata; CORE-02 memory domain.
- No allocation or blocking in real-time audio callbacks; no unsafe code in signal/crash handler.
- No raw dumps or privileged trace operations exposed to MCP. Bounded, authorized redacted resources only.
- UI and GPU diagnostics modules consume CORE-06 contracts, do not create circular dependencies.
- Security/privacy, versioning, consent/retention and deterministic evidence by build SHA are mandatory.

## CONSTRAINTS
P00 docs only; no money or subscription; zero-cost GitHub CI on public repo; no external human reviewer, CodeRabbit, force-push or bypass. No claims about completed native tests, runtime performance or profiling data.

## ACCEPTANCE CRITERIA
- [ ] Versioned event/span/metric/crash contract and typed failure modes, severity, correlation and clock semantics documented.
- [ ] Comparison with license/maintenance/platform risks for spdlog, Tracy, Perfetto, Crashpad and baseline.
- [ ] Local-first privacy, opt-in consent, retention/redaction, no cloud/listeners by default, safe crash handling documented.
- [ ] Future benchmark/OS matrix includes time overhead, p95/p99, disk/RAM, symbolication and overload/crash fault injection.
- [ ] SDF hypothesis has A/B and prove-or-drop, no invention claim.
- [ ] ADR-0008 PROPOSED, code issue #23 BLOCKED and future 80-WO registry unchanged/blocked.
- [ ] GitHub Actions docs-validation passes on exact PR HEAD; scoped diff, Evidence Bundle, review pt-BR.
- [ ] Following audited merge, checkpoint delta in same WO, no new research increment until reconciled.

## TESTS
Now only `python3 scripts/validate_docs.py`, `validate_module_catalog.py`, `validate_wo_registry.py`, `select_wo.py CORE-06` (expected BLOCKED). Real GitHub CI. Future native Windows/Linux/macOS crash/profiler/benchmark tests are NOT RUN.

## DELIVERABLES
CORE-06 architecture, technology matrix, ADR-0008, this Work Order, update Source Pack architecture/backlog, link blocked packet, Evidence Bundle, PR, pt-BR objective audit and post-merge checkpoint reconciliation.

## REVIEW FORMAT
Portuguese (Brazil): APPROVED / CORRECTION REQUIRED / BLOCKED with base/head SHA, exact GitHub CI job and diff, severity, tests run/unrun, privacy/license concerns and proposed Checkpoint Delta.

## STOP CONDITION
STALE source, hidden/automatic telemetry, invented test result or software performance, HIGH/CRITICAL privacy defect, optional dependency presented as installed, paid service, code added, failed CI or unapproved source scope. Correction stays in same WO/PR.

## CONTEXT LOCK
BASE `cc18ce33a05cbadac330effcc7ad6ddf29380721`. Use Git blob SHAs for document fingerprints and label them correctly; future code executor must generate true SHA-256 hashes. Recompile if checkpoint/Scope/DoD/Architecture/approved ADR changes.
