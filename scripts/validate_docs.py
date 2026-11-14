#!/usr/bin/env python3
"""Validate Stormline's planning Source Pack and repository presentation (stdlib only)."""
from __future__ import annotations

from pathlib import Path
from urllib.parse import unquote
import re
import sys

ROOT = Path(__file__).resolve().parents[1]
REQUIRED = [
    "README.md", "README.pt-BR.md", "AGENTS.md",
    "CHANGELOG.md", "CONTRIBUTING.md", "SECURITY.md",
    "SUPPORT.md", "CODE_OF_CONDUCT.md", ".editorconfig", ".gitattributes",
    ".gitignore", ".github/PULL_REQUEST_TEMPLATE.md", ".github/workflows/docs.yml",
    ".github/ISSUE_TEMPLATE/config.yml",
    ".github/ISSUE_TEMPLATE/01-work-order.md",
    ".github/ISSUE_TEMPLATE/02-bug-report.md",
    "docs/00-source-hierarchy.md", "docs/01-project-overview.md",
    "docs/02-requirements.md", "docs/03-scope.md", "docs/04-architecture.md",
    "docs/05-security.md", "docs/06-test-benchmark-plan.md",
    "docs/07-deployment.md", "docs/08-backlog.md",
    "docs/09-definition-of-done.md", "docs/10-decisions-ledger.md",
    "docs/11-checkpoint.md", "docs/brand/brand-foundation.md",
    "docs/brand/logo-system.md", "docs/brand/motion-sound.md",
    "docs/brand/asset-register.md",
    "docs/engineering/solo-governance.md", "docs/engineering/free-ci.md",
    "docs/engineering/agent-execution.md", "docs/engineering/wo-template.md",
    "docs/engineering/technology-radar.md",
    "docs/engineering/versioning.md",
    "docs/engineering/repository-standards.md",
    "docs/work-orders/NLE-P00-WO-001-EXT-001.md",
    "docs/adr/0001-original-engine.md", "docs/adr/0002-solo-free-governance.md",
]
# Deliberately limited to straightforward inline links. This is not a full CommonMark parser.
MD_LINK = re.compile(r'!?\[[^\]]*\]\(([^)]+)\)')
HTML_LINK = re.compile(r'\b(?:href|src)="([^"]+)"')
errors: list[str] = []

for rel in REQUIRED:
    path = ROOT / rel
    if not path.is_file():
        errors.append(f"missing: {rel}")
    elif not path.read_bytes().strip():
        errors.append(f"empty: {rel}")

markdown = sorted(ROOT.rglob("*.md"))
for file in markdown:
    if any(part in {".git", ".venv", "build", "dist", "out"} for part in file.relative_to(ROOT).parts):
        continue
    rel = file.relative_to(ROOT)
    content = file.read_text(encoding="utf-8")
    if "\r" in content or not content.endswith("\n"):
        errors.append(f"invalid LF/final newline: {rel}")
    if "\\`" in content:
        errors.append(f"escaped Markdown code-fence marker: {rel}")
    for raw in [*MD_LINK.findall(content), *HTML_LINK.findall(content)]:
        target = raw.strip().split()[0].strip("<>")
        if target.startswith(("http://", "https://", "mailto:", "data:", "#")):
            continue
        target = unquote(target.split("#", 1)[0].split("?", 1)[0])
        if not target:
            continue
        resolved = (file.parent / target).resolve()
        if not resolved.is_relative_to(ROOT.resolve()) or not resolved.exists():
            errors.append(f"broken local link: {rel} -> {target}")

for name in ("01-work-order.md", "02-bug-report.md"):
    issue_file = ROOT / ".github" / "ISSUE_TEMPLATE" / name
    if not issue_file.is_file():
        continue
    contents = issue_file.read_text(encoding="utf-8")
    if not contents.startswith("---\n") or "\n---\n" not in contents[4:]:
        errors.append(f"invalid issue-template frontmatter: {name}")
    else:
        meta = contents.split("\n---\n", 1)[0]
        for field in ("name:", "about:"):
            if not any(line.startswith(field) for line in meta.splitlines()):
                errors.append(f"missing issue-template {field} in {name}")

readme = ROOT / "README.md"
if readme.is_file():
    body = readme.read_text(encoding="utf-8")
    for truth in ("ENGINE: NOT IMPLEMENTED", "LICENSE: PENDING", "docs-validation", "README.pt-BR.md"):
        if truth not in body:
            errors.append(f"README missing current-state disclosure: {truth}")

if errors:
    print("FAILED:")
    for entry in errors:
        print(" -", entry)
    sys.exit(1)
print(f"PASS: {len(REQUIRED)} required files; {len(markdown)} Markdown files scanned; local links and issue templates validated.")
