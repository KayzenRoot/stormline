# AI-09 — Proposed Validation Session, Measured Evidence and Optimization Proposal Contracts v0.1

**2026-11-15 | P00 DOCUMENTARY RESEARCH ONLY / NOT IMPLEMENTED | research [#313](https://github.com/KayzenRoot/stormline/issues/313) | NLE-P00-WO-002-AI-09 | future code [#83](https://github.com/KayzenRoot/stormline/issues/83) OPEN/BLOCKED | BASE `84eb288251684ed68311887b1c7901d49c44a2c3`.** Catalog 65/80, formal deps **AI-07 + CORE-06 ONLY**, predecessors ADR-0066/0008 PROPOSED; 64/80 researched at baseline, 16 pending, 80/80 coding WOs BLOCKED. NLE-D009 engine license OPEN.

**LOGICAL CONTRACTS ONLY. No compiled API, test runner, benchmark, GPU capture, report implementation, issue automation, SDK, engine, profiler or optimization executor.**

## 1. Formal authority and compatibility ports
| Formal owner | Type/contract owned there | AI-09 consumption |
|---|---|---|
| **CORE-06** | `DiagnosticEventV1`, `TraceSpanV1`, `CounterSampleV1`, `CorrelationContextV1`, `DiagnosticExportV1`, local redaction policy and drop/availability counters | read bounded validated local diagnostic evidence only, no independent raw crash access/export |
| **AI-07** | `ChangeSetDraftV1`, `ChangePlanV1`, `SemanticDiffV1`, `ChangeApplyReceiptV1`, `ChangeRecoveryDecisionV1` | produce owner-scoped optimization **preview** and reference original source receipts; never direct commit, consent, undo or approval |

Transitive QA/CORE/GFX/AUDIO/GAME/DATA/EDIT/MCP owners supply runnable scenarios when implemented; not formal AI-09 DAG edges. AI-01 command kernel and AI-06 human consent remain transitive owner gates.

## 2. Proposed versioned types
| Type | Fields (candidate) | Invariant |
|---|---|---|
| `ValidationSessionV1` | SessionId, actor, ProjectId, test suite ID/schema/digest, source+candidate Git SHAs, target profile, requested metrics, privacy scope, budgets, created/expiry, owner state snapshot | explicit bounded run; no implicit project commit or external network |
| `ValidationFixtureV1` | fixtureId, scene/asset/package owner IDs/revisions/digests, rights/provenance, fixed seeds/ticks, target OS/arch/features, required owner validators and golden visual profile | synthetic or rights-cleared; no customer secrets and no unknown owner PASS |
| `ValidationCapabilityProfileV1` | owners actually available, GFX timestamp availability/time domain, CORE-06 trace support/clock type/drop counter, platform capture support, shader/audio/physics test capability | unsupported/partial measurement explicit; never substitute zero |
| `ValidationEnvironmentV1` | build SHA/config/compiler and flags, hardware CPU/GPU/driver/OS, battery/power/thermal, resolution/HDR/color/AA/VSync, renderer profile, sampling/profiler versions, installed tool SPDX digests | comparability frozen or qualified strata |
| `ValidationMetricSampleV1` | metricId/unit/clock domain, raw sample values and ordered timestamps, availability, dropped count, correlation, frame/tick/job/owner trace refs, redaction class | no NaN-as-zero, invalid frame sample or silent dropped result |
| `VisualReferenceProfileV1` | renderer/build/driver, scene+camera/light IDs, fixed exposure/color space/HDR/AA/TAA seeds/frames, golden image digests, masks/regions, allowed metrics, source provenance | per-profile, no global cross-GPU exact-pixel promise |
| `VisualDiffReceiptV1` | before/after capture hashes, alignment/transform profile, per-region threshold, SSIM/structural optional score, temporal series refs, semantic UI/lighting and accessibility validators, failures | similarity alone never overrides semantic failure |
| `FunctionalTestReceiptV1` | owner test ID/command, actual run status PASS/FAIL/FLAKY/INCONCLUSIVE/UNSUPPORTED/NOT_EXECUTED, fixture/build seed/digest, exit/issue evidence and redaction | a retry does not erase historical failure |
| `ValidationRunReceiptV1` | session+run id, owner test/diagnostic source IDs, environment, tool versions, diagnostics capture hash, sample count and drops, cold/warm, start/end monotonic spans, stdout/exit redaction, completeness | no self-attested data or cloud-only artifact |
| `ValidationPairV1` | exact baseline and candidate receipt references, matched metric/fixture/target profiles, randomized order/seed, comparability verdict, unmatched factors, statistical test config | comparisons require both independent runs and same frozen harness |
| `ValidationStatisticalSummaryV1` | primary declared endpoints, p50/p95/p99, variance/confidence/bootstrap/interval method, sample N, censored/dropped, correction for comparisons, practical threshold and availability | no invented precision/p99 from too-small samples |
| `ValidationReportV1` | baseline/candidate SHAs, before/after independent evidence hashes, all metrics, functional/visual/security regressions, confidence, environment comparability, unknowns, redaction/retention, recommendation, human approval state | report may say INCONCLUSIVE/NO_CHANGE; natural language not proof |
| `OptimizationHypothesisV1` | measured bottleneck, mechanism, affected owner components, supporting trace spans/metrics, expected effect range/uncertainty, risks, permission/scope, alternative hypotheses | proposed, not implemented/benchmarked |
| `OptimizationProposalV1` | owner ProjectId+revision, AI-07 ChangeSetDraft/Plan reference + semantic diff, hypothesis, regression gates, predicted/unmeasured impact, rollback class, approval required and status | AI-07 PREVIEW ONLY, human approves in separate trusted UI |
| `ValidationErrorV1` | ENV_NOT_COMPARABLE/METRIC_UNAVAILABLE/CLOCK_UNCALIBRATED/TRACE_INCOMPLETE/UNSUPPORTED_OWNER/FLAKY/REGRESSION/HUMAN_APPROVAL_REQUIRED/BUDGET_EXCEEDED/PRIVACY_DENIED, safe trace ID | no leaked secret/path or false pass |

## 3. Proposed logical API, NOT implementation
```text
list_validation_capabilities(VerifiedActorProjectScope, TargetProfile)
  -> ValidationCapabilityProfileV1 | UNSUPPORTED

create_validation_session(VerifiedActor, FixtureManifest, SourceBaselineAndCandidate, Budget)
  -> ValidationSessionV1 | DENY

run_validation_session(VerifiedActor, ValidationSession, IsolatedOwnerRunner)
  -> ValidationRunReceiptV1 | ValidationErrorV1

collect_redacted_diagnostics(VerifiedActor, CORE06DiagnosticExportRef, Bound)
  -> AuthorizedDiagnosticEvidenceV1 | PRIVACY_DENIED

compare_validation_runs(VerifiedActor, ValidationPairV1, FrozenOracleManifest)
  -> ValidationReportV1 | ENV_NOT_COMPARABLE | INSUFFICIENT_EVIDENCE

propose_optimization_preview(VerifiedActor, ValidationReportV1, OwnerRevisionAndConstraints)
  -> AI07ChangePlanV1 + OptimizationProposalV1 | BLOCKED

submit_for_human_review(VerifiedActor, ProposalId, ReviewUIProfile)
  -> PendingApprovalReferenceV1 | BLOCKED

get_validation_report(VerifiedActor, ReportId, RedactedViewProfile)
  -> ValidationReportV1 | DENY
```
No exposed function for `apply_optimization`, `approve_self`, `merge_pr`, `capture_raw_process_memory` or `upload_crash_dump`. If owner applies a separately authorized ChangePlan in future, AI-09 may compare afterwards but is not executor or trusted approver.

## 4. Validation status machine, separation of observations
```text
CREATED -> PREFLIGHT -> FIXTURE_PINNED -> BASELINE_RUNNING
    -> CANDIDATE_RUNNING -> EVIDENCE_COLLECTED
    -> COMPARABILITY_CHECKED -> ANALYZED -> REPORT_READY
    -> OPTIONAL_PROPOSAL_PREVIEW -> PENDING_HUMAN_APPROVAL
TERMINAL ALTERNATIVES:
  BLOCKED, UNSUPPORTED, NOT_EXECUTED, NOT_COMPARABLE,
  INCONCLUSIVE, VALIDATION_FAILED, REGRESSION_DETECTED,
  CANCELLED, RESOURCE_LIMIT, COMPLETE_REPORT_ONLY
```
A terminal `COMPLETE_REPORT_ONLY` proves a report was generated with verified data, not that optimization was applied/approved. Human approval must be a distinct authenticated event bound to actual AI-07 PlanId/source/args digest and policy, not natural language. Optional stage without a plan may be omitted only with visible NO_CHANGE or EVIDENCE_INSUFFICIENT recommendation.

## 5. Comparability and correctness gates
- Prevalidate that the pair uses same toolchain optimization mode, target hardware/driver, renderer/AA, resolution, scene/seed data and exact test harness/golden version. Unknown factors must be listed. A mismatch may be stratified with explicit design but cannot be silently treated comparable.
- Freeze correctness test suite independent of candidate branch. All required tests pass with actual owner receipts; if missing profile, `UNSUPPORTED` or `NOT_EXECUTED`.
- Preserve raw sample N and invalid/drop/censor count, time domains, scope/sequence and frame/tick correlation. Report p50/p95/p99 only where N adequate; otherwise uncertainty/inconclusive. GPU times converted by physical device period, never host CPU timer.
- An accurate image hash tests byte-level equality for pinned deterministic renderer; SSIM/perceptual optional diagnostics. Temporal VFX/TAA needs frame sequences and semantic region test; unknown golden ownership => UNSUPPORTED. No autonomous updating of goldens.
- If source AI-07 plan changes after approval request or actor grant revokes, owner JIT rechecks and denies; proposal cannot bypass policy.

## 6. Security and data governance
Diagnostic reports and generated visual captures may contain private source/game content. Export is local, redacted, bounded, rights-classified, opt-in and separately authorized. No profiler network listener default. No raw heap/VRAM/stack from untrusted actor. Golden/benchmark fixtures rights-cleared and immutable hashed, never copied from prohibited commercial IP. Each decision trace has audit status and actual CORE-06 dropped-event count. No known allowed screenshot/profiler tool source is assumed safe without artifact policy.

## 7. Future acceptance
Exactly 128 A09 FUTURE/NOT EXECUTED tests validate before/after real measurements and explicit human signoff, no runtime claims. Separate future HIGH_ASSURANCE code Work Order required before real test harness or model tool use.

[Architecture](../architecture/ai-09-validation-optimization.md) · [ADR-0068](../adr/0068-ai-09-evidence-first-human-gated-optimization.md) · [Tests](../testing/ai-09-acceptance-matrix.md).
