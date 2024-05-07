cmake_minimum_required(VERSION 3.29 FATAL_ERROR)

project(shits LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP ON)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)
set(CMAKE_TOOLCHAIN_FILE cmake/toolchain.cmake)

include(cmake/CPM.cmake)
include(cmake/std.cmake)

CPMAddPackage(
  NAME aiopp
  GITHUB_REPOSITORY pfirsich/aiopp
  GIT_TAG main
)

# CPMAddPackage(
#   NAME nlohmann_json
#   VERSION 3.9.1
#   GITHUB_REPOSITORY nlohmann/json
#   OPTIONS
#     "JSON_BuildTests OFF"
# )

# CPMAddPackage("gh:ericniebler/range-v3#0.12.0")

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

add_library(shits
  STATIC
)

target_sources(shits
    PUBLIC
    FILE_SET all_my_modules TYPE CXX_MODULES FILES
    src/shits.cppm
    src/cotest.cppm
)

target_include_directories(shits
  PUBLIC
  include
)

add_executable(main
  apps/main.cpp
)

add_executable(cobin
  apps/cobin.cpp
)

target_link_libraries(main PUBLIC shits)
target_link_libraries(cobin PUBLIC shits)
