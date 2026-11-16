# ADR-0080 — Rights-Separated Licensing, Creator Ownership and Fail-Closed Compliance

**STATUS: PROPOSED / NOT RATIFIED. 2026-11-16.** NLE-P00-WO-002-BIZ-01, issue [#362](https://github.com/KayzenRoot/stormline/issues/362), formal dependency **QA-05 ONLY**, predecessor ADR-0079 PROPOSED. Module 77/80. Source base 81aded1f42dffd9a7f36f0c3fd30a3168db15344. No legal document, royalty model, engine LICENSE, third-party redistribution right or privacy policy has been owner-approved.

## Problem
A public engine repo with no license decision can encourage legally unsupported redistribution and confuse ownership of creator content, engine runtime, samples and transitive dependencies. A model that reserves royalties may prevent OSI-open-source classification; a permissive source license may not cover patents, embedded user assets, vendor SDKs or trademark. Optional online AI, crash and telemetry features create cross-border and data protection obligations. This ADR specifies a **review framework only**, not a license.

## Proposed design policy
1. **Keep owner decisions OPEN.** NLE-D009 license, royalty schedule, dual licensing, rights to source/binaries, sublicensing and enterprise terms are not assumed. Source available publicly without an explicit license is not automatically open source. No LICENSE file/ToS/royalty disclosure is issued in P00. Escalate legal judgment to owner and qualified counsel.
2. **Evaluate distinct models:** MIT/BSD-3-Clause/Apache-2.0 permissive; LGPL/GPL/AGPL copyleft and linking/network consequences; OSI licensing vs source-available business/source licenses with field-of-use or paid licenses vs closed proprietary and dual license; royalty-free flat-fee, per-seat, usage-based, revenue share/threshold models. Never call a non-OSI restriction open-source.
3. **Separate what authors own.** The user retains user-supplied game, art, music, scripts, data and independently generated output; no forced blanket relicense, revenue share or assignment. An exported game might include engine binary, tooling/runtime redistributables, samples or third-party IP that retain their own terms. Explicit future runtime redistribution grant is needed before release. Generative output's ownership may depend on law, input and license.
4. **Provenance-led release:** full SPDX license expression, exact upstream versions/commit hashes, license text and file-level notices, allowed uses/redistribution, static/dynamic/IPC linkage, modified source, source offer, patent/trademark grants, OFL font constraints, CC BY attribution/ND/NC incompatibility where relevant and vendor SDK terms. Software scanner warnings never substitute legal review; UNKNOWN => BLOCKED.
5. **No implicit sublicense:** engine may license its own IP only when entitled; third-party and creator content is not sublicensed by the engine without a matching grant. Do not import game assets into model training/marketing/telemetry; separate consent or lawful authorization and narrow use terms would be required.
6. **Privacy by design:** no telemetry/crash upload by default until lawfully justified, consent where required and auditable opt-in/opt-out; consent not a universal substitute for other legal bases. Inventory personal/sensitive data, purpose limitation, controller vs processor, minimization, retention, encryption and deletion. LGPD and GDPR applicability is jurisdiction/data-flow specific. International transfers need valid mechanisms, not just US hosting/notice ([ANPD](https://www.gov.br/anpd/pt-br/assuntos/assuntos-internacionais/transferencia-internacional-de-dados), [GDPR](https://eur-lex.europa.eu/eli/reg/2016/679/oj/eng/)).
7. **Accessible fair commercial product:** web WCAG 2.2 and native WCAG2ICT/OS assistive technologies as proposed test baselines; no certification claim. Taxes, invoicing, local consumer law, EU seller/platform and export/sanctions screening are specialist/market-specific owner gates, not automatic permissions.
8. **Formal dependency QA-05 only** verifies future release-qualification evidence; other systems supply necessary data through typed integrations but must not change catalog DAG. Legal gates and release classes remain independent from a green docs CI; only the owner can approve licensing/terms/revenue model at a future auditable increment.
9. **P00 boundaries:** exactly eight new Markdown and 128 future cases, no executable/licensing implementation, no scan or real legal audit of non-existent engine binaries, no data collection, no paid tools, all 80 code Work Orders blocked.

## Options analyzed (decision intentionally deferred)
| Candidate | Commercial use | Redistributions/royalties | Source modifications | Key gate |
|---|---|---|---|---|
| MIT/BSD-3-Clause | generally permitted | no license-imposed royalty | permissive | notices, warranty, third-party/patent review |
| Apache-2.0 | generally permitted | no license-imposed royalty | permissive, changes notices | express patent grant and termination, NOTICE and scope |
| LGPL | generally permitted | no blanket royalty assumption | copyleft scope around library | shipping/link/relink, modified library source obligations |
| GPL/AGPL | commercial use allowed | royalties/restrictions not presumed | stronger distribution/network copyleft | combined-work/network boundary, code/source obligations |
| Source-available customized | per contract | could charge or restrict | limited by contract | do NOT label OSI open-source |
| Proprietary | per EULA | flat-fee, per-seat, royalties possible | per contract | precise copyright, sublicense, runtime export & creator rights |
| Dual-license | per chosen grant | pricing by contract | contributor rights and compatibility crucial | CLA/rightsholder authority, alternatives consistent |

## Rejected shortcuts
- Selecting MIT automatically to make README appear open-source.
- Charging a mandatory fee for redistribution while claiming OSI-compliant open-source.
- Equating an engine binary embedded in an export with a creator-authored asset.
- Treating an SPDX ID or ORT scan as proof no patent/asset/SDK restrictions exist.
- Treating GPL/LGPL as universally forbidden, or asserting all generated output inherits tool license.
- Uploading private game projects/crash dumps to public CI/third-party AI.
- Calling cookie banners or mandatory telemetry sufficient LGPD/GDPR compliance.
- Calling WCAG checklist, physical accessibility certification or global export legally approved.
- Enabling publication, license changes, monetization or code issue #95 from a planning PR.

## Pending owner/legal decision gates
Choose copyright holder/contributor agreements, legal entity/jurisdiction, engine source license, public runtime EULA/redistribution clauses, commercial/personal rights, derivative/distributed binary obligations, fee/royalty model, source escrow/support/warranties/indemnity, patent/trademark clearance, third-party license/SBOM legal review, privacy/retention/DPA/transfer instruments, accessibility and consumer/export policy, tax/invoicing and actual global release geography. Requires counsel before release; ADR remains PROPOSED.

[Architecture](../architecture/biz-01-commercial-licensing-compliance.md) · [license/regulatory matrix](../research/biz-01-licensing-rights-regulatory-matrix.md) · [typed evidence](../contracts/biz-01-license-compliance-evidence-api.md).