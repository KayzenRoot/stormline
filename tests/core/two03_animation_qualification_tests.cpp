#include "stormline/animation/blend_plan.hpp"
#include "stormline/animation/flipbook_plan.hpp"
#include "stormline/animation/sequence_plan.hpp"
#include "stormline/animation/skeleton_plan.hpp"
#include "stormline/animation/timeline_plan.hpp"

#include <cstdio>
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

BoneDesc bone(u32 id, u32 parent) {
    BoneDesc desc{};
    desc.bone_id = id;
    desc.revision = 1;
    desc.parent_id = parent;
    return desc;
}

BlendClipDesc blend_clip(u32 id, f32 weight) {
    BlendClipDesc desc{};
    desc.clip_id = id;
    desc.revision = 1;
    desc.weight = weight;
    return desc;
}

SequenceCue cue(u32 id, TrackKind kind, u64 tick, u64 duration) {
    SequenceCue desc{};
    desc.cue_id = id;
    desc.revision = 1;
    desc.kind = kind;
    desc.tick = tick;
    desc.duration_ticks = duration;
    return desc;
}

SequenceTrack sequence_track(u32 id, TrackKind kind) {
    SequenceTrack desc{};
    desc.track_id = id;
    desc.revision = 1;
    desc.kind = kind;
    return desc;
}

FlipbookDesc make_flipbook() {
    FlipbookDesc desc{};
    desc.clip_id = 41;
    desc.revision = 1;
    desc.timebase_denominator = 60;
    desc.frame_count = 3;
    desc.frames[0] = FlipbookFrame{1, 100, 10, 1};
    desc.frames[1] = FlipbookFrame{2, 101, 11, 2};
    desc.frames[2] = FlipbookFrame{3, 102, 12, 3};
    return desc;
}

SkeletonDesc make_skeleton() {
    SkeletonDesc desc{};
    desc.skeleton_id = 42;
    desc.revision = 1;
    desc.bone_count = 3;
    desc.bones[0] = bone(1, 0);
    desc.bones[1] = bone(2, 1);
    desc.bones[2] = bone(3, 2);
    return desc;
}

BlendDesc make_blend() {
    BlendDesc desc{};
    desc.blend_id = 43;
    desc.revision = 1;
    desc.clip_count = 3;
    desc.clips[0] = blend_clip(1, 1.0f);
    desc.clips[1] = blend_clip(2, 2.0f);
    desc.clips[2] = blend_clip(3, 1.0f);
    return desc;
}

SequenceDesc make_sequence() {
    SequenceDesc desc{};
    desc.sequence_id = 44;
    desc.revision = 1;
    desc.timebase_denominator = 60;
    desc.duration_ticks = 120;
    desc.track_count = 2;
    desc.nesting_depth = 2;
    desc.tracks[0] = sequence_track(1, TrackKind::Sprite);
    desc.tracks[0].cue_count = 1;
    desc.tracks[0].cues[0] = cue(1, TrackKind::Sprite, 0, 10);
    desc.tracks[1] = sequence_track(2, TrackKind::Camera);
    desc.tracks[1].cue_count = 1;
    desc.tracks[1].cues[0] = cue(2, TrackKind::Camera, 30, 5);
    return desc;
}

TimelineDesc make_timeline() {
    TimelineDesc desc{};
    desc.timeline_id = 45;
    desc.revision = 1;
    desc.fps_numerator = 30;
    desc.fps_denominator = 1;
    desc.duration_frames = 120;
    desc.sample_rate = 48000;
    desc.loop_start_frame = 0;
    desc.loop_end_frame = 120;
    return desc;
}

struct IntegratedPlans {
    FlipbookPlan flipbook{};
    SkeletonPlan skeleton{};
    BlendPlan blend{};
    SequencePlan sequence{};
    TimelinePlan timeline{};
    AnimationDiagnostic diagnostic{};
};

