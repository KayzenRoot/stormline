#!/usr/bin/env python3
"""Positive and negative tests for Stormline PR plan and G6 activation validation."""
import copy
import json
import subprocess
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
        cls.core08_activation = json.loads(v.CORE01_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.core09_activation = json.loads(v.CORE01_09_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.core10_activation = json.loads(v.CORE01_10_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.core11_activation = json.loads(v.CORE01_11_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.core02_activation = json.loads(v.CORE02_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.core12_activation = json.loads(v.CORE01_12_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.core13_activation = json.loads(v.CORE01_13_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.core14_activation = json.loads(v.CORE01_14_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.core15_activation = json.loads(v.CORE01_15_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.core16_activation = json.loads(v.CORE01_16_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.core02_04_activation = json.loads(v.CORE02_04_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.core02_05_activation = json.loads(v.CORE02_05_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.core02_06_activation = json.loads(v.CORE02_06_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.core02_07_activation = json.loads(v.CORE02_07_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.core02_08_activation = json.loads(v.CORE02_08_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.core02_09_activation = json.loads(v.CORE02_09_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.core02_10_activation = json.loads(v.CORE02_10_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.core03_01_activation = json.loads(v.CORE03_01_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.core03_02_activation = json.loads(v.CORE03_02_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.core03_03_activation = json.loads(v.CORE03_03_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.core03_09_activation = json.loads(v.CORE03_09_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.core04_01_activation = json.loads(v.CORE04_01_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.core04_02_activation = json.loads(v.CORE04_02_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.core04_03_activation = json.loads(v.CORE04_03_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.core04_04_activation = json.loads(v.CORE04_04_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.core04_09_activation = json.loads(v.CORE04_09_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.core05_01_activation = json.loads(v.CORE05_01_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.core05_02_activation = json.loads(v.CORE05_02_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.core05_03_activation = json.loads(v.CORE05_03_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.core05_04_activation = json.loads(v.CORE05_04_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.core05_05_activation = json.loads(v.CORE05_05_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.core05_06_activation = json.loads(v.CORE05_06_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.core05_07_activation = json.loads(v.CORE05_07_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.core05_08_activation = json.loads(v.CORE05_08_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.core05_09_activation = json.loads(v.CORE05_09_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.core06_01_activation = json.loads(v.CORE06_01_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.core06_02_activation = json.loads(v.CORE06_02_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.core06_03_activation = json.loads(v.CORE06_03_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.core06_04_activation = json.loads(v.CORE06_04_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.core06_05_activation = json.loads(v.CORE06_05_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.core06_06_activation = json.loads(v.CORE06_06_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.core06_07_activation = json.loads(v.CORE06_07_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.core06_08_activation = json.loads(v.CORE06_08_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.core06_09_activation = json.loads(v.CORE06_09_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.data01_01_activation = json.loads(v.DATA01_01_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.data01_02_activation = json.loads(v.DATA01_02_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.data01_03_activation = json.loads(v.DATA01_03_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.data01_04_activation = json.loads(v.DATA01_04_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.data01_05_activation = json.loads(v.DATA01_05_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.data01_06_activation = json.loads(v.DATA01_06_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.data01_07_activation = json.loads(v.DATA01_07_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.data01_08_activation = json.loads(v.DATA01_08_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.data01_09_activation = json.loads(v.DATA01_09_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.data02_01_activation = json.loads(v.DATA02_01_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.data02_02_activation = json.loads(v.DATA02_02_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.data02_03_activation = json.loads(v.DATA02_03_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.data02_04_activation = json.loads(v.DATA02_04_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.data02_05_activation = json.loads(v.DATA02_05_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.data02_06_activation = json.loads(v.DATA02_06_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.data02_07_activation = json.loads(v.DATA02_07_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.data02_08_activation = json.loads(v.DATA02_08_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.data02_09_activation = json.loads(v.DATA02_09_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.data03_01_activation = json.loads(v.DATA03_01_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.data03_02_activation = json.loads(v.DATA03_02_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.data03_03_activation = json.loads(v.DATA03_03_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.data03_04_activation = json.loads(v.DATA03_04_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.data03_05_activation = json.loads(v.DATA03_05_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.data03_06_activation = json.loads(v.DATA03_06_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.data03_07_activation = json.loads(v.DATA03_07_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.data03_08_activation = json.loads(v.DATA03_08_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.data03_09_activation = json.loads(v.DATA03_09_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.data04_01_activation = json.loads(v.DATA04_01_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.data04_02_activation = json.loads(v.DATA04_02_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.data04_03_activation = json.loads(v.DATA04_03_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.data04_04_activation = json.loads(v.DATA04_04_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.data04_05_activation = json.loads(v.DATA04_05_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.data04_06_activation = json.loads(v.DATA04_06_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.data04_07_activation = json.loads(v.DATA04_07_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.data05_01_activation = json.loads(v.DATA05_01_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.data05_02_activation = json.loads(v.DATA05_02_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.data05_03_activation = json.loads(v.DATA05_03_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.data05_04_activation = json.loads(v.DATA05_04_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.data05_05_activation = json.loads(v.DATA05_05_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.data05_06_activation = json.loads(v.DATA05_06_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.data05_07_activation = json.loads(v.DATA05_07_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.data05_08_activation = json.loads(v.DATA05_08_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx01_01_activation = json.loads(v.GFX01_01_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx01_02_activation = json.loads(v.GFX01_02_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx01_03_activation = json.loads(v.GFX01_03_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx01_04_activation = json.loads(v.GFX01_04_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx01_05_activation = json.loads(v.GFX01_05_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx01_06_activation = json.loads(v.GFX01_06_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx01_07_activation = json.loads(v.GFX01_07_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx01_08_activation = json.loads(v.GFX01_08_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx01_09_activation = json.loads(v.GFX01_09_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx02_01_activation = json.loads(v.GFX02_01_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx02_02_activation = json.loads(v.GFX02_02_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx02_03_activation = json.loads(v.GFX02_03_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx02_04_activation = json.loads(v.GFX02_04_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx02_05_activation = json.loads(v.GFX02_05_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx02_06_activation = json.loads(v.GFX02_06_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx02_07_activation = json.loads(v.GFX02_07_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx02_08_activation = json.loads(v.GFX02_08_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx03_01_activation = json.loads(v.GFX03_01_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx03_02_activation = json.loads(v.GFX03_02_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx03_03_activation = json.loads(v.GFX03_03_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx03_04_activation = json.loads(v.GFX03_04_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx03_05_activation = json.loads(v.GFX03_05_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx03_06_activation = json.loads(v.GFX03_06_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx03_07_activation = json.loads(v.GFX03_07_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx03_08_activation = json.loads(v.GFX03_08_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx04_01_activation = json.loads(v.GFX04_01_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx04_02_activation = json.loads(v.GFX04_02_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx04_03_activation = json.loads(v.GFX04_03_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx04_04_activation = json.loads(v.GFX04_04_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx04_05_activation = json.loads(v.GFX04_05_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx04_06_activation = json.loads(v.GFX04_06_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx04_07_activation = json.loads(v.GFX04_07_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx04_08_activation = json.loads(v.GFX04_08_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx04_09_activation = json.loads(v.GFX04_09_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx05_01_activation = json.loads(v.GFX05_01_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx05_02_activation = json.loads(v.GFX05_02_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx05_03_activation = json.loads(v.GFX05_03_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx05_04_activation = json.loads(v.GFX05_04_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx05_05_activation = json.loads(v.GFX05_05_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx05_06_activation = json.loads(v.GFX05_06_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx05_07_activation = json.loads(v.GFX05_07_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx05_08_activation = json.loads(v.GFX05_08_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx05_09_activation = json.loads(v.GFX05_09_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx06_01_activation = json.loads(v.GFX06_01_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx06_02_activation = json.loads(v.GFX06_02_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx06_03_activation = json.loads(v.GFX06_03_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx06_04_activation = json.loads(v.GFX06_04_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx06_05_activation = json.loads(v.GFX06_05_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx06_06_activation = json.loads(v.GFX06_06_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx06_07_activation = json.loads(v.GFX06_07_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx06_08_activation = json.loads(v.GFX06_08_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx06_09_activation = json.loads(v.GFX06_09_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx07_01_activation = json.loads(v.GFX07_01_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx07_02_activation = json.loads(v.GFX07_02_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx07_03_activation = json.loads(v.GFX07_03_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx07_04_activation = json.loads(v.GFX07_04_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx07_05_activation = json.loads(v.GFX07_05_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx07_06_activation = json.loads(v.GFX07_06_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx07_07_activation = json.loads(v.GFX07_07_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx07_08_activation = json.loads(v.GFX07_08_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx07_09_activation = json.loads(v.GFX07_09_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx08_01_activation = json.loads(v.GFX08_01_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx08_02_activation = json.loads(v.GFX08_02_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx08_03_activation = json.loads(v.GFX08_03_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx08_04_activation = json.loads(v.GFX08_04_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx08_05_activation = json.loads(v.GFX08_05_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx08_06_activation = json.loads(v.GFX08_06_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx08_07_activation = json.loads(v.GFX08_07_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx08_08_activation = json.loads(v.GFX08_08_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.gfx08_09_activation = json.loads(v.GFX08_09_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.two01_01_activation = json.loads(v.TWO01_01_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.two01_02_activation = json.loads(v.TWO01_02_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.two01_03_activation = json.loads(v.TWO01_03_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.activation = json.loads(v.TWO01_03_ACTIVATION_FILE.read_text(encoding="utf-8"))

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

    def test_predecessor_reconciliation(self):
        packets = self.manifest["modules"][0]["packets"]
        self.assertEqual("COMPLETED", packets[2]["status"])
        self.assertEqual(428, packets[2]["github_pr"])
        self.assertEqual("COMPLETED", packets[3]["status"])
        self.assertEqual(428, packets[3]["github_pr"])
        self.assertEqual("COMPLETED", packets[4]["status"])
        self.assertEqual(428, packets[4]["github_pr"])
        self.assertEqual("COMPLETED", packets[5]["status"])
        self.assertEqual(432, packets[5]["github_pr"])
        self.assertEqual("COMPLETED", packets[6]["status"])
        self.assertEqual(435, packets[6]["github_pr"])
        self.assertEqual("COMPLETED", packets[7]["status"])
        self.assertEqual(438, packets[7]["github_pr"])
        ready = [p["packet_id"] for m in self.manifest["modules"] for p in m["packets"]
                 if p["status"] == "EXECUTOR_READY"]
        self.assertEqual(["NLE-PRPLAN-TWO-01-03"], ready)
        completed = [p["packet_id"] for m in self.manifest["modules"] for p in m["packets"]
                     if p["status"] == "COMPLETED"]
        self.assertEqual(["NLE-PRPLAN-CORE-01-03", "NLE-PRPLAN-CORE-01-04",
                          "NLE-PRPLAN-CORE-01-05", "NLE-PRPLAN-CORE-01-06",
                          "NLE-PRPLAN-CORE-01-07", "NLE-PRPLAN-CORE-01-08",
                          "NLE-PRPLAN-CORE-01-09", "NLE-PRPLAN-CORE-01-10",
                          "NLE-PRPLAN-CORE-01-11", "NLE-PRPLAN-CORE-01-12",
                          "NLE-PRPLAN-CORE-01-13", "NLE-PRPLAN-CORE-01-14",
                          "NLE-PRPLAN-CORE-01-15", "NLE-PRPLAN-CORE-01-16",
                          "NLE-PRPLAN-CORE-02-03", "NLE-PRPLAN-CORE-02-04",
                          "NLE-PRPLAN-CORE-02-05", "NLE-PRPLAN-CORE-02-06",
                          "NLE-PRPLAN-CORE-02-07", "NLE-PRPLAN-CORE-02-08",
                          "NLE-PRPLAN-CORE-02-09", "NLE-PRPLAN-CORE-02-10",
                          "NLE-PRPLAN-CORE-03-03", "NLE-PRPLAN-CORE-03-04",
                          "NLE-PRPLAN-CORE-03-05", "NLE-PRPLAN-CORE-03-06",
                          "NLE-PRPLAN-CORE-03-07", "NLE-PRPLAN-CORE-03-08",
                          "NLE-PRPLAN-CORE-03-09", "NLE-PRPLAN-CORE-03-10",
                          "NLE-PRPLAN-CORE-04-03", "NLE-PRPLAN-CORE-04-04",
                          "NLE-PRPLAN-CORE-04-05", "NLE-PRPLAN-CORE-04-06",
                          "NLE-PRPLAN-CORE-04-07", "NLE-PRPLAN-CORE-04-08",
                          "NLE-PRPLAN-CORE-04-09", "NLE-PRPLAN-CORE-04-10",
                          "NLE-PRPLAN-CORE-05-03", "NLE-PRPLAN-CORE-05-04", "NLE-PRPLAN-CORE-05-05", "NLE-PRPLAN-CORE-05-06", "NLE-PRPLAN-CORE-05-07", "NLE-PRPLAN-CORE-05-08", "NLE-PRPLAN-CORE-05-09", "NLE-PRPLAN-CORE-05-10",
                          "NLE-PRPLAN-CORE-06-03", "NLE-PRPLAN-CORE-06-04", "NLE-PRPLAN-CORE-06-05", "NLE-PRPLAN-CORE-06-06", "NLE-PRPLAN-CORE-06-07", "NLE-PRPLAN-CORE-06-08", "NLE-PRPLAN-CORE-06-09",
                          "NLE-PRPLAN-CORE-06-10", "NLE-PRPLAN-DATA-01-03",
                          "NLE-PRPLAN-DATA-01-04", "NLE-PRPLAN-DATA-01-05", "NLE-PRPLAN-DATA-01-06", "NLE-PRPLAN-DATA-01-07", "NLE-PRPLAN-DATA-01-08", "NLE-PRPLAN-DATA-01-09", "NLE-PRPLAN-DATA-01-10", "NLE-PRPLAN-DATA-02-03", "NLE-PRPLAN-DATA-02-04", "NLE-PRPLAN-DATA-02-05", "NLE-PRPLAN-DATA-02-06", "NLE-PRPLAN-DATA-02-07", "NLE-PRPLAN-DATA-02-08", "NLE-PRPLAN-DATA-02-09", "NLE-PRPLAN-DATA-02-10", "NLE-PRPLAN-DATA-03-03", "NLE-PRPLAN-DATA-03-04", "NLE-PRPLAN-DATA-03-05", "NLE-PRPLAN-DATA-03-06", "NLE-PRPLAN-DATA-03-07", "NLE-PRPLAN-DATA-03-08", "NLE-PRPLAN-DATA-03-09", "NLE-PRPLAN-DATA-03-10", "NLE-PRPLAN-DATA-04-03", "NLE-PRPLAN-DATA-04-04", "NLE-PRPLAN-DATA-04-05", "NLE-PRPLAN-DATA-04-06", "NLE-PRPLAN-DATA-04-07", "NLE-PRPLAN-DATA-04-08", "NLE-PRPLAN-DATA-05-03", "NLE-PRPLAN-DATA-05-04", "NLE-PRPLAN-DATA-05-05", "NLE-PRPLAN-DATA-05-06", "NLE-PRPLAN-DATA-05-07", "NLE-PRPLAN-DATA-05-08", "NLE-PRPLAN-DATA-05-09", "NLE-PRPLAN-GFX-01-03", "NLE-PRPLAN-GFX-01-04", "NLE-PRPLAN-GFX-01-05", "NLE-PRPLAN-GFX-01-06", "NLE-PRPLAN-GFX-01-07", "NLE-PRPLAN-GFX-01-08", "NLE-PRPLAN-GFX-01-09", "NLE-PRPLAN-GFX-01-10", "NLE-PRPLAN-GFX-02-03", "NLE-PRPLAN-GFX-02-04", "NLE-PRPLAN-GFX-02-05", "NLE-PRPLAN-GFX-02-06", "NLE-PRPLAN-GFX-02-07", "NLE-PRPLAN-GFX-02-08", "NLE-PRPLAN-GFX-02-09", "NLE-PRPLAN-GFX-03-03", "NLE-PRPLAN-GFX-03-04", "NLE-PRPLAN-GFX-03-05", "NLE-PRPLAN-GFX-03-06", "NLE-PRPLAN-GFX-03-07", "NLE-PRPLAN-GFX-03-08", "NLE-PRPLAN-GFX-03-09", "NLE-PRPLAN-GFX-04-03", "NLE-PRPLAN-GFX-04-04", "NLE-PRPLAN-GFX-04-05", "NLE-PRPLAN-GFX-04-06", "NLE-PRPLAN-GFX-04-07", "NLE-PRPLAN-GFX-04-08", "NLE-PRPLAN-GFX-04-09", "NLE-PRPLAN-GFX-04-10", "NLE-PRPLAN-GFX-05-03", "NLE-PRPLAN-GFX-05-04", "NLE-PRPLAN-GFX-05-05", "NLE-PRPLAN-GFX-05-06", "NLE-PRPLAN-GFX-05-07", "NLE-PRPLAN-GFX-05-08", "NLE-PRPLAN-GFX-05-09", "NLE-PRPLAN-GFX-05-10", "NLE-PRPLAN-GFX-06-03", "NLE-PRPLAN-GFX-06-04", "NLE-PRPLAN-GFX-06-05", "NLE-PRPLAN-GFX-06-06", "NLE-PRPLAN-GFX-06-07", "NLE-PRPLAN-GFX-06-08", "NLE-PRPLAN-GFX-06-09", "NLE-PRPLAN-GFX-06-10", "NLE-PRPLAN-GFX-07-03", "NLE-PRPLAN-GFX-07-04", "NLE-PRPLAN-GFX-07-05", "NLE-PRPLAN-GFX-07-06", "NLE-PRPLAN-GFX-07-07", "NLE-PRPLAN-GFX-07-08", "NLE-PRPLAN-GFX-07-09", "NLE-PRPLAN-GFX-07-10", "NLE-PRPLAN-GFX-08-03", "NLE-PRPLAN-GFX-08-04", "NLE-PRPLAN-GFX-08-05", "NLE-PRPLAN-GFX-08-06", "NLE-PRPLAN-GFX-08-07", "NLE-PRPLAN-GFX-08-08", "NLE-PRPLAN-GFX-08-09", "NLE-PRPLAN-GFX-08-10"], completed)
        self.assertEqual("COMPLETED", self.manifest["modules"][0]["packets"][8]["status"])
        self.assertEqual(444, self.manifest["modules"][0]["packets"][8]["github_pr"])
        self.assertEqual("COMPLETED", self.manifest["modules"][0]["packets"][9]["status"])
        self.assertEqual(447, self.manifest["modules"][0]["packets"][9]["github_pr"])
        self.assertEqual("COMPLETED", self.manifest["modules"][0]["packets"][10]["status"])
        self.assertEqual(450, self.manifest["modules"][0]["packets"][10]["github_pr"])
        self.assertEqual("COMPLETED", self.manifest["modules"][0]["packets"][11]["status"])
        self.assertEqual(453, self.manifest["modules"][0]["packets"][11]["github_pr"])
        self.assertEqual("COMPLETED", self.manifest["modules"][0]["packets"][12]["status"])
        self.assertEqual(456, self.manifest["modules"][0]["packets"][12]["github_pr"])
        self.assertEqual("COMPLETED", self.manifest["modules"][0]["packets"][13]["status"])
        self.assertEqual(459, self.manifest["modules"][0]["packets"][13]["github_pr"])
        self.assertEqual("COMPLETED", self.manifest["modules"][0]["packets"][14]["status"])
        self.assertEqual(462, self.manifest["modules"][0]["packets"][14]["github_pr"])
        core02 = self.manifest["modules"][1]["packets"]
        self.assertEqual("APPROVED_GOVERNANCE", core02[0]["status"])
        self.assertEqual("APPROVED_CONTRACT", core02[1]["status"])
        self.assertEqual("COMPLETED", core02[2]["status"])
        self.assertEqual(441, core02[2]["github_pr"])
        self.assertEqual("COMPLETED", core02[3]["status"])
        self.assertEqual(466, core02[3]["github_pr"])
        self.assertEqual("COMPLETED", core02[4]["status"])
        self.assertEqual(469, core02[4]["github_pr"])
        self.assertEqual("COMPLETED", core02[5]["status"])
        self.assertEqual(472, core02[5]["github_pr"])
        self.assertEqual("COMPLETED", core02[6]["status"])
        self.assertEqual(475, core02[6]["github_pr"])
        self.assertEqual("COMPLETED", core02[7]["status"])
        self.assertEqual(484, core02[7]["github_pr"])
        self.assertEqual("COMPLETED", core02[8]["status"])
        self.assertEqual(487, core02[8]["github_pr"])
        self.assertEqual("COMPLETED", core02[9]["status"])
        self.assertEqual(489, core02[9]["github_pr"])
        core03 = self.manifest["modules"][2]["packets"]
        self.assertEqual("APPROVED_GOVERNANCE", core03[0]["status"])
        self.assertEqual(492, core03[0]["github_pr"])
        self.assertEqual("APPROVED_CONTRACT", core03[1]["status"])
        self.assertEqual(505, core03[1]["github_pr"])
        self.assertEqual("COMPLETED", core03[2]["status"])
        self.assertEqual(508, core03[2]["github_pr"])
        self.assertEqual("ELEVATED", core03[2]["risk"])
        self.assertEqual("INTERNAL_ONLY", core03[2]["release_class"])
        self.assertEqual("COMPLETED", core03[3]["status"])
        self.assertEqual(v.CORE03_04_CLOSEOUT_PR, core03[3]["github_pr"])
        self.assertEqual("ELEVATED", core03[3]["risk"])
        self.assertEqual("INTERNAL_ONLY", core03[3]["release_class"])
        self.assertEqual("COMPLETED", core03[4]["status"])
        self.assertEqual(v.CORE03_05_CLOSEOUT_PR, core03[4]["github_pr"])
        self.assertEqual("ELEVATED", core03[4]["risk"])
        self.assertEqual("INTERNAL_ONLY", core03[4]["release_class"])
        self.assertEqual("COMPLETED", core03[5]["status"])
        self.assertEqual(v.CORE03_06_CLOSEOUT_PR, core03[5]["github_pr"])
        self.assertEqual("ELEVATED", core03[5]["risk"])
        self.assertEqual("INTERNAL_ONLY", core03[5]["release_class"])
        self.assertEqual("COMPLETED", core03[6]["status"])
        self.assertEqual(v.CORE03_07_CLOSEOUT_PR, core03[6]["github_pr"])
        self.assertEqual("ELEVATED", core03[6]["risk"])
        self.assertEqual("INTERNAL_ONLY", core03[6]["release_class"])
        self.assertEqual("COMPLETED", core03[7]["status"])
        self.assertEqual(v.CORE03_08_CLOSEOUT_PR, core03[7]["github_pr"])
        self.assertEqual("ELEVATED", core03[7]["risk"])
        self.assertEqual("INTERNAL_ONLY", core03[7]["release_class"])
        self.assertEqual("COMPLETED", core03[8]["status"])
        self.assertEqual(v.CORE03_09_CODE_PR, core03[8]["github_pr"])
        self.assertEqual("ELEVATED", core03[8]["risk"])
        self.assertEqual("INTERNAL_ONLY", core03[8]["release_class"])
        self.assertEqual("COMPLETED", core03[9]["status"])
        self.assertEqual(v.CORE03_10_CLOSEOUT_PR, core03[9]["github_pr"])
        self.assertEqual("ELEVATED", core03[9]["risk"])
        self.assertEqual("INTERNAL_ONLY", core03[9]["release_class"])
        self.assertFalse(core02[2]["capability_admission"]["module_completion_claimed"])
        self.assertFalse(core02[3]["capability_admission"]["module_completion_claimed"])
        core05 = self.manifest["modules"][4]["packets"]
        self.assertEqual("APPROVED_GOVERNANCE", core05[0]["status"])
        self.assertEqual(v.CORE05_01_GATE_PR, core05[0]["github_pr"])
        self.assertEqual("APPROVED_CONTRACT", core05[1]["status"])
        self.assertEqual(v.CORE05_02_GATE_PR, core05[1]["github_pr"])
        self.assertEqual("COMPLETED", core05[2]["status"])
        self.assertEqual(v.CORE05_03_CLOSEOUT_PR, core05[2]["github_pr"])
        self.assertEqual("ELEVATED", core05[2]["risk"])
        self.assertEqual("INTERNAL_ONLY", core05[2]["release_class"])
        self.assertEqual("COMPLETED", core05[3]["status"])
        self.assertEqual(v.CORE05_04_CLOSEOUT_PR, core05[3]["github_pr"])
        self.assertEqual("ELEVATED", core05[3]["risk"])
        self.assertEqual("INTERNAL_ONLY", core05[3]["release_class"])
        self.assertEqual("COMPLETED", core05[4]["status"])
        self.assertEqual(v.CORE05_05_CLOSEOUT_PR, core05[4]["github_pr"])
        self.assertEqual("ELEVATED", core05[4]["risk"])
        self.assertEqual("INTERNAL_ONLY", core05[4]["release_class"])
        self.assertEqual("COMPLETED", core05[5]["status"])
        self.assertEqual(v.CORE05_06_CLOSEOUT_PR, core05[5]["github_pr"])
        self.assertEqual("ELEVATED", core05[5]["risk"])
        self.assertEqual("INTERNAL_ONLY", core05[5]["release_class"])
        self.assertEqual("COMPLETED", core05[6]["status"])
        self.assertEqual(v.CORE05_07_CLOSEOUT_PR, core05[6]["github_pr"])
        self.assertEqual("ELEVATED", core05[6]["risk"])
        self.assertEqual("INTERNAL_ONLY", core05[6]["release_class"])
        self.assertEqual("COMPLETED", core05[7]["status"])
        self.assertEqual(v.CORE05_08_CLOSEOUT_PR, core05[7]["github_pr"])
        self.assertEqual("ELEVATED", core05[7]["risk"])
        self.assertEqual("INTERNAL_ONLY", core05[7]["release_class"])
        self.assertEqual("COMPLETED", core05[8]["status"])
        self.assertEqual(v.CORE05_09_CLOSEOUT_PR, core05[8]["github_pr"])
        self.assertEqual("COMPLETED", core05[9]["status"])
        self.assertEqual(v.CORE05_10_CLOSEOUT_PR, core05[9]["github_pr"])
        self.assertEqual("ELEVATED", core05[8]["risk"])
        self.assertEqual("INTERNAL_ONLY", core05[8]["release_class"])
        self.assertEqual("ELEVATED", core05[9]["risk"])
        self.assertEqual("INTERNAL_ONLY", core05[9]["release_class"])
        core06 = self.manifest["modules"][5]["packets"]
        self.assertEqual("APPROVED_GOVERNANCE", core06[0]["status"])
        self.assertEqual(v.CORE06_01_GATE_PR, core06[0]["github_pr"])
        self.assertEqual("APPROVED_CONTRACT", core06[1]["status"])
        self.assertEqual(v.CORE06_02_GATE_PR, core06[1]["github_pr"])
        self.assertEqual("COMPLETED", core06[2]["status"])
        self.assertEqual(v.CORE06_03_CODE_PR, core06[2]["github_pr"])
        self.assertEqual("ELEVATED", core06[2]["risk"])
        self.assertEqual("INTERNAL_ONLY", core06[2]["release_class"])
        self.assertEqual("COMPLETED", core06[3]["status"])
        self.assertEqual(v.CORE06_04_CODE_PR, core06[3]["github_pr"])
        self.assertEqual("ELEVATED", core06[3]["risk"])
        self.assertEqual("INTERNAL_ONLY", core06[3]["release_class"])
        self.assertEqual("COMPLETED", core06[4]["status"])
        self.assertEqual(v.CORE06_05_CODE_PR, core06[4]["github_pr"])
        self.assertEqual("ELEVATED", core06[4]["risk"])
        self.assertEqual("INTERNAL_ONLY", core06[4]["release_class"])
        self.assertEqual("COMPLETED", core06[5]["status"])
        self.assertEqual(v.CORE06_06_CODE_PR, core06[5]["github_pr"])
        self.assertEqual("ELEVATED", core06[5]["risk"])
        self.assertEqual("INTERNAL_ONLY", core06[5]["release_class"])
        self.assertEqual("COMPLETED", core06[6]["status"])
        self.assertEqual(v.CORE06_07_CODE_PR, core06[6]["github_pr"])
        self.assertEqual("ELEVATED", core06[6]["risk"])
        self.assertEqual("INTERNAL_ONLY", core06[6]["release_class"])
        self.assertEqual("COMPLETED", core06[7]["status"])
        self.assertEqual(v.CORE06_08_CODE_PR, core06[7]["github_pr"])
        self.assertEqual("ELEVATED", core06[7]["risk"])
        self.assertEqual("INTERNAL_ONLY", core06[7]["release_class"])
        self.assertEqual("COMPLETED", core06[8]["status"])
        self.assertEqual(576, core06[8]["github_pr"])
        self.assertEqual("COMPLETED", core06[9]["status"])
        self.assertEqual(v.CORE06_10_CLOSEOUT_PR, core06[9]["github_pr"])
        self.assertEqual("ELEVATED", core06[8]["risk"])
        self.assertEqual("INTERNAL_ONLY", core06[8]["release_class"])
        self.assertEqual("ELEVATED", core06[9]["risk"])
        self.assertEqual("INTERNAL_ONLY", core06[9]["release_class"])
        data01 = self.manifest["modules"][6]["packets"]
        self.assertEqual("APPROVED_GOVERNANCE", data01[0]["status"])
        self.assertEqual(v.DATA01_01_GATE_PR, data01[0]["github_pr"])
        self.assertEqual("APPROVED_CONTRACT", data01[1]["status"])
        self.assertEqual(v.DATA01_02_GATE_PR, data01[1]["github_pr"])
        self.assertEqual("COMPLETED", data01[2]["status"])
        self.assertEqual(v.DATA01_03_CODE_PR, data01[2]["github_pr"])
        self.assertEqual("ELEVATED", data01[2]["risk"])
        self.assertEqual("INTERNAL_ONLY", data01[2]["release_class"])
        self.assertEqual("COMPLETED", data01[3]["status"])
        self.assertEqual(v.DATA01_04_CODE_PR, data01[3]["github_pr"])
        self.assertEqual("ELEVATED", data01[3]["risk"])
        self.assertEqual("INTERNAL_ONLY", data01[3]["release_class"])
        self.assertEqual("COMPLETED", data01[4]["status"])
        self.assertEqual(v.DATA01_05_CODE_PR, data01[4]["github_pr"])
        self.assertEqual("ELEVATED", data01[4]["risk"])
        self.assertEqual("INTERNAL_ONLY", data01[4]["release_class"])
        self.assertEqual("COMPLETED", data01[5]["status"])
        self.assertEqual(v.DATA01_06_CODE_PR, data01[5]["github_pr"])
        self.assertEqual("ELEVATED", data01[5]["risk"])
        self.assertEqual("INTERNAL_ONLY", data01[5]["release_class"])
        self.assertEqual("COMPLETED", data01[6]["status"])
        self.assertEqual(v.DATA01_07_CODE_PR, data01[6]["github_pr"])
        self.assertEqual("ELEVATED", data01[6]["risk"])
        self.assertEqual("INTERNAL_ONLY", data01[6]["release_class"])
        self.assertEqual("COMPLETED", data01[7]["status"])
        self.assertEqual(v.DATA01_08_CODE_PR, data01[7]["github_pr"])
        self.assertEqual("ELEVATED", data01[7]["risk"])
        self.assertEqual("INTERNAL_ONLY", data01[7]["release_class"])
        self.assertEqual("COMPLETED", data01[8]["status"])
        self.assertEqual(v.DATA01_09_CODE_PR, data01[8]["github_pr"])
        self.assertEqual("ELEVATED", data01[8]["risk"])
        self.assertEqual("INTERNAL_ONLY", data01[8]["release_class"])
        self.assertEqual("COMPLETED", data01[9]["status"])
        self.assertEqual(v.DATA01_10_CLOSEOUT_PR, data01[9]["github_pr"])
        data02 = self.manifest["modules"][7]["packets"]
        self.assertEqual("APPROVED_GOVERNANCE", data02[0]["status"])
        self.assertEqual(v.DATA02_01_GATE_PR, data02[0]["github_pr"])
        self.assertEqual("APPROVED_CONTRACT", data02[1]["status"])
        self.assertEqual(v.DATA02_02_GATE_PR, data02[1]["github_pr"])
        self.assertEqual("COMPLETED", data02[2]["status"])
        self.assertEqual(v.DATA02_CODE_PRS[3], data02[2]["github_pr"])
        self.assertEqual("ELEVATED", data02[2]["risk"])
        self.assertEqual("INTERNAL_ONLY", data02[2]["release_class"])
        self.assertEqual(v.DATA02_CAPABILITY_ADMISSION,
                         data02[2]["capability_admission"])
        self.assertEqual("COMPLETED", data02[3]["status"])
        self.assertEqual(v.DATA02_CODE_PRS[4], data02[3]["github_pr"])
        self.assertEqual("ELEVATED", data02[3]["risk"])
        self.assertEqual("INTERNAL_ONLY", data02[3]["release_class"])
        self.assertEqual("COMPLETED", data02[4]["status"])
        self.assertEqual(v.DATA02_CODE_PRS[5], data02[4]["github_pr"])
        self.assertEqual("ELEVATED", data02[4]["risk"])
        self.assertEqual("INTERNAL_ONLY", data02[4]["release_class"])
        self.assertEqual("COMPLETED", data02[5]["status"])
        self.assertEqual(v.DATA02_CODE_PRS[6], data02[5]["github_pr"])
        self.assertEqual("ELEVATED", data02[5]["risk"])
        self.assertEqual("INTERNAL_ONLY", data02[5]["release_class"])
        self.assertEqual("COMPLETED", data02[6]["status"])
        self.assertEqual(v.DATA02_CODE_PRS[7], data02[6]["github_pr"])
        self.assertEqual("ELEVATED", data02[6]["risk"])
        self.assertEqual("INTERNAL_ONLY", data02[6]["release_class"])
        self.assertEqual("COMPLETED", data02[7]["status"])
        self.assertEqual(v.DATA02_CODE_PRS[8], data02[7]["github_pr"])
        self.assertEqual("ELEVATED", data02[7]["risk"])
        self.assertEqual("INTERNAL_ONLY", data02[7]["release_class"])
        self.assertEqual("COMPLETED", data02[8]["status"])
        self.assertEqual(v.DATA02_CODE_PRS[9], data02[8]["github_pr"])
        self.assertEqual("ELEVATED", data02[8]["risk"])
        self.assertEqual("INTERNAL_ONLY", data02[8]["release_class"])
        self.assertEqual("COMPLETED", data02[9]["status"])
        self.assertEqual(v.DATA02_CODE_PRS[10], data02[9]["github_pr"])
        data03 = self.manifest["modules"][8]["packets"]
        self.assertEqual("APPROVED_GOVERNANCE", data03[0]["status"])
        self.assertEqual(v.DATA03_01_GATE_PR, data03[0]["github_pr"])
        self.assertEqual("APPROVED_CONTRACT", data03[1]["status"])
        self.assertEqual(v.DATA03_02_GATE_PR, data03[1]["github_pr"])
        self.assertEqual("COMPLETED", data03[2]["status"])
        self.assertEqual(v.DATA03_CODE_PRS[3], data03[2]["github_pr"])
        self.assertEqual("ELEVATED", data03[2]["risk"])
        self.assertEqual("INTERNAL_ONLY", data03[2]["release_class"])
        self.assertEqual(v.DATA03_CAPABILITY_ADMISSION,
                         data03[2]["capability_admission"])
        self.assertEqual("COMPLETED", data03[3]["status"])
        self.assertEqual(v.DATA03_CODE_PRS[4], data03[3]["github_pr"])
        self.assertEqual("ELEVATED", data03[3]["risk"])
        self.assertEqual("INTERNAL_ONLY", data03[3]["release_class"])
        self.assertEqual("COMPLETED", data03[4]["status"])
        self.assertEqual(v.DATA03_CODE_PRS[5], data03[4]["github_pr"])
        self.assertEqual("ELEVATED", data03[4]["risk"])
        self.assertEqual("INTERNAL_ONLY", data03[4]["release_class"])
        self.assertEqual("COMPLETED", data03[5]["status"])
        self.assertEqual(v.DATA03_CODE_PRS[6], data03[5]["github_pr"])
        self.assertEqual("ELEVATED", data03[5]["risk"])
        self.assertEqual("COMPLETED", data03[5]["status"])
        self.assertEqual("COMPLETED", data03[6]["status"])
        self.assertEqual(v.DATA03_CODE_PRS[7], data03[6]["github_pr"])
        self.assertEqual("ELEVATED", data03[6]["risk"])
        self.assertEqual("INTERNAL_ONLY", data03[6]["release_class"])
        self.assertEqual("COMPLETED", data03[7]["status"])
        self.assertEqual(v.DATA03_CODE_PRS[8], data03[7]["github_pr"])
        self.assertEqual("ELEVATED", data03[7]["risk"])
        self.assertEqual("INTERNAL_ONLY", data03[7]["release_class"])
        self.assertEqual("COMPLETED", data03[8]["status"])
        self.assertEqual(v.DATA03_CODE_PRS[9], data03[8]["github_pr"])
        self.assertEqual("ELEVATED", data03[8]["risk"])
        self.assertEqual("INTERNAL_ONLY", data03[8]["release_class"])
        self.assertEqual("COMPLETED", data03[9]["status"])
        self.assertEqual(v.DATA03_CODE_PRS[10], data03[9]["github_pr"])
        data04 = self.manifest["modules"][9]["packets"]
        self.assertEqual("APPROVED_GOVERNANCE", data04[0]["status"])
        self.assertEqual(v.DATA04_01_GATE_PR, data04[0]["github_pr"])
        self.assertEqual("APPROVED_CONTRACT", data04[1]["status"])
        self.assertEqual(v.DATA04_02_GATE_PR, data04[1]["github_pr"])
        self.assertEqual("COMPLETED", data04[2]["status"])
        self.assertEqual(v.DATA04_CODE_PRS[3], data04[2]["github_pr"])
        self.assertEqual("ELEVATED", data04[2]["risk"])
        self.assertEqual("INTERNAL_ONLY", data04[2]["release_class"])
        self.assertEqual(v.DATA04_CAPABILITY_ADMISSION,
                         data04[2]["capability_admission"])
        self.assertEqual("COMPLETED", data04[3]["status"])
        self.assertEqual(v.DATA04_CODE_PRS[4], data04[3]["github_pr"])
        self.assertEqual("ELEVATED", data04[3]["risk"])
        self.assertEqual("INTERNAL_ONLY", data04[3]["release_class"])
        self.assertEqual("COMPLETED", data04[4]["status"])
        self.assertEqual(v.DATA04_CODE_PRS[5], data04[4]["github_pr"])
        self.assertEqual("ELEVATED", data04[4]["risk"])
        self.assertEqual("INTERNAL_ONLY", data04[4]["release_class"])
        self.assertEqual("COMPLETED", data04[5]["status"])
        self.assertEqual(v.DATA04_CODE_PRS[6], data04[5]["github_pr"])
        self.assertEqual("ELEVATED", data04[5]["risk"])
        self.assertEqual("INTERNAL_ONLY", data04[5]["release_class"])
        self.assertEqual("COMPLETED", data04[6]["status"])
        self.assertEqual(v.DATA04_CODE_PRS[7], data04[6]["github_pr"])
        self.assertEqual("ELEVATED", data04[6]["risk"])
        self.assertEqual("INTERNAL_ONLY", data04[6]["release_class"])
        self.assertEqual("COMPLETED", data04[7]["status"])
        self.assertEqual(v.DATA04_CODE_PRS[8], data04[7]["github_pr"])
        data05 = self.manifest["modules"][10]["packets"]
        self.assertEqual("APPROVED_GOVERNANCE", data05[0]["status"])
        self.assertEqual(v.DATA05_01_GATE_PR, data05[0]["github_pr"])
        self.assertEqual("APPROVED_CONTRACT", data05[1]["status"])
        self.assertEqual(v.DATA05_02_GATE_PR, data05[1]["github_pr"])
        self.assertEqual("COMPLETED", data05[2]["status"])
        self.assertEqual(v.DATA05_CODE_PRS[3], data05[2]["github_pr"])
        self.assertEqual("ELEVATED", data05[2]["risk"])
        self.assertEqual("INTERNAL_ONLY", data05[2]["release_class"])
        self.assertEqual(v.DATA05_CAPABILITY_ADMISSION,
                         data05[2]["capability_admission"])
        self.assertEqual("COMPLETED", data05[3]["status"])
        self.assertEqual(v.DATA05_CODE_PRS[4], data05[3]["github_pr"])
        self.assertEqual("ELEVATED", data05[3]["risk"])
        self.assertEqual("INTERNAL_ONLY", data05[3]["release_class"])
        self.assertEqual("COMPLETED", data05[4]["status"])
        self.assertEqual(v.DATA05_CODE_PRS[5], data05[4]["github_pr"])
        self.assertEqual("ELEVATED", data05[4]["risk"])
        self.assertEqual("INTERNAL_ONLY", data05[4]["release_class"])
        self.assertEqual("COMPLETED", data05[5]["status"])
        self.assertEqual(v.DATA05_CODE_PRS[6], data05[5]["github_pr"])
        self.assertEqual("ELEVATED", data05[5]["risk"])
        self.assertEqual("INTERNAL_ONLY", data05[5]["release_class"])
        self.assertEqual("COMPLETED", data05[6]["status"])
        self.assertEqual(v.DATA05_CODE_PRS[7], data05[6]["github_pr"])
        self.assertEqual("ELEVATED", data05[6]["risk"])
        self.assertEqual("INTERNAL_ONLY", data05[6]["release_class"])
        self.assertEqual("COMPLETED", data05[7]["status"])
        self.assertEqual(v.DATA05_CODE_PRS[8], data05[7]["github_pr"])
        self.assertEqual("ELEVATED", data05[7]["risk"])
        self.assertEqual("INTERNAL_ONLY", data05[7]["release_class"])
        self.assertEqual("COMPLETED", data05[8]["status"])
        self.assertEqual(v.DATA05_CODE_PRS[9], data05[8]["github_pr"])
        gfx01 = self.manifest["modules"][11]["packets"]
        self.assertEqual("APPROVED_GOVERNANCE", gfx01[0]["status"])
        self.assertEqual(v.GFX01_01_GATE_PR, gfx01[0]["github_pr"])
        self.assertEqual("APPROVED_CONTRACT", gfx01[1]["status"])
        self.assertEqual(v.GFX01_02_GATE_PR, gfx01[1]["github_pr"])
        self.assertEqual("COMPLETED", gfx01[2]["status"])
        self.assertEqual(v.GFX01_CODE_PRS[3], gfx01[2]["github_pr"])
        self.assertEqual("ELEVATED", gfx01[2]["risk"])
        self.assertEqual("INTERNAL_ONLY", gfx01[2]["release_class"])
        self.assertEqual(v.GFX01_CAPABILITY_ADMISSION,
                         gfx01[2]["capability_admission"])
        self.assertEqual("COMPLETED", gfx01[3]["status"])
        self.assertEqual(v.GFX01_CODE_PRS[4], gfx01[3]["github_pr"])
        self.assertEqual("ELEVATED", gfx01[3]["risk"])
        self.assertEqual("INTERNAL_ONLY", gfx01[3]["release_class"])
        self.assertEqual("COMPLETED", gfx01[4]["status"])
        self.assertEqual(v.GFX01_CODE_PRS[5], gfx01[4]["github_pr"])
        self.assertEqual("ELEVATED", gfx01[4]["risk"])
        self.assertEqual("INTERNAL_ONLY", gfx01[4]["release_class"])
        self.assertEqual("COMPLETED", gfx01[5]["status"])
        self.assertEqual(v.GFX01_CODE_PRS[6], gfx01[5]["github_pr"])
        self.assertEqual("ELEVATED", gfx01[5]["risk"])
        self.assertEqual("INTERNAL_ONLY", gfx01[5]["release_class"])
        self.assertEqual("COMPLETED", gfx01[6]["status"])
        self.assertEqual(v.GFX01_CODE_PRS[7], gfx01[6]["github_pr"])
        self.assertEqual("ELEVATED", gfx01[6]["risk"])
        self.assertEqual("INTERNAL_ONLY", gfx01[6]["release_class"])
        self.assertEqual("COMPLETED", gfx01[7]["status"])
        self.assertEqual(v.GFX01_CODE_PRS[8], gfx01[7]["github_pr"])
        self.assertEqual("ELEVATED", gfx01[7]["risk"])
        self.assertEqual("INTERNAL_ONLY", gfx01[7]["release_class"])
        self.assertEqual("COMPLETED", gfx01[8]["status"])
        self.assertEqual(v.GFX01_CODE_PRS[9], gfx01[8]["github_pr"])
        self.assertEqual("ELEVATED", gfx01[8]["risk"])
        self.assertEqual("INTERNAL_ONLY", gfx01[8]["release_class"])
        self.assertEqual("COMPLETED", gfx01[9]["status"])
        self.assertEqual(v.GFX01_CODE_PRS[10], gfx01[9]["github_pr"])
        gfx02 = self.manifest["modules"][12]["packets"]
        self.assertEqual("APPROVED_GOVERNANCE", gfx02[0]["status"])
        self.assertEqual(v.GFX02_01_GATE_PR, gfx02[0]["github_pr"])
        self.assertEqual("APPROVED_CONTRACT", gfx02[1]["status"])
        self.assertEqual(v.GFX02_02_GATE_PR, gfx02[1]["github_pr"])
        self.assertEqual("COMPLETED", gfx02[2]["status"])
        self.assertEqual(v.GFX02_CODE_PRS[3], gfx02[2]["github_pr"])
        self.assertEqual("COMPLETED", gfx02[3]["status"])
        self.assertEqual(v.GFX02_CODE_PRS[4], gfx02[3]["github_pr"])
        self.assertEqual("COMPLETED", gfx02[4]["status"])
        self.assertEqual(v.GFX02_CODE_PRS[5], gfx02[4]["github_pr"])
        self.assertEqual("COMPLETED", gfx02[5]["status"])
        self.assertEqual(v.GFX02_CODE_PRS[6], gfx02[5]["github_pr"])
        self.assertEqual("COMPLETED", gfx02[6]["status"])
        self.assertEqual(v.GFX02_CODE_PRS[7], gfx02[6]["github_pr"])
        self.assertEqual("COMPLETED", gfx02[7]["status"])
        self.assertEqual(v.GFX02_CODE_PRS[8], gfx02[7]["github_pr"])
        self.assertEqual("COMPLETED", gfx02[8]["status"])
        self.assertEqual(v.GFX02_CODE_PRS[9], gfx02[8]["github_pr"])
        gfx03 = self.manifest["modules"][13]["packets"]
        self.assertEqual("APPROVED_GOVERNANCE", gfx03[0]["status"])
        self.assertEqual(v.GFX03_01_GATE_PR, gfx03[0]["github_pr"])
        self.assertEqual("APPROVED_CONTRACT", gfx03[1]["status"])
        self.assertEqual(v.GFX03_02_GATE_PR, gfx03[1]["github_pr"])
        self.assertEqual("COMPLETED", gfx03[2]["status"])
        self.assertEqual(v.GFX03_CODE_PRS[3], gfx03[2]["github_pr"])
        self.assertEqual("COMPLETED", gfx03[3]["status"])
        self.assertEqual(v.GFX03_CODE_PRS[4], gfx03[3]["github_pr"])
        self.assertEqual("COMPLETED", gfx03[4]["status"])
        self.assertEqual(v.GFX03_CODE_PRS[5], gfx03[4]["github_pr"])
        self.assertEqual("COMPLETED", gfx03[5]["status"])
        self.assertEqual(v.GFX03_CODE_PRS[6], gfx03[5]["github_pr"])
        self.assertEqual("COMPLETED", gfx03[6]["status"])
        self.assertEqual(v.GFX03_CODE_PRS[7], gfx03[6]["github_pr"])
        self.assertEqual("COMPLETED", gfx03[7]["status"])
        self.assertEqual(v.GFX03_CODE_PRS[8], gfx03[7]["github_pr"])
        self.assertEqual("COMPLETED", gfx03[8]["status"])
        self.assertEqual(v.GFX03_CODE_PRS[9], gfx03[8]["github_pr"])
        core04 = self.manifest["modules"][3]["packets"]
        self.assertEqual("APPROVED_GOVERNANCE", core04[0]["status"])
        self.assertEqual(v.CORE04_01_GATE_PR, core04[0]["github_pr"])
        self.assertEqual("APPROVED_CONTRACT", core04[1]["status"])
        self.assertEqual(v.CORE04_02_GATE_PR, core04[1]["github_pr"])
        self.assertEqual("COMPLETED", core04[2]["status"])
        self.assertEqual(v.CORE04_03_CODE_PR, core04[2]["github_pr"])
        self.assertEqual("ELEVATED", core04[2]["risk"])
        self.assertEqual("INTERNAL_ONLY", core04[2]["release_class"])
        self.assertEqual("COMPLETED", core04[3]["status"])
        self.assertEqual(v.CORE04_04_CODE_PR, core04[3]["github_pr"])
        self.assertEqual("ELEVATED", core04[3]["risk"])
        self.assertEqual("INTERNAL_ONLY", core04[3]["release_class"])
        self.assertEqual("COMPLETED", core04[4]["status"])
        self.assertEqual(v.CORE04_05_CLOSEOUT_PR, core04[4]["github_pr"])
        self.assertEqual("ELEVATED", core04[4]["risk"])
        self.assertEqual("INTERNAL_ONLY", core04[4]["release_class"])
        self.assertEqual("COMPLETED", core04[5]["status"])
        self.assertEqual(v.CORE04_06_CLOSEOUT_PR, core04[5]["github_pr"])
        self.assertEqual("ELEVATED", core04[5]["risk"])
        self.assertEqual("INTERNAL_ONLY", core04[5]["release_class"])
        self.assertEqual("COMPLETED", core04[6]["status"])
        self.assertEqual(v.CORE04_07_CLOSEOUT_PR, core04[6]["github_pr"])
        self.assertEqual("ELEVATED", core04[6]["risk"])
        self.assertEqual("INTERNAL_ONLY", core04[6]["release_class"])
        self.assertEqual("COMPLETED", core04[7]["status"])
        self.assertEqual(v.CORE04_08_CLOSEOUT_PR, core04[7]["github_pr"])
        self.assertEqual("ELEVATED", core04[7]["risk"])
        self.assertEqual("INTERNAL_ONLY", core04[7]["release_class"])
        self.assertEqual("COMPLETED", core04[8]["status"])
        self.assertEqual(v.CORE04_09_CODE_PR, core04[8]["github_pr"])
        self.assertEqual("ELEVATED", core04[8]["risk"])
        self.assertEqual("INTERNAL_ONLY", core04[8]["release_class"])
        self.assertEqual("COMPLETED", core04[9]["status"])
        self.assertEqual(v.CORE04_10_CLOSEOUT_PR, core04[9]["github_pr"])
        self.assertEqual("ELEVATED", core04[9]["risk"])
        self.assertEqual("INTERNAL_ONLY", core04[9]["release_class"])

    def test_completed_slice_08_cannot_claim_wrong_pr(self):
        def wrong(d):
            d["modules"][0]["packets"][7]["github_pr"] = 999
        self.assertTrue(any("expected COMPLETED/438" in x for x in self.check(wrong)))

    def test_completed_slice_07_cannot_claim_wrong_pr(self):
        def wrong(d):
            d["modules"][0]["packets"][6]["github_pr"] = 999
        self.assertTrue(any("expected COMPLETED/435" in x for x in self.check(wrong)))

    def test_predecessor_cannot_be_reopened(self):
        def wrong(d):
            d["modules"][0]["packets"][3]["status"] = "PLANNED_BLOCKED"
            d["modules"][0]["packets"][3]["github_pr"] = None
        self.assertTrue(any("expected COMPLETED/428" in x for x in self.check(wrong)))

    def test_completed_packet_cannot_claim_wrong_pr(self):
        def wrong(d):
            d["modules"][0]["packets"][4]["github_pr"] = 999
        self.assertTrue(any("expected COMPLETED/428" in x for x in self.check(wrong)))

    def test_ready_packet_requires_bounded_evidence(self):
        def wrong(d):
            d["modules"][0]["packets"][7]["activation_evidence"] = "docs/evidence/wrong.md"
        self.assertTrue(any("lacks bounded risk/ADR/evidence" in x for x in self.check(wrong)))

    def test_ready_packet_requires_correct_adr(self):
        def wrong(d):
            d["modules"][0]["packets"][7]["approved_adr"] = "docs/adr/0084-core-01-sdl3-runtime-slice.md"
        self.assertTrue(any("lacks bounded risk/ADR/evidence" in x for x in self.check(wrong)))

    def test_no_activation_record_denies_ready(self):
        self.assertTrue(v.validate_manifest(self.manifest, self.registry, None))
        self.assertFalse(v.packet_readiness(self.manifest, self.registry, None, "NLE-PRPLAN-CORE-01-08"))

    def test_forged_activation_denied(self):
        bad = copy.deepcopy(self.activation)
        bad["owner_authorization_ref"] = "forged"
        self.assertTrue(v.validate_manifest(self.manifest, self.registry, bad))
        bad = copy.deepcopy(self.activation)
        bad["risk"] = "HIGH"
        self.assertTrue(v.validate_manifest(self.manifest, self.registry, bad))
        bad = copy.deepcopy(self.activation)
        bad["source_blob_sha1"]["checkpoint"] = "bad"
        self.assertTrue(v.validate_manifest(self.manifest, self.registry, bad))

    def test_sdl3_pin_is_exact(self):
        self.assertEqual({
            "version": "3.4.20",
            "repository": "https://github.com/libsdl-org/SDL.git",
            "commit": "f00dc919ca35b9756316e86c4777392de442f9b2",
            "license": "zlib",
            "linkage": "static",
            "build_time_fetch": True,
        }, self.core08_activation["sdl3"])
        bad = copy.deepcopy(self.core08_activation)
        bad["sdl3"]["commit"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_window_slice_is_exact(self):
        window_slice = self.core08_activation["window_slice"]
        self.assertEqual(["x11", "wayland"], window_slice["linux_drivers_built"])
        self.assertEqual("x11", window_slice["linux_runtime_tested"])
        self.assertEqual("wayland", window_slice["linux_runtime_not_qualified"])
        self.assertEqual("win32", window_slice["windows_runtime"])
        self.assertEqual("cocoa_or_not_qualified", window_slice["macos_runtime"])
        self.assertEqual("xvfb+openbox", window_slice["linux_display"])
        self.assertEqual("disabled", window_slice["render_gpu_audio"])
        self.assertIn("libx11-dev", window_slice["linux_packages"])
        self.assertIn("openbox", window_slice["linux_packages"])
        bad = copy.deepcopy(self.core08_activation)
        bad["window_slice"]["linux_packages"].append("forbidden-package")
        self.assertTrue(v.validate_activation(bad))

    def test_any_second_packet_activation_denied(self):
        def wrong(d):
            d["modules"][0]["packets"][15]["status"] = "EXECUTOR_READY"
        self.assertTrue(self.check(wrong))

    def test_module_level_promotion_remains_forbidden(self):
        reg = copy.deepcopy(self.registry)
        reg["modules"][0]["executor_ready"] = True
        self.assertTrue(v.validate_manifest(self.manifest, reg, self.activation))

    def test_selector_cli_denies_all_after_core02_09_closeout(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        for packet_id in ("NLE-PRPLAN-CORE-03-01", "NLE-PRPLAN-CORE-03-02",
                          "NLE-PRPLAN-CORE-02-10", "NLE-PRPLAN-CORE-02-09",
                          "NLE-PRPLAN-CORE-02-08", "NLE-PRPLAN-CORE-02-07",
                          "NLE-PRPLAN-CORE-02-06", "NLE-PRPLAN-CORE-02-05",
                          "NLE-PRPLAN-CORE-01-16", "NLE-PRPLAN-CORE-01-17",
                          "NLE-PRPLAN-CORE-01-99"):
            blocked = subprocess.run([sys.executable, selector, packet_id, "--json"],
                                     capture_output=True, text=True, timeout=20, check=False)
            self.assertEqual(2, blocked.returncode, (packet_id, blocked.stdout, blocked.stderr))
            self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_core01_12_completed_slice_cannot_claim_wrong_pr(self):
        def wrong(d):
            d["modules"][0]["packets"][11]["github_pr"] = 999
        self.assertTrue(any("expected COMPLETED/453" in x for x in self.check(wrong)))

    def test_core01_11_completed_slice_cannot_claim_wrong_pr(self):
        def wrong(d):
            d["modules"][0]["packets"][10]["github_pr"] = 999
        self.assertTrue(any("expected COMPLETED/450" in x for x in self.check(wrong)))

    def test_core01_10_completed_slice_cannot_claim_wrong_pr(self):
        def wrong(d):
            d["modules"][0]["packets"][9]["github_pr"] = 999
        self.assertTrue(any("expected COMPLETED/447" in x for x in self.check(wrong)))

    def test_core01_09_completed_slice_cannot_claim_wrong_pr(self):
        def wrong(d):
            d["modules"][0]["packets"][8]["github_pr"] = 999
        self.assertTrue(any("expected COMPLETED/444" in x for x in self.check(wrong)))

    def test_core02_completed_slice_cannot_claim_wrong_pr(self):
        def wrong(d):
            d["modules"][1]["packets"][2]["github_pr"] = 999
        self.assertTrue(any("expected COMPLETED/441" in x for x in self.check(wrong)))

    def test_core02_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-CORE-02-03", self.core02_activation["selected_packet_id"])
        self.assertEqual("CORE-02", self.core02_activation["module_id"])
        self.assertEqual("STANDARD", self.core02_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.core02_activation["release_class"])
        self.assertEqual(v.CORE02_CAPABILITY_ADMISSION, self.core02_activation["capability_admission"])
        self.assertEqual(self.core02_activation["gate_pr"],
                         self.manifest["modules"][1]["packets"][0]["github_pr"])
        bad = copy.deepcopy(self.core02_activation)
        bad["capability_admission"]["required_capabilities"].append(
            {"id": "CORE01_WINDOW", "satisfied_by": "NLE-PRPLAN-CORE-01-08"})
        self.assertTrue(v.validate_activation(bad))

    def test_core02_capability_source_must_be_completed(self):
        def wrong(d):
            d["modules"][1]["packets"][2]["capability_admission"]["required_capabilities"][0]["satisfied_by"] = "NLE-PRPLAN-CORE-01-17"
        self.assertTrue(any("lacks a completed packet" in x for x in self.check(wrong)))

    def test_core02_cannot_claim_module_completion(self):
        def wrong(d):
            d["modules"][1]["packets"][2]["capability_admission"]["module_completion_claimed"] = True
        self.assertTrue(any("must not claim module completion" in x for x in self.check(wrong)))

    def test_core02_extra_capability_denied(self):
        def wrong(d):
            d["modules"][1]["packets"][2]["capability_admission"]["not_required"].append("window_runtime")
        self.assertTrue(any("capability admission" in x for x in self.check(wrong)))

    def test_core02_wrong_gate_pr_denied(self):
        def wrong(d):
            d["modules"][1]["packets"][0]["github_pr"] = 999
        self.assertTrue(any("expected APPROVED_GOVERNANCE/" in x for x in self.check(wrong)))

    def test_core02_cannot_unlock_10(self):
        def wrong(d):
            d["modules"][1]["packets"][9]["status"] = "EXECUTOR_READY"
        self.assertTrue(self.check(wrong))

    def test_core03_10_cannot_be_reopened(self):
        def wrong(d):
            d["modules"][2]["packets"][9]["status"] = "EXECUTOR_READY"
        self.assertTrue(self.check(wrong))

    def test_core02_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.core02_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_core02_module_registry_promotion_forbidden(self):
        reg = copy.deepcopy(self.registry)
        by_id = {m["module_id"]: m for m in reg["modules"]}
        by_id["CORE-02"]["executor_ready"] = True
        self.assertTrue(v.validate_manifest(self.manifest, reg, self.activation))

    def test_core01_09_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-CORE-01-09", self.core09_activation["selected_packet_id"])
        self.assertEqual("CORE-01", self.core09_activation["module_id"])
        self.assertEqual("STANDARD", self.core09_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.core09_activation["release_class"])
        self.assertEqual("3.4.20", self.core09_activation["sdl3"]["version"])
        self.assertEqual("f00dc919ca35b9756316e86c4777392de442f9b2",
                         self.core09_activation["sdl3"]["commit"])
        self.assertIsInstance(self.core09_activation["gate_pr"], int)
        bad = copy.deepcopy(self.core09_activation)
        bad["sdl3"]["commit"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_core01_09_cannot_unlock_16(self):
        def wrong(d):
            d["modules"][0]["packets"][15]["status"] = "EXECUTOR_READY"
        self.assertTrue(self.check(wrong))

    def test_core01_09_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.core09_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_core01_10_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-CORE-01-10", self.core10_activation["selected_packet_id"])
        self.assertEqual("CORE-01", self.core10_activation["module_id"])
        self.assertEqual("STANDARD", self.core10_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.core10_activation["release_class"])
        self.assertEqual("3.4.20", self.core10_activation["sdl3"]["version"])
        self.assertEqual("f00dc919ca35b9756316e86c4777392de442f9b2",
                         self.core10_activation["sdl3"]["commit"])
        self.assertIsInstance(self.core10_activation["gate_pr"], int)
        bad = copy.deepcopy(self.core10_activation)
        bad["sdl3"]["commit"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_core01_10_cannot_unlock_16(self):
        def wrong(d):
            d["modules"][0]["packets"][15]["status"] = "EXECUTOR_READY"
        self.assertTrue(self.check(wrong))

    def test_core01_10_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.core10_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_core01_11_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-CORE-01-11", self.core11_activation["selected_packet_id"])
        self.assertEqual("CORE-01", self.core11_activation["module_id"])
        self.assertEqual("STANDARD", self.core11_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.core11_activation["release_class"])
        self.assertEqual("3.4.20", self.core11_activation["sdl3"]["version"])
        self.assertEqual("f00dc919ca35b9756316e86c4777392de442f9b2",
                         self.core11_activation["sdl3"]["commit"])
        self.assertIsInstance(self.core11_activation["gate_pr"], int)
        bad = copy.deepcopy(self.core11_activation)
        bad["sdl3"]["commit"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_core01_11_cannot_unlock_16(self):
        def wrong(d):
            d["modules"][0]["packets"][15]["status"] = "EXECUTOR_READY"
        self.assertTrue(self.check(wrong))

    def test_core01_11_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.core11_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_core01_12_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-CORE-01-12", self.core12_activation["selected_packet_id"])
        self.assertEqual("CORE-01", self.core12_activation["module_id"])
        self.assertEqual("STANDARD", self.core12_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.core12_activation["release_class"])
        self.assertIsInstance(self.core12_activation["gate_pr"], int)
        bad = copy.deepcopy(self.core12_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_core01_12_cannot_unlock_16(self):
        def wrong(d):
            d["modules"][0]["packets"][15]["status"] = "EXECUTOR_READY"
        self.assertTrue(self.check(wrong))

    def test_core01_12_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.core12_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_core01_13_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-CORE-01-13", self.core13_activation["selected_packet_id"])
        self.assertEqual("CORE-01", self.core13_activation["module_id"])
        self.assertEqual("STANDARD", self.core13_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.core13_activation["release_class"])
        self.assertEqual("3.4.20", self.core13_activation["sdl3"]["version"])
        self.assertIsInstance(self.core13_activation["gate_pr"], int)
        bad = copy.deepcopy(self.core13_activation)
        bad["sdl3"]["commit"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_core01_13_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.core13_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_core01_14_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-CORE-01-14", self.core14_activation["selected_packet_id"])
        self.assertEqual("CORE-01", self.core14_activation["module_id"])
        self.assertEqual("STANDARD", self.core14_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.core14_activation["release_class"])
        self.assertIsInstance(self.core14_activation["gate_pr"], int)
        bad = copy.deepcopy(self.core14_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_core01_14_cannot_unlock_16(self):
        def wrong(d):
            d["modules"][0]["packets"][15]["status"] = "EXECUTOR_READY"
        self.assertTrue(self.check(wrong))

    def test_core01_14_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.core14_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_core01_15_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-CORE-01-15", self.core15_activation["selected_packet_id"])
        self.assertEqual("CORE-01", self.core15_activation["module_id"])
        self.assertEqual("STANDARD", self.core15_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.core15_activation["release_class"])
        self.assertIsInstance(self.core15_activation["gate_pr"], int)
        bad = copy.deepcopy(self.core15_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_core01_15_cannot_unlock_16(self):
        def wrong(d):
            d["modules"][0]["packets"][15]["status"] = "EXECUTOR_READY"
        self.assertTrue(self.check(wrong))

    def test_core01_15_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.core15_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_core01_16_closeout_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-CORE-01-16", self.core16_activation["selected_packet_id"])
        self.assertEqual("CORE-01", self.core16_activation["module_id"])
        self.assertEqual("STANDARD", self.core16_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.core16_activation["release_class"])
        self.assertIsInstance(self.core16_activation["gate_pr"], int)
        bad = copy.deepcopy(self.core16_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_core01_16_closeout_source_drift_denied(self):
        bad = copy.deepcopy(self.core16_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_core02_04_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-CORE-02-04", self.core02_04_activation["selected_packet_id"])
        self.assertEqual("CORE-02", self.core02_04_activation["module_id"])
        self.assertEqual("STANDARD", self.core02_04_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.core02_04_activation["release_class"])
        self.assertEqual(v.CORE02_CAPABILITY_ADMISSION, self.core02_04_activation["capability_admission"])
        self.assertIsInstance(self.core02_04_activation["gate_pr"], int)
        bad = copy.deepcopy(self.core02_04_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_core02_04_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.core02_04_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_core02_05_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-CORE-02-05", self.core02_05_activation["selected_packet_id"])
        self.assertEqual("CORE-02", self.core02_05_activation["module_id"])
        self.assertEqual("STANDARD", self.core02_05_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.core02_05_activation["release_class"])
        self.assertEqual(v.CORE02_CAPABILITY_ADMISSION, self.core02_05_activation["capability_admission"])
        self.assertIsInstance(self.core02_05_activation["gate_pr"], int)
        bad = copy.deepcopy(self.core02_05_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_core02_05_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.core02_05_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_core02_06_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-CORE-02-06", self.core02_06_activation["selected_packet_id"])
        self.assertEqual("CORE-02", self.core02_06_activation["module_id"])
        self.assertEqual("STANDARD", self.core02_06_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.core02_06_activation["release_class"])
        self.assertEqual(v.CORE02_CAPABILITY_ADMISSION, self.core02_06_activation["capability_admission"])
        self.assertIsInstance(self.core02_06_activation["gate_pr"], int)
        bad = copy.deepcopy(self.core02_06_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_core02_06_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.core02_06_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_core02_07_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-CORE-02-07", self.core02_07_activation["selected_packet_id"])
        self.assertEqual("CORE-02", self.core02_07_activation["module_id"])
        self.assertEqual("STANDARD", self.core02_07_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.core02_07_activation["release_class"])
        self.assertEqual(v.CORE02_CAPABILITY_ADMISSION, self.core02_07_activation["capability_admission"])
        self.assertIsInstance(self.core02_07_activation["gate_pr"], int)
        bad = copy.deepcopy(self.core02_07_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_core02_07_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.core02_07_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_core02_08_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-CORE-02-08", self.core02_08_activation["selected_packet_id"])
        self.assertEqual("CORE-02", self.core02_08_activation["module_id"])
        self.assertEqual("STANDARD", self.core02_08_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.core02_08_activation["release_class"])
        self.assertEqual(v.CORE02_CAPABILITY_ADMISSION, self.core02_08_activation["capability_admission"])
        self.assertIsInstance(self.core02_08_activation["gate_pr"], int)
        bad = copy.deepcopy(self.core02_08_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_core02_08_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.core02_08_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_core02_09_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-CORE-02-09", self.core02_09_activation["selected_packet_id"])
        self.assertEqual("CORE-02", self.core02_09_activation["module_id"])
        self.assertEqual("STANDARD", self.core02_09_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.core02_09_activation["release_class"])
        self.assertEqual(v.CORE02_CAPABILITY_ADMISSION, self.core02_09_activation["capability_admission"])
        self.assertIsInstance(self.core02_09_activation["gate_pr"], int)
        bad = copy.deepcopy(self.core02_09_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_core02_09_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.core02_09_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_core02_10_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-CORE-02-10", self.core02_10_activation["selected_packet_id"])
        self.assertEqual("CORE-02", self.core02_10_activation["module_id"])
        self.assertEqual("STANDARD", self.core02_10_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.core02_10_activation["release_class"])
        self.assertIsInstance(self.core02_10_activation["gate_pr"], int)
        bad = copy.deepcopy(self.core02_10_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_core02_10_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.core02_10_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_core03_01_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-CORE-03-01", self.core03_01_activation["selected_packet_id"])
        self.assertEqual("CORE-03", self.core03_01_activation["module_id"])
        self.assertEqual("LOW", self.core03_01_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.core03_01_activation["release_class"])
        self.assertIsInstance(self.core03_01_activation["gate_pr"], int)
        bad = copy.deepcopy(self.core03_01_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_core03_01_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.core03_01_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_core03_02_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-CORE-03-02", self.core03_02_activation["selected_packet_id"])
        self.assertEqual("CORE-03", self.core03_02_activation["module_id"])
        self.assertEqual("LOW", self.core03_02_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.core03_02_activation["release_class"])
        self.assertIsInstance(self.core03_02_activation["gate_pr"], int)
        bad = copy.deepcopy(self.core03_02_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_core03_02_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.core03_02_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_core03_04_completed_slice_cannot_claim_wrong_pr(self):
        def wrong(d):
            d["modules"][2]["packets"][3]["github_pr"] = 999
        self.assertTrue(any("expected COMPLETED/" in x for x in self.check(wrong)))

    def test_core03_05_completed_slice_cannot_claim_wrong_pr(self):
        def wrong(d):
            d["modules"][2]["packets"][4]["github_pr"] = 999
        self.assertTrue(any("expected COMPLETED/" in x for x in self.check(wrong)))

    def test_core03_06_completed_slice_cannot_claim_wrong_pr(self):
        def wrong(d):
            d["modules"][2]["packets"][5]["github_pr"] = 999
        self.assertTrue(any("expected COMPLETED/" in x for x in self.check(wrong)))

    def test_core03_07_completed_slice_cannot_claim_wrong_pr(self):
        def wrong(d):
            d["modules"][2]["packets"][6]["github_pr"] = 999
        self.assertTrue(any("expected COMPLETED/" in x for x in self.check(wrong)))

    def test_core03_08_completed_slice_cannot_claim_wrong_pr(self):
        def wrong(d):
            d["modules"][2]["packets"][7]["github_pr"] = 999
        self.assertTrue(any("expected COMPLETED/" in x for x in self.check(wrong)))

    def test_core03_03_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-CORE-03-03", self.core03_03_activation["selected_packet_id"])
        self.assertEqual("CORE-03", self.core03_03_activation["module_id"])
        self.assertEqual("ELEVATED", self.core03_03_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.core03_03_activation["release_class"])
        self.assertEqual(v.CORE03_CAPABILITY_ADMISSION,
                         self.core03_03_activation["capability_admission"])
        self.assertIsInstance(self.core03_03_activation["gate_pr"], int)
        bad = copy.deepcopy(self.core03_03_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_core03_03_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.core03_03_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_core03_03_capability_source_must_be_completed(self):
        def wrong(d):
            d["modules"][2]["packets"][2]["capability_admission"]["required_capabilities"][0]["satisfied_by"] = "NLE-PRPLAN-CORE-02-99"
        self.assertTrue(any("lacks a completed packet" in x for x in self.check(wrong)))

    def test_core03_03_cannot_claim_module_completion(self):
        def wrong(d):
            d["modules"][2]["packets"][2]["capability_admission"]["module_completion_claimed"] = True
        self.assertTrue(any("must not claim module completion" in x for x in self.check(wrong)))

    def test_core03_03_extra_capability_denied(self):
        def wrong(d):
            d["modules"][2]["packets"][2]["capability_admission"]["not_required"].append("window_runtime")
        self.assertTrue(any("capability admission" in x for x in self.check(wrong)))

    def test_selector_denies_all_after_core03_09_completion(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        for packet_id in ("NLE-PRPLAN-CORE-03-09", "NLE-PRPLAN-CORE-03-08",
                          "NLE-PRPLAN-CORE-03-10", "NLE-PRPLAN-CORE-02-10"):
            blocked = subprocess.run([sys.executable, selector, packet_id, "--json"],
                                     capture_output=True, text=True, timeout=20, check=False)
            self.assertEqual(2, blocked.returncode, (packet_id, blocked.stdout, blocked.stderr))
            self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_core03_09_completed_slice_cannot_claim_wrong_pr(self):
        def wrong(d):
            d["modules"][2]["packets"][8]["github_pr"] = 999
        self.assertTrue(any("expected COMPLETED/" in x for x in self.check(wrong)))

    def test_core03_10_completed_slice_cannot_claim_wrong_pr(self):
        def wrong(d):
            d["modules"][2]["packets"][9]["github_pr"] = 999
        self.assertTrue(any("expected COMPLETED/" in x for x in self.check(wrong)))

    def test_core04_governance_selector_denies_all(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        for packet_id in ("NLE-PRPLAN-CORE-04-01", "NLE-PRPLAN-CORE-04-02",
                          "NLE-PRPLAN-CORE-04-05", "NLE-PRPLAN-CORE-04-10"):
            blocked = subprocess.run([sys.executable, selector, packet_id, "--json"],
                                     capture_output=True, text=True, timeout=20, check=False)
            self.assertEqual(2, blocked.returncode, (packet_id, blocked.stdout, blocked.stderr))
            self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_core04_01_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-CORE-04-01",
                         self.core04_01_activation["selected_packet_id"])
        self.assertEqual("CORE-04", self.core04_01_activation["module_id"])
        self.assertEqual("LOW", self.core04_01_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.core04_01_activation["release_class"])
        self.assertEqual(v.CORE04_CAPABILITY_ADMISSION,
                         self.core04_01_activation["capability_admission"])
        self.assertIsInstance(self.core04_01_activation["gate_pr"], int)
        bad = copy.deepcopy(self.core04_01_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_core04_01_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.core04_01_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_selector_denies_all_after_core04_03_completion(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        for packet_id in ("NLE-PRPLAN-CORE-04-03", "NLE-PRPLAN-CORE-04-02",
                          "NLE-PRPLAN-CORE-04-05", "NLE-PRPLAN-CORE-04-10",
                          "NLE-PRPLAN-CORE-03-03"):
            blocked = subprocess.run([sys.executable, selector, packet_id, "--json"],
                                     capture_output=True, text=True, timeout=20, check=False)
            self.assertEqual(2, blocked.returncode, (packet_id, blocked.stdout, blocked.stderr))
            self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_selector_denies_all_after_core04_04_completion(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        for packet_id in ("NLE-PRPLAN-CORE-04-04", "NLE-PRPLAN-CORE-04-03",
                          "NLE-PRPLAN-CORE-04-05", "NLE-PRPLAN-CORE-04-10",
                          "NLE-PRPLAN-CORE-03-03"):
            blocked = subprocess.run([sys.executable, selector, packet_id, "--json"],
                                     capture_output=True, text=True, timeout=20, check=False)
            self.assertEqual(2, blocked.returncode, (packet_id, blocked.stdout, blocked.stderr))
            self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_selector_denies_all_after_core04_09_completion(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        for packet_id in ("NLE-PRPLAN-CORE-04-09", "NLE-PRPLAN-CORE-04-08",
                          "NLE-PRPLAN-CORE-04-10", "NLE-PRPLAN-CORE-03-03"):
            blocked = subprocess.run([sys.executable, selector, packet_id, "--json"],
                                     capture_output=True, text=True, timeout=20, check=False)
            self.assertEqual(2, blocked.returncode, (packet_id, blocked.stdout, blocked.stderr))
            self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_core05_governance_selector_denies_all(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        for packet_id in ("NLE-PRPLAN-CORE-05-01", "NLE-PRPLAN-CORE-05-02",
                          "NLE-PRPLAN-CORE-05-03", "NLE-PRPLAN-CORE-05-04",
                          "NLE-PRPLAN-CORE-05-05", "NLE-PRPLAN-CORE-05-06",
                          "NLE-PRPLAN-CORE-05-07", "NLE-PRPLAN-CORE-05-08",
                          "NLE-PRPLAN-CORE-05-09", "NLE-PRPLAN-CORE-05-10"):
            blocked = subprocess.run([sys.executable, selector, packet_id, "--json"],
                                     capture_output=True, text=True, timeout=20, check=False)
            self.assertEqual(2, blocked.returncode, (packet_id, blocked.stdout, blocked.stderr))
            self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_core05_03_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-CORE-05-03", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_core05_04_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-CORE-05-04", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_core05_05_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-CORE-05-05", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_core05_06_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-CORE-05-06", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_core05_07_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-CORE-05-07", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_core05_08_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-CORE-05-08", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_core05_09_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-CORE-05-09", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_core05_01_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-CORE-05-01",
                         self.core05_01_activation["selected_packet_id"])
        self.assertEqual("CORE-05", self.core05_01_activation["module_id"])
        self.assertEqual("LOW", self.core05_01_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.core05_01_activation["release_class"])
        self.assertEqual(v.CORE04_CAPABILITY_ADMISSION,
                         self.core05_01_activation["capability_admission"])
        self.assertIsInstance(self.core05_01_activation["gate_pr"], int)
        bad = copy.deepcopy(self.core05_01_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_core05_01_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.core05_01_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_core05_02_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-CORE-05-02",
                         self.core05_02_activation["selected_packet_id"])
        self.assertEqual("CORE-05", self.core05_02_activation["module_id"])
        self.assertEqual("LOW", self.core05_02_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.core05_02_activation["release_class"])
        self.assertEqual("docs/contracts/core-05-math-v0.md",
                         self.core05_02_activation["approved_contract"])
        self.assertEqual(v.CORE04_CAPABILITY_ADMISSION,
                         self.core05_02_activation["capability_admission"])
        self.assertIsInstance(self.core05_02_activation["gate_pr"], int)
        bad = copy.deepcopy(self.core05_02_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_core05_02_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.core05_02_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_core05_03_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-CORE-05-03",
                         self.core05_03_activation["selected_packet_id"])
        self.assertEqual("CORE-05", self.core05_03_activation["module_id"])
        self.assertEqual("ELEVATED", self.core05_03_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.core05_03_activation["release_class"])
        self.assertEqual("docs/contracts/core-05-math-v0.md",
                         self.core05_03_activation["approved_contract"])
        self.assertEqual(v.CORE04_CAPABILITY_ADMISSION,
                         self.core05_03_activation["capability_admission"])
        self.assertIsInstance(self.core05_03_activation["gate_pr"], int)
        bad = copy.deepcopy(self.core05_03_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_core05_03_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.core05_03_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_core05_04_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-CORE-05-04",
                         self.core05_04_activation["selected_packet_id"])
        self.assertEqual("CORE-05", self.core05_04_activation["module_id"])
        self.assertEqual("ELEVATED", self.core05_04_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.core05_04_activation["release_class"])
        self.assertEqual("docs/contracts/core-05-math-v0.md",
                         self.core05_04_activation["approved_contract"])
        self.assertEqual(v.CORE04_CAPABILITY_ADMISSION,
                         self.core05_04_activation["capability_admission"])
        self.assertIsInstance(self.core05_04_activation["gate_pr"], int)
        bad = copy.deepcopy(self.core05_04_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_core05_04_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.core05_04_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_core05_05_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-CORE-05-05",
                         self.core05_05_activation["selected_packet_id"])
        self.assertEqual("CORE-05", self.core05_05_activation["module_id"])
        self.assertEqual("ELEVATED", self.core05_05_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.core05_05_activation["release_class"])
        self.assertEqual("docs/contracts/core-05-math-v0.md",
                         self.core05_05_activation["approved_contract"])
        self.assertEqual(v.CORE04_CAPABILITY_ADMISSION,
                         self.core05_05_activation["capability_admission"])
        self.assertIsInstance(self.core05_05_activation["gate_pr"], int)
        bad = copy.deepcopy(self.core05_05_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_core05_05_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.core05_05_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_core05_06_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-CORE-05-06",
                         self.core05_06_activation["selected_packet_id"])
        self.assertEqual("CORE-05", self.core05_06_activation["module_id"])
        self.assertEqual("ELEVATED", self.core05_06_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.core05_06_activation["release_class"])
        self.assertEqual("docs/contracts/core-05-math-v0.md",
                         self.core05_06_activation["approved_contract"])
        self.assertEqual(v.CORE04_CAPABILITY_ADMISSION,
                         self.core05_06_activation["capability_admission"])
        self.assertIsInstance(self.core05_06_activation["gate_pr"], int)
        bad = copy.deepcopy(self.core05_06_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_core05_06_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.core05_06_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_core05_07_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-CORE-05-07",
                         self.core05_07_activation["selected_packet_id"])
        self.assertEqual("CORE-05", self.core05_07_activation["module_id"])
        self.assertEqual("ELEVATED", self.core05_07_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.core05_07_activation["release_class"])
        self.assertEqual("docs/contracts/core-05-math-v0.md",
                         self.core05_07_activation["approved_contract"])
        self.assertEqual(v.CORE04_CAPABILITY_ADMISSION,
                         self.core05_07_activation["capability_admission"])
        self.assertIsInstance(self.core05_07_activation["gate_pr"], int)
        bad = copy.deepcopy(self.core05_07_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_core05_07_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.core05_07_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_core05_08_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-CORE-05-08",
                         self.core05_08_activation["selected_packet_id"])
        self.assertEqual("CORE-05", self.core05_08_activation["module_id"])
        self.assertEqual("ELEVATED", self.core05_08_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.core05_08_activation["release_class"])
        self.assertEqual("docs/contracts/core-05-math-v0.md",
                         self.core05_08_activation["approved_contract"])
        self.assertEqual(v.CORE04_CAPABILITY_ADMISSION,
                         self.core05_08_activation["capability_admission"])
        self.assertIsInstance(self.core05_08_activation["gate_pr"], int)
        bad = copy.deepcopy(self.core05_08_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_core05_08_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.core05_08_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_core05_09_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-CORE-05-09",
                         self.core05_09_activation["selected_packet_id"])
        self.assertEqual("CORE-05", self.core05_09_activation["module_id"])
        self.assertEqual("ELEVATED", self.core05_09_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.core05_09_activation["release_class"])
        self.assertEqual("docs/contracts/core-05-math-v0.md",
                         self.core05_09_activation["approved_contract"])
        self.assertEqual(v.CORE04_CAPABILITY_ADMISSION,
                         self.core05_09_activation["capability_admission"])
        self.assertIsInstance(self.core05_09_activation["gate_pr"], int)
        bad = copy.deepcopy(self.core05_09_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_core05_09_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.core05_09_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_core06_01_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-CORE-06-01",
                         self.core06_01_activation["selected_packet_id"])
        self.assertEqual("CORE-06", self.core06_01_activation["module_id"])
        self.assertEqual("LOW", self.core06_01_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.core06_01_activation["release_class"])
        self.assertEqual("docs/contracts/core-06-governance-v0.md",
                         self.core06_01_activation["approved_contract"])
        self.assertEqual(v.CORE04_CAPABILITY_ADMISSION,
                         self.core06_01_activation["capability_admission"])
        self.assertIsInstance(self.core06_01_activation["gate_pr"], int)
        bad = copy.deepcopy(self.core06_01_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_core06_01_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.core06_01_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_core06_02_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-CORE-06-02",
                         self.core06_02_activation["selected_packet_id"])
        self.assertEqual("CORE-06", self.core06_02_activation["module_id"])
        self.assertEqual("LOW", self.core06_02_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.core06_02_activation["release_class"])
        self.assertEqual("docs/contracts/core-06-diagnostics-v0.md",
                         self.core06_02_activation["approved_contract"])
        self.assertEqual(v.CORE04_CAPABILITY_ADMISSION,
                         self.core06_02_activation["capability_admission"])
        self.assertIsInstance(self.core06_02_activation["gate_pr"], int)
        bad = copy.deepcopy(self.core06_02_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_core06_02_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.core06_02_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_core06_03_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-CORE-06-03",
                         self.core06_03_activation["selected_packet_id"])
        self.assertEqual("CORE-06", self.core06_03_activation["module_id"])
        self.assertEqual("ELEVATED", self.core06_03_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.core06_03_activation["release_class"])
        self.assertEqual("docs/contracts/core-06-diagnostics-v0.md",
                         self.core06_03_activation["approved_contract"])
        self.assertEqual(v.CORE04_CAPABILITY_ADMISSION,
                         self.core06_03_activation["capability_admission"])
        self.assertIsInstance(self.core06_03_activation["gate_pr"], int)
        bad = copy.deepcopy(self.core06_03_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_core06_03_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.core06_03_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_core06_04_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-CORE-06-04",
                         self.core06_04_activation["selected_packet_id"])
        self.assertEqual("CORE-06", self.core06_04_activation["module_id"])
        self.assertEqual("ELEVATED", self.core06_04_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.core06_04_activation["release_class"])
        self.assertEqual("docs/contracts/core-06-diagnostics-v0.md",
                         self.core06_04_activation["approved_contract"])
        self.assertEqual(v.CORE04_CAPABILITY_ADMISSION,
                         self.core06_04_activation["capability_admission"])
        self.assertIsInstance(self.core06_04_activation["gate_pr"], int)
        bad = copy.deepcopy(self.core06_04_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_core06_04_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.core06_04_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_core06_05_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-CORE-06-05",
                         self.core06_05_activation["selected_packet_id"])
        self.assertEqual("CORE-06", self.core06_05_activation["module_id"])
        self.assertEqual("ELEVATED", self.core06_05_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.core06_05_activation["release_class"])
        self.assertEqual("docs/contracts/core-06-diagnostics-v0.md",
                         self.core06_05_activation["approved_contract"])
        self.assertEqual(v.CORE04_CAPABILITY_ADMISSION,
                         self.core06_05_activation["capability_admission"])
        self.assertIsInstance(self.core06_05_activation["gate_pr"], int)
        bad = copy.deepcopy(self.core06_05_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_core06_05_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.core06_05_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_core06_06_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-CORE-06-06",
                         self.core06_06_activation["selected_packet_id"])
        self.assertEqual("CORE-06", self.core06_06_activation["module_id"])
        self.assertEqual("ELEVATED", self.core06_06_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.core06_06_activation["release_class"])
        self.assertEqual("docs/contracts/core-06-diagnostics-v0.md",
                         self.core06_06_activation["approved_contract"])
        self.assertEqual(v.CORE04_CAPABILITY_ADMISSION,
                         self.core06_06_activation["capability_admission"])
        self.assertIsInstance(self.core06_06_activation["gate_pr"], int)
        bad = copy.deepcopy(self.core06_06_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_core06_06_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.core06_06_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_core06_07_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-CORE-06-07",
                         self.core06_07_activation["selected_packet_id"])
        self.assertEqual("CORE-06", self.core06_07_activation["module_id"])
        self.assertEqual("ELEVATED", self.core06_07_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.core06_07_activation["release_class"])
        self.assertEqual("docs/contracts/core-06-diagnostics-v0.md",
                         self.core06_07_activation["approved_contract"])
        self.assertEqual(v.CORE04_CAPABILITY_ADMISSION,
                         self.core06_07_activation["capability_admission"])
        self.assertIsInstance(self.core06_07_activation["gate_pr"], int)
        bad = copy.deepcopy(self.core06_07_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_core06_07_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.core06_07_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_core06_08_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-CORE-06-08",
                         self.core06_08_activation["selected_packet_id"])
        self.assertEqual("CORE-06", self.core06_08_activation["module_id"])
        self.assertEqual("ELEVATED", self.core06_08_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.core06_08_activation["release_class"])
        self.assertEqual("docs/contracts/core-06-diagnostics-v0.md",
                         self.core06_08_activation["approved_contract"])
        self.assertEqual(v.CORE04_CAPABILITY_ADMISSION,
                         self.core06_08_activation["capability_admission"])
        self.assertIsInstance(self.core06_08_activation["gate_pr"], int)
        bad = copy.deepcopy(self.core06_08_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_core06_08_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.core06_08_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_core06_09_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-CORE-06-09",
                         self.core06_09_activation["selected_packet_id"])
        self.assertEqual("CORE-06", self.core06_09_activation["module_id"])
        self.assertEqual("ELEVATED", self.core06_09_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.core06_09_activation["release_class"])
        self.assertEqual("docs/contracts/core-06-diagnostics-v0.md",
                         self.core06_09_activation["approved_contract"])
        self.assertEqual(v.CORE04_CAPABILITY_ADMISSION,
                         self.core06_09_activation["capability_admission"])
        self.assertIsInstance(self.core06_09_activation["gate_pr"], int)
        bad = copy.deepcopy(self.core06_09_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_core06_09_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.core06_09_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_data01_01_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-DATA-01-01",
                         self.data01_01_activation["selected_packet_id"])
        self.assertEqual("DATA-01", self.data01_01_activation["module_id"])
        self.assertEqual("LOW", self.data01_01_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.data01_01_activation["release_class"])
        self.assertEqual("docs/contracts/data-01-governance-v0.md",
                         self.data01_01_activation["approved_contract"])
        self.assertEqual(v.CORE04_CAPABILITY_ADMISSION,
                         self.data01_01_activation["capability_admission"])
        self.assertIsInstance(self.data01_01_activation["gate_pr"], int)
        bad = copy.deepcopy(self.data01_01_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_data01_01_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.data01_01_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_data01_02_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-DATA-01-02",
                         self.data01_02_activation["selected_packet_id"])
        self.assertEqual("DATA-01", self.data01_02_activation["module_id"])
        self.assertEqual("LOW", self.data01_02_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.data01_02_activation["release_class"])
        self.assertEqual("docs/contracts/data-01-vfs-v0.md",
                         self.data01_02_activation["approved_contract"])
        self.assertEqual(v.CORE04_CAPABILITY_ADMISSION,
                         self.data01_02_activation["capability_admission"])
        self.assertIsInstance(self.data01_02_activation["gate_pr"], int)
        bad = copy.deepcopy(self.data01_02_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_data01_02_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.data01_02_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_data01_03_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-DATA-01-03",
                         self.data01_03_activation["selected_packet_id"])
        self.assertEqual("DATA-01", self.data01_03_activation["module_id"])
        self.assertEqual("ELEVATED", self.data01_03_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.data01_03_activation["release_class"])
        self.assertEqual("docs/contracts/data-01-vfs-v0.md",
                         self.data01_03_activation["approved_contract"])
        self.assertEqual(v.CORE04_CAPABILITY_ADMISSION,
                         self.data01_03_activation["capability_admission"])
        self.assertIsInstance(self.data01_03_activation["gate_pr"], int)
        bad = copy.deepcopy(self.data01_03_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_data01_03_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.data01_03_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_data01_04_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-DATA-01-04",
                         self.data01_04_activation["selected_packet_id"])
        self.assertEqual("DATA-01", self.data01_04_activation["module_id"])
        self.assertEqual("ELEVATED", self.data01_04_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.data01_04_activation["release_class"])
        self.assertEqual("docs/contracts/data-01-vfs-v0.md",
                         self.data01_04_activation["approved_contract"])
        self.assertEqual(v.CORE04_CAPABILITY_ADMISSION,
                         self.data01_04_activation["capability_admission"])
        self.assertIsInstance(self.data01_04_activation["gate_pr"], int)
        bad = copy.deepcopy(self.data01_04_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_data01_04_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.data01_04_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_data01_05_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-DATA-01-05",
                         self.data01_05_activation["selected_packet_id"])
        self.assertEqual("DATA-01", self.data01_05_activation["module_id"])
        self.assertEqual("ELEVATED", self.data01_05_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.data01_05_activation["release_class"])
        self.assertEqual("docs/contracts/data-01-vfs-v0.md",
                         self.data01_05_activation["approved_contract"])
        self.assertEqual(v.CORE04_CAPABILITY_ADMISSION,
                         self.data01_05_activation["capability_admission"])
        self.assertIsInstance(self.data01_05_activation["gate_pr"], int)
        bad = copy.deepcopy(self.data01_05_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_data01_05_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.data01_05_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_data01_06_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-DATA-01-06",
                         self.data01_06_activation["selected_packet_id"])
        self.assertEqual("DATA-01", self.data01_06_activation["module_id"])
        self.assertEqual("ELEVATED", self.data01_06_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.data01_06_activation["release_class"])
        self.assertEqual("docs/contracts/data-01-vfs-v0.md",
                         self.data01_06_activation["approved_contract"])
        self.assertEqual(v.CORE04_CAPABILITY_ADMISSION,
                         self.data01_06_activation["capability_admission"])
        self.assertIsInstance(self.data01_06_activation["gate_pr"], int)
        bad = copy.deepcopy(self.data01_06_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_data01_06_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.data01_06_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_data01_07_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-DATA-01-07",
                         self.data01_07_activation["selected_packet_id"])
        self.assertEqual("DATA-01", self.data01_07_activation["module_id"])
        self.assertEqual("ELEVATED", self.data01_07_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.data01_07_activation["release_class"])
        self.assertEqual("docs/contracts/data-01-vfs-v0.md",
                         self.data01_07_activation["approved_contract"])
        self.assertEqual(v.CORE04_CAPABILITY_ADMISSION,
                         self.data01_07_activation["capability_admission"])
        self.assertIsInstance(self.data01_07_activation["gate_pr"], int)
        bad = copy.deepcopy(self.data01_07_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_data01_07_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.data01_07_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_data01_08_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-DATA-01-08",
                         self.data01_08_activation["selected_packet_id"])
        self.assertEqual("DATA-01", self.data01_08_activation["module_id"])
        self.assertEqual("ELEVATED", self.data01_08_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.data01_08_activation["release_class"])
        self.assertEqual("docs/contracts/data-01-vfs-v0.md",
                         self.data01_08_activation["approved_contract"])
        self.assertEqual(v.CORE04_CAPABILITY_ADMISSION,
                         self.data01_08_activation["capability_admission"])
        self.assertIsInstance(self.data01_08_activation["gate_pr"], int)
        bad = copy.deepcopy(self.data01_08_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_data01_08_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.data01_08_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_data01_09_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-DATA-01-09",
                         self.data01_09_activation["selected_packet_id"])
        self.assertEqual("DATA-01", self.data01_09_activation["module_id"])
        self.assertEqual("ELEVATED", self.data01_09_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.data01_09_activation["release_class"])
        self.assertEqual("docs/contracts/data-01-vfs-v0.md",
                         self.data01_09_activation["approved_contract"])
        self.assertEqual(v.CORE04_CAPABILITY_ADMISSION,
                         self.data01_09_activation["capability_admission"])
        self.assertIsInstance(self.data01_09_activation["gate_pr"], int)
        bad = copy.deepcopy(self.data01_09_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_data01_09_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.data01_09_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_data02_01_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-DATA-02-01",
                         self.data02_01_activation["selected_packet_id"])
        self.assertEqual("DATA-02", self.data02_01_activation["module_id"])
        self.assertEqual("LOW", self.data02_01_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.data02_01_activation["release_class"])
        self.assertEqual("docs/contracts/data-02-governance-v0.md",
                         self.data02_01_activation["approved_contract"])
        self.assertEqual(v.CORE04_CAPABILITY_ADMISSION,
                         self.data02_01_activation["capability_admission"])
        self.assertIsInstance(self.data02_01_activation["gate_pr"], int)
        bad = copy.deepcopy(self.data02_01_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_data02_01_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.data02_01_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_data02_02_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-DATA-02-02",
                         self.data02_02_activation["selected_packet_id"])
        self.assertEqual("DATA-02", self.data02_02_activation["module_id"])
        self.assertEqual("LOW", self.data02_02_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.data02_02_activation["release_class"])
        self.assertEqual("docs/contracts/data-02-registry-v0.md",
                         self.data02_02_activation["approved_contract"])
        self.assertEqual(v.CORE04_CAPABILITY_ADMISSION,
                         self.data02_02_activation["capability_admission"])
        self.assertIsInstance(self.data02_02_activation["gate_pr"], int)
        bad = copy.deepcopy(self.data02_02_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_data02_02_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.data02_02_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_data02_03_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-DATA-02-03",
                         self.data02_03_activation["selected_packet_id"])
        self.assertEqual("DATA-02", self.data02_03_activation["module_id"])
        self.assertEqual("ELEVATED", self.data02_03_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.data02_03_activation["release_class"])
        self.assertEqual("docs/contracts/data-02-registry-v0.md",
                         self.data02_03_activation["approved_contract"])
        self.assertEqual(v.DATA02_CAPABILITY_ADMISSION,
                         self.data02_03_activation["capability_admission"])
        self.assertIsInstance(self.data02_03_activation["gate_pr"], int)
        bad = copy.deepcopy(self.data02_03_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_data02_03_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.data02_03_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_data02_04_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-DATA-02-04",
                         self.data02_04_activation["selected_packet_id"])
        self.assertEqual("DATA-02", self.data02_04_activation["module_id"])
        self.assertEqual("ELEVATED", self.data02_04_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.data02_04_activation["release_class"])
        self.assertEqual("docs/contracts/data-02-registry-v0.md",
                         self.data02_04_activation["approved_contract"])
        self.assertEqual(v.DATA02_CAPABILITY_ADMISSION,
                         self.data02_04_activation["capability_admission"])
        self.assertIsInstance(self.data02_04_activation["gate_pr"], int)
        bad = copy.deepcopy(self.data02_04_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_data02_04_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.data02_04_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_data02_05_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-DATA-02-05",
                         self.data02_05_activation["selected_packet_id"])
        self.assertEqual("DATA-02", self.data02_05_activation["module_id"])
        self.assertEqual("ELEVATED", self.data02_05_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.data02_05_activation["release_class"])
        self.assertEqual("docs/contracts/data-02-registry-v0.md",
                         self.data02_05_activation["approved_contract"])
        self.assertEqual(v.DATA02_CAPABILITY_ADMISSION,
                         self.data02_05_activation["capability_admission"])
        self.assertIsInstance(self.data02_05_activation["gate_pr"], int)
        bad = copy.deepcopy(self.data02_05_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_data02_05_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.data02_05_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_data02_06_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-DATA-02-06",
                         self.data02_06_activation["selected_packet_id"])
        self.assertEqual("DATA-02", self.data02_06_activation["module_id"])
        self.assertEqual("ELEVATED", self.data02_06_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.data02_06_activation["release_class"])
        self.assertEqual("docs/contracts/data-02-registry-v0.md",
                         self.data02_06_activation["approved_contract"])
        self.assertEqual(v.DATA02_CAPABILITY_ADMISSION,
                         self.data02_06_activation["capability_admission"])
        bad = copy.deepcopy(self.data02_06_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_data02_06_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.data02_06_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_data02_07_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-DATA-02-07",
                         self.data02_07_activation["selected_packet_id"])
        self.assertEqual("DATA-02", self.data02_07_activation["module_id"])
        self.assertEqual("ELEVATED", self.data02_07_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.data02_07_activation["release_class"])
        self.assertEqual("docs/contracts/data-02-registry-v0.md",
                         self.data02_07_activation["approved_contract"])
        self.assertEqual(v.DATA02_CAPABILITY_ADMISSION,
                         self.data02_07_activation["capability_admission"])
        bad = copy.deepcopy(self.data02_07_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_data02_07_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.data02_07_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_data02_08_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-DATA-02-08",
                         self.data02_08_activation["selected_packet_id"])
        self.assertEqual("DATA-02", self.data02_08_activation["module_id"])
        self.assertEqual("ELEVATED", self.data02_08_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.data02_08_activation["release_class"])
        self.assertEqual("docs/contracts/data-02-registry-v0.md",
                         self.data02_08_activation["approved_contract"])
        self.assertEqual(v.DATA02_CAPABILITY_ADMISSION,
                         self.data02_08_activation["capability_admission"])
        bad = copy.deepcopy(self.data02_08_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_data02_08_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.data02_08_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_data02_09_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-DATA-02-09",
                         self.data02_09_activation["selected_packet_id"])
        self.assertEqual("DATA-02", self.data02_09_activation["module_id"])
        self.assertEqual("ELEVATED", self.data02_09_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.data02_09_activation["release_class"])
        self.assertEqual("docs/contracts/data-02-registry-v0.md",
                         self.data02_09_activation["approved_contract"])
        self.assertEqual(v.DATA02_CAPABILITY_ADMISSION,
                         self.data02_09_activation["capability_admission"])
        bad = copy.deepcopy(self.data02_09_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_data02_09_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.data02_09_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_data03_01_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-DATA-03-01",
                         self.data03_01_activation["selected_packet_id"])
        self.assertEqual("DATA-03", self.data03_01_activation["module_id"])
        self.assertEqual("LOW", self.data03_01_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.data03_01_activation["release_class"])
        self.assertEqual("docs/contracts/data-03-governance-v0.md",
                         self.data03_01_activation["approved_contract"])
        self.assertEqual(v.DATA03_CAPABILITY_ADMISSION,
                         self.data03_01_activation["capability_admission"])
        bad = copy.deepcopy(self.data03_01_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_data03_01_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.data03_01_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_data03_02_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-DATA-03-02",
                         self.data03_02_activation["selected_packet_id"])
        self.assertEqual("DATA-03", self.data03_02_activation["module_id"])
        self.assertEqual("LOW", self.data03_02_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.data03_02_activation["release_class"])
        self.assertEqual("docs/contracts/data-03-import-v0.md",
                         self.data03_02_activation["approved_contract"])
        self.assertEqual(v.DATA03_CAPABILITY_ADMISSION,
                         self.data03_02_activation["capability_admission"])
        bad = copy.deepcopy(self.data03_02_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_data03_02_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.data03_02_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_data03_03_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-DATA-03-03",
                         self.data03_03_activation["selected_packet_id"])
        self.assertEqual("DATA-03", self.data03_03_activation["module_id"])
        self.assertEqual("ELEVATED", self.data03_03_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.data03_03_activation["release_class"])
        self.assertEqual("docs/contracts/data-03-import-v0.md",
                         self.data03_03_activation["approved_contract"])
        self.assertEqual(v.DATA03_CAPABILITY_ADMISSION,
                         self.data03_03_activation["capability_admission"])
        bad = copy.deepcopy(self.data03_03_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_data03_03_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.data03_03_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_data03_04_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-DATA-03-04",
                         self.data03_04_activation["selected_packet_id"])
        self.assertEqual("DATA-03", self.data03_04_activation["module_id"])
        self.assertEqual("ELEVATED", self.data03_04_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.data03_04_activation["release_class"])
        self.assertEqual("docs/contracts/data-03-import-v0.md",
                         self.data03_04_activation["approved_contract"])
        self.assertEqual(v.DATA03_CAPABILITY_ADMISSION,
                         self.data03_04_activation["capability_admission"])
        bad = copy.deepcopy(self.data03_04_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_data03_04_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.data03_04_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_data03_05_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-DATA-03-05",
                         self.data03_05_activation["selected_packet_id"])
        self.assertEqual("DATA-03", self.data03_05_activation["module_id"])
        self.assertEqual("ELEVATED", self.data03_05_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.data03_05_activation["release_class"])
        self.assertEqual("docs/contracts/data-03-import-v0.md",
                         self.data03_05_activation["approved_contract"])
        self.assertEqual(v.DATA03_CAPABILITY_ADMISSION,
                         self.data03_05_activation["capability_admission"])
        bad = copy.deepcopy(self.data03_05_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_data03_05_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.data03_05_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_data03_06_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-DATA-03-06",
                         self.data03_06_activation["selected_packet_id"])
        self.assertEqual("DATA-03", self.data03_06_activation["module_id"])
        self.assertEqual("ELEVATED", self.data03_06_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.data03_06_activation["release_class"])
        self.assertEqual("docs/contracts/data-03-import-v0.md",
                         self.data03_06_activation["approved_contract"])
        self.assertEqual(v.DATA03_CAPABILITY_ADMISSION,
                         self.data03_06_activation["capability_admission"])
        bad = copy.deepcopy(self.data03_06_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_data03_06_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.data03_06_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_data03_07_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-DATA-03-07",
                         self.data03_07_activation["selected_packet_id"])
        self.assertEqual("DATA-03", self.data03_07_activation["module_id"])
        self.assertEqual("ELEVATED", self.data03_07_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.data03_07_activation["release_class"])
        self.assertEqual("docs/contracts/data-03-import-v0.md",
                         self.data03_07_activation["approved_contract"])
        self.assertEqual(v.DATA03_CAPABILITY_ADMISSION,
                         self.data03_07_activation["capability_admission"])
        bad = copy.deepcopy(self.data03_07_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_data03_07_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.data03_07_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_data03_08_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-DATA-03-08",
                         self.data03_08_activation["selected_packet_id"])
        self.assertEqual("DATA-03", self.data03_08_activation["module_id"])
        self.assertEqual("ELEVATED", self.data03_08_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.data03_08_activation["release_class"])
        self.assertEqual("docs/contracts/data-03-import-v0.md",
                         self.data03_08_activation["approved_contract"])
        self.assertEqual(v.DATA03_CAPABILITY_ADMISSION,
                         self.data03_08_activation["capability_admission"])
        bad = copy.deepcopy(self.data03_08_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_data03_08_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.data03_08_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_data03_09_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-DATA-03-09",
                         self.data03_09_activation["selected_packet_id"])
        self.assertEqual("DATA-03", self.data03_09_activation["module_id"])
        self.assertEqual("ELEVATED", self.data03_09_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.data03_09_activation["release_class"])
        self.assertEqual("docs/contracts/data-03-import-v0.md",
                         self.data03_09_activation["approved_contract"])
        self.assertEqual(v.DATA03_CAPABILITY_ADMISSION,
                         self.data03_09_activation["capability_admission"])
        bad = copy.deepcopy(self.data03_09_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_data03_09_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.data03_09_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_data04_01_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-DATA-04-01",
                         self.data04_01_activation["selected_packet_id"])
        self.assertEqual("DATA-04", self.data04_01_activation["module_id"])
        self.assertEqual("LOW", self.data04_01_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.data04_01_activation["release_class"])
        self.assertEqual("docs/contracts/data-04-governance-v0.md",
                         self.data04_01_activation["approved_contract"])
        self.assertEqual(v.DATA04_CAPABILITY_ADMISSION,
                         self.data04_01_activation["capability_admission"])
        bad = copy.deepcopy(self.data04_01_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_data04_01_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.data04_01_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_data04_02_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-DATA-04-02",
                         self.data04_02_activation["selected_packet_id"])
        self.assertEqual("DATA-04", self.data04_02_activation["module_id"])
        self.assertEqual("LOW", self.data04_02_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.data04_02_activation["release_class"])
        self.assertEqual("docs/contracts/data-04-scene-v0.md",
                         self.data04_02_activation["approved_contract"])
        self.assertEqual(v.DATA04_CAPABILITY_ADMISSION,
                         self.data04_02_activation["capability_admission"])
        bad = copy.deepcopy(self.data04_02_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_data04_02_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.data04_02_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_data04_03_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-DATA-04-03",
                         self.data04_03_activation["selected_packet_id"])
        self.assertEqual("DATA-04", self.data04_03_activation["module_id"])
        self.assertEqual("ELEVATED", self.data04_03_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.data04_03_activation["release_class"])
        self.assertEqual("docs/contracts/data-04-scene-v0.md",
                         self.data04_03_activation["approved_contract"])
        self.assertEqual(v.DATA04_CAPABILITY_ADMISSION,
                         self.data04_03_activation["capability_admission"])
        bad = copy.deepcopy(self.data04_03_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_data04_03_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.data04_03_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_data04_04_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-DATA-04-04",
                         self.data04_04_activation["selected_packet_id"])
        self.assertEqual("DATA-04", self.data04_04_activation["module_id"])
        self.assertEqual("ELEVATED", self.data04_04_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.data04_04_activation["release_class"])
        self.assertEqual("docs/contracts/data-04-scene-v0.md",
                         self.data04_04_activation["approved_contract"])
        self.assertEqual(v.DATA04_CAPABILITY_ADMISSION,
                         self.data04_04_activation["capability_admission"])
        bad = copy.deepcopy(self.data04_04_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_data04_04_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.data04_04_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_data04_05_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-DATA-04-05",
                         self.data04_05_activation["selected_packet_id"])
        self.assertEqual("DATA-04", self.data04_05_activation["module_id"])
        self.assertEqual("ELEVATED", self.data04_05_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.data04_05_activation["release_class"])
        self.assertEqual("docs/contracts/data-04-scene-v0.md",
                         self.data04_05_activation["approved_contract"])
        self.assertEqual(v.DATA04_CAPABILITY_ADMISSION,
                         self.data04_05_activation["capability_admission"])
        bad = copy.deepcopy(self.data04_05_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_data04_05_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.data04_05_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_data04_06_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-DATA-04-06",
                         self.data04_06_activation["selected_packet_id"])
        self.assertEqual("DATA-04", self.data04_06_activation["module_id"])
        self.assertEqual("ELEVATED", self.data04_06_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.data04_06_activation["release_class"])
        self.assertEqual("docs/contracts/data-04-scene-v0.md",
                         self.data04_06_activation["approved_contract"])
        self.assertEqual(v.DATA04_CAPABILITY_ADMISSION,
                         self.data04_06_activation["capability_admission"])
        bad = copy.deepcopy(self.data04_06_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_data04_06_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.data04_06_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_data04_07_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-DATA-04-07",
                         self.data04_07_activation["selected_packet_id"])
        self.assertEqual("DATA-04", self.data04_07_activation["module_id"])
        self.assertEqual("ELEVATED", self.data04_07_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.data04_07_activation["release_class"])
        self.assertEqual("docs/contracts/data-04-scene-v0.md",
                         self.data04_07_activation["approved_contract"])
        self.assertEqual(v.DATA04_CAPABILITY_ADMISSION,
                         self.data04_07_activation["capability_admission"])
        bad = copy.deepcopy(self.data04_07_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_data04_07_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.data04_07_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_data05_01_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-DATA-05-01",
                         self.data05_01_activation["selected_packet_id"])
        self.assertEqual("DATA-05", self.data05_01_activation["module_id"])
        self.assertEqual("LOW", self.data05_01_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.data05_01_activation["release_class"])
        self.assertEqual("docs/contracts/data-05-governance-v0.md",
                         self.data05_01_activation["approved_contract"])
        self.assertEqual(v.DATA05_CAPABILITY_ADMISSION,
                         self.data05_01_activation["capability_admission"])
        bad = copy.deepcopy(self.data05_01_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_data05_01_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.data05_01_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_data05_02_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-DATA-05-02",
                         self.data05_02_activation["selected_packet_id"])
        self.assertEqual("DATA-05", self.data05_02_activation["module_id"])
        self.assertEqual("LOW", self.data05_02_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.data05_02_activation["release_class"])
        self.assertEqual("docs/contracts/data-05-bundle-v0.md",
                         self.data05_02_activation["approved_contract"])
        self.assertEqual(v.DATA05_CAPABILITY_ADMISSION,
                         self.data05_02_activation["capability_admission"])
        bad = copy.deepcopy(self.data05_02_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_data05_02_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.data05_02_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_data05_03_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-DATA-05-03",
                         self.data05_03_activation["selected_packet_id"])
        self.assertEqual("DATA-05", self.data05_03_activation["module_id"])
        self.assertEqual("ELEVATED", self.data05_03_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.data05_03_activation["release_class"])
        self.assertEqual("docs/contracts/data-05-bundle-v0.md",
                         self.data05_03_activation["approved_contract"])
        self.assertEqual(v.DATA05_CAPABILITY_ADMISSION,
                         self.data05_03_activation["capability_admission"])
        bad = copy.deepcopy(self.data05_03_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_data05_03_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.data05_03_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_data05_04_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-DATA-05-04",
                         self.data05_04_activation["selected_packet_id"])
        self.assertEqual("DATA-05", self.data05_04_activation["module_id"])
        self.assertEqual("ELEVATED", self.data05_04_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.data05_04_activation["release_class"])
        self.assertEqual("docs/contracts/data-05-bundle-v0.md",
                         self.data05_04_activation["approved_contract"])
        self.assertEqual(v.DATA05_CAPABILITY_ADMISSION,
                         self.data05_04_activation["capability_admission"])
        bad = copy.deepcopy(self.data05_04_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_data05_04_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.data05_04_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_data05_05_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-DATA-05-05",
                         self.data05_05_activation["selected_packet_id"])
        self.assertEqual("DATA-05", self.data05_05_activation["module_id"])
        self.assertEqual("ELEVATED", self.data05_05_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.data05_05_activation["release_class"])
        self.assertEqual("docs/contracts/data-05-bundle-v0.md",
                         self.data05_05_activation["approved_contract"])
        self.assertEqual(v.DATA05_CAPABILITY_ADMISSION,
                         self.data05_05_activation["capability_admission"])
        bad = copy.deepcopy(self.data05_05_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_data05_05_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.data05_05_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_data05_06_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-DATA-05-06",
                         self.data05_06_activation["selected_packet_id"])
        self.assertEqual("DATA-05", self.data05_06_activation["module_id"])
        self.assertEqual("ELEVATED", self.data05_06_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.data05_06_activation["release_class"])
        self.assertEqual("docs/contracts/data-05-bundle-v0.md",
                         self.data05_06_activation["approved_contract"])
        self.assertEqual(v.DATA05_CAPABILITY_ADMISSION,
                         self.data05_06_activation["capability_admission"])
        bad = copy.deepcopy(self.data05_06_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_data05_06_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.data05_06_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_data05_07_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-DATA-05-07",
                         self.data05_07_activation["selected_packet_id"])
        self.assertEqual("DATA-05", self.data05_07_activation["module_id"])
        self.assertEqual("ELEVATED", self.data05_07_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.data05_07_activation["release_class"])
        self.assertEqual("docs/contracts/data-05-bundle-v0.md",
                         self.data05_07_activation["approved_contract"])
        self.assertEqual(v.DATA05_CAPABILITY_ADMISSION,
                         self.data05_07_activation["capability_admission"])
        bad = copy.deepcopy(self.data05_07_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_data05_07_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.data05_07_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_data05_08_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-DATA-05-08",
                         self.data05_08_activation["selected_packet_id"])
        self.assertEqual("DATA-05", self.data05_08_activation["module_id"])
        self.assertEqual("ELEVATED", self.data05_08_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.data05_08_activation["release_class"])
        self.assertEqual("docs/contracts/data-05-bundle-v0.md",
                         self.data05_08_activation["approved_contract"])
        self.assertEqual(v.DATA05_CAPABILITY_ADMISSION,
                         self.data05_08_activation["capability_admission"])
        bad = copy.deepcopy(self.data05_08_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_data05_08_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.data05_08_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx01_01_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-01-01",
                         self.gfx01_01_activation["selected_packet_id"])
        self.assertEqual("GFX-01", self.gfx01_01_activation["module_id"])
        self.assertEqual("LOW", self.gfx01_01_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx01_01_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-01-governance-v0.md",
                         self.gfx01_01_activation["approved_contract"])
        self.assertEqual(v.GFX01_CAPABILITY_ADMISSION,
                         self.gfx01_01_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx01_01_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx01_01_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx01_01_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx01_02_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-01-02",
                         self.gfx01_02_activation["selected_packet_id"])
        self.assertEqual("GFX-01", self.gfx01_02_activation["module_id"])
        self.assertEqual("LOW", self.gfx01_02_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx01_02_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-01-rhi-v0.md",
                         self.gfx01_02_activation["approved_contract"])
        self.assertEqual(v.GFX01_CAPABILITY_ADMISSION,
                         self.gfx01_02_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx01_02_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx01_02_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx01_02_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx01_03_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-01-03",
                         self.gfx01_03_activation["selected_packet_id"])
        self.assertEqual("GFX-01", self.gfx01_03_activation["module_id"])
        self.assertEqual("ELEVATED", self.gfx01_03_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx01_03_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-01-rhi-v0.md",
                         self.gfx01_03_activation["approved_contract"])
        self.assertEqual(v.GFX01_CAPABILITY_ADMISSION,
                         self.gfx01_03_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx01_03_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx01_03_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx01_03_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx01_04_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-01-04",
                         self.gfx01_04_activation["selected_packet_id"])
        self.assertEqual("GFX-01", self.gfx01_04_activation["module_id"])
        self.assertEqual("ELEVATED", self.gfx01_04_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx01_04_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-01-rhi-v0.md",
                         self.gfx01_04_activation["approved_contract"])
        self.assertEqual(v.GFX01_CAPABILITY_ADMISSION,
                         self.gfx01_04_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx01_04_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx01_04_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx01_04_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx01_05_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-01-05",
                         self.gfx01_05_activation["selected_packet_id"])
        self.assertEqual("GFX-01", self.gfx01_05_activation["module_id"])
        self.assertEqual("ELEVATED", self.gfx01_05_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx01_05_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-01-rhi-v0.md",
                         self.gfx01_05_activation["approved_contract"])
        self.assertEqual(v.GFX01_CAPABILITY_ADMISSION,
                         self.gfx01_05_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx01_05_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx01_05_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx01_05_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx01_06_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-01-06",
                         self.gfx01_06_activation["selected_packet_id"])
        self.assertEqual("GFX-01", self.gfx01_06_activation["module_id"])
        self.assertEqual("ELEVATED", self.gfx01_06_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx01_06_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-01-rhi-v0.md",
                         self.gfx01_06_activation["approved_contract"])
        self.assertEqual(v.GFX01_CAPABILITY_ADMISSION,
                         self.gfx01_06_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx01_06_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx01_06_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx01_06_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx01_07_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-01-07",
                         self.gfx01_07_activation["selected_packet_id"])
        self.assertEqual("GFX-01", self.gfx01_07_activation["module_id"])
        self.assertEqual("ELEVATED", self.gfx01_07_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx01_07_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-01-rhi-v0.md",
                         self.gfx01_07_activation["approved_contract"])
        self.assertEqual(v.GFX01_CAPABILITY_ADMISSION,
                         self.gfx01_07_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx01_07_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx01_07_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx01_07_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx01_08_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-01-08",
                         self.gfx01_08_activation["selected_packet_id"])
        self.assertEqual("GFX-01", self.gfx01_08_activation["module_id"])
        self.assertEqual("ELEVATED", self.gfx01_08_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx01_08_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-01-rhi-v0.md",
                         self.gfx01_08_activation["approved_contract"])
        self.assertEqual(v.GFX01_CAPABILITY_ADMISSION,
                         self.gfx01_08_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx01_08_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx01_08_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx01_08_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx01_09_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-01-09",
                         self.gfx01_09_activation["selected_packet_id"])
        self.assertEqual("GFX-01", self.gfx01_09_activation["module_id"])
        self.assertEqual("ELEVATED", self.gfx01_09_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx01_09_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-01-rhi-v0.md",
                         self.gfx01_09_activation["approved_contract"])
        self.assertEqual(v.GFX01_CAPABILITY_ADMISSION,
                         self.gfx01_09_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx01_09_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx01_09_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx01_09_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx02_01_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-02-01",
                         self.gfx02_01_activation["selected_packet_id"])
        self.assertEqual("GFX-02", self.gfx02_01_activation["module_id"])
        self.assertEqual("LOW", self.gfx02_01_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx02_01_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-02-governance-v0.md",
                         self.gfx02_01_activation["approved_contract"])
        self.assertEqual(v.GFX02_CAPABILITY_ADMISSION,
                         self.gfx02_01_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx02_01_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx02_01_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx02_01_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx02_02_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-02-02",
                         self.gfx02_02_activation["selected_packet_id"])
        self.assertEqual("GFX-02", self.gfx02_02_activation["module_id"])
        self.assertEqual("LOW", self.gfx02_02_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx02_02_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-02-shader-internal-v0.md",
                         self.gfx02_02_activation["approved_contract"])
        self.assertEqual(v.GFX02_CAPABILITY_ADMISSION,
                         self.gfx02_02_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx02_02_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx02_02_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx02_02_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx02_03_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-02-03",
                         self.gfx02_03_activation["selected_packet_id"])
        self.assertEqual("GFX-02", self.gfx02_03_activation["module_id"])
        self.assertEqual("ELEVATED", self.gfx02_03_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx02_03_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-02-shader-internal-v0.md",
                         self.gfx02_03_activation["approved_contract"])
        self.assertEqual(v.GFX02_CAPABILITY_ADMISSION,
                         self.gfx02_03_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx02_03_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx02_03_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx02_03_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx02_04_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-02-04",
                         self.gfx02_04_activation["selected_packet_id"])
        self.assertEqual("GFX-02", self.gfx02_04_activation["module_id"])
        self.assertEqual("ELEVATED", self.gfx02_04_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx02_04_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-02-shader-internal-v0.md",
                         self.gfx02_04_activation["approved_contract"])
        self.assertEqual(v.GFX02_CAPABILITY_ADMISSION,
                         self.gfx02_04_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx02_04_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx02_04_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx02_04_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx02_05_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-02-05",
                         self.gfx02_05_activation["selected_packet_id"])
        self.assertEqual("GFX-02", self.gfx02_05_activation["module_id"])
        self.assertEqual("ELEVATED", self.gfx02_05_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx02_05_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-02-shader-internal-v0.md",
                         self.gfx02_05_activation["approved_contract"])
        self.assertEqual(v.GFX02_CAPABILITY_ADMISSION,
                         self.gfx02_05_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx02_05_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx02_05_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx02_05_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx02_06_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-02-06",
                         self.gfx02_06_activation["selected_packet_id"])
        self.assertEqual("GFX-02", self.gfx02_06_activation["module_id"])
        self.assertEqual("ELEVATED", self.gfx02_06_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx02_06_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-02-shader-internal-v0.md",
                         self.gfx02_06_activation["approved_contract"])
        self.assertEqual(v.GFX02_CAPABILITY_ADMISSION,
                         self.gfx02_06_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx02_06_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx02_06_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx02_06_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx02_07_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-02-07",
                         self.gfx02_07_activation["selected_packet_id"])
        self.assertEqual("GFX-02", self.gfx02_07_activation["module_id"])
        self.assertEqual("ELEVATED", self.gfx02_07_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx02_07_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-02-shader-internal-v0.md",
                         self.gfx02_07_activation["approved_contract"])
        self.assertEqual(v.GFX02_CAPABILITY_ADMISSION,
                         self.gfx02_07_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx02_07_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx02_07_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx02_07_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx02_08_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-02-08",
                         self.gfx02_08_activation["selected_packet_id"])
        self.assertEqual("GFX-02", self.gfx02_08_activation["module_id"])
        self.assertEqual("ELEVATED", self.gfx02_08_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx02_08_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-02-shader-internal-v0.md",
                         self.gfx02_08_activation["approved_contract"])
        self.assertEqual(v.GFX02_CAPABILITY_ADMISSION,
                         self.gfx02_08_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx02_08_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx02_08_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx02_08_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx03_01_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-03-01",
                         self.gfx03_01_activation["selected_packet_id"])
        self.assertEqual("GFX-03", self.gfx03_01_activation["module_id"])
        self.assertEqual("LOW", self.gfx03_01_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx03_01_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-03-governance-v0.md",
                         self.gfx03_01_activation["approved_contract"])
        self.assertEqual(v.GFX03_CAPABILITY_ADMISSION,
                         self.gfx03_01_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx03_01_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx03_01_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx03_01_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx03_02_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-03-02",
                         self.gfx03_02_activation["selected_packet_id"])
        self.assertEqual("GFX-03", self.gfx03_02_activation["module_id"])
        self.assertEqual("LOW", self.gfx03_02_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx03_02_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-03-render-graph-internal-v0.md",
                         self.gfx03_02_activation["approved_contract"])
        self.assertEqual(v.GFX03_CAPABILITY_ADMISSION,
                         self.gfx03_02_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx03_02_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx03_02_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx03_02_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx03_03_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-03-03",
                         self.gfx03_03_activation["selected_packet_id"])
        self.assertEqual("GFX-03", self.gfx03_03_activation["module_id"])
        self.assertEqual("ELEVATED", self.gfx03_03_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx03_03_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-03-render-graph-internal-v0.md",
                         self.gfx03_03_activation["approved_contract"])
        self.assertEqual(v.GFX03_CAPABILITY_ADMISSION,
                         self.gfx03_03_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx03_03_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx03_03_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx03_03_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx03_04_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-03-04",
                         self.gfx03_04_activation["selected_packet_id"])
        self.assertEqual("GFX-03", self.gfx03_04_activation["module_id"])
        self.assertEqual("ELEVATED", self.gfx03_04_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx03_04_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-03-render-graph-internal-v0.md",
                         self.gfx03_04_activation["approved_contract"])
        self.assertEqual(v.GFX03_CAPABILITY_ADMISSION,
                         self.gfx03_04_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx03_04_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx03_04_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx03_04_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx03_05_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-03-05",
                         self.gfx03_05_activation["selected_packet_id"])
        self.assertEqual("GFX-03", self.gfx03_05_activation["module_id"])
        self.assertEqual("ELEVATED", self.gfx03_05_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx03_05_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-03-render-graph-internal-v0.md",
                         self.gfx03_05_activation["approved_contract"])
        self.assertEqual(v.GFX03_CAPABILITY_ADMISSION,
                         self.gfx03_05_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx03_05_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx03_05_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx03_05_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx03_06_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-03-06",
                         self.gfx03_06_activation["selected_packet_id"])
        self.assertEqual("GFX-03", self.gfx03_06_activation["module_id"])
        self.assertEqual("ELEVATED", self.gfx03_06_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx03_06_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-03-render-graph-internal-v0.md",
                         self.gfx03_06_activation["approved_contract"])
        self.assertEqual(v.GFX03_CAPABILITY_ADMISSION,
                         self.gfx03_06_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx03_06_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx03_06_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx03_06_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx03_07_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-03-07",
                         self.gfx03_07_activation["selected_packet_id"])
        self.assertEqual("GFX-03", self.gfx03_07_activation["module_id"])
        self.assertEqual("ELEVATED", self.gfx03_07_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx03_07_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-03-render-graph-internal-v0.md",
                         self.gfx03_07_activation["approved_contract"])
        self.assertEqual(v.GFX03_CAPABILITY_ADMISSION,
                         self.gfx03_07_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx03_07_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx03_07_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx03_07_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx03_08_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-03-08",
                         self.gfx03_08_activation["selected_packet_id"])
        self.assertEqual("GFX-03", self.gfx03_08_activation["module_id"])
        self.assertEqual("ELEVATED", self.gfx03_08_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx03_08_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-03-render-graph-internal-v0.md",
                         self.gfx03_08_activation["approved_contract"])
        self.assertEqual(v.GFX03_CAPABILITY_ADMISSION,
                         self.gfx03_08_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx03_08_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx03_08_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx03_08_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx04_01_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-04-01",
                         self.gfx04_01_activation["selected_packet_id"])
        self.assertEqual("GFX-04", self.gfx04_01_activation["module_id"])
        self.assertEqual("LOW", self.gfx04_01_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx04_01_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-04-governance-v0.md",
                         self.gfx04_01_activation["approved_contract"])
        self.assertEqual(v.GFX04_CAPABILITY_ADMISSION,
                         self.gfx04_01_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx04_01_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx04_01_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx04_01_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx04_02_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-04-02",
                         self.gfx04_02_activation["selected_packet_id"])
        self.assertEqual("GFX-04", self.gfx04_02_activation["module_id"])
        self.assertEqual("LOW", self.gfx04_02_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx04_02_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-04-geometry-internal-v0.md",
                         self.gfx04_02_activation["approved_contract"])
        self.assertEqual(v.GFX04_CAPABILITY_ADMISSION,
                         self.gfx04_02_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx04_02_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx04_02_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx04_02_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx04_03_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-04-03",
                         self.gfx04_03_activation["selected_packet_id"])
        self.assertEqual("GFX-04", self.gfx04_03_activation["module_id"])
        self.assertEqual("ELEVATED", self.gfx04_03_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx04_03_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-04-geometry-internal-v0.md",
                         self.gfx04_03_activation["approved_contract"])
        self.assertEqual(v.GFX04_CAPABILITY_ADMISSION,
                         self.gfx04_03_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx04_03_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx04_03_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx04_03_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx04_04_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-04-04",
                         self.gfx04_04_activation["selected_packet_id"])
        self.assertEqual("GFX-04", self.gfx04_04_activation["module_id"])
        self.assertEqual("ELEVATED", self.gfx04_04_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx04_04_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-04-geometry-internal-v0.md",
                         self.gfx04_04_activation["approved_contract"])
        self.assertEqual(v.GFX04_CAPABILITY_ADMISSION,
                         self.gfx04_04_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx04_04_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx04_04_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx04_04_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx04_05_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-04-05",
                         self.gfx04_05_activation["selected_packet_id"])
        self.assertEqual("GFX-04", self.gfx04_05_activation["module_id"])
        self.assertEqual("ELEVATED", self.gfx04_05_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx04_05_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-04-geometry-internal-v0.md",
                         self.gfx04_05_activation["approved_contract"])
        self.assertEqual(v.GFX04_CAPABILITY_ADMISSION,
                         self.gfx04_05_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx04_05_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx04_05_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx04_05_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx04_06_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-04-06",
                         self.gfx04_06_activation["selected_packet_id"])
        self.assertEqual("GFX-04", self.gfx04_06_activation["module_id"])
        self.assertEqual("ELEVATED", self.gfx04_06_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx04_06_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-04-geometry-internal-v0.md",
                         self.gfx04_06_activation["approved_contract"])
        self.assertEqual(v.GFX04_CAPABILITY_ADMISSION,
                         self.gfx04_06_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx04_06_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx04_06_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx04_06_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx04_07_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-04-07",
                         self.gfx04_07_activation["selected_packet_id"])
        self.assertEqual("GFX-04", self.gfx04_07_activation["module_id"])
        self.assertEqual("ELEVATED", self.gfx04_07_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx04_07_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-04-geometry-internal-v0.md",
                         self.gfx04_07_activation["approved_contract"])
        self.assertEqual(v.GFX04_CAPABILITY_ADMISSION,
                         self.gfx04_07_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx04_07_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx04_07_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx04_07_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx04_08_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-04-08",
                         self.gfx04_08_activation["selected_packet_id"])
        self.assertEqual("GFX-04", self.gfx04_08_activation["module_id"])
        self.assertEqual("ELEVATED", self.gfx04_08_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx04_08_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-04-geometry-internal-v0.md",
                         self.gfx04_08_activation["approved_contract"])
        self.assertEqual(v.GFX04_CAPABILITY_ADMISSION,
                         self.gfx04_08_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx04_08_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx04_08_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx04_08_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx04_09_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-04-09",
                         self.gfx04_09_activation["selected_packet_id"])
        self.assertEqual("GFX-04", self.gfx04_09_activation["module_id"])
        self.assertEqual("ELEVATED", self.gfx04_09_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx04_09_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-04-geometry-internal-v0.md",
                         self.gfx04_09_activation["approved_contract"])
        self.assertEqual(v.GFX04_CAPABILITY_ADMISSION,
                         self.gfx04_09_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx04_09_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx04_09_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx04_09_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx05_01_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-05-01",
                         self.gfx05_01_activation["selected_packet_id"])
        self.assertEqual("GFX-05", self.gfx05_01_activation["module_id"])
        self.assertEqual("LOW", self.gfx05_01_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx05_01_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-05-governance-v0.md",
                         self.gfx05_01_activation["approved_contract"])
        self.assertEqual(v.GFX05_CAPABILITY_ADMISSION,
                         self.gfx05_01_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx05_01_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx05_01_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx05_01_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx05_02_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-05-02",
                         self.gfx05_02_activation["selected_packet_id"])
        self.assertEqual("GFX-05", self.gfx05_02_activation["module_id"])
        self.assertEqual("LOW", self.gfx05_02_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx05_02_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-05-material-internal-v0.md",
                         self.gfx05_02_activation["approved_contract"])
        self.assertEqual(v.GFX05_CAPABILITY_ADMISSION,
                         self.gfx05_02_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx05_02_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx05_02_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx05_02_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx05_03_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-05-03",
                         self.gfx05_03_activation["selected_packet_id"])
        self.assertEqual("GFX-05", self.gfx05_03_activation["module_id"])
        self.assertEqual("ELEVATED", self.gfx05_03_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx05_03_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-05-material-internal-v0.md",
                         self.gfx05_03_activation["approved_contract"])
        self.assertEqual(v.GFX05_CAPABILITY_ADMISSION,
                         self.gfx05_03_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx05_03_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx05_03_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx05_03_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx05_04_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-05-04",
                         self.gfx05_04_activation["selected_packet_id"])
        self.assertEqual("GFX-05", self.gfx05_04_activation["module_id"])
        self.assertEqual("ELEVATED", self.gfx05_04_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx05_04_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-05-material-internal-v0.md",
                         self.gfx05_04_activation["approved_contract"])
        self.assertEqual(v.GFX05_CAPABILITY_ADMISSION,
                         self.gfx05_04_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx05_04_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx05_04_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx05_04_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx05_05_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-05-05",
                         self.gfx05_05_activation["selected_packet_id"])
        self.assertEqual("GFX-05", self.gfx05_05_activation["module_id"])
        self.assertEqual("ELEVATED", self.gfx05_05_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx05_05_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-05-material-internal-v0.md",
                         self.gfx05_05_activation["approved_contract"])
        self.assertEqual(v.GFX05_CAPABILITY_ADMISSION,
                         self.gfx05_05_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx05_05_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx05_05_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx05_05_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx05_06_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-05-06",
                         self.gfx05_06_activation["selected_packet_id"])
        self.assertEqual("GFX-05", self.gfx05_06_activation["module_id"])
        self.assertEqual("ELEVATED", self.gfx05_06_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx05_06_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-05-material-internal-v0.md",
                         self.gfx05_06_activation["approved_contract"])
        self.assertEqual(v.GFX05_CAPABILITY_ADMISSION,
                         self.gfx05_06_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx05_06_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx05_06_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx05_06_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx05_07_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-05-07",
                         self.gfx05_07_activation["selected_packet_id"])
        self.assertEqual("GFX-05", self.gfx05_07_activation["module_id"])
        self.assertEqual("ELEVATED", self.gfx05_07_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx05_07_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-05-material-internal-v0.md",
                         self.gfx05_07_activation["approved_contract"])
        self.assertEqual(v.GFX05_CAPABILITY_ADMISSION,
                         self.gfx05_07_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx05_07_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx05_07_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx05_07_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx05_08_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-05-08",
                         self.gfx05_08_activation["selected_packet_id"])
        self.assertEqual("GFX-05", self.gfx05_08_activation["module_id"])
        self.assertEqual("ELEVATED", self.gfx05_08_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx05_08_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-05-material-internal-v0.md",
                         self.gfx05_08_activation["approved_contract"])
        self.assertEqual(v.GFX05_CAPABILITY_ADMISSION,
                         self.gfx05_08_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx05_08_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx05_08_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx05_08_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx05_09_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-05-09",
                         self.gfx05_09_activation["selected_packet_id"])
        self.assertEqual("GFX-05", self.gfx05_09_activation["module_id"])
        self.assertEqual("ELEVATED", self.gfx05_09_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx05_09_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-05-material-internal-v0.md",
                         self.gfx05_09_activation["approved_contract"])
        self.assertEqual(v.GFX05_CAPABILITY_ADMISSION,
                         self.gfx05_09_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx05_09_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx05_09_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx05_09_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx06_01_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-06-01",
                         self.gfx06_01_activation["selected_packet_id"])
        self.assertEqual("GFX-06", self.gfx06_01_activation["module_id"])
        self.assertEqual("LOW", self.gfx06_01_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx06_01_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-06-governance-v0.md",
                         self.gfx06_01_activation["approved_contract"])
        self.assertEqual(v.GFX06_CAPABILITY_ADMISSION,
                         self.gfx06_01_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx06_01_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx06_01_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx06_01_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx06_02_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-06-02",
                         self.gfx06_02_activation["selected_packet_id"])
        self.assertEqual("GFX-06", self.gfx06_02_activation["module_id"])
        self.assertEqual("LOW", self.gfx06_02_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx06_02_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-06-lighting-internal-v0.md",
                         self.gfx06_02_activation["approved_contract"])
        self.assertEqual(v.GFX06_CAPABILITY_ADMISSION,
                         self.gfx06_02_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx06_02_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx06_02_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx06_02_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx06_03_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-06-03",
                         self.gfx06_03_activation["selected_packet_id"])
        self.assertEqual("GFX-06", self.gfx06_03_activation["module_id"])
        self.assertEqual("ELEVATED", self.gfx06_03_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx06_03_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-06-lighting-internal-v0.md",
                         self.gfx06_03_activation["approved_contract"])
        self.assertEqual(v.GFX06_CAPABILITY_ADMISSION,
                         self.gfx06_03_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx06_03_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx06_03_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx06_03_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx06_04_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-06-04",
                         self.gfx06_04_activation["selected_packet_id"])
        self.assertEqual("GFX-06", self.gfx06_04_activation["module_id"])
        self.assertEqual("ELEVATED", self.gfx06_04_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx06_04_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-06-lighting-internal-v0.md",
                         self.gfx06_04_activation["approved_contract"])
        self.assertEqual(v.GFX06_CAPABILITY_ADMISSION,
                         self.gfx06_04_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx06_04_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx06_04_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx06_04_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx06_05_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-06-05",
                         self.gfx06_05_activation["selected_packet_id"])
        self.assertEqual("GFX-06", self.gfx06_05_activation["module_id"])
        self.assertEqual("ELEVATED", self.gfx06_05_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx06_05_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-06-lighting-internal-v0.md",
                         self.gfx06_05_activation["approved_contract"])
        self.assertEqual(v.GFX06_CAPABILITY_ADMISSION,
                         self.gfx06_05_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx06_05_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx06_05_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx06_05_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx06_06_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-06-06",
                         self.gfx06_06_activation["selected_packet_id"])
        self.assertEqual("GFX-06", self.gfx06_06_activation["module_id"])
        self.assertEqual("ELEVATED", self.gfx06_06_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx06_06_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-06-lighting-internal-v0.md",
                         self.gfx06_06_activation["approved_contract"])
        self.assertEqual(v.GFX06_CAPABILITY_ADMISSION,
                         self.gfx06_06_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx06_06_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx06_06_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx06_06_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx06_07_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-06-07",
                         self.gfx06_07_activation["selected_packet_id"])
        self.assertEqual("GFX-06", self.gfx06_07_activation["module_id"])
        self.assertEqual("ELEVATED", self.gfx06_07_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx06_07_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-06-lighting-internal-v0.md",
                         self.gfx06_07_activation["approved_contract"])
        self.assertEqual(v.GFX06_CAPABILITY_ADMISSION,
                         self.gfx06_07_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx06_07_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx06_07_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx06_07_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx06_08_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-06-08",
                         self.gfx06_08_activation["selected_packet_id"])
        self.assertEqual("GFX-06", self.gfx06_08_activation["module_id"])
        self.assertEqual("ELEVATED", self.gfx06_08_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx06_08_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-06-lighting-internal-v0.md",
                         self.gfx06_08_activation["approved_contract"])
        self.assertEqual(v.GFX06_CAPABILITY_ADMISSION,
                         self.gfx06_08_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx06_08_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx06_08_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx06_08_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx06_09_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-06-09",
                         self.gfx06_09_activation["selected_packet_id"])
        self.assertEqual("GFX-06", self.gfx06_09_activation["module_id"])
        self.assertEqual("ELEVATED", self.gfx06_09_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx06_09_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-06-lighting-internal-v0.md",
                         self.gfx06_09_activation["approved_contract"])
        self.assertEqual(v.GFX06_CAPABILITY_ADMISSION,
                         self.gfx06_09_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx06_09_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx06_09_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx06_09_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_two01_03_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-TWO-01-03",
                         self.two01_03_activation["selected_packet_id"])
        self.assertEqual("TWO-01", self.two01_03_activation["module_id"])
        self.assertEqual("ELEVATED", self.two01_03_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.two01_03_activation["release_class"])
        self.assertEqual("docs/contracts/two-01-canvas-internal-v0.md",
                         self.two01_03_activation["approved_contract"])
        self.assertEqual(v.TWO01_CAPABILITY_ADMISSION,
                         self.two01_03_activation["capability_admission"])
        bad = copy.deepcopy(self.two01_03_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_two01_03_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.two01_03_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_two01_02_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-TWO-01-02",
                         self.two01_02_activation["selected_packet_id"])
        self.assertEqual("TWO-01", self.two01_02_activation["module_id"])
        self.assertEqual("LOW", self.two01_02_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.two01_02_activation["release_class"])
        self.assertEqual("docs/contracts/two-01-canvas-internal-v0.md",
                         self.two01_02_activation["approved_contract"])
        self.assertEqual(v.TWO01_CAPABILITY_ADMISSION,
                         self.two01_02_activation["capability_admission"])
        bad = copy.deepcopy(self.two01_02_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_two01_02_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.two01_02_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_two01_01_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-TWO-01-01",
                         self.two01_01_activation["selected_packet_id"])
        self.assertEqual("TWO-01", self.two01_01_activation["module_id"])
        self.assertEqual("LOW", self.two01_01_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.two01_01_activation["release_class"])
        self.assertEqual("docs/contracts/two-01-governance-v0.md",
                         self.two01_01_activation["approved_contract"])
        self.assertEqual(v.TWO01_CAPABILITY_ADMISSION,
                         self.two01_01_activation["capability_admission"])
        bad = copy.deepcopy(self.two01_01_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_two01_01_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.two01_01_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx08_09_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-08-09",
                         self.gfx08_09_activation["selected_packet_id"])
        self.assertEqual("GFX-08", self.gfx08_09_activation["module_id"])
        self.assertEqual("ELEVATED", self.gfx08_09_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx08_09_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-08-vfx-internal-v0.md",
                         self.gfx08_09_activation["approved_contract"])
        self.assertEqual(v.GFX08_CAPABILITY_ADMISSION,
                         self.gfx08_09_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx08_09_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx08_09_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx08_09_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx08_08_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-08-08",
                         self.gfx08_08_activation["selected_packet_id"])
        self.assertEqual("GFX-08", self.gfx08_08_activation["module_id"])
        self.assertEqual("ELEVATED", self.gfx08_08_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx08_08_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-08-vfx-internal-v0.md",
                         self.gfx08_08_activation["approved_contract"])
        self.assertEqual(v.GFX08_CAPABILITY_ADMISSION,
                         self.gfx08_08_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx08_08_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx08_08_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx08_08_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx08_07_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-08-07",
                         self.gfx08_07_activation["selected_packet_id"])
        self.assertEqual("GFX-08", self.gfx08_07_activation["module_id"])
        self.assertEqual("ELEVATED", self.gfx08_07_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx08_07_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-08-vfx-internal-v0.md",
                         self.gfx08_07_activation["approved_contract"])
        self.assertEqual(v.GFX08_CAPABILITY_ADMISSION,
                         self.gfx08_07_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx08_07_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx08_07_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx08_07_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx08_06_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-08-06",
                         self.gfx08_06_activation["selected_packet_id"])
        self.assertEqual("GFX-08", self.gfx08_06_activation["module_id"])
        self.assertEqual("ELEVATED", self.gfx08_06_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx08_06_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-08-vfx-internal-v0.md",
                         self.gfx08_06_activation["approved_contract"])
        self.assertEqual(v.GFX08_CAPABILITY_ADMISSION,
                         self.gfx08_06_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx08_06_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx08_06_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx08_06_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx08_05_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-08-05",
                         self.gfx08_05_activation["selected_packet_id"])
        self.assertEqual("GFX-08", self.gfx08_05_activation["module_id"])
        self.assertEqual("ELEVATED", self.gfx08_05_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx08_05_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-08-vfx-internal-v0.md",
                         self.gfx08_05_activation["approved_contract"])
        self.assertEqual(v.GFX08_CAPABILITY_ADMISSION,
                         self.gfx08_05_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx08_05_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx08_05_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx08_05_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx08_04_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-08-04",
                         self.gfx08_04_activation["selected_packet_id"])
        self.assertEqual("GFX-08", self.gfx08_04_activation["module_id"])
        self.assertEqual("ELEVATED", self.gfx08_04_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx08_04_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-08-vfx-internal-v0.md",
                         self.gfx08_04_activation["approved_contract"])
        self.assertEqual(v.GFX08_CAPABILITY_ADMISSION,
                         self.gfx08_04_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx08_04_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx08_04_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx08_04_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx08_03_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-08-03",
                         self.gfx08_03_activation["selected_packet_id"])
        self.assertEqual("GFX-08", self.gfx08_03_activation["module_id"])
        self.assertEqual("ELEVATED", self.gfx08_03_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx08_03_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-08-vfx-internal-v0.md",
                         self.gfx08_03_activation["approved_contract"])
        self.assertEqual(v.GFX08_CAPABILITY_ADMISSION,
                         self.gfx08_03_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx08_03_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx08_03_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx08_03_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx08_02_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-08-02",
                         self.gfx08_02_activation["selected_packet_id"])
        self.assertEqual("GFX-08", self.gfx08_02_activation["module_id"])
        self.assertEqual("LOW", self.gfx08_02_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx08_02_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-08-vfx-internal-v0.md",
                         self.gfx08_02_activation["approved_contract"])
        self.assertEqual(v.GFX08_CAPABILITY_ADMISSION,
                         self.gfx08_02_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx08_02_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx08_02_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx08_02_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx08_01_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-08-01",
                         self.gfx08_01_activation["selected_packet_id"])
        self.assertEqual("GFX-08", self.gfx08_01_activation["module_id"])
        self.assertEqual("LOW", self.gfx08_01_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx08_01_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-08-governance-v0.md",
                         self.gfx08_01_activation["approved_contract"])
        self.assertEqual(v.GFX08_CAPABILITY_ADMISSION,
                         self.gfx08_01_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx08_01_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx08_01_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx08_01_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx07_01_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-07-01",
                         self.gfx07_01_activation["selected_packet_id"])
        self.assertEqual("GFX-07", self.gfx07_01_activation["module_id"])
        self.assertEqual("LOW", self.gfx07_01_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx07_01_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-07-governance-v0.md",
                         self.gfx07_01_activation["approved_contract"])
        self.assertEqual(v.GFX07_CAPABILITY_ADMISSION,
                         self.gfx07_01_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx07_01_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx07_01_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx07_01_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx07_02_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-07-02",
                         self.gfx07_02_activation["selected_packet_id"])
        self.assertEqual("GFX-07", self.gfx07_02_activation["module_id"])
        self.assertEqual("LOW", self.gfx07_02_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx07_02_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-07-post-processing-internal-v0.md",
                         self.gfx07_02_activation["approved_contract"])
        self.assertEqual(v.GFX07_CAPABILITY_ADMISSION,
                         self.gfx07_02_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx07_02_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx07_02_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx07_02_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx07_03_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-07-03",
                         self.gfx07_03_activation["selected_packet_id"])
        self.assertEqual("GFX-07", self.gfx07_03_activation["module_id"])
        self.assertEqual("ELEVATED", self.gfx07_03_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx07_03_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-07-post-processing-internal-v0.md",
                         self.gfx07_03_activation["approved_contract"])
        self.assertEqual(v.GFX07_CAPABILITY_ADMISSION,
                         self.gfx07_03_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx07_03_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx07_03_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx07_03_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx07_04_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-07-04",
                         self.gfx07_04_activation["selected_packet_id"])
        self.assertEqual("GFX-07", self.gfx07_04_activation["module_id"])
        self.assertEqual("ELEVATED", self.gfx07_04_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx07_04_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-07-post-processing-internal-v0.md",
                         self.gfx07_04_activation["approved_contract"])
        self.assertEqual(v.GFX07_CAPABILITY_ADMISSION,
                         self.gfx07_04_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx07_04_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx07_04_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx07_04_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx07_05_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-07-05",
                         self.gfx07_05_activation["selected_packet_id"])
        self.assertEqual("GFX-07", self.gfx07_05_activation["module_id"])
        self.assertEqual("ELEVATED", self.gfx07_05_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx07_05_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-07-post-processing-internal-v0.md",
                         self.gfx07_05_activation["approved_contract"])
        self.assertEqual(v.GFX07_CAPABILITY_ADMISSION,
                         self.gfx07_05_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx07_05_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx07_05_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx07_05_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx07_06_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-07-06",
                         self.gfx07_06_activation["selected_packet_id"])
        self.assertEqual("GFX-07", self.gfx07_06_activation["module_id"])
        self.assertEqual("ELEVATED", self.gfx07_06_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx07_06_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-07-post-processing-internal-v0.md",
                         self.gfx07_06_activation["approved_contract"])
        self.assertEqual(v.GFX07_CAPABILITY_ADMISSION,
                         self.gfx07_06_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx07_06_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx07_06_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx07_06_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx07_07_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-07-07",
                         self.gfx07_07_activation["selected_packet_id"])
        self.assertEqual("GFX-07", self.gfx07_07_activation["module_id"])
        self.assertEqual("ELEVATED", self.gfx07_07_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx07_07_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-07-post-processing-internal-v0.md",
                         self.gfx07_07_activation["approved_contract"])
        self.assertEqual(v.GFX07_CAPABILITY_ADMISSION,
                         self.gfx07_07_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx07_07_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx07_07_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx07_07_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx07_08_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-07-08",
                         self.gfx07_08_activation["selected_packet_id"])
        self.assertEqual("GFX-07", self.gfx07_08_activation["module_id"])
        self.assertEqual("ELEVATED", self.gfx07_08_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx07_08_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-07-post-processing-internal-v0.md",
                         self.gfx07_08_activation["approved_contract"])
        self.assertEqual(v.GFX07_CAPABILITY_ADMISSION,
                         self.gfx07_08_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx07_08_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx07_08_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx07_08_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_data01_03_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-DATA-01-03", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_data01_04_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-DATA-01-04", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_data01_05_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-DATA-01-05", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_data01_06_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-DATA-01-06", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_data01_07_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-DATA-01-07", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_data01_08_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-DATA-01-08", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_data01_09_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-DATA-01-09", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_data02_03_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-DATA-02-03", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_data02_04_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-DATA-02-04", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_data02_05_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-DATA-02-05", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_data02_06_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-DATA-02-06", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_data02_07_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-DATA-02-07", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_data02_08_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-DATA-02-08", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_data02_09_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-DATA-02-09", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_data03_03_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-DATA-03-03", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_data03_04_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-DATA-03-04", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_data03_05_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-DATA-03-05", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_data03_06_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-DATA-03-06", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_data03_07_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-DATA-03-07", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_data03_08_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-DATA-03-08", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_data03_09_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-DATA-03-09", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_data04_03_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-DATA-04-03", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_data04_04_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-DATA-04-04", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_data04_05_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-DATA-04-05", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_data04_06_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-DATA-04-06", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_data04_07_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-DATA-04-07", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_data05_03_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-DATA-05-03", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_data05_04_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-DATA-05-04", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_data05_05_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-DATA-05-05", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_data05_06_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-DATA-05-06", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_data05_07_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-DATA-05-07", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_data05_08_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-DATA-05-08", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx01_03_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-01-03", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx01_04_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-01-04", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx01_05_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-01-05", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx01_06_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-01-06", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx01_07_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-01-07", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx01_08_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-01-08", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx01_09_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-01-09", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx01_10_closeout_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-01-10", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx02_01_governance_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-02-01", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx02_02_contract_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-02-02", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx02_03_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-02-03", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx02_04_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-02-04", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx02_05_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-02-05", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx02_06_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-02-06", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx02_07_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-02-07", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx02_08_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-02-08", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx02_09_closeout_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-02-09", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx03_01_governance_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-03-01", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx03_02_contract_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-03-02", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx03_03_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-03-03", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx03_04_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-03-04", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx03_05_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-03-05", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx03_06_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-03-06", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx03_07_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-03-07", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx03_08_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-03-08", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx03_09_closeout_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-03-09", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx04_01_governance_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-04-01", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx04_02_contract_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-04-02", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx04_03_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-04-03", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx04_04_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-04-04", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx04_05_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-04-05", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx04_06_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-04-06", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx04_07_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-04-07", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx04_08_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-04-08", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx04_09_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-04-09", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx04_10_closeout_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-04-10", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx05_01_governance_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-05-01", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx05_02_contract_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-05-02", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx05_03_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-05-03", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx05_04_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-05-04", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx05_05_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-05-05", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx05_06_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-05-06", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx05_07_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-05-07", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx05_08_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-05-08", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx05_09_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-05-09", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx05_10_closeout_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-05-10", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx06_01_governance_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-06-01", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx06_02_contract_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-06-02", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx06_03_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-06-03", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx06_04_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-06-04", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx06_05_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-06-05", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx06_06_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-06-06", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx06_07_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-06-07", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx06_08_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-06-08", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx06_09_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-06-09", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx06_10_closeout_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-06-10", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx08_09_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-08-09", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx08_08_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-08-08", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx08_07_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-08-07", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx08_06_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-08-06", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx08_05_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-08-05", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx08_04_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-08-04", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx08_03_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-08-03", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_two01_03_selector_is_ready(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        ready = subprocess.run([sys.executable, selector, "NLE-PRPLAN-TWO-01-03", "--json"],
                               capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(0, ready.returncode, (ready.stdout, ready.stderr))
        self.assertTrue(json.loads(ready.stdout)["executor_ready"])

    def test_two01_02_contract_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-TWO-01-02", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_two01_01_governance_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-TWO-01-01", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx08_10_closeout_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-08-10", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx08_02_contract_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-08-02", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx08_01_governance_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-08-01", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx07_01_governance_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-07-01", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx07_02_contract_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-07-02", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx07_03_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-07-03", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx07_04_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-07-04", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx07_05_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-07-05", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx07_06_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-07-06", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx07_07_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-07-07", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx07_08_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-07-08", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx07_09_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-GFX-07-09",
                         self.gfx07_09_activation["selected_packet_id"])
        self.assertEqual("GFX-07", self.gfx07_09_activation["module_id"])
        self.assertEqual("ELEVATED", self.gfx07_09_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.gfx07_09_activation["release_class"])
        self.assertEqual("docs/contracts/gfx-07-post-processing-internal-v0.md",
                         self.gfx07_09_activation["approved_contract"])
        self.assertEqual(v.GFX07_CAPABILITY_ADMISSION,
                         self.gfx07_09_activation["capability_admission"])
        bad = copy.deepcopy(self.gfx07_09_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_gfx07_09_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.gfx07_09_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_gfx07_09_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-07-09", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx07_10_closeout_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-07-10", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx01_02_contract_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-01-02", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_gfx01_01_governance_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-GFX-01-01", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_data05_09_closeout_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-DATA-05-09", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_data05_02_contract_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-DATA-05-02", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_data05_01_governance_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-DATA-05-01", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_data04_08_closeout_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-DATA-04-08", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_data04_02_contract_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-DATA-04-02", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_data04_01_governance_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-DATA-04-01", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_data03_10_closeout_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-DATA-03-10", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_data03_02_contract_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-DATA-03-02", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_data03_01_governance_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-DATA-03-01", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_data02_10_closeout_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-DATA-02-10", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_data02_02_contract_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-DATA-02-02", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_data02_01_governance_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-DATA-02-01", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_data01_10_closeout_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-DATA-01-10", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_data01_01_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-DATA-01-01", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_core06_04_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-CORE-06-04", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_core06_05_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-CORE-06-05", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_core06_06_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-CORE-06-06", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_core06_07_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-CORE-06-07", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_core06_08_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-CORE-06-08", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_core06_09_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-CORE-06-09", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_core06_03_completed_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-CORE-06-03", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_core06_02_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-CORE-06-02", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_core06_01_selector_denies(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        blocked = subprocess.run([sys.executable, selector, "NLE-PRPLAN-CORE-06-01", "--json"],
                                 capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(2, blocked.returncode, (blocked.stdout, blocked.stderr))
        self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_core04_09_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-CORE-04-09",
                         self.core04_09_activation["selected_packet_id"])
        self.assertEqual("CORE-04", self.core04_09_activation["module_id"])
        self.assertEqual("ELEVATED", self.core04_09_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.core04_09_activation["release_class"])
        self.assertEqual("docs/contracts/core-04-qualification-v0.md",
                         self.core04_09_activation["approved_contract"])
        self.assertEqual(v.CORE04_CAPABILITY_ADMISSION,
                         self.core04_09_activation["capability_admission"])
        self.assertIsInstance(self.core04_09_activation["gate_pr"], int)
        bad = copy.deepcopy(self.core04_09_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_core04_09_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.core04_09_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_core04_04_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-CORE-04-04",
                         self.core04_04_activation["selected_packet_id"])
        self.assertEqual("CORE-04", self.core04_04_activation["module_id"])
        self.assertEqual("ELEVATED", self.core04_04_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.core04_04_activation["release_class"])
        self.assertEqual("docs/contracts/core-04-timeline-v0.md",
                         self.core04_04_activation["approved_contract"])
        self.assertEqual(v.CORE04_CAPABILITY_ADMISSION,
                         self.core04_04_activation["capability_admission"])
        self.assertIsInstance(self.core04_04_activation["gate_pr"], int)
        bad = copy.deepcopy(self.core04_04_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_core04_04_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.core04_04_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_core04_03_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-CORE-04-03",
                         self.core04_03_activation["selected_packet_id"])
        self.assertEqual("CORE-04", self.core04_03_activation["module_id"])
        self.assertEqual("ELEVATED", self.core04_03_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.core04_03_activation["release_class"])
        self.assertEqual("docs/contracts/core-04-timeline-v0.md",
                         self.core04_03_activation["approved_contract"])
        self.assertEqual(v.CORE04_CAPABILITY_ADMISSION,
                         self.core04_03_activation["capability_admission"])
        self.assertIsInstance(self.core04_03_activation["gate_pr"], int)
        bad = copy.deepcopy(self.core04_03_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_core04_03_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.core04_03_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_core04_02_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-CORE-04-02",
                         self.core04_02_activation["selected_packet_id"])
        self.assertEqual("CORE-04", self.core04_02_activation["module_id"])
        self.assertEqual("LOW", self.core04_02_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.core04_02_activation["release_class"])
        self.assertEqual("docs/contracts/core-04-timeline-v0.md",
                         self.core04_02_activation["approved_contract"])
        self.assertEqual(v.CORE04_CAPABILITY_ADMISSION,
                         self.core04_02_activation["capability_admission"])
        self.assertIsInstance(self.core04_02_activation["gate_pr"], int)
        bad = copy.deepcopy(self.core04_02_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_core04_02_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.core04_02_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_core03_09_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-CORE-03-09",
                         self.core03_09_activation["selected_packet_id"])
        self.assertEqual("CORE-03", self.core03_09_activation["module_id"])
        self.assertEqual("ELEVATED", self.core03_09_activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.core03_09_activation["release_class"])
        self.assertEqual("docs/contracts/core-03-qualification-v0.md",
                         self.core03_09_activation["approved_contract"])
        self.assertEqual(v.CORE03_CAPABILITY_ADMISSION,
                         self.core03_09_activation["capability_admission"])
        self.assertIsInstance(self.core03_09_activation["gate_pr"], int)
        bad = copy.deepcopy(self.core03_09_activation)
        bad["gate_pr"] = -1
        self.assertTrue(v.validate_activation(bad))

    def test_core03_09_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.core03_09_activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_selector_denies_all_after_core03_03_completion(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        for packet_id in ("NLE-PRPLAN-CORE-03-03", "NLE-PRPLAN-CORE-03-02",
                          "NLE-PRPLAN-CORE-03-04", "NLE-PRPLAN-CORE-03-05",
                          "NLE-PRPLAN-CORE-03-06", "NLE-PRPLAN-CORE-03-07",
                          "NLE-PRPLAN-CORE-03-08", "NLE-PRPLAN-CORE-03-10",
                          "NLE-PRPLAN-CORE-02-10"):
            blocked = subprocess.run([sys.executable, selector, packet_id, "--json"],
                                     capture_output=True, text=True, timeout=20, check=False)
            self.assertEqual(2, blocked.returncode, (packet_id, blocked.stdout, blocked.stderr))
            self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_live_source_drift_is_detected(self):
        with tempfile.TemporaryDirectory() as temp:
            root = Path(temp)
            fingerprints = {}
            for key, rel in v.ACTIVATION_SOURCES.items():
                path = root / rel
                path.parent.mkdir(parents=True, exist_ok=True)
                path.write_bytes(b"x")
                fingerprints[key] = v.file_blob_sha1(path)
            self.assertEqual([], v.verify_source_blobs(fingerprints, root))
            (root / v.ACTIVATION_SOURCES["checkpoint"]).write_bytes(b"y")
            self.assertTrue(any("source drift" in x for x in v.verify_source_blobs(fingerprints, root)))

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
