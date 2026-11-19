#include "stormline/core/memory/system_memory_resource.hpp"

#include <mimalloc.h>
#include <rpmalloc.h>

#include <atomic>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <memory_resource>
#include <new>
#include <string_view>
#include <thread>
#include <vector>

#if defined(_WIN32)
#include <malloc.h>
#endif

namespace {

using stormline::core::memory::SystemMemoryResource;

using AllocFn = void* (*)(void* context, std::size_t size, std::size_t alignment);
using FreeFn = void (*)(void* context, void* pointer, std::size_t size,
                        std::size_t alignment);

struct Allocator final {
    const char* name;
    void* context;
    AllocFn allocate;
    FreeFn deallocate;
};

constexpr std::size_t kDefaultAlignment = alignof(std::max_align_t);
constexpr std::size_t kAligned = 64;

void* malloc_allocate(void*, std::size_t size, std::size_t) {
    return std::malloc(size);
}

void malloc_deallocate(void*, void* pointer, std::size_t, std::size_t) {
    std::free(pointer);
}

void* malloc_aligned_allocate(void*, std::size_t size, std::size_t alignment) {
#if defined(_WIN32)
    return _aligned_malloc(size, alignment);
#else
    const std::size_t rounded = (size + alignment - 1) / alignment * alignment;
    return std::aligned_alloc(alignment, rounded);
#endif
}

void malloc_aligned_deallocate(void*, void* pointer, std::size_t, std::size_t) {
#if defined(_WIN32)
    _aligned_free(pointer);
#else
    std::free(pointer);
#endif
}

void* new_allocate(void*, std::size_t size, std::size_t) {
    return ::operator new(size);
}

void new_deallocate(void*, void* pointer, std::size_t, std::size_t) {
    ::operator delete(pointer);
}

void* new_aligned_allocate(void*, std::size_t size, std::size_t alignment) {
    return ::operator new(size, std::align_val_t(alignment));
}

void new_aligned_deallocate(void*, void* pointer, std::size_t, std::size_t alignment) {
    ::operator delete(pointer, std::align_val_t(alignment));
}

void* pmr_allocate(void* context, std::size_t size, std::size_t alignment) {
    return static_cast<std::pmr::memory_resource*>(context)->allocate(size, alignment);
}

void pmr_deallocate(void* context, void* pointer, std::size_t size, std::size_t alignment) {
    static_cast<std::pmr::memory_resource*>(context)->deallocate(pointer, size, alignment);
}

void* mi_allocate(void*, std::size_t size, std::size_t) {
    return mi_malloc(size);
}

void mi_deallocate(void*, void* pointer, std::size_t, std::size_t) {
    mi_free(pointer);
}

void* mi_aligned_allocate(void*, std::size_t size, std::size_t alignment) {
    return mi_malloc_aligned(size, alignment);
}

void mi_aligned_deallocate(void*, void* pointer, std::size_t, std::size_t alignment) {
    mi_free_aligned(pointer, alignment);
}

void* rp_allocate(void*, std::size_t size, std::size_t) {
    return rpmalloc(size);
}

void rp_deallocate(void*, void* pointer, std::size_t, std::size_t) {
    rpfree(pointer);
}

void* rp_aligned_allocate(void*, std::size_t size, std::size_t alignment) {
    return rpaligned_alloc(alignment, size);
}

void rp_aligned_deallocate(void*, void* pointer, std::size_t, std::size_t) {
    rpfree(pointer);
}

struct AlignedAllocator final {
    const char* name;
    void* context;
    AllocFn allocate;
    FreeFn deallocate;
};

const char* compiler_name() {
#if defined(_MSC_VER)
    return "MSVC";
#elif defined(__clang__)
    return "Clang";
#elif defined(__GNUC__)
    return "GCC";
#else
    return "unknown";
#endif
}

bool check_allocation(const Allocator& allocator, std::size_t size, std::size_t alignment) {
    void* pointer = allocator.allocate(allocator.context, size, alignment);
    if (pointer == nullptr) {
        std::fprintf(stderr, "ALLOC_FAIL allocator=%s size=%zu alignment=%zu null\n",
                     allocator.name, size, alignment);
        return false;
    }
    if (reinterpret_cast<std::uintptr_t>(pointer) % alignment != 0) {
        std::fprintf(stderr, "ALLOC_FAIL allocator=%s size=%zu alignment=%zu misaligned\n",
                     allocator.name, size, alignment);
        allocator.deallocate(allocator.context, pointer, size, alignment);
        return false;
    }
    volatile std::byte* bytes = static_cast<volatile std::byte*>(pointer);
    const std::byte first = static_cast<std::byte>(size & 0xFFU);
    const std::byte last = static_cast<std::byte>((size + 1U) & 0xFFU);
    bytes[0] = first;
    if (size > 1) {
        bytes[size - 1] = last;
    }
    const bool ok = bytes[0] == first && (size == 1 || bytes[size - 1] == last);
    allocator.deallocate(allocator.context, pointer, size, alignment);
    if (!ok) {
        std::fprintf(stderr, "ALLOC_FAIL allocator=%s size=%zu readback\n",
                     allocator.name, size);
    }
    return ok;
}

bool correctness(const std::vector<Allocator>& allocators, std::size_t alignment) {
    const std::size_t sizes[] = {1, 16, 64, 256, 4096};
    bool ok = true;
    for (const Allocator& allocator : allocators) {
        for (std::size_t size : sizes) {
            ok = check_allocation(allocator, size, alignment) && ok;
        }
    }
    std::printf("ALLOC_BENCH_CORRECTNESS=%s allocators=%zu\n", ok ? "PASS" : "FAIL",
                allocators.size());
    return ok;
}

double benchmark_single(const Allocator& allocator, std::size_t size,
                        int iterations, std::uint64_t& checksum) {
    for (int warmup = 0; warmup < 1000; ++warmup) {
        void* pointer = allocator.allocate(allocator.context, size, kDefaultAlignment);
        if (pointer == nullptr) {
            return -1.0;
        }
        allocator.deallocate(allocator.context, pointer, size, kDefaultAlignment);
    }
    checksum = 0;
    const auto start = std::chrono::steady_clock::now();
    for (int iteration = 0; iteration < iterations; ++iteration) {
        void* pointer = allocator.allocate(allocator.context, size, kDefaultAlignment);
        if (pointer == nullptr) {
            return -1.0;
        }
        volatile std::byte* bytes = static_cast<volatile std::byte*>(pointer);
        bytes[0] = static_cast<std::byte>(iteration & 0xFF);
        checksum += static_cast<std::uint64_t>(bytes[0]);
        allocator.deallocate(allocator.context, pointer, size, kDefaultAlignment);
    }
    const auto elapsed = std::chrono::steady_clock::now() - start;
    return std::chrono::duration<double, std::nano>(elapsed).count() /
           static_cast<double>(iterations);
}

double benchmark_thread(const Allocator& allocator, std::size_t size, int iterations,
                        std::uint64_t& checksum) {
    void* pointer = allocator.allocate(allocator.context, size, kDefaultAlignment);
    if (pointer == nullptr) {
        return -1.0;
    }
    allocator.deallocate(allocator.context, pointer, size, kDefaultAlignment);
    checksum = 0;
    const auto start = std::chrono::steady_clock::now();
    for (int iteration = 0; iteration < iterations; ++iteration) {
        void* block = allocator.allocate(allocator.context, size, kDefaultAlignment);
        if (block == nullptr) {
            return -1.0;
        }
        volatile std::byte* bytes = static_cast<volatile std::byte*>(block);
        bytes[0] = static_cast<std::byte>(iteration & 0xFF);
        checksum += static_cast<std::uint64_t>(bytes[0]);
        allocator.deallocate(allocator.context, block, size, kDefaultAlignment);
    }
    const auto elapsed = std::chrono::steady_clock::now() - start;
    return std::chrono::duration<double, std::nano>(elapsed).count() /
           static_cast<double>(iterations);
}

bool run_bench(const std::vector<Allocator>& allocators, bool multithread) {
    const std::size_t sizes[] = {16, 64, 256, 1024, 4096};
    constexpr int iterations = 200000;
    constexpr int thread_count = 4;
    bool ok = true;
    for (const Allocator& allocator : allocators) {
        for (std::size_t size : sizes) {
            if (!multithread) {
                std::uint64_t checksum = 0;
                const double ns = benchmark_single(allocator, size, iterations, checksum);
                if (ns < 0.0) {
                    std::fprintf(stderr, "ALLOC_FAIL allocator=%s size=%zu\n",
                                 allocator.name, size);
                    ok = false;
                    continue;
                }
                std::printf("ALLOC_BENCH allocator=%s size=%zu threads=1 "
                            "ns_per_pair=%.3f checksum=%llu\n",
                            allocator.name, size, ns,
                            static_cast<unsigned long long>(checksum));
            } else {
                std::vector<std::thread> workers;
                std::vector<double> thread_ns(thread_count, -1.0);
                std::vector<std::uint64_t> thread_checksum(thread_count, 0);
                workers.reserve(thread_count);
                for (int thread = 0; thread < thread_count; ++thread) {
                    workers.emplace_back([&allocator, size, thread, &thread_ns,
                                          &thread_checksum] {
                        rpmalloc_thread_initialize();
                        thread_ns[static_cast<std::size_t>(thread)] = benchmark_thread(
                            allocator, size, iterations,
                            thread_checksum[static_cast<std::size_t>(thread)]);
                        rpmalloc_thread_finalize();
                    });
                }
                for (std::thread& worker : workers) {
                    worker.join();
                }
                double total_ns = 0.0;
                std::uint64_t checksum = 0;
                bool thread_ok = true;
                for (int thread = 0; thread < thread_count; ++thread) {
                    const double ns = thread_ns[static_cast<std::size_t>(thread)];
                    if (ns < 0.0) {
                        thread_ok = false;
                    } else {
                        total_ns += ns;
                    }
                    checksum += thread_checksum[static_cast<std::size_t>(thread)];
                }
                if (!thread_ok) {
                    std::fprintf(stderr, "ALLOC_FAIL allocator=%s size=%zu threads=%d\n",
                                 allocator.name, size, thread_count);
                    ok = false;
                    continue;
                }
                std::printf("ALLOC_BENCH allocator=%s size=%zu threads=%d "
                            "ns_per_pair=%.3f checksum=%llu\n",
                            allocator.name, size, thread_count,
                            total_ns / static_cast<double>(thread_count), checksum);
            }
        }
    }
    return ok;
}

bool run_aligned(const std::vector<Allocator>& allocators) {
    const std::size_t sizes[] = {64, 256, 1024, 4096};
    constexpr int iterations = 50000;
    bool ok = true;
    for (const Allocator& allocator : allocators) {
        for (std::size_t size : sizes) {
            std::uint64_t checksum = 0;
            const auto start = std::chrono::steady_clock::now();
            for (int iteration = 0; iteration < iterations; ++iteration) {
                void* pointer =
                    allocator.allocate(allocator.context, size, kAligned);
                if (pointer == nullptr ||
                    reinterpret_cast<std::uintptr_t>(pointer) % kAligned != 0) {
                    ok = false;
                    break;
                }
                volatile std::byte* bytes = static_cast<volatile std::byte*>(pointer);
                bytes[0] = static_cast<std::byte>(iteration & 0xFF);
                checksum += static_cast<std::uint64_t>(bytes[0]);
                allocator.deallocate(allocator.context, pointer, size, kAligned);
            }
            const auto elapsed = std::chrono::steady_clock::now() - start;
            const double ns = std::chrono::duration<double, std::nano>(elapsed).count() /
                              static_cast<double>(iterations);
            std::printf("ALLOC_BENCH allocator=%s size=%zu threads=1 aligned=%zu "
                        "ns_per_pair=%.3f checksum=%llu\n",
                        allocator.name, size, kAligned, ns,
                        static_cast<unsigned long long>(checksum));
        }
    }
    return ok;
}

}  // namespace

