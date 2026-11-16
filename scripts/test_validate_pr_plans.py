#!/usr/bin/env python3
"""Positive and negative tests for proposed Stormline PR plan validation."""
import copy
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

    def check(self, edit):
        d = copy.deepcopy(self.manifest)
        edit(d)
        return v.validate_manifest(d, self.registry)

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
