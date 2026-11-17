#include "stormline/core/internal/headless_host.hpp"
#include <cstdint>
#include <iostream>
#include <type_traits>

using stormline::core::internal::HeadlessHost;
using stormline::core::internal::HostConfig;
using stormline::core::internal::HostError;
using stormline::core::internal::HostState;
using stormline::core::internal::HostTestSeam;

static_assert(!std::is_copy_constructible_v<HeadlessHost>);
static_assert(!std::is_move_constructible_v<HeadlessHost>);

namespace {
bool expect(bool ok, const char* label) {
    if (!ok) std::cerr << "FAIL: " << label << '\n';
    return ok;
}

bool test_cycles() {
    HostTestSeam seam;
    HeadlessHost host(&seam);
    const HostConfig config;
    bool ok = expect(host.stop() == HostError::None, "initial stop idempotent");
    for (int i = 0; i < 200; ++i) {
        ok &= expect(host.start(config) == HostError::None, "start");
        ok &= expect(host.state() == HostState::Running, "running");
        ok &= expect(host.start(config) == HostError::AlreadyRunning, "duplicate start");
        ok &= expect(host.stop() == HostError::None, "stop");
        ok &= expect(host.state() == HostState::Stopped, "stopped");
        ok &= expect(host.stop() == HostError::None, "idempotent stop");
    }
    ok &= expect(seam.acquired == 400 && seam.released == 400, "exactly one release per lease");
    return ok;
}

bool test_unsupported_mode() {
    HostTestSeam seam;
    HeadlessHost host(&seam);
    const HostConfig windowed{false};
    bool ok = expect(host.start(windowed) == HostError::UnsupportedMode, "reject non-headless");
    ok &= expect(host.state() == HostState::Stopped, "unchanged after rejected config");
    ok &= expect(seam.acquired == 0 && seam.released == 0, "no allocation on rejection");
    return ok;
}

bool test_partial_failures() {
    bool ok = true;
    for (std::uint8_t stage = 1; stage <= 3; ++stage) {
        HostTestSeam seam;
        seam.fail_stage = stage;
        HeadlessHost host(&seam);
        const HostConfig config;
        ok &= expect(host.start(config) == HostError::InitFailed, "init fault surfaced");
        ok &= expect(host.state() == HostState::Stopped, "rollback to stopped");
        ok &= expect(seam.acquired == seam.released, "partial resources released");
        seam.fail_stage = 0;
        ok &= expect(host.start(config) == HostError::None, "retry after rollback");
        ok &= expect(host.stop() == HostError::None, "stop recovered instance");
        ok &= expect(seam.acquired == seam.released, "retry resources balanced");
    }
    return ok;
}

bool test_cleanup_faults() {
    bool ok = true;
    {
        HostTestSeam seam;
        seam.fail_stage = 3;
        seam.fail_cleanup = true;
        HeadlessHost host(&seam);
        const HostConfig config;
        ok &= expect(host.start(config) == HostError::CleanupFailed, "rollback cleanup error");
        ok &= expect(host.state() == HostState::Failed, "rollback failed state");
        ok &= expect(seam.acquired > seam.released, "retained resources for retry");
        ok &= expect(host.start(config) == HostError::InvalidState, "no start in Failed");
        ok &= expect(host.stop() == HostError::CleanupFailed, "failed cleanup retry visible");
        seam.fail_cleanup = false;
        ok &= expect(host.stop() == HostError::None, "cleanup retry recovered");
        ok &= expect(seam.acquired == seam.released, "resources returned after recovery");
    }
    {
        HostTestSeam seam;
        HeadlessHost host(&seam);
        const HostConfig config;
        ok &= expect(host.start(config) == HostError::None, "start before stop failure");
        seam.fail_cleanup = true;
        ok &= expect(host.stop() == HostError::CleanupFailed, "stop cleanup error");
        ok &= expect(host.state() == HostState::Failed, "failed stop state");
        seam.fail_cleanup = false;
        ok &= expect(host.stop() == HostError::None, "recover failed stop");
        ok &= expect(host.stop() == HostError::None, "repeat cleanup is idempotent");
        ok &= expect(seam.acquired == seam.released, "no resources after cleanup");
    }
    return ok;
}

bool test_destructor() {
    HostTestSeam seam;
    {
        HeadlessHost host(&seam);
        const HostConfig config;
        if (!expect(host.start(config) == HostError::None, "start before destructor"))
            return false;
        seam.fail_cleanup = true;
    }
    return expect(seam.acquired == 2 && seam.released == 2, "destructor releases leases");
}
}

int main() {
    bool ok = test_cycles();
    ok &= test_unsupported_mode();
    ok &= test_partial_failures();
    ok &= test_cleanup_faults();
    ok &= test_destructor();
    if (!ok) return 1;
    std::cout << "PASS: 200 headless cycles, negative transitions, RAII and rollback\n";
    return 0;
}
