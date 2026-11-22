#include "stormline/core/math/precision.hpp"

#include <cmath>
#include <cstdio>
#include <limits>
#include <string_view>

namespace {

using stormline::core::math::LocalPosition;
using stormline::core::math::local_error_bound;
using stormline::core::math::MathError;
using stormline::core::math::Origin;
using stormline::core::math::OriginEpoch;
using stormline::core::math::rebase;
using stormline::core::math::to_local;
using stormline::core::math::to_world;
using stormline::core::math::Vec3d;
using stormline::core::math::Vec3f;
using stormline::core::math::WorldPosition;

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

bool run_math08() {
    begin_case();

    const OriginEpoch epoch{7};
    const Origin origin{Vec3d{0.0, 0.0, 0.0}, epoch};
    const WorldPosition near_world{Vec3d{1'000'000.0, 0.0, 0.0}, epoch};
    const auto near_local = to_local(near_world, origin);
    expect(near_local.ok(), "1e6 local conversion");
    if (near_local.ok()) {
        const double delta = 1'000'000.0;
        expect(std::fabs(static_cast<double>(near_local.value.meters.x) - delta)
                   <= local_error_bound(delta),
               "1e6 within f32 error bound");
        expect(near_local.value.epoch.value == epoch.value, "1e6 preserves epoch");
    }

    const double large_delta = 1'000'000'000.0;
    const WorldPosition far_world{Vec3d{large_delta, 0.0, 0.0}, epoch};
    const auto far_local = to_local(far_world, origin);
    expect(far_local.ok(), "1e9 local conversion");
    if (far_local.ok()) {
        expect(std::fabs(static_cast<double>(far_local.value.meters.x) - large_delta)
                   <= local_error_bound(large_delta),
               "1e9 within f32 error bound");
    }

    const Origin far_origin{Vec3d{large_delta, 0.0, 0.0}, epoch};
    const WorldPosition nearby{Vec3d{large_delta + 123.5, 0.0, 0.0}, epoch};
    const auto nearby_local = to_local(nearby, far_origin);
    expect(nearby_local.ok()
               && std::fabs(static_cast<double>(nearby_local.value.meters.x) - 123.5)
                   <= local_error_bound(123.5),
           "large origin subtraction in f64");

    if (nearby_local.ok()) {
        const auto round_trip = to_world(nearby_local.value, far_origin);
        expect(round_trip.ok()
                   && std::fabs(round_trip.value.global_meters.x - nearby.global_meters.x)
                       <= local_error_bound(123.5),
               "local/world round-trip");
    }

    const Origin wrong_epoch{Vec3d{0.0, 0.0, 0.0}, OriginEpoch{8}};
    const auto mismatch = to_local(near_world, wrong_epoch);
    expect(!mismatch.ok() && mismatch.error == MathError::InvalidOriginEpoch,
           "epoch mismatch rejected");

    const WorldPosition huge{Vec3d{1.0e39, 0.0, 0.0}, epoch};
    const auto overflow = to_local(huge, origin);
    expect(!overflow.ok() && overflow.error == MathError::Overflow,
           "f32 range overflow rejected");

    const float nan = std::numeric_limits<float>::quiet_NaN();
    const auto nonfinite = to_world(LocalPosition{Vec3f{nan, 0.0F, 0.0F}, epoch}, origin);
    expect(!nonfinite.ok() && nonfinite.error == MathError::NonFinite,
           "non-finite local rejected");

    expect(local_error_bound(0.0) == 5.9604644775390625e-8, "error bound at zero");
    expect(local_error_bound(1.0e9) == 59.604644775390625, "error bound at 1e9");

    return finish_case();
}

bool run_math09() {
    begin_case();

    const OriginEpoch epoch{3};
    const WorldPosition original{Vec3d{12.0, -4.0, 9.0}, epoch};
    const auto rebased = rebase(original, epoch, OriginEpoch{4});
    expect(rebased.ok(), "rebase success");
    if (rebased.ok()) {
        expect(rebased.value.global_meters.x == original.global_meters.x
                   && rebased.value.global_meters.y == original.global_meters.y
                   && rebased.value.global_meters.z == original.global_meters.z,
               "rebase preserves global exactly");
        expect(rebased.value.epoch.value == 4, "rebase advances epoch");
    }

    const auto stale = rebase(original, OriginEpoch{4}, OriginEpoch{5});
    expect(!stale.ok() && stale.error == MathError::InvalidOriginEpoch,
           "stale expected epoch rejected");
    const auto backward = rebase(original, epoch, epoch);
    expect(!backward.ok() && backward.error == MathError::InvalidOriginEpoch,
           "non-advancing epoch rejected");
    const auto duplicate =
        rebase(rebased.ok() ? rebased.value : original, epoch, OriginEpoch{4});
    expect(!duplicate.ok() && duplicate.error == MathError::InvalidOriginEpoch,
           "duplicate rebase rejected");

    const WorldPosition nonfinite{
        Vec3d{std::numeric_limits<double>::infinity(), 0.0, 0.0}, epoch};
    const auto rejected = rebase(nonfinite, epoch, OriginEpoch{4});
    expect(!rejected.ok() && rejected.error == MathError::NonFinite,
           "non-finite rebase rejected");

    return finish_case();
}

}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_core05_precision_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "math08") {
        success = run_math08();
    } else if (mode == "math09") {
        success = run_math09();
    } else {
        std::fprintf(stderr, "unknown mode: %s\n", argv[1]);
        return 2;
    }
    return success ? 0 : 1;
}
