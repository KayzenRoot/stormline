#!/usr/bin/env python3
"""Validate Stormline packet planning and at most one bounded owner-approved activation."""
from __future__ import annotations

import hashlib
import json
from pathlib import Path
import re
import sys

ROOT = Path(__file__).resolve().parents[1]
REGISTRY = ROOT / "docs/queue/implementation-registry.json"
MANIFEST = ROOT / "docs/pr-plans/manifest.json"
CORE01_ACTIVATION_FILE = ROOT / "docs/queue/packet-activation-core-01-08.json"
CORE01_09_ACTIVATION_FILE = ROOT / "docs/queue/packet-activation-core-01-09.json"
CORE01_10_ACTIVATION_FILE = ROOT / "docs/queue/packet-activation-core-01-10.json"
CORE01_11_ACTIVATION_FILE = ROOT / "docs/queue/packet-activation-core-01-11.json"
CORE01_12_ACTIVATION_FILE = ROOT / "docs/queue/packet-activation-core-01-12.json"
CORE01_13_ACTIVATION_FILE = ROOT / "docs/queue/packet-activation-core-01-13.json"
CORE01_14_ACTIVATION_FILE = ROOT / "docs/queue/packet-activation-core-01-14.json"
CORE02_ACTIVATION_FILE = ROOT / "docs/queue/packet-activation-core-02-03.json"
# The selector reads this path; it is the activation for the current manifest state.
ACTIVATION_FILE = CORE01_14_ACTIVATION_FILE
CORE01_ACTIVATED_STATUS = "CORE01_08_READY_PREDECESSORS_COMPLETED"
CORE01_COMPLETED_STATUS = "CORE01_08_COMPLETED_REST_BLOCKED"
CORE01_09_ACTIVATED_STATUS = "CORE01_09_READY_PREDECESSORS_COMPLETED"
CORE01_09_COMPLETED_STATUS = "CORE01_09_COMPLETED_REST_BLOCKED"
CORE01_10_ACTIVATED_STATUS = "CORE01_10_READY_PREDECESSORS_COMPLETED"
CORE01_10_COMPLETED_STATUS = "CORE01_10_COMPLETED_REST_BLOCKED"
CORE01_11_ACTIVATED_STATUS = "CORE01_11_READY_PREDECESSORS_COMPLETED"
CORE01_11_COMPLETED_STATUS = "CORE01_11_COMPLETED_REST_BLOCKED"
CORE01_12_ACTIVATED_STATUS = "CORE01_12_READY_PREDECESSORS_COMPLETED"
CORE01_12_COMPLETED_STATUS = "CORE01_12_COMPLETED_REST_BLOCKED"
CORE01_13_ACTIVATED_STATUS = "CORE01_13_READY_PREDECESSORS_COMPLETED"
CORE01_13_COMPLETED_STATUS = "CORE01_13_COMPLETED_REST_BLOCKED"
CORE01_14_ACTIVATED_STATUS = "CORE01_14_READY_PREDECESSORS_COMPLETED"
CORE01_14_COMPLETED_STATUS = "CORE01_14_COMPLETED_REST_BLOCKED"
CORE02_ACTIVATED_STATUS = "CORE02_03_READY_L1_CAPABILITY_OVERLAY"
CORE02_COMPLETED_STATUS = "CORE02_03_COMPLETED_REST_BLOCKED"
ACTIVE_STATUSES = {
    CORE01_ACTIVATED_STATUS,
    CORE01_COMPLETED_STATUS,
    CORE01_09_ACTIVATED_STATUS,
    CORE01_09_COMPLETED_STATUS,
    CORE01_10_ACTIVATED_STATUS,
    CORE01_10_COMPLETED_STATUS,
    CORE01_11_ACTIVATED_STATUS,
    CORE01_11_COMPLETED_STATUS,
    CORE01_12_ACTIVATED_STATUS,
    CORE01_12_COMPLETED_STATUS,
    CORE01_13_ACTIVATED_STATUS,
    CORE01_13_COMPLETED_STATUS,
    CORE01_14_ACTIVATED_STATUS,
    CORE01_14_COMPLETED_STATUS,
    CORE02_ACTIVATED_STATUS,
    CORE02_COMPLETED_STATUS,
}
BLOCKED_STATUS = "ALL_PROPOSED_BLOCKED_NOT_ACTUAL_CODE_PRS"
CORE01_08_CODE_PR = 438
CORE01_09_CODE_PR = 444
CORE01_10_CODE_PR = 447
CORE01_11_CODE_PR = 450
CORE01_12_CODE_PR = 453
CORE01_13_CODE_PR = 456
CORE02_03_GATE_PR = 440
CORE02_03_CODE_PR = 441
PACKET = re.compile(r"^NLE-PRPLAN-([A-Z]+-[0-9]{2})-([0-9]{2})$")

CORE01_PINNED_SOURCE_BLOBS = {
    "checkpoint": "9241c67f35a149b9070dd23007536f1370d4d5dd",
    "decisions_ledger": "01aa967790dc1ea5e72c2ebebae7b832ec579981",
    "scope": "0b65820507d946d2b2b4ed3a2b869e60cafaaf22",
    "definition_of_done": "e0b7c2466ebec9790a715e47490c015cfb502db4",
    "adr_0003": "50d028c7a28acc25164256c5f4547c14ac7192d4",
    "adr_0083": "82d4968e37f0400f092e885d9fe201df772f4719",
    "adr_0084": "15067edecb676996c08949f9e0c1e7dc02bb5273",
    "adr_0085": "e4ba773dadd33a4fa439a8da988eac02850c2d2a",
    "contract_v0": "4ea41263bcfd412ca35df2abb32a158706b64e48",
    "process_paths_contract": "e551ad7b3c8112f79b88a65c33050059762b71fc",
    "sdl3_contract": "841bff9de1caa9f8d995599a02d46ba7bf0ff470",
    "window_contract": "5bf7eaee2d0aea3f0dc4cc89a419f79f8442b479",
}

CORE01_ACTIVATION_SOURCES = {
    "checkpoint": "docs/11-checkpoint.md",
    "decisions_ledger": "docs/10-decisions-ledger.md",
    "scope": "docs/03-scope.md",
    "definition_of_done": "docs/09-definition-of-done.md",
    "adr_0003": "docs/adr/0003-core-01-platform-technology.md",
    "adr_0083": "docs/adr/0083-core-01-internal-headless-slice.md",
    "adr_0084": "docs/adr/0084-core-01-sdl3-runtime-slice.md",
    "adr_0085": "docs/adr/0085-core-01-window-lifecycle-slice.md",
    "contract_v0": "docs/contracts/core-01-internal-headless-v0.md",
    "process_paths_contract": "docs/contracts/core-01-process-paths-v0.md",
    "sdl3_contract": "docs/contracts/core-01-sdl3-runtime-v0.md",
    "window_contract": "docs/contracts/core-01-window-lifecycle-v0.md",
}

