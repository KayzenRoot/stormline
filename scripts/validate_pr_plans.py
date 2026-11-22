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
CORE01_15_ACTIVATION_FILE = ROOT / "docs/queue/packet-activation-core-01-15.json"
CORE01_16_ACTIVATION_FILE = ROOT / "docs/queue/packet-activation-core-01-16.json"
CORE02_04_ACTIVATION_FILE = ROOT / "docs/queue/packet-activation-core-02-04.json"
CORE02_05_ACTIVATION_FILE = ROOT / "docs/queue/packet-activation-core-02-05.json"
CORE02_06_ACTIVATION_FILE = ROOT / "docs/queue/packet-activation-core-02-06.json"
CORE02_07_ACTIVATION_FILE = ROOT / "docs/queue/packet-activation-core-02-07.json"
CORE02_08_ACTIVATION_FILE = ROOT / "docs/queue/packet-activation-core-02-08.json"
CORE02_09_ACTIVATION_FILE = ROOT / "docs/queue/packet-activation-core-02-09.json"
CORE02_10_ACTIVATION_FILE = ROOT / "docs/queue/packet-activation-core-02-10.json"
CORE03_01_ACTIVATION_FILE = ROOT / "docs/queue/packet-activation-core-03-01.json"
CORE03_02_ACTIVATION_FILE = ROOT / "docs/queue/packet-activation-core-03-02.json"
CORE03_03_ACTIVATION_FILE = ROOT / "docs/queue/packet-activation-core-03-03.json"
CORE03_09_ACTIVATION_FILE = ROOT / "docs/queue/packet-activation-core-03-09.json"
CORE04_01_ACTIVATION_FILE = ROOT / "docs/queue/packet-activation-core-04-01.json"
CORE04_02_ACTIVATION_FILE = ROOT / "docs/queue/packet-activation-core-04-02.json"
CORE04_03_ACTIVATION_FILE = ROOT / "docs/queue/packet-activation-core-04-03.json"
CORE04_04_ACTIVATION_FILE = ROOT / "docs/queue/packet-activation-core-04-04.json"
CORE04_09_ACTIVATION_FILE = ROOT / "docs/queue/packet-activation-core-04-09.json"
CORE05_01_ACTIVATION_FILE = ROOT / "docs/queue/packet-activation-core-05-01.json"
CORE05_02_ACTIVATION_FILE = ROOT / "docs/queue/packet-activation-core-05-02.json"
CORE05_03_ACTIVATION_FILE = ROOT / "docs/queue/packet-activation-core-05-03.json"
CORE05_04_ACTIVATION_FILE = ROOT / "docs/queue/packet-activation-core-05-04.json"
CORE05_05_ACTIVATION_FILE = ROOT / "docs/queue/packet-activation-core-05-05.json"
CORE05_06_ACTIVATION_FILE = ROOT / "docs/queue/packet-activation-core-05-06.json"
CORE05_07_ACTIVATION_FILE = ROOT / "docs/queue/packet-activation-core-05-07.json"
CORE05_08_ACTIVATION_FILE = ROOT / "docs/queue/packet-activation-core-05-08.json"
CORE02_ACTIVATION_FILE = ROOT / "docs/queue/packet-activation-core-02-03.json"
# The selector reads this path; it is the activation for the current manifest state.
ACTIVATION_FILE = CORE05_08_ACTIVATION_FILE
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
CORE01_15_ACTIVATED_STATUS = "CORE01_15_READY_PREDECESSORS_COMPLETED"
CORE01_15_COMPLETED_STATUS = "CORE01_15_COMPLETED_REST_BLOCKED"
CORE01_16_COMPLETED_STATUS = "CORE01_16_COMPLETED_REST_BLOCKED"
CORE02_04_ACTIVATED_STATUS = "CORE02_04_READY_L1_CAPABILITY_OVERLAY"
CORE02_04_COMPLETED_STATUS = "CORE02_04_COMPLETED_REST_BLOCKED"
CORE02_05_ACTIVATED_STATUS = "CORE02_05_READY_L1_CAPABILITY_OVERLAY"
CORE02_05_COMPLETED_STATUS = "CORE02_05_COMPLETED_REST_BLOCKED"
CORE02_06_ACTIVATED_STATUS = "CORE02_06_READY_L1_CAPABILITY_OVERLAY"
CORE02_06_COMPLETED_STATUS = "CORE02_06_COMPLETED_REST_BLOCKED"
CORE02_07_ACTIVATED_STATUS = "CORE02_07_READY_L1_CAPABILITY_OVERLAY"
CORE02_07_COMPLETED_STATUS = "CORE02_07_COMPLETED_REST_BLOCKED"
CORE02_08_ACTIVATED_STATUS = "CORE02_08_READY_L1_CAPABILITY_OVERLAY"
CORE02_08_COMPLETED_STATUS = "CORE02_08_COMPLETED_REST_BLOCKED"
CORE02_09_ACTIVATED_STATUS = "CORE02_09_READY_L1_CAPABILITY_OVERLAY"
CORE02_09_COMPLETED_STATUS = "CORE02_09_COMPLETED_REST_BLOCKED"
CORE02_10_COMPLETED_STATUS = "CORE02_10_COMPLETED_REST_BLOCKED"
CORE03_01_APPROVED_STATUS = "CORE03_01_APPROVED_GOVERNANCE_ONLY"
CORE03_02_APPROVED_STATUS = "CORE03_02_APPROVED_CONTRACT_ONLY"
CORE03_03_READY_STATUS = "CORE03_03_READY_L1_CAPABILITY_OVERLAY"
CORE03_03_COMPLETED_STATUS = "CORE03_03_COMPLETED_REST_BLOCKED"
CORE03_04_COMPLETED_STATUS = "CORE03_04_COMPLETED_REST_BLOCKED"
CORE03_05_COMPLETED_STATUS = "CORE03_05_COMPLETED_REST_BLOCKED"
CORE03_06_COMPLETED_STATUS = "CORE03_06_COMPLETED_REST_BLOCKED"
CORE03_07_COMPLETED_STATUS = "CORE03_07_COMPLETED_REST_BLOCKED"
CORE03_08_COMPLETED_STATUS = "CORE03_08_COMPLETED_REST_BLOCKED"
CORE03_09_READY_STATUS = "CORE03_09_READY_L1_CAPABILITY_OVERLAY"
CORE03_09_COMPLETED_STATUS = "CORE03_09_COMPLETED_REST_BLOCKED"
CORE03_10_COMPLETED_STATUS = "CORE03_10_COMPLETED_REST_BLOCKED"
CORE04_01_APPROVED_STATUS = "CORE04_01_APPROVED_GOVERNANCE_ONLY"
CORE04_02_APPROVED_STATUS = "CORE04_02_APPROVED_CONTRACT_ONLY"
CORE04_03_READY_STATUS = "CORE04_03_READY_L1_CAPABILITY_OVERLAY"
CORE04_03_COMPLETED_STATUS = "CORE04_03_COMPLETED_REST_BLOCKED"
CORE04_04_READY_STATUS = "CORE04_04_READY_L1_CAPABILITY_OVERLAY"
CORE04_04_COMPLETED_STATUS = "CORE04_04_COMPLETED_REST_BLOCKED"
CORE04_05_COMPLETED_STATUS = "CORE04_05_COMPLETED_REST_BLOCKED"
CORE04_06_COMPLETED_STATUS = "CORE04_06_COMPLETED_REST_BLOCKED"
CORE04_07_COMPLETED_STATUS = "CORE04_07_COMPLETED_REST_BLOCKED"
CORE04_08_COMPLETED_STATUS = "CORE04_08_COMPLETED_REST_BLOCKED"
CORE04_09_READY_STATUS = "CORE04_09_READY_L1_CAPABILITY_OVERLAY"
CORE04_09_COMPLETED_STATUS = "CORE04_09_COMPLETED_REST_BLOCKED"
CORE04_10_COMPLETED_STATUS = "CORE04_10_COMPLETED_REST_BLOCKED"
CORE05_01_APPROVED_STATUS = "CORE05_01_APPROVED_GOVERNANCE_ONLY"
CORE05_02_APPROVED_STATUS = "CORE05_02_APPROVED_CONTRACT_ONLY"
CORE05_03_READY_STATUS = "CORE05_03_READY_L1_CAPABILITY_OVERLAY"
CORE05_03_COMPLETED_STATUS = "CORE05_03_COMPLETED_REST_BLOCKED"
CORE05_04_READY_STATUS = "CORE05_04_READY_L1_CAPABILITY_OVERLAY"
CORE05_04_COMPLETED_STATUS = "CORE05_04_COMPLETED_REST_BLOCKED"
CORE05_05_READY_STATUS = "CORE05_05_READY_L1_CAPABILITY_OVERLAY"
CORE05_05_COMPLETED_STATUS = "CORE05_05_COMPLETED_REST_BLOCKED"
CORE05_06_READY_STATUS = "CORE05_06_READY_L1_CAPABILITY_OVERLAY"
CORE05_06_COMPLETED_STATUS = "CORE05_06_COMPLETED_REST_BLOCKED"
CORE05_07_READY_STATUS = "CORE05_07_READY_L1_CAPABILITY_OVERLAY"
CORE05_07_COMPLETED_STATUS = "CORE05_07_COMPLETED_REST_BLOCKED"
CORE05_08_READY_STATUS = "CORE05_08_READY_L1_CAPABILITY_OVERLAY"
CORE05_08_COMPLETED_STATUS = "CORE05_08_COMPLETED_REST_BLOCKED"
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
    CORE01_15_ACTIVATED_STATUS,
    CORE01_15_COMPLETED_STATUS,
    CORE01_16_COMPLETED_STATUS,
    CORE02_04_ACTIVATED_STATUS,
    CORE02_04_COMPLETED_STATUS,
    CORE02_05_ACTIVATED_STATUS,
    CORE02_05_COMPLETED_STATUS,
    CORE02_06_ACTIVATED_STATUS,
    CORE02_06_COMPLETED_STATUS,
    CORE02_07_ACTIVATED_STATUS,
    CORE02_07_COMPLETED_STATUS,
    CORE02_08_ACTIVATED_STATUS,
    CORE02_08_COMPLETED_STATUS,
    CORE02_09_ACTIVATED_STATUS,
    CORE02_09_COMPLETED_STATUS,
    CORE02_10_COMPLETED_STATUS,
    CORE03_01_APPROVED_STATUS,
    CORE03_02_APPROVED_STATUS,
    CORE03_03_READY_STATUS,
    CORE03_03_COMPLETED_STATUS,
    CORE03_04_COMPLETED_STATUS,
    CORE03_05_COMPLETED_STATUS,
    CORE03_06_COMPLETED_STATUS,
    CORE03_07_COMPLETED_STATUS,
    CORE03_08_COMPLETED_STATUS,
    CORE03_09_READY_STATUS,
    CORE03_09_COMPLETED_STATUS,
    CORE03_10_COMPLETED_STATUS,
    CORE04_01_APPROVED_STATUS,
    CORE04_02_APPROVED_STATUS,
    CORE04_03_READY_STATUS,
    CORE04_03_COMPLETED_STATUS,
    CORE04_04_READY_STATUS,
    CORE04_04_COMPLETED_STATUS,
    CORE04_05_COMPLETED_STATUS,
    CORE04_06_COMPLETED_STATUS,
    CORE04_07_COMPLETED_STATUS,
    CORE04_08_COMPLETED_STATUS,
    CORE04_09_READY_STATUS,
    CORE04_09_COMPLETED_STATUS,
    CORE04_10_COMPLETED_STATUS,
    CORE05_01_APPROVED_STATUS,
    CORE05_02_APPROVED_STATUS,
    CORE05_03_READY_STATUS,
    CORE05_03_COMPLETED_STATUS,
    CORE05_04_READY_STATUS,
    CORE05_04_COMPLETED_STATUS,
    CORE05_05_READY_STATUS,
    CORE05_05_COMPLETED_STATUS,
    CORE05_06_READY_STATUS,
    CORE05_06_COMPLETED_STATUS,
    CORE05_07_READY_STATUS,
    CORE05_07_COMPLETED_STATUS,
    CORE05_08_READY_STATUS,
    CORE05_08_COMPLETED_STATUS,
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
CORE01_14_CODE_PR = 459
CORE01_15_CODE_PR = 462
CORE01_16_CODE_PR = 464
CORE02_04_CODE_PR = 466
CORE02_05_CODE_PR = 469
CORE02_06_CODE_PR = 472
CORE02_07_CODE_PR = 475
CORE02_08_CODE_PR = 484
CORE02_09_CODE_PR = 487
CORE02_10_CODE_PR = 489
CORE03_01_GATE_PR = 492
CORE03_02_GATE_PR = 505
CORE03_03_CODE_PR = 508
CORE03_04_CLOSEOUT_PR = 510
CORE03_05_CLOSEOUT_PR = 511
CORE03_06_CLOSEOUT_PR = 512
CORE03_07_CLOSEOUT_PR = 513
CORE03_08_CLOSEOUT_PR = 514
CORE03_09_CODE_PR = 516
CORE03_10_CLOSEOUT_PR = 518
CORE04_01_GATE_PR = 519
CORE04_02_GATE_PR = 520
CORE04_03_CODE_PR = 522
CORE04_04_CODE_PR = 525
CORE04_05_CLOSEOUT_PR = 528
CORE04_06_CLOSEOUT_PR = 529
CORE04_07_CLOSEOUT_PR = 530
CORE04_08_CLOSEOUT_PR = 531
CORE04_09_CODE_PR = 533
CORE04_10_CLOSEOUT_PR = 535
CORE05_01_GATE_PR = 536
CORE05_02_GATE_PR = 537
CORE05_03_GATE_PR = 538
CORE05_03_CLOSEOUT_PR = 540
CORE05_04_GATE_PR = 541
CORE05_04_CLOSEOUT_PR = 543
CORE05_05_GATE_PR = 544
CORE05_05_CLOSEOUT_PR = 546
CORE05_06_GATE_PR = 547
CORE05_06_CLOSEOUT_PR = 549
CORE05_07_GATE_PR = 550
CORE05_07_CLOSEOUT_PR = 552
CORE05_08_GATE_PR = 553
CORE05_08_CLOSEOUT_PR = 555
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

CORE05_01_PINNED_SOURCE_BLOBS = {
    "checkpoint": "6e58068de7a9fda2b29dc493119e05751f1b213a",
    "decisions_ledger": "5fa9a9deef076252fa89675a17f1958e499f277c",
    "scope": "0b65820507d946d2b2b4ed3a2b869e60cafaaf22",
    "definition_of_done": "e0b7c2466ebec9790a715e47490c015cfb502db4",
    "adr_0007": "74cf3b71d26d791608c7ddace6cf2e011e00e24d",
    "adr_0086": "76e3160fa75770d97bf444171a5188cceee39e3c",
    "adr_0108": "e50dc2cdca4c9ef502e1f586ffcbd1bca64c480d",
    "core05_architecture": "70496cc39b4b7937cf370b49f5deed6e46c68e54",
    "core05_governance_contract": "104ee7e65f02209b8d402340be3cb345b4b45854",
    "module_catalog": "18d69bca439831d65982cb0f8acbca1dbaa2eee9",
    "core05_plan": "da36c9e0314e6b265311f6b4d08799a7203937ae",
    "implementation_registry": "abbf8e5f971b8de5d73f55c9ec5a0bd7a2632024",
}

CORE05_01_ACTIVATION_SOURCES = {
    "checkpoint": "docs/11-checkpoint.md",
    "decisions_ledger": "docs/10-decisions-ledger.md",
    "scope": "docs/03-scope.md",
    "definition_of_done": "docs/09-definition-of-done.md",
    "adr_0007": "docs/adr/0007-core-05-coordinate-policy.md",
    "adr_0086": "docs/adr/0086-capability-based-l1-dependency.md",
    "adr_0108": "docs/adr/0108-core-05-governance-slice.md",
    "core05_architecture": "docs/architecture/core-05-math-coordinate-types.md",
    "core05_governance_contract": "docs/contracts/core-05-governance-v0.md",
    "module_catalog": "docs/product/module-catalog.md",
    "core05_plan": "docs/pr-plans/CORE-05.md",
    "implementation_registry": "docs/queue/implementation-registry.json",
}

CORE05_02_PINNED_SOURCE_BLOBS = {
    "checkpoint": "cb97a9f0dbb71aceced95d80b7b1dfb4f5a221c0",
    "decisions_ledger": "5fa9a9deef076252fa89675a17f1958e499f277c",
    "scope": "0b65820507d946d2b2b4ed3a2b869e60cafaaf22",
    "definition_of_done": "e0b7c2466ebec9790a715e47490c015cfb502db4",
    "adr_0007": "74cf3b71d26d791608c7ddace6cf2e011e00e24d",
    "adr_0086": "76e3160fa75770d97bf444171a5188cceee39e3c",
    "adr_0108": "e50dc2cdca4c9ef502e1f586ffcbd1bca64c480d",
    "core05_architecture": "70496cc39b4b7937cf370b49f5deed6e46c68e54",
    "core05_governance_contract": "104ee7e65f02209b8d402340be3cb345b4b45854",
    "core05_math_contract": "e6fb5f8a4f9934848d71be9d535018b0b99531e2",
    "module_catalog": "18d69bca439831d65982cb0f8acbca1dbaa2eee9",
    "core05_plan": "da36c9e0314e6b265311f6b4d08799a7203937ae",
    "implementation_registry": "abbf8e5f971b8de5d73f55c9ec5a0bd7a2632024",
}

CORE05_02_ACTIVATION_SOURCES = {
    "checkpoint": "docs/11-checkpoint.md",
    "decisions_ledger": "docs/10-decisions-ledger.md",
    "scope": "docs/03-scope.md",
    "definition_of_done": "docs/09-definition-of-done.md",
    "adr_0007": "docs/adr/0007-core-05-coordinate-policy.md",
    "adr_0086": "docs/adr/0086-capability-based-l1-dependency.md",
    "adr_0108": "docs/adr/0108-core-05-governance-slice.md",
    "core05_architecture": "docs/architecture/core-05-math-coordinate-types.md",
    "core05_governance_contract": "docs/contracts/core-05-governance-v0.md",
    "core05_math_contract": "docs/contracts/core-05-math-v0.md",
    "module_catalog": "docs/product/module-catalog.md",
    "core05_plan": "docs/pr-plans/CORE-05.md",
    "implementation_registry": "docs/queue/implementation-registry.json",
}

CORE05_03_PINNED_SOURCE_BLOBS = {
    "checkpoint": "58ec80572462e87c44783b38303d9f763a489774",
    "decisions_ledger": "5fa9a9deef076252fa89675a17f1958e499f277c",
    "scope": "0b65820507d946d2b2b4ed3a2b869e60cafaaf22",
    "definition_of_done": "e0b7c2466ebec9790a715e47490c015cfb502db4",
    "adr_0007": "74cf3b71d26d791608c7ddace6cf2e011e00e24d",
    "adr_0086": "76e3160fa75770d97bf444171a5188cceee39e3c",
    "adr_0108": "e50dc2cdca4c9ef502e1f586ffcbd1bca64c480d",
    "core05_architecture": "70496cc39b4b7937cf370b49f5deed6e46c68e54",
    "core05_governance_contract": "104ee7e65f02209b8d402340be3cb345b4b45854",
    "core05_math_contract": "e6fb5f8a4f9934848d71be9d535018b0b99531e2",
    "module_catalog": "18d69bca439831d65982cb0f8acbca1dbaa2eee9",
    "core05_plan": "da36c9e0314e6b265311f6b4d08799a7203937ae",
    "implementation_registry": "abbf8e5f971b8de5d73f55c9ec5a0bd7a2632024",
}

CORE05_03_ACTIVATION_SOURCES = {
    "checkpoint": "docs/11-checkpoint.md",
    "decisions_ledger": "docs/10-decisions-ledger.md",
    "scope": "docs/03-scope.md",
    "definition_of_done": "docs/09-definition-of-done.md",
    "adr_0007": "docs/adr/0007-core-05-coordinate-policy.md",
    "adr_0086": "docs/adr/0086-capability-based-l1-dependency.md",
    "adr_0108": "docs/adr/0108-core-05-governance-slice.md",
    "core05_architecture": "docs/architecture/core-05-math-coordinate-types.md",
    "core05_governance_contract": "docs/contracts/core-05-governance-v0.md",
    "core05_math_contract": "docs/contracts/core-05-math-v0.md",
    "module_catalog": "docs/product/module-catalog.md",
    "core05_plan": "docs/pr-plans/CORE-05.md",
    "implementation_registry": "docs/queue/implementation-registry.json",
}

CORE05_04_PINNED_SOURCE_BLOBS = {
    "checkpoint": "0e576f3a3e23e93dfc76a903e6452733598232c7",
    "decisions_ledger": "5fa9a9deef076252fa89675a17f1958e499f277c",
    "scope": "0b65820507d946d2b2b4ed3a2b869e60cafaaf22",
    "definition_of_done": "e0b7c2466ebec9790a715e47490c015cfb502db4",
    "adr_0007": "74cf3b71d26d791608c7ddace6cf2e011e00e24d",
    "adr_0086": "76e3160fa75770d97bf444171a5188cceee39e3c",
    "adr_0108": "e50dc2cdca4c9ef502e1f586ffcbd1bca64c480d",
    "core05_architecture": "70496cc39b4b7937cf370b49f5deed6e46c68e54",
    "core05_governance_contract": "104ee7e65f02209b8d402340be3cb345b4b45854",
    "core05_math_contract": "e6fb5f8a4f9934848d71be9d535018b0b99531e2",
    "module_catalog": "18d69bca439831d65982cb0f8acbca1dbaa2eee9",
    "core05_plan": "da36c9e0314e6b265311f6b4d08799a7203937ae",
    "implementation_registry": "abbf8e5f971b8de5d73f55c9ec5a0bd7a2632024",
}

CORE05_04_ACTIVATION_SOURCES = {
    "checkpoint": "docs/11-checkpoint.md",
    "decisions_ledger": "docs/10-decisions-ledger.md",
    "scope": "docs/03-scope.md",
    "definition_of_done": "docs/09-definition-of-done.md",
    "adr_0007": "docs/adr/0007-core-05-coordinate-policy.md",
    "adr_0086": "docs/adr/0086-capability-based-l1-dependency.md",
    "adr_0108": "docs/adr/0108-core-05-governance-slice.md",
    "core05_architecture": "docs/architecture/core-05-math-coordinate-types.md",
    "core05_governance_contract": "docs/contracts/core-05-governance-v0.md",
    "core05_math_contract": "docs/contracts/core-05-math-v0.md",
    "module_catalog": "docs/product/module-catalog.md",
    "core05_plan": "docs/pr-plans/CORE-05.md",
    "implementation_registry": "docs/queue/implementation-registry.json",
}

CORE05_05_PINNED_SOURCE_BLOBS = {
    "checkpoint": "bd01dc8ed54b8c0de1bb32664c6edd39c031b4c4",
    "decisions_ledger": "5fa9a9deef076252fa89675a17f1958e499f277c",
    "scope": "0b65820507d946d2b2b4ed3a2b869e60cafaaf22",
    "definition_of_done": "e0b7c2466ebec9790a715e47490c015cfb502db4",
    "adr_0007": "74cf3b71d26d791608c7ddace6cf2e011e00e24d",
    "adr_0086": "76e3160fa75770d97bf444171a5188cceee39e3c",
    "adr_0108": "e50dc2cdca4c9ef502e1f586ffcbd1bca64c480d",
    "core05_architecture": "70496cc39b4b7937cf370b49f5deed6e46c68e54",
    "core05_governance_contract": "104ee7e65f02209b8d402340be3cb345b4b45854",
    "core05_math_contract": "e6fb5f8a4f9934848d71be9d535018b0b99531e2",
    "module_catalog": "18d69bca439831d65982cb0f8acbca1dbaa2eee9",
    "core05_plan": "da36c9e0314e6b265311f6b4d08799a7203937ae",
    "implementation_registry": "abbf8e5f971b8de5d73f55c9ec5a0bd7a2632024",
}

CORE05_05_ACTIVATION_SOURCES = {
    "checkpoint": "docs/11-checkpoint.md",
    "decisions_ledger": "docs/10-decisions-ledger.md",
    "scope": "docs/03-scope.md",
    "definition_of_done": "docs/09-definition-of-done.md",
    "adr_0007": "docs/adr/0007-core-05-coordinate-policy.md",
    "adr_0086": "docs/adr/0086-capability-based-l1-dependency.md",
    "adr_0108": "docs/adr/0108-core-05-governance-slice.md",
    "core05_architecture": "docs/architecture/core-05-math-coordinate-types.md",
    "core05_governance_contract": "docs/contracts/core-05-governance-v0.md",
    "core05_math_contract": "docs/contracts/core-05-math-v0.md",
    "module_catalog": "docs/product/module-catalog.md",
    "core05_plan": "docs/pr-plans/CORE-05.md",
    "implementation_registry": "docs/queue/implementation-registry.json",
}

