cmake_minimum_required(VERSION 3.27)
project(stormline_core01_internal LANGUAGES CXX)

option(STORMLINE_CORE01_ENABLE_SANITIZERS "Enable ASan/UBSan for the internal CORE-01 slice" OFF)

function(stormline_core01_apply_options target scope)
    target_compile_features(${target} ${scope} cxx_std_20)
    set_target_properties(${target} PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
    )
    if(MSVC)
        target_compile_options(${target} PRIVATE /W4 /WX)
    else()
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic -Werror)
    endif()
    if(STORMLINE_CORE01_ENABLE_SANITIZERS)
        if(MSVC)
            message(FATAL_ERROR "Sanitizers are not enabled for the MSVC internal slice")
        endif()
        target_compile_options(${target} PRIVATE
            -fsanitize=address,undefined
            -fno-omit-frame-pointer
        )
        target_link_options(${target} PRIVATE
            -fsanitize=address,undefined
        )
    endif()
endfunction()

add_library(stormline_core01_headless STATIC
    src/stormline/core/internal/headless_host.cpp
)
target_include_directories(stormline_core01_headless PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
stormline_core01_apply_options(stormline_core01_headless PUBLIC)

add_library(stormline_core01_paths STATIC
    src/stormline/core/internal/process_paths.cpp
)
target_include_directories(stormline_core01_paths PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
stormline_core01_apply_options(stormline_core01_paths PUBLIC)

add_executable(stormline_core01_headless_test
    tests/core/headless_host_tests.cpp
)
target_link_libraries(stormline_core01_headless_test PRIVATE stormline_core01_headless)
stormline_core01_apply_options(stormline_core01_headless_test PRIVATE)

add_executable(stormline_core01_paths_test
    tests/core/process_paths_tests.cpp
)
target_link_libraries(stormline_core01_paths_test PRIVATE stormline_core01_paths)
stormline_core01_apply_options(stormline_core01_paths_test PRIVATE)

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

add_test(NAME core01_paths_basic
    COMMAND stormline_core01_paths_test basic
)
add_test(NAME core01_paths_unicode
    COMMAND stormline_core01_paths_test unicode
)
add_test(NAME core01_paths_traversal
    COMMAND stormline_core01_paths_test traversal
)
add_test(NAME core01_paths_errors
    COMMAND stormline_core01_paths_test errors
)
add_test(NAME core01_paths_no_write
    COMMAND stormline_core01_paths_test no_write
)
add_test(NAME core01_paths_symlink
    COMMAND stormline_core01_paths_test symlink
)
add_test(NAME core01_paths_access
    COMMAND stormline_core01_paths_test access
)

set_tests_properties(
    core01_headless_lifecycle
    core01_headless_errors
    core01_headless_cleanup
    core01_headless_destructor
    core01_headless_invalid
    core01_paths_basic
    core01_paths_unicode
    core01_paths_traversal
    core01_paths_errors
    core01_paths_no_write
    core01_paths_symlink
    core01_paths_access
    PROPERTIES TIMEOUT 60
)
