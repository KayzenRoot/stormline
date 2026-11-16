# BIZ-01 — 2026 Licensing, IP, SPDX, Privacy and Global Commercial Research Matrix

**Research only (2026-11-16), NLE-P00-WO-002-BIZ-01, issue #362, QA-05 sole formal prerequisite.** Do not mistake this research for professional legal advice or certified clearance. Product LICENSE and royalties remain OPEN/UNDECIDED. Specific law applicability, license versions and contractual rights must be checked on exact actual releases by counsel before distribution.

## Engine licensing models
| Model | Source/reuse | Commercial game outputs and embedded runtime | Constraints and unresolved decision |
|---|---|---|---|
| MIT | broad reuse, preserve copyright/license | generally games commercially distributed; runtime inclusion must carry applicable notice | no patent terms expressly comparable to Apache; cannot impose royalties over downstream MIT uses |
| BSD-2/BSD-3-Clause | broad reuse, notices; BSD-3 no endorsement | independent game IP not automatically BSD-licensed | preserve attribution, do not claim endorsement |
| Apache-2.0 | broad reuse with express patent terms, modifications/NOTICE as applicable | commercially distributable with compliance | patent termination, trademark excluded; notice/source scope audit |
| MPL-2.0 / LGPL | file or library copyleft depending on actual terms | may allow proprietary games with fulfilled library/file duties | source & relinking/modified library availability; dynamic vs static must be analyzed, not shortcut |
| GPL-3.0 / AGPL-3.0 | strong reciprocal conditions in covered combinations and sometimes network interaction | standalone authored game output not automatically GPL; bundled combined code may be covered | distribution/network boundary and embedded engine code require counsel |
| Source-available restricted | readable source under business license, NOT OSI if commercial use/field restrictions | per custom grant, possibly royalties | must label accurately; irrevocability and community expectations |
| Proprietary EULA | source withheld or rights contractually limited | grant game-export and engine-runtime rights expressly | author ownership, warranty, indemnity, consumer law, jurisdiction |
| Dual license | qualified owner offers different grants | per chosen path; commercially paid options possible | CLA/rightsholder authority and mixed contributions |

