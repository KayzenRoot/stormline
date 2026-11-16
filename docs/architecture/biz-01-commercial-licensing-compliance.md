# BIZ-01 — Commercial Licensing & Compliance: Proposed Architecture

**2026-11-16 · P00 RESEARCH ONLY · NLE-P00-WO-002-BIZ-01 · issue #362 · ordinal 77/80 · base 81aded1f42dffd9a7f36f0c3fd30a3168db15344.** Formal prerequisite **QA-05 ONLY** (ADR-0079 PROPOSED). Source license NLE-D009 **OPEN**, no issued LICENSE, royalties/fees/terms approved or public game engine. All 80 implementation packets blocked.

## System and legal boundaries
The first-class objects are **engine/editor source**, **redistributable engine runtime and generated binaries**, **creator-authored projects/assets/source/game data**, **third-party components and imported content**, **optional hosted services**. Each has an independent rights and privacy policy. Public repository visibility is NOT an open-source grant. Game users keep their independently authored IP; publishing a game does not automatically grant Stormline rights to its music, art, fonts, scripts or proprietary business data. Do not promise an absolute exception when generated game packages copy engine runtime code, sample assets or licensed third-party files: each copied component carries its own obligations.

| Boundary | Owner of decisions | Allowed design proposal, NOT live permission |
|---|---|---|
| NexLabs engine source/editor | NexLabs owner/legal clearance | compare permissive open-source, copyleft, source-available and proprietary/dual license |
| Engine runtime included in game export | BIZ-01 rights gate + PLAT-05 artifact inventory | explicit royalty-free redistribution grant may be offered after approval, subject to exceptions and notices |
| User project, user-provided assets and resulting game | respective rightsholder | no forced relicensing of creator content, no automated claim over game revenue or game IP |
| Template/sample content | source owner + explicit grant | ship only original/cleared content with separate sample license |
| Third-party library/source/font/shader/SDK | upstream rightsholder | per exact release/tag/file, license/exceptions/patent/attribution obligations preserved |
| Hosted account, optional AI/telemetry/payment | controller/processor and contract owner | additional privacy, DPA and lawful purpose gates before integration |

