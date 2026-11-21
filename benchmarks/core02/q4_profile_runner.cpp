#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <string_view>
#include <vector>

namespace {

struct RunOptions final {
    std::wstring profile;
    unsigned cpus{0};
    std::size_t memory_mib{0};
    unsigned runs{0};
    std::wstring executable;
    std::wstring arguments;
};

struct WinHandle final {
    HANDLE handle{nullptr};
    ~WinHandle() {
        if (handle != nullptr && handle != INVALID_HANDLE_VALUE) {
            CloseHandle(handle);
        }
    }
};

struct RunContext final {
    HANDLE job{nullptr};
    HANDLE process{nullptr};
    HANDLE thread{nullptr};
    HANDLE stdin_handle{nullptr};
    HANDLE stdout_handle{nullptr};
    HANDLE stderr_handle{nullptr};
    std::wstring stdout_path;
    std::wstring stderr_path;

    ~RunContext() {
        if (job != nullptr) CloseHandle(job);
        if (process != nullptr) {
            if (WaitForSingleObject(process, 0) == WAIT_TIMEOUT) {
                TerminateProcess(process, 1);
            }
            CloseHandle(process);
        }
        if (thread != nullptr) CloseHandle(thread);
        if (stdin_handle != nullptr && stdin_handle != INVALID_HANDLE_VALUE) CloseHandle(stdin_handle);
        if (stdout_handle != nullptr && stdout_handle != INVALID_HANDLE_VALUE) CloseHandle(stdout_handle);
        if (stderr_handle != nullptr && stderr_handle != INVALID_HANDLE_VALUE) CloseHandle(stderr_handle);
        if (!stdout_path.empty()) DeleteFileW(stdout_path.c_str());
        if (!stderr_path.empty()) DeleteFileW(stderr_path.c_str());
    }
};

std::string narrow(const std::wstring& value) {
    if (value.empty()) return {};
    const int size = WideCharToMultiByte(CP_UTF8, 0, value.c_str(),
                                         static_cast<int>(value.size()), nullptr, 0,
                                         nullptr, nullptr);
    if (size <= 0) return {};
    std::string result(static_cast<std::size_t>(size), '\0');
    WideCharToMultiByte(CP_UTF8, 0, value.c_str(), static_cast<int>(value.size()),
                        result.data(), size, nullptr, nullptr);
    return result;
}

bool parse_unsigned(const wchar_t* text, unsigned& out) {
    if (text == nullptr || *text == L'\0') return false;
    wchar_t* end = nullptr;
    const unsigned long value = std::wcstoul(text, &end, 10);
    if (end == nullptr || *end != L'\0' || value > 0xFFFFFFFFUL) return false;
    out = static_cast<unsigned>(value);
    return true;
}

bool parse_size(const wchar_t* text, std::size_t& out) {
    if (text == nullptr || *text == L'\0') return false;
    wchar_t* end = nullptr;
    const unsigned long long value = std::wcstoull(text, &end, 10);
    if (end == nullptr || *end != L'\0') return false;
    out = static_cast<std::size_t>(value);
    return true;
}

bool create_temp_file(const wchar_t* prefix, SECURITY_ATTRIBUTES& attributes,
                      std::wstring& path, HANDLE& handle) {
    wchar_t temp_path[MAX_PATH]{};
    const DWORD length = GetTempPathW(MAX_PATH, temp_path);
    if (length == 0 || length >= MAX_PATH) return false;
    wchar_t name[MAX_PATH]{};
    if (GetTempFileNameW(temp_path, prefix, 0, name) == 0) return false;
    path = name;
    handle = CreateFileW(path.c_str(), GENERIC_WRITE,
                         FILE_SHARE_READ | FILE_SHARE_WRITE, &attributes,
                         OPEN_EXISTING, FILE_ATTRIBUTE_TEMPORARY, nullptr);
    return handle != INVALID_HANDLE_VALUE;
}

std::string read_all(const std::wstring& path) {
    HANDLE handle = CreateFileW(path.c_str(), GENERIC_READ,
                                FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr,
                                OPEN_EXISTING, FILE_ATTRIBUTE_TEMPORARY, nullptr);
    if (handle == INVALID_HANDLE_VALUE) return {};
    WinHandle owned{handle};
    std::string result;
    char buffer[4096];
    for (;;) {
        DWORD read = 0;
        if (!ReadFile(handle, buffer, sizeof(buffer), &read, nullptr) || read == 0) break;
        result.append(buffer, read);
    }
    return result;
}

std::size_t count_occurrences(const std::string& text, const std::string& needle) {
    std::size_t count = 0;
    std::size_t position = 0;
    while ((position = text.find(needle, position)) != std::string::npos) {
        ++count;
        position += needle.size();
    }
    return count;
}

void print_filtered(const std::string& text) {
    std::size_t start = 0;
    while (start < text.size()) {
        const std::size_t end = text.find('\n', start);
        const std::string line = text.substr(start, end == std::string::npos
                                                       ? std::string::npos
                                                       : end - start);
        if (line.find("ALLOC_BENCH_CONFIG") != std::string::npos ||
            line.find("ALLOC_BENCH_CORRECTNESS") != std::string::npos ||
            (line.find("ALLOC_BENCH allocator=") != std::string::npos &&
             line.find(" size=64 ") != std::string::npos)) {
            std::printf("%s\n", line.c_str());
        }
        if (end == std::string::npos) break;
        start = end + 1;
    }
}

bool run_one(const RunOptions& options, unsigned run, std::string& failure) {
    RunContext context;
    SECURITY_ATTRIBUTES attributes{};
    attributes.nLength = sizeof(attributes);
    attributes.bInheritHandle = TRUE;

    if (!create_temp_file(L"q4p", attributes, context.stdout_path, context.stdout_handle) ||
        !create_temp_file(L"q4e", attributes, context.stderr_path, context.stderr_handle)) {
        failure = "temp_file_failed";
        return false;
    }
    context.stdin_handle = CreateFileW(L"NUL", GENERIC_READ,
                                       FILE_SHARE_READ | FILE_SHARE_WRITE, &attributes,
                                       OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (context.stdin_handle == INVALID_HANDLE_VALUE) {
        failure = "nul_open_failed";
        return false;
    }

    context.job = CreateJobObjectW(nullptr, nullptr);
    if (context.job == nullptr) {
        failure = "job_create_failed";
        return false;
    }
    JOBOBJECT_EXTENDED_LIMIT_INFORMATION limits{};
    limits.BasicLimitInformation.LimitFlags = JOB_OBJECT_LIMIT_PROCESS_MEMORY | JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE;
    limits.ProcessMemoryLimit = options.memory_mib * 1024ULL * 1024ULL;
    if (!SetInformationJobObject(context.job, JobObjectExtendedLimitInformation,
                                 &limits, sizeof(limits))) {
        failure = "job_limit_failed";
        return false;
    }

    const DWORD_PTR mask = (static_cast<DWORD_PTR>(1) << options.cpus) - 1;
    std::wstring command_line = L"\"" + options.executable + L"\" " + options.arguments;
    std::vector<wchar_t> mutable_command(command_line.begin(), command_line.end());
    mutable_command.push_back(L'\0');

    STARTUPINFOW startup{};
    startup.cb = sizeof(startup);
    startup.dwFlags = STARTF_USESTDHANDLES;
    startup.hStdInput = context.stdin_handle;
    startup.hStdOutput = context.stdout_handle;
    startup.hStdError = context.stderr_handle;
    PROCESS_INFORMATION process{};
    if (!CreateProcessW(options.executable.c_str(), mutable_command.data(), nullptr, nullptr,
                        TRUE, CREATE_SUSPENDED | CREATE_NO_WINDOW, nullptr, nullptr,
                        &startup, &process)) {
        failure = "create_process_failed";
        return false;
    }
    context.process = process.hProcess;
    context.thread = process.hThread;

    if (!AssignProcessToJobObject(context.job, context.process)) {
        failure = "job_assign_failed";
        return false;
    }
    if (!SetProcessAffinityMask(context.process, mask)) {
        failure = "affinity_set_failed";
        return false;
    }
    DWORD_PTR effective_mask = 0;
    DWORD_PTR system_mask = 0;
    if (!GetProcessAffinityMask(context.process, &effective_mask, &system_mask) ||
        effective_mask != mask || (system_mask & mask) != mask) {
        failure = "affinity_readback_failed";
        return false;
    }
    JOBOBJECT_EXTENDED_LIMIT_INFORMATION applied{};
    DWORD returned = 0;
    if (!QueryInformationJobObject(context.job, JobObjectExtendedLimitInformation,
                                   &applied, sizeof(applied), &returned) ||
        applied.ProcessMemoryLimit != limits.ProcessMemoryLimit) {
        failure = "memory_limit_readback_failed";
        return false;
    }
    if (ResumeThread(context.thread) == static_cast<DWORD>(-1)) {
        failure = "resume_failed";
        return false;
    }
    if (WaitForSingleObject(context.process, INFINITE) != WAIT_OBJECT_0) {
        failure = "wait_failed";
        return false;
    }
    DWORD exit_code = 0;
    if (!GetExitCodeProcess(context.process, &exit_code)) {
        failure = "exit_code_failed";
        return false;
    }
    if (exit_code != 0) {
        failure = "exit_code=" + std::to_string(exit_code);
        return false;
    }

    const std::string stdout_text = read_all(context.stdout_path);
    const std::string stderr_text = read_all(context.stderr_path);
    if (!stderr_text.empty()) {
        failure = "stderr_nonempty";
        return false;
    }
    const std::size_t config = count_occurrences(stdout_text, "ALLOC_BENCH_CONFIG");
    const std::size_t pass = count_occurrences(stdout_text, "ALLOC_BENCH_CORRECTNESS=PASS");
    const std::size_t ok = count_occurrences(stdout_text, "ALLOC_BENCH_OK");
    const std::size_t results = count_occurrences(stdout_text, "ALLOC_BENCH allocator=");
    if (config != 1 || pass != 2 || ok != 1 || results < 84) {
        failure = "markers config=" + std::to_string(config) +
                  " pass=" + std::to_string(pass) +
                  " ok=" + std::to_string(ok) +
                  " results=" + std::to_string(results);
        return false;
    }

    std::printf("PROFILE_RUN profile=%s run=%u exit=%lu cpus=%u affinity=0x%llx "
                "affinity_coverage=before_resume memory_limit_mib=%zu results=%zu\n",
                narrow(options.profile).c_str(), run, static_cast<unsigned long>(exit_code),
                options.cpus, static_cast<unsigned long long>(effective_mask),
                options.memory_mib, results);
    print_filtered(stdout_text);
    return true;
}

bool parse_arguments(int argc, wchar_t** argv, RunOptions& options) {
    for (int index = 1; index < argc; ++index) {
        const std::wstring_view flag(argv[index]);
        if (flag == L"--profile" && index + 1 < argc) {
            options.profile = argv[++index];
        } else if (flag == L"--cpus" && index + 1 < argc) {
            if (!parse_unsigned(argv[++index], options.cpus)) return false;
        } else if (flag == L"--memory-mib" && index + 1 < argc) {
            if (!parse_size(argv[++index], options.memory_mib)) return false;
        } else if (flag == L"--runs" && index + 1 < argc) {
            if (!parse_unsigned(argv[++index], options.runs)) return false;
        } else if (flag == L"--executable" && index + 1 < argc) {
            options.executable = argv[++index];
        } else if (flag == L"--arguments" && index + 1 < argc) {
            options.arguments = argv[++index];
        } else {
            return false;
        }
    }
    return !options.profile.empty() && options.cpus >= 1 && options.cpus <= 32 &&
           options.memory_mib >= 1024 && options.memory_mib <= 65536 &&
           options.runs >= 1 && options.runs <= 100 &&
           !options.executable.empty() && !options.arguments.empty();
}

}  // namespace

int wmain(int argc, wchar_t** argv) {
    RunOptions options;
    if (!parse_arguments(argc, argv, options)) {
        std::fprintf(stderr, "usage: %ls --profile <name> --cpus <1..32> "
                             "--memory-mib <1024..65536> --runs <1..100> "
                             "--executable <path> --arguments <args>\n",
                     argv[0]);
        return 2;
    }
    const std::string profile = narrow(options.profile);
    unsigned completed = 0;
    for (unsigned run = 1; run <= options.runs; ++run) {
        std::string failure;
        if (!run_one(options, run, failure)) {
            std::printf("PROFILE_FAIL profile=%s reason=%s\n", profile.c_str(),
                        failure.c_str());
            return 1;
        }
        ++completed;
    }
    if (completed != options.runs) {
        std::printf("PROFILE_FAIL profile=%s reason=run_count expected=%u completed=%u\n",
                    profile.c_str(), options.runs, completed);
        return 1;
    }
    std::printf("PROFILE_SUMMARY profile=%s runs=%u failures=0 cpus=%u "
                "memory_limit_mib=%zu affinity_coverage=before_resume\n",
                profile.c_str(), completed, options.cpus, options.memory_mib);
    return 0;
}
