#include "stormline/graphics/shader/shader_parser.hpp"

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

[[nodiscard]] bool compile_ok(
    const SourcePath& path, std::string_view source, ShaderIr& ir) {
    Diagnostic diagnostic{};
    return compile_shader(path, source, ir, diagnostic) == ShaderError::None
        && diagnostic.code == ShaderError::None;
}

[[nodiscard]] bool compile_error(
    const SourcePath& path, std::string_view source, ShaderError expected,
    Diagnostic& diagnostic) {
    ShaderIr ir{};
    return compile_shader(path, source, ir, diagnostic) == expected
        && diagnostic.code == expected;
}

bool run_par01() {
    begin();
    SourcePath path{};
    expect(make_source_path("shaders/demo.sscl", path) == ShaderError::None,
           "path");
    expect(path_view(path) == "shaders/demo.sscl", "path view");

    const std::string_view valid =
        "shader Demo {\n"
        "  // logical declarations only\n"
        "  stage vertex;\n"
        "  input vec3 position;\n"
        "  output vec4 color;\n"
        "  uniform mat4 view;\n"
        "}\n";
    ShaderIr ir{};
    expect(compile_ok(path, valid, ir), "valid vertex");
    expect(name_view(ir.module_name) == "Demo", "module");
    expect(ir.stage == ShaderStage::Vertex, "stage");
    expect(ir.binding_count == 3, "binding count");
    expect(ir.bindings[0].kind == BindingKind::Input
               && ir.bindings[0].type == ShaderType::Vec3
               && name_view(ir.bindings[0].name) == "position",
           "input");
    expect(ir.bindings[1].kind == BindingKind::Output
               && ir.bindings[1].type == ShaderType::Vec4
               && name_view(ir.bindings[1].name) == "color",
           "output");
    expect(ir.bindings[2].kind == BindingKind::Uniform
               && ir.bindings[2].type == ShaderType::Mat4
               && name_view(ir.bindings[2].name) == "view",
           "uniform");
    expect(ir.source_fingerprint != 0, "fingerprint");
    expect(ir.source_lines >= 7, "source lines");
    expect(path_view(ir.path) == "shaders/demo.sscl", "ir path");

    ShaderIr same{};
    expect(compile_ok(path, valid, same), "valid repeat");
    expect(same.source_fingerprint == ir.source_fingerprint, "fingerprint repeat");
    expect(same.binding_count == ir.binding_count, "binding repeat");

    const std::string_view fragment =
        "shader Shade{stage fragment;uniform vec4 tint;input vec2 uv;"
        "output vec4 color;}";
    expect(compile_ok(path, fragment, ir), "valid fragment");
    expect(ir.stage == ShaderStage::Fragment && ir.binding_count == 3, "fragment values");

    const std::string_view compute =
        "shader Compute { stage compute; uniform vec4 values; uniform int count; }";
    expect(compile_ok(path, compute, ir), "valid compute");
    expect(ir.stage == ShaderStage::Compute && ir.binding_count == 2, "compute values");

    const std::string_view all_types =
        "shader Types { stage vertex;"
        "uniform float a; uniform vec2 b; uniform vec3 c; uniform vec4 d;"
        "uniform mat3 e; uniform mat4 f; uniform int g; uniform uint h;"
        "uniform bool i; }";
    expect(compile_ok(path, all_types, ir) && ir.binding_count == 9, "all types");

    Diagnostic diagnostic{};
    expect(compile_error(path, "", ShaderError::EmptySource, diagnostic),
           "empty source");
    expect(compile_error(path, std::string(4097, 'a'), ShaderError::SourceTooLarge,
                         diagnostic), "source too large");
    expect(!compile_ok(path, std::string(300, '\n'), ir), "line limit");
    expect(compile_error(path, "shader X {\n@\n}", ShaderError::InvalidToken,
                         diagnostic), "invalid token");
    expect(diagnostic.span.line == 2 && diagnostic.span.column == 1,
           "invalid token span");
    expect(path_view(diagnostic.path) == "shaders/demo.sscl", "diagnostic path");
    expect(compile_error(path, "model X { stage vertex; }",
                         ShaderError::InvalidModule, diagnostic),
           "invalid module");
    expect(compile_error(path, "shader { stage vertex; }",
                         ShaderError::InvalidName, diagnostic),
           "missing module name");
    expect(compile_error(path, "shader X stage vertex; }",
                         ShaderError::UnexpectedToken, diagnostic),
           "missing brace");
    expect(compile_error(path, "shader X { stage vertex; stage fragment; }",
                         ShaderError::DuplicateStage, diagnostic),
           "duplicate stage");
    expect(compile_error(path, "shader X { uniform float a; }",
                         ShaderError::MissingStage, diagnostic),
           "missing stage");
    expect(compile_error(path, "shader X { stage vertex; input dvec3 a; }",
                         ShaderError::UnknownType, diagnostic),
           "unknown type");
    expect(compile_error(path,
        "shader X { stage vertex; uniform float a; uniform int a; }",
        ShaderError::DuplicateBinding, diagnostic), "duplicate binding");
    expect(compile_error(path, "shader X { stage compute; input vec3 a; }",
                         ShaderError::StageRestriction, diagnostic),
           "compute restriction");
    expect(compile_error(path,
        "shader X { stage vertex; input float a }",
        ShaderError::UnexpectedToken, diagnostic), "missing semicolon");
    expect(compile_error(path,
        "shader X { stage vertex; uniform float a; } trailing",
        ShaderError::UnexpectedToken, diagnostic), "trailing token");

    std::string many_inputs = "shader X { stage vertex;";
    for (u32 index = 0; index < kMaxInputs + 1; ++index) {
        many_inputs += " input float in";
        many_inputs += std::to_string(index);
        many_inputs += ";";
    }
    many_inputs += " }";
    expect(compile_error(path, many_inputs, ShaderError::CapacityFull, diagnostic),
           "input capacity");

    SourcePath long_path{};
    expect(make_source_path(std::string(65, 'p'), long_path) == ShaderError::PathTooLong,
           "path too long");
    expect(make_source_path("", long_path) == ShaderError::InvalidArgument,
           "empty path");
    Name name{};
    expect(make_name("", name) == ShaderError::InvalidName, "empty name");
    expect(make_name("1bad", name) == ShaderError::InvalidName, "bad name start");
    expect(make_name("bad-name", name) == ShaderError::InvalidName, "bad name body");
    expect(make_name(std::string(33, 'a'), name) == ShaderError::InvalidName,
           "long name");
    expect(make_name("ok_name1", name) == ShaderError::None
               && name_view(name) == "ok_name1", "valid name");
    expect(std::string_view(shader_error_name(ShaderError::DuplicateBinding))
               == "DuplicateBinding", "error name");
    expect(shader_type_size(ShaderType::Vec3) == 12
               && shader_type_alignment(ShaderType::Vec3) == 16,
           "type metadata");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_gfx02_shader_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "par01") { success = run_par01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
