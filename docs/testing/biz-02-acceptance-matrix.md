# BIZ-02 — 128 FUTURE SDK, Plugin, ABI, Sandbox and Developer Experience Acceptance Tests (B02-T001..B02-T128)

**2026-11-16 · P00 DOCS ONLY · ALL 128 SCENARIOS FUTURE/NOT EXECUTED · ZERO PASS.** Source `0ee74d476b7c5ff09744b323cfde7423c06673b2`; planning issue #366, coding #96 OPEN/BLOCKED, formal prerequisites GAME-02 + AI-01 ONLY, ADR-0043/0060/0081 PROPOSED, NLE-D009 source license OPEN.

## Mandatory future oracle
A valid future PASS requires actual **owner-approved SDK/ABI/API contracts**, exact source commit and schema hash, a reproducible built SDK and real plugin/sample artifact, test fixture rightsholder and rights clearance, target OS/browser/compiler/engine version, measured isolated run and logs/receipts, privilege and privacy review, QA-05 qualification where applicable, and evidence of no HIGH/CRITICAL. None exists today. For Web/Apple targets unavailable in the actual lab mark NOT_QUALIFIED, not PASS. CMake/CI docs checks are NOT runtime tests.

## Group 1 — PUBLIC-API-SEMVER

| Future ID | Scenario | Independent future oracle | Status |
|---|---|---|---|
| B02-T001 | SDK public schema ID and type surface match canonical owner descriptors | future generated schema hash, owner version approval, contract-diff checker | FUTURE / NOT EXECUTED |
| B02-T002 | SDK public API major mismatch rejected during negotiation | future generated schema hash, owner version approval, contract-diff checker | FUTURE / NOT EXECUTED |
| B02-T003 | SDK additive minor capability accepted with feature probe | future generated schema hash, owner version approval, contract-diff checker | FUTURE / NOT EXECUTED |
| B02-T004 | SDK patch bugfix preserves declared command semantics | future generated schema hash, owner version approval, contract-diff checker | FUTURE / NOT EXECUTED |
| B02-T005 | SDK pre-1.0 version labeled unstable rather than LTS | future generated schema hash, owner version approval, contract-diff checker | FUTURE / NOT EXECUTED |
| B02-T006 | Deprecated public API yields documented migration warning | future generated schema hash, owner version approval, contract-diff checker | FUTURE / NOT EXECUTED |
| B02-T007 | Removed field requires major/schema migration rather than silent drop | future generated schema hash, owner version approval, contract-diff checker | FUTURE / NOT EXECUTED |
| B02-T008 | Unknown required schema field returns typed error | future generated schema hash, owner version approval, contract-diff checker | FUTURE / NOT EXECUTED |
| B02-T009 | Unknown optional schema field preserved without capability escalation | future generated schema hash, owner version approval, contract-diff checker | FUTURE / NOT EXECUTED |
| B02-T010 | Feature bitset rejects unsupported mandatory capabilities | future generated schema hash, owner version approval, contract-diff checker | FUTURE / NOT EXECUTED |
| B02-T011 | Schema hash mismatch fails before plugin activation | future generated schema hash, owner version approval, contract-diff checker | FUTURE / NOT EXECUTED |
| B02-T012 | Stable public event identifiers survive refactor | future generated schema hash, owner version approval, contract-diff checker | FUTURE / NOT EXECUTED |
| B02-T013 | UTF-8 string and Unicode normalization documented across bindings | future generated schema hash, owner version approval, contract-diff checker | FUTURE / NOT EXECUTED |
| B02-T014 | Units time coordinate frame and null semantics retained in projection | future generated schema hash, owner version approval, contract-diff checker | FUTURE / NOT EXECUTED |
| B02-T015 | SDK documentation and generated bindings reference same version hash | future generated schema hash, owner version approval, contract-diff checker | FUTURE / NOT EXECUTED |
| B02-T016 | Consumer under older supported version receives reproducible compatibility report | future generated schema hash, owner version approval, contract-diff checker | FUTURE / NOT EXECUTED |

## Group 2 — C-ABI-LIFETIMES

