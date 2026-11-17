# CORE-01 INTERNAL_ONLY Capability Graph Contract v0 (NLE-PRPLAN-CORE-01-13)

**Status:** `PROTOTYPE CONTRACT / NOT IMPLEMENTED / NOT A SAPL ADOPTION / NO PERFORMANCE PASS`. **Base:** `967e136d517c6d78430bcde1fd66ef97a283efe5`. **ADR:** [ADR-0092](../adr/0092-core-01-capability-graph-prototype.md). **WO:** [NLE-PRPLAN-CORE-01-13](../work-orders/NLE-PRPLAN-CORE-01-13.md).

## Objective and bounded scope

Provide a fixed-capacity capability graph prototype with explicit `Unknown`/`Supported`/`Unsupported` states and a thin SDL3 probe, plus a **report-only** comparative measurement of graph lookup vs a direct `SDL_WasInit` query. This is not a SAPL production layer, not a performance PASS and not a product-architecture decision.

Out of scope: SAPL production adoption, performance thresholds/benchmark verdicts, direct OS APIs, renderer/GPU/audio, public ABI, release.

## Dependency and build profile

- SDL3 3.4.20, commit `f00dc919ca35b9756316e86c4777392de442f9b2`, zlib, static build-time `FetchContent`; existing `-07`..`-12` baseline.
- `CapabilityProbe` requires the SDL3 runtime initialized on the same owner thread; before init it reports `Unknown`.
- Tests use `SDL_VIDEODRIVER=dummy` except the real-driver Wayland check, which uses the platform driver (X11/Win32/Cocoa).
- No package installation, paid runner, secret or runtime download.

## Internal API (exact names)

```cpp
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <thread>

namespace stormline::core::internal {

enum class CapabilityId : std::uint8_t {
    Video,
    Events,
    Window,
    Displays,
    WaylandRuntime
};

enum class CapabilityState : std::uint8_t {
    Unknown,
    Supported,
    Unsupported
};

enum class CapabilitySource : std::uint8_t {
    Unknown,
    SdlProbe,
    Explicit
};

enum class CapabilityError : std::uint8_t {
    None,
    WrongThread,
    GraphFull,
    InvalidId,
    InternalFailure
};

struct CapabilityRecord final {
    CapabilityId id{CapabilityId::Video};
    CapabilityState state{CapabilityState::Unknown};
    CapabilitySource source{CapabilitySource::Unknown};
};

class CapabilityGraph final {
public:
    static constexpr std::size_t capacity = 8;

    CapabilityGraph() noexcept = default;
    ~CapabilityGraph() noexcept = default;

    CapabilityGraph(const CapabilityGraph&) = delete;
    CapabilityGraph& operator=(const CapabilityGraph&) = delete;
    CapabilityGraph(CapabilityGraph&&) = delete;
    CapabilityGraph& operator=(CapabilityGraph&&) = delete;

    [[nodiscard]] bool set(CapabilityId id, CapabilityState state,
                           CapabilitySource source) noexcept;
    [[nodiscard]] bool find(CapabilityId id, CapabilityRecord& out) const noexcept;
    [[nodiscard]] CapabilityState state(CapabilityId id) const noexcept;
    [[nodiscard]] std::size_t count() const noexcept;
    void clear() noexcept;

private:
    std::array<CapabilityRecord, capacity> records_{};
    std::size_t count_{0};
};

class CapabilityProbe final {
public:
    CapabilityProbe() noexcept;
    ~CapabilityProbe() noexcept = default;

    CapabilityProbe(const CapabilityProbe&) = delete;
    CapabilityProbe& operator=(const CapabilityProbe&) = delete;
    CapabilityProbe(CapabilityProbe&&) = delete;
    CapabilityProbe& operator=(CapabilityProbe&&) = delete;

    [[nodiscard]] CapabilityError probe(CapabilityGraph& graph) noexcept;

private:
    std::thread::id owner_thread_;
};

}  // namespace stormline::core::internal
```

