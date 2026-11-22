# CORE-06 INTERNAL_ONLY Diagnostics Contract v0 (NLE-PRPLAN-CORE-06-02)

**Status:** `CONTRACT PROPOSAL / NOT IMPLEMENTED / NO CODE AUTHORIZED`. **Base:** `9c800e5fb6750dd8e6206e0ea72af7bb9aeabf9a`. **ADR:** [ADR-0109](../adr/0109-core-06-governance-slice.md), [ADR-0008](../adr/0008-core-06-observability-policy.md) planning-only. **WO:** [NLE-PRPLAN-CORE-06-02](../work-orders/NLE-PRPLAN-CORE-06-02.md).

## Objective

Freeze the first bounded CORE-06 logical API: owned typed log records, spans, counters, local crash envelopes, profile samples and opt-in local telemetry buffers. Define bounded text, typed errors, local-only sinks, drop accounting and exact implementation allowlists. No dependency, network, crash handler, profiler adapter, binary format, public ABI or release is authorized.

## Admission and boundaries

- Formal `CORE-01` dependency remains; admission is limited to completed `CORE-01-03/-06/-07/-08/-12/-13` capabilities under ADR-0109/ADR-0086. CORE-01 module completion is **not** claimed.
- CORE-06 owns the facade, event semantics, local sink policy, bounded buffers, correlation envelope and local export values.
- CORE-01 owns OS crash/process lifecycle; CORE-02 memory; CORE-03 job IDs; CORE-04 ticks; GFX GPU timing/device loss; AUD realtime constraints; DATA provenance; EDIT/QA/AI authorized projections.
- No spdlog, Tracy, Perfetto, Crashpad, OpenTelemetry, cloud service, network socket, profiler listener, graphics device or editor UI appears in this contract.

## Policy invariants

- **Local-first:** values go to caller-provided local buffers; no file path is opened by this API and no network is possible.
- **Bounded:** every text field has a fixed byte capacity; every buffer has fixed record capacity; drops are counted, never silent.
- **Per-producer sequence:** sequence is caller-supplied per logger/producer; no total cross-thread ordering claim.
- **Typed failure:** invalid text, invalid IDs, negative time, non-finite counter values, full buffers and disabled telemetry return `DiagnosticError`.
- **Redaction at source:** callers must not put secrets in messages/attributes; `assign_text` rejects embedded NUL and overlong data, and bounded fields are not an authorization to log secrets.
- **Realtime boundary:** no allocation, lock, file I/O, network or blocking call occurs in any API; audio/render callers must use only preallocated paths.
- **No crash claim:** `CrashEnvelope` is a local value snapshot; this contract does not install a signal handler, parse dumps, symbolize, upload or guarantee crash capture.
- **No telemetry network:** `TelemetryBuffer` is an in-memory local buffer; default disabled and only explicit local opt-in enables it.
- **No performance claim:** disabled/active overhead, sampling and release behavior remain future measurements.

## Internal API (logical, exact names)

