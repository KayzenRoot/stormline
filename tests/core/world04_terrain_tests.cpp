#include "stormline/terrain/terrain_patch_plan.hpp"

#include <cstdio>
#include <string_view>

namespace {
using namespace stormline::terrain;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

TerrainPatchDesc patch(
    u64 key, i64 tile_x, i64 tile_z, u32 lod, PatchTopology topology) {
    TerrainPatchDesc desc{};
    desc.patch_key = key;
    desc.revision = 1;
    desc.tile_x = tile_x;
    desc.tile_z = tile_z;
    desc.lod = lod;
    desc.topology = topology;
    return desc;
}

TerrainPatchSetDesc patch_set() {
    TerrainPatchSetDesc desc{};
    desc.asset_id = 10;
    desc.revision = 2;
    desc.patch_count = 4;
    desc.patches[0] = patch(1, 0, 0, 0, PatchTopology::Heightfield);
    desc.patches[1] = patch(2, 1, 0, 1, PatchTopology::Heightfield);
    desc.patches[2] = patch(3, -1, 2, 2, PatchTopology::MeshSurface);
    desc.patches[3] = patch(4, 3, -2, 3, PatchTopology::Heightfield);
    desc.patches[0].neighbor_count = 1;
    desc.patches[0].neighbors[0] = 2;
    desc.patches[1].neighbor_count = 2;
    desc.patches[1].neighbors[0] = 1;
    desc.patches[1].neighbors[1] = 3;
    return desc;
}

bool run_ter01() {
    begin();
    TerrainPatchSetDesc patches = patch_set();
    TerrainPatchPlan plan{};
    TerrainDiagnostic diagnostic{};
    expect(plan_terrain_patches(patches, plan, diagnostic)
               == TerrainError::None,
           "valid patches");
    expect(plan.patch_count == 4 && plan.max_lod == 3
               && plan.mesh_surface_count == 1,
           "valid counts");
    expect(plan.min_tile_x == -1 && plan.max_tile_x == 3
               && plan.min_tile_z == -2 && plan.max_tile_z == 2,
           "valid bounds");
    expect(diagnostic.code == TerrainError::None, "success diagnostic");
    TerrainPatchPlan repeat{};
    expect(plan_terrain_patches(patches, repeat, diagnostic)
               == TerrainError::None,
           "repeat patches");
    expect(repeat.max_lod == plan.max_lod
               && repeat.min_tile_x == plan.min_tile_x
               && repeat.mesh_surface_count == plan.mesh_surface_count,
           "deterministic plan");

    patches.asset_id = 0;
    expect(plan_terrain_patches(patches, plan, diagnostic)
               == TerrainError::InvalidArgument,
           "zero asset");
    expect(plan.patch_count == 0 && plan.max_lod == 0,
           "reset on zero asset");
    patches = patch_set();
    patches.revision = 0;
    expect(plan_terrain_patches(patches, plan, diagnostic)
               == TerrainError::InvalidArgument,
           "zero revision");
    patches = patch_set();
    patches.patch_count = 0;
    expect(plan_terrain_patches(patches, plan, diagnostic)
               == TerrainError::PatchInvalid,
           "zero count");
    patches.patch_count = kMaxTerrainPatches + 1;
    expect(plan_terrain_patches(patches, plan, diagnostic)
               == TerrainError::CapacityFull,
           "count overflow");

    patches = patch_set();
    patches.patches[1].patch_key = 0;
    expect(plan_terrain_patches(patches, plan, diagnostic)
               == TerrainError::PatchInvalid,
           "zero patch key");
    expect(diagnostic.index == 1, "zero key diagnostic");
    patches = patch_set();
    patches.patches[1].revision = 0;
    expect(plan_terrain_patches(patches, plan, diagnostic)
               == TerrainError::PatchInvalid,
           "zero patch revision");
    patches = patch_set();
    patches.patches[2].lod = kMaxTerrainLod + 1;
    expect(plan_terrain_patches(patches, plan, diagnostic)
               == TerrainError::OutOfRange,
           "lod overflow");
    patches = patch_set();
    patches.patches[2].topology =
        static_cast<PatchTopology>(static_cast<u8>(99));
    expect(plan_terrain_patches(patches, plan, diagnostic)
               == TerrainError::PatchInvalid,
           "unknown topology");
    patches = patch_set();
    patches.patches[3].patch_key = 1;
    expect(plan_terrain_patches(patches, plan, diagnostic)
               == TerrainError::DuplicateId,
           "duplicate key");
    expect(diagnostic.index == 3, "duplicate key diagnostic");
    patches = patch_set();
    patches.patches[3].tile_x = 1;
    patches.patches[3].tile_z = 0;
    expect(plan_terrain_patches(patches, plan, diagnostic)
               == TerrainError::DuplicateId,
           "duplicate tile");
    patches = patch_set();
    patches.patches[0].neighbor_count = kMaxPatchNeighbors + 1;
    expect(plan_terrain_patches(patches, plan, diagnostic)
               == TerrainError::CapacityFull,
           "neighbor overflow");

    patches = patch_set();
    patches.patches[0].neighbors[0] = 0;
    expect(plan_terrain_patches(patches, plan, diagnostic)
               == TerrainError::PatchInvalid,
           "zero neighbor");
    patches = patch_set();
    patches.patches[0].neighbors[0] = 1;
    expect(plan_terrain_patches(patches, plan, diagnostic)
               == TerrainError::PatchInvalid,
           "self neighbor");
    patches = patch_set();
    patches.patches[1].neighbors[1] = 1;
    expect(plan_terrain_patches(patches, plan, diagnostic)
               == TerrainError::DuplicateId,
           "duplicate neighbor");
    patches = patch_set();
    patches.patches[0].neighbors[0] = 99;
    expect(plan_terrain_patches(patches, plan, diagnostic)
               == TerrainError::NotFound,
           "missing neighbor");
    expect(diagnostic.asset_id == 10 && diagnostic.index == 0,
           "neighbor diagnostic");

    patches = patch_set();
    patches.patch_count = kMaxTerrainPatches;
    for (u32 index = 0; index < kMaxTerrainPatches; ++index) {
        patches.patches[index] =
            patch(static_cast<u64>(index) + 1,
                  static_cast<i64>(index) - 32,
                  static_cast<i64>(index), index % (kMaxTerrainLod + 1),
                  index % 2 == 0 ? PatchTopology::Heightfield
                                 : PatchTopology::MeshSurface);
        patches.patches[index].neighbor_count = 1;
        patches.patches[index].neighbors[0] =
            static_cast<u64>(index + 1) % kMaxTerrainPatches + 1;
    }
    expect(plan_terrain_patches(patches, plan, diagnostic)
               == TerrainError::None,
           "capacity patches");
    expect(plan.patch_count == kMaxTerrainPatches
               && plan.mesh_surface_count == 32,
           "capacity counts");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_world04_terrain_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "ter01") { success = run_ter01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