CORE01_09_PINNED_SOURCE_BLOBS = {
    "checkpoint": "cb240cae5608641f85cd8552c2e7259142670b65",
    "decisions_ledger": "01aa967790dc1ea5e72c2ebebae7b832ec579981",
    "scope": "0b65820507d946d2b2b4ed3a2b869e60cafaaf22",
    "definition_of_done": "e0b7c2466ebec9790a715e47490c015cfb502db4",
    "adr_0003": "50d028c7a28acc25164256c5f4547c14ac7192d4",
    "adr_0085": "e4ba773dadd33a4fa439a8da988eac02850c2d2a",
    "adr_0088": "c0a0d8b3f53ffa5ce7e537cb1b58a9778f013d97",
    "core01_architecture": "11c7ec4125f40cf0172aa552a1e9835e84d2c172",
    "sdl3_contract": "841bff9de1caa9f8d995599a02d46ba7bf0ff470",
    "window_contract": "5bf7eaee2d0aea3f0dc4cc89a419f79f8442b479",
    "event_queue_contract": "7d8659ccf5235d36fc2d982589c16f5b8574ac5d",
    "core01_plan": "88a144291b4149109cf2f90907cd724bde196651",
    "implementation_registry": "abbf8e5f971b8de5d73f55c9ec5a0bd7a2632024",
}

CORE01_09_ACTIVATION_SOURCES = {
    "checkpoint": "docs/11-checkpoint.md",
    "decisions_ledger": "docs/10-decisions-ledger.md",
    "scope": "docs/03-scope.md",
    "definition_of_done": "docs/09-definition-of-done.md",
    "adr_0003": "docs/adr/0003-core-01-platform-technology.md",
    "adr_0085": "docs/adr/0085-core-01-window-lifecycle-slice.md",
    "adr_0088": "docs/adr/0088-core-01-event-queue-slice.md",
    "core01_architecture": "docs/architecture/core-01-platform-lifecycle.md",
    "sdl3_contract": "docs/contracts/core-01-sdl3-runtime-v0.md",
    "window_contract": "docs/contracts/core-01-window-lifecycle-v0.md",
    "event_queue_contract": "docs/contracts/core-01-event-queue-v0.md",
    "core01_plan": "docs/pr-plans/CORE-01.md",
    "implementation_registry": "docs/queue/implementation-registry.json",
}

CORE01_10_PINNED_SOURCE_BLOBS = {
    "checkpoint": "e1fa38bc5876feaa3c1076039a075a34234b92bc",
    "decisions_ledger": "01aa967790dc1ea5e72c2ebebae7b832ec579981",
    "scope": "0b65820507d946d2b2b4ed3a2b869e60cafaaf22",
    "definition_of_done": "e0b7c2466ebec9790a715e47490c015cfb502db4",
    "adr_0003": "50d028c7a28acc25164256c5f4547c14ac7192d4",
    "adr_0085": "e4ba773dadd33a4fa439a8da988eac02850c2d2a",
    "adr_0088": "c0a0d8b3f53ffa5ce7e537cb1b58a9778f013d97",
    "adr_0089": "3f6913b3bd1bd23215337d72b13101cca57ec66f",
    "core01_architecture": "11c7ec4125f40cf0172aa552a1e9835e84d2c172",
    "sdl3_contract": "841bff9de1caa9f8d995599a02d46ba7bf0ff470",
    "window_contract": "5bf7eaee2d0aea3f0dc4cc89a419f79f8442b479",
    "event_queue_contract": "7d8659ccf5235d36fc2d982589c16f5b8574ac5d",
    "display_contract": "dbcff81eb6e5442154c564609c7a8234a23803e9",
    "core01_plan": "88a144291b4149109cf2f90907cd724bde196651",
    "implementation_registry": "abbf8e5f971b8de5d73f55c9ec5a0bd7a2632024",
}

CORE01_10_ACTIVATION_SOURCES = {
    "checkpoint": "docs/11-checkpoint.md",
    "decisions_ledger": "docs/10-decisions-ledger.md",
    "scope": "docs/03-scope.md",
    "definition_of_done": "docs/09-definition-of-done.md",
    "adr_0003": "docs/adr/0003-core-01-platform-technology.md",
    "adr_0085": "docs/adr/0085-core-01-window-lifecycle-slice.md",
    "adr_0088": "docs/adr/0088-core-01-event-queue-slice.md",
    "adr_0089": "docs/adr/0089-core-01-display-surface-slice.md",
    "core01_architecture": "docs/architecture/core-01-platform-lifecycle.md",
    "sdl3_contract": "docs/contracts/core-01-sdl3-runtime-v0.md",
    "window_contract": "docs/contracts/core-01-window-lifecycle-v0.md",
    "event_queue_contract": "docs/contracts/core-01-event-queue-v0.md",
    "display_contract": "docs/contracts/core-01-display-surface-v0.md",
    "core01_plan": "docs/pr-plans/CORE-01.md",
    "implementation_registry": "docs/queue/implementation-registry.json",
}

CORE01_11_PINNED_SOURCE_BLOBS = {
    "checkpoint": "dfc85a6b8b8a27cb50a735b2f502b0d955be339c",
    "decisions_ledger": "01aa967790dc1ea5e72c2ebebae7b832ec579981",
    "scope": "0b65820507d946d2b2b4ed3a2b869e60cafaaf22",
    "definition_of_done": "e0b7c2466ebec9790a715e47490c015cfb502db4",
    "adr_0003": "50d028c7a28acc25164256c5f4547c14ac7192d4",
    "adr_0085": "e4ba773dadd33a4fa439a8da988eac02850c2d2a",
    "adr_0088": "c0a0d8b3f53ffa5ce7e537cb1b58a9778f013d97",
    "adr_0089": "3f6913b3bd1bd23215337d72b13101cca57ec66f",
    "adr_0090": "5648a33812b9bfaedf149b930b74fc389698715a",
    "core01_architecture": "11c7ec4125f40cf0172aa552a1e9835e84d2c172",
    "sdl3_contract": "841bff9de1caa9f8d995599a02d46ba7bf0ff470",
    "window_contract": "5bf7eaee2d0aea3f0dc4cc89a419f79f8442b479",
    "event_queue_contract": "7d8659ccf5235d36fc2d982589c16f5b8574ac5d",
    "display_contract": "dbcff81eb6e5442154c564609c7a8234a23803e9",
    "native_bridge_contract": "1c2f9bd140676282bfaad3f963a86b3d58b401c0",
    "core01_plan": "88a144291b4149109cf2f90907cd724bde196651",
    "implementation_registry": "abbf8e5f971b8de5d73f55c9ec5a0bd7a2632024",
}

CORE01_11_ACTIVATION_SOURCES = {
    "checkpoint": "docs/11-checkpoint.md",
    "decisions_ledger": "docs/10-decisions-ledger.md",
    "scope": "docs/03-scope.md",
    "definition_of_done": "docs/09-definition-of-done.md",
    "adr_0003": "docs/adr/0003-core-01-platform-technology.md",
    "adr_0085": "docs/adr/0085-core-01-window-lifecycle-slice.md",
    "adr_0088": "docs/adr/0088-core-01-event-queue-slice.md",
    "adr_0089": "docs/adr/0089-core-01-display-surface-slice.md",
    "adr_0090": "docs/adr/0090-core-01-native-window-handle-bridge.md",
    "core01_architecture": "docs/architecture/core-01-platform-lifecycle.md",
    "sdl3_contract": "docs/contracts/core-01-sdl3-runtime-v0.md",
    "window_contract": "docs/contracts/core-01-window-lifecycle-v0.md",
    "event_queue_contract": "docs/contracts/core-01-event-queue-v0.md",
    "display_contract": "docs/contracts/core-01-display-surface-v0.md",
    "native_bridge_contract": "docs/contracts/core-01-native-window-handle-v0.md",
    "core01_plan": "docs/pr-plans/CORE-01.md",
    "implementation_registry": "docs/queue/implementation-registry.json",
}

