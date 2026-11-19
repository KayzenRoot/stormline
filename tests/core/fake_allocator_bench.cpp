#include <chrono>
#include <cstdio>
#include <string_view>
#include <thread>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: %s <success|exit7|missing_ok|missing_correctness|short_results>\n",
                     argv[0]);
        return 2;
    }
    const std::string_view mode(argv[1]);
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    if (mode == "exit7") {
        return 7;
    }
    std::printf("ALLOC_BENCH_CONFIG compiler=Fake pointer_bits=64 hardware_threads=1 "
                "mimalloc_version=0 rpmalloc=0 override=none\n");
    if (mode != "missing_correctness") {
        std::printf("ALLOC_BENCH_CORRECTNESS=PASS allocators=6\n");
        std::printf("ALLOC_BENCH_CORRECTNESS=PASS allocators=6\n");
    }
    const int results = mode == "short_results" ? 1 : 84;
    for (int index = 0; index < results; ++index) {
        std::printf("ALLOC_BENCH allocator=malloc size=64 threads=1 "
                    "ns_per_pair=1.000 checksum=1\n");
    }
    if (mode != "missing_ok") {
        std::printf("ALLOC_BENCH_OK\n");
    }
    return 0;
}
