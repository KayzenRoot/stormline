#pragma once

#include <cstdint>
#include <thread>

namespace stormline::core::internal {

// Internal-only typed result for the bounded SDL3 runtime slice. This header
// must never include SDL headers or expose SDL types/macros/handles.
enum class SdlError : std::uint8_t {
    None,
    AlreadyInitialized,
    WrongThread,
    InitFailed,
    InternalFailure,
    WindowsActive
};

struct SdlVersion final {
    int major{0};
    int minor{0};
    int patch{0};
};

// One active instance per process; sequential init/quit cycles are supported.
// All calls must happen on the thread that constructed the object.
class Window;

class SdlRuntime final {
public:
    SdlRuntime() noexcept;
    ~SdlRuntime() noexcept;

    SdlRuntime(const SdlRuntime&) = delete;
    SdlRuntime& operator=(const SdlRuntime&) = delete;
    SdlRuntime(SdlRuntime&&) = delete;
    SdlRuntime& operator=(SdlRuntime&&) = delete;

    [[nodiscard]] SdlError initialize() noexcept;
    [[nodiscard]] SdlError shutdown() noexcept;
    [[nodiscard]] bool initialized() const noexcept;

private:
    friend class Window;

    // Process-scoped SDL ownership and window-lifetime accounting.
    // All access is main-thread-only; no public runtime ABI is introduced.
    [[nodiscard]] static bool owns_runtime() noexcept;
    [[nodiscard]] static bool window_created(std::uint64_t& surface, std::uint64_t& native) noexcept;
    static void window_destroyed() noexcept;
    [[nodiscard]] static std::uint64_t next_generation() noexcept;

    bool initialized_{false};
    std::thread::id owner_thread_;
};

[[nodiscard]] SdlVersion linked_version() noexcept;

} // namespace stormline::core::internal
