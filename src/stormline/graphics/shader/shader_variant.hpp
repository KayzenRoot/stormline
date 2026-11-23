#ifndef STORMLINE_GRAPHICS_SHADER_SHADER_VARIANT_HPP
#define STORMLINE_GRAPHICS_SHADER_SHADER_VARIANT_HPP

#include "stormline/graphics/shader/shader_parser.hpp"

namespace stormline::graphics::shader {

struct VariantRequest {
    u32 recipe_version{0};
    u32 switch_count{0};
    u32 max_variants{0};
};

struct VariantKey {
    u64 source_fingerprint{0};
    u32 recipe_version{0};
    u16 switch_bits{0};
    ShaderStage stage{ShaderStage::Vertex};
};

struct VariantPlan {
    u32 count{0};
    std::array<VariantKey, kMaxVariants> keys{};
};

[[nodiscard]] inline ShaderError plan_variants(
    const ShaderIr& ir, const VariantRequest& request,
    VariantPlan& out) noexcept {
    out = VariantPlan{};
    if (request.recipe_version == 0
        || request.switch_count > kMaxStaticSwitches
        || request.max_variants == 0
        || request.max_variants > kMaxVariants
        || static_cast<u8>(ir.stage) > static_cast<u8>(ShaderStage::Compute)
        || ir.binding_count > kMaxBindings) {
        return ShaderError::InvalidArgument;
    }
    const u32 required = 1u << request.switch_count;
    if (required > request.max_variants || required > kMaxVariants) {
        return ShaderError::VariantLimit;
    }
    for (u32 index = 0; index < required; ++index) {
        out.keys[index] = VariantKey{
            ir.source_fingerprint, request.recipe_version,
            static_cast<u16>(index), ir.stage};
    }
    out.count = required;
    return ShaderError::None;
}

}  // namespace stormline::graphics::shader

#endif  // STORMLINE_GRAPHICS_SHADER_SHADER_VARIANT_HPP