CORE01_14_PINNED_SOURCE_BLOBS = {
    "checkpoint": "bded66f9fec96e626c2b5e8cdce929105e0792cb",
    "decisions_ledger": "01aa967790dc1ea5e72c2ebebae7b832ec579981",
    "scope": "0b65820507d946d2b2b4ed3a2b869e60cafaaf22",
    "definition_of_done": "e0b7c2466ebec9790a715e47490c015cfb502db4",
    "adr_0003": "50d028c7a28acc25164256c5f4547c14ac7192d4",
    "adr_0093": "6e8ec9df917c2f3bfdd7772fe10bdb102c47ec42",
    "core01_architecture": "11c7ec4125f40cf0172aa552a1e9835e84d2c172",
    "soak_contract": "0136883fbd70602b5e7614f2e49311d32ba92552",
    "core01_plan": "88a144291b4149109cf2f90907cd724bde196651",
    "implementation_registry": "abbf8e5f971b8de5d73f55c9ec5a0bd7a2632024",
}

CORE01_14_ACTIVATION_SOURCES = {
    "checkpoint": "docs/11-checkpoint.md",
    "decisions_ledger": "docs/10-decisions-ledger.md",
    "scope": "docs/03-scope.md",
    "definition_of_done": "docs/09-definition-of-done.md",
    "adr_0003": "docs/adr/0003-core-01-platform-technology.md",
    "adr_0093": "docs/adr/0093-core-01-multi-os-soak-harness.md",
    "core01_architecture": "docs/architecture/core-01-platform-lifecycle.md",
    "soak_contract": "docs/contracts/core-01-multi-os-soak-v0.md",
    "core01_plan": "docs/pr-plans/CORE-01.md",
    "implementation_registry": "docs/queue/implementation-registry.json",
}

CORE01_13_PINNED_SOURCE_BLOBS = {
    "checkpoint": "85d753cc215ef1eb66767a09b2b247b12ffc0084",
    "decisions_ledger": "01aa967790dc1ea5e72c2ebebae7b832ec579981",
    "scope": "0b65820507d946d2b2b4ed3a2b869e60cafaaf22",
    "definition_of_done": "e0b7c2466ebec9790a715e47490c015cfb502db4",
    "adr_0003": "50d028c7a28acc25164256c5f4547c14ac7192d4",
    "adr_0092": "011113a1b6485fff424c11bf9cdd2c145090ba3d",
    "core01_architecture": "11c7ec4125f40cf0172aa552a1e9835e84d2c172",
    "sdl3_contract": "841bff9de1caa9f8d995599a02d46ba7bf0ff470",
    "capability_contract": "d1d9ab515a1be13532053666b25a498f9d812e0f",
    "core01_plan": "88a144291b4149109cf2f90907cd724bde196651",
    "implementation_registry": "abbf8e5f971b8de5d73f55c9ec5a0bd7a2632024",
}

CORE01_13_ACTIVATION_SOURCES = {
    "checkpoint": "docs/11-checkpoint.md",
    "decisions_ledger": "docs/10-decisions-ledger.md",
    "scope": "docs/03-scope.md",
    "definition_of_done": "docs/09-definition-of-done.md",
    "adr_0003": "docs/adr/0003-core-01-platform-technology.md",
    "adr_0092": "docs/adr/0092-core-01-capability-graph-prototype.md",
    "core01_architecture": "docs/architecture/core-01-platform-lifecycle.md",
    "sdl3_contract": "docs/contracts/core-01-sdl3-runtime-v0.md",
    "capability_contract": "docs/contracts/core-01-capability-graph-v0.md",
    "core01_plan": "docs/pr-plans/CORE-01.md",
    "implementation_registry": "docs/queue/implementation-registry.json",
}

CORE01_12_PINNED_SOURCE_BLOBS = {
    "checkpoint": "5c0b7e4fe5a0121c533be73fad2e0e22b913ab7d",
    "decisions_ledger": "01aa967790dc1ea5e72c2ebebae7b832ec579981",
    "scope": "0b65820507d946d2b2b4ed3a2b869e60cafaaf22",
    "definition_of_done": "e0b7c2466ebec9790a715e47490c015cfb502db4",
    "adr_0003": "50d028c7a28acc25164256c5f4547c14ac7192d4",
    "adr_0088": "c0a0d8b3f53ffa5ce7e537cb1b58a9778f013d97",
    "adr_0091": "ef717de769255cdf9d68ee82d70a8dbc51ca7687",
    "core01_architecture": "11c7ec4125f40cf0172aa552a1e9835e84d2c172",
    "event_queue_contract": "7d8659ccf5235d36fc2d982589c16f5b8574ac5d",
    "lifecycle_contract": "173a328ac8a1fa802f68519dcf2332743a1fbec7",
    "core01_plan": "88a144291b4149109cf2f90907cd724bde196651",
    "implementation_registry": "abbf8e5f971b8de5d73f55c9ec5a0bd7a2632024",
}

CORE01_12_ACTIVATION_SOURCES = {
    "checkpoint": "docs/11-checkpoint.md",
    "decisions_ledger": "docs/10-decisions-ledger.md",
    "scope": "docs/03-scope.md",
    "definition_of_done": "docs/09-definition-of-done.md",
    "adr_0003": "docs/adr/0003-core-01-platform-technology.md",
    "adr_0088": "docs/adr/0088-core-01-event-queue-slice.md",
    "adr_0091": "docs/adr/0091-core-01-lifecycle-request-state-machine.md",
    "core01_architecture": "docs/architecture/core-01-platform-lifecycle.md",
    "event_queue_contract": "docs/contracts/core-01-event-queue-v0.md",
    "lifecycle_contract": "docs/contracts/core-01-lifecycle-requests-v0.md",
    "core01_plan": "docs/pr-plans/CORE-01.md",
    "implementation_registry": "docs/queue/implementation-registry.json",
}

CORE02_PINNED_SOURCE_BLOBS = {
    "checkpoint": "cfa158f175f82d79c91e6cb825bf8c341c1e5ff3",
    "decisions_ledger": "01aa967790dc1ea5e72c2ebebae7b832ec579981",
    "scope": "0b65820507d946d2b2b4ed3a2b869e60cafaaf22",
    "definition_of_done": "e0b7c2466ebec9790a715e47490c015cfb502db4",
    "adr_0004": "e6c1639a96d6d484385476358bde50b38cc5b2ec",
    "adr_0086": "76e3160fa75770d97bf444171a5188cceee39e3c",
    "adr_0087": "fb93a02bc07c8ecfdc70953aff33783d508ef1e2",
    "core02_architecture": "f2b531fc1d2814d51ce59a136ed60320343a5625",
    "core02_contract": "897546dab541cab50a0c5d9f4ec1b7a0c5ef360f",
    "core01_headless_contract": "4ea41263bcfd412ca35df2abb32a158706b64e48",
    "core01_paths_contract": "e551ad7b3c8112f79b88a65c33050059762b71fc",
    "core01_sdl3_contract": "841bff9de1caa9f8d995599a02d46ba7bf0ff470",
    "core01_window_contract": "5bf7eaee2d0aea3f0dc4cc89a419f79f8442b479",
    "core02_plan": "73901b368e5583c087254cf901bc4379b05deca3",
    "implementation_registry": "abbf8e5f971b8de5d73f55c9ec5a0bd7a2632024",
}

