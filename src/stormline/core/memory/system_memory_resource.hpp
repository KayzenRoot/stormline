#pragma once

#include <cstddef>
#include <memory_resource>

namespace stormline::core::memory {

class SystemMemoryResource final : public std::pmr::memory_resource {
public:
    SystemMemoryResource() noexcept = default;
    ~SystemMemoryResource() override = default;

    SystemMemoryResource(const SystemMemoryResource&) = delete;
    SystemMemoryResource& operator=(const SystemMemoryResource&) = delete;
    SystemMemoryResource(SystemMemoryResource&&) = delete;
    SystemMemoryResource& operator=(SystemMemoryResource&&) = delete;

private:
    void* do_allocate(std::size_t bytes, std::size_t alignment) override;
    void do_deallocate(void* pointer, std::size_t bytes, std::size_t alignment) override;
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override;
};

}  // namespace stormline::core::memory
