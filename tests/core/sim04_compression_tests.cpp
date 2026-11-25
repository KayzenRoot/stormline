#include "stormline/animation/skeletal/compression_plan.hpp"

#include <cstdio>
#include <string_view>

namespace {
using namespace stormline::animation::skeletal;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

CompressionProfileDesc profile(u32 id, u32 bits, bool lossless,
                               bool enabled) {
    CompressionProfileDesc desc{};
    desc.profile_id = id;
    desc.revision = 1;
    desc.translation_bits = bits;
    desc.rotation_bits = bits;
    desc.scale_bits = bits;
    desc.keyframe_interval = 8;
    desc.lossless = lossless;
    desc.enabled = enabled;
    return desc;
}

CompressionSetDesc compression_set() {
    CompressionSetDesc desc{};
    desc.owner_id = 10;
    desc.revision = 2;
    desc.profile_count = 3;
    desc.profiles[0] = profile(1, 16, true, true);
    desc.profiles[1] = profile(2, 8, false, false);
    desc.profiles[2] = profile(3, 24, false, true);
    return desc;
}

bool run_cmp01() {
    begin();
    CompressionSetDesc compression = compression_set();
    CompressionPlan plan{};
    SkeletalDiagnostic diagnostic{};
    expect(plan_compression(compression, plan, diagnostic)
               == SkeletalError::None,
           "valid compression");
    expect(plan.profile_count == 3 && plan.lossless_count == 1
               && plan.enabled_count == 2,
           "valid plan");
    expect(diagnostic.code == SkeletalError::None, "success diagnostic");

    CompressionPlan repeat{};
    expect(plan_compression(compression, repeat, diagnostic)
               == SkeletalError::None,
           "repeat compression");
    expect(repeat.lossless_count == plan.lossless_count,
           "deterministic plan");

    compression.owner_id = 0;
    expect(plan_compression(compression, plan, diagnostic)
               == SkeletalError::InvalidArgument,
           "zero owner");
    expect(plan.profile_count == 0, "reset on zero owner");
    compression = compression_set();
    compression.revision = 0;
    expect(plan_compression(compression, plan, diagnostic)
               == SkeletalError::InvalidArgument,
           "zero revision");
    compression = compression_set();
    compression.profile_count = kMaxCompressionProfiles + 1;
    expect(plan_compression(compression, plan, diagnostic)
               == SkeletalError::CapacityFull,
           "profile overflow");

    compression = compression_set();
    compression.profiles[1].profile_id = 0;
    expect(plan_compression(compression, plan, diagnostic)
               == SkeletalError::CompressionInvalid,
           "zero profile id");
    expect(diagnostic.index == 1, "zero profile diagnostic");
    compression = compression_set();
    compression.profiles[1].revision = 0;
    expect(plan_compression(compression, plan, diagnostic)
               == SkeletalError::CompressionInvalid,
           "zero revision");
    compression = compression_set();
    compression.profiles[1].translation_bits = 0;
    expect(plan_compression(compression, plan, diagnostic)
               == SkeletalError::OutOfRange,
           "zero translation bits");
    compression = compression_set();
    compression.profiles[1].rotation_bits = 33;
    expect(plan_compression(compression, plan, diagnostic)
               == SkeletalError::OutOfRange,
           "rotation bits overflow");
    compression = compression_set();
    compression.profiles[1].scale_bits = 0;
    expect(plan_compression(compression, plan, diagnostic)
               == SkeletalError::OutOfRange,
           "zero scale bits");
    compression = compression_set();
    compression.profiles[1].keyframe_interval = 0;
    expect(plan_compression(compression, plan, diagnostic)
               == SkeletalError::OutOfRange,
           "zero keyframe interval");
    compression = compression_set();
    compression.profiles[1].keyframe_interval = kMaxTickWindow + 1;
    expect(plan_compression(compression, plan, diagnostic)
               == SkeletalError::OutOfRange,
           "keyframe interval overflow");
    compression = compression_set();
    compression.profiles[2].profile_id = 1;
    expect(plan_compression(compression, plan, diagnostic)
               == SkeletalError::DuplicateId,
           "duplicate profile");
    expect(diagnostic.index == 2, "duplicate profile diagnostic");

    compression = compression_set();
    compression.profile_count = kMaxCompressionProfiles;
    for (u32 index = 0; index < kMaxCompressionProfiles; ++index) {
        compression.profiles[index] =
            profile(index + 1, 1 + index % 32, index % 3 == 0,
                    index % 2 == 0);
    }
    expect(plan_compression(compression, plan, diagnostic)
               == SkeletalError::None,
           "capacity compression");
    expect(plan.profile_count == kMaxCompressionProfiles
               && plan.lossless_count == 6
               && plan.enabled_count == kMaxCompressionProfiles / 2,
           "capacity plan");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_sim04_compression_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "cmp01") { success = run_cmp01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