```cpp
namespace stormline::core::diag {

using u8 = std::uint8_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using i64 = std::int64_t;
using f64 = double;

inline constexpr u32 kDiagnosticsSchemaVersion = 1;
inline constexpr u32 kMaxAttributes = 8;
inline constexpr u32 kLogBufferCapacity = 128;
inline constexpr u32 kTraceBufferCapacity = 128;
inline constexpr u32 kCounterCapacity = 64;
inline constexpr u32 kCrashPrecedingRecords = 16;
inline constexpr u32 kProfileCapacity = 64;
inline constexpr u32 kTelemetryCapacity = 64;
inline constexpr u32 kMaxMessageBytes = 192;
inline constexpr u32 kMaxNameBytes = 96;
inline constexpr u32 kMaxAttributeKeyBytes = 32;
inline constexpr u32 kMaxAttributeValueBytes = 96;

enum class DiagnosticSeverity : u8 {
    Trace, Debug, Info, Warn, Error, Fatal
};

enum class DiagnosticReason : u8 {
    None, InvalidInput, ProjectAssetError, AllocationPressure, FrameBudgetOverrun,
    JobDeadlineMiss, DeviceLost, AudioUnderrun, NetworkPeerError, CrashUnhandled,
    BufferFull, Unsupported, NotEnabled, InternalFailure
};

enum class DiagnosticError : u8 {
    None, InvalidArgument, OutOfRange, BufferFull, NotEnabled, Shutdown,
    Overflow, NonFinite, Unsupported, InternalFailure
};

struct BuildId { u64 high{0}; u64 low{0}; };
struct TraceId { u64 high{0}; u64 low{0}; };
struct SpanId { u64 value{0}; };
struct SessionId { u64 value{0}; };
struct DiagnosticTime { i64 monotonic_ns{0}; };

template <typename T>
struct DiagResult {
    T value{};
    DiagnosticError error{DiagnosticError::None};
    [[nodiscard]] constexpr bool ok() const noexcept {
        return error == DiagnosticError::None;
    }
};

[[nodiscard]] constexpr bool valid(BuildId id) noexcept;
[[nodiscard]] constexpr bool valid(TraceId id) noexcept;
[[nodiscard]] constexpr bool valid(SpanId id) noexcept;
[[nodiscard]] constexpr bool valid(SessionId id) noexcept;

template <u32 N>
struct BoundedText {
    std::array<char, N> bytes{};
    u32 length{0};
};

template <u32 N>
[[nodiscard]] std::string_view view(const BoundedText<N>& text) noexcept;

template <u32 N>
[[nodiscard]] DiagnosticError assign_text(BoundedText<N>& out, std::string_view text) noexcept;

struct Attribute {
    BoundedText<kMaxAttributeKeyBytes> key{};
    BoundedText<kMaxAttributeValueBytes> value{};
};

struct LogRecord {
    u32 schema_version{kDiagnosticsSchemaVersion};
    BuildId build{};
    u64 producer_sequence{0};
    DiagnosticTime time{};
    DiagnosticSeverity severity{DiagnosticSeverity::Info};
    DiagnosticReason reason{DiagnosticReason::None};
    u32 subsystem{0};
    BoundedText<kMaxMessageBytes> message{};
    std::array<Attribute, kMaxAttributes> attributes{};
    u32 attribute_count{0};
};

[[nodiscard]] DiagnosticError make_log_record(
    BuildId build, u64 producer_sequence, DiagnosticTime time,
    DiagnosticSeverity severity, DiagnosticReason reason, u32 subsystem,
    std::string_view message, const Attribute* attributes, u32 attribute_count,
    LogRecord& out) noexcept;

class DiagnosticSink {
public:
    virtual ~DiagnosticSink() = default;
    virtual DiagnosticError accept(const LogRecord& record) noexcept = 0;
    virtual DiagnosticError flush() noexcept = 0;
    virtual void shutdown() noexcept = 0;
};

class LogBuffer final : public DiagnosticSink {
public:
    LogBuffer() noexcept = default;
    ~LogBuffer() override = default;
    LogBuffer(const LogBuffer&) = delete;
    LogBuffer& operator=(const LogBuffer&) = delete;
    DiagnosticError accept(const LogRecord& record) noexcept override;
    DiagnosticError flush() noexcept override;
    void shutdown() noexcept override;
    [[nodiscard]] u32 size() const noexcept;
    [[nodiscard]] u64 dropped() const noexcept;
    [[nodiscard]] bool at(u32 index, LogRecord& out) const noexcept;
private:
    std::array<LogRecord, kLogBufferCapacity> records_{};
    u32 size_{0};
    u64 dropped_{0};
    bool shutdown_{false};
};

class Logger final {
public:
    Logger(BuildId build, DiagnosticSink* sink) noexcept;
    [[nodiscard]] DiagnosticError log(
        DiagnosticTime time, DiagnosticSeverity severity, DiagnosticReason reason,
        u32 subsystem, std::string_view message,
        const Attribute* attributes = nullptr, u32 attribute_count = 0) noexcept;
    [[nodiscard]] u64 next_sequence() const noexcept;
private:
    BuildId build_{};
    DiagnosticSink* sink_{nullptr};
    u64 sequence_{0};
};

struct SpanRecord {
    u32 schema_version{kDiagnosticsSchemaVersion};
    BuildId build{};
    TraceId trace{};
    SpanId span{};
    SpanId parent{};
    u64 producer_sequence{0};
    DiagnosticTime start{};
    DiagnosticTime end{};
    u32 subsystem{0};
    DiagnosticReason outcome{DiagnosticReason::None};
    BoundedText<kMaxNameBytes> name{};
    bool completed{false};
};

[[nodiscard]] DiagnosticError make_span(
    BuildId build, TraceId trace, SpanId span, SpanId parent,
    u64 producer_sequence, DiagnosticTime start, u32 subsystem,
    std::string_view name, SpanRecord& out) noexcept;
[[nodiscard]] DiagnosticError complete_span(
    SpanRecord& span, DiagnosticTime end, DiagnosticReason outcome) noexcept;

class TraceBuffer final {
public:
    TraceBuffer() noexcept = default;
    [[nodiscard]] DiagnosticError accept(const SpanRecord& span) noexcept;
    [[nodiscard]] u32 size() const noexcept;
    [[nodiscard]] u64 dropped() const noexcept;
    [[nodiscard]] bool at(u32 index, SpanRecord& out) const noexcept;
private:
    std::array<SpanRecord, kTraceBufferCapacity> spans_{};
    u32 size_{0};
    u64 dropped_{0};
};

enum class CounterUnit : u8 { Count, Nanoseconds, Bytes, Percent, Custom };

struct CounterSample {
    u32 schema_version{kDiagnosticsSchemaVersion};
    BuildId build{};
    DiagnosticTime time{};
    u32 counter_id{0};
    CounterUnit unit{CounterUnit::Count};
    f64 value{0.0};
};

[[nodiscard]] DiagnosticError make_counter_sample(
    BuildId build, DiagnosticTime time, u32 counter_id, CounterUnit unit,
    f64 value, CounterSample& out) noexcept;

class CounterSet final {
public:
    CounterSet() noexcept = default;
    [[nodiscard]] DiagnosticError record(const CounterSample& sample) noexcept;
    [[nodiscard]] bool find(u32 counter_id, CounterSample& out) const noexcept;
    [[nodiscard]] u32 size() const noexcept;
    [[nodiscard]] u64 dropped() const noexcept;
private:
    std::array<CounterSample, kCounterCapacity> samples_{};
    u32 size_{0};
    u64 dropped_{0};
};

struct CrashEnvelope {
    u32 schema_version{kDiagnosticsSchemaVersion};
    BuildId build{};
    SessionId session{};
    u32 platform_tag{0};
    DiagnosticTime time{};
    DiagnosticReason reason{DiagnosticReason::CrashUnhandled};
    u32 preceding_count{0};
    std::array<LogRecord, kCrashPrecedingRecords> preceding{};
};

[[nodiscard]] DiagnosticError make_crash_envelope(
    BuildId build, SessionId session, u32 platform_tag, DiagnosticTime time,
    DiagnosticReason reason, const LogRecord* preceding, u32 count,
    CrashEnvelope& out) noexcept;

struct ProfileSample {
    u32 schema_version{kDiagnosticsSchemaVersion};
    BuildId build{};
    u32 scope_id{0};
    u32 subsystem{0};
    u64 elapsed_ns{0};
};

[[nodiscard]] DiagnosticError make_profile_sample(
    BuildId build, u32 scope_id, u64 elapsed_ns, u32 subsystem,
    ProfileSample& out) noexcept;

class ProfileAccumulator final {
public:
    ProfileAccumulator() noexcept = default;
    [[nodiscard]] DiagnosticError add(const ProfileSample& sample) noexcept;
    void reset() noexcept;
    [[nodiscard]] u32 count() const noexcept;
    [[nodiscard]] u64 total_ns() const noexcept;
    [[nodiscard]] u64 min_ns() const noexcept;
    [[nodiscard]] u64 max_ns() const noexcept;
    [[nodiscard]] u64 dropped() const noexcept;
private:
    std::array<ProfileSample, kProfileCapacity> samples_{};
    u32 size_{0};
    u64 dropped_{0};
};

struct TelemetryPolicy {
    bool enabled{false};
    bool local_only{true};
};

struct TelemetryEvent {
    u32 schema_version{kDiagnosticsSchemaVersion};
    BuildId build{};
    DiagnosticTime time{};
    u32 event_id{0};
    f64 value{0.0};
    BoundedText<kMaxNameBytes> name{};
};

[[nodiscard]] DiagnosticError make_telemetry_event(
    BuildId build, DiagnosticTime time, u32 event_id, f64 value,
    std::string_view name, TelemetryEvent& out) noexcept;

class TelemetryBuffer final {
public:
    explicit TelemetryBuffer(TelemetryPolicy policy = {}) noexcept;
    [[nodiscard]] DiagnosticError set_enabled(bool enabled) noexcept;
    [[nodiscard]] bool enabled() const noexcept;
    [[nodiscard]] DiagnosticError record(const TelemetryEvent& event) noexcept;
    [[nodiscard]] u32 size() const noexcept;
    [[nodiscard]] u64 dropped() const noexcept;
private:
    std::array<TelemetryEvent, kTelemetryCapacity> events_{};
    TelemetryPolicy policy_{};
    u32 size_{0};
    u64 dropped_{0};
};

}  // namespace stormline::core::diag
```

