#ifndef STORMLINE_GRAPHICS_SHADER_SHADER_PARSER_HPP
#define STORMLINE_GRAPHICS_SHADER_SHADER_PARSER_HPP

#include "stormline/graphics/shader/shader_types.hpp"

#include <string_view>

namespace stormline::graphics::shader {

struct Binding {
    Name name{};
    ShaderType type{ShaderType::Float};
    BindingKind kind{BindingKind::Uniform};
};

struct SourceSpan {
    u32 line{0};
    u32 column{0};
    u32 length{0};
};

struct Diagnostic {
    ShaderError code{ShaderError::None};
    SourceSpan span{};
    SourcePath path{};
};

struct ShaderIr {
    SourcePath path{};
    Name module_name{};
    ShaderStage stage{ShaderStage::Vertex};
    u32 binding_count{0};
    std::array<Binding, kMaxBindings> bindings{};
    u64 source_fingerprint{0};
    u32 source_lines{0};
};

namespace detail {

inline constexpr u64 kFnvOffset = 1469598103934665603ULL;
inline constexpr u64 kFnvPrime = 1099511628211ULL;

[[nodiscard]] inline u64 shader_fnv1a64(std::string_view bytes) noexcept {
    u64 hash = kFnvOffset;
    for (const char value : bytes) {
        hash ^= static_cast<u8>(value);
        hash *= kFnvPrime;
    }
    return hash;
}

enum class TokenKind : std::uint8_t {
    End, Identifier, Shader, Stage, Input, Output, Uniform,
    Vertex, Fragment, Compute, Type, LBrace, RBrace, Semicolon
};

struct Token {
    TokenKind kind{TokenKind::End};
    Name name{};
    ShaderType type{ShaderType::Float};
    u32 line{0};
    u32 column{0};
    u32 length{0};
};

struct Lexer {
    std::string_view source{};
    u32 position{0};
    u32 line{1};
    u32 column{1};
};

inline void advance(Lexer& lexer) noexcept {
    if (lexer.source[lexer.position] == '\n') {
        ++lexer.line;
        lexer.column = 1;
    } else {
        ++lexer.column;
    }
    ++lexer.position;
}

inline void set_diagnostic(
    Diagnostic& diagnostic, ShaderError code, u32 line, u32 column,
    u32 length) noexcept {
    diagnostic.code = code;
    diagnostic.span = SourceSpan{line, column, length};
}

[[nodiscard]] inline bool classify_type(
    std::string_view text, ShaderType& out) noexcept {
    if (text == "float") { out = ShaderType::Float; return true; }
    if (text == "vec2") { out = ShaderType::Vec2; return true; }
    if (text == "vec3") { out = ShaderType::Vec3; return true; }
    if (text == "vec4") { out = ShaderType::Vec4; return true; }
    if (text == "mat3") { out = ShaderType::Mat3; return true; }
    if (text == "mat4") { out = ShaderType::Mat4; return true; }
    if (text == "int") { out = ShaderType::Int; return true; }
    if (text == "uint") { out = ShaderType::Uint; return true; }
    if (text == "bool") { out = ShaderType::Bool; return true; }
    return false;
}

[[nodiscard]] inline ShaderError lexer_next(
    Lexer& lexer, Token& token, Diagnostic& diagnostic) noexcept {
    for (;;) {
        while (lexer.position < lexer.source.size()
               && (lexer.source[lexer.position] == ' '
                   || lexer.source[lexer.position] == '\t'
                   || lexer.source[lexer.position] == '\r'
                   || lexer.source[lexer.position] == '\n')) {
            advance(lexer);
        }
        if (lexer.position + 1 < lexer.source.size()
            && lexer.source[lexer.position] == '/'
            && lexer.source[lexer.position + 1] == '/') {
            while (lexer.position < lexer.source.size()
                   && lexer.source[lexer.position] != '\n') {
                advance(lexer);
            }
            continue;
        }
        break;
    }

    token = Token{};
    token.line = lexer.line;
    token.column = lexer.column;
    if (lexer.position >= lexer.source.size()) {
        token.kind = TokenKind::End;
        token.length = 0;
        return ShaderError::None;
    }

    const char current = lexer.source[lexer.position];
    if (current == '{' || current == '}' || current == ';') {
        token.kind = current == '{' ? TokenKind::LBrace
            : (current == '}' ? TokenKind::RBrace : TokenKind::Semicolon);
        token.length = 1;
        advance(lexer);
        return ShaderError::None;
    }

    if (!is_identifier_start(current)) {
        token.length = 1;
        advance(lexer);
        set_diagnostic(diagnostic, ShaderError::InvalidToken,
                       token.line, token.column, 1);
        return ShaderError::InvalidToken;
    }

    const u32 start = lexer.position;
    while (lexer.position < lexer.source.size()
           && is_identifier_body(lexer.source[lexer.position])) {
        advance(lexer);
    }
    const std::string_view text =
        lexer.source.substr(start, lexer.position - start);
    token.length = static_cast<u32>(text.size());
    const ShaderError name_status = make_name(text, token.name);
    if (name_status != ShaderError::None) {
        set_diagnostic(diagnostic, name_status, token.line, token.column,
                       token.length);
        return name_status;
    }
    if (text == "shader") { token.kind = TokenKind::Shader; return ShaderError::None; }
    if (text == "stage") { token.kind = TokenKind::Stage; return ShaderError::None; }
    if (text == "input") { token.kind = TokenKind::Input; return ShaderError::None; }
    if (text == "output") { token.kind = TokenKind::Output; return ShaderError::None; }
    if (text == "uniform") { token.kind = TokenKind::Uniform; return ShaderError::None; }
    if (text == "vertex") { token.kind = TokenKind::Vertex; return ShaderError::None; }
    if (text == "fragment") { token.kind = TokenKind::Fragment; return ShaderError::None; }
    if (text == "compute") { token.kind = TokenKind::Compute; return ShaderError::None; }
    if (classify_type(text, token.type)) {
        token.kind = TokenKind::Type;
        return ShaderError::None;
    }
    token.kind = TokenKind::Identifier;
    return ShaderError::None;
}

struct Parser {
    Lexer lexer{};
    const SourcePath& path;
    Diagnostic& diagnostic;
    Token token{};
    bool failed{false};
};

[[nodiscard]] inline bool advance_token(Parser& parser) noexcept {
    const ShaderError status =
        lexer_next(parser.lexer, parser.token, parser.diagnostic);
    if (status != ShaderError::None) {
        parser.failed = true;
        return false;
    }
    return true;
}

[[nodiscard]] inline bool fail(
    Parser& parser, ShaderError code, const Token& token) noexcept {
    set_diagnostic(parser.diagnostic, code, token.line, token.column,
                   token.length);
    parser.failed = true;
    return false;
}

[[nodiscard]] inline bool expect(
    Parser& parser, TokenKind kind, ShaderError code) noexcept {
    if (parser.token.kind != kind) {
        return fail(parser, code, parser.token);
    }
    return true;
}

[[nodiscard]] inline bool binding_type(
    const Token& token, ShaderType& out) noexcept {
    if (token.kind != TokenKind::Type) {
        return false;
    }
    out = token.type;
    return true;
}

[[nodiscard]] inline bool binding_kind(
    TokenKind kind, BindingKind& out) noexcept {
    switch (kind) {
        case TokenKind::Input: out = BindingKind::Input; return true;
        case TokenKind::Output: out = BindingKind::Output; return true;
        case TokenKind::Uniform: out = BindingKind::Uniform; return true;
        default: return false;
    }
}

[[nodiscard]] inline bool duplicate_binding(
    const ShaderIr& ir, const Name& name) noexcept {
    const std::string_view candidate = name_view(name);
    for (u32 index = 0; index < ir.binding_count; ++index) {
        if (name_view(ir.bindings[index].name) == candidate) {
            return true;
        }
    }
    return false;
}

}  // namespace detail

[[nodiscard]] inline ShaderError compile_shader(
    const SourcePath& path, std::string_view source,
    ShaderIr& out, Diagnostic& diagnostic) noexcept {
    out = ShaderIr{};
    diagnostic = Diagnostic{};
    diagnostic.path = path;

    if (path.length == 0 || path.length > kMaxPathBytes) {
        diagnostic.code = ShaderError::InvalidArgument;
        return diagnostic.code;
    }
    if (source.empty()) {
        detail::set_diagnostic(diagnostic, ShaderError::EmptySource, 1, 1, 1);
        return diagnostic.code;
    }
    if (source.size() > kMaxSourceBytes) {
        detail::set_diagnostic(diagnostic, ShaderError::SourceTooLarge, 1, 1, 1);
        return diagnostic.code;
    }
    u32 line_count = 1;
    for (const char value : source) {
        if (value == '\n') {
            ++line_count;
        }
    }
    if (line_count > kMaxSourceLines) {
        detail::set_diagnostic(diagnostic, ShaderError::TooManyLines, 1, 1, 1);
        return diagnostic.code;
    }

    detail::Parser parser{
        detail::Lexer{source, 0, 1, 1}, path, diagnostic, detail::Token{}, false};
    if (!detail::advance_token(parser)) {
        return diagnostic.code;
    }
    if (parser.token.kind != detail::TokenKind::Shader) {
        (void)detail::fail(parser, ShaderError::InvalidModule, parser.token);
        return diagnostic.code;
    }
    if (!detail::advance_token(parser)) {
        return diagnostic.code;
    }
    if (parser.token.kind != detail::TokenKind::Identifier) {
        (void)detail::fail(parser, ShaderError::InvalidName, parser.token);
        return diagnostic.code;
    }
    const Name module_name = parser.token.name;
    if (!detail::advance_token(parser)) {
        return diagnostic.code;
    }
    if (!detail::expect(parser, detail::TokenKind::LBrace,
                        ShaderError::UnexpectedToken)) {
        return diagnostic.code;
    }
    if (!detail::advance_token(parser)) {
        return diagnostic.code;
    }

    out.path = path;
    out.module_name = module_name;
    bool stage_seen = false;
    ShaderStage stage = ShaderStage::Vertex;
    u32 input_count = 0;
    u32 output_count = 0;
    u32 uniform_count = 0;
    bool restricted = false;
    detail::Token restricted_token{};

    while (parser.token.kind != detail::TokenKind::RBrace) {
        if (parser.token.kind == detail::TokenKind::End) {
            (void)detail::fail(parser, ShaderError::UnexpectedToken, parser.token);
            return diagnostic.code;
        }
        if (parser.token.kind == detail::TokenKind::Stage) {
            if (stage_seen) {
                (void)detail::fail(parser, ShaderError::DuplicateStage, parser.token);
                return diagnostic.code;
            }
            if (!detail::advance_token(parser)) {
                return diagnostic.code;
            }
            if (parser.token.kind == detail::TokenKind::Vertex) {
                stage = ShaderStage::Vertex;
            } else if (parser.token.kind == detail::TokenKind::Fragment) {
                stage = ShaderStage::Fragment;
            } else if (parser.token.kind == detail::TokenKind::Compute) {
                stage = ShaderStage::Compute;
            } else {
                (void)detail::fail(parser, ShaderError::UnexpectedToken,
                                   parser.token);
                return diagnostic.code;
            }
            stage_seen = true;
            if (!detail::advance_token(parser)) {
                return diagnostic.code;
            }
            if (!detail::expect(parser, detail::TokenKind::Semicolon,
                                ShaderError::UnexpectedToken)) {
                return diagnostic.code;
            }
            if (!detail::advance_token(parser)) {
                return diagnostic.code;
            }
            continue;
        }

        BindingKind kind{};
        if (!detail::binding_kind(parser.token.kind, kind)) {
            (void)detail::fail(parser, ShaderError::UnexpectedToken, parser.token);
            return diagnostic.code;
        }
        const detail::Token kind_token = parser.token;
        if (!detail::advance_token(parser)) {
            return diagnostic.code;
        }
        ShaderType type{};
        if (!detail::binding_type(parser.token, type)) {
            (void)detail::fail(parser, ShaderError::UnknownType, parser.token);
            return diagnostic.code;
        }
        if (!detail::advance_token(parser)) {
            return diagnostic.code;
        }
        if (parser.token.kind != detail::TokenKind::Identifier) {
            (void)detail::fail(parser, ShaderError::InvalidName, parser.token);
            return diagnostic.code;
        }
        const detail::Token name_token = parser.token;
        if (detail::duplicate_binding(out, name_token.name)) {
            (void)detail::fail(parser, ShaderError::DuplicateBinding, name_token);
            return diagnostic.code;
        }
        u32 kind_count = 0;
        if (kind == BindingKind::Input) {
            kind_count = input_count;
        } else if (kind == BindingKind::Output) {
            kind_count = output_count;
        } else {
            kind_count = uniform_count;
        }
        const u32 kind_limit = kind == BindingKind::Input ? kMaxInputs
            : (kind == BindingKind::Output ? kMaxOutputs : kMaxUniforms);
        if (out.binding_count >= kMaxBindings || kind_count >= kind_limit) {
            (void)detail::fail(parser, ShaderError::CapacityFull, name_token);
            return diagnostic.code;
        }
        if (kind == BindingKind::Input) {
            ++input_count;
        } else if (kind == BindingKind::Output) {
            ++output_count;
        } else {
            ++uniform_count;
        }
        out.bindings[out.binding_count] =
            Binding{name_token.name, type, kind};
        ++out.binding_count;
        if (kind != BindingKind::Uniform && !restricted) {
            restricted_token = kind_token;
            restricted = true;
        }
        if (!detail::advance_token(parser)) {
            return diagnostic.code;
        }
        if (!detail::expect(parser, detail::TokenKind::Semicolon,
                            ShaderError::UnexpectedToken)) {
            return diagnostic.code;
        }
        if (!detail::advance_token(parser)) {
            return diagnostic.code;
        }
    }

    if (!stage_seen) {
        (void)detail::fail(parser, ShaderError::MissingStage, parser.token);
        return diagnostic.code;
    }
    if (stage == ShaderStage::Compute && restricted) {
        (void)detail::fail(parser, ShaderError::StageRestriction,
                           restricted_token);
        return diagnostic.code;
    }
    if (!detail::advance_token(parser)) {
        return diagnostic.code;
    }
    if (parser.token.kind != detail::TokenKind::End) {
        (void)detail::fail(parser, ShaderError::UnexpectedToken, parser.token);
        return diagnostic.code;
    }

    out.stage = stage;
    out.source_fingerprint = detail::shader_fnv1a64(source);
    out.source_lines = line_count;
    return ShaderError::None;
}

}  // namespace stormline::graphics::shader

#endif  // STORMLINE_GRAPHICS_SHADER_SHADER_PARSER_HPP
