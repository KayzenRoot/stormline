#include "stormline/core/internal/capability_graph.hpp"
#include "stormline/core/internal/sdl_runtime.hpp"

#if defined(SDL_h_)
#error "SDL header/type leaked through the CORE-01 capability graph header"
#endif

#include <SDL3/SDL.h>

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <string_view>
#include <thread>

namespace {

using stormline::core::internal::CapabilityError;
using stormline::core::internal::CapabilityGraph;
using stormline::core::internal::CapabilityId;
using stormline::core::internal::CapabilityProbe;
using stormline::core::internal::CapabilityRecord;
using stormline::core::internal::CapabilitySource;
using stormline::core::internal::CapabilityState;
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

bool run_states() {
    begin_case();
    CapabilityGraph graph;
    expect(graph.count() == 0, "fresh graph is empty");
    expect(graph.state(CapabilityId::Video) == CapabilityState::Unknown,
           "absent capability is unknown");

    expect(graph.set(CapabilityId::Video, CapabilityState::Unknown,
                     CapabilitySource::Explicit),
           "set unknown capability");
    expect(graph.state(CapabilityId::Video) == CapabilityState::Unknown,
           "unknown state round-trips");
    expect(graph.set(CapabilityId::WaylandRuntime, CapabilityState::Unsupported,
                     CapabilitySource::Explicit),
           "set unsupported capability");
    expect(graph.state(CapabilityId::WaylandRuntime) == CapabilityState::Unsupported,
           "unsupported state round-trips");
    expect(graph.set(CapabilityId::Video, CapabilityState::Supported,
                     CapabilitySource::SdlProbe),
           "overwrite capability");
    CapabilityRecord record{};
    expect(graph.find(CapabilityId::Video, record), "find overwritten capability");
    expect(record.state == CapabilityState::Supported, "overwritten state");
    expect(record.source == CapabilitySource::SdlProbe, "overwritten source");
    expect(graph.count() == 2, "overwrite does not grow the graph");

    expect(!graph.set(static_cast<CapabilityId>(99), CapabilityState::Supported,
                      CapabilitySource::Explicit),
           "invalid capability id is rejected");
    graph.clear();
    expect(graph.count() == 0, "clear empties the graph");
    expect(graph.state(CapabilityId::Video) == CapabilityState::Unknown,
           "clear returns capabilities to unknown");
    return finish_case();
}

bool run_uninitialized() {
    begin_case();
    CapabilityGraph graph;
    CapabilityProbe probe;
    expect(probe.probe(graph) == CapabilityError::None, "probe without runtime succeeds");
    for (CapabilityId id : {CapabilityId::Video, CapabilityId::Events,
                            CapabilityId::Window, CapabilityId::Displays,
                            CapabilityId::WaylandRuntime}) {
        CapabilityRecord record{};
        expect(graph.find(id, record), "uninitialized capability is recorded");
        expect(record.state == CapabilityState::Unknown, "uninitialized state is unknown");
        expect(record.source == CapabilitySource::SdlProbe, "uninitialized probe source");
    }
    return finish_case();
}

bool run_dummy() {
    begin_case();
    SdlRuntime runtime;
    expect(runtime.initialize() == SdlError::None, "dummy runtime initialize succeeds");
    CapabilityGraph graph;
    CapabilityProbe probe;
    expect(probe.probe(graph) == CapabilityError::None, "dummy probe succeeds");
    expect(graph.state(CapabilityId::Video) == CapabilityState::Supported, "dummy video supported");
    expect(graph.state(CapabilityId::Events) == CapabilityState::Supported,
           "dummy events supported");
    expect(graph.state(CapabilityId::Window) == CapabilityState::Supported,
           "dummy window supported");
    expect(graph.state(CapabilityId::Displays) == CapabilityState::Supported,
           "dummy displays supported");
    expect(graph.state(CapabilityId::WaylandRuntime) == CapabilityState::Unknown,
           "dummy wayland is unknown");
    expect(runtime.shutdown() == SdlError::None, "runtime shutdown succeeds");
    return finish_case();
}

bool run_real() {
    begin_case();
    SdlRuntime runtime;
    if (runtime.initialize() != SdlError::None) {
#if defined(__APPLE__)
        std::printf("NOT_QUALIFIED: cocoa runtime unavailable\n");
        return finish_case();
#else
        expect(false, "real runtime initialize succeeds");
        return finish_case();
#endif
    }

    CapabilityGraph graph;
    CapabilityProbe probe;
    expect(probe.probe(graph) == CapabilityError::None, "real probe succeeds");
    expect(graph.state(CapabilityId::Video) == CapabilityState::Supported,
           "real video supported");
    const char* driver = SDL_GetCurrentVideoDriver();
    const bool wayland = driver != nullptr && std::string_view(driver) == "wayland";
    expect(graph.state(CapabilityId::WaylandRuntime)
               == (wayland ? CapabilityState::Supported : CapabilityState::Unsupported),
           "real driver reports wayland supported or unsupported");
    expect(runtime.shutdown() == SdlError::None, "runtime shutdown succeeds");
    return finish_case();
}

bool run_wrong_thread() {
    begin_case();
    SdlRuntime runtime;
    expect(runtime.initialize() == SdlError::None, "dummy runtime initialize succeeds");
    CapabilityGraph graph;
    CapabilityProbe probe;
    expect(probe.probe(graph) == CapabilityError::None, "initial probe succeeds");
    const std::size_t before = graph.count();

    CapabilityError worker_error = CapabilityError::None;
    std::thread worker([&probe, &graph, &worker_error] { worker_error = probe.probe(graph); });
    worker.join();
    expect(worker_error == CapabilityError::WrongThread, "worker probe is rejected");
    expect(graph.count() == before, "worker probe leaves the graph unchanged");
    expect(runtime.shutdown() == SdlError::None, "runtime shutdown succeeds");
    return finish_case();
}

bool run_benchmark() {
    begin_case();
    SdlRuntime runtime;
    expect(runtime.initialize() == SdlError::None, "dummy runtime initialize succeeds");
    CapabilityGraph graph;
    CapabilityProbe probe;
    expect(probe.probe(graph) == CapabilityError::None, "probe before benchmark succeeds");
    expect(graph.state(CapabilityId::Video) == CapabilityState::Supported,
           "benchmark capability is supported");

    constexpr int iterations = 1000000;
    volatile std::uint64_t graph_sink = 0;
    volatile std::uint32_t direct_sink = 0;

    const auto graph_start = std::chrono::steady_clock::now();
    for (int index = 0; index < iterations; ++index) {
        graph_sink += static_cast<std::uint64_t>(graph.state(CapabilityId::Video));
    }
    const auto graph_end = std::chrono::steady_clock::now();

    const auto direct_start = std::chrono::steady_clock::now();
    for (int index = 0; index < iterations; ++index) {
        direct_sink += SDL_WasInit(SDL_INIT_VIDEO);
    }
    const auto direct_end = std::chrono::steady_clock::now();

    const auto graph_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(
                              graph_end - graph_start).count();
    const auto direct_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(
                               direct_end - direct_start).count();
    const double graph_per_op = static_cast<double>(graph_ns) / iterations;
    const double direct_per_op = static_cast<double>(direct_ns) / iterations;
    const double ratio = direct_per_op > 0.0 ? graph_per_op / direct_per_op : 0.0;

    std::printf("CAPABILITY_BENCHMARK graph_ns_per_op=%.3f direct_ns_per_op=%.3f ratio=%.3f "
                "iterations=%d\n",
                graph_per_op, direct_per_op, ratio, iterations);
    expect(graph_sink != 0, "graph benchmark observed supported state");
    expect(direct_sink != 0, "direct benchmark observed initialized video");
    expect(runtime.shutdown() == SdlError::None, "runtime shutdown succeeds");
    return finish_case();
}

}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr,
                     "usage: %s <states|uninitialized|dummy|real|wrong_thread|benchmark>\n",
                     argv[0]);
        return 2;
    }

    const std::string_view mode(argv[1]);
    if (mode == "states") {
        return run_states() ? 0 : 1;
    }
    if (mode == "uninitialized") {
        return run_uninitialized() ? 0 : 1;
    }
    if (mode == "dummy") {
        return run_dummy() ? 0 : 1;
    }
    if (mode == "real") {
        return run_real() ? 0 : 1;
    }
    if (mode == "wrong_thread") {
        return run_wrong_thread() ? 0 : 1;
    }
    if (mode == "benchmark") {
        return run_benchmark() ? 0 : 1;
    }

    std::fprintf(stderr, "unknown mode: %s\n", argv[1]);
    return 2;
}
