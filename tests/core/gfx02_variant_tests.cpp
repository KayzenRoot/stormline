#include "stormline/graphics/shader/shader_variant.hpp"

#include <cstdio>
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
    ok = make_source_path("variant.sscl", path) == ShaderError::None;
    ShaderIr ir{};
    Diagnostic diagnostic{};
    ok = ok && compile_shader(path, source, ir, diagnostic) == ShaderError::None;
    return ir;
}

bool run_var01() {
    begin();
    bool ok = false;
    ShaderIr ir = parsed("shader V { stage fragment; uniform vec3 color; }", ok);
    expect(ok, "parse");

    VariantPlan plan{};
    expect(plan_variants(ir, VariantRequest{1, 0, 1}, plan) == ShaderError::None,
           "zero switches");
    expect(plan.count == 1 && plan.keys[0].switch_bits == 0, "zero key");
    expect(plan.keys[0].source_fingerprint == ir.source_fingerprint
               && plan.keys[0].recipe_version == 1
               && plan.keys[0].stage == ShaderStage::Fragment,
           "zero identity");

    expect(plan_variants(ir, VariantRequest{2, 1, 2}, plan) == ShaderError::None,
           "one switch");
    expect(plan.count == 2 && plan.keys[0].switch_bits == 0
               && plan.keys[1].switch_bits == 1,
           "one keys");

    expect(plan_variants(ir, VariantRequest{3, 6, 64}, plan) == ShaderError::None,
           "six switches");
    expect(plan.count == 64, "six count");
    const VariantPlan expected_plan = plan;
    for (u32 index = 0; index < plan.count; ++index) {
        expect(plan.keys[index].switch_bits == index, "ascending keys");
        expect(plan.keys[index].source_fingerprint == ir.source_fingerprint,
               "source identity");
        expect(plan.keys[index].recipe_version == 3, "recipe identity");
        expect(plan.keys[index].stage == ShaderStage::Fragment, "stage identity");
    }

    expect(plan_variants(ir, VariantRequest{1, 7, 64}, plan)
               == ShaderError::VariantLimit, "seven limit");
    expect(plan_variants(ir, VariantRequest{1, 8, 64}, plan)
               == ShaderError::VariantLimit, "eight limit");
    expect(plan_variants(ir, VariantRequest{1, 16, 64}, plan)
               == ShaderError::VariantLimit, "sixteen limit");
    expect(plan_variants(ir, VariantRequest{0, 1, 2}, plan)
               == ShaderError::InvalidArgument, "zero recipe");
    expect(plan_variants(ir, VariantRequest{1, 17, 64}, plan)
               == ShaderError::InvalidArgument, "switch range");
    expect(plan_variants(ir, VariantRequest{1, 1, 0}, plan)
               == ShaderError::InvalidArgument, "zero max");
    expect(plan_variants(ir, VariantRequest{1, 1, 65}, plan)
               == ShaderError::InvalidArgument, "max range");

    ShaderIr invalid = ir;
    invalid.stage = static_cast<ShaderStage>(9);
    expect(plan_variants(invalid, VariantRequest{1, 1, 2}, plan)
               == ShaderError::InvalidArgument, "invalid stage");
    invalid = ir;
    invalid.binding_count = kMaxBindings + 1;
    expect(plan_variants(invalid, VariantRequest{1, 1, 2}, plan)
               == ShaderError::InvalidArgument, "invalid count");

    VariantPlan repeat{};
    expect(plan_variants(ir, VariantRequest{3, 6, 64}, repeat) == ShaderError::None,
           "repeat");
    expect(repeat.count == expected_plan.count, "repeat count");
    for (u32 index = 0; index < repeat.count; ++index) {
        expect(repeat.keys[index].switch_bits == expected_plan.keys[index].switch_bits,
               "repeat mask");
        expect(repeat.keys[index].source_fingerprint
                   == expected_plan.keys[index].source_fingerprint,
               "repeat fingerprint");
    }
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_gfx02_variant_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "var01") { success = run_var01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