CORE02_ACTIVATION_SOURCES = {
    "checkpoint": "docs/11-checkpoint.md",
    "decisions_ledger": "docs/10-decisions-ledger.md",
    "scope": "docs/03-scope.md",
    "definition_of_done": "docs/09-definition-of-done.md",
    "adr_0004": "docs/adr/0004-core-02-memory-policy.md",
    "adr_0086": "docs/adr/0086-capability-based-l1-dependency.md",
    "adr_0087": "docs/adr/0087-core-02-ownership-slice.md",
    "core02_architecture": "docs/architecture/core-02-memory-allocators.md",
    "core02_contract": "docs/contracts/core-02-ownership-v0.md",
    "core01_headless_contract": "docs/contracts/core-01-internal-headless-v0.md",
    "core01_paths_contract": "docs/contracts/core-01-process-paths-v0.md",
    "core01_sdl3_contract": "docs/contracts/core-01-sdl3-runtime-v0.md",
    "core01_window_contract": "docs/contracts/core-01-window-lifecycle-v0.md",
    "core02_plan": "docs/pr-plans/CORE-02.md",
    "implementation_registry": "docs/queue/implementation-registry.json",
}

CORE02_CAPABILITY_ADMISSION = {
    "adr": "docs/adr/0086-capability-based-l1-dependency.md",
    "formal_dependency": "CORE-01",
    "module_completion_claimed": False,
    "required_capabilities": [
        {"id": "CORE01_HEADLESS_BUILD_AND_TEST", "satisfied_by": "NLE-PRPLAN-CORE-01-03"},
        {"id": "CORE01_PORTABLE_PATHS", "satisfied_by": "NLE-PRPLAN-CORE-01-06"},
        {"id": "CORE01_SDL3_BUILD_BASELINE", "satisfied_by": "NLE-PRPLAN-CORE-01-07"},
        {"id": "CORE01_NATIVE_CI_MATRIX", "satisfied_by": "NLE-PRPLAN-CORE-01-08"},
    ],
    "not_required": [
        "window_runtime",
        "input",
        "dpi",
        "ime",
        "hotplug",
        "sleep_resume",
        "soak",
        "renderer",
        "gpu",
        "audio",
        "network",
        "public_abi",
        "release",
    ],
}

# Compatibility aliases for the current CORE-02 activation and existing tooling.
ACTIVATED_STATUS = CORE02_ACTIVATED_STATUS
COMPLETED_STATUS = CORE02_COMPLETED_STATUS
PINNED_SOURCE_BLOBS = CORE02_PINNED_SOURCE_BLOBS
ACTIVATION_SOURCES = CORE02_ACTIVATION_SOURCES

SLICE_METADATA = {
    3: ("docs/adr/0083-core-01-internal-headless-slice.md",
        "docs/evidence/NLE-PRPLAN-CORE-01-03-G6-ACTIVATION.md"),
    4: ("docs/adr/0083-core-01-internal-headless-slice.md",
        "docs/evidence/NLE-PRPLAN-CORE-01-06-G6-ACTIVATION.md"),
    5: ("docs/adr/0083-core-01-internal-headless-slice.md",
        "docs/evidence/NLE-PRPLAN-CORE-01-06-G6-ACTIVATION.md"),
    6: ("docs/adr/0083-core-01-internal-headless-slice.md",
        "docs/evidence/NLE-PRPLAN-CORE-01-06-G6-ACTIVATION.md"),
    7: ("docs/adr/0084-core-01-sdl3-runtime-slice.md",
        "docs/evidence/NLE-PRPLAN-CORE-01-07-G6-ACTIVATION.md"),
    8: ("docs/adr/0085-core-01-window-lifecycle-slice.md",
        "docs/evidence/NLE-PRPLAN-CORE-01-08-G6-ACTIVATION.md"),
    9: ("docs/adr/0088-core-01-event-queue-slice.md",
        "docs/evidence/NLE-PRPLAN-CORE-01-09-G6-ACTIVATION.md"),
    10: ("docs/adr/0089-core-01-display-surface-slice.md",
         "docs/evidence/NLE-PRPLAN-CORE-01-10-G6-ACTIVATION.md"),
    11: ("docs/adr/0090-core-01-native-window-handle-bridge.md",
         "docs/evidence/NLE-PRPLAN-CORE-01-11-G6-ACTIVATION.md"),
    12: ("docs/adr/0091-core-01-lifecycle-request-state-machine.md",
         "docs/evidence/NLE-PRPLAN-CORE-01-12-G6-ACTIVATION.md"),
    13: ("docs/adr/0092-core-01-capability-graph-prototype.md",
         "docs/evidence/NLE-PRPLAN-CORE-01-13-G6-ACTIVATION.md"),
    14: ("docs/adr/0093-core-01-multi-os-soak-harness.md",
         "docs/evidence/NLE-PRPLAN-CORE-01-14-G6-ACTIVATION.md"),
}

CORE02_SLICE_METADATA = {
    3: ("docs/adr/0087-core-02-ownership-slice.md",
        "docs/evidence/NLE-PRPLAN-CORE-02-03-G6-ACTIVATION.md"),
}


def git_blob_sha1(data: bytes) -> str:
    header = b"blob " + str(len(data)).encode("ascii") + b"\0"
    return hashlib.sha1(header + data).hexdigest()


def file_blob_sha1(path: Path) -> str:
    # Match Git's blob identity for LF-normalized repository text on Windows
    # working trees that may materialize CRLF.
    return git_blob_sha1(path.read_bytes().replace(b"\r\n", b"\n"))


def verify_source_blobs(fingerprints: dict, root: Path, sources: dict | None = None) -> list[str]:
    sources = ACTIVATION_SOURCES if sources is None else sources
    errors = []
    for key, rel in sources.items():
        path = root / rel
        try:
            actual = file_blob_sha1(path)
        except OSError as err:
            errors.append(f"activation source missing: {rel}: {err}")
            continue
        if fingerprints.get(key) != actual:
            errors.append(f"activation source drift: {rel} expected {fingerprints.get(key)} got {actual}")
    return errors


