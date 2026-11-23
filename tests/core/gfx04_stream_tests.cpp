#include "stormline/graphics/geometry/geometry_stream.hpp"

#include <cstdio>
#include <string_view>

namespace {
using namespace stormline::graphics::geometry;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

[[nodiscard]] ChunkSet chunks() {
    ChunkSet value{};
    value.scene_generation = 1;
    value.count = 3;
    value.chunks[0] = GeometryChunk{10, 2, 1, 100, true};
    value.chunks[1] = GeometryChunk{11, 1, 2, 200, true};
    value.chunks[2] = GeometryChunk{12, 1, 0, 50, true};
    return value;
}

bool run_str01() {
    begin();
    ChunkSet set = chunks();
    ResidentChunks resident{};
    resident.count = 1;
    resident.chunk_ids[0] = 10;
    StreamPlan plan{};
    GeometryDiagnostic diagnostic{};
    expect(plan_stream(set, resident, 500, plan, diagnostic) == GeometryError::None,
           "stream");
    expect(plan.count == 2, "count");
    expect(plan.chunk_ids[0] == 12 && plan.chunk_ids[1] == 11, "order");
    expect(plan.total_bytes == 250 && !plan.truncated, "bytes");

    expect(plan_stream(set, resident, 100, plan, diagnostic) == GeometryError::None,
           "small budget");
    expect(plan.count == 1 && plan.total_bytes == 50 && plan.truncated,
           "truncated");
    expect(plan_stream(set, resident, 10, plan, diagnostic) == GeometryError::None,
           "tiny budget");
    expect(plan.count == 0 && plan.truncated, "tiny truncated");

    ChunkSet unverified = set;
    unverified.chunks[0].verified = false;
    expect(plan_stream(unverified, resident, 500, plan, diagnostic)
               == GeometryError::UnverifiedChunk,
           "unverified");
    ChunkSet duplicate = set;
    duplicate.chunks[2].chunk_id = 10;
    expect(plan_stream(duplicate, resident, 500, plan, diagnostic)
               == GeometryError::DuplicateId,
           "duplicate");
    ChunkSet invalid = set;
    invalid.chunks[0].bytes = 0;
    expect(plan_stream(invalid, resident, 500, plan, diagnostic)
               == GeometryError::InvalidArgument,
           "zero bytes");
    ResidentChunks unknown{};
    unknown.count = 1;
    unknown.chunk_ids[0] = 99;
    expect(plan_stream(set, unknown, 500, plan, diagnostic)
               == GeometryError::NotFound,
           "unknown resident");
    ResidentChunks duplicate_resident{};
    duplicate_resident.count = 2;
    duplicate_resident.chunk_ids[0] = 10;
    duplicate_resident.chunk_ids[1] = 10;
    expect(plan_stream(set, duplicate_resident, 500, plan, diagnostic)
               == GeometryError::InvalidArgument,
           "duplicate resident");
    expect(plan_stream(set, resident, 0, plan, diagnostic)
               == GeometryError::InvalidArgument,
           "zero budget");

    ChunkSet full{};
    full.scene_generation = 1;
    full.count = kMaxChunks;
    for (u32 index = 0; index < kMaxChunks; ++index) {
        full.chunks[index] = GeometryChunk{index + 1, 1, 0, 1, true};
    }
    expect(plan_stream(full, ResidentChunks{}, 1000, plan, diagnostic)
               == GeometryError::None,
           "capacity");
    expect(plan.count == kMaxChunks, "capacity count");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_gfx04_stream_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "str01") { success = run_str01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
