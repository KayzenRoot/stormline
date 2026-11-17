#!/usr/bin/env python3
"""Positive and negative tests for proposed Stormline PR plan validation."""
import copy
import subprocess
import json
from pathlib import Path
import sys
import tempfile
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parent))
import validate_pr_plans as v


class PrPlanValidationTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.manifest = json.loads(v.MANIFEST.read_text(encoding="utf-8"))
        cls.registry = json.loads(v.REGISTRY.read_text(encoding="utf-8"))
        cls.activation = json.loads(v.ACTIVATION_FILE.read_text(encoding="utf-8"))

    def check(self, edit):
        d = copy.deepcopy(self.manifest)
        edit(d)
        return v.validate_manifest(d, self.registry, self.activation)

    def test_real_manifest(self):
        self.assertEqual([], v.validate_repository(v.ROOT))

    def test_missing_module(self):
        self.assertTrue(any("80" in x or "missing" in x for x in
                            self.check(lambda d: d["modules"].pop())))

    def test_wrong_formal_dependency(self):
        self.assertTrue(any("formal_dependencies" in x for x in
                            self.check(lambda d: d["modules"][1].update(formal_dependencies=[]))))

    def test_duplicate_packet(self):
        def wrong(d):
            d["modules"][0]["packets"][1]["packet_id"] = d["modules"][0]["packets"][0]["packet_id"]
        self.assertTrue(any("duplicate" in x for x in self.check(wrong)))

    def test_nonnull_real_pr_claim_fails(self):
        self.assertTrue(any("must not be opened" in x for x in
                            self.check(lambda d: d["modules"][0]["packets"][0].update(github_pr=999))))

    def test_ready_packet_is_rejected(self):
        self.assertTrue(any("must not be opened" in x for x in
                            self.check(lambda d: d["modules"][0]["packets"][0].update(status="READY"))))

    def test_missing_contract_gate(self):
        self.assertTrue(any("invalid gate" in x for x in
                            self.check(lambda d: d["modules"][0]["packets"][1].update(kind="IMPLEMENTATION"))))

    def test_wrong_packet_predecessor(self):
        self.assertTrue(any("broken PR packet dependency" in x for x in
                            self.check(lambda d: d["modules"][0]["packets"][3].update(depends_on=[]))))

    def test_wrong_count(self):
        self.assertTrue(any("packet count" in x for x in
                            self.check(lambda d: d.update(planned_packet_count=20))))


    def test_only_single_scoped_packet_can_be_ready(self):
        ready = [p["packet_id"] for m in self.manifest["modules"] for p in m["packets"]
                 if p["status"] == "EXECUTOR_READY"]
        self.assertEqual(["NLE-PRPLAN-CORE-01-03"], ready)
        self.assertTrue(v.packet_readiness(self.manifest, self.registry, self.activation, ready[0]))
        self.assertFalse(v.packet_readiness(self.manifest, self.registry, self.activation, "NLE-PRPLAN-CORE-01-04"))
        self.assertFalse(v.packet_readiness(self.manifest, self.registry, self.activation, "NLE-PRPLAN-CORE-02-03"))

    def test_no_activation_record_denies_ready(self):
        self.assertTrue(v.validate_manifest(self.manifest, self.registry, None))
        self.assertFalse(v.packet_readiness(self.manifest, self.registry, None, "NLE-PRPLAN-CORE-01-03"))

    def test_forged_approval_or_risk_denied(self):
        bad = copy.deepcopy(self.activation)
        bad["owner_ratification_pr"] = 999
        self.assertTrue(v.validate_manifest(self.manifest, self.registry, bad))
        bad = copy.deepcopy(self.activation)
        bad["risk"] = "LOW"
        self.assertTrue(v.validate_manifest(self.manifest, self.registry, bad))
        bad = copy.deepcopy(self.activation)
        bad["source_blob_sha1"]["checkpoint"] = "bad"
        self.assertTrue(v.validate_manifest(self.manifest, self.registry, bad))

    def test_any_second_packet_activation_denied(self):
        def wrong(d):
            d["modules"][0]["packets"][3]["status"] = "EXECUTOR_READY"
        self.assertTrue(self.check(wrong))

    def test_module_level_promotion_remains_forbidden(self):
        reg = copy.deepcopy(self.registry)
        reg["modules"][0]["executor_ready"] = True
        self.assertTrue(v.validate_manifest(self.manifest, reg, self.activation))


    def test_selector_cli_fail_closed_and_one_allowed(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        allowed = subprocess.run([sys.executable, selector, "NLE-PRPLAN-CORE-01-03", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(0, allowed.returncode, allowed.stderr)
        self.assertTrue(json.loads(allowed.stdout)["executor_ready"])
        for packet_id in ("NLE-PRPLAN-CORE-01-04", "NLE-PRPLAN-CORE-02-03",
                          "NLE-PRPLAN-NET-01-03", "NLE-PRPLAN-CORE-01-99"):
            blocked = subprocess.run([sys.executable, selector, packet_id, "--json"],
                                     capture_output=True, text=True, timeout=20, check=False)
            self.assertEqual(2, blocked.returncode, (packet_id, blocked.stdout, blocked.stderr))
            self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_missing_document(self):
        with tempfile.TemporaryDirectory() as temp:
            root = Path(temp)
            (root / "docs/pr-plans").mkdir(parents=True)
            (root / "docs/queue").mkdir(parents=True)
            (root / "docs/pr-plans/manifest.json").write_text(json.dumps(self.manifest), encoding="utf-8")
            (root / "docs/queue/implementation-registry.json").write_text(json.dumps(self.registry), encoding="utf-8")
            errs = v.validate_repository(root)
            self.assertTrue(any("missing module PR plan" in x for x in errs))


if __name__ == "__main__":
    unittest.main()
