#include "stormline/core/internal/headless_host.hpp"

#include <new>
#include <utility>

namespace stormline::core::internal {

struct HeadlessHost::Resources final {
    struct Lease final {
        explicit Lease(HostTestSeam* seam) noexcept : seam_(seam) {
            if (seam_) ++seam_->acquired;
        }
        ~Lease() noexcept {
            if (seam_) ++seam_->released;
        }
        Lease(const Lease&) = delete;
        Lease& operator=(const Lease&) = delete;
    private:
        HostTestSeam* seam_;
    };
    std::unique_ptr<Lease> first;
    std::unique_ptr<Lease> second;
};

HeadlessHost::HeadlessHost(HostTestSeam* seam) noexcept : seam_(seam) {}

HeadlessHost::~HeadlessHost() noexcept {
    // Destructor always releases owned leases, even if the simulated stop fails.
    resources_.reset();
    state_ = HostState::Stopped;
}

HostError HeadlessHost::start(const HostConfig& config) noexcept {
    if (state_ == HostState::Running) return HostError::AlreadyRunning;
    if (state_ != HostState::Stopped) return HostError::InvalidState;
    if (!config.headless) return HostError::UnsupportedMode;

    state_ = HostState::Starting;
    std::unique_ptr<Resources> pending(new (std::nothrow) Resources{});
    if (!pending) {
        state_ = HostState::Stopped;
        return HostError::InitFailed;
    }
    const auto rollback = [this, &pending]() noexcept -> HostError {
        if (seam_ && seam_->fail_cleanup && (pending->first || pending->second)) {
            resources_ = std::move(pending); // preserve ownership for a cleanup retry
            state_ = HostState::Failed;
            return HostError::CleanupFailed;
        }
        pending.reset();
        state_ = HostState::Stopped;
        return HostError::InitFailed;
    };

    if (seam_ && seam_->fail_stage == 1) return rollback();
    pending->first.reset(new (std::nothrow) Resources::Lease(seam_));
    if (!pending->first || (seam_ && seam_->fail_stage == 2)) return rollback();
    pending->second.reset(new (std::nothrow) Resources::Lease(seam_));
    if (!pending->second || (seam_ && seam_->fail_stage == 3)) return rollback();

    resources_ = std::move(pending);
    state_ = HostState::Running;
    return HostError::None;
}

HostError HeadlessHost::stop() noexcept {
    if (state_ == HostState::Stopped) return HostError::None; // idempotent
    if (state_ != HostState::Running && state_ != HostState::Failed)
        return HostError::InvalidState;
    state_ = HostState::Stopping;
    if (resources_ && seam_ && seam_->fail_cleanup) {
        state_ = HostState::Failed;
        return HostError::CleanupFailed;
    }
    resources_.reset();
    state_ = HostState::Stopped;
    return HostError::None;
}

} // namespace stormline::core::internal
