#include "stormline/animation/sequence_plan.hpp"

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

SequenceCue cue(u32 id, TrackKind kind, u64 tick, u64 duration) {
    SequenceCue desc{};
    desc.cue_id = id;
    desc.revision = 1;
    desc.kind = kind;
    desc.tick = tick;
    desc.duration_ticks = duration;
    return desc;
}

SequenceTrack track(u32 id, TrackKind kind) {
    SequenceTrack desc{};
    desc.track_id = id;
    desc.revision = 1;
    desc.kind = kind;
    return desc;
}

bool run_seq01() {
    begin();
    SequenceDesc sequence{};
    sequence.sequence_id = 21;
    sequence.revision = 2;
    sequence.timebase_denominator = 60;
    sequence.duration_ticks = 100;
    sequence.track_count = 2;
    sequence.nesting_depth = 1;
    sequence.tracks[0] = track(1, TrackKind::Sprite);
    sequence.tracks[0].cue_count = 1;
    sequence.tracks[0].cues[0] = cue(1, TrackKind::Sprite, 0, 10);
    sequence.tracks[1] = track(2, TrackKind::Camera);
    sequence.tracks[1].cue_count = 1;
    sequence.tracks[1].cues[0] = cue(2, TrackKind::Camera, 20, 5);
    SequencePlan plan{};
    AnimationDiagnostic diagnostic{};

    expect(plan_sequence(sequence, plan, diagnostic) == AnimationError::None,
           "valid sequence");
    expect(plan.track_count == 2 && plan.cue_count == 2
               && plan.max_depth == 1,
           "valid plan");
    SequencePlan repeat{};
    expect(plan_sequence(sequence, repeat, diagnostic) == AnimationError::None,
           "repeat sequence");
    expect(plan.track_count == repeat.track_count
               && plan.cue_count == repeat.cue_count
               && plan.max_depth == repeat.max_depth,
           "deterministic plan");

    sequence.track_count = 0;
    expect(plan_sequence(sequence, plan, diagnostic)
               == AnimationError::SequenceInvalid,
           "empty sequence");
    expect(plan.track_count == 0 && plan.cue_count == 0
               && plan.max_depth == 0,
           "reset on empty");

    sequence.track_count = kMaxSequenceTracks + 1;
    expect(plan_sequence(sequence, plan, diagnostic)
               == AnimationError::SequenceInvalid,
           "track overflow");

    sequence.track_count = 2;
    sequence.sequence_id = 0;
    expect(plan_sequence(sequence, plan, diagnostic)
               == AnimationError::InvalidArgument,
           "zero sequence");
    sequence.sequence_id = 21;
    sequence.revision = 0;
    expect(plan_sequence(sequence, plan, diagnostic)
               == AnimationError::InvalidArgument,
           "zero revision");
    sequence.revision = 2;
    sequence.timebase_denominator = 0;
    expect(plan_sequence(sequence, plan, diagnostic)
               == AnimationError::InvalidArgument,
           "zero timebase");
    sequence.timebase_denominator = 60;
    sequence.duration_ticks = 0;
    expect(plan_sequence(sequence, plan, diagnostic)
               == AnimationError::InvalidArgument,
           "zero duration");
    sequence.duration_ticks = 100;

    sequence.nesting_depth = kMaxSequenceDepth;
    expect(plan_sequence(sequence, plan, diagnostic) == AnimationError::None,
           "max depth");
    expect(plan.max_depth == kMaxSequenceDepth, "max depth plan");
    sequence.nesting_depth = kMaxSequenceDepth + 1;
    expect(plan_sequence(sequence, plan, diagnostic)
               == AnimationError::DepthExceeded,
           "depth exceeded");
    sequence.nesting_depth = 1;

    sequence.tracks[0].track_id = 0;
    expect(plan_sequence(sequence, plan, diagnostic)
               == AnimationError::SequenceInvalid,
           "zero track id");
    sequence.tracks[0].track_id = 1;
    sequence.tracks[0].revision = 0;
    expect(plan_sequence(sequence, plan, diagnostic)
               == AnimationError::SequenceInvalid,
           "zero track revision");
    sequence.tracks[0].revision = 1;
    sequence.tracks[0].kind = static_cast<TrackKind>(200);
    expect(plan_sequence(sequence, plan, diagnostic)
               == AnimationError::SequenceInvalid,
           "invalid track kind");
    sequence.tracks[0].kind = TrackKind::Sprite;

    sequence.tracks[1].track_id = 1;
    expect(plan_sequence(sequence, plan, diagnostic)
               == AnimationError::DuplicateId,
           "duplicate track id");
    sequence.tracks[1].track_id = 2;

    sequence.tracks[0].cue_count = kMaxSequenceCues + 1;
    expect(plan_sequence(sequence, plan, diagnostic)
               == AnimationError::SequenceInvalid,
           "cue overflow");
    sequence.tracks[0].cue_count = 1;

    sequence.tracks[0].cues[0].cue_id = 0;
    expect(plan_sequence(sequence, plan, diagnostic)
               == AnimationError::SequenceInvalid,
           "zero cue id");
    expect(diagnostic.source_id == 21, "cue diagnostic source");
    sequence.tracks[0].cues[0].cue_id = 1;
    sequence.tracks[0].cues[0].revision = 0;
    expect(plan_sequence(sequence, plan, diagnostic)
               == AnimationError::SequenceInvalid,
           "zero cue revision");
    sequence.tracks[0].cues[0].revision = 1;
    sequence.tracks[0].cues[0].kind = static_cast<TrackKind>(200);
    expect(plan_sequence(sequence, plan, diagnostic)
               == AnimationError::SequenceInvalid,
           "invalid cue kind");
    sequence.tracks[0].cues[0].kind = TrackKind::Sprite;

    sequence.tracks[1].cues[0].cue_id = 1;
    expect(plan_sequence(sequence, plan, diagnostic)
               == AnimationError::DuplicateId,
           "duplicate cue across tracks");
    sequence.tracks[1].cues[0].cue_id = 2;

    sequence.tracks[0].cues[0].tick = 100;
    sequence.tracks[0].cues[0].duration_ticks = 0;
    expect(plan_sequence(sequence, plan, diagnostic) == AnimationError::None,
           "cue at duration boundary");
    sequence.tracks[0].cues[0].tick = 101;
    expect(plan_sequence(sequence, plan, diagnostic)
               == AnimationError::TimeInvalid,
           "cue beyond duration");
    sequence.tracks[0].cues[0].tick = 95;
    sequence.tracks[0].cues[0].duration_ticks = 6;
    expect(plan_sequence(sequence, plan, diagnostic)
               == AnimationError::TimeInvalid,
           "cue duration overflow");
    sequence.tracks[0].cues[0].tick = std::numeric_limits<u64>::max();
    sequence.tracks[0].cues[0].duration_ticks = 0;
    expect(plan_sequence(sequence, plan, diagnostic)
               == AnimationError::TimeInvalid,
           "huge tick");
    sequence.tracks[0].cues[0].tick = 0;
    sequence.tracks[0].cues[0].duration_ticks = 10;

    sequence.track_count = kMaxSequenceTracks;
    for (u32 track_index = 0; track_index < kMaxSequenceTracks;
         ++track_index) {
        sequence.tracks[track_index] = track(track_index + 1, TrackKind::Vfx);
        sequence.tracks[track_index].cue_count = kMaxSequenceCues;
        for (u32 cue_index = 0; cue_index < kMaxSequenceCues; ++cue_index) {
            sequence.tracks[track_index].cues[cue_index] = cue(
                track_index * kMaxSequenceCues + cue_index + 1,
                TrackKind::Vfx, 0, 1);
        }
    }
    expect(plan_sequence(sequence, plan, diagnostic) == AnimationError::None,
           "capacity sequence");
    expect(plan.track_count == kMaxSequenceTracks
               && plan.cue_count == kMaxSequenceTracks * kMaxSequenceCues,
           "capacity counts");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_two03_sequence_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "seq01") { success = run_seq01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
