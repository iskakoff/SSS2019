
#include <vector>
#include <cmath>
#include <boost/multi_array.hpp>

void init_grid(std::vector<double>& grid,int N, double beta) {
  grid.resize(N);
  double delta = beta/(N+1);
  for(int i = 0; i<N; ++i) {
    grid[i] = delta*i;
  }
}

void init_G(boost::multi_array<double, 3> & G) {
  for(int i1 = 0; i1 < G.shape()[0]; ++i1) {
    for(int i2 = 0; i2< G.shape()[1]; ++i2) {
      for(int i3 = 0; i3< G.shape()[2]; ++i3) {
        G[i1][i2][i3] = i1*std::sqrt(G.shape()[2]) + i2*std::sqrt(G.shape()[1]) + i3 + 0.5;
      }
    }
  }
}