bool plan_all(const FlipbookDesc& flipbook, const SkeletonDesc& skeleton,
              const BlendDesc& blend, const SequenceDesc& sequence,
              const TimelineDesc& timeline, IntegratedPlans& plans) {
    return plan_flipbook(flipbook, plans.flipbook, plans.diagnostic)
               == AnimationError::None
        && plan_skeleton(skeleton, plans.skeleton, plans.diagnostic)
               == AnimationError::None
        && plan_blend(blend, plans.blend, plans.diagnostic)
               == AnimationError::None
        && plan_sequence(sequence, plans.sequence, plans.diagnostic)
               == AnimationError::None
        && plan_timeline(timeline, plans.timeline, plans.diagnostic)
               == AnimationError::None;
}

bool run_qlft301() {
    begin();
    const FlipbookDesc flipbook = make_flipbook();
    const SkeletonDesc skeleton = make_skeleton();
    const BlendDesc blend = make_blend();
    const SequenceDesc sequence = make_sequence();
    const TimelineDesc timeline = make_timeline();
    IntegratedPlans plans{};

    expect(plan_all(flipbook, skeleton, blend, sequence, timeline, plans),
           "integrated plans");
    expect(plans.flipbook.frame_count == 3 && plans.flipbook.total_frames == 6,
           "integrated flipbook");
    expect(plans.skeleton.bone_count == 3 && plans.skeleton.max_depth == 3
               && plans.skeleton.root_count == 1,
           "integrated skeleton");
    expect(plans.blend.clip_count == 3
               && plans.blend.normalized_weights[1] == 0.5f,
           "integrated blend");
    expect(plans.sequence.track_count == 2 && plans.sequence.cue_count == 2
               && plans.sequence.max_depth == 2,
           "integrated sequence");
    expect(plans.timeline.frame_count == 120
               && plans.timeline.sample_count == 192000
               && plans.timeline.loop_length_frames == 120,
           "integrated timeline");
    expect(plans.diagnostic.code == AnimationError::None,
           "integrated diagnostic");
    return finish();
}

bool run_qlft302() {
    begin();
    const FlipbookDesc flipbook = make_flipbook();
    const SkeletonDesc skeleton = make_skeleton();
    const BlendDesc blend = make_blend();
    const SequenceDesc sequence = make_sequence();
    const TimelineDesc timeline = make_timeline();
    IntegratedPlans first{};
    IntegratedPlans second{};

    expect(plan_all(flipbook, skeleton, blend, sequence, timeline, first),
           "first integrated");
    expect(plan_all(flipbook, skeleton, blend, sequence, timeline, second),
           "second integrated");
    expect(first.flipbook.frame_count == second.flipbook.frame_count
               && first.flipbook.total_frames == second.flipbook.total_frames,
           "repeat flipbook");
    expect(first.skeleton.bone_count == second.skeleton.bone_count
               && first.skeleton.max_depth == second.skeleton.max_depth
               && first.skeleton.root_count == second.skeleton.root_count,
           "repeat skeleton");
    expect(first.blend.clip_count == second.blend.clip_count
               && first.blend.normalized_weights
                   == second.blend.normalized_weights,
           "repeat blend");
    expect(first.sequence.track_count == second.sequence.track_count
               && first.sequence.cue_count == second.sequence.cue_count
               && first.sequence.max_depth == second.sequence.max_depth,
           "repeat sequence");
    expect(first.timeline.frame_count == second.timeline.frame_count
               && first.timeline.sample_count == second.timeline.sample_count
               && first.timeline.loop_length_frames
                   == second.timeline.loop_length_frames,
           "repeat timeline");
    return finish();
}

