#include "stormline/data/import/import_receipt.hpp"
#include "stormline/data/import/import_validation.hpp"
#include "stormline/data/import/importer_registry.hpp"

#include <array>
#include <cstdio>
#include <string>
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
    u32 id, FormatId format, ArtifactType artifact, std::string_view extension) {
    ImporterDescriptor value{};
    value.importer_id = id;
    value.version = 1;
    value.format = format;
    value.artifact = artifact;
    value.extension_length = static_cast<u32>(extension.size());
    for (u32 index = 0; index < value.extension_length; ++index) {
        value.extension[index] = extension[index];
    }
    return value;
}

[[nodiscard]] ImportReceipt receipt(u64 operation, u64 asset) {
    ImportReceipt value{};
    value.operation_id = operation;
    value.asset = registry::AssetId{0, asset};
    value.importer_id = 1;
    value.importer_version = 1;
    value.format = FormatId::Png;
    value.artifact_count = 1;
    value.warning_count = 1;
    value.validation = ValidationStatus::Valid;
    return value;
}

bool run_qlf_i01() {
    begin();
    ImporterRegistry importers;
    expect(importers.add(descriptor(1, FormatId::Png, ArtifactType::Texture2D, "png"))
           == ImportError::None, "descriptor");
    const std::array<std::uint8_t, 8> png{
        0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};
    vfs::VfsPath source{};
    expect(vfs::make_path("assets/hero.png", source) == vfs::VfsError::None, "path");
    ImporterRegistry::ImportRequest request{source, FormatId::Unknown, png};
    ImporterRegistry::ImportPlan plan{};
    expect(importers.plan(request, plan) == ImportError::None, "plan");
    expect(plan.detected == FormatId::Png && plan.importer_id == 1, "plan value");

    ArtifactMetadata metadata{};
    metadata.type = ArtifactType::Texture2D;
    metadata.texture = TextureMetadata{64, 64, 7, 4, true};
    ValidationResult validation{};
    expect(validate_artifact(metadata, validation) == ImportError::None, "validate");
    expect(validation.status == ValidationStatus::Valid, "validation status");

    ReceiptLog log;
    ImportReceipt value = receipt(1, 1);
    value.validation = validation.status;
    value.warning_count = validation.warning_count;
    expect(log.add(value) == ImportError::None, "receipt");
    ImportReceipt found{};
    expect(log.find(1, found) == ImportError::None && found.format == FormatId::Png,
           "receipt find");
    return finish();
}

struct Snapshot {
    FormatId detected{FormatId::Unknown};
    u32 importer{0};
    ValidationStatus validation{ValidationStatus::Invalid};
    u32 warnings{0};
    bool receipt_found{false};
};

[[nodiscard]] bool snapshot(Snapshot& out) {
    ImporterRegistry importers;
    if (importers.add(descriptor(1, FormatId::Png, ArtifactType::Texture2D, "png"))
        != ImportError::None) {
        return false;
    }
    const std::array<std::uint8_t, 8> png{
        0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};
    vfs::VfsPath source{};
    if (vfs::make_path("assets/hero.png", source) != vfs::VfsError::None) {
        return false;
    }
    ImporterRegistry::ImportRequest request{source, FormatId::Png, png};
    ImporterRegistry::ImportPlan plan{};
    if (importers.plan(request, plan) != ImportError::None) {
        return false;
    }
    out.detected = plan.detected;
    out.importer = plan.importer_id;
    ArtifactMetadata metadata{};
    metadata.type = ArtifactType::Texture2D;
    metadata.texture = TextureMetadata{100, 64, 7, 4, true};
    ValidationResult validation{};
    if (validate_artifact(metadata, validation) != ImportError::None) {
        return false;
    }
    out.validation = validation.status;
    out.warnings = validation.warning_count;
    ReceiptLog log;
    if (log.add(receipt(1, 1)) != ImportError::None) {
        return false;
    }
    ImportReceipt found{};
    out.receipt_found = log.find(1, found) == ImportError::None;
    return true;
}

