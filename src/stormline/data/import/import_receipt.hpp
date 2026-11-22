#ifndef STORMLINE_DATA_IMPORT_IMPORT_RECEIPT_HPP
#define STORMLINE_DATA_IMPORT_IMPORT_RECEIPT_HPP

#include "stormline/data/import/import_types.hpp"
#include "stormline/data/registry/registry_types.hpp"

#include <array>
#include <limits>

namespace stormline::data::imports {

namespace registry = stormline::data::registry;

struct ImportReceipt {
    u64 operation_id{0};
    registry::AssetId asset{};
    u32 importer_id{0};
    u32 importer_version{0};
    FormatId format{FormatId::Unknown};
    u64 source_fingerprint{0};
    u32 artifact_count{0};
    u32 warning_count{0};
    ValidationStatus validation{ValidationStatus::Invalid};
};

class ReceiptLog final {
public:
    ReceiptLog() noexcept = default;

    [[nodiscard]] ImportError add(const ImportReceipt& receipt) noexcept {
        if (receipt.operation_id == 0 || !registry::valid(receipt.asset)
            || receipt.format == FormatId::Unknown || receipt.importer_id == 0
            || receipt.importer_version == 0 || receipt.artifact_count == 0
            || receipt.artifact_count > 8) {
            return ImportError::InvalidArgument;
        }
        for (u32 index = 0; index < size_; ++index) {
            if (receipts_[index].operation_id == receipt.operation_id) {
                return ImportError::DuplicateReceipt;
            }
        }
        if (size_ >= kMaxReceipts) {
            return ImportError::CapacityFull;
        }
        receipts_[size_] = receipt;
        ++size_;
        const u64 total = static_cast<u64>(warning_total_) + receipt.warning_count;
        warning_total_ = total > std::numeric_limits<u32>::max()
            ? std::numeric_limits<u32>::max()
            : static_cast<u32>(total);
        return ImportError::None;
    }

    [[nodiscard]] ImportError find(u64 operation_id, ImportReceipt& out) const noexcept {
        for (u32 index = 0; index < size_; ++index) {
            if (receipts_[index].operation_id == operation_id) {
                out = receipts_[index];
                return ImportError::None;
            }
        }
        return ImportError::NotFound;
    }

    [[nodiscard]] u32 size() const noexcept { return size_; }
    [[nodiscard]] u32 warning_total() const noexcept { return warning_total_; }

private:
    std::array<ImportReceipt, kMaxReceipts> receipts_{};
    u32 size_{0};
    u32 warning_total_{0};
};

}  // namespace stormline::data::imports

#endif  // STORMLINE_DATA_IMPORT_IMPORT_RECEIPT_HPP