def activation_spec(activation: dict) -> tuple[dict, dict, dict, set[str]] | None:
    selected = activation.get("selected_packet_id")
    if selected == "NLE-PRPLAN-CORE-01-08":
        expected = {
            "schema_version": 2,
            "status": "OWNER_RATIFIED_BOUNDED_G6_ACTIVATION",
            "selected_packet_id": "NLE-PRPLAN-CORE-01-08",
            "module_id": "CORE-01",
            "risk": "STANDARD",
            "release_class": "INTERNAL_ONLY",
            "owner_authorization_ref": "STORM-CORE-01-IMPL-001/issue-387/2026-11-17/next-increments",
            "approved_adr": "docs/adr/0085-core-01-window-lifecycle-slice.md",
            "approved_contract": "docs/contracts/core-01-window-lifecycle-v0.md",
            "work_order": "docs/work-orders/NLE-PRPLAN-CORE-01-08.md",
            "activation_evidence": "docs/evidence/NLE-PRPLAN-CORE-01-08-G6-ACTIVATION.md",
            "gate_base_sha": "b54f19c252fda9c06a7d7289a853bd4cf957cf53",
            "requires_fresh_context_lock": True,
        }
        return expected, CORE01_ACTIVATION_SOURCES, CORE01_PINNED_SOURCE_BLOBS, {
            "source_blob_sha1", "sdl3", "window_slice"
        }
    if selected == "NLE-PRPLAN-CORE-01-14":
        expected = {
            "schema_version": 2,
            "status": "OWNER_RATIFIED_BOUNDED_G6_ACTIVATION",
            "selected_packet_id": "NLE-PRPLAN-CORE-01-14",
            "module_id": "CORE-01",
            "risk": "STANDARD",
            "release_class": "INTERNAL_ONLY",
            "owner_authorization_ref": "STORM-CORE-01-IMPL-001/issue-387/2026-11-17/next-increments",
            "approved_adr": "docs/adr/0093-core-01-multi-os-soak-harness.md",
            "approved_contract": "docs/contracts/core-01-multi-os-soak-v0.md",
            "work_order": "docs/work-orders/NLE-PRPLAN-CORE-01-14.md",
            "activation_evidence": "docs/evidence/NLE-PRPLAN-CORE-01-14-G6-ACTIVATION.md",
            "gate_base_sha": "9bfbed5901947a3073b2910a48b4c9873702d37f",
            "requires_fresh_context_lock": True,
        }
        return expected, CORE01_14_ACTIVATION_SOURCES, CORE01_14_PINNED_SOURCE_BLOBS, {
            "source_blob_sha1", "gate_pr"
        }
    if selected == "NLE-PRPLAN-CORE-01-13":
        expected = {
            "schema_version": 2,
            "status": "OWNER_RATIFIED_BOUNDED_G6_ACTIVATION",
            "selected_packet_id": "NLE-PRPLAN-CORE-01-13",
            "module_id": "CORE-01",
            "risk": "STANDARD",
            "release_class": "INTERNAL_ONLY",
            "owner_authorization_ref": "STORM-CORE-01-IMPL-001/issue-387/2026-11-17/next-increments",
            "approved_adr": "docs/adr/0092-core-01-capability-graph-prototype.md",
            "approved_contract": "docs/contracts/core-01-capability-graph-v0.md",
            "work_order": "docs/work-orders/NLE-PRPLAN-CORE-01-13.md",
            "activation_evidence": "docs/evidence/NLE-PRPLAN-CORE-01-13-G6-ACTIVATION.md",
            "gate_base_sha": "967e136d517c6d78430bcde1fd66ef97a283efe5",
            "requires_fresh_context_lock": True,
        }
        return expected, CORE01_13_ACTIVATION_SOURCES, CORE01_13_PINNED_SOURCE_BLOBS, {
            "source_blob_sha1", "gate_pr", "sdl3"
        }
    if selected == "NLE-PRPLAN-CORE-01-12":
        expected = {
            "schema_version": 2,
            "status": "OWNER_RATIFIED_BOUNDED_G6_ACTIVATION",
            "selected_packet_id": "NLE-PRPLAN-CORE-01-12",
            "module_id": "CORE-01",
            "risk": "STANDARD",
            "release_class": "INTERNAL_ONLY",
            "owner_authorization_ref": "STORM-CORE-01-IMPL-001/issue-387/2026-11-17/next-increments",
            "approved_adr": "docs/adr/0091-core-01-lifecycle-request-state-machine.md",
            "approved_contract": "docs/contracts/core-01-lifecycle-requests-v0.md",
            "work_order": "docs/work-orders/NLE-PRPLAN-CORE-01-12.md",
            "activation_evidence": "docs/evidence/NLE-PRPLAN-CORE-01-12-G6-ACTIVATION.md",
            "gate_base_sha": "df551006982868e616d867c7daaa3fc5a7c51ee8",
            "requires_fresh_context_lock": True,
        }
        return expected, CORE01_12_ACTIVATION_SOURCES, CORE01_12_PINNED_SOURCE_BLOBS, {
            "source_blob_sha1", "gate_pr"
        }
    if selected == "NLE-PRPLAN-CORE-01-11":
        expected = {
            "schema_version": 2,
            "status": "OWNER_RATIFIED_BOUNDED_G6_ACTIVATION",
            "selected_packet_id": "NLE-PRPLAN-CORE-01-11",
            "module_id": "CORE-01",
            "risk": "STANDARD",
            "release_class": "INTERNAL_ONLY",
            "owner_authorization_ref": "STORM-CORE-01-IMPL-001/issue-387/2026-11-17/next-increments",
            "approved_adr": "docs/adr/0090-core-01-native-window-handle-bridge.md",
            "approved_contract": "docs/contracts/core-01-native-window-handle-v0.md",
            "work_order": "docs/work-orders/NLE-PRPLAN-CORE-01-11.md",
            "activation_evidence": "docs/evidence/NLE-PRPLAN-CORE-01-11-G6-ACTIVATION.md",
            "gate_base_sha": "44b37d4b6e67314e7317257707a3064bd69c6830",
            "requires_fresh_context_lock": True,
        }
        return expected, CORE01_11_ACTIVATION_SOURCES, CORE01_11_PINNED_SOURCE_BLOBS, {
            "source_blob_sha1", "gate_pr", "sdl3"
        }
    if selected == "NLE-PRPLAN-CORE-01-10":
        expected = {
            "schema_version": 2,
            "status": "OWNER_RATIFIED_BOUNDED_G6_ACTIVATION",
            "selected_packet_id": "NLE-PRPLAN-CORE-01-10",
            "module_id": "CORE-01",
            "risk": "STANDARD",
            "release_class": "INTERNAL_ONLY",
            "owner_authorization_ref": "STORM-CORE-01-IMPL-001/issue-387/2026-11-17/next-increments",
            "approved_adr": "docs/adr/0089-core-01-display-surface-slice.md",
            "approved_contract": "docs/contracts/core-01-display-surface-v0.md",
            "work_order": "docs/work-orders/NLE-PRPLAN-CORE-01-10.md",
            "activation_evidence": "docs/evidence/NLE-PRPLAN-CORE-01-10-G6-ACTIVATION.md",
            "gate_base_sha": "7e42b48f19272498c732d75f2051704f5b82311f",
            "requires_fresh_context_lock": True,
        }
        return expected, CORE01_10_ACTIVATION_SOURCES, CORE01_10_PINNED_SOURCE_BLOBS, {
            "source_blob_sha1", "gate_pr", "sdl3"
        }
    if selected == "NLE-PRPLAN-CORE-01-09":
        expected = {
            "schema_version": 2,
            "status": "OWNER_RATIFIED_BOUNDED_G6_ACTIVATION",
            "selected_packet_id": "NLE-PRPLAN-CORE-01-09",
            "module_id": "CORE-01",
            "risk": "STANDARD",
            "release_class": "INTERNAL_ONLY",
            "owner_authorization_ref": "STORM-CORE-01-IMPL-001/issue-387/2026-11-17/next-increments",
            "approved_adr": "docs/adr/0088-core-01-event-queue-slice.md",
            "approved_contract": "docs/contracts/core-01-event-queue-v0.md",
            "work_order": "docs/work-orders/NLE-PRPLAN-CORE-01-09.md",
            "activation_evidence": "docs/evidence/NLE-PRPLAN-CORE-01-09-G6-ACTIVATION.md",
            "gate_base_sha": "27cd592ec235a63def60f04757ac27700babd334",
            "requires_fresh_context_lock": True,
        }
        return expected, CORE01_09_ACTIVATION_SOURCES, CORE01_09_PINNED_SOURCE_BLOBS, {
            "source_blob_sha1", "gate_pr", "sdl3"
        }
    if selected == "NLE-PRPLAN-CORE-02-03":
        expected = {
            "schema_version": 2,
            "status": "OWNER_RATIFIED_BOUNDED_G6_ACTIVATION",
            "selected_packet_id": "NLE-PRPLAN-CORE-02-03",
            "module_id": "CORE-02",
            "risk": "STANDARD",
            "release_class": "INTERNAL_ONLY",
            "owner_authorization_ref": "STORM-CORE-01-IMPL-001/issue-387/2026-11-17/next-increments",
            "approved_adr": "docs/adr/0087-core-02-ownership-slice.md",
            "approved_contract": "docs/contracts/core-02-ownership-v0.md",
            "work_order": "docs/work-orders/NLE-PRPLAN-CORE-02-03.md",
            "activation_evidence": "docs/evidence/NLE-PRPLAN-CORE-02-03-G6-ACTIVATION.md",
            "gate_base_sha": "bb7229496a5c015ae4d2e31be444381cefc49c1f",
            "requires_fresh_context_lock": True,
        }
        return expected, CORE02_ACTIVATION_SOURCES, CORE02_PINNED_SOURCE_BLOBS, {
            "source_blob_sha1", "gate_pr", "capability_admission"
        }
    return None


