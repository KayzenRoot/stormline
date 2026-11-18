#include "stormline/core/internal/capability_graph.hpp"
#include "stormline/core/internal/display.hpp"
#include "stormline/core/internal/event_queue.hpp"
#include "stormline/core/internal/headless_host.hpp"
#include "stormline/core/internal/lifecycle.hpp"
#include "stormline/core/internal/native_bridge.hpp"
#include "stormline/core/internal/sdl_runtime.hpp"
#include "stormline/core/internal/window.hpp"

#include <SDL3/SDL.h>

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <string_view>

namespace {

using stormline::core::internal::CapabilityError;
using stormline::core::internal::CapabilityGraph;
using stormline::core::internal::CapabilityId;
using stormline::core::internal::CapabilityProbe;
using stormline::core::internal::CapabilityState;
using stormline::core::internal::DisplayError;
using stormline::core::internal::DisplayInfo;
using stormline::core::internal::DisplayService;
using stormline::core::internal::EventError;
using stormline::core::internal::EventQueue;
using stormline::core::internal::HeadlessHost;
using stormline::core::internal::HeadlessHostTestAccess;
using stormline::core::internal::HostConfig;
using stormline::core::internal::HostError;
using stormline::core::internal::HostState;
using stormline::core::internal::InputEvent;
using stormline::core::internal::LifecycleController;
using stormline::core::internal::LifecycleError;
using stormline::core::internal::LifecycleState;
using stormline::core::internal::NativeWindowHandle;
using stormline::core::internal::SdlError;
using stormline::core::internal::SdlRuntime;
using stormline::core::internal::SurfaceMetrics;
using stormline::core::internal::Window;
using stormline::core::internal::WindowConfig;
using stormline::core::internal::WindowError;

int failures = 0;

void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}

bool qualify_headless() {
    HeadlessHostTestAccess::reset_instrumentation();
    HeadlessHost host;
    for (int cycle = 0; cycle < 200; ++cycle) {
        expect(host.start(HostConfig{true}) == HostError::None, "qualify headless start");
        expect(host.state() == HostState::Running, "qualify headless running");
        expect(host.stop() == HostError::None, "qualify headless stop");
        expect(host.state() == HostState::Stopped, "qualify headless stopped");
    }
    expect(HeadlessHostTestAccess::live_resources() == 0, "qualify headless zero live resources");
    expect(HeadlessHostTestAccess::acquire_count() == HeadlessHostTestAccess::release_count(),
           "qualify headless acquire/release balanced");
    return failures == 0;
}

bool qualify_window_cycle() {
    Window window;
    expect(window.create(WindowConfig{}) == WindowError::None, "qualify window create");
    expect(window.show() == WindowError::None, "qualify window show");
    expect(window.resize(720, 540) == WindowError::None, "qualify window resize");
    SurfaceMetrics metrics{};
    expect(window.query_surface(metrics) == WindowError::None, "qualify surface query");
    expect(window.surface_valid(metrics.generation), "qualify surface valid");
    NativeWindowHandle handle{};
    expect(window.query_native_handle(handle) == WindowError::None, "qualify native handle");
    expect(window.native_handle_valid(handle), "qualify native handle valid");
    expect(window.destroy() == WindowError::None, "qualify window destroy");
    expect(!window.native_handle_valid(handle), "qualify native handle invalid after destroy");
    return failures == 0;
}

bool qualify_sdl_cycles() {
    for (int cycle = 0; cycle < 10; ++cycle) {
        SdlRuntime runtime;
        if (runtime.initialize() != SdlError::None) {
#if defined(__APPLE__)
            std::printf("NOT_QUALIFIED: cocoa runtime unavailable\n");
            expect(false, "NOT_QUALIFIED: required Cocoa runtime for qualification unavailable");
            return false;
#else
            expect(false, "qualify runtime initialize");
            return false;
#endif
        }
        if (!qualify_window_cycle()) {
            expect(runtime.shutdown() == SdlError::None, "qualify runtime shutdown after failure");
            return false;
        }
        expect(runtime.shutdown() == SdlError::None, "qualify runtime shutdown");
    }
    return failures == 0;
}

