cmake_minimum_required(VERSION 3.30.0 FATAL_ERROR)

set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD
  # This specific value changes as experimental support evolves. See
  # `Help/dev/experimental.rst` in the CMake source corresponding to
  # your CMake build for the exact value to use.
  "0e5b6991-d74f-4b3d-a41c-cf096e0b2508")

project(shits LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
set(CMAKE_EXE_LINKER_FLAGS "-lc++abi")
set(CMAKE_CXX_MODULE_STD 1)
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(shitslib
  STATIC
  src/shits.cpp
  src/any.cpp
  src/algo.cpp
  src/homework.cpp
  src/anytest.cpp
  src/test.cpp
)

target_include_directories(shitslib
  PUBLIC
  include
)

add_executable(main
  apps/main.cpp
)

target_link_libraries(main PUBLIC shitslib)
