/* Compute the dot product of two (properly aligned) vectors. */
#include <iostream>
#include <immintrin.h>
#include <cmath>
#include <chrono>
#include <array>

const int N = 8030;
const int N_ITER = 10000;
const int N_Warmup = 10;

/* Horizontal add works within 128-bit lanes. Use scalar ops to add
 * across the boundary. */
double reduce_vector1(__m256d input) {
  __m256d temp = _mm256_hadd_pd(input, input);
  return ((double*)&temp)[0] + ((double*)&temp)[2];
}

/* Another way to get around the 128-bit boundary: grab the first 128
 * bits, grab the lower 128 bits and then add them together with a 128
 * bit add instruction. */
double reduce_vector2(__m256d input) {
  __m256d temp = _mm256_hadd_pd(input, input);
  __m128d sum_high = _mm256_extractf128_pd(temp, 1);
  __m128d result = _mm_add_pd(sum_high, _mm256_castpd256_pd128(temp));
  return ((double*)&result)[0];
}

double dot_product(const std::array<double, N> &a, const std::array<double, N> &b) {
  __m256d sum_vec = _mm256_set_pd(0.0, 0.0, 0.0, 0.0);

  /* Add up partial dot-products in blocks of 256 bits */
  for(int ii = 0; ii < N/4; ++ii) {
    __m256d x = _mm256_load_pd(&a[0]+4*ii);
    __m256d y = _mm256_load_pd(&b[0]+4*ii);
    __m256d z = _mm256_mul_pd(x,y);
    sum_vec = _mm256_add_pd(sum_vec, z);
  }

  /* Find the partial dot-product for the remaining elements after
   * dealing with all 256-bit blocks. */
  double final = 0.0;
  for(int ii = N-N%4; ii < N; ++ii)
    final += a[ii] * b[ii];

  return reduce_vector2(sum_vec) + final;
}

int main() {
  alignas (32) std::array<double, N> a, b;

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

  std::cout << "Dot product with explicitly using avx2 instructions time: " << time.count() << " s\n";
  std::cout << "Result: " << answer<<std::endl;
}