| Future ID | Scenario | Independent future oracle | Status |
|---|---|---|---|
| B02-T017 | Native plugin C entry symbol exported with declared calling convention | future C ABI header + compiled plugin, dynamic loader and sanitizer proof | FUTURE / NOT EXECUTED |
| B02-T018 | Size-prefixed ABI table rejects undersized function table | future C ABI header + compiled plugin, dynamic loader and sanitizer proof | FUTURE / NOT EXECUTED |
| B02-T019 | Size-prefixed struct accepts compatible additive extension | future C ABI header + compiled plugin, dynamic loader and sanitizer proof | FUTURE / NOT EXECUTED |
| B02-T020 | Misaligned ABI struct detected without invalid native call | future C ABI header + compiled plugin, dynamic loader and sanitizer proof | FUTURE / NOT EXECUTED |
| B02-T021 | Cross-CRT allocated buffer cannot be freed by mismatched allocator | future C ABI header + compiled plugin, dynamic loader and sanitizer proof | FUTURE / NOT EXECUTED |
| B02-T022 | Caller-provided allocator callback release on same ownership domain | future C ABI header + compiled plugin, dynamic loader and sanitizer proof | FUTURE / NOT EXECUTED |
| B02-T023 | Opaque handle generation rejects stale ABA reuse | future C ABI header + compiled plugin, dynamic loader and sanitizer proof | FUTURE / NOT EXECUTED |
| B02-T024 | Cross-project/world opaque handle reuse denied | future C ABI header + compiled plugin, dynamic loader and sanitizer proof | FUTURE / NOT EXECUTED |
| B02-T025 | C++ exception cannot escape C boundary | future C ABI header + compiled plugin, dynamic loader and sanitizer proof | FUTURE / NOT EXECUTED |
| B02-T026 | STL std::string or std::vector excluded from exported ABI | future C ABI header + compiled plugin, dynamic loader and sanitizer proof | FUTURE / NOT EXECUTED |
| B02-T027 | Null pointer with positive buffer size rejected | future C ABI header + compiled plugin, dynamic loader and sanitizer proof | FUTURE / NOT EXECUTED |
| B02-T028 | Integer overflow in length or count rejected | future C ABI header + compiled plugin, dynamic loader and sanitizer proof | FUTURE / NOT EXECUTED |
| B02-T029 | Reentrant plugin callback restricted to documented phase | future C ABI header + compiled plugin, dynamic loader and sanitizer proof | FUTURE / NOT EXECUTED |
| B02-T030 | Plugin unload blocks while callback stack or background thread alive | future C ABI header + compiled plugin, dynamic loader and sanitizer proof | FUTURE / NOT EXECUTED |
| B02-T031 | Host API function pointer not used after generation retirement | future C ABI header + compiled plugin, dynamic loader and sanitizer proof | FUTURE / NOT EXECUTED |
| B02-T032 | Little-endian and 32-bit abi assumptions explicitly rejected or qualified | future C ABI header + compiled plugin, dynamic loader and sanitizer proof | FUTURE / NOT EXECUTED |

## Group 3 — PLUGIN-TRUST-LIFECYCLE

| Future ID | Scenario | Independent future oracle | Status |
|---|---|---|---|
| B02-T033 | Discovery of plugin manifest has zero code execution | future signed/hashed artifact, safe host lifecycle receipt and rollback fixture | FUTURE / NOT EXECUTED |
| B02-T034 | Unsigned/untrusted native in-process plugin denied | future signed/hashed artifact, safe host lifecycle receipt and rollback fixture | FUTURE / NOT EXECUTED |
| B02-T035 | Signed native plugin integrity accepted only with explicit owner trust | future signed/hashed artifact, safe host lifecycle receipt and rollback fixture | FUTURE / NOT EXECUTED |
| B02-T036 | Signature cannot be mistaken for sandbox permissions | future signed/hashed artifact, safe host lifecycle receipt and rollback fixture | FUTURE / NOT EXECUTED |
| B02-T037 | Manifest path traversal or symlink escape rejected | future signed/hashed artifact, safe host lifecycle receipt and rollback fixture | FUTURE / NOT EXECUTED |
| B02-T038 | Archive decompression bomb quota enforced | future signed/hashed artifact, safe host lifecycle receipt and rollback fixture | FUTURE / NOT EXECUTED |
| B02-T039 | Plugin dependency cycles rejected with bounded diagnostics | future signed/hashed artifact, safe host lifecycle receipt and rollback fixture | FUTURE / NOT EXECUTED |
| B02-T040 | Duplicate namespace and version ambiguity refused | future signed/hashed artifact, safe host lifecycle receipt and rollback fixture | FUTURE / NOT EXECUTED |
| B02-T041 | Missing transitive dependency yields explicit incompatible state | future signed/hashed artifact, safe host lifecycle receipt and rollback fixture | FUTURE / NOT EXECUTED |
| B02-T042 | Plugin initialized only after permissions and rights validated | future signed/hashed artifact, safe host lifecycle receipt and rollback fixture | FUTURE / NOT EXECUTED |
| B02-T043 | Activation at safe owner phase and not halfway through world tick | future signed/hashed artifact, safe host lifecycle receipt and rollback fixture | FUTURE / NOT EXECUTED |
| B02-T044 | Crashing plugin isolated or disabled with recoverable host | future signed/hashed artifact, safe host lifecycle receipt and rollback fixture | FUTURE / NOT EXECUTED |
| B02-T045 | Faulted plugin quarantined without corrupting project state | future signed/hashed artifact, safe host lifecycle receipt and rollback fixture | FUTURE / NOT EXECUTED |
| B02-T046 | Revoked capability invalidates active guest operations | future signed/hashed artifact, safe host lifecycle receipt and rollback fixture | FUTURE / NOT EXECUTED |
| B02-T047 | Native unload requires safe quiescence or restart | future signed/hashed artifact, safe host lifecycle receipt and rollback fixture | FUTURE / NOT EXECUTED |
| B02-T048 | Plugin instance lifecycle includes complete immutable receipt | future signed/hashed artifact, safe host lifecycle receipt and rollback fixture | FUTURE / NOT EXECUTED |