Headers include only C++ standard headers; no SDL/platform/third-party type.

## Semantics

### `CapabilityGraph`

- `set(id, state, source)`: validates `id`; overwrites an existing record or appends; returns false on invalid id or full capacity. Fixed capacity 8, no allocation.
- `find(id, out)`: returns true and fills the record if present; false leaves `out` unchanged.
- `state(id)`: returns the record state or `Unknown` when absent.
- `count()`: number of stored records; `clear()` empties the graph.
- No hidden global state; the graph is not thread-safe for concurrent mutation.

### `CapabilityProbe::probe(graph)`

1. Wrong owner thread → `WrongThread`; graph unchanged.
2. If `SDL_WasInit(SDL_INIT_VIDEO) == 0`: set Video/Events/Window/Displays/WaylandRuntime to `Unknown`/`SdlProbe`; return `None`.
3. Otherwise set Video/Events/Window/Displays to `Supported`/`SdlProbe`.
4. WaylandRuntime:
   - driver `wayland` → `Supported`;
   - driver `dummy`/`offscreen`/null → `Unknown`;
   - any other real driver (`x11`, `windows`, `cocoa`) → `Unsupported`.
5. Return `None`; unexpected exceptions → `InternalFailure`.

### Comparative measurement

A test mode performs a fixed iteration count of `graph.state(CapabilityId::Video)` and `SDL_WasInit(SDL_INIT_VIDEO)`, prints graph ns/op, direct ns/op and ratio, and asserts only that both operations return consistent results. **No timing threshold is asserted and no PASS/FAIL performance claim is made.** The measured values are reported in the Evidence Bundle.

## Test oracles

| ID | Scenario | Oracle |
|---|---|---|
| CAP-01 | graph states | Unknown/Supported/Unsupported round-trip; overwrite; invalid id rejected; clear empties |
| CAP-02 | probe before init | all capabilities Unknown; source SdlProbe |
| CAP-03 | probe on dummy | video/events/window/displays Supported; WaylandRuntime Unknown |
| CAP-04 | probe on real driver | video Supported; WaylandRuntime Unsupported on X11/Win32/Cocoa; macOS runtime unavailable → NOT_QUALIFIED |
| CAP-05 | wrong thread | worker probe → WrongThread; graph unchanged |
| CAP-06 | report-only benchmark | fixed iterations; prints ns/op and ratio; correctness only; existing 59 CTests regression |

No absolute budget, SAPL adoption, speedup claim or product decision is part of this contract.

## Exact implementation allowlist for packet -13

1. `src/stormline/core/internal/capability_graph.hpp`
2. `src/stormline/core/internal/capability_graph.cpp`
3. `tests/core/capability_graph_tests.cpp`
4. `CMakeLists.txt` (additive capability-graph target/tests only)
5. `.github/workflows/core01-internal-headless.yml` (additive CORE-01-13 path filters only)
6. `docs/evidence/NLE-PRPLAN-CORE-01-13.md`

`docs/work-orders/NLE-PRPLAN-CORE-01-13.md` is created by the gate and is not modified by the code packet unless an audited correction is required. No other path is allowed.

## Stop / rollback / security

- Stop on stale source, gate not merged, selector blocked, existing test regression, CI red, HIGH/CRITICAL, unsafe write, out-of-allowlist change, SAPL/performance/OS/ABI/release overclaim, or another packet/module unlock.
- Unmerged: close the branch; `main` untouched. After merge: normal revert PR, never force push.
- No secret, paid runner/service, upload, runtime download or package installation. SDL3 zlib notice remains preserved for future distribution; `NLE-D009 OPEN`; no release.
- Risk `STANDARD`, release `INTERNAL_ONLY`. ADR-0003/0075 `PROPOSED`; ADR-0092 bounded; G3 global `NOT_CLEARED`; 80/80 module WOs `BLOCKED`; `engine_implemented=false` at module/product level.

**Contract is a proposal until the exact gate PR passes Docs Validation, objective pt-BR audit and merge; code packet -13 remains blocked until then.**
