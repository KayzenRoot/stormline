#!/usr/bin/env python3
"""Negative and positive unit tests for Stormline skill manifest/parser checks."""
import json
from pathlib import Path
import sys
import tempfile
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parent))
import validate_skills as v


VALID = """---
name: stormline-test-example
description: "Use when reviewing a test example; not for unapproved execution."
---
# TEST
[AGENTS.md](../../../AGENTS.md)

## Source and authority
Work Order must be BLOCKED until approved.

## Workflow
1. Inspect sources and formal gates.

## Acceptance and evidence
Record files, tests and real evidence.

## Stop condition
BLOCKED without owner approval.
"""


class SkillValidatorTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        self.skill = self.root / ".agents" / "skills" / "stormline-test-example" / "SKILL.md"
        self.skill.parent.mkdir(parents=True)
        (self.root / "AGENTS.md").write_text("Canonical rules\n", encoding="utf-8")
        self.skill.write_text(VALID, encoding="utf-8")

    def check(self, content):
        self.skill.write_text(content, encoding="utf-8")
        return v.validate_skill_document(self.skill, self.root)

    def test_valid_skill(self):
        self.assertEqual([], v.validate_skill_document(self.skill, self.root))

    def test_frontmatter_is_required(self):
        self.assertTrue(any("frontmatter" in s for s in self.check(VALID[4:])))

    def test_folder_name_must_match(self):
        self.assertTrue(any("name must match folder" in s for s in self.check(
            VALID.replace("stormline-test-example", "stormline-different"))))

    def test_description_cannot_be_empty(self):
        self.assertTrue(any("description" in s for s in self.check(
            VALID.replace('description: "Use when reviewing a test example; not for unapproved execution."',
                          'description: ""'))))

    def test_stop_gate_cannot_be_deleted(self):
        self.assertTrue(any("Stop condition" in s for s in self.check(
            VALID.replace("## Stop condition", "## Summary"))))

    def test_canonical_link_must_exist(self):
        self.assertTrue(any("nonexistent linked file" in s for s in self.check(
            VALID.replace("../../../AGENTS.md", "../../../missing.md"))))

    def test_links_cannot_escape_repo(self):
        self.assertTrue(any("escapes repository" in s for s in self.check(
            VALID.replace("../../../AGENTS.md", "../../../../outside.md"))))

    def test_duplicate_field(self):
        self.assertTrue(any("duplicate field" in s for s in self.check(
            VALID.replace('name: stormline-test-example\n',
                          'name: stormline-test-example\nname: stormline-test-example\n')))

    def test_verb_variants_use_for_and_use_to(self):
        self.assertEqual([], self.check(VALID.replace("Use when reviewing", "Use for reviewing")))
        self.assertEqual([], self.check(VALID.replace("Use when reviewing", "Use to review")))

    def test_fail_closed_case_insensitive(self):
        self.assertEqual([], self.check(VALID.replace("Work Order must be BLOCKED until approved.",
                                                       "Work Order must block until approved.")
                                         .replace("BLOCKED without owner approval.",
                                                  "Block without owner approval.")))

    def test_full_repository_manifest(self):
        self.assertEqual([], v.validate_repository(v.ROOT))


if __name__ == "__main__":
    unittest.main()
