#!/usr/bin/env python3
"""Validate proposed Stormline PR packet plans against the canonical blocked queue."""
from __future__ import annotations

import json
from pathlib import Path
import re
import sys

ROOT = Path(__file__).resolve().parents[1]
REGISTRY = ROOT / "docs/queue/implementation-registry.json"
MANIFEST = ROOT / "docs/pr-plans/manifest.json"
PACKET = re.compile(r"^NLE-PRPLAN-([A-Z]+-[0-9]{2})-([0-9]{2})$")


def validate_manifest(manifest: dict, registry: dict) -> list[str]:
    issues: list[str] = []
    source = registry.get("modules", [])
    plans = manifest.get("modules", [])
    if manifest.get("schema_version") != 1 or manifest.get("module_count") != 80:
        issues.append("schema_version=1 and module_count=80 required")
    if manifest.get("status") != "ALL_PROPOSED_BLOCKED_NOT_ACTUAL_CODE_PRS":
        issues.append("manifest must remain documentary and blocked")
    by_id = {x.get("module_id"): x for x in source}
    all_ids: set[str] = set()
    module_ids: list[str] = []
    if len(source) != 80 or len(plans) != 80:
        issues.append(f"exactly 80 source modules and 80 plans required; got {len(source)}/{len(plans)}")
    for entry in plans:
        mid = entry.get("module_id")
        module_ids.append(mid)
        original = by_id.get(mid)
        if original is None:
            issues.append(f"{mid}: not present in canonical registry")
            continue
        for name, value in (
            ("catalog_order", original["catalog_order"]),
            ("name", original["name"]),
            ("existing_code_issue", original["github_issue"]),
            ("formal_dependencies", original["dependencies"]),
            ("catalog_acceptance", original["catalog_acceptance"]),
            ("scope", original["scope"]),
        ):
            if entry.get(name) != value:
                issues.append(f"{mid}: {name} differs from registry")
        if original.get("work_order_status") != "BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS":
            issues.append(f"{mid}: source coding WO no longer blocked")
        if original.get("executor_ready") or original.get("approved_adr") is not None:
            issues.append(f"{mid}: unexpected approved executable source")
        if entry.get("plan_file") != f"docs/pr-plans/{mid}.md":
            issues.append(f"{mid}: plan_file invalid")
        packets = entry.get("packets", [])
        if not isinstance(packets, list) or len(packets) < 8:
            issues.append(f"{mid}: >=8 packets required")
            continue
        kinds = [p.get("kind") for p in packets]
        if (kinds[:2] != ["GOVERNANCE", "CONTRACT"]
                or kinds[-2:] != ["QUALIFICATION", "CLOSEOUT"]
                or any(k != "IMPLEMENTATION" for k in kinds[2:-2])):
            issues.append(f"{mid}: invalid gate/implementation/qualification order")
        if mid == "CORE-01" and len(kinds[2:-2]) != 12:
            issues.append("CORE-01 must have twelve individually planned implementation slices")
        if len(kinds[2:-2]) < 4:
            issues.append(f"{mid}: fewer than four functional code slices")
        for idx, packet in enumerate(packets, start=1):
            ident = packet.get("packet_id")
            expected = f"NLE-PRPLAN-{mid}-{idx:02}"
            if ident != expected or not PACKET.fullmatch(ident or ""):
                issues.append(f"{mid}: nonstable or unordered PR packet ID {ident}")
            if ident in all_ids:
                issues.append(f"{mid}: duplicate packet ID {ident}")
            all_ids.add(ident)
            if packet.get("status") != "PLANNED_BLOCKED" or packet.get("github_pr") is not None:
                issues.append(f"{mid}: code PR must not be opened/authorized by documentary map")
            if packet.get("depends_on") != ([] if idx == 1 else [f"NLE-PRPLAN-{mid}-{idx-1:02}"]):
                issues.append(f"{mid}: broken PR packet dependency at {idx}")
            if packet.get("kind") in ("IMPLEMENTATION", "QUALIFICATION"):
                if packet.get("requires_modules_merged") != original["dependencies"]:
                    issues.append(f"{mid}: formal predecessor gate drift in {ident}")
            if not all(isinstance(packet.get(key), str) and packet[key].strip()
                       for key in ("packet_id", "kind", "title", "acceptance")):
                issues.append(f"{mid}: incomplete objective/acceptance on packet {idx}")
    if set(module_ids) != set(by_id) or len(set(module_ids)) != len(module_ids):
        issues.append("module IDs missing/duplicated vs canonical registry")
    if manifest.get("planned_packet_count") != len(all_ids):
        issues.append("manifest packet count differs from actual unique IDs")
    if len(all_ids) < 600:
        issues.append("unexpectedly low candidate PR breakdown")
    return issues


def validate_repository(root: Path = ROOT) -> list[str]:
    root = root.resolve()
    try:
        reg = json.loads((root / "docs/queue/implementation-registry.json").read_text(encoding="utf-8"))
        manifest = json.loads((root / "docs/pr-plans/manifest.json").read_text(encoding="utf-8"))
    except (OSError, UnicodeError, ValueError) as err:
        return [f"Cannot read JSON: {err}"]
    issues = validate_manifest(manifest, reg)
    for required in (
        "docs/pr-plans/index.md",
        "docs/engineering/pr-decomposition-policy.md",
        "docs/work-orders/NLE-P00-GOV-003-PRMAP.md",
        "docs/evidence/NLE-P00-GOV-003-PRMAP.md",
    ):
        if not (root / required).is_file():
            issues.append(f"Missing critical PR map file: {required}")
    for entry in manifest.get("modules", []):
        mid = entry.get("module_id", "")
        path = root / "docs/pr-plans" / f"{mid}.md"
        if not path.is_file():
            issues.append(f"{mid}: missing module PR plan file")
            continue
        content = path.read_text(encoding="utf-8")
        if "\r" in content or not content.endswith("\n"):
            issues.append(f"{mid}: invalid line endings")
        if f"# {mid} " not in content or "PLANNED_BLOCKED" not in content:
            issues.append(f"{mid}: missing header/blocked declaration")
        for packet in entry.get("packets", []):
            if packet.get("packet_id", "") not in content:
                issues.append(f"{mid}: packet absent from prose {packet.get('packet_id')}")
    actual = sorted(p.name for p in (root / "docs/pr-plans").glob("*.md") if p.name != "index.md")
    expected = sorted(f"{m['module_id']}.md" for m in manifest.get("modules", []))
    if actual != expected:
        issues.append("PR plan Markdown file set does not equal 80 module plans")
    return issues


def main() -> int:
    errors = validate_repository()
    if errors:
        for e in errors:
            print("PR PLAN FAILED:", e, file=sys.stderr)
        return 1
    data = json.loads(MANIFEST.read_text(encoding="utf-8"))
    print(f"PR plan PASS: {data['module_count']} modules, "
          f"{data['planned_packet_count']} candidate packets, all BLOCKED, 0 live code PRs.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