No implementation is provided. Names or semantics may be refined only by an audited contract correction before `CORE-06-03`.

## Semantics

- **Validation:** `valid(BuildId)`/`valid(TraceId)` require a nonzero 128-bit value; `valid(SpanId)`/`valid(SessionId)` require nonzero. Invalid IDs, negative `monotonic_ns`, `attribute_count > kMaxAttributes`, null attributes with count > 0, empty attribute key, overlong text or embedded NUL return `InvalidArgument`.
- **Bounded text:** `assign_text` accepts at most `N` bytes, rejects embedded NUL, copies bytes and sets `length`; `view` returns `[bytes, length)` and never reads uninitialized bytes.
- **Logs:** `make_log_record` validates/copies message and attributes; schema and severity/reason are stable enums. `Logger` supplies per-producer sequence (incremented on every attempt, including rejected/full attempts), and `LogBuffer` accepts until full, then increments `dropped` and returns `BufferFull`. `shutdown` is idempotent; later `accept`/`flush` return `Shutdown`. `at` returns false out of range.
- **Traces:** `make_span` requires valid build/trace/span/parent (parent zero is allowed for root), nonnegative start and bounded name; `complete_span` requires `!completed` and `end >= start`, sets outcome. `TraceBuffer` accepts only completed spans; full increments `dropped` and returns `BufferFull`.
- **Counters:** `make_counter_sample` requires valid build, nonnegative time, nonzero counter ID, finite value; `CounterSet::record` updates an existing ID in place, otherwise appends; full increments `dropped` and returns `BufferFull`; `find` returns false for absent/out-of-range.
- **Crash:** `make_crash_envelope` requires valid build/session, nonnegative time, `count <= kCrashPrecedingRecords`; null preceding with nonzero count is invalid. It copies bounded preceding log records only; no handler, dump, symbol or upload is performed.
- **Profile:** `make_profile_sample` requires valid build, nonzero scope ID, and `elapsed_ns` within `u64`; `ProfileAccumulator` adds up to capacity, tracks count/total/min/max, drops with `BufferFull` and resets explicitly.
- **Telemetry:** policy is local-only; default disabled. `set_enabled(true)` requires `local_only=true`; `record` returns `NotEnabled` while disabled, an invalid event returns `InvalidArgument`, full increments `dropped` and returns `BufferFull`. No file or network I/O exists.
- **Threading:** each `Logger` and buffer is single-producer unless the caller provides external synchronization; sequence is per producer, not a total order. No global mutable state or exception crosses the API.
- **Schema:** `kDiagnosticsSchemaVersion` is 1. Serialization/export is not implemented; any future format requires a separate contract and must record schema/build/redaction metadata.

