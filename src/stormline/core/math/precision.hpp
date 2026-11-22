#ifndef STORMLINE_CORE_MATH_PRECISION_HPP
#define STORMLINE_CORE_MATH_PRECISION_HPP

#include "stormline/core/math/vec.hpp"

#include <algorithm>
#include <cmath>
#include <limits>

namespace stormline::core::math {

struct OriginEpoch {
    std::uint64_t value{0};
};

struct WorldPosition {
    Vec3<f64> global_meters{};
    OriginEpoch epoch{};
};

struct LocalPosition {
    Vec3<f32> meters{};
    OriginEpoch epoch{};
};

struct Origin {
    Vec3<f64> meters{};
    OriginEpoch epoch{};
};

[[nodiscard]] inline MathResult<LocalPosition> to_local(
    const WorldPosition& world, const Origin& origin) noexcept {
    if (!finite(world.global_meters) || !finite(origin.meters)) {
        return MathResult<LocalPosition>{LocalPosition{}, MathError::NonFinite};
    }
    if (world.epoch.value != origin.epoch.value) {
        return MathResult<LocalPosition>{LocalPosition{}, MathError::InvalidOriginEpoch};
    }
    const Vec3<f64> delta = subtract(world.global_meters, origin.meters);
    if (!finite(delta)) {
        return MathResult<LocalPosition>{LocalPosition{}, MathError::Overflow};
    }
    const f64 limit = static_cast<f64>(std::numeric_limits<f32>::max());
    if (std::fabs(delta.x) > limit || std::fabs(delta.y) > limit
        || std::fabs(delta.z) > limit) {
        return MathResult<LocalPosition>{LocalPosition{}, MathError::Overflow};
    }
    const LocalPosition result{
        Vec3<f32>{
            static_cast<f32>(delta.x),
            static_cast<f32>(delta.y),
            static_cast<f32>(delta.z),
        },
        world.epoch,
    };
    if (!finite(result.meters)) {
        return MathResult<LocalPosition>{LocalPosition{}, MathError::Overflow};
    }
    return MathResult<LocalPosition>{result, MathError::None};
}

[[nodiscard]] inline MathResult<WorldPosition> to_world(
    const LocalPosition& local, const Origin& origin) noexcept {
    if (!finite(local.meters) || !finite(origin.meters)) {
        return MathResult<WorldPosition>{WorldPosition{}, MathError::NonFinite};
    }
    if (local.epoch.value != origin.epoch.value) {
        return MathResult<WorldPosition>{WorldPosition{}, MathError::InvalidOriginEpoch};
    }
    const Vec3<f64> global = add(
        origin.meters,
        Vec3<f64>{
            static_cast<f64>(local.meters.x),
            static_cast<f64>(local.meters.y),
            static_cast<f64>(local.meters.z),
        });
    if (!finite(global)) {
        return MathResult<WorldPosition>{WorldPosition{}, MathError::Overflow};
    }
    return MathResult<WorldPosition>{WorldPosition{global, local.epoch}, MathError::None};
}

[[nodiscard]] inline MathResult<WorldPosition> rebase(
    const WorldPosition& world, OriginEpoch expected, OriginEpoch next) noexcept {
    if (!finite(world.global_meters)) {
        return MathResult<WorldPosition>{WorldPosition{}, MathError::NonFinite};
    }
    if (world.epoch.value != expected.value || next.value <= expected.value) {
        return MathResult<WorldPosition>{WorldPosition{}, MathError::InvalidOriginEpoch};
    }
    return MathResult<WorldPosition>{
        WorldPosition{world.global_meters, next}, MathError::None};
}

[[nodiscard]] inline f64 local_error_bound(f64 global_delta_meters) noexcept {
    if (!detail::finite_value(global_delta_meters)) {
        return std::numeric_limits<f64>::infinity();
    }
    constexpr f64 kF32Epsilon = 5.9604644775390625e-8;
    return kF32Epsilon * std::max(1.0, std::fabs(global_delta_meters));
}

}  // namespace stormline::core::math

#endif  // STORMLINE_CORE_MATH_PRECISION_HPP