def validate_activation(activation: dict, root: Path = ROOT, verify_sources: bool = False) -> list[str]:
    """Hard-stop on a broad or forged G6 transition. Only the audited packet is authorized."""
    spec = activation_spec(activation)
    if spec is None:
        return ["activation selected packet is not an audited G6 packet"]
    expected, sources, pinned, extra_keys = spec
    errors = []
    if set(activation) != set(expected) | extra_keys:
        errors.append("activation keys must match exactly one audited G6 packet")
    for key, value in expected.items():
        if activation.get(key) != value:
            errors.append(f"activation {key} mismatch: no bulk owner authority")
    if "gate_pr" in extra_keys:
        gate_pr = activation.get("gate_pr")
        if not isinstance(gate_pr, int) or gate_pr < 0:
            errors.append("activation gate_pr must be a non-negative integer")
    if "sdl3" in extra_keys:
        expected_sdl3 = {
            "version": "3.4.20",
            "repository": "https://github.com/libsdl-org/SDL.git",
            "commit": "f00dc919ca35b9756316e86c4777392de442f9b2",
            "license": "zlib",
            "linkage": "static",
            "build_time_fetch": True,
        }
        if activation.get("sdl3") != expected_sdl3:
            errors.append("activation SDL3 pin mismatch: only static 3.4.20 at the exact commit is authorized")
    if "window_slice" in extra_keys:
        expected_window_slice = {
            "linux_drivers_built": ["x11", "wayland"],
            "linux_runtime_tested": "x11",
            "linux_runtime_not_qualified": "wayland",
            "windows_runtime": "win32",
            "macos_runtime": "cocoa_or_not_qualified",
            "linux_display": "xvfb+openbox",
            "render_gpu_audio": "disabled",
            "linux_packages": [
                "libx11-dev",
                "libxext-dev",
                "libxrandr-dev",
                "libxcursor-dev",
                "libxfixes-dev",
                "libxi-dev",
                "libxss-dev",
                "libxtst-dev",
                "libxinerama-dev",
                "libxrender-dev",
                "libxkbcommon-dev",
                "libxkbcommon-x11-dev",
                "libwayland-dev",
                "libdecor-0-dev",
                "wayland-protocols",
                "libdbus-1-dev",
                "libibus-1.0-dev",
                "libthai-dev",
                "libfribidi-dev",
                "libgl1-mesa-dev",
                "libegl1-mesa-dev",
                "libgles2-mesa-dev",
                "xvfb",
                "x11-utils",
                "openbox",
            ],
        }
        if activation.get("window_slice") != expected_window_slice:
            errors.append("activation window slice mismatch: only the exact X11/Win32/Cocoa install matrix is authorized")
    if "capability_admission" in extra_keys:
        if activation.get("capability_admission") != CORE02_CAPABILITY_ADMISSION:
            errors.append("activation capability admission mismatch: only the exact CORE-02 ownership set is authorized")
    fingerprints = activation.get("source_blob_sha1")
    if not isinstance(fingerprints, dict) or set(fingerprints) != set(sources):
        errors.append("activation source_blob_sha1 must contain exactly the pinned sources")
    elif fingerprints != pinned:
        errors.append("activation source fingerprints do not match approved baseline")
    elif verify_sources:
        errors.extend(verify_source_blobs(fingerprints, root, sources))
    return errors


def expected_packet_state(
    module_id: str, idx: int, activation: dict | None, manifest_status: str | None
) -> tuple[str, int | None]:
    if activation is not None and module_id == "CORE-01":
        if idx == 1:
            return "APPROVED_GOVERNANCE", 422
        if idx == 2:
            return "APPROVED_CONTRACT", 424
        if idx in (3, 4, 5):
            return "COMPLETED", 428
        if idx == 6:
            return "COMPLETED", 432
        if idx == 7:
            return "COMPLETED", 435
        if idx == 8:
            if manifest_status in (CORE01_COMPLETED_STATUS, CORE01_09_ACTIVATED_STATUS,
                                   CORE01_09_COMPLETED_STATUS, CORE01_10_ACTIVATED_STATUS,
                                   CORE01_10_COMPLETED_STATUS, CORE01_11_ACTIVATED_STATUS,
                                   CORE01_11_COMPLETED_STATUS, CORE01_12_ACTIVATED_STATUS,
                                   CORE01_12_COMPLETED_STATUS, CORE01_13_ACTIVATED_STATUS,
                                   CORE01_13_COMPLETED_STATUS, CORE01_14_ACTIVATED_STATUS,
                                   CORE01_14_COMPLETED_STATUS, CORE02_ACTIVATED_STATUS,
                                   CORE02_COMPLETED_STATUS):
                return "COMPLETED", CORE01_08_CODE_PR
            return "EXECUTOR_READY", None
        if idx == 9:
            if manifest_status in (CORE01_09_COMPLETED_STATUS, CORE01_10_ACTIVATED_STATUS,
                                   CORE01_10_COMPLETED_STATUS, CORE01_11_ACTIVATED_STATUS,
                                   CORE01_11_COMPLETED_STATUS, CORE01_12_ACTIVATED_STATUS,
                                   CORE01_12_COMPLETED_STATUS, CORE01_13_ACTIVATED_STATUS,
                                   CORE01_13_COMPLETED_STATUS, CORE01_14_ACTIVATED_STATUS,
                                   CORE01_14_COMPLETED_STATUS):
                return "COMPLETED", CORE01_09_CODE_PR
            if manifest_status == CORE01_09_ACTIVATED_STATUS:
                return "EXECUTOR_READY", None
        if idx == 10:
            if manifest_status in (CORE01_10_COMPLETED_STATUS, CORE01_11_ACTIVATED_STATUS,
                                   CORE01_11_COMPLETED_STATUS, CORE01_12_ACTIVATED_STATUS,
                                   CORE01_12_COMPLETED_STATUS, CORE01_13_ACTIVATED_STATUS,
                                   CORE01_13_COMPLETED_STATUS, CORE01_14_ACTIVATED_STATUS,
                                   CORE01_14_COMPLETED_STATUS):
                return "COMPLETED", CORE01_10_CODE_PR
            if manifest_status == CORE01_10_ACTIVATED_STATUS:
                return "EXECUTOR_READY", None
        if idx == 11:
            if manifest_status in (CORE01_11_COMPLETED_STATUS, CORE01_12_ACTIVATED_STATUS,
                                   CORE01_12_COMPLETED_STATUS, CORE01_13_ACTIVATED_STATUS,
                                   CORE01_13_COMPLETED_STATUS, CORE01_14_ACTIVATED_STATUS,
                                   CORE01_14_COMPLETED_STATUS):
                return "COMPLETED", CORE01_11_CODE_PR
            if manifest_status == CORE01_11_ACTIVATED_STATUS:
                return "EXECUTOR_READY", None
        if idx == 12:
            if manifest_status in (CORE01_12_COMPLETED_STATUS, CORE01_13_ACTIVATED_STATUS,
                                   CORE01_13_COMPLETED_STATUS, CORE01_14_ACTIVATED_STATUS,
                                   CORE01_14_COMPLETED_STATUS):
                return "COMPLETED", CORE01_12_CODE_PR
            if manifest_status == CORE01_12_ACTIVATED_STATUS:
                return "EXECUTOR_READY", None
        if idx == 13:
            if manifest_status in (CORE01_13_COMPLETED_STATUS, CORE01_14_ACTIVATED_STATUS,
                                   CORE01_14_COMPLETED_STATUS):
                return "COMPLETED", CORE01_13_CODE_PR
            if manifest_status == CORE01_13_ACTIVATED_STATUS:
                return "EXECUTOR_READY", None
        if idx == 14:
            if manifest_status == CORE01_14_COMPLETED_STATUS:
                return "COMPLETED", CORE01_14_CODE_PR
            if manifest_status == CORE01_14_ACTIVATED_STATUS:
                return "EXECUTOR_READY", None
    if activation is not None and module_id == "CORE-02":
        if idx == 1:
            return "APPROVED_GOVERNANCE", CORE02_03_GATE_PR
        if idx == 2:
            return "APPROVED_CONTRACT", CORE02_03_GATE_PR
        if idx == 3:
            if manifest_status == CORE02_ACTIVATED_STATUS:
                return "EXECUTOR_READY", None
            if manifest_status in (CORE02_COMPLETED_STATUS, CORE01_09_ACTIVATED_STATUS,
                                   CORE01_09_COMPLETED_STATUS, CORE01_10_ACTIVATED_STATUS,
                                   CORE01_10_COMPLETED_STATUS, CORE01_11_ACTIVATED_STATUS,
                                   CORE01_11_COMPLETED_STATUS, CORE01_12_ACTIVATED_STATUS,
                                   CORE01_12_COMPLETED_STATUS, CORE01_13_ACTIVATED_STATUS,
                                   CORE01_13_COMPLETED_STATUS, CORE01_14_ACTIVATED_STATUS,
                                   CORE01_14_COMPLETED_STATUS):
                return "COMPLETED", CORE02_03_CODE_PR
    return "PLANNED_BLOCKED", None


