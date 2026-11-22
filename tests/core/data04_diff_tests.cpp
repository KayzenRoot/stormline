#include "stormline/data/scene/scene_diff.hpp"

#include <array>
#include <cstdio>
#include <string_view>

namespace {
using namespace stormline::data::scene;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

[[nodiscard]] EntityRecord entity(u64 id, std::string_view name, bool enabled) {
    EntityRecord value{};
    value.id = EntityId{id};
    value.name_length = static_cast<u32>(name.size());
    value.enabled = enabled;
    for (u32 index = 0; index < value.name_length; ++index) {
        value.name[index] = name[index];
    }
    return value;
}

[[nodiscard]] SceneDocument make_document() {
    SceneDocument document;
    (void)document.init(SceneId{1}, registry::ProjectId{1}, SchemaDescriptor{1, 1, 0, 1});
    return document;
}

bool run_diff01() {
    begin();
    SceneDocument base = make_document();
    SceneDocument next = make_document();
    (void)base.add_entity(entity(1, "a", true));
    (void)base.add_entity(entity(2, "b", true));
    (void)next.add_entity(entity(2, "renamed", false));
    (void)next.add_entity(entity(3, "c", true));

    std::array<DiffEntry, 8> output{};
    u32 count = 0;
    expect(diff(base, next, output, count) == SceneError::None, "diff");
    expect(count == 4, "diff count");
    expect(output[0].entity.value == 1 && output[0].kind == DiffKind::Removed, "removed");
    expect(output[1].entity.value == 2 && output[1].kind == DiffKind::EnabledChanged,
           "enabled");
    expect(output[2].entity.value == 2 && output[2].kind == DiffKind::NameChanged, "name");
    expect(output[3].entity.value == 3 && output[3].kind == DiffKind::Added, "added");

    std::array<DiffEntry, 2> small{};
    expect(diff(base, next, small, count) == SceneError::BufferFull, "buffer");
    expect(count == 4, "buffer required");

    std::array<DiffEntry, 1> same{};
    expect(diff(base, base, same, count) == SceneError::None && count == 0, "same");

    SceneDocument other;
    (void)other.init(SceneId{2}, registry::ProjectId{1}, SchemaDescriptor{1, 1, 0, 1});
    expect(diff(base, other, output, count) == SceneError::InvalidArgument, "scene mismatch");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_data04_diff_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "diff01") { success = run_diff01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
