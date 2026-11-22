#include "stormline/data/import/animation_metadata.hpp"

#include <cstdio>
#include <string_view>

namespace {
using namespace stormline::data::imports;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

bool run_anim01() {
    begin();
    AnimationMetadata animation{1, 1, 1, 1};
    u32 warnings = 99;
    expect(validate_animation(animation, warnings) == ImportError::None, "minimal");
    expect(warnings == 0, "minimal warnings");
    animation = AnimationMetadata{kMaxAnimationJoints, kMaxAnimationTracks,
                                  kMaxAnimationKeyframes, kMaxAnimationDurationMs};
    expect(validate_animation(animation, warnings) == ImportError::None, "maximal");
    expect(warnings == 0, "maximal warnings");
    animation = AnimationMetadata{0, 1, 1, 1};
    expect(validate_animation(animation, warnings) == ImportError::InvalidAnimation, "joints");
    animation = AnimationMetadata{kMaxAnimationJoints + 1, 1, 1, 1};
    expect(validate_animation(animation, warnings) == ImportError::InvalidAnimation, "joints max");
    animation = AnimationMetadata{1, 0, 1, 1};
    expect(validate_animation(animation, warnings) == ImportError::InvalidAnimation, "tracks");
    animation = AnimationMetadata{1, kMaxAnimationTracks + 1, 1, 1};
    expect(validate_animation(animation, warnings) == ImportError::InvalidAnimation, "tracks max");
    animation = AnimationMetadata{1, 1, 0, 1};
    expect(validate_animation(animation, warnings) == ImportError::InvalidAnimation, "keys");
    animation = AnimationMetadata{1, 1, kMaxAnimationKeyframes + 1, 1};
    expect(validate_animation(animation, warnings) == ImportError::InvalidAnimation, "keys max");
    animation = AnimationMetadata{1, 1, 1, 0};
    expect(validate_animation(animation, warnings) == ImportError::InvalidAnimation, "duration");
    animation = AnimationMetadata{1, 1, 1, kMaxAnimationDurationMs + 1};
    expect(validate_animation(animation, warnings) == ImportError::InvalidAnimation,
           "duration max");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_data03_animation_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "anim01") { success = run_anim01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
