#!/usr/bin/env python3
"""Validate repository-local Stormline Agent Skills without external dependencies."""
from __future__ import annotations

import json
from pathlib import Path
import re
import sys

ROOT = Path(__file__).resolve().parents[1]
SLUG = re.compile(r"^[a-z0-9]+(?:-[a-z0-9]+)*$")
FRONT = re.compile(r"\A---\n(.*?)\n---\n(.*)\Z", re.DOTALL)
LINK = re.compile(r"\]\(([^)\s]+)\)")


def validate_skill_document(path: Path, root: Path) -> list[str]:
    """Return specific errors; never modify files or execute skills."""
    errors: list[str] = []
    try:
        value = path.read_text(encoding="utf-8")
    except (OSError, UnicodeError) as exc:
        return [f"{path}: cannot read UTF-8: {exc}"]
    if "\r" in value or not value.endswith("\n"):
        errors.append(f"{path}: use LF and final newline")
    match = FRONT.fullmatch(value)
    if not match:
        return errors + [f"{path}: missing YAML frontmatter delimited by ---"]
    headers: dict[str, str] = {}
    for line in match.group(1).split("\n"):
        if ":" not in line:
            errors.append(f"{path}: invalid frontmatter line {line!r}")
            continue
        key, data = line.split(":", 1)
        key = key.strip()
        if key in headers:
            errors.append(f"{path}: duplicate field {key}")
        headers[key] = data.strip()
    if set(headers) != {"name", "description"}:
        errors.append(f"{path}: exactly name and description required, got {sorted(headers)}")
    name = headers.get("name", "")
    if not SLUG.fullmatch(name) or len(name) > 64 or name != path.parent.name:
        errors.append(f"{path}: name must match folder and be lowercase kebab-case <=64")
    try:
        description = json.loads(headers.get("description", ""))
        if not isinstance(description, str) or not description.strip() or len(description) > 1024:
            raise ValueError("description must be 1..1024 characters")
        if not description.startswith(("Use when ", "Use for ", "Use to ")):
            errors.append(f"{path}: description must declare a clear use-when trigger")
    except (ValueError, json.JSONDecodeError):
        errors.append(f"{path}: description must be a valid quoted YAML/JSON string")
    body = match.group(2)
    for section in ("## Source and authority", "## Workflow", "## Acceptance and evidence", "## Stop condition"):
        if section not in body:
            errors.append(f"{path}: missing {section}")
    if "[AGENTS.md]" not in body:
        errors.append(f"{path}: must link canonical AGENTS.md")
    if not re.search(r"\bblock(?:ed)?\b", body, re.IGNORECASE) or not re.search(r"\bwork order\b", body, re.IGNORECASE):
        errors.append(f"{path}: missing work-order and fail-closed safeguards")
    root_abs = root.resolve()
    for reference in LINK.findall(body):
        if reference.startswith(("https://", "http://", "mailto:", "#")):
            continue
        target = reference.split("#", 1)[0]
        resolved = (path.parent / target).resolve()
        if not resolved.is_relative_to(root_abs):
            errors.append(f"{path}: link escapes repository: {reference}")
        elif not resolved.is_file():
            errors.append(f"{path}: nonexistent linked file: {reference}")
    return errors


def validate_repository(root: Path = ROOT) -> list[str]:
    root = root.resolve()
    skills_dir = root / ".agents" / "skills"
    manifest_path = root / "docs" / "engineering" / "stormline-skills-manifest.json"
    registry_path = root / "docs" / "queue" / "implementation-registry.json"
    if not manifest_path.is_file() or not registry_path.is_file() or not skills_dir.is_dir():
        return ["Missing skill directory, manifest or implementation registry"]
    try:
        manifest = json.loads(manifest_path.read_text(encoding="utf-8"))
        registry = json.loads(registry_path.read_text(encoding="utf-8"))
    except (ValueError, OSError, UnicodeError) as exc:
        return [f"Cannot read skill manifest/registry: {exc}"]
    errors: list[str] = []
    if manifest.get("schema_version") != 1 or manifest.get("expected_count") != 36:
        errors.append("Manifest must declare schema_version=1 and expected_count=36")
    entries = manifest.get("skills", [])
    skill_names = [x.get("name") for x in entries if isinstance(x, dict)]
    if len(entries) != 36 or len(skill_names) != 36 or len(set(skill_names)) != 36:
        errors.append("Exactly 36 unique manifest skill names required")
    category_counts: dict[str, int] = {}
    for entry in entries:
        if not isinstance(entry, dict):
            errors.append("Manifest skill entry must be object")
            continue
        name, category = entry.get("name"), entry.get("category")
        if not isinstance(name, str) or not SLUG.fullmatch(name) or not isinstance(category, str):
            errors.append("Invalid name/category in skill manifest")
            continue
        category_counts[category] = category_counts.get(category, 0) + 1
    if category_counts != {"governance": 5, "design": 8, "engine": 15, "qa": 8}:
        errors.append(f"Skill category counts unexpected: {category_counts}")
    paths = sorted(skills_dir.glob("*/SKILL.md"))
    actual_names = [path.parent.name for path in paths]
    if sorted(actual_names) != sorted(skill_names):
        errors.append(f"Skill directory/manifest drift: missing={set(skill_names)-set(actual_names)}, extra={set(actual_names)-set(skill_names)}")
    for path in paths:
        errors.extend(validate_skill_document(path, root))
    folders = sorted(p.name for p in skills_dir.iterdir() if p.is_dir())
    if folders != sorted(actual_names):
        errors.append(f"Skill folders without SKILL.md: {set(folders)-set(actual_names)}")
    actual_modules = {x.get("module_id") for x in registry.get("modules", [])}
    mapping = manifest.get("modules", {})
    if len(actual_modules) != 80 or set(mapping) != actual_modules:
        errors.append(f"Expected exactly the 80 real registry IDs; missing={actual_modules-set(mapping)}, extra={set(mapping)-actual_modules}")
    for module_id, assigned in mapping.items():
        if not isinstance(assigned, list) or not assigned or len(assigned) != len(set(assigned)):
            errors.append(f"{module_id}: mapping must list unique skills")
        elif any(name not in skill_names for name in assigned):
            errors.append(f"{module_id}: references unknown skill")
    return errors


def main() -> int:
    errors = validate_repository()
    if errors:
        for item in errors:
            print(f"SKILL CHECK FAILED: {item}", file=sys.stderr)
        return 1
    print("Skill Pack PASS: 36 valid SKILL.md files; 80 registry modules mapped; canonical links and stop gates valid.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