CORE05_06_PINNED_SOURCE_BLOBS = {
    "checkpoint": "9f2748abb7100ebd08f0fdef1c32b9765af1b8d7",
    "decisions_ledger": "5fa9a9deef076252fa89675a17f1958e499f277c",
    "scope": "0b65820507d946d2b2b4ed3a2b869e60cafaaf22",
    "definition_of_done": "e0b7c2466ebec9790a715e47490c015cfb502db4",
    "adr_0007": "74cf3b71d26d791608c7ddace6cf2e011e00e24d",
    "adr_0086": "76e3160fa75770d97bf444171a5188cceee39e3c",
    "adr_0108": "e50dc2cdca4c9ef502e1f586ffcbd1bca64c480d",
    "core05_architecture": "70496cc39b4b7937cf370b49f5deed6e46c68e54",
    "core05_governance_contract": "104ee7e65f02209b8d402340be3cb345b4b45854",
    "core05_math_contract": "e6fb5f8a4f9934848d71be9d535018b0b99531e2",
    "module_catalog": "18d69bca439831d65982cb0f8acbca1dbaa2eee9",
    "core05_plan": "da36c9e0314e6b265311f6b4d08799a7203937ae",
    "implementation_registry": "abbf8e5f971b8de5d73f55c9ec5a0bd7a2632024",
}

CORE05_06_ACTIVATION_SOURCES = {
    "checkpoint": "docs/11-checkpoint.md",
    "decisions_ledger": "docs/10-decisions-ledger.md",
    "scope": "docs/03-scope.md",
    "definition_of_done": "docs/09-definition-of-done.md",
    "adr_0007": "docs/adr/0007-core-05-coordinate-policy.md",
    "adr_0086": "docs/adr/0086-capability-based-l1-dependency.md",
    "adr_0108": "docs/adr/0108-core-05-governance-slice.md",
    "core05_architecture": "docs/architecture/core-05-math-coordinate-types.md",
    "core05_governance_contract": "docs/contracts/core-05-governance-v0.md",
    "core05_math_contract": "docs/contracts/core-05-math-v0.md",
    "module_catalog": "docs/product/module-catalog.md",
    "core05_plan": "docs/pr-plans/CORE-05.md",
    "implementation_registry": "docs/queue/implementation-registry.json",
}

CORE05_07_PINNED_SOURCE_BLOBS = {
    "checkpoint": "40cac8f2cdf152c21981ee100bbc6fd3b8a0d2cb",
    "decisions_ledger": "5fa9a9deef076252fa89675a17f1958e499f277c",
    "scope": "0b65820507d946d2b2b4ed3a2b869e60cafaaf22",
    "definition_of_done": "e0b7c2466ebec9790a715e47490c015cfb502db4",
    "adr_0007": "74cf3b71d26d791608c7ddace6cf2e011e00e24d",
    "adr_0086": "76e3160fa75770d97bf444171a5188cceee39e3c",
    "adr_0108": "e50dc2cdca4c9ef502e1f586ffcbd1bca64c480d",
    "core05_architecture": "70496cc39b4b7937cf370b49f5deed6e46c68e54",
    "core05_governance_contract": "104ee7e65f02209b8d402340be3cb345b4b45854",
    "core05_math_contract": "e6fb5f8a4f9934848d71be9d535018b0b99531e2",
    "module_catalog": "18d69bca439831d65982cb0f8acbca1dbaa2eee9",
    "core05_plan": "da36c9e0314e6b265311f6b4d08799a7203937ae",
    "implementation_registry": "abbf8e5f971b8de5d73f55c9ec5a0bd7a2632024",
}

CORE05_07_ACTIVATION_SOURCES = {
    "checkpoint": "docs/11-checkpoint.md",
    "decisions_ledger": "docs/10-decisions-ledger.md",
    "scope": "docs/03-scope.md",
    "definition_of_done": "docs/09-definition-of-done.md",
    "adr_0007": "docs/adr/0007-core-05-coordinate-policy.md",
    "adr_0086": "docs/adr/0086-capability-based-l1-dependency.md",
    "adr_0108": "docs/adr/0108-core-05-governance-slice.md",
    "core05_architecture": "docs/architecture/core-05-math-coordinate-types.md",
    "core05_governance_contract": "docs/contracts/core-05-governance-v0.md",
    "core05_math_contract": "docs/contracts/core-05-math-v0.md",
    "module_catalog": "docs/product/module-catalog.md",
    "core05_plan": "docs/pr-plans/CORE-05.md",
    "implementation_registry": "docs/queue/implementation-registry.json",
}

CORE05_08_PINNED_SOURCE_BLOBS = {
    "checkpoint": "0206ba8971664357ca3fc6398423e6245285c433",
    "decisions_ledger": "5fa9a9deef076252fa89675a17f1958e499f277c",
    "scope": "0b65820507d946d2b2b4ed3a2b869e60cafaaf22",
    "definition_of_done": "e0b7c2466ebec9790a715e47490c015cfb502db4",
    "adr_0007": "74cf3b71d26d791608c7ddace6cf2e011e00e24d",
    "adr_0086": "76e3160fa75770d97bf444171a5188cceee39e3c",
    "adr_0108": "e50dc2cdca4c9ef502e1f586ffcbd1bca64c480d",
    "core05_architecture": "70496cc39b4b7937cf370b49f5deed6e46c68e54",
    "core05_governance_contract": "104ee7e65f02209b8d402340be3cb345b4b45854",
    "core05_math_contract": "e6fb5f8a4f9934848d71be9d535018b0b99531e2",
    "module_catalog": "18d69bca439831d65982cb0f8acbca1dbaa2eee9",
    "core05_plan": "da36c9e0314e6b265311f6b4d08799a7203937ae",
    "implementation_registry": "abbf8e5f971b8de5d73f55c9ec5a0bd7a2632024",
}

CORE05_08_ACTIVATION_SOURCES = {
    "checkpoint": "docs/11-checkpoint.md",
    "decisions_ledger": "docs/10-decisions-ledger.md",
    "scope": "docs/03-scope.md",
    "definition_of_done": "docs/09-definition-of-done.md",
    "adr_0007": "docs/adr/0007-core-05-coordinate-policy.md",
    "adr_0086": "docs/adr/0086-capability-based-l1-dependency.md",
    "adr_0108": "docs/adr/0108-core-05-governance-slice.md",
    "core05_architecture": "docs/architecture/core-05-math-coordinate-types.md",
    "core05_governance_contract": "docs/contracts/core-05-governance-v0.md",
    "core05_math_contract": "docs/contracts/core-05-math-v0.md",
    "module_catalog": "docs/product/module-catalog.md",
    "core05_plan": "docs/pr-plans/CORE-05.md",
    "implementation_registry": "docs/queue/implementation-registry.json",
}

CORE04_09_PINNED_SOURCE_BLOBS = {
    "checkpoint": "0de701bc20a4721cd27eb6cf14a63cf91c430616",
    "decisions_ledger": "93f7aaefe58cdcbb30bee3dd8f6c86fd746b11b1",
    "scope": "0b65820507d946d2b2b4ed3a2b869e60cafaaf22",
    "definition_of_done": "e0b7c2466ebec9790a715e47490c015cfb502db4",
    "adr_0006": "ce9d591cf088c0d8fa38f9216d2b23604b766342",
    "adr_0086": "76e3160fa75770d97bf444171a5188cceee39e3c",
    "adr_0107": "ff6b8bff44f32e59a2cf2954107d5508ac048fd2",
    "core04_architecture": "b40b1bf97b934a883d6bb99e45bd40de6711912c",
    "core04_governance_contract": "fa656a370a2ba09fcf8b5c2be27d7fae0ee4a41f",
    "core04_timeline_contract": "7137e433f13b564ba4171d59750346e4a8815c47",
    "core04_qualification_contract": "59f8c44ad8cca1d49e328b96d8d0a262f3ca89de",
    "module_catalog": "18d69bca439831d65982cb0f8acbca1dbaa2eee9",
    "core04_plan": "b56f13b86bdc79ebd0c8299365e493447bd1e4b7",
    "implementation_registry": "abbf8e5f971b8de5d73f55c9ec5a0bd7a2632024",
}

CORE04_09_ACTIVATION_SOURCES = {
    "checkpoint": "docs/11-checkpoint.md",
    "decisions_ledger": "docs/10-decisions-ledger.md",
    "scope": "docs/03-scope.md",
    "definition_of_done": "docs/09-definition-of-done.md",
    "adr_0006": "docs/adr/0006-core-04-time-policy.md",
    "adr_0086": "docs/adr/0086-capability-based-l1-dependency.md",
    "adr_0107": "docs/adr/0107-core-04-governance-slice.md",
    "core04_architecture": "docs/architecture/core-04-time-simulation.md",
    "core04_governance_contract": "docs/contracts/core-04-governance-v0.md",
    "core04_timeline_contract": "docs/contracts/core-04-timeline-v0.md",
    "core04_qualification_contract": "docs/contracts/core-04-qualification-v0.md",
    "module_catalog": "docs/product/module-catalog.md",
    "core04_plan": "docs/pr-plans/CORE-04.md",
    "implementation_registry": "docs/queue/implementation-registry.json",
}

CORE04_04_PINNED_SOURCE_BLOBS = {
    "checkpoint": "76fee3599e23d888f6d8659cc4da33913e3827a1",
    "decisions_ledger": "93f7aaefe58cdcbb30bee3dd8f6c86fd746b11b1",
    "scope": "0b65820507d946d2b2b4ed3a2b869e60cafaaf22",
    "definition_of_done": "e0b7c2466ebec9790a715e47490c015cfb502db4",
    "adr_0006": "ce9d591cf088c0d8fa38f9216d2b23604b766342",
    "adr_0086": "76e3160fa75770d97bf444171a5188cceee39e3c",
    "adr_0107": "ff6b8bff44f32e59a2cf2954107d5508ac048fd2",
    "core04_architecture": "b40b1bf97b934a883d6bb99e45bd40de6711912c",
    "core04_governance_contract": "fa656a370a2ba09fcf8b5c2be27d7fae0ee4a41f",
    "core04_timeline_contract": "7137e433f13b564ba4171d59750346e4a8815c47",
    "module_catalog": "18d69bca439831d65982cb0f8acbca1dbaa2eee9",
    "core04_plan": "b56f13b86bdc79ebd0c8299365e493447bd1e4b7",
    "implementation_registry": "abbf8e5f971b8de5d73f55c9ec5a0bd7a2632024",
}

CORE04_04_ACTIVATION_SOURCES = {
    "checkpoint": "docs/11-checkpoint.md",
    "decisions_ledger": "docs/10-decisions-ledger.md",
    "scope": "docs/03-scope.md",
    "definition_of_done": "docs/09-definition-of-done.md",
    "adr_0006": "docs/adr/0006-core-04-time-policy.md",
    "adr_0086": "docs/adr/0086-capability-based-l1-dependency.md",
    "adr_0107": "docs/adr/0107-core-04-governance-slice.md",
    "core04_architecture": "docs/architecture/core-04-time-simulation.md",
    "core04_governance_contract": "docs/contracts/core-04-governance-v0.md",
    "core04_timeline_contract": "docs/contracts/core-04-timeline-v0.md",
    "module_catalog": "docs/product/module-catalog.md",
    "core04_plan": "docs/pr-plans/CORE-04.md",
    "implementation_registry": "docs/queue/implementation-registry.json",
}

CORE04_03_PINNED_SOURCE_BLOBS = {
    "checkpoint": "3a07dce08410de3a84ad68455e59e76bd01f3279",
    "decisions_ledger": "93f7aaefe58cdcbb30bee3dd8f6c86fd746b11b1",
    "scope": "0b65820507d946d2b2b4ed3a2b869e60cafaaf22",
    "definition_of_done": "e0b7c2466ebec9790a715e47490c015cfb502db4",
    "adr_0006": "ce9d591cf088c0d8fa38f9216d2b23604b766342",
    "adr_0086": "76e3160fa75770d97bf444171a5188cceee39e3c",
    "adr_0107": "ff6b8bff44f32e59a2cf2954107d5508ac048fd2",
    "core04_architecture": "b40b1bf97b934a883d6bb99e45bd40de6711912c",
    "core04_governance_contract": "fa656a370a2ba09fcf8b5c2be27d7fae0ee4a41f",
    "core04_timeline_contract": "7137e433f13b564ba4171d59750346e4a8815c47",
    "module_catalog": "18d69bca439831d65982cb0f8acbca1dbaa2eee9",
    "core04_plan": "b56f13b86bdc79ebd0c8299365e493447bd1e4b7",
    "implementation_registry": "abbf8e5f971b8de5d73f55c9ec5a0bd7a2632024",
}

CORE04_03_ACTIVATION_SOURCES = {
    "checkpoint": "docs/11-checkpoint.md",
    "decisions_ledger": "docs/10-decisions-ledger.md",
    "scope": "docs/03-scope.md",
    "definition_of_done": "docs/09-definition-of-done.md",
    "adr_0006": "docs/adr/0006-core-04-time-policy.md",
    "adr_0086": "docs/adr/0086-capability-based-l1-dependency.md",
    "adr_0107": "docs/adr/0107-core-04-governance-slice.md",
    "core04_architecture": "docs/architecture/core-04-time-simulation.md",
    "core04_governance_contract": "docs/contracts/core-04-governance-v0.md",
    "core04_timeline_contract": "docs/contracts/core-04-timeline-v0.md",
    "module_catalog": "docs/product/module-catalog.md",
    "core04_plan": "docs/pr-plans/CORE-04.md",
    "implementation_registry": "docs/queue/implementation-registry.json",
}

CORE04_02_PINNED_SOURCE_BLOBS = {
    "checkpoint": "bd66c1f9ada3a55ac513c135f03cb6a6d48fb571",
    "decisions_ledger": "93f7aaefe58cdcbb30bee3dd8f6c86fd746b11b1",
    "scope": "0b65820507d946d2b2b4ed3a2b869e60cafaaf22",
    "definition_of_done": "e0b7c2466ebec9790a715e47490c015cfb502db4",
    "adr_0006": "ce9d591cf088c0d8fa38f9216d2b23604b766342",
    "adr_0086": "76e3160fa75770d97bf444171a5188cceee39e3c",
    "adr_0107": "ff6b8bff44f32e59a2cf2954107d5508ac048fd2",
    "core04_architecture": "b40b1bf97b934a883d6bb99e45bd40de6711912c",
    "core04_governance_contract": "fa656a370a2ba09fcf8b5c2be27d7fae0ee4a41f",
    "core04_timeline_contract": "7137e433f13b564ba4171d59750346e4a8815c47",
    "module_catalog": "18d69bca439831d65982cb0f8acbca1dbaa2eee9",
    "core04_plan": "b56f13b86bdc79ebd0c8299365e493447bd1e4b7",
    "implementation_registry": "abbf8e5f971b8de5d73f55c9ec5a0bd7a2632024",
}

CORE04_02_ACTIVATION_SOURCES = {
    "checkpoint": "docs/11-checkpoint.md",
    "decisions_ledger": "docs/10-decisions-ledger.md",
    "scope": "docs/03-scope.md",
    "definition_of_done": "docs/09-definition-of-done.md",
    "adr_0006": "docs/adr/0006-core-04-time-policy.md",
    "adr_0086": "docs/adr/0086-capability-based-l1-dependency.md",
    "adr_0107": "docs/adr/0107-core-04-governance-slice.md",
    "core04_architecture": "docs/architecture/core-04-time-simulation.md",
    "core04_governance_contract": "docs/contracts/core-04-governance-v0.md",
    "core04_timeline_contract": "docs/contracts/core-04-timeline-v0.md",
    "module_catalog": "docs/product/module-catalog.md",
    "core04_plan": "docs/pr-plans/CORE-04.md",
    "implementation_registry": "docs/queue/implementation-registry.json",
}

CORE04_01_PINNED_SOURCE_BLOBS = {
    "checkpoint": "2943d0e573fdef24d4e7abc3c51c20bdbab20a5f",
    "decisions_ledger": "93f7aaefe58cdcbb30bee3dd8f6c86fd746b11b1",
    "scope": "0b65820507d946d2b2b4ed3a2b869e60cafaaf22",
    "definition_of_done": "e0b7c2466ebec9790a715e47490c015cfb502db4",
    "adr_0006": "ce9d591cf088c0d8fa38f9216d2b23604b766342",
    "adr_0086": "76e3160fa75770d97bf444171a5188cceee39e3c",
    "adr_0107": "ff6b8bff44f32e59a2cf2954107d5508ac048fd2",
    "core04_architecture": "b40b1bf97b934a883d6bb99e45bd40de6711912c",
    "core04_governance_contract": "fa656a370a2ba09fcf8b5c2be27d7fae0ee4a41f",
    "module_catalog": "18d69bca439831d65982cb0f8acbca1dbaa2eee9",
    "core04_plan": "b56f13b86bdc79ebd0c8299365e493447bd1e4b7",
    "implementation_registry": "abbf8e5f971b8de5d73f55c9ec5a0bd7a2632024",
}

CORE04_01_ACTIVATION_SOURCES = {
    "checkpoint": "docs/11-checkpoint.md",
    "decisions_ledger": "docs/10-decisions-ledger.md",
    "scope": "docs/03-scope.md",
    "definition_of_done": "docs/09-definition-of-done.md",
    "adr_0006": "docs/adr/0006-core-04-time-policy.md",
    "adr_0086": "docs/adr/0086-capability-based-l1-dependency.md",
    "adr_0107": "docs/adr/0107-core-04-governance-slice.md",
    "core04_architecture": "docs/architecture/core-04-time-simulation.md",
    "core04_governance_contract": "docs/contracts/core-04-governance-v0.md",
    "module_catalog": "docs/product/module-catalog.md",
    "core04_plan": "docs/pr-plans/CORE-04.md",
    "implementation_registry": "docs/queue/implementation-registry.json",
}

