#!/usr/bin/env python3
"""Deterministic validation of the proposed Stormline module catalog (stdlib only)."""
from __future__ import annotations
from collections import Counter
from pathlib import Path
import re
import sys

ROOT = Path(__file__).resolve().parents[1]
catalog = ROOT / "docs/product/module-catalog.md"
mcp = ROOT / "docs/product/ai-mcp-contract.md"
release = ROOT / "docs/product/full-release-readiness.md"
template = ROOT / "docs/product/module-spec-template.md"
errors: list[str] = []

for path in (catalog, mcp, release, template):
    if not path.is_file():
        errors.append(f"missing required planning file: {path.relative_to(ROOT)}")
if errors:
    print("\n".join(errors))
    raise SystemExit(1)

content = catalog.read_text(encoding="utf-8")
row_re = re.compile(
    r"^\| \`([A-Z]+-\d{2})\` \| \*\*(.+?)\*\* \| (.+?) \| (.+?) \| (.+?) \|$",
    re.MULTILINE,
)
rows = row_re.findall(content)
ids = [row[0] for row in rows]
dep_map: dict[str, list[str]] = {}
if len(ids) != 79:
    errors.append(f"expected 79 catalog modules; got {len(ids)}")
if len(set(ids)) != len(ids):
    errors.append("duplicate module IDs")
if "| **TOTAL** | **79** |" not in content:
    errors.append("catalog summary does not claim 79 modules")
group_counts = Counter(identifier.split("-", 1)[0] for identifier in ids)
if len(group_counts) != 14:
    errors.append(f"expected 14 functional areas; got {len(group_counts)}")
if group_counts.get("SIM") != 7:
    errors.append("vehicles/flight dynamics module missing from SIM family")
for item_id, title, scope, dependencies, acceptance in rows:
    if not title.strip() or not scope.strip() or not acceptance.strip():
        errors.append(f"incomplete title/scope/acceptance: {item_id}")
    dep_ids = re.findall(r"\b[A-Z]+-\d{2}\b", dependencies)
    dep_map[item_id] = dep_ids
    for dep in dep_ids:
        if dep not in ids:
            errors.append(f"missing dependency {item_id} -> {dep}")

states: dict[str, int] = {}
def walk(node: str, stack: list[str]) -> None:
    if states.get(node) == 1:
        errors.append("dependency cycle: " + " -> ".join(stack + [node]))
        return
    if states.get(node) == 2:
        return
    states[node] = 1
    for dep in dep_map.get(node, []):
        if dep in dep_map:
            walk(dep, stack + [node])
    states[node] = 2

for identifier in ids:
    walk(identifier, [])

for phrase in ("NO MVP", "2D", "2.5D", "3D", "Web", "MCP"):
    text = content + mcp.read_text(encoding="utf-8") + release.read_text(encoding="utf-8")
    if phrase not in text:
        errors.append(f"missing declared scope: {phrase}")
if "2026-07-28" not in mcp.read_text(encoding="utf-8"):
    errors.append("MCP protocol compatibility strategy is undocumented")
if errors:
    print("MODULE CATALOG VALIDATION FAILED")
    for entry in errors:
        print(" - " + entry)
    sys.exit(1)
print(f"PASS: {len(ids)} unique modules in {len(group_counts)} areas; no missing deps or cycles; release & MCP planning briefs present.")
