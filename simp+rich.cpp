#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>

double trapezoid_irregular(const std::vector<double> & x, const std::vector<double> & fx);
template <typename fptr>
double trapezoid_regular(const double a, const double b, const int n, fptr func);
template <typename fptr>
double trapezoid_richardson(const double a, const double b, const int n, fptr func);
template <typename fptr>
double simpson(const double a, const double b, const int n, fptr func);
template <typename fptr>
double simpson_rich(const double a, const double b, const int n, fptr func);

int main(int argc, char **argv)
{
  const int N = std::atoi(argv[1]);
  auto myfun = [](double x){return std::sin(x); };
  std::cout.precision(15); std::cout.setf(std::ios::scientific);

  // test on-iregular (modelled as regular to compare)
  std::vector<double> x(N), f(N);
  for (int ii = 0; ii < N; ++ii) {
    x[ii] = 0 + ii*(M_PI-0)/N;
    f[ii] = myfun(x[ii]);
  }
  std::cout << "Non-regular integral is : " << trapezoid_irregular(x, f) << std::endl;

  // test on regular
  //std::cout << "Regular integral (n = 20) is : " << trapezoid_regular(0, M_PI, N, myfun) << std::endl;
  //std::cout << "Regular integral (n = 40) is : " << trapezoid_regular(0, M_PI, N*2, myfun) << std::endl;

  // test with Richardson
  //std::cout << "Richardson integral (n = 20) is : " << trapezoid_richardson(0, M_PI, N, myfun) << std::endl;

  // test with Simpson
  //std::cout << "Simpson integral (n = 20) is : " << simpson(0, M_PI, N, myfun) << std::endl;

  //rich simpson
  //std::cout << "simpson rich test " << simpson_rich(0, M_PI, N, myfun) << std::endl;
  double error_trapez = (std::fabs(2.000000 -  trapezoid_regular(0, M_PI, N, myfun)))/std::fabs(2.000000);;
  double error_rich = (std::fabs(2.000000 - trapezoid_richardson(0, M_PI, N, myfun)))/std::fabs(2.000000);;
  double error_simp = (std::fabs(2.000000 - simpson(0, M_PI, N, myfun)))/std::fabs(2.000000);
  double errorsimp_rich = (std::fabs(2.000000 - simpson_rich(0, M_PI, N, myfun)))/std::fabs(2.000000);

  std::cout << N << std::endl;
  std::cout <<"error trapecio  "<< error_trapez << std::endl;
  std::cout <<"error rich  " << error_rich << std::endl;
  std::cout <<"error simp  "<< error_simp << std::endl;
  std::cout <<"error simp rich  " << errorsimp_rich << std::endl;


  return 0;
}

double trapezoid_irregular(const std::vector<double> & x, const std::vector<double> & fx)
{
  double sum = 0.0;
  for (int ii = 0; ii < x.size() - 1; ++ii) { // note the upper limit
    sum += (x[ii + 1] - x[ii])*(fx[ii] + fx[ii+1]);
  }
  return 0.5*sum;
}

template <typename fptr>
double trapezoid_regular(const double a, const double b, const int n, fptr func)
{
  const double h = (b-a)/n;
  double sum = 0.5*(func(a) + func(b));
  for(int ii = 1; ii < n-1; ++ii) { // note limits
    double x = a + ii*h;
    sum += func(x);
  }
  return h*sum;
}

template <typename fptr>
double trapezoid_richardson(const double a, const double b, const int n, fptr func)
{
  return (4*trapezoid_regular(a, b, 2*n, func) - trapezoid_regular(a, b, n, func))/3;
}

template <typename fptr>
double simpson(const double a, const double b, const int n, fptr func)
{
  int nlocal = n;
  if (n%2 != 0) {
    nlocal = n+1;
  }
  double sum = 0, result = func(a) + func(b);
  double x;
  const double h = (b-a)/nlocal;

  sum = 0;
  for(int ii = 1; ii <= nlocal/2 - 1; ++ii ) {
    x = a + 2*ii*h;
    sum += func(x);
  }
  result += 2*sum;

  sum = 0;
  for(int ii = 1; ii <= nlocal/2; ++ii ) {
    x = a + (2*ii-1)*h;
    sum += func(x);
  }
  result += 4*sum;

  return result*h/3;
}

template <typename fptr>
double simpson_rich(const double a, const double b, const int n, fptr func)
{
  return (4*simpson(a, b, 2*n, func) - simpson(a, b, n, func))/3;
}
