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

CPMAddPackage("gh:nlohmann/json@3.10.5")

add_library(shits
  STATIC
)

target_sources(shits
    PUBLIC
    FILE_SET all_my_modules TYPE CXX_MODULES FILES
    src/shits.cppm
)

target_include_directories(shits
  PUBLIC
  include
)

add_executable(main
  apps/main.cpp
)

target_link_libraries(main PUBLIC shits)