bool run_qlf_i02() {
    begin();
    Snapshot first{};
    Snapshot second{};
    expect(snapshot(first), "first");
    expect(snapshot(second), "second");
    expect(first.detected == second.detected, "repeat format");
    expect(first.importer == second.importer, "repeat importer");
    expect(first.validation == second.validation, "repeat validation");
    expect(first.warnings == second.warnings, "repeat warnings");
    expect(first.receipt_found == second.receipt_found, "repeat receipt");
    return finish();
}

bool run_qlf_i03() {
    begin();
    ImporterRegistry importers;
    expect(importers.add(descriptor(1, FormatId::Png, ArtifactType::Texture2D, "png"))
           == ImportError::None, "add");
    const std::array<std::uint8_t, 8> png{
        0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};
    vfs::VfsPath source{};
    expect(vfs::make_path("a.png", source) == vfs::VfsError::None, "path");
    const std::array<std::uint8_t, 2> unknown{0x00, 0x01};
    ImporterRegistry::ImportRequest request{source, FormatId::Unknown, unknown};
    ImporterRegistry::ImportPlan plan{};
    expect(importers.plan(request, plan) == ImportError::UnknownFormat, "unknown");
    request.signature = png;
    expect(importers.plan(request, plan) == ImportError::None, "after unknown");

    ArtifactMetadata metadata{};
    metadata.type = ArtifactType::Texture2D;
    metadata.texture = TextureMetadata{0, 64, 0, 4, true};
    ValidationResult validation{};
    expect(validate_artifact(metadata, validation) == ImportError::InvalidTexture, "bad tex");
    metadata.texture = TextureMetadata{64, 64, 7, 4, true};
    expect(validate_artifact(metadata, validation) == ImportError::None, "after bad tex");

    ReceiptLog log;
    expect(log.add(receipt(1, 1)) == ImportError::None, "receipt");
    expect(log.add(receipt(1, 2)) == ImportError::DuplicateReceipt, "duplicate receipt");
    expect(log.add(receipt(2, 2)) == ImportError::None, "after duplicate");
    return finish();
}

bool run_qlf_i04() {
    begin();
    ImporterRegistry importers;
    u32 added = 0;
    for (u32 index = 0; index < 10000; ++index) {
        const FormatId format = static_cast<FormatId>(index % 5);
        const ImportError status = importers.add(
            descriptor(index + 1, format, ArtifactType::Texture2D, "png"));
        if (status == ImportError::None) {
            ++added;
        } else {
            expect(status == ImportError::DuplicateImporter
                   || status == ImportError::InvalidArgument, "descriptor overload");
        }
    }
    expect(added == 4, "descriptor count");

    const std::array<std::uint8_t, 8> png{
        0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};
    vfs::VfsPath source{};
    expect(vfs::make_path("a.png", source) == vfs::VfsError::None, "path");
    ImporterRegistry::ImportRequest request{source, FormatId::Unknown, png};
    for (u32 index = 0; index < 10000; ++index) {
        ImporterRegistry::ImportPlan plan{};
        expect(importers.plan(request, plan) == ImportError::None, "plan overload");
    }

    ArtifactMetadata metadata{};
    metadata.type = ArtifactType::Texture2D;
    metadata.texture = TextureMetadata{64, 64, 7, 4, true};
    for (u32 index = 0; index < 10000; ++index) {
        ValidationResult validation{};
        expect(validate_artifact(metadata, validation) == ImportError::None,
               "validate overload");
    }

    ReceiptLog log;
    u32 receipts = 0;
    for (u32 index = 0; index < 10000; ++index) {
        const ImportError status = log.add(receipt(index + 1, index + 1));
        if (status == ImportError::None) {
            ++receipts;
        } else {
            expect(status == ImportError::CapacityFull, "receipt overload");
        }
    }
    expect(receipts == kMaxReceipts, "receipt capacity");
    expect(log.size() == kMaxReceipts, "receipt size");
    expect(log.warning_total() == kMaxReceipts, "warning stable");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_data03_import_qualification_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "qlf01") { success = run_qlf_i01(); }
    else if (mode == "qlf02") { success = run_qlf_i02(); }
    else if (mode == "qlf03") { success = run_qlf_i03(); }
    else if (mode == "qlf04") { success = run_qlf_i04(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
