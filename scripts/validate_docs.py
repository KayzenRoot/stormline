#!/usr/bin/env python3
"""Validate Stormline's initial Source Pack with Python stdlib only."""
from pathlib import Path
from urllib.parse import unquote
import re
import sys

ROOT = Path(__file__).resolve().parents[1]
REQUIRED = [
    "README.md", "AGENTS.md",
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
    "docs/adr/0001-original-engine.md", "docs/adr/0002-solo-free-governance.md",
]
# Simple inline Markdown references; deliberately not a full CommonMark parser.
LINK = re.compile(r'\[[^\]]+\]\(([^)]+)\)')
errors = []
for rel in REQUIRED:
    file = ROOT / rel
    if not file.is_file():
        errors.append(f"missing: {rel}")
        continue
    value = file.read_text(encoding="utf-8")
    if not value.strip():
        errors.append(f"empty: {rel}")
    for raw in LINK.findall(value):
        target = raw.strip().split()[0].strip("<>")
        if target.startswith(("http://", "https://", "mailto:", "#", "data:")):
            continue
        target = unquote(target.split("#", 1)[0].split("?", 1)[0])
        if not target:
            continue
        resolved = (file.parent / target).resolve()
        if not resolved.is_relative_to(ROOT.resolve()) or not resolved.exists():
            errors.append(f"broken local link: {rel} -> {target}")
if errors:
    print("FAILED:")
    print("\n".join(" - " + x for x in errors))
    sys.exit(1)
print(f"PASS: {len(REQUIRED)} required documents, all checked local links.")
