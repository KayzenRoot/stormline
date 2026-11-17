#include "stormline/core/internal/event_queue.hpp"

#include <SDL3/SDL.h>

#include <algorithm>
#include <limits>
#include <thread>

namespace stormline::core::internal {
namespace {

bool on_owner_thread(const std::thread::id& owner) noexcept {
    return std::this_thread::get_id() == owner;
}

bool normalize(const SDL_Event& raw, InputEvent& out) noexcept {
    out = InputEvent{};
    out.timestamp_ns = raw.common.timestamp;

    switch (raw.type) {
        case SDL_EVENT_QUIT:
            out.type = InputEventType::Quit;
            return true;
        case SDL_EVENT_KEY_DOWN:
        case SDL_EVENT_KEY_UP:
            out.type = raw.type == SDL_EVENT_KEY_DOWN
                           ? InputEventType::KeyDown
                           : InputEventType::KeyUp;
            out.window_id = raw.key.windowID;
            out.keycode = static_cast<std::int32_t>(raw.key.key);
            out.scancode = static_cast<std::int32_t>(raw.key.scancode);
            out.modifiers = static_cast<std::uint16_t>(raw.key.mod);
            return true;
        case SDL_EVENT_MOUSE_MOTION:
            out.type = InputEventType::MouseMotion;
            out.window_id = raw.motion.windowID;
            out.mouse_state = raw.motion.state;
            out.x = raw.motion.x;
            out.y = raw.motion.y;
            out.xrel = raw.motion.xrel;
            out.yrel = raw.motion.yrel;
            return true;
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
        case SDL_EVENT_MOUSE_BUTTON_UP:
            out.type = raw.type == SDL_EVENT_MOUSE_BUTTON_DOWN
                           ? InputEventType::MouseButtonDown
                           : InputEventType::MouseButtonUp;
            out.window_id = raw.button.windowID;
            out.button = raw.button.button;
            out.clicks = raw.button.clicks;
            out.x = raw.button.x;
            out.y = raw.button.y;
            return true;
        case SDL_EVENT_WINDOW_RESIZED:
            out.type = InputEventType::WindowResized;
            out.window_id = raw.window.windowID;
            out.width = raw.window.data1;
            out.height = raw.window.data2;
            return true;
        case SDL_EVENT_WINDOW_FOCUS_GAINED:
            out.type = InputEventType::WindowFocusGained;
            out.window_id = raw.window.windowID;
            return true;
        case SDL_EVENT_WINDOW_FOCUS_LOST:
            out.type = InputEventType::WindowFocusLost;
            out.window_id = raw.window.windowID;
            return true;
        case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
            out.type = InputEventType::WindowCloseRequested;
            out.window_id = raw.window.windowID;
            return true;
        default:
            return false;
    }
}

}  // namespace

EventQueue::EventQueue() noexcept
    : owner_thread_(std::this_thread::get_id()) {}

EventError EventQueue::poll() noexcept {
    if (!on_owner_thread(owner_thread_)) {
        return EventError::WrongThread;
    }
    if (SDL_WasInit(SDL_INIT_EVENTS) == 0) {
        return EventError::RuntimeNotInitialized;
    }
    if (size_ == capacity) {
        return EventError::Overflow;
    }

    try {
        SDL_Event raw{};
        while (size_ < capacity && SDL_PollEvent(&raw)) {
            InputEvent event{};
            if (!normalize(raw, event)) {
                continue;
            }
            event.sequence = next_sequence_++;
            push_back(event);
        }
        return EventError::None;
    } catch (...) {
        return EventError::InternalFailure;
    }
}

EventError EventQueue::replay(const InputEvent* events, std::size_t count) noexcept {
    if (!on_owner_thread(owner_thread_)) {
        return EventError::WrongThread;
    }
    if (count == 0) {
        return EventError::None;
    }
    if (events == nullptr) {
        return EventError::InvalidReplay;
    }
    if (count > capacity - size_) {
        return EventError::Full;
    }

    const std::size_t last_index = (tail_ + capacity - 1) % capacity;
    std::uint64_t previous_sequence = size_ == 0 ? 0 : events_[last_index].sequence;
    std::uint64_t previous_timestamp = size_ == 0 ? 0 : events_[last_index].timestamp_ns;

    for (std::size_t index = 0; index < count; ++index) {
        const InputEvent& event = events[index];
        if (event.type == InputEventType::None) {
            return EventError::InvalidReplay;
        }
        if (event.sequence <= previous_sequence) {
            return EventError::InvalidReplay;
        }
        if (event.timestamp_ns < previous_timestamp) {
            return EventError::InvalidReplay;
        }
        if (event.sequence == std::numeric_limits<std::uint64_t>::max()) {
            return EventError::InvalidReplay;
        }
        previous_sequence = event.sequence;
        previous_timestamp = event.timestamp_ns;
    }

    for (std::size_t index = 0; index < count; ++index) {
        push_back(events[index]);
    }
    next_sequence_ = std::max(next_sequence_, previous_sequence + 1);
    return EventError::None;
}

EventError EventQueue::pop(InputEvent& out) noexcept {
    if (!on_owner_thread(owner_thread_)) {
        return EventError::WrongThread;
    }
    if (size_ == 0) {
        return EventError::Empty;
    }

    out = events_[head_];
    events_[head_] = InputEvent{};
    head_ = (head_ + 1) % capacity;
    --size_;
    return EventError::None;
}

EventError EventQueue::clear() noexcept {
    if (!on_owner_thread(owner_thread_)) {
        return EventError::WrongThread;
    }
    events_.fill(InputEvent{});
    head_ = 0;
    tail_ = 0;
    size_ = 0;
    return EventError::None;
}

std::size_t EventQueue::size() const noexcept {
    return size_;
}

bool EventQueue::empty() const noexcept {
    return size_ == 0;
}

std::uint64_t EventQueue::next_sequence() const noexcept {
    return next_sequence_;
}

void EventQueue::push_back(const InputEvent& event) noexcept {
    events_[tail_] = event;
    tail_ = (tail_ + 1) % capacity;
    ++size_;
}

}  // namespace stormline::core::internal
