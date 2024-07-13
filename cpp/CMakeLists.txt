cmake_minimum_required(VERSION 3.28.0 FATAL_ERROR)

project(shits LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(std.cmake)

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
