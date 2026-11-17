#include "stormline/core/internal/headless_host.hpp"

#include <cstdio>
#include <iostream>
#include <string_view>

namespace {

using stormline::core::internal::HeadlessHost;
using stormline::core::internal::HeadlessHostTestAccess;
using stormline::core::internal::HostConfig;
using stormline::core::internal::HostError;
using stormline::core::internal::HostState;

int failures = 0;

void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}

void begin_case() {
    failures = 0;
    HeadlessHostTestAccess::reset_instrumentation();
}

bool finish_case() {
    return failures == 0;
}

bool run_lifecycle() {
    begin_case();
    HeadlessHost host;

    expect(host.state() == HostState::Stopped, "initial state is Stopped");
    expect(host.stop() == HostError::None, "stop on Stopped is idempotent");

    for (int cycle = 0; cycle < 200; ++cycle) {
        const HostConfig config{};
        expect(host.start(config) == HostError::None, "start succeeds");
        expect(host.state() == HostState::Running, "state is Running");
        expect(HeadlessHostTestAccess::owned_resources(host) == 3, "three resources are owned");
        expect(host.start(config) == HostError::AlreadyRunning, "duplicate start is rejected");
        expect(HeadlessHostTestAccess::owned_resources(host) == 3, "duplicate start does not allocate");
        expect(host.stop() == HostError::None, "stop succeeds");
        expect(host.state() == HostState::Stopped, "state is Stopped");
        expect(HeadlessHostTestAccess::owned_resources(host) == 0, "resources are released");
        expect(host.stop() == HostError::None, "repeated stop is idempotent");
    }

    expect(HeadlessHostTestAccess::live_resources() == 0, "no live resources after 200 cycles");
    expect(HeadlessHostTestAccess::acquire_count() == 600, "600 acquisitions");
    expect(HeadlessHostTestAccess::release_count() == 600, "600 releases");
    return finish_case();
}

bool run_errors() {
    begin_case();
    {
        HeadlessHost host;
        HostConfig config{};
        config.headless = false;
        expect(host.start(config) == HostError::UnsupportedMode, "window mode is unsupported");
        expect(host.state() == HostState::Stopped, "unsupported mode leaves state Stopped");
        expect(HeadlessHostTestAccess::owned_resources(host) == 0, "unsupported mode allocates nothing");
        expect(HeadlessHostTestAccess::live_resources() == 0, "no live resource after unsupported mode");
        expect(HeadlessHostTestAccess::acquire_count() == 0, "no acquisition after unsupported mode");
        expect(host.stop() == HostError::None, "stop after unsupported mode is idempotent");
    }

    for (int stage = 1; stage <= 3; ++stage) {
        begin_case();
        HeadlessHostTestAccess::set_init_failure_stage(stage);
        HeadlessHost host;
        expect(host.start(HostConfig{}) == HostError::InitFailed, "injected init failure");
        expect(host.state() == HostState::Stopped, "init failure returns to Stopped");
        expect(HeadlessHostTestAccess::owned_resources(host) == 0, "init rollback releases resources");
        expect(HeadlessHostTestAccess::live_resources() == 0, "no live resources after init failure");
        expect(HeadlessHostTestAccess::acquire_count() == stage, "expected acquisition count");
        expect(HeadlessHostTestAccess::release_count() == stage, "expected release count");

        HeadlessHostTestAccess::set_init_failure_stage(0);
        expect(host.start(HostConfig{}) == HostError::None, "recovery start succeeds");
        expect(host.stop() == HostError::None, "recovery stop succeeds");
        expect(HeadlessHostTestAccess::owned_resources(host) == 0, "recovery leaves no resources");
    }

    begin_case();
    HeadlessHostTestAccess::set_init_failure_stage(3);
    HeadlessHostTestAccess::set_cleanup_failure(true);
    {
        HeadlessHost host;
        expect(host.start(HostConfig{}) == HostError::CleanupFailed, "init cleanup failure is reported");
        expect(host.state() == HostState::Failed, "cleanup failure enters Failed");
        expect(HeadlessHostTestAccess::owned_resources(host) == 3, "failed cleanup retains resources");
        expect(HeadlessHostTestAccess::live_resources() == 3, "live resources retained after failure");
        expect(host.start(HostConfig{}) == HostError::InvalidState, "start from Failed is invalid");
        expect(HeadlessHostTestAccess::acquire_count() == 3, "start from Failed does not allocate");

        HeadlessHostTestAccess::set_cleanup_failure(false);
        expect(host.stop() == HostError::None, "cleanup retry recovers");
        expect(host.state() == HostState::Stopped, "recovery returns to Stopped");
        expect(HeadlessHostTestAccess::owned_resources(host) == 0, "recovery releases resources");
        expect(HeadlessHostTestAccess::live_resources() == 0, "no live resources after recovery");
        expect(HeadlessHostTestAccess::release_count() == 3, "resources released exactly once");

        HeadlessHostTestAccess::set_init_failure_stage(0);
        expect(host.start(HostConfig{}) == HostError::None, "start after recovery succeeds");
        expect(host.stop() == HostError::None, "stop after recovery succeeds");
    }
    return finish_case();
}

