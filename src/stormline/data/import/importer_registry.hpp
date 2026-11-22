#ifndef STORMLINE_DATA_IMPORT_IMPORTER_REGISTRY_HPP
#define STORMLINE_DATA_IMPORT_IMPORTER_REGISTRY_HPP

#include "stormline/data/import/import_types.hpp"
#include "stormline/data/vfs/vfs_path.hpp"

#include <array>
#include <span>

namespace stormline::data::imports {

class ImporterRegistry final {
public:
    ImporterRegistry() noexcept = default;

    [[nodiscard]] ImportError add(const ImporterDescriptor& descriptor) noexcept {
        if (descriptor.importer_id == 0 || descriptor.version == 0
            || descriptor.format == FormatId::Unknown
            || descriptor.artifact == ArtifactType::Unknown
            || descriptor.extension_length == 0
            || descriptor.extension_length > descriptor.extension.size()) {
            return ImportError::InvalidArgument;
        }
        for (u32 index = 0; index < descriptor.extension_length; ++index) {
            const char byte = descriptor.extension[index];
            const bool alpha = (byte >= 'a' && byte <= 'z')
                || (byte >= 'A' && byte <= 'Z') || (byte >= '0' && byte <= '9');
            if (!alpha && byte != '.' && byte != '-' && byte != '_') {
                return ImportError::InvalidArgument;
            }
        }
        for (u32 index = 0; index < size_; ++index) {
            if (descriptors_[index].importer_id == descriptor.importer_id
                || descriptors_[index].format == descriptor.format) {
                return ImportError::DuplicateImporter;
            }
        }
        if (size_ >= kMaxImporters) {
            return ImportError::CapacityFull;
        }
        descriptors_[size_] = descriptor;
        ++size_;
        return ImportError::None;
    }

    [[nodiscard]] ImportError find(
        FormatId format, ImporterDescriptor& out) const noexcept {
        if (format == FormatId::Unknown) {
            return ImportError::InvalidArgument;
        }
        for (u32 index = 0; index < size_; ++index) {
            if (descriptors_[index].format == format) {
                out = descriptors_[index];
                return ImportError::None;
            }
        }
        return ImportError::NotFound;
    }

    [[nodiscard]] ImportError sniff(
        std::span<const u8> signature, FormatId& out) const noexcept {
        out = FormatId::Unknown;
        if (signature.empty()) {
            return ImportError::SignatureTruncated;
        }
        const auto match = [&](std::span<const u8> magic) {
            const u32 available = static_cast<u32>(signature.size());
            const u32 required = static_cast<u32>(magic.size());
            const u32 limit = available < required ? available : required;
            for (u32 index = 0; index < limit; ++index) {
                if (signature[index] != magic[index]) {
                    return 0;
                }
            }
            return available >= required ? 2 : 1;
        };
        static constexpr u8 png[] = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};
        static constexpr u8 jpeg[] = {0xFF, 0xD8, 0xFF};
        static constexpr u8 glb[] = {0x67, 0x6C, 0x54, 0x46};
        static constexpr u8 riff[] = {0x52, 0x49, 0x46, 0x46};
        static constexpr u8 wave[] = {0x57, 0x41, 0x56, 0x45};
        const u32 png_match = match(std::span<const u8>(png, sizeof(png)));
        if (png_match == 2) {
            out = FormatId::Png;
            return ImportError::None;
        }
        if (png_match == 1) {
            return ImportError::SignatureTruncated;
        }
        const u32 jpeg_match = match(std::span<const u8>(jpeg, sizeof(jpeg)));
        if (jpeg_match == 2) {
            out = FormatId::Jpeg;
            return ImportError::None;
        }
        if (jpeg_match == 1) {
            return ImportError::SignatureTruncated;
        }
        const u32 glb_match = match(std::span<const u8>(glb, sizeof(glb)));
        if (glb_match == 2) {
            out = FormatId::Glb;
            return ImportError::None;
        }
        if (glb_match == 1) {
            return ImportError::SignatureTruncated;
        }
        const u32 riff_match = match(std::span<const u8>(riff, sizeof(riff)));
        if (riff_match == 0) {
            return ImportError::UnknownFormat;
        }
        if (riff_match == 1 || signature.size() < 12) {
            return ImportError::SignatureTruncated;
        }
        for (u32 index = 0; index < 4; ++index) {
            if (signature[8 + index] != wave[index]) {
                return ImportError::UnknownFormat;
            }
        }
        out = FormatId::Wav;
        return ImportError::None;
    }

    struct ImportRequest {
        vfs::VfsPath source{};
        FormatId declared_format{FormatId::Unknown};
        std::span<const u8> signature{};
    };

    struct ImportPlan {
        FormatId detected{FormatId::Unknown};
        u32 importer_id{0};
        u32 importer_version{0};
        ArtifactType artifact{ArtifactType::Unknown};
    };

    [[nodiscard]] ImportError plan(
        const ImportRequest& request, ImportPlan& out) const noexcept {
        if (request.source.length == 0
            || request.source.length > vfs::kMaxPathBytes) {
            return ImportError::InvalidPath;
        }
        vfs::VfsPath normalized{};
        if (vfs::make_path(vfs::view(request.source), normalized) != vfs::VfsError::None) {
            return ImportError::InvalidPath;
        }
        FormatId detected = FormatId::Unknown;
        const ImportError sniff_status = sniff(request.signature, detected);
        if (sniff_status != ImportError::None) {
            return sniff_status;
        }
        if (request.declared_format != FormatId::Unknown
            && request.declared_format != detected) {
            return ImportError::UnsupportedFormat;
        }
        ImporterDescriptor descriptor{};
        const ImportError find_status = find(detected, descriptor);
        if (find_status != ImportError::None) {
            return find_status;
        }
        out = ImportPlan{detected, descriptor.importer_id, descriptor.version,
                         descriptor.artifact};
        return ImportError::None;
    }

    [[nodiscard]] u32 size() const noexcept { return size_; }

private:
    std::array<ImporterDescriptor, kMaxImporters> descriptors_{};
    u32 size_{0};
};

}  // namespace stormline::data::imports

#endif  // STORMLINE_DATA_IMPORT_IMPORTER_REGISTRY_HPP
