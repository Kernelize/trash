cmake_minimum_required(VERSION 3.28.0 FATAL_ERROR)

project(HelloWorld LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS YES)

include(std.cmake)

add_executable(main)

target_sources(main
  PRIVATE
    main.cpp
)