bool qualify_events_and_components() {
    SdlRuntime runtime;
    expect(runtime.initialize() == SdlError::None, "qualify component runtime initialize");
    SDL_FlushEvents(SDL_EVENT_FIRST, SDL_EVENT_LAST);

    for (int cycle = 0; cycle < 25; ++cycle) {
        if (!qualify_window_cycle()) {
            expect(runtime.shutdown() == SdlError::None, "qualify shutdown after window failure");
            return false;
        }
    }

    EventQueue queue;
    int pushed = 0;
    int produced = 0;
    for (int index = 0; index < 10000; ++index) {
        SDL_Event event{};
        event.type = SDL_EVENT_KEY_DOWN;
        event.key.timestamp = static_cast<Uint64>(index + 1);
        event.key.windowID = 0;
        event.key.key = static_cast<SDL_Keycode>(static_cast<std::uint32_t>(SDLK_A) +
                                                 static_cast<std::uint32_t>(index % 26));
        event.key.scancode = SDL_SCANCODE_A;
        event.key.down = true;
        if (SDL_PushEvent(&event)) {
            ++pushed;
        }
        ++produced;
    }
    int consumed = 0;
    for (;;) {
        const int before = consumed;
        expect(queue.poll() == EventError::None, "qualify event poll");
        while (queue.size() > 0) {
            InputEvent event{};
            expect(queue.pop(event) == EventError::None, "qualify event pop");
            if (event.type == stormline::core::internal::InputEventType::KeyDown) {
                ++consumed;
            }
        }
        if (consumed == before) {
            break;
        }
    }
    std::printf("QUAL_EVENTS produced=%d pushed=%d consumed=%d", produced, pushed, consumed);
    expect(produced == 10000, "qualify produced 10000 events");
    expect(pushed == 10000, "qualify pushed 10000 events");
    expect(consumed == 10000, "qualify consumed 10000 events");

    DisplayService display;
    std::array<DisplayInfo, 8> displays{};
    std::size_t count = 0;
    expect(display.enumerate(displays.data(), displays.size(), count) == DisplayError::None,
           "qualify display enumerate");
    expect(count >= 1, "qualify display count");
    DisplayInfo primary{};
    expect(display.primary(primary) == DisplayError::None, "qualify display primary");

    CapabilityGraph graph;
    CapabilityProbe probe;
    expect(probe.probe(graph) == CapabilityError::None, "qualify capability probe");
    expect(graph.state(CapabilityId::Video) == CapabilityState::Supported,
           "qualify video supported");

    LifecycleController lifecycle;
    for (int cycle = 0; cycle < 50; ++cycle) {
        expect(lifecycle.request_suspend() == LifecycleError::None, "qualify suspend");
        expect(lifecycle.acknowledge_suspend() == LifecycleError::None, "qualify suspend ack");
        expect(lifecycle.request_resume() == LifecycleError::None, "qualify resume");
        expect(lifecycle.acknowledge_resume() == LifecycleError::None, "qualify resume ack");
    }
    expect(lifecycle.request_shutdown() == LifecycleError::None, "qualify shutdown");
    expect(lifecycle.acknowledge_shutdown() == LifecycleError::None, "qualify shutdown ack");
    expect(lifecycle.state() == LifecycleState::Terminated, "qualify terminated");

    expect(runtime.shutdown() == SdlError::None, "qualify component runtime shutdown");
    return failures == 0;
}

bool run_qualification() {
    if (!qualify_headless() || !qualify_sdl_cycles() || !qualify_events_and_components()) {
        return false;
    }
    if (failures == 0) {
        std::printf("CORE01_QUALIFICATION_OK headless=200 sdl_cycles=10 window_cycles=25 "
                    "events=10000 lifecycle_cycles=50");
    }
    return failures == 0;
}

}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: %s qualify\n", argv[0]);
        return 2;
    }
    if (std::string_view(argv[1]) != "qualify") {
        std::fprintf(stderr, "unknown mode: %s\n", argv[1]);
        return 2;
    }
    return run_qualification() ? 0 : 1;
}
