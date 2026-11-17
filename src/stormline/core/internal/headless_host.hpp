#pragma once

#include <cstdint>

namespace stormline::core::internal {

// Internal-only lifecycle states for the first CPU-only headless host slice.
// These symbols are not a public API, ABI or plugin boundary.
enum class HostState : std::uint8_t {
    Stopped,
    Starting,
    Running,
    Stopping,
    Failed
};

enum class HostError : std::uint8_t {
    None,
    AlreadyRunning,
    UnsupportedMode,
    InvalidState,
    InitFailed,
    CleanupFailed
};

struct HostConfig final {
    bool headless{true};
};

// Single-owner, single-thread lifecycle host. No global authority, no hidden
// OS handles and no exceptions across this internal boundary.
class HeadlessHost final {
public:
    HeadlessHost() noexcept = default;
    ~HeadlessHost() noexcept;

    HeadlessHost(const HeadlessHost&) = delete;
    HeadlessHost& operator=(const HeadlessHost&) = delete;
    HeadlessHost(HeadlessHost&&) = delete;
    HeadlessHost& operator=(HeadlessHost&&) = delete;

    [[nodiscard]] HostError start(const HostConfig& config) noexcept;
    [[nodiscard]] HostError stop() noexcept;
    [[nodiscard]] HostState state() const noexcept;

private:
    friend struct HeadlessHostTestAccess;

    static constexpr int kResourceCapacity = 3;

    struct Resource final {
        bool owned{false};
    };

    [[nodiscard]] bool acquire_resource(int index) noexcept;
    [[nodiscard]] bool release_resources() noexcept;
    void force_release_resources() noexcept;

    HostState state_{HostState::Stopped};
    Resource resources_[kResourceCapacity]{};
    int owned_count_{0};
};

// Internal-only instrumentation seam. It exists so the approved failure and
// ownership tests can be written without exposing injection as a public API.
// It is not part of any ABI, release surface or production contract.
struct HeadlessHostTestAccess final {
    static void set_init_failure_stage(int stage) noexcept;
    static void set_cleanup_failure(bool enabled) noexcept;
    static void reset_instrumentation() noexcept;

    [[nodiscard]] static int owned_resources(const HeadlessHost& host) noexcept;
    [[nodiscard]] static int live_resources() noexcept;
    [[nodiscard]] static int acquire_count() noexcept;
    [[nodiscard]] static int release_count() noexcept;
};

} // namespace stormline::core::internal
