// NLE-CORE01-QUAL-002: native ABI observability; INTERNAL_ONLY, NOT a public ABI.
// No SDL headers/types or plugin SDK are part of this test contract.
#include "stormline/core/internal/capability_graph.hpp"
#include "stormline/core/internal/headless_host.hpp"
#include "stormline/core/internal/native_bridge.hpp"
#include "stormline/core/internal/sdl_runtime.hpp"
#include "stormline/core/internal/window.hpp"

#include <bit>
#include <cstddef>
#include <cstdint>
#include <initializer_list>
#include <iostream>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>

namespace {
using namespace stormline::core::internal;

#if defined(_MSC_VER)
static_assert(_MSVC_LANG >= 202002L, "CORE-01 requires MSVC /std:c++20");
#else
static_assert(__cplusplus >= 202002L, "CORE-01 requires internal C++20");
#endif
static_assert(std::is_same_v<decltype(NativeWindowHandle{}.value), std::uint64_t>);
static_assert(std::is_same_v<decltype(NativeWindowHandle{}.generation), std::uint64_t>);
static_assert(std::is_same_v<std::underlying_type_t<NativeHandleKind>, std::uint8_t>);
static_assert(std::is_same_v<std::underlying_type_t<NativeWindowSystem>, std::uint8_t>);
static_assert(std::is_same_v<std::underlying_type_t<HostError>, std::uint8_t>);
static_assert(std::is_same_v<std::underlying_type_t<SdlError>, std::uint8_t>);
static_assert(std::is_same_v<std::underlying_type_t<WindowError>, std::uint8_t>);
static_assert(std::is_standard_layout_v<NativeWindowHandle>);
static_assert(std::is_trivially_copyable_v<NativeWindowHandle>);
static_assert(std::is_standard_layout_v<CapabilityRecord>);
static_assert(std::is_trivially_copyable_v<CapabilityRecord>);
static_assert(!std::is_copy_constructible_v<HeadlessHost>);
static_assert(!std::is_copy_assignable_v<HeadlessHost>);
static_assert(!std::is_move_constructible_v<HeadlessHost>);
static_assert(!std::is_copy_constructible_v<SdlRuntime>);
static_assert(!std::is_move_constructible_v<SdlRuntime>);
static_assert(!std::is_copy_constructible_v<Window>);
static_assert(!std::is_move_constructible_v<Window>);
static_assert(!std::is_copy_constructible_v<CapabilityGraph>);
static_assert(!std::is_move_constructible_v<CapabilityGraph>);
static_assert(std::is_nothrow_destructible_v<HeadlessHost>);
static_assert(std::is_nothrow_destructible_v<SdlRuntime>);
static_assert(std::is_nothrow_destructible_v<Window>);
static_assert(alignof(NativeWindowHandle) >= alignof(std::uint64_t));
static_assert(sizeof(NativeWindowHandle) >= sizeof(std::uint64_t) * 2 +
                                             sizeof(NativeHandleKind));

constexpr std::string_view endian_name() {
    if constexpr (std::endian::native == std::endian::little) {
        return "little";
    } else if constexpr (std::endian::native == std::endian::big) {
        return "big";
    } else {
        return "mixed";
    }
}

void print_observed() {
    const std::string runtime{"STORMLINE_ABI_INTERNAL_CXX20"};
    std::cout << "ABI_META marker=" << runtime
              << " cplusplus=" << __cplusplus
#if defined(_MSC_VER)
              << " msvc_lang=" << _MSVC_LANG
#endif
              << " pointer_bytes=" << sizeof(void*)
              << " endian=" << endian_name()
              << " native_handle_bytes=" << sizeof(NativeWindowHandle)
              << " native_handle_align=" << alignof(NativeWindowHandle)
              << " native_handle_kind_bytes=" << sizeof(NativeHandleKind)
              << " capability_record_bytes=" << sizeof(CapabilityRecord)
              << " capability_record_align=" << alignof(CapabilityRecord)
              << " headless_host_bytes=" << sizeof(HeadlessHost)
              << " sdl_runtime_bytes=" << sizeof(SdlRuntime)
              << " window_bytes=" << sizeof(Window)
              << " external_abi=NOT_DEFINED"
              << " stable_cross_compiler_layout=NOT_QUALIFIED"
              << '\n';
#if defined(_MSC_FULL_VER)
    std::cout << "ABI_COMPILER id=MSVC full=" << _MSC_FULL_VER << '\n';
#elif defined(__apple_build_version__)
    std::cout << "ABI_COMPILER id=AppleClang build=" << __apple_build_version__ << '\n';
#elif defined(__clang__)
    std::cout << "ABI_COMPILER id=Clang version=" << __clang_major__ << '.'
              << __clang_minor__ << '.' << __clang_patchlevel__ << '\n';
#elif defined(__GNUC__)
    std::cout << "ABI_COMPILER id=GCC version=" << __GNUC__ << '.'
              << __GNUC_MINOR__ << '.' << __GNUC_PATCHLEVEL__ << '\n';
#endif
#if defined(_GLIBCXX_USE_CXX11_ABI)
    std::cout << "ABI_STDLIB libstdcxx_cxx11_abi=" << _GLIBCXX_USE_CXX11_ABI << '\n';
#elif defined(_LIBCPP_VERSION)
    std::cout << "ABI_STDLIB libcxx_version=" << _LIBCPP_VERSION << '\n';
#elif defined(_MSVC_STL_VERSION)
    std::cout << "ABI_STDLIB msvc_stl_version=" << _MSVC_STL_VERSION << '\n';
#else
    std::cout << "ABI_STDLIB details=NOT_QUALIFIED" << '\n';
#endif
}

bool baseline_layout_is_valid() {
    const NativeWindowHandle handle{};
    return handle.kind == NativeHandleKind::None &&
           handle.value == 0 &&
           handle.generation == 0 &&
           sizeof(std::uint64_t) == 8 &&
           std::is_nothrow_destructible_v<CapabilityGraph>;
}

bool negative_unissued_handle_is_rejected() {
    Window uncreated;
    NativeWindowHandle out{};
    if (uncreated.query_native_handle(out) != WindowError::NotCreated) {
        return false;
    }
    for (const auto kind : {NativeHandleKind::None, NativeHandleKind::X11Window,
                            NativeHandleKind::WaylandSurface, NativeHandleKind::Win32Hwnd,
                            NativeHandleKind::CocoaWindow}) {
        const NativeWindowHandle forged{kind, 42U, 42U};
        if (uncreated.native_handle_valid(forged)) {
            return false;
        }
    }
    return !uncreated.surface_valid(42U) &&
           !uncreated.native_handle_valid(NativeWindowHandle{});
}

} // namespace

int main(int argc, char** argv) {
    if (argc != 2 || argv == nullptr || argv[1] == nullptr) {
        std::cerr << "ABI_FAIL invalid argument count\n";
        return 2;
    }
    const std::string_view test{argv[1]};
    if (test == "positive") {
        if (!baseline_layout_is_valid()) {
            std::cerr << "ABI_FAIL internal header baseline\n";
            return 1;
        }
        print_observed();
        std::cout << "ABI_INTERNAL_POSITIVE_OK typed_ownership=YES native_layout=OBSERVED_ONLY\n";
        return 0;
    }
    if (test == "negative") {
        if (!negative_unissued_handle_is_rejected()) {
            std::cerr << "ABI_FAIL unissued native handle accepted\n";
            return 1;
        }
        std::cout << "ABI_INTERNAL_NEGATIVE_OK unissued_and_forged_handles=REJECTED\n";
        return 0;
    }
    std::cerr << "ABI_FAIL unexpected mode; expected positive or negative\n";
    return 2;
}
