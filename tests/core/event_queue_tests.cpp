#include "stormline/core/internal/event_queue.hpp"
#include "stormline/core/internal/sdl_runtime.hpp"

#if defined(SDL_h_)
#error "SDL header/type leaked through the CORE-01 event queue header"
#endif

#include <SDL3/SDL.h>

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <string_view>
#include <thread>

namespace {

using stormline::core::internal::EventError;
using stormline::core::internal::EventQueue;
using stormline::core::internal::InputEvent;
using stormline::core::internal::InputEventType;
using stormline::core::internal::SdlError;
using stormline::core::internal::SdlRuntime;

int failures = 0;

void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}

void begin_case() {
    failures = 0;
}

bool finish_case() {
    return failures == 0;
}

void flush_events() {
    SDL_FlushEvents(SDL_EVENT_FIRST, SDL_EVENT_LAST);
}

bool push_event(SDL_Event& event) {
    return SDL_PushEvent(&event);
}

InputEvent make_event(InputEventType type, std::uint64_t sequence, std::uint64_t timestamp) {
    InputEvent event{};
    event.type = type;
    event.sequence = sequence;
    event.timestamp_ns = timestamp;
    return event;
}

bool run_basic() {
    begin_case();
    SdlRuntime runtime;
    expect(runtime.initialize() == SdlError::None, "runtime initialize succeeds");
    flush_events();

    EventQueue queue;
    expect(queue.empty(), "fresh queue is empty");
    expect(queue.next_sequence() == 1, "fresh sequence starts at one");

    SDL_Event quit{};
    quit.type = SDL_EVENT_QUIT;
    quit.common.timestamp = 1000;
    expect(push_event(quit), "push quit event");

    SDL_Event key{};
    key.type = SDL_EVENT_KEY_DOWN;
    key.key.timestamp = 1001;
    key.key.windowID = 7;
    key.key.key = SDLK_A;
    key.key.scancode = SDL_SCANCODE_A;
    key.key.mod = SDL_KMOD_LSHIFT;
    key.key.down = true;
    expect(push_event(key), "push key down event");
    key.type = SDL_EVENT_KEY_UP;
    key.key.timestamp = 1002;
    key.key.down = false;
    expect(push_event(key), "push key up event");

    SDL_Event motion{};
    motion.type = SDL_EVENT_MOUSE_MOTION;
    motion.motion.timestamp = 1003;
    motion.motion.windowID = 7;
    motion.motion.state = 0x1;
    motion.motion.x = 10.5F;
    motion.motion.y = 20.5F;
    motion.motion.xrel = 1.5F;
    motion.motion.yrel = -2.5F;
    expect(push_event(motion), "push mouse motion event");

    SDL_Event button{};
    button.type = SDL_EVENT_MOUSE_BUTTON_DOWN;
    button.button.timestamp = 1004;
    button.button.windowID = 7;
    button.button.button = 1;
    button.button.clicks = 1;
    button.button.x = 10.0F;
    button.button.y = 20.0F;
    button.button.down = true;
    expect(push_event(button), "push mouse button down event");
    button.type = SDL_EVENT_MOUSE_BUTTON_UP;
    button.button.timestamp = 1005;
    button.button.down = false;
    expect(push_event(button), "push mouse button up event");

    SDL_Event resized{};
    resized.type = SDL_EVENT_WINDOW_RESIZED;
    resized.window.timestamp = 1006;
    resized.window.windowID = 7;
    resized.window.data1 = 800;
    resized.window.data2 = 600;
    expect(push_event(resized), "push window resized event");

    SDL_Event focus{};
    focus.type = SDL_EVENT_WINDOW_FOCUS_GAINED;
    focus.window.timestamp = 1007;
    focus.window.windowID = 7;
    expect(push_event(focus), "push focus gained event");
    focus.type = SDL_EVENT_WINDOW_FOCUS_LOST;
    focus.window.timestamp = 1008;
    expect(push_event(focus), "push focus lost event");

    SDL_Event close{};
    close.type = SDL_EVENT_WINDOW_CLOSE_REQUESTED;
    close.window.timestamp = 1009;
    close.window.windowID = 7;
    expect(push_event(close), "push close requested event");

    expect(queue.poll() == EventError::None, "poll succeeds");
    expect(queue.size() == 10, "poll normalized all ten events");

    InputEvent event{};
    expect(queue.pop(event) == EventError::None, "pop quit");
    expect(event.type == InputEventType::Quit, "quit type");
    expect(event.sequence == 1, "quit sequence");
    expect(event.timestamp_ns == 1000, "quit timestamp");

    expect(queue.pop(event) == EventError::None, "pop key down");
    expect(event.type == InputEventType::KeyDown, "key down type");
    expect(event.window_id == 7, "key window id");
    expect(event.keycode == static_cast<std::int32_t>(SDLK_A), "key code");
    expect(event.scancode == static_cast<std::int32_t>(SDL_SCANCODE_A), "scan code");
    expect(event.modifiers == static_cast<std::uint16_t>(SDL_KMOD_LSHIFT), "modifiers");
    expect(event.sequence == 2, "key down sequence");

    expect(queue.pop(event) == EventError::None, "pop key up");
    expect(event.type == InputEventType::KeyUp, "key up type");
    expect(event.sequence == 3, "key up sequence");

    expect(queue.pop(event) == EventError::None, "pop motion");
    expect(event.type == InputEventType::MouseMotion, "motion type");
    expect(event.x == 10.5F, "motion x");
    expect(event.y == 20.5F, "motion y");
    expect(event.xrel == 1.5F, "motion xrel");
    expect(event.yrel == -2.5F, "motion yrel");
    expect(event.mouse_state == 0x1, "motion state");

    expect(queue.pop(event) == EventError::None, "pop button down");
    expect(event.type == InputEventType::MouseButtonDown, "button down type");
    expect(event.button == 1, "button index");
    expect(event.clicks == 1, "button clicks");

    expect(queue.pop(event) == EventError::None, "pop button up");
    expect(event.type == InputEventType::MouseButtonUp, "button up type");

    expect(queue.pop(event) == EventError::None, "pop resized");
    expect(event.type == InputEventType::WindowResized, "resized type");
    expect(event.width == 800, "resized width");
    expect(event.height == 600, "resized height");

    expect(queue.pop(event) == EventError::None, "pop focus gained");
    expect(event.type == InputEventType::WindowFocusGained, "focus gained type");
    expect(queue.pop(event) == EventError::None, "pop focus lost");
    expect(event.type == InputEventType::WindowFocusLost, "focus lost type");
    expect(queue.pop(event) == EventError::None, "pop close requested");
    expect(event.type == InputEventType::WindowCloseRequested, "close requested type");
    expect(queue.empty(), "queue is empty after draining");
    expect(queue.pop(event) == EventError::Empty, "pop empty queue");

    expect(runtime.shutdown() == SdlError::None, "runtime shutdown succeeds");
    return finish_case();
}

