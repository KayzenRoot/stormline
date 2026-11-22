#include "stormline/data/scene/scene_schema.hpp"

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

bool run_sch01() {
    begin();
    SchemaDescriptor schema{1, 1, 0, 1};
    expect(validate_schema(schema) == SceneError::None, "v1");
    schema.version = 2;
    expect(validate_schema(schema) == SceneError::None, "v2");
    schema.version = 3;
    schema.capabilities = 0x3;
    expect(validate_schema(schema) == SceneError::None, "v3 caps");
    schema.schema_id = 2;
    expect(validate_schema(schema) == SceneError::InvalidSchema, "schema id");
    schema.schema_id = 1;
    schema.version = 0;
    expect(validate_schema(schema) == SceneError::UnsupportedSchema, "version 0");
    schema.version = 4;
    expect(validate_schema(schema) == SceneError::UnsupportedSchema, "version 4");
    schema.version = 1;
    schema.capabilities = 0x4;
    expect(validate_schema(schema) == SceneError::UnsupportedSchema, "capability");
    schema.capabilities = 0;
    schema.canonicalization_version = 2;
    expect(validate_schema(schema) == SceneError::UnsupportedSchema, "canonicalization");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_data04_schema_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "sch01") { success = run_sch01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
