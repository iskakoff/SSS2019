/* Compute the dot product of two (properly aligned) vectors. */
#include <iostream>
#include <immintrin.h>
#include <cmath>
#include <chrono>
#include <array>

const int N = 8030;
const int N_ITER = 10000;
const int N_Warmup = 10;

double dot_product(const std::array<double, N> &a, const std::array<double, N> &b) {
  double answer = 0.0;
  for(int ii = 0; ii < N; ++ii)
    answer += a[ii]*b[ii];
  return answer;
}

int main() {
  std::array<double, N> a, b;

  for(int ii = 0; ii < N; ++ii)
    a[ii] = b[ii] = ii/std::sqrt(N);

  for(int iter = 0; iter< N_Warmup; ++iter) {
    dot_product(a, b);
  }
  auto t1 = std::chrono::high_resolution_clock::now();
  double answer = 0;
  for(int iter = 0; iter< N_ITER; ++iter) {
    answer += dot_product(a, b);
  }
  auto t2 = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> time = t2 - t1;

  std::cout << "Dot product using loops time: " << time.count() << " s\n";
  std::cout << "Result: " << answer <<std::endl;
}


