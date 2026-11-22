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
        cls.activation = json.loads(v.CORE05_07_ACTIVATION_FILE.read_text(encoding="utf-8"))

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
        self.assertEqual(["NLE-PRPLAN-CORE-05-07"], ready)
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
                          "NLE-PRPLAN-CORE-05-03", "NLE-PRPLAN-CORE-05-04", "NLE-PRPLAN-CORE-05-05", "NLE-PRPLAN-CORE-05-06"], completed)
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
        self.assertEqual("EXECUTOR_READY", core05[6]["status"])
        self.assertIsNone(core05[6]["github_pr"])
        self.assertEqual("ELEVATED", core05[6]["risk"])
        self.assertEqual("INTERNAL_ONLY", core05[6]["release_class"])
        self.assertEqual("PLANNED_BLOCKED", core05[9]["status"])
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
                          "NLE-PRPLAN-CORE-05-08", "NLE-PRPLAN-CORE-05-10"):
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

    def test_core05_07_selector_is_ready(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        ready = subprocess.run([sys.executable, selector, "NLE-PRPLAN-CORE-05-07", "--json"],
                               capture_output=True, text=True, timeout=20, check=False)
        self.assertEqual(0, ready.returncode, (ready.stdout, ready.stderr))
        self.assertTrue(json.loads(ready.stdout)["executor_ready"])

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
