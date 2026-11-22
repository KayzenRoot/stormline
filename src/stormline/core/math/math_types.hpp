#ifndef STORMLINE_CORE_MATH_MATH_TYPES_HPP
#define STORMLINE_CORE_MATH_MATH_TYPES_HPP

#include <cstdint>

namespace stormline::core::math {

using f32 = float;
using f64 = double;

inline constexpr f64 kPi = 3.14159265358979323846;
inline constexpr f64 kDegreesToRadians = kPi / 180.0;
inline constexpr f64 kRadiansToDegrees = 180.0 / kPi;
inline constexpr std::uint32_t kMathSchemaVersion = 1;

enum class MathError : std::uint8_t {
    None,
    NonFinite,
    ZeroLength,
    SingularMatrix,
    Overflow,
    OutOfRange,
    InvalidQuaternion,
    SpaceMismatch,
    UnitMismatch,
    PrecisionLoss,
    InvalidOriginEpoch,
    StaleHandle,
    InvalidId,
    InternalFailure
};

template <typename T>
struct MathResult {
    T value{};
    MathError error{MathError::None};

    [[nodiscard]] constexpr bool ok() const noexcept {
        return error == MathError::None;
    }
};

template <typename T>
struct Vec2 {
    T x{};
    T y{};
};

template <typename T>
struct Vec3 {
    T x{};
    T y{};
    T z{};
};

template <typename T>
struct Vec4 {
    T x{};
    T y{};
    T z{};
    T w{};
};

using Vec2f = Vec2<f32>;
using Vec2d = Vec2<f64>;
using Vec3f = Vec3<f32>;
using Vec3d = Vec3<f64>;
using Vec4f = Vec4<f32>;
using Vec4d = Vec4<f64>;

}  // namespace stormline::core::math

#endif  // STORMLINE_CORE_MATH_MATH_TYPES_HPP
