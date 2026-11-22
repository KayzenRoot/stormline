#include "stormline/data/import/import_receipt.hpp"

#include <cstdio>
#include <limits>
#include <string_view>

namespace {
using namespace stormline::data::imports;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

[[nodiscard]] ImportReceipt receipt(u64 operation, u64 asset) {
    ImportReceipt value{};
    value.operation_id = operation;
    value.asset = registry::AssetId{0, asset};
    value.importer_id = 1;
    value.importer_version = 1;
    value.format = FormatId::Png;
    value.source_fingerprint = 42;
    value.artifact_count = 1;
    value.warning_count = 1;
    value.validation = ValidationStatus::Valid;
    return value;
}

bool run_rec01() {
    begin();
    ReceiptLog log;
    expect(log.add(receipt(1, 1)) == ImportError::None, "add");
    ImportReceipt found{};
    expect(log.find(1, found) == ImportError::None && found.asset.low == 1
           && found.format == FormatId::Png, "find");
    expect(log.size() == 1 && log.warning_total() == 1, "counts");
    expect(log.add(receipt(1, 2)) == ImportError::DuplicateReceipt, "duplicate");
    expect(log.find(2, found) == ImportError::NotFound, "missing");

    ImportReceipt invalid = receipt(2, 2);
    invalid.operation_id = 0;
    expect(log.add(invalid) == ImportError::InvalidArgument, "zero op");
    invalid = receipt(2, 2);
    invalid.asset = registry::AssetId{};
    expect(log.add(invalid) == ImportError::InvalidArgument, "zero asset");
    invalid = receipt(2, 2);
    invalid.format = FormatId::Unknown;
    expect(log.add(invalid) == ImportError::InvalidArgument, "unknown format");
    invalid = receipt(2, 2);
    invalid.importer_id = 0;
    expect(log.add(invalid) == ImportError::InvalidArgument, "zero importer");
    invalid = receipt(2, 2);
    invalid.artifact_count = 0;
    expect(log.add(invalid) == ImportError::InvalidArgument, "zero artifacts");
    invalid = receipt(2, 2);
    invalid.artifact_count = 9;
    expect(log.add(invalid) == ImportError::InvalidArgument, "too many artifacts");

    ReceiptLog full;
    for (u32 index = 0; index < kMaxReceipts; ++index) {
        expect(full.add(receipt(index + 1, index + 1)) == ImportError::None, "fill");
    }
    expect(full.size() == kMaxReceipts, "capacity");
    expect(full.warning_total() == kMaxReceipts, "warning sum");
    expect(full.add(receipt(1000, 1000)) == ImportError::CapacityFull, "capacity full");

    ReceiptLog saturated;
    ImportReceipt big = receipt(1, 1);
    big.warning_count = std::numeric_limits<u32>::max();
    expect(saturated.add(big) == ImportError::None, "saturate first");
    big = receipt(2, 2);
    big.warning_count = 1;
    expect(saturated.add(big) == ImportError::None, "saturate second");
    expect(saturated.warning_total() == std::numeric_limits<u32>::max(), "saturated");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_data03_receipt_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "rec01") { success = run_rec01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
