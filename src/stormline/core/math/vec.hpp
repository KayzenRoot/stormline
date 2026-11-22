#ifndef STORMLINE_CORE_MATH_VEC_HPP
#define STORMLINE_CORE_MATH_VEC_HPP

#include "stormline/core/math/math_types.hpp"

#include <algorithm>
#include <cmath>
#include <limits>

namespace stormline::core::math {

namespace detail {

template <typename T>
[[nodiscard]] constexpr bool finite_value(T value) noexcept {
    return value == value
        && value != std::numeric_limits<T>::infinity()
        && value != -std::numeric_limits<T>::infinity();
}

}  // namespace detail

template <typename T>
[[nodiscard]] constexpr Vec2<T> add(const Vec2<T>& lhs, const Vec2<T>& rhs) noexcept {
    return Vec2<T>{lhs.x + rhs.x, lhs.y + rhs.y};
}

template <typename T>
[[nodiscard]] constexpr Vec3<T> add(const Vec3<T>& lhs, const Vec3<T>& rhs) noexcept {
    return Vec3<T>{lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
}

template <typename T>
[[nodiscard]] constexpr Vec4<T> add(const Vec4<T>& lhs, const Vec4<T>& rhs) noexcept {
    return Vec4<T>{lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w};
}

template <typename T>
[[nodiscard]] constexpr Vec2<T> subtract(const Vec2<T>& lhs, const Vec2<T>& rhs) noexcept {
    return Vec2<T>{lhs.x - rhs.x, lhs.y - rhs.y};
}

template <typename T>
[[nodiscard]] constexpr Vec3<T> subtract(const Vec3<T>& lhs, const Vec3<T>& rhs) noexcept {
    return Vec3<T>{lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
}

template <typename T>
[[nodiscard]] constexpr Vec4<T> subtract(const Vec4<T>& lhs, const Vec4<T>& rhs) noexcept {
    return Vec4<T>{lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w};
}

template <typename T>
[[nodiscard]] constexpr Vec2<T> scale(const Vec2<T>& value, T factor) noexcept {
    return Vec2<T>{value.x * factor, value.y * factor};
}

template <typename T>
[[nodiscard]] constexpr Vec3<T> scale(const Vec3<T>& value, T factor) noexcept {
    return Vec3<T>{value.x * factor, value.y * factor, value.z * factor};
}

template <typename T>
[[nodiscard]] constexpr Vec4<T> scale(const Vec4<T>& value, T factor) noexcept {
    return Vec4<T>{value.x * factor, value.y * factor, value.z * factor, value.w * factor};
}

template <typename T>
[[nodiscard]] constexpr T dot(const Vec2<T>& lhs, const Vec2<T>& rhs) noexcept {
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

template <typename T>
[[nodiscard]] constexpr T dot(const Vec3<T>& lhs, const Vec3<T>& rhs) noexcept {
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

template <typename T>
[[nodiscard]] constexpr T dot(const Vec4<T>& lhs, const Vec4<T>& rhs) noexcept {
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
}

template <typename T>
[[nodiscard]] constexpr Vec3<T> cross(const Vec3<T>& lhs, const Vec3<T>& rhs) noexcept {
    return Vec3<T>{
        lhs.y * rhs.z - lhs.z * rhs.y,
        lhs.z * rhs.x - lhs.x * rhs.z,
        lhs.x * rhs.y - lhs.y * rhs.x,
    };
}

template <typename T>
[[nodiscard]] constexpr T length_squared(const Vec2<T>& value) noexcept {
    return dot(value, value);
}

template <typename T>
[[nodiscard]] constexpr T length_squared(const Vec3<T>& value) noexcept {
    return dot(value, value);
}

template <typename T>
[[nodiscard]] constexpr T length_squared(const Vec4<T>& value) noexcept {
    return dot(value, value);
}

template <typename T>
[[nodiscard]] MathResult<T> length(const Vec2<T>& value) noexcept {
    if (!detail::finite_value(value.x) || !detail::finite_value(value.y)) {
        return MathResult<T>{T{}, MathError::NonFinite};
    }
    const T magnitude = std::hypot(value.x, value.y);
    if (!detail::finite_value(magnitude)) {
        return MathResult<T>{T{}, MathError::Overflow};
    }
    return MathResult<T>{magnitude, MathError::None};
}

template <typename T>
[[nodiscard]] MathResult<T> length(const Vec3<T>& value) noexcept {
    if (!detail::finite_value(value.x) || !detail::finite_value(value.y) || !detail::finite_value(value.z)) {
        return MathResult<T>{T{}, MathError::NonFinite};
    }
    const T magnitude = std::hypot(value.x, value.y, value.z);
    if (!detail::finite_value(magnitude)) {
        return MathResult<T>{T{}, MathError::Overflow};
    }
    return MathResult<T>{magnitude, MathError::None};
}

template <typename T>
[[nodiscard]] MathResult<T> length(const Vec4<T>& value) noexcept {
    if (!detail::finite_value(value.x) || !detail::finite_value(value.y)
        || !detail::finite_value(value.z) || !detail::finite_value(value.w)) {
        return MathResult<T>{T{}, MathError::NonFinite};
    }
    const T magnitude = std::hypot(std::hypot(value.x, value.y), std::hypot(value.z, value.w));
    if (!detail::finite_value(magnitude)) {
        return MathResult<T>{T{}, MathError::Overflow};
    }
    return MathResult<T>{magnitude, MathError::None};
}

template <typename T>
[[nodiscard]] MathResult<Vec2<T>> normalized(const Vec2<T>& value) noexcept {
    const MathResult<T> magnitude = length(value);
    if (!magnitude.ok()) {
        return MathResult<Vec2<T>>{Vec2<T>{}, magnitude.error};
    }
    if (magnitude.value == T{}) {
        return MathResult<Vec2<T>>{Vec2<T>{}, MathError::ZeroLength};
    }
    const T inverse = T{1} / magnitude.value;
    if (!detail::finite_value(inverse)) {
        return MathResult<Vec2<T>>{Vec2<T>{}, MathError::Overflow};
    }
    const Vec2<T> result = scale(value, inverse);
    if (!detail::finite_value(result.x) || !detail::finite_value(result.y)) {
        return MathResult<Vec2<T>>{Vec2<T>{}, MathError::Overflow};
    }
    return MathResult<Vec2<T>>{result, MathError::None};
}

template <typename T>
[[nodiscard]] MathResult<Vec3<T>> normalized(const Vec3<T>& value) noexcept {
    const MathResult<T> magnitude = length(value);
    if (!magnitude.ok()) {
        return MathResult<Vec3<T>>{Vec3<T>{}, magnitude.error};
    }
    if (magnitude.value == T{}) {
        return MathResult<Vec3<T>>{Vec3<T>{}, MathError::ZeroLength};
    }
    const T inverse = T{1} / magnitude.value;
    if (!detail::finite_value(inverse)) {
        return MathResult<Vec3<T>>{Vec3<T>{}, MathError::Overflow};
    }
    const Vec3<T> result = scale(value, inverse);
    if (!detail::finite_value(result.x) || !detail::finite_value(result.y) || !detail::finite_value(result.z)) {
        return MathResult<Vec3<T>>{Vec3<T>{}, MathError::Overflow};
    }
    return MathResult<Vec3<T>>{result, MathError::None};
}

template <typename T>
[[nodiscard]] MathResult<Vec4<T>> normalized(const Vec4<T>& value) noexcept {
    const MathResult<T> magnitude = length(value);
    if (!magnitude.ok()) {
        return MathResult<Vec4<T>>{Vec4<T>{}, magnitude.error};
    }
    if (magnitude.value == T{}) {
        return MathResult<Vec4<T>>{Vec4<T>{}, MathError::ZeroLength};
    }
    const T inverse = T{1} / magnitude.value;
    if (!detail::finite_value(inverse)) {
        return MathResult<Vec4<T>>{Vec4<T>{}, MathError::Overflow};
    }
    const Vec4<T> result = scale(value, inverse);
    if (!detail::finite_value(result.x) || !detail::finite_value(result.y)
        || !detail::finite_value(result.z) || !detail::finite_value(result.w)) {
        return MathResult<Vec4<T>>{Vec4<T>{}, MathError::Overflow};
    }
    return MathResult<Vec4<T>>{result, MathError::None};
}

template <typename T>
[[nodiscard]] constexpr bool finite(const Vec2<T>& value) noexcept {
    return detail::finite_value(value.x) && detail::finite_value(value.y);
}

template <typename T>
[[nodiscard]] constexpr bool finite(const Vec3<T>& value) noexcept {
    return detail::finite_value(value.x) && detail::finite_value(value.y) && detail::finite_value(value.z);
}

template <typename T>
[[nodiscard]] constexpr bool finite(const Vec4<T>& value) noexcept {
    return detail::finite_value(value.x) && detail::finite_value(value.y)
        && detail::finite_value(value.z) && detail::finite_value(value.w);
}

template <typename T>
[[nodiscard]] bool approx_equal(T lhs, T rhs, T abs_tolerance, T rel_tolerance) noexcept {
    if (!detail::finite_value(abs_tolerance) || !detail::finite_value(rel_tolerance)
        || abs_tolerance < T{} || rel_tolerance < T{}) {
        return false;
    }
    if (!detail::finite_value(lhs) || !detail::finite_value(rhs)) {
        return false;
    }
    const T difference = static_cast<T>(std::fabs(lhs - rhs));
    const T scale_value = std::max(static_cast<T>(std::fabs(lhs)),
                                   static_cast<T>(std::fabs(rhs)));
    const T threshold = std::max(abs_tolerance, rel_tolerance * scale_value);
    return difference <= threshold;
}

template <typename T>
[[nodiscard]] bool approx_equal(const Vec2<T>& lhs, const Vec2<T>& rhs,
                                T abs_tolerance, T rel_tolerance) noexcept {
    return approx_equal(lhs.x, rhs.x, abs_tolerance, rel_tolerance)
        && approx_equal(lhs.y, rhs.y, abs_tolerance, rel_tolerance);
}

template <typename T>
[[nodiscard]] bool approx_equal(const Vec3<T>& lhs, const Vec3<T>& rhs,
                                T abs_tolerance, T rel_tolerance) noexcept {
    return approx_equal(lhs.x, rhs.x, abs_tolerance, rel_tolerance)
        && approx_equal(lhs.y, rhs.y, abs_tolerance, rel_tolerance)
        && approx_equal(lhs.z, rhs.z, abs_tolerance, rel_tolerance);
}

template <typename T>
[[nodiscard]] bool approx_equal(const Vec4<T>& lhs, const Vec4<T>& rhs,
                                T abs_tolerance, T rel_tolerance) noexcept {
    return approx_equal(lhs.x, rhs.x, abs_tolerance, rel_tolerance)
        && approx_equal(lhs.y, rhs.y, abs_tolerance, rel_tolerance)
        && approx_equal(lhs.z, rhs.z, abs_tolerance, rel_tolerance)
        && approx_equal(lhs.w, rhs.w, abs_tolerance, rel_tolerance);
}

}  // namespace stormline::core::math

#endif  // STORMLINE_CORE_MATH_VEC_HPP
