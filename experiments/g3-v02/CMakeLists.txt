cmake_minimum_required(VERSION 3.27)
project(stormline_g3_v02_probe LANGUAGES CXX)

# Intentionally isolated from all Stormline engine targets and dependencies.
add_executable(stormline_g3_v02_probe main.cpp)
target_compile_features(stormline_g3_v02_probe PRIVATE cxx_std_20)
set_target_properties(stormline_g3_v02_probe PROPERTIES
  CXX_STANDARD 20
  CXX_STANDARD_REQUIRED YES
  CXX_EXTENSIONS NO
)
enable_testing()
add_test(NAME g3_v02_cpp20_smoke COMMAND $<TARGET_FILE:stormline_g3_v02_probe>)