## Group 4 — SANDBOX-WASI-BROWSER

| Future ID | Scenario | Independent future oracle | Status |
|---|---|---|---|
| B02-T049 | WIT interface version negotiation rejects unsupported imports | future WASI/WIT sandbox host/guest or isolated process and browser runtime receipt | FUTURE / NOT EXECUTED |
| B02-T050 | WASI 0.2 guest runs only when host and toolchain qualify | future WASI/WIT sandbox host/guest or isolated process and browser runtime receipt | FUTURE / NOT EXECUTED |
| B02-T051 | WASI 0.3 async guest rejected if host lacks 0.3 feature support | future WASI/WIT sandbox host/guest or isolated process and browser runtime receipt | FUTURE / NOT EXECUTED |
| B02-T052 | WASI guest with no filesystem grant cannot read host project files | future WASI/WIT sandbox host/guest or isolated process and browser runtime receipt | FUTURE / NOT EXECUTED |
| B02-T053 | WASI guest with no network grant cannot open outbound sockets | future WASI/WIT sandbox host/guest or isolated process and browser runtime receipt | FUTURE / NOT EXECUTED |
| B02-T054 | WASM linear memory bounds trap without host memory corruption | future WASI/WIT sandbox host/guest or isolated process and browser runtime receipt | FUTURE / NOT EXECUTED |
| B02-T055 | WASM fuel or instruction budget stops infinite loop | future WASI/WIT sandbox host/guest or isolated process and browser runtime receipt | FUTURE / NOT EXECUTED |
| B02-T056 | WASM host-call timeout protects against blocking native host callback | future WASI/WIT sandbox host/guest or isolated process and browser runtime receipt | FUTURE / NOT EXECUTED |
| B02-T057 | Out-of-process guest IPC authentication rejects spoofed principal | future WASI/WIT sandbox host/guest or isolated process and browser runtime receipt | FUTURE / NOT EXECUTED |
| B02-T058 | Out-of-process plugin crash leaves host alive with explicit receipt | future WASI/WIT sandbox host/guest or isolated process and browser runtime receipt | FUTURE / NOT EXECUTED |
| B02-T059 | Browser loader never attempts to load DLL SO or dylib | future WASI/WIT sandbox host/guest or isolated process and browser runtime receipt | FUTURE / NOT EXECUTED |
| B02-T060 | Browser CSP violation rejects unapproved remote extension script | future WASI/WIT sandbox host/guest or isolated process and browser runtime receipt | FUTURE / NOT EXECUTED |
| B02-T061 | Browser Worker cross-origin message schema rejects malicious payload | future WASI/WIT sandbox host/guest or isolated process and browser runtime receipt | FUTURE / NOT EXECUTED |
| B02-T062 | Browser WASM runtime without required feature becomes unsupported | future WASI/WIT sandbox host/guest or isolated process and browser runtime receipt | FUTURE / NOT EXECUTED |
| B02-T063 | Headless target plugin never requires GPU or interactive window | future WASI/WIT sandbox host/guest or isolated process and browser runtime receipt | FUTURE / NOT EXECUTED |
| B02-T064 | Sandbox guest denied OS clock and non-deterministic entropy in replay mode | future WASI/WIT sandbox host/guest or isolated process and browser runtime receipt | FUTURE / NOT EXECUTED |

