//ZAIR VALENTIN BARETO TORRES
//JUAN JOSE GONZALEZ FLOREZ
#include <iostream>
#include <cmath>
#include <cstdlib>

template <typename fptr>
double trapezoid_regular(double a, double b, int n, fptr func);
double integ_exact(double a, double b); 

int main(int argc, char **argv)
{
  const int N = std::atoi(argv[1]);
  auto myfun = [](double x){return std::sin(x); };
  std::cout.precision(15); std::cout.setf(std::ios::scientific);
  //error relativo
  double porcerror = (std::fabs(integ_exact(0.0, M_PI) - trapezoid_regular(0.0, M_PI, N, myfun)))/(std::fabs(integ_exact(0.0, M_PI)));

  std::cout << N <<"   "<<porcerror<< std::endl;

  return 0;
}

template <typename fptr>
double trapezoid_regular(double a, double b, int n, fptr func)
{
  double h = (b-a)/n;
  double xi = 0;
  double xi2 = 0;
  double suma = 0;
  for (int ii=0; ii <= n-1; ii++)
    {
      xi = a + ii*h;
      xi2 = a + (ii+1)*h;
      suma += h*(func(xi)+func(xi2));
    }
  return 0.5*suma;
}

double integ_exact(double a, double b)
{
  return -std::cos(b)+std::cos(a);
}
