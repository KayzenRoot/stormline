#include "stormline/core/math/units.hpp"

#include <cmath>
#include <cstdio>
#include <limits>
#include <string_view>
#include <type_traits>

namespace {

using stormline::core::math::add;
using stormline::core::math::approx_equal;
using stormline::core::math::Centimeters;
using stormline::core::math::Degrees;
using stormline::core::math::MathError;
using stormline::core::math::Meters;
using stormline::core::math::Millimeters;
using stormline::core::math::Milliseconds;
using stormline::core::math::Quantity;
using stormline::core::math::Radians;
using stormline::core::math::scale;
using stormline::core::math::Seconds;
using stormline::core::math::subtract;
using stormline::core::math::to_centimeters;
using stormline::core::math::to_degrees;
using stormline::core::math::to_meters;
using stormline::core::math::to_milliseconds;
using stormline::core::math::to_radians;
using stormline::core::math::to_seconds;

static_assert(!std::is_convertible_v<Quantity<float, Meters>,
                                    Quantity<float, Centimeters>>,
              "length units must not convert implicitly");
static_assert(!std::is_assignable_v<Quantity<float, Seconds>&,
                                    Quantity<float, Milliseconds>>,
              "time units must not assign implicitly");
static_assert(!std::is_same_v<Quantity<float, Radians>,
                              Quantity<float, Degrees>>,
              "angle units must remain distinct");

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

bool run_math07() {
    begin_case();

    const auto radians = to_radians(Quantity<float, Degrees>{180.0F});
    expect(radians.ok() && approx_equal(radians.value.value, 3.14159265F, 1.0e-6F, 0.0F),
           "180 degrees to pi radians");
    const auto half_radians = to_radians(Quantity<float, Degrees>{90.0F});
    expect(half_radians.ok()
               && approx_equal(half_radians.value.value, 1.57079632F, 1.0e-6F, 0.0F),
           "90 degrees to half pi");
    const auto degrees = to_degrees(Quantity<float, Radians>{3.14159265F});
    expect(degrees.ok() && approx_equal(degrees.value.value, 180.0F, 1.0e-5F, 0.0F),
           "pi radians to degrees");

    const auto meters = to_meters(Quantity<float, Centimeters>{100.0F});
    expect(meters.ok() && approx_equal(meters.value.value, 1.0F, 1.0e-6F, 0.0F),
           "100 cm to 1 m");
    const auto centimeters = to_centimeters(Quantity<float, Meters>{1.0F});
    expect(centimeters.ok()
               && approx_equal(centimeters.value.value, 100.0F, 1.0e-6F, 0.0F),
           "1 m to 100 cm");
    const auto millimeters = to_meters(Quantity<float, Millimeters>{1000.0F});
    expect(millimeters.ok()
               && approx_equal(millimeters.value.value, 1.0F, 1.0e-6F, 0.0F),
           "1000 mm to 1 m");

    const auto milliseconds = to_milliseconds(Quantity<float, Seconds>{1.0F});
    expect(milliseconds.ok() && milliseconds.value.value == 1000.0F, "1 s to 1000 ms");
    const auto seconds = to_seconds(Quantity<float, Milliseconds>{250.0F});
    expect(seconds.ok() && approx_equal(seconds.value.value, 0.25F, 1.0e-6F, 0.0F),
           "250 ms to 0.25 s");

    const auto sum = add(Quantity<float, Meters>{1.0F}, Quantity<float, Meters>{2.5F});
    expect(sum.value == 3.5F, "same-unit add");
    const auto difference =
        subtract(Quantity<float, Meters>{4.0F}, Quantity<float, Meters>{1.5F});
    expect(difference.value == 2.5F, "same-unit subtract");
    const auto scaled = scale(Quantity<float, Seconds>{2.0F}, 3.0F);
    expect(scaled.value == 6.0F, "same-unit scale");

    const float nan = std::numeric_limits<float>::quiet_NaN();
    const auto nonfinite = to_radians(Quantity<float, Degrees>{nan});
    expect(!nonfinite.ok() && nonfinite.error == MathError::NonFinite,
           "nan conversion rejected");
    const auto infinity = to_milliseconds(
        Quantity<float, Seconds>{std::numeric_limits<float>::infinity()});
    expect(!infinity.ok() && infinity.error == MathError::NonFinite,
           "infinity conversion rejected");
    const auto overflow = to_milliseconds(
        Quantity<float, Seconds>{std::numeric_limits<float>::max()});
    expect(!overflow.ok() && overflow.error == MathError::Overflow,
           "conversion overflow rejected");

    return finish_case();
}

}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_core05_unit_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "math07") {
        success = run_math07();
    } else {
        std::fprintf(stderr, "unknown mode: %s\n", argv[1]);
        return 2;
    }
    return success ? 0 : 1;
}
