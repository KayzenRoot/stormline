# Security Policy

## Supported versions

| Component | Supported |
|---|---|
| Stormline Engine / Runtime / Editor / SDK | **Not released** |
| Planning documents and repository automation | Maintained as part of the P00 program |

No executable product or security-tested runtime is currently available. Do not mistake a passing documentation workflow for a security certification.

## Responsible disclosure

**Do not publish suspected vulnerabilities, credentials, tokens, or exploit details in GitHub issues, discussions, or pull requests.**

Use GitHub's **Private vulnerability reporting** feature **if it is enabled on this repository**. If it is unavailable, contact the repository owner through a separately established private channel and request a secure reporting path **without including exploit details in public**. A dedicated security mailbox has **not** been verified, so none is advertised.

The owner-operated team will assess impact and coordinate a fix when a valid private report reaches it. No guaranteed response SLA or bug bounty program is offered.

## CI and supply-chain position
- Read-only default permissions for GitHub Actions tokens and no secrets in PR runs.
- No CodeRabbit or required paid review tools.
- Dependency and asset licenses, vulnerability alerts, code scanning, reproducibility, and runtime fuzzing are planned as relevant code is introduced.
- Public-repository CI is cost-constrained to no mandatory paid services.
- [Threat-model plan](docs/05-security.md), [free CI policy](docs/engineering/free-ci.md), [checkpoint](docs/11-checkpoint.md).
