#include <iostream>
#include <valarray>
#include <cmath>
#include <iomanip>
#include <numeric>
#include <vector>


int main(void)
{
  const int N = 1000;
  std::valarray<double> v1(N);
  std::iota(std::begin(v1), std::end(v1), 0.0);
  const double DX = 2*M_PI/N;
  v1=v1*DX;
  std::valarray<double> v2 = std::abs(std::sin(v1));
  v2 = v2[v2 < 0.5];
  for(int n : v2) std::cout << n <<std::endl;
}