Official: [OSI OSD](https://opensource.org/osd), [SPDX expressions](https://spdx.github.io/spdx-spec/v3.0.1/annexes/spdx-license-expressions/), [FSF tool output](https://www.gnu.org/licenses/gpl-faq.html). No option is APPROVED by listing it.

## Distribution object rights matrix
| Object/route | Copyright/licensing question | Required evidence before future shipment |
|---|---|---|
| Engine source/editor | owner rights, contributor contracts and source license | owner approval, provenance, license texts, warranty limitations |
| Engine runtime linked/statically embedded/dynamically loaded | distribution grant, third-party libraries, patented functionality | packaged file-level BOM, linking map, notices, upstream obligations |
| Game code/project and own art/music/scripts | independent user ownership; no blanket transfer to NexLabs | contractual terms that respect user's copyright, explicit exceptional embedded components |
| Export templates/standard assets | authored or third-party sampled license | original creation evidence, sample pack license, redistribution permission |
| Third-party textures/fonts/audio/3D/models | commercial/resale, alteration, attribution, NoDerivatives/NonCommercial restrictions | license grant and proof for each file, CC-BY credit if applicable, unknown asset blocked |
| Font OFL-1.1 | embedding and font redistribution (not mere artwork output) | reserved font name, copyright, OFL copy and modified font review |
| Shader/source snippets, GPU SDK code | file-level license, vendor copyright, API implementation patent/SDK terms | exact upstream tag and file/binary shipped, permitted targets |
| Model-generated code, music, images, text | input rights, provider terms, machine-generated copyright uncertainty and infringement | prompt provenance without private contents, human review & legal clearance; no automatic exclusive IP |
| Cloud AI/crash/telemetry | personal/company data, vendor DPA and model data use | purpose, legal basis, minimization, account config, transfer, deletion, access logs |

## SPDX and third-party notices policy
1. Capture package URL/purl, source repository/commit, exact license texts and hashes, authors, version, source of evidence, platform target and actual distribution graph (build/dev/test/runtime/optional).
2. Use SPDX identifiers and **expressions**: OR means valid license choice by licensee, AND means both obligations, WITH means only an actual documented exception. LicenseRef for custom unlisted terms; NONE and NOASSERTION are not a blanket release permission. Verify using official [SPDX License List](https://spdx.org/licenses/) and [SPDX 3.0.1 expressions](https://spdx.github.io/spdx-spec/v3.0.1/annexes/spdx-license-expressions/).
3. Include submodules, vendored files, header-only libs, fonts, sample assets, generated code and platform-specific binaries in an accurate **transitive** manifest. Scan actual exported artifact and not merely lockfile. Preserve license text, attribution, NOTICE, source offer, relinking package and modifications when applicable. Classify unknown/contradictory as BLOCKED.
4. Optional candidates: [OSS Review Toolkit ORT](https://github.com/oss-review-toolkit/ort) Apache-2.0 package and policy automation, [REUSE](https://reuse.software/spec-3.3/) file annotations, SPDX and CycloneDX SBOM. Versions, environment and R$0 CI budgets must be checked at implementation; a scanner alone does not certify legality. Avoid assuming multi-vendor SDK/driver licenses from a general project license.
5. Future automated policy gate should provide summary to QA-04 supply chain and QA-05 qualification **without altering formal QA-05-only dependency**.

## Privacy and regulatory research
| Requirement source | Proposed policy, no certification | Evidence/owner gate |
|---|---|---|
| [LGPD ANPD legal bases](https://www.gov.br/anpd/pt-br/acesso-a-informacao/perguntas-frequentes) | map purpose to an applicable lawful basis, NOT consent for everything; sensitive data stricter | controller/processor, necessity, records, notice and rights response |
| [ANPD international transfers Resolution 19/2024](https://www.gov.br/anpd/pt-br/acesso-a-informacao/institucional/atos-normativos/regulamentacoes_anpd/resolucao-cd-anpd-no-19-de-23-de-agosto-de-2024) | transfer mechanism and proportionality, if export of personal data crosses borders | legal review of country, destination, instrument and contract |
| [GDPR 2016/679](https://eur-lex.europa.eu/eli/reg/2016/679/oj/eng/) | Articles 5,6,7,13,25,28,32,35,44+ as applicable; consent, DPA, retention/privacy by design | lawful basis, DPIA when needed, transfer instrument, rights SLA per law |
| Optional crash upload | explicit opt-in proposed, off by default, local redaction | no project secrets, path, user names or proprietary asset samples in crash blobs |
| AI model/agent content | separate authorization, DPA and no training on user data by default absent explicit approval | vendor version/terms, prompt audit, consent/provenance, revoke/delete flow |
| Payment/subscription/ads | no payment platform selected, no billing collection | taxes, chargeback, refunds, consumer contracts, fair notice and security |
| Child/minor-related game/telemetry | age-specific law and higher protection may apply | age gating, parental consent where legally required, avoid profiling minors |
| [WCAG 2.2](https://www.w3.org/TR/wcag/) + [WCAG2ICT](https://www.w3.org/WAI/standards-guidelines/wcag/non-web-ict/) | future accessibility testing web and native, OS screen reader/keyboard gamepad | real assistive tech and target platform verification; no certification assertion |

## Global distribution and IP hazards
- Trademark: brand name Stormline and logo availability not cleared (NLE-D010 OPEN). Domain/search visibility does not confer trademark exclusivity.
- Patents: evaluate express Apache patent grant/termination, patents in codec/graphics techniques; open-source code grant does not imply third-party patent freedom to operate.
- Third-party content: Creative Commons NC is incompatible with commercial use; ND may disallow transformative redistribution, BY attribution required, CC0 may help for known assets but rights other than copyright remain. [Creative Commons](https://creativecommons.org/share-your-work/cclicenses/).
- Region/market: contracts and VAT/GST/sales taxes, refunds, platform store terms, consumer law, sanctions/export control including encryption regulations and prohibited end uses require region-specific advice. No unsupported statement of worldwide permission.
- Games/distributions can require PEGI/ESRB/ratings and accessibility guidelines independent of engine source license. Do not pre-approve market claims.
- CI costs: standard hosted GitHub public compute may be free; ORT dependency/image data, large artifact storage, legal counsel, signing, notary and physical compliance audits are not automatically cost R$0.

## Severity and future recommendation
Recommend designing **separate author-owned game licensing and runtime redistribution grants** regardless of final source-license choice. This is a **nonbinding architectural recommendation**. Every unknown copyright chain, conflicting copyleft, missing vendor redistribution or unlawful personal-data transfer is BLOCKED rather than auto-waived. Actual selection requires owner/counsel decision.
