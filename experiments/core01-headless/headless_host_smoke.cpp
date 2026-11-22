#include "headless_host.hpp"

#include <iostream>

namespace {
[[nodiscard]] bool verify(bool condition, const char* description) {
    if (!condition) {
        std::cerr << "FAIL: " << description << '\n';
    }
    return condition;
}
} // namespace

int main() {
    using namespace stormline::experimental;
    HeadlessHost host;
    if (!verify(host.state() == HostState::stopped, "initial state") ||
        !verify(host.stop() == HostError::not_running, "stop without start")) {
        return 1;
    }

    for (int cycle = 0; cycle < 200; ++cycle) {
        if (!verify(host.start() == HostError::none, "start") ||
            !verify(host.state() == HostState::running, "running state") ||
            !verify(host.start() == HostError::already_running, "duplicate start") ||
            !verify(host.stop() == HostError::none, "stop") ||
            !verify(host.state() == HostState::stopped, "stopped state") ||
            !verify(host.stop() == HostError::not_running, "duplicate stop")) {
            return 1;
        }
    }
    if (!verify(host.starts() == 200, "completed cycles")) {
        return 1;
    }
    std::cout << "PASS: 200 deterministic headless state cycles\n";
    return 0;
}
