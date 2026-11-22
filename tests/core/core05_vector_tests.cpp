#include "stormline/core/math/vec.hpp"

#include <cmath>
#include <cstdio>
#include <limits>
#include <string_view>

namespace {

using stormline::core::math::add;
using stormline::core::math::approx_equal;
using stormline::core::math::cross;
using stormline::core::math::dot;
using stormline::core::math::finite;
using stormline::core::math::length;
using stormline::core::math::length_squared;
using stormline::core::math::MathError;
using stormline::core::math::MathResult;
using stormline::core::math::normalized;
using stormline::core::math::scale;
using stormline::core::math::subtract;
using stormline::core::math::Vec2f;
using stormline::core::math::Vec3d;
using stormline::core::math::Vec3f;
using stormline::core::math::Vec4f;

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

bool run_math01() {
    begin_case();

    const Vec2f a2{1.0F, 2.0F};
    const Vec2f b2{3.0F, 4.0F};
    const Vec3f a3{1.0F, 2.0F, 3.0F};
    const Vec3f b3{4.0F, 5.0F, 6.0F};
    const Vec4f a4{1.0F, 2.0F, 3.0F, 4.0F};
    const Vec4f b4{5.0F, 6.0F, 7.0F, 8.0F};

    const Vec2f sum2 = add(a2, b2);
    expect(sum2.x == 4.0F && sum2.y == 6.0F, "vec2 add exact");
    const Vec2f difference2 = subtract(b2, a2);
    expect(difference2.x == 2.0F && difference2.y == 2.0F, "vec2 subtract exact");
    const Vec2f scaled2 = scale(a2, 2.0F);
    expect(scaled2.x == 2.0F && scaled2.y == 4.0F, "vec2 scale exact");
    expect(dot(a2, b2) == 11.0F, "vec2 dot exact");

    const Vec3f sum3 = add(a3, b3);
    expect(sum3.x == 5.0F && sum3.y == 7.0F && sum3.z == 9.0F, "vec3 add exact");
    const Vec3f difference3 = subtract(b3, a3);
    expect(difference3.x == 3.0F && difference3.y == 3.0F && difference3.z == 3.0F,
           "vec3 subtract exact");
    const Vec3f scaled3 = scale(a3, -1.0F);
    expect(scaled3.x == -1.0F && scaled3.y == -2.0F && scaled3.z == -3.0F,
           "vec3 scale exact");
    expect(dot(a3, b3) == 32.0F, "vec3 dot exact");

    const Vec4f sum4 = add(a4, b4);
    expect(sum4.x == 6.0F && sum4.y == 8.0F && sum4.z == 10.0F && sum4.w == 12.0F,
           "vec4 add exact");
    const Vec4f difference4 = subtract(b4, a4);
    expect(difference4.x == 4.0F && difference4.y == 4.0F
               && difference4.z == 4.0F && difference4.w == 4.0F,
           "vec4 subtract exact");
    const Vec4f scaled4 = scale(a4, 0.5F);
    expect(scaled4.x == 0.5F && scaled4.y == 1.0F && scaled4.z == 1.5F && scaled4.w == 2.0F,
           "vec4 scale exact");
    expect(dot(a4, b4) == 70.0F, "vec4 dot exact");

    expect(length_squared(Vec3f{3.0F, 4.0F, 0.0F}) == 25.0F, "length_squared exact");
    const MathResult<float> length3 = length(Vec3f{3.0F, 4.0F, 0.0F});
    expect(length3.ok() && length3.value == 5.0F, "length exact");

    const MathResult<Vec3f> unit3 = normalized(Vec3f{3.0F, 4.0F, 0.0F});
    expect(unit3.ok(), "normalize success");
    if (unit3.ok()) {
        expect(approx_equal(unit3.value.x, 0.6F, 1.0e-6F, 1.0e-6F), "normalize x");
        expect(approx_equal(unit3.value.y, 0.8F, 1.0e-6F, 1.0e-6F), "normalize y");
        expect(unit3.value.z == 0.0F, "normalize z");
        const MathResult<float> unit_length = length(unit3.value);
        expect(unit_length.ok() && approx_equal(unit_length.value, 1.0F, 1.0e-6F, 1.0e-6F),
               "normalize unit length");
    }

    const MathResult<Vec2f> unit2 = normalized(Vec2f{0.0F, 5.0F});
    expect(unit2.ok() && unit2.value.x == 0.0F && unit2.value.y == 1.0F, "vec2 normalize");
    const MathResult<Vec4f> unit4 = normalized(Vec4f{0.0F, 0.0F, 0.0F, 2.0F});
    expect(unit4.ok() && unit4.value.w == 1.0F, "vec4 normalize");

    const float nan = std::numeric_limits<float>::quiet_NaN();
    const float infinity = std::numeric_limits<float>::infinity();
    expect(!finite(Vec3f{nan, 0.0F, 0.0F}), "finite rejects nan");
    expect(!finite(Vec3f{infinity, 0.0F, 0.0F}), "finite rejects infinity");
    expect(finite(Vec3f{1.0F, -2.0F, 3.0F}), "finite accepts values");

    expect(approx_equal(1.0F, 1.0F + 1.0e-7F, 1.0e-6F, 0.0F), "approx abs tolerance");
    expect(!approx_equal(1.0F, 1.1F, 1.0e-6F, 0.0F), "approx rejects difference");
    expect(!approx_equal(1.0F, 1.0F, -1.0F, 0.0F), "approx rejects negative tolerance");
    expect(!approx_equal(nan, nan, 1.0F, 1.0F), "approx rejects nan");

    return finish_case();
}

bool run_math02() {
    begin_case();

    const Vec3f right{1.0F, 0.0F, 0.0F};
    const Vec3f up{0.0F, 1.0F, 0.0F};
    const Vec3f forward{0.0F, 0.0F, -1.0F};

    const Vec3f z_axis = cross(right, up);
    expect(z_axis.x == 0.0F && z_axis.y == 0.0F && z_axis.z == 1.0F,
           "right-handed cross(+X,+Y)=+Z");
    const Vec3f x_axis = cross(up, forward);
    expect(x_axis.x == -1.0F && x_axis.y == 0.0F && x_axis.z == 0.0F,
           "cross(+Y,-Z)=-X");
    const Vec3f y_axis = cross(right, forward);
    expect(y_axis.x == 0.0F && y_axis.y == 1.0F && y_axis.z == 0.0F,
           "cross(+X,-Z)=+Y");

    expect(dot(right, up) == 0.0F, "right/up orthogonal");
    expect(dot(up, forward) == 0.0F, "up/forward orthogonal");
    expect(right.y == 0.0F && up.y == 1.0F && forward.z == -1.0F,
           "Y-up and -Z-forward fixtures");

    const Vec3d right_d{1.0, 0.0, 0.0};
    const Vec3d up_d{0.0, 1.0, 0.0};
    const Vec3d z_d = cross(right_d, up_d);
    expect(z_d.x == 0.0 && z_d.y == 0.0 && z_d.z == 1.0, "f64 right-handed basis");

    return finish_case();
}

bool run_errors() {
    begin_case();

    const float nan = std::numeric_limits<float>::quiet_NaN();
    const float infinity = std::numeric_limits<float>::infinity();
    const float maximum = std::numeric_limits<float>::max();

    const MathResult<Vec3f> zero = normalized(Vec3f{0.0F, 0.0F, 0.0F});
    expect(!zero.ok() && zero.error == MathError::ZeroLength, "zero normalize typed error");

    const MathResult<Vec3f> nonfinite = normalized(Vec3f{nan, 1.0F, 0.0F});
    expect(!nonfinite.ok() && nonfinite.error == MathError::NonFinite,
           "nan normalize typed error");

    const MathResult<float> length_nonfinite = length(Vec3f{infinity, 0.0F, 0.0F});
    expect(!length_nonfinite.ok() && length_nonfinite.error == MathError::NonFinite,
           "infinity length typed error");

    const MathResult<float> length_overflow = length(Vec3f{maximum, maximum, maximum});
    expect(!length_overflow.ok() && length_overflow.error == MathError::Overflow,
           "overflow length typed error");

    const MathResult<Vec3f> normalize_overflow = normalized(Vec3f{maximum, maximum, maximum});
    expect(!normalize_overflow.ok() && normalize_overflow.error == MathError::Overflow,
           "overflow normalize typed error");

    const MathResult<float> default_result;
    expect(default_result.ok() && default_result.value == 0.0F,
           "MathResult defaults to success");

    const MathResult<float> failure{0.0F, MathError::NonFinite};
    expect(!failure.ok(), "MathResult failure state");

    return finish_case();
}

}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_core05_vector_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "math01") {
        success = run_math01();
    } else if (mode == "math02") {
        success = run_math02();
    } else if (mode == "errors") {
        success = run_errors();
    } else {
        std::fprintf(stderr, "unknown mode: %s\n", argv[1]);
        return 2;
    }
    return success ? 0 : 1;
}
