#ifndef STORMLINE_CORE_MATH_QUAT_HPP
#define STORMLINE_CORE_MATH_QUAT_HPP

#include "stormline/core/math/vec.hpp"

#include <cmath>
#include <limits>

namespace stormline::core::math {

template <typename T>
struct Quat {
    T x{};
    T y{};
    T z{};
    T w{};
};

using Quatf = Quat<f32>;
using Quatd = Quat<f64>;

template <typename T>
[[nodiscard]] constexpr Quat<T> identity_quat() noexcept {
    return Quat<T>{T{}, T{}, T{}, T{1}};
}

template <typename T>
[[nodiscard]] MathResult<Quat<T>> from_axis_angle(
    const Vec3<T>& axis, T radians) noexcept {
    if (!finite(axis) || !detail::finite_value(radians)) {
        return MathResult<Quat<T>>{Quat<T>{}, MathError::NonFinite};
    }
    const MathResult<Vec3<T>> unit_axis = normalized(axis);
    if (!unit_axis.ok()) {
        return MathResult<Quat<T>>{Quat<T>{}, unit_axis.error};
    }
    const T half_angle = radians / T{2};
    const T sine = static_cast<T>(std::sin(half_angle));
    const T cosine = static_cast<T>(std::cos(half_angle));
    const Quat<T> result{
        unit_axis.value.x * sine,
        unit_axis.value.y * sine,
        unit_axis.value.z * sine,
        cosine,
    };
    if (!detail::finite_value(result.x) || !detail::finite_value(result.y)
        || !detail::finite_value(result.z) || !detail::finite_value(result.w)) {
        return MathResult<Quat<T>>{Quat<T>{}, MathError::Overflow};
    }
    return MathResult<Quat<T>>{result, MathError::None};
}

template <typename T>
[[nodiscard]] MathResult<Quat<T>> normalized(const Quat<T>& value) noexcept {
    if (!detail::finite_value(value.x) || !detail::finite_value(value.y)
        || !detail::finite_value(value.z) || !detail::finite_value(value.w)) {
        return MathResult<Quat<T>>{Quat<T>{}, MathError::NonFinite};
    }
    const T magnitude = std::hypot(
        std::hypot(value.x, value.y), std::hypot(value.z, value.w));
    if (!detail::finite_value(magnitude)) {
        return MathResult<Quat<T>>{Quat<T>{}, MathError::Overflow};
    }
    if (magnitude == T{}) {
        return MathResult<Quat<T>>{Quat<T>{}, MathError::ZeroLength};
    }
    const T inverse = T{1} / magnitude;
    if (!detail::finite_value(inverse)) {
        return MathResult<Quat<T>>{Quat<T>{}, MathError::Overflow};
    }
    const Quat<T> result{
        value.x * inverse,
        value.y * inverse,
        value.z * inverse,
        value.w * inverse,
    };
    if (!detail::finite_value(result.x) || !detail::finite_value(result.y)
        || !detail::finite_value(result.z) || !detail::finite_value(result.w)) {
        return MathResult<Quat<T>>{Quat<T>{}, MathError::Overflow};
    }
    return MathResult<Quat<T>>{result, MathError::None};
}

template <typename T>
[[nodiscard]] constexpr Quat<T> multiply(
    const Quat<T>& lhs, const Quat<T>& rhs) noexcept {
    return Quat<T>{
        lhs.w * rhs.x + lhs.x * rhs.w + lhs.y * rhs.z - lhs.z * rhs.y,
        lhs.w * rhs.y - lhs.x * rhs.z + lhs.y * rhs.w + lhs.z * rhs.x,
        lhs.w * rhs.z + lhs.x * rhs.y - lhs.y * rhs.x + lhs.z * rhs.w,
        lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z,
    };
}

template <typename T>
[[nodiscard]] constexpr Quat<T> conjugate(const Quat<T>& value) noexcept {
    return Quat<T>{-value.x, -value.y, -value.z, value.w};
}

template <typename T>
[[nodiscard]] constexpr T dot(const Quat<T>& lhs, const Quat<T>& rhs) noexcept {
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
}

template <typename T>
[[nodiscard]] constexpr Quat<T> canonicalized(const Quat<T>& value) noexcept {
    const bool negative = value.w < T{}
        || (value.w == T{}
            && (value.x < T{} || (value.x == T{} && value.y < T{})
                || (value.x == T{} && value.y == T{} && value.z < T{})));
    if (!negative) {
        return value;
    }
    return Quat<T>{-value.x, -value.y, -value.z, -value.w};
}

template <typename T>
[[nodiscard]] MathResult<Vec3<T>> rotate(
    const Quat<T>& rotation, const Vec3<T>& value) noexcept {
    if (!detail::finite_value(rotation.x) || !detail::finite_value(rotation.y)
        || !detail::finite_value(rotation.z) || !detail::finite_value(rotation.w)
        || !finite(value)) {
        return MathResult<Vec3<T>>{Vec3<T>{}, MathError::NonFinite};
    }
    const T norm_squared = dot(rotation, rotation);
    if (!detail::finite_value(norm_squared)
        || std::fabs(norm_squared - T{1})
            > T{8} * std::numeric_limits<T>::epsilon()) {
        return MathResult<Vec3<T>>{Vec3<T>{}, MathError::InvalidQuaternion};
    }
    const Vec3<T> imaginary{rotation.x, rotation.y, rotation.z};
    const Vec3<T> cross_once = cross(imaginary, value);
    const Vec3<T> doubled_cross = scale(cross_once, T{2});
    const Vec3<T> result = add(value,
        add(scale(doubled_cross, rotation.w), cross(imaginary, doubled_cross)));
    if (!finite(result)) {
        return MathResult<Vec3<T>>{Vec3<T>{}, MathError::Overflow};
    }
    return MathResult<Vec3<T>>{result, MathError::None};
}

}  // namespace stormline::core::math

#endif  // STORMLINE_CORE_MATH_QUAT_HPP
