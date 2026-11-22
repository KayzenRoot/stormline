#ifndef STORMLINE_CORE_DIAG_PROFILE_HPP
#define STORMLINE_CORE_DIAG_PROFILE_HPP

#include "stormline/core/diag/diagnostics_types.hpp"

#include <array>

namespace stormline::core::diag {

struct ProfileSample {
    u32 schema_version{kDiagnosticsSchemaVersion};
    BuildId build{};
    u32 scope_id{0};
    u32 subsystem{0};
    u64 elapsed_ns{0};
};

[[nodiscard]] inline DiagnosticError make_profile_sample(
    BuildId build, u32 scope_id, u64 elapsed_ns, u32 subsystem,
    ProfileSample& out) noexcept {
    if (!valid(build) || scope_id == 0) {
        return DiagnosticError::InvalidArgument;
    }
    ProfileSample sample{};
    sample.build = build;
    sample.scope_id = scope_id;
    sample.subsystem = subsystem;
    sample.elapsed_ns = elapsed_ns;
    out = sample;
    return DiagnosticError::None;
}

class ProfileAccumulator final {
public:
    ProfileAccumulator() noexcept = default;

    [[nodiscard]] DiagnosticError add(const ProfileSample& sample) noexcept {
        if (!valid(sample.build) || sample.scope_id == 0) {
            return DiagnosticError::InvalidArgument;
        }
        if (size_ >= kProfileCapacity) {
            ++dropped_;
            return DiagnosticError::BufferFull;
        }
        samples_[size_] = sample;
        ++size_;
        total_ns_ += sample.elapsed_ns;
        if (size_ == 1 || sample.elapsed_ns < min_ns_) {
            min_ns_ = sample.elapsed_ns;
        }
        if (sample.elapsed_ns > max_ns_) {
            max_ns_ = sample.elapsed_ns;
        }
        return DiagnosticError::None;
    }

    void reset() noexcept {
        size_ = 0;
        dropped_ = 0;
        total_ns_ = 0;
        min_ns_ = 0;
        max_ns_ = 0;
    }

    [[nodiscard]] u32 count() const noexcept { return size_; }
    [[nodiscard]] u64 total_ns() const noexcept { return total_ns_; }
    [[nodiscard]] u64 min_ns() const noexcept { return min_ns_; }
    [[nodiscard]] u64 max_ns() const noexcept { return max_ns_; }
    [[nodiscard]] u64 dropped() const noexcept { return dropped_; }

private:
    std::array<ProfileSample, kProfileCapacity> samples_{};
    u32 size_{0};
    u64 dropped_{0};
    u64 total_ns_{0};
    u64 min_ns_{0};
    u64 max_ns_{0};
};

}  // namespace stormline::core::diag

#endif  // STORMLINE_CORE_DIAG_PROFILE_HPP