## Group 5 — AUTHORING-GAMEPLAY-PARITY

| Future ID | Scenario | Independent future oracle | Status |
|---|---|---|---|
| B02-T065 | Editor plugin command routes through AI-01 kernel not parallel mutation path | future GAME-02/AI-01 owning command receipts and semantic state readback | FUTURE / NOT EXECUTED |
| B02-T066 | CLI plugin command yields same source semantic digest as Editor | future GAME-02/AI-01 owning command receipts and semantic state readback | FUTURE / NOT EXECUTED |
| B02-T067 | Future MCP adapter uses same AI-01 descriptor grant and receipt | future GAME-02/AI-01 owning command receipts and semantic state readback | FUTURE / NOT EXECUTED |
| B02-T068 | UI extension request cannot bypass owner authorization | future GAME-02/AI-01 owning command receipts and semantic state readback | FUTURE / NOT EXECUTED |
| B02-T069 | GAME-02 script host denies raw mutable ECS pointer | future GAME-02/AI-01 owning command receipts and semantic state readback | FUTURE / NOT EXECUTED |
| B02-T070 | GAME-02 scripted command buffered until safe tick barrier | future GAME-02/AI-01 owning command receipts and semantic state readback | FUTURE / NOT EXECUTED |
| B02-T071 | Unauthorized gameplay event cannot mutate authoritative server state | future GAME-02/AI-01 owning command receipts and semantic state readback | FUTURE / NOT EXECUTED |
| B02-T072 | Auth role and project provenance preserved across binding adapters | future GAME-02/AI-01 owning command receipts and semantic state readback | FUTURE / NOT EXECUTED |
| B02-T073 | Idempotent authoring replay returns prior operation receipt | future GAME-02/AI-01 owning command receipts and semantic state readback | FUTURE / NOT EXECUTED |
| B02-T074 | Stale expected revision returns conflict without changed scene | future GAME-02/AI-01 owning command receipts and semantic state readback | FUTURE / NOT EXECUTED |
| B02-T075 | Project consent denial applies identically to UI CLI and MCP | future GAME-02/AI-01 owning command receipts and semantic state readback | FUTURE / NOT EXECUTED |
| B02-T076 | Script compiled source-map reports fault sanitized in SDK | future GAME-02/AI-01 owning command receipts and semantic state readback | FUTURE / NOT EXECUTED |
| B02-T077 | Script-initiated change vs authored change correctly distinguished | future GAME-02/AI-01 owning command receipts and semantic state readback | FUTURE / NOT EXECUTED |
| B02-T078 | Long-running plugin job cancellation before intent has no side effect | future GAME-02/AI-01 owning command receipts and semantic state readback | FUTURE / NOT EXECUTED |
| B02-T079 | Cancellation after durable intent returns recoverable status | future GAME-02/AI-01 owning command receipts and semantic state readback | FUTURE / NOT EXECUTED |
| B02-T080 | Plugin cannot overwrite another module's authority-owned data | future GAME-02/AI-01 owning command receipts and semantic state readback | FUTURE / NOT EXECUTED |

## Group 6 — TARGET-TOOLCHAIN-PACKAGING

