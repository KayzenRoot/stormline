#!/usr/bin/env python3
"""Fail-closed, read-only executor selection of one owner-approved Stormline PR packet."""
from __future__ import annotations
import argparse
import json
from pathlib import Path
import sys

import validate_pr_plans as gates

def main() -> int:
    parser = argparse.ArgumentParser(description="Select a single audited packet, never a whole blocked module")
    parser.add_argument("packet_id", help="Stable NLE-PRPLAN-MODULE-NN packet ID")
    parser.add_argument("--json", action="store_true", help="Machine-readable result")
    args = parser.parse_args()
    issues = gates.validate_repository()
    manifest = json.loads(gates.MANIFEST.read_text(encoding="utf-8"))
    registry = json.loads(gates.REGISTRY.read_text(encoding="utf-8"))
    activation = json.loads(gates.ACTIVATION_FILE.read_text(encoding="utf-8")) if gates.ACTIVATION_FILE.is_file() else None
    ready = not issues and gates.packet_readiness(manifest, registry, activation, args.packet_id)
    entry = next((p for m in manifest["modules"] for p in m["packets"]
                  if p["packet_id"] == args.packet_id), None)
    result = {
        "packet_id": args.packet_id,
        "status": entry["status"] if entry else "UNKNOWN",
        "executor_ready": bool(ready),
        "work_order": activation["work_order"] if ready else None,
        "next_action": "PREFLIGHT_FRESH_CONTEXT_LOCK_THEN_EXECUTE_APPROVED_WORK_ORDER" if ready
                       else "BLOCKED: no audited per-packet authorization or invalid canonical sources",
        "validation_issues": issues,
    }
    print(json.dumps(result, indent=2) if args.json else
          f"{result['packet_id']}: {result['status']} -> {result['next_action']}")
    return 0 if ready else 2

if __name__ == "__main__":
    raise SystemExit(main())
