cmake_minimum_required(VERSION 3.12)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
project(simons_examples C CXX)

set(CMAKE_CXX_STANDARD 11)

if (NOT CMAKE_BUILD_TYPE) 
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING
      "Choose the type of build, options are: Debug Release
RelWithDebInfo MinSizeRel."
      FORCE)
endif()

add_subdirectory(memory)
add_subdirectory(memory_access_patterns)
add_subdirectory(loop)
add_subdirectory(avx2)