bool run_sequence() {
    begin_case();
    SdlRuntime runtime;
    expect(runtime.initialize() == SdlError::None, "runtime initialize succeeds");
    flush_events();

    EventQueue queue;
    for (int index = 0; index < 100; ++index) {
        SDL_Event key{};
        key.type = SDL_EVENT_KEY_DOWN;
        key.key.timestamp = static_cast<Uint64>(100 + index);
        key.key.windowID = 1;
        key.key.key = static_cast<SDL_Keycode>(static_cast<std::uint32_t>(SDLK_A) +
                                               static_cast<std::uint32_t>(index));
        key.key.scancode = static_cast<SDL_Scancode>(SDL_SCANCODE_A + index);
        key.key.down = true;
        expect(push_event(key), "push sequence event");
    }

    expect(queue.poll() == EventError::None, "poll sequence events");
    expect(queue.size() == 100, "all sequence events queued");
    InputEvent event{};
    for (int index = 0; index < 100; ++index) {
        expect(queue.pop(event) == EventError::None, "pop sequence event");
        expect(event.sequence == static_cast<std::uint64_t>(index + 1), "sequence is monotonic");
        expect(event.timestamp_ns == static_cast<std::uint64_t>(100 + index),
               "timestamp is preserved");
        expect(event.keycode == static_cast<std::int32_t>(
                                    static_cast<std::uint32_t>(SDLK_A) +
                                    static_cast<std::uint32_t>(index)),
               "keycode order is preserved");
    }
    expect(queue.next_sequence() == 101, "next sequence follows the live events");
    expect(queue.poll() == EventError::None, "empty poll succeeds");
    expect(queue.empty(), "empty poll does not enqueue");
    expect(runtime.shutdown() == SdlError::None, "runtime shutdown succeeds");
    return finish_case();
}

