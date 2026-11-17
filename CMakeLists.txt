cmake_minimum_required(VERSION 3.27)
project(stormline_core01_internal LANGUAGES C CXX)

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

include(FetchContent)

# Pinned official SDL3 3.4.20 source, fetched at build time only. No system
# install, vendor copy, package manager or runtime download.
set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_STATIC ON CACHE BOOL "" FORCE)
set(SDL_TEST_LIBRARY OFF CACHE BOOL "" FORCE)
set(SDL_TESTS OFF CACHE BOOL "" FORCE)
set(SDL_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SDL_INSTALL OFF CACHE BOOL "" FORCE)
set(SDL_AUDIO OFF CACHE BOOL "" FORCE)
set(SDL_JOYSTICK OFF CACHE BOOL "" FORCE)
set(SDL_HAPTIC OFF CACHE BOOL "" FORCE)
set(SDL_HIDAPI OFF CACHE BOOL "" FORCE)
set(SDL_SENSOR OFF CACHE BOOL "" FORCE)
set(SDL_POWER OFF CACHE BOOL "" FORCE)
set(SDL_CAMERA OFF CACHE BOOL "" FORCE)
set(SDL_X11 OFF CACHE BOOL "" FORCE)
set(SDL_WAYLAND OFF CACHE BOOL "" FORCE)
set(SDL_KMSDRM OFF CACHE BOOL "" FORCE)
set(SDL_UNIX_CONSOLE_BUILD ON CACHE BOOL "" FORCE)
set(SDL_RENDER OFF CACHE BOOL "" FORCE)
set(SDL_RENDER_GPU OFF CACHE BOOL "" FORCE)
set(SDL_RENDER_VULKAN OFF CACHE BOOL "" FORCE)
set(SDL_RENDER_METAL OFF CACHE BOOL "" FORCE)
set(SDL_RENDER_D3D OFF CACHE BOOL "" FORCE)
set(SDL_RENDER_D3D11 OFF CACHE BOOL "" FORCE)
set(SDL_RENDER_D3D12 OFF CACHE BOOL "" FORCE)
set(SDL_VULKAN OFF CACHE BOOL "" FORCE)
set(SDL_OPENGL OFF CACHE BOOL "" FORCE)
set(SDL_OPENGLES OFF CACHE BOOL "" FORCE)
set(SDL_METAL OFF CACHE BOOL "" FORCE)
set(SDL_GPU OFF CACHE BOOL "" FORCE)
set(SDL_DUMMYAUDIO OFF CACHE BOOL "" FORCE)
set(SDL_DISKAUDIO OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG f00dc919ca35b9756316e86c4777392de442f9b2
    GIT_SHALLOW FALSE
)
FetchContent_MakeAvailable(SDL3)

if(TARGET SDL3::SDL3-static)
    get_target_property(SDL3_INTERFACE_INCLUDES SDL3::SDL3-static INTERFACE_INCLUDE_DIRECTORIES)
    if(SDL3_INTERFACE_INCLUDES)
        set_property(TARGET SDL3::SDL3-static PROPERTY
            INTERFACE_SYSTEM_INCLUDE_DIRECTORIES "${SDL3_INTERFACE_INCLUDES}")
    endif()
endif()

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

add_library(stormline_core01_sdl STATIC
    src/stormline/core/internal/sdl_runtime.cpp
)
target_include_directories(stormline_core01_sdl PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
target_link_libraries(stormline_core01_sdl PRIVATE SDL3::SDL3-static)
stormline_core01_apply_options(stormline_core01_sdl PUBLIC)

add_executable(stormline_core01_sdl_test
    tests/core/sdl_runtime_tests.cpp
)
target_link_libraries(stormline_core01_sdl_test PRIVATE stormline_core01_sdl)
stormline_core01_apply_options(stormline_core01_sdl_test PRIVATE)

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

add_test(NAME core01_sdl_basic
    COMMAND stormline_core01_sdl_test basic
)
add_test(NAME core01_sdl_wrong_thread
    COMMAND stormline_core01_sdl_test wrong_thread
)
add_test(NAME core01_sdl_init_failure
    COMMAND stormline_core01_sdl_test init_failure
)
add_test(NAME core01_sdl_destructor
    COMMAND stormline_core01_sdl_test destructor
)
add_test(NAME core01_sdl_version
    COMMAND stormline_core01_sdl_test version
)
add_test(NAME core01_sdl_header
    COMMAND stormline_core01_sdl_test header
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
    core01_sdl_basic
    core01_sdl_wrong_thread
    core01_sdl_init_failure
    core01_sdl_destructor
    core01_sdl_version
    core01_sdl_header
    PROPERTIES TIMEOUT 180
)

set_tests_properties(
    core01_sdl_basic
    core01_sdl_wrong_thread
    core01_sdl_init_failure
    core01_sdl_destructor
    core01_sdl_version
    core01_sdl_header
    PROPERTIES ENVIRONMENT "SDL_VIDEODRIVER=dummy"
)