## Test oracles (future CORE-06-03..-09)

| ID | Scenario | Oracle |
|---|---|---|
| LOG-01 | bounded text/attributes | overlong/embedded-NUL rejected; exact max accepted; key/value view exact |
| LOG-02 | log buffer/drop/shutdown | capacity records accepted; next returns `BufferFull` and increments dropped; shutdown idempotent; flush/accept after shutdown typed |
| LOG-03 | per-producer logger | sequence increments per attempt; build/time/severity/reason/subsystem round-trip; null sink/build invalid |
| TRACE-01 | span lifecycle | root/non-root IDs; end before start rejected; complete twice rejected; trace buffer accepts completed only and drops on full |
| COUNTER-01 | counter set | finite value accepted; NaN/Inf overflow rejected; duplicate ID updates; full/drop; find miss |
| CRASH-01 | local envelope | valid bounded preceding copy; >16 or null+count rejected; no network/file side effect |
| PROF-01 | profile accumulator | min/max/total/count exact; reset; full/drop; zero elapsed allowed |
| TEL-01 | opt-in telemetry | default disabled; `record` → `NotEnabled`; explicit local enable; non-local policy rejected; full/drop |
| QLF-01 | integrated diagnostics | log→trace→counter→profile→crash envelope→opt-in telemetry flow with deterministic values and no network |
| QLF-02 | deterministic repeat | repeated local sequence yields identical records/counters/drop counts |
| QLF-03 | failure recovery | each typed error is followed by a successful valid operation |
| QLF-04 | bounded overload | 10,000 log/trace/telemetry attempts keep memory fixed and count every drop |

