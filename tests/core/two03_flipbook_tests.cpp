#include "stormline/animation/flipbook_plan.hpp"

#include <cstdio>
#include <limits>
#include <string_view>

namespace {
using namespace stormline::animation;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

bool run_flb01() {
    begin();
    FlipbookDesc flipbook{};
    flipbook.clip_id = 7;
    flipbook.revision = 2;
    flipbook.timebase_denominator = 60;
    flipbook.frame_count = 3;
    flipbook.frames[0] = FlipbookFrame{1, 100, 10, 2};
    flipbook.frames[1] = FlipbookFrame{2, 101, 11, 1};
    flipbook.frames[2] = FlipbookFrame{3, 102, 12, 4};
    FlipbookPlan plan{};
    AnimationDiagnostic diagnostic{};

    expect(plan_flipbook(flipbook, plan, diagnostic) == AnimationError::None,
           "valid flipbook");
    expect(plan.frame_count == 3 && plan.total_frames == 7,
           "valid plan totals");
    expect(diagnostic.code == AnimationError::None, "clean diagnostic");

    flipbook.frame_count = 0;
    expect(plan_flipbook(flipbook, plan, diagnostic)
               == AnimationError::FlipbookInvalid,
           "empty flipbook");
    expect(plan.frame_count == 0 && plan.total_frames == 0, "reset on empty");

    flipbook.frame_count = kMaxFlipbookFrames + 1;
    expect(plan_flipbook(flipbook, plan, diagnostic)
               == AnimationError::FlipbookInvalid,
           "over capacity");

    flipbook.frame_count = 2;
    flipbook.clip_id = 0;
    expect(plan_flipbook(flipbook, plan, diagnostic)
               == AnimationError::InvalidArgument,
           "zero clip");
    flipbook.clip_id = 7;
    flipbook.revision = 0;
    expect(plan_flipbook(flipbook, plan, diagnostic)
               == AnimationError::InvalidArgument,
           "zero revision");
    flipbook.revision = 1;
    flipbook.timebase_denominator = 0;
    expect(plan_flipbook(flipbook, plan, diagnostic)
               == AnimationError::InvalidArgument,
           "zero timebase");
    flipbook.timebase_denominator = 60;

    flipbook.frames[0] = FlipbookFrame{0, 100, 10, 1};
    expect(plan_flipbook(flipbook, plan, diagnostic)
               == AnimationError::FlipbookInvalid,
           "zero frame id");
    expect(diagnostic.index == 0 && diagnostic.source_id == 7,
           "frame diagnostic");

    flipbook.frames[0] = FlipbookFrame{1, 0, 10, 1};
    expect(plan_flipbook(flipbook, plan, diagnostic)
               == AnimationError::FlipbookInvalid,
           "zero sprite");
    flipbook.frames[0] = FlipbookFrame{1, 100, 0, 1};
    expect(plan_flipbook(flipbook, plan, diagnostic)
               == AnimationError::FlipbookInvalid,
           "zero atlas region");
    flipbook.frames[0] = FlipbookFrame{1, 100, 10, 0};
    expect(plan_flipbook(flipbook, plan, diagnostic)
               == AnimationError::FlipbookInvalid,
           "zero hold");

    flipbook.frames[0] = FlipbookFrame{1, 100, 10, 1};
    flipbook.frames[1] = FlipbookFrame{1, 101, 11, 1};
    expect(plan_flipbook(flipbook, plan, diagnostic)
               == AnimationError::DuplicateId,
           "duplicate frame id");
    expect(diagnostic.index == 1, "duplicate index");

    flipbook.frames[1] = FlipbookFrame{2, 101, 11, 1};
    expect(plan_flipbook(flipbook, plan, diagnostic) == AnimationError::None,
           "recovered flipbook");
    expect(plan.total_frames == 2, "recovered totals");

    flipbook.frame_count = kMaxFlipbookFrames;
    for (u32 index = 0; index < kMaxFlipbookFrames; ++index) {
        flipbook.frames[index] = FlipbookFrame{index + 1, 100, 10, 1};
    }
    expect(plan_flipbook(flipbook, plan, diagnostic) == AnimationError::None,
           "capacity flipbook");
    expect(plan.frame_count == kMaxFlipbookFrames
               && plan.total_frames == kMaxFlipbookFrames,
           "capacity totals");

    flipbook.frames[0].hold_frames
        = static_cast<u32>(std::numeric_limits<u32>::max());
    flipbook.frame_count = 1;
    expect(plan_flipbook(flipbook, plan, diagnostic) == AnimationError::None,
           "large hold");
    expect(plan.total_frames == std::numeric_limits<u32>::max(),
           "large hold total");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_two03_flipbook_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "flb01") { success = run_flb01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
