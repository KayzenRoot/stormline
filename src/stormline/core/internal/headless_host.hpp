#pragma once
#include <cstdint>
#include <memory>

namespace stormline::core::internal {

enum class HostState : std::uint8_t { Stopped, Starting, Running, Stopping, Failed };
enum class HostError : std::uint8_t {
    None, AlreadyRunning, UnsupportedMode, InvalidState, InitFailed, CleanupFailed
};
struct HostConfig final { bool headless{true}; };

// Test-only seam in the INTERNAL interface. Borrowed pointer must outlive the host.
struct HostTestSeam final {
    std::uint8_t fail_stage{0};  // 1=before acquisition, 2=after first, 3=after second
    bool fail_cleanup{false};
    std::uint64_t acquired{0};
    std::uint64_t released{0};
};

class HeadlessHost final {
public:
    explicit HeadlessHost(HostTestSeam* seam = nullptr) noexcept;
    ~HeadlessHost() noexcept;
    HeadlessHost(const HeadlessHost&) = delete;
    HeadlessHost& operator=(const HeadlessHost&) = delete;
    HeadlessHost(HeadlessHost&&) = delete;
    HeadlessHost& operator=(HeadlessHost&&) = delete;

    [[nodiscard]] HostError start(const HostConfig& config) noexcept;
    [[nodiscard]] HostError stop() noexcept;
    [[nodiscard]] HostState state() const noexcept { return state_; }

private:
    struct Resources;
    std::unique_ptr<Resources> resources_;
    HostTestSeam* seam_{nullptr};
    HostState state_{HostState::Stopped};
};

} // namespace stormline::core::internal
