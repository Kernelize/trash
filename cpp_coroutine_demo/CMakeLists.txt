# CMake 3.30 is required for C++23 `import std` support; we use 3.29.20240416
# here so that in-development versions satisfy it. 
cmake_minimum_required(VERSION 3.29.20240416 FATAL_ERROR)

project(cpp_coroutine_demo LANGUAGES CXX)

# Set experimental flag to enable `import std` support from CMake.
# This must be enabled before C++ language support.
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD
  # This specific value changes as experimental support evolves. See
  # `Help/dev/experimental.rst` in the CMake source corresponding to
  # your CMake build for the exact value to use.
  "0e5b6991-d74f-4b3d-a41c-cf096e0b2508")

# Tell CMake that we explicitly want `import std`. This will initialize the
# property on all targets declared after this to 1
set(CMAKE_CXX_MODULE_STD 1)

# Default to C++ extensions being off. Clang's modules support have trouble
# with extensions right now and it is not required for any other compiler
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP ON)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)

include(cmake/CPM.cmake)
# include(cmake/std.cmake)

CPMAddPackage(
  NAME asyncsimple
  GITHUB_REPOSITORY alibaba/async_simple
  GIT_TAG main
  OPTIONS "ASYNC_SIMPLE_BUILD_MODULES ON"
)

# CPMAddPackage(
#   NAME nlohmann_json
#   VERSION 3.9.1
#   GITHUB_REPOSITORY nlohmann/json
#   OPTIONS
#     "JSON_BuildTests OFF"
# )

# CPMAddPackage("gh:ericniebler/range-v3 #0.12.0")

# CPMAddPackage("gh:catchorg/Catch2@2.5.0")

# the install option has to be explicitly set to allow installation
# CPMAddPackage(
#   GITHUB_REPOSITORY jarro2783/cxxopts
#   VERSION 2.2.1
#   OPTIONS "CXXOPTS_BUILD_EXAMPLES NO" "CXXOPTS_BUILD_TESTS NO" "CXXOPTS_ENABLE_INSTALL YES"
# )

# CPMAddPackage(
#   NAME benchmark
#   GITHUB_REPOSITORY google/benchmark
#   VERSION 1.5.2
#   OPTIONS "BENCHMARK_ENABLE_TESTING Off"
# )
#
# if(benchmark_ADDED)
#   # enable c++11 to avoid compilation errors
#   set_target_properties(benchmark PROPERTIES CXX_STANDARD 11)
# endif()

add_library(asyncserver
  STATIC
)

target_link_libraries(asyncserver PRIVATE asyncsimple)

target_sources(asyncserver
    PRIVATE
    FILE_SET all_my_modules TYPE CXX_MODULES FILES
    src/AsyncServer.cppm
)


add_executable(main
  apps/main.cpp
)

target_link_libraries(main PUBLIC asyncserver)

