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
        cls.core01_activation = json.loads(v.CORE01_ACTIVATION_FILE.read_text(encoding="utf-8"))
        cls.activation = json.loads(v.CORE02_ACTIVATION_FILE.read_text(encoding="utf-8"))

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
        self.assertEqual([], ready)
        completed = [p["packet_id"] for m in self.manifest["modules"] for p in m["packets"]
                     if p["status"] == "COMPLETED"]
        self.assertEqual(["NLE-PRPLAN-CORE-01-03", "NLE-PRPLAN-CORE-01-04",
                          "NLE-PRPLAN-CORE-01-05", "NLE-PRPLAN-CORE-01-06",
                          "NLE-PRPLAN-CORE-01-07", "NLE-PRPLAN-CORE-01-08",
                          "NLE-PRPLAN-CORE-02-03"], completed)
        core02 = self.manifest["modules"][1]["packets"]
        self.assertEqual("APPROVED_GOVERNANCE", core02[0]["status"])
        self.assertEqual("APPROVED_CONTRACT", core02[1]["status"])
        self.assertEqual("COMPLETED", core02[2]["status"])
        self.assertEqual(441, core02[2]["github_pr"])
        self.assertFalse(core02[2]["capability_admission"]["module_completion_claimed"])

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
        bad["risk"] = "LOW"
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
        }, self.core01_activation["sdl3"])
        bad = copy.deepcopy(self.core01_activation)
        bad["sdl3"]["commit"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_window_slice_is_exact(self):
        window_slice = self.core01_activation["window_slice"]
        self.assertEqual(["x11", "wayland"], window_slice["linux_drivers_built"])
        self.assertEqual("x11", window_slice["linux_runtime_tested"])
        self.assertEqual("wayland", window_slice["linux_runtime_not_qualified"])
        self.assertEqual("win32", window_slice["windows_runtime"])
        self.assertEqual("cocoa_or_not_qualified", window_slice["macos_runtime"])
        self.assertEqual("xvfb+openbox", window_slice["linux_display"])
        self.assertEqual("disabled", window_slice["render_gpu_audio"])
        self.assertIn("libx11-dev", window_slice["linux_packages"])
        self.assertIn("openbox", window_slice["linux_packages"])
        bad = copy.deepcopy(self.core01_activation)
        bad["window_slice"]["linux_packages"].append("forbidden-package")
        self.assertTrue(v.validate_activation(bad))

    def test_any_second_packet_activation_denied(self):
        def wrong(d):
            d["modules"][0]["packets"][8]["status"] = "EXECUTOR_READY"
        self.assertTrue(self.check(wrong))

    def test_module_level_promotion_remains_forbidden(self):
        reg = copy.deepcopy(self.registry)
        reg["modules"][0]["executor_ready"] = True
        self.assertTrue(v.validate_manifest(self.manifest, reg, self.activation))

    def test_selector_cli_all_denied_after_core02_03_completion(self):
        selector = str(v.ROOT / "scripts/select_packet.py")
        for packet_id in ("NLE-PRPLAN-CORE-01-03", "NLE-PRPLAN-CORE-01-04",
                          "NLE-PRPLAN-CORE-01-05", "NLE-PRPLAN-CORE-01-06",
                          "NLE-PRPLAN-CORE-01-07", "NLE-PRPLAN-CORE-01-08",
                          "NLE-PRPLAN-CORE-01-09", "NLE-PRPLAN-CORE-02-04",
                          "NLE-PRPLAN-CORE-02-03", "NLE-PRPLAN-CORE-02-03-EXTRA",
                          "NLE-PRPLAN-CORE-01-99"):
            blocked = subprocess.run([sys.executable, selector, packet_id, "--json"],
                                     capture_output=True, text=True, timeout=20, check=False)
            self.assertEqual(2, blocked.returncode, (packet_id, blocked.stdout, blocked.stderr))
            self.assertFalse(json.loads(blocked.stdout)["executor_ready"])

    def test_core02_completed_slice_cannot_claim_wrong_pr(self):
        def wrong(d):
            d["modules"][1]["packets"][2]["github_pr"] = 999
        self.assertTrue(any("expected COMPLETED/441" in x for x in self.check(wrong)))

    def test_core02_activation_is_exact(self):
        self.assertEqual("NLE-PRPLAN-CORE-02-03", self.activation["selected_packet_id"])
        self.assertEqual("CORE-02", self.activation["module_id"])
        self.assertEqual("STANDARD", self.activation["risk"])
        self.assertEqual("INTERNAL_ONLY", self.activation["release_class"])
        self.assertEqual(v.CORE02_CAPABILITY_ADMISSION, self.activation["capability_admission"])
        self.assertEqual(self.activation["gate_pr"],
                         self.manifest["modules"][1]["packets"][0]["github_pr"])
        bad = copy.deepcopy(self.activation)
        bad["capability_admission"]["required_capabilities"].append(
            {"id": "CORE01_WINDOW", "satisfied_by": "NLE-PRPLAN-CORE-01-08"})
        self.assertTrue(v.validate_activation(bad))

    def test_core02_capability_source_must_be_completed(self):
        def wrong(d):
            d["modules"][1]["packets"][2]["capability_admission"]["required_capabilities"][0]["satisfied_by"] = "NLE-PRPLAN-CORE-01-09"
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

    def test_core02_cannot_unlock_04(self):
        def wrong(d):
            d["modules"][1]["packets"][3]["status"] = "EXECUTOR_READY"
        self.assertTrue(self.check(wrong))

    def test_core02_activation_source_drift_denied(self):
        bad = copy.deepcopy(self.activation)
        bad["source_blob_sha1"]["checkpoint"] = "deadbeef"
        self.assertTrue(v.validate_activation(bad))

    def test_core02_module_registry_promotion_forbidden(self):
        reg = copy.deepcopy(self.registry)
        by_id = {m["module_id"]: m for m in reg["modules"]}
        by_id["CORE-02"]["executor_ready"] = True
        self.assertTrue(v.validate_manifest(self.manifest, reg, self.activation))

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