| Future ID | Scenario | Independent future oracle | Status |
|---|---|---|---|
| B02-T081 | Windows MSVC x64 plugin linking and CRT baseline verified on clean host | future clean native OS/browser toolchain, export manifest and loader diagnostics | FUTURE / NOT EXECUTED |
| B02-T082 | Windows dynamic loader DllMain avoids unsafe heavy initialization | future clean native OS/browser toolchain, export manifest and loader diagnostics | FUTURE / NOT EXECUTED |
| B02-T083 | Windows ABI rejects wrong architecture binary | future clean native OS/browser toolchain, export manifest and loader diagnostics | FUTURE / NOT EXECUTED |
| B02-T084 | Linux glibc and libstdc++ symbol mismatch produces safe error | future clean native OS/browser toolchain, export manifest and loader diagnostics | FUTURE / NOT EXECUTED |
| B02-T085 | Linux plugin rpath or runpath cannot hijack privileged library | future clean native OS/browser toolchain, export manifest and loader diagnostics | FUTURE / NOT EXECUTED |
| B02-T086 | Linux Wayland X11 target independent of native SDK core load | future clean native OS/browser toolchain, export manifest and loader diagnostics | FUTURE / NOT EXECUTED |
| B02-T087 | macOS Apple Silicon signed plugin loads under qualified host policy | future clean native OS/browser toolchain, export manifest and loader diagnostics | FUTURE / NOT EXECUTED |
| B02-T088 | macOS Intel binary conditional support no false arm64 compatibility | future clean native OS/browser toolchain, export manifest and loader diagnostics | FUTURE / NOT EXECUTED |
| B02-T089 | macOS hardened runtime entitlement conflict reported without bypass | future clean native OS/browser toolchain, export manifest and loader diagnostics | FUTURE / NOT EXECUTED |
| B02-T090 | Web ESM optional package runs only in qualified browser profile | future clean native OS/browser toolchain, export manifest and loader diagnostics | FUTURE / NOT EXECUTED |
| B02-T091 | Web no native plugin export on any browser | future clean native OS/browser toolchain, export manifest and loader diagnostics | FUTURE / NOT EXECUTED |
| B02-T092 | CMake find_package imported SDK targets relocatable to clean prefix | future clean native OS/browser toolchain, export manifest and loader diagnostics | FUTURE / NOT EXECUTED |
| B02-T093 | SDK package contains correct headers libraries licenses and notices | future clean native OS/browser toolchain, export manifest and loader diagnostics | FUTURE / NOT EXECUTED |
| B02-T094 | Offline sample builds without undisclosed remote dependency fetch | future clean native OS/browser toolchain, export manifest and loader diagnostics | FUTURE / NOT EXECUTED |
| B02-T095 | Platform SDK target triple mismatch fails before link | future clean native OS/browser toolchain, export manifest and loader diagnostics | FUTURE / NOT EXECUTED |
| B02-T096 | Each exported game includes only approved and licensed plugin binaries | future clean native OS/browser toolchain, export manifest and loader diagnostics | FUTURE / NOT EXECUTED |

## Group 7 — DX-DOCS-SAMPLES-MIGRATIONS

| Future ID | Scenario | Independent future oracle | Status |
|---|---|---|---|
| B02-T097 | Original Hello World sample source and asset provenance verified | future original sample fixture, generated docs diff and supported migration plan | FUTURE / NOT EXECUTED |
| B02-T098 | Hello World sample emits expected typed authorized receipt | future original sample fixture, generated docs diff and supported migration plan | FUTURE / NOT EXECUTED |
| B02-T099 | Sample editor and headless outputs documented as semantically equal | future original sample fixture, generated docs diff and supported migration plan | FUTURE / NOT EXECUTED |
| B02-T100 | SDK quickstart exact commands tested from clean offline environment | future original sample fixture, generated docs diff and supported migration plan | FUTURE / NOT EXECUTED |
| B02-T101 | SDK error code reference contains every public failure code | future original sample fixture, generated docs diff and supported migration plan | FUTURE / NOT EXECUTED |
| B02-T102 | API reference matches shipped interface schema and hashes | future original sample fixture, generated docs diff and supported migration plan | FUTURE / NOT EXECUTED |
| B02-T103 | Sample CMake config resolves optional dependency without global paths | future original sample fixture, generated docs diff and supported migration plan | FUTURE / NOT EXECUTED |
| B02-T104 | Binding code generation produces reproducible output from same schema | future original sample fixture, generated docs diff and supported migration plan | FUTURE / NOT EXECUTED |
| B02-T105 | Bindings for optional language preserve handle ownership and errors | future original sample fixture, generated docs diff and supported migration plan | FUTURE / NOT EXECUTED |
| B02-T106 | Documentation links and version selector detect stale removed APIs | future original sample fixture, generated docs diff and supported migration plan | FUTURE / NOT EXECUTED |
| B02-T107 | Docs WCAG keyboard focus and screen reader workflow tested | future original sample fixture, generated docs diff and supported migration plan | FUTURE / NOT EXECUTED |
| B02-T108 | Plugin upgrade from compatible prior API preserves authored project | future original sample fixture, generated docs diff and supported migration plan | FUTURE / NOT EXECUTED |
| B02-T109 | Plugin upgrade incompatible schema blocks with migration plan | future original sample fixture, generated docs diff and supported migration plan | FUTURE / NOT EXECUTED |
| B02-T110 | Failed staged migration restores known-good plugin and project | future original sample fixture, generated docs diff and supported migration plan | FUTURE / NOT EXECUTED |
| B02-T111 | SDK uninstall leaves creator assets and projects intact | future original sample fixture, generated docs diff and supported migration plan | FUTURE / NOT EXECUTED |
| B02-T112 | Deprecation window and changelog alerts present before breaking release | future original sample fixture, generated docs diff and supported migration plan | FUTURE / NOT EXECUTED |

