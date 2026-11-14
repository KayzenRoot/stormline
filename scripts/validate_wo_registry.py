#!/usr/bin/env python3
"""Validate every draft Stormline Work Order against the versioned 80-module catalog."""
from __future__ import annotations
from pathlib import Path
import json
import re
import sys

ROOT = Path(__file__).resolve().parents[1]
registry_path = ROOT / "docs/queue/implementation-registry.json"
catalog_path = ROOT / "docs/product/module-catalog.md"
errors: list[str] = []
try:
    reg = json.loads(registry_path.read_text(encoding="utf-8"))
    modules = reg["modules"]
except (FileNotFoundError, KeyError, ValueError, TypeError) as exc:
    raise SystemExit(f"invalid registry: {exc}")

catalog = catalog_path.read_text(encoding="utf-8")
row_pattern = re.compile(
    r"^\| `([A-Z]+-\d{2})` \| \*\*(.+?)\*\* \| (.+?) \| (.+?) \| (.+?) \|$", re.MULTILINE
)
rows = row_pattern.findall(catalog)
source: dict[str, dict[str, object]] = {}
for module_id, name, scope, dependencies, acceptance in rows:
    source[module_id] = {
        "name": name, "scope": scope,
        "dependencies": re.findall(r"\b[A-Z]+-\d{2}\b", dependencies),
        "catalog_acceptance": acceptance,
    }

if len(rows) != 80 or len(source) != 80:
    errors.append(f"catalog needs 80 unique modules, got {len(rows)}")
if reg.get("schema_version") != 1 or reg.get("engine_implemented") is not False:
    errors.append("invalid registry schema or false engine status")
if len(modules) != 80:
    errors.append(f"expected 80 WOs, got {len(modules)}")

issue_numbers: set[int] = set()
ids: set[str] = set()
wo_ids: set[str] = set()
seen: set[str] = set()
mandatory = [
    "OBJECTIVE", "CONTEXT", "SCOPE", "OUT OF SCOPE",
    "FILES / SOURCES TO READ", "REQUIREMENTS", "ARCHITECTURE RULES",
    "CONSTRAINTS", "ACCEPTANCE CRITERIA", "TESTS", "DELIVERABLES",
    "REVIEW FORMAT", "STOP CONDITION", "CONTEXT LOCK", "EVIDENCE BUNDLE",
]
for m in modules:
    module_id = m.get("module_id", "")
    work_id = m.get("id", "")
    if module_id in ids or work_id in wo_ids:
        errors.append(f"duplicate module or WO: {module_id}")
    ids.add(module_id)
    wo_ids.add(work_id)
    if work_id != f"NLE-EXEC-WO-{module_id}-001":
        errors.append(f"invalid WO ID: {work_id}")
    meta = source.get(module_id)
    if not meta:
        errors.append(f"unknown module: {module_id}")
        continue
    for key, value in meta.items():
        if m.get(key) != value:
            errors.append(f"catalog mismatch {module_id}.{key}")
    deps = m.get("dependencies", [])
    for dep in deps:
        if dep not in seen:
            errors.append(f"out-of-order dependency {module_id} <- {dep}")
    seen.add(module_id)
    if m.get("work_order_status") != "BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS":
        errors.append(f"WO incorrectly unblocked: {module_id}")
    if m.get("executor_ready") is not False or m.get("release_class") != "UNDECIDED":
        errors.append(f"WO falsely executor-ready/released: {module_id}")
    issue_number = m.get("github_issue")
    if not isinstance(issue_number, int) or issue_number <= 0:
        errors.append(f"missing/non-integer issue for {module_id}")
    elif issue_number in issue_numbers:
        errors.append(f"duplicate GitHub issue number: {issue_number}")
    else:
        issue_numbers.add(issue_number)
    if m.get("issue_url") != f"https://github.com/KayzenRoot/stormline/issues/{issue_number}":
        errors.append(f"incorrect issue URL for {module_id}")
    if m.get("approved_adr") is not None or m.get("context_lock_sha") is not None:
        errors.append(f"WO claims approved architecture/lock: {module_id}")
    path = ROOT / m.get("file", "")
    if not path.is_file():
        errors.append(f"missing WO packet: {path}")
        continue
    source_md = path.read_text(encoding="utf-8")
    if work_id not in source_md or module_id not in source_md:
        errors.append(f"packet ID mismatch: {module_id}")
    if "BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS" not in source_md:
        errors.append(f"packet does not declare blocked: {module_id}")
    for title in mandatory:
        if f"## {title}" not in source_md:
            errors.append(f"missing WO section: {module_id} {title}")
    if not source_md.endswith("\n"):
        errors.append(f"missing final newline: {module_id}")

doc_wo_count = len(list((ROOT / "docs/queue/work-orders").glob("*.md")))
if doc_wo_count != 80:
    errors.append(f"expected 80 individual WO files, got {doc_wo_count}")
if len(issue_numbers) != 80:
    errors.append(f"expected 80 mapped GitHub issues, got {len(issue_numbers)}")
if len({m.get("module_id") for m in modules}) != 80:
    errors.append("registry module IDs not unique")
if errors:
    print("FAIL: Work Order registry")
    for error in errors:
        print(" -", error)
    sys.exit(1)
print("PASS: 80 unique blocked Work Order packets and GitHub issue mappings; catalog, dependency order, required sections and no-premature-execution gate verified.")