bool run_overflow() {
    begin_case();
    SdlRuntime runtime;
    expect(runtime.initialize() == SdlError::None, "runtime initialize succeeds");
    flush_events();

    EventQueue queue;
    std::array<InputEvent, EventQueue::capacity + 1> events{};
    for (std::size_t index = 0; index < events.size(); ++index) {
        events[index] = make_event(InputEventType::Quit,
                                   static_cast<std::uint64_t>(index + 1),
                                   static_cast<std::uint64_t>(index));
    }

    expect(queue.replay(events.data(), EventQueue::capacity) == EventError::None,
           "fill queue to capacity");
    expect(queue.size() == EventQueue::capacity, "queue is full");
    expect(queue.replay(events.data() + EventQueue::capacity, 1) == EventError::Full,
           "replay beyond capacity is rejected");
    expect(queue.size() == EventQueue::capacity, "rejected replay does not mutate");
    expect(queue.poll() == EventError::Overflow, "poll reports overflow before SDL");
    expect(queue.size() == EventQueue::capacity, "overflow preserves queued events");

    InputEvent event{};
    expect(queue.pop(event) == EventError::None, "pop one queued event");
    expect(queue.size() == EventQueue::capacity - 1, "queue has one free slot");
    expect(queue.poll() == EventError::None, "poll recovers after draining");
    expect(queue.size() == EventQueue::capacity - 1, "no SDL event was queued");
    expect(runtime.shutdown() == SdlError::None, "runtime shutdown succeeds");
    return finish_case();
}

bool run_replay() {
    begin_case();
    EventQueue queue;
    std::array<InputEvent, 3> events{};
    events[0] = make_event(InputEventType::Quit, 10, 100);
    events[1] = make_event(InputEventType::KeyDown, 11, 100);
    events[1].window_id = 3;
    events[1].keycode = static_cast<std::int32_t>(SDLK_A);
    events[2] = make_event(InputEventType::MouseMotion, 12, 200);

    expect(queue.replay(events.data(), events.size()) == EventError::None,
           "replay accepts a monotonic batch");
    expect(queue.size() == events.size(), "replay enqueues the whole batch");
    expect(queue.next_sequence() == 13, "replay advances the next sequence");

    InputEvent event{};
    expect(queue.pop(event) == EventError::None, "replay pop quit");
    expect(event.sequence == 10, "replay preserves sequence");
    expect(event.timestamp_ns == 100, "replay preserves timestamp");
    expect(queue.pop(event) == EventError::None, "replay pop key");
    expect(event.window_id == 3, "replay preserves fields");
    expect(queue.pop(event) == EventError::None, "replay pop motion");
    expect(event.type == InputEventType::MouseMotion, "replay preserves type");

    InputEvent invalid = make_event(InputEventType::None, 13, 300);
    expect(queue.replay(&invalid, 1) == EventError::InvalidReplay,
           "replay rejects None type");
    expect(queue.empty(), "invalid replay is atomic");

    std::array<InputEvent, 2> descending{};
    descending[0] = make_event(InputEventType::Quit, 14, 300);
    descending[1] = make_event(InputEventType::Quit, 13, 301);
    expect(queue.replay(descending.data(), descending.size()) == EventError::InvalidReplay,
           "replay rejects descending sequence");
    expect(queue.empty(), "descending replay is atomic");

    std::array<InputEvent, 2> timestamps{};
    timestamps[0] = make_event(InputEventType::Quit, 14, 400);
    timestamps[1] = make_event(InputEventType::Quit, 15, 399);
    expect(queue.replay(timestamps.data(), timestamps.size()) == EventError::InvalidReplay,
           "replay rejects descending timestamp");
    expect(queue.empty(), "timestamp replay is atomic");

    expect(queue.replay(nullptr, 1) == EventError::InvalidReplay,
           "replay rejects null with non-zero count");
    expect(queue.replay(nullptr, 0) == EventError::None,
           "replay accepts null with zero count");
    expect(queue.empty(), "invalid replay leaves the queue unchanged");
    return finish_case();
}