## Implementation allowlists

Headers are internal and header-only. CMake adds one `INTERFACE` target and one test executable per packet; no production `.cpp` is required. Any new file requires an audited contract correction.

### `CORE-06-03` (types + logs)

1. `src/stormline/core/diag/diagnostics_types.hpp`
2. `src/stormline/core/diag/log.hpp`
3. `tests/core/core06_log_tests.cpp`
4. `CMakeLists.txt` (additive CORE-06 target/tests)
5. `.github/workflows/core01-internal-headless.yml` (additive CORE-06 filters)
6. `docs/evidence/NLE-PRPLAN-CORE-06-03.md`

### `CORE-06-04` (traces)

1. `src/stormline/core/diag/trace.hpp`
2. `tests/core/core06_trace_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-CORE-06-04.md`

### `CORE-06-05` (counters)

1. `src/stormline/core/diag/counter.hpp`
2. `tests/core/core06_counter_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-CORE-06-05.md`

### `CORE-06-06` (local crash envelope)

1. `src/stormline/core/diag/crash.hpp`
2. `tests/core/core06_crash_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-CORE-06-06.md`

### `CORE-06-07` (profile samples)

1. `src/stormline/core/diag/profile.hpp`
2. `tests/core/core06_profile_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-CORE-06-07.md`

### `CORE-06-08` (local opt-in telemetry)

1. `src/stormline/core/diag/telemetry.hpp`
2. `tests/core/core06_telemetry_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-CORE-06-08.md`

### `CORE-06-09` (qualification)

1. `tests/core/core06_diagnostics_qualification_tests.cpp`
2. `CMakeLists.txt`
3. `.github/workflows/core01-internal-headless.yml`
4. `docs/evidence/NLE-PRPLAN-CORE-06-09.md`

`CORE-06-10` is documentary closeout only. Qualification is internal/CI-only; no hardware, crash-dump, profiler, SIMD, ABI or release claim.

## Stop / rollback / security

Stop on stale source, missing admission, third-party type, network/file/upload path, unbounded text/attribute/cardinality, hidden allocation/lock in a realtime path, secret/path exposure, public ABI/release claim or HIGH/CRITICAL. Unmerged: close the branch. After merge: normal revert PR; never force push.

No implementation is authorized by this contract. `CORE-06-03` requires its own G6 activation and explicit owner authorization.
