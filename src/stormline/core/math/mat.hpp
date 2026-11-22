#ifndef STORMLINE_CORE_MATH_MAT_HPP
#define STORMLINE_CORE_MATH_MAT_HPP

#include "stormline/core/math/vec.hpp"

#include <array>
#include <cmath>
#include <limits>

namespace stormline::core::math {

template <typename T>
struct Mat3 {
    std::array<T, 9> elements{};
};

template <typename T>
struct Mat4 {
    std::array<T, 16> elements{};
};

using Mat3f = Mat3<f32>;
using Mat3d = Mat3<f64>;
using Mat4f = Mat4<f32>;
using Mat4d = Mat4<f64>;

template <typename T>
[[nodiscard]] constexpr Mat3<T> identity3() noexcept {
    Mat3<T> result{};
    result.elements[0] = T{1};
    result.elements[4] = T{1};
    result.elements[8] = T{1};
    return result;
}

template <typename T>
[[nodiscard]] constexpr Mat4<T> identity4() noexcept {
    Mat4<T> result{};
    result.elements[0] = T{1};
    result.elements[5] = T{1};
    result.elements[10] = T{1};
    result.elements[15] = T{1};
    return result;
}

template <typename T>
[[nodiscard]] Mat3<T> multiply(const Mat3<T>& lhs, const Mat3<T>& rhs) noexcept {
    Mat3<T> result{};
    for (std::size_t column = 0; column < 3; ++column) {
        for (std::size_t row = 0; row < 3; ++row) {
            T value{};
            for (std::size_t k = 0; k < 3; ++k) {
                value += lhs.elements[k * 3 + row] * rhs.elements[column * 3 + k];
            }
            result.elements[column * 3 + row] = value;
        }
    }
    return result;
}

template <typename T>
[[nodiscard]] Mat4<T> multiply(const Mat4<T>& lhs, const Mat4<T>& rhs) noexcept {
    Mat4<T> result{};
    for (std::size_t column = 0; column < 4; ++column) {
        for (std::size_t row = 0; row < 4; ++row) {
            T value{};
            for (std::size_t k = 0; k < 4; ++k) {
                value += lhs.elements[k * 4 + row] * rhs.elements[column * 4 + k];
            }
            result.elements[column * 4 + row] = value;
        }
    }
    return result;
}

template <typename T>
[[nodiscard]] constexpr Mat3<T> transpose(const Mat3<T>& value) noexcept {
    Mat3<T> result{};
    for (std::size_t column = 0; column < 3; ++column) {
        for (std::size_t row = 0; row < 3; ++row) {
            result.elements[column * 3 + row] = value.elements[row * 3 + column];
        }
    }
    return result;
}

template <typename T>
[[nodiscard]] constexpr Mat4<T> transpose(const Mat4<T>& value) noexcept {
    Mat4<T> result{};
    for (std::size_t column = 0; column < 4; ++column) {
        for (std::size_t row = 0; row < 4; ++row) {
            result.elements[column * 4 + row] = value.elements[row * 4 + column];
        }
    }
    return result;
}

template <typename T>
[[nodiscard]] constexpr Mat4<T> translation(const Vec3<T>& offset) noexcept {
    Mat4<T> result = identity4<T>();
    result.elements[12] = offset.x;
    result.elements[13] = offset.y;
    result.elements[14] = offset.z;
    return result;
}

template <typename T>
[[nodiscard]] constexpr Mat4<T> scaling(const Vec3<T>& factor) noexcept {
    Mat4<T> result{};
    result.elements[0] = factor.x;
    result.elements[5] = factor.y;
    result.elements[10] = factor.z;
    result.elements[15] = T{1};
    return result;
}

template <typename T>
[[nodiscard]] Mat4<T> rotation_x(T radians) noexcept {
    const T cosine = static_cast<T>(std::cos(radians));
    const T sine = static_cast<T>(std::sin(radians));
    Mat4<T> result = identity4<T>();
    result.elements[5] = cosine;
    result.elements[6] = sine;
    result.elements[9] = -sine;
    result.elements[10] = cosine;
    return result;
}

template <typename T>
[[nodiscard]] Mat4<T> rotation_y(T radians) noexcept {
    const T cosine = static_cast<T>(std::cos(radians));
    const T sine = static_cast<T>(std::sin(radians));
    Mat4<T> result = identity4<T>();
    result.elements[0] = cosine;
    result.elements[2] = -sine;
    result.elements[8] = sine;
    result.elements[10] = cosine;
    return result;
}

template <typename T>
[[nodiscard]] Mat4<T> rotation_z(T radians) noexcept {
    const T cosine = static_cast<T>(std::cos(radians));
    const T sine = static_cast<T>(std::sin(radians));
    Mat4<T> result = identity4<T>();
    result.elements[0] = cosine;
    result.elements[1] = sine;
    result.elements[4] = -sine;
    result.elements[5] = cosine;
    return result;
}

namespace detail {

template <typename T>
[[nodiscard]] bool all_finite(const Mat3<T>& value) noexcept {
    for (const T element : value.elements) {
        if (!finite_value(element)) {
            return false;
        }
    }
    return true;
}

template <typename T>
[[nodiscard]] bool all_finite(const Mat4<T>& value) noexcept {
    for (const T element : value.elements) {
        if (!finite_value(element)) {
            return false;
        }
    }
    return true;
}

template <typename T>
[[nodiscard]] T maximum_abs(const Mat3<T>& value) noexcept {
    T result{};
    for (const T element : value.elements) {
        const T magnitude = static_cast<T>(std::fabs(element));
        if (magnitude > result) {
            result = magnitude;
        }
    }
    return result;
}

template <typename T>
[[nodiscard]] T maximum_abs(const Mat4<T>& value) noexcept {
    T result{};
    for (const T element : value.elements) {
        const T magnitude = static_cast<T>(std::fabs(element));
        if (magnitude > result) {
            result = magnitude;
        }
    }
    return result;
}

}  // namespace detail

template <typename T>
[[nodiscard]] MathResult<T> determinant(const Mat3<T>& value) noexcept {
    if (!detail::all_finite(value)) {
        return MathResult<T>{T{}, MathError::NonFinite};
    }
    const T m00 = value.elements[0];
    const T m10 = value.elements[1];
    const T m20 = value.elements[2];
    const T m01 = value.elements[3];
    const T m11 = value.elements[4];
    const T m21 = value.elements[5];
    const T m02 = value.elements[6];
    const T m12 = value.elements[7];
    const T m22 = value.elements[8];
    const T result = m00 * (m11 * m22 - m12 * m21)
        - m01 * (m10 * m22 - m12 * m20)
        + m02 * (m10 * m21 - m11 * m20);
    if (!detail::finite_value(result)) {
        return MathResult<T>{T{}, MathError::Overflow};
    }
    return MathResult<T>{result, MathError::None};
}

template <typename T>
[[nodiscard]] MathResult<T> determinant(const Mat4<T>& value) noexcept {
    if (!detail::all_finite(value)) {
        return MathResult<T>{T{}, MathError::NonFinite};
    }
    const T a00 = value.elements[0];
    const T a10 = value.elements[1];
    const T a20 = value.elements[2];
    const T a30 = value.elements[3];
    const T a01 = value.elements[4];
    const T a11 = value.elements[5];
    const T a21 = value.elements[6];
    const T a31 = value.elements[7];
    const T a02 = value.elements[8];
    const T a12 = value.elements[9];
    const T a22 = value.elements[10];
    const T a32 = value.elements[11];
    const T a03 = value.elements[12];
    const T a13 = value.elements[13];
    const T a23 = value.elements[14];
    const T a33 = value.elements[15];

    const T b00 = a00 * a11 - a01 * a10;
    const T b01 = a00 * a12 - a02 * a10;
    const T b02 = a00 * a13 - a03 * a10;
    const T b03 = a01 * a12 - a02 * a11;
    const T b04 = a01 * a13 - a03 * a11;
    const T b05 = a02 * a13 - a03 * a12;
    const T b06 = a20 * a31 - a21 * a30;
    const T b07 = a20 * a32 - a22 * a30;
    const T b08 = a20 * a33 - a23 * a30;
    const T b09 = a21 * a32 - a22 * a31;
    const T b10 = a21 * a33 - a23 * a31;
    const T b11 = a22 * a33 - a23 * a32;

    const T result = b00 * b11 - b01 * b10 + b02 * b09
        + b03 * b08 - b04 * b07 + b05 * b06;
    if (!detail::finite_value(result)) {
        return MathResult<T>{T{}, MathError::Overflow};
    }
    return MathResult<T>{result, MathError::None};
}

template <typename T>
[[nodiscard]] MathResult<Mat3<T>> inverse(const Mat3<T>& value) noexcept {
    if (!detail::all_finite(value)) {
        return MathResult<Mat3<T>>{Mat3<T>{}, MathError::NonFinite};
    }
    const T scale = detail::maximum_abs(value);
    if (scale == T{}) {
        return MathResult<Mat3<T>>{Mat3<T>{}, MathError::SingularMatrix};
    }
    const MathResult<T> determinant_result = determinant(value);
    if (!determinant_result.ok()) {
        return MathResult<Mat3<T>>{Mat3<T>{}, determinant_result.error};
    }
    const T threshold = std::numeric_limits<T>::epsilon() * scale * scale * scale;
    if (!detail::finite_value(threshold)
        || std::fabs(determinant_result.value) <= threshold) {
        return MathResult<Mat3<T>>{Mat3<T>{}, MathError::SingularMatrix};
    }

    const T m00 = value.elements[0];
    const T m10 = value.elements[1];
    const T m20 = value.elements[2];
    const T m01 = value.elements[3];
    const T m11 = value.elements[4];
    const T m21 = value.elements[5];
    const T m02 = value.elements[6];
    const T m12 = value.elements[7];
    const T m22 = value.elements[8];
    const T determinant_value = determinant_result.value;

    Mat3<T> result{};
    result.elements[0] = (m11 * m22 - m12 * m21) / determinant_value;
    result.elements[1] = (m12 * m20 - m10 * m22) / determinant_value;
    result.elements[2] = (m10 * m21 - m11 * m20) / determinant_value;
    result.elements[3] = (m02 * m21 - m01 * m22) / determinant_value;
    result.elements[4] = (m00 * m22 - m02 * m20) / determinant_value;
    result.elements[5] = (m01 * m20 - m00 * m21) / determinant_value;
    result.elements[6] = (m01 * m12 - m02 * m11) / determinant_value;
    result.elements[7] = (m02 * m10 - m00 * m12) / determinant_value;
    result.elements[8] = (m00 * m11 - m01 * m10) / determinant_value;
    if (!detail::all_finite(result)) {
        return MathResult<Mat3<T>>{Mat3<T>{}, MathError::Overflow};
    }
    return MathResult<Mat3<T>>{result, MathError::None};
}

template <typename T>
[[nodiscard]] MathResult<Mat4<T>> inverse(const Mat4<T>& value) noexcept {
    if (!detail::all_finite(value)) {
        return MathResult<Mat4<T>>{Mat4<T>{}, MathError::NonFinite};
    }
    const T scale = detail::maximum_abs(value);
    if (scale == T{}) {
        return MathResult<Mat4<T>>{Mat4<T>{}, MathError::SingularMatrix};
    }
    const MathResult<T> determinant_result = determinant(value);
    if (!determinant_result.ok()) {
        return MathResult<Mat4<T>>{Mat4<T>{}, determinant_result.error};
    }
    const T threshold = std::numeric_limits<T>::epsilon() * scale * scale * scale * scale;
    if (!detail::finite_value(threshold)
        || std::fabs(determinant_result.value) <= threshold) {
        return MathResult<Mat4<T>>{Mat4<T>{}, MathError::SingularMatrix};
    }

    const T a00 = value.elements[0];
    const T a10 = value.elements[1];
    const T a20 = value.elements[2];
    const T a30 = value.elements[3];
    const T a01 = value.elements[4];
    const T a11 = value.elements[5];
    const T a21 = value.elements[6];
    const T a31 = value.elements[7];
    const T a02 = value.elements[8];
    const T a12 = value.elements[9];
    const T a22 = value.elements[10];
    const T a32 = value.elements[11];
    const T a03 = value.elements[12];
    const T a13 = value.elements[13];
    const T a23 = value.elements[14];
    const T a33 = value.elements[15];
    const T determinant_value = determinant_result.value;

    const T b00 = a00 * a11 - a01 * a10;
    const T b01 = a00 * a12 - a02 * a10;
    const T b02 = a00 * a13 - a03 * a10;
    const T b03 = a01 * a12 - a02 * a11;
    const T b04 = a01 * a13 - a03 * a11;
    const T b05 = a02 * a13 - a03 * a12;
    const T b06 = a20 * a31 - a21 * a30;
    const T b07 = a20 * a32 - a22 * a30;
    const T b08 = a20 * a33 - a23 * a30;
    const T b09 = a21 * a32 - a22 * a31;
    const T b10 = a21 * a33 - a23 * a31;
    const T b11 = a22 * a33 - a23 * a32;

    const T inv00 = (a11 * b11 - a12 * b10 + a13 * b09) / determinant_value;
    const T inv10 = (-a01 * b11 + a02 * b10 - a03 * b09) / determinant_value;
    const T inv20 = (a31 * b05 - a32 * b04 + a33 * b03) / determinant_value;
    const T inv30 = (-a21 * b05 + a22 * b04 - a23 * b03) / determinant_value;
    const T inv01 = (-a10 * b11 + a12 * b08 - a13 * b07) / determinant_value;
    const T inv11 = (a00 * b11 - a02 * b08 + a03 * b07) / determinant_value;
    const T inv21 = (-a30 * b05 + a32 * b02 - a33 * b01) / determinant_value;
    const T inv31 = (a20 * b05 - a22 * b02 + a23 * b01) / determinant_value;
    const T inv02 = (a10 * b10 - a11 * b08 + a13 * b06) / determinant_value;
    const T inv12 = (-a00 * b10 + a01 * b08 - a03 * b06) / determinant_value;
    const T inv22 = (a30 * b04 - a31 * b02 + a33 * b00) / determinant_value;
    const T inv32 = (-a20 * b04 + a21 * b02 - a23 * b00) / determinant_value;
    const T inv03 = (-a10 * b09 + a11 * b07 - a12 * b06) / determinant_value;
    const T inv13 = (a00 * b09 - a01 * b07 + a02 * b06) / determinant_value;
    const T inv23 = (-a30 * b03 + a31 * b01 - a32 * b00) / determinant_value;
    const T inv33 = (a20 * b03 - a21 * b01 + a22 * b00) / determinant_value;

    Mat4<T> result{};
    result.elements[0] = inv00;
    result.elements[1] = inv01;
    result.elements[2] = inv02;
    result.elements[3] = inv03;
    result.elements[4] = inv10;
    result.elements[5] = inv11;
    result.elements[6] = inv12;
    result.elements[7] = inv13;
    result.elements[8] = inv20;
    result.elements[9] = inv21;
    result.elements[10] = inv22;
    result.elements[11] = inv23;
    result.elements[12] = inv30;
    result.elements[13] = inv31;
    result.elements[14] = inv32;
    result.elements[15] = inv33;
    if (!detail::all_finite(result)) {
        return MathResult<Mat4<T>>{Mat4<T>{}, MathError::Overflow};
    }
    return MathResult<Mat4<T>>{result, MathError::None};
}

template <typename T>
[[nodiscard]] MathResult<Vec3<T>> transform_point(
    const Mat4<T>& matrix, const Vec3<T>& point) noexcept {
    if (!detail::all_finite(matrix) || !finite(point)) {
        return MathResult<Vec3<T>>{Vec3<T>{}, MathError::NonFinite};
    }
    const T x = matrix.elements[0] * point.x + matrix.elements[4] * point.y
        + matrix.elements[8] * point.z + matrix.elements[12];
    const T y = matrix.elements[1] * point.x + matrix.elements[5] * point.y
        + matrix.elements[9] * point.z + matrix.elements[13];
    const T z = matrix.elements[2] * point.x + matrix.elements[6] * point.y
        + matrix.elements[10] * point.z + matrix.elements[14];
    const T w = matrix.elements[3] * point.x + matrix.elements[7] * point.y
        + matrix.elements[11] * point.z + matrix.elements[15];
    if (!detail::finite_value(w) || w == T{}) {
        return MathResult<Vec3<T>>{Vec3<T>{}, MathError::SingularMatrix};
    }
    Vec3<T> result{x, y, z};
    if (w != T{1}) {
        result = scale(result, T{1} / w);
    }
    if (!finite(result)) {
        return MathResult<Vec3<T>>{Vec3<T>{}, MathError::Overflow};
    }
    return MathResult<Vec3<T>>{result, MathError::None};
}

template <typename T>
[[nodiscard]] Vec3<T> transform_direction(
    const Mat4<T>& matrix, const Vec3<T>& direction) noexcept {
    return Vec3<T>{
        matrix.elements[0] * direction.x + matrix.elements[4] * direction.y
            + matrix.elements[8] * direction.z,
        matrix.elements[1] * direction.x + matrix.elements[5] * direction.y
            + matrix.elements[9] * direction.z,
        matrix.elements[2] * direction.x + matrix.elements[6] * direction.y
            + matrix.elements[10] * direction.z,
    };
}

}  // namespace stormline::core::math

#endif  // STORMLINE_CORE_MATH_MAT_HPP
