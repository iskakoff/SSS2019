
#include <iostream>
#include <chrono>
#include <cmath>
#include <boost/multi_array.hpp>
#include <boost/math/special_functions/legendre.hpp>
#include "init.hpp"


typedef boost::multi_array<double, 3> array_type;

const double DELTA = 0.01;
const double beta = 100.0;

void loop_test(array_type & G_out, const array_type & G_in, const std::vector<double> & grid, int n1, int n2, int n3, int n4, int n5) {
  for(int l=0;l<n1;++l) {
    for (int i = 0; i < n2; ++i) {
      for (int j = 0; j < n3; ++j) {
        G_out[i][j][l] = 0.0;//clear out the arrays
      }
    }
  }
  for(int l=0;l<n1;++l){
    double sqrtl=std::sqrt(2.*l+1.);
    for(int p=0;p<n4;++p){
      double h = DELTA*p;
      for(int t=1;t<n5-1;++t){
        int ntau1 = t-1;
        int ntau2 = t;
        int ntau3 = t+1;
        double legendre_p1 = boost::math::legendre_p(l, (grid[ntau1] / beta - 0.5) * 2.);
        double legendre_p2 = boost::math::legendre_p(l, (grid[ntau2] / beta - 0.5) * 2.);
        double legendre_p3 = boost::math::legendre_p(l, (grid[ntau3] / beta - 0.5) * 2.);
        for(int i=0;i<n2;++i){
          for(int j=0;j<n3;++j){
            G_out[i][j][l] += h / 3. * sqrtl * (G_in[ntau1][i][j] * legendre_p1 +
                                             4.0 * G_in[ntau2][i][j] * legendre_p2 +
                                             G_in[ntau3][i][j] * legendre_p3);
          }
        }
      }
    }
  }
}



int main() {
  int n1 = 100;
  int n2 = 10;
  int n3 = 10;
  int n4 = 20;
  int n5 = 50;
  array_type G_in(boost::extents[n5][n2][n3]);
  array_type G_out(boost::extents[n2][n3][n1]);
  std::vector<double> grid;
  init_grid(grid, n5, beta);
  init_G(G_in);
  auto start = std::chrono::high_resolution_clock::now();
  loop_test(G_out, G_in, grid, n1, n2, n3, n4, n5);
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = end - start;
  std::cout << "Elapsed time: " << elapsed.count() << " s\n";
  std::cout << "G_out[1][2][3] = "<< G_out[1][2][3]<<std::endl;
}
