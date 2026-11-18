#include "stormline/core/memory/monotonic_arena.hpp"

#include <atomic>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <memory_resource>
#include <string_view>
#include <thread>

namespace {

using stormline::core::memory::ArenaError;
using stormline::core::memory::ArenaSlice;
using stormline::core::memory::MonotonicArena;

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

class CountingResource final : public std::pmr::memory_resource {
public:
    std::atomic<int> allocations{0};
    std::atomic<int> deallocations{0};
    std::atomic<int> live{0};

private:
    void* do_allocate(std::size_t bytes, std::size_t alignment) override {
        void* pointer = std::pmr::new_delete_resource()->allocate(bytes, alignment);
        allocations.fetch_add(1, std::memory_order_relaxed);
        live.fetch_add(1, std::memory_order_relaxed);
        return pointer;
    }

    void do_deallocate(void* pointer, std::size_t bytes, std::size_t alignment) override {
        std::pmr::new_delete_resource()->deallocate(pointer, bytes, alignment);
        deallocations.fetch_add(1, std::memory_order_relaxed);
        live.fetch_sub(1, std::memory_order_relaxed);
    }

    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override {
        return this == &other;
    }
};

bool run_basic() {
    begin_case();
    MonotonicArena arena(1024, 64);
    expect(arena.valid(), "arena is valid");
    expect(arena.capacity() == 1024, "arena capacity");
    expect(arena.used() == 0, "fresh arena unused");
    expect(arena.remaining() == 1024, "fresh arena remaining");

    ArenaSlice first{};
    expect(arena.allocate(100, 16, first) == ArenaError::None, "first allocation");
    expect(first.data != nullptr, "first slice data");
    expect(first.size == 100, "first slice size");
    expect(first.offset == 0, "first slice offset");
    expect(is_aligned(first.data, 16), "first slice alignment");
    std::memset(first.data, 0x5a, first.size);
    expect(first.data[0] == std::byte{0x5a}, "first slice writable");
    expect(arena.used() == 100, "used after first");
    expect(arena.high_water() == 100, "high water after first");

    ArenaSlice second{};
    expect(arena.allocate(50, 16, second) == ArenaError::None, "second allocation");
    expect(second.offset == 112, "second allocation is aligned up");
    expect(arena.used() == 162, "used after second");
    expect(arena.high_water() == 162, "high water after second");

    expect(arena.reset() == ArenaError::None, "reset succeeds");
    expect(arena.used() == 0, "reset rewinds used");
    expect(arena.high_water() == 162, "reset preserves high water");
    ArenaSlice third{};
    expect(arena.allocate(16, 16, third) == ArenaError::None, "allocation after reset");
    expect(third.offset == 0, "reset reuses the start");
    return finish_case();
}

bool run_alignment() {
    begin_case();
    MonotonicArena arena(4096, 64);
    for (std::size_t alignment : {std::size_t{1}, std::size_t{8}, std::size_t{16},
                                  std::size_t{32}, std::size_t{64}}) {
        ArenaSlice slice{};
        expect(arena.allocate(8, alignment, slice) == ArenaError::None, "alignment allocation");
        expect(is_aligned(slice.data, alignment), "requested arena alignment");
        expect(slice.size == 8, "alignment slice size");
    }
    return finish_case();
}

bool run_overflow() {
    begin_case();
    MonotonicArena arena(128, 64);
    ArenaSlice first{};
    ArenaSlice second{};
    expect(arena.allocate(64, 16, first) == ArenaError::None, "overflow first allocation");
    expect(arena.allocate(64, 16, second) == ArenaError::None, "overflow second allocation");
    expect(arena.used() == 128, "arena is full");
    ArenaSlice rejected{};
    expect(arena.allocate(1, 16, rejected) == ArenaError::OutOfMemory,
           "allocation beyond capacity is rejected");
    expect(arena.used() == 128, "overflow leaves used unchanged");
    expect(arena.reset() == ArenaError::None, "overflow reset succeeds");
    expect(arena.allocate(128, 64, rejected) == ArenaError::None, "full-capacity allocation after reset");
    return finish_case();
}

bool run_invalid() {
    begin_case();
    MonotonicArena zero(0, 64);
    expect(!zero.valid(), "zero-capacity arena is invalid");
    ArenaSlice slice{};
    expect(zero.allocate(1, 16, slice) == ArenaError::InvalidCapacity,
           "zero capacity reports InvalidCapacity");
    expect(zero.reset() == ArenaError::InvalidCapacity, "zero capacity reset reports error");

    MonotonicArena bad_alignment(128, 48);
    expect(!bad_alignment.valid(), "non-power-of-two backing alignment is invalid");
    expect(bad_alignment.allocate(1, 16, slice) == ArenaError::InvalidAlignment,
           "bad backing alignment reports InvalidAlignment");

    MonotonicArena arena(128, 64);
    expect(arena.allocate(0, 16, slice) == ArenaError::InvalidSize, "zero bytes rejected");
    expect(arena.allocate(8, 3, slice) == ArenaError::InvalidAlignment,
           "non-power-of-two slice alignment rejected");
    expect(arena.allocate(8, 128, slice) == ArenaError::AlignmentExceedsBacking,
           "alignment beyond backing rejected");
    expect(arena.used() == 0, "invalid input leaves arena unused");
    return finish_case();
}

bool run_resource() {
    begin_case();
    CountingResource resource;
    {
        MonotonicArena arena(256, 64, &resource);
        expect(arena.valid(), "custom-resource arena is valid");
        expect(resource.allocations.load() == 1, "one backing allocation");
        ArenaSlice slice{};
        expect(arena.allocate(64, 16, slice) == ArenaError::None, "custom-resource slice");
    }
    expect(resource.deallocations.load() == 1, "one backing deallocation");
    expect(resource.live.load() == 0, "no live backing allocation");
    return finish_case();
}

bool run_lifetime() {
    begin_case();
    MonotonicArena arena(4096, 64);
    bool ok = true;
    for (int cycle = 0; cycle < 1000 && ok; ++cycle) {
        const std::size_t bytes = 4 + (static_cast<std::size_t>(cycle) % 13) * 8;
        const std::size_t alignment = (cycle % 4 == 0) ? 64 : 16;
        ArenaSlice slice{};
        ok = arena.allocate(bytes, alignment, slice) == ArenaError::None;
        ok = ok && is_aligned(slice.data, alignment);
        ok = ok && arena.used() <= arena.capacity();
        ok = ok && arena.reset() == ArenaError::None;
        ok = ok && arena.used() == 0;
    }
    expect(ok, "1000 arena allocate/reset cycles succeed");
    expect(arena.high_water() <= arena.capacity(), "high water within capacity");
    return finish_case();
}

bool run_wrong_thread() {
    begin_case();
    MonotonicArena arena(256, 64);
    ArenaError worker_allocate = ArenaError::None;
    ArenaError worker_reset = ArenaError::None;
    std::thread worker([&arena, &worker_allocate, &worker_reset] {
        ArenaSlice slice{};
        worker_allocate = arena.allocate(16, 16, slice);
        worker_reset = arena.reset();
    });
    worker.join();
    expect(worker_allocate == ArenaError::WrongThread, "worker allocation rejected");
    expect(worker_reset == ArenaError::WrongThread, "worker reset rejected");
    expect(arena.used() == 0, "worker calls leave arena unused");
    expect(arena.reset() == ArenaError::None, "owner reset succeeds");
    return finish_case();
}

}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr,
                     "usage: %s <basic|alignment|overflow|invalid|resource|lifetime|wrong_thread>\n",
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
    if (mode == "overflow") {
        return run_overflow() ? 0 : 1;
    }
    if (mode == "invalid") {
        return run_invalid() ? 0 : 1;
    }
    if (mode == "resource") {
        return run_resource() ? 0 : 1;
    }
    if (mode == "lifetime") {
        return run_lifetime() ? 0 : 1;
    }
    if (mode == "wrong_thread") {
        return run_wrong_thread() ? 0 : 1;
    }

    std::fprintf(stderr, "unknown mode: %s\n", argv[1]);
    return 2;
}
