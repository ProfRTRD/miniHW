#include <iostream>
#include <valarray>
#include <cmath>
#include <iomanip>
#include <numeric>
#include <vector>


int main(void)
{
  const int N =1000;
  std::valarray<double> v1(N);
  std::iota(v1.begin(), v1.end(), 0.0);
  const double DX = 2*M_PI/N;
  v1=v1*DX;
  std::valarray<double> v2 = std::sin(v1);
  v2 = v2[std::abs(v2) < 0.5];
  for(auto n : v2) {
    if(n!=0){
      std::cout << n<<"  ";
    }
    std::cout << "/n";
  }
}