CORE04_CAPABILITY_ADMISSION = {
    "adr": "docs/adr/0086-capability-based-l1-dependency.md",
    "formal_dependency": "CORE-01",
    "module_completion_claimed": False,
    "required_capabilities": [
        {"id": "CORE01_HEADLESS_BUILD_AND_TEST", "satisfied_by": "NLE-PRPLAN-CORE-01-03"},
        {"id": "CORE01_PORTABLE_PATHS", "satisfied_by": "NLE-PRPLAN-CORE-01-06"},
        {"id": "CORE01_SDL3_BUILD_BASELINE", "satisfied_by": "NLE-PRPLAN-CORE-01-07"},
        {"id": "CORE01_NATIVE_CI_MATRIX", "satisfied_by": "NLE-PRPLAN-CORE-01-08"},
        {"id": "CORE01_LIFECYCLE_REQUESTS", "satisfied_by": "NLE-PRPLAN-CORE-01-12"},
        {"id": "CORE01_CAPABILITY_GRAPH", "satisfied_by": "NLE-PRPLAN-CORE-01-13"},
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

CORE03_09_PINNED_SOURCE_BLOBS = {
    "checkpoint": "a230833480b501c978c7cf04b47ef8785fe2e19c",
    "decisions_ledger": "cafc9f927e735781f6b7f098ff0e6f7d264459a5",
    "scope": "0b65820507d946d2b2b4ed3a2b869e60cafaaf22",
    "definition_of_done": "e0b7c2466ebec9790a715e47490c015cfb502db4",
    "adr_0005": "8569be8dd610ba449e4cbb0e553c2d8c6786f6d4",
    "adr_0086": "76e3160fa75770d97bf444171a5188cceee39e3c",
    "adr_0103": "81adca6d4bc25574a4093783e55d22091b78c203",
    "adr_0105": "a87906e17b5e393a9b3cc500840e14b42f7ac858",
    "core03_architecture": "d27523a71854d2f3952453b2ec7a3ef31f2d4aac",
    "core03_task_graph_contract": "36b03944504b6b8e74907f773ead6901ce8705b0",
    "core03_qualification_contract": "12dd2480d7a272881f1b0c88dd8ccb945f7256e7",
    "module_catalog": "18d69bca439831d65982cb0f8acbca1dbaa2eee9",
    "core03_plan": "6527c5ca5a176176506029edd4ae2de69d58928a",
    "implementation_registry": "abbf8e5f971b8de5d73f55c9ec5a0bd7a2632024",
}

CORE03_09_ACTIVATION_SOURCES = {
    "checkpoint": "docs/11-checkpoint.md",
    "decisions_ledger": "docs/10-decisions-ledger.md",
    "scope": "docs/03-scope.md",
    "definition_of_done": "docs/09-definition-of-done.md",
    "adr_0005": "docs/adr/0005-core-03-jobs-concurrency.md",
    "adr_0086": "docs/adr/0086-capability-based-l1-dependency.md",
    "adr_0103": "docs/adr/0103-core-03-governance-gate.md",
    "adr_0105": "docs/adr/0105-core-03-limited-capability-admission.md",
    "core03_architecture": "docs/architecture/core-03-concurrency-jobs.md",
    "core03_task_graph_contract": "docs/contracts/core-03-task-graph-v0.md",
    "core03_qualification_contract": "docs/contracts/core-03-qualification-v0.md",
    "module_catalog": "docs/product/module-catalog.md",
    "core03_plan": "docs/pr-plans/CORE-03.md",
    "implementation_registry": "docs/queue/implementation-registry.json",
}

CORE03_03_PINNED_SOURCE_BLOBS = {
    "checkpoint": "5f27254e23ddd5f90c67e02465f19bf2e82a4194",
    "decisions_ledger": "0a33485023c43cb9d70da846071293394e45e998",
    "scope": "0b65820507d946d2b2b4ed3a2b869e60cafaaf22",
    "definition_of_done": "e0b7c2466ebec9790a715e47490c015cfb502db4",
    "adr_0005": "8569be8dd610ba449e4cbb0e553c2d8c6786f6d4",
    "adr_0086": "76e3160fa75770d97bf444171a5188cceee39e3c",
    "adr_0103": "81adca6d4bc25574a4093783e55d22091b78c203",
    "adr_0105": "a87906e17b5e393a9b3cc500840e14b42f7ac858",
    "core03_architecture": "d27523a71854d2f3952453b2ec7a3ef31f2d4aac",
    "core03_task_graph_contract": "36b03944504b6b8e74907f773ead6901ce8705b0",
    "module_catalog": "18d69bca439831d65982cb0f8acbca1dbaa2eee9",
    "core03_plan": "6527c5ca5a176176506029edd4ae2de69d58928a",
    "implementation_registry": "abbf8e5f971b8de5d73f55c9ec5a0bd7a2632024",
}

CORE03_03_ACTIVATION_SOURCES = {
    "checkpoint": "docs/11-checkpoint.md",
    "decisions_ledger": "docs/10-decisions-ledger.md",
    "scope": "docs/03-scope.md",
    "definition_of_done": "docs/09-definition-of-done.md",
    "adr_0005": "docs/adr/0005-core-03-jobs-concurrency.md",
    "adr_0086": "docs/adr/0086-capability-based-l1-dependency.md",
    "adr_0103": "docs/adr/0103-core-03-governance-gate.md",
    "adr_0105": "docs/adr/0105-core-03-limited-capability-admission.md",
    "core03_architecture": "docs/architecture/core-03-concurrency-jobs.md",
    "core03_task_graph_contract": "docs/contracts/core-03-task-graph-v0.md",
    "module_catalog": "docs/product/module-catalog.md",
    "core03_plan": "docs/pr-plans/CORE-03.md",
    "implementation_registry": "docs/queue/implementation-registry.json",
}

CORE03_02_PINNED_SOURCE_BLOBS = {
    "checkpoint": "011cb358602914e4f3ce0a420dc5d597c5ef74c2",
    "decisions_ledger": "0a33485023c43cb9d70da846071293394e45e998",
    "scope": "0b65820507d946d2b2b4ed3a2b869e60cafaaf22",
    "definition_of_done": "e0b7c2466ebec9790a715e47490c015cfb502db4",
    "adr_0005": "8569be8dd610ba449e4cbb0e553c2d8c6786f6d4",
    "adr_0086": "76e3160fa75770d97bf444171a5188cceee39e3c",
    "adr_0103": "81adca6d4bc25574a4093783e55d22091b78c203",
    "adr_0105": "a87906e17b5e393a9b3cc500840e14b42f7ac858",
    "core03_architecture": "d27523a71854d2f3952453b2ec7a3ef31f2d4aac",
    "core03_task_graph_contract": "36b03944504b6b8e74907f773ead6901ce8705b0",
    "module_catalog": "18d69bca439831d65982cb0f8acbca1dbaa2eee9",
    "core03_plan": "6527c5ca5a176176506029edd4ae2de69d58928a",
    "implementation_registry": "abbf8e5f971b8de5d73f55c9ec5a0bd7a2632024",
}

CORE03_02_ACTIVATION_SOURCES = {
    "checkpoint": "docs/11-checkpoint.md",
    "decisions_ledger": "docs/10-decisions-ledger.md",
    "scope": "docs/03-scope.md",
    "definition_of_done": "docs/09-definition-of-done.md",
    "adr_0005": "docs/adr/0005-core-03-jobs-concurrency.md",
    "adr_0086": "docs/adr/0086-capability-based-l1-dependency.md",
    "adr_0103": "docs/adr/0103-core-03-governance-gate.md",
    "adr_0105": "docs/adr/0105-core-03-limited-capability-admission.md",
    "core03_architecture": "docs/architecture/core-03-concurrency-jobs.md",
    "core03_task_graph_contract": "docs/contracts/core-03-task-graph-v0.md",
    "module_catalog": "docs/product/module-catalog.md",
    "core03_plan": "docs/pr-plans/CORE-03.md",
    "implementation_registry": "docs/queue/implementation-registry.json",
}

CORE03_01_PINNED_SOURCE_BLOBS = {
    "checkpoint": "4be93feeccf32d6ef31b48b2d59fcfd551ac42da",
    "decisions_ledger": "01aa967790dc1ea5e72c2ebebae7b832ec579981",
    "scope": "0b65820507d946d2b2b4ed3a2b869e60cafaaf22",
    "definition_of_done": "e0b7c2466ebec9790a715e47490c015cfb502db4",
    "adr_0005": "6302ec933f89733d0f0ed7c1009059b2c0eb15f4",
    "adr_0086": "76e3160fa75770d97bf444171a5188cceee39e3c",
    "adr_0103": "81adca6d4bc25574a4093783e55d22091b78c203",
    "core03_architecture": "d27523a71854d2f3952453b2ec7a3ef31f2d4aac",
    "core03_governance_contract": "00f962b919e85eece40ee3b3d7e03c4f6b3f7d4e",
    "module_catalog": "18d69bca439831d65982cb0f8acbca1dbaa2eee9",
    "core03_plan": "6527c5ca5a176176506029edd4ae2de69d58928a",
    "implementation_registry": "abbf8e5f971b8de5d73f55c9ec5a0bd7a2632024",
}

CORE03_01_ACTIVATION_SOURCES = {
    "checkpoint": "docs/11-checkpoint.md",
    "decisions_ledger": "docs/10-decisions-ledger.md",
    "scope": "docs/03-scope.md",
    "definition_of_done": "docs/09-definition-of-done.md",
    "adr_0005": "docs/adr/0005-core-03-jobs-concurrency.md",
    "adr_0086": "docs/adr/0086-capability-based-l1-dependency.md",
    "adr_0103": "docs/adr/0103-core-03-governance-gate.md",
    "core03_architecture": "docs/architecture/core-03-concurrency-jobs.md",
    "core03_governance_contract": "docs/contracts/core-03-governance-v0.md",
    "module_catalog": "docs/product/module-catalog.md",
    "core03_plan": "docs/pr-plans/CORE-03.md",
    "implementation_registry": "docs/queue/implementation-registry.json",
}

CORE02_10_PINNED_SOURCE_BLOBS = {
    "checkpoint": "a0f4d69dfa4fe494191f04269c5eb31053e99ce9",
    "decisions_ledger": "01aa967790dc1ea5e72c2ebebae7b832ec579981",
    "scope": "0b65820507d946d2b2b4ed3a2b869e60cafaaf22",
    "definition_of_done": "e0b7c2466ebec9790a715e47490c015cfb502db4",
    "adr_0004": "e6c1639a96d6d484385476358bde50b38cc5b2ec",
    "adr_0086": "76e3160fa75770d97bf444171a5188cceee39e3c",
    "adr_0102": "f2259eb4a70c0fda0d9c623e791c1563aa7ef4a2",
    "core02_architecture": "f2b531fc1d2814d51ce59a136ed60320343a5625",
    "core02_ownership_contract": "897546dab541cab50a0c5d9f4ec1b7a0c5ef360f",
    "core02_system_contract": "658e2384ba357a3af03123e08d11902ebcf2d3e6",
    "core02_arena_contract": "26daed9e9ff6ef2b5a1f8d10de007059ef915882",
    "core02_budget_contract": "708ec2c47fcd51a69973869f86d5c693bceddb39",
    "core02_leak_contract": "fea0dc6676e66fc01466e889effd24607361cc30",
    "core02_telemetry_contract": "cc91b0abf31b46dbb52b574c5a0eb33f4446159a",
    "core02_qualification_contract": "24489d544ffabfa02575cf29000c63e0950af81f",
    "core02_closeout_contract": "29b78e429d09cdf3deccaac7c2cb878693bed7f7",
    "core01_headless_contract": "4ea41263bcfd412ca35df2abb32a158706b64e48",
    "core01_paths_contract": "e551ad7b3c8112f79b88a65c33050059762b71fc",
    "core01_sdl3_contract": "841bff9de1caa9f8d995599a02d46ba7bf0ff470",
    "core01_window_contract": "5bf7eaee2d0aea3f0dc4cc89a419f79f8442b479",
    "core02_plan": "93ae6a8e2d5fa354604a57dc19ef5d17ba750689",
    "implementation_registry": "abbf8e5f971b8de5d73f55c9ec5a0bd7a2632024",
}

CORE02_10_ACTIVATION_SOURCES = {
    "checkpoint": "docs/11-checkpoint.md",
    "decisions_ledger": "docs/10-decisions-ledger.md",
    "scope": "docs/03-scope.md",
    "definition_of_done": "docs/09-definition-of-done.md",
    "adr_0004": "docs/adr/0004-core-02-memory-policy.md",
    "adr_0086": "docs/adr/0086-capability-based-l1-dependency.md",
    "adr_0102": "docs/adr/0102-core-02-internal-sequence-closeout.md",
    "core02_architecture": "docs/architecture/core-02-memory-allocators.md",
    "core02_ownership_contract": "docs/contracts/core-02-ownership-v0.md",
    "core02_system_contract": "docs/contracts/core-02-system-allocator-v0.md",
    "core02_arena_contract": "docs/contracts/core-02-monotonic-arena-v0.md",
    "core02_budget_contract": "docs/contracts/core-02-memory-budget-v0.md",
    "core02_leak_contract": "docs/contracts/core-02-leak-tracking-v0.md",
    "core02_telemetry_contract": "docs/contracts/core-02-memory-telemetry-v0.md",
    "core02_qualification_contract": "docs/contracts/core-02-integrated-memory-qualification-v0.md",
    "core02_closeout_contract": "docs/contracts/core-02-internal-sequence-closeout-v0.md",
    "core01_headless_contract": "docs/contracts/core-01-internal-headless-v0.md",
    "core01_paths_contract": "docs/contracts/core-01-process-paths-v0.md",
    "core01_sdl3_contract": "docs/contracts/core-01-sdl3-runtime-v0.md",
    "core01_window_contract": "docs/contracts/core-01-window-lifecycle-v0.md",
    "core02_plan": "docs/pr-plans/CORE-02.md",
    "implementation_registry": "docs/queue/implementation-registry.json",
}

CORE02_09_PINNED_SOURCE_BLOBS = {
    "checkpoint": "a30c4421112d0ef45f227dddb3c20ba6d11408be",
    "decisions_ledger": "01aa967790dc1ea5e72c2ebebae7b832ec579981",
    "scope": "0b65820507d946d2b2b4ed3a2b869e60cafaaf22",
    "definition_of_done": "e0b7c2466ebec9790a715e47490c015cfb502db4",
    "adr_0004": "e6c1639a96d6d484385476358bde50b38cc5b2ec",
    "adr_0086": "76e3160fa75770d97bf444171a5188cceee39e3c",
    "adr_0087": "fb93a02bc07c8ecfdc70953aff33783d508ef1e2",
    "adr_0100": "74d30c49bf2fccc10699116bca29d29aeff3b064",
    "adr_0101": "78be9fe08e32571868a78ded069b329dbb3a1603",
    "core02_architecture": "f2b531fc1d2814d51ce59a136ed60320343a5625",
    "core02_ownership_contract": "897546dab541cab50a0c5d9f4ec1b7a0c5ef360f",
    "core02_system_contract": "658e2384ba357a3af03123e08d11902ebcf2d3e6",
    "core02_arena_contract": "26daed9e9ff6ef2b5a1f8d10de007059ef915882",
    "core02_budget_contract": "708ec2c47fcd51a69973869f86d5c693bceddb39",
    "core02_leak_contract": "fea0dc6676e66fc01466e889effd24607361cc30",
    "core02_telemetry_contract": "cc91b0abf31b46dbb52b574c5a0eb33f4446159a",
    "core02_qualification_contract": "24489d544ffabfa02575cf29000c63e0950af81f",
    "core01_headless_contract": "4ea41263bcfd412ca35df2abb32a158706b64e48",
    "core01_paths_contract": "e551ad7b3c8112f79b88a65c33050059762b71fc",
    "core01_sdl3_contract": "841bff9de1caa9f8d995599a02d46ba7bf0ff470",
    "core01_window_contract": "5bf7eaee2d0aea3f0dc4cc89a419f79f8442b479",
    "core02_plan": "93ae6a8e2d5fa354604a57dc19ef5d17ba750689",
    "implementation_registry": "abbf8e5f971b8de5d73f55c9ec5a0bd7a2632024",
}

CORE02_09_ACTIVATION_SOURCES = {
    "checkpoint": "docs/11-checkpoint.md",
    "decisions_ledger": "docs/10-decisions-ledger.md",
    "scope": "docs/03-scope.md",
    "definition_of_done": "docs/09-definition-of-done.md",
    "adr_0004": "docs/adr/0004-core-02-memory-policy.md",
    "adr_0086": "docs/adr/0086-capability-based-l1-dependency.md",
    "adr_0087": "docs/adr/0087-core-02-ownership-slice.md",
    "adr_0100": "docs/adr/0100-core-02-memory-telemetry.md",
    "adr_0101": "docs/adr/0101-core-02-integrated-memory-qualification.md",
    "core02_architecture": "docs/architecture/core-02-memory-allocators.md",
    "core02_ownership_contract": "docs/contracts/core-02-ownership-v0.md",
    "core02_system_contract": "docs/contracts/core-02-system-allocator-v0.md",
    "core02_arena_contract": "docs/contracts/core-02-monotonic-arena-v0.md",
    "core02_budget_contract": "docs/contracts/core-02-memory-budget-v0.md",
    "core02_leak_contract": "docs/contracts/core-02-leak-tracking-v0.md",
    "core02_telemetry_contract": "docs/contracts/core-02-memory-telemetry-v0.md",
    "core02_qualification_contract": "docs/contracts/core-02-integrated-memory-qualification-v0.md",
    "core01_headless_contract": "docs/contracts/core-01-internal-headless-v0.md",
    "core01_paths_contract": "docs/contracts/core-01-process-paths-v0.md",
    "core01_sdl3_contract": "docs/contracts/core-01-sdl3-runtime-v0.md",
    "core01_window_contract": "docs/contracts/core-01-window-lifecycle-v0.md",
    "core02_plan": "docs/pr-plans/CORE-02.md",
    "implementation_registry": "docs/queue/implementation-registry.json",
}

CORE02_08_PINNED_SOURCE_BLOBS = {
    "checkpoint": "102fa61f64c084db3c7470b024fbb064b8793770",
    "decisions_ledger": "01aa967790dc1ea5e72c2ebebae7b832ec579981",
    "scope": "0b65820507d946d2b2b4ed3a2b869e60cafaaf22",
    "definition_of_done": "e0b7c2466ebec9790a715e47490c015cfb502db4",
    "adr_0004": "e6c1639a96d6d484385476358bde50b38cc5b2ec",
    "adr_0086": "76e3160fa75770d97bf444171a5188cceee39e3c",
    "adr_0087": "fb93a02bc07c8ecfdc70953aff33783d508ef1e2",
    "adr_0099": "fabde826cc64b5f6661c64b49bb2ae7f1e64d2e1",
    "adr_0100": "74d30c49bf2fccc10699116bca29d29aeff3b064",
    "core02_architecture": "f2b531fc1d2814d51ce59a136ed60320343a5625",
    "core02_ownership_contract": "897546dab541cab50a0c5d9f4ec1b7a0c5ef360f",
    "core02_system_contract": "658e2384ba357a3af03123e08d11902ebcf2d3e6",
    "core02_arena_contract": "26daed9e9ff6ef2b5a1f8d10de007059ef915882",
    "core02_budget_contract": "708ec2c47fcd51a69973869f86d5c693bceddb39",
    "core02_leak_contract": "fea0dc6676e66fc01466e889effd24607361cc30",
    "core02_telemetry_contract": "cc91b0abf31b46dbb52b574c5a0eb33f4446159a",
    "core01_headless_contract": "4ea41263bcfd412ca35df2abb32a158706b64e48",
    "core01_paths_contract": "e551ad7b3c8112f79b88a65c33050059762b71fc",
    "core01_sdl3_contract": "841bff9de1caa9f8d995599a02d46ba7bf0ff470",
    "core01_window_contract": "5bf7eaee2d0aea3f0dc4cc89a419f79f8442b479",
    "core02_plan": "93ae6a8e2d5fa354604a57dc19ef5d17ba750689",
    "implementation_registry": "abbf8e5f971b8de5d73f55c9ec5a0bd7a2632024",
}

CORE02_08_ACTIVATION_SOURCES = {
    "checkpoint": "docs/11-checkpoint.md",
    "decisions_ledger": "docs/10-decisions-ledger.md",
    "scope": "docs/03-scope.md",
    "definition_of_done": "docs/09-definition-of-done.md",
    "adr_0004": "docs/adr/0004-core-02-memory-policy.md",
    "adr_0086": "docs/adr/0086-capability-based-l1-dependency.md",
    "adr_0087": "docs/adr/0087-core-02-ownership-slice.md",
    "adr_0099": "docs/adr/0099-core-02-leak-tracking.md",
    "adr_0100": "docs/adr/0100-core-02-memory-telemetry.md",
    "core02_architecture": "docs/architecture/core-02-memory-allocators.md",
    "core02_ownership_contract": "docs/contracts/core-02-ownership-v0.md",
    "core02_system_contract": "docs/contracts/core-02-system-allocator-v0.md",
    "core02_arena_contract": "docs/contracts/core-02-monotonic-arena-v0.md",
    "core02_budget_contract": "docs/contracts/core-02-memory-budget-v0.md",
    "core02_leak_contract": "docs/contracts/core-02-leak-tracking-v0.md",
    "core02_telemetry_contract": "docs/contracts/core-02-memory-telemetry-v0.md",
    "core01_headless_contract": "docs/contracts/core-01-internal-headless-v0.md",
    "core01_paths_contract": "docs/contracts/core-01-process-paths-v0.md",
    "core01_sdl3_contract": "docs/contracts/core-01-sdl3-runtime-v0.md",
    "core01_window_contract": "docs/contracts/core-01-window-lifecycle-v0.md",
    "core02_plan": "docs/pr-plans/CORE-02.md",
    "implementation_registry": "docs/queue/implementation-registry.json",
}

CORE02_07_PINNED_SOURCE_BLOBS = {
    "checkpoint": "da4449f7a204405ff4fb480c2c11d43964695d5c",
    "decisions_ledger": "01aa967790dc1ea5e72c2ebebae7b832ec579981",
    "scope": "0b65820507d946d2b2b4ed3a2b869e60cafaaf22",
    "definition_of_done": "e0b7c2466ebec9790a715e47490c015cfb502db4",
    "adr_0004": "e6c1639a96d6d484385476358bde50b38cc5b2ec",
    "adr_0086": "76e3160fa75770d97bf444171a5188cceee39e3c",
    "adr_0087": "fb93a02bc07c8ecfdc70953aff33783d508ef1e2",
    "adr_0098": "6bf04e782ee4189f737792be12de7335229d7c90",
    "adr_0099": "fabde826cc64b5f6661c64b49bb2ae7f1e64d2e1",
    "core02_architecture": "f2b531fc1d2814d51ce59a136ed60320343a5625",
    "core02_ownership_contract": "897546dab541cab50a0c5d9f4ec1b7a0c5ef360f",
    "core02_system_contract": "658e2384ba357a3af03123e08d11902ebcf2d3e6",
    "core02_arena_contract": "26daed9e9ff6ef2b5a1f8d10de007059ef915882",
    "core02_budget_contract": "708ec2c47fcd51a69973869f86d5c693bceddb39",
    "core02_leak_contract": "fea0dc6676e66fc01466e889effd24607361cc30",
    "core01_headless_contract": "4ea41263bcfd412ca35df2abb32a158706b64e48",
    "core01_paths_contract": "e551ad7b3c8112f79b88a65c33050059762b71fc",
    "core01_sdl3_contract": "841bff9de1caa9f8d995599a02d46ba7bf0ff470",
    "core01_window_contract": "5bf7eaee2d0aea3f0dc4cc89a419f79f8442b479",
    "core02_plan": "93ae6a8e2d5fa354604a57dc19ef5d17ba750689",
    "implementation_registry": "abbf8e5f971b8de5d73f55c9ec5a0bd7a2632024",
}

CORE02_07_ACTIVATION_SOURCES = {
    "checkpoint": "docs/11-checkpoint.md",
    "decisions_ledger": "docs/10-decisions-ledger.md",
    "scope": "docs/03-scope.md",
    "definition_of_done": "docs/09-definition-of-done.md",
    "adr_0004": "docs/adr/0004-core-02-memory-policy.md",
    "adr_0086": "docs/adr/0086-capability-based-l1-dependency.md",
    "adr_0087": "docs/adr/0087-core-02-ownership-slice.md",
    "adr_0098": "docs/adr/0098-core-02-memory-budget.md",
    "adr_0099": "docs/adr/0099-core-02-leak-tracking.md",
    "core02_architecture": "docs/architecture/core-02-memory-allocators.md",
    "core02_ownership_contract": "docs/contracts/core-02-ownership-v0.md",
    "core02_system_contract": "docs/contracts/core-02-system-allocator-v0.md",
    "core02_arena_contract": "docs/contracts/core-02-monotonic-arena-v0.md",
    "core02_budget_contract": "docs/contracts/core-02-memory-budget-v0.md",
    "core02_leak_contract": "docs/contracts/core-02-leak-tracking-v0.md",
    "core01_headless_contract": "docs/contracts/core-01-internal-headless-v0.md",
    "core01_paths_contract": "docs/contracts/core-01-process-paths-v0.md",
    "core01_sdl3_contract": "docs/contracts/core-01-sdl3-runtime-v0.md",
    "core01_window_contract": "docs/contracts/core-01-window-lifecycle-v0.md",
    "core02_plan": "docs/pr-plans/CORE-02.md",
    "implementation_registry": "docs/queue/implementation-registry.json",
}

CORE02_06_PINNED_SOURCE_BLOBS = {
    "checkpoint": "3878d5573cdb300f0daccc71cebb35d89b8223ce",
    "decisions_ledger": "01aa967790dc1ea5e72c2ebebae7b832ec579981",
    "scope": "0b65820507d946d2b2b4ed3a2b869e60cafaaf22",
    "definition_of_done": "e0b7c2466ebec9790a715e47490c015cfb502db4",
    "adr_0004": "e6c1639a96d6d484385476358bde50b38cc5b2ec",
    "adr_0086": "76e3160fa75770d97bf444171a5188cceee39e3c",
    "adr_0087": "fb93a02bc07c8ecfdc70953aff33783d508ef1e2",
    "adr_0097": "3b517e3f997a9fc806cfeee9b572a1c68f7d3c1c",
    "adr_0098": "6bf04e782ee4189f737792be12de7335229d7c90",
    "core02_architecture": "f2b531fc1d2814d51ce59a136ed60320343a5625",
    "core02_ownership_contract": "897546dab541cab50a0c5d9f4ec1b7a0c5ef360f",
    "core02_system_contract": "658e2384ba357a3af03123e08d11902ebcf2d3e6",
    "core02_arena_contract": "26daed9e9ff6ef2b5a1f8d10de007059ef915882",
    "core02_budget_contract": "708ec2c47fcd51a69973869f86d5c693bceddb39",
    "core01_headless_contract": "4ea41263bcfd412ca35df2abb32a158706b64e48",
    "core01_paths_contract": "e551ad7b3c8112f79b88a65c33050059762b71fc",
    "core01_sdl3_contract": "841bff9de1caa9f8d995599a02d46ba7bf0ff470",
    "core01_window_contract": "5bf7eaee2d0aea3f0dc4cc89a419f79f8442b479",
    "core02_plan": "93ae6a8e2d5fa354604a57dc19ef5d17ba750689",
    "implementation_registry": "abbf8e5f971b8de5d73f55c9ec5a0bd7a2632024",
}

CORE02_06_ACTIVATION_SOURCES = {
    "checkpoint": "docs/11-checkpoint.md",
    "decisions_ledger": "docs/10-decisions-ledger.md",
    "scope": "docs/03-scope.md",
    "definition_of_done": "docs/09-definition-of-done.md",
    "adr_0004": "docs/adr/0004-core-02-memory-policy.md",
    "adr_0086": "docs/adr/0086-capability-based-l1-dependency.md",
    "adr_0087": "docs/adr/0087-core-02-ownership-slice.md",
    "adr_0097": "docs/adr/0097-core-02-monotonic-arena.md",
    "adr_0098": "docs/adr/0098-core-02-memory-budget.md",
    "core02_architecture": "docs/architecture/core-02-memory-allocators.md",
    "core02_ownership_contract": "docs/contracts/core-02-ownership-v0.md",
    "core02_system_contract": "docs/contracts/core-02-system-allocator-v0.md",
    "core02_arena_contract": "docs/contracts/core-02-monotonic-arena-v0.md",
    "core02_budget_contract": "docs/contracts/core-02-memory-budget-v0.md",
    "core01_headless_contract": "docs/contracts/core-01-internal-headless-v0.md",
    "core01_paths_contract": "docs/contracts/core-01-process-paths-v0.md",
    "core01_sdl3_contract": "docs/contracts/core-01-sdl3-runtime-v0.md",
    "core01_window_contract": "docs/contracts/core-01-window-lifecycle-v0.md",
    "core02_plan": "docs/pr-plans/CORE-02.md",
    "implementation_registry": "docs/queue/implementation-registry.json",
}

CORE02_05_PINNED_SOURCE_BLOBS = {
    "checkpoint": "69981208f1160b33770692137b8a1fcf958b04f2",
    "decisions_ledger": "01aa967790dc1ea5e72c2ebebae7b832ec579981",
    "scope": "0b65820507d946d2b2b4ed3a2b869e60cafaaf22",
    "definition_of_done": "e0b7c2466ebec9790a715e47490c015cfb502db4",
    "adr_0004": "e6c1639a96d6d484385476358bde50b38cc5b2ec",
    "adr_0086": "76e3160fa75770d97bf444171a5188cceee39e3c",
    "adr_0087": "fb93a02bc07c8ecfdc70953aff33783d508ef1e2",
    "adr_0096": "5335427e0ff2764c2d9db5c4f6bef78560d07c9d",
    "adr_0097": "3b517e3f997a9fc806cfeee9b572a1c68f7d3c1c",
    "core02_architecture": "f2b531fc1d2814d51ce59a136ed60320343a5625",
    "core02_ownership_contract": "897546dab541cab50a0c5d9f4ec1b7a0c5ef360f",
    "core02_system_contract": "658e2384ba357a3af03123e08d11902ebcf2d3e6",
    "core02_arena_contract": "26daed9e9ff6ef2b5a1f8d10de007059ef915882",
    "core01_headless_contract": "4ea41263bcfd412ca35df2abb32a158706b64e48",
    "core01_paths_contract": "e551ad7b3c8112f79b88a65c33050059762b71fc",
    "core01_sdl3_contract": "841bff9de1caa9f8d995599a02d46ba7bf0ff470",
    "core01_window_contract": "5bf7eaee2d0aea3f0dc4cc89a419f79f8442b479",
    "core02_plan": "93ae6a8e2d5fa354604a57dc19ef5d17ba750689",
    "implementation_registry": "abbf8e5f971b8de5d73f55c9ec5a0bd7a2632024",
}

CORE02_05_ACTIVATION_SOURCES = {
    "checkpoint": "docs/11-checkpoint.md",
    "decisions_ledger": "docs/10-decisions-ledger.md",
    "scope": "docs/03-scope.md",
    "definition_of_done": "docs/09-definition-of-done.md",
    "adr_0004": "docs/adr/0004-core-02-memory-policy.md",
    "adr_0086": "docs/adr/0086-capability-based-l1-dependency.md",
    "adr_0087": "docs/adr/0087-core-02-ownership-slice.md",
    "adr_0096": "docs/adr/0096-core-02-system-allocator-baseline.md",
    "adr_0097": "docs/adr/0097-core-02-monotonic-arena.md",
    "core02_architecture": "docs/architecture/core-02-memory-allocators.md",
    "core02_ownership_contract": "docs/contracts/core-02-ownership-v0.md",
    "core02_system_contract": "docs/contracts/core-02-system-allocator-v0.md",
    "core02_arena_contract": "docs/contracts/core-02-monotonic-arena-v0.md",
    "core01_headless_contract": "docs/contracts/core-01-internal-headless-v0.md",
    "core01_paths_contract": "docs/contracts/core-01-process-paths-v0.md",
    "core01_sdl3_contract": "docs/contracts/core-01-sdl3-runtime-v0.md",
    "core01_window_contract": "docs/contracts/core-01-window-lifecycle-v0.md",
    "core02_plan": "docs/pr-plans/CORE-02.md",
    "implementation_registry": "docs/queue/implementation-registry.json",
}

CORE02_04_PINNED_SOURCE_BLOBS = {
    "checkpoint": "cee66c38571ec6956213287b49f880372580c2ea",
    "decisions_ledger": "01aa967790dc1ea5e72c2ebebae7b832ec579981",
    "scope": "0b65820507d946d2b2b4ed3a2b869e60cafaaf22",
    "definition_of_done": "e0b7c2466ebec9790a715e47490c015cfb502db4",
    "adr_0004": "e6c1639a96d6d484385476358bde50b38cc5b2ec",
    "adr_0086": "76e3160fa75770d97bf444171a5188cceee39e3c",
    "adr_0087": "fb93a02bc07c8ecfdc70953aff33783d508ef1e2",
    "adr_0096": "5335427e0ff2764c2d9db5c4f6bef78560d07c9d",
    "core02_architecture": "f2b531fc1d2814d51ce59a136ed60320343a5625",
    "core02_ownership_contract": "897546dab541cab50a0c5d9f4ec1b7a0c5ef360f",
    "core02_system_contract": "658e2384ba357a3af03123e08d11902ebcf2d3e6",
    "core01_headless_contract": "4ea41263bcfd412ca35df2abb32a158706b64e48",
    "core01_paths_contract": "e551ad7b3c8112f79b88a65c33050059762b71fc",
    "core01_sdl3_contract": "841bff9de1caa9f8d995599a02d46ba7bf0ff470",
    "core01_window_contract": "5bf7eaee2d0aea3f0dc4cc89a419f79f8442b479",
    "core02_plan": "93ae6a8e2d5fa354604a57dc19ef5d17ba750689",
    "implementation_registry": "abbf8e5f971b8de5d73f55c9ec5a0bd7a2632024",
}

CORE02_04_ACTIVATION_SOURCES = {
    "checkpoint": "docs/11-checkpoint.md",
    "decisions_ledger": "docs/10-decisions-ledger.md",
    "scope": "docs/03-scope.md",
    "definition_of_done": "docs/09-definition-of-done.md",
    "adr_0004": "docs/adr/0004-core-02-memory-policy.md",
    "adr_0086": "docs/adr/0086-capability-based-l1-dependency.md",
    "adr_0087": "docs/adr/0087-core-02-ownership-slice.md",
    "adr_0096": "docs/adr/0096-core-02-system-allocator-baseline.md",
    "core02_architecture": "docs/architecture/core-02-memory-allocators.md",
    "core02_ownership_contract": "docs/contracts/core-02-ownership-v0.md",
    "core02_system_contract": "docs/contracts/core-02-system-allocator-v0.md",
    "core01_headless_contract": "docs/contracts/core-01-internal-headless-v0.md",
    "core01_paths_contract": "docs/contracts/core-01-process-paths-v0.md",
    "core01_sdl3_contract": "docs/contracts/core-01-sdl3-runtime-v0.md",
    "core01_window_contract": "docs/contracts/core-01-window-lifecycle-v0.md",
    "core02_plan": "docs/pr-plans/CORE-02.md",
    "implementation_registry": "docs/queue/implementation-registry.json",
}

CORE01_16_PINNED_SOURCE_BLOBS = {
    "checkpoint": "426b9375deb009e57ccbe7666bd964e63f53133f",
    "decisions_ledger": "01aa967790dc1ea5e72c2ebebae7b832ec579981",
    "scope": "0b65820507d946d2b2b4ed3a2b869e60cafaaf22",
    "definition_of_done": "e0b7c2466ebec9790a715e47490c015cfb502db4",
    "adr_0003": "50d028c7a28acc25164256c5f4547c14ac7192d4",
    "adr_0095": "ba4b2a8566d7ae637ce3216902884360469c9db0",
    "core01_architecture": "11c7ec4125f40cf0172aa552a1e9835e84d2c172",
    "closeout_contract": "326b2b090e2fdb8d72cf356925b9163d56ac1a93",
    "core01_plan": "88a144291b4149109cf2f90907cd724bde196651",
    "implementation_registry": "abbf8e5f971b8de5d73f55c9ec5a0bd7a2632024",
}

CORE01_16_ACTIVATION_SOURCES = {
    "checkpoint": "docs/11-checkpoint.md",
    "decisions_ledger": "docs/10-decisions-ledger.md",
    "scope": "docs/03-scope.md",
    "definition_of_done": "docs/09-definition-of-done.md",
    "adr_0003": "docs/adr/0003-core-01-platform-technology.md",
    "adr_0095": "docs/adr/0095-core-01-internal-sequence-closeout.md",
    "core01_architecture": "docs/architecture/core-01-platform-lifecycle.md",
    "closeout_contract": "docs/contracts/core-01-internal-sequence-closeout-v0.md",
    "core01_plan": "docs/pr-plans/CORE-01.md",
    "implementation_registry": "docs/queue/implementation-registry.json",
}

CORE01_15_PINNED_SOURCE_BLOBS = {
    "checkpoint": "a8d5b84373f30022ecb1cd2668166de798677278",
    "decisions_ledger": "01aa967790dc1ea5e72c2ebebae7b832ec579981",
    "scope": "0b65820507d946d2b2b4ed3a2b869e60cafaaf22",
    "definition_of_done": "e0b7c2466ebec9790a715e47490c015cfb502db4",
    "adr_0003": "50d028c7a28acc25164256c5f4547c14ac7192d4",
    "adr_0094": "66562b8f9e3125796681519dfbd656b37409cdaa",
    "core01_architecture": "11c7ec4125f40cf0172aa552a1e9835e84d2c172",
    "qualification_contract": "afa3ee17bcb6f22e0f304f2dd1f6e4ff0ad079a0",
    "core01_plan": "88a144291b4149109cf2f90907cd724bde196651",
    "implementation_registry": "abbf8e5f971b8de5d73f55c9ec5a0bd7a2632024",
}

CORE01_15_ACTIVATION_SOURCES = {
    "checkpoint": "docs/11-checkpoint.md",
    "decisions_ledger": "docs/10-decisions-ledger.md",
    "scope": "docs/03-scope.md",
    "definition_of_done": "docs/09-definition-of-done.md",
    "adr_0003": "docs/adr/0003-core-01-platform-technology.md",
    "adr_0094": "docs/adr/0094-core-01-integrated-ci-qualification.md",
    "core01_architecture": "docs/architecture/core-01-platform-lifecycle.md",
    "qualification_contract": "docs/contracts/core-01-integrated-qualification-v0.md",
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

CORE03_CAPABILITY_ADMISSION = {
    "adr": "docs/adr/0105-core-03-limited-capability-admission.md",
    "formal_dependency": "CORE-02",
    "module_completion_claimed": False,
    "required_capabilities": [
        {"id": "CORE02_MEMORY_OWNERSHIP", "satisfied_by": "NLE-PRPLAN-CORE-02-03"},
        {"id": "CORE02_SYSTEM_ALLOCATOR_BASELINE", "satisfied_by": "NLE-PRPLAN-CORE-02-04"},
        {"id": "CORE02_MONOTONIC_ARENA", "satisfied_by": "NLE-PRPLAN-CORE-02-05"},
        {"id": "CORE02_MEMORY_BUDGET", "satisfied_by": "NLE-PRPLAN-CORE-02-06"},
        {"id": "CORE02_LEAK_TRACKING", "satisfied_by": "NLE-PRPLAN-CORE-02-07"},
        {"id": "CORE02_MEMORY_TELEMETRY", "satisfied_by": "NLE-PRPLAN-CORE-02-08"},
        {"id": "CORE02_INTEGRATED_QUALIFICATION", "satisfied_by": "NLE-PRPLAN-CORE-02-09"},
    ],
    "not_required": [
        "module_completion",
        "allocator_selection",
        "q4_physical_matrix",
        "public_abi",
        "release",
        "renderer_gpu",
        "audio",
        "network",
    ],
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
    15: ("docs/adr/0094-core-01-integrated-ci-qualification.md",
         "docs/evidence/NLE-PRPLAN-CORE-01-15-G6-ACTIVATION.md"),
    16: ("docs/adr/0095-core-01-internal-sequence-closeout.md",
         "docs/evidence/NLE-PRPLAN-CORE-01-16-G6-ACTIVATION.md"),
}

CORE03_SLICE_METADATA = {
    3: ("docs/adr/0105-core-03-limited-capability-admission.md",
        "docs/evidence/NLE-PRPLAN-CORE-03-03-G6-ACTIVATION.md"),
    4: ("docs/adr/0105-core-03-limited-capability-admission.md",
        "docs/evidence/NLE-PRPLAN-CORE-03-04.md"),
    5: ("docs/adr/0105-core-03-limited-capability-admission.md",
        "docs/evidence/NLE-PRPLAN-CORE-03-05.md"),
    6: ("docs/adr/0105-core-03-limited-capability-admission.md",
        "docs/evidence/NLE-PRPLAN-CORE-03-06.md"),
    7: ("docs/adr/0105-core-03-limited-capability-admission.md",
        "docs/evidence/NLE-PRPLAN-CORE-03-07.md"),
    8: ("docs/adr/0105-core-03-limited-capability-admission.md",
        "docs/evidence/NLE-PRPLAN-CORE-03-08.md"),
    9: ("docs/adr/0105-core-03-limited-capability-admission.md",
        "docs/evidence/NLE-PRPLAN-CORE-03-09-G6-ACTIVATION.md"),
    10: ("docs/adr/0105-core-03-limited-capability-admission.md",
         "docs/evidence/NLE-PRPLAN-CORE-03-10.md"),
}

CORE05_SLICE_METADATA = {
    3: ("docs/adr/0108-core-05-governance-slice.md",
        "docs/evidence/NLE-PRPLAN-CORE-05-03-G6-ACTIVATION.md"),
    4: ("docs/adr/0108-core-05-governance-slice.md",
        "docs/evidence/NLE-PRPLAN-CORE-05-04-G6-ACTIVATION.md"),
    5: ("docs/adr/0108-core-05-governance-slice.md",
        "docs/evidence/NLE-PRPLAN-CORE-05-05-G6-ACTIVATION.md"),
    6: ("docs/adr/0108-core-05-governance-slice.md",
        "docs/evidence/NLE-PRPLAN-CORE-05-06-G6-ACTIVATION.md"),
    7: ("docs/adr/0108-core-05-governance-slice.md",
        "docs/evidence/NLE-PRPLAN-CORE-05-07-G6-ACTIVATION.md"),
    8: ("docs/adr/0108-core-05-governance-slice.md",
        "docs/evidence/NLE-PRPLAN-CORE-05-08-G6-ACTIVATION.md"),
}

CORE04_SLICE_METADATA = {
    3: ("docs/adr/0107-core-04-governance-slice.md",
        "docs/evidence/NLE-PRPLAN-CORE-04-03-G6-ACTIVATION.md"),
    4: ("docs/adr/0107-core-04-governance-slice.md",
        "docs/evidence/NLE-PRPLAN-CORE-04-04-G6-ACTIVATION.md"),
    5: ("docs/adr/0107-core-04-governance-slice.md",
        "docs/evidence/NLE-PRPLAN-CORE-04-05.md"),
    6: ("docs/adr/0107-core-04-governance-slice.md",
        "docs/evidence/NLE-PRPLAN-CORE-04-06.md"),
    7: ("docs/adr/0107-core-04-governance-slice.md",
        "docs/evidence/NLE-PRPLAN-CORE-04-07.md"),
    8: ("docs/adr/0107-core-04-governance-slice.md",
        "docs/evidence/NLE-PRPLAN-CORE-04-08.md"),
    9: ("docs/adr/0107-core-04-governance-slice.md",
        "docs/evidence/NLE-PRPLAN-CORE-04-09-G6-ACTIVATION.md"),
    10: ("docs/adr/0107-core-04-governance-slice.md",
         "docs/evidence/NLE-PRPLAN-CORE-04-10.md"),
}

CORE02_SLICE_METADATA = {
    3: ("docs/adr/0087-core-02-ownership-slice.md",
        "docs/evidence/NLE-PRPLAN-CORE-02-03-G6-ACTIVATION.md"),
    4: ("docs/adr/0096-core-02-system-allocator-baseline.md",
        "docs/evidence/NLE-PRPLAN-CORE-02-04-G6-ACTIVATION.md"),
    5: ("docs/adr/0097-core-02-monotonic-arena.md",
        "docs/evidence/NLE-PRPLAN-CORE-02-05-G6-ACTIVATION.md"),
    6: ("docs/adr/0098-core-02-memory-budget.md",
        "docs/evidence/NLE-PRPLAN-CORE-02-06-G6-ACTIVATION.md"),
    7: ("docs/adr/0099-core-02-leak-tracking.md",
        "docs/evidence/NLE-PRPLAN-CORE-02-07-G6-ACTIVATION.md"),
    8: ("docs/adr/0100-core-02-memory-telemetry.md",
        "docs/evidence/NLE-PRPLAN-CORE-02-08-G6-ACTIVATION.md"),
    9: ("docs/adr/0101-core-02-integrated-memory-qualification.md",
        "docs/evidence/NLE-PRPLAN-CORE-02-09-G6-ACTIVATION.md"),
    10: ("docs/adr/0102-core-02-internal-sequence-closeout.md",
         "docs/evidence/NLE-PRPLAN-CORE-02-10-G6-ACTIVATION.md"),
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
    if selected == "NLE-PRPLAN-CORE-05-08":
        expected = {
            "schema_version": 2,
            "status": "OWNER_RATIFIED_BOUNDED_G6_ACTIVATION",
            "selected_packet_id": "NLE-PRPLAN-CORE-05-08",
            "module_id": "CORE-05",
            "risk": "ELEVATED",
            "release_class": "INTERNAL_ONLY",
            "owner_authorization_ref": "STORM-CORE-01-IMPL-001/issue-387/2026-11-22/core05-id-continuation",
            "approved_adr": "docs/adr/0108-core-05-governance-slice.md",
            "approved_contract": "docs/contracts/core-05-math-v0.md",
            "work_order": "docs/work-orders/NLE-PRPLAN-CORE-05-08.md",
            "activation_evidence": "docs/evidence/NLE-PRPLAN-CORE-05-08-G6-ACTIVATION.md",
            "gate_base_sha": "4fea483465cdbc54aec7a3ba52533842236c6a33",
            "requires_fresh_context_lock": True,
        }
        return expected, CORE05_08_ACTIVATION_SOURCES, CORE05_08_PINNED_SOURCE_BLOBS, {
            "selected_packet_id", "module_id", "risk", "release_class",
            "owner_authorization_ref", "approved_adr", "approved_contract",
            "work_order", "activation_evidence", "capability_admission",
            "source_blob_sha1", "gate_pr",
        }
    if selected == "NLE-PRPLAN-CORE-05-07":
        expected = {
            "schema_version": 2,
            "status": "OWNER_RATIFIED_BOUNDED_G6_ACTIVATION",
            "selected_packet_id": "NLE-PRPLAN-CORE-05-07",
            "module_id": "CORE-05",
            "risk": "ELEVATED",
            "release_class": "INTERNAL_ONLY",
            "owner_authorization_ref": "STORM-CORE-01-IMPL-001/issue-387/2026-11-22/core05-precision-continuation",
            "approved_adr": "docs/adr/0108-core-05-governance-slice.md",
            "approved_contract": "docs/contracts/core-05-math-v0.md",
            "work_order": "docs/work-orders/NLE-PRPLAN-CORE-05-07.md",
            "activation_evidence": "docs/evidence/NLE-PRPLAN-CORE-05-07-G6-ACTIVATION.md",
            "gate_base_sha": "cdda5ab9c4082e3ead5c42317c8b1277416dc0be",
            "requires_fresh_context_lock": True,
        }
        return expected, CORE05_07_ACTIVATION_SOURCES, CORE05_07_PINNED_SOURCE_BLOBS, {
            "selected_packet_id", "module_id", "risk", "release_class",
            "owner_authorization_ref", "approved_adr", "approved_contract",
            "work_order", "activation_evidence", "capability_admission",
            "source_blob_sha1", "gate_pr",
        }
    if selected == "NLE-PRPLAN-CORE-05-06":
        expected = {
            "schema_version": 2,
            "status": "OWNER_RATIFIED_BOUNDED_G6_ACTIVATION",
            "selected_packet_id": "NLE-PRPLAN-CORE-05-06",
            "module_id": "CORE-05",
            "risk": "ELEVATED",
            "release_class": "INTERNAL_ONLY",
            "owner_authorization_ref": "STORM-CORE-01-IMPL-001/issue-387/2026-11-22/core05-unit-continuation",
            "approved_adr": "docs/adr/0108-core-05-governance-slice.md",
            "approved_contract": "docs/contracts/core-05-math-v0.md",
            "work_order": "docs/work-orders/NLE-PRPLAN-CORE-05-06.md",
            "activation_evidence": "docs/evidence/NLE-PRPLAN-CORE-05-06-G6-ACTIVATION.md",
            "gate_base_sha": "e2277fd6710c7db4b1c9c1cf709d39f1d3030574",
            "requires_fresh_context_lock": True,
        }
        return expected, CORE05_06_ACTIVATION_SOURCES, CORE05_06_PINNED_SOURCE_BLOBS, {
            "selected_packet_id", "module_id", "risk", "release_class",
            "owner_authorization_ref", "approved_adr", "approved_contract",
            "work_order", "activation_evidence", "capability_admission",
            "source_blob_sha1", "gate_pr",
        }
    if selected == "NLE-PRPLAN-CORE-05-05":
        expected = {
            "schema_version": 2,
            "status": "OWNER_RATIFIED_BOUNDED_G6_ACTIVATION",
            "selected_packet_id": "NLE-PRPLAN-CORE-05-05",
            "module_id": "CORE-05",
            "risk": "ELEVATED",
            "release_class": "INTERNAL_ONLY",
            "owner_authorization_ref": "STORM-CORE-01-IMPL-001/issue-387/2026-11-22/core05-coordinate-continuation",
            "approved_adr": "docs/adr/0108-core-05-governance-slice.md",
            "approved_contract": "docs/contracts/core-05-math-v0.md",
            "work_order": "docs/work-orders/NLE-PRPLAN-CORE-05-05.md",
            "activation_evidence": "docs/evidence/NLE-PRPLAN-CORE-05-05-G6-ACTIVATION.md",
            "gate_base_sha": "a9e1fce752e8190d875caa5d7fea7415d0a6c8ab",
            "requires_fresh_context_lock": True,
        }
        return expected, CORE05_05_ACTIVATION_SOURCES, CORE05_05_PINNED_SOURCE_BLOBS, {
            "selected_packet_id", "module_id", "risk", "release_class",
            "owner_authorization_ref", "approved_adr", "approved_contract",
            "work_order", "activation_evidence", "capability_admission",
            "source_blob_sha1", "gate_pr",
        }
    if selected == "NLE-PRPLAN-CORE-05-04":
        expected = {
            "schema_version": 2,
            "status": "OWNER_RATIFIED_BOUNDED_G6_ACTIVATION",
            "selected_packet_id": "NLE-PRPLAN-CORE-05-04",
            "module_id": "CORE-05",
            "risk": "ELEVATED",
            "release_class": "INTERNAL_ONLY",
            "owner_authorization_ref": "STORM-CORE-01-IMPL-001/issue-387/2026-11-22/core05-matrix-continuation",
            "approved_adr": "docs/adr/0108-core-05-governance-slice.md",
            "approved_contract": "docs/contracts/core-05-math-v0.md",
            "work_order": "docs/work-orders/NLE-PRPLAN-CORE-05-04.md",
            "activation_evidence": "docs/evidence/NLE-PRPLAN-CORE-05-04-G6-ACTIVATION.md",
            "gate_base_sha": "c81778bc22a6df36553b249e9311772dbf87a19e",
            "requires_fresh_context_lock": True,
        }
        return expected, CORE05_04_ACTIVATION_SOURCES, CORE05_04_PINNED_SOURCE_BLOBS, {
            "selected_packet_id", "module_id", "risk", "release_class",
            "owner_authorization_ref", "approved_adr", "approved_contract",
            "work_order", "activation_evidence", "capability_admission",
            "source_blob_sha1", "gate_pr",
        }
    if selected == "NLE-PRPLAN-CORE-05-03":
        expected = {
            "schema_version": 2,
            "status": "OWNER_RATIFIED_BOUNDED_G6_ACTIVATION",
            "selected_packet_id": "NLE-PRPLAN-CORE-05-03",
            "module_id": "CORE-05",
            "risk": "ELEVATED",
            "release_class": "INTERNAL_ONLY",
            "owner_authorization_ref": "STORM-CORE-01-IMPL-001/issue-387/2026-11-22/core05-vector-continuation",
            "approved_adr": "docs/adr/0108-core-05-governance-slice.md",
            "approved_contract": "docs/contracts/core-05-math-v0.md",
            "work_order": "docs/work-orders/NLE-PRPLAN-CORE-05-03.md",
            "activation_evidence": "docs/evidence/NLE-PRPLAN-CORE-05-03-G6-ACTIVATION.md",
            "gate_base_sha": "de206bfc17f2f43011ca06effe9993baee85cab3",
            "requires_fresh_context_lock": True,
        }
        return expected, CORE05_03_ACTIVATION_SOURCES, CORE05_03_PINNED_SOURCE_BLOBS, {
            "selected_packet_id", "module_id", "risk", "release_class",
            "owner_authorization_ref", "approved_adr", "approved_contract",
            "work_order", "activation_evidence", "capability_admission",
            "source_blob_sha1", "gate_pr",
        }
    if selected == "NLE-PRPLAN-CORE-05-02":
        expected = {
            "schema_version": 2,
            "status": "OWNER_RATIFIED_BOUNDED_G6_ACTIVATION",
            "selected_packet_id": "NLE-PRPLAN-CORE-05-02",
            "module_id": "CORE-05",
            "risk": "LOW",
            "release_class": "INTERNAL_ONLY",
            "owner_authorization_ref": "STORM-CORE-01-IMPL-001/issue-387/2026-11-22/core05-contract-continuation",
            "approved_adr": "docs/adr/0108-core-05-governance-slice.md",
            "approved_contract": "docs/contracts/core-05-math-v0.md",
            "work_order": "docs/work-orders/NLE-PRPLAN-CORE-05-02.md",
            "activation_evidence": "docs/evidence/NLE-PRPLAN-CORE-05-02-G6-ACTIVATION.md",
            "gate_base_sha": "d08150a11b9688482ae2aa4d84b3a5756830fa75",
            "requires_fresh_context_lock": True,
        }
        return expected, CORE05_02_ACTIVATION_SOURCES, CORE05_02_PINNED_SOURCE_BLOBS, {
            "selected_packet_id", "module_id", "risk", "release_class",
            "owner_authorization_ref", "approved_adr", "approved_contract",
            "work_order", "activation_evidence", "capability_admission",
            "source_blob_sha1", "gate_pr",
        }
    if selected == "NLE-PRPLAN-CORE-05-01":
        expected = {
            "status": "OWNER_RATIFIED_BOUNDED_G6_ACTIVATION",
            "selected_packet_id": "NLE-PRPLAN-CORE-05-01",
            "module_id": "CORE-05",
            "risk": "LOW",
            "release_class": "INTERNAL_ONLY",
            "owner_authorization_ref": "STORM-CORE-01-IMPL-001/issue-387/2026-11-22/core05-governance-continuation",
            "approved_adr": "docs/adr/0108-core-05-governance-slice.md",
            "approved_contract": "docs/contracts/core-05-governance-v0.md",
            "work_order": "docs/work-orders/NLE-PRPLAN-CORE-05-01.md",
            "activation_evidence": "docs/evidence/NLE-PRPLAN-CORE-05-01-G6-ACTIVATION.md",
            "gate_base_sha": "0e5d6e5ae0b418823d667aa7e67d0e82154d532c",
            "requires_fresh_context_lock": True,
        }
        return expected, CORE05_01_ACTIVATION_SOURCES, CORE05_01_PINNED_SOURCE_BLOBS, {
            "source_blob_sha1", "gate_pr", "capability_admission"
        }
    if selected == "NLE-PRPLAN-CORE-04-09":
        expected = {
            "schema_version": 2,
            "status": "OWNER_RATIFIED_BOUNDED_G6_ACTIVATION",
            "selected_packet_id": "NLE-PRPLAN-CORE-04-09",
            "module_id": "CORE-04",
            "risk": "ELEVATED",
            "release_class": "INTERNAL_ONLY",
            "owner_authorization_ref": "STORM-CORE-01-IMPL-001/issue-387/2026-11-22/core04-qualification-continuation",
            "approved_adr": "docs/adr/0107-core-04-governance-slice.md",
            "approved_contract": "docs/contracts/core-04-qualification-v0.md",
            "work_order": "docs/work-orders/NLE-PRPLAN-CORE-04-09.md",
            "activation_evidence": "docs/evidence/NLE-PRPLAN-CORE-04-09-G6-ACTIVATION.md",
            "gate_base_sha": "754efc5a1dbf1043f9ae09c8f174d787ea594dc6",
            "requires_fresh_context_lock": True,
        }
        return expected, CORE04_09_ACTIVATION_SOURCES, CORE04_09_PINNED_SOURCE_BLOBS, {
            "source_blob_sha1", "gate_pr", "capability_admission"
        }
    if selected == "NLE-PRPLAN-CORE-04-04":
        expected = {
            "schema_version": 2,
            "status": "OWNER_RATIFIED_BOUNDED_G6_ACTIVATION",
            "selected_packet_id": "NLE-PRPLAN-CORE-04-04",
            "module_id": "CORE-04",
            "risk": "ELEVATED",
            "release_class": "INTERNAL_ONLY",
            "owner_authorization_ref": "STORM-CORE-01-IMPL-001/issue-387/2026-11-22/core04-timeline-continuation",
            "approved_adr": "docs/adr/0107-core-04-governance-slice.md",
            "approved_contract": "docs/contracts/core-04-timeline-v0.md",
            "work_order": "docs/work-orders/NLE-PRPLAN-CORE-04-04.md",
            "activation_evidence": "docs/evidence/NLE-PRPLAN-CORE-04-04-G6-ACTIVATION.md",
            "gate_base_sha": "60cd2dfbaf38ee43b332f0b2274816a9b739736e",
            "requires_fresh_context_lock": True,
        }
        return expected, CORE04_04_ACTIVATION_SOURCES, CORE04_04_PINNED_SOURCE_BLOBS, {
            "source_blob_sha1", "gate_pr", "capability_admission"
        }
    if selected == "NLE-PRPLAN-CORE-04-03":
        expected = {
            "schema_version": 2,
            "status": "OWNER_RATIFIED_BOUNDED_G6_ACTIVATION",
            "selected_packet_id": "NLE-PRPLAN-CORE-04-03",
            "module_id": "CORE-04",
            "risk": "ELEVATED",
            "release_class": "INTERNAL_ONLY",
            "owner_authorization_ref": "STORM-CORE-01-IMPL-001/issue-387/2026-11-21/core04-governance-continuation",
            "approved_adr": "docs/adr/0107-core-04-governance-slice.md",
            "approved_contract": "docs/contracts/core-04-timeline-v0.md",
            "work_order": "docs/work-orders/NLE-PRPLAN-CORE-04-03.md",
            "activation_evidence": "docs/evidence/NLE-PRPLAN-CORE-04-03-G6-ACTIVATION.md",
            "gate_base_sha": "67bbdfdcded5c2172c3773794fd45a85759082a8",
            "requires_fresh_context_lock": True,
        }
        return expected, CORE04_03_ACTIVATION_SOURCES, CORE04_03_PINNED_SOURCE_BLOBS, {
            "source_blob_sha1", "gate_pr", "capability_admission"
        }
    if selected == "NLE-PRPLAN-CORE-04-02":
        expected = {
            "schema_version": 2,
            "status": "OWNER_RATIFIED_BOUNDED_G6_ACTIVATION",
            "selected_packet_id": "NLE-PRPLAN-CORE-04-02",
            "module_id": "CORE-04",
            "risk": "LOW",
            "release_class": "INTERNAL_ONLY",
            "owner_authorization_ref": "STORM-CORE-01-IMPL-001/issue-387/2026-11-21/core04-governance-continuation",
            "approved_adr": "docs/adr/0107-core-04-governance-slice.md",
            "approved_contract": "docs/contracts/core-04-timeline-v0.md",
            "work_order": "docs/work-orders/NLE-PRPLAN-CORE-04-02.md",
            "activation_evidence": "docs/evidence/NLE-PRPLAN-CORE-04-02-G6-ACTIVATION.md",
            "gate_base_sha": "7fb094906a23e4933e25fd90aa19b59bfce49df4",
            "requires_fresh_context_lock": True,
        }
        return expected, CORE04_02_ACTIVATION_SOURCES, CORE04_02_PINNED_SOURCE_BLOBS, {
            "source_blob_sha1", "gate_pr", "capability_admission"
        }
    if selected == "NLE-PRPLAN-CORE-04-01":
        expected = {
            "schema_version": 2,
            "status": "OWNER_RATIFIED_BOUNDED_G6_ACTIVATION",
            "selected_packet_id": "NLE-PRPLAN-CORE-04-01",
            "module_id": "CORE-04",
            "risk": "LOW",
            "release_class": "INTERNAL_ONLY",
            "owner_authorization_ref": "STORM-CORE-01-IMPL-001/issue-387/2026-11-21/core04-governance-continuation",
            "approved_adr": "docs/adr/0107-core-04-governance-slice.md",
            "approved_contract": "docs/contracts/core-04-governance-v0.md",
            "work_order": "docs/work-orders/NLE-PRPLAN-CORE-04-01.md",
            "activation_evidence": "docs/evidence/NLE-PRPLAN-CORE-04-01-G6-ACTIVATION.md",
            "gate_base_sha": "6747eb9fd6949c177e293ed2d754661929f16451",
            "requires_fresh_context_lock": True,
        }
        return expected, CORE04_01_ACTIVATION_SOURCES, CORE04_01_PINNED_SOURCE_BLOBS, {
            "source_blob_sha1", "gate_pr", "capability_admission"
        }
    if selected == "NLE-PRPLAN-CORE-03-09":
        expected = {
            "schema_version": 2,
            "status": "OWNER_RATIFIED_BOUNDED_G6_ACTIVATION",
            "selected_packet_id": "NLE-PRPLAN-CORE-03-09",
            "module_id": "CORE-03",
            "risk": "ELEVATED",
            "release_class": "INTERNAL_ONLY",
            "owner_authorization_ref": "STORM-CORE-01-IMPL-001/issue-387/2026-11-21/core03-09-qualification-continuation",
            "approved_adr": "docs/adr/0105-core-03-limited-capability-admission.md",
            "approved_contract": "docs/contracts/core-03-qualification-v0.md",
            "work_order": "docs/work-orders/NLE-PRPLAN-CORE-03-09.md",
            "activation_evidence": "docs/evidence/NLE-PRPLAN-CORE-03-09-G6-ACTIVATION.md",
            "gate_base_sha": "6a3f245b3647b4b708b239147ec3c666fa5fef2c",
            "requires_fresh_context_lock": True,
        }
        return expected, CORE03_09_ACTIVATION_SOURCES, CORE03_09_PINNED_SOURCE_BLOBS, {
            "source_blob_sha1", "gate_pr", "capability_admission"
        }
    if selected == "NLE-PRPLAN-CORE-03-03":
        expected = {
            "schema_version": 2,
            "status": "OWNER_RATIFIED_BOUNDED_G6_ACTIVATION",
            "selected_packet_id": "NLE-PRPLAN-CORE-03-03",
            "module_id": "CORE-03",
            "risk": "ELEVATED",
            "release_class": "INTERNAL_ONLY",
            "owner_authorization_ref": "STORM-CORE-01-IMPL-001/issue-387/2026-11-21/core03-03-continuation-authorized",
            "approved_adr": "docs/adr/0105-core-03-limited-capability-admission.md",
            "approved_contract": "docs/contracts/core-03-task-graph-v0.md",
            "work_order": "docs/work-orders/NLE-PRPLAN-CORE-03-03.md",
            "activation_evidence": "docs/evidence/NLE-PRPLAN-CORE-03-03-G6-ACTIVATION.md",
            "gate_base_sha": "38d73bd46fc66cc4f83294bcad44e7e310534013",
            "requires_fresh_context_lock": True,
        }
        return expected, CORE03_03_ACTIVATION_SOURCES, CORE03_03_PINNED_SOURCE_BLOBS, {
            "source_blob_sha1", "gate_pr", "capability_admission"
        }
    if selected == "NLE-PRPLAN-CORE-03-02":
        expected = {
            "schema_version": 2,
            "status": "OWNER_RATIFIED_BOUNDED_G6_ACTIVATION",
            "selected_packet_id": "NLE-PRPLAN-CORE-03-02",
            "module_id": "CORE-03",
            "risk": "LOW",
            "release_class": "INTERNAL_ONLY",
            "owner_authorization_ref": "STORM-CORE-01-IMPL-001/issue-387/2026-11-21/core03-a-b-c-d2",
            "approved_adr": "docs/adr/0105-core-03-limited-capability-admission.md",
            "approved_contract": "docs/contracts/core-03-task-graph-v0.md",
            "work_order": "docs/work-orders/NLE-PRPLAN-CORE-03-02.md",
            "activation_evidence": "docs/evidence/NLE-PRPLAN-CORE-03-02-G6-ACTIVATION.md",
            "gate_base_sha": "dcb2cbd7739d44d09f432621d2dbd0acdef14cb1",
            "requires_fresh_context_lock": True,
        }
        return expected, CORE03_02_ACTIVATION_SOURCES, CORE03_02_PINNED_SOURCE_BLOBS, {
            "source_blob_sha1", "gate_pr"
        }
    if selected == "NLE-PRPLAN-CORE-03-01":
        expected = {
            "schema_version": 2,
            "status": "OWNER_RATIFIED_BOUNDED_G6_ACTIVATION",
            "selected_packet_id": "NLE-PRPLAN-CORE-03-01",
            "module_id": "CORE-03",
            "risk": "LOW",
            "release_class": "INTERNAL_ONLY",
            "owner_authorization_ref": "STORM-CORE-01-IMPL-001/issue-387/2026-11-19/core03-governance-prep",
            "approved_adr": "docs/adr/0103-core-03-governance-gate.md",
            "approved_contract": "docs/contracts/core-03-governance-v0.md",
            "work_order": "docs/work-orders/NLE-PRPLAN-CORE-03-01.md",
            "activation_evidence": "docs/evidence/NLE-PRPLAN-CORE-03-01-G6-ACTIVATION.md",
            "gate_base_sha": "a24d65092da5401b5534a7ba13d3391b991dd94a",
            "requires_fresh_context_lock": True,
        }
        return expected, CORE03_01_ACTIVATION_SOURCES, CORE03_01_PINNED_SOURCE_BLOBS, {
            "source_blob_sha1", "gate_pr"
        }
    if selected == "NLE-PRPLAN-CORE-02-10":
        expected = {
            "schema_version": 2,
            "status": "OWNER_RATIFIED_BOUNDED_G6_ACTIVATION",
            "selected_packet_id": "NLE-PRPLAN-CORE-02-10",
            "module_id": "CORE-02",
            "risk": "STANDARD",
            "release_class": "INTERNAL_ONLY",
            "owner_authorization_ref": "STORM-CORE-01-IMPL-001/issue-387/2026-11-18/core01-core02-core03-continuous",
            "approved_adr": "docs/adr/0102-core-02-internal-sequence-closeout.md",
            "approved_contract": "docs/contracts/core-02-internal-sequence-closeout-v0.md",
            "work_order": "docs/work-orders/NLE-PRPLAN-CORE-02-10.md",
            "activation_evidence": "docs/evidence/NLE-PRPLAN-CORE-02-10-G6-ACTIVATION.md",
            "gate_base_sha": "3ad22f34167d76e31a9c88d8ca2a7f27a3a5a73c",
            "requires_fresh_context_lock": True,
        }
        return expected, CORE02_10_ACTIVATION_SOURCES, CORE02_10_PINNED_SOURCE_BLOBS, {
            "source_blob_sha1", "gate_pr"
        }
    if selected == "NLE-PRPLAN-CORE-02-09":
        expected = {
            "schema_version": 2,
            "status": "OWNER_RATIFIED_BOUNDED_G6_ACTIVATION",
            "selected_packet_id": "NLE-PRPLAN-CORE-02-09",
            "module_id": "CORE-02",
            "risk": "STANDARD",
            "release_class": "INTERNAL_ONLY",
            "owner_authorization_ref": "STORM-CORE-01-IMPL-001/issue-387/2026-11-18/core01-core02-core03-continuous",
            "approved_adr": "docs/adr/0101-core-02-integrated-memory-qualification.md",
            "approved_contract": "docs/contracts/core-02-integrated-memory-qualification-v0.md",
            "work_order": "docs/work-orders/NLE-PRPLAN-CORE-02-09.md",
            "activation_evidence": "docs/evidence/NLE-PRPLAN-CORE-02-09-G6-ACTIVATION.md",
            "gate_base_sha": "a20ff42cce2879657d357a52a9ba80052b9f7c02",
            "requires_fresh_context_lock": True,
        }
        return expected, CORE02_09_ACTIVATION_SOURCES, CORE02_09_PINNED_SOURCE_BLOBS, {
            "source_blob_sha1", "gate_pr", "capability_admission"
        }
    if selected == "NLE-PRPLAN-CORE-02-08":
        expected = {
            "schema_version": 2,
            "status": "OWNER_RATIFIED_BOUNDED_G6_ACTIVATION",
            "selected_packet_id": "NLE-PRPLAN-CORE-02-08",
            "module_id": "CORE-02",
            "risk": "STANDARD",
            "release_class": "INTERNAL_ONLY",
            "owner_authorization_ref": "STORM-CORE-01-IMPL-001/issue-387/2026-11-18/core01-core02-core03-continuous",
            "approved_adr": "docs/adr/0100-core-02-memory-telemetry.md",
            "approved_contract": "docs/contracts/core-02-memory-telemetry-v0.md",
            "work_order": "docs/work-orders/NLE-PRPLAN-CORE-02-08.md",
            "activation_evidence": "docs/evidence/NLE-PRPLAN-CORE-02-08-G6-ACTIVATION.md",
            "gate_base_sha": "dd76fceb6b9e835dd505c24a3c89065317528440",
            "requires_fresh_context_lock": True,
        }
        return expected, CORE02_08_ACTIVATION_SOURCES, CORE02_08_PINNED_SOURCE_BLOBS, {
            "source_blob_sha1", "gate_pr", "capability_admission"
        }
    if selected == "NLE-PRPLAN-CORE-02-07":
        expected = {
            "schema_version": 2,
            "status": "OWNER_RATIFIED_BOUNDED_G6_ACTIVATION",
            "selected_packet_id": "NLE-PRPLAN-CORE-02-07",
            "module_id": "CORE-02",
            "risk": "STANDARD",
            "release_class": "INTERNAL_ONLY",
            "owner_authorization_ref": "STORM-CORE-01-IMPL-001/issue-387/2026-11-17/next-increments",
            "approved_adr": "docs/adr/0099-core-02-leak-tracking.md",
            "approved_contract": "docs/contracts/core-02-leak-tracking-v0.md",
            "work_order": "docs/work-orders/NLE-PRPLAN-CORE-02-07.md",
            "activation_evidence": "docs/evidence/NLE-PRPLAN-CORE-02-07-G6-ACTIVATION.md",
            "gate_base_sha": "74524e55237436a6b4501aab58b31e76cd1d5479",
            "requires_fresh_context_lock": True,
        }
        return expected, CORE02_07_ACTIVATION_SOURCES, CORE02_07_PINNED_SOURCE_BLOBS, {
            "source_blob_sha1", "gate_pr", "capability_admission"
        }
    if selected == "NLE-PRPLAN-CORE-02-06":
        expected = {
            "schema_version": 2,
            "status": "OWNER_RATIFIED_BOUNDED_G6_ACTIVATION",
            "selected_packet_id": "NLE-PRPLAN-CORE-02-06",
            "module_id": "CORE-02",
            "risk": "STANDARD",
            "release_class": "INTERNAL_ONLY",
            "owner_authorization_ref": "STORM-CORE-01-IMPL-001/issue-387/2026-11-17/next-increments",
            "approved_adr": "docs/adr/0098-core-02-memory-budget.md",
            "approved_contract": "docs/contracts/core-02-memory-budget-v0.md",
            "work_order": "docs/work-orders/NLE-PRPLAN-CORE-02-06.md",
            "activation_evidence": "docs/evidence/NLE-PRPLAN-CORE-02-06-G6-ACTIVATION.md",
            "gate_base_sha": "42ab4b74b686e9856c150101895a9e6182c964b5",
            "requires_fresh_context_lock": True,
        }
        return expected, CORE02_06_ACTIVATION_SOURCES, CORE02_06_PINNED_SOURCE_BLOBS, {
            "source_blob_sha1", "gate_pr", "capability_admission"
        }
    if selected == "NLE-PRPLAN-CORE-02-05":
        expected = {
            "schema_version": 2,
            "status": "OWNER_RATIFIED_BOUNDED_G6_ACTIVATION",
            "selected_packet_id": "NLE-PRPLAN-CORE-02-05",
            "module_id": "CORE-02",
            "risk": "STANDARD",
            "release_class": "INTERNAL_ONLY",
            "owner_authorization_ref": "STORM-CORE-01-IMPL-001/issue-387/2026-11-17/next-increments",
            "approved_adr": "docs/adr/0097-core-02-monotonic-arena.md",
            "approved_contract": "docs/contracts/core-02-monotonic-arena-v0.md",
            "work_order": "docs/work-orders/NLE-PRPLAN-CORE-02-05.md",
            "activation_evidence": "docs/evidence/NLE-PRPLAN-CORE-02-05-G6-ACTIVATION.md",
            "gate_base_sha": "9d49dc3da22d245daf1df95d0f27ee56588904af",
            "requires_fresh_context_lock": True,
        }
        return expected, CORE02_05_ACTIVATION_SOURCES, CORE02_05_PINNED_SOURCE_BLOBS, {
            "source_blob_sha1", "gate_pr", "capability_admission"
        }
    if selected == "NLE-PRPLAN-CORE-02-04":
        expected = {
            "schema_version": 2,
            "status": "OWNER_RATIFIED_BOUNDED_G6_ACTIVATION",
            "selected_packet_id": "NLE-PRPLAN-CORE-02-04",
            "module_id": "CORE-02",
            "risk": "STANDARD",
            "release_class": "INTERNAL_ONLY",
            "owner_authorization_ref": "STORM-CORE-01-IMPL-001/issue-387/2026-11-17/next-increments",
            "approved_adr": "docs/adr/0096-core-02-system-allocator-baseline.md",
            "approved_contract": "docs/contracts/core-02-system-allocator-v0.md",
            "work_order": "docs/work-orders/NLE-PRPLAN-CORE-02-04.md",
            "activation_evidence": "docs/evidence/NLE-PRPLAN-CORE-02-04-G6-ACTIVATION.md",
            "gate_base_sha": "4920c2f4e3bf787f58c867c2df5bd321eaca8729",
            "requires_fresh_context_lock": True,
        }
        return expected, CORE02_04_ACTIVATION_SOURCES, CORE02_04_PINNED_SOURCE_BLOBS, {
            "source_blob_sha1", "gate_pr", "capability_admission"
        }
    if selected == "NLE-PRPLAN-CORE-01-16":
        expected = {
            "schema_version": 2,
            "status": "OWNER_RATIFIED_BOUNDED_G6_ACTIVATION",
            "selected_packet_id": "NLE-PRPLAN-CORE-01-16",
            "module_id": "CORE-01",
            "risk": "STANDARD",
            "release_class": "INTERNAL_ONLY",
            "owner_authorization_ref": "STORM-CORE-01-IMPL-001/issue-387/2026-11-17/next-increments",
            "approved_adr": "docs/adr/0095-core-01-internal-sequence-closeout.md",
            "approved_contract": "docs/contracts/core-01-internal-sequence-closeout-v0.md",
            "work_order": "docs/work-orders/NLE-PRPLAN-CORE-01-16.md",
            "activation_evidence": "docs/evidence/NLE-PRPLAN-CORE-01-16-G6-ACTIVATION.md",
            "gate_base_sha": "30e254716b127b1a5ceb33c7527c3dd413c75665",
            "requires_fresh_context_lock": True,
        }
        return expected, CORE01_16_ACTIVATION_SOURCES, CORE01_16_PINNED_SOURCE_BLOBS, {
            "source_blob_sha1", "gate_pr"
        }
    if selected == "NLE-PRPLAN-CORE-01-15":
        expected = {
            "schema_version": 2,
            "status": "OWNER_RATIFIED_BOUNDED_G6_ACTIVATION",
            "selected_packet_id": "NLE-PRPLAN-CORE-01-15",
            "module_id": "CORE-01",
            "risk": "STANDARD",
            "release_class": "INTERNAL_ONLY",
            "owner_authorization_ref": "STORM-CORE-01-IMPL-001/issue-387/2026-11-17/next-increments",
            "approved_adr": "docs/adr/0094-core-01-integrated-ci-qualification.md",
            "approved_contract": "docs/contracts/core-01-integrated-qualification-v0.md",
            "work_order": "docs/work-orders/NLE-PRPLAN-CORE-01-15.md",
            "activation_evidence": "docs/evidence/NLE-PRPLAN-CORE-01-15-G6-ACTIVATION.md",
            "gate_base_sha": "ee7f3188eee314b7f051ef39ce4c88ab74492fb1",
            "requires_fresh_context_lock": True,
        }
        return expected, CORE01_15_ACTIVATION_SOURCES, CORE01_15_PINNED_SOURCE_BLOBS, {
            "source_blob_sha1", "gate_pr"
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
        selected_id = str(activation.get("selected_packet_id", ""))
        if selected_id.startswith("NLE-PRPLAN-CORE-05-"):
            expected_admission = CORE04_CAPABILITY_ADMISSION
        elif selected_id.startswith("NLE-PRPLAN-CORE-04-"):
            expected_admission = CORE04_CAPABILITY_ADMISSION
        elif selected_id.startswith("NLE-PRPLAN-CORE-03-"):
            expected_admission = CORE03_CAPABILITY_ADMISSION
        else:
            expected_admission = CORE02_CAPABILITY_ADMISSION
        if activation.get("capability_admission") != expected_admission:
            errors.append("activation capability admission mismatch: only the exact audited set is authorized")
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
    if activation is not None and activation.get("selected_packet_id") == "NLE-PRPLAN-CORE-05-08":
        if module_id == "CORE-05":
            if idx == 1:
                return "APPROVED_GOVERNANCE", CORE05_01_GATE_PR
            if idx == 2:
                return "APPROVED_CONTRACT", CORE05_02_GATE_PR
            if idx == 3:
                return "COMPLETED", CORE05_03_CLOSEOUT_PR
            if idx == 4:
                return "COMPLETED", CORE05_04_CLOSEOUT_PR
            if idx == 5:
                return "COMPLETED", CORE05_05_CLOSEOUT_PR
            if idx == 6:
                return "COMPLETED", CORE05_06_CLOSEOUT_PR
            if idx == 7:
                return "COMPLETED", CORE05_07_CLOSEOUT_PR
            if idx == 8:
                if manifest_status == CORE05_08_COMPLETED_STATUS:
                    return "COMPLETED", CORE05_08_CLOSEOUT_PR
                return "EXECUTOR_READY", None
            return "PLANNED_BLOCKED", None
        activation = {"selected_packet_id": "NLE-PRPLAN-CORE-05-07"}
    if activation is not None and activation.get("selected_packet_id") == "NLE-PRPLAN-CORE-05-07":
        if module_id == "CORE-05":
            if idx == 1:
                return "APPROVED_GOVERNANCE", CORE05_01_GATE_PR
            if idx == 2:
                return "APPROVED_CONTRACT", CORE05_02_GATE_PR
            if idx == 3:
                return "COMPLETED", CORE05_03_CLOSEOUT_PR
            if idx == 4:
                return "COMPLETED", CORE05_04_CLOSEOUT_PR
            if idx == 5:
                return "COMPLETED", CORE05_05_CLOSEOUT_PR
            if idx == 6:
                return "COMPLETED", CORE05_06_CLOSEOUT_PR
            if idx == 7:
                if manifest_status == CORE05_07_COMPLETED_STATUS:
                    return "COMPLETED", CORE05_07_CLOSEOUT_PR
                return "EXECUTOR_READY", None
            return "PLANNED_BLOCKED", None
        activation = {"selected_packet_id": "NLE-PRPLAN-CORE-05-06"}
    if activation is not None and activation.get("selected_packet_id") == "NLE-PRPLAN-CORE-05-06":
        if module_id == "CORE-05":
            if idx == 1:
                return "APPROVED_GOVERNANCE", CORE05_01_GATE_PR
            if idx == 2:
                return "APPROVED_CONTRACT", CORE05_02_GATE_PR
            if idx == 3:
                return "COMPLETED", CORE05_03_CLOSEOUT_PR
            if idx == 4:
                return "COMPLETED", CORE05_04_CLOSEOUT_PR
            if idx == 5:
                return "COMPLETED", CORE05_05_CLOSEOUT_PR
            if idx == 6:
                if manifest_status == CORE05_06_COMPLETED_STATUS:
                    return "COMPLETED", CORE05_06_CLOSEOUT_PR
                return "EXECUTOR_READY", None
            return "PLANNED_BLOCKED", None
        activation = {"selected_packet_id": "NLE-PRPLAN-CORE-05-05"}
    if activation is not None and activation.get("selected_packet_id") == "NLE-PRPLAN-CORE-05-05":
        if module_id == "CORE-05":
            if idx == 1:
                return "APPROVED_GOVERNANCE", CORE05_01_GATE_PR
            if idx == 2:
                return "APPROVED_CONTRACT", CORE05_02_GATE_PR
            if idx == 3:
                return "COMPLETED", CORE05_03_CLOSEOUT_PR
            if idx == 4:
                return "COMPLETED", CORE05_04_CLOSEOUT_PR
            if idx == 5:
                if manifest_status == CORE05_05_COMPLETED_STATUS:
                    return "COMPLETED", CORE05_05_CLOSEOUT_PR
                return "EXECUTOR_READY", None
            return "PLANNED_BLOCKED", None
        activation = {"selected_packet_id": "NLE-PRPLAN-CORE-05-04"}
    if activation is not None and activation.get("selected_packet_id") == "NLE-PRPLAN-CORE-05-04":
        if module_id == "CORE-05":
            if idx == 1:
                return "APPROVED_GOVERNANCE", CORE05_01_GATE_PR
            if idx == 2:
                return "APPROVED_CONTRACT", CORE05_02_GATE_PR
            if idx == 3:
                return "COMPLETED", CORE05_03_CLOSEOUT_PR
            if idx == 4:
                if manifest_status == CORE05_04_COMPLETED_STATUS:
                    return "COMPLETED", CORE05_04_CLOSEOUT_PR
                return "EXECUTOR_READY", None
            return "PLANNED_BLOCKED", None
        activation = {"selected_packet_id": "NLE-PRPLAN-CORE-05-03"}
    if activation is not None and activation.get("selected_packet_id") == "NLE-PRPLAN-CORE-05-03":
        if module_id == "CORE-05":
            if idx == 1:
                return "APPROVED_GOVERNANCE", CORE05_01_GATE_PR
            if idx == 2:
                return "APPROVED_CONTRACT", CORE05_02_GATE_PR
            if idx == 3:
                if manifest_status == CORE05_03_COMPLETED_STATUS:
                    return "COMPLETED", CORE05_03_CLOSEOUT_PR
                return "EXECUTOR_READY", None
            return "PLANNED_BLOCKED", None
        activation = {"selected_packet_id": "NLE-PRPLAN-CORE-05-02"}
    if activation is not None and activation.get("selected_packet_id") == "NLE-PRPLAN-CORE-05-02":
        if module_id == "CORE-05":
            if idx == 1:
                return "APPROVED_GOVERNANCE", CORE05_01_GATE_PR
            if idx == 2:
                return "APPROVED_CONTRACT", CORE05_02_GATE_PR
            return "PLANNED_BLOCKED", None
        activation = {"selected_packet_id": "NLE-PRPLAN-CORE-05-01"}
    if (activation is not None
            and activation.get("selected_packet_id") == "NLE-PRPLAN-CORE-03-01"
            and module_id == "CORE-01"):
        if idx == 1:
            return "APPROVED_GOVERNANCE", 422
        if idx == 2:
            return "APPROVED_CONTRACT", 424
        code_prs = {
            3: 428, 4: 428, 5: 428, 6: 432, 7: 435, 8: 438,
            9: 444, 10: 447, 11: 450, 12: 453, 13: 456, 14: 459,
            15: 462, 16: 464,
        }
        if idx in code_prs:
            return "COMPLETED", code_prs[idx]
        return "PLANNED_BLOCKED", None
    if (activation is not None
            and activation.get("selected_packet_id") == "NLE-PRPLAN-CORE-03-01"
            and module_id == "CORE-02"):
        if idx == 1:
            return "APPROVED_GOVERNANCE", CORE02_03_GATE_PR
        if idx == 2:
            return "APPROVED_CONTRACT", CORE02_03_GATE_PR
        if idx == 3:
            return "COMPLETED", CORE02_03_CODE_PR
        if idx == 4:
            return "COMPLETED", CORE02_04_CODE_PR
        if idx == 5:
            return "COMPLETED", CORE02_05_CODE_PR
        if idx == 6:
            return "COMPLETED", CORE02_06_CODE_PR
        if idx == 7:
            return "COMPLETED", CORE02_07_CODE_PR
        if idx == 8:
            return "COMPLETED", CORE02_08_CODE_PR
        if idx == 9:
            return "COMPLETED", CORE02_09_CODE_PR
        if idx == 10:
            return "COMPLETED", CORE02_10_CODE_PR
        return "PLANNED_BLOCKED", None
    if (activation is not None
            and activation.get("selected_packet_id") == "NLE-PRPLAN-CORE-05-01"
            and module_id == "CORE-01"):
        if idx == 1:
            return "APPROVED_GOVERNANCE", 422
        if idx == 2:
            return "APPROVED_CONTRACT", 424
        code_prs = {
            3: 428, 4: 428, 5: 428, 6: 432, 7: 435, 8: 438,
            9: 444, 10: 447, 11: 450, 12: 453, 13: 456, 14: 459,
            15: 462, 16: 464,
        }
        if idx in code_prs:
            return "COMPLETED", code_prs[idx]
        return "PLANNED_BLOCKED", None
    if (activation is not None
            and activation.get("selected_packet_id") == "NLE-PRPLAN-CORE-05-01"
            and module_id == "CORE-02"):
        if idx == 1:
            return "APPROVED_GOVERNANCE", CORE02_03_GATE_PR
        if idx == 2:
            return "APPROVED_CONTRACT", CORE02_03_GATE_PR
        code_prs = {
            3: CORE02_03_CODE_PR, 4: CORE02_04_CODE_PR, 5: CORE02_05_CODE_PR,
            6: CORE02_06_CODE_PR, 7: CORE02_07_CODE_PR, 8: CORE02_08_CODE_PR,
            9: CORE02_09_CODE_PR, 10: CORE02_10_CODE_PR,
        }
        if idx in code_prs:
            return "COMPLETED", code_prs[idx]
        return "PLANNED_BLOCKED", None
    if (activation is not None
            and activation.get("selected_packet_id") == "NLE-PRPLAN-CORE-05-01"
            and module_id == "CORE-03"):
        if idx == 1:
            return "APPROVED_GOVERNANCE", CORE03_01_GATE_PR
        if idx == 2:
            return "APPROVED_CONTRACT", CORE03_02_GATE_PR
        code_prs = {
            3: CORE03_03_CODE_PR, 4: CORE03_04_CLOSEOUT_PR, 5: CORE03_05_CLOSEOUT_PR,
            6: CORE03_06_CLOSEOUT_PR, 7: CORE03_07_CLOSEOUT_PR, 8: CORE03_08_CLOSEOUT_PR,
            9: CORE03_09_CODE_PR, 10: CORE03_10_CLOSEOUT_PR,
        }
        if idx in code_prs:
            return "COMPLETED", code_prs[idx]
        return "PLANNED_BLOCKED", None
    if (activation is not None
            and activation.get("selected_packet_id") == "NLE-PRPLAN-CORE-05-01"
            and module_id == "CORE-04"):
        if idx == 1:
            return "APPROVED_GOVERNANCE", CORE04_01_GATE_PR
        if idx == 2:
            return "APPROVED_CONTRACT", CORE04_02_GATE_PR
        code_prs = {
            3: CORE04_03_CODE_PR, 4: CORE04_04_CODE_PR, 5: CORE04_05_CLOSEOUT_PR,
            6: CORE04_06_CLOSEOUT_PR, 7: CORE04_07_CLOSEOUT_PR, 8: CORE04_08_CLOSEOUT_PR,
            9: CORE04_09_CODE_PR, 10: CORE04_10_CLOSEOUT_PR,
        }
        if idx in code_prs:
            return "COMPLETED", code_prs[idx]
        return "PLANNED_BLOCKED", None
    if (activation is not None
            and activation.get("selected_packet_id") == "NLE-PRPLAN-CORE-05-01"
            and module_id == "CORE-05"):
        if idx == 1:
            return "APPROVED_GOVERNANCE", CORE05_01_GATE_PR
        return "PLANNED_BLOCKED", None
    if (activation is not None
            and activation.get("selected_packet_id") == "NLE-PRPLAN-CORE-04-09"
            and module_id == "CORE-01"):
        if idx == 1:
            return "APPROVED_GOVERNANCE", 422
        if idx == 2:
            return "APPROVED_CONTRACT", 424
        code_prs = {
            3: 428, 4: 428, 5: 428, 6: 432, 7: 435, 8: 438,
            9: 444, 10: 447, 11: 450, 12: 453, 13: 456, 14: 459,
            15: 462, 16: 464,
        }
        if idx in code_prs:
            return "COMPLETED", code_prs[idx]
        return "PLANNED_BLOCKED", None
    if (activation is not None
            and activation.get("selected_packet_id") == "NLE-PRPLAN-CORE-04-09"
            and module_id == "CORE-02"):
        if idx == 1:
            return "APPROVED_GOVERNANCE", CORE02_03_GATE_PR
        if idx == 2:
            return "APPROVED_CONTRACT", CORE02_03_GATE_PR
        if idx == 3:
            return "COMPLETED", CORE02_03_CODE_PR
        if idx == 4:
            return "COMPLETED", CORE02_04_CODE_PR
        if idx == 5:
            return "COMPLETED", CORE02_05_CODE_PR
        if idx == 6:
            return "COMPLETED", CORE02_06_CODE_PR
        if idx == 7:
            return "COMPLETED", CORE02_07_CODE_PR
        if idx == 8:
            return "COMPLETED", CORE02_08_CODE_PR
        if idx == 9:
            return "COMPLETED", CORE02_09_CODE_PR
        if idx == 10:
            return "COMPLETED", CORE02_10_CODE_PR
        return "PLANNED_BLOCKED", None
    if (activation is not None
            and activation.get("selected_packet_id") == "NLE-PRPLAN-CORE-04-09"
            and module_id == "CORE-03"):
        if idx == 1:
            return "APPROVED_GOVERNANCE", CORE03_01_GATE_PR
        if idx == 2:
            return "APPROVED_CONTRACT", CORE03_02_GATE_PR
        if idx == 3:
            return "COMPLETED", CORE03_03_CODE_PR
        if idx == 4:
            return "COMPLETED", CORE03_04_CLOSEOUT_PR
        if idx == 5:
            return "COMPLETED", CORE03_05_CLOSEOUT_PR
        if idx == 6:
            return "COMPLETED", CORE03_06_CLOSEOUT_PR
        if idx == 7:
            return "COMPLETED", CORE03_07_CLOSEOUT_PR
        if idx == 8:
            return "COMPLETED", CORE03_08_CLOSEOUT_PR
        if idx == 9:
            return "COMPLETED", CORE03_09_CODE_PR
        if idx == 10:
            return "COMPLETED", CORE03_10_CLOSEOUT_PR
        return "PLANNED_BLOCKED", None
    if (activation is not None
            and activation.get("selected_packet_id") == "NLE-PRPLAN-CORE-04-09"
            and module_id == "CORE-04"):
        if idx == 1:
            return "APPROVED_GOVERNANCE", CORE04_01_GATE_PR
        if idx == 2:
            return "APPROVED_CONTRACT", CORE04_02_GATE_PR
        if idx == 3:
            return "COMPLETED", CORE04_03_CODE_PR
        if idx == 4:
            return "COMPLETED", CORE04_04_CODE_PR
        if idx == 5:
            return "COMPLETED", CORE04_05_CLOSEOUT_PR
        if idx == 6:
            return "COMPLETED", CORE04_06_CLOSEOUT_PR
        if idx == 7:
            return "COMPLETED", CORE04_07_CLOSEOUT_PR
        if idx == 8:
            return "COMPLETED", CORE04_08_CLOSEOUT_PR
        if idx == 9:
            if manifest_status in (CORE04_09_COMPLETED_STATUS, CORE04_10_COMPLETED_STATUS):
                return "COMPLETED", CORE04_09_CODE_PR
            return "EXECUTOR_READY", None
        if idx == 10:
            if manifest_status == CORE04_10_COMPLETED_STATUS:
                return "COMPLETED", CORE04_10_CLOSEOUT_PR
            return "PLANNED_BLOCKED", None
        return "PLANNED_BLOCKED", None
    if (activation is not None
            and activation.get("selected_packet_id") == "NLE-PRPLAN-CORE-04-04"
            and module_id == "CORE-01"):
        if idx == 1:
            return "APPROVED_GOVERNANCE", 422
        if idx == 2:
            return "APPROVED_CONTRACT", 424
        code_prs = {
            3: 428, 4: 428, 5: 428, 6: 432, 7: 435, 8: 438,
            9: 444, 10: 447, 11: 450, 12: 453, 13: 456, 14: 459,
            15: 462, 16: 464,
        }
        if idx in code_prs:
            return "COMPLETED", code_prs[idx]
        return "PLANNED_BLOCKED", None
    if (activation is not None
            and activation.get("selected_packet_id") == "NLE-PRPLAN-CORE-04-04"
            and module_id == "CORE-02"):
        if idx == 1:
            return "APPROVED_GOVERNANCE", CORE02_03_GATE_PR
        if idx == 2:
            return "APPROVED_CONTRACT", CORE02_03_GATE_PR
        if idx == 3:
            return "COMPLETED", CORE02_03_CODE_PR
        if idx == 4:
            return "COMPLETED", CORE02_04_CODE_PR
        if idx == 5:
            return "COMPLETED", CORE02_05_CODE_PR
        if idx == 6:
            return "COMPLETED", CORE02_06_CODE_PR
        if idx == 7:
            return "COMPLETED", CORE02_07_CODE_PR
        if idx == 8:
            return "COMPLETED", CORE02_08_CODE_PR
        if idx == 9:
            return "COMPLETED", CORE02_09_CODE_PR
        if idx == 10:
            return "COMPLETED", CORE02_10_CODE_PR
        return "PLANNED_BLOCKED", None
    if (activation is not None
            and activation.get("selected_packet_id") == "NLE-PRPLAN-CORE-04-04"
            and module_id == "CORE-03"):
        if idx == 1:
            return "APPROVED_GOVERNANCE", CORE03_01_GATE_PR
        if idx == 2:
            return "APPROVED_CONTRACT", CORE03_02_GATE_PR
        if idx == 3:
            return "COMPLETED", CORE03_03_CODE_PR
        if idx == 4:
            return "COMPLETED", CORE03_04_CLOSEOUT_PR
        if idx == 5:
            return "COMPLETED", CORE03_05_CLOSEOUT_PR
        if idx == 6:
            return "COMPLETED", CORE03_06_CLOSEOUT_PR
        if idx == 7:
            return "COMPLETED", CORE03_07_CLOSEOUT_PR
        if idx == 8:
            return "COMPLETED", CORE03_08_CLOSEOUT_PR
        if idx == 9:
            return "COMPLETED", CORE03_09_CODE_PR
        if idx == 10:
            return "COMPLETED", CORE03_10_CLOSEOUT_PR
        return "PLANNED_BLOCKED", None
    if (activation is not None
            and activation.get("selected_packet_id") == "NLE-PRPLAN-CORE-04-04"
            and module_id == "CORE-04"):
        if idx == 1:
            return "APPROVED_GOVERNANCE", CORE04_01_GATE_PR
        if idx == 2:
            return "APPROVED_CONTRACT", CORE04_02_GATE_PR
        if idx == 3:
            return "COMPLETED", CORE04_03_CODE_PR
        if idx == 4:
            if manifest_status in (CORE04_04_COMPLETED_STATUS, CORE04_05_COMPLETED_STATUS,
                                   CORE04_06_COMPLETED_STATUS, CORE04_07_COMPLETED_STATUS,
                                   CORE04_08_COMPLETED_STATUS):
                return "COMPLETED", CORE04_04_CODE_PR
            return "EXECUTOR_READY", None
        if idx == 5:
            if manifest_status in (CORE04_05_COMPLETED_STATUS, CORE04_06_COMPLETED_STATUS,
                                   CORE04_07_COMPLETED_STATUS, CORE04_08_COMPLETED_STATUS):
                return "COMPLETED", CORE04_05_CLOSEOUT_PR
            return "PLANNED_BLOCKED", None
        if idx == 6:
            if manifest_status in (CORE04_06_COMPLETED_STATUS, CORE04_07_COMPLETED_STATUS,
                                   CORE04_08_COMPLETED_STATUS):
                return "COMPLETED", CORE04_06_CLOSEOUT_PR
            return "PLANNED_BLOCKED", None
        if idx == 7:
            if manifest_status in (CORE04_07_COMPLETED_STATUS, CORE04_08_COMPLETED_STATUS):
                return "COMPLETED", CORE04_07_CLOSEOUT_PR
            return "PLANNED_BLOCKED", None
        if idx == 8:
            if manifest_status == CORE04_08_COMPLETED_STATUS:
                return "COMPLETED", CORE04_08_CLOSEOUT_PR
            return "PLANNED_BLOCKED", None
        return "PLANNED_BLOCKED", None
    if (activation is not None
            and activation.get("selected_packet_id") == "NLE-PRPLAN-CORE-04-03"
            and module_id == "CORE-01"):
        if idx == 1:
            return "APPROVED_GOVERNANCE", 422
        if idx == 2:
            return "APPROVED_CONTRACT", 424
        code_prs = {
            3: 428, 4: 428, 5: 428, 6: 432, 7: 435, 8: 438,
            9: 444, 10: 447, 11: 450, 12: 453, 13: 456, 14: 459,
            15: 462, 16: 464,
        }
        if idx in code_prs:
            return "COMPLETED", code_prs[idx]
        return "PLANNED_BLOCKED", None
    if (activation is not None
            and activation.get("selected_packet_id") == "NLE-PRPLAN-CORE-04-03"
            and module_id == "CORE-02"):
        if idx == 1:
            return "APPROVED_GOVERNANCE", CORE02_03_GATE_PR
        if idx == 2:
            return "APPROVED_CONTRACT", CORE02_03_GATE_PR
        if idx == 3:
            return "COMPLETED", CORE02_03_CODE_PR
        if idx == 4:
            return "COMPLETED", CORE02_04_CODE_PR
        if idx == 5:
            return "COMPLETED", CORE02_05_CODE_PR
        if idx == 6:
            return "COMPLETED", CORE02_06_CODE_PR
        if idx == 7:
            return "COMPLETED", CORE02_07_CODE_PR
        if idx == 8:
            return "COMPLETED", CORE02_08_CODE_PR
        if idx == 9:
            return "COMPLETED", CORE02_09_CODE_PR
        if idx == 10:
            return "COMPLETED", CORE02_10_CODE_PR
        return "PLANNED_BLOCKED", None
    if (activation is not None
            and activation.get("selected_packet_id") == "NLE-PRPLAN-CORE-04-03"
            and module_id == "CORE-03"):
        if idx == 1:
            return "APPROVED_GOVERNANCE", CORE03_01_GATE_PR
        if idx == 2:
            return "APPROVED_CONTRACT", CORE03_02_GATE_PR
        if idx == 3:
            return "COMPLETED", CORE03_03_CODE_PR
        if idx == 4:
            return "COMPLETED", CORE03_04_CLOSEOUT_PR
        if idx == 5:
            return "COMPLETED", CORE03_05_CLOSEOUT_PR
        if idx == 6:
            return "COMPLETED", CORE03_06_CLOSEOUT_PR
        if idx == 7:
            return "COMPLETED", CORE03_07_CLOSEOUT_PR
        if idx == 8:
            return "COMPLETED", CORE03_08_CLOSEOUT_PR
        if idx == 9:
            return "COMPLETED", CORE03_09_CODE_PR
        if idx == 10:
            return "COMPLETED", CORE03_10_CLOSEOUT_PR
        return "PLANNED_BLOCKED", None
    if (activation is not None
            and activation.get("selected_packet_id") == "NLE-PRPLAN-CORE-04-03"
            and module_id == "CORE-04"):
        if idx == 1:
            return "APPROVED_GOVERNANCE", CORE04_01_GATE_PR
        if idx == 2:
            return "APPROVED_CONTRACT", CORE04_02_GATE_PR
        if idx == 3:
            if manifest_status == CORE04_03_COMPLETED_STATUS:
                return "COMPLETED", CORE04_03_CODE_PR
            return "EXECUTOR_READY", None
        return "PLANNED_BLOCKED", None
    if (activation is not None
            and activation.get("selected_packet_id") == "NLE-PRPLAN-CORE-04-02"
            and module_id == "CORE-01"):
        if idx == 1:
            return "APPROVED_GOVERNANCE", 422
        if idx == 2:
            return "APPROVED_CONTRACT", 424
        code_prs = {
            3: 428, 4: 428, 5: 428, 6: 432, 7: 435, 8: 438,
            9: 444, 10: 447, 11: 450, 12: 453, 13: 456, 14: 459,
            15: 462, 16: 464,
        }
        if idx in code_prs:
            return "COMPLETED", code_prs[idx]
        return "PLANNED_BLOCKED", None
    if (activation is not None
            and activation.get("selected_packet_id") == "NLE-PRPLAN-CORE-04-02"
            and module_id == "CORE-02"):
        if idx == 1:
            return "APPROVED_GOVERNANCE", CORE02_03_GATE_PR
        if idx == 2:
            return "APPROVED_CONTRACT", CORE02_03_GATE_PR
        if idx == 3:
            return "COMPLETED", CORE02_03_CODE_PR
        if idx == 4:
            return "COMPLETED", CORE02_04_CODE_PR
        if idx == 5:
            return "COMPLETED", CORE02_05_CODE_PR
        if idx == 6:
            return "COMPLETED", CORE02_06_CODE_PR
        if idx == 7:
            return "COMPLETED", CORE02_07_CODE_PR
        if idx == 8:
            return "COMPLETED", CORE02_08_CODE_PR
        if idx == 9:
            return "COMPLETED", CORE02_09_CODE_PR
        if idx == 10:
            return "COMPLETED", CORE02_10_CODE_PR
        return "PLANNED_BLOCKED", None
    if (activation is not None
            and activation.get("selected_packet_id") == "NLE-PRPLAN-CORE-04-02"
            and module_id == "CORE-03"):
        if idx == 1:
            return "APPROVED_GOVERNANCE", CORE03_01_GATE_PR
        if idx == 2:
            return "APPROVED_CONTRACT", CORE03_02_GATE_PR
        if idx == 3:
            return "COMPLETED", CORE03_03_CODE_PR
        if idx == 4:
            return "COMPLETED", CORE03_04_CLOSEOUT_PR
        if idx == 5:
            return "COMPLETED", CORE03_05_CLOSEOUT_PR
        if idx == 6:
            return "COMPLETED", CORE03_06_CLOSEOUT_PR
        if idx == 7:
            return "COMPLETED", CORE03_07_CLOSEOUT_PR
        if idx == 8:
            return "COMPLETED", CORE03_08_CLOSEOUT_PR
        if idx == 9:
            return "COMPLETED", CORE03_09_CODE_PR
        if idx == 10:
            return "COMPLETED", CORE03_10_CLOSEOUT_PR
        return "PLANNED_BLOCKED", None
    if (activation is not None
            and activation.get("selected_packet_id") == "NLE-PRPLAN-CORE-04-02"
            and module_id == "CORE-04"):
        if idx == 1:
            return "APPROVED_GOVERNANCE", CORE04_01_GATE_PR
        if idx == 2:
            return "APPROVED_CONTRACT", CORE04_02_GATE_PR
        return "PLANNED_BLOCKED", None
    if (activation is not None
            and activation.get("selected_packet_id") == "NLE-PRPLAN-CORE-04-01"
            and module_id == "CORE-01"):
        if idx == 1:
            return "APPROVED_GOVERNANCE", 422
        if idx == 2:
            return "APPROVED_CONTRACT", 424
        code_prs = {
            3: 428, 4: 428, 5: 428, 6: 432, 7: 435, 8: 438,
            9: 444, 10: 447, 11: 450, 12: 453, 13: 456, 14: 459,
            15: 462, 16: 464,
        }
        if idx in code_prs:
            return "COMPLETED", code_prs[idx]
        return "PLANNED_BLOCKED", None
    if (activation is not None
            and activation.get("selected_packet_id") == "NLE-PRPLAN-CORE-04-01"
            and module_id == "CORE-02"):
        if idx == 1:
            return "APPROVED_GOVERNANCE", CORE02_03_GATE_PR
        if idx == 2:
            return "APPROVED_CONTRACT", CORE02_03_GATE_PR
        if idx == 3:
            return "COMPLETED", CORE02_03_CODE_PR
        if idx == 4:
            return "COMPLETED", CORE02_04_CODE_PR
        if idx == 5:
            return "COMPLETED", CORE02_05_CODE_PR
        if idx == 6:
            return "COMPLETED", CORE02_06_CODE_PR
        if idx == 7:
            return "COMPLETED", CORE02_07_CODE_PR
        if idx == 8:
            return "COMPLETED", CORE02_08_CODE_PR
        if idx == 9:
            return "COMPLETED", CORE02_09_CODE_PR
        if idx == 10:
            return "COMPLETED", CORE02_10_CODE_PR
        return "PLANNED_BLOCKED", None
    if (activation is not None
            and activation.get("selected_packet_id") == "NLE-PRPLAN-CORE-04-01"
            and module_id == "CORE-03"):
        if idx == 1:
            return "APPROVED_GOVERNANCE", CORE03_01_GATE_PR
        if idx == 2:
            return "APPROVED_CONTRACT", CORE03_02_GATE_PR
        if idx == 3:
            return "COMPLETED", CORE03_03_CODE_PR
        if idx == 4:
            return "COMPLETED", CORE03_04_CLOSEOUT_PR
        if idx == 5:
            return "COMPLETED", CORE03_05_CLOSEOUT_PR
        if idx == 6:
            return "COMPLETED", CORE03_06_CLOSEOUT_PR
        if idx == 7:
            return "COMPLETED", CORE03_07_CLOSEOUT_PR
        if idx == 8:
            return "COMPLETED", CORE03_08_CLOSEOUT_PR
        if idx == 9:
            return "COMPLETED", CORE03_09_CODE_PR
        if idx == 10:
            return "COMPLETED", CORE03_10_CLOSEOUT_PR
        return "PLANNED_BLOCKED", None
    if (activation is not None
            and activation.get("selected_packet_id") == "NLE-PRPLAN-CORE-04-01"
            and module_id == "CORE-04"):
        if idx == 1:
            return "APPROVED_GOVERNANCE", CORE04_01_GATE_PR
        return "PLANNED_BLOCKED", None
    if (activation is not None
            and activation.get("selected_packet_id") == "NLE-PRPLAN-CORE-03-09"
            and module_id == "CORE-01"):
        if idx == 1:
            return "APPROVED_GOVERNANCE", 422
        if idx == 2:
            return "APPROVED_CONTRACT", 424
        code_prs = {
            3: 428, 4: 428, 5: 428, 6: 432, 7: 435, 8: 438,
            9: 444, 10: 447, 11: 450, 12: 453, 13: 456, 14: 459,
            15: 462, 16: 464,
        }
        if idx in code_prs:
            return "COMPLETED", code_prs[idx]
        return "PLANNED_BLOCKED", None
    if (activation is not None
            and activation.get("selected_packet_id") == "NLE-PRPLAN-CORE-03-09"
            and module_id == "CORE-02"):
        if idx == 1:
            return "APPROVED_GOVERNANCE", CORE02_03_GATE_PR
        if idx == 2:
            return "APPROVED_CONTRACT", CORE02_03_GATE_PR
        if idx == 3:
            return "COMPLETED", CORE02_03_CODE_PR
        if idx == 4:
            return "COMPLETED", CORE02_04_CODE_PR
        if idx == 5:
            return "COMPLETED", CORE02_05_CODE_PR
        if idx == 6:
            return "COMPLETED", CORE02_06_CODE_PR
        if idx == 7:
            return "COMPLETED", CORE02_07_CODE_PR
        if idx == 8:
            return "COMPLETED", CORE02_08_CODE_PR
        if idx == 9:
            return "COMPLETED", CORE02_09_CODE_PR
        if idx == 10:
            return "COMPLETED", CORE02_10_CODE_PR
        return "PLANNED_BLOCKED", None
    if (activation is not None
            and activation.get("selected_packet_id") == "NLE-PRPLAN-CORE-03-09"
            and module_id == "CORE-03"):
        if idx == 1:
            return "APPROVED_GOVERNANCE", CORE03_01_GATE_PR
        if idx == 2:
            return "APPROVED_CONTRACT", CORE03_02_GATE_PR
        if idx == 3:
            return "COMPLETED", CORE03_03_CODE_PR
        if idx == 4:
            return "COMPLETED", CORE03_04_CLOSEOUT_PR
        if idx == 5:
            return "COMPLETED", CORE03_05_CLOSEOUT_PR
        if idx == 6:
            return "COMPLETED", CORE03_06_CLOSEOUT_PR
        if idx == 7:
            return "COMPLETED", CORE03_07_CLOSEOUT_PR
        if idx == 8:
            return "COMPLETED", CORE03_08_CLOSEOUT_PR
        if idx == 9:
            if manifest_status in (CORE03_09_COMPLETED_STATUS, CORE03_10_COMPLETED_STATUS):
                return "COMPLETED", CORE03_09_CODE_PR
            return "EXECUTOR_READY", None
        if idx == 10:
            if manifest_status == CORE03_10_COMPLETED_STATUS:
                return "COMPLETED", CORE03_10_CLOSEOUT_PR
            return "PLANNED_BLOCKED", None
        return "PLANNED_BLOCKED", None
    if (activation is not None
            and activation.get("selected_packet_id") == "NLE-PRPLAN-CORE-03-03"
            and module_id == "CORE-01"):
        if idx == 1:
            return "APPROVED_GOVERNANCE", 422
        if idx == 2:
            return "APPROVED_CONTRACT", 424
        code_prs = {
            3: 428, 4: 428, 5: 428, 6: 432, 7: 435, 8: 438,
            9: 444, 10: 447, 11: 450, 12: 453, 13: 456, 14: 459,
            15: 462, 16: 464,
        }
        if idx in code_prs:
            return "COMPLETED", code_prs[idx]
        return "PLANNED_BLOCKED", None
    if (activation is not None
            and activation.get("selected_packet_id") == "NLE-PRPLAN-CORE-03-03"
            and module_id == "CORE-02"):
        if idx == 1:
            return "APPROVED_GOVERNANCE", CORE02_03_GATE_PR
        if idx == 2:
            return "APPROVED_CONTRACT", CORE02_03_GATE_PR
        if idx == 3:
            return "COMPLETED", CORE02_03_CODE_PR
        if idx == 4:
            return "COMPLETED", CORE02_04_CODE_PR
        if idx == 5:
            return "COMPLETED", CORE02_05_CODE_PR
        if idx == 6:
            return "COMPLETED", CORE02_06_CODE_PR
        if idx == 7:
            return "COMPLETED", CORE02_07_CODE_PR
        if idx == 8:
            return "COMPLETED", CORE02_08_CODE_PR
        if idx == 9:
            return "COMPLETED", CORE02_09_CODE_PR
        if idx == 10:
            return "COMPLETED", CORE02_10_CODE_PR
        return "PLANNED_BLOCKED", None
    if (activation is not None
            and activation.get("selected_packet_id") == "NLE-PRPLAN-CORE-03-03"
            and module_id == "CORE-03"):
        if idx == 1:
            return "APPROVED_GOVERNANCE", CORE03_01_GATE_PR
        if idx == 2:
            return "APPROVED_CONTRACT", CORE03_02_GATE_PR
        if idx == 3:
            if manifest_status in (CORE03_03_COMPLETED_STATUS, CORE03_04_COMPLETED_STATUS,
                                   CORE03_05_COMPLETED_STATUS, CORE03_06_COMPLETED_STATUS,
                                   CORE03_07_COMPLETED_STATUS, CORE03_08_COMPLETED_STATUS):
                return "COMPLETED", CORE03_03_CODE_PR
            return "EXECUTOR_READY", None
        if idx == 4:
            if manifest_status in (CORE03_04_COMPLETED_STATUS, CORE03_05_COMPLETED_STATUS,
                                   CORE03_06_COMPLETED_STATUS, CORE03_07_COMPLETED_STATUS,
                                   CORE03_08_COMPLETED_STATUS):
                return "COMPLETED", CORE03_04_CLOSEOUT_PR
            return "PLANNED_BLOCKED", None
        if idx == 5:
            if manifest_status in (CORE03_05_COMPLETED_STATUS, CORE03_06_COMPLETED_STATUS,
                                   CORE03_07_COMPLETED_STATUS, CORE03_08_COMPLETED_STATUS):
                return "COMPLETED", CORE03_05_CLOSEOUT_PR
            return "PLANNED_BLOCKED", None
        if idx == 6:
            if manifest_status in (CORE03_06_COMPLETED_STATUS, CORE03_07_COMPLETED_STATUS,
                                   CORE03_08_COMPLETED_STATUS):
                return "COMPLETED", CORE03_06_CLOSEOUT_PR
            return "PLANNED_BLOCKED", None
        if idx == 7:
            if manifest_status in (CORE03_07_COMPLETED_STATUS, CORE03_08_COMPLETED_STATUS):
                return "COMPLETED", CORE03_07_CLOSEOUT_PR
            return "PLANNED_BLOCKED", None
        if idx == 8:
            if manifest_status == CORE03_08_COMPLETED_STATUS:
                return "COMPLETED", CORE03_08_CLOSEOUT_PR
            return "PLANNED_BLOCKED", None
        return "PLANNED_BLOCKED", None
    if (activation is not None
            and activation.get("selected_packet_id") == "NLE-PRPLAN-CORE-03-02"
            and module_id == "CORE-01"):
        if idx == 1:
            return "APPROVED_GOVERNANCE", 422
        if idx == 2:
            return "APPROVED_CONTRACT", 424
        code_prs = {
            3: 428, 4: 428, 5: 428, 6: 432, 7: 435, 8: 438,
            9: 444, 10: 447, 11: 450, 12: 453, 13: 456, 14: 459,
            15: 462, 16: 464,
        }
        if idx in code_prs:
            return "COMPLETED", code_prs[idx]
        return "PLANNED_BLOCKED", None
    if (activation is not None
            and activation.get("selected_packet_id") == "NLE-PRPLAN-CORE-03-02"
            and module_id == "CORE-02"):
        if idx == 1:
            return "APPROVED_GOVERNANCE", CORE02_03_GATE_PR
        if idx == 2:
            return "APPROVED_CONTRACT", CORE02_03_GATE_PR
        if idx == 3:
            return "COMPLETED", CORE02_03_CODE_PR
        if idx == 4:
            return "COMPLETED", CORE02_04_CODE_PR
        if idx == 5:
            return "COMPLETED", CORE02_05_CODE_PR
        if idx == 6:
            return "COMPLETED", CORE02_06_CODE_PR
        if idx == 7:
            return "COMPLETED", CORE02_07_CODE_PR
        if idx == 8:
            return "COMPLETED", CORE02_08_CODE_PR
        if idx == 9:
            return "COMPLETED", CORE02_09_CODE_PR
        if idx == 10:
            return "COMPLETED", CORE02_10_CODE_PR
        return "PLANNED_BLOCKED", None
    if (activation is not None
            and activation.get("selected_packet_id") == "NLE-PRPLAN-CORE-03-02"
            and module_id == "CORE-03"):
        if idx == 1:
            return "APPROVED_GOVERNANCE", CORE03_01_GATE_PR
        if idx == 2:
            return "APPROVED_CONTRACT", CORE03_02_GATE_PR
        return "PLANNED_BLOCKED", None
    if (activation is not None
            and activation.get("selected_packet_id") == "NLE-PRPLAN-CORE-03-01"
            and module_id == "CORE-03"):
        if idx == 1:
            return "APPROVED_GOVERNANCE", CORE03_01_GATE_PR
        return "PLANNED_BLOCKED", None
    if (activation is not None
            and activation.get("selected_packet_id") == "NLE-PRPLAN-CORE-02-10"
            and module_id == "CORE-01"):
        if idx == 1:
            return "APPROVED_GOVERNANCE", 422
        if idx == 2:
            return "APPROVED_CONTRACT", 424
        code_prs = {
            3: 428, 4: 428, 5: 428, 6: 432, 7: 435, 8: 438,
            9: 444, 10: 447, 11: 450, 12: 453, 13: 456, 14: 459,
            15: 462, 16: 464,
        }
        if idx in code_prs:
            return "COMPLETED", code_prs[idx]
        return "PLANNED_BLOCKED", None
    if (activation is not None
            and activation.get("selected_packet_id") == "NLE-PRPLAN-CORE-02-10"
            and module_id == "CORE-02"):
        if idx == 1:
            return "APPROVED_GOVERNANCE", CORE02_03_GATE_PR
        if idx == 2:
            return "APPROVED_CONTRACT", CORE02_03_GATE_PR
        if idx == 3:
            return "COMPLETED", CORE02_03_CODE_PR
        if idx == 4:
            return "COMPLETED", CORE02_04_CODE_PR
        if idx == 5:
            return "COMPLETED", CORE02_05_CODE_PR
        if idx == 6:
            return "COMPLETED", CORE02_06_CODE_PR
        if idx == 7:
            return "COMPLETED", CORE02_07_CODE_PR
        if idx == 8:
            return "COMPLETED", CORE02_08_CODE_PR
        if idx == 9:
            return "COMPLETED", CORE02_09_CODE_PR
        if idx == 10:
            return "COMPLETED", CORE02_10_CODE_PR
        return "PLANNED_BLOCKED", None
    if (activation is not None
            and activation.get("selected_packet_id") == "NLE-PRPLAN-CORE-02-09"
            and module_id == "CORE-01"):
        if idx == 1:
            return "APPROVED_GOVERNANCE", 422
        if idx == 2:
            return "APPROVED_CONTRACT", 424
        code_prs = {
            3: 428, 4: 428, 5: 428, 6: 432, 7: 435, 8: 438,
            9: 444, 10: 447, 11: 450, 12: 453, 13: 456, 14: 459,
            15: 462, 16: 464,
        }
        if idx in code_prs:
            return "COMPLETED", code_prs[idx]
        return "PLANNED_BLOCKED", None
    if (activation is not None
            and activation.get("selected_packet_id") == "NLE-PRPLAN-CORE-02-09"
            and module_id == "CORE-02"):
        if idx == 1:
            return "APPROVED_GOVERNANCE", CORE02_03_GATE_PR
        if idx == 2:
            return "APPROVED_CONTRACT", CORE02_03_GATE_PR
        if idx == 3:
            return "COMPLETED", CORE02_03_CODE_PR
        if idx == 4:
            return "COMPLETED", CORE02_04_CODE_PR
        if idx == 5:
            return "COMPLETED", CORE02_05_CODE_PR
        if idx == 6:
            return "COMPLETED", CORE02_06_CODE_PR
        if idx == 7:
            return "COMPLETED", CORE02_07_CODE_PR
        if idx == 8:
            return "COMPLETED", CORE02_08_CODE_PR
        if idx == 9:
            if manifest_status == CORE02_09_COMPLETED_STATUS:
                return "COMPLETED", CORE02_09_CODE_PR
            return "EXECUTOR_READY", None
        return "PLANNED_BLOCKED", None
    if (activation is not None
            and activation.get("selected_packet_id") == "NLE-PRPLAN-CORE-02-08"
            and module_id == "CORE-01"):
        if idx == 1:
            return "APPROVED_GOVERNANCE", 422
        if idx == 2:
            return "APPROVED_CONTRACT", 424
        code_prs = {
            3: 428, 4: 428, 5: 428, 6: 432, 7: 435, 8: 438,
            9: 444, 10: 447, 11: 450, 12: 453, 13: 456, 14: 459,
            15: 462, 16: 464,
        }
        if idx in code_prs:
            return "COMPLETED", code_prs[idx]
        return "PLANNED_BLOCKED", None
    if (activation is not None
            and activation.get("selected_packet_id") == "NLE-PRPLAN-CORE-02-08"
            and module_id == "CORE-02"):
        if idx == 1:
            return "APPROVED_GOVERNANCE", CORE02_03_GATE_PR
        if idx == 2:
            return "APPROVED_CONTRACT", CORE02_03_GATE_PR
        if idx == 3:
            return "COMPLETED", CORE02_03_CODE_PR
        if idx == 4:
            return "COMPLETED", CORE02_04_CODE_PR
        if idx == 5:
            return "COMPLETED", CORE02_05_CODE_PR
        if idx == 6:
            return "COMPLETED", CORE02_06_CODE_PR
        if idx == 7:
            return "COMPLETED", CORE02_07_CODE_PR
        if idx == 8:
            if manifest_status == CORE02_08_COMPLETED_STATUS:
                return "COMPLETED", CORE02_08_CODE_PR
            return "EXECUTOR_READY", None
        return "PLANNED_BLOCKED", None
    if (activation is not None
            and activation.get("selected_packet_id") == "NLE-PRPLAN-CORE-02-07"
            and module_id == "CORE-01"):
        if idx == 1:
            return "APPROVED_GOVERNANCE", 422
        if idx == 2:
            return "APPROVED_CONTRACT", 424
        code_prs = {
            3: 428, 4: 428, 5: 428, 6: 432, 7: 435, 8: 438,
            9: 444, 10: 447, 11: 450, 12: 453, 13: 456, 14: 459,
            15: 462, 16: 464,
        }
        if idx in code_prs:
            return "COMPLETED", code_prs[idx]
        return "PLANNED_BLOCKED", None
    if (activation is not None
            and activation.get("selected_packet_id") == "NLE-PRPLAN-CORE-02-07"
            and module_id == "CORE-02"):
        if idx == 1:
            return "APPROVED_GOVERNANCE", CORE02_03_GATE_PR
        if idx == 2:
            return "APPROVED_CONTRACT", CORE02_03_GATE_PR
        if idx == 3:
            return "COMPLETED", CORE02_03_CODE_PR
        if idx == 4:
            return "COMPLETED", CORE02_04_CODE_PR
        if idx == 5:
            return "COMPLETED", CORE02_05_CODE_PR
        if idx == 6:
            return "COMPLETED", CORE02_06_CODE_PR
        if idx == 7:
            if manifest_status == CORE02_07_COMPLETED_STATUS:
                return "COMPLETED", CORE02_07_CODE_PR
            return "EXECUTOR_READY", None
        return "PLANNED_BLOCKED", None
    if (activation is not None
            and activation.get("selected_packet_id") == "NLE-PRPLAN-CORE-02-06"
            and module_id == "CORE-01"):
        if idx == 1:
            return "APPROVED_GOVERNANCE", 422
        if idx == 2:
            return "APPROVED_CONTRACT", 424
        code_prs = {
            3: 428, 4: 428, 5: 428, 6: 432, 7: 435, 8: 438,
            9: 444, 10: 447, 11: 450, 12: 453, 13: 456, 14: 459,
            15: 462, 16: 464,
        }
        if idx in code_prs:
            return "COMPLETED", code_prs[idx]
        return "PLANNED_BLOCKED", None
    if (activation is not None
            and activation.get("selected_packet_id") == "NLE-PRPLAN-CORE-02-06"
            and module_id == "CORE-02"):
        if idx == 1:
            return "APPROVED_GOVERNANCE", CORE02_03_GATE_PR
        if idx == 2:
            return "APPROVED_CONTRACT", CORE02_03_GATE_PR
        if idx == 3:
            return "COMPLETED", CORE02_03_CODE_PR
        if idx == 4:
            return "COMPLETED", CORE02_04_CODE_PR
        if idx == 5:
            return "COMPLETED", CORE02_05_CODE_PR
        if idx == 6:
            if manifest_status == CORE02_06_COMPLETED_STATUS:
                return "COMPLETED", CORE02_06_CODE_PR
            return "EXECUTOR_READY", None
        return "PLANNED_BLOCKED", None
    if (activation is not None
            and activation.get("selected_packet_id") == "NLE-PRPLAN-CORE-02-05"
            and module_id == "CORE-01"):
        if idx == 1:
            return "APPROVED_GOVERNANCE", 422
        if idx == 2:
            return "APPROVED_CONTRACT", 424
        code_prs = {
            3: 428, 4: 428, 5: 428, 6: 432, 7: 435, 8: 438,
            9: 444, 10: 447, 11: 450, 12: 453, 13: 456, 14: 459,
            15: 462, 16: 464,
        }
        if idx in code_prs:
            return "COMPLETED", code_prs[idx]
        return "PLANNED_BLOCKED", None
    if (activation is not None
            and activation.get("selected_packet_id") == "NLE-PRPLAN-CORE-02-05"
            and module_id == "CORE-02"):
        if idx == 1:
            return "APPROVED_GOVERNANCE", CORE02_03_GATE_PR
        if idx == 2:
            return "APPROVED_CONTRACT", CORE02_03_GATE_PR
        if idx == 3:
            return "COMPLETED", CORE02_03_CODE_PR
        if idx == 4:
            return "COMPLETED", CORE02_04_CODE_PR
        if idx == 5:
            if manifest_status == CORE02_05_COMPLETED_STATUS:
                return "COMPLETED", CORE02_05_CODE_PR
            return "EXECUTOR_READY", None
        return "PLANNED_BLOCKED", None
    if (activation is not None
            and activation.get("selected_packet_id") == "NLE-PRPLAN-CORE-02-04"
            and module_id == "CORE-01"):
        if idx == 1:
            return "APPROVED_GOVERNANCE", 422
        if idx == 2:
            return "APPROVED_CONTRACT", 424
        code_prs = {
            3: 428, 4: 428, 5: 428, 6: 432, 7: 435, 8: 438,
            9: 444, 10: 447, 11: 450, 12: 453, 13: 456, 14: 459,
            15: 462, 16: 464,
        }
        if idx in code_prs:
            return "COMPLETED", code_prs[idx]
        return "PLANNED_BLOCKED", None
    if (activation is not None
            and activation.get("selected_packet_id") == "NLE-PRPLAN-CORE-02-04"
            and module_id == "CORE-02"):
        if idx == 1:
            return "APPROVED_GOVERNANCE", CORE02_03_GATE_PR
        if idx == 2:
            return "APPROVED_CONTRACT", CORE02_03_GATE_PR
        if idx == 3:
            return "COMPLETED", CORE02_03_CODE_PR
        if idx == 4:
            if manifest_status == CORE02_04_COMPLETED_STATUS:
                return "COMPLETED", CORE02_04_CODE_PR
            return "EXECUTOR_READY", None
        return "PLANNED_BLOCKED", None
    if (activation is not None
            and activation.get("selected_packet_id") == "NLE-PRPLAN-CORE-01-16"
            and module_id == "CORE-01"):
        if idx == 1:
            return "APPROVED_GOVERNANCE", 422
        if idx == 2:
            return "APPROVED_CONTRACT", 424
        code_prs = {
            3: 428, 4: 428, 5: 428, 6: 432, 7: 435, 8: 438,
            9: 444, 10: 447, 11: 450, 12: 453, 13: 456, 14: 459, 15: 462,
            16: CORE01_16_CODE_PR,
        }
        if idx in code_prs:
            return "COMPLETED", code_prs[idx]
        return "PLANNED_BLOCKED", None
    if (activation is not None
            and activation.get("selected_packet_id") == "NLE-PRPLAN-CORE-01-16"
            and module_id == "CORE-02"):
        if idx == 1:
            return "APPROVED_GOVERNANCE", CORE02_03_GATE_PR
        if idx == 2:
            return "APPROVED_CONTRACT", CORE02_03_GATE_PR
        if idx == 3:
            return "COMPLETED", CORE02_03_CODE_PR
        return "PLANNED_BLOCKED", None
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
                                   CORE01_14_COMPLETED_STATUS, CORE01_15_ACTIVATED_STATUS, CORE01_15_COMPLETED_STATUS, CORE02_ACTIVATED_STATUS,
                                   CORE02_COMPLETED_STATUS):
                return "COMPLETED", CORE01_08_CODE_PR
            return "EXECUTOR_READY", None
        if idx == 9:
            if manifest_status in (CORE01_09_COMPLETED_STATUS, CORE01_10_ACTIVATED_STATUS,
                                   CORE01_10_COMPLETED_STATUS, CORE01_11_ACTIVATED_STATUS,
                                   CORE01_11_COMPLETED_STATUS, CORE01_12_ACTIVATED_STATUS,
                                   CORE01_12_COMPLETED_STATUS, CORE01_13_ACTIVATED_STATUS,
                                   CORE01_13_COMPLETED_STATUS, CORE01_14_ACTIVATED_STATUS,
                                   CORE01_14_COMPLETED_STATUS, CORE01_15_ACTIVATED_STATUS, CORE01_15_COMPLETED_STATUS):
                return "COMPLETED", CORE01_09_CODE_PR
            if manifest_status == CORE01_09_ACTIVATED_STATUS:
                return "EXECUTOR_READY", None
        if idx == 10:
            if manifest_status in (CORE01_10_COMPLETED_STATUS, CORE01_11_ACTIVATED_STATUS,
                                   CORE01_11_COMPLETED_STATUS, CORE01_12_ACTIVATED_STATUS,
                                   CORE01_12_COMPLETED_STATUS, CORE01_13_ACTIVATED_STATUS,
                                   CORE01_13_COMPLETED_STATUS, CORE01_14_ACTIVATED_STATUS,
                                   CORE01_14_COMPLETED_STATUS, CORE01_15_ACTIVATED_STATUS, CORE01_15_COMPLETED_STATUS):
                return "COMPLETED", CORE01_10_CODE_PR
            if manifest_status == CORE01_10_ACTIVATED_STATUS:
                return "EXECUTOR_READY", None
        if idx == 11:
            if manifest_status in (CORE01_11_COMPLETED_STATUS, CORE01_12_ACTIVATED_STATUS,
                                   CORE01_12_COMPLETED_STATUS, CORE01_13_ACTIVATED_STATUS,
                                   CORE01_13_COMPLETED_STATUS, CORE01_14_ACTIVATED_STATUS,
                                   CORE01_14_COMPLETED_STATUS, CORE01_15_ACTIVATED_STATUS, CORE01_15_COMPLETED_STATUS):
                return "COMPLETED", CORE01_11_CODE_PR
            if manifest_status == CORE01_11_ACTIVATED_STATUS:
                return "EXECUTOR_READY", None
        if idx == 12:
            if manifest_status in (CORE01_12_COMPLETED_STATUS, CORE01_13_ACTIVATED_STATUS,
                                   CORE01_13_COMPLETED_STATUS, CORE01_14_ACTIVATED_STATUS,
                                   CORE01_14_COMPLETED_STATUS, CORE01_15_ACTIVATED_STATUS, CORE01_15_COMPLETED_STATUS):
                return "COMPLETED", CORE01_12_CODE_PR
            if manifest_status == CORE01_12_ACTIVATED_STATUS:
                return "EXECUTOR_READY", None
        if idx == 13:
            if manifest_status in (CORE01_13_COMPLETED_STATUS, CORE01_14_ACTIVATED_STATUS,
                                   CORE01_14_COMPLETED_STATUS, CORE01_15_ACTIVATED_STATUS, CORE01_15_COMPLETED_STATUS, CORE01_15_ACTIVATED_STATUS,
                                   CORE01_15_COMPLETED_STATUS):
                return "COMPLETED", CORE01_13_CODE_PR
            if manifest_status == CORE01_13_ACTIVATED_STATUS:
                return "EXECUTOR_READY", None
        if idx == 14:
            if manifest_status in (CORE01_14_COMPLETED_STATUS, CORE01_15_ACTIVATED_STATUS, CORE01_15_COMPLETED_STATUS, CORE01_15_ACTIVATED_STATUS,
                                   CORE01_15_COMPLETED_STATUS):
                return "COMPLETED", CORE01_14_CODE_PR
            if manifest_status == CORE01_14_ACTIVATED_STATUS:
                return "EXECUTOR_READY", None
        if idx == 15:
            if manifest_status == CORE01_15_COMPLETED_STATUS:
                return "COMPLETED", CORE01_15_CODE_PR
            if manifest_status == CORE01_15_ACTIVATED_STATUS:
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
                                   CORE01_14_COMPLETED_STATUS, CORE01_15_ACTIVATED_STATUS, CORE01_15_COMPLETED_STATUS, CORE01_15_ACTIVATED_STATUS,
                                   CORE01_15_COMPLETED_STATUS):
                return "COMPLETED", CORE02_03_CODE_PR
    return "PLANNED_BLOCKED", None


def expected_metadata(module_id: str, idx: int) -> tuple[str, str] | None:
    if module_id == "CORE-01" and idx in SLICE_METADATA:
        return SLICE_METADATA[idx]
    if module_id == "CORE-02" and idx in CORE02_SLICE_METADATA:
        return CORE02_SLICE_METADATA[idx]
    if module_id == "CORE-03" and idx in CORE03_SLICE_METADATA:
        return CORE03_SLICE_METADATA[idx]
    if module_id == "CORE-04" and idx in CORE04_SLICE_METADATA:
        return CORE04_SLICE_METADATA[idx]
    if module_id == "CORE-05" and idx in CORE05_SLICE_METADATA:
        return CORE05_SLICE_METADATA[idx]
    return None


def validate_capability_admission(
    packet: dict,
    status_by_packet: dict[str, str | None],
    formal_dependency: str,
    expected: dict | None = None,
    allowed_prefix: str = "NLE-PRPLAN-CORE-01-",
    label: str = "CORE-02-03",
) -> list[str]:
    expected = CORE02_CAPABILITY_ADMISSION if expected is None else expected
    errors = []
    admission = packet.get("capability_admission")
    if not isinstance(admission, dict):
        return [f"{label} capability admission must match the audited exact set"]
    if admission != expected:
        errors.append(f"{label} capability admission must match the audited exact set")
    if admission.get("formal_dependency") != formal_dependency:
        errors.append(f"{label} capability admission changes the formal module dependency")
    if admission.get("module_completion_claimed") is not False:
        errors.append(f"{label} capability admission must not claim module completion")
    for capability in admission.get("required_capabilities", []):
        if not isinstance(capability, dict) or "satisfied_by" not in capability:
            errors.append(f"{label} capability admission has an invalid capability entry")
            continue
        satisfied_by = capability["satisfied_by"]
        if not isinstance(satisfied_by, str) or not satisfied_by.startswith(allowed_prefix):
            errors.append(f"{label} capability admission accepts only {allowed_prefix} packets")
        if status_by_packet.get(satisfied_by) != "COMPLETED":
            errors.append(f"{label} capability {capability.get('id')} lacks a completed packet")
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
                expected_risk = ("ELEVATED"
                                 if (mid in ("CORE-03", "CORE-04", "CORE-05") and idx >= 3)
                                 else "STANDARD")
                if (packet.get("risk") != expected_risk
                      or packet.get("release_class") != "INTERNAL_ONLY"
                      or packet.get("approved_adr") != adr
                      or packet.get("activation_evidence") != evidence):
                    issues.append(f"{mid}: ready/completed slice lacks bounded risk/ADR/evidence")
                if mid == "CORE-02" and idx in (3, 4, 5, 6, 7, 8, 9):
                    issues.extend(validate_capability_admission(
                        packet, status_by_packet, original["dependencies"][0]))
                if mid == "CORE-03" and idx in (3, 9):
                    issues.extend(validate_capability_admission(
                        packet, status_by_packet, original["dependencies"][0],
                        expected=CORE03_CAPABILITY_ADMISSION,
                        allowed_prefix="NLE-PRPLAN-CORE-02-",
                        label=f"CORE-03-{idx:02}"))
                if mid == "CORE-04" and idx in (3, 4, 9):
                    issues.extend(validate_capability_admission(
                        packet, status_by_packet, original["dependencies"][0],
                        expected=CORE04_CAPABILITY_ADMISSION,
                        allowed_prefix="NLE-PRPLAN-CORE-01-",
                        label=f"CORE-04-{idx:02}"))
                if mid == "CORE-05" and idx in (3, 4, 5, 6, 7, 8):
                    issues.extend(validate_capability_admission(
                        packet, status_by_packet, original["dependencies"][0],
                        expected=CORE04_CAPABILITY_ADMISSION,
                        allowed_prefix="NLE-PRPLAN-CORE-01-",
                        label=f"CORE-05-{idx:02}"))
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
    if manifest.get("status") == CORE01_15_ACTIVATED_STATUS:
        if statuses.count("EXECUTOR_READY") != 1 or statuses.count("COMPLETED") != 13 or approved != 4:
            issues.append("CORE-01-15 activated state must have one ready packet, thirteen completed slices and four approved gates")
    if manifest.get("status") == CORE01_15_COMPLETED_STATUS:
        if statuses.count("EXECUTOR_READY") != 0 or statuses.count("COMPLETED") != 14 or approved != 4:
            issues.append("CORE-01-15 completed state must have zero ready packets, fourteen completed slices and four approved gates")
    if manifest.get("status") == CORE01_16_COMPLETED_STATUS:
        if statuses.count("EXECUTOR_READY") != 0 or statuses.count("COMPLETED") != 15 or approved != 4:
            issues.append("CORE-01-16 closeout must have zero ready packets, fifteen completed slices and four approved gates")
    if manifest.get("status") == CORE02_04_ACTIVATED_STATUS:
        if statuses.count("EXECUTOR_READY") != 1 or statuses.count("COMPLETED") != 15 or approved != 4:
            issues.append("CORE-02-04 activated state must have one ready packet, fifteen completed slices and four approved gates")
    if manifest.get("status") == CORE02_04_COMPLETED_STATUS:
        if statuses.count("EXECUTOR_READY") != 0 or statuses.count("COMPLETED") != 16 or approved != 4:
            issues.append("CORE-02-04 completed state must have zero ready packets, sixteen completed slices and four approved gates")
    if manifest.get("status") == CORE02_05_ACTIVATED_STATUS:
        if statuses.count("EXECUTOR_READY") != 1 or statuses.count("COMPLETED") != 16 or approved != 4:
            issues.append("CORE-02-05 activated state must have one ready packet, sixteen completed slices and four approved gates")
    if manifest.get("status") == CORE02_05_COMPLETED_STATUS:
        if statuses.count("EXECUTOR_READY") != 0 or statuses.count("COMPLETED") != 17 or approved != 4:
            issues.append("CORE-02-05 completed state must have zero ready packets, seventeen completed slices and four approved gates")
    if manifest.get("status") == CORE02_06_ACTIVATED_STATUS:
        if statuses.count("EXECUTOR_READY") != 1 or statuses.count("COMPLETED") != 17 or approved != 4:
            issues.append("CORE-02-06 activated state must have one ready packet, seventeen completed slices and four approved gates")
    if manifest.get("status") == CORE02_06_COMPLETED_STATUS:
        if statuses.count("EXECUTOR_READY") != 0 or statuses.count("COMPLETED") != 18 or approved != 4:
            issues.append("CORE-02-06 completed state must have zero ready packets, eighteen completed slices and four approved gates")
    if manifest.get("status") == CORE02_07_ACTIVATED_STATUS:
        if statuses.count("EXECUTOR_READY") != 1 or statuses.count("COMPLETED") != 18 or approved != 4:
            issues.append("CORE-02-07 activated state must have one ready packet, eighteen completed slices and four approved gates")
    if manifest.get("status") == CORE02_07_COMPLETED_STATUS:
        if statuses.count("EXECUTOR_READY") != 0 or statuses.count("COMPLETED") != 19 or approved != 4:
            issues.append("CORE-02-07 completed state must have zero ready packets, nineteen completed slices and four approved gates")
    if manifest.get("status") == CORE02_08_ACTIVATED_STATUS:
        if statuses.count("EXECUTOR_READY") != 1 or statuses.count("COMPLETED") != 19 or approved != 4:
            issues.append("CORE-02-08 activated state must have one ready packet, nineteen completed slices and four approved gates")
    if manifest.get("status") == CORE02_08_COMPLETED_STATUS:
        if statuses.count("EXECUTOR_READY") != 0 or statuses.count("COMPLETED") != 20 or approved != 4:
            issues.append("CORE-02-08 completed state must have zero ready packets, twenty completed slices and four approved gates")
    if manifest.get("status") == CORE02_09_ACTIVATED_STATUS:
        if statuses.count("EXECUTOR_READY") != 1 or statuses.count("COMPLETED") != 20 or approved != 4:
            issues.append("CORE-02-09 activated state must have one ready packet, twenty completed slices and four approved gates")
    if manifest.get("status") == CORE02_09_COMPLETED_STATUS:
        if statuses.count("EXECUTOR_READY") != 0 or statuses.count("COMPLETED") != 21 or approved != 4:
            issues.append("CORE-02-09 completed state must have zero ready packets, twenty-one completed slices and four approved gates")
    if manifest.get("status") == CORE02_10_COMPLETED_STATUS:
        if statuses.count("EXECUTOR_READY") != 0 or statuses.count("COMPLETED") != 22 or approved != 4:
            issues.append("CORE-02-10 closeout must have zero ready packets, twenty-two completed slices and four approved gates")
    if manifest.get("status") == CORE03_01_APPROVED_STATUS:
        if statuses.count("EXECUTOR_READY") != 0 or statuses.count("COMPLETED") != 22 or approved != 5:
            issues.append("CORE-03-01 governance state must have zero ready packets, twenty-two completed slices and five approved gates")
    if manifest.get("status") == CORE03_02_APPROVED_STATUS:
        if statuses.count("EXECUTOR_READY") != 0 or statuses.count("COMPLETED") != 22 or approved != 6:
            issues.append("CORE-03-02 contract state must have zero ready packets, twenty-two completed slices and six approved gates")
    if manifest.get("status") == CORE03_03_READY_STATUS:
        if statuses.count("EXECUTOR_READY") != 1 or statuses.count("COMPLETED") != 22 or approved != 6:
            issues.append("CORE-03-03 activated state must have one ready packet, twenty-two completed slices and six approved gates")
    if manifest.get("status") == CORE03_03_COMPLETED_STATUS:
        if statuses.count("EXECUTOR_READY") != 0 or statuses.count("COMPLETED") != 23 or approved != 6:
            issues.append("CORE-03-03 completed state must have zero ready packets, twenty-three completed slices and six approved gates")
    if manifest.get("status") == CORE03_04_COMPLETED_STATUS:
        if statuses.count("EXECUTOR_READY") != 0 or statuses.count("COMPLETED") != 24 or approved != 6:
            issues.append("CORE-03-04 completed state must have zero ready packets, twenty-four completed slices and six approved gates")
    if manifest.get("status") == CORE03_05_COMPLETED_STATUS:
        if statuses.count("EXECUTOR_READY") != 0 or statuses.count("COMPLETED") != 25 or approved != 6:
            issues.append("CORE-03-05 completed state must have zero ready packets, twenty-five completed slices and six approved gates")
    if manifest.get("status") == CORE03_06_COMPLETED_STATUS:
        if statuses.count("EXECUTOR_READY") != 0 or statuses.count("COMPLETED") != 26 or approved != 6:
            issues.append("CORE-03-06 completed state must have zero ready packets, twenty-six completed slices and six approved gates")
    if manifest.get("status") == CORE03_07_COMPLETED_STATUS:
        if statuses.count("EXECUTOR_READY") != 0 or statuses.count("COMPLETED") != 27 or approved != 6:
            issues.append("CORE-03-07 completed state must have zero ready packets, twenty-seven completed slices and six approved gates")
    if manifest.get("status") == CORE03_08_COMPLETED_STATUS:
        if statuses.count("EXECUTOR_READY") != 0 or statuses.count("COMPLETED") != 28 or approved != 6:
            issues.append("CORE-03-08 completed state must have zero ready packets, twenty-eight completed slices and six approved gates")
    if manifest.get("status") == CORE03_09_READY_STATUS:
        if statuses.count("EXECUTOR_READY") != 1 or statuses.count("COMPLETED") != 28 or approved != 6:
            issues.append("CORE-03-09 activated state must have one ready packet, twenty-eight completed slices and six approved gates")
    if manifest.get("status") == CORE03_09_COMPLETED_STATUS:
        if statuses.count("EXECUTOR_READY") != 0 or statuses.count("COMPLETED") != 29 or approved != 6:
            issues.append("CORE-03-09 completed state must have zero ready packets, twenty-nine completed slices and six approved gates")
    if manifest.get("status") == CORE03_10_COMPLETED_STATUS:
        if statuses.count("EXECUTOR_READY") != 0 or statuses.count("COMPLETED") != 30 or approved != 6:
            issues.append("CORE-03-10 closeout must have zero ready packets, thirty completed slices and six approved gates")
    if manifest.get("status") == CORE04_01_APPROVED_STATUS:
        if statuses.count("EXECUTOR_READY") != 0 or statuses.count("COMPLETED") != 30 or approved != 7:
            issues.append("CORE-04-01 governance state must have zero ready packets, thirty completed slices and seven approved gates")
    if manifest.get("status") == CORE04_02_APPROVED_STATUS:
        if statuses.count("EXECUTOR_READY") != 0 or statuses.count("COMPLETED") != 30 or approved != 8:
            issues.append("CORE-04-02 contract state must have zero ready packets, thirty completed slices and eight approved gates")
    if manifest.get("status") == CORE04_03_READY_STATUS:
        if statuses.count("EXECUTOR_READY") != 1 or statuses.count("COMPLETED") != 30 or approved != 8:
            issues.append("CORE-04-03 activated state must have one ready packet, thirty completed slices and eight approved gates")
    if manifest.get("status") == CORE04_03_COMPLETED_STATUS:
        if statuses.count("EXECUTOR_READY") != 0 or statuses.count("COMPLETED") != 31 or approved != 8:
            issues.append("CORE-04-03 completed state must have zero ready packets, thirty-one completed slices and eight approved gates")
    if manifest.get("status") == CORE04_04_READY_STATUS:
        if statuses.count("EXECUTOR_READY") != 1 or statuses.count("COMPLETED") != 31 or approved != 8:
            issues.append("CORE-04-04 activated state must have one ready packet, thirty-one completed slices and eight approved gates")
    if manifest.get("status") == CORE04_04_COMPLETED_STATUS:
        if statuses.count("EXECUTOR_READY") != 0 or statuses.count("COMPLETED") != 32 or approved != 8:
            issues.append("CORE-04-04 completed state must have zero ready packets, thirty-two completed slices and eight approved gates")
    if manifest.get("status") == CORE04_05_COMPLETED_STATUS:
        if statuses.count("EXECUTOR_READY") != 0 or statuses.count("COMPLETED") != 33 or approved != 8:
            issues.append("CORE-04-05 completed state must have zero ready packets, thirty-three completed slices and eight approved gates")
    if manifest.get("status") == CORE04_06_COMPLETED_STATUS:
        if statuses.count("EXECUTOR_READY") != 0 or statuses.count("COMPLETED") != 34 or approved != 8:
            issues.append("CORE-04-06 completed state must have zero ready packets, thirty-four completed slices and eight approved gates")
    if manifest.get("status") == CORE04_07_COMPLETED_STATUS:
        if statuses.count("EXECUTOR_READY") != 0 or statuses.count("COMPLETED") != 35 or approved != 8:
            issues.append("CORE-04-07 completed state must have zero ready packets, thirty-five completed slices and eight approved gates")
    if manifest.get("status") == CORE04_08_COMPLETED_STATUS:
        if statuses.count("EXECUTOR_READY") != 0 or statuses.count("COMPLETED") != 36 or approved != 8:
            issues.append("CORE-04-08 completed state must have zero ready packets, thirty-six completed slices and eight approved gates")
    if manifest.get("status") == CORE04_09_READY_STATUS:
        if statuses.count("EXECUTOR_READY") != 1 or statuses.count("COMPLETED") != 36 or approved != 8:
            issues.append("CORE-04-09 activated state must have one ready packet, thirty-six completed slices and eight approved gates")
    if manifest.get("status") == CORE04_09_COMPLETED_STATUS:
        if statuses.count("EXECUTOR_READY") != 0 or statuses.count("COMPLETED") != 37 or approved != 8:
            issues.append("CORE-04-09 completed state must have zero ready packets, thirty-seven completed slices and eight approved gates")
    if manifest.get("status") == CORE04_10_COMPLETED_STATUS:
        if statuses.count("EXECUTOR_READY") != 0 or statuses.count("COMPLETED") != 38 or approved != 8:
            issues.append("CORE-04-10 closeout must have zero ready packets, thirty-eight completed slices and eight approved gates")
    if manifest.get("status") == CORE05_01_APPROVED_STATUS:
        if statuses.count("EXECUTOR_READY") != 0 or statuses.count("COMPLETED") != 38 or approved != 9:
            issues.append("CORE-05-01 governance state must have zero ready packets, thirty-eight completed slices and nine approved gates")
    if manifest.get("status") == CORE05_02_APPROVED_STATUS:
        if statuses.count("EXECUTOR_READY") != 0 or statuses.count("COMPLETED") != 38 or approved != 10:
            issues.append("CORE-05-02 contract state must have zero ready packets, thirty-eight completed slices and ten approved gates")
    if manifest.get("status") == CORE05_03_READY_STATUS:
        if statuses.count("EXECUTOR_READY") != 1 or statuses.count("COMPLETED") != 38 or approved != 10:
            issues.append("CORE-05-03 activated state must have one ready packet, thirty-eight completed slices and ten approved gates")
    if manifest.get("status") == CORE05_03_COMPLETED_STATUS:
        if statuses.count("EXECUTOR_READY") != 0 or statuses.count("COMPLETED") != 39 or approved != 10:
            issues.append("CORE-05-03 completed state must have zero ready packets, thirty-nine completed slices and ten approved gates")
    if manifest.get("status") == CORE05_04_READY_STATUS:
        if statuses.count("EXECUTOR_READY") != 1 or statuses.count("COMPLETED") != 39 or approved != 10:
            issues.append("CORE-05-04 activated state must have one ready packet, thirty-nine completed slices and ten approved gates")
    if manifest.get("status") == CORE05_04_COMPLETED_STATUS:
        if statuses.count("EXECUTOR_READY") != 0 or statuses.count("COMPLETED") != 40 or approved != 10:
            issues.append("CORE-05-04 completed state must have zero ready packets, forty completed slices and ten approved gates")
    if manifest.get("status") == CORE05_05_READY_STATUS:
        if statuses.count("EXECUTOR_READY") != 1 or statuses.count("COMPLETED") != 40 or approved != 10:
            issues.append("CORE-05-05 activated state must have one ready packet, forty completed slices and ten approved gates")
    if manifest.get("status") == CORE05_05_COMPLETED_STATUS:
        if statuses.count("EXECUTOR_READY") != 0 or statuses.count("COMPLETED") != 41 or approved != 10:
            issues.append("CORE-05-05 completed state must have zero ready packets, forty-one completed slices and ten approved gates")
    if manifest.get("status") == CORE05_06_READY_STATUS:
        if statuses.count("EXECUTOR_READY") != 1 or statuses.count("COMPLETED") != 41 or approved != 10:
            issues.append("CORE-05-06 activated state must have one ready packet, forty-one completed slices and ten approved gates")
    if manifest.get("status") == CORE05_06_COMPLETED_STATUS:
        if statuses.count("EXECUTOR_READY") != 0 or statuses.count("COMPLETED") != 42 or approved != 10:
            issues.append("CORE-05-06 completed state must have zero ready packets, forty-two completed slices and ten approved gates")
    if manifest.get("status") == CORE05_07_READY_STATUS:
        if statuses.count("EXECUTOR_READY") != 1 or statuses.count("COMPLETED") != 42 or approved != 10:
            issues.append("CORE-05-07 activated state must have one ready packet, forty-two completed slices and ten approved gates")
    if manifest.get("status") == CORE05_07_COMPLETED_STATUS:
        if statuses.count("EXECUTOR_READY") != 0 or statuses.count("COMPLETED") != 43 or approved != 10:
            issues.append("CORE-05-07 completed state must have zero ready packets, forty-three completed slices and ten approved gates")
    if manifest.get("status") == CORE05_08_READY_STATUS:
        if statuses.count("EXECUTOR_READY") != 1 or statuses.count("COMPLETED") != 43 or approved != 10:
            issues.append("CORE-05-08 activated state must have one ready packet, forty-three completed slices and ten approved gates")
    if manifest.get("status") == CORE05_08_COMPLETED_STATUS:
        if statuses.count("EXECUTOR_READY") != 0 or statuses.count("COMPLETED") != 44 or approved != 10:
            issues.append("CORE-05-08 completed state must have zero ready packets, forty-four completed slices and ten approved gates")
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
    elif status in (CORE01_15_ACTIVATED_STATUS, CORE01_15_COMPLETED_STATUS):
        activation_path = root / "docs/queue/packet-activation-core-01-15.json"
    elif status == CORE01_16_COMPLETED_STATUS:
        activation_path = root / "docs/queue/packet-activation-core-01-16.json"
    elif status in (CORE02_04_ACTIVATED_STATUS, CORE02_04_COMPLETED_STATUS):
        activation_path = root / "docs/queue/packet-activation-core-02-04.json"
    elif status in (CORE02_05_ACTIVATED_STATUS, CORE02_05_COMPLETED_STATUS):
        activation_path = root / "docs/queue/packet-activation-core-02-05.json"
    elif status in (CORE02_06_ACTIVATED_STATUS, CORE02_06_COMPLETED_STATUS):
        activation_path = root / "docs/queue/packet-activation-core-02-06.json"
    elif status in (CORE02_07_ACTIVATED_STATUS, CORE02_07_COMPLETED_STATUS):
        activation_path = root / "docs/queue/packet-activation-core-02-07.json"
    elif status in (CORE02_08_ACTIVATED_STATUS, CORE02_08_COMPLETED_STATUS):
        activation_path = root / "docs/queue/packet-activation-core-02-08.json"
    elif status in (CORE02_09_ACTIVATED_STATUS, CORE02_09_COMPLETED_STATUS):
        activation_path = root / "docs/queue/packet-activation-core-02-09.json"
    elif status == CORE02_10_COMPLETED_STATUS:
        activation_path = root / "docs/queue/packet-activation-core-02-10.json"
    elif status == CORE03_01_APPROVED_STATUS:
        activation_path = root / "docs/queue/packet-activation-core-03-01.json"
    elif status == CORE03_02_APPROVED_STATUS:
        activation_path = root / "docs/queue/packet-activation-core-03-02.json"
    elif status in (CORE03_03_READY_STATUS, CORE03_03_COMPLETED_STATUS,
                    CORE03_04_COMPLETED_STATUS, CORE03_05_COMPLETED_STATUS,
                    CORE03_06_COMPLETED_STATUS, CORE03_07_COMPLETED_STATUS,
                    CORE03_08_COMPLETED_STATUS):
        activation_path = root / "docs/queue/packet-activation-core-03-03.json"
    elif status in (CORE03_09_READY_STATUS, CORE03_09_COMPLETED_STATUS,
                    CORE03_10_COMPLETED_STATUS):
        activation_path = root / "docs/queue/packet-activation-core-03-09.json"
    elif status == CORE04_01_APPROVED_STATUS:
        activation_path = root / "docs/queue/packet-activation-core-04-01.json"
    elif status == CORE04_02_APPROVED_STATUS:
        activation_path = root / "docs/queue/packet-activation-core-04-02.json"
    elif status in (CORE04_03_READY_STATUS, CORE04_03_COMPLETED_STATUS):
        activation_path = root / "docs/queue/packet-activation-core-04-03.json"
    elif status in (CORE04_04_READY_STATUS, CORE04_04_COMPLETED_STATUS,
                    CORE04_05_COMPLETED_STATUS, CORE04_06_COMPLETED_STATUS,
                    CORE04_07_COMPLETED_STATUS, CORE04_08_COMPLETED_STATUS):
        activation_path = root / "docs/queue/packet-activation-core-04-04.json"
    elif status in (CORE04_09_READY_STATUS, CORE04_09_COMPLETED_STATUS,
                    CORE04_10_COMPLETED_STATUS):
        activation_path = root / "docs/queue/packet-activation-core-04-09.json"
    elif status == CORE05_01_APPROVED_STATUS:
        activation_path = root / "docs/queue/packet-activation-core-05-01.json"
    elif status == CORE05_02_APPROVED_STATUS:
        activation_path = root / "docs/queue/packet-activation-core-05-02.json"
    elif status in (CORE05_03_READY_STATUS, CORE05_03_COMPLETED_STATUS):
        activation_path = root / "docs/queue/packet-activation-core-05-03.json"
    elif status in (CORE05_04_READY_STATUS, CORE05_04_COMPLETED_STATUS):
        activation_path = root / "docs/queue/packet-activation-core-05-04.json"
    elif status in (CORE05_05_READY_STATUS, CORE05_05_COMPLETED_STATUS):
        activation_path = root / "docs/queue/packet-activation-core-05-05.json"
    elif status in (CORE05_06_READY_STATUS, CORE05_06_COMPLETED_STATUS):
        activation_path = root / "docs/queue/packet-activation-core-05-06.json"
    elif status in (CORE05_07_READY_STATUS, CORE05_07_COMPLETED_STATUS):
        activation_path = root / "docs/queue/packet-activation-core-05-07.json"
    elif status in (CORE05_08_READY_STATUS, CORE05_08_COMPLETED_STATUS):
        activation_path = root / "docs/queue/packet-activation-core-05-08.json"
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
