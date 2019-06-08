
#include <iostream>
#include <cmath>
#include <vector>
#include <chrono>
#include <sstream>

const int N_ITER = 5;
const int N = 500;

template<typename X>
void init(std::vector<std::vector<X> >&x) {
  for(int i = 0; i< N; ++i) {
    for(int j = 0; j< N; ++j ) {
      x[i][j] = i*std::sqrt(N) + j*std::sqrt(N+5) + 2;
    }
  }
}

template<typename X>
void prod(const std::vector<std::vector<X> >& x, const std::vector<std::vector<X> >& y, std::vector<std::vector<X> >& z) {
  for(int i = 0; i< N; ++i) {
    for(int j = 0; j< N; ++j ) { 
      for(int k = 0; k< N; ++k ) { 
        z[i][j] += x[i][k]*y[k][j];
      }
    }
  }
}

template<typename X>
void vector_of_vectors() {
  std::vector<std::vector<X> > x(N, std::vector<X>(N, 0));
  std::vector<std::vector<X> > y(N, std::vector<X>(N, 0));
  std::vector<std::vector<X> > z(N, std::vector<X>(N, 0));
  X tmp = 0;
  init(x);
  init(y);

  auto t1 = std::chrono::high_resolution_clock::now();
  for(int it = 0; it < N_ITER; ++it){
    prod(x, y, z);
  }
  auto t2 = std::chrono::high_resolution_clock::now();
  tmp += z[0][0];
  std::stringstream sss;
  sss<<tmp;

  std::chrono::duration<double> elapsed = t2 - t1; 
  std::cout<<"Matrix product time: "<<elapsed.count()<<std::endl;
}

int main() {
  vector_of_vectors<TYPE>();
}
