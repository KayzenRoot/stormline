#include "stormline/core/math/coords.hpp"

#include <cstdio>
#include <string_view>
#include <type_traits>

namespace {

using stormline::core::math::compose;
using stormline::core::math::Direction3;
using stormline::core::math::identity_transform;
using stormline::core::math::inverse;
using stormline::core::math::LocalSpace;
using stormline::core::math::MathError;
using stormline::core::math::MathResult;
using stormline::core::math::Position3;
using stormline::core::math::scaling;
using stormline::core::math::Transform3;
using stormline::core::math::transform_direction;
using stormline::core::math::transform_position;
using stormline::core::math::translation;
using stormline::core::math::Vec3f;
using stormline::core::math::ViewSpace;
using stormline::core::math::WorldSpace;

static_assert(!std::is_convertible_v<Position3<float, LocalSpace>,
                                    Position3<float, WorldSpace>>,
              "position spaces must not convert implicitly");
static_assert(!std::is_assignable_v<Position3<float, WorldSpace>&,
                                    Position3<float, LocalSpace>>,
              "position spaces must not assign implicitly");
static_assert(!std::is_same_v<Transform3<float, LocalSpace, WorldSpace>,
                              Transform3<float, WorldSpace, LocalSpace>>,
              "transform directions must remain distinct");
static_assert(!std::is_convertible_v<Direction3<float, WorldSpace>,
                                     Direction3<float, LocalSpace>>,
              "direction spaces must not convert implicitly");

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
    return stormline::core::math::approx_equal(lhs, rhs, tolerance, 0.0F);
}

bool run_math06() {
    begin_case();

    const Transform3<float, LocalSpace, LocalSpace> identity =
        identity_transform<float, LocalSpace>();
    const MathResult<Position3<float, LocalSpace>> identity_position =
        transform_position(identity, Position3<float, LocalSpace>{Vec3f{1.0F, 2.0F, 3.0F}});
    expect(identity_position.ok()
               && vector_near(identity_position.value.value, Vec3f{1.0F, 2.0F, 3.0F}, 1.0e-6F),
           "identity transform preserves position");

    const Transform3<float, LocalSpace, WorldSpace> child{
        translation(Vec3f{1.0F, 0.0F, 0.0F})};
    const Transform3<float, WorldSpace, ViewSpace> parent{
        scaling(Vec3f{2.0F, 2.0F, 2.0F})};
    const Transform3<float, LocalSpace, ViewSpace> composed = compose(parent, child);
    const MathResult<Position3<float, ViewSpace>> composed_position =
        transform_position(composed, Position3<float, LocalSpace>{Vec3f{0.0F, 0.0F, 0.0F}});
    expect(composed_position.ok()
               && vector_near(composed_position.value.value, Vec3f{2.0F, 0.0F, 0.0F}, 1.0e-6F),
           "compose parent times child");

    const Direction3<float, LocalSpace> local_direction{Vec3f{1.0F, 0.0F, 0.0F}};
    const Direction3<float, WorldSpace> world_direction =
        transform_direction(child, local_direction);
    expect(vector_near(world_direction.value, Vec3f{1.0F, 0.0F, 0.0F}, 1.0e-6F),
           "direction ignores translation");

    const MathResult<Transform3<float, WorldSpace, LocalSpace>> inverse_child =
        inverse(child);
    expect(inverse_child.ok(), "transform inverse success");
    if (inverse_child.ok()) {
        const MathResult<Position3<float, LocalSpace>> round_trip =
            transform_position(inverse_child.value,
                               Position3<float, WorldSpace>{Vec3f{3.0F, 4.0F, 5.0F}});
        expect(round_trip.ok()
                   && vector_near(round_trip.value.value, Vec3f{2.0F, 4.0F, 5.0F}, 1.0e-5F),
               "transform inverse round-trip");
    }

    Transform3<float, LocalSpace, WorldSpace> singular{};
    const MathResult<Position3<float, WorldSpace>> singular_position =
        transform_position(singular, Position3<float, LocalSpace>{Vec3f{1.0F, 0.0F, 0.0F}});
    expect(!singular_position.ok() && singular_position.error == MathError::SingularMatrix,
           "zero transform rejected");

    return finish_case();
}

}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_core05_coord_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "math06") {
        success = run_math06();
    } else {
        std::fprintf(stderr, "unknown mode: %s\n", argv[1]);
        return 2;
    }
    return success ? 0 : 1;
}
