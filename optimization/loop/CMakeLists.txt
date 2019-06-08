project(loops)

find_package(Boost REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DBOOST_DISABLE_ASSERTS")

include_directories(${Boost_INCLUDE_DIRS})

add_executable(Example03 loop.cpp)
add_executable(Example04 loop_reordered.cpp)