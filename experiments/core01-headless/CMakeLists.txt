cmake_minimum_required(VERSION 3.27)
project(stormline_core01_experimental_smoke LANGUAGES CXX)

add_executable(stormline_core01_headless_smoke headless_host_smoke.cpp)
target_compile_features(stormline_core01_headless_smoke PRIVATE cxx_std_20)
set_target_properties(stormline_core01_headless_smoke PROPERTIES
    CXX_EXTENSIONS OFF
    CXX_STANDARD_REQUIRED ON)

if(MSVC)
    target_compile_options(stormline_core01_headless_smoke PRIVATE /W4 /WX)
else()
    target_compile_options(stormline_core01_headless_smoke PRIVATE -Wall -Wextra -Werror -pedantic)
endif()

enable_testing()
add_test(NAME stormline_core01_headless_smoke COMMAND stormline_core01_headless_smoke)
set_tests_properties(stormline_core01_headless_smoke PROPERTIES TIMEOUT 20)