int main(int argc, char** argv) {
    if (rpmalloc_initialize(nullptr) != 0) {
        std::fprintf(stderr, "ALLOC_FAIL rpmalloc_initialize\n");
        return 1;
    }

    SystemMemoryResource system_resource;
    std::pmr::memory_resource* const pmr_resource = std::pmr::new_delete_resource();
    const std::vector<Allocator> allocators = {
        {"malloc", nullptr, malloc_allocate, malloc_deallocate},
        {"new", nullptr, new_allocate, new_deallocate},
        {"pmr", pmr_resource, pmr_allocate, pmr_deallocate},
        {"system", &system_resource, pmr_allocate, pmr_deallocate},
        {"mimalloc", nullptr, mi_allocate, mi_deallocate},
        {"rpmalloc", nullptr, rp_allocate, rp_deallocate},
    };
    const std::vector<Allocator> aligned_allocators = {
        {"malloc", nullptr, malloc_aligned_allocate, malloc_aligned_deallocate},
        {"new", nullptr, new_aligned_allocate, new_aligned_deallocate},
        {"pmr", pmr_resource, pmr_allocate, pmr_deallocate},
        {"system", &system_resource, pmr_allocate, pmr_deallocate},
        {"mimalloc", nullptr, mi_aligned_allocate, mi_aligned_deallocate},
        {"rpmalloc", nullptr, rp_aligned_allocate, rp_aligned_deallocate},
    };

    std::printf("ALLOC_BENCH_CONFIG compiler=%s pointer_bits=%zu hardware_threads=%u "
                "mimalloc_version=%d rpmalloc=2.0.1 override=none\n",
                compiler_name(), sizeof(void*) * 8U, std::thread::hardware_concurrency(),
                mi_version());
    std::printf("ALLOC_BENCH_NOTE report_only=true thresholds=none selection=none\n");

    const std::string_view mode = argc == 2 ? std::string_view(argv[1]) : "full";
    bool ok = true;
    if (mode == "correctness") {
        ok = correctness(allocators, kDefaultAlignment);
        ok = correctness(aligned_allocators, kAligned) && ok;
    } else if (mode == "bench") {
        ok = run_bench(allocators, false);
    } else if (mode == "bench_mt") {
        ok = run_bench(allocators, true);
    } else if (mode == "aligned") {
        ok = run_aligned(aligned_allocators);
    } else if (mode == "full") {
        ok = correctness(allocators, kDefaultAlignment);
        ok = correctness(aligned_allocators, kAligned) && ok;
        ok = run_bench(allocators, false) && ok;
        ok = run_bench(allocators, true) && ok;
        ok = run_aligned(aligned_allocators) && ok;
    } else {
        std::fprintf(stderr,
                     "usage: %s <correctness|bench|bench_mt|aligned|full>\n", argv[0]);
        rpmalloc_finalize();
        return 2;
    }

    rpmalloc_thread_finalize();
    rpmalloc_finalize();
    if (!ok) {
        std::fprintf(stderr, "ALLOC_BENCH_FAILED\n");
        return 1;
    }
    std::printf("ALLOC_BENCH_OK\n");
    return 0;
}