bool run_wrong_thread() {
    begin_case();
    SdlRuntime runtime;
    expect(runtime.initialize() == SdlError::None, "runtime initialize succeeds");
    flush_events();

    EventQueue queue;
    SDL_Event quit{};
    quit.type = SDL_EVENT_QUIT;
    quit.common.timestamp = 2000;
    expect(push_event(quit), "push owner event");

    EventError worker_poll = EventError::None;
    EventError worker_replay = EventError::None;
    EventError worker_pop = EventError::None;
    EventError worker_clear = EventError::None;
    std::thread worker([&queue, &worker_poll, &worker_replay, &worker_pop, &worker_clear] {
        worker_poll = queue.poll();
        InputEvent event = make_event(InputEventType::Quit, 1, 1);
        worker_replay = queue.replay(&event, 1);
        InputEvent out{};
        worker_pop = queue.pop(out);
        worker_clear = queue.clear();
    });
    worker.join();

    expect(worker_poll == EventError::WrongThread, "worker poll is rejected");
    expect(worker_replay == EventError::WrongThread, "worker replay is rejected");
    expect(worker_pop == EventError::WrongThread, "worker pop is rejected");
    expect(worker_clear == EventError::WrongThread, "worker clear is rejected");
    expect(queue.empty(), "worker operations do not enqueue");
    expect(queue.poll() == EventError::None, "owner poll still works");
    expect(queue.size() == 1, "owner poll sees the SDL event");
    expect(runtime.shutdown() == SdlError::None, "runtime shutdown succeeds");
    return finish_case();
}

bool run_not_initialized() {
    begin_case();
    EventQueue queue;
    expect(queue.poll() == EventError::RuntimeNotInitialized,
           "poll without events subsystem is rejected");

    InputEvent event = make_event(InputEventType::Quit, 1, 1);
    expect(queue.replay(&event, 1) == EventError::None,
           "replay works without SDL runtime");
    InputEvent out{};
    expect(queue.pop(out) == EventError::None, "replay pop works without SDL");
    expect(out.sequence == 1, "replay sequence is preserved without SDL");
    return finish_case();
}

bool run_empty_clear() {
    begin_case();
    EventQueue queue;
    InputEvent out{};
    expect(queue.pop(out) == EventError::Empty, "pop on a fresh queue is empty");
    expect(queue.clear() == EventError::None, "clear on a fresh queue succeeds");

    std::array<InputEvent, 2> events{};
    events[0] = make_event(InputEventType::Quit, 1, 1);
    events[1] = make_event(InputEventType::KeyDown, 2, 2);
    expect(queue.replay(events.data(), events.size()) == EventError::None,
           "replay before clear succeeds");
    expect(queue.clear() == EventError::None, "clear after replay succeeds");
    expect(queue.empty(), "clear empties the queue");
    expect(queue.next_sequence() == 3, "clear preserves the sequence counter");
    expect(queue.pop(out) == EventError::Empty, "pop after clear is empty");

    InputEvent next = make_event(InputEventType::Quit, 3, 3);
    expect(queue.replay(&next, 1) == EventError::None,
           "replay after clear uses the preserved sequence");
    expect(queue.pop(out) == EventError::None, "pop after clear replay succeeds");
    expect(out.sequence == 3, "post-clear replay sequence");
    return finish_case();
}

bool run_lifetime() {
    begin_case();
    EventQueue queue;
    bool ok = true;
    for (int cycle = 0; cycle < 1000 && ok; ++cycle) {
        InputEvent event = make_event(InputEventType::Quit,
                                      static_cast<std::uint64_t>(cycle + 1),
                                      static_cast<std::uint64_t>(cycle));
        ok = queue.replay(&event, 1) == EventError::None;
        InputEvent out{};
        ok = ok && queue.pop(out) == EventError::None;
        ok = ok && out.sequence == static_cast<std::uint64_t>(cycle + 1);
        ok = ok && queue.empty();
    }
    expect(ok, "1000 replay/pop cycles succeed");
    expect(queue.next_sequence() == 1001, "lifetime sequence advances exactly");
    expect(queue.size() == 0, "lifetime leaves no queued event");
    return finish_case();
}

}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr,
                     "usage: %s <basic|sequence|overflow|replay|wrong_thread|not_initialized|empty_clear|lifetime>\n",
                     argv[0]);
        return 2;
    }

    const std::string_view mode(argv[1]);
    if (mode == "basic") {
        return run_basic() ? 0 : 1;
    }
    if (mode == "sequence") {
        return run_sequence() ? 0 : 1;
    }
    if (mode == "overflow") {
        return run_overflow() ? 0 : 1;
    }
    if (mode == "replay") {
        return run_replay() ? 0 : 1;
    }
    if (mode == "wrong_thread") {
        return run_wrong_thread() ? 0 : 1;
    }
    if (mode == "not_initialized") {
        return run_not_initialized() ? 0 : 1;
    }
    if (mode == "empty_clear") {
        return run_empty_clear() ? 0 : 1;
    }
    if (mode == "lifetime") {
        return run_lifetime() ? 0 : 1;
    }

    std::fprintf(stderr, "unknown mode: %s\n", argv[1]);
    return 2;
}
