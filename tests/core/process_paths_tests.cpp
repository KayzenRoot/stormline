#include "stormline/core/internal/process_paths.hpp"

#include <algorithm>
#include <chrono>
#include <cstdint>
#include <cstdio>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

#if !defined(_WIN32)
#include <sys/stat.h>
#include <unistd.h>
#endif

namespace {

using stormline::core::internal::PathError;
using stormline::core::internal::ProcessPathsTestAccess;
using stormline::core::internal::current_directory;
using stormline::core::internal::normalize_absolute;
using stormline::core::internal::normalize_within_root;
using stormline::core::internal::temporary_directory;
using stormline::core::internal::to_utf8;

int failures = 0;

void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}

void note(const char* description) {
    std::printf("NOT_QUALIFIED: %s\n", description);
}

void begin_case() {
    failures = 0;
    ProcessPathsTestAccess::clear_forced_error();
}

bool finish_case() {
    ProcessPathsTestAccess::clear_forced_error();
    return failures == 0;
}

class TempFixture final {
public:
    TempFixture() {
        std::error_code error;
        const auto base = std::filesystem::temp_directory_path(error);
        if (error) {
            valid_ = false;
            return;
        }
        static int counter = 0;
        const auto stamp = std::chrono::steady_clock::now().time_since_epoch().count();
        path_ = base / ("stormline_paths_" + std::to_string(stamp) + "_" + std::to_string(++counter));
        std::filesystem::create_directories(path_, error);
        valid_ = !error;
    }

    ~TempFixture() {
        if (!path_.empty()) {
            std::error_code error;
            std::filesystem::remove_all(path_, error);
        }
    }

    TempFixture(const TempFixture&) = delete;
    TempFixture& operator=(const TempFixture&) = delete;

    [[nodiscard]] bool valid() const noexcept { return valid_; }
    [[nodiscard]] const std::filesystem::path& path() const noexcept { return path_; }

private:
    std::filesystem::path path_;
    bool valid_{false};
};

std::vector<std::string> snapshot(const std::filesystem::path& root) {
    std::vector<std::string> entries;
    std::error_code error;
    for (std::filesystem::recursive_directory_iterator it(root, error), end; it != end; it.increment(error)) {
        if (error) {
            break;
        }
        entries.push_back(it->path().lexically_relative(root).generic_string());
    }
    std::sort(entries.begin(), entries.end());
    return entries;
}

std::string bytes_of(const std::u8string& text) {
    return std::string(reinterpret_cast<const char*>(text.data()), text.size());
}

bool run_basic() {
    begin_case();
    const auto cwd = current_directory();
    expect(cwd.ok(), "current_directory succeeds");
    expect(cwd.path.is_absolute(), "current_directory is absolute");
    expect(std::filesystem::is_directory(cwd.path), "current_directory is a directory");

    const auto temp = temporary_directory();
    expect(temp.ok(), "temporary_directory succeeds");
    expect(temp.path.is_absolute(), "temporary_directory is absolute");
    expect(std::filesystem::is_directory(temp.path), "temporary_directory is a directory");

    TempFixture fixture;
    expect(fixture.valid(), "temporary fixture created");
    if (fixture.valid()) {
        const auto normalized = normalize_absolute(fixture.path());
        expect(normalized.ok(), "normalize_absolute succeeds");
        expect(normalized.path.is_absolute(), "normalized path is absolute");
        std::error_code error;
        expect(std::filesystem::equivalent(normalized.path, fixture.path(), error) && !error,
               "normalized path is equivalent to fixture");
    }

    for (int iteration = 0; iteration < 200; ++iteration) {
        expect(current_directory().ok(), "repeated current_directory");
        expect(temporary_directory().ok(), "repeated temporary_directory");
        expect(normalize_absolute(".").ok(), "repeated normalize_absolute");
    }
    return finish_case();
}

