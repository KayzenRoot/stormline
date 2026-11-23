#ifndef STORMLINE_GRAPHICS_SHADER_SHADER_REFLECTION_HPP
#define STORMLINE_GRAPHICS_SHADER_SHADER_REFLECTION_HPP

#include "stormline/graphics/shader/shader_parser.hpp"

namespace stormline::graphics::shader {

struct ReflectedBinding {
    Name name{};
    ShaderType type{ShaderType::Float};
    BindingKind kind{BindingKind::Uniform};
    u32 slot{0};
    u32 byte_size{0};
    u32 alignment{0};
};

struct ShaderReflection {
    Name module_name{};
    ShaderStage stage{ShaderStage::Vertex};
    u32 binding_count{0};
    std::array<ReflectedBinding, kMaxBindings> bindings{};
    u64 source_fingerprint{0};
};

namespace detail {

[[nodiscard]] inline bool valid_name(const Name& name) noexcept {
    if (name.length == 0 || name.length > kMaxNameBytes) {
        return false;
    }
    if (!is_identifier_start(name.text[0])) {
        return false;
    }
    for (u32 index = 0; index < name.length; ++index) {
        if (!is_identifier_body(name.text[index])) {
            return false;
        }
    }
    return true;
}

[[nodiscard]] inline bool valid_binding(const Binding& binding) noexcept {
    return valid_name(binding.name)
        && static_cast<u8>(binding.type) <= static_cast<u8>(ShaderType::Bool)
        && static_cast<u8>(binding.kind) <= static_cast<u8>(BindingKind::Uniform);
}

[[nodiscard]] inline u32 kind_index(BindingKind kind) noexcept {
    switch (kind) {
        case BindingKind::Input: return 0;
        case BindingKind::Output: return 1;
        case BindingKind::Uniform: return 2;
    }
    return 3;
}

[[nodiscard]] inline u32 kind_limit(BindingKind kind) noexcept {
    switch (kind) {
        case BindingKind::Input: return kMaxInputs;
        case BindingKind::Output: return kMaxOutputs;
        case BindingKind::Uniform: return kMaxUniforms;
    }
    return 0;
}

}  // namespace detail

[[nodiscard]] inline ShaderError reflect_shader(
    const ShaderIr& ir, ShaderReflection& out) noexcept {
    out = ShaderReflection{};
    if (!detail::valid_name(ir.module_name)
        || static_cast<u8>(ir.stage) > static_cast<u8>(ShaderStage::Compute)
        || ir.binding_count > kMaxBindings) {
        return ShaderError::InvalidArgument;
    }
    std::array<u32, 3> counts{0, 0, 0};
    for (u32 index = 0; index < ir.binding_count; ++index) {
        const Binding& binding = ir.bindings[index];
        if (!detail::valid_binding(binding)) {
            return ShaderError::InvalidArgument;
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (name_view(ir.bindings[previous].name) == name_view(binding.name)) {
                return ShaderError::InvalidArgument;
            }
        }
        const u32 kind = detail::kind_index(binding.kind);
        if (kind >= counts.size() || counts[kind] >= detail::kind_limit(binding.kind)) {
            return ShaderError::CapacityFull;
        }
        ++counts[kind];
    }
    std::array<u32, 3> slots{0, 0, 0};
    for (u32 index = 0; index < ir.binding_count; ++index) {
        const Binding& binding = ir.bindings[index];
        const u32 kind = detail::kind_index(binding.kind);
        const u32 size = shader_type_size(binding.type);
        const u32 alignment = shader_type_alignment(binding.type);
        if (size == 0 || alignment == 0) {
            return ShaderError::InvalidArgument;
        }
        out.bindings[index] = ReflectedBinding{
            binding.name, binding.type, binding.kind, slots[kind], size, alignment};
        ++slots[kind];
    }
    out.module_name = ir.module_name;
    out.stage = ir.stage;
    out.binding_count = ir.binding_count;
    out.source_fingerprint = ir.source_fingerprint;
    return ShaderError::None;
}

}  // namespace stormline::graphics::shader

#endif  // STORMLINE_GRAPHICS_SHADER_SHADER_REFLECTION_HPP
