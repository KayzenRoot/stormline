#ifndef STORMLINE_CORE_MATH_UNITS_HPP
#define STORMLINE_CORE_MATH_UNITS_HPP

#include "stormline/core/math/vec.hpp"

namespace stormline::core::math {

struct Meters final {};
struct Centimeters final {};
struct Millimeters final {};
struct Seconds final {};
struct Milliseconds final {};
struct Radians final {};
struct Degrees final {};

template <typename T, typename Unit>
struct Quantity {
    T value{};
};

template <typename T, typename Unit>
[[nodiscard]] constexpr Quantity<T, Unit> add(
    const Quantity<T, Unit>& lhs, const Quantity<T, Unit>& rhs) noexcept {
    return Quantity<T, Unit>{lhs.value + rhs.value};
}

template <typename T, typename Unit>
[[nodiscard]] constexpr Quantity<T, Unit> subtract(
    const Quantity<T, Unit>& lhs, const Quantity<T, Unit>& rhs) noexcept {
    return Quantity<T, Unit>{lhs.value - rhs.value};
}

template <typename T, typename Unit>
[[nodiscard]] constexpr Quantity<T, Unit> scale(
    const Quantity<T, Unit>& value, T factor) noexcept {
    return Quantity<T, Unit>{value.value * factor};
}

namespace detail {

template <typename T, typename From, typename To>
[[nodiscard]] MathResult<Quantity<T, To>> convert_quantity(
    Quantity<T, From> value, T factor) noexcept {
    if (!finite_value(value.value) || !finite_value(factor)) {
        return MathResult<Quantity<T, To>>{Quantity<T, To>{}, MathError::NonFinite};
    }
    const T converted = value.value * factor;
    if (!finite_value(converted)) {
        return MathResult<Quantity<T, To>>{Quantity<T, To>{}, MathError::Overflow};
    }
    return MathResult<Quantity<T, To>>{
        Quantity<T, To>{converted}, MathError::None};
}

}  // namespace detail

template <typename T>
[[nodiscard]] MathResult<Quantity<T, Radians>> to_radians(
    Quantity<T, Degrees> value) noexcept {
    return detail::convert_quantity<T, Degrees, Radians>(
        value, static_cast<T>(kDegreesToRadians));
}

template <typename T>
[[nodiscard]] MathResult<Quantity<T, Degrees>> to_degrees(
    Quantity<T, Radians> value) noexcept {
    return detail::convert_quantity<T, Radians, Degrees>(
        value, static_cast<T>(kRadiansToDegrees));
}

template <typename T>
[[nodiscard]] MathResult<Quantity<T, Meters>> to_meters(
    Quantity<T, Centimeters> value) noexcept {
    return detail::convert_quantity<T, Centimeters, Meters>(value, T{0.01});
}

template <typename T>
[[nodiscard]] MathResult<Quantity<T, Centimeters>> to_centimeters(
    Quantity<T, Meters> value) noexcept {
    return detail::convert_quantity<T, Meters, Centimeters>(value, T{100});
}

template <typename T>
[[nodiscard]] MathResult<Quantity<T, Meters>> to_meters(
    Quantity<T, Millimeters> value) noexcept {
    return detail::convert_quantity<T, Millimeters, Meters>(value, T{0.001});
}

template <typename T>
[[nodiscard]] MathResult<Quantity<T, Seconds>> to_seconds(
    Quantity<T, Milliseconds> value) noexcept {
    return detail::convert_quantity<T, Milliseconds, Seconds>(value, T{0.001});
}

template <typename T>
[[nodiscard]] MathResult<Quantity<T, Milliseconds>> to_milliseconds(
    Quantity<T, Seconds> value) noexcept {
    return detail::convert_quantity<T, Seconds, Milliseconds>(value, T{1000});
}

}  // namespace stormline::core::math

#endif  // STORMLINE_CORE_MATH_UNITS_HPP