## Group 8 — SECURITY-LICENSE-PERF-EVIDENCE

| Future ID | Scenario | Independent future oracle | Status |
|---|---|---|---|
| B02-T113 | SDK source license OPEN prevents public redistribution approval | future legal/consent/supply-chain proof plus measured benchmark and unchanged blocked registry | FUTURE / NOT EXECUTED |
| B02-T114 | Original sample grant cannot infer engine binary sublicense | future legal/consent/supply-chain proof plus measured benchmark and unchanged blocked registry | FUTURE / NOT EXECUTED |
| B02-T115 | Third-party plugin SPDX transitive notices audited in actual package | future legal/consent/supply-chain proof plus measured benchmark and unchanged blocked registry | FUTURE / NOT EXECUTED |
| B02-T116 | Plugin license incompatible with target export blocks shipment | future legal/consent/supply-chain proof plus measured benchmark and unchanged blocked registry | FUTURE / NOT EXECUTED |
| B02-T117 | Plugin telemetry opt-in disabled without lawful authorization | future legal/consent/supply-chain proof plus measured benchmark and unchanged blocked registry | FUTURE / NOT EXECUTED |
| B02-T118 | Plugin cannot log private asset source or user tokens into public CI | future legal/consent/supply-chain proof plus measured benchmark and unchanged blocked registry | FUTURE / NOT EXECUTED |
| B02-T119 | Plugin capability quotas prevent memory CPU or output log exhaustion | future legal/consent/supply-chain proof plus measured benchmark and unchanged blocked registry | FUTURE / NOT EXECUTED |
| B02-T120 | Native plugin without proven sandbox labeled high assurance not safe by default | future legal/consent/supply-chain proof plus measured benchmark and unchanged blocked registry | FUTURE / NOT EXECUTED |
| B02-T121 | Cold start latency p50 p95 p99 recorded for each real target | future legal/consent/supply-chain proof plus measured benchmark and unchanged blocked registry | FUTURE / NOT EXECUTED |
| B02-T122 | Plugin host-call overhead measured against direct owner API baseline | future legal/consent/supply-chain proof plus measured benchmark and unchanged blocked registry | FUTURE / NOT EXECUTED |
| B02-T123 | Sandbox guest memory peak recorded under declared workload | future legal/consent/supply-chain proof plus measured benchmark and unchanged blocked registry | FUTURE / NOT EXECUTED |
| B02-T124 | Plugin hot reload fault injection retains project source integrity | future legal/consent/supply-chain proof plus measured benchmark and unchanged blocked registry | FUTURE / NOT EXECUTED |
| B02-T125 | Physical Windows Linux macOS and Web qualification status distinguished | future legal/consent/supply-chain proof plus measured benchmark and unchanged blocked registry | FUTURE / NOT EXECUTED |
| B02-T126 | Free CI artifact storage and runner budget checked before introducing tooling | future legal/consent/supply-chain proof plus measured benchmark and unchanged blocked registry | FUTURE / NOT EXECUTED |
| B02-T127 | Only 128 future cases planned no synthetic PASS or runtime claim | future legal/consent/supply-chain proof plus measured benchmark and unchanged blocked registry | FUTURE / NOT EXECUTED |
| B02-T128 | Registry keeps all 80 implementation WOs BLOCKED and BIZ-02 issue #96 OPEN | future legal/consent/supply-chain proof plus measured benchmark and unchanged blocked registry | FUTURE / NOT EXECUTED |

## Recording format and limitations
For each future ID record source and exact engine/SDK/guest version, binary hash/ABI/compiler triple, fixture rights, real OS/browser/hardware vs emulator, grants, expected and actual result, reproducible commands, regression evidence, signed review and severity. A proposed case is not evidence of a passing test. [API](../contracts/biz-02-sdk-plugin-api.md), [future benchmark](../research/biz-02-sdk-plugin-benchmark-protocol.md), [research Work Order](../work-orders/NLE-P00-WO-002-BIZ-02.md).