bool run_cleanup() {
    begin_case();
    {
        HeadlessHost host;
        expect(host.start(HostConfig{}) == HostError::None, "start before cleanup failure");
        HeadlessHostTestAccess::set_cleanup_failure(true);
        expect(host.stop() == HostError::CleanupFailed, "cleanup failure is reported");
        expect(host.state() == HostState::Failed, "cleanup failure enters Failed");
        expect(HeadlessHostTestAccess::owned_resources(host) == 3, "resources retained on cleanup failure");
        expect(HeadlessHostTestAccess::live_resources() == 3, "live resources retained on cleanup failure");
        expect(HeadlessHostTestAccess::release_count() == 0, "no release on failed cleanup");

        expect(host.start(HostConfig{}) == HostError::InvalidState, "start from Failed is invalid");
        expect(HeadlessHostTestAccess::owned_resources(host) == 3, "invalid start keeps ownership");
        expect(host.stop() == HostError::CleanupFailed, "repeated cleanup failure is reported");
        expect(HeadlessHostTestAccess::owned_resources(host) == 3, "repeated failure keeps ownership");
        expect(HeadlessHostTestAccess::release_count() == 0, "repeated failure does not release twice");

        HeadlessHostTestAccess::set_cleanup_failure(false);
        expect(host.stop() == HostError::None, "cleanup retry succeeds");
        expect(host.state() == HostState::Stopped, "cleanup retry returns to Stopped");
        expect(HeadlessHostTestAccess::owned_resources(host) == 0, "cleanup retry releases exactly once");
        expect(HeadlessHostTestAccess::live_resources() == 0, "no live resources after retry");
        expect(HeadlessHostTestAccess::acquire_count() == 3, "no extra acquisition");
        expect(HeadlessHostTestAccess::release_count() == 3, "exactly three releases");
        expect(host.stop() == HostError::None, "stop after recovery is idempotent");
    }
    return finish_case();
}

bool run_destructor() {
    begin_case();
    {
        HeadlessHost host;
        expect(host.start(HostConfig{}) == HostError::None, "start for running destructor");
        expect(HeadlessHostTestAccess::live_resources() == 3, "resources live before destruction");
    }
    expect(HeadlessHostTestAccess::live_resources() == 0, "running destructor releases resources");
    expect(HeadlessHostTestAccess::release_count() == 3, "running destructor releases exactly once");

    begin_case();
    HeadlessHostTestAccess::set_init_failure_stage(3);
    HeadlessHostTestAccess::set_cleanup_failure(true);
    {
        HeadlessHost host;
        expect(host.start(HostConfig{}) == HostError::CleanupFailed, "start for failed destructor");
        expect(HeadlessHostTestAccess::live_resources() == 3, "failed host retains resources");
    }
    expect(HeadlessHostTestAccess::live_resources() == 0, "failed destructor force-releases resources");
    return finish_case();
}

bool run_invalid() {
    begin_case();
    HeadlessHost host;
    expect(host.stop() == HostError::None, "stop on Stopped is None");
    expect(host.start(HostConfig{}) == HostError::None, "start succeeds");
    expect(host.start(HostConfig{}) == HostError::AlreadyRunning, "duplicate start is AlreadyRunning");
    expect(host.stop() == HostError::None, "stop succeeds");
    expect(host.state() == HostState::Stopped, "state returns to Stopped");
    expect(host.stop() == HostError::None, "stop is idempotent");
    return finish_case();
}

} // namespace

int main(int argc, char** argv) {
    const std::string_view mode = argc > 1 ? std::string_view(argv[1]) : std::string_view("all");

    bool ok = true;
    if (mode == "all" || mode == "lifecycle") {
        ok = run_lifecycle() && ok;
    }
    if (mode == "all" || mode == "errors") {
        ok = run_errors() && ok;
    }
    if (mode == "all" || mode == "cleanup") {
        ok = run_cleanup() && ok;
    }
    if (mode == "all" || mode == "destructor") {
        ok = run_destructor() && ok;
    }
    if (mode == "all" || mode == "invalid") {
        ok = run_invalid() && ok;
    }

    if (mode != "all" && mode != "lifecycle" && mode != "errors" && mode != "cleanup"
        && mode != "destructor" && mode != "invalid") {
        std::cerr << "Unknown test mode: " << mode << '\n';
        return 2;
    }

    if (ok) {
        std::cout << "PASS: " << mode << '\n';
        return 0;
    }
    std::cerr << "FAIL: " << mode << '\n';
    return 1;
}
