#include "stormline/core/internal/display.hpp"
#include "stormline/core/internal/sdl_runtime.hpp"
#include "stormline/core/internal/window.hpp"

#if defined(SDL_h_)
#error "SDL header/type leaked through the CORE-01 display/window headers"
#endif

#include <SDL3/SDL.h>

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <string_view>
#include <thread>

namespace {

using stormline::core::internal::DisplayError;
using stormline::core::internal::DisplayInfo;
using stormline::core::internal::DisplayService;
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

void begin_case() {
    failures = 0;
}

bool finish_case() {
    return failures == 0;
}

bool run_displays() {
    begin_case();
    SdlRuntime runtime;
    expect(runtime.initialize() == SdlError::None, "runtime initialize succeeds");
    DisplayService service;

    std::array<DisplayInfo, 16> displays{};
    std::size_t count = 0;
    const DisplayError error = service.enumerate(displays.data(), displays.size(), count);
    expect(error == DisplayError::None, "display enumeration succeeds");
    expect(count >= 1, "at least one display is present");
    expect(count <= displays.size(), "display count fits the caller buffer");

    std::size_t primary_count = 0;
    for (std::size_t index = 0; index < count; ++index) {
        const DisplayInfo& display = displays[index];
        expect(display.id != 0, "display id is non-zero");
        expect(display.width > 0 && display.height > 0, "display bounds are positive");
        expect(display.content_scale > 0.0F, "display content scale is positive");
        expect(display.usable_width >= 0 && display.usable_height >= 0,
               "usable bounds are non-negative");
        if (display.primary) {
            ++primary_count;
        }
    }
    expect(primary_count == 1, "exactly one primary display");

    DisplayInfo primary{};
    expect(service.primary(primary) == DisplayError::None, "primary display query succeeds");
    expect(primary.primary, "primary display is marked");
    expect(primary.id != 0, "primary display id is non-zero");

    bool found = false;
    for (std::size_t index = 0; index < count; ++index) {
        if (displays[index].id == primary.id) {
            found = true;
            expect(displays[index].primary, "enumerated primary matches primary query");
        }
    }
    expect(found, "primary display appears in the enumeration");

    expect(runtime.shutdown() == SdlError::None, "runtime shutdown succeeds");
    return finish_case();
}

bool run_errors() {
    begin_case();
    SdlRuntime runtime;
    expect(runtime.initialize() == SdlError::None, "runtime initialize succeeds");
    DisplayService service;

    std::array<DisplayInfo, 16> displays{};
    std::size_t count = 7;
    expect(service.enumerate(nullptr, 1, count) == DisplayError::InvalidArgument,
           "null output with non-zero capacity is rejected");
    expect(count == 7, "invalid argument leaves count unchanged");

    std::size_t total = 0;
    expect(service.enumerate(nullptr, 0, total) == DisplayError::BufferTooSmall,
           "zero-capacity query reports a small buffer");
    expect(total >= 1, "zero-capacity query returns the total count");
    expect(total <= displays.size(), "total fits the test buffer");

    count = 0;
    expect(service.enumerate(displays.data(), total - 1, count) == DisplayError::BufferTooSmall,
           "undersized buffer is rejected");
    expect(count == total, "undersized buffer reports the total count");
    expect(service.enumerate(displays.data(), displays.size(), count) == DisplayError::None,
           "full buffer enumeration succeeds");
    expect(count == total, "full buffer returns the total count");

    expect(runtime.shutdown() == SdlError::None, "runtime shutdown succeeds");
    expect(service.enumerate(displays.data(), displays.size(), count)
               == DisplayError::VideoNotInitialized,
           "enumeration without video runtime is rejected");
    DisplayInfo primary{};
    expect(service.primary(primary) == DisplayError::VideoNotInitialized,
           "primary without video runtime is rejected");
    return finish_case();
}

bool run_wrong_thread() {
    begin_case();
    SdlRuntime runtime;
    expect(runtime.initialize() == SdlError::None, "runtime initialize succeeds");
    DisplayService service;

    DisplayError worker_enumerate = DisplayError::None;
    DisplayError worker_primary = DisplayError::None;
    std::thread worker([&service, &worker_enumerate, &worker_primary] {
        std::array<DisplayInfo, 4> displays{};
        std::size_t count = 0;
        worker_enumerate = service.enumerate(displays.data(), displays.size(), count);
        DisplayInfo primary{};
        worker_primary = service.primary(primary);
    });
    worker.join();

    expect(worker_enumerate == DisplayError::WrongThread, "worker enumeration is rejected");
    expect(worker_primary == DisplayError::WrongThread, "worker primary query is rejected");
    expect(runtime.shutdown() == SdlError::None, "runtime shutdown succeeds");
    return finish_case();
}

bool run_surface() {
    begin_case();
    SdlRuntime runtime;
    expect(runtime.initialize() == SdlError::None, "runtime initialize succeeds");

    Window window;
    expect(window.create(WindowConfig{}) == WindowError::None, "window create succeeds");
    SurfaceMetrics metrics{};
    expect(window.query_surface(metrics) == WindowError::None, "surface query succeeds");
    expect(metrics.display_id != 0, "surface display id is non-zero");
    expect(metrics.display_scale > 0.0F, "surface display scale is positive");
    expect(metrics.logical_width == 640, "surface logical width");
    expect(metrics.logical_height == 480, "surface logical height");
    expect(metrics.pixel_width > 0, "surface pixel width is positive");
    expect(metrics.pixel_height > 0, "surface pixel height is positive");
    expect(metrics.generation >= 1, "surface generation starts at one");
    expect(window.surface_valid(metrics.generation), "current generation is valid");
    expect(!window.surface_valid(0), "zero generation is invalid");

    const SurfaceMetrics original = metrics;
    expect(window.query_surface(metrics) == WindowError::None, "second surface query succeeds");
    expect(metrics.generation == original.generation,
           "stable query does not advance the generation");

    expect(window.resize(800, 600) == WindowError::None, "window resize succeeds");
    expect(!window.surface_valid(original.generation), "resize invalidates the old generation");
    SurfaceMetrics resized{};
    expect(window.query_surface(resized) == WindowError::None, "post-resize query succeeds");
    expect(resized.generation > original.generation, "resize advances the generation");
    expect(resized.logical_width == 800, "resized logical width");
    expect(resized.logical_height == 600, "resized logical height");
    expect(window.surface_valid(resized.generation), "resized generation is valid");

    expect(window.destroy() == WindowError::None, "window destroy succeeds");
    expect(!window.surface_valid(resized.generation), "destroy invalidates the generation");
    expect(runtime.shutdown() == SdlError::None, "runtime shutdown succeeds");
    return finish_case();
}

bool run_surface_errors() {
    begin_case();
    Window window;
    SurfaceMetrics metrics{};
    expect(window.query_surface(metrics) == WindowError::NotCreated,
           "query before create is rejected");
    expect(!window.surface_valid(1), "surface validity is false without a window");

    SdlRuntime runtime;
    expect(runtime.initialize() == SdlError::None, "runtime initialize succeeds");
    expect(window.create(WindowConfig{}) == WindowError::None, "window create succeeds");

    WindowError worker_query = WindowError::None;
    std::thread worker([&window, &worker_query] {
        SurfaceMetrics worker_metrics{};
        worker_query = window.query_surface(worker_metrics);
    });
    worker.join();
    expect(worker_query == WindowError::WrongThread, "worker surface query is rejected");

    expect(window.destroy() == WindowError::None, "window destroy succeeds");
    expect(window.query_surface(metrics) == WindowError::NotCreated,
           "query after destroy is rejected");
    expect(runtime.shutdown() == SdlError::None, "runtime shutdown succeeds");
    return finish_case();
}

bool run_stability() {
    begin_case();
    SdlRuntime runtime;
    expect(runtime.initialize() == SdlError::None, "runtime initialize succeeds");
    Window window;
    expect(window.create(WindowConfig{}) == WindowError::None, "window create succeeds");

    SurfaceMetrics first{};
    expect(window.query_surface(first) == WindowError::None, "first surface query succeeds");
    for (int index = 0; index < 10; ++index) {
        SurfaceMetrics current{};
        expect(window.query_surface(current) == WindowError::None, "stable surface query succeeds");
        expect(current.display_id == first.display_id, "stable display id");
        expect(current.display_scale == first.display_scale, "stable display scale");
        expect(current.logical_width == first.logical_width, "stable logical width");
        expect(current.logical_height == first.logical_height, "stable logical height");
        expect(current.pixel_width == first.pixel_width, "stable pixel width");
        expect(current.pixel_height == first.pixel_height, "stable pixel height");
        expect(current.generation == first.generation, "stable generation");
    }

    expect(window.destroy() == WindowError::None, "window destroy succeeds");
    expect(runtime.shutdown() == SdlError::None, "runtime shutdown succeeds");
    return finish_case();
}

bool run_lifetime() {
    begin_case();
    SdlRuntime runtime;
    expect(runtime.initialize() == SdlError::None, "runtime initialize succeeds");
    Window window;
    expect(window.create(WindowConfig{}) == WindowError::None, "window create succeeds");

    SurfaceMetrics previous{};
    expect(window.query_surface(previous) == WindowError::None, "initial surface query succeeds");
    bool ok = true;
    for (int cycle = 0; cycle < 100 && ok; ++cycle) {
        const int width = 640 + (cycle % 20) * 8;
        const int height = 480 + (cycle % 20) * 6;
        ok = window.resize(width, height) == WindowError::None;
        SurfaceMetrics current{};
        ok = ok && window.query_surface(current) == WindowError::None;
        ok = ok && current.generation > previous.generation;
        ok = ok && current.logical_width == width;
        ok = ok && current.logical_height == height;
        ok = ok && window.surface_valid(current.generation);
        expect(!window.surface_valid(previous.generation),
               "each resize invalidates the previous generation");
        previous = current;
    }
    expect(ok, "100 resize/query cycles succeed");
    expect(window.destroy() == WindowError::None, "window destroy succeeds");
    expect(runtime.shutdown() == SdlError::None, "runtime shutdown succeeds");
    return finish_case();
}

}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr,
                     "usage: %s <displays|errors|wrong_thread|surface|surface_errors|stability|lifetime>\n",
                     argv[0]);
        return 2;
    }

    const std::string_view mode(argv[1]);
    if (mode == "displays") {
        return run_displays() ? 0 : 1;
    }
    if (mode == "errors") {
        return run_errors() ? 0 : 1;
    }
    if (mode == "wrong_thread") {
        return run_wrong_thread() ? 0 : 1;
    }
    if (mode == "surface") {
        return run_surface() ? 0 : 1;
    }
    if (mode == "surface_errors") {
        return run_surface_errors() ? 0 : 1;
    }
    if (mode == "stability") {
        return run_stability() ? 0 : 1;
    }
    if (mode == "lifetime") {
        return run_lifetime() ? 0 : 1;
    }

    std::fprintf(stderr, "unknown mode: %s\n", argv[1]);
    return 2;
}
