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
using stormline::core::internal::DisplayError;
using stormline::core::internal::DisplayInfo;
using stormline::core::internal::DisplayService;
using stormline::core::internal::EventError;
using stormline::core::internal::EventQueue;
using stormline::core::internal::HeadlessHost;
using stormline::core::internal::HostConfig;
using stormline::core::internal::HostError;
using stormline::core::internal::HostState;
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

bool run_headless_cycles() {
    HeadlessHost host;
    for (int cycle = 0; cycle < 200; ++cycle) {
        expect(host.start(HostConfig{true}) == HostError::None, "headless start succeeds");
        expect(host.state() == HostState::Running, "headless host is running");
        expect(host.stop() == HostError::None, "headless stop succeeds");
        expect(host.state() == HostState::Stopped, "headless host is stopped");
    }
    return failures == 0;
}

bool run_window_cycles() {
    for (int cycle = 0; cycle < 100; ++cycle) {
        Window window;
        expect(window.create(WindowConfig{}) == WindowError::None, "soak window create");
        expect(window.show() == WindowError::None, "soak window show");
        expect(window.resize(640 + (cycle % 8) * 16, 480 + (cycle % 8) * 12)
                   == WindowError::None,
               "soak window resize");
        SurfaceMetrics metrics{};
        expect(window.query_surface(metrics) == WindowError::None, "soak surface query");
        expect(window.surface_valid(metrics.generation), "soak surface generation valid");
        NativeWindowHandle handle{};
        expect(window.query_native_handle(handle) == WindowError::None, "soak native handle");
        expect(window.native_handle_valid(handle), "soak native handle valid");
        expect(window.destroy() == WindowError::None, "soak window destroy");
        expect(!window.native_handle_valid(handle), "soak native handle invalid after destroy");
    }
    return failures == 0;
}

bool run_event_cycles() {
    SDL_FlushEvents(SDL_EVENT_FIRST, SDL_EVENT_LAST);
    EventQueue queue;
    int produced = 0;
    int pushed = 0;
    int consumed = 0;
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
    for (;;) {
        const int before = consumed;
        expect(queue.poll() == EventError::None, "soak event poll");
        while (queue.size() > 0) {
            stormline::core::internal::InputEvent out{};
            expect(queue.pop(out) == EventError::None, "soak event pop");
            ++consumed;
        }
        if (consumed == before) {
            break;
        }
    }
    std::printf("SOAK_EVENTS produced=%d pushed=%d consumed=%d", produced, pushed, consumed);
    expect(produced == 10000, "soak produced 10000 events");
    expect(pushed == 10000, "soak pushed 10000 events");
    expect(consumed == 10000, "soak consumed 10000 events");
    return failures == 0;
}

bool run_display_and_lifecycle() {
    DisplayService display;
    std::array<DisplayInfo, 8> displays{};
    std::size_t count = 0;
    expect(display.enumerate(displays.data(), displays.size(), count) == DisplayError::None,
           "soak display enumerate");
    expect(count >= 1, "soak display count");
    DisplayInfo primary{};
    expect(display.primary(primary) == DisplayError::None, "soak display primary");
    expect(primary.id != 0, "soak primary id");

    LifecycleController lifecycle;
    for (int cycle = 0; cycle < 100; ++cycle) {
        expect(lifecycle.request_suspend() == LifecycleError::None, "soak suspend request");
        expect(lifecycle.acknowledge_suspend() == LifecycleError::None, "soak suspend ack");
        expect(lifecycle.request_resume() == LifecycleError::None, "soak resume request");
        expect(lifecycle.acknowledge_resume() == LifecycleError::None, "soak resume ack");
    }
    expect(lifecycle.request_shutdown() == LifecycleError::None, "soak shutdown request");
    expect(lifecycle.acknowledge_shutdown() == LifecycleError::None, "soak shutdown ack");
    expect(lifecycle.state() == LifecycleState::Terminated, "soak lifecycle terminated");

    CapabilityGraph graph;
    CapabilityProbe probe;
    expect(probe.probe(graph) == CapabilityError::None, "soak capability probe");
    expect(graph.state(CapabilityId::Video) == stormline::core::internal::CapabilityState::Supported,
           "soak video capability supported");
    return failures == 0;
}

bool run_soak() {
    SdlRuntime runtime;
    if (runtime.initialize() != SdlError::None) {
#if defined(__APPLE__)
        std::printf("NOT_QUALIFIED: cocoa runtime unavailable\n");
        return true;
#else
        expect(false, "soak runtime initialize succeeds");
        return false;
#endif
    }

    if (!run_headless_cycles() || !run_window_cycles() || !run_event_cycles()
        || !run_display_and_lifecycle()) {
        expect(runtime.shutdown() == SdlError::None, "soak runtime shutdown after failure");
        return false;
    }

    expect(runtime.shutdown() == SdlError::None, "soak runtime shutdown succeeds");
    if (failures == 0) {
        std::printf("SOAK_OK headless=200 window=100 events=10000\n");
    }
    return failures == 0;
}

}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: %s soak\n", argv[0]);
        return 2;
    }
    if (std::string_view(argv[1]) != "soak") {
        std::fprintf(stderr, "unknown mode: %s\n", argv[1]);
        return 2;
    }
    return run_soak() ? 0 : 1;
}
