cmake_minimum_required(VERSION 3.27)
project(stormline_core01_internal LANGUAGES CXX)

option(STORMLINE_CORE01_ENABLE_SANITIZERS "Enable ASan/UBSan for the internal headless slice" OFF)

add_library(stormline_core01_headless STATIC
    src/stormline/core/internal/headless_host.cpp
)
target_include_directories(stormline_core01_headless PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
target_compile_features(stormline_core01_headless PUBLIC cxx_std_20)
set_target_properties(stormline_core01_headless PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

if(MSVC)
    target_compile_options(stormline_core01_headless PRIVATE /W4 /WX)
else()
    target_compile_options(stormline_core01_headless PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

if(STORMLINE_CORE01_ENABLE_SANITIZERS)
    if(MSVC)
        message(FATAL_ERROR "Sanitizers are not enabled for the MSVC internal slice")
    endif()
    target_compile_options(stormline_core01_headless PRIVATE
        -fsanitize=address,undefined
        -fno-omit-frame-pointer
    )
    target_link_options(stormline_core01_headless PRIVATE
        -fsanitize=address,undefined
    )
endif()

add_executable(stormline_core01_headless_test
    tests/core/headless_host_tests.cpp
)
target_link_libraries(stormline_core01_headless_test PRIVATE stormline_core01_headless)
target_compile_features(stormline_core01_headless_test PRIVATE cxx_std_20)
set_target_properties(stormline_core01_headless_test PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

if(MSVC)
    target_compile_options(stormline_core01_headless_test PRIVATE /W4 /WX)
else()
    target_compile_options(stormline_core01_headless_test PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

if(STORMLINE_CORE01_ENABLE_SANITIZERS AND NOT MSVC)
    target_compile_options(stormline_core01_headless_test PRIVATE
        -fsanitize=address,undefined
        -fno-omit-frame-pointer
    )
    target_link_options(stormline_core01_headless_test PRIVATE
        -fsanitize=address,undefined
    )
endif()

enable_testing()

add_test(NAME core01_headless_lifecycle
    COMMAND stormline_core01_headless_test lifecycle
)
add_test(NAME core01_headless_errors
    COMMAND stormline_core01_headless_test errors
)
add_test(NAME core01_headless_cleanup
    COMMAND stormline_core01_headless_test cleanup
)
add_test(NAME core01_headless_destructor
    COMMAND stormline_core01_headless_test destructor
)
add_test(NAME core01_headless_invalid
    COMMAND stormline_core01_headless_test invalid
)

set_tests_properties(
    core01_headless_lifecycle
    core01_headless_errors
    core01_headless_cleanup
    core01_headless_destructor
    core01_headless_invalid
    PROPERTIES TIMEOUT 60
)