bool run_unicode() {
    begin_case();
    TempFixture fixture;
    expect(fixture.valid(), "unicode fixture created");
    if (!fixture.valid()) {
        return finish_case();
    }

    const std::u8string name = u8"caminho-ç-日本-🚀";
    const auto directory = fixture.path() / std::filesystem::path(name);
    std::error_code error;
    std::filesystem::create_directories(directory, error);
    expect(!error, "unicode directory created");

    const auto normalized = normalize_absolute(directory);
    expect(normalized.ok(), "unicode normalize_absolute succeeds");
    const auto text = to_utf8(normalized.path);
    expect(text.ok(), "unicode to_utf8 succeeds");
    expect(text.utf8.find("caminho-") != std::string::npos, "unicode ASCII prefix preserved");

    const std::u8string round_trip_u8(reinterpret_cast<const char8_t*>(text.utf8.data()), text.utf8.size());
    const std::filesystem::path round_trip(round_trip_u8);
    std::error_code equivalent_error;
    expect(std::filesystem::equivalent(round_trip, directory, equivalent_error) && !equivalent_error,
           "unicode UTF-8 round-trip is equivalent");

    const std::u8string composed = u8"café";
    const std::u8string decomposed = u8"cafe\u0301";
    expect(to_utf8(std::filesystem::path(composed)).ok(), "composed Unicode path converts");
    expect(to_utf8(std::filesystem::path(decomposed)).ok(), "decomposed Unicode path converts");
    expect(bytes_of(composed) != bytes_of(decomposed), "no Unicode normalization is imposed");
    return finish_case();
}

bool run_traversal() {
    begin_case();
    TempFixture fixture;
    expect(fixture.valid(), "traversal fixture created");
    if (!fixture.valid()) {
        return finish_case();
    }

    std::error_code error;
    std::filesystem::create_directories(fixture.path() / "sub", error);
    expect(!error, "traversal subdirectory created");

    const auto inside = normalize_within_root(fixture.path(), "sub/../file.txt");
    expect(inside.ok(), "contained normalization succeeds");
    expect(inside.path.filename() == "file.txt", "contained normalization preserves filename");
    std::error_code equivalent_error;
    expect(std::filesystem::equivalent(inside.path.parent_path(), fixture.path(), equivalent_error)
               && !equivalent_error,
           "contained normalization stays under root");

    const auto escape = normalize_within_root(fixture.path(), fixture.path() / ".." / "escape.txt");
    expect(escape.error == PathError::PathTraversalRejected, "parent traversal rejected");

    const auto outside = normalize_within_root(fixture.path(), fixture.path().parent_path());
    expect(outside.error == PathError::PathTraversalRejected, "absolute outside path rejected");

    const auto relative_inside = normalize_within_root(fixture.path(), "sub");
    expect(relative_inside.ok(), "relative contained path succeeds");
    return finish_case();
}

bool run_errors() {
    begin_case();
    expect(normalize_absolute(std::filesystem::path{}).error == PathError::InvalidPath,
           "empty path rejected");
    bool nul_rejected = false;
    try {
        nul_rejected = normalize_absolute(std::filesystem::path(std::string("a\0b", 3))).error
                       == PathError::InvalidPath;
    } catch (const std::exception&) {
        nul_rejected = true;
    }
    expect(nul_rejected, "embedded NUL rejected");

    std::u8string invalid;
    invalid.push_back(static_cast<char8_t>(0xFF));
    bool invalid_utf8_rejected = false;
    try {
        const std::filesystem::path invalid_path(invalid);
        invalid_utf8_rejected = normalize_absolute(invalid_path).error == PathError::InvalidPath
                                && to_utf8(invalid_path).error == PathError::InvalidPath;
    } catch (const std::exception&) {
        invalid_utf8_rejected = true;
    }
    expect(invalid_utf8_rejected, "invalid UTF-8 rejected");

    TempFixture fixture;
    expect(fixture.valid(), "errors fixture created");
    if (!fixture.valid()) {
        return finish_case();
    }

    ProcessPathsTestAccess::force_error(std::errc::permission_denied);
    expect(current_directory().error == PathError::AccessDenied, "forced cwd access denied");
    expect(temporary_directory().error == PathError::AccessDenied, "forced temp access denied");
    expect(normalize_within_root(fixture.path(), "x").error == PathError::AccessDenied,
           "forced path access denied");
    expect(normalize_absolute(".").error == PathError::AccessDenied, "forced normalize access denied");
    ProcessPathsTestAccess::clear_forced_error();

    ProcessPathsTestAccess::force_error(std::errc::no_such_file_or_directory);
    expect(current_directory().error == PathError::CurrentDirectoryUnavailable,
           "forced cwd unavailable");
    expect(temporary_directory().error == PathError::TemporaryDirectoryUnavailable,
           "forced temp unavailable");
    expect(normalize_within_root(fixture.path(), "x").error == PathError::NotFound,
           "forced path not found");
    ProcessPathsTestAccess::clear_forced_error();

    expect(normalize_within_root(fixture.path() / "missing-root", "x").error == PathError::NotFound,
           "missing root rejected");

    std::ofstream marker(fixture.path() / "root-file.txt");
    marker << "x";
    marker.close();
    expect(normalize_within_root(fixture.path() / "root-file.txt", "x").error == PathError::InvalidPath,
           "non-directory root rejected");
    return finish_case();
}

