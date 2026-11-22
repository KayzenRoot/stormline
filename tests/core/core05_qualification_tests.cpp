#include "stormline/core/math/coords.hpp"
#include "stormline/core/math/ids.hpp"
#include "stormline/core/math/mat.hpp"
#include "stormline/core/math/precision.hpp"
#include "stormline/core/math/quat.hpp"
#include "stormline/core/math/units.hpp"
#include "stormline/core/math/vec.hpp"

#include <cmath>
#include <cstdio>
#include <limits>
#include <string_view>

namespace {

using namespace stormline::core::math;

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

bool vector_near(const Vec3f& lhs, const Vec3f& rhs, float tolerance) {
    return approx_equal(lhs, rhs, tolerance, 0.0F);
}

struct Fixture {
    Vec3f vector{3.0F, 4.0F, 0.0F};
    float angle{1.57079632679F};
    Quatf rotation{};
    Mat4f transform{};
};

bool build_fixture(Fixture& fixture) {
    const MathResult<Vec3f> unit = normalized(fixture.vector);
    if (!unit.ok()) {
        return false;
    }
    const MathResult<Quatf> rotation =
        from_axis_angle(Vec3f{0.0F, 0.0F, 1.0F}, fixture.angle);
    if (!rotation.ok()) {
        return false;
    }
    fixture.rotation = rotation.value;
    fixture.transform = multiply(translation(Vec3f{2.0F, 0.0F, 0.0F}),
                                 rotation_z(fixture.angle));
    return true;
}

bool run_qlf01() {
    begin_case();

    Fixture fixture{};
    expect(build_fixture(fixture), "fixture build");

    const MathResult<Vec3f> unit = normalized(fixture.vector);
    expect(unit.ok() && approx_equal(unit.value.x, 0.6F, 1.0e-6F, 0.0F)
               && approx_equal(unit.value.y, 0.8F, 1.0e-6F, 0.0F),
           "qlf01 vector normalize");

    const MathResult<Vec3f> rotated = rotate(fixture.rotation, Vec3f{1.0F, 0.0F, 0.0F});
    expect(rotated.ok() && vector_near(rotated.value, Vec3f{0.0F, 1.0F, 0.0F}, 1.0e-6F),
           "qlf01 quaternion rotation");

    const MathResult<Vec3f> transformed =
        transform_point(fixture.transform, Vec3f{1.0F, 0.0F, 0.0F});
    expect(transformed.ok() && vector_near(transformed.value, Vec3f{2.0F, 1.0F, 0.0F}, 1.0e-6F),
           "qlf01 matrix transform");

    const Transform3<float, LocalSpace, WorldSpace> local_to_world{fixture.transform};
    const MathResult<Position3<float, WorldSpace>> world_position =
        transform_position(local_to_world, Position3<float, LocalSpace>{Vec3f{1.0F, 0.0F, 0.0F}});
    expect(world_position.ok()
               && vector_near(world_position.value.value, Vec3f{2.0F, 1.0F, 0.0F}, 1.0e-6F),
           "qlf01 coordinate transform");

    const auto meters = to_meters(Quantity<float, Centimeters>{100.0F});
    expect(meters.ok() && approx_equal(meters.value.value, 1.0F, 1.0e-6F, 0.0F),
           "qlf01 units");
    const auto milliseconds = to_milliseconds(Quantity<float, Seconds>{1.0F});
    expect(milliseconds.ok() && milliseconds.value.value == 1000.0F, "qlf01 time units");

    const OriginEpoch epoch{1};
    const Origin origin{Vec3d{0.0, 0.0, 0.0}, epoch};
    const WorldPosition world{Vec3d{1'000'000.0, 0.0, 0.0}, epoch};
    const auto local = to_local(world, origin);
    expect(local.ok() && std::fabs(static_cast<double>(local.value.meters.x) - 1.0e6)
               <= local_error_bound(1.0e6),
           "qlf01 precision");
    const auto rebased = rebase(world, epoch, OriginEpoch{2});
    expect(rebased.ok() && rebased.value.global_meters.x == world.global_meters.x,
           "qlf01 rebase");

    const PersistentId id{0x0102030405060708ULL, 0x1112131415161718ULL};
    const auto decoded = decode_persistent_id(encode_persistent_id(id));
    expect(decoded.ok() && decoded.value == id
               && handle_is_current(RuntimeHandle{4, 9}, 9),
           "qlf01 IDs");

    return finish_case();
}

bool run_qlf02() {
    begin_case();

    bool stable = true;
    Vec3f previous{};
    for (int iteration = 0; iteration < 1000; ++iteration) {
        const MathResult<Vec3f> unit = normalized(Vec3f{3.0F, 4.0F, 0.0F});
        const MathResult<Quatf> rotation =
            from_axis_angle(Vec3f{0.0F, 0.0F, 1.0F}, 0.7F);
        const MathResult<Vec3f> rotated =
            rotation.ok() ? rotate(rotation.value, Vec3f{1.0F, 2.0F, 3.0F})
                          : MathResult<Vec3f>{};
        if (!unit.ok() || !rotated.ok()) {
            stable = false;
            break;
        }
        if (iteration == 0) {
            previous = rotated.value;
        } else if (!(rotated.value.x == previous.x
                     && rotated.value.y == previous.y
                     && rotated.value.z == previous.z)) {
            stable = false;
            break;
        }
    }
    expect(stable, "qlf02 repeated scalar fixture identical");

    return finish_case();
}

bool run_qlf03() {
    begin_case();

    const MathResult<Vec3f> zero = normalized(Vec3f{0.0F, 0.0F, 0.0F});
    expect(!zero.ok() && zero.error == MathError::ZeroLength, "qlf03 zero error");
    const MathResult<Vec3f> recovered = normalized(Vec3f{0.0F, 0.0F, 2.0F});
    expect(recovered.ok() && recovered.value.z == 1.0F, "qlf03 vector recovery");

    const MathResult<Mat4f> singular = inverse(Mat4f{});
    expect(!singular.ok() && singular.error == MathError::SingularMatrix,
           "qlf03 singular error");
    const MathResult<Mat4f> nonsingular = inverse(translation(Vec3f{1.0F, 2.0F, 3.0F}));
    expect(nonsingular.ok(), "qlf03 matrix recovery");

    const OriginEpoch epoch{3};
    const Origin origin{Vec3d{0.0, 0.0, 0.0}, epoch};
    const WorldPosition world{Vec3d{1.0, 2.0, 3.0}, epoch};
    const auto mismatch = to_local(world, Origin{Vec3d{0.0, 0.0, 0.0}, OriginEpoch{4}});
    expect(!mismatch.ok() && mismatch.error == MathError::InvalidOriginEpoch,
           "qlf03 epoch error");
    const auto recovered_world = to_local(world, origin);
    expect(recovered_world.ok(), "qlf03 precision recovery");

    const auto invalid_id = decode_persistent_id(IdBytes{});
    expect(!invalid_id.ok() && invalid_id.error == MathError::InvalidId,
           "qlf03 invalid ID error");
    const PersistentId id{1, 2};
    expect(decode_persistent_id(encode_persistent_id(id)).ok(), "qlf03 ID recovery");

    const MathResult<Vec3f> unnormalized =
        rotate(Quatf{0.0F, 0.0F, 0.0F, 2.0F}, Vec3f{1.0F, 0.0F, 0.0F});
    expect(!unnormalized.ok() && unnormalized.error == MathError::InvalidQuaternion,
           "qlf03 quaternion error");
    const auto valid_rotation =
        from_axis_angle(Vec3f{0.0F, 1.0F, 0.0F}, 0.5F);
    expect(valid_rotation.ok(), "qlf03 quaternion recovery");

    return finish_case();
}

bool run_qlf04() {
    begin_case();

    const OriginEpoch epoch{10};
    const double origin_metres = 1'000'000'000.0;
    const double delta = 123.5;
    const Origin origin{Vec3d{origin_metres, 0.0, 0.0}, epoch};
    const WorldPosition world{Vec3d{origin_metres + delta, 0.0, 0.0}, epoch};
    const auto local = to_local(world, origin);
    expect(local.ok(), "qlf04 local conversion");
    if (local.ok()) {
        const double error =
            std::fabs(static_cast<double>(local.value.meters.x) - delta);
        expect(error <= local_error_bound(delta), "qlf04 error budget");
        const auto round_trip = to_world(local.value, origin);
        expect(round_trip.ok()
                   && std::fabs(round_trip.value.global_meters.x - world.global_meters.x)
                       <= local_error_bound(delta),
               "qlf04 round-trip");
    }

    const auto rebased = rebase(world, epoch, OriginEpoch{11});
    expect(rebased.ok() && rebased.value.epoch.value == 11
               && rebased.value.global_meters.x == world.global_meters.x,
           "qlf04 rebase preserves global");
    const auto stale = rebase(rebased.ok() ? rebased.value : world, epoch, OriginEpoch{11});
    expect(!stale.ok() && stale.error == MathError::InvalidOriginEpoch,
           "qlf04 stale rebase rejected");

    const Transform3<double, LocalSpace, WorldSpace> large_transform{
        translation(Vec3d{origin_metres, 0.0, 0.0})};
    const auto transformed = transform_position(
        large_transform, Position3<double, LocalSpace>{Vec3d{delta, 0.0, 0.0}});
    expect(transformed.ok()
               && transformed.value.value.x == origin_metres + delta,
           "qlf04 large coordinate transform");

    return finish_case();
}

}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_core05_qualification_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "qlf01") {
        success = run_qlf01();
    } else if (mode == "qlf02") {
        success = run_qlf02();
    } else if (mode == "qlf03") {
        success = run_qlf03();
    } else if (mode == "qlf04") {
        success = run_qlf04();
    } else {
        std::fprintf(stderr, "unknown mode: %s\n", argv[1]);
        return 2;
    }
    return success ? 0 : 1;
}
