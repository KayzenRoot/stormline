#include "stormline/data/vfs/vfs_capability.hpp"

#include <cstdio>
#include <string_view>

namespace {
using namespace stormline::data::vfs;
int failures = 0;
void expect(bool c, const char* d) { if (!c) { std::fprintf(stderr, "FAIL: %s\n", d); ++failures; } }
void begin() { failures = 0; }
bool finish() { return failures == 0; }

bool run_cap01() {
    begin();
    CapabilitySet set;
    const WorkspaceId workspace{1};
    const MountId mount{2};
    AccessCapability capability{workspace, mount, true};
    expect(set.size() == 0 && !set.allows(workspace, mount), "initial");
    expect(set.grant(capability) == VfsError::None, "grant");
    expect(set.size() == 1 && set.allows(workspace, mount), "grant allows");
    expect(!set.allows(WorkspaceId{3}, mount), "wrong workspace");
    expect(!set.allows(workspace, MountId{3}), "wrong mount");
    expect(!set.allows(WorkspaceId{}, mount), "invalid workspace");
    expect(set.grant(capability) == VfsError::None && set.size() == 1,
           "duplicate update");
    expect(set.grant(AccessCapability{WorkspaceId{}, mount, true})
               == VfsError::InvalidArgument,
           "invalid workspace grant");
    expect(set.grant(AccessCapability{workspace, MountId{}, true})
               == VfsError::InvalidArgument,
           "invalid mount grant");
    expect(set.grant(AccessCapability{workspace, MountId{4}, false})
               == VfsError::InvalidArgument,
           "write grant rejected");
    expect(set.revoke(WorkspaceId{3}, mount) == VfsError::NotFound,
           "revoke missing");
    expect(set.revoke(workspace, mount) == VfsError::None, "revoke");
    expect(set.size() == 0 && !set.allows(workspace, mount), "revoked");

    for (u32 index = 1; index <= kMaxCapabilities; ++index) {
        expect(set.grant(AccessCapability{WorkspaceId{index}, MountId{1}, true})
                   == VfsError::None,
               "fill capability");
    }
    expect(set.size() == kMaxCapabilities, "capacity");
    expect(set.grant(AccessCapability{WorkspaceId{99}, MountId{1}, true})
               == VfsError::BufferFull,
           "capacity error");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) { std::fprintf(stderr, "usage: stormline_data01_capability_test <mode>\n"); return 2; }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "cap01") { success = run_cap01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
