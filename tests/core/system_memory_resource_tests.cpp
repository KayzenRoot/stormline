#include "stormline/core/memory/memory_block.hpp"
#include "stormline/core/memory/system_memory_resource.hpp"

#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <memory_resource>
#include <string_view>
#include <thread>

namespace {

using stormline::core::memory::MemoryBlock;
using stormline::core::memory::MemoryDomain;
using stormline::core::memory::MemoryError;
using stormline::core::memory::SystemMemoryResource;

int failures = 0;

void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}

void begin_case() {
    failures = 0;
}

bool finish_case() {
    return failures == 0;
}

bool is_aligned(const void* pointer, std::size_t alignment) {
    return reinterpret_cast<std::uintptr_t>(pointer) % alignment == 0;
}

bool run_basic() {
    begin_case();
    SystemMemoryResource resource;
    void* pointer = resource.allocate(256, 64);
    expect(pointer != nullptr, "basic allocation succeeds");
    expect(is_aligned(pointer, 64), "basic allocation is aligned");
    std::memset(pointer, 0x5a, 256);
    expect(static_cast<std::byte*>(pointer)[0] == std::byte{0x5a}, "basic allocation is writable");
    resource.deallocate(pointer, 256, 64);

    void* zero = resource.allocate(0, 16);
    expect(zero != nullptr, "zero-byte allocation returns a pointer");
    resource.deallocate(zero, 0, 16);

    SystemMemoryResource other;
    expect(resource.is_equal(resource), "resource equals itself");
    expect(!resource.is_equal(other), "distinct resources are not equal");
    return finish_case();
}

bool run_alignment() {
    begin_case();
    SystemMemoryResource resource;
    for (std::size_t alignment : {std::size_t{1}, std::size_t{8}, std::size_t{16},
                                  std::size_t{32}, std::size_t{64}, std::size_t{128},
                                  std::size_t{4096}}) {
        void* pointer = resource.allocate(64, alignment);
        expect(pointer != nullptr, "alignment allocation succeeds");
        expect(is_aligned(pointer, alignment), "requested alignment is honored");
        resource.deallocate(pointer, 64, alignment);
    }
    return finish_case();
}

bool run_block() {
    begin_case();
    SystemMemoryResource resource;
    MemoryBlock block;
    expect(MemoryBlock::allocate(&resource, 128, 64, MemoryDomain::Persistent, block)
               == MemoryError::None,
           "MemoryBlock uses the system resource");
    expect(block.valid(), "block is valid");
    expect(block.size() == 128, "block size");
    expect(block.alignment() == 64, "block alignment");
    expect(is_aligned(block.data(), 64), "block pointer alignment");
    std::memset(block.data(), 0x33, block.size());
    expect(block.release() == MemoryError::None, "block release succeeds");
    expect(!block.valid(), "block invalid after release");
    return finish_case();
}

bool run_lifetime() {
    begin_case();
    SystemMemoryResource resource;
    bool ok = true;
    for (int cycle = 0; cycle < 10000 && ok; ++cycle) {
        const std::size_t bytes = 16 + (static_cast<std::size_t>(cycle) % 17) * 64;
        const std::size_t alignment = (cycle % 3 == 0) ? 64 : 16;
        void* pointer = resource.allocate(bytes, alignment);
        ok = pointer != nullptr && is_aligned(pointer, alignment);
        resource.deallocate(pointer, bytes, alignment);
    }
    expect(ok, "10000 system allocations/deallocations succeed");
    return finish_case();
}

bool run_cross_thread() {
    begin_case();
    SystemMemoryResource resource;
    void* pointer = resource.allocate(128, 64);
    expect(pointer != nullptr, "cross-thread allocation succeeds");
    std::thread worker([&resource, pointer] { resource.deallocate(pointer, 128, 64); });
    worker.join();
    return finish_case();
}

bool run_benchmark() {
    begin_case();
    SystemMemoryResource system;
    std::pmr::memory_resource* pmr = std::pmr::new_delete_resource();
    constexpr int iterations = 50000;
    constexpr std::array<std::size_t, 5> sizes{16, 64, 256, 4096, 65536};
    volatile std::uintptr_t sink = 0;

    std::uint64_t system_ns = 0;
    std::uint64_t pmr_ns = 0;
    std::uint64_t new_ns = 0;
    std::uint64_t malloc_ns = 0;

    for (std::size_t size : sizes) {
        const auto t0 = std::chrono::steady_clock::now();
        for (int index = 0; index < iterations; ++index) {
            void* pointer = system.allocate(size, 16);
            sink += reinterpret_cast<std::uintptr_t>(pointer);
            system.deallocate(pointer, size, 16);
        }
        const auto t1 = std::chrono::steady_clock::now();
        system_ns += static_cast<std::uint64_t>(
            std::chrono::duration_cast<std::chrono::nanoseconds>(t1 - t0).count());

        const auto t2 = std::chrono::steady_clock::now();
        for (int index = 0; index < iterations; ++index) {
            void* pointer = pmr->allocate(size, 16);
            sink += reinterpret_cast<std::uintptr_t>(pointer);
            pmr->deallocate(pointer, size, 16);
        }
        const auto t3 = std::chrono::steady_clock::now();
        pmr_ns += static_cast<std::uint64_t>(
            std::chrono::duration_cast<std::chrono::nanoseconds>(t3 - t2).count());

        const auto t4 = std::chrono::steady_clock::now();
        for (int index = 0; index < iterations; ++index) {
            void* pointer = ::operator new(size);
            sink += reinterpret_cast<std::uintptr_t>(pointer);
            ::operator delete(pointer);
        }
        const auto t5 = std::chrono::steady_clock::now();
        new_ns += static_cast<std::uint64_t>(
            std::chrono::duration_cast<std::chrono::nanoseconds>(t5 - t4).count());

        const auto t6 = std::chrono::steady_clock::now();
        for (int index = 0; index < iterations; ++index) {
            void* pointer = std::malloc(size);
            sink += reinterpret_cast<std::uintptr_t>(pointer);
            std::free(pointer);
        }
        const auto t7 = std::chrono::steady_clock::now();
        malloc_ns += static_cast<std::uint64_t>(
            std::chrono::duration_cast<std::chrono::nanoseconds>(t7 - t6).count());
    }

    const double total_ops = static_cast<double>(iterations) * sizes.size();
    std::printf("SYSTEM_ALLOC_BENCHMARK system_ns_op=%.3f pmr_ns_op=%.3f new_ns_op=%.3f "
                "malloc_ns_op=%.3f",
                static_cast<double>(system_ns) / total_ops,
                static_cast<double>(pmr_ns) / total_ops,
                static_cast<double>(new_ns) / total_ops,
                static_cast<double>(malloc_ns) / total_ops);
    expect(sink != 0, "benchmark observed allocations");
    return finish_case();
}

}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr,
                     "usage: %s <basic|alignment|block|lifetime|cross_thread|benchmark>\n",
                     argv[0]);
        return 2;
    }

    const std::string_view mode(argv[1]);
    if (mode == "basic") {
        return run_basic() ? 0 : 1;
    }
    if (mode == "alignment") {
        return run_alignment() ? 0 : 1;
    }
    if (mode == "block") {
        return run_block() ? 0 : 1;
    }
    if (mode == "lifetime") {
        return run_lifetime() ? 0 : 1;
    }
    if (mode == "cross_thread") {
        return run_cross_thread() ? 0 : 1;
    }
    if (mode == "benchmark") {
        return run_benchmark() ? 0 : 1;
    }

    std::fprintf(stderr, "unknown mode: %s\n", argv[1]);
    return 2;
}
