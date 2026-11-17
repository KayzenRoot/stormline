#include "stormline/core/internal/headless_host.hpp"

namespace stormline::core::internal {
namespace {

// Single-thread test instrument. It is deliberately small, fixed-layout and
// allocation-free so the production path does not depend on dynamic memory.
struct Instrumentation final {
    int init_failure_stage{0};
    bool cleanup_failure{false};
    int live_resources{0};
    int acquire_count{0};
    int release_count{0};
};

Instrumentation& instrumentation() noexcept {
    static Instrumentation state;
    return state;
}

} // namespace

HeadlessHost::~HeadlessHost() noexcept {
    force_release_resources();
}

HostError HeadlessHost::start(const HostConfig& config) noexcept {
    switch (state_) {
        case HostState::Running:
            return HostError::AlreadyRunning;
        case HostState::Starting:
        case HostState::Stopping:
        case HostState::Failed:
            return HostError::InvalidState;
        case HostState::Stopped:
            break;
    }

    if (!config.headless) {
        return HostError::UnsupportedMode;
    }

    state_ = HostState::Starting;
    const int failure_stage = instrumentation().init_failure_stage;

    for (int index = 0; index < kResourceCapacity; ++index) {
        if (!acquire_resource(index)) {
            if (!release_resources()) {
                state_ = HostState::Failed;
                return HostError::CleanupFailed;
            }
            state_ = HostState::Stopped;
            return HostError::InitFailed;
        }

        if (failure_stage == owned_count_) {
            if (!release_resources()) {
                state_ = HostState::Failed;
                return HostError::CleanupFailed;
            }
            state_ = HostState::Stopped;
            return HostError::InitFailed;
        }
    }

    state_ = HostState::Running;
    return HostError::None;
}

HostError HeadlessHost::stop() noexcept {
    switch (state_) {
        case HostState::Stopped:
            return HostError::None;
        case HostState::Starting:
        case HostState::Stopping:
            return HostError::InvalidState;
        case HostState::Running:
            state_ = HostState::Stopping;
            break;
        case HostState::Failed:
            break;
    }

    if (!release_resources()) {
        state_ = HostState::Failed;
        return HostError::CleanupFailed;
    }

    state_ = HostState::Stopped;
    return HostError::None;
}

HostState HeadlessHost::state() const noexcept {
    return state_;
}

bool HeadlessHost::acquire_resource(int index) noexcept {
    if (index < 0 || index >= kResourceCapacity) {
        return false;
    }

    Resource& resource = resources_[index];
    if (resource.owned) {
        return false;
    }

    resource.owned = true;
    ++owned_count_;
    ++instrumentation().live_resources;
    ++instrumentation().acquire_count;
    return true;
}

bool HeadlessHost::release_resources() noexcept {
    if (instrumentation().cleanup_failure) {
        return false;
    }

    for (int index = kResourceCapacity - 1; index >= 0; --index) {
        Resource& resource = resources_[index];
        if (!resource.owned) {
            continue;
        }

        resource.owned = false;
        --owned_count_;
        --instrumentation().live_resources;
        ++instrumentation().release_count;
    }

    return true;
}

void HeadlessHost::force_release_resources() noexcept {
    for (int index = kResourceCapacity - 1; index >= 0; --index) {
        Resource& resource = resources_[index];
        if (!resource.owned) {
            continue;
        }

        resource.owned = false;
        --owned_count_;
        --instrumentation().live_resources;
        ++instrumentation().release_count;
    }
    state_ = HostState::Stopped;
}

void HeadlessHostTestAccess::set_init_failure_stage(int stage) noexcept {
    instrumentation().init_failure_stage = stage;
}

void HeadlessHostTestAccess::set_cleanup_failure(bool enabled) noexcept {
    instrumentation().cleanup_failure = enabled;
}

void HeadlessHostTestAccess::reset_instrumentation() noexcept {
    instrumentation() = Instrumentation{};
}

int HeadlessHostTestAccess::owned_resources(const HeadlessHost& host) noexcept {
    return host.owned_count_;
}

int HeadlessHostTestAccess::live_resources() noexcept {
    return instrumentation().live_resources;
}

int HeadlessHostTestAccess::acquire_count() noexcept {
    return instrumentation().acquire_count;
}

int HeadlessHostTestAccess::release_count() noexcept {
    return instrumentation().release_count;
}

} // namespace stormline::core::internal
