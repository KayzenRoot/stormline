// NLE-G3-V02-EXP-001: disposable, deterministic C++20 toolchain smoke test.
// This is NOT Stormline engine code and exposes no public API or ABI.
#include <bit>
#include <cstdint>
#include <iostream>
#include <string_view>
#include <type_traits>

#define STORM_G3_STR_IMPL(value) #value
#define STORM_G3_STR(value) STORM_G3_STR_IMPL(value)

static_assert(__cplusplus >= 202002L, "C++20 compiler required");
static_assert(sizeof(std::uint32_t) == 4U);
static_assert(std::bit_cast<std::uint32_t>(1.0F) == 0x3F800000U);
static_assert(std::is_same_v<std::remove_cvref_t<const int&>, int>);

int main() {
  constexpr std::string_view marker{"STORMLINE_G3_V02_SMOKE_OK"};
  if (marker.size() != 25U) {
    return 2;
  }
  std::cout << marker << " CXX=" << STORM_G3_STR(__cplusplus) << '\n';
#if defined(_MSC_FULL_VER)
  std::cout << "MSVC_FULL_VER=" << STORM_G3_STR(_MSC_FULL_VER) << '\n';
#elif defined(__apple_build_version__)
  std::cout << "APPLE_CLANG_BUILD=" << STORM_G3_STR(__apple_build_version__) << '\n';
#elif defined(__clang__)
  std::cout << "CLANG=" << __clang_major__ << '.' << __clang_minor__ << '.' << __clang_patchlevel__ << '\n';
#elif defined(__GNUC__)
  std::cout << "GCC=" << __GNUC__ << '.' << __GNUC_MINOR__ << '.' << __GNUC_PATCHLEVEL__ << '\n';
#endif
  return 0;
}
