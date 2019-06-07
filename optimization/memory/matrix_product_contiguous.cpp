
#include <iostream>
#include <cmath>
#include <vector>
#include <chrono>
#include <sstream>

const int N_ITER = 10;
const int N = 500;

template<typename T>
struct matrix {

  matrix(int size) : data(size*size, T(0)), _N(size) {}
  
  T& operator()(int i, int j) {return data[i*_N + j];}
  const T& operator()(int i, int j) const {return data[i*_N + j];}

  std::vector<T> data;
  int _N;
};

template<typename X>
void init(matrix<X>&x) {
  for(int i = 0; i< N; ++i) {
    for(int j = 0; j< N; ++j ) {
      x(i, j) = i*std::sqrt(N) + j*std::sqrt(N+5) + 2;
    }
  }
}

template<typename X>
void prod(const matrix<X>& x, const matrix<X>& y, matrix<X>& z) {
  for(int i = 0; i< N; ++i) {
    for(int j = 0; j< N; ++j ) { 
      for(int k = 0; k< N; ++k ) { 
        z(i,j) += x(i,k) * y(k,j);
      }
    }
  }
}

template<typename X>
void contiguous_storage() {
  matrix<X> x(N);
  matrix<X> y(N);
  matrix<X> z(N);
  X tmp = 0;
  init(x);
  init(y);
  
  auto t1 = std::chrono::high_resolution_clock::now();
  for(int it = 0; it < N_ITER; ++it){
    prod(x, y, z);
  }
  auto t2 = std::chrono::high_resolution_clock::now();
  tmp += z(0,0);
  std::stringstream sss;
  sss<<tmp;

  std::chrono::duration<double> elapsed = t2 - t1; 
  std::cout<<"Contiguous storage matrix prod time: "<<elapsed.count()<<std::endl;
}


int main() {
  contiguous_storage<TYPE>();
}