def expected_metadata(module_id: str, idx: int) -> tuple[str, str] | None:
    if module_id == "CORE-01" and idx in SLICE_METADATA:
        return SLICE_METADATA[idx]
    if module_id == "CORE-02" and idx in CORE02_SLICE_METADATA:
        return CORE02_SLICE_METADATA[idx]
    return None


def validate_capability_admission(
    packet: dict, status_by_packet: dict[str, str | None], formal_dependency: str
) -> list[str]:
    errors = []
    admission = packet.get("capability_admission")
    if not isinstance(admission, dict):
        return ["CORE-02-03 capability admission must match the audited exact set"]
    if admission != CORE02_CAPABILITY_ADMISSION:
        errors.append("CORE-02-03 capability admission must match the audited exact set")
    if admission.get("formal_dependency") != formal_dependency:
        errors.append("CORE-02-03 capability admission changes the formal module dependency")
    if admission.get("module_completion_claimed") is not False:
        errors.append("CORE-02-03 capability admission must not claim module completion")
    for capability in admission.get("required_capabilities", []):
        if not isinstance(capability, dict) or "satisfied_by" not in capability:
            errors.append("CORE-02-03 capability admission has an invalid capability entry")
            continue
        satisfied_by = capability["satisfied_by"]
        if not isinstance(satisfied_by, str) or not satisfied_by.startswith("NLE-PRPLAN-CORE-01-"):
            errors.append("CORE-02-03 capability admission accepts only CORE-01 packets")
        if status_by_packet.get(satisfied_by) != "COMPLETED":
            errors.append(f"CORE-02-03 capability {capability.get('id')} lacks a completed packet")
    return errors


def packet_readiness(
    manifest: dict, registry: dict, activation: dict | None, packet_id: str, root: Path = ROOT
) -> bool:
    verify_sources = manifest.get("status") in (
        CORE01_ACTIVATED_STATUS, CORE01_09_ACTIVATED_STATUS, CORE01_10_ACTIVATED_STATUS,
        CORE01_11_ACTIVATED_STATUS, CORE01_12_ACTIVATED_STATUS, CORE01_13_ACTIVATED_STATUS,
        CORE01_14_ACTIVATED_STATUS, CORE02_ACTIVATED_STATUS
    )
    if validate_manifest(manifest, registry, activation, root, verify_sources):
        return False
    if activation is None or activation.get("selected_packet_id") != packet_id:
        return False
    matches = [packet for entry in manifest.get("modules", [])
               for packet in entry.get("packets", []) if packet.get("packet_id") == packet_id]
    return len(matches) == 1 and matches[0].get("status") == "EXECUTOR_READY"


