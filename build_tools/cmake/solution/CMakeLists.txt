cmake_minimum_required(VERSION 3.1)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

project(TEST CXX)


find_package(Boost 1.66 REQUIRED COMPONENTS filesystem)

add_executable(main.exe main.cpp)
target_link_libraries(main.exe Boost::filesystem)