bool run_no_write() {
    begin_case();
    TempFixture fixture;
    expect(fixture.valid(), "no-write fixture created");
    if (!fixture.valid()) {
        return finish_case();
    }

    std::error_code error;
    std::filesystem::create_directories(fixture.path() / "observe", error);
    expect(!error, "observe directory created");
    {
        std::ofstream marker(fixture.path() / "observe" / "marker.txt");
        marker << "marker";
        marker.close();
        expect(!marker.fail(), "marker written");
    }

    const auto before = snapshot(fixture.path());
    for (int iteration = 0; iteration < 50; ++iteration) {
        (void)current_directory();
        (void)temporary_directory();
        (void)normalize_absolute(fixture.path());
        (void)normalize_within_root(fixture.path(), "observe/marker.txt");
        (void)to_utf8(fixture.path());
    }
    const auto after = snapshot(fixture.path());
    expect(before == after, "read-only queries do not create or remove entries");

    const auto size = std::filesystem::file_size(fixture.path() / "observe" / "marker.txt", error);
    expect(!error && size == static_cast<std::uintmax_t>(6), "marker file remains unchanged");
    return finish_case();
}

bool run_symlink() {
    begin_case();
    TempFixture fixture;
    expect(fixture.valid(), "symlink fixture created");
    if (!fixture.valid()) {
        return finish_case();
    }

    std::error_code error;
    std::filesystem::create_directories(fixture.path() / "real", error);
    expect(!error, "symlink target created");

    std::filesystem::create_directory_symlink(fixture.path() / "real", fixture.path() / "link", error);
    if (error) {
        note("symlink creation unavailable; inside/escape symlink cases not executed");
        return finish_case();
    }
    expect(normalize_within_root(fixture.path(), "link").ok(), "inside symlink accepted");

    std::filesystem::create_directory_symlink(fixture.path().parent_path(), fixture.path() / "escape", error);
    if (error) {
        note("escape symlink creation unavailable; escape symlink case not executed");
        return finish_case();
    }
    expect(normalize_within_root(fixture.path(), "escape").error == PathError::PathTraversalRejected,
           "symlink escaping root rejected");
    return finish_case();
}

bool run_access() {
    begin_case();
#if !defined(_WIN32)
    TempFixture fixture;
    expect(fixture.valid(), "access fixture created");
    if (!fixture.valid()) {
        return finish_case();
    }
    if (::geteuid() == 0) {
        note("running as root; real POSIX access-denial case not qualified");
        return finish_case();
    }

    const auto denied = fixture.path() / "denied";
    std::error_code error;
    std::filesystem::create_directory(denied, error);
    expect(!error, "denied directory created");
    if (::chmod(denied.c_str(), 0) != 0) {
        note("chmod unavailable; real POSIX access-denial case not qualified");
        return finish_case();
    }

    const auto result = normalize_within_root(fixture.path(), denied / "child");
    expect(result.error == PathError::AccessDenied, "real POSIX access denial maps to AccessDenied");
    (void)::chmod(denied.c_str(), 0700);
#else
    note("real Windows ACL denial is environment-dependent; deterministic mapping covered by errors test");
#endif
    return finish_case();
}

} // namespace

int main(int argc, char** argv) {
    const std::string_view mode = argc > 1 ? std::string_view(argv[1]) : std::string_view("all");

    try {
        bool ok = true;
        if (mode == "all" || mode == "basic") {
            ok = run_basic() && ok;
        }
        if (mode == "all" || mode == "unicode") {
            ok = run_unicode() && ok;
        }
        if (mode == "all" || mode == "traversal") {
            ok = run_traversal() && ok;
        }
        if (mode == "all" || mode == "errors") {
            ok = run_errors() && ok;
        }
        if (mode == "all" || mode == "no_write") {
            ok = run_no_write() && ok;
        }
        if (mode == "all" || mode == "symlink") {
            ok = run_symlink() && ok;
        }
        if (mode == "all" || mode == "access") {
            ok = run_access() && ok;
        }

        if (mode != "all" && mode != "basic" && mode != "unicode" && mode != "traversal"
            && mode != "errors" && mode != "no_write" && mode != "symlink" && mode != "access") {
            std::cerr << "Unknown test mode: " << mode << '\n';
            return 2;
        }

        if (ok) {
            std::cout << "PASS: " << mode << '\n';
            return 0;
        }
        std::cerr << "FAIL: " << mode << '\n';
        return 1;
    } catch (const std::exception& error) {
        std::cerr << "FAIL: uncaught exception: " << error.what() << '\n';
        return 1;
    }
}
