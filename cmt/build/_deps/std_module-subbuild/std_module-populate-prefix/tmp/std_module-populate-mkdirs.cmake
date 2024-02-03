# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/hank/Development/trash/cmt/build/_deps/std_module-src"
  "/Users/hank/Development/trash/cmt/build/_deps/std_module-build"
  "/Users/hank/Library/Mobile Documents/com~apple~CloudDocs/Development/trash/cmt/build/_deps/std_module-subbuild/std_module-populate-prefix"
  "/Users/hank/Library/Mobile Documents/com~apple~CloudDocs/Development/trash/cmt/build/_deps/std_module-subbuild/std_module-populate-prefix/tmp"
  "/Users/hank/Library/Mobile Documents/com~apple~CloudDocs/Development/trash/cmt/build/_deps/std_module-subbuild/std_module-populate-prefix/src/std_module-populate-stamp"
  "/Users/hank/Library/Mobile Documents/com~apple~CloudDocs/Development/trash/cmt/build/_deps/std_module-subbuild/std_module-populate-prefix/src"
  "/Users/hank/Library/Mobile Documents/com~apple~CloudDocs/Development/trash/cmt/build/_deps/std_module-subbuild/std_module-populate-prefix/src/std_module-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/hank/Library/Mobile Documents/com~apple~CloudDocs/Development/trash/cmt/build/_deps/std_module-subbuild/std_module-populate-prefix/src/std_module-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/hank/Library/Mobile Documents/com~apple~CloudDocs/Development/trash/cmt/build/_deps/std_module-subbuild/std_module-populate-prefix/src/std_module-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
