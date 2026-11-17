#include "stormline/core/memory/memory_block.hpp"

#include <new>
#include <utility>

namespace stormline::core::memory {
namespace {

constexpr bool is_power_of_two(std::size_t value) noexcept {
    return value != 0 && (value & (value - 1)) == 0;
}

bool is_aligned(const void* pointer, std::size_t alignment) noexcept {
    return reinterpret_cast<std::uintptr_t>(pointer) % alignment == 0;
}

}  // namespace

MemoryBlock::~MemoryBlock() noexcept {
    (void)release();
}

MemoryBlock::MemoryBlock(std::pmr::memory_resource* resource, void* data, std::size_t bytes,
                         std::size_t alignment, MemoryDomain domain) noexcept
    : resource_(resource),
      data_(data),
      bytes_(bytes),
      alignment_(alignment),
      domain_(domain) {}

MemoryBlock::MemoryBlock(MemoryBlock&& other) noexcept
    : resource_(other.resource_),
      data_(other.data_),
      bytes_(other.bytes_),
      alignment_(other.alignment_),
      domain_(other.domain_) {
    other.resource_ = nullptr;
    other.data_ = nullptr;
    other.bytes_ = 0;
    other.alignment_ = 0;
    other.domain_ = MemoryDomain::Persistent;
}

MemoryBlock& MemoryBlock::operator=(MemoryBlock&& other) noexcept {
    if (this == &other) {
        return *this;
    }
    (void)release();
    resource_ = other.resource_;
    data_ = other.data_;
    bytes_ = other.bytes_;
    alignment_ = other.alignment_;
    domain_ = other.domain_;
    other.resource_ = nullptr;
    other.data_ = nullptr;
    other.bytes_ = 0;
    other.alignment_ = 0;
    other.domain_ = MemoryDomain::Persistent;
    return *this;
}

MemoryError MemoryBlock::allocate(std::pmr::memory_resource* resource,
                                  std::size_t bytes,
                                  std::size_t alignment,
                                  MemoryDomain domain,
                                  MemoryBlock& out) noexcept {
    if (out.valid()) {
        return MemoryError::AlreadyOwned;
    }
    if (bytes == 0) {
        return MemoryError::InvalidSize;
    }
    if (!is_power_of_two(alignment)) {
        return MemoryError::InvalidAlignment;
    }

    std::pmr::memory_resource* const selected =
        resource != nullptr ? resource : std::pmr::new_delete_resource();
    void* data = nullptr;
    try {
        data = selected->allocate(bytes, alignment);
    } catch (const std::bad_alloc&) {
        return MemoryError::OutOfMemory;
    } catch (...) {
        return MemoryError::InternalFailure;
    }
    if (data == nullptr) {
        return MemoryError::OutOfMemory;
    }
    if (!is_aligned(data, alignment)) {
        try {
            selected->deallocate(data, bytes, alignment);
        } catch (...) {
            // The block was never handed out; preserve the single-release invariant.
        }
        return MemoryError::InternalFailure;
    }

    out = MemoryBlock(selected, data, bytes, alignment, domain);
    return MemoryError::None;
}

MemoryError MemoryBlock::release() noexcept {
    if (data_ == nullptr) {
        return MemoryError::None;
    }

    std::pmr::memory_resource* const resource = resource_;
    void* const data = data_;
    const std::size_t bytes = bytes_;
    const std::size_t alignment = alignment_;

    resource_ = nullptr;
    data_ = nullptr;
    bytes_ = 0;
    alignment_ = 0;
    domain_ = MemoryDomain::Persistent;

    try {
        resource->deallocate(data, bytes, alignment);
    } catch (...) {
        return MemoryError::InternalFailure;
    }
    return MemoryError::None;
}

std::byte* MemoryBlock::data() noexcept {
    return static_cast<std::byte*>(data_);
}

const std::byte* MemoryBlock::data() const noexcept {
    return static_cast<const std::byte*>(data_);
}

std::size_t MemoryBlock::size() const noexcept {
    return bytes_;
}

std::size_t MemoryBlock::alignment() const noexcept {
    return alignment_;
}

MemoryDomain MemoryBlock::domain() const noexcept {
    return domain_;
}

bool MemoryBlock::valid() const noexcept {
    return data_ != nullptr;
}

MemoryBlock::operator bool() const noexcept {
    return valid();
}

}  // namespace stormline::core::memory