def validate_manifest(
    manifest: dict,
    registry: dict,
    activation: dict | None = None,
    root: Path = ROOT,
    verify_sources: bool = False,
) -> list[str]:
    issues: list[str] = []
    source = registry.get("modules", [])
    plans = manifest.get("modules", [])
    if manifest.get("schema_version") != 1 or manifest.get("module_count") != 80:
        issues.append("schema_version=1 and module_count=80 required")
    if activation is None:
        if manifest.get("status") != BLOCKED_STATUS:
            issues.append("manifest must remain blocked without G6 activation")
    else:
        if manifest.get("status") not in ACTIVE_STATUSES:
            issues.append("manifest activation/completion status mismatch")
        issues.extend(validate_activation(activation, root, verify_sources))
    by_id = {x.get("module_id"): x for x in source}
    status_by_packet = {
        packet.get("packet_id"): packet.get("status")
        for entry in plans for packet in entry.get("packets", [])
    }
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
            metadata = expected_metadata(mid, idx)
            if metadata is not None:
                adr, evidence = metadata
                if want_status not in ("EXECUTOR_READY", "COMPLETED"):
                    issues.append(f"{mid}: slice metadata on a non-completed packet")
                elif (packet.get("risk") != "STANDARD"
                      or packet.get("release_class") != "INTERNAL_ONLY"
                      or packet.get("approved_adr") != adr
                      or packet.get("activation_evidence") != evidence):
                    issues.append(f"{mid}: ready/completed slice lacks bounded risk/ADR/evidence")
                if mid == "CORE-02" and idx == 3:
                    issues.extend(validate_capability_admission(
                        packet, status_by_packet, original["dependencies"][0]))
            elif any(field in packet for field in (
                "risk", "release_class", "approved_adr", "activation_evidence",
                "capability_admission"
            )):
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
    statuses = [p.get("status") for entry in plans for p in entry.get("packets", [])]
    approved = statuses.count("APPROVED_GOVERNANCE") + statuses.count("APPROVED_CONTRACT")
    if manifest.get("status") == CORE01_ACTIVATED_STATUS:
        if statuses.count("EXECUTOR_READY") != 1 or statuses.count("COMPLETED") != 5 or approved != 2:
            issues.append("CORE-01 activated state must have one ready packet, five completed slices and two approved gates")
    if manifest.get("status") == CORE01_COMPLETED_STATUS:
        if statuses.count("EXECUTOR_READY") != 0 or statuses.count("COMPLETED") != 6 or approved != 2:
            issues.append("CORE-01 completed state must have zero ready packets, six completed slices and two approved gates")
    if manifest.get("status") == CORE01_09_ACTIVATED_STATUS:
        if statuses.count("EXECUTOR_READY") != 1 or statuses.count("COMPLETED") != 7 or approved != 4:
            issues.append("CORE-01-09 activated state must have one ready packet, seven completed slices and four approved gates")
    if manifest.get("status") == CORE01_09_COMPLETED_STATUS:
        if statuses.count("EXECUTOR_READY") != 0 or statuses.count("COMPLETED") != 8 or approved != 4:
            issues.append("CORE-01-09 completed state must have zero ready packets, eight completed slices and four approved gates")
    if manifest.get("status") == CORE01_10_ACTIVATED_STATUS:
        if statuses.count("EXECUTOR_READY") != 1 or statuses.count("COMPLETED") != 8 or approved != 4:
            issues.append("CORE-01-10 activated state must have one ready packet, eight completed slices and four approved gates")
    if manifest.get("status") == CORE01_10_COMPLETED_STATUS:
        if statuses.count("EXECUTOR_READY") != 0 or statuses.count("COMPLETED") != 9 or approved != 4:
            issues.append("CORE-01-10 completed state must have zero ready packets, nine completed slices and four approved gates")
    if manifest.get("status") == CORE01_11_ACTIVATED_STATUS:
        if statuses.count("EXECUTOR_READY") != 1 or statuses.count("COMPLETED") != 9 or approved != 4:
            issues.append("CORE-01-11 activated state must have one ready packet, nine completed slices and four approved gates")
    if manifest.get("status") == CORE01_11_COMPLETED_STATUS:
        if statuses.count("EXECUTOR_READY") != 0 or statuses.count("COMPLETED") != 10 or approved != 4:
            issues.append("CORE-01-11 completed state must have zero ready packets, ten completed slices and four approved gates")
    if manifest.get("status") == CORE01_12_ACTIVATED_STATUS:
        if statuses.count("EXECUTOR_READY") != 1 or statuses.count("COMPLETED") != 10 or approved != 4:
            issues.append("CORE-01-12 activated state must have one ready packet, ten completed slices and four approved gates")
    if manifest.get("status") == CORE01_12_COMPLETED_STATUS:
        if statuses.count("EXECUTOR_READY") != 0 or statuses.count("COMPLETED") != 11 or approved != 4:
            issues.append("CORE-01-12 completed state must have zero ready packets, eleven completed slices and four approved gates")
    if manifest.get("status") == CORE01_13_ACTIVATED_STATUS:
        if statuses.count("EXECUTOR_READY") != 1 or statuses.count("COMPLETED") != 11 or approved != 4:
            issues.append("CORE-01-13 activated state must have one ready packet, eleven completed slices and four approved gates")
    if manifest.get("status") == CORE01_13_COMPLETED_STATUS:
        if statuses.count("EXECUTOR_READY") != 0 or statuses.count("COMPLETED") != 12 or approved != 4:
            issues.append("CORE-01-13 completed state must have zero ready packets, twelve completed slices and four approved gates")
    if manifest.get("status") == CORE01_14_ACTIVATED_STATUS:
        if statuses.count("EXECUTOR_READY") != 1 or statuses.count("COMPLETED") != 12 or approved != 4:
            issues.append("CORE-01-14 activated state must have one ready packet, twelve completed slices and four approved gates")
    if manifest.get("status") == CORE01_14_COMPLETED_STATUS:
        if statuses.count("EXECUTOR_READY") != 0 or statuses.count("COMPLETED") != 13 or approved != 4:
            issues.append("CORE-01-14 completed state must have zero ready packets, thirteen completed slices and four approved gates")
    if manifest.get("status") == CORE02_ACTIVATED_STATUS:
        if statuses.count("EXECUTOR_READY") != 1 or statuses.count("COMPLETED") != 6 or approved != 4:
            issues.append("CORE-02 activated state must have one ready packet, six completed CORE-01 slices and four approved gates")
    if manifest.get("status") == CORE02_COMPLETED_STATUS:
        if statuses.count("EXECUTOR_READY") != 0 or statuses.count("COMPLETED") != 7 or approved != 4:
            issues.append("CORE-02 completed state must have zero ready packets, seven completed slices and four approved gates")
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
    status = manifest.get("status")
    if status in (CORE01_ACTIVATED_STATUS, CORE01_COMPLETED_STATUS):
        activation_path = root / "docs/queue/packet-activation-core-01-08.json"
    elif status in (CORE01_09_ACTIVATED_STATUS, CORE01_09_COMPLETED_STATUS):
        activation_path = root / "docs/queue/packet-activation-core-01-09.json"
    elif status in (CORE01_10_ACTIVATED_STATUS, CORE01_10_COMPLETED_STATUS):
        activation_path = root / "docs/queue/packet-activation-core-01-10.json"
    elif status in (CORE01_11_ACTIVATED_STATUS, CORE01_11_COMPLETED_STATUS):
        activation_path = root / "docs/queue/packet-activation-core-01-11.json"
    elif status in (CORE01_12_ACTIVATED_STATUS, CORE01_12_COMPLETED_STATUS):
        activation_path = root / "docs/queue/packet-activation-core-01-12.json"
    elif status in (CORE01_13_ACTIVATED_STATUS, CORE01_13_COMPLETED_STATUS):
        activation_path = root / "docs/queue/packet-activation-core-01-13.json"
    elif status in (CORE01_14_ACTIVATED_STATUS, CORE01_14_COMPLETED_STATUS):
        activation_path = root / "docs/queue/packet-activation-core-01-14.json"
    elif status in (CORE02_ACTIVATED_STATUS, CORE02_COMPLETED_STATUS):
        activation_path = root / "docs/queue/packet-activation-core-02-03.json"
    else:
        activation_path = None
    if activation_path is not None:
        try:
            activation = json.loads(activation_path.read_text(encoding="utf-8"))
        except (OSError, UnicodeError, ValueError) as err:
            issues.append(f"Missing/invalid bounded G6 activation record: {err}")
    verify_sources = status in (CORE01_ACTIVATED_STATUS, CORE01_09_ACTIVATED_STATUS,
                                CORE01_10_ACTIVATED_STATUS, CORE01_11_ACTIVATED_STATUS,
                                CORE01_12_ACTIVATED_STATUS, CORE01_13_ACTIVATED_STATUS,
                                CORE01_14_ACTIVATED_STATUS, CORE02_ACTIVATED_STATUS)
    issues.extend(validate_manifest(manifest, reg, activation, root, verify_sources))
    if activation is not None:
        for key in ("approved_adr", "approved_contract", "work_order", "activation_evidence"):
            path = root / activation[key]
            if not path.is_file():
                issues.append(f"G6 evidence file missing: {path}")
        admission = activation.get("capability_admission")
        if isinstance(admission, dict):
            adr_path = root / admission["adr"]
            if not adr_path.is_file():
                issues.append(f"capability admission ADR missing: {adr_path}")
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
    approved = statuses.count("APPROVED_GOVERNANCE") + statuses.count("APPROVED_CONTRACT")
    print(f"PR plan PASS: {data['module_count']} module WOs stay BLOCKED; "
          f"{data['planned_packet_count']} packets: {statuses.count('PLANNED_BLOCKED')} blocked, "
          f"{statuses.count('EXECUTOR_READY')} individually ready, "
          f"{statuses.count('COMPLETED')} completed, {approved} approved gates, "
          f"0 code PRs opened by this validator.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
