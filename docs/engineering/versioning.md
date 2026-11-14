# Stormline Versioning & Release Policy
**Status:** PROPOSED editorial standard for the program, pending owner approval for software-release semantics.

## Separate streams
1. **Planning documents:** revisions live in Git and ADRs. Documents may carry editorial labels (e.g. Brand Foundation v0.1), which are NOT engine version numbers.
2. **Engine software:** version numbers are not assigned until a runtime exists and a verified release is authorized.
3. **Assets and formats:** future independent schema versions and migrations must be specified before serialization or external SDK use.

## Proposed release scheme
- Semantic Versioning 2.0.0 is a candidate for distributable engine builds: `MAJOR.MINOR.PATCH`, with pre-release tags where needed.
- During early development, `0.x.y` would denote unstable public API, **only after the owner approves a real build and release process**.
- Version labels do not demonstrate stability or performance; a release requires artifacts, tests, compatibility data, security/license review and an approved DoD.
- Tags should point to approved immutable commits with provenance and documentation; do not retag or rewrite published history.

## Branches and PRs
- Default integration branch: `main`.
- One work-order branch per increment: `docs/NLE-P00-WO-...-description` or `work/NLE-...-description`.
- Stable WO ID included in issues, PRs, commits, evidence and checkpoint.
- Prefer normal **squash merge**, provided the branch is current, the diff/audit passes, and rulesets are satisfied. No force push or bypass.
- Externally staffed reviews are not required; objective CI and owner authorization remain obligatory.

## Changelog rules
- [CHANGELOG.md](../../CHANGELOG.md) records **verified** milestones and explicitly distinguishes P00 documentation from executable software.
- Only label a build `Released` after publishing approved artifacts and verifying actual distribution.
- Keep plans as planned, proposals as proposed, and experiments as experiments.

## Open decisions
Licensing, API stability policy, binary ABI, platform support, artifact hosting, release signing, support window and patch policy remain open. They require ADRs and evidence, not extrapolation from the README.
