#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <thread>

namespace stormline::core::internal {

enum class InputEventType : std::uint8_t {
    None,
    Quit,
    KeyDown,
    KeyUp,
    MouseMotion,
    MouseButtonDown,
    MouseButtonUp,
    WindowResized,
    WindowFocusGained,
    WindowFocusLost,
    WindowCloseRequested
};

enum class EventError : std::uint8_t {
    None,
    Empty,
    Full,
    Overflow,
    WrongThread,
    RuntimeNotInitialized,
    InvalidReplay,
    InternalFailure
};

struct InputEvent final {
    InputEventType type{InputEventType::None};
    std::uint64_t sequence{0};
    std::uint64_t timestamp_ns{0};
    std::uint32_t window_id{0};
    std::int32_t keycode{0};
    std::int32_t scancode{0};
    std::uint16_t modifiers{0};
    std::uint32_t mouse_state{0};
    std::uint8_t button{0};
    std::uint8_t clicks{0};
    float x{0.0F};
    float y{0.0F};
    float xrel{0.0F};
    float yrel{0.0F};
    int width{0};
    int height{0};
};

class EventQueue final {
public:
    static constexpr std::size_t capacity = 256;

    EventQueue() noexcept;
    ~EventQueue() noexcept = default;

    EventQueue(const EventQueue&) = delete;
    EventQueue& operator=(const EventQueue&) = delete;
    EventQueue(EventQueue&&) = delete;
    EventQueue& operator=(EventQueue&&) = delete;

    [[nodiscard]] EventError poll() noexcept;
    [[nodiscard]] EventError replay(const InputEvent* events, std::size_t count) noexcept;
    [[nodiscard]] EventError pop(InputEvent& out) noexcept;
    [[nodiscard]] EventError clear() noexcept;
    [[nodiscard]] std::size_t size() const noexcept;
    [[nodiscard]] bool empty() const noexcept;
    [[nodiscard]] std::uint64_t next_sequence() const noexcept;

private:
    void push_back(const InputEvent& event) noexcept;

    std::array<InputEvent, capacity> events_{};
    std::size_t head_{0};
    std::size_t tail_{0};
    std::size_t size_{0};
    std::uint64_t next_sequence_{1};
    std::thread::id owner_thread_;
};

}  // namespace stormline::core::internal