bool run_qlft303() {
    begin();
    FlipbookDesc flipbook = make_flipbook();
    SkeletonDesc skeleton = make_skeleton();
    BlendDesc blend = make_blend();
    SequenceDesc sequence = make_sequence();
    TimelineDesc timeline = make_timeline();
    IntegratedPlans plans{};

    flipbook.clip_id = 0;
    expect(plan_flipbook(flipbook, plans.flipbook, plans.diagnostic)
               == AnimationError::InvalidArgument,
           "flipbook failure");
    flipbook = make_flipbook();
    expect(plan_flipbook(flipbook, plans.flipbook, plans.diagnostic)
               == AnimationError::None,
           "flipbook recovery");

    skeleton.bones[2].parent_id = 3;
    expect(plan_skeleton(skeleton, plans.skeleton, plans.diagnostic)
               == AnimationError::SkeletonInvalid,
           "skeleton failure");
    skeleton = make_skeleton();
    expect(plan_skeleton(skeleton, plans.skeleton, plans.diagnostic)
               == AnimationError::None,
           "skeleton recovery");

    blend.clips[0].weight = -1.0f;
    expect(plan_blend(blend, plans.blend, plans.diagnostic)
               == AnimationError::BlendInvalid,
           "blend failure");
    blend = make_blend();
    expect(plan_blend(blend, plans.blend, plans.diagnostic)
               == AnimationError::None,
           "blend recovery");

    sequence.tracks[0].cues[0].duration_ticks = 121;
    expect(plan_sequence(sequence, plans.sequence, plans.diagnostic)
               == AnimationError::TimeInvalid,
           "sequence failure");
    sequence = make_sequence();
    expect(plan_sequence(sequence, plans.sequence, plans.diagnostic)
               == AnimationError::None,
           "sequence recovery");

    timeline.loop_end_frame = 0;
    expect(plan_timeline(timeline, plans.timeline, plans.diagnostic)
               == AnimationError::TimeInvalid,
           "timeline failure");
    timeline = make_timeline();
    expect(plan_timeline(timeline, plans.timeline, plans.diagnostic)
               == AnimationError::None,
           "timeline recovery");
    return finish();
}

bool run_qlft304() {
    begin();
    constexpr u32 kAttempts = 10000;
    for (u32 attempt = 0; attempt < kAttempts; ++attempt) {
        FlipbookDesc flipbook = make_flipbook();
        SkeletonDesc skeleton = make_skeleton();
        BlendDesc blend = make_blend();
        SequenceDesc sequence = make_sequence();
        TimelineDesc timeline = make_timeline();
        IntegratedPlans plans{};
        if (attempt % 97 == 0) {
            flipbook.frames[0].hold_frames = 0;
            expect(plan_flipbook(flipbook, plans.flipbook, plans.diagnostic)
                       == AnimationError::FlipbookInvalid,
                   "overload flipbook failure");
            expect(plans.flipbook.frame_count == 0
                       && plans.flipbook.total_frames == 0,
                   "overload flipbook reset");
            flipbook = make_flipbook();
        }
        if (attempt % 89 == 0) {
            blend.additive = true;
            expect(plan_blend(blend, plans.blend, plans.diagnostic)
                       == AnimationError::BlendInvalid,
                   "overload blend failure");
            blend = make_blend();
        }
        if (attempt % 83 == 0) {
            sequence.nesting_depth = kMaxSequenceDepth + 1;
            expect(plan_sequence(sequence, plans.sequence, plans.diagnostic)
                       == AnimationError::DepthExceeded,
                   "overload sequence failure");
            sequence = make_sequence();
        }
        expect(plan_all(flipbook, skeleton, blend, sequence, timeline, plans),
               "overload plans");
        expect(plans.flipbook.frame_count <= kMaxFlipbookFrames,
               "flipbook cap");
        expect(plans.skeleton.bone_count <= kMaxBones, "skeleton cap");
        expect(plans.blend.clip_count <= kMaxBlendClips, "blend cap");
        expect(plans.sequence.track_count <= kMaxSequenceTracks,
               "sequence track cap");
        expect(plans.sequence.cue_count
                   <= kMaxSequenceTracks * kMaxSequenceCues,
               "sequence cue cap");
        expect(plans.sequence.max_depth <= kMaxSequenceDepth,
               "sequence depth cap");
        expect(plans.timeline.sample_count
                   == timeline.duration_frames * timeline.sample_rate
                       / timeline.fps_numerator,
               "timeline mapping cap");
    }
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr,
                     "usage: stormline_two03_animation_qualification_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "qlft301") { success = run_qlft301(); }
    else if (mode == "qlft302") { success = run_qlft302(); }
    else if (mode == "qlft303") { success = run_qlft303(); }
    else if (mode == "qlft304") { success = run_qlft304(); }
    else {
        std::fprintf(stderr, "unknown mode: %s\n", argv[1]);
        return 2;
    }
    return success ? 0 : 1;
}
