project(memory)

if( NOT DEFINED ${DTYPE} )
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DTYPE=float")
endif()

add_executable(Example01 matrix_product.cpp) 
add_executable(Example02 matrix_product_contiguous.cpp) 
