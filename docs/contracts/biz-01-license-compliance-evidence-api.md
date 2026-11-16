# BIZ-01 — Proposed Versioned License, Rights and Compliance Evidence Contracts

**Conceptual API v0.1 / NOT IMPLEMENTED / NO PUBLIC SDK.** NLE-P00-WO-002-BIZ-01, issue #362, base 81aded1f42dffd9a7f36f0c3fd30a3168db15344; formal dependency QA-05 only. No license, ToS, royalty plan or legally binding permission published. Integrate existing [QA-05 qualification API](qa-05-qualification-evidence-api.md) through evidence references, not ownership migration.

## Typing and records
Every record must have schema_version, record_id, revision, timestamp_utc, actor role, content_digest, immutable provenance URL/reference, adjudicator, effective scope, evidence URIs and explicit status. Owner-generated authenticated approval is future, not satisfied by ChatGPT writing an ADR.

| Record | Minimum immutable and validated fields | Failure behavior |
|---|---|---|
| LicensingDecision | decision_id; engine_source=OPEN or OWNER_APPROVED; license_id/text_digest; runtime grant id; personal/commercial mode; royalty rule; effective_on; territory; owner signature | no approved license => NO_LICENSE_RELEASE |
| CreatorRightsManifest | project_id; author rightsholder; ownership representation; embedded redistribution exception IDs; asset hashes; export target; consent scopes | no implied NexLabs ownership or rights assignment |
| ComponentRights | purl/name/tag/commit; provenance; SPDX expression; source license digest; copyright/NOTICE; package file list; include linkage kind | UNKNOWN/NOASSERTION => BLOCKED pending legal proof |
| LicenseObligation | component_id; distribution action; obligation type; exact target; source offer/relink/reproduce notice conditions; legal reviewer | missing required obligations => BLOCKED |
| PlatformDistribution | PLAT-05 immutable export digest; QA-05 qualification evidence ID; packaged files; vendor SDK redistribution receipts; license notices digest | unqualified/unlicensed platform => BLOCKED |
| PrivacyProcessing | controller/processor; data category; purpose; jurisdiction; lawful basis; retention; recipient/transfer mechanism; minors category; opt-in evidence if basis requires | no legal basis/required transfer guard => BLOCKED |
| ConsentReceipt | person-specific opaque id; notice text/version; optional feature; presented purpose; grant or withdraw; timestamp; retention reference; no secret in evidence | withdrawn/absent where required => opt-out, never forced |
| ProductRightsGate | gate_id, source commit, artifact hash, rights matrix, outstanding exceptions, owner/counsel approvals, status | unknown/error/STALE => FAIL_CLOSED |

## Enumerations and semantics
- Rights states: NOT_AUDITED, NEEDS_REVIEW, VERIFIED_FOR_SCOPED_USE, BLOCKED, EXPIRED.
- Decision states: OPEN, PROPOSED, OWNER_APPROVED, REVOKED; **current engine_source=OPEN**. Proposals cannot generate live license files.
- Artifact states: DRAFT, NOT_RELEASEABLE, RELEASE_READY_PROPOSED, OWNER_APPROVED_RELEASE; P00 always NOT_RELEASEABLE.
- License graph edges: SOURCE, RUNTIME_STATIC, RUNTIME_DYNAMIC, HEADER_ONLY, TOOL_ONLY, SOURCE_GENERATED, ASSET_EMBEDDED, FONT_EMBEDDED, SHADER_BINARY, SDK_REDISTRIBUTABLE, NETWORK_SERVICE. These are factual packaging classifications, not legal outcomes.
- Error taxonomy: LICENSE_UNDECIDED, OWNER_SIGNATURE_REQUIRED, UNKNOWN_UPSTREAM_LICENSE, TRANSITIVE_NOTICES_MISSING, RIGHTS_CHAIN_CONFLICT, CREATOR_RIGHTS_VIOLATION, PATENT_OR_TRADEMARK_REVIEW, SDK_RESTRICTION, PRIVACY_BASIS_MISSING, INVALID_CONSENT, INTERNATIONAL_TRANSFER_UNCLEARED, A11Y_EVIDENCE_MISSING, SCOPE_STALE, RELEASE_NOT_QUALIFIED.
- Each approval must be scoped by target/channel/locale/legal jurisdiction/commit/term effective date. Version upgrade, new OS/export or changed vendor SDK **invalidates** prior evidence unless reverified. No global wildcard waiver.

## Draft operations for Editor/CLI/MCP
| Name | Authority | Result contract |
|---|---|---|
| rights.inspectProject | owner-authorized read | provenance summary with redactions; no secret or full proprietary asset uploads |
| rights.inspectExport | read only | list packaged licensed components and missing notices |
| rights.proposeLicense | draft only | alternate OSI/source-available/proprietary options; engine license remains OPEN |
| rights.validateSPDX | read only | normalized expression and upstream exceptions to manually verify |
| privacy.previewProcessing | read only | data flow/minimization/legal basis/transfer gap report |
| rights.requestApproval | protected, future owner authorization | human review record, NOT self approval by executor |
| rights.publishGrant | privileged legal action, disabled in P00 | denied until owner/counsel and full v1.0 release gates |
| compliance.exportEvidence | authorized read and redacted | signed/hashed evidence manifest with contents not user data |

Use deterministic schemas and explicit timeouts/size caps, path allowlist and non-mutating reads. Unknown fields: optional preservation where compatible, unknown mandatory legal flags fail closed. Use optimistic revision/ETag on approval; stale snapshot cannot publish. No private project contents in public CI artifacts.

## Example future logical gate
Input: engine_source OPEN, creator manifest valid, dependency MIT notice missing, optional crash upload consent absent, QA-05 NOT_QUALIFIED. Output: NOT_RELEASEABLE; violations LICENSE_UNDECIDED, TRANSITIVE_NOTICES_MISSING, RELEASE_NOT_QUALIFIED; crash-upload disabled; creator ownership preserved. This is a **hypothetical example**, not a test run.

## Acceptance and revocation
Changing a license for future versions must preserve legal rights of already-distributed covered copies where irreversible, and require counsel. Withdrawn consent stops future optional processing when consent is basis, and retention/deletion follows lawful obligations. Audit trail distinguishes permissions to use project as authored from opt-in telemetry, marketing, AI training and sublicensing. No automatic relicensing from file extension/asset import.

See [ADR-0080](../adr/0080-biz-01-rights-compliance-policy.md), [research matrix](../research/biz-01-licensing-rights-regulatory-matrix.md), [future cases](../testing/biz-01-acceptance-matrix.md).
