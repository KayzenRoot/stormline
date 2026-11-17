#pragma once

#include <cstdint>
#include <memory>
#include <thread>

namespace stormline::core::internal {

struct WindowConfig final {
    int width{640};
    int height{480};
};

struct SurfaceMetrics final {
    std::uint32_t display_id{0};
    float display_scale{1.0F};
    int logical_width{0};
    int logical_height{0};
    int pixel_width{0};
    int pixel_height{0};
    std::uint64_t generation{1};
};

// Internal-only typed result for the bounded native window slice. This header
// must never include SDL headers or expose SDL types/macros/handles.
enum class WindowError : std::uint8_t {
    None,
    AlreadyCreated,
    NotCreated,
    InvalidSize,
    VideoNotInitialized,
    WrongThread,
    CreateFailed,
    ResizeFailed,
    ShowFailed,
    FocusFailed,
    AllocationFailed,
    InternalFailure,
    SurfaceQueryFailed
};

// A SdlRuntime must be initialized on the same owner thread and outlive this
// object. One window per Window; single-owner thread; no public ABI.
class Window final {
public:
    Window() noexcept;
    ~Window() noexcept;

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;
    Window(Window&&) = delete;
    Window& operator=(Window&&) = delete;

    [[nodiscard]] WindowError create(const WindowConfig& config) noexcept;
    [[nodiscard]] WindowError destroy() noexcept;
    [[nodiscard]] WindowError resize(int width, int height) noexcept;
    [[nodiscard]] WindowError show() noexcept;
    [[nodiscard]] WindowError focus() noexcept;
    [[nodiscard]] WindowError query_surface(SurfaceMetrics& out) noexcept;
    [[nodiscard]] bool surface_valid(std::uint64_t generation) const noexcept;
    [[nodiscard]] bool valid() const noexcept;

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
    std::thread::id owner_thread_;
};

} // namespace stormline::core::internal
