#include "stormline/core/memory/system_memory_resource.hpp"

#include <new>

namespace stormline::core::memory {
namespace {

constexpr bool is_power_of_two(std::size_t value) noexcept {
    return value != 0 && (value & (value - 1)) == 0;
}

std::size_t effective_size(std::size_t bytes) noexcept {
    return bytes == 0 ? 1 : bytes;
}

bool uses_aligned_new(std::size_t alignment) noexcept {
    return alignment > alignof(std::max_align_t);
}

}  // namespace

void* SystemMemoryResource::do_allocate(std::size_t bytes, std::size_t alignment) {
    const std::size_t size = effective_size(bytes);
    if (!is_power_of_two(alignment)) {
        alignment = alignof(std::max_align_t);
    }
    if (uses_aligned_new(alignment)) {
        return ::operator new(size, std::align_val_t(alignment));
    }
    return ::operator new(size);
}

void SystemMemoryResource::do_deallocate(void* pointer, std::size_t bytes,
                                          std::size_t alignment) {
    (void)bytes;
    if (pointer == nullptr) {
        return;
    }
    if (!is_power_of_two(alignment)) {
        alignment = alignof(std::max_align_t);
    }
    if (uses_aligned_new(alignment)) {
        ::operator delete(pointer, std::align_val_t(alignment));
    } else {
        ::operator delete(pointer);
    }
}

bool SystemMemoryResource::do_is_equal(
    const std::pmr::memory_resource& other) const noexcept {
    return this == &other;
}

}  // namespace stormline::core::memory
