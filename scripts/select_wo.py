#!/usr/bin/env python3
"""Read-only view of Stormline's versioned future Zcode Work Order queue."""
from __future__ import annotations
import argparse
import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
p = argparse.ArgumentParser(description="View an approved catalog work-order draft (never authorizes code)")
p.add_argument("module_id", nargs="?", help="CORE-01, GFX-08, AI-04, ...")
p.add_argument("--list", action="store_true", help="list all module packets and states")
p.add_argument("--json", action="store_true", help="machine-readable summary")
args = p.parse_args()
registry = json.loads((ROOT / "docs/queue/implementation-registry.json").read_text(encoding="utf-8"))
mods = registry["modules"]
if args.list or not args.module_id:
    if args.json:
        print(json.dumps([
            {"module": m["module_id"], "wo": m["id"], "status": m["work_order_status"], "issue_number": m.get("github_issue"),
             "path": m["file"], "dependencies": m["dependencies"]}
            for m in mods
        ], indent=2))
    else:
        for m in mods:
            print(f'{m["module_id"]:9s} {m["id"]:29s} {m["work_order_status"]}')
    raise SystemExit(0)

selected = next((m for m in mods if m["module_id"].upper() == args.module_id.upper()
                 or m["id"].upper() == args.module_id.upper()), None)
if selected is None:
    p.error(f"unknown module: {args.module_id}")
ready = bool(selected["executor_ready"]) and selected["approved_adr"] and selected["context_lock_sha"]
result = {
    "module_id": selected["module_id"],
    "work_order_id": selected["id"],
    "packet_file": selected["file"],
    "dependencies": selected["dependencies"],
    "issue_number": selected.get("github_issue"),
    "issue_url": selected.get("issue_url"),
    "status": selected["work_order_status"],
    "executor_ready": bool(ready),
    "next_action": "EXECUTE_ONLY_AFTER_NEW_OBJECTIVE_AUDIT" if ready else
                   "BLOCKED: planner must approve ADR, contracts, exact files/tests, release class and current context",
}
if args.json:
    print(json.dumps(result, indent=2))
else:
    print(f'Work Order: {result["work_order_id"]}')
    print(f'Packet: {result["packet_file"]}')
    print(f'GitHub issue: {result["issue_url"]}')
    print(f'Dependencies: {", ".join(result["dependencies"]) or "(foundational)"}')
    print(f'Status: {result["status"]}')
    print(f'Executor-ready: {result["executor_ready"]}')
    print(f'Next: {result["next_action"]}')
if not ready:
    raise SystemExit(2)
