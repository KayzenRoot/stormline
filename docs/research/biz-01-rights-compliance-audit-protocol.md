# BIZ-01 — Future Legal Rights, License and Privacy Audit Protocol

**FUTURE PROTOCOL ONLY · 2026-11-16 · NO EXECUTABLE ENGINE, PRODUCT RIGHTS CERTIFICATION, LEGAL ADVICE OR ACTUAL BENCHMARK.** Planning issue #362, code #95 OPEN/BLOCKED; base 81aded1f42dffd9a7f36f0c3fd30a3168db15344. Formal dependency QA-05 only. 128 B01-T001..B01-T128 all FUTURE/NOT EXECUTED. Product/license NLE-D009 OPEN.

## Future audit stages, owner-approved inputs needed
| Stage | Inputs expected once implementation exists | Output evidence and failure mode |
|---|---|---|
| A1 source copyright | contributor register, original engine code, rights assignments/CLA, approved license | provenance gaps BLOCKED; counsel attribution/ownership report |
| A2 packaged dependency closure | versioned PLAT-05 output, linker flags, optional plugins, transitive SBOM, OS SDK runtime | exact file manifest and SPDX graph; UNKNOWN BLOCKED |
| A3 obligations | legal source file & license hash, exception/grant, notice, source offer, relinking | obligations per shipped file/artifact/platform; incomplete => BLOCKED |
| A4 creator project isolation | synthetic rights-cleared project, game exports, original independent art/music/logic | assert no blanket relicense/asset ownership; embedded runtime distinguished |
| A5 AI and content origin | provider terms, prompt/source provenance, human copyright review, model retention | similarity/unlicensed assets/unknown contractual rights => BLOCKED |
| A6 privacy and consent | purpose/legal-basis mapping, local-only baseline, opt-in/crash dump test, delete/DSAR | negative consent/withdrawal/retention/transfer tests must be verified |
| A7 accessibility and geography | WCAG 2.2 web matrix, WCAG2ICT and native OS assistive tech evidence, consumer/export counsel map | unsupported jurisdiction/target marked NOT_QUALIFIED |
| A8 final rights release gate | actual license/ToS, third-party notices, QA-05 release evidence, approvals and rollback | owner-counsel signoff or NOT_RELEASEABLE; no silent override |

## Hypotheses, not measured benchmarks
- Coverage: each actually shipped dependency and asset needs exact provenance; target 100% for release **as proposed acceptance threshold**, not measured today.
- No automatic tool audit is conclusive. Compare ORT/REUSE with manual legal sampling, false positives/negatives, license-text drift and file-level mixed licensing. Record scanner version, package manager, cache, pinned dependency hashes.
- Simulate 4 negative policy classes: no source license, missing font notice, source-available misrepresented as OSI, unconsented crash upload. Every class should fail closed with stable error/reason and not corrupt creator data.
- Software privacy test fixtures only, generated identities and synthetic projects; NEVER copy real personal/game content to public CI. Compliance and rights tests may require isolated confidential evidence vault and access-controlled review.
- Validate change impact: dependency upgrade, SDK binary update, source change, new export target, privacy policy change, opt-out, revoked permission, incomplete patent search. Recompute applicable legal obligations, not global waiver.
- Treat legal review as professional judgment, not deterministic unit-test substitute. Publication requires real lawyer/owner clearance as applicable, payments/marketing/export jurisdiction and release decision.

## R$0 and CI design
Initial free public GitHub Actions: stdlib docs checks only; future ORT/REUSE/SPDX scanners considered after version/license and resource profiling, source-only synthetic inventories in CI. No purchase of legal counsel, signing, paid hardware, vendor API, new runner tier or royalty billing authorized by these docs. License scanner build output belongs future execution after approval; hosted public runners may have artifact/storage limits even if compute free.

## Independent exit/rollback
Any HIGH/CRITICAL right infringement, unlicensed dependency, exposed personal data, noncompliant transfer, unapproved terms, missing consent, failed a11y gate required by owner, missing QA-05 proof or unverified trademark means BLOCKED. Correct in the same Work Order/PR if safe; if future release published, counsel-approved notice/takedown/revocation and roll-forward plan, preserving vested licensed copies and user creations. A future legal notice cannot retroactively assign creator IP.

## P00 audit limitations
Today there is no binary, bundled asset, SDK, model-generated engine code, uploaded crash log, customer dataset, commercial license, CI license scanner, benchmark, signature, third-party notices for released engine, or revenue model to audit. Only proposed architecture and primary-source research are reviewable. Run [128 future cases](../testing/biz-01-acceptance-matrix.md) after implementation authorization and genuine artifacts.
