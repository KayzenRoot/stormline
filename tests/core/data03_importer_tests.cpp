#include "stormline/data/import/importer_registry.hpp"

#include <array>
#include <cstdio>
#include <string_view>

namespace {
using namespace stormline::data::imports;
namespace vfs = stormline::data::vfs;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

[[nodiscard]] ImporterDescriptor descriptor(
    u32 id, u32 version, FormatId format, ArtifactType artifact, std::string_view extension) {
    ImporterDescriptor value{};
    value.importer_id = id;
    value.version = version;
    value.format = format;
    value.artifact = artifact;
    value.extension_length = static_cast<u32>(extension.size());
    for (u32 index = 0; index < value.extension_length; ++index) {
        value.extension[index] = extension[index];
    }
    return value;
}

bool run_imp01() {
    begin();
    ImporterRegistry registry;
    const std::array<std::uint8_t, 8> png{0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};
    const std::array<std::uint8_t, 3> jpeg{0xFF, 0xD8, 0xFF};
    const std::array<std::uint8_t, 4> glb{0x67, 0x6C, 0x54, 0x46};
    const std::array<std::uint8_t, 12> wav{
        0x52, 0x49, 0x46, 0x46, 0x00, 0x00, 0x00, 0x00, 0x57, 0x41, 0x56, 0x45};
    expect(registry.add(descriptor(1, 1, FormatId::Png, ArtifactType::Texture2D, "png"))
           == ImportError::None, "png");
    expect(registry.add(descriptor(2, 1, FormatId::Jpeg, ArtifactType::Texture2D, "jpg"))
           == ImportError::None, "jpeg");
    expect(registry.add(descriptor(3, 1, FormatId::Glb, ArtifactType::Mesh, "glb"))
           == ImportError::None, "glb");
    expect(registry.add(descriptor(4, 1, FormatId::Wav, ArtifactType::Audio, "wav"))
           == ImportError::None, "wav");
    expect(registry.add(descriptor(5, 2, FormatId::Png, ArtifactType::Texture2D, "png"))
           == ImportError::DuplicateImporter, "duplicate format");
    expect(registry.add(descriptor(1, 2, FormatId::Glb, ArtifactType::Mesh, "glb"))
           == ImportError::DuplicateImporter, "duplicate id");
    expect(registry.add(descriptor(0, 1, FormatId::Png, ArtifactType::Texture2D, "png"))
           == ImportError::InvalidArgument, "invalid id");
    expect(registry.add(descriptor(6, 0, FormatId::Png, ArtifactType::Texture2D, "png"))
           == ImportError::InvalidArgument, "invalid version");
    expect(registry.add(descriptor(7, 1, FormatId::Unknown, ArtifactType::Texture2D, "x"))
           == ImportError::InvalidArgument, "unknown format");
    expect(registry.add(descriptor(7, 1, FormatId::Png, ArtifactType::Unknown, "x"))
           == ImportError::InvalidArgument, "unknown artifact");
    expect(registry.add(descriptor(7, 1, FormatId::Png, ArtifactType::Texture2D, ""))
           == ImportError::InvalidArgument, "empty extension");
    expect(registry.add(descriptor(7, 1, FormatId::Png, ArtifactType::Texture2D, "p g"))
           == ImportError::InvalidArgument, "bad extension");
    expect(registry.size() == 4, "registry size");

    ImporterDescriptor found{};
    expect(registry.find(FormatId::Png, found) == ImportError::None
           && found.importer_id == 1 && found.artifact == ArtifactType::Texture2D, "find");
    expect(registry.find(FormatId::Wav, found) == ImportError::None
           && found.artifact == ArtifactType::Audio, "find wav");
    expect(registry.find(FormatId::Unknown, found) == ImportError::InvalidArgument,
           "find unknown");
    expect(registry.find(FormatId::Wav, found) == ImportError::None, "find after unknown");

    FormatId format = FormatId::Unknown;
    expect(registry.sniff(png, format) == ImportError::None && format == FormatId::Png,
           "sniff png");
    expect(registry.sniff(jpeg, format) == ImportError::None && format == FormatId::Jpeg,
           "sniff jpeg");
    expect(registry.sniff(glb, format) == ImportError::None && format == FormatId::Glb,
           "sniff glb");
    expect(registry.sniff(wav, format) == ImportError::None && format == FormatId::Wav,
           "sniff wav");
    const std::array<std::uint8_t, 4> partial_png{0x89, 0x50, 0x4E, 0x47};
    expect(registry.sniff(partial_png, format) == ImportError::SignatureTruncated,
           "truncated png");
    const std::array<std::uint8_t, 8> partial_wav{
        0x52, 0x49, 0x46, 0x46, 0, 0, 0, 0};
    expect(registry.sniff(partial_wav, format) == ImportError::SignatureTruncated,
           "truncated wav");
    const std::array<std::uint8_t, 12> bad_wav{
        0x52, 0x49, 0x46, 0x46, 0, 0, 0, 0, 0x41, 0x56, 0x49, 0x00};
    expect(registry.sniff(bad_wav, format) == ImportError::UnknownFormat, "bad wav");
    const std::array<std::uint8_t, 2> unknown{0x00, 0x01};
    expect(registry.sniff(unknown, format) == ImportError::UnknownFormat, "unknown");
    expect(registry.sniff(std::span<const std::uint8_t>(), format)
           == ImportError::SignatureTruncated, "empty signature");

    vfs::VfsPath source{};
    expect(vfs::make_path("assets/hero.png", source) == vfs::VfsError::None, "source");
    ImporterRegistry::ImportRequest request{};
    request.source = source;
    request.signature = png;
    ImporterRegistry::ImportPlan plan{};
    expect(registry.plan(request, plan) == ImportError::None, "plan");
    expect(plan.detected == FormatId::Png && plan.importer_id == 1
           && plan.artifact == ArtifactType::Texture2D, "plan values");
    request.declared_format = FormatId::Png;
    expect(registry.plan(request, plan) == ImportError::None, "declared match");
    request.declared_format = FormatId::Jpeg;
    expect(registry.plan(request, plan) == ImportError::UnsupportedFormat, "declared mismatch");
    request.declared_format = FormatId::Unknown;
    request.source = vfs::VfsPath{};
    expect(registry.plan(request, plan) == ImportError::InvalidPath, "empty path");
    request.source = source;
    request.signature = partial_png;
    expect(registry.plan(request, plan) == ImportError::SignatureTruncated, "plan truncated");
    request.signature = png;
    ImporterRegistry empty;
    expect(empty.plan(request, plan) == ImportError::NotFound, "no importer");

    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_data03_importer_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "imp01") { success = run_imp01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
