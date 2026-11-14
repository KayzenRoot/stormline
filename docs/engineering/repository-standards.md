# Repository Presentation & Administration Standards
Work Order: NLE-P00-WO-001-EXT-001 | Status: PROPOSED until audited/merged.

## Presentation
- Main README in English, pt-BR companion, direct navigation to Source Pack and current checkpoint.
- Use existing typography and restrained symbols; don't present a provisional graphic as an approved Stormline logo.
- Only show **real** workflow badges pointing to this repository; a passing documentation workflow is not a C++ build, graphics, security, or release certification.
- Prefer source-controlled onboarding, versioning, security, support and templates over decorative badge clutter.
- Public-facing material distinguishes *vision*, *planned capability*, *proposal*, and *verified implementation*.

## Suggested GitHub About metadata (NOT APPLIED)
**Description:** \`Stormline is NexLabs Technology's original high-performance 3D engine initiative, focused on real-time graphics, VFX, spatial audio and efficient worlds. Planning phase.\`

**Topics (candidates):** \`game-engine\`, \`3d-graphics\`, \`rendering\`, \`engine-development\`, \`nexlabs\`, \`research\`.

**Website:** leave unset until official destination is owner-approved and verified. Do not advertise a download or public product site.

## Recommended settings (NOT VERIFIED OR APPLIED)
- Default branch main; allow pull requests and squash merge, disallow force-push/deletions.
- Require PR and the existing \`docs-validation\` check **after** verifying exact check context on main.
- Required human approvals: **0**; no mandatory outside reviewer or CodeRabbit.
- Prefer linear history if compatible with chosen merge strategy; no bypass of existing rules.
- Allow free security scanning and dependency monitoring for public repositories where eligible.
- Configure private vulnerability reporting if supported; until then do not advertise private reporting as active.
- Public repository is not necessarily open source: no LICENSE file until owner chooses legal terms.
- Repository description/topics and settings require a supported admin tool or owner action; changes to files do not modify GitHub About or protection rules.

## Local formatting
- UTF-8 and LF for text; final newline; no trailing spaces in Markdown outside intentionally formatted blocks.
- Use Python stdlib for P00 documentation validation to avoid subscriptions and network dependencies.
- Never add CI minutes/credentials/third-party action solely for visual polish.
- Source Pack before implementation, one WO per PR, Evidence Bundle and post-merge checkpoint reconciliation.

## Validation
Verify links, file presence, README claims, issue templates, PR template, GitHub CI run and exact SHAs. If a setting is inaccessible, report \`NOT VERIFIED\` rather than claiming \`CONFIGURED\`.
