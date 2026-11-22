#include "stormline/core/math/mat.hpp"
#include "stormline/core/math/quat.hpp"

#include <cmath>
#include <cstdio>
#include <limits>
#include <string_view>

namespace {

using stormline::core::math::approx_equal;
using stormline::core::math::canonicalized;
using stormline::core::math::conjugate;
using stormline::core::math::determinant;
using stormline::core::math::dot;
using stormline::core::math::from_axis_angle;
using stormline::core::math::identity3;
using stormline::core::math::identity4;
using stormline::core::math::identity_quat;
using stormline::core::math::inverse;
using stormline::core::math::Mat3f;
using stormline::core::math::Mat4f;
using stormline::core::math::MathError;
using stormline::core::math::MathResult;
using stormline::core::math::multiply;
using stormline::core::math::normalized;
using stormline::core::math::Quatf;
using stormline::core::math::rotate;
using stormline::core::math::rotation_x;
using stormline::core::math::rotation_y;
using stormline::core::math::rotation_z;
using stormline::core::math::scaling;
using stormline::core::math::transform_direction;
using stormline::core::math::transform_point;
using stormline::core::math::translation;
using stormline::core::math::Vec3f;

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

bool matrix_near(const Mat4f& lhs, const Mat4f& rhs, float tolerance) {
    for (std::size_t index = 0; index < lhs.elements.size(); ++index) {
        if (!approx_equal(lhs.elements[index], rhs.elements[index], tolerance, 0.0F)) {
            return false;
        }
    }
    return true;
}

bool matrix3_near(const Mat3f& lhs, const Mat3f& rhs, float tolerance) {
    for (std::size_t index = 0; index < lhs.elements.size(); ++index) {
        if (!approx_equal(lhs.elements[index], rhs.elements[index], tolerance, 0.0F)) {
            return false;
        }
    }
    return true;
}

bool vector_near(const Vec3f& lhs, const Vec3f& rhs, float tolerance) {
    return approx_equal(lhs, rhs, tolerance, 0.0F);
}

bool quat_near(const Quatf& lhs, const Quatf& rhs, float tolerance) {
    return approx_equal(lhs.x, rhs.x, tolerance, 0.0F)
        && approx_equal(lhs.y, rhs.y, tolerance, 0.0F)
        && approx_equal(lhs.z, rhs.z, tolerance, 0.0F)
        && approx_equal(lhs.w, rhs.w, tolerance, 0.0F);
}

bool run_math03() {
    begin_case();

    const Mat4f identity = identity4<float>();
    expect(identity.elements[0] == 1.0F && identity.elements[5] == 1.0F
               && identity.elements[10] == 1.0F && identity.elements[15] == 1.0F,
           "identity diagonal");

    const MathResult<Vec3f> identity_point =
        transform_point(identity, Vec3f{1.0F, -2.0F, 3.0F});
    expect(identity_point.ok() && vector_near(identity_point.value, Vec3f{1.0F, -2.0F, 3.0F}, 1.0e-6F),
           "identity preserves point");

    const Mat4f translate = translation(Vec3f{1.0F, 2.0F, 3.0F});
    expect(translate.elements[12] == 1.0F && translate.elements[13] == 2.0F
               && translate.elements[14] == 3.0F,
           "translation column-major indices");
    const MathResult<Vec3f> translated =
        transform_point(translate, Vec3f{4.0F, 5.0F, 6.0F});
    expect(translated.ok() && vector_near(translated.value, Vec3f{5.0F, 7.0F, 9.0F}, 1.0e-6F),
           "translation point");
    const Vec3f translated_direction =
        transform_direction(translate, Vec3f{4.0F, 5.0F, 6.0F});
    expect(vector_near(translated_direction, Vec3f{4.0F, 5.0F, 6.0F}, 1.0e-6F),
           "direction ignores translation");

    const Mat4f scale_matrix = scaling(Vec3f{2.0F, 3.0F, 4.0F});
    const MathResult<Vec3f> scaled =
        transform_point(scale_matrix, Vec3f{1.0F, 1.0F, 1.0F});
    expect(scaled.ok() && vector_near(scaled.value, Vec3f{2.0F, 3.0F, 4.0F}, 1.0e-6F),
           "scaling point");

    const Mat4f rotated = rotation_z(1.57079632679F);
    const MathResult<Vec3f> rotated_x =
        transform_point(rotated, Vec3f{1.0F, 0.0F, 0.0F});
    expect(rotated_x.ok() && vector_near(rotated_x.value, Vec3f{0.0F, 1.0F, 0.0F}, 1.0e-6F),
           "right-handed z rotation");

    const MathResult<Vec3f> rotated_y =
        transform_point(rotation_x(1.57079632679F), Vec3f{0.0F, 1.0F, 0.0F});
    expect(rotated_y.ok() && vector_near(rotated_y.value, Vec3f{0.0F, 0.0F, 1.0F}, 1.0e-6F),
           "right-handed x rotation");
    const MathResult<Vec3f> rotated_z =
        transform_point(rotation_y(1.57079632679F), Vec3f{0.0F, 0.0F, 1.0F});
    expect(rotated_z.ok() && vector_near(rotated_z.value, Vec3f{1.0F, 0.0F, 0.0F}, 1.0e-6F),
           "right-handed y rotation");

    const Mat3f identity3_value = identity3<float>();
    const Mat3f scale3{};
    expect(identity3_value.elements[0] == 1.0F && identity3_value.elements[4] == 1.0F
               && identity3_value.elements[8] == 1.0F,
           "mat3 identity");
    expect(matrix3_near(multiply(identity3_value, scale3), scale3, 1.0e-6F),
           "mat3 multiply identity");

    const Mat4f combined = multiply(translate, scale_matrix);
    const MathResult<Vec3f> combined_point =
        transform_point(combined, Vec3f{1.0F, 1.0F, 1.0F});
    expect(combined_point.ok()
               && vector_near(combined_point.value, Vec3f{3.0F, 5.0F, 7.0F}, 1.0e-6F),
           "multiply applies right operand first");

    return finish_case();
}

bool run_math04() {
    begin_case();

    const Mat4f translation_matrix = translation(Vec3f{1.0F, 2.0F, 3.0F});
    const MathResult<Mat4f> inverse_translation = inverse(translation_matrix);
    expect(inverse_translation.ok(), "translation inverse success");
    if (inverse_translation.ok()) {
        expect(matrix_near(multiply(translation_matrix, inverse_translation.value),
                           identity4<float>(), 1.0e-5F),
               "translation inverse round-trip");
    }

    const Mat4f rotation_matrix = rotation_z(0.7F);
    const MathResult<Mat4f> inverse_rotation = inverse(rotation_matrix);
    expect(inverse_rotation.ok(), "rotation inverse success");
    if (inverse_rotation.ok()) {
        expect(matrix_near(multiply(rotation_matrix, inverse_rotation.value),
                           identity4<float>(), 1.0e-5F),
               "rotation inverse round-trip");
    }

    const Mat4f scale_matrix = scaling(Vec3f{2.0F, 4.0F, 5.0F});
    const MathResult<Mat4f> inverse_scale = inverse(scale_matrix);
    expect(inverse_scale.ok(), "scale inverse success");
    if (inverse_scale.ok()) {
        expect(matrix_near(multiply(scale_matrix, inverse_scale.value),
                           identity4<float>(), 1.0e-5F),
               "scale inverse round-trip");
    }

    const Mat3f zero3{};
    const MathResult<Mat3f> zero_inverse = inverse(zero3);
    expect(!zero_inverse.ok() && zero_inverse.error == MathError::SingularMatrix,
           "zero mat3 singular");

    Mat3f near_singular{};
    near_singular.elements[0] = 1.0F;
    near_singular.elements[4] = 1.0F;
    near_singular.elements[8] = 1.0e-8F;
    const MathResult<Mat3f> near_inverse = inverse(near_singular);
    expect(!near_inverse.ok() && near_inverse.error == MathError::SingularMatrix,
           "near-singular mat3 rejected");

    Mat4f duplicate_column = identity4<float>();
    duplicate_column.elements[0] = duplicate_column.elements[4];
    const MathResult<Mat4f> duplicate_inverse = inverse(duplicate_column);
    expect(!duplicate_inverse.ok() && duplicate_inverse.error == MathError::SingularMatrix,
           "duplicate column mat4 singular");

    Mat4f nonfinite = identity4<float>();
    nonfinite.elements[0] = std::numeric_limits<float>::quiet_NaN();
    const MathResult<Mat4f> nonfinite_inverse = inverse(nonfinite);
    expect(!nonfinite_inverse.ok() && nonfinite_inverse.error == MathError::NonFinite,
           "nonfinite mat4 rejected");

    Mat4f no_w = identity4<float>();
    no_w.elements[15] = 0.0F;
    const MathResult<Vec3f> divided = transform_point(no_w, Vec3f{1.0F, 2.0F, 3.0F});
    expect(!divided.ok() && divided.error == MathError::SingularMatrix,
           "zero homogeneous w rejected");

    const MathResult<float> determinant3 = determinant(near_singular);
    expect(determinant3.ok() && determinant3.value == 1.0e-8F, "mat3 determinant");

    return finish_case();
}

bool run_math05() {
    begin_case();

    const Quatf identity = identity_quat<float>();
    const MathResult<Vec3f> identity_rotated = rotate(identity, Vec3f{1.0F, 2.0F, 3.0F});
    expect(identity_rotated.ok()
               && vector_near(identity_rotated.value, Vec3f{1.0F, 2.0F, 3.0F}, 1.0e-6F),
           "identity quaternion rotation");

    const float half_pi = 1.57079632679F;
    const MathResult<Quatf> axis_angle =
        from_axis_angle(Vec3f{0.0F, 0.0F, 1.0F}, half_pi);
    expect(axis_angle.ok(), "axis-angle success");
    if (axis_angle.ok()) {
        const MathResult<Vec3f> rotated_x =
            rotate(axis_angle.value, Vec3f{1.0F, 0.0F, 0.0F});
        expect(rotated_x.ok() && vector_near(rotated_x.value, Vec3f{0.0F, 1.0F, 0.0F}, 1.0e-6F),
               "axis-angle rotates x to y");
        expect(quat_near(canonicalized(axis_angle.value),
                         canonicalized(Quatf{-axis_angle.value.x, -axis_angle.value.y,
                                             -axis_angle.value.z, -axis_angle.value.w}),
                         0.0F),
               "q and -q canonicalize identically");
        const MathResult<Vec3f> negative_rotated =
            rotate(Quatf{-axis_angle.value.x, -axis_angle.value.y,
                         -axis_angle.value.z, -axis_angle.value.w},
                   Vec3f{1.0F, 0.0F, 0.0F});
        expect(negative_rotated.ok()
                   && vector_near(negative_rotated.value, Vec3f{0.0F, 1.0F, 0.0F}, 1.0e-6F),
               "q and -q rotate identically");

        const Quatf conjugate_value = conjugate(axis_angle.value);
        const MathResult<Vec3f> inverse_rotated =
            rotate(conjugate_value, Vec3f{0.0F, 1.0F, 0.0F});
        expect(inverse_rotated.ok()
                   && vector_near(inverse_rotated.value, Vec3f{1.0F, 0.0F, 0.0F}, 1.0e-6F),
               "conjugate inverse rotation");
        const Quatf product = multiply(axis_angle.value, conjugate_value);
        expect(quat_near(product, identity, 1.0e-5F), "q times conjugate identity");
    }

    const MathResult<Quatf> zero_axis = from_axis_angle(Vec3f{0.0F, 0.0F, 0.0F}, 1.0F);
    expect(!zero_axis.ok() && zero_axis.error == MathError::ZeroLength,
           "zero axis rejected");

    const MathResult<Quatf> zero_quat = normalized(Quatf{0.0F, 0.0F, 0.0F, 0.0F});
    expect(!zero_quat.ok() && zero_quat.error == MathError::ZeroLength,
           "zero quaternion rejected");

    const MathResult<Vec3f> unnormalized_rotation =
        rotate(Quatf{0.0F, 0.0F, 0.0F, 2.0F}, Vec3f{1.0F, 0.0F, 0.0F});
    expect(!unnormalized_rotation.ok()
               && unnormalized_rotation.error == MathError::InvalidQuaternion,
           "unnormalized quaternion rejected");

    const Quatf negative_w{0.0F, 0.0F, 0.0F, -1.0F};
    const Quatf canonical = canonicalized(negative_w);
    expect(canonical.w == 1.0F && canonical.x == 0.0F, "negative w canonicalized");

    const Quatf negative_x{-1.0F, 0.0F, 0.0F, 0.0F};
    const Quatf canonical_x = canonicalized(negative_x);
    expect(canonical_x.x == 1.0F && canonical_x.w == 0.0F, "negative x canonicalized");

    expect(dot(identity, identity) == 1.0F, "quaternion dot identity");
    const MathResult<Quatf> unit = normalized(axis_angle.value);
    expect(unit.ok(), "already-normalized quaternion");

    return finish_case();
}

}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_core05_matrix_quat_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "math03") {
        success = run_math03();
    } else if (mode == "math04") {
        success = run_math04();
    } else if (mode == "math05") {
        success = run_math05();
    } else {
        std::fprintf(stderr, "unknown mode: %s\n", argv[1]);
        return 2;
    }
    return success ? 0 : 1;
}
