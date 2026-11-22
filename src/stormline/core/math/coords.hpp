#ifndef STORMLINE_CORE_MATH_COORDS_HPP
#define STORMLINE_CORE_MATH_COORDS_HPP

#include "stormline/core/math/mat.hpp"

namespace stormline::core::math {

struct WorldSpace final {};
struct LocalSpace final {};
struct ViewSpace final {};
struct ClipSpace final {};
struct PixelSpace final {};

template <typename T, typename Space>
struct Position3 {
    Vec3<T> value{};
};

template <typename T, typename Space>
struct Direction3 {
    Vec3<T> value{};
};

template <typename T, typename From, typename To>
struct Transform3 {
    Mat4<T> matrix{};
};

template <typename T, typename Space>
[[nodiscard]] constexpr Transform3<T, Space, Space> identity_transform() noexcept {
    return Transform3<T, Space, Space>{identity4<T>()};
}

template <typename T, typename A, typename B, typename C>
[[nodiscard]] Transform3<T, A, C> compose(
    const Transform3<T, B, C>& parent,
    const Transform3<T, A, B>& child) noexcept {
    return Transform3<T, A, C>{multiply(parent.matrix, child.matrix)};
}

template <typename T, typename From, typename To>
[[nodiscard]] MathResult<Position3<T, To>> transform_position(
    const Transform3<T, From, To>& transform,
    const Position3<T, From>& position) noexcept {
    const MathResult<Vec3<T>> result = transform_point(transform.matrix, position.value);
    if (!result.ok()) {
        return MathResult<Position3<T, To>>{Position3<T, To>{}, result.error};
    }
    return MathResult<Position3<T, To>>{Position3<T, To>{result.value}, MathError::None};
}

template <typename T, typename From, typename To>
[[nodiscard]] Direction3<T, To> transform_direction(
    const Transform3<T, From, To>& transform,
    const Direction3<T, From>& direction) noexcept {
    return Direction3<T, To>{transform_direction(transform.matrix, direction.value)};
}

template <typename T, typename From, typename To>
[[nodiscard]] MathResult<Transform3<T, To, From>> inverse(
    const Transform3<T, From, To>& transform) noexcept {
    const MathResult<Mat4<T>> result = inverse(transform.matrix);
    if (!result.ok()) {
        return MathResult<Transform3<T, To, From>>{
            Transform3<T, To, From>{}, result.error};
    }
    return MathResult<Transform3<T, To, From>>{
        Transform3<T, To, From>{result.value}, MathError::None};
}

}  // namespace stormline::core::math

#endif  // STORMLINE_CORE_MATH_COORDS_HPP
