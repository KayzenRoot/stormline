#!/usr/bin/env python3
"""Validate Stormline packet planning and at most one bounded owner-approved activation."""
from __future__ import annotations

import json
from pathlib import Path
import re
import sys

ROOT = Path(__file__).resolve().parents[1]
REGISTRY = ROOT / "docs/queue/implementation-registry.json"
MANIFEST = ROOT / "docs/pr-plans/manifest.json"
ACTIVATION_FILE = ROOT / "docs/queue/packet-activations.json"
ACTIVATED_STATUS = "ONE_BOUNDED_CORE01_INTERNAL_PACKET_READY"
COMPLETED_STATUS = "CORE01_03_COMPLETED_REST_BLOCKED"
PACKET = re.compile(r"^NLE-PRPLAN-([A-Z]+-[0-9]{2})-([0-9]{2})$")



def validate_activation(activation: dict) -> list[str]:
    """Hard-stop on a broad or forged G6 transition. This is only the first reviewed packet."""
    expected = {
        "schema_version": 1,
        "status": "OWNER_RATIFIED_BOUNDED_G6_ACTIVATION",
        "selected_packet_id": "NLE-PRPLAN-CORE-01-03",
        "module_id": "CORE-01",
        "risk": "STANDARD",
        "release_class": "INTERNAL_ONLY",
        "owner_ratification_pr": 422,
        "contract_pr": 424,
        "checkpoint_pr": 425,
        "approved_adr": "docs/adr/0083-core-01-internal-headless-slice.md",
        "approved_contract": "docs/contracts/core-01-internal-headless-v0.md",
        "work_order": "docs/work-orders/NLE-PRPLAN-CORE-01-03.md",
        "activation_evidence": "docs/evidence/NLE-PRPLAN-CORE-01-03-G6-ACTIVATION.md",
        "gate_base_sha": "c355de53bca5be1d64dedb4d7111bd40c8859e83",
        "requires_fresh_context_lock": True,
    }
    errors = []
    if set(activation) != set(expected) | {"source_blob_sha1"}:
        errors.append("activation keys must match exactly one audited G6 packet")
    for key, value in expected.items():
        if activation.get(key) != value:
            errors.append(f"activation {key} mismatch: no bulk owner authority")
    fingerprints = activation.get("source_blob_sha1")
    required = {
        "checkpoint": "5090dfa5fc39f3e26e5df038c6e23bce2ff1e26a",
        "decisions_ledger": "01aa967790dc1ea5e72c2ebebae7b832ec579981",
        "scope": "0b65820507d946d2b2b4ed3a2b869e60cafaaf22",
        "definition_of_done": "e0b7c2466ebec9790a715e47490c015cfb502db4",
        "adr_0083": "82d4968e37f0400f092e885d9fe201df772f4719",
        "contract_v0": "4ea41263bcfd412ca35df2abb32a158706b64e48",
    }
    if fingerprints != required:
        errors.append("activation source fingerprints do not match approved baseline")
    return errors


def expected_packet_state(
    module_id: str, idx: int, activation: dict | None, manifest_status: str | None
) -> tuple[str, int | None]:
    if activation is not None and module_id == "CORE-01":
        if idx == 1:
            return "APPROVED_GOVERNANCE", 422
        if idx == 2:
            return "APPROVED_CONTRACT", 424
        if idx == 3:
            if manifest_status == COMPLETED_STATUS:
                return "COMPLETED", 428
            return "EXECUTOR_READY", None
    return "PLANNED_BLOCKED", None


def packet_readiness(manifest: dict, registry: dict, activation: dict | None, packet_id: str) -> bool:
    if validate_manifest(manifest, registry, activation):
        return False
    if activation is None or activation.get("selected_packet_id") != packet_id:
        return False
    matches = [packet for entry in manifest.get("modules", [])
               for packet in entry.get("packets", []) if packet.get("packet_id") == packet_id]
    return len(matches) == 1 and matches[0].get("status") == "EXECUTOR_READY"


def validate_manifest(manifest: dict, registry: dict, activation: dict | None = None) -> list[str]:
    issues: list[str] = []
    source = registry.get("modules", [])
    plans = manifest.get("modules", [])
    if manifest.get("schema_version") != 1 or manifest.get("module_count") != 80:
        issues.append("schema_version=1 and module_count=80 required")
    if activation is None:
        if manifest.get("status") != "ALL_PROPOSED_BLOCKED_NOT_ACTUAL_CODE_PRS":
            issues.append("manifest must remain blocked without G6 activation")
    else:
        if manifest.get("status") not in (ACTIVATED_STATUS, COMPLETED_STATUS):
            issues.append("manifest activation/completion status mismatch")
        issues.extend(validate_activation(activation))
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
            want_status, want_pr = expected_packet_state(mid, idx, activation, manifest.get("status"))
            if packet.get("status") != want_status or packet.get("github_pr") != want_pr:
                issues.append(f"{mid}: code PR must not be opened/authorized by documentary map; expected {want_status}/{want_pr}")
            if want_status in ("EXECUTOR_READY", "COMPLETED"):
                if (packet.get("risk") != "STANDARD"
                        or packet.get("release_class") != "INTERNAL_ONLY"
                        or packet.get("approved_adr") != "docs/adr/0083-core-01-internal-headless-slice.md"
                        or packet.get("activation_evidence") != "docs/evidence/NLE-PRPLAN-CORE-01-03-G6-ACTIVATION.md"):
                    issues.append(f"{mid}: ready/completed packet lacks bounded risk/ADR/evidence")
            elif any(field in packet for field in ("risk", "release_class", "approved_adr", "activation_evidence")):
                issues.append(f"{mid}: blocked or documentary packet claims executor metadata")
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
    if manifest.get("status") == COMPLETED_STATUS:
        statuses = [p.get("status") for entry in plans for p in entry.get("packets", [])]
        if statuses.count("COMPLETED") != 1 or "EXECUTOR_READY" in statuses:
            issues.append("completed activation must have exactly one COMPLETED and zero EXECUTOR_READY packets")
    return issues


def validate_repository(root: Path = ROOT) -> list[str]:
    root = root.resolve()
    try:
        reg = json.loads((root / "docs/queue/implementation-registry.json").read_text(encoding="utf-8"))
        manifest = json.loads((root / "docs/pr-plans/manifest.json").read_text(encoding="utf-8"))
    except (OSError, UnicodeError, ValueError) as err:
        return [f"Cannot read JSON: {err}"]
    issues = []
    activation = None
    if manifest.get("status") in (ACTIVATED_STATUS, COMPLETED_STATUS):
        path = root / "docs/queue/packet-activations.json"
        try:
            activation = json.loads(path.read_text(encoding="utf-8"))
        except (OSError, UnicodeError, ValueError) as err:
            issues.append(f"Missing/invalid bounded G6 activation record: {err}")
    issues.extend(validate_manifest(manifest, reg, activation))
    if activation is not None:
        for key in ("approved_adr", "approved_contract", "work_order", "activation_evidence"):
            path = root / activation[key]
            if not path.is_file():
                issues.append(f"G6 evidence file missing: {path}")
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
    statuses = [p["status"] for m in data["modules"] for p in m["packets"]]
    print(f"PR plan PASS: {data['module_count']} module WOs stay BLOCKED; "
          f"{data['planned_packet_count']} packets: {statuses.count('PLANNED_BLOCKED')} blocked, "
          f"{statuses.count('EXECUTOR_READY')} individually ready, "
          f"{statuses.count('COMPLETED')} completed, 0 code PRs opened by this validator.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
