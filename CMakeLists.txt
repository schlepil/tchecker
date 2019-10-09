# This file is a part of the TChecker project.
#
# See files AUTHORS and LICENSE for copyright details.

cmake_minimum_required(VERSION 2.8)
project(tchecker LANGUAGES CXX)

include("${CMAKE_SOURCE_DIR}/cmake/CheckCompilerFlags.cmake")
#-gcc
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmax-errors=10")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DCMAKE_CXX_COMPILER=clang++-8 -fPIC")


# The project version number.
set(VERSION_MAJOR   0   CACHE STRING "Project major version number.")
set(VERSION_MINOR   2   CACHE STRING "Project minor version number.")
mark_as_advanced(VERSION_MAJOR VERSION_MINOR)

add_subdirectory(include)
add_subdirectory(src)

enable_testing()
add_subdirectory(test)
