project(memory)

if( NOT DEFINED DTYPE )
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DTYPE=double")
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DTYPE=${DTYPE}")
endif()

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
  # using Intel C++
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=core-avx2")
else ()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mavx2")
endif ()

add_executable(Example01 matrix_product.cpp) 
add_executable(Example02 matrix_product_contiguous.cpp) 
