#include "stormline/animation/timeline_plan.hpp"

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

TimelineDesc timeline(u32 id, u64 duration, u64 loop_start, u64 loop_end) {
    TimelineDesc desc{};
    desc.timeline_id = id;
    desc.revision = 1;
    desc.fps_numerator = 30;
    desc.fps_denominator = 1;
    desc.duration_frames = duration;
    desc.sample_rate = 48000;
    desc.loop_start_frame = loop_start;
    desc.loop_end_frame = loop_end;
    return desc;
}

bool run_tml01() {
    begin();
    TimelineDesc desc = timeline(31, 120, 0, 120);
    TimelinePlan plan{};
    AnimationDiagnostic diagnostic{};

    expect(plan_timeline(desc, plan, diagnostic) == AnimationError::None,
           "valid timeline");
    expect(plan.frame_count == 120 && plan.sample_count == 192000
               && plan.loop_length_frames == 120,
           "valid plan");
    TimelinePlan repeat{};
    expect(plan_timeline(desc, repeat, diagnostic) == AnimationError::None,
           "repeat timeline");
    expect(plan.frame_count == repeat.frame_count
               && plan.sample_count == repeat.sample_count
               && plan.loop_length_frames == repeat.loop_length_frames,
           "deterministic plan");

    desc = timeline(31, 100, 10, 90);
    desc.fps_numerator = 30000;
    desc.fps_denominator = 1001;
    expect(plan_timeline(desc, plan, diagnostic) == AnimationError::None,
           "rational timeline");
    expect(plan.sample_count == 160160 && plan.loop_length_frames == 80,
           "rational plan");

    desc = timeline(31, 1, 0, 1);
    desc.fps_numerator = 7;
    expect(plan_timeline(desc, plan, diagnostic) == AnimationError::None,
           "floor mapping");
    expect(plan.sample_count == 6857, "floor sample count");

    desc = timeline(0, 120, 0, 120);
    expect(plan_timeline(desc, plan, diagnostic)
               == AnimationError::InvalidArgument,
           "zero timeline");
    expect(plan.frame_count == 0 && plan.sample_count == 0
               && plan.loop_length_frames == 0,
           "reset on zero timeline");
    desc = timeline(31, 120, 0, 120);
    desc.revision = 0;
    expect(plan_timeline(desc, plan, diagnostic)
               == AnimationError::InvalidArgument,
           "zero revision");
    desc.revision = 1;
    desc.fps_numerator = 0;
    expect(plan_timeline(desc, plan, diagnostic)
               == AnimationError::InvalidArgument,
           "zero fps numerator");
    desc = timeline(31, 120, 0, 120);
    desc.fps_denominator = 0;
    expect(plan_timeline(desc, plan, diagnostic)
               == AnimationError::InvalidArgument,
           "zero fps denominator");
    desc = timeline(31, 120, 0, 120);
    desc.duration_frames = 0;
    expect(plan_timeline(desc, plan, diagnostic)
               == AnimationError::InvalidArgument,
           "zero duration");
    desc = timeline(31, 120, 0, 120);
    desc.sample_rate = 0;
    expect(plan_timeline(desc, plan, diagnostic)
               == AnimationError::InvalidArgument,
           "zero sample rate");

    desc = timeline(31, 120, 0, 0);
    expect(plan_timeline(desc, plan, diagnostic)
               == AnimationError::TimeInvalid,
           "empty loop");
    expect(diagnostic.source_id == 31, "loop diagnostic source");
    desc = timeline(31, 120, 10, 10);
    expect(plan_timeline(desc, plan, diagnostic)
               == AnimationError::TimeInvalid,
           "zero loop length");
    desc = timeline(31, 120, 20, 10);
    expect(plan_timeline(desc, plan, diagnostic)
               == AnimationError::TimeInvalid,
           "reverse loop");
    desc = timeline(31, 120, 0, 121);
    expect(plan_timeline(desc, plan, diagnostic)
               == AnimationError::TimeInvalid,
           "loop beyond duration");

    desc = timeline(31, 120, 0, 120);
    desc.fps_denominator = std::numeric_limits<u32>::max();
    expect(plan_timeline(desc, plan, diagnostic) == AnimationError::None,
           "large denominator");
    expect(plan.sample_count > 0, "large denominator samples");

    desc = timeline(31, std::numeric_limits<u64>::max(), 0,
                    std::numeric_limits<u64>::max());
    desc.fps_denominator = 2;
    expect(plan_timeline(desc, plan, diagnostic)
               == AnimationError::OutOfRange,
           "sample overflow");
    expect(plan.frame_count == 0 && plan.sample_count == 0
               && plan.loop_length_frames == 0,
           "reset on overflow");

    const u64 half = std::numeric_limits<u64>::max() / 2;
    desc = timeline(31, half, 0, half);
    desc.sample_rate = 1;
    desc.fps_numerator = 1;
    desc.fps_denominator = 1;
    expect(plan_timeline(desc, plan, diagnostic) == AnimationError::None,
           "large frame count");
    expect(plan.frame_count == half && plan.sample_count == half
               && plan.loop_length_frames == half,
           "large frame plan");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_two03_timeline_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "tml01") { success = run_tml01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
