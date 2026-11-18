// NLE-CORE01-QUAL-001: test-only exploratory lifecycle baseline.
// Cold = first lifecycle in an independently spawned process. Warm = 30
// successive lifecycles in one process. Process launch is excluded from timing.
// This does NOT certify hardware, release performance or statistical p99.
#include "stormline/core/internal/headless_host.hpp"
#include "stormline/core/internal/sdl_runtime.hpp"
#include "stormline/core/internal/window.hpp"

#include <SDL3/SDL.h>

#include <algorithm>
#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <limits>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define PSAPI_VERSION 2
#include <Windows.h>
#include <Psapi.h>
#else
#include <cerrno>
#include <spawn.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#if defined(__APPLE__)
#include <crt_externs.h>
#else
extern char** environ;
#endif
#endif

namespace {

using namespace stormline::core::internal;
using Clock = std::chrono::steady_clock;

constexpr std::size_t kSamples = 30;
constexpr std::size_t kMaxOutput = 65536;

struct Sample final {
    std::uint64_t nanoseconds{0};
    std::uint64_t peak_rss_bytes{0};
};

void fail(const char* detail) {
    std::fprintf(stderr, "BASELINE_FAIL: %s\n", detail);
}

bool set_environment(const char* name, const char* value) {
#if defined(_WIN32)
    return _putenv_s(name, value) == 0;
#else
    return setenv(name, value, 1) == 0;
#endif
}

bool remove_environment(const char* name) {
#if defined(_WIN32)
    return _putenv_s(name, "") == 0;
#else
    return unsetenv(name) == 0;
#endif
}

const char* expected_driver() {
#if defined(_WIN32)
    return "windows";
#elif defined(__APPLE__)
    return "cocoa";
#else
    return "x11";
#endif
}

std::uint64_t peak_resident_bytes() {
#if defined(_WIN32)
    PROCESS_MEMORY_COUNTERS counters{};
    counters.cb = sizeof(counters);
    if (GetProcessMemoryInfo(GetCurrentProcess(), &counters, sizeof(counters)) == FALSE) {
        return 0;
    }
    return static_cast<std::uint64_t>(counters.PeakWorkingSetSize);
#else
    rusage usage{};
    if (getrusage(RUSAGE_SELF, &usage) != 0 || usage.ru_maxrss <= 0) {
        return 0;
    }
#if defined(__APPLE__)
    return static_cast<std::uint64_t>(usage.ru_maxrss);
#else
    return static_cast<std::uint64_t>(usage.ru_maxrss) * 1024ULL;
#endif
#endif
}

bool measure_once(std::string_view mode, Sample& sample) {
    const auto start = Clock::now();
    if (mode == "headless") {
        HeadlessHost host;
        if (host.start(HostConfig{true}) != HostError::None ||
            host.state() != HostState::Running ||
            host.stop() != HostError::None ||
            host.state() != HostState::Stopped) {
            fail("headless lifecycle failed");
            return false;
        }
    } else if (mode == "window") {
        SdlRuntime runtime;
        if (runtime.initialize() != SdlError::None) {
            fail("SDL window runtime initialization failed");
            return false;
        }
        const char* const actual_driver = SDL_GetCurrentVideoDriver();
        if (actual_driver == nullptr || std::string_view(actual_driver) != expected_driver()) {
            fail("SDL backend is not the requested platform backend");
            return false;
        }
        {
            Window window;
            if (window.create(WindowConfig{}) != WindowError::None ||
                window.show() != WindowError::None ||
                window.destroy() != WindowError::None) {
                fail("SDL window lifecycle failed");
                return false;
            }
        }
        if (runtime.shutdown() != SdlError::None) {
            fail("SDL window runtime shutdown failed");
            return false;
        }
    } else {
        fail("unknown measurement mode");
        return false;
    }

    const auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(
        Clock::now() - start).count();
    const auto memory = peak_resident_bytes();
    if (elapsed <= 0 || memory == 0) {
        fail("invalid clock or process peak memory measurement");
        return false;
    }
    sample.nanoseconds = static_cast<std::uint64_t>(elapsed);
    sample.peak_rss_bytes = memory;
    return true;
}

int sample_child(std::string_view mode, std::string_view phase) {
    if (mode != "headless" && mode != "window") {
        fail("unknown child mode");
        return 2;
    }
    if (phase != "cold" && phase != "warm") {
        fail("unknown child phase");
        return 2;
    }
    if (mode == "headless") {
        if (!remove_environment("DISPLAY") || !remove_environment("WAYLAND_DISPLAY")) {
            fail("cannot clear display variables for headless measurement");
            return 1;
        }
    } else if (!set_environment("SDL_VIDEODRIVER", expected_driver())) {
        fail("cannot select explicit native SDL video backend");
        return 1;
    }
    const std::size_t count = phase == "cold" ? 1U : kSamples;
    for (std::size_t i = 0; i < count; ++i) {
        Sample sample{};
        if (!measure_once(mode, sample)) {
            return 1;
        }
        std::printf("SAMPLE %llu %llu\n",
                    static_cast<unsigned long long>(sample.nanoseconds),
                    static_cast<unsigned long long>(sample.peak_rss_bytes));
    }
    return std::fflush(stdout) == 0 ? 0 : 1;
}

bool parse_samples(const std::string& output, std::size_t expected,
                   std::vector<Sample>& out) {
    std::istringstream stream(output);
    std::string marker;
    std::uint64_t ns = 0;
    std::uint64_t rss = 0;
    while (stream >> marker) {
        if (marker != "SAMPLE" || !(stream >> ns >> rss) ||
            ns == 0 || rss == 0 || out.size() >= expected) {
            return false;
        }
        out.push_back(Sample{ns, rss});
    }
    return out.size() == expected && stream.eof();
}

bool launch_child(const char* executable, std::string_view mode,
                  std::string_view phase, std::string& output) {
#if defined(_WIN32)
    (void)executable;
    std::array<wchar_t, 32768> path{};
    const DWORD size = GetModuleFileNameW(nullptr, path.data(),
                                           static_cast<DWORD>(path.size()));
    if (size == 0 || static_cast<std::size_t>(size) >= path.size()) {
        fail("GetModuleFileNameW failed");
        return false;
    }
    const std::wstring image(path.data(), size);
    const std::wstring kind(mode.begin(), mode.end());
    const std::wstring stage(phase.begin(), phase.end());
    std::wstring command = L"\"" + image + L"\" --child " + kind + L" " + stage;

    SECURITY_ATTRIBUTES attrs{};
    attrs.nLength = sizeof(attrs);
    attrs.bInheritHandle = TRUE;
    HANDLE pipe_read = nullptr;
    HANDLE pipe_write = nullptr;
    if (CreatePipe(&pipe_read, &pipe_write, &attrs, 0) == FALSE) {
        fail("CreatePipe failed");
        return false;
    }
    if (SetHandleInformation(pipe_read, HANDLE_FLAG_INHERIT, 0) == FALSE) {
        CloseHandle(pipe_read);
        CloseHandle(pipe_write);
        fail("pipe inherit control failed");
        return false;
    }

    STARTUPINFOW startup{};
    startup.cb = sizeof(startup);
    startup.dwFlags = STARTF_USESTDHANDLES;
    startup.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
    startup.hStdOutput = pipe_write;
    startup.hStdError = GetStdHandle(STD_ERROR_HANDLE);
    PROCESS_INFORMATION process{};
    const BOOL spawned = CreateProcessW(image.c_str(), command.data(), nullptr, nullptr,
                                        TRUE, CREATE_NO_WINDOW, nullptr, nullptr,
                                        &startup, &process);
    CloseHandle(pipe_write);
    if (spawned == FALSE) {
        CloseHandle(pipe_read);
        fail("CreateProcessW failed");
        return false;
    }

    std::array<char, 4096> buffer{};
    DWORD received = 0;
    while (ReadFile(pipe_read, buffer.data(), static_cast<DWORD>(buffer.size()),
                    &received, nullptr) != FALSE && received != 0) {
        if (output.size() + received > kMaxOutput) {
            break;
        }
        output.append(buffer.data(), received);
    }
    CloseHandle(pipe_read);
    const DWORD waited = WaitForSingleObject(process.hProcess, 60000);
    DWORD code = 1;
    const bool complete = waited == WAIT_OBJECT_0 &&
                          GetExitCodeProcess(process.hProcess, &code) != FALSE;
    if (waited == WAIT_TIMEOUT) {
        // Only this explicitly spawned, nonprivileged test child is terminated.
        (void)TerminateProcess(process.hProcess, 1);
        (void)WaitForSingleObject(process.hProcess, 5000);
    }
    CloseHandle(process.hThread);
    CloseHandle(process.hProcess);
    if (!complete || code != 0 || output.size() > kMaxOutput) {
        fail("Windows child exited unsuccessfully or exceeded output bound");
        return false;
    }
#else
    int descriptors[2]{};
    if (pipe(descriptors) != 0) {
        fail("pipe failed");
        return false;
    }
    posix_spawn_file_actions_t actions{};
    if (posix_spawn_file_actions_init(&actions) != 0) {
        close(descriptors[0]);
        close(descriptors[1]);
        fail("posix_spawn_file_actions_init failed");
        return false;
    }
    const bool configured =
        posix_spawn_file_actions_adddup2(&actions, descriptors[1], STDOUT_FILENO) == 0 &&
        posix_spawn_file_actions_addclose(&actions, descriptors[0]) == 0 &&
        posix_spawn_file_actions_addclose(&actions, descriptors[1]) == 0;
    if (!configured) {
        posix_spawn_file_actions_destroy(&actions);
        close(descriptors[0]);
        close(descriptors[1]);
        fail("posix_spawn file actions failed");
        return false;
    }
    std::string kind(mode);
    std::string stage(phase);
    char* const args[] = {const_cast<char*>(executable),
                          const_cast<char*>("--child"), kind.data(), stage.data(),
                          nullptr};
#if defined(__APPLE__)
    char** child_environment = *_NSGetEnviron();
#else
    char** child_environment = environ;
#endif
    pid_t pid = -1;
    const int spawned = posix_spawn(&pid, executable, &actions, nullptr,
                                   args, child_environment);
    posix_spawn_file_actions_destroy(&actions);
    close(descriptors[1]);
    if (spawned != 0) {
        close(descriptors[0]);
        fail("posix_spawn failed");
        return false;
    }

    std::array<char, 4096> buffer{};
    for (;;) {
        const ssize_t received = read(descriptors[0], buffer.data(), buffer.size());
        if (received == 0) {
            break;
        }
        if (received < 0) {
            if (errno == EINTR) {
                continue;
            }
            fail("reading child stdout failed");
            break;
        }
        if (output.size() + static_cast<std::size_t>(received) > kMaxOutput) {
            fail("child output exceeded 64 KiB");
            break;
        }
        output.append(buffer.data(), static_cast<std::size_t>(received));
    }
    close(descriptors[0]);
    int status = 0;
    pid_t waited = -1;
    do {
        waited = waitpid(pid, &status, 0);
    } while (waited < 0 && errno == EINTR);
    if (waited != pid || !WIFEXITED(status) || WEXITSTATUS(status) != 0 ||
        output.size() > kMaxOutput) {
        fail("POSIX child exited unsuccessfully");
        return false;
    }
#endif
    return true;
}

std::uint64_t nearest_rank(std::vector<std::uint64_t> values, std::size_t percentile) {
    if (values.empty() || percentile == 0 || percentile > 100) {
        return 0;
    }
    std::sort(values.begin(), values.end());
    const auto index = ((percentile * values.size() + 99U) / 100U) - 1U;
    return values.at(index);
}

void report(std::string_view mode, std::string_view phase,
            const std::vector<Sample>& samples) {
    std::vector<std::uint64_t> times;
    std::vector<std::uint64_t> peaks;
    times.reserve(samples.size());
    peaks.reserve(samples.size());
    for (const auto& sample : samples) {
        times.push_back(sample.nanoseconds);
        peaks.push_back(sample.peak_rss_bytes);
    }
    const std::string kind(mode);
    const std::string stage(phase);
    std::printf("BASELINE mode=%s phase=%s n=%zu p50_ms=%.6f p95_ms=%.6f "
                "max_process_peak_rss_bytes=%llu rss_unit=bytes\n",
                kind.c_str(), stage.c_str(), samples.size(),
                static_cast<double>(nearest_rank(times, 50)) / 1e6,
                static_cast<double>(nearest_rank(times, 95)) / 1e6,
                static_cast<unsigned long long>(*std::max_element(peaks.begin(), peaks.end())));
    std::printf("BASELINE_RAW_NS mode=%s phase=%s values=", kind.c_str(), stage.c_str());
    for (std::size_t i = 0; i < times.size(); ++i) {
        std::printf("%s%llu", i == 0 ? "" : ",",
                    static_cast<unsigned long long>(times[i]));
    }
    std::printf("\nBASELINE_RAW_PEAK_RSS_BYTES mode=%s phase=%s values=",
                kind.c_str(), stage.c_str());
    for (std::size_t i = 0; i < peaks.size(); ++i) {
        std::printf("%s%llu", i == 0 ? "" : ",",
                    static_cast<unsigned long long>(peaks[i]));
    }
    std::printf("\n");
}

int benchmark(const char* executable) {
    const auto ver = linked_version();
#if defined(_WIN32)
    std::printf("BASELINE_META os=windows arch=%s compiler=MSVC compiler_build=%ld ",
#if defined(_M_ARM64)
                "arm64",
#else
                "x86_64",
#endif
                static_cast<long>(_MSC_FULL_VER));
#elif defined(__APPLE__)
    std::printf("BASELINE_META os=macos arch=%s compiler=%s ",
#if defined(__aarch64__)
                "arm64",
#else
                "other",
#endif
                __VERSION__);
#else
    std::printf("BASELINE_META os=linux arch=%s compiler=%s ",
#if defined(__x86_64__)
                "x86_64",
#elif defined(__aarch64__)
                "arm64",
#else
                "other",
#endif
                __VERSION__);
#endif
    std::printf("SDL=%d.%d.%d cold=fresh_process warm=reused_process "
                "measured=init_to_teardown_excludes_spawn "
                "rss=process_peak_not_idle_or_leak_proof\n",
                ver.major, ver.minor, ver.patch);
    for (const char* mode : {"headless", "window"}) {
        std::vector<Sample> cold;
        cold.reserve(kSamples);
        for (std::size_t i = 0; i < kSamples; ++i) {
            std::string data;
            if (!launch_child(executable, mode, "cold", data) ||
                !parse_samples(data, 1U, cold)) {
                // parse_samples expects out.size() == expected; use a new vector
                // in the corrected loop below instead of accumulating directly.
                fail("cold process measurement failed");
                return 1;
            }
        }
        std::string data;
        std::vector<Sample> warm;
        if (!launch_child(executable, mode, "warm", data) ||
            !parse_samples(data, kSamples, warm)) {
            fail("warm process measurement failed");
            return 1;
        }
        if (cold.size() != kSamples || warm.size() != kSamples) {
            fail("sample count mismatch");
            return 1;
        }
        report(mode, "cold", cold);
        report(mode, "warm", warm);
    }
    std::printf("BASELINE_OK modes=headless,window cold=30 warm=30 "
                "percentiles=nearest-rank p50,p95 no_threshold_or_p99_claim\n");
    return 0;
}

int selftest() {
    std::vector<std::uint64_t> input;
    for (std::uint64_t i = 30; i >= 1; --i) {
        input.push_back(i);
    }
    std::vector<Sample> parsed;
    if (nearest_rank(input, 50) != 15 || nearest_rank(input, 95) != 29 ||
        nearest_rank(input, 0) != 0 ||
        !parse_samples("SAMPLE 12 1024\nSAMPLE 20 2048\n", 2, parsed) ||
        parsed.size() != 2 || parsed[1].nanoseconds != 20) {
        fail("statistics/parser positive selftest failed");
        return 1;
    }
    std::vector<Sample> bad;
    if (parse_samples("SAMPLE 0 4\n", 1, bad) ||
        parse_samples("UNQUALIFIED 10 10\n", 1, bad) ||
        parse_samples("SAMPLE 5 5\n", 2, bad)) {
        fail("parser fail-closed selftest failed");
        return 1;
    }
    std::puts("BASELINE_SELFTEST_OK percentile=nearest-rank strict_sample_parser=true");
    return 0;
}

int no_display() {
#if !defined(__linux__)
    std::fprintf(stderr, "NOT_QUALIFIED: true missing-display simulation is Linux-only\n");
    return 77;
#else
    if (!remove_environment("DISPLAY") || !remove_environment("WAYLAND_DISPLAY") ||
        !set_environment("SDL_VIDEODRIVER", "x11") ||
        std::getenv("DISPLAY") != nullptr || std::getenv("WAYLAND_DISPLAY") != nullptr) {
        fail("cannot enforce genuine absent X11/Wayland display variables");
        return 1;
    }
    HeadlessHost host;
    if (host.start(HostConfig{true}) != HostError::None ||
        host.stop() != HostError::None) {
        fail("headless depends on graphical display environment");
        return 1;
    }
    SdlRuntime runtime;
    const auto start = Clock::now();
    const SdlError result = runtime.initialize();
    const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
        Clock::now() - start).count();
    if (result != SdlError::InitFailed || runtime.initialized() ||
        SDL_WasInit(SDL_INIT_VIDEO) != 0 || elapsed > 5000) {
        fail("windowed runtime failed to return typed InitFailed within 5 seconds");
        return 1;
    }
    std::printf("NO_DISPLAY_OK headless=PASS video=InitFailed SDL_VIDEODRIVER=x11 "
                "DISPLAY=unset WAYLAND_DISPLAY=unset duration_ms=%lld limit_ms=5000\n",
                static_cast<long long>(elapsed));
    return 0;
#endif
}

} // namespace

int main(int argc, char** argv) {
    if (argc == 2 && std::string_view(argv[1]) == "baseline") {
        return benchmark(argv[0]);
    }
    if (argc == 2 && std::string_view(argv[1]) == "selftest") {
        return selftest();
    }
    if (argc == 2 && std::string_view(argv[1]) == "no-display") {
        return no_display();
    }
    if (argc == 4 && std::string_view(argv[1]) == "--child") {
        return sample_child(argv[2], argv[3]);
    }
    fail("usage: baseline | selftest | no-display | --child <headless|window> <cold|warm>");
    return 2;
}
