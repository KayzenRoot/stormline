#include "stormline/graphics/shader/shader_reflection.hpp"

#include <cstdio>
#include <string>
#include <string_view>

namespace {
using namespace stormline::graphics::shader;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

[[nodiscard]] ShaderIr parsed(std::string_view source, bool& ok) {
    SourcePath path{};
    std::string_view text = "reflection.sscl";
    ok = make_source_path(text, path) == ShaderError::None;
    ShaderIr ir{};
    Diagnostic diagnostic{};
    ok = ok && compile_shader(path, source, ir, diagnostic) == ShaderError::None;
    return ir;
}

bool run_ref01() {
    begin();
    bool ok = false;
    ShaderIr ir = parsed(
        "shader Demo { stage vertex;"
        "input vec3 position; input vec2 uv;"
        "output vec4 color;"
        "uniform mat4 view; uniform vec3 light;"
        "}", ok);
    expect(ok, "parse");

    ShaderReflection reflection{};
    expect(reflect_shader(ir, reflection) == ShaderError::None, "reflect");
    expect(name_view(reflection.module_name) == "Demo", "module");
    expect(reflection.stage == ShaderStage::Vertex, "stage");
    expect(reflection.binding_count == 5, "count");
    expect(reflection.source_fingerprint == ir.source_fingerprint, "fingerprint");

    expect(name_view(reflection.bindings[0].name) == "position"
               && reflection.bindings[0].kind == BindingKind::Input
               && reflection.bindings[0].slot == 0
               && reflection.bindings[0].byte_size == 12
               && reflection.bindings[0].alignment == 16,
           "input 0");
    expect(name_view(reflection.bindings[1].name) == "uv"
               && reflection.bindings[1].slot == 1
               && reflection.bindings[1].byte_size == 8
               && reflection.bindings[1].alignment == 8,
           "input 1");
    expect(name_view(reflection.bindings[2].name) == "color"
               && reflection.bindings[2].kind == BindingKind::Output
               && reflection.bindings[2].slot == 0
               && reflection.bindings[2].byte_size == 16,
           "output 0");
    expect(name_view(reflection.bindings[3].name) == "view"
               && reflection.bindings[3].kind == BindingKind::Uniform
               && reflection.bindings[3].slot == 0
               && reflection.bindings[3].byte_size == 64,
           "uniform 0");
    expect(name_view(reflection.bindings[4].name) == "light"
               && reflection.bindings[4].slot == 1
               && reflection.bindings[4].byte_size == 12
               && reflection.bindings[4].alignment == 16,
           "uniform 1");

    ShaderIr empty = parsed("shader Empty { stage fragment; }", ok);
    expect(ok, "empty parse");
    ShaderReflection empty_reflection{};
    expect(reflect_shader(empty, empty_reflection) == ShaderError::None
               && empty_reflection.binding_count == 0,
           "empty reflection");

    ShaderIr invalid = ir;
    invalid.binding_count = kMaxBindings + 1;
    expect(reflect_shader(invalid, reflection) == ShaderError::InvalidArgument,
           "count invalid");
    invalid = ir;
    invalid.stage = static_cast<ShaderStage>(9);
    expect(reflect_shader(invalid, reflection) == ShaderError::InvalidArgument,
           "stage invalid");
    invalid = ir;
    invalid.module_name = Name{};
    expect(reflect_shader(invalid, reflection) == ShaderError::InvalidArgument,
           "name invalid");
    invalid = ir;
    invalid.bindings[0].type = static_cast<ShaderType>(9);
    expect(reflect_shader(invalid, reflection) == ShaderError::InvalidArgument,
           "type invalid");
    invalid = ir;
    invalid.bindings[0].kind = static_cast<BindingKind>(9);
    expect(reflect_shader(invalid, reflection) == ShaderError::InvalidArgument,
           "kind invalid");
    invalid = ir;
    invalid.bindings[1].name = invalid.bindings[0].name;
    expect(reflect_shader(invalid, reflection) == ShaderError::InvalidArgument,
           "duplicate invalid");

    ShaderIr full = ir;
    full.binding_count = kMaxInputs + 1;
    for (u32 index = 0; index < full.binding_count; ++index) {
        full.bindings[index].kind = BindingKind::Input;
        full.bindings[index].type = ShaderType::Float;
        (void)make_name("in" + std::to_string(index), full.bindings[index].name);
    }
    expect(reflect_shader(full, reflection) == ShaderError::CapacityFull,
           "kind capacity");

    for (const ShaderType type : {ShaderType::Float, ShaderType::Vec2,
             ShaderType::Vec3, ShaderType::Vec4, ShaderType::Mat3,
             ShaderType::Mat4, ShaderType::Int, ShaderType::Uint,
             ShaderType::Bool}) {
        expect(shader_type_size(type) != 0 && shader_type_alignment(type) != 0,
               "type metadata");
    }
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_gfx02_reflection_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "ref01") { success = run_ref01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