## Research decision model
Maintain separate decision fields: engineSourceLicense=OPEN, runtimeRedistribution=UNAPPROVED, royaltyModel=UNDECIDED, personalUseTerms=UNAPPROVED, commercialUseTerms=UNAPPROVED, thirdPartyClearance=NOT_AUDITED, trademarkClearance=OPEN, privacyPolicy=NOT_PUBLISHED. No selected model may be called OSI-open-source unless it complies with the [Open Source Definition](https://opensource.org/osd), including permitted commercial uses, modifications and redistribution. Source-available restrictions, field-of-use bans, revenue caps and royalty charges for redistribution should **not** be mislabeled OSI open-source. Ownership, confidentiality, patents, indemnification and warranties require legal specialist review.

## Ownership and distribution pipeline (conceptual; no implementation)
1. Ingest candidate package and original creator rights declaration with provenance and license scope; preserve the original signed terms, immutable digest and corresponding source.
2. Build exact **component inventory** per release target: source dependency DAG, static/dynamic linkage, generated code, assets/fonts/shaders, toolchain/runtime code included, SDK runtime clauses and transitive closure. Identify shipped vs build-only vs user-authored components; **never treat development-only dependencies as shipped without evidence**.
3. Parse declared SPDX expressions (including AND, OR, WITH and LicenseRef), reconcile against upstream legal files **and** file-level exceptions, choose OR branches explicitly with evidence; license detector is not final legal adjudication.
4. Resolve each shipment edge: permission scope, commercial use, derivative or linking trigger, distribution of source/object, patent clauses, reserved trademark, NOTICE/source offers/relinking obligations and attribution; generate third-party notices only from verified evidence.
5. Link game export package to PLAT-05 manifest, QA-05 supported platform/recovery outcome and QA-04 supply chain provenance as **transitive integrations only**; they are not new formal DAG dependencies.
6. Produce versioned rights decision, waiver with approver/expiry or explicit BLOCKED; unknown/conflicting provenance => fail closed. UI/CLI/MCP may read summary; only owner-gated actions can approve/publish a license.
7. When services are introduced, create data-flow map and record purposes, legal basis, controller/processor, telemetry opt-in, retention, deletion, international transfer mechanism, minors/age and DPIA/LIA where applicable. Local-first no-data default and exportable/deletable records are proposed privacy-minimizing defaults, NOT proof of GDPR/LGPD compliance.
8. Release gate enforces license text chosen by owner, creator-content boundaries, cleared third-party notices and obligations, privacy documents, accessibility evidence, legal review and rollback before a future public v1.0. Until then: BLOCKED/NOT_RELEASEABLE.

## Critical failure modes and handling
- **Copyleft/linking:** GPL/AGPL/LGPL nuances depend on actual distribution, combination, network service and specific license text. Never mark all GPL or all LGPL incompatible by name alone; require a counsel-reviewed linking/runtime topology, source-offer and replacement/relinkability plan. Build tools do not normally force a game output license merely by processing user content; an output embedding substantial licensed content may change the result ([FSF GPL FAQ](https://www.gnu.org/licenses/gpl-faq.html)).
- **Fonts:** OFL-1.1 embedding/modified font/reserved-font-name and redistribution depend on exact font files and package; images made using fonts are not automatically font distributions ([SIL FAQ](https://openfontlicense.org/ofl-faq/)).
- **Shader/material/sample:** track actual included source/binary and source licensing. Avoid copying proprietary shader techniques or competitor engine content; a high-level technical idea is not a license.
- **AI-generated code/art:** preserve model/provider terms, input rights, human review, provenance and potentially similar third-party output; do not assume every AI output is copyrightable or entirely free of third-party claims. No secrets/project data uploaded without authorization.
- **Patents and trademarks:** permissive copyright permission is not necessarily patent immunity. Patent license/termination and trademark name use are distinct; NLE-D010 remains OPEN pending brand clearance.
- **SDK/store restrictions:** Apple/Windows/Android/browser/driver SDK redistribution, telemetry and store clauses are audited per actual version/channel before shipping; downloadable SDK != automatic sublicensing.
- **Unknown evidence:** legal obligations cannot be proven by green docs workflow or by generated SPDX string. Package blocked until actual inventory and full counsel/owner approval.

## Interfaces and governance
Canonical [semantic rights evidence contract](../contracts/biz-01-license-compliance-evidence-api.md) defines versioned entities, status and fail-closed behavior. Contract integrates future DATA-02 asset provenance, DATA-05/PLAT-05 distribution manifests, AI-06 authorization, QA-05 qualification, QA-04 SBOM and CORE-06 optional diagnostic classification, **without adding dependencies**. UI, CLI and MCP can propose/view findings; publication, pricing, rights waivers and third-party relicensing are privileged human approval actions. Future runtime risk ELEVATED; handling private data/payment/irreversible license grants HIGH_ASSURANCE.

## Roadmap and acceptance
The **P00 DoD** is eight docs, credible primary sources, 128 distinctive FUTURE cases, exact-head Docs Validation, audit in pt-BR, separate checkpoint and history, no license selection. The **future production DoD** requires real artifact audit across Windows/Linux/macOS/Web where approved, counsel-reviewed owner-approved license & contracts, complete notices and consent evidence, data-subject handling, creator-project non-relicensing, support/rollback, real tests and owner release authorization. No released 1.0, license grant or legal certification exists.

See [ADR-0080](../adr/0080-biz-01-rights-compliance-policy.md), [matrix](../research/biz-01-licensing-rights-regulatory-matrix.md), [future protocol](../research/biz-01-rights-compliance-audit-protocol.md), [128 tests](../testing/biz-01-acceptance-matrix.md